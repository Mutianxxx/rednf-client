"""1031 CBT structure recovered from 01003770/010032B0; no game calls.

Keep the original token stream, duplicate fields and unknown payloads. Group
numbers start at one because the native reader prepends an empty record.
This module does not infer business state from a resource load.
"""
from copy import deepcopy

OPEN = '[CHANGEABLE BUTTON]'
CLOSE = '[/CHANGEABLE BUTTON]'
FIELDS = {'[img index]': ('img_index', 1, 2),
          '[img path]': ('img_path', 1, 7),
          '[button index]': ('button_indices', 4, 2),
          '[highlight index]': ('highlight_index', 1, 2)}
POINTER_OFFSETS = (0x2b8, 0x2c0, 0x2bc, 0x2c4)


def is_command(token):
    value = token.get('value')
    return token['type'] == 7 and isinstance(value, str) and value.startswith('[') and value.endswith(']')


def decode_cbt(script):
    ts = script['tokens']
    if len(ts) > 65536:
        raise ValueError('CBT token bound exceeded')
    groups = []
    i = 0
    while i < len(ts):
        start = ts[i]
        if start['type'] != 5 or start.get('value') != OPEN:
            raise ValueError(f'Expected CBT opening group at token {i}')
        group = dict(native_group=len(groups)+1, token_index=i, offset=start['offset'], fields=[],
                     effective=dict(img_index=0, img_path='', button_indices=[0, 0, 0, -1], highlight_index=-1))
        i += 1
        while i < len(ts) and ts[i]['type'] != 5:
            token = ts[i]
            tag = token.get('value') if is_command(token) else None
            field = dict(tag=tag, token_index=i, offset=token['offset'])
            if tag in FIELDS:
                key, count, kind = FIELDS[tag]
                values = ts[i+1:i+1+count]
                if len(values) != count or any(t['type'] != kind for t in values):
                    raise ValueError(f'CBT field {tag} requires {count} type-{kind} tokens at {i}')
                data = [t.get('value') for t in values]
                if kind == 7 and not all(isinstance(v, str) for v in data):
                    raise ValueError('Unresolved CBT string')
                if kind == 2 and not all(type(v) is int and -0x80000000 <= v <= 0x7fffffff for v in data):
                    raise ValueError('Invalid CBT signed integer')
                field.update(known=True, tokens=deepcopy(ts[i:i+count+1]), values=data)
                group['effective'][key] = data if count > 1 else data[0]
                i += count+1
            else:
                end = i+1
                while end < len(ts) and ts[end]['type'] != 5 and not is_command(ts[end]):
                    end += 1
                field.update(known=False, tokens=deepcopy(ts[i:end]))
                i = end
            group['fields'].append(field)
        if i >= len(ts) or ts[i].get('value') != CLOSE:
            raise ValueError(f'Unclosed or nested CBT group at token {group["token_index"]}')
        group.update(end_token_index=i, end_offset=ts[i]['offset'],
                     schema_complete=all(f['known'] for f in group['fields']))
        groups.append(group)
        i += 1
    return dict(path=script['path'], groups=groups, group_count=len(groups),
                schema_complete=all(g['schema_complete'] for g in groups),
                source_tokens=deepcopy(ts))


def select_group(decoded, number):
    """Mirror native selection bounds; zero cannot restore the original button."""
    if type(number) is not int or not 1 <= number <= len(decoded['groups']):
        return None
    group = decoded['groups'][number-1]
    if not group['schema_complete']:
        raise ValueError('Unknown CBT fields require explicit interpretation')
    return deepcopy(group['effective'])


def image_branch(*, gate_0c, enabled_0d, alternate_34c, control_id, active_id,
                 input_1b5650c, forced_id):
    """Exact main-image predicate in 011C35D0, without unverified input names.

    Return a zero-based index into [button index], not an IMG frame number.
    Other draw modes can layer the base image, text and highlights on top.
    """
    if not gate_0c:
        return dict(branch='skip', slot=None, pointer_offset=None)
    if alternate_34c != 0:
        return dict(branch='alternate', slot=None, pointer_offset=None)
    if not enabled_0d:
        name, slot = 'disabled', 3
    elif active_id == control_id and input_1b5650c == 1:
        name, slot = 'active_input_1', 2
    elif active_id == control_id or forced_id == control_id:
        name, slot = 'active_or_forced', 1
    else:
        name, slot = 'default', 0
    return dict(branch=name, slot=slot, pointer_offset=POINTER_OFFSETS[slot])
