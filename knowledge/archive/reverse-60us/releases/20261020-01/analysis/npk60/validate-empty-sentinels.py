from pathlib import Path
import sys,zlib,json,collections
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets
assets=Assets(r'D:\dnf\60US\DFO\ImagePacks2');counts=collections.Counter();nonzero=[]
for entries in assets.entries.values():
 for entry in entries:
  img=assets._load(entry)
  for r in img.records:
   if r.get('empty'):
    raw=img.data[r['pixel_offset']:r['pixel_offset']+r['pixel_length']]
    if r['compression']==6:raw=zlib.decompress(raw)
    counts[(r['color_format'],r['compression'],raw.hex())]+=1
    if any(raw) and len(nonzero)<15:nonzero.append([entry.package,entry.logical,r['index'],raw.hex(),r['raw_values']])
summary={'counts':[{'color':k[0],'compression':k[1],'raw':k[2],'count':v} for k,v in counts.items()],'nonzero_examples':nonzero}
Path(r'D:\dnf\60US\analysis\npk60\empty-sentinel-validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
print(summary)
