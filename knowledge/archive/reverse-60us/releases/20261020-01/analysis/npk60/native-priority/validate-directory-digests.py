from pathlib import Path
import struct,hashlib,json
root=Path(r'D:\dnf\60US\DFO\ImagePacks2');rows=[]
for p in root.iterdir():
 if p.suffix.casefold()!='.npk':continue
 with p.open('rb') as f:
  h=f.read(20);n=struct.unpack_from('<I',h,16)[0];table_end=20+n*264;f.seek(0);prefix=f.read(table_end);expected=f.read(32)
 digest=hashlib.sha256(prefix[:table_end//17*17]).digest()
 rows.append({'package':p.name,'table_end':table_end,'hashed_length':table_end//17*17,'stored_sha256':expected.hex(),'computed_sha256':digest.hex(),'valid':expected==digest})
summary={'algorithm':'SHA256 of first floor((20+count*264)/17)*17 bytes; digest stored at table_end','packages':len(rows),'valid':sum(r['valid'] for r in rows),'invalid':[r for r in rows if not r['valid']],'skin':[r for r in rows if 'swordman_equipment_avatar_skin' in r['package'].lower()],'all_results':rows}
Path(r'D:\dnf\60US\analysis\npk60\native-priority\directory-digest-validation.json').write_text(json.dumps(summary,indent=2),encoding='utf8')
print(json.dumps({k:v for k,v in summary.items() if k!='all_results'},indent=2))
