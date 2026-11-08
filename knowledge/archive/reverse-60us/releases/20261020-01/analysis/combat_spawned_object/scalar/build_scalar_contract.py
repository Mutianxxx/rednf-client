"""Bind selected current PVF columns and native scalar evidence."""
from pathlib import Path
import json,hashlib
ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parents[2]

def main():
    resources=json.loads((ROOT.parent/'resources.json').read_text(encoding='utf-8'))
    skill=next(r for r in resources['resources'] if r['path']=='skill/swordman/releasewave.skl')
    fields=skill['fields']
    def field(tag,scope=()):return next(f for f in fields if f['tag']==tag and tuple(f['scope'])==scope)
    tables={}
    for section in ['dungeon','pvp']:
        source=field('level info',(section,));count=source['values'][0];flat=source['values'][1:]
        assert count==1 and len(flat)%count==0
        tables[section]=dict(source=source,column_count=count,columns=[flat[i::count] for i in range(count)],
                             rows=len(flat)//count,
                             selection='Explicit caller selection; no current runtime section observation claimed')
    assert tables['dungeon']['columns'][0][0]==552 and tables['dungeon']['columns'][0][-1]==5158
    assert tables['pvp']['columns'][0][0]==172 and tables['pvp']['columns'][0][-1]==1954
    metadata={}
    for tag,offset,parser in [('maximum level','0x20','0x8A1052'),('required level','0x38','0x8A110B'),('required level range','0x40','0x8A113D')]:
        f=field(tag)
        metadata[tag.replace(' ','_')]=dict(current_pvf=f['values'][0],field=f,runtime_offset=offset,parser_site=parser)
    contract=dict(schema='60us-releasewave-scalar-v1',status='Static direct-query and ordered modifier/environment branch contract',
        source=dict(executable='DFO/DFO_fixed_v3.exe',executable_sha256='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b',
            pvf='DFO/Script.pvf',pvf_sha256=resources['archive_sha256'],skill=skill['path'],skill_sha256=skill['sha256']),
        identity=dict(skill_id=32,object_id=20018,numeric_binding='../preview-contract.json'),
        arithmetic_model='Declared reconstruction: x87 64-bit significand, nearest-even intermediate rounding; explicit float32 stores; C01544 truncates toward zero in supported int32 domain. Actual target x87 control word is unobserved; overflow/NaN/Infinity are unsupported.',
        tables=tables,runtime_metadata=metadata,
        call_chain=dict(callsite='0x73C2B3',level='max(actor.virtual+64C(32),1)',
            bridge='0x4CAA20',bridge_args=[0,'level','actor','actor.virtual+0x1D0()',0],
            branch_function='0x550150',branch_args=[0,'level','actor','same actor_context','same actor_context',0],
            base_function='0x550080',base_args=[0,'level','actor','same actor_context','same actor_context',0,0,0],
            base_ratio_skipped='0x550117 compares identical context copies; equality jumps past448150 conversion.',
            modifier='0x54FC40(actor,raw,col0,query_kind1,protected(skill+8))',
            modifier_key_boundary='protected(skill+8) is passed as runtime key; exact identity assignment is not inferred from numeric skill32 registration.'),
        runtime_table_layout=dict(parser='0x8A1E5B',script_header='0x268',script_begin='0x26C',
            runtime_materializer='0x55326C..0x55340B',runtime_header='0x23C',runtime_begin='0x240',
            outer_stride=16,inner_stride=8,value='protected int32',column=0,level_index='level-1',
            invalid_result=0,invalid_check='unsigned col/level index checks; returns0 before modifiers'),
        modifier_rows=dict(function='0x54FC40',source_slots=23,source_getter='actor.virtual+0x428(slot)',
            traversal='source slots0..22; each primary row vector then secondary row vector, preserving row order',
            row_stride='0x28',vector_offsets=['0x2A0','0x2A4'],
            fields=[dict(offset='0',name='actor_filter',type='int32',match='6 wildcard or *actor.virtual+0x5B0()'),
                    dict(offset='4',name='skill_key',type='protected uint32',match='protected(skill+8)'),
                    dict(offset='0xC',name='column',type='int32',match=0),
                    dict(offset='0x10',name='percent_mode',type='protected int32',match='0 add; nonzero percent'),
                    dict(offset='0x18',name='amount',type='protected int32'),
                    dict(offset='0x20',name='query_kind',type='int32',match=1),
                    dict(offset='0x24',name='mode_filter',type='int32',match='Primary value2 requires43ABF0; no such test in secondary traversal')],
            primary='source.virtual+0xE4().rowVector',secondary='source.virtual+0x11C().rowVector',
            secondary_gates=['source.virtual+0x12C()','source.virtual+0x118()'],
            add_formula='int32_wrap(value+amount)',
            percent_formula='old=f32(value); value=trunc_i32(x87(amount*f32(0.01)*old+old))',
            percent_constant=dict(va='0xCC10AC',hex='0ad7233c',exact_f32=0.009999999776482582),
            completeness='Executable requires modifier_snapshot_complete=true and explicit ordered sources. Each listed source requires primary and secondary row arrays; omitted slots mean null/empty. Explicit empty source list declares an unmodified baseline.',
            snapshot_boundary='Input values are a stable snapshot throughout this modeled call. Native virtual getters and mode predicates are reread; changes during the call are not modeled.'),
        environment=dict(function='0x550150',mode_gate='global[1002848]+1040 in {4,6,7,9}',mode_predicate='0x43ABF0',
            secondary_mode_gate='0x43A310: *(global+1050)!=0 and pointee+23C==10',
            additional_gates=['protected(skill+20)>1','protected(skill+40)!=0','actor_context!=-1'],
            reference_cap='protected(skill+178), required as runtime input; not assumed to equal SKL maximum20 or table rows30',
            formula=['effective=min(trunc((actor_context-required)/required_range)+1,reference_cap); no lower clamp',
                'top=query(col0,reference_cap,actor,context=-1,-1,type12)',
                'slope=trunc((raw(cap)-raw(1))/(cap-1)); if cap1 use raw(2)-raw(1)',
                'projected=f32(top-(effective-learned_level)*slope)',
                'rounded=447FF0(projected)',
                'required_at_cap=required+(cap-1)*required_range',
                'If actor_context<required_at_cap, scale by448150(required_at_cap,type0,0)/448150(actor_context,type0,0), preserving float32 stores',
                'f32(scale*selected_f5e954_or_f5e958);447FF0 again'],
            rounding=dict(function='0x447FF0',policy='add/subtract protected half then C01544 truncation',
                initialized_half=0.5,runtime_half='global protected0x10040CC; explicit branch input in executable'),
            global_multipliers=[dict(va='0xF5E954',source_initial_f32=1.0,meaning='selected when secondary mode predicate false'),
                                dict(va='0xF5E958',source_initial_f32=1.0,meaning='selected when secondary mode predicate true')],
            external_factors='448150 chooses additional mode functions; executable requires factor samples for each used context, never guesses1'),
        destination=dict(constructor_setup='0x5C77B0',conversion='received signed int -> float32',
            protected_offset='passiveobject+0x5DC',atk_field='ATK+0 damage',
            final_damage='No final victim damage formula; ATK type/element, defense and later hit processing remain separate.'),
        endpoint_scope='Dungeon table probes level1=552, level30=5158 under explicit unmodified mode3 baseline. Level30 exceeds current maximum20 and growtype caps; this is not a learnable-skill claim.',
        unknowns=['Current native runtime section selection and actor/source snapshots.',
            'Assignment of modifier runtime_skill_key (protected(skill+8)) and actor_filter value.',
            'Complete construction/mutation of runtime reference cap+178.',
            'Runtime context_factor448150, multiplier and protected-half values in active modes.',
            'Observed native x87 precision/control and exact runtime result snapshots.',
            'Changes of source getter results, gates or globals during the call; executable uses a declared stable snapshot.'],observed_execution=False)
    (ROOT/'scalar-contract.json').write_text(json.dumps(contract,ensure_ascii=False,indent=2),encoding='utf-8')
    baseline=dict(name='Explicit unmodified mode3 baseline; not a native memory observation',mode_id=3,
                  secondary_mode_gate=False,modifier_snapshot_complete=True,modifier_sources=[])
    (ROOT/'unmodified-baseline-context.json').write_text(json.dumps(baseline,indent=2),encoding='utf-8')
    retained=[]
    for prefix in ['074','075','076']:
        for p in (WORKSPACE/'analysis/rea/results').glob(prefix+'-*.json'):
            s=json.loads(p.read_text(encoding='utf-8'))['structuredContent']
            retained.append(dict(path=str(p.relative_to(WORKSPACE)),sha256=hashlib.sha256(p.read_bytes()).hexdigest(),
                evidence_id=s['evidence_id'],parameters=s['parameters'],subject=s['subject']))
    (ROOT/'rea-evidence.json').write_text(json.dumps(retained,indent=2),encoding='utf-8')
    from scalar_model import evaluate
    endpoints=[evaluate(lvl,baseline,section=section,contract=contract) for section in ('dungeon','pvp') for lvl in (1,20,30)]
    (ROOT/'endpoints.json').write_text(json.dumps(dict(context=baseline,results=endpoints),ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(dict(dungeon_rows=tables['dungeon']['rows'],pvp_rows=tables['pvp']['rows'],rea=len(retained))))

if __name__=='__main__':main()
