"""Targeted offline decompilation; never starts the game executable."""
from pathlib import Path
import json
import logging
import sys
import time
root=Path(__file__).resolve().parent
sys.path.insert(0,str(root/'angr_deps'))
import angr

logging.getLogger('angr').setLevel(logging.ERROR)
logging.getLogger('cle').setLevel(logging.ERROR)
targets={
    0xa54e70:'pvf_decrypt_verify',
    0xa54f80:'path_hash',
    0xa55fa0:'pvf_read_tree_entry',
    0xa570d0:'pvf_open_archive',
    0xa55170:'pvf_read_entry_stream',
    0xa55320:'pvf_read_entry_buffer',
    0x82fde0:'script_init',
    0x82f790:'script_open',
    0x82f7d0:'script_read_int',
    0x82f860:'script_read_float',
    0x8b2950:'script_reader_open',
    0x8b2970:'script_reader_next_type',
    0x8a0da0:'skill_parse_properties',
    0x8a0ae0:'skill_list_init',
    0x8a2940:'skill_load_class',
    0xb8ba50:'text_reader_open',
    0xb8b7a0:'text_reader_next_token',
}
if len(sys.argv)>1:
    targets={int(a,0):f'func_{int(a,0):08x}' for a in sys.argv[1:]}
dest=root/'decompiled'
dest.mkdir(exist_ok=True)
print('loading',flush=True)
project=angr.Project(str(root.parent/'DFO'/'DFO_fixed_v3.exe'),auto_load_libs=False,load_debug_info=False)
regions=[]
for a in targets:
    start=a & ~0xfff
    region=(start,start+(0x7000 if a==0x8a0da0 else 0x3000))
    regions.append(region)
print('CFG',regions,flush=True)
beg=time.monotonic()
cfg=project.analyses.CFGFast(regions=regions, function_starts=list(targets),
    start_at_entry=False, symbols=False, force_complete_scan=False,
    normalize=True, resolve_indirect_jumps=False, data_references=True)
print('CFG done',len(cfg.kb.functions),round(time.monotonic()-beg,2),flush=True)
items=[]
for addr,name in targets.items():
    func=cfg.kb.functions.get(addr)
    if func is None:
        print('missing',hex(addr),flush=True)
        continue
    func.name=name
for addr,name in targets.items():
    func=cfg.kb.functions.get(addr)
    if func is None:
        continue
    print('decompile',hex(addr),name,'blocks',len(func.block_addrs_set),flush=True)
    try:
        d=project.analyses.Decompiler(func,cfg=cfg.model)
        text=d.codegen.text if d.codegen else '/* No pseudocode generated */'
        (dest/f'{addr:08x}_{name}.c').write_text(text,encoding='utf-8')
        item=dict(address=hex(addr),name=name,blocks=len(func.block_addrs_set),
                  size=func.size, output=f'{addr:08x}_{name}.c')
        print('wrote',len(text),flush=True)
    except Exception as exc:
        item=dict(address=hex(addr),name=name,error=repr(exc))
        print('failed',repr(exc),flush=True)
    items.append(item)
(dest/'index.json').write_text(json.dumps(items,indent=2),encoding='utf-8')
print('done',flush=True)
