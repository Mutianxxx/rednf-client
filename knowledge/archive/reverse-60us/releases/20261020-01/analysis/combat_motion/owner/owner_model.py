"""Bounded owner predicates: no mutation of the top-level motion model.

Class masks and data fields deliberately retain numeric native identities.
"""
from dataclasses import dataclass, field


def truncdiv(value, divisor):
    """Signed int division toward zero without Python float intermediates."""
    return value // divisor if value >= 0 else -((-value) // divisor)


@dataclass
class Owner:
    x: int = 0
    y: int = 0
    z: int = 0
    width: int = 0
    height: int = 0
    layer498: int = 0
    scalar21c: int = 0
    class_mask_e4: int = 0
    data_type8: int = 0
    data_bounds1d: bool = False
    native_state: int = 22
    status16_active: bool = False
    appendage_scan_flag184: bool = False
    appendages: list = field(default_factory=list)
    ignore4d4: list = field(default_factory=list)

    def has_mask(self, value):
        return self.class_mask_e4 & value == value

    def bounds(self):
        left = self.x - truncdiv(self.width, 2)
        top = self.y - truncdiv(self.height, 2)
        return left, top, left + self.width, top + self.height


@dataclass
class Appendage:
    owner: Owner
    cast_web_pull: bool
    active60: bool


@dataclass
class Terrain:
    base_column_records: int
    base_rows: int
    extension_row_blocks: int = 0
    rectangles174: list = field(default_factory=list)
    tile_at: object = None

    @property
    def columns(self):
        return self.base_column_records * 14

    @property
    def rows(self):
        return self.base_rows + self.extension_row_blocks * 10


def z_allowed(z):
    """4AC100 uses signed integer comparison only."""
    return z >= 0


def terrain_allowed(owner, terrain):
    """485950; caller supplies exact grid cells, base and extension shape."""
    check_bounds = owner.has_mask(0x11) or owner.has_mask(0x81) or (owner.has_mask(0x21) and owner.data_bounds1d)
    if check_bounds and not (0 <= owner.x < terrain.columns * 16 and 0 <= owner.y < terrain.rows * 12):
        return False
    if owner.width == 0 and owner.height == 0:
        return True
    if terrain.rectangles174:
        return any(x <= owner.x < x + w and y <= owner.y < y + h for x, y, w, h in terrain.rectangles174)
    left, top, right, bottom = owner.bounds()
    start_x, start_y = max(0, truncdiv(left, 16)), max(0, truncdiv(top, 12))
    end_x, end_y = min(truncdiv(right, 16), terrain.columns - 1), min(truncdiv(bottom, 12), terrain.rows - 1)
    if terrain.tile_at is None:
        raise ValueError("tile_at(x_cell,y_cell) must implement 485580's actual input grid")
    for cell_x in range(start_x, end_x + 1):
        for cell_y in range(start_y, end_y + 1):
            tile = terrain.tile_at(cell_x, cell_y)
            if tile == 1 and owner.scalar21c <= 0:
                return False
            if tile == 2:
                return False
            if tile == 3 and owner.layer498 != 0:
                return False
            if tile == 4 and owner.layer498 != 1:
                return False
    return True


def bounds_overlap(a, b):
    """4E81D0 accepts touching bounds; no z test is present."""
    al, at, ar, ab = a.bounds()
    bl, bt, br, bb = b.bounds()
    return ar >= bl and br >= al and ab >= bt and bb >= at


def contains_identity(values, value):
    return any(item is value for item in values)


def pair_blocks(a, b):
    """4EB600's current Swordman v+244 implementation."""
    if not (a.has_mask(0x21) or b.has_mask(0x21)):
        return False
    if a.width == 0 or a.height == 0 or b.width == 0 or b.height == 0 or not bounds_overlap(a, b):
        return False
    if a.has_mask(0x21):
        if a.data_type8 == 1 and a.scalar21c <= 0:
            return True
        if a.data_type8 == 2 and not contains_identity(a.ignore4d4, b):
            return True
        if a.data_type8 in (3, 4) and a.layer498 != b.layer498:
            return True
    if b.has_mask(0x21):
        if b.data_type8 == 1 and a.scalar21c <= 0:
            return True
        if b.data_type8 == 2 and not contains_identity(b.ignore4d4, a):
            return True
        if b.data_type8 in (3, 4) and a.layer498 != b.layer498:
            return True
    return False


def first_blocker(owner, registered, candidates, pair_predicate=pair_blocks):
    """50B240: registration gate, nonempty footprint gate, first candidate."""
    if not contains_identity(registered, owner) or (owner.width == 0 and owner.height == 0):
        return None
    return next((other for other in candidates if other is not owner and pair_predicate(owner, other)), None)


def wrapper_branch(owner):
    """4B00F0 prefix; preserve final RTTI pointer, even if its active60=false."""
    retained_cast = None
    if owner.appendage_scan_flag184:
        for appendage in owner.appendages:
            if appendage.owner is owner:
                retained_cast = appendage if appendage.cast_web_pull else None
                if retained_cast is not None and appendage.active60:
                    break
    if owner.status16_active and retained_cast is None:
        return owner.native_state == 5
    return None  # delegate to 4E7DD0, not an allowed result


def response_effects(axis, velocity, collision_object, attachment148=None, attachment154=None,
                     live_x=False, live_y=False, detour1678=-1):
    """Observed calls only; attached +1C bodies and detour mutations not simulated."""
    result = []
    for field_name, attachment in [("0x148", attachment148), ("0x154", attachment154)]:
        if attachment is not None:
            result.append(dict(kind="attachment_v1c", field=field_name, target=attachment,
                               args=[axis, velocity, collision_object]))
    if live_x and live_y and detour1678 == -1 and axis in (0, 1):
        result.append(dict(kind="owner_v57c", args=[axis]))
    return result
