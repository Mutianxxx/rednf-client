"""Final builder: swordman skill_id -> animation binding.

Combines:
  A. exe state-handler analysis (entry motions, ATK args)      [state-handler-events.json]
  B. exe proc-eligibility pairs (skill -> state)               [skill-state-pairs verified manually]
  C. PVF CHR etc_motion table (motion index -> .ani)           [pvf-out/character/swordman/swordman.chr.json]
  D. PVF skilllist (skill_id -> .skl)                           [pvf-out/skill/swordmanskill.lst.json]
  E. PVF names (CP949-misread-as-GBK mojibake -> Chinese)      [skill-names.json]
  F. PVF sqr/common.nut effect bindings (skill -> effect .anis)
  G. name-inferred phase motions (etc_motion entries matching skl name)
"""
import json
import os
import re

# Resolves from this file: pvf-out/ and evidence/ live under tools/skill-bindings/.
BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EVID = os.path.join(BASE, "evidence")
# Provenance recorded into the binding JSON; archived files keep the path used at
# extraction time (D:/game/...-20260708), override with DNF1031_EXE on re-runs.
EXE = os.environ.get("DNF1031_EXE", r"D:\dnf-rebuild\DNF1031客户端\DNF.exe")

events = json.load(open(f"{EVID}\\state-handler-events.json"))
chrj = json.load(open(f"{BASE}\\pvf-out\\character\\swordman\\swordman.chr.json"))
lst = json.load(open(f"{BASE}\\pvf-out\\skill\\swordmanskill.lst.json"))
names = json.load(open(f"{EVID}\\skill-names.json"))["swordman"]

etc_motion = next(i["etc_motion"] for i in chrj if isinstance(i, dict) and "etc_motion" in i)
etc_atk = next((i["etc_attack_info"] for i in chrj if isinstance(i, dict) and "etc_attack_info" in i), None)

def fix_name(s):
    if not isinstance(s, str):
        return None
    try:
        return s.encode("cp949").decode("gbk")
    except Exception:
        try:
            return s.encode("cp949", errors="ignore").decode("gbk", errors="replace")
        except Exception:
            return s

# ---- function boundary fences: all known code entry points ----
import struct
IMG = r"D:\game\DNF1031客户端-20260708\DNF1031客户端\skill-bind-dump\ck3-exe-image.bin"
img = open(IMG, "rb").read()
fences = set()
for i in range(77):
    v = struct.unpack("<I", img[0xCE1998 - 0x400000 + i * 4:][:4])[0]
    if 0x400000 < v < 0x115A000:
        fences.add(v)
for i in range(35):
    v = struct.unpack("<I", img[0xCCA2DC - 0x400000 + i * 4:][:4])[0]
    if 0x400000 < v < 0x115A000:
        fences.add(v)
fences = sorted(fences)

def fn_end(handler):
    h = int(handler, 16)
    for f in fences:
        if f > h:
            return f
    return h + 0x800

# ---- F: common.nut effect bindings ----
nut = json.load(open(f"{BASE}\\pvf-out\\sqr\\common.nut.json", encoding="utf-8"))
txt = nut["content"]
enum = json.load(open(f"{BASE}\\pvf-out\\sqr\\dnf_enum_header.nut.json", encoding="utf-8"))["content"]
SK = {}
for src in (enum, txt):
    for m in re.finditer(r"(SKILL_[A-Z_0-9]+)\s*(?:<-|=)\s*(\d+)", src):
        SK[m.group(1)] = int(m.group(2))

m = re.search(r"function\s+sq_LoadSkillEffect_Swordman\(.*?\)\s*\{(.*?)\n\}", txt, re.S)
body = m.group(1)
# split into branches: if (skillIndex == SKILL_X) { ... }
effects = {}
cur = None
branch_re = re.compile(r"skillIndex\s*==\s*(SKILL_[A-Z_0-9]+)")
for line in body.splitlines():
    bm = branch_re.search(line)
    if bm:
        cur = SK.get(bm.group(1))
        if cur is not None and cur not in effects:
            effects[cur] = []
        continue
    am = re.search(r'sq_LoadSkillEffectAni\s*\(\s*skillIndex\s*,\s*"([^"]+)"', line)
    if am and cur is not None:
        effects[cur].append(am.group(1))

# ---- A+B: state handler analysis ----
MOTION_SLOT, MOTION_SLOT2 = 0x49C, 0x498
SKILL_SLOTS = {0x804, 0x7D0, 0xA14}
ATK_THUNK = "0x0070213f"

state_info = {}
for state, rec in events.items():
    skill_ids, motions, atk_args = [], [], []
    fend = fn_end(rec["handler"])
    for e in rec["events"]:
        if int(e["at"], 16) >= fend:
            continue  # event belongs to the adjacent function
        if e["kind"] == "vtcall":
            if e["slot"] in SKILL_SLOTS and e["args"]:
                cand = [a for a in e["args"] if isinstance(a, int) and 0 < a <= 300]
                if cand:
                    skill_ids.append(cand[-1])
            elif e["slot"] == MOTION_SLOT and e["args"]:
                for a in e["args"]:
                    if isinstance(a, int) and 0 <= a < len(etc_motion):
                        motions.append(a)
            elif e["slot"] == MOTION_SLOT2 and e["args"]:
                for a in e["args"]:
                    idx = a + 0x5B
                    if isinstance(a, int) and 0 <= idx < len(etc_motion):
                        motions.append(idx)
        elif e["kind"] == "call" and e["target"] == ATK_THUNK and e["args"]:
            atk_args.append(e["args"][0])
    state_info[int(state)] = {
        "handler": rec["handler"],
        "skill_ids": sorted(set(skill_ids)),
        "entry_motions": motions,
        "atk_args": sorted(set(atk_args)),
    }

# manual verified skill->state additions (proc eligibility evidence)
VERIFIED_PAIRS = {
    5: [20],    # 鬼斩: queue at 0xCC2D5E (skill5 cmd -> state 20), handler +0x49C(1)
    8: [22],    # 三段斩: queue at 0xCC25BA region (+0x864(1,1,1,8) -> +0x30C(0,0,1,22))
    46: [30],   # 上挑 (proc pair 0xCC81CF)
    11: [29], 64: [35], 86: [47], 87: [50], 88: [51], 107: [62],
}

skill_states = {}
for state, si in state_info.items():
    for sid in si["skill_ids"]:
        skill_states.setdefault(sid, []).append(state)
for sid, sts in VERIFIED_PAIRS.items():
    for st in sts:
        if st not in skill_states.get(sid, []):
            skill_states.setdefault(sid, []).append(st)

def name_infer_motions(skl_name):
    """etc_motion entries whose base name matches the skl name (case-insensitive)."""
    if not skl_name:
        return []
    base = skl_name.replace("Swordman/", "").replace(".skl", "").lower()
    out = []
    for i, m in enumerate(etc_motion):
        mn = m.replace("Animation/", "").replace(".ani", "").lower()
        if mn == base or mn.startswith(base):
            out.append(i)
    return out

out = {
    "_meta": {
        "title": "DNF 1031 swordman skill_id -> animation binding",
        "source_exe": EXE.replace("\\", "/"),
        "exe_sha256": "246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264",
        "source_pvf": "Script.pvf sha256 d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d",
        "mechanism": {
            "setstate_table": "0xCE1998[state-3] -> handler (disk plaintext, verified states 3..79)",
            "vtable": "0x1706a24 (character class vtable)",
            "slot_0x49c": "select etc-motion (body animation) by index -> 0x84ce20, array at char+0x2c64",
            "slot_0x498": "etc-motion index + 0x5b",
            "slot_0x804_0x7d0_0xa14": "skill-id arg (0x84b100: skill table at char+0x4414+growtype*0x3fc+id*4)",
            "atk_thunk_0x70213f": "protected ATK selector arg; CHR etc_attack_info space (translation unresolved, same as prior contract)",
            "state_queue": "vtable+0x30C(state, vec, priority, ...) after +0x864(skill,1,1,1) eligibility",
            "effect_map": "char+0x5e38[skillId] list, loaded by sqr/common.nut sq_LoadSkillEffectAni, lookup 0x690420",
        },
        "validation_anchors": {
            "state29_dashattackmultihit": "motion 11, ATK arg 14 (matches dnf-native-demo contract)",
            "state35_gorecross": "motion 25, ATK arg 24 (matches contract)",
        },
        "evidence_tiers": {
            "entry_motion": "immediate arg of vtable+0x49c call in setState handler (disk exe)",
            "phase_motion": "additional +0x49c args in handler body / name-inferred from CHR table",
            "effect": "PVF sqr/common.nut sq_LoadSkillEffect_Swordman branch (authoritative)",
        },
        "limits": [
            "ATK selector immediate -> actual .atk path translation remains protected (0x70213f VM thunk)",
            "some basic movement states (3..18 default handler 0xcdc8a8) carry no skill id",
            "buff skills (e.g. Khazan 25) cast via generic buff state; visual comes from passiveobject .obj",
        ],
    },
    "etc_motion": {str(i): p for i, p in enumerate(etc_motion)},
    "skills": {},
}

for sid in sorted(set(list(skill_states.keys()) + [int(k) for k in lst.keys()])):
    sid = int(sid)
    skl = lst.get(str(sid))
    nm = names.get(str(sid), {})
    cname = fix_name(nm.get("name")) if nm else None
    rec = {"skl": skl, "name": cname, "states": [], "effect_anis": effects.get(sid)}
    skl_base = skl.replace("Swordman/", "").replace(".skl", "") if skl else None
    for state in sorted(skill_states.get(sid, [])):
        si = state_info.get(state, {"handler": None, "entry_motions": [], "atk_args": []})
        inferred = name_infer_motions(skl)
        rec["states"].append({
            "state": state,
            "handler": si.get("handler"),
            "entry_motions": [{"index": m, "ani": etc_motion[m]} for m in si.get("entry_motions", [])],
            "phase_motions_inferred": [{"index": m, "ani": etc_motion[m]} for m in inferred
                                        if m not in si.get("entry_motions", [])],
            "atk_selector_args": si.get("atk_args", []),
        })
    if not rec["states"] and skl_base:
        # no exe state found: name-inferred motions only
        inferred = name_infer_motions(skl)
        if inferred:
            rec["states"].append({
                "state": None,
                "handler": None,
                "entry_motions": [],
                "phase_motions_inferred": [{"index": m, "ani": etc_motion[m]} for m in inferred],
                "atk_selector_args": [],
                "note": "no native state handler skill-id found; motions inferred by skl-name match in CHR etc_motion",
            })
    out["skills"][sid] = rec

path = os.path.join(BASE, "bindings", "swordman-skill-binding.json")
json.dump(out, open(path, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
print(f"written {path}")
print(f"skills: {len(out['skills'])}, with exe states: {len([s for s in out['skills'].values() if any(st['state'] for st in s['states'])])}, with effects: {len([s for s in out['skills'].values() if s['effect_anis']])}")

print("\n== four cast skills final ==")
for sid in (5, 65, 58, 25):
    s = out["skills"].get(str(sid)) or out["skills"].get(sid)
    print(f"skill {sid} {s['name']} ({s['skl']}):")
    print(f"  effects: {s['effect_anis']}")
    for st in s["states"]:
        print(f"  state {st['state']}: entry={[(m['index'], m['ani']) for m in st['entry_motions']]} "
              f"inferred={[(m['index'], m['ani']) for m in st['phase_motions_inferred']]} atk={st['atk_selector_args']}")
