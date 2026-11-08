"""Preserve sample source bytes, strict CP949 transcriptions, and provenance."""
from pathlib import Path
import hashlib
import json
from pvf60 import Pvf60
pvf=Pvf60('DFO/Script.pvf')
root=Path(__file__).resolve().parent/'samples'
root.mkdir(exist_ok=True)
names=['skill/skilllist.usa.lst','skill/swordmanskill.lst','skill/swordman/hardattack.skl',
       'skill/swordman/upperslash.skl','character/character.usa.lst',
       'character/swordman/swordman.chr','string.usa.lst']
manifest=[]
for name in names:
    b=pvf.read(name)
    file=name.replace('/','__')
    (root/(file+'.raw')).write_bytes(b)
    item=dict(pvf.by_path[name],sha256=hashlib.sha256(b).hexdigest(),raw_file=file+'.raw')
    try:
        text=b.decode('cp949',errors='strict')
        (root/(file+'.utf8.txt')).write_bytes(text.encode('utf-8'))
        item.update(strict_decoding='cp949',text_file=file+'.utf8.txt')
    except UnicodeDecodeError as exc:
        item.update(strict_decoding='failed',error=str(exc))
    manifest.append(item)
(root/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(manifest,ensure_ascii=True,indent=2))
