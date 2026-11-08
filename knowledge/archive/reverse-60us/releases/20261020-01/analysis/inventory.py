"""Read-only PE/PVF evidence inventory. Run from the workspace root."""
import collections
import hashlib
import json
import math
import pathlib
import re
import struct
import sys

HERE = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(HERE / 'deps'))
import pefile


def inspect(path):
    data = path.read_bytes()
    out = {'path': str(path), 'size': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
    if data[:2] != b'MZ':
        out['header_hex'] = data[:100].hex()
        return out
    pe = pefile.PE(data=data)
    out.update(machine=hex(pe.FILE_HEADER.Machine), timestamp=pe.FILE_HEADER.TimeDateStamp,
               image_base=hex(pe.OPTIONAL_HEADER.ImageBase),
               entrypoint_rva=hex(pe.OPTIONAL_HEADER.AddressOfEntryPoint),
               image_size=hex(pe.OPTIONAL_HEADER.SizeOfImage))
    out['sections'] = []
    for sec in pe.sections:
        raw = sec.get_data()
        ent = -sum(n / len(raw) * math.log2(n / len(raw)) for n in collections.Counter(raw).values()) if raw else 0
        out['sections'].append({'name': sec.Name.rstrip(b'\0').decode('ascii', 'backslashreplace'),
                                'rva': hex(sec.VirtualAddress), 'virtual_size': hex(sec.Misc_VirtualSize),
                                'raw_offset': hex(sec.PointerToRawData), 'raw_size': hex(sec.SizeOfRawData),
                                'flags': hex(sec.Characteristics), 'entropy': round(ent, 4)})
    out['imports'] = {dll.dll.decode('ascii', 'backslashreplace'): [
        {'name': imp.name.decode('ascii', 'backslashreplace') if imp.name else '#'+str(imp.ordinal),
         'iat_va': hex(imp.address)} for imp in dll.imports]
        for dll in getattr(pe, 'DIRECTORY_ENTRY_IMPORT', [])}
    pattern = re.compile(rb'pvf|stringtable|n_string|skill/|character/|\.pdb|Themida|UPX|WinLicense|ASPack|Petite|VMProtect|ScriptFile|PackFile', re.I)
    strings = []
    for m in re.finditer(rb'[ -~]{5,}', data):
        if pattern.search(m.group()):
            try:
                va = hex(pe.OPTIONAL_HEADER.ImageBase + pe.get_rva_from_offset(m.start()))
            except pefile.PEFormatError:
                va = None
            strings.append({'offset': hex(m.start()), 'va': va, 'text': m.group().decode('ascii')})
    out['relevant_strings'] = strings
    out['debug'] = []
    for dbg in getattr(pe, 'DIRECTORY_ENTRY_DEBUG', []):
        out['debug'].append({'type': dbg.struct.Type, 'data': repr(data[dbg.struct.PointerToRawData:dbg.struct.PointerToRawData + dbg.struct.SizeOfData])})
    return out


if __name__ == '__main__':
    report = [inspect(pathlib.Path(p)) for p in sys.argv[1:]]
    (HERE / 'inventory.json').write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
    for item in report:
        print(json.dumps({k: v for k, v in item.items() if k != 'imports'}, ensure_ascii=True, indent=2))
