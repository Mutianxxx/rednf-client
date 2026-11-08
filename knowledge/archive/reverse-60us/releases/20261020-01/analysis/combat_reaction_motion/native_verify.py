"""Run original reaction instructions in a separate, synthetic numeric PE32.

Never launches DFO. Protected-value and v344 getters are explicit plain fixtures;
arithmetic bodies and C01544 retain original addresses and bytes. No target file
is written. Both 53-bit and 64-bit x87 modes are fixture choices, not observations
of the client's runtime control word.
"""
from pathlib import Path
from dataclasses import asdict
import hashlib, json, struct, subprocess, sys
from reaction_model import horizontal, gravity, impulse, payload_scale

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT/'analysis/deps'))
import pefile

SOURCE_HASH = 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
raw = (ROOT/'DFO/DFO_fixed_v3.exe').read_bytes()
assert hashlib.sha256(raw).hexdigest() == SOURCE_HASH
original = pefile.PE(data=raw)


def source_bytes(va, size):
    off = original.get_offset_from_rva(va-0x400000)
    return raw[off:off+size]


def u32(value):
    return struct.pack('<I', value & 0xffffffff)


def floatbits(value):
    return struct.unpack('<I', struct.pack('<f', value))[0]


def align(value, boundary):
    return (value+boundary-1)//boundary*boundary


def cases():
    horizontal_cases = []
    for kind in (-1, 0, 1, 2, 3):
        for scale_integer in (0, 1, 50, 100, 200):
            horizontal_cases.append(dict(kind=kind, special_flag=False,
                scale=payload_scale(scale_integer), stat218=1000, stat220=1.0,
                motion_enabled=True))
    for stat218, stat220 in [(0, 1), (1999, 1), (2000, 1), (3000, 1),
                              (1001, .999), (1000, .5), (-1000, 1)]:
        horizontal_cases.append(dict(kind=0, special_flag=False, scale=1.0,
            stat218=stat218, stat220=stat220, motion_enabled=True))
    for kind, flag, enabled in [(0, True, True), (1, True, True), (2, True, True),
                                (0, False, False), (1, False, False), (-1, True, False)]:
        horizontal_cases.append(dict(kind=kind, special_flag=flag, scale=1.0,
            stat218=1000, stat220=1.0, motion_enabled=enabled))
    gravity_cases = []
    for fixed in (False, True):
        for base in (0, -1000, -1500):
            for map_present in (False, True):
                gravity_cases.append(dict(fixed_base=fixed, actor163c=base,
                    stat238=85, stat240=1.0, map_present=map_present,
                    map9dc=50, actor1660=25))
    for stat238, stat240 in [(100, 1), (101, .5), (1000, 1.234), (0, 1)]:
        gravity_cases.append(dict(fixed_base=False, actor163c=-1500,
            stat238=stat238, stat240=stat240, map_present=False, map9dc=0, actor1660=0))
    impulse_cases = [dict(param1=a, param2=b, param3=c) for a,b,c in [
        (400, 100, 100), (-400, 100, 100), (400, 60000, 100),
        (400, 100000, 100), (0, 100, 100), (286, 100000, 100),
        (400, 12345, 99), (400, 12345, 101), (1000000, 100, 100)]]
    return horizontal_cases, gravity_cases, impulse_cases


def build_harness(hcases, gcases, icases):
    first = bytearray(0xf000)  # VA401000..410000; larger zero-filled virtual tail
    native = bytearray(0x5000)
    trunc = bytearray(0x1000)
    constants = bytearray(0x1000)
    constant_ranges = [(0xcd1434, 8), (0xcd1440, 4), (0xcd145c, 4)]
    copies = [(0x4b98f0, 0x37), (0x4b9fa0, 0x113), (0x4ba620, 0x149), (0x4bdd40, 0x33)]
    for va, size in copies:
        native[va-0x4b9000:va-0x4b9000+size] = source_bytes(va, size)
    trunc[0x544:0x5b9] = source_bytes(0xc01544, 0x75)
    for va, size in constant_ranges:
        constants[va-0xcd1000:va-0xcd1000+size] = source_bytes(va, size)
    # Plain decoded-value providers are substitutes, never called original data.
    providers = {
        0x402010: b'\xc3',  # protected destructor
        0x402060: bytes.fromhex('8b01c3'),  # decoded int *(ecx)
        0x402150: bytes.fromhex('8b4424048b0089018bc1c20400'),  # local value ctor
        0x401100: bytes.fromhex('8b4120c20400'),  # actor.v344(3) -> actor fixture +20
    }
    for va, code in providers.items():
        first[va-0x401000:va-0x401000+len(code)] = code
    flt = bytearray(0x1000)
    flt[0x3b0:0x3b3] = bytes.fromhex('d901c3')  # decoded float fld [ecx]
    # One imports table used only by our numeric harness.
    imports_rva = 0x3000
    dll_rva, names_rva, ilt_rva, iat_rva = 0x3040, 0x3060, 0x30c0, 0x30e0
    blob = bytearray(0x200)
    blob[:20] = struct.pack('<5I', ilt_rva, 0, 0, dll_rva, iat_rva)
    blob[0x40:0x4d] = b'kernel32.dll\0'
    names, cursor = ['GetStdHandle', 'WriteFile', 'ExitProcess'], names_rva
    for i, name in enumerate(names):
        encoded = b'\0\0'+name.encode()+b'\0'
        blob[cursor-imports_rva:cursor-imports_rva+len(encoded)] = encoded
        blob[ilt_rva-imports_rva+i*4:ilt_rva-imports_rva+i*4+4] = u32(cursor)
        blob[iat_rva-imports_rva+i*4:iat_rva-imports_rva+i*4+4] = u32(cursor)
        cursor = align(cursor+len(encoded), 2)
    first[imports_rva-0x1000:imports_rva-0x1000+len(blob)] = blob
    first[0x200:0x202] = struct.pack('<H', 0x027f)
    actor, stats, vtable, map_owner, map_data = 0x410000, 0x413000, 0x414000, 0x415000, 0x416000
    scratch, output, written = 0x418000, 0x420000, 0x419000
    entry, code, record = 0x404000, bytearray(), 0

    def emit(data):
        code.extend(data)

    def push(value):
        emit(b'\x68'+u32(value))

    def mem(address, value):
        emit(b'\xc7\x05'+u32(address)+u32(value))

    def call(va):
        emit(b'\xe8'+u32(va-(entry+len(code))-5))

    def capture(address, dest):
        emit(b'\xa1'+u32(address)+b'\xa3'+u32(dest))

    for precision in (64, 53):
        emit(bytes.fromhex('dbe3'))
        if precision == 53:
            emit(b'\xd9\x2d'+u32(0x401200))
        mem(actor, vtable)
        mem(actor+0x20, stats)
        mem(vtable+0x344, 0x401100)
        for values in hcases:
            mem(stats+0x218, values['stat218'])
            mem(stats+0x220, floatbits(values['stat220']))
            mem(actor+0x18d8, int(values['motion_enabled']))
            push(floatbits(values['scale']))
            push(int(values['special_flag']))
            push(values['kind'])
            push(scratch+4)
            push(scratch)
            emit(b'\xb9'+u32(actor))
            call(0x4ba620)
            dest = output+record*12
            emit(b'\xa3'+u32(dest+8))
            capture(scratch, dest)
            capture(scratch+4, dest+4)
            record += 1
        for values in gcases:
            mem(stats+0x238, values['stat238'])
            mem(stats+0x240, floatbits(values['stat240']))
            mem(actor+0x163c, values['actor163c'])
            mem(actor+0x1660, values['actor1660'])
            mem(actor+0x100, map_owner if values['map_present'] else 0)
            mem(map_owner+0x114, map_data)
            mem(map_data+0x9dc, values['map9dc'])
            push(int(values['fixed_base']))
            emit(b'\xb9'+u32(actor))
            call(0x4b9fa0)
            emit(b'\xa3'+u32(output+record*12))
            record += 1
        for values in icases:
            for key in ('param3', 'param2', 'param1'):
                push(values[key])
            call(0x4b98f0)
            emit(b'\x83\xc4\x0c\xd9\x1d'+u32(output+record*12))
            record += 1
    push(-11)
    emit(b'\xff\x15'+u32(0x400000+iat_rva))
    push(0)
    push(written)
    push(record*12)
    push(output)
    emit(b'\x50\xff\x15'+u32(0x400000+iat_rva+4))
    push(0)
    emit(b'\xff\x15'+u32(0x400000+iat_rva+8))
    assert entry+len(code) < actor
    first[entry-0x401000:entry-0x401000+len(code)] = code
    sections = [
        (b'.harness', 0x1000, 0x32000, first, 0xe0000020),
        (b'.float', 0x33000, 0x86000, flt, 0x60000020),
        (b'.native', 0xb9000, 0x748000, native, 0x60000020),
        (b'.trunc', 0x801000, 0xd0000, trunc, 0x60000020),
        (b'.const', 0x8d1000, 0x1000, constants, 0x40000040)]
    headers = bytearray(0x400)
    headers[:2] = b'MZ'
    struct.pack_into('<I', headers, 0x3c, 0x80)
    headers[0x80:0x84] = b'PE\0\0'
    headers[0x84:0x98] = struct.pack('<HHIIIHH', 0x14c, len(sections), 0,0,0,224,0x0103)
    opt = 0x98
    struct.pack_into('<HBBIIIIII', headers, opt, 0x10b,0,0,0x16000,0x1000,0,entry-0x400000,0x1000,0x8d1000)
    struct.pack_into('<III', headers, opt+28, 0x400000,0x1000,0x200)
    struct.pack_into('<HHHHHH', headers, opt+40, 4,0,0,0,4,0)
    struct.pack_into('<IIIIHH', headers, opt+52, 0,0x8d2000,0x400,0,3,0)
    struct.pack_into('<IIIIII', headers, opt+72, 0x100000,0x1000,0x100000,0x1000,0,16)
    struct.pack_into('<II', headers, opt+104, imports_rva,40)
    out = bytearray(headers)
    for i, (name,rva,vsize,data,flags) in enumerate(sections):
        offset, size = len(out), align(len(data),0x200)
        out[0x178+i*40:0x178+(i+1)*40] = struct.pack('<8sIIIIIIHHI', name,vsize,rva,size,offset,0,0,0,0,flags)
        out.extend(data)
        out.extend(b'\0'*(size-len(data)))
    checked = pefile.PE(data=out)
    assert [i.name.decode() for i in checked.DIRECTORY_ENTRY_IMPORT[0].imports] == names
    return bytes(out), copies


def main():
    hcases, gcases, icases = cases()
    image, copies = build_harness(hcases, gcases, icases)
    executable = HERE/'native-reaction-harness.exe'
    executable.write_bytes(image)
    result = subprocess.run([str(executable)], cwd=HERE, capture_output=True, timeout=20)
    (HERE/'native-output.bin').write_bytes(result.stdout)
    total = (len(hcases)+len(gcases)+len(icases))*2
    if result.returncode or len(result.stdout) != total*12:
        raise RuntimeError(f'Numeric harness exit {result.returncode:#x}, bytes {len(result.stdout)} / {total*12}, stderr={result.stderr!r}')
    rows, record = [], 0
    for precision in (64,53):
        for values in hcases:
            speed, acceleration, duration = struct.unpack_from('<iii', result.stdout, record*12)
            expected = horizontal(**values)
            match = (speed,acceleration,duration) == (expected.speed,expected.acceleration,expected.duration)
            rows.append(dict(kind='horizontal', x87_precision=precision, inputs=values,
                native=dict(speed=speed,acceleration=acceleration,duration=duration),
                model=asdict(expected), matches=match))
            record += 1
        for values in gcases:
            actual = struct.unpack_from('<i', result.stdout, record*12)[0]
            expected = gravity(**values)
            rows.append(dict(kind='gravity',x87_precision=precision,inputs=values,native=actual,model=expected,matches=actual==expected))
            record += 1
        for values in icases:
            actual_bytes = result.stdout[record*12:record*12+4]
            expected = impulse(**values)
            rows.append(dict(kind='impulse',x87_precision=precision,inputs=values,
                native=struct.unpack('<f',actual_bytes)[0],model=expected,
                matches=actual_bytes==struct.pack('<f',expected)))
            record += 1
    failures = [r for r in rows if not r['matches']]
    report = dict(schema='60us-native-reaction-vectors-v1',
        evidence_kind='extracted original instructions with declared plain providers in a synthetic PE32; no DFO launch',
        source_sha256=SOURCE_HASH, original_client_runtime=False,
        extracted_bodies=[dict(va=hex(va),size=size,sha256=hashlib.sha256(source_bytes(va,size)).hexdigest()) for va,size in copies],
        harness_sha256=hashlib.sha256(image).hexdigest(), output_sha256=hashlib.sha256(result.stdout).hexdigest(),
        matches=len(rows)-len(failures), mismatches=len(failures), vectors=rows,
        limitations=['Runtime protected getters replaced by plain fixture getters.',
            'Runtime stats assumed unchanged across both horizontal-stat reads.',
            'Client x87 control word not observed; two explicit fixture settings checked.',
            'No hit qualification, HP, owner collision, state handler or actual ANI dispatch is executed.'])
    (HERE/'native-vectors.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:report[k] for k in ['matches','mismatches','original_client_runtime']}))
    if failures:
        print(json.dumps(failures,indent=2))
        raise SystemExit(1)


if __name__ == '__main__':
    main()
