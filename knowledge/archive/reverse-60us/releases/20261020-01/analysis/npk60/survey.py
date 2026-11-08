from pathlib import Path
import struct,json,collections
root=Path(r'D:\dnf\60US\DFO\ImagePacks2')
seed=(b'puchikon@neople dungeon and fighter '+b'DNF'*100)[:255]+b'\0'
entries=collections.defaultdict(list); versions=collections.Counter(); formats=collections.Counter(); errors=[]; examples=[]
packages=[]
for p in sorted(root.iterdir(),key=lambda p:p.name.casefold()):
 if p.suffix.casefold()!='.npk': continue
 with p.open('rb') as f:
  h=f.read(20)
  if h[:16]!=b'NeoplePack_Bill\0':
   errors.append([p.name,'magic',h.hex()]);continue
  n=struct.unpack_from('<I',h,16)[0];tab=f.read(n*264)
  packages.append({'name':p.name,'size':p.stat().st_size,'count':n})
  for i in range(n):
   off,length=struct.unpack_from('<II',tab,i*264); enc=tab[i*264+8:(i+1)*264]
   raw=bytes(a^b for a,b in zip(enc,seed)).split(b'\0')[0]
   try:name=raw.decode('ascii').replace('\\','/').lower()
   except UnicodeDecodeError:name=raw.decode('cp949').replace('\\','/').lower()
   if not name.startswith('sprite/'):name='sprite/'+name.lstrip('/')
   row={'logical':name,'package':p.name,'offset':off,'length':length,'table_index':i,'name_hex':raw.hex()}
   entries[name].append(row)
   f.seek(off);head=f.read(min(length,100));version=struct.unpack_from('<I',head,24)[0] if len(head)>=32 else -1
   versions[(head[:16],version)]+=1
   if head.startswith(b'Neople Img File\0'):
    count=struct.unpack_from('<I',head,28)[0]
    if version==2 and count and len(head)>=68:
     fmt,compress=struct.unpack_from('<ii',head,32);formats[(fmt,compress)]+=1
   if ('sm_body0000.img' in name or ('monster/goblin/' in name and len(examples)<15) or 'hardattack' in name):examples.append({**row,'header':head.hex()})
summary={'package_count':len(packages),'entry_count':sum(len(v) for v in entries.values()),'unique_count':len(entries),'versions':[(h.hex(),v,c) for (h,v),c in versions.items()],'first_frame_formats':[(a,b,c) for (a,b),c in formats.items()],'conflicts':{k:v for k,v in entries.items() if len(v)>1},'errors':errors,'examples':examples}
out=Path(r'D:\dnf\60US\analysis\npk60');(out/'survey.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8');(out/'entries.json').write_text(json.dumps(entries,ensure_ascii=False),encoding='utf-8');(out/'packages.json').write_text(json.dumps(packages,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in summary.items() if k not in ('conflicts','examples')},ensure_ascii=False,indent=2));print('conflict count',len(summary['conflicts']));print(json.dumps(examples[:12],ensure_ascii=False,indent=2))

