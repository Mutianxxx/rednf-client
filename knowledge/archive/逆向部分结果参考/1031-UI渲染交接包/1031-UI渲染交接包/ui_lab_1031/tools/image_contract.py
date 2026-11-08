"""Evidence-bound routing diagnostics; not a replacement native renderer."""
import struct


EVIDENCE = 'reports/remaining-followup/evidence.json'


def context_type(row):
    state = row.get('draw_state', {})
    arguments = row.get('args', [])
    if len(arguments) < 16 or type(state.get('context')) is not int or state['context'] <= 0 or state['context'] != arguments[15]:
        return None
    try:
        payload = bytes.fromhex(row.get('payload_hex', ''))
    except (TypeError, ValueError):
        return None
    if len(payload) < 0x0c:
        return None
    return struct.unpack_from('<I', payload, 8)[0]


def unsupported_image_reason(state, site=None):
    if state.get('image_vtable') != 0x185c76c:
        return 'Image vtable is not 0185C76C; consumer layout unconfirmed'
    if state.get('consumer_verified') is not True:
        return 'Native consumer guard was not verified for this request'
    destination_type = state.get('context_type')
    if site == 7 and destination_type in (8, 14, 15, 16):
        return ('Destination context type '+str(destination_type)+' routes 011DB180 -> 011DADE0; '
                'destination format/surface state not captured; no type7 approximation')
    if destination_type is not None and destination_type != 7:
        route = '011DB180 simple dispatcher' if site == 7 else 'transformed pixel consumer'
        return 'Destination context type '+str(destination_type)+' has no supported captured '+route
    return 'Source image type '+str(state.get('image_type'))+' has no supported captured pixel consumer; destination route is not inferred from source type'
