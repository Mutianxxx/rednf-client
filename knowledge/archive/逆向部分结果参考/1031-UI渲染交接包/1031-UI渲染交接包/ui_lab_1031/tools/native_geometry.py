"""1031 geometry from 011B4710, 011B41E0 and 011DB510; no inferred stack."""
import math
import struct


CENTER_SENTINEL = struct.unpack('<f', bytes.fromhex('9976967e'))[0]
SECONDARY_CENTER_SENTINEL = 4294967296.0


def rectangle_words(arguments):
    return [max(0, value if value < 0x80000000 else value-0x100000000) & 0xffff for value in arguments[:4]]


def signed_word(value):
    return value-0x10000 if value & 0x8000 else value


def image_affine(scale_x, scale_y, rotation, center_x, center_y, width, height):
    values = (scale_x, scale_y, rotation, center_x, center_y)
    if not all(math.isfinite(value) for value in values) or max(abs(scale_x), abs(scale_y)) > 32:
        raise ValueError('Nonfinite or out-of-preview-bound transform')
    center_x = width//2 if center_x == CENTER_SENTINEL else center_x
    center_y = height//2 if center_y == CENTER_SENTINEL else center_y
    if rotation == 0.0:
        center_x = width//2 if center_x == SECONDARY_CENTER_SENTINEL else center_x
        center_y = height//2 if center_y == SECONDARY_CENTER_SENTINEL else center_y
    elif center_x == SECONDARY_CENTER_SENTINEL or center_y == SECONDARY_CENTER_SENTINEL:
        raise ValueError('011DB510 leaves 2^32 center literal for nonzero rotation; outside preview bounds')
    cosine, sine = math.cos(rotation), math.sin(rotation)
    horizontal_x, vertical_x = cosine*scale_x, sine*scale_x
    horizontal_y, vertical_y = -sine*scale_y, cosine*scale_y
    return (horizontal_x, horizontal_y, vertical_x, vertical_y,
            center_x-horizontal_x*center_x-vertical_x*center_y,
            center_y-horizontal_y*center_x-vertical_y*center_y)
