"""Source-bound scalar-only captures; writes exclusively inside this directory."""
from pathlib import Path
import sys,json,hashlib
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent))
from static_evidence import chunk,MD,SOURCE,SHA256

RANGES=[(0x54FC40,0x315),(0x550080,0xC9),(0x550150,0x215),
        (0x43ABF0,0x46),(0x43A310,0x1E),(0x447FF0,0xA9),
        (0x448150,0xA0),(0x553BA0,0x28),(0x551B8F,0x59),
        (0x551CA9,0xDE),(0x8A1052,0x32),(0x8A110B,0x64),
        (0xC01544,0x76),(0xF5E954,8),(0xCC10AC,4),
        (0x73C254,0x72),(0x4CAA20,0x21)]

def main():
    rows=[]
    for va,length in RANGES:
        data,off=chunk(va,length);stem=f'{va:08X}-{va+length:08X}'
        (ROOT/(stem+'.bin')).write_bytes(data)
        (ROOT/(stem+'.asm')).write_text('\n'.join(
            f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data,va)),encoding='utf-8')
        rows.append(dict(start_va=va,length=length,file_offset=off,sha256=hashlib.sha256(data).hexdigest(),
                         binary=stem+'.bin',assembly=stem+'.asm'))
    index=json.loads((ROOT.parents[1]/'combat_attackinfo/evidence.json').read_text(encoding='utf-8'))
    wanted={'level_query_bridge','level_value','level_query','skill_load_parse','skill_levelinfo_materialize',
            'skl_levelinfo_parse','skl_parser_entry','swordman_context_stat'}
    reused=[dict(base='analysis/combat_attackinfo',**r) for r in index['excerpts'] if r['name'] in wanted]
    result=dict(source=str(SOURCE),source_sha256=SHA256,excerpts=rows,reused_excerpts=reused,observed_execution=False)
    (ROOT/'native-evidence.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print(json.dumps(dict(captures=len(rows),reused=len(reused))))

if __name__=='__main__':main()
