from pathlib import Path
import sys,json
sys.path.insert(0,r'D:\dnf\60US\combat-preview')
from resources import Assets
assets=Assets(r'D:\dnf\60US\DFO\ImagePacks2')
examples=[('character/swordman/equipment/avatar/skin/sm_body0000.img',139,'sprite_character_swordman_equipment_avatar_skin.npk'),('character/swordman/equipment/avatar/skin/sm_body0000.img',139,'sprite_character_swordman_equipment_avatar_skin1.NPK'),('monster/goblin/body0.img',0,None),('monster/goblin/body0.img',15,None),('character/swordman/effect/hardattackblade1.img',0,None)]
manifest=[]
out=Path(r'D:\dnf\60US\analysis\npk60')
for i,(logical,index,package) in enumerate(examples):
 try:
  frame=assets.frame(logical,index,package)
  png=frame.pop('png');name=f'sample-{i}-{Path(logical).stem}-{index}.png';(out/name).write_bytes(png)
  manifest.append({'output':name,**frame})
  print(name,frame['width'],frame['height'],frame['x'],frame['y'],frame['full_width'],frame['full_height'])
 except Exception as e:print('ERROR',logical,index,package,repr(e))
(out/'samples.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
