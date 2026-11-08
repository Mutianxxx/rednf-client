"""Build the current-client skill32 contract without guessing name-based bindings."""
from pathlib import Path
import json, hashlib
ROOT = Path(__file__).resolve().parent
WORKSPACE = ROOT.parents[1]

def main():
    resources = json.loads((ROOT/'resources.json').read_text(encoding='utf-8'))
    by_path = {r['path']:r for r in resources['resources']}
    paths = json.loads((WORKSPACE/'analysis/combat_skill_dispatch/local-dispatch-paths.json').read_text(encoding='utf-8'))
    request = next(r for r in paths['paths'] if r['native_class']=='Swordman' and r['consume_call_va']=='0x72b7c6')
    assert request['skill_id']==32 and request['state']==10
    skill = by_path['skill/swordman/releasewave.skl']
    obj = by_path['passiveobject/character/swordman/releasewave.obj']
    atk = by_path['passiveobject/character/swordman/attackinfo/releasewave.atk']
    registrations = {r['path']:r['selected_rows'] for r in resources['resources'] if r['path'].endswith('.lst')}
    for path, rows in registrations.items():
        assert len(rows)==1
        assert rows[0]['id']==(32 if path.startswith('skill/') else 20018)
    def animation(path, role, native_site):
        resource = by_path[path]
        animation = resource['animation']
        time = 0
        frames = []
        for frame in animation['frames']:
            assert len(frame['delays'])==1 and len(frame['delays'][0])==1
            delay = frame['delays'][0][0]
            frames.append(dict(index=frame['index'], start=time, end=time+delay,
                images=frame['images'], image_positions=frame['image_positions'],
                attack_boxes=frame['attack_boxes'], damage_boxes=frame['damage_boxes'],
                fields=frame['fields'], source_start=frame['start'], source_end=frame['end']))
            time += delay
        return dict(path=path, sha256=resource['sha256'], role=role,
                    native_binding_site=native_site, start_event='state10.phase0.apply',
                    frame_delay_sum=time, loop=0, frame_count=len(frames), frames=frames)
    tracks = [
        animation('character/swordman/effect/animation/releasewave1.ani','actor_attached_visual','0x73C197'),
        animation('character/swordman/effect/animation/releasewave2.ani','actor_attached_visual','0x73C1D9'),
        animation('passiveobject/character/swordman/animation/releasewave.ani','spawned_invisible_attack_entity','0x49F65A'),
    ]
    tracks[0]['attach_stack_args']=[1,'animation1',0,0,0,0,0,0,0,1]
    tracks[0]['attach_callsite']='0x73C21C'
    tracks[1]['attach_stack_args']=[-1,'animation2',0,0,0,0,0,0,0,1]
    tracks[1]['attach_callsite']='0x73C23F'
    contract = dict(
        schema='60us-swordman32-releasewave-preview-v1',
        source=dict(executable='DFO/DFO_fixed_v3.exe', executable_sha256=paths['source_sha256'],
                    pvf='DFO/Script.pvf',pvf_sha256=resources['archive_sha256']),
        status='confirmed static skill-to-object-to-resource chain; limited executable timeline',
        observed_execution=False,
        identity=dict(native_class='Swordman',job_ids=[0],skill_id=32,
                      skill_path=skill['path'],skill_sha256=skill['sha256'],
                      passiveobject_id=20018,passiveobject_hex='0x4E32',
                      obj_path=obj['path'],obj_sha256=obj['sha256'],
                      binding_basis='native literal ID and successful request path plus current numeric registrations'),
        registrations=registrations,
        request=dict(consume_callsite=request['consume_call_va'],consume_failure_branch=request['failure_branch_va'],
                     consume_failure_target=request['failure_target_va'],request_callsite=request['request_call_va'],
                     request_state=10, vector=[0,0,32,0,'return(0x54FF60@0x72B849)',1,4,4],
                     phase_resources_contract='../combat_cast_state/phase-animation-contract.json',
                     caution='request does not itself prove runtime application or transport'),
        activation=dict(handler='0x7307B0',post_shared_branch='0x73B42C',
            guards=[dict(site='0x73B42C',predicate='entity+0x2428 == 0'),
                    dict(site='0x73C147',predicate='protected(entity+0x242C) == 32'),
                    dict(site='0x73C15B',predicate='protected(entity+0x2420) == 0')],
            visual_calls_before_spawn_gate=True,
            spawn_gate=dict(callsite='0x73C245',function='0x49C090',
                predicate='entity.virtual+0x160() == global[0x104F1D4] and global != 0'),
            warning='Skill effects are phase0. Do not move this event to phase1 or bind only by throw-motion name.'),
        spawn_request=dict(callsite='0x73C2C0',virtual_slot='0x2B8',function='0x4EA4D0',callee_ret_bytes=52,
            stack_arguments=[20018,'return(0x4CAA20)',0,0,0,0,0,4,0,0,0,0,0],
            arguments=['object_id','dynamic_scalar','optional_structure','arg4','dx','dy','dz','direction','arg9','arg10','arg11','arg12','arg13'],
            dynamic_scalar=dict(callsite='0x73C2B3',function='0x4CAA20',this='actor.virtual+0x67C(32)',
                args=[0,'max(actor.virtual+0x64C(32),1)','actor','actor.virtual+0x1D0()',0],
                forwarded_to='0x550150',scalar_formula='pending; do not replace with raw SKL level_info[0]',
                destination='0x5C77B0 converts received signed integer to float32 and stores protected(entity+0x5DC)'),
            direction=dict(input=4,resolve_site='0x4EA507',resolve='actor.virtual+0xC0()'),
            position=dict(native_sites=['0x4EA520','0x4EA52C','0x4EA538','0x4EA548'],
                formula=['actorX + (direction==1 ? dx : -dx)','actorY + dy','actorZ + dz'],
                selected_skill_offsets=[0,0,0],motion='No displacement is specified by this request. No projectile velocity is invented.'),
            message=dict(writer='0x4E9EA0',opcode=21,opcode_hex='0x15',write_site='0x4E9F24',
                receive_dispatch_table='0x8C5E64',case_address='0x8C4248',factory_callsite='0x8C4395',
                note='Static writer and receiver are connected by opcode/field order, not observed packet execution.')),
        factory=dict(function='0x5E8500',selected_id=20018,
            decision_blocks=['0x5E851C','0x5EA005','0x5EA029','0x5EA482','0x5EA79A'],
            table='0x5F1F54',index=3,table_entry='0x5EA85E',allocation_bytes=2160,
            constructor='0x5CE740',base_constructor='0x490720',registration_consumer='0x4A0DA0',
            registration_map='0x10BE3E8',resource_loader='0x49F4D0',vtable='0xD057D4',
            native_list_selection=dict(site='0x44ADDB',base='PassiveObject/',list='PassiveObject.usa.lst',
                initializer='0x882A50',numeric_path_parser='0x831AD0'),
            obj_manager=dict(global_address='0x10030E4',constructor_site='0x44B159',constructor='0xA614D0',type=2,
                vtable='0xE4C4F4',load_slot8='0xA618E0',type_table='0xA61FEC',type_case='0xA619C2',
                obj_parser='0x884720',parser_callsite='0xA619F8')),
        object_fields=obj['fields'],
        action_binding=dict(declared_act_paths=[],source='No ACT tag in the selected current OBJ. Initial motion is direct ANI.',
            basic_motion=dict(parser_site='0x884A70',template_offset='0x34',loader_site='0x49F65A',
                construct='0x472A60 -> 0xA29AD0',set_basic_slot='0x6C = 0x407BC0',basic_pointer='entity+0x118',
                set_current_if_empty='0x49D070 -> 0x49B250',current_pointer='entity+0x104',
                cache_refresh='0x49B2BF -> 0xA27F60 when ANI+0x138 is nonzero'),
            attack_info=dict(path=atk['path'],sha256=atk['sha256'],parser_site='0x884C99',template_offset='0x70',
                loader_site='0x49FAAC',manager='0x10030F8',resource_lookup='0xB7D230',
                copy='0x4A27E0 -> entity+0x5DC',fields=atk['fields']),
            directory_resolution=dict(parser_site='0x88477A',helper='0x82F710',format='%s%s',template_base_offset='0xA4',
                behavior='Concatenate base+OBJ path, retain directory through last slash/backslash; append relative ANI/ATK path.',
                normalization='No dot-segment normalization is asserted at this helper.')),
        tracks=tracks,
        collision=dict(source='../combat_native_collision/geometry-contract.json',
            native_chain=['0xA28410 parses frame ATTACK BOX -> keyframe+0x38',
                '0xA27F60 refreshes current attack container ANI+0xE0',
                '0x4AEF80 primary/child ANI -> 0x4E9B10 transforms -> 0xA244E0 intersects'],
            selected_attack_box=[-84,-50,0,168,100,234],
            active_resource_frames=[0,1,2,3,4],
            preview_contact='Only geometric overlap may be emitted by this contract.',
            accepted_hit_contract='../combat_native_collision/hit-contract.json',
            damage_and_reaction='ATK requests down/push400/lift400, but final gates, repeat-hit state and damage formula are outside this selected contract.'),
        lifetime=dict(tick='0x5CE7A0',slot='0x188',current_animation='entity+0x104',
            ani_advance='0xA27DC0',ended_byte='ANI+0x13A',loop_byte='ANI+0x130',
            ended_semantics='Nonlooping ANI sets ended byte after the final-frame deadline and retains the final frame; independently confirmed by REA060.',
            native_remove_predicate='ANI.byte+0x13A != 0 and entity.byte+0x1E8 == 0',
            remove_callsite='0x5CE7C8',remove_slot='0x164 = 0x49E840',remove_base_call='0x499120',
            remove_opcode=23,remove_opcode_hex='0x17',
            preview_end_policy='Use the summed source DELAY values on a normalized local clock; origin t=0 means phase0 apply. Object can be removed after its ANI ended flag. Visual final frame is retained; both selected visual ANI final frames have empty image paths. Actual native clock/tick scheduling is not observed.'),
        supported_preview=['Select only current registered Swordman skill32.',
            'On applied phase0: play the two exact actor-attached effect tracks in parallel.',
            'If native spawn predicates are considered passed, instantiate object20018 at actor XYZ with resolved facing.',
            'Object ANI contains no image and five equal attack-box frames; preserve invisibility.',
            'Display current 3D geometric contact separately from native accepted hit, HP and monster reaction.'],
        unknowns=['Complete dynamic-scalar formula in 0x550150 and all scaling inputs.',
            'Native transport scheduling, exact phase/apply tick alignment and observed client visuals.',
            'Meaning of actor effect attach argument +1/-1 beyond the raw parameter values.',
            'Native accepted-hit target history/reset and all ATK-to-motion units.',
            'Full monster motion integration, death, scene destruction and UI. These are separate analyses.'])
    (ROOT/'preview-contract.json').write_text(json.dumps(contract,ensure_ascii=False,indent=2),encoding='utf-8')
    evidence=[]
    for prefix in ['015','051','052','057','058','059','060']:
        for p in (WORKSPACE/'analysis/rea/results').glob(prefix+'-*.json'):
            data=json.loads(p.read_text(encoding='utf-8'))
            s=data.get('structuredContent',{})
            if s.get('evidence_id'):
                evidence.append(dict(path=str(p.relative_to(WORKSPACE)),sha256=hashlib.sha256(p.read_bytes()).hexdigest(),
                    evidence_id=s['evidence_id'],parameters=s['parameters'],subject=s['subject'],observed_execution=False))
    captures=[]
    for p in sorted(ROOT.glob('????????-????????.json')):
        captures.append(dict(path=p.name,**json.loads(p.read_text(encoding='utf-8'))))
    index=dict(source=contract['source'],native_captures=captures,rea_evidence=evidence,
               selected_request=request,failed_provider_query='056-passiveobject-factory.json failed to find procedure; no decompiler claim used',
               observed_execution=False)
    (ROOT/'evidence-index.json').write_text(json.dumps(index,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(dict(tracks=len(tracks),native_captures=len(captures),rea_evidence=len(evidence))))

if __name__=='__main__':main()
