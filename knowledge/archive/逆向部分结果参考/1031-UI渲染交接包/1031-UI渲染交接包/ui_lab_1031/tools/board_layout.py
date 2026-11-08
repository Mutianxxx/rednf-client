"""Bounded 1031 board submissions from 01072820 and 011E9C30/011E9E20."""
import math
import struct
from preview_layout import board_frames


EVIDENCE = 'reports/board-followup/evidence.json'
MAX_OPERATIONS = 16384
MAX_EXTENT = 4096


def float32(value):
    return struct.unpack('<f', struct.pack('<f', value))[0]


def board_layout(control, images):
    first, second, frames = board_frames(control)
    if len(images) != 9 or not all(images):
        raise ValueError('native board requires all nine image objects; no partial replacement')
    for image in images:
        for field, minimum, maximum in (('logical_width', 0, 65535), ('logical_height', 0, 65535),
                                         ('width', 0, MAX_EXTENT), ('height', 0, MAX_EXTENT),
                                         ('x', -32768, 32767), ('y', -32768, 32767)):
            value = image.get(field)
            if type(value) is not int or not minimum <= value <= maximum:
                raise ValueError('board IMG metadata missing or outside preview bounds: '+field)
    origin_x, origin_y = control.get('absolute_x', 0), control.get('absolute_y', 0)
    if any(type(value) is not int or abs(value) > 1048576 for value in (origin_x, origin_y)):
        raise ValueError('board absolute anchor exceeds external preview bounds')
    loop = 'draw by loop' in control['strings'][1:]
    center_width, center_height = images[4]['logical_width'], images[4]['logical_height']
    left, right = images[3]['logical_width'], images[5]['logical_width']
    top, bottom = images[1]['logical_height'], images[7]['logical_height']
    width = left+center_width*first+right if loop else first
    height = top+center_height*second+bottom if loop else second
    result = dict(mode='loop' if loop else 'stretch', raw_parameters=control['parameters'][:],
                  raw_strings=control['strings'][:], origin=[origin_x, origin_y], logical_size=[width, height],
                  evidence=EVIDENCE, consumer='011E9C30' if loop else '011E9E20', draw_ops=[],
                  status='confirmed layout; runtime visibility and rasterization pending')
    if center_width == 0 or center_height == 0:
        result.update(status='native no draw', reason='center logical width or height is zero')
        return result
    if not 1 <= width <= MAX_EXTENT or not 1 <= height <= MAX_EXTENT:
        raise ValueError('board logical size exceeds external preview bounds; native values retained')
    if loop and (first+2)*(second+2) > MAX_OPERATIONS:
        raise ValueError('board operation count exceeds external preview limit of '+str(MAX_OPERATIONS))

    def submit(slot, anchor_x, anchor_y, scale_x=1.0, scale_y=1.0, transformed=False):
        image = images[slot]
        result['draw_ops'].append(dict(order=len(result['draw_ops']), event='board_image', slot=slot,
            path=control['strings'][0], frame=frames[slot], x=anchor_x, y=anchor_y,
            scale_x=scale_x, scale_y=scale_y, rotation=0.0, center=[0.0, 0.0], color=0xffffffff,
            image_crop=[image['x'], image['y']], image_dimensions=[image['logical_width'], image['logical_height']],
            request='011B41E0' if transformed else '011B3950', instance=control.get('key'),
            source=dict(path=control.get('source'), offset=control.get('offset'), name=control.get('name')),
            confirmed_state='authored board layout only; no runtime state inferred'))

    if loop:
        for row in range(second+2):
            anchor_y = origin_y if row == 0 else origin_y+top+(row-1)*center_height
            row_slot = 0 if row == 0 else 6 if row == second+1 else 3
            submit(row_slot, origin_x, anchor_y)
            for column in range(first):
                submit(row_slot+1, origin_x+left+column*center_width, anchor_y)
            submit(row_slot+2, origin_x+left+first*center_width, anchor_y)
    else:
        scale_x = float32((width-left-right)/center_width)
        scale_y = float32((height-top-bottom)/center_height)
        result['scale'] = [scale_x, scale_y]
        if scale_x <= 0 or scale_y <= 0:
            result.update(status='native no draw', reason='nonpositive interior scale suppresses the entire board')
            return result
        inner_x, inner_y = origin_x+images[0]['logical_width'], origin_y+images[0]['logical_height']
        right_x = math.trunc(inner_x+center_width*scale_x+0.5)
        bottom_y = math.trunc(inner_y+center_height*scale_y+0.5)
        for row, anchor_y in enumerate((origin_y, inner_y, bottom_y)):
            for column, anchor_x in enumerate((origin_x, inner_x, right_x)):
                submit(row*3+column, anchor_x, anchor_y, scale_x if column == 1 else 1.0,
                       scale_y if row == 1 else 1.0, column == 1 or row == 1)
    left_bound, top_bound = origin_x, origin_y
    right_bound, bottom_bound = origin_x+width, origin_y+height
    for operation in result['draw_ops']:
        image = images[operation['slot']]
        pixel_x = operation['x']+image['x']*operation['scale_x']
        pixel_y = operation['y']+image['y']*operation['scale_y']
        left_bound, top_bound = min(left_bound, pixel_x), min(top_bound, pixel_y)
        right_bound = max(right_bound, pixel_x+image['width']*operation['scale_x'])
        bottom_bound = max(bottom_bound, pixel_y+image['height']*operation['scale_y'])
    bounds = [math.floor(left_bound), math.floor(top_bound), math.ceil(right_bound), math.ceil(bottom_bound)]
    if bounds[2]-bounds[0] > MAX_EXTENT or bounds[3]-bounds[1] > MAX_EXTENT:
        raise ValueError('board cropped-pixel extent exceeds external preview bounds; no inferred clipping')
    result['pixel_bounds'] = bounds
    return result
