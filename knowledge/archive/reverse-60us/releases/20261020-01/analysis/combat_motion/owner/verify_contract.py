"""Composition checks for manager and owner wrapper boundaries, not map capture."""
from pathlib import Path
import json

from owner_model import Appendage, Owner, Terrain, first_blocker, response_effects, terrain_allowed, wrapper_branch

DEST = Path(__file__).resolve().parent


def main():
    actor = Owner(x=50, y=50, width=10, height=10)
    first = Owner(x=50, y=50, width=10, height=10, class_mask_e4=0x21, data_type8=2)
    second = Owner(x=50, y=50, width=10, height=10, class_mask_e4=0x21, data_type8=2)
    assert first_blocker(actor, [], [first, second]) is None
    assert first_blocker(actor, [actor], [actor, first, second]) is first
    first.ignore4d4 = [actor]
    assert first_blocker(actor, [actor], [actor, first, second]) is second
    actor.status16_active = True
    actor.appendage_scan_flag184 = True
    actor.native_state = 22
    actor.appendages = [Appendage(actor, True, False)]
    assert wrapper_branch(actor) is None
    actor.appendages.append(Appendage(actor, False, False))
    assert wrapper_branch(actor) is False
    actor.native_state = 5
    assert wrapper_branch(actor) is True
    assert response_effects(0, 500, None, "attachment148", "attachment154") == [
        dict(kind="attachment_v1c", field="0x148", target="attachment148", args=[0, 500, None]),
        dict(kind="attachment_v1c", field="0x154", target="attachment154", args=[0, 500, None])]
    terrain = Terrain(1, 10, tile_at=lambda x, y: 0)
    touched = []
    terrain.tile_at = lambda x, y: touched.append((x, y)) or 0
    test_actor = Owner(x=16, y=12, width=2, height=2)
    assert terrain_allowed(test_actor, terrain)
    assert touched == [(0, 0), (0, 1), (1, 0), (1, 1)]
    # Bounds end is sampled after signed division and includes the resulting cell.
    result = dict(kind="synthetic composition checks; actual DFO world/query state not observed",
                  passed=True, checks=8, sampled_cells=touched,
                  checked=["registration gate", "first blocker order/self skip", "ignore identity list",
                           "inactive retained cast delegation", "later failed cast clears retained pointer",
                           "state5 shortcut", "attachment forwarding order", "inclusive footprint end cell traversal"])
    (DEST / "contract-checks.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(checks=8, passed=True)))


if __name__ == "__main__":
    main()
