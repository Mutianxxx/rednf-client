"""Reproduce structure validation without repairing source scripts."""
import argparse
import collections
import json
from pathlib import Path
import sys
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT/"combat-preview"))
from catalog import Catalog
from pvf_model import parse_animation


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvf", default=str(ROOT/"DFO"/"Script.pvf"))
    parser.add_argument("--all", action="store_true", help="Scan every ANI instead of only registered CHR references")
    args = parser.parse_args()
    catalog = Catalog(args.pvf)
    if args.all:
        names = [entry["path"] for entry in catalog.pvf.entries if entry["path"].endswith(".ani")]
    else:
        names = sorted({slot["path"] for character in catalog.characters for slot in character["slots"]
                        if slot["kind"] == "animation" and not slot["empty"]})
    started = time.monotonic()
    counts = collections.Counter()
    field_counts = collections.Counter()
    box_shapes = collections.Counter()
    records, failures, warnings, oddities = [], [], [], []
    for index, name in enumerate(names):
        try:
            animation = parse_animation(catalog.pvf.read(name), name)
            counts["parsed"] += 1
            counts["frames"] += animation["frame_count"]
            warnings.extend(dict(path=name, **warning) for warning in animation["warnings"])
            if not animation["frames"]:
                oddities.append(dict(path=name, kind="no_frames", size=animation["size"]))
            per_file = collections.Counter()
            bad_boxes = []
            for frame in animation["frames"]:
                per_file.update(field["tag"] for field in frame["fields"])
                for key in ("attack_boxes", "damage_boxes"):
                    counts[key] += len(frame[key])
                    for box in frame[key]:
                        box_shapes[(key, len(box))] += 1
                        if len(box) != 6 or not all(isinstance(value, (float, int)) for value in box):
                            box_record = dict(frame=frame["index"], kind=key, values=box)
                            bad_boxes.append(box_record)
                            oddities.append(dict(path=name, kind="non_six_number_box", box=box_record))
            field_counts.update(per_file)
            if not args.all:
                records.append(dict(path=name, sha256=animation["sha256"], size=animation["size"],
                                    frame_count=animation["frame_count"], warnings=animation["warnings"],
                                    field_counts=dict(per_file), non_six_number_boxes=bad_boxes,
                                    attack_box_count=sum(len(frame["attack_boxes"]) for frame in animation["frames"]),
                                    damage_box_count=sum(len(frame["damage_boxes"]) for frame in animation["frames"]),
                                    literal_delay_sum=sum(values[0] for frame in animation["frames"]
                                                          for values in frame["delays"]
                                                          if len(values) == 1 and isinstance(values[0], (int, float)))))
        except Exception as error:
            failures.append(dict(path=name, error=type(error).__name__, detail=str(error)))
        if index % 5000 == 0:
            print(index, "ANI checked", round(time.monotonic()-started, 1), "s", flush=True)
    result = dict(source=catalog.source, scope="All PVF ANI resources" if args.all else "All distinct registered CHR ANI references",
                  entry_count=len(names), counts=dict(counts), field_counts=dict(field_counts),
                  box_shapes={str(key): value for key, value in box_shapes.items()},
                  elapsed_seconds=time.monotonic()-started,
                  failures=failures, warnings=warnings, oddities=oddities)
    if not args.all:
        result.update(distinct_animations=len(names), parsed=counts["parsed"], frame_count=counts["frames"], records=records)
    target = Path(__file__).resolve().parent/("all-animation-validation.json" if args.all else "chr-animation-validation.json")
    target.write_text(json.dumps(result, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
    print(json.dumps({key: value for key, value in result.items()
                      if key not in ("source", "records", "warnings", "oddities", "failures")}, ensure_ascii=False, indent=2))
    print("failures", len(failures), "warnings", len(warnings), "oddities", len(oddities))


if __name__ == "__main__":
    main()
