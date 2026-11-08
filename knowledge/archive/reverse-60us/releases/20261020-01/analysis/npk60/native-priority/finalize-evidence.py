from pathlib import Path
import json,sys,hashlib,struct
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
out=Path(r'D:\dnf\60US\analysis\npk60\native-priority');source=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe');raw=source.read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
strings=[]
for name,va,enc,length in [('ImagePacks2/',0xcb3c20,'utf-16-le',24),('*.npk',0xe67cb0,'utf-16-le',12),('NeoplePack_Bill',0xe67b98,'ascii',16),('NPK-name-xor-seed',0xe67978,'utf-16-le',512),('IMG-v1-magic',0xe43a98,'ascii',20),('IMG-v2-magic',0xe6aa80,'ascii',16)]:
 off=pe.get_offset_from_rva(va-base);b=raw[off:off+length];strings.append({'name':name,'va':hex(va),'file_offset':off,'raw_hex':b.hex(),'decoded':b.decode(enc,errors='strict').rstrip('\0')})
searched={}
for label in ('localpackage.lst','NpkIndex.etc'):
 searched[label]={enc:raw.lower().find(label.encode(enc).lower()) for enc in ('ascii','utf-16-le')}
(out/'strings.json').write_text(json.dumps({'source_sha256':hashlib.sha256(raw).hexdigest(),'strings':strings,'literal_search_file_offsets':searched},ensure_ascii=False,indent=2),encoding='utf8')
observed=json.loads((out/'filesystem-enumeration.json').read_text(encoding='utf8'));ranks={r['name'].casefold():r['ordinal'] for r in observed['enumeration']}
conflicts=json.loads((out.parent/'conflict-validation.json').read_text(encoding='utf8'))['conflicts'];digest=json.loads((out/'directory-digest-validation.json').read_text(encoding='utf8'));valid={r['package'].casefold():r['valid'] for r in digest['all_results']}
choices={}
for logical,row in conflicts.items():
 candidates=sorted([{**entry,'observed_ordinal':ranks[entry['package'].casefold()],'native_directory_digest_valid':valid[entry['package'].casefold()]} for entry in row['candidates']],key=lambda v:v['observed_ordinal'])
 choices[logical]={'expected_packed_source_in_observed_directory':candidates[0]['package'],'candidates_in_observed_order':candidates}
(out/'observed-conflict-choices.json').write_text(json.dumps({'classification':'static native rule + read-only current filesystem enumeration; not a game runtime observation','observed_at':observed['observed_at'],'source_exe_sha256':hashlib.sha256(raw).hexdigest(),'rule':'accept valid packages in FindFirst/Next enumeration order, append to tail, search from head, stop at first match','choices':choices},ensure_ascii=False,indent=2),encoding='utf8')
curated=['0040C850-0040CB70','00B0D3A0-00B0D3E3','00ACA380-00ACA39B','00ACA0C0-00ACA36B','00AC8E00-00AC8F14','00AC9E30-00ACA04C','00ACB540-00ACB5C4','00AC95B0-00AC9689','00AC9220-00AC92F0','00C04322-00C043FF','00C043FF-00C044D0','00AF20E0-00AF2231','00AC9C10-00AC9CF3']
index={'source':str(source),'sha256':hashlib.sha256(raw).hexdigest(),'evidence':[json.loads((out/(name+'.json')).read_text())|{'bin':name+'.bin','asm':name+'.asm'} for name in curated]}
(out/'evidence-index.json').write_text(json.dumps(index,indent=2),encoding='utf8')
print('curated evidence',len(curated),'conflict choices',len(choices),'searches',searched)
