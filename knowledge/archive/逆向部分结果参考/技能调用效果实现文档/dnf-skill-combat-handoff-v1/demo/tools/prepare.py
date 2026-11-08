"""Independent battle content, bound to the current saved packed PVF.

Source graphs determine eligibility; observed draw intervals calibrate missing
controller schedules. These schedules are NOT a generic native state machine.
No screenshots or captured sprite pixels are used as animation content.
"""
from pathlib import Path
import sys, json, struct, collections, hashlib, shutil, posixpath, re
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT.parent
sys.path.insert(0,str(BASE/'derivation/lib'))
from prepare_content import PackedPvf, script, animation

def norm(p):return posixpath.normpath(p.replace('\\','/')).lower()
def rel(p,v):return norm(posixpath.join(posixpath.dirname(p),v))
def dump(p,v):
    p.parent.mkdir(parents=True,exist_ok=True)
    p.write_text(json.dumps(v,ensure_ascii=False,indent=2),encoding='utf8')

def main():
    from rebuild_seed import rebuild_seed
    rebuild_seed()
    p=PackedPvf(); cache=ROOT/'content/cache'; cache.mkdir(parents=True,exist_ok=True)
    old=BASE/'derivation/seed'
    index=json.loads((old/'cache/index.json').read_text('utf8'))
    shutil.copyfile(old/'cache/resources.bin',cache/'resources.bin')
    shutil.copyfile(old/'profile.json',ROOT/'content/profile.json')
    shutil.copyfile(old/'skills.json',ROOT/'content/skills.json')
    strings=index['strings']; ids={s:i for i,s in enumerate(strings)}
    scripts={}; stats=collections.Counter(); diagnostics=[]
    def src(path):
        path=norm(path)
        if path not in scripts:scripts[path]=script(p,path)
        return scripts[path]
    def vals(s,tag):return next((f['values'] for f in s['fields'] if f['tag'].lower()==tag.lower()),[])
    def ensure(path):
        path=norm(path)
        if path in index['entries']:return
        s=src(path)
        if path.endswith('.ani'):data=json.dumps(animation(s,stats),ensure_ascii=False,separators=(',',':')).encode('utf8')
        else:
            data=bytearray(b'\xb0\xd0')
            for t in s['tokens']:
                typ=t['type'];v=t['value']
                if typ in (0,2):nt,nv=(2 if typ==0 else 4),t['raw']
                else:
                    if v not in ids:ids[v]=len(strings);strings.append(v)
                    nt,nv=(5 if typ==3 else 6),ids[v]
                data.extend(struct.pack('<BI',nt,nv))
        with (cache/'resources.bin').open('ab') as out:
            index['entries'][path]=dict(offset=out.tell(),size=len(data),raw_sha256=s['raw_sha256'],record=p.entries[path]['record'])
            out.write(data)
    def refs(path):
        out=[]
        for f in src(path)['fields']:
            for v in f['values']:
                if not isinstance(v,str) or not v.lower().endswith(('.ani','.als','.obj','.ptl','.atk','.act')):continue
                candidates=[rel(path,v),norm(v)]
                match=next((c for c in candidates if c in p.entries),None)
                if match:out.append((match,f))
                else:diagnostics.append(dict(source=path,offset=f['offset'],missing=v))
        return out
    def closure(roots):
        seen=set();todo=list(roots)
        while todo:
            path=norm(todo.pop())
            if path in seen or path not in p.entries:continue
            seen.add(path);ensure(path)
            if path.endswith('.ani') and path+'.als' in p.entries:todo.append(path+'.als')
            if not path.endswith('.ani'):todo.extend(x for x,f in refs(path))
        return seen
    def ani(path):return animation(src(path),collections.Counter())
    def duration(path):return sum(f['duration'] for f in ani(path)['frames'])
    def boundary(path,frame):
        a=ani(path)
        if frame<0 or frame>=len(a['frames']):raise ValueError(f'Unresolved ALS frame {frame}: {path}')
        return sum(f['duration'] for f in a['frames'][:frame])
    def tracks(path,begin=0,layer=0,pos=(0,0,0),anchor='actor',limit=1e9,stack=()):
        path=norm(path)
        if path in stack or len(stack)>12:raise ValueError('Recursive ALS')
        ensure(path);end=min(limit,begin+duration(path))
        out=[dict(path=path,begin=begin,end=end,layer=layer,position=pos,anchor=anchor,repeat=False,basis='source ANI + ALS frame events',source=path)]
        ap=path+'.als'
        if ap not in p.entries:return out
        ensure(ap);s=src(ap);decl={};events=[]
        for f in s['fields']:
            v=f['values'];tag=f['tag'].lower()
            if tag=='[use animation]' and len(v)==2:decl[v[1]]=rel(path,v[0])
            elif tag in ('[add]','[remove]') and len(v)==3:events.append((v,tag,f['offset']))
        for i,(v,tag,off) in enumerate(events):
            if tag!='[add]':continue
            try:
                child=decl[v[2]];start=begin+boundary(path,v[0]);stop=end
                for vv,tt,oo in events[i+1:]:
                    if vv[2]==v[2] and vv[0]>=v[0]:stop=min(stop,begin+boundary(path,vv[0]));break
                if start<stop:out.extend(tracks(child,start,layer+v[1],pos,anchor,stop,stack+(path,)))
            except (ValueError,KeyError) as e:diagnostics.append(dict(source=ap,offset=off,unexecuted=str(e)))
        return out

    # Rebind selected monsters from THIS snapshot. Never copy the other client's
    # action addresses, source offsets, hashes or MOB state bindings.
    monster_paths=['monster/goblin/goblin.mob','monster/lugaru/lugaru.mob','monster/dragondungeon/rockgolem/rockgolem.mob']
    monsters=[]
    def act_tracks(path):
        out=[]
        if path not in p.entries:return out
        # Restrict to explicit BASE ANI, rather than searching animation names.
        for f in src(path)['fields']:
            if f['tag'].lower()=='[base ani]':
                for v in f['values']:
                    if isinstance(v,str):
                        ap=rel(path,v)
                        if ap in p.entries:out.extend(tracks(ap))
        return out
    for path in monster_paths:
        s=src(path);closure([path]);states={};issues=[]
        for state,tag in [('idle','[waiting motion]'),('damage1','[damage motion 1]'),('damage2','[damage motion 2]'),('down','[down motion]')]:
            v=vals(s,tag)
            if len(v)==1 and isinstance(v[0],str):
                ap=rel(path,v[0]);states[state]=dict(entry=ap,tracks=tracks(ap),duration=duration(ap),binding_tag=tag)
            else:
                atag={'idle':'[waiting action]','damage1':'[damage action 1]','damage2':'[damage action 2]','down':'[down action]'}[state]
                av=vals(s,atag)
                if len(av)==1:
                    ap=rel(path,av[0]);tt=act_tracks(ap)
                    if tt:states[state]=dict(entry=ap,tracks=tt,duration=max(t['end'] for t in tt),binding_tag=atag)
        death=vals(s,'[last action]')
        if death:
            # Only explicit MOTION tracks in the declared final ACT are bound.
            act=rel(path,death[0]);states['death']=dict(entry=act,tracks=[],duration=0,binding_tag='[last action]')
            states['death']['tracks']=act_tracks(act)
            states['death']['duration']=max((t['end'] for t in states['death']['tracks']),default=0)
            if not states['death']['tracks']:issues.append('Explicit final action has no supported MOTION; no silent shared fallback')
        die=[vals(s,'[die effect]')] if vals(s,'[die effect]') else []
        monsters.append(dict(path=path,name=vals(s,'[name]')[0],raw_sha256=s['raw_sha256'],die_effect=die,states=states,issues=issues))
    closure(['monster/common/particle/monsterdiepiece.ptl','monster/common/animation/monsterdiepiece.ani','monster/common/animation/monsterdieflash.ani','monster/common/animation/monsterdiesmoke.ani'])

    report=BASE/'evidence/skill-chain-analysis'
    cat=json.loads((old/'skills.json').read_text('utf8'));catalog={s['key']:s for s in cat['skills']}
    specs=[]
    for key,hotkey in [('hopsmash','A'),('gorecross','S'),('bloodblast','D'),('outragebreak','G'),('bloodblastex','H'),('bloodsword','Q'),('bloodboom','E'),('frenzy','W')]:
        evidence=json.loads((report/f'skills/{key}.json').read_text('utf8'));skill=catalog[key]
        roots=skill['body_sequence']+[b['path'] for b in evidence['source_object_bindings']]
        roots.extend(v['target'] for v in evidence['static_controller_references'])
        # Verified resource request/return pairs establish code-selected roots
        # which are not declared in ALS (e.g. G ready sword, A sword/smash).
        for ph in evidence['phase_observations'][:1]:
            for req in ph['resource_requests']:
                if 'base_path' in req and 'relative_path' in req:
                    ap=rel(req['base_path'].rstrip('/')+'/root',req['relative_path'])
                    if ap in p.entries and not (key=='bloodsword' and '/frenzy/' in ap):roots.append(ap)
        if key=='frenzy':roots+=['character/swordman/effect/animation/frenzy/cast.ani','character/swordman/effect/animation/frenzy/blast.ani','character/swordman/effect/animation/frenzy/buff.ani']
        if key=='frenzy':roots.append('common/etc/animation/endofcasting.ani')
        eligible=closure(roots);body_related=closure(skill['body_sequence']);body=[];fx=[];t=0
        for path in skill['body_sequence']:
            d=duration(path);body.append(dict(path=path,begin=t,end=t+d))
            fx.extend(tracks(path,t)[1:]);t+=d
        # Known frame-triggered creation rules take precedence over calibration.
        if key in ('hopsmash','gorecross'):
            for e in skill['effects_timeline']:
                if e.get('als_source'):continue
                start=body[e['stage']]['begin']+e['offset_ms'];path=e['path']
                if e.get('object_source'):
                    fx.append(dict(path=path,begin=start,end=min(start+duration(path),body[e['stage']]['begin']+e['end_offset_ms']),layer=e['layer'],position=e.get('position',[0,0,0]),anchor=e.get('anchor','actor'),spawn=body[e['stage']]['begin']+e.get('spawn_offset_ms',e['offset_ms']),repeat=False,basis=e['basis'],source=e))
                else:fx.extend(tracks(path,start,e['layer'],e.get('position',[0,0,0]),e.get('anchor','actor')))
        else:
            phase=evidence['phase_observations'][0]
            intervals=[v for v in phase['animation_intervals'] if v.get('first_draw_ms') is not None and v['normalized_source_path'] in eligible]
            # First actually observed draw, never construction time, aligns this
            # diagnostic schedule. It is explicit in the exported provenance.
            offset=min((v['first_draw_ms'] for v in intervals),default=0)
            shift=0
            if key in ('bloodboom','bloodsword','outragebreak'):
                # If a body attachment draw exists it supplies the start. If
                # all observed draws belong to an object, align to the body's
                # first attack box, or its final frame as an explicit inference.
                body_fx=[v for v in intervals if any(v['normalized_source_path']==e['path'] for e in fx)]
                if not body_fx and body and key!='outragebreak':
                    tt=body[-1];aa=ani(tt['path']);elapsed=tt['begin'];found=False
                    for ff in aa['frames']:
                        if any(bb['type']==15 for bb in ff['boxes']):shift=elapsed;found=True;break
                        elapsed+=ff['duration']
                    if not found:shift=tt['end']-aa['frames'][-1]['duration']
            basepacket=None
            for v in intervals:
                if v['normalized_source_path'].startswith('character/') and v['verified_flat_packet_examples']:
                    basepacket=v['verified_flat_packet_examples'][0]['packet_first_dwords'][1:3];break
            parentxyz=None
            for chain in phase['spawn_chains']:
                if chain.get('flag_4c_add_parent_position') and chain.get('core_xyz'):
                    parentxyz=[chain['core_xyz'][i]-chain['input_xyz'][i] for i in range(3)];break
            # Infer projection translation from a source-bound object's own
            # draw packet and verified creation XYZ; no fixed camera offset.
            object_members={}
            for binding in evidence['source_object_bindings']:
                object_members[binding['object_id']]=closure([binding['path']])
            native_positions={}
            for obj in phase['generic_objects']:
                for writes in obj['position_write_requests'].values():
                    if all(str(i) in writes and writes[str(i)]['minimum']==writes[str(i)]['maximum'] for i in range(3)):
                        native_positions[obj['object_address']]=[writes[str(i)]['minimum'] for i in range(3)]
            # Keep the actor's early attached effect as projection origin, so
            # later horizontal motion is not folded into a negative sword offset.
            early_basepacket=basepacket
            if parentxyz and basepacket is None:
                for binding in evidence['source_object_bindings']:
                    basic=vals(src(binding['path']),'[basic motion]')
                    if not basic:continue
                    bp=rel(binding['path'],basic[0])
                    vv=next((v for v in intervals if v['normalized_source_path']==bp and v['verified_flat_packet_examples']),None)
                    cc=next((c for c in phase['spawn_chains'] if c['object_id']==binding['object_id']),None)
                    if vv and cc:
                        packet=vv['verified_flat_packet_examples'][0]['packet_first_dwords'][1:3];xyz=cc['core_xyz'];delta=[xyz[i]-parentxyz[i] for i in range(3)]
                        basepacket=[packet[0]-delta[0],packet[1]-(delta[1]-delta[2])];break
            observed_paths=set()
            for v in intervals:
                path=v['normalized_source_path'];start=shift+max(0,v['first_draw_ms']-offset)
                end=max(start+1,shift+v['last_draw_ms']-offset+5)
                # Screen-projection difference is observed. Do not pretend it
                # recovers XYZ or particle trajectory. Combat uses only source
                # boxes with source-bound coordinates, not these projections.
                packet=v['verified_flat_packet_examples'];delta=[0,0,0]
                if basepacket and packet:
                    xy=packet[0]['packet_first_dwords'][1:3];delta=[xy[0]-basepacket[0],xy[1]-basepacket[1],0]
                projection_only=True
                # Source XYZ remains XYZ where object ancestry and an actual
                # position write/creation chain agree. Only unresolved instances
                # use explicitly labelled projected-anchor inference.
                owners=[int(vv) for vv in v.get('verified_main_draw_object_counts',{}) if int(vv) in native_positions]
                belonging=[oid for oid,paths in object_members.items() if path in paths]
                chain=next((cc for cc in phase['spawn_chains'] if cc['object_id'] in belonging),None)
                xyz=native_positions[owners[0]] if len(owners)==1 else chain['core_xyz'] if chain else None
                if xyz and parentxyz:
                    rootdelta=[xyz[i]-parentxyz[i] for i in range(3)]
                    if basepacket is not None and early_basepacket is not None and chain:
                        # Native parent motion has not been recovered generally;
                        # preserve observed projected X but retain source Y/Z.
                        rootdelta[0]=delta[0]
                    delta=[rootdelta[0],rootdelta[1],rootdelta[2]];projection_only=False
                elif xyz and packet and basepacket:
                    # A planar actor is a demo assumption, but effect Z is
                    # supplied by the actual creation chain. Preserve it so a
                    # raised explosion does not become a different ground lane.
                    delta=[delta[0],delta[1]+xyz[2],xyz[2]];projection_only=False
                layer=0
                # Match actual ALS declarations for layer; names alone never
                # select layers or eligibility.
                for ap in eligible:
                    if not ap.endswith('.als'):continue
                    ss=src(ap);names=[f['values'][1] for f in ss['fields'] if f['tag'].lower()=='[use animation]' and len(f['values'])==2 and rel(ap[:-4],f['values'][0])==path]
                    for f in ss['fields']:
                        if f['tag'].lower()=='[add]' and len(f['values'])==3 and f['values'][2] in names:layer=f['values'][1]
                if path not in observed_paths:fx=[e for e in fx if e['path']!=path]
                observed_paths.add(path)
                fx.append(dict(path=path,begin=start,end=end,layer=layer,position=delta,anchor='actor' if path in body_related else 'cast',repeat=end-start>duration(path)+50,projection_only=projection_only,basis='source graph + verified object XYZ or explicitly inferred projected anchor + calibrated draw schedule',source=dict(sample=phase['sample'],constructor_seq=v['seq'],first_draw_ms=v['first_draw_ms'],last_draw_ms=v['last_draw_ms'],packet_examples=packet,call_witnesses=v['draw_callsite_witnesses'])))
        if key in ('bloodblast','bloodblastex','frenzy'):
            # Explicit demo body choice from CHR [buff motion]. Native body
            # animation identity is resident and not yet joined to its path.
            path='character/swordman/animation/summon2.ani';closure([path]);body=[dict(path=path,begin=0,end=duration(path),basis='CHR buff motion demo fallback; native identity unresolved')]
        spec=dict(key=key,name=skill['name'],hotkey=hotkey,groups=skill['groups'],classification_basis=skill['classification_basis'],skill_source=skill['source'],skill_raw_sha256=evidence['skill_raw_sha256'],body=body,effects=fx,duration=max([t,*(e['end'] for e in fx),*(b['end'] for b in body),1]),controller_complete=False,evidence=str((report/f'skills/{key}.json').relative_to(BASE)).replace('\\','/'))
        if key=='hopsmash':spec['motion']=skill['actor_motion'];spec['internal_parameter']=27
        if key=='bloodsword':
            ss=src(skill['source']);dungeon=False;static=[]
            for f in ss['fields']:
                if f['tag']=='[dungeon]':dungeon=True
                elif f['tag']=='[/dungeon]':dungeon=False
                elif dungeon and f['tag']=='[static data]':static=f['values'];break
            spec['inferred_motion']=dict(distance=static[2],ready=body[1]['begin'],end=body[1]['end'],basis='SKL dungeon static data index 2 + charge body interval; lunge interpretation inferred',source=skill['source'])
        specs.append(spec)
    # Persistent buff follows character. Disappearance follows explicit toggle;
    # do not equate disappearance with observed native object destruction.
    closure(['character/swordman/effect/animation/frenzy/buff.ani'])
    index['battle_extension']=dict(source='same packed snapshot',monster_bindings='regenerated from current MOB/ACT/ALS',native_cross_version_addresses_imported=False)
    dump(cache/'index.json',index)
    diagnostics=list({json.dumps(d,sort_keys=True):d for d in diagnostics}.values())
    dump(ROOT/'content/battle.json',dict(schema=1,source_exe_sha256=index['client_exe_sha256'],skills=specs,monsters=monsters,diagnostics=diagnostics,policy=dict(version='battle-reconstruction-v1',move_units_per_second=180,damage_per_hit=100,monster_hp=700,repeat_hit_ms=250,source_hit_boxes=True,native_damage_formula_recovered=False,trace_calibration_is_generic_controller=False,hopsmash_vertical='source-interpolated height, inferred parabola; native getter modifier unknown',bloodsword_motion='inferred SKL static index 2 lunge over charge stage',projected_effect_collision='unresolved projected anchors interpreted in demo plane; not full native XYZ reconstruction')))
    dump(ROOT/'reports/content-provenance.json',dict(snapshot=index['snapshot'],snapshot_sha256=index['snapshot_sha256'],exe_sha256=index['client_exe_sha256'],entries=len(index['entries']),source_graph_sha256=hashlib.sha256((report/'source-graph.json').read_bytes()).hexdigest(),skills=[dict(key=s['key'],effect_instances=len(s['effects']),controller_complete=False) for s in specs],monsters=[dict(path=m['path'],sha256=m['raw_sha256'],states=list(m['states'])) for m in monsters],diagnostics=diagnostics))
    measured={s['key'] for s in specs};excluded={'bloodyrave'};rows=[]
    for s in cat['skills']:
        status='non_active' if s['type']!='[active]' else 'excluded' if s['key'] in excluded else 'observed_chain_partial_controller' if s['key'] in measured else 'inferred_resource_preview' if s['body_sequence'] else 'unmapped'
        rows.append(dict(key=s['key'],name=s['name'],groups=s['groups'],classification_basis=s['classification_basis'],status=status))
    dump(ROOT/'reports/capabilities.json',dict(status_counts=dict(collections.Counter(s['status'] for s in rows)),skills=rows,monster_types=monsters,notes='Status describes source/mapping coverage, not whole-game runtime validation. Current character family is Swordman only.'))
    print('Prepared',len(specs),'skills,',sum(len(s['effects']) for s in specs),'effect instances;',len(monsters),'monster types;',len(diagnostics),'diagnostics',flush=True)

if __name__=='__main__':main()
