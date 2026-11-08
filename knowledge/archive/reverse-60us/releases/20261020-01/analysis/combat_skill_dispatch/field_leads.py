from pathlib import Path
import sys,re,struct
sys.path.insert(0,r'D:\dnf\60US\analysis\deps');import pefile
raw=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe').read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
for s in pe.sections:
    if not s.Characteristics&0x20000000:continue
    data=s.get_data()
    for m in re.finditer(bytes.fromhex(sys.argv[1]),data):
        va=base+s.VirtualAddress+m.start();o=s.PointerToRawData+m.start()
        print(f'{va:08X}',raw[o-6:o+22].hex())
