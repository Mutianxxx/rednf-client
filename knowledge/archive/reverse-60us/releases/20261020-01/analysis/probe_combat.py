"""Read selected current-version PVF files; preserve samples for analysis."""
from pathlib import Path
import json
import sys
from pvf60 import Pvf60

pvf=Pvf60('DFO/Script.pvf')
dest=Path('analysis/combat_samples')
dest.mkdir(exist_ok=True)
selected=[
 'character/character.usa.lst','skill/skilllist.usa.lst',
 'character/swordman/swordman.chr','skill/swordman/hardattack.skl',
 'character/swordman/animation/hardattack.ani',
 'character/swordman/animation/hardattack.ani.als',
 'character/swordman/attackinfo/hardattack.atk',
]
selected += [e['path'] for e in pvf.entries if e['path'].endswith('.chr')]
selected += [e['path'] for e in pvf.entries if 'goblin' in e['path'] and e['path'].endswith('.mob')][:2]
manifest=[]
for path in dict.fromkeys(selected):
 if path not in pvf.by_path:
  print('MISSING',path);continue
 data=pvf.read(path)
 out=dest/path
 out.parent.mkdir(exist_ok=True,parents=True)
 out.write_bytes(data)
 try:
  content=data.decode('cp949')
  out.with_suffix(out.suffix+'.utf8.txt').write_text(content,encoding='utf-8')
 except UnicodeDecodeError:
  content=repr(data[:160])
 print('\nFILE',path,len(data))
 print(content[:7500] if path.endswith('.ani') or path.endswith('.atk') else content[:1800])
 manifest.append(pvf.by_path[path])
(dest/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
