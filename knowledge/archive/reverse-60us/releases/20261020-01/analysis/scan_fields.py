from pathlib import Path
import re
b=Path('DFO/DFO_fixed_v3.exe').read_bytes()
lo,hi=0x1000,0x870000
for field in (0x180,0x188,0x190,0x198,0x10bf0d0):
    print('field',hex(field))
    matches=[]
    needle=field.to_bytes(4,'little')
    for m in re.finditer(re.escape(needle), b[lo:hi]):
        a=lo+m.start()
        if field!=0x10bf0d0 and not 0x140000<=a<0x170000:
            continue
        pro=b.rfind(b'\x55\x8b\xec',max(0,a-0x3000),a)
        matches.append((hex(a+0x400000),hex(pro+0x400000),b[max(0,a-4):a+12].hex()))
    print(matches)
