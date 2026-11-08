"""Extract skill_id -> animation binding for all 6 native class controller regions.

Mechanism (established in the swordman case, generalized here):
  - each class region ends with jump tables (`jmp [idx*4 + base]`, FF 24 SIB disp32)
  - the skill setState table maps state -> handler; handlers select body motions
    via vtable+0x49C (etc-motion index) / +0x498 (index + 0x5B), reference skill
    ids via +0x7D0/+0x804/+0xA14, and pass ATK args through the 0x70213F thunk
  - skill->state pairs come from eligibility code (vtable+0x864(skill,1,1,1) ->
    vtable+0x30C(state,...)) found in the same region
  - PVF supplies: skill id -> .skl (class .lst), motion index -> .ani (chr
    etc_motion), skill -> effect .ani chain (sqr/common.nut)
"""
import json
import os
import re
import struct
import sys

sys.path.insert(0, r"D:\dnf-rebuild\gba-research\third_party\research-python")
import capstone
from capstone import CS_ARCH_X86, CS_MODE_32, CS_OP_REG, CS_OP_IMM, CS_OP_MEM

# Paths resolve from this file; override the client exe with DNF1031_EXE.
BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.environ.get("DNF1031_EXE", r"D:\dnf-rebuild\DNF1031客户端\DNF.exe")
IB = 0x400000


def va2off(va):
    rva = va - IB
    if 0x1000 <= rva < 0x115A000:
        return rva - 0x1000 + 0x400
    raise ValueError(hex(va))


f = open(EXE, "rb")
f.seek(va2off(0x401000))
TEXT = f.read(0x115A000 - 0x1000)
md = capstone.Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = True

CLASSES = [
    {"tag": "A", "region": (0xB00000, 0xBF31EC),
     "tables": [(0xBF2FF0, 62), (0xBF30E8, 52), (0xBF31B8, 13)]},
    {"tag": "B", "region": (0xBF31EC, 0xC2F344),
     "tables": [(0xC2F180, 52), (0xC2F250, 54), (0xC2F328, 7)]},
    {"tag": "C", "region": (0xC2F344, 0xC6D960),
     "tables": [(0xC6D894, 42), (0xC6D93C, 9)]},
    {"tag": "D", "region": (0xC6D960, 0xC90580),
     "tables": [(0xC90480, 40)]},
    {"tag": "E", "region": (0xC90580, 0xCA511C),
     "tables": [(0xCA5004, 53), (0xCA50D8, 13)]},
    {"tag": "F", "region": (0xCA511C, 0xCE1AE8),
     "tables": [(0xCE18A8, 60), (0xCE1998, 77), (0xCE1A9C, 12)]},
]

MOTION_SLOTS = {0x49C, 0x498}
SKILL_SLOTS = {0x7D0, 0x804, 0xA14, 0x864, 0x918}
ATK_THUNK = 0x70213F


def read_handler_events(handler, fence):
    """Linear disasm with resync up to fence; return (motions, skill_refs, atk_args)."""
    if not (0x401000 <= handler < 0x115A000) or fence <= handler:
        return [], [], []
    end = min(fence, handler + 0x1000)
    start_idx = handler - 0x401000
    code = TEXT[start_idx: start_idx + (end - handler)]
    regs, stack = {}, {}
    motions, skill_refs, atk_args = [], [], []
    pos = 0
    while pos < len(code):
        chunk = list(md.disasm(code[pos:], handler + pos))
        if not chunk:
            pos += 1
            regs = {}
            continue
        for insn in chunk:
            m = insn.mnemonic
            ops = insn.operands
            if m == "push":
                stack[insn.address] = ops[0].imm if ops and ops[0].type == CS_OP_IMM else None
            elif m == "mov" and len(ops) == 2:
                d, s = ops
                if d.type == CS_OP_REG and s.type == CS_OP_MEM and s.mem.index == 0 and s.mem.base != 0:
                    base = insn.reg_name(s.mem.base)
                    disp = s.mem.disp
                    dn = insn.reg_name(d.reg)
                    if base in ("esi", "ebx", "edi", "ecx") and disp == 0:
                        regs[dn] = ("vt", base)
                    elif regs.get(base, ("?",))[0] == "vt":
                        regs[dn] = ("slot", disp)
                    else:
                        regs[dn] = ("field",)
                elif d.type == CS_OP_REG and s.type == CS_OP_REG:
                    regs[insn.reg_name(d.reg)] = regs.get(insn.reg_name(s.reg), ("copy",))
                elif d.type == CS_OP_REG:
                    regs[insn.reg_name(d.reg)] = ("const",)
            elif m == "call":
                if ops and ops[0].type == CS_OP_REG:
                    tgt = regs.get(insn.reg_name(ops[0].reg))
                    if tgt and tgt[0] == "slot":
                        args = [stack[a] for a in sorted(stack) if a > (insn.address - 0x80)]
                        imms = [a for a in args if a is not None]
                        slot = tgt[1]
                        if slot in MOTION_SLOTS and imms:
                            for a in imms:
                                motions.append(a if slot == 0x49C else a + 0x5B)
                        elif slot in SKILL_SLOTS and imms:
                            cand = [a for a in imms if 0 < a <= 400]
                            if cand:
                                skill_refs.append(cand[-1])
                elif ops and ops[0].type == CS_OP_IMM:
                    if insn.address + insn.size + ops[0].imm == ATK_THUNK:
                        args = [stack[a] for a in sorted(stack) if a > (insn.address - 0x80)]
                        if args and args[0] is not None:
                            atk_args.append(args[0])
                stack = {}
            elif m == "add" and ops and ops[0].type == CS_OP_REG and insn.reg_name(ops[0].reg) == "esp":
                stack = {}
        last = chunk[-1]
        nxt = last.address + last.size - handler
        pos = nxt + 1 if nxt < len(code) else len(code)
        if last.mnemonic in ("ret", "int3", "hlt", "ud2"):
            regs = {}
            stack = {}
    return motions, skill_refs, atk_args


def scan_class(cls):
    """Scan all sub-table entries of one class; return entries with events."""
    entries = []
    for base, n in cls["tables"]:
        for i in range(n):
            target = struct.unpack_from("<I", TEXT, base - 0x401000 + i * 4)[0]
            if 0x401000 <= target < 0x115A000:
                entries.append({"table": base, "idx": i, "handler": target})
    fences = sorted({e["handler"] for e in entries})
    for e in entries:
        h = e["handler"]
        fence = next((x for x in fences if x > h), h + 0x1000)
        motions, refs, atk = read_handler_events(h, fence)
        e["motions"] = motions
        e["skill_refs"] = sorted(set(refs))
        e["atk_args"] = sorted(set(atk))
    return entries


def main():
    pairs = json.load(open(f"{BASE}\\all-class-skill-state-pairs.json"))

    # PVF inputs
    lsts = {}
    for name in ("swordman", "demonicswordman", "fighter", "atfighter", "gunner", "atgunner",
                 "mage", "atmage", "creatormage", "priest", "thief"):
        lst_file = f"{BASE}\\pvf-out\\skill\\{name}skill.lst.json"
        try:
            lsts[name] = json.load(open(lst_file, encoding="utf-8"))
        except FileNotFoundError:
            lsts[name] = json.load(open(f"{BASE}\\pvf-out\\skill\\{name}.lst.json", encoding="utf-8"))

    chrs = {}
    chr_of = {"swordman": "swordman/swordman", "demonicswordman": "swordman/demonicswordman",
              "fighter": "fighter/fighter", "atfighter": "fighter/atfighter",
              "gunner": "gunner/gunner", "atgunner": "gunner/atgunner",
              "mage": "mage/mage", "atmage": "mage/atmage", "creatormage": "mage/creatormage",
              "priest": "priest/priest", "thief": "thief/thief"}
    for name, chrf in chr_of.items():
        c = json.load(open(f"{BASE}\\pvf-out\\character\\{chrf}.chr.json", encoding="utf-8"))
        em = next((i["etc_motion"] for i in c if isinstance(i, dict) and "etc_motion" in i), None)
        chrs[name] = em

    nut = json.load(open(f"{BASE}\\pvf-out\\sqr\\common.nut.json", encoding="utf-8"))["content"]
    enum = json.load(open(f"{BASE}\\pvf-out\\sqr\\dnf_enum_header.nut.json", encoding="utf-8"))["content"]
    SK = {}
    for src in (enum, nut):
        for m in re.finditer(r"(SKILL_[A-Z_0-9]+)\s*(?:<-|=)\s*(\d+)", src):
            SK[m.group(1)] = int(m.group(2))

    effects_by_class = {}
    for m in re.finditer(r"function\s+sq_LoadSkillEffect_(\w+)\s*\(.*?\)\s*\{(.*?)\n\}", nut, re.S):
        fname, body = m.group(1), m.group(2)
        eff = {}
        cur = None
        for line in body.splitlines():
            bm = re.search(r"skillIndex\s*==\s*(SKILL_[A-Z_0-9]+)", line)
            if bm:
                cur = SK.get(bm.group(1))
                if cur is not None and cur not in eff:
                    eff[cur] = []
                continue
            am = re.search(r'sq_LoadSkillEffectAni\s*\(\s*skillIndex\s*,\s*"([^"]+)"', line)
            if am and cur is not None:
                eff[cur].append(am.group(1))
        if eff:
            effects_by_class.setdefault(fname.lower(), {}).update(eff)

    def stem_of(path):
        return path.rsplit("/", 1)[-1].rsplit(".", 1)[0].lower()

    report = []
    for cls in CLASSES:
        tag = cls["tag"]
        lo, hi = cls["region"]
        region_pairs = [p for p in pairs if p["skill"] and lo <= int(p["at"], 16) < hi]
        entries = scan_class(cls)

        # resolve state offset per table by voting with eligibility pairs
        table_off, table_votes = {}, {}
        for base, n in cls["tables"]:
            te = [e for e in entries if e["table"] == base]
            offs = {}
            for p in region_pairs:
                for e in te:
                    if p["skill"] in e["skill_refs"]:
                        o = p["state"] - e["idx"]
                        offs[o] = offs.get(o, 0) + 1
            if offs:
                best = max(offs, key=offs.get)
                table_off[base] = best
                table_votes[base] = offs[best]
            else:
                table_off[base] = 3
                table_votes[base] = 0

        # primary skill-state table: strongest vote; fallback largest table @off 3
        primaries = [b for b, _ in cls["tables"]]
        primary = max(primaries, key=lambda b: table_votes[b]) if any(table_votes.values()) else None
        if primary is None or table_votes[primary] < 3:
            primary = max(cls["tables"], key=lambda t: t[1])[0]
            table_off[primary] = 3

        # state -> entry map from the primary table only
        state_map = {}
        for e in entries:
            if e["table"] == primary:
                state_map.setdefault(e["idx"] + table_off[primary], e)

        # skill -> states: eligibility pairs + handler skill refs
        skill_states = {}
        for p in region_pairs:
            skill_states.setdefault(p["skill"], set()).add(p["state"])
        for st, e in state_map.items():
            for sid in e["skill_refs"]:
                skill_states.setdefault(sid, set()).add(st)

        # attribution: which class lsts does this region serve?
        # score = 3 * index-aligned motion matches + 1 * name-existence matches
        def chr_namepool(name):
            chrj = json.load(open(
                f"{BASE}\\pvf-out\\character\\{chr_of[name]}.chr.json", encoding="utf-8"))
            pool = set()
            for i in chrj:
                if isinstance(i, dict):
                    for k, v in i.items():
                        if "motion" in k and isinstance(v, list):
                            pool.update(stem_of(p) for p in v)
            return pool

        def motion_index_map(name):
            chrj = json.load(open(
                f"{BASE}\\pvf-out\\character\\{chr_of[name]}.chr.json", encoding="utf-8"))
            return next((i["etc_motion"] for i in chrj
                         if isinstance(i, dict) and "etc_motion" in i), None)

        scores = {}
        for name, lst in lsts.items():
            em = motion_index_map(name) or []
            pool = chr_namepool(name)
            aligned, named = 0, 0
            for sid, states in skill_states.items():
                skl = lst.get(str(sid))
                if not skl:
                    continue
                skl_stem = stem_of(skl)[:8]
                a = False
                for st in states:
                    e = state_map.get(st)
                    if not e:
                        continue
                    for midx in e["motions"]:
                        if 0 <= midx < len(em) and stem_of(em[midx]).startswith(skl_stem):
                            a = True
                            break
                    if a:
                        break
                if a:
                    aligned += 1
                elif skl_stem and any(s.startswith(skl_stem) for s in pool):
                    named += 1
            if aligned or named:
                scores[name] = {"aligned": aligned, "named": named}
        # exclusive-id evidence: region skill ids present only in this lst
        for name, lst in lsts.items():
            exclusive = sum(1 for sid in skill_states
                            if str(sid) in lst
                            and all(str(sid) not in other
                                    for oname, other in lsts.items() if oname != name))
            if name in scores:
                scores[name]["exclusive"] = exclusive
            elif exclusive:
                scores[name] = {"aligned": 0, "named": 0, "exclusive": exclusive}

        def covered_of(sc):
            al = {k: v["aligned"] for k, v in sc.items() if v.get("aligned")}
            if al and max(al.values()) >= 3:
                top = max(al.values())
                return [k for k, v in sc.items() if v.get("aligned", 0) >= max(3, 0.3 * top)]
            ex_ = {k: v["exclusive"] for k, v in sc.items() if v.get("exclusive")}
            if ex_ and max(ex_.values()) >= 3:
                top = max(ex_.values())
                return [k for k, v in sc.items() if v.get("exclusive", 0) >= max(3, 0.4 * top)]
            return []

        covered = covered_of(scores)
        report.append({"tag": tag, "region": [hex(lo), hex(hi)], "pairs": len(region_pairs),
                       "states": len(state_map), "skill_ids": len(skill_states),
                       "covered_classes": {k: scores[k] for k in covered}})

        # per-class binding build
        for name in covered:
            lst = lsts[name]
            em = chrs.get(name) or []
            job_dir = f"character/{name}"
            eff_map = {}
            for fname, eff in effects_by_class.items():
                if fname == name or fname.startswith(name):
                    eff_map.update(eff)
            out = {"class": name, "exe_region": [hex(lo), hex(hi)],
                   "etc_motion": {str(i): p for i, p in enumerate(em)},
                   "skills": {}}
            all_ids = sorted(set([int(k) for k in lst] + list(skill_states)))
            for sid in all_ids:
                skl = lst.get(str(sid))
                states = []
                for st in sorted(skill_states.get(sid, [])):
                    e = state_map.get(st)
                    if not e:
                        continue
                    states.append({
                        "state": st,
                        "handler": f"0x{e['handler']:08x}",
                        "entry_motions": [{"index": m, "ani": em[m]} for m in e["motions"] if 0 <= m < len(em)],
                        "atk_selector_args": e["atk_args"],
                    })
                if skl and not states:
                    # name-inferred chain from chr table
                    skl_stem = stem_of(skl)
                    inferred = [i for i, p in enumerate(em) if stem_of(p).startswith(skl_stem[:8])]
                    if inferred:
                        states.append({"state": None, "handler": None,
                                       "entry_motions": [{"index": i, "ani": em[i]} for i in inferred],
                                       "note": "name-inferred"})
                if states or skl:
                    out["skills"][sid] = {"skl": skl,
                                          "states": states,
                                          "effect_anis": eff_map.get(sid)}
            path = f"{BASE}\\bindings\\{name}-skill-binding.json"
            json.dump(out, open(path, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
            n_exe = sum(1 for s in out["skills"].values() if any(x["state"] for x in s["states"]))
            print(f"[{tag}] {name}: skills={len(out['skills'])} with_exe_state={n_exe} "
                  f"effects={sum(1 for s in out['skills'].values() if s['effect_anis'])}")

    json.dump(report, open(f"{BASE}\\all-class-report.json", "w"), indent=1)
    print("\n== attribution ==")
    for r in report:
        print(f"region {r['tag']} {r['region']}: pairs={r['pairs']} states={r['states']} "
              f"ids={r['skill_ids']} covered={r['covered_classes']}")


if __name__ == "__main__":
    main()
