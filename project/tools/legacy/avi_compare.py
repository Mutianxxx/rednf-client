"""Side-by-side reference video x skill previewer comparison.

The reference AVI is an independent observation of the shipping client. This
tool never feeds a measurement back into the mapping; it only puts the two
pictures next to each other and records the numeric gap so the review can say
"we stop at 280ms while the client keeps going for 3070ms" instead of "looks
wrong".

Client videos are wrapped in the Neople container ("Neople Video Fil" + a
running-XOR payload), so ffmpeg cannot open them directly. `decode_neople`
from reference_videos.py unwraps them; the decoded bytes are standard MPEG-1.

Usage:
  python tools/legacy/avi_compare.py --job 1 --skill 77 \
      --avi "D:/.../Video/Fighter/JunkSpin.avi" --out OUTDIR --samples 4
"""
from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from reference_videos import decode_neople  # noqa: E402

ROOT = Path(__file__).resolve().parents[3]
PREVIEWER = ROOT / "checkpoints" / "build" / "dnf_skill_previewer.exe"
PROFILE = ROOT / "project" / "content-profile.json"
TILE_W, TILE_H = 640, 360


def run(cmd: list[str], **kwargs) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, **kwargs)


def probe(avi: Path) -> dict:
    out = run(["ffprobe", "-v", "error", "-select_streams", "v:0", "-show_entries",
               "stream=width,height,nb_frames,duration", "-of", "json", str(avi)])
    if out.returncode != 0:
        raise RuntimeError("ffprobe failed: " + out.stderr.decode("utf-8", "replace")[:300])
    stream = json.loads(out.stdout.decode("utf-8", "replace"))["streams"][0]
    return {"width": int(stream["width"]), "height": int(stream["height"]),
            "frames": int(stream.get("nb_frames") or 0),
            "durationMs": float(stream.get("duration") or 0) * 1000.0}


def export_frames(avi: Path, samples: int, outdir: Path) -> list[Path]:
    """Even samples of the decoded stream, one tile each."""
    outdir.mkdir(parents=True, exist_ok=True)
    pattern = outdir / "raw_%03d.png"
    run(["ffmpeg", "-v", "error", "-i", str(avi), "-vf",
         f"scale={TILE_W}:{TILE_H}:flags=neighbor", "-vsync", "0", "-y", str(pattern)])
    frames = sorted(outdir.glob("raw_*.png"))
    if not frames:
        raise RuntimeError("no frames decoded from " + str(avi))
    picked: list[Path] = []
    for index in range(samples):
        # Centre of each equal slice: the first and last frames of these clips
        # are usually black or a fade, and would waste two of four tiles.
        at = min(len(frames) - 1, int((index + 0.5) * len(frames) / samples))
        target = outdir / f"ref_{index + 1}.png"
        shutil.copyfile(frames[at], target)
        picked.append(target)
    for frame in frames:
        frame.unlink(missing_ok=True)
    return picked


def capture_previewer(job: int, skill: int, times_ms: list[int], outdir: Path) -> list[Path]:
    outdir.mkdir(parents=True, exist_ok=True)
    shots: list[Path] = []
    for index, ms in enumerate(times_ms):
        target = outdir / f"our_{index + 1}.png"
        result = run([str(PREVIEWER), "--content-profile", str(PROFILE),
                      "--report-dir", str(outdir), "--job", str(job), "--skill", str(skill),
                      "--capture", str(target), "--capture-frames", "2",
                      "--capture-after-ms", str(ms)])
        if result.returncode != 0 or not target.exists():
            raise RuntimeError("previewer capture failed at %dms: %s"
                               % (ms, result.stderr.decode("utf-8", "replace")[:300]))
        shots.append(target)
    return shots


def stack(rows: list[list[Path]], out: Path) -> None:
    """rows[0] is the reference row, rows[1] the previewer row.

    hstack/vstack need every tile at the same size; the previewer renders at
    1280x720 while the reference frame is 160x90, so each input is scaled to the
    tile size first.
    """
    inputs: list[str] = []
    for row in rows:
        for tile in row:
            inputs.extend(["-i", str(tile)])
    count = len(rows[0])
    parts, scaled = [], []
    index = 0
    for r, row in enumerate(rows):
        chain = ""
        for _ in row:
            parts.append(f"[{index}:v]scale={TILE_W}:{TILE_H}:flags=neighbor[s{index}]")
            chain += f"[s{index}]"
            index += 1
        parts.append(f"{chain}hstack=inputs={count}[r{r}]")
        scaled.append(f"[r{r}]")
    parts.append("".join(scaled) + f"vstack=inputs={len(rows)}[out]")
    result = run(["ffmpeg", "-v", "error", "-y", *inputs, "-filter_complex", ";".join(parts),
                  "-map", "[out]", "-frames:v", "1", str(out)])
    if result.returncode != 0 or not out.exists():
        raise RuntimeError("ffmpeg stack failed: "
                           + result.stderr.decode("utf-8", "replace")[:400])


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--job", type=int, required=True)
    ap.add_argument("--skill", type=int, required=True)
    ap.add_argument("--avi", required=True, help="client .avi (Neople wrapper is unwrapped here)")
    ap.add_argument("--out", required=True)
    ap.add_argument("--samples", type=int, default=4)
    args = ap.parse_args()

    outdir = Path(args.out)
    outdir.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix="avicmp-"))

    source = Path(args.avi)
    if source.read_bytes()[:16] == b"Neople Video Fil":
        decoded = work / "decoded.avi"
        decoded.write_bytes(decode_neople(source.read_bytes()))
        video = decoded
        wrapped = True
    else:
        video = source
        wrapped = False

    info = probe(video)
    refs = export_frames(video, args.samples, work / "ref")

    # Sample the previewer on the reference clip's own clock: if the parse is
    # shorter than the video, the later tiles show the held last pose, which is
    # exactly the gap the report has to state.
    times = [int(info["durationMs"] * (i + 0.5) / args.samples) for i in range(args.samples)]
    ours = capture_previewer(args.job, args.skill, times, work / "our")
    comparison = outdir / "compare.png"
    stack([refs, ours], comparison)

    report_path = work / "our" / "skill-preview-report.json"
    parsed = json.loads(report_path.read_text(encoding="utf-8")) if report_path.exists() else {}
    layer_plan = parsed.get("layerPlan") or []
    births: dict[str, int] = {}
    for layer in layer_plan:
        key = str(int(layer.get("birthMs", 0)))
        births[key] = births.get(key, 0) + 1

    summary = {
        "source": str(source),
        "neopleWrapped": wrapped,
        "reference": info,
        "samplesMsOnReferenceClock": times,
        "parsedDurationMs": parsed.get("durationMs"),
        "parsedLayers": len(layer_plan),
        "parsedBirths": dict(sorted(births.items(), key=lambda kv: float(kv[0]))),
        "durationRatio": (round(parsed.get("durationMs", 0) / info["durationMs"], 3)
                          if info["durationMs"] else None),
        "skill": (parsed.get("skill") or {}).get("name"),
        "note": "The AVI is an observation, not a fitting target. Tiles are the "
                "reference above and the previewer below at the same reference time.",
    }
    (outdir / "compare.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2),
                                         encoding="utf-8")
    shutil.rmtree(work, ignore_errors=True)
    print(json.dumps(summary, ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
