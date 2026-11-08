"""Compile generic visual state bindings from the hash-bound 1031 inventory.

Only animation composition is compiled. ACT behaviors, native damage/death
controllers, scripts and die-effect enums are not interpreted by this preview.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
from collections import Counter

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT.parent / "combat_ui_1031/handoff"


def load(path):
    return json.loads(path.read_text("utf-8"))


def main():
    manifest = load(SOURCE / "manifest.json")
    for name in ("data/monster-definitions.jsonl", "data/action-definitions.jsonl"):
        assert hashlib.sha256((SOURCE / name).read_bytes()).hexdigest() == manifest["files"][name]["sha256"]
    monsters = [json.loads(line) for line in (SOURCE / "data/monster-definitions.jsonl").read_text("utf-8").splitlines()]
    acts = {row["path"]: row for row in map(json.loads, (SOURCE / "data/action-definitions.jsonl").read_text("utf-8").splitlines())}

    def ref_at(record, field, slot):
        refs = [r for r in record["references"] if r["field_offset"] == field["offset"] and r["value_slot"] == slot]
        if len(refs) != 1 or len(refs[0]["existing_candidates"]) != 1:
            raise ValueError(f"Missing/ambiguous reference: {record['path']}:{field['offset']}:{slot}")
        return refs[0]["existing_candidates"][0]

    def plan(record, tag):
        fields = [f for f in record["fields"] if f["tag"] == tag and any(isinstance(v, str) and v.lower().endswith((".ani", ".act")) for v in f["values"])]
        if not fields:
            return None
        result = dict(binding_tag=tag, source=record["path"], source_offset=fields[0]["offset"],
                      tracks=[], issues=[], unexecuted_tags=[])
        try:
            refs = [(f, i) for f in fields for i, v in enumerate(f["values"]) if isinstance(v, str) and v.lower().endswith((".ani", ".act"))]
            if len(refs) != 1:
                raise ValueError(f"Expected one state entry: {tag}")
            field, slot = refs[0]
            target = ref_at(record, field, slot)
            result["entry"] = target
            result["kind"] = "motion" if target.endswith(".ani") else "action"
            if target.endswith(".ani"):
                result["tracks"] = [dict(path=target, start_frame=0, layer=0, x=0, y=0, role="base", source=record["path"], source_offset=field["offset"])]
                return result
            action = acts[target]
            result["action_sha256"] = action["sha256"]
            inside = False
            bases = 0
            for f in action["fields"]:
                tag2 = f["tag"].upper()
                if tag2 == "[MOTION]":
                    inside = True
                elif tag2 == "[/MOTION]":
                    inside = False
                elif inside and tag2 == "[BASE ANI]":
                    bases += 1
                    result["tracks"].append(dict(path=ref_at(action, f, 0), start_frame=0, layer=0, x=0, y=0, role="base", source=target, source_offset=f["offset"]))
                elif inside and tag2 in ("[SUB ANI]", "[SUB ANI WITH XY]"):
                    stride = 5 if tag2 == "[SUB ANI WITH XY]" else 3
                    values = f["values"]
                    if len(values) % stride:
                        raise ValueError(f"Unrecognized {tag2} tuple")
                    for i in range(0, len(values), stride):
                        if not isinstance(values[i], str) or not all(isinstance(x, int) for x in values[i+1:i+stride]):
                            raise ValueError(f"Unrecognized {tag2} types")
                        result["tracks"].append(dict(path=ref_at(action, f, i), start_frame=values[i+1], layer=values[i+2],
                                                     x=values[i+3] if stride == 5 else 0,
                                                     y=values[i+4] if stride == 5 else 0, role="sub", source=target, source_offset=f["offset"]))
                elif not inside and not tag2.startswith("[/"):
                    result["unexecuted_tags"].append(f["tag"])
            if bases != 1:
                raise ValueError("Expected exactly one MOTION base animation")
        except (ValueError, KeyError) as exc:
            result["issues"].append(str(exc))
            result["tracks"] = []
        return result

    state_tags = {
        "idle": ["[waiting motion]", "[waiting action]", "[basic action]"],
        "damage1": ["[damage motion 1]", "[damage action 1]"],
        "damage2": ["[damage motion 2]", "[damage action 2]"],
        "down": ["[down motion]", "[down action]"],
        "death": ["[last action]"],
    }
    rows = []
    counts = Counter()
    for monster in monsters:
        names = [v for f in monster["fields"] if f["tag"] == "[name]" for v in f["values"] if isinstance(v, str)]
        states = {}
        for key, tags in state_tags.items():
            for tag in tags:
                state = plan(monster, tag)
                if state is not None:
                    states[key] = state
                    break
            if key in states and states[key]["tracks"]:
                counts[key] += 1
        rows.append(dict(path=monster["path"], sha256=monster["sha256"], ids=monster["monster_list_ids"],
                         name=names[0] if names else Path(monster["path"]).stem,
                         states=states, die_effect=[f["values"] for f in monster["fields"] if f["tag"] == "[die effect]"]))
    # Order useful examples first, without changing generic binding logic.
    preferred = [5001, 1, 61491, 56013, 59005, 62638, 61192, 100004, 59001]
    def rank(row):
        match = next((preferred.index(i) for i in row["ids"] if i in preferred), len(preferred))
        return match, row["path"]
    rows.sort(key=rank)
    data = dict(schema_version=1, source=manifest["source"], default_id=5001, monsters=rows,
                scope="Visual state preview: direct ANI or ACT MOTION base/sub composition plus runtime ALS; native damage/death state machines and ACT behaviors are not executed.")
    (ROOT / "content").mkdir(exist_ok=True)
    (ROOT / "reports").mkdir(exist_ok=True)
    (ROOT / "content/monsters.json").write_text(json.dumps(data, ensure_ascii=False, separators=(",", ":")), "utf-8")
    report = dict(monsters=len(rows), configured_visual_states=dict(counts), runtime_all_monsters_verified=False,
                  catalog_sha256=hashlib.sha256((ROOT / "content/monsters.json").read_bytes()).hexdigest(), source=manifest["source"],
                  death_binding="Explicit [last action] preserved. Separate resource-backed frozen-pose/common death preview uses [die effect]; native route selection remains unverified.",
                  sample_reference={"actionsample.act": "1-14: SUB ANI tuples; source SHA256 4dc013c7b56e42f81add3ad2b6bacb42ac8c1ee63cbeaa1436608f95dd703039",
                                    "newmonstersample.mob": "282: last action before destruction; source SHA256 b37eb5e8dc0014c320e3a4596c457e5a2d56d431522ef0c020f74af251172bda"})
    (ROOT / "reports/catalog.json").write_text(json.dumps(report, ensure_ascii=False, indent=2), "utf-8")
    print(json.dumps({k:report[k] for k in ("monsters", "configured_visual_states")}, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
