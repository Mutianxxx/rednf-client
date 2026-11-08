"""Read-only PE captures for bounded common numeric stages."""
from pathlib import Path
import sys, json, hashlib, struct
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent/'combat_spawned_object'))
from static_evidence import chunk,MD,SOURCE,SHA256

RANGES=[
 (0x8B7AB0,0x13B,'critical'),(0x8B7C90,0x194,'defense'),
 (0x8B87EB,0x356,'numeric_consumers'),
 (0x4EB780,0x1280,'numeric_packing'),
 (0x8377FD,0x370,'atk_critical_and_category_parse'),
 (0xCC10AC,4,'percent_constant'),(0xCC1F58,4,'one_constant'),
 (0xCCB578,4,'critical_base_constant'),(0xCCB9D8,4,'critical_scale_constant'),
 (0xE9D7A4,4,'low_defense_constant'),(0xD5A848,4,'low_level_defense_constant'),
 (0xDF5190,4,'postcritical_constant'),
]

def main():
 records=[]
 for va,size,label in RANGES:
  raw,offset=chunk(va,size);name=f'{va:08X}-{label}'
  (ROOT/(name+'.bin')).write_bytes(raw)
  if 'constant' not in label:
   (ROOT/(name+'.asm')).write_text('\n'.join(f'{x.address:08x} {x.bytes.hex():24} {x.mnemonic:10} {x.op_str}' for x in MD.disasm(raw,va)),encoding='utf-8')
  rec=dict(start_va=hex(va),length=size,file_offset=offset,sha256=hashlib.sha256(raw).hexdigest(),capture=name+'.bin')
  if 'constant' in label:rec.update(f32=struct.unpack('<f',raw)[0],hex=raw.hex())
  records.append(rec)
 rea=[]
 for stem in ('095-damage-defense','096-damage-scale'):
  source=ROOT.parent/'rea/results'/ (stem+'.json')
  d=json.loads(source.read_text(encoding='utf-8'))['structuredContent']
  n=d['normalized_result'];(ROOT/(stem+'.c')).write_text(n['pseudocode'],encoding='utf-8')
  rea.append(dict(source=str(source),sha256=hashlib.sha256(source.read_bytes()).hexdigest(),evidence_id=d['evidence_id'],procedure=n['procedure']))
 result=dict(schema='60us-bounded-numeric-evidence-v1',source=str(SOURCE),source_sha256=SHA256,observed_execution=False,captures=records,rea=rea)
 (ROOT/'evidence.json').write_text(json.dumps(result,indent=2,ensure_ascii=False),encoding='utf-8')
 print(json.dumps(dict(captures=len(records),rea=len(rea))))

if __name__=='__main__':main()
