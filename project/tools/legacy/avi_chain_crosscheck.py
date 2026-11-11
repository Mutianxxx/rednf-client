"""Independent AVI observation x skill-chain parse cross-validation.

IMPORTANT METHOD BOUNDARY
------------------------
The AVI is an INDEPENDENT OBSERVATION, not a target to fit. This script never
writes a timing value back into the mapping. It:

  1. decodes a base-client AVI and measures per-frame luminance change
     (no reference to any PVF/ANI/chain data),
  2. reads the *already completed* chain parse (dnf_inspect --skill-chain),
  3. compares event ORDER, event COUNT and fixed-span PROPORTIONS,
  4. reports the residual: input-wait slots and inter-trigger gaps that no
     source file times, and chain details the video cannot qualify.

Anything quantified from the video is labelled "observed" and stays in the
report. Source [DELAY] spans stay labelled "source". Nothing is blended.

Usage:
  python avi_chain_crosscheck.py --avi DECODED.avi --chain CHAIN.json \
                                 --output REPORT.json
"""
import argparse
import json
import subprocess
import statistics
import sys
from pathlib import Path

WIDTH, HEIGHT = 160, 90
FRAME_BYTES = WIDTH * HEIGHT
FPS = 30000.0 / 1001.0
BUCKET_S = 0.1


def decode_gray(avi: Path):
    """Return a list of luma frames. No PVF or chain data is consulted."""
    cmd = ["ffmpeg", "-v", "error", "-i", str(avi),
           "-vf", "format=gray", "-pix_fmt", "gray",
           "-f", "rawvideo", "-vsync", "0", "-"]
    proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if proc.returncode != 0:
        raise RuntimeError("ffmpeg failed: " + proc.stderr.decode("utf-8", "replace")[:500])
    raw = proc.stdout
    usable = len(raw) - (len(raw) % FRAME_BYTES)
    frames = [raw[i:i + FRAME_BYTES] for i in range(0, usable, FRAME_BYTES)]
    if not frames:
        raise RuntimeError("no decoded frames")
    return frames


def frame_diffs(frames):
    diffs = [0.0]
    for prev, cur in zip(frames, frames[1:]):
        diffs.append(sum(abs(a - b) for a, b in zip(prev, cur)) / FRAME_BYTES)
    return diffs


def bucketize(diffs):
    buckets = []
    for start in range(0, len(diffs), 3):
        chunk = diffs[start:start + 3]
        if not chunk:
            continue
        buckets.append({
            "index": len(buckets),
            "fromMs": round(start / FPS * 1000.0, 2),
            "toMs": round((start + len(chunk)) / FPS * 1000.0, 2),
            "avg": round(sum(chunk) / len(chunk), 3),
            "max": round(max(chunk), 3),
        })
    return buckets


def observation_windows(buckets):
    values = [b["avg"] for b in buckets]
    baseline = statistics.median(values)
    # A window is a run of buckets well above the clip's own baseline. The
    # threshold is derived ONLY from the video, never from the chain parse.
    threshold = max(baseline * 1.8, baseline + 1.5, 3.0)
    windows = []
    run = []
    for b in buckets:
        if b["avg"] >= threshold:
            run.append(b)
        elif run:
            windows.append(make_window(run))
            run = []
    if run:
        windows.append(make_window(run))
    peaks = []
    for i in range(1, len(values) - 1):
        if values[i] >= values[i - 1] and values[i] > values[i + 1] and values[i] >= threshold:
            peaks.append({"fromMs": buckets[i]["fromMs"], "avg": values[i]})
    return {"baseline": round(baseline, 3), "threshold": round(threshold, 3),
            "windows": windows, "localPeaks": peaks,
            "globalPeak": max(buckets, key=lambda b: b["avg"])}


def make_window(run):
    return {"fromMs": run[0]["fromMs"], "toMs": run[-1]["toMs"],
            "buckets": len(run),
            "peakMs": max(run, key=lambda b: b["avg"])["fromMs"],
            "peakAvg": round(max(b["avg"] for b in run), 3),
            "area": round(sum(b["avg"] for b in run), 3)}


def cross_validate(chain, obs):
    pt = chain["predictedTimeline"]
    fixed = pt["fixedSlots"]
    external = pt["externalSlots"]
    windows = pt["phaseWindows"]
    ow = obs["windows"]
    global_peak = obs["globalPeak"]

    source_span = chain["nominalActionMs"]
    observed_span = obs["durationMs"]
    residual = round(observed_span - source_span, 2)

    by_role = {}
    for w in windows:
        by_role.setdefault(w["role"], []).append(w)
    entry = by_role.get("entry", [{}])[0]
    triggered = by_role.get("triggered", [{}])[0]
    finish = by_role.get("finish", [{}])[0]

    # ORDER: the strongest visual event must be the terminal burst, and the
    # clip must settle after it. These are qualitative predictions of the
    # completed chain parse, not fitted thresholds.
    burst = max(ow, key=lambda w: w["peakAvg"]) if ow else {}
    settled_tail = False
    if ow:
        last_end = ow[-1]["toMs"]
        settled_tail = observed_span - last_end >= 300
    strongest_is_terminal = bool(burst) and (
        burst["peakMs"] >= observed_span * 0.6)

    # COUNT: the parse publishes N triggered slots. The observation supplies
    # its own count of local activity peaks inside the middle (post-opening,
    # pre-terminal) band; agreement is reported as a ratio, not enforced.
    mid_from = observed_span * 0.30
    mid_to = observed_span * 0.88
    mid_peaks = [p for p in obs["localPeaks"] if mid_from <= p["fromMs"] <= mid_to]
    triggered_slots = sum(w.get("slotCount", 0) for w in by_role.get("triggered", []))

    # PROPORTION: source fixed spans vs observed phase lengths. External slots
    # are explicitly excluded from the source side of this comparison.
    checks = [
        {"name": "chain order ends with finish slot",
         "pass": bool(fixed) and fixed[-1]["role"] == "finish",
         "source": fixed[-1]["path"] if fixed else None},
        {"name": "input-wait state is unquantified in source",
         "pass": len(external) > 0 and all(s["startMs"] is None for s in external),
         "source": [s["path"] for s in external]},
        {"name": "observed terminal burst is the clip maximum",
         "pass": strongest_is_terminal,
         "observed": {"peakMs": burst.get("peakMs"), "peakAvg": burst.get("peakAvg")}},
        {"name": "observed clip settles after the terminal burst",
         "pass": settled_tail,
         "observed": {"lastWindowEndMs": ow[-1]["toMs"] if ow else None,
                      "durationMs": observed_span}},
        {"name": "one or more discrete mid-band activity peaks",
         "pass": len(mid_peaks) > 0,
         "observed": {"midBandPeaks": len(mid_peaks),
                      "triggeredSlotsInParse": triggered_slots}},
        {"name": "source fixed spans are shorter than the observed clip",
         "pass": 0 < source_span < observed_span,
         "source": {"nominalActionMs": source_span},
         "observed": {"durationMs": observed_span}},
    ]

    # Residual = what the cross-check proves is still missing from the chain
    # parse. These are findings, NOT parameters to fit.
    unbound = [b for b in pt["layerBirths"]
               if not b["timed"] and not b["stageBound"]]
    late_band = [b for b in unbound if b["birthMs"] >= source_span * 0.8]
    findings = [
        {
            "id": "external-timing-slots",
            "finding": "Source fixed spans are %.1fms; the observed clip is %.1fms" %
                       (source_span, observed_span),
            "differenceMs": residual,
            "sourceSide": "input-wait hold (guard.ani 2x10000ms sentinel) + five inter-trigger gaps; none timed by a PVF file",
            "observationSide": "terminal burst at %.1fms, settled tail after %.1fms" %
                               (global_peak["fromMs"], ow[-1]["toMs"] if ow else 0),
            "status": "designed open slot, not an error; deliberately not written back to the mapping",
        },
        {
            "id": "unbound-effect-layers",
            "finding": "%d/%d effect layers still have no source instant and fall back to the stem-order spread" %
                       (len(unbound), len(pt["layerBirths"])),
            "examples": [b["path"].split("/")[-1] for b in unbound[:8]],
            "impact": "per-layer birth instants cannot be verified against the video",
            "nextStep": "recover the state-handler effect dispatch or the family ANI's own sidecar",
        },
        {
            "id": "unbound-layer-concentration",
            "finding": "%d of %d unbound layers are compressed into the last 20%% of the nominal clock" %
                       (len(late_band), len(unbound)),
            "sourceSide": "birthRatio beats are keyed on the untimed list index, not on the source stage",
            "observationSide": "%d mid-band activity peaks spread across %.1f-%.1fms" %
                               (len(mid_peaks), mid_from, mid_to),
            "impact": "flash/light/dust layers that belong to slash beats are predicted after the triggered group",
            "nextStep": "extend same-stem binding with serial-to-triggered-pair rules (flash1..3, light1..3, lighttail1..4)",
            "status": "identified by this cross-check; NOT yet changed",
        },
        {
            "id": "triggered-pair-count",
            "finding": "parse publishes %d triggered slots; observation shows %d mid-band peaks" %
                       (triggered_slots, len(mid_peaks)),
            "impact": "one triggered pair may produce more than one visible event (weapon, ground array, flash, damage text)",
            "nextStep": "do not force a 1:1 mapping; the video has no element-level annotation",
        },
        {
            "id": "frame-clock-scaling",
            "finding": "the nominal clock is a raw [DELAY] sum; 1031 ratePercent scaling and delayed-add birth offset are unrecovered",
            "impact": "absolute ms comparisons carry an unknown scale factor even after external slots are accounted for",
            "nextStep": "recover the renderer's delay scaling from the 1031 exe before claiming clock equivalence",
        },
    ]

    return {
        "method": "source-parse prediction vs independent video observation; no parameter fitting",
        "pvf_identity": chain["pvf_identity"],
        "source": {
            "nominalActionMs": source_span,
            "phaseWindows": windows,
            "triggeredSlots": triggered_slots,
            "externalSlots": [{"path": s["path"],
                               "sourceDurationMs": s["sourceDurationMs"],
                               "frameCount": s["frameCount"]} for s in external],
            "layerClockCounts": count_clocks(pt["layerBirths"]),
        },
        "observation": {
            "durationMs": observed_span,
            "baseline": obs["baseline"], "threshold": obs["threshold"],
            "globalPeak": global_peak,
            "windows": ow,
            "midBandPeaks": mid_peaks,
        },
        "residual": {
            "observedMinusSourceMs": residual,
            "interpretation": "input-wait hold plus inter-trigger gaps; NOT timed by any PVF file",
            "quantifiedBy": "video observation only, never written back to the mapping",
        },
        "checks": checks,
        "residualFindings": findings,
        "unverifiableByThisVideo": [
            "per-layer birth instants (48 family layers have no ALS sidecar)",
            "[IMAGE ROTATE] sign / local rotation transforms",
            "cast-local XYZ offsets and depth ordering",
            "ratePercent frame-delay scaling and delayed-add birth offset",
            "which of the 5 triggered pairs maps to a specific visible sword",
        ],
    }


def count_clocks(births):
    out = {}
    for b in births:
        out[b["clock"]] = out.get(b["clock"], 0) + 1
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--avi", required=True)
    ap.add_argument("--chain", required=True)
    ap.add_argument("--output", required=True)
    args = ap.parse_args()

    avi, chain_path, out = Path(args.avi), Path(args.chain), Path(args.output)
    frames = decode_gray(avi)
    diffs = frame_diffs(frames)
    buckets = bucketize(diffs)
    obs = observation_windows(buckets)
    obs.update({"frames": len(frames),
                "durationMs": round(len(frames) / FPS * 1000.0, 2),
                "fps": FPS,
                "buckets": buckets,
                "source": "base-client AVI luma frame difference; video only"})

    chain = json.loads(chain_path.read_text(encoding="utf-8"))
    report = cross_validate(chain, obs)
    report["observationFull"] = obs
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8")

    print(f"frames={len(frames)} durationMs={obs['durationMs']} "
          f"windows={len(obs['windows'])} peaks={len(obs['localPeaks'])}")
    for c in report["checks"]:
        print(("PASS " if c["pass"] else "FAIL ") + c["name"])
    print(f"residual(observed-source)={report['residual']['observedMinusSourceMs']}ms")
    print("report:", out)
    return 0 if all(c["pass"] for c in report["checks"]) else 1


if __name__ == "__main__":
    sys.exit(main())
