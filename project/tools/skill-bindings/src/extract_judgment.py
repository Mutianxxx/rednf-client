"""Extract exe judgment (attack-launch) evidence from state-handler-events.json.

The ATK selector thunk 0x70213F is called inside each skill's setState handler to
launch an attack volume. Its first immediate argument is the ATTACK INDEX into the
skill's .atk resource. This script correlates every ATK-selector call with the
skill that owns the handler (via the per-class binding JSONs) and emits a flat
evidence file the previewer can join on the skill stem to mark a skill's judgment
as exe-verified rather than ANI-box-inferred.

Evidence grade: state-handler-events.json is a static capstone scan of the on-disk
1031 DNF.exe text segment (unpacked, disk-clear). The .atk geometry itself is read
from PVF; this file is the exe -> PVF link proving *which* .atk a state launches
and *when* (the call site address). The ATK selector is Themida-VM protected, so
the immediate is recorded as-is and not yet translated to a .atk file name.

Attribution caveat: the on-disk handler -> skill mapping is many-to-one for shared
states (e.g. the generic hard-attack state serves both HardAttack and its charged
variant). Those cases are emitted for every claiming skill and flagged `shared`,
because only the runtime skill_id selector (vtable +0x804) picks the concrete .atk.
"""
import json
import os
import glob

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))  # .../skill-bindings
EVID = os.path.join(BASE, "evidence")
ATK_SEL = "0x0070213f"
EFFECT_ATTACH = {"0x00690210", "0x00690420"}


def stem_of(path):
    return os.path.basename(path).split(".", 1)[0].lower()


def decode_name(g):
    try:
        return g.encode("cp949").decode("gbk")
    except Exception:
        return g


events = json.load(open(os.path.join(EVID, "state-handler-events.json")))

# Display names from skill-names.json, keyed by (class, skill_id).
_names = json.load(open(os.path.join(EVID, "skill-names.json")))
name_cache = {}
for cls, skills in _names.items():
    for sid, info in skills.items():
        name_cache[(str(cls), int(sid))] = info.get("name", "")

# handler_claims keyed by (handler, state). The evidence file was scanned from the
# swordman setState table (0xCE1998), so we only correlate against the swordman
# family; handler addresses are shared *generic* code across classes, so state
# NUMBER is required too. Both keys together are the exact join.
SWORD_FAMILY = {"swordman", "demonicswordman"}
handler_claims = {}
for bpath in glob.glob(os.path.join(BASE, "bindings", "*.json")):
    b = json.load(open(bpath))
    cls = b.get("class")
    if cls not in SWORD_FAMILY:
        continue
    for sid, sk in b.get("skills", {}).items():
        skl = sk.get("skl", "")
        if not skl:
            continue
        claim = {"class": cls, "skill_id": int(sid), "skl": skl,
                 "stem": stem_of(skl)}
        for st in sk.get("states", []):
            if st.get("state") is None:
                continue
            h = (st.get("handler") or "").lower()
            if not h:
                continue
            bucket = handler_claims.setdefault((h, int(st["state"])), [])
            if all(c["skill_id"] != claim["skill_id"] or c["class"] != claim["class"] for c in bucket):
                bucket.append(claim)

# Collect per state the ATK-selector calls and effect-attach calls.
per_state_atk = {}
per_state_eff = {}
handler_by_state = {}
for st, rec in events.items():
    st = int(st)
    handler_by_state[st] = (rec.get("handler") or "").lower()
    for e in rec.get("events", []):
        tgt = e.get("target")
        if tgt == ATK_SEL:
            args = e.get("args", [])
            per_state_atk.setdefault(st, []).append({
                "atk_index": args[0] if args else None,
                "n_args": len(args),
                "at": e.get("at"),
            })
        elif tgt in EFFECT_ATTACH:
            per_state_eff.setdefault(st, []).append({
                "target": tgt, "args": e.get("args"), "at": e.get("at"),
            })

# Group by skill stem; a shared handler fans out to every claiming skill.
judgments = {}
for st, calls in per_state_atk.items():
    claims = handler_claims.get((handler_by_state.get(st), st), [])
    if not claims:
        grp = judgments.setdefault(f"state{st}",
                                   {"state": st, "skill": None, "atk_calls": []})
        for c in calls:
            c["state"] = st
        grp["atk_calls"].extend(calls)
        continue
    shared = len(claims) > 1
    for claim in claims:
        key = claim["stem"]
        grp = judgments.setdefault(key, {
            "class": claim["class"], "skill_id": claim["skill_id"], "skl": claim["skl"],
            "name": decode_name(name_cache.get((str(claim["class"]), claim["skill_id"]), "")),
            "atk_calls": [], "states": [], "shared_handler": False,
        })
        if shared:
            grp["shared_handler"] = True
        for c in calls:
            c2 = dict(c)
            c2["state"] = st
            grp["atk_calls"].append(c2)
        if st not in grp["states"]:
            grp["states"].append(st)

for grp in judgments.values():
    grp.setdefault("states", [])
    grp["states"].sort()

effect_attach = {str(k): v for k, v in per_state_eff.items()}

summary = {
    "source": "evidence/state-handler-events.json (capstone static scan of 1031 DNF.exe on-disk text segment)",
    "atk_selector": ATK_SEL,
    "effect_attach_targets": sorted(EFFECT_ATTACH),
    "note": ("ATK selector first immediate arg = attack index into the skill's .atk resource; "
             "proves which attack volume a state launches. Geometry is read from PVF .atk; this is "
             "the exe->PVF dispatch link. The selector sits in a Themida VM region, so the immediate "
             "is recorded as-is (not yet translated to a .atk file name)."),
    "attribution_caveat": ("On-disk handlers are many-to-one for shared states; those groups carry "
                           "shared_handler=true because only the runtime skill_id selector picks the "
                           "concrete .atk."),
    "skills_with_judgment": len([k for k in judgments if not k.startswith("state")]),
    "states_total_with_atk": len(per_state_atk),
    "shared_handler_skills": len([k for k, v in judgments.items()
                                  if v.get("shared_handler")]),
}

out_path = os.path.join(EVID, "judgment-events.json")
json.dump({"summary": summary, "judgments": judgments, "effect_attach": effect_attach},
          open(out_path, "w"), indent=1, ensure_ascii=False)
print("wrote", out_path)
print("skills_with_judgment:", summary["skills_with_judgment"],
      "states_with_atk:", summary["states_total_with_atk"],
      "shared:", summary["shared_handler_skills"])
for k in list(judgments.keys())[:8]:
    print(" ", k, json.dumps(judgments[k], ensure_ascii=False)[:230])
