import sys,json,hashlib,collections,time
from pathlib import Path
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets
assets=Assets(r'D:\dnf\60US\DFO\ImagePacks2');out=Path(r'D:\dnf\60US\analysis\npk60')
selected=[]
for logical,entries in assets.entries.items():
 if (logical.endswith('/sm_body0000.img') or logical.startswith('sprite/monster/goblin/') or logical.startswith('sprite/character/swordman/effect/hardattack')):
  selected.extend(entries)
errors=[];count=0;formats=collections.Counter();elapsed=time.monotonic();examples=[]
for entry in selected:
 img=assets._load(entry)
 for index in range(len(img.records)):
  try:
   frame=img.decode(index);count+=1;formats[frame['record']['color_format']]+=1
  except Exception as e:errors.append([entry.metadata(),index,str(e)])
 if len(examples)<30:examples.append({'entry':entry.metadata(),'frames':len(img.records),'sha256':img.sha256})
summary={'selected_imgs':len(selected),'decoded_frames':count,'resolved_pixel_formats':dict(formats),'errors':errors,'seconds':time.monotonic()-elapsed,'selection_rule':'all frames of sm_body0000.img, monster/goblin/*, character/swordman/effect/hardattack*','examples':examples}
(out/'pixel-validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps({k:v for k,v in summary.items() if k!='examples'},indent=2))
