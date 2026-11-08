from pathlib import Path
import sys,json,hashlib,collections
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets,png_rgba
assets=Assets(r'D:\dnf\60US\DFO\ImagePacks2');out=Path(r'D:\dnf\60US\analysis\npk60')
conflicts={};same=0;different=0
for logical, entries in assets.entries.items():
 if len(entries)<2:continue
 rows=[]
 for entry in entries:
  with (assets.root/entry.package).open('rb') as f:f.seek(entry.offset);sha=hashlib.sha256(f.read(entry.length)).hexdigest()
  rows.append({**entry.metadata(),'img_sha256':sha})
 identical=len(set(r['img_sha256'] for r in rows))==1
 if identical:same+=1
 else:different+=1
 conflicts[logical]={'byte_identical':identical,'candidates':rows}
(out/'conflict-validation.json').write_text(json.dumps({'identical':same,'different':different,'conflicts':conflicts},ensure_ascii=False,indent=2),encoding='utf8')
print('CONFLICTS byte-identical',same,'different',different)
samples=json.loads((out/'samples.json').read_text(encoding='utf8'))
width,height=1000,300
rgba=bytearray(width*height*4)
for y in range(height):
 for x in range(width):
  tone=43 if (x//16+y//16)%2 else 60;p=(y*width+x)*4;rgba[p:p+4]=bytes((tone,tone+3,tone+10,255))
for i,s in enumerate(samples):
 e=assets._entry(s['source']['logical'],s['source']['package']);frame=assets._load(e).decode(s['source']['requested_index'])
 scale=2 if i<4 else 1;dx=i*200+(200-frame['width']*scale)//2;dy=250-frame['height']*scale
 raw=frame['rgba']
 for y in range(frame['height']*scale):
  for x in range(frame['width']*scale):
   src=((y//scale)*frame['width']+x//scale)*4;dst=((y+dy)*width+x+dx)*4;alpha=raw[src+3]
   for c in range(3):rgba[dst+c]=(raw[src+c]*alpha+rgba[dst+c]*(255-alpha)+127)//255
(out/'contact-sheet.png').write_bytes(png_rgba(width,height,bytes(rgba)))
print('BODY frame139 PNG identical:',(out/samples[0]['output']).read_bytes()==(out/samples[1]['output']).read_bytes())
