"""1031 STM/WDM reference decoders; preserve tokens, scopes and unnamed columns.

The native STM reader uses five DWORDs per slot type and four per stage.
WDM [in progress] is a marker inside a dungeon row, not a new top-level field.
These are offline structure decoders, not native UI or business-state emulators.
"""
from copy import deepcopy


def command(token, value=None):
    return token.get('type') == 5 and (value is None or token.get('value') == value)


def integer(token):
    value = token.get('value')
    if token.get('type') != 2 or type(value) is not int or not -0x80000000 <= value <= 0x7fffffff:
        raise ValueError('Expected a signed type-2 integer')
    return value


def values(tokens):
    result = []
    i = 0
    while i < len(tokens):
        token = tokens[i]
        if token['type'] == 9:
            if i+1 >= len(tokens) or tokens[i+1]['type'] != 10 or not isinstance(tokens[i+1].get('resolved_text'), str):
                raise ValueError('Unresolved or truncated linked string')
            result.append(tokens[i+1]['resolved_text'])
            i += 2
        else:
            if token['type'] not in (2, 7) or token.get('value') is None:
                raise ValueError('Unsupported scalar payload')
            result.append(integer(token) if token['type'] == 2 else token['value'])
            i += 1
    return result


def fields(script, list_tags=()):
    ts = script['tokens']
    if len(ts) > 65536:
        raise ValueError('Spatial script exceeds token bound')
    result, i = [], 0
    while i < len(ts):
        if not command(ts[i]):
            raise ValueError(f'Expected command at token {i}')
        tag, start = ts[i]['value'], i
        i += 1
        if tag in list_tags:
            close = '[/'+tag[1:]
            while i < len(ts) and not command(ts[i], close):
                i += 1
            if i == len(ts):
                raise ValueError(f'Unclosed {tag}')
            end, i = i, i+1
        else:
            while i < len(ts) and not command(ts[i]):
                i += 1
            end = i
        result.append(dict(tag=tag, token_index=start, offset=ts[start]['offset'],
                           payload=deepcopy(ts[start+1:end]), tokens=deepcopy(ts[start:i])))
    return result


def scalar(field, kinds):
    data = values(field['payload'])
    if len(data) != len(kinds) or any(type(v) is not k for v, k in zip(data, kinds)):
        raise ValueError('Invalid scalar arity/type for '+field['tag'])
    return data


def rows(field, width):
    data = [integer(t) for t in field['payload']]
    if len(data) % width:
        raise ValueError(f'{field["tag"]} needs complete {width}-integer rows')
    return [data[i:i+width] for i in range(0, len(data), width)]


def decode_stm(script):
    ordered = fields(script, ('[slot type]', '[stage]', '[survival]'))
    result = dict(path=script['path'], name='', map_image='', map_frame=0, dungeon=0,
                  areas=[], fields=ordered, source_tokens=deepcopy(script['tokens']))
    area, district = None, None
    for field in ordered:
        tag = field['tag']
        field['known'] = True
        if tag in ('[name]', '[map image]', '[dungeon]'):
            if area is not None:
                raise ValueError('Unexpected top-level field inside STM area')
            if tag == '[name]':
                result['name'], = scalar(field, (str,))
            elif tag == '[map image]':
                result['map_image'], result['map_frame'] = scalar(field, (str, int))
            else:
                result['dungeon'], = scalar(field, (int,))
        elif tag == '[area]':
            if area is not None:
                raise ValueError('Nested STM area')
            area_id, = scalar(field, (int,))
            area = dict(area_id=area_id, slot_image='', slot_types=[], districts=[], survival=0,
                        token_index=field['token_index'])
            district = dict(district_id=0, append_image='', append_frame=0, stages=[])
        elif tag == '[/area]':
            if area is None or field['payload']:
                raise ValueError('Unexpected STM area close')
            result['areas'].append(deepcopy(area))
            area, district = None, None
        elif tag in ('[slot image]', '[slot type]', '[district]', '[append image]', '[stage]', '[survival]'):
            if area is None:
                raise ValueError('STM scoped field outside area')
            if tag == '[slot image]':
                area['slot_image'], = scalar(field, (str,))
            elif tag == '[slot type]':
                # 01314D0E finds by the first integer; duplicate keys keep the first row.
                for row in rows(field, 5):
                    if not any(r[0] == row[0] for r in area['slot_types']):
                        area['slot_types'].append(row)
            elif tag == '[district]':
                district_id, = scalar(field, (int,))
                district = dict(district_id=district_id, append_image='', append_frame=0, stages=[])
            elif tag == '[append image]':
                district['append_image'], district['append_frame'] = scalar(field, (str, int))
            elif tag == '[stage]':
                district['stages'].extend(rows(field, 4))
                # 01314EE3 appends the current district after every [stage] block.
                area['districts'].append(deepcopy(district))
            else:
                data = [integer(t) for t in field['payload']]
                if len(data) != 1:
                    raise ValueError('1031 survival reader accepts one integer')
                area['survival'] = data[0]
        else:
            field['known'] = False
    if area is not None:
        raise ValueError('Unclosed STM area')
    result['schema_complete'] = all(f['known'] for f in ordered)
    result['semantic_complete'] = False
    return result


def decode_wdm(script):
    list_tags = ('[dungeon]', '[hell quest]', '[hell freepass item]', '[item condition]', '[minimap points]')
    ordered = fields(script, list_tags)
    result = dict(path=script['path'], fields=ordered, source_tokens=deepcopy(script['tokens']),
                  name='', map_image='', map_frame=0, ui_path='', dungeons=[])
    for field in ordered:
        tag = field['tag']
        field['known'] = True
        if tag in ('[name]', '[map image]', '[ui path]'):
            if tag == '[name]':
                result['name'], = scalar(field, (str,))
            elif tag == '[map image]':
                result['map_image'], result['map_frame'] = scalar(field, (str, int))
            else:
                result['ui_path'], = scalar(field, (str,))
        elif tag == '[dungeon]':
            result['dungeons'] = []  # 012EC899 clears this collection on each occurrence.
            payload, i = field['payload'], 0
            while i < len(payload):
                dungeon_id = integer(payload[i])
                i += 1
                in_progress = i < len(payload) and command(payload[i], '[in progress]')
                i += int(in_progress)
                if i >= len(payload):
                    raise ValueError('Truncated WDM dungeon row')
                condition = integer(payload[i])
                i += 1
                result['dungeons'].append(dict(dungeon_id=dungeon_id, condition_value=condition,
                                               in_progress=int(in_progress)))
        elif tag == '[hell dungeon]':
            value, = scalar(field, (int,))
            field['boolean_value'] = value != 0
        elif tag == '[hell freepass item]' or tag == '[minimap points]':
            field['rows'] = rows(field, 2)
        elif tag in ('[hell quest]', '[item condition]'):
            field['raw_integer_values'] = [integer(t) for t in field['payload']]
            if tag == '[item condition]':
                field['native_secondary_read'] = '012ECA7D/012ECAAC read another integer without saving it; purpose unresolved'
        else:
            field['known'] = False
    result['schema_complete'] = all(f['known'] for f in ordered)
    result['semantic_complete'] = False
    return result
