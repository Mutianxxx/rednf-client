"""Project complete REA observations without discarding original tool responses."""
from pathlib import Path
import json
HERE=Path(__file__).resolve().parent
records={}
bundle=HERE/'combat-evidence-bundle.json'
if bundle.exists():
    for item in json.loads(bundle.read_text(encoding='utf-8'))['records']:
        records[item['evidence_id']]=item
origins={}
for path in sorted((HERE/'results').glob('*.json')):
    result=json.loads(path.read_text(encoding='utf-8'))
    for block in result.get('content',[]):
        if block.get('type')!='text':continue
        try:item=json.loads(block['text'])
        except ValueError:continue
        if item.get('evidence_id'):
            records[item['evidence_id']]=item
            origins[item['evidence_id']]=path.name
        else:
            limits=item.get('error',{}).get('details',{}).get('reported_limits',{})
            if limits.get('evidence_id'):origins[limits['evidence_id']]=path.name
index=[]
for key,item in records.items():
    normal=item.get('normalized_result',{})
    procedure=normal.get('procedure',{}) if isinstance(normal,dict) else {}
    body=procedure.get('body') or (normal.get('body') if isinstance(normal,dict) else None)
    address=procedure.get('address') or (normal.get('entrypoint') if isinstance(normal,dict) else None)
    entry=dict(evidence_id=key,result_file=origins.get(key),operation=item['operation'],
               parameters=item['parameters'],address=address,body=body,
               provider=item['provider'],source=item['subject'],
               limitations=normal.get('limitations',[]) if isinstance(normal,dict) else [])
    pseudo=normal.get('pseudocode') if isinstance(normal,dict) else (
        normal if isinstance(normal,str) and item['operation']=='procedure_pseudo_code' else None)
    if pseudo:
        name=origins.get(key,key).replace('.json','.c')
        # Write one faithful text projection with the original CRLF normalized.
        (HERE/name).write_text(pseudo.replace('\r\n','\n'),encoding='utf-8')
        entry['pseudocode_file']=name
    index.append(entry)
(HERE/'evidence-index.json').write_text(json.dumps(index,ensure_ascii=False,indent=2),encoding='utf-8')
print('Indexed complete REA observations:',len(index))
