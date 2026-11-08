"""Read source bytes and retained evidence; writes exclusively to consumer/."""
from pathlib import Path
import sys,json,hashlib
ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parents[3]
sys.path.insert(0,str(ROOT.parents[1]))
from static_evidence import chunk,MD,SHA256,SOURCE

RANGES=[('spawn_owner_and_register',0x8C438C,0x43),
        ('register_full',0x50DD70,0x2EB),
        ('source_atk_install',0x49F010,0x75),
        ('owner_stat_snapshot',0x49DD10,0x1A3),
        ('snapshot_operand_getters',0x4390C0,0x87),
        ('releasewave_vtable',0xD057D4,0x384),
        ('numeric_full',0x8B8650,0x84D),
        ('alternate_base',0x8B8560,0x46),
        ('action_atk_validity',0x467480,0x3A),
        ('atk_ctor_defaults',0x437D30,0x271),
        ('numeric_defaults',0x455A50,0x1B9),
        ('passive_type_and_snapshot_defaults',0x49EE70,0x6F),
        ('passive_owner_getters',0x439080,0x38),
        ('swordman_false_slot',0x8E49B0,3),
        ('type_mask_getter',0x407B60,7),
        ('swordman_owner_1bc_slot',0xD80F94+0x1BC,4),
        ('victim_damage_to_hp',0x4B2E86,0x4CE),
        ('monster_numeric_wrapper',0x4F5C20,0x96)]

def main():
    rows=[]
    for name,va,length in RANGES:
        data,off=chunk(va,length);stem=f'{va:08X}-{name}'
        (ROOT/(stem+'.bin')).write_bytes(data)
        (ROOT/(stem+'.asm')).write_text('\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data,va)),encoding='utf-8')
        rows.append(dict(name=name,va=va,length=length,file_offset=off,sha256=hashlib.sha256(data).hexdigest(),binary=stem+'.bin',assembly=stem+'.asm'))
    reused=[]
    manifest=json.loads((WORKSPACE/'analysis/combat_attackinfo/evidence.json').read_text(encoding='utf-8'))
    selected={'atk_reset_core','atk_copy','atk_install_copy','current_atk_get','damage_pack_full',
              'damage_base_dispatch','damage_weapon_percent','damage_pack_atk_core','damage_pack_stats',
              'atk_damage_and_bonus_parse','atk_weapon_apply_parse'}
    reused.extend(dict(base='analysis/combat_attackinfo',**r) for r in manifest['excerpts'] if r['name'] in selected)
    for prefix in ['005C77B0','005CE740','00490720','0049FAAC']:
        for path in ROOT.parents[1].glob(prefix+'-*.json'):
            d=json.loads(path.read_text(encoding='utf-8'))
            reused.append(dict(base='analysis/combat_spawned_object',name=path.stem,va=hex(d['start_va']),size=d['length'],
                sha256=d['chunk_sha256'],file_offset=d['file_offset'],binary=path.with_suffix('.bin').name,
                assembly=path.with_suffix('.asm').name))
    retained=[]
    for prefix in ['057','058','059','070','094']:
        for p in (WORKSPACE/'analysis/rea/results').glob(prefix+'-*.json'):
            d=json.loads(p.read_text(encoding='utf-8'))['structuredContent']
            retained.append(dict(path=str(p.relative_to(WORKSPACE)),sha256=hashlib.sha256(p.read_bytes()).hexdigest(),
                evidence_id=d.get('evidence_id'),parameters=d.get('parameters'),subject=d.get('subject')))
    external=[]
    for p in ['analysis/combat_native_collision/hit-contract.json','analysis/combat_hit_lifecycle/history-contract.json',
              'analysis/combat_hit_lifecycle/evidence-index.json','analysis/combat_hit_lifecycle/passive_reset_and_install.bin']:
        data=(WORKSPACE/p).read_bytes();external.append(dict(path=p,sha256=hashlib.sha256(data).hexdigest()))
    (ROOT/'evidence.json').write_text(json.dumps(dict(source=str(SOURCE),source_sha256=SHA256,excerpts=rows,reused_excerpts=reused,
        rea_evidence=retained,external_references=external,observed_execution=False),indent=2),encoding='utf-8')
    print(json.dumps(dict(captures=len(rows),reused=len(reused),rea=len(retained))))

if __name__=='__main__':main()
