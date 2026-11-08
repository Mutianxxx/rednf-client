"""Retain source-bound static evidence for ANI transforms and vertex modulation.

This reads disk artifacts only. It is not a recording of a game draw call.
"""
from pathlib import Path
import hashlib
import json
import struct
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
OUT = HERE / 'transform'
sys.path[:0] = [str(ROOT/'analysis/deps'), str(ROOT/'combat-preview'), str(ROOT/'analysis')]
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from executable_source import BACKUP, ORIGINAL_SHA256, inspect_executable
from pvf60 import Pvf60
from pvf_model import parse_animation


def digest(data):
    return hashlib.sha256(data).hexdigest()


def main():
    original = BACKUP.read_bytes()
    assert digest(original) == ORIGINAL_SHA256
    current_path = ROOT/'DFO/DFO_fixed_v3.exe'
    selected = inspect_executable(current_path)
    assert selected['static_evidence_sha256'] == ORIGINAL_SHA256
    current = current_path.read_bytes()
    pe = pefile.PE(data=original)
    installed = pefile.PE(data=current)
    base = pe.OPTIONAL_HEADER.ImageBase
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    OUT.mkdir(parents=True, exist_ok=True)
    ranges = {
        'ani_rotation_rgba_parse': (0xA2912B, 0x66),
        'rgba_texture_dispatch': (0xB0E050, 0xB3),
        'texture_quad': (0xADD3D0, 0x220),
        'rotation_matrix_dispatch': (0xC3551A, 0x22),
        'rotation_matrix_x87': (0xC3553C, 0x7A),
        'math_cpu_dispatch': (0xC3788E, 0xDB),
        'quad_vertex_fill': (0xB08D30, 0x4E0),
        'texture_stage_setup': (0xB08383, 0x53),
    }
    slices = []
    for name, (va, size) in ranges.items():
        data = pe.get_data(va-base, size)
        assert len(data) == size
        same = data == installed.get_data(va-installed.OPTIONAL_HEADER.ImageBase, size)
        assert same, name
        (OUT/(name+'.bin')).write_bytes(data)
        (OUT/(name+'.asm')).write_text('\n'.join(
            f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}'
            for i in md.disasm(data, va))+'\n', encoding='utf-8')
        slices.append(dict(name=name, va=hex(va), size=size,
                           file_offset=pe.get_offset_from_rva(va-base),
                           sha256=digest(data), selected_disk_bytes_equal=same))

    def u32(va):
        return struct.unpack('<I', pe.get_data(va-base, 4))[0]

    tables = []
    for name, va, col, descriptor in [
        ('CND3DBaseTexture', 0xE6A074, 0xECBCC0, 0xFF2664),
        ('CND3DTexture32', 0xE6A12C, 0xECBD14, 0xFF268C),
    ]:
        assert u32(va-4) == col
        assert u32(col+0xC) == descriptor
        assert u32(va+0xA0) == 0xADD3D0
        data = pe.get_data(va-base-4, 0xA8)
        (OUT/(name+'-vtable.bin')).write_bytes(data)
        typename = pe.get_data(descriptor-base+8, 96).split(b'\0', 1)[0].decode('ascii')
        tables.append(dict(name=name, vtable=hex(va), complete_object_locator=hex(col),
                           type_descriptor=hex(descriptor), decorated_type=typename,
                           slot_a0=hex(u32(va+0xA0)), sha256=digest(data)))
    # C3788E copies the baseline table FFB168 to FFB080 before CPU selection.
    assert u32(0xFFB100) == 0xC3551A
    assert u32(0xFFB168+(0xFFB100-0xFFB080)) == 0xC3553C
    for name, va, size in [('math-dispatch-tables', 0xFFB080, 0x1D8),
                           ('texture-rtti', 0xFF2664, 0x50),
                           ('texture-col', 0xECBCC0, 0x68)]:
        data = pe.get_data(va-base, size)
        (OUT/(name+'.bin')).write_bytes(data)
        slices.append(dict(name=name, va=hex(va), size=size, sha256=digest(data),
                           kind='data', selected_disk_bytes_equal=data == installed.get_data(va-base, size)))

    pvf = Pvf60(ROOT/'DFO/Script.pvf')
    pvf_sha = digest(pvf.data)
    assert pvf_sha == '23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98'
    samples = []
    for path in ['character/swordman/effect/animation/soulbringer2.ani',
                 'character/swordman/effect/animation/hundredsword/finishcircle1.ani',
                 'character/swordman/effect/animation/hundredsword/flash1.ani']:
        raw = pvf.read(path)
        parsed = parse_animation(raw, path)
        (OUT/Path(path).name).write_bytes(raw)
        frames = [dict(index=f['index'], fields=[field for field in f['fields']
                  if field['tag'].upper() in ('IMAGE', 'IMAGE POS', 'IMAGE ROTATE', 'IMAGE RATE', 'RGBA', 'GRAPHIC EFFECT')])
                  for f in parsed['frames']]
        samples.append(dict(path=path, sha256=digest(raw), size=len(raw),
                            encoding='cp949', archive_sha256=pvf_sha, crc_verified=True,
                            entry=pvf.by_path[path], frames=frames))

    old = json.loads((ROOT/'analysis/rea/evidence-index.json').read_text(encoding='utf-8'))
    reused = [dict(evidence_id=e['evidence_id'], result_file=e['result_file'],
                   address=e['address']) for e in old if (e.get('address') or '').lower()
              in ('0xa23d60', '0x5383d0', '0xb08200')]
    result = dict(source_path=str(BACKUP), source_sha256=ORIGINAL_SHA256,
        selected_executable=selected, evidence_kind='static PE bytes, REA pseudocode, original PVF data',
        runtime_draw_trace=False, slices=slices, texture_vtables=tables,
        matrix_dispatch=dict(static_pointer='0xc3551a', baseline_implementation='0xc3553c',
                             cpu_selected_runtime_pointer_observed=False),
        reused_rea=reused, texture_quad_rea='ev_d7062f931a7f0b1868e46746fc93b88b6e853b7425cc61669a2f0dfa0f2a7aad',
        pvf_samples=samples,
        contract=dict(rotation_unit='radians', matrix_angle='negative source angle',
                      vertex_rgb='texture.rgb * frame.rgb / 255',
                      vertex_alpha='texture.alpha * frame.alpha / 255',
                      normal_origin_canvas_order=['translate(actorX,actorY-actorZ)',
                          'scale(directionSign*rateX,rateY)', 'rotate(-sourceAngle)',
                          'translate(imagePosX,imagePosY)', 'drawImage(cropX,cropY)']),
        limitations=['Static disk-byte equality does not establish launcher/runtime equivalence.',
                     'Baseline x87 matrix and CPU dispatcher retained; no live draw trace or runtime CPU-target sample.',
                     'Transform applies to the normal IMAGE POS origin; center-origin mode remains unimplemented.',
                     'Interpolation, native clocks, alternate graphic effects and original-game pixel equality remain unverified.'])
    (OUT/'evidence-index.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(dict(native_slices=len(slices), vtables=len(tables), pvf_samples=len(samples),
                          selected_binding=selected['binding'], runtime_draw_trace=False)))


if __name__ == '__main__':
    main()
