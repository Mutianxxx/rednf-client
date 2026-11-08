"""Typed, bounded PVF preview contracts. Raw parameters remain in the view.

These layouts are resource reconstruction candidates, not native runtime state.
"""
import copy
import math


def board_frames(control):
    p = control['parameters']
    if len(p) != 11 or not all(type(value) is int for value in p):
        raise ValueError('board image requires width, height and nine frame IDs')
    if any(not 0 <= value <= 0x7fffffff for value in p[2:]):
        raise ValueError('board image contains absent frame IDs')
    strings = control['strings']
    if not strings or not all(isinstance(value, str) for value in strings):
        raise ValueError('board image requires an IMG path followed by optional draw by loop')
    if any(value != 'draw by loop' for value in strings[1:]):
        raise ValueError('unverified board string option; raw fields retained')
    minimum = 0 if 'draw by loop' in strings[1:] else 1
    if not minimum <= p[0] <= 4096 or not minimum <= p[1] <= 4096:
        raise ValueError('board dimensions/counts exceed external preview bounds; native values retained')
    return p[0], p[1], p[2:]


def nine_slice(width, height, images):
    """Use logical cells, including transparent cropped margins, for destinations."""
    if len(images) != 9:
        raise ValueError('nine images required')
    left = max(images[i]['logical_width'] for i in (0, 3, 6))
    right = max(images[i]['logical_width'] for i in (2, 5, 8))
    top = max(images[i]['logical_height'] for i in (0, 1, 2))
    bottom = max(images[i]['logical_height'] for i in (6, 7, 8))
    if left + right > width or top + bottom > height:
        raise ValueError('board smaller than its fixed corners')
    xs, ys = (0, left, width-right, width), (0, top, height-bottom, height)
    return [(xs[i % 3], ys[i // 3], xs[i % 3+1]-xs[i % 3],
             ys[i // 3+1]-ys[i // 3]) for i in range(9)]


def radio_entries(control):
    p = control['parameters']
    if not p or not isinstance(p[0], int) or not 1 <= p[0] <= 256:
        raise ValueError('invalid radio count')
    count = p[0]
    if len(p) not in (1+6*count, 2+6*count) or not all(isinstance(v, int) for v in p):
        raise ValueError('radio extent does not match six values per entry')
    entries = [dict(frames=p[1+i*6:5+i*6], x=p[5+i*6], y=p[6+i*6]) for i in range(count)]
    selected = p[-1] if len(p) == 2+6*count else 0
    if not 0 <= selected < count:
        raise ValueError('invalid initial radio selection')
    return entries, selected


def sample_animation(animation, milliseconds, loop=False):
    """Match the shared native sampler: defaults reset, discrete image and blend."""
    frames = animation['frames']
    if not frames:
        return None
    time = max(0.0, milliseconds if math.isfinite(milliseconds) else 0.0)
    if loop and animation['duration'] > 0:
        time %= animation['duration']
    start = 0
    index = len(frames)-1
    for i, frame in enumerate(frames):
        end = start + frame['duration']
        if time < end:
            index = i
            break
        if i+1 < len(frames):
            start = end
    current = frames[index]
    pose = copy.deepcopy(current['pose'])
    next_index = index+1 if index+1 < len(frames) else 0 if loop else index
    progress = min(1.0, max(0.0, (time-start)/current['duration'])) if current['duration'] else 0
    if current['interpolate'] and next_index != index:
        next_pose = frames[next_index]['pose']
        for key in ('x', 'y', 'scale_x', 'scale_y', 'rotation'):
            pose[key] += (next_pose[key]-pose[key])*progress
        pose['rgba'] = [a+(b-a)*progress for a, b in zip(pose['rgba'], next_pose['rgba'])]
    pose.update(frame=index, progress=progress)
    return pose
