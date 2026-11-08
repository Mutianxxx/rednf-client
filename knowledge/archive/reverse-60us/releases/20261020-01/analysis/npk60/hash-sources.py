import sys,json,hashlib,time
from pathlib import Path
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets,_sha_file
root=Path(r'D:\dnf\60US\DFO\ImagePacks2');assets=Assets(root)
rows=[]
for name,meta in assets.packages.items():
 rows.append({**meta,'sha256':_sha_file(root/name),'package':name})
Path(r'D:\dnf\60US\analysis\npk60\source-identities.json').write_text(json.dumps({'root':str(root),'total_bytes':sum(r['size'] for r in rows),'packages':rows},ensure_ascii=False,indent=2),encoding='utf8')
print('hashed packages',len(rows))
