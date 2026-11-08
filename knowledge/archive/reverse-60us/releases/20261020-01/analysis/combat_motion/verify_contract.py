"""Check collision probe order, bounded unsupported paths, and composed timelines."""
from dataclasses import asdict
from pathlib import Path
import json

from motion_model import Axis, ani_rate, frame_deadlines, position_round, simulate, step, step_axis

DEST = Path(__file__).resolve().parent


def main():
    cases = []
    for velocity, expected_probes, expected_position in [
        (10000, [(1, 0, 0), (2, 0, 0), (3, 0, 0)], 2.0),
        (-10000, [(-1, 0, 0), (-2, 0, 0), (-3, 0, 0)], -2.0),
    ]:
        axes = [Axis(0, velocity), Axis(), Axis()]
        probes = []

        def probe(axis, xyz):
            probes.append(xyz)
            return abs(xyz[axis]) < 3

        code = step_axis(axes, 0, 1, probe)
        assert probes == expected_probes and axes[0].position == expected_position
        assert axes[0].velocity == velocity and code == 4
        cases.append(dict(name="collision_positive" if velocity > 0 else "collision_negative",
                          probes=probes, after=asdict(axes[0]), result=code))
    assert [position_round(v) for v in [0.49, 0.5, -0.49, -0.5, 1.5, -1.5]] == [0, 1, 0, -1, 2, -2]
    axes = [Axis(0, 1000), Axis(0, 1000), Axis(0, 1000)]
    calls = []
    codes = step(axes, 1, lambda axis, xyz: calls.append((axis, xyz)) or True)
    assert calls == [(0, (1, 0, 0)), (1, (1, 1, 0)), (2, (1, 1, 1))]
    assert codes == [2, 2, 2]
    cases.append(dict(name="xyz_sequential_probe", calls=calls, result=codes))
    try:
        step(axes, 1, external_controller=True)
    except NotImplementedError:
        cases.append(dict(name="external_controller_rejected", result="NotImplementedError"))
    else:
        raise AssertionError("unresolved controller branch must not silently use free-axis logic")
    timelines = []
    for scale in (850, 1000):
        rates = dict(refresh=ani_rate(scale), installation=ani_rate(scale, True))
        for path, rate in rates.items():
            deadlines = frame_deadlines([70, 70, 70, 70, 300], rate)
            rows = simulate(scale, 1, [deadlines[0]] + [b - a for a, b in zip(deadlines, deadlines[1:])])
            timelines.append(dict(scale_input=scale, rate_path=path, rate_percent=rate,
                                  deadlines=deadlines, motion_samples=rows["samples"]))
    result = dict(kind="contract composition checks; collision policy synthetic, not original-map evidence",
                  checks=len(cases) + 1, passed=True, cases=cases, illustrative_timelines=timelines,
                  limitations=["Probe policy is supplied by this verifier; actual +A8/+AC/+274 bodies remain unresolved.",
                               "ANI timelines assume positive decoded delays and fixed rate with no elapsed-preserving rate refresh.",
                               "Frame boundary elapsed tests are not part of this verifier.",
                               "No actual runtime stat of 850 or 1000 is asserted."])
    (DEST / "contract-checks.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (DEST / "example-motion.json").write_text(json.dumps(simulate(), ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(checks=result["checks"], passed=True, illustrative_timelines=len(timelines))))


if __name__ == "__main__":
    main()
