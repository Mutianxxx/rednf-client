import sys,json,collections
from pathlib import Path
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets
assets=Assets(r'D:\dnf\60US\DFO\ImagePacks2')
print('INDEX',len(assets.packages),sum(map(len,assets.entries.values())),len(assets.conflicts))
errors=[];versions=collections.Counter();formats=collections.Counter();compress=collections.Counter();trailing=[];total_frames=0
for logical, entries in assets.entries.items():
 for entry in entries:
  try:
   img=assets._load(entry);versions[img.version]+=1;total_frames+=len(img.records)
   for row in img.records:
    formats[row['color_format']]+=1
    if 'compression' in row:compress[row['compression']]+=1
   if img.trailing_bytes:trailing.append([entry.metadata(),img.trailing_bytes])
  except Exception as e:errors.append([entry.metadata(),str(e)])
summary={'packages':len(assets.packages),'entries':sum(map(len,assets.entries.values())),'conflict_paths':len(assets.conflicts),'versions':dict(versions),'formats':dict(formats),'compression':dict(compress),'total_frames':total_frames,'errors':errors,'trailing':trailing}
Path(r'D:\dnf\60US\analysis\npk60\parse-validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps({k:v for k,v in summary.items() if k not in ('errors','trailing')},indent=2));print('error count',len(errors),errors[:4]);print('trailing',len(trailing),trailing[:4])
