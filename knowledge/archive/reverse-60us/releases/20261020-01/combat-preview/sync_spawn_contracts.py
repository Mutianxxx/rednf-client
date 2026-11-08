"""Copy the reviewed source-bound spawned-object contract into the preview."""
from pathlib import Path
import json
ROOT=Path(__file__).resolve().parent
data=json.loads((ROOT.parent/'analysis/combat_spawned_object/preview-contract.json').read_text(encoding='utf-8'))
assert data['identity']['skill_id']==32 and data['identity']['passiveobject_id']==20018
assert len(data['tracks'])==3
(ROOT/'spawn-contract.json').write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Copied source-bound skill32 spawned-object contract')
