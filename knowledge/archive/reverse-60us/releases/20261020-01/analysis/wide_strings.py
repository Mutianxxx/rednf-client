import json
from pathlib import Path
import re
b=Path('DFO/DFO_fixed_v3.exe').read_bytes()
strings=[]
for m in re.finditer(rb'(?:[ -~]\x00){4,}', b):
    s=m.group().decode('utf-16-le')
    if re.search(r'PVF|Script|Skill|FilePack|\.cpp|\.h$',s,re.I):
        strings.append(dict(va=hex(0x400000+m.start()), file_offset=hex(m.start()), text=s))
Path('analysis/wide_strings.json').write_text(json.dumps(strings,indent=2),encoding='utf-8')
for s in strings:
    if any(x in s['text'].lower() for x in ['pvf','pack','compiled','skilllist','skill/','\\skill','scriptfile','hardattack','nstring']):
        print(s)
