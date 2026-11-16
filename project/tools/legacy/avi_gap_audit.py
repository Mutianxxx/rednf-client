"""Whole-pack duration audit: parsed nominal action clock vs the client video.

A Neople video is `Neople Video Fil` + a wrapper length at 0x18 + a RIFF AVI
whose first 1024 bytes are stored in clear (the running XOR starts at offset
1024). The AVI `avih` chunk therefore sits at a fixed place: microseconds per
frame at +0x20, total frames at +0x30 of the unwrapped buffer. Reading those
two fields gives the clip length without decoding a single video frame, so the
whole Video/ tree costs seconds instead of minutes.

Usage:
  python tools/legacy/avi_gap_audit.py --audit OUTDIR/skill-map-audit.json \
      --video-root "D:/.../Video" --output report.json
"""
from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path

SKILL_SUFFIX = ".skl"


def clip_seconds(path: Path) -> float | None:
    raw = path.read_bytes()[:4096]
    if len(raw) < 64 or raw[:16] != b"Neople Video Fil":
        return None
    body = raw[32:]
    if body[:4] != b"RIFF":
        return None
    micros_per_frame, frames = struct.unpack_from("<II", body, 0x20)[0], \
        struct.unpack_from("<I", body, 0x30)[0]
    if not micros_per_frame or not frames:
        return None
    return micros_per_frame * frames / 1_000_000.0


def normalise(name: str) -> str:
    return "".join(ch for ch in name.lower() if ch.isalnum())


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--audit", required=True, help="skill-map-audit.json from --audit-map")
    ap.add_argument("--video-root", required=True)
    ap.add_argument("--output", required=True)
    args = ap.parse_args()

    audit = json.loads(Path(args.audit).read_text(encoding="utf-8"))

    # stem -> rows, so a clip can find every skill that could own it.
    by_stem: dict[str, list[dict]] = {}
    for job in audit["jobs"]:
        for row in job["skills"]:
            skill_path = row.get("skillPath") or ""
            if not skill_path.lower().endswith(SKILL_SUFFIX):
                continue
            stem = normalise(Path(skill_path).stem)
            by_stem.setdefault(stem, []).append({
                "jobId": job["jobId"],
                "skillId": row["skillId"],
                "name": row["name"],
                "nominalMs": row.get("nominalActionMs"),
                "bodyAni": row.get("bodyAni"),
                "layers": len(row.get("effectLayers") or []),
                "grade": row.get("grade"),
            })

    clips: list[dict] = []
    for clip in sorted(Path(args.video_root).glob("*/*.avi")):
        seconds = clip_seconds(clip)
        if not seconds:
            continue
        rows = by_stem.get(normalise(clip.stem)) or []
        entry = {"clip": str(clip.relative_to(args.video_root)).replace("\\", "/"),
                 "clipMs": round(seconds * 1000.0),
                 "matches": rows}
        for row in rows:
            nominal = row.get("nominalMs") or 0
            row["ratio"] = round(nominal / (seconds * 1000.0), 3) if nominal else None
        clips.append(entry)

    matched = [c for c in clips if c["matches"]]
    flat = []
    for clip in matched:
        for row in clip["matches"]:
            if row["ratio"] is None:
                continue
            flat.append({"clip": clip["clip"], "clipMs": clip["clipMs"], **row})
    flat.sort(key=lambda item: item["ratio"])

    report = {
        "videoRoot": args.video_root,
        "clips": len(clips),
        "matchedClips": len(matched),
        "rowsCompared": len(flat),
        "note": "ratio = parsed nominal action clock / client clip length. The clip "
                "includes the player's own input timing, so a low ratio is not proof "
                "of a short animation; it marks a row whose nominal clock is far from "
                "the demonstration and has to be explained (input-wait sentinel, "
                "missing state, or a genuinely short cut).",
        "shortest10": flat[:10],
        "longest10": list(reversed(flat[-10:])),
        "rows": flat,
    }
    Path(args.output).write_text(json.dumps(report, ensure_ascii=False, indent=2),
                                 encoding="utf-8")
    print(json.dumps({k: report[k] for k in ("clips", "matchedClips", "rowsCompared")},
                     ensure_ascii=False))
    print("--- nominal far below the clip ---")
    for item in flat[:8]:
        print("  ratio %-7s %-32s nominal=%-8s clip=%-6s job%d skill%d %s" % (
            item["ratio"], item["clip"], item["nominalMs"], item["clipMs"],
            item["jobId"], item["skillId"], item["name"]))
    print("--- nominal far above the clip ---")
    for item in reversed(flat[-8:]):
        print("  ratio %-7s %-32s nominal=%-8s clip=%-6s job%d skill%d %s" % (
            item["ratio"], item["clip"], item["nominalMs"], item["clipMs"],
            item["jobId"], item["skillId"], item["name"]))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
