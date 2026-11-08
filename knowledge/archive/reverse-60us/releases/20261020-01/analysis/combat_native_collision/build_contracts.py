"""Emit source-bound contracts. Does not execute or modify the target."""
import hashlib
import json
from audit60 import RAW, BASE, OUT, off, capture
from scene_contract import SCENE_BLOCKS, contract as scene_contract
from scene_specialized_contract import BLOCKS as SPECIALIZED_BLOCKS, contract as specialized_contract

SOURCE = {
    'path': 'DFO/DFO_fixed_v3.exe',
    'sha256': hashlib.sha256(RAW).hexdigest(),
    'image_base': hex(BASE),
    'evidence_kind': 'local static PE bytes and Capstone x86 disassembly',
    'runtime_observed': False,
    'rea_provider_evidence': False,
}

def emit(name, value):
    (OUT / name).write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf8')

# These are clean instruction blocks or bounded bodies, not the old exploratory surveys.
blocks = [
    (0x4EDF70, 0x4EE174, 'qualification-body', 'bounded function body'),
    (0x4EABF0, 0x4EAFFA, 'hit-message-send-body', 'bounded function body'),
    (0x8C39B0, 0x8C3CF7, 'message13-receiver-block', 'case block; enclosing receiver is 8C1A30'),
    (0x4F8A30, 0x4F9ADA, 'monster-received-hit-body', 'enclosing function region; Ghidra body omits a small alignment gap'),
    (0x4B2E78, 0x4B3220, 'hit-calc-hp-state-block', 'instruction block within 4B28D0'),
    (0x4AF140, 0x4AF31D, 'absolute-hp-wrapper-block', 'entry and relevant call block; end not asserted'),
    (0x4F58C0, 0x4F5BBB, 'monster-absolute-hp-body', 'bounded function body'),
    (0x4B4E00, 0x4B535B, 'active-absolute-hp-body', 'bounded function body'),
    (0x4AD960, 0x4AD9EC, 'death-flag-body', 'bounded function body'),
    (0x4AC440, 0x4AC4E3, 'death-state-choice-block', 'bounded function body'),
    (0x4AF540, 0x4AF6C0, 'reaction-state-choice-block', 'function entry and branch block; end not asserted'),
    (0x4BAD60, 0x4BC796, 'active-state-apply-body', 'enclosing function region including switch cases; Ghidra noncontiguous membership differs'),
    (0x4BC7D0, 0x4BDACE, 'active-state-tick-body', 'enclosing function region including switch cases; Ghidra noncontiguous membership differs'),
    (0x4BC798, 0x4BC7C0, 'active-state-apply-table', 'data: 10 little-endian function addresses'),
    (0x4BDAD0, 0x4BDAF4, 'active-state-tick-table', 'data: 9 little-endian function addresses'),
    (0x8894B6, 0x8895D3, 'mob-motion-parser-cases', 'clean cases inside 887E60'),
    (0x8896D6, 0x88981C, 'mob-action-parser-cases', 'clean cases inside 887E60'),
    (0x8898F0, 0x889919, 'mob-lastaction-parser-case', 'case block inside 887E60'),
    (0x500BFA, 0x500F1C, 'mob-runtime-motion-load', 'instruction block inside 500530'),
    (0x50136F, 0x5014B5, 'mob-runtime-wait-move-action-load', 'instruction block inside 500530'),
    (0x5015D7, 0x5017FC, 'mob-runtime-reaction-action-load', 'instruction block inside 500530'),
    (0x501C2D, 0x501CD3, 'mob-runtime-lastaction-load', 'instruction block inside 500530'),
    (0x7447B0, 0x7447B7, 'sit-motion-getter', 'bounded function body'),
    (0x7447D0, 0x7447D7, 'waiting-action-getter', 'bounded function body'),
    (0x7447F0, 0x7447F7, 'sit-action-getter', 'bounded function body'),
    (0x744800, 0x74481C, 'damage-action-getter', 'bounded function body'),
    (0x744820, 0x744827, 'down-action-getter', 'bounded function body'),
    (0x744830, 0x744837, 'overturn-action-getter', 'bounded function body'),
    (0x4AC7C0, 0x4AC84C, 'reaction-motion-getters', 'four bounded adjacent functions'),
    (0xA2CFB0, 0xA2CFB4, 'act-current-ani-getter', 'bounded function body'),
    (0x830590, 0x830614, 'path-directory-helper', 'bounded function body'),
    (0x778880, 0x778918, 'path-append-helper', 'bounded function body'),
    (0xA3F0E0, 0xA3F156, 'act-parser-base-directory-block', 'entry block inside A3F0E0'),
    (0xA3F23B, 0xA3F2EE, 'act-base-ani-parser-case', 'case block inside A3F0E0'),
    (0xA321B0, 0xA32273, 'act-base-ani-consumer-block', 'entry block inside A321B0'),
    (0x4936D0, 0x4937F1, 'ani-full-path-constructor', 'bounded function body'),
    (0x4FE97E, 0x4FE991, 'monster-state5-zero-payload-dispatch', 'case fragment inside 4FE290'),
    (0x4FC892, 0x4FC8B4, 'monster-tick-state-dispatch', 'switch dispatch inside 4FB720'),
    (0x4FCE68, 0x4FCE92, 'monster-tick-state-tables', 'data: 7 function addresses followed by 14 remapping bytes'),
    (0x4FCB2A, 0x4FCD6C, 'monster-state5-tick-case', 'case fragment inside 4FB720'),
    (0x4FA1D0, 0x4FA1F5, 'monster-slot654-protected-entry', 'entry fragment; jumps to protected thunk, native continuation not resolved'),
    (0x13BAA5F, 0x13BAA69, 'monster-slot654-protected-thunk', 'push token and jump to shared protection interpreter; not decoded'),
    (0x4FA222, 0x4FA2E2, 'monster-slot654-visible-down-selection', 'native fragment after protected gap; entry reachability not established'),
    (0x499120, 0x4991AB, 'object-removal-request-body', 'bounded function body'),
    (0x8C4D73, 0x8C4E69, 'object-removal-message17-case', 'case block inside 8C1A30'),
    (0x4EFC80, 0x4EFCBB, 'active-object-slot60-body', 'bounded function body'),
    (0x498EC0, 0x498FC2, 'object-field-initializer', 'bounded function body; distinct from preceding color helper 498E60'),
    (0x498E60, 0x498EB9, 'object-color-mask-helper', 'bounded function body'),
    (0xB099B0, 0xB099DA, 'clamped-linear-interpolation', 'bounded function body'),
    (0xA297B0, 0xA29940, 'ani-frame-scale-helper', 'bounded function body and alignment bytes'),
    (0x8E49B0, 0x8E49B3, 'false-return-method', 'bounded function body'),
]
blocks.extend(SCENE_BLOCKS)
blocks.extend(SPECIALIZED_BLOCKS)
manifest = {'source': SOURCE, 'end_convention': 'exclusive', 'authoritative_excerpts': []}
for start, end, label, scope in blocks:
    capture(start, end - start, 'verified-' + label)
    stem = f'{start:08x}-verified-{label}'
    manifest['authoritative_excerpts'].append({
        'va_start': hex(start), 'va_end_exclusive': hex(end), 'rva': hex(start - BASE),
        'file_offset': off(start), 'length': end - start,
        'sha256': hashlib.sha256(RAW[off(start):off(start)+(end-start)]).hexdigest(),
        'bin': stem + '.bin', 'asm': stem + '.asm', 'scope': scope,
    })
manifest['old_captures'] = 'All other captures are exploratory. Their filename, apparent prologue, and capture length do not establish symbol identity or function extent.'
emit('capture-manifest.json', manifest)

hit = {
    'source': SOURCE,
    'observed_static': {
        'collision_is_not_damage': True,
        'monster_vtable': '0xD8385C',
        'qualification': {'function': '0x4EDF70', 'target_history': 'this+0x418', 'throttle_map': 'this+0x470', 'seen_query': '0x4ECE50', 'register_target': '0x4EDE20', 'reset_target_history': '0x438990', 'lifecycle_contract': '../combat_hit_lifecycle/history-contract.json', 'lifecycle_readme': '../combat_hit_lifecycle/README.md', 'lifecycle_scope': 'Local ATK installation, reset behavior and ownership are now closed by the separate current-binary audit; all-skill active trigger coverage remains unknown.'},
        'message_0x13': {'opcode_hex':'0x13', 'opcode_decimal':19, 'send': '0x4EABF0', 'receiver': '0x8C1A30', 'dispatch_table': '0x8C5E64', 'table_index': 19, 'case': '0x8C39B0', 'target_slot260_call': '0x8C3CD1', 'callback_order': ['attacker.slot250', 'target.slot25C', 'attacker.slot254', 'target.slot260', 'attacker.slot258', 'target.slot264']},
        'monster_hit': {'slot': '0x260', 'function': '0x4F8A30', 'base_call_site': '0x4F9AC2', 'base': '0x4B28D0'},
        'calculation': {'slot': '0x2F8', 'slot_call_site': '0x4B2EC1', 'monster_wrapper': '0x4F5C20', 'common': '0x4EB780', 'numeric_calculator': '0x8B8650'},
        'hp': {'subtract_site': '0x4B312F', 'update_call': '0x4B3135', 'argument': 'new absolute HP, not damage or delta', 'wrapper_slot': '0x3E8', 'wrapper': '0x4AF140', 'setter_slot': '0x3EC', 'setter_call_site': '0x4AF300', 'monster_setter': '0x4F58C0', 'base_setter_call': '0x4F59DD', 'base_setter': '0x4B4E00', 'field': 'protected(this+0x1230)', 'clamp': '0..maxHP', 'current_getter_slot': '0x234', 'current_getter': '0x744B90', 'maximum_getter_slot': '0x238', 'maximum_getter': '0x744BA0'},
        'death': {'hp_zero_call_site': '0x4B4ECB', 'flag_setter_slot': '0x3D8', 'flag_setter': '0x4AD960', 'flag_getter_slot': '0x3DC', 'flag_getter': '0x744B70', 'field': 'protected(this+0x1554)'},
        'reaction_request': {'selector_call': '0x4B31EF', 'selector_slot': '0x3E0', 'selector': '0x4AF540', 'candidate_states': [3,4,5,-1], 'death_state_choice_slot': '0x3E4', 'death_state_choice': '0x4AC440', 'pending_request': '0x4ED1D0', 'pending_field': 'this+0x4A0', 'request_does_not_apply_or_serialize': True},
        'actual_state': {'monster_slot': '0x22C', 'monster_method': '0x4FE290', 'base_method': '0x4BAD60', 'base_call_site': '0x4FEBA0', 'field': 'protected(this+0x155C)', 'write_range': ['0x4BC685','0x4BC6C5']},
    },
    'inferences': [
        'History and throttle structures serve repeat-hit qualification; the source-bound local ATK installation/reset/ownership chain is documented in ../combat_hit_lifecycle/history-contract.json.',
        'State 3 denotes a damage reaction, state 4 a down/airborne reaction, state 5 death handling in these consumers; enum source names are not recovered.',
    ],
    'unknown': [
        'Complete 8B8650 damage formula and all ATK parameter units',
        'All-skill active trigger coverage for the locally recovered history reset/install lifecycle',
        'Clock units for the mode==2 signed interval >=1000 test',
        'Runtime packet/authority behavior and visual equivalence',
        'Not every hit is network-only: another direct target.slot260 caller exists at 0x5F36CD',
    ],
    'preview_rule': 'Keep geometric overlap, qualified contact, accepted hit, HP change, and selected reaction distinct; do not invent numeric damage or authority.'
}
emit('hit-contract.json', hit)

motions = [
    ('waiting', '[waiting motion]',0xE1EBC8,0x6C0,0x1240,0x370,0x4AC830),
    ('sit', '[sit motion]',0xE1EB90,0x6C8,0x1248,0x36C,0x7447B0),
    ('damage1','[damage motion 1]',0xE1EB6C,0x6CC,0x124C,0x374,0x4AC7C0),
    ('damage2','[damage motion 2]',0xE1EB48,0x6D0,0x1250,0x374,0x4AC7C0),
    ('down','[down motion]',0xE1EB2C,0x6D4,0x1254,0x378,0x4AC7F0),
    ('overturn','[overturn motion]',0xE1EB08,0x6D8,0x1258,0x37C,0x4AC810),
]
actions = [
    ('waiting','[waiting action]',0xE24FE0,0x704,0x12E0,0x390,0x7447D0),
    ('sit','[sit action]',0xE24FA8,0x70C,0x12E8,0x398,0x7447F0),
    ('damage1','[damage action 1]',0xE24F84,0x710,0x12EC,0x39C,0x744800),
    ('damage2','[damage action 2]',0xE24F60,0x714,0x12F0,0x39C,0x744800),
    ('down','[down action]',0xE24F44,0x718,0x12F4,0x3A0,0x744820),
    ('overturn','[overturn action]',0xE24F20,0x71C,0x12F8,0x3A4,0x744830),
    ('last','[last action]',0xE234E4,0x748,0x150,None,None),
]
def resource_row(row):
    name, tag, literal, template, runtime, slot, getter = row
    return {'role':name,'tag':tag,'literal_va':hex(literal),'template_offset':hex(template),'runtime_offset':hex(runtime),'slot':None if slot is None else hex(slot),'getter':None if getter is None else hex(getter)}
reaction = {
    'source': SOURCE,
    'observed_static': {
        'mob_consumer': {'template_reader':'0x887E60','resource_instantiation':'0x500530','string_reader':'0x8304E0','ani_constructor':'0x472A60','act_constructor':'0x4A3900','runtime_base_path':'this+0x244/+0x248 from template+0x7C0'},
        'motions':[resource_row(x) for x in motions],
        'actions':[resource_row(x) for x in actions],
        'getter_policy': 'damage/down/overturn/waiting ANI getters return motion if nonnull, otherwise ACT.currentANI (+0x20). This does not imply motion always wins execution.',
        'state3': {'entry':'0x4BB091','payload':'int vector [direction, scale_integer, damage_variant, optional3, optional4]','variant_field':'this+0x16BC','selection':['0x4BB1E9 slot374(variant): require resolved ANI != null','0x4BB202/0x4BB20B slot39C(variant) -> slot100(ACT)','If ACT remains nonnull, no direct ANI set','Else 0x4BB235/0x4BB23E slot374(variant) -> slotF0(ANI)'],'priority':'damage ACT when present and resolved current ANI exists; otherwise damage ANI'},
        'state4': {'entry':'0x4BB249','payload':'int vector [direction, down_substate, mode, p3, p4]','substate_field':'protected(this+0x1720)','mode_field':'this+0x1728','selection':['slot3A0 downACT if present -> slot100(ACT) at 0x4BB53C; slotF0(0) at 0x4BB548','otherwise slot378 downANI -> slotF0(ANI) at 0x4BB581','otherwise slot36C sitANI -> slotF0(ANI) at the same call'],'fallback_is_sit_not_waiting':True,'physics':'Native consumer computes signed horizontal quantities and vertical displacement using 4B98F0, 4B9FA0; exact units/complete integration not established.'},
        'state0': {'selection':'slot390 waitingACT -> slot100; if current ACT null, slot370 waitingANI -> slotF0, else slotF0(0)'},
        'state1_and_2': {'selection':'slot36C sitANI -> slotF0; slot398 sitACT -> slot100'},
        'state5': {'entry':'0x4BB976','behavior':'Attribution/callbacks, sound, attack/damage gate disable, pause current ANI, stop/reset movement; no proven lastACT switch in this case','attribution_resolver':'0x4AC500 is not an animation constructor or death visual selector'},
        'last_action_preload': {'template_field':'0x748','call_constructor':'0x501C99','runtime_store':'0x501CAB -> this+0x150','act_type_store':'0x501CB3 -> ACT+0x2CC = 11','owner_attach':'0x501CCE -> A2D020','execution_established':False},
        'act_base_ani': {'tags':['[MOTION]','[BASE ANI]'],'tag_literal':'0xE49288','tag_case':'0xA3F23B..0xA3F2EE','read_string':'0xA3F267 -> 0x8304E0','base_directory':'0xA3F151 -> 0x830590 with format %s%s, base and ACT path; truncate after last slash/backslash','append':'0xA3F286 -> 0x778880; append raw BASE ANI path to ACT directory prefix','parsed_path':'parsed+0x4 wstring object (inline/pointer at +0x8)','consumer':'0xA321B0','constructor_calls':['0xA32229 -> 0x4936D0','0xA32238 -> 0x4936D0'],'ani_loader':'0x4937D7 -> 0xA29AD0','runtime_store':'0xA3224A -> ACT+0x20','owner_link':'0xA3224F -> ANI+0x19C = ACT','path_normalization_in_helpers':False},
        'tick': {'function':'0x4BC7D0','end_exclusive':'0x4BDACE','jump_table':'0x4BDAD0','state3_case':'0x4BD06A','state4_case':'0x4BD0B7','state5_case':'0x4BD649','state3_timer':'this+0x1564 elapsed >= protected(this+0x16C0) then queues another state','state4_timing':'uses animation frame indices and ACT indices alongside state timers and grounded/velocity predicates; no simple fixed hit duration inferred'},
    },
    'unknown': ['Full state4 integration and native units','Overturn transition execution (resource load/getters confirmed, execution not closed)','State5/removal to preloaded last action, including special death styles','Generic death animation resource: not invented; MOB does not have a required death ANI in the confirmed tags','Runtime monster hit/down/death equivalence'],
    'preview_rule':'Manual inspection may choose native-confirmed state3/state4 resources. Preserve missing resources and unknown transitions; no invented death animation or automatic accepted hit from overlap.'
}
emit('monster-reaction-contract.json', reaction)

death = {
    'source': SOURCE,
    'observed_static': {
        'native_state5_tick': {
            'enclosing_method': '0x4FB720 (Monster.slot188; called from 49C046)',
            'rea': {'evidence_id': 'ev_2a43bf6ec4f4c0448af3cf08236d51460c7335b467bb6ee529e628ccb6a2e260', 'artifact': '../rea/053-monster-state-tick.c', 'result': '../rea/results/053-monster-state-tick.json', 'scope': 'Pseudocode includes the state5 consumer, while Ghidra FunctionManager body ranges omit switch cases4FC8B4..4FCD6B. Local captures establish case bytes and table dispatch separately.'},
            'state_read': '0x4FC892 protected(this+0x155C) -> 402060',
            'dispatch': '0x4FC8A6 remap4FCE84[state] -> table4FCE68[remap]',
            'state5_case': '0x4FCB2A..0x4FCD6C',
            'default_case': '0x4FCD6C',
            'state5_remap_index': 1,
            'requires_direct_ani': 'this+0x104 != null, else jump to final expiry check at 4FCD45',
            'elapsed': 'B06F00(this+0x1564); call-site values are kept as raw timer counts',
            'lifetime': 'this+0x1E18, set by 4FE290 state5 branch before base state application',
            'ordinary_alpha': 'when slot5A0 is false and mode[1002848]+19A8 != 2: native_u8(C01544(lerp(255,0,elapsed+100-lifetime,100))) -> alpha byte of this+1C0; RGB preserved; alpha mask ORed into this+1C4',
            'gate_true_grayscale': 'when slot5A0 is true: native_u8(C01544(lerp(255,100,elapsed+100-lifetime,100))) copied to RGB bytes of this+1C0; alpha preserved; RGB mask ORed into this+1C4',
            'special_mode': 'slot5A0 false and mode==2: timer+24B8 must exceed 25 and elapsed<=lifetime; factor=lerp(1.0,1.05,elapsed+100-lifetime,100), accumulated+24F8*=factor; when accumulated<=float32(1.2), A297B0 applies factor to current ANI and 4577F0 applies it to available extra-layer entries; velocity reset; timer24B8 restarted',
            'expiry': '4FCD45 elapsed>=this+1E18 and byte(this+1E8)==0 -> virtual.slot654 at4FCD66',
            'color_reset_helper': '498E60; merges selected color bits into +1C0 and clears them from +1C4, with ANI refresh when needed',
            'not_a_lastaction_lookup': True,
        },
        'interpolation': {
            'function': '0xB099B0',
            'signature_inferred_from_x86_arguments': 'float lerp(float start,float end,int position,int duration)',
            'exact_branch_order': 'if position>=duration return end; else if position<=0 return start; else return start+(end-start)*position/duration',
            'float_and_integer_conversion': 'native x87 evaluation and C01544 conversion; do not substitute browser rounding without separate verification',
        },
        'slot654': {
            'monster_vtable': '0xD8385C', 'target': '0x4FA1D0',
            'state_apply_zero_payload_call': '0x4FE986 when state5 payload[0]==0',
            'state_tick_expiry_call': '0x4FCD66',
            'other_tick_call': '0x4FCA98 in state13 when local-authority predicate and elapsed>=0x352',
            'protected_entry': '0x4FA1F0 -> 0x13BAA5F -> push0x08100E7E; jmp0x12EE7C9',
            'rea': {
                'evidence_id': 'ev_f12cbd9cf3515a2bd49d1d6be29f521879abba0515f70fd6f70e9aa6d0681ace',
                'artifact': '../rea/050-monster-death-callback.c',
                'scope': 'REA/Ghidra pseudocode establishes protected entry only. It returns after FUN_013baa5f; it does not decode the virtualized instructions or prove continuation reachability.',
            },
            'visible_fragment_after_protected_gap': {
                'range': '0x4FA222..0x4FA2E2',
                'gate': 'AL false then slot5A0 true required for down-resource switching',
                'act': 'slot3A0 downACT if nonnull and differs from current+148: protected+1704 -> A305B0 index, then slot100(ACT) at4FA284',
                'ani': 'else slot378 downANI if nonnull and differs from directANI+104: protected+1704 -> A27870, then slotF0(ANI) at4FA2D2',
                'continuation': 'slot5D0 at4FA2DC (precise Monster vtable maps it to 750CD0 ret stub)',
                'reachability_limit': 'These native bytes and their local CFG are confirmed. The intervening protection interpreter has not been decoded, so normal entry-to-fragment reachability remains unknown.',
            },
        },
        'removal_request': {
            'slot': '0x164', 'target': '0x499120',
            'gates': 'argument!=0 or slot160==global104F1D4!=null, plus byte(this+1E8)!=1',
            'message_opcode_hex': '0x17', 'message_opcode_decimal': 23,
            'send_begin': '0x499159 global1003164.slot8(0x17,2)',
            'identifiers': 'this.slot3C and this.slot40 via global1003164.slot24',
            'submit': 'global10C0790.slot44(1,-1,this,3) at49919B',
            'mark_pending': 'byte(this+1E8)=1 at49919E',
            'visible_slot654_tail': '4FA7FD..4FA83D: if49C090(this), diagnostic then this.slot164(0) at4FA837; protected entry-to-tail reachability unresolved',
        },
        'removal_receive': {
            'receiver': '0x8C1A30', 'dispatch_table': '0x8C5E64', 'index': 23, 'case': '0x8C4D73',
            'read_ids': 'two slot54 reads; low16 used as object identifiers',
            'resolve': '0x8C4DB7 -> 0x50B820',
            'callback': '0x8C4DCB object.slot60(0)',
            'monster_slot60': '0x4EFC80',
            'behavior': 'if this.slot5A0 true and argument==0: this.slot3C4 returns AuraMaster at+12DC, then565740(this); otherwise byte(this+184)=argument',
            'aura_master_route': '565740 finds an entry whose+4 equals owner; dynamic_cast descriptorF61E98, then child.slot5C(0) when child.slot60() true; no lastaction field read established',
            'native_friendly_type': 'RTTI raw bytes spell .?AVCNRDAuraMaster@@',
        },
        'last_action': {
            'preload': 'MOB template+748 -> ACT ctor501C99 -> object+150; ACT+2CC=11; owner attachA2D020',
            'initializer': '498EC0 zeroes current+148,default+14C,last+150,secondary+154; not498E60',
            'destructor': '49BB48 reads+150 and calls ACT.slot0(1), then zeroes+150 at49BB5E; this is destruction, not visual execution',
            'precise_monster_slot38': 'D8385C.slot38=8E49B0 -> xor al,al;ret',
            'gate_caveat': 'The slot38&&nonempty(last action path) early return in4F2A40 is therefore false for this exact Monster vtable; derived overrides must be checked separately.',
            'execution_established': False,
        },
    },
    'inferences': [
        'Opcode0x17 is an object deactivation/removal request based on call chain and active flag effects; original source enum names are not recovered.',
        'State5 tick implements a fading/graying death lifecycle in the inspected native consumer, not a general mandatory death ANI tag.',
    ],
    'unknown': [
        'Virtualized instructions reached through12EE7C9 and their conditions/call effects',
        'Entry-to-visible-fragment reachability inside4FA1D0',
        'Actual lastACT+150 switching/execution and resource-specific special death behaviors',
        'Timer clock scaling, exact end-to-end removal authority/runtime behavior',
        'Render pipeline application of+1C0/+1C4 and runtime visual equivalence',
        'Scene destruction effects and complete scene cleanup lifetime',
    ],
    'preview_rule': 'Use native-confirmed damage/down resource routing. Keep death lifecycle fragments separate from a recovered full death controller; do not auto-play lastACT or assign generic death ANI. Raw timer counts and native numeric conversions are not assumed to be web milliseconds/Math.round.',
}
emit('death-lifecycle-contract.json', death)
emit('scene-destruction-contract.json', scene_contract(SOURCE))
emit('scene-specialized-contract.json', specialized_contract(SOURCE))
print(json.dumps({'source_sha256':SOURCE['sha256'],'authoritative_excerpts':len(blocks),'contracts':['hit-contract.json','monster-reaction-contract.json','death-lifecycle-contract.json','scene-destruction-contract.json','scene-specialized-contract.json','capture-manifest.json']}, indent=2))
