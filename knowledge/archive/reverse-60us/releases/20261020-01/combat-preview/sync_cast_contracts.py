"""Copy a faithful, bounded projection of the current phase evidence for portability."""
from pathlib import Path
import hashlib
import json

root=Path(__file__).resolve().parent
source=root.parent/'analysis/combat_cast_state/phase-animation-contract.json'
raw=source.read_bytes()
data=json.loads(raw)
result={k:data[k] for k in ('schema_version','source_sha256','pvf_sha256','scope',
                            'rea_evidence','bindings','limitations')}
result['derivation']=dict(source_contract='analysis/combat_cast_state/phase-animation-contract.json',
                          source_sha256=hashlib.sha256(raw).hexdigest(),
                          projection='verbatim selected fields; controller status unchanged')
(root/'cast-contracts.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Copied native phase request bindings:',len(result['bindings']))
