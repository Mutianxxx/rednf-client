"""Decode local Neople AVI references and export hash-bound visual timelines.

Original files are read-only. Pure decoded AVI bytes are kept separately from
square-pixel display MP4s. Requires ffmpeg/ffprobe on PATH; Python uses stdlib.
These references are evidence, never a claim that the C++ renderer matches them.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import shutil
import struct
import subprocess


ROOT = Path(__file__).resolve().parents[1]
BASE_SKILLS = (
    "UpperSlash", "HardAttack", "TripleSlash", "DashAttackMultiHit", "AshenFork",
    "JumpAttackMulti", "NormalWave", "Khazan", "VaneSlash", "GoreCross", "HopSmash",
    "MoonlightSlash", "Guard",
)


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for data in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(data)
    return h.hexdigest()


def decode_neople(raw: bytes) -> bytes:
    if len(raw) < 32 or raw[:16] != b"Neople Video Fil":
        raise ValueError("Not a Neople Video Fil wrapper")
    size = struct.unpack_from("<I", raw, 0x18)[0]
    if size < 12 or 32 + size > len(raw):
        raise ValueError("Invalid Neople output length")
    result = bytearray(raw[32:32 + size])
    for i in range(1024, size):
        result[i] ^= result[i - 1024]
    if result[:4] != b"RIFF" or result[8:12] != b"AVI ":
        raise ValueError("Decoded data is not RIFF AVI")
    if struct.unpack_from("<I", result, 4)[0] + 8 != size:
        raise ValueError("Decoded RIFF size does not match wrapper output length")
    return bytes(result)


def run(command: list[str]) -> str:
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode:
        raise RuntimeError("Command failed: " + repr(command) + "\n" +
                           result.stderr.decode("utf-8", "replace"))
    return result.stdout.decode("utf-8", "replace")


def probe(tool: str, path: Path) -> dict:
    return json.loads(run([tool, "-v", "error", "-show_entries",
                           "stream=codec_name,width,height,r_frame_rate,sample_aspect_ratio,display_aspect_ratio,duration:format=duration",
                           "-of", "json", str(path)]))


def timeline(ffmpeg: str, source: Path, directory: Path, step: float, duration: float) -> list[dict]:
    directory.mkdir(parents=True, exist_ok=True)
    # Work from display-corrected pixels. No resizing or sharpen/denoise filters.
    run([ffmpeg, "-v", "error", "-nostdin", "-y", "-i", str(source), "-an",
         "-vf", f"fps=1/{step},setsar=1", "-start_number", "0",
         str(directory / "%05d.png")])
    rows = []
    for p in sorted(directory.glob("[0-9][0-9][0-9][0-9][0-9].png")):
        index = int(p.stem)
        if index >= math.floor(duration / step + .5):
            continue  # ignore stale files left by an older longer sampling pass
        rows.append({"file": p.name, "nominal_time_seconds": round(index * step, 6),
                     "sha256": digest(p)})
    return rows


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--client", type=Path, default=ROOT.parent / "DNF1031客户端")
    parser.add_argument("--output", type=Path, default=ROOT / "reports/dynamics/render-reference-videos")
    parser.add_argument("--only", nargs="+", choices=BASE_SKILLS)
    parser.add_argument("--skip-pc", action="store_true")
    parser.add_argument("--step", type=float, default=.1)
    parser.add_argument("--pc-step", type=float, default=1.0)
    parser.add_argument("--pc-video", type=Path)
    args = parser.parse_args()
    if min(args.step, args.pc_step) <= 0:
        parser.error("Sampling steps must be positive")
    ffmpeg, ffprobe = shutil.which("ffmpeg"), shutil.which("ffprobe")
    if not ffmpeg or not ffprobe:
        parser.error("ffmpeg and ffprobe are required on PATH")
    client, output = args.client.resolve(), args.output.resolve()
    if output == client or client in output.parents:
        parser.error("Output must not be inside the read-only original client")
    output.mkdir(parents=True, exist_ok=True)
    report = {"created_utc": datetime.now(timezone.utc).isoformat(),
              "scope": "Original-client AVI references and supplied PC recording; no game visual acceptance claim.",
              "decoder_source": "npk-pvf解析器/src/avi/decrypt.ts (wrapper/XOR only, no AVI byte patches)",
              "display_transform": "ffmpeg MP4 re-encode with setsar=1; raw decoded AVI is unchanged",
              "ffmpeg": run([ffmpeg, "-version"]).splitlines()[0], "references": []}
    for name in args.only or BASE_SKILLS:
        source = client / "Video/Swordman" / (name + ".avi")
        encoded = source.read_bytes()
        decoded = decode_neople(encoded)
        folder = output / name
        folder.mkdir(exist_ok=True)
        raw_path, display = folder / "raw-decoded.avi", folder / "display.mp4"
        raw_path.write_bytes(decoded)
        metadata = probe(ffprobe, raw_path)
        duration = float(metadata["format"]["duration"])
        run([ffmpeg, "-v", "error", "-nostdin", "-y", "-i", str(raw_path),
             "-map", "0:v:0", "-an", "-vf", "setsar=1", "-c:v", "libx264",
             "-crf", "15", "-pix_fmt", "yuv420p", str(display)])
        samples = timeline(ffmpeg, display, folder / "timeline", args.step, duration)
        report["references"].append({"kind": "client-skill-preview", "skill": name,
            "source": str(source), "source_size": len(encoded), "source_sha256": hashlib.sha256(encoded).hexdigest(),
            "wrapper_declared_decoded_bytes": len(decoded), "wrapper_padding_bytes": len(encoded) - 32 - len(decoded),
            "raw_decoded": str(raw_path.relative_to(output)), "raw_decoded_sha256": digest(raw_path),
            "raw_probe": metadata, "display": str(display.relative_to(output)),
            "display_sha256": digest(display), "display_probe": probe(ffprobe, display),
            "timeline_step_seconds": args.step, "timeline": samples,
            "limitation": "160x90 skill preview may show skill variants; use PVF qualification, not video alone, to select unadvanced behavior."})
        print(f"{name}: {duration:.6f}s, {len(samples)} samples", flush=True)
    if not args.skip_pc:
        recordings = [args.pc_video] if args.pc_video else sorted((ROOT.parent / "pc版dnf视频").glob("*.mp4"))
        for index, source in enumerate(recordings):
            source = source.resolve()
            folder = output / ("pc-recording-" + str(index))
            metadata = probe(ffprobe, source)
            duration = float(metadata["format"]["duration"])
            samples = timeline(ffmpeg, source, folder / "timeline", args.pc_step, duration)
            report["references"].append({"kind": "user-pc-recording", "source": str(source),
                "source_sha256": digest(source), "source_size": source.stat().st_size,
                "probe": metadata, "display_source": "original source, no duplicate or transcode",
                "timeline_step_seconds": args.pc_step, "timeline": samples,
                "limitation": "Recording is auxiliary to local PC/PVF content; segment timing annotations pending inspection."})
            print(f"PC recording: {duration:.6f}s, {len(samples)} samples", flush=True)
    (output / "manifest.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(output / "manifest.json")


if __name__ == "__main__":
    main()
