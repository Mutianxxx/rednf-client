"""Ordered EVN record decoder based on the 1031 native reader at 004EB120."""
from copy import deepcopy

OPEN = '[info]'
CLOSE = '[/info]'
KNOWN = {'[id]': ('id', 1, 2),
         '[imageStartIndex]': ('image_start_index', 1, 2)}


def tooltip_state(mode):
    """004EB5F0..004EB694: all names other than disable/timer use key 1."""
    return 0 if mode == 'disable' else 2 if mode == 'timer' else 1


def button_spec(event_id, image_start_index):
    """004E9520 frame arguments staged across IMG lookup, consumed by 011C4100."""
    low16 = event_id & 0xffff
    suffix = '' if low16 < 100 and low16 != 24 else '_tw'
    n = image_start_index
    return dict(path=f'Interface2/HUD/Information_button/Information_button{suffix}.img',
                input_frames=[n, n, n+1, n+2], highlight_frame=0,
                pointer_offsets=[0x2b8, 0x2c0, 0x2bc, 0x2c4], constructor='011C4100',
                shared_button_vtable='0185A81C', generic_draw_entry='00FD50A0')


def is_command(token):
    value = token.get('value')
    return token.get('type') == 5 and isinstance(value, str) and value.startswith('[') and value.endswith(']')


def decode_evn(script):
    tokens = script['tokens']
    if len(tokens) > 65536:
        raise ValueError('EVN token bound exceeded')
    groups = []
    i = 0
    while i < len(tokens):
        start = tokens[i]
        if start.get('value') != OPEN or start.get('type') != 5:
            raise ValueError(f'Expected EVN [info] at token {i}')
        group = dict(file_record=len(groups), token_index=i, offset=start['offset'],
                     fields=[], effective=dict(id=-1, image_start_index=0, tooltips={}))
        i += 1
        while i < len(tokens) and tokens[i].get('value') != CLOSE:
            token = tokens[i]
            tag = token.get('value') if is_command(token) else None
            if tag == '[tooltip]':
                mode = tokens[i+1] if i+1 < len(tokens) else {}
                text = tokens[i+2] if i+2 < len(tokens) else {}
                if mode.get('type') != 7 or not isinstance(mode.get('value'), str):
                    raise ValueError(f'Invalid tooltip mode at token {i}')
                count = 3
                link = None
                if text.get('type') == 7:
                    value = text.get('value')
                elif text.get('type') == 9 and i+3 < len(tokens) and tokens[i+3].get('type') == 10:
                    linked = tokens[i+3]
                    value = linked.get('resolved_text')
                    link = deepcopy(linked.get('string_link'))
                    count = 4
                else:
                    raise ValueError(f'Invalid tooltip text encoding at token {i}')
                if not isinstance(value, str):
                    raise ValueError(f'Unresolved tooltip text at token {i}')
                state = tooltip_state(mode['value'])
                field = dict(tag=tag, token_index=i, offset=token['offset'], known=True,
                             values=[mode['value'], value], native_state_key=state,
                             string_link=link, tokens=deepcopy(tokens[i:i+count]))
                group['effective']['tooltips'][str(state)] = value
                i += count
            elif tag in KNOWN:
                key, count, kind = KNOWN[tag]
                values = tokens[i+1:i+1+count]
                if len(values) != count or any(item.get('type') != kind for item in values):
                    raise ValueError(f'EVN field {tag} has invalid payload at token {i}')
                data = [item.get('value') for item in values]
                if kind == 2 and any(type(value) is not int for value in data):
                    raise ValueError(f'EVN integer field {tag} is not an integer')
                if kind == 7 and any(not isinstance(value, str) for value in data):
                    raise ValueError('EVN tooltip payload is not text')
                field = dict(tag=tag, token_index=i, offset=token['offset'], known=True,
                             values=data, tokens=deepcopy(tokens[i:i+count+1]))
                group['effective'][key] = data[0]
                i += count+1
            else:
                end = i+1
                while end < len(tokens) and not is_command(tokens[end]):
                    end += 1
                field = dict(tag=tag, token_index=i, offset=token['offset'], known=False,
                             tokens=deepcopy(tokens[i:end]))
                i = end
            group['fields'].append(field)
        if i >= len(tokens) or tokens[i].get('value') != CLOSE:
            raise ValueError(f'Unclosed EVN info record at token {group["token_index"]}')
        group['end_token_index'] = i
        group['end_offset'] = tokens[i]['offset']
        group['schema_complete'] = all(field['known'] for field in group['fields'])
        groups.append(group)
        i += 1
    return dict(path=script['path'], groups=groups, group_count=len(groups),
                source_tokens=deepcopy(tokens))
