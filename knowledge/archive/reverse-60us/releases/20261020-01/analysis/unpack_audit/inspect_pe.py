"""Read-only PE/entry/import audit of the two user-selected client files.

This is a packing/layout check, not an unpacker or a successful execution test.
"""
from pathlib import Path
from collections import Counter
import hashlib
import json
import math
import struct
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32


def entropy(data):
    if not data:
        return 0
    n = len(data)
    return -sum(c/n * math.log2(c/n) for c in Counter(data).values())


def audit(path):
    raw = path.read_bytes()
    pe = pefile.PE(data=raw)
    base = pe.OPTIONAL_HEADER.ImageBase
    entry = base + pe.OPTIONAL_HEADER.AddressOfEntryPoint
    sections = []
    for s in pe.sections:
        data = raw[s.PointerToRawData:s.PointerToRawData+s.SizeOfRawData]
        sections.append(dict(name=s.Name.rstrip(b'\0').decode('ascii', 'backslashreplace'),
            va=hex(base+s.VirtualAddress), rva=hex(s.VirtualAddress),
            virtual_size=s.Misc_VirtualSize, file_offset=s.PointerToRawData,
            raw_size=s.SizeOfRawData, characteristics=hex(s.Characteristics),
            entropy=entropy(data), zero_fraction=data.count(0)/len(data) if data else None,
            sha256=hashlib.sha256(data).hexdigest()))
    imports = []
    for d in getattr(pe, 'DIRECTORY_ENTRY_IMPORT', []):
        entries = []
        for i in d.imports:
            entries.append(dict(iat=hex(i.address), name=i.name.decode('ascii', 'backslashreplace') if i.name else None,
                                ordinal=i.ordinal))
        imports.append(dict(dll=d.dll.decode('ascii', 'backslashreplace'), entries=entries,
                            descriptor=hex(base+d.struct.get_file_offset()) if False else d.struct.get_file_offset()))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    locations = []
    for label, va, size in [('entry', entry, 0x100),
                            ('pvf_open', 0xa570d0, 0x40),
                            ('monster_slot654', 0x4fa1d0, 0x60),
                            ('slot654_thunk', 0x13baa5f, 0x30),
                            ('suspected_dispatch', 0x12ee7c9, 0x80)]:
        rva = va-base
        sec = pe.get_section_by_rva(rva) if rva >= 0 else None
        if not sec:
            locations.append(dict(label=label,va=hex(va),mapped=False))
            continue
        delta = rva-sec.VirtualAddress
        if delta >= sec.SizeOfRawData:
            locations.append(dict(label=label,va=hex(va),mapped=True,file_backed=False,
                                  section=sec.Name.rstrip(b'\0').decode('ascii', 'backslashreplace')))
            continue
        off = sec.PointerToRawData+delta
        data = raw[off:off+min(size,sec.SizeOfRawData-delta)]
        stem = path.stem+'-'+label
        (HERE/(stem+'.bin')).write_bytes(data)
        dis = '\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(data, va))+'\n'
        (HERE/(stem+'.asm')).write_text(dis, encoding='utf8')
        locations.append(dict(label=label,va=hex(va),mapped=True,file_backed=True,file_offset=off,
            size=len(data),sha256=hashlib.sha256(data).hexdigest(),first32=data[:32].hex(),asm=stem+'.asm'))
    tls = None
    if hasattr(pe, 'DIRECTORY_ENTRY_TLS'):
        st = pe.DIRECTORY_ENTRY_TLS.struct
        cb = st.AddressOfCallBacks
        callbacks = []
        if cb:
            for i in range(256):
                try:
                    value = struct.unpack('<I', pe.get_data(cb-base+i*4, 4))[0]
                except (pefile.PEFormatError, struct.error):
                    break
                if not value:
                    break
                callbacks.append(hex(value))
        tls = dict(start=hex(st.StartAddressOfRawData),end=hex(st.EndAddressOfRawData),
            index=hex(st.AddressOfIndex),callback_array=hex(cb),callbacks=callbacks)
    markers = []
    for token in (b'Themida',b'themida',b'WinLicense',b'Winlicense',b'Oreans',b'.themida',b'VMProtect',b'UPX!'):
        at = 0
        while True:
            at = raw.find(token,at)
            if at < 0:
                break
            markers.append(dict(text=token.decode(),file_offset=at))
            at += len(token)
    overlay = pe.get_overlay_data_start_offset()
    return dict(path=str(path.relative_to(ROOT)),sha256=hashlib.sha256(raw).hexdigest(),size=len(raw),
        machine=hex(pe.FILE_HEADER.Machine),timestamp=pe.FILE_HEADER.TimeDateStamp,
        image_base=hex(base),entry_va=hex(entry),size_of_image=pe.OPTIONAL_HEADER.SizeOfImage,
        subsystem=pe.OPTIONAL_HEADER.Subsystem,dll_characteristics=hex(pe.OPTIONAL_HEADER.DllCharacteristics),
        sections=sections,imports=imports,import_dll_count=len(imports),
        import_symbol_count=sum(len(d['entries']) for d in imports),tls=tls,
        directories=[dict(name=d.name,rva=hex(d.VirtualAddress),size=d.Size) for d in pe.OPTIONAL_HEADER.DATA_DIRECTORY],
        locations=locations,markers=markers,overlay_offset=overlay,
        overlay_size=len(raw)-overlay if overlay else 0,
        pe_warnings=pe.get_warnings(),executed=False,unpacking_attempted=False)


def main():
    results = [audit(ROOT/'DFO'/name) for name in ('DFO.exe','DFO_fixed_v3.exe')]
    (HERE/'pe-audit.json').write_text(json.dumps(results,indent=2)+'\n',encoding='utf8')
    for x in results:
        print(x['path'], x['sha256'])
        print('size',x['size'],'entry',x['entry_va'],'imports',x['import_dll_count'],x['import_symbol_count'],'TLS',x['tls'])
        for s in x['sections']:
            print(s['name'],s['va'],'vsize',hex(s['virtual_size']),'raw',hex(s['raw_size']),'offset',hex(s['file_offset']),'entropy',round(s['entropy'],3))
        print('markers',x['markers'])
        for loc in x['locations']:
            print(loc)


if __name__ == '__main__':
    main()
