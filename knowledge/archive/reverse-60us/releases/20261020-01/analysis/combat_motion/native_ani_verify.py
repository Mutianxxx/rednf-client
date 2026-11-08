"""Execute untouched A2792F..A2794A and C01544 bytes for ANI deadline vectors."""
from pathlib import Path
import hashlib
import json
import struct
import subprocess

from motion_model import ani_rate, frame_duration
from native_verify import build_harness, original_bytes, SOURCE_HASH

DEST = Path(__file__).resolve().parent


def main():
    values = [("rate_100_delay_70", 70, 100.0), ("rate_85_delay_70", 70, 85.0),
              ("rate_85_delay_300", 300, 85.0)]
    for scale in (850, 999, 1000, 1001, 1500):
        for installation in (False, True):
            rate = ani_rate(scale, installation)
            for delay in (70, 300):
                values.append((f"scale_{scale}_{'install' if installation else 'refresh'}_delay_{delay}", delay, rate))
    executable = DEST / "native-ani-harness.exe"
    image = build_harness([], values)
    executable.write_bytes(image)
    result = subprocess.run([str(executable)], cwd=DEST, capture_output=True, check=False, timeout=20)
    (DEST / "native-ani-output.bin").write_bytes(result.stdout)
    if result.returncode != 0 or len(result.stdout) != len(values) * 2 * 20:
        raise RuntimeError(f"ANI harness exit {result.returncode:#x}, bytes={len(result.stdout)}")
    rows, mismatches = [], []
    for mode_index, precision in enumerate((64, 53)):
        for index, (name, delay, rate) in enumerate(values):
            offset = (mode_index * len(values) + index) * 20
            negative_delta, deadline, stored_rate, stored_delay, _ = struct.unpack("<iifii", result.stdout[offset:offset + 20])
            expected = frame_duration(delay, rate)
            match = deadline == expected and negative_delta == -expected and stored_rate == rate and stored_delay == delay
            row = dict(name=name, x87_precision=precision,
                       rate_percent=rate, delay_input=delay,
                       native_negative_delta=negative_delta, native_deadline=deadline,
                       model_duration=expected, matches=match)
            rows.append(row)
            if not match:
                mismatches.append(row)
    report = dict(kind="extracted ANI arithmetic slice and native truncation helper in synthetic PE32; delay/rate inputs synthetic",
                  source_sha256=SOURCE_HASH,
                  arithmetic_va="0x00a2792f", arithmetic_size=0x1c,
                  arithmetic_sha256=hashlib.sha256(original_bytes(0xa2792f, 0x1c)).hexdigest(),
                  helper_va="0x00c01544", helper_size=0x75,
                  helper_sha256=hashlib.sha256(original_bytes(0xc01544, 0x75)).hexdigest(),
                  harness_sha256=hashlib.sha256(image).hexdigest(),
                  output_sha256=hashlib.sha256(result.stdout).hexdigest(),
                  precisions=[64, 53], matches=len(rows) - len(mismatches), mismatches=len(mismatches), vectors=rows,
                  limitations=["This validates arithmetic given decoded signed delay; the parser's delay write is not exercised.",
                               "Rate inputs use formulas recovered from install/refresh sites; those functions are not executed here.",
                               "The original client's runtime x87 control word and actual effective attack-speed stat are not captured."])
    (DEST / "native-ani-vectors.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in ["kind", "matches", "mismatches"]}))
    if mismatches:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
