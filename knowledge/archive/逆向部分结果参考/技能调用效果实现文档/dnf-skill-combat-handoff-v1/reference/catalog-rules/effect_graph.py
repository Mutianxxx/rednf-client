"""Actor-independent source graph and bounded ALS/OBJ timeline compiler.

Only file-authored events with known nonnegative frames execute. Executable
spawn rules are supplied separately and bound to the source build hash.
"""
from pathlib import Path
import collections,functools,json,posixpath,struct

def resolve(parent,child):
    return posixpath.normpath(posixpath.join(posixpath.dirname(parent),child.replace('\\','/').lower()))

class CacheSource:
    def __init__(self,root):
        self.index=json.loads((root/'content/cache/index.json').read_text(encoding='utf8'))
        self.entries=self.index['entries'];self.stream=(root/'content/cache/resources.bin').open('rb')
    def has(self,path):return path in self.entries
    @functools.lru_cache(maxsize=None)
    def data(self,path):
        e=self.entries[path];self.stream.seek(e['offset']);return self.stream.read(e['size'])
    @functools.lru_cache(maxsize=None)
    def ani(self,path):return json.loads(self.data(path))
    @functools.lru_cache(maxsize=None)
    def fields(self,path):
        out=[];strings=self.index['strings']
        for off,(typ,val) in enumerate(struct.iter_unpack('<BI',self.data(path)[2:])):
            if typ in (5,6):v=strings[val]
            elif typ==4:v=struct.unpack('<f',struct.pack('<I',val))[0]
            else:v=struct.unpack('<i',struct.pack('<I',val))[0]
            if typ==5:out.append(dict(tag=v,values=[],normalized_offset=off*5+2))
            elif out:out[-1]['values'].append(v)
        return out
    def provenance(self,path):
        return {k:self.entries[path][k] for k in ['raw_sha256','record']}

class EffectGraph:
    def __init__(self,source):
        self.source=source;self.unresolved=[];self.dependencies={};self.serial=0
    def gap(self,path,reason,**data):self.unresolved.append(dict(source=path,reason=reason,**data))
    def times(self,path):
        out=[0]
        for f in self.source.ani(path)['frames']:out.append(out[-1]+f['duration'])
        return out
    def trigger(self,path,trigger):
        if 'frame' in trigger:
            n=trigger['frame']
            if not 0<=n<len(self.times(path))-1:raise ValueError(f'Invalid trigger frame {path}: {n}')
            return self.times(path)[n]
        if 'flag' in trigger:
            time=0
            for frame in self.source.ani(path)['frames']:
                if any(f['tag']=='[SET FLAG]' and f['values']==[trigger['flag']] for f in frame['properties'].get('unconsumed',[])):return time
                time+=frame['duration']
            raise ValueError(f'Missing flag {trigger}: {path}')
        raise ValueError('Unknown trigger')
    def track(self,path,stage,begin=0,layer=10000,end=None,chain=(),**meta):
        if path in chain or len(chain)>=16:
            self.gap(path,'recursive animation cycle/depth',chain=chain);return []
        if not self.source.has(path):self.gap(path,'missing animation');return []
        natural=begin+self.times(path)[-1]
        repeat=bool(self.source.ani(path)['globals'].get('0',False))
        end=natural if end is None else (end if repeat else min(end,natural))
        if end<=begin:return []
        self.serial+=1
        row=dict(path=path,stage=stage,offset_ms=begin,end_offset_ms=end,layer=layer,repeat=repeat,
                 instance=f'animation-{self.serial}',**meta)
        return [row]+self.attachments(path,stage,begin,end,layer,chain+(path,),meta)
    def attachments(self,parent,stage,begin,end,layer=0,chain=(),meta=None):
        ap=parent+'.als'
        if not self.source.has(ap):return []
        refs={};active={};spawns=[];scheduled=[];times=self.times(parent)
        for ordinal,event in enumerate(self.source.fields(ap)):
            tag,v=event['tag'],event['values']
            if tag=='[use animation]' and len(v)==2:refs[v[1]]=resolve(parent,v[0]);continue
            if tag in ('[add]','[none effect add]','[remove]') and len(v)==3:
                frame,sub_layer,name=v
                if not isinstance(frame,int) or not 0<=frame<len(times)-1:
                    self.gap(ap,'controller/negative or invalid frame event',event=event);continue
                if tag!='[remove]' and (name not in refs or not self.source.has(refs[name])):
                    self.gap(ap,'undeclared/missing child animation',event=event);continue
                scheduled.append(dict(frame=frame,name=name,layer=layer+sub_layer,path=refs.get(name),event=event,ordinal=ordinal,tag=tag))
            elif not tag.startswith('[/'):
                self.gap(ap,'unsupported ALS instruction',event=event)
        self.dependencies[ap]=dict(parent=parent,animations=refs,source=self.source.provenance(ap))
        period=times[-1]
        cycles=max(1,int((end-begin-1)//period)+1) if period>0 and self.source.ani(parent)['globals'].get('0',False) else 1
        if cycles>1000:self.gap(ap,'loop expansion exceeds preview bound',cycles=cycles);cycles=1000
        # Declarations can be interleaved; runtime events follow frame order,
        # with source order retained for events on the same frame.
        for cycle in range(cycles):
            for event in sorted(scheduled,key=lambda e:(e['frame'],e['ordinal'])):
                at=begin+cycle*period+times[event['frame']]
                if at>=end:continue
                name=event['name']
                if event['tag']=='[remove]':
                    if name in active:active.pop(name)['end']=at
                    continue
                if name in active:active.pop(name)['end']=at
                item=dict(event,begin=at,end=end)
                active[name]=item;spawns.append(item)
        out=[]
        for item in spawns:
            m=dict(meta or {});m.update(als_source=ap,unique_name=item['name'],als_event=item['event'],
                basis='ALS parent frame/layer/remove; recursive child local clock; lifetime clipped to parent (reconstruction policy)')
            # repeat is derived from this child ANI, not inherited from parent.
            m.pop('repeat',None)
            out+=self.track(item['path'],stage,item['begin'],item['layer'],item['end'],chain,**m)
        return out
    def object(self,path):
        fields=self.source.fields(path);basic=[];add=[];extra=[]
        for f in fields:
            tag,v=f['tag'],f['values']
            if tag=='[basic motion]' and v:basic.append(dict(path=resolve(path,v[0]),layer=0,source_field=f))
            elif tag=='[add object effect]' and len(v)>=2:
                # Third parameter is preserved, not misinterpreted as XYZ.
                add.append(dict(path=resolve(path,v[0]),layer=v[1],raw_parameters=v[2:],source_field=f))
            elif tag in ('[etc motion]','[action]','[particle]'):extra.append(f)
        result=dict(path=path,source=self.source.provenance(path),basic=basic,add=add,
            controller_fields=extra,source_fields=fields)
        self.dependencies[path]=result
        return result
    def spawn(self,obj,rule,body):
        definition=self.object(obj);begin=self.trigger(body,rule['trigger']);tracks=[]
        primary=definition['basic']
        if not primary:raise ValueError('Missing OBJ basic motion: '+obj)
        # A single source ANI cycle is a preview bound, not an invented entity TTL.
        lifetime=max(self.times(v['path'])[-1] for v in primary)
        meta=dict(object_source=obj,object_id=rule['object_id'],anchor=rule['anchor'],position=rule['position'],
            spawn_offset_ms=begin,spawn_code=rule['spawn_code'],trigger=rule['trigger'],
            basis='verified client spawn/trigger + OBJ basic/add animation',
            entity_lifetime_policy='one basic motion cycle; controller overrides unresolved')
        if rule.get('conditional'):meta['conditional']=rule['conditional']
        for part in primary+definition['add']+rule.get('extra_animations',[]):
            m=dict(meta)
            m['position']=[a+b for a,b in zip(rule['position'],part.get('position',[0,0,0]))]
            m['object_component']=part
            tracks+=self.track(part['path'],rule['stage'],begin,10000+part['layer'] if part in primary+definition['add'] else part['layer'],begin+lifetime,**m)
        return tracks

def compile_profiles(root,catalog):
    source=CacheSource(root);graph=EffectGraph(source)
    config=json.loads((root/'content/controller-effects.json').read_text(encoding='utf8'))
    if config['client_exe_sha256']!=source.index['client_exe_sha256']:raise ValueError('Controller evidence belongs to a different client')
    # The authoritative ID table, not basename matching, selects the object.
    import sys
    sys.path.insert(0,str(root.parent/'reverse_lab/v2/tools'))
    from packed_pvf import PackedPvf
    sys.path.insert(0,str(root/'tools'))
    from prepare_content import script
    pvf=PackedPvf();lst=script(pvf,'passiveobject/passiveobject.lst')
    tokens=lst['tokens'];ids={}
    for i,t in enumerate(tokens[:-1]):
        if isinstance(t['value'],int) and isinstance(tokens[i+1]['value'],str):ids[t['value']]='passiveobject/'+tokens[i+1]['value'].replace('\\','/').lower()
    bykey={s['key']:s for s in catalog['skills']};counts={}
    for skill in catalog['skills']:
        tracks=[]
        for stage,path in enumerate(skill['body_sequence']):
            tracks+=graph.attachments(path,stage,0,graph.times(path)[-1],chain=(path,),meta=dict(anchor='actor',position=[0,0,0]))
        # Explicit old profiles are still labelled reconstructed; now expand their ALS too.
        for e in skill['effects_timeline']:
            base={k:v for k,v in e.items() if k not in ('path','stage','offset_ms','layer','end_offset_ms')}
            base.update(anchor='actor',position=[0,0,0])
            tracks+=graph.track(e['path'],e['stage'],e.get('offset_ms',0),e.get('layer',10000),e.get('end_offset_ms'),**base)
        skill['effects_timeline']=tracks;skill['effect_controller_rules']=[]
        skill.pop('actor_motion',None)
    for rule in config['rules']:
        skill=bykey[rule['skill']]
        if skill['id']!=rule['skill_id']:raise ValueError('Skill ID changed')
        obj=ids[rule['object_id']]
        skill['effects_timeline']+=graph.spawn(obj,rule,skill['body_sequence'][rule['stage']])
        skill['effect_controller_rules'].append(dict(rule,object_source=obj,object_source_sha256=source.provenance(obj)['raw_sha256']))
        skill['limitations']=rule.get('limitations',[])
        motion=rule.get('actor_motion')
        if motion:
            source_path=motion['source_skl']
            fields=source.fields(source_path)
            in_scope=False;static=None
            for field in fields:
                if field['tag']==f"[{motion['scope']}]":in_scope=True
                elif field['tag']==f"[/{motion['scope']}]":in_scope=False
                elif in_scope and field['tag']=='[static data]':
                    static=field;break
            if static is None:raise ValueError(f"Missing {motion['scope']} static data: {source_path}")
            values=static['values'];distance_indices=motion['distance_data_indices'];height_indices=motion['height_data_indices']
            required=distance_indices+height_indices
            if any(index<0 or index>=len(values) for index in required):raise ValueError(f"Static data index out of range: {source_path}")
            if any(not isinstance(values[index],(int,float)) for index in required):raise ValueError(f"Non-numeric motion data: {source_path}")
            stage=motion['stage'];body=skill['body_sequence'][stage];times=graph.times(body)
            frame_indices=motion['frame_indices']
            if any(index<0 or index>=len(times) for index in frame_indices):raise ValueError(f"Motion frame out of range: {body}")
            frame_times=[times[index] for index in frame_indices]
            if len(frame_times)!=3 or frame_times[0]!=0 or frame_times[0]>=frame_times[1] or frame_times[1]>=frame_times[2]:
                raise ValueError(f"Invalid motion frame timing: {body}")
            evidence=source.provenance(source_path)
            skill['actor_motion']=dict(
                source=dict(path=source_path,raw_sha256=evidence['raw_sha256'],record=evidence['record'],
                    scope=motion['scope'],field=static['tag'],normalized_offset=static['normalized_offset']),
                static_data=values,
                distance_range=[values[index] for index in distance_indices],
                height_range=[values[index] for index in height_indices],
                distance_data_indices=distance_indices,height_data_indices=height_indices,
                input_interval_denominator_ms=motion['input_interval_denominator_ms'],
                stage=stage,frame_indices=frame_indices,frame_times_ms=frame_times,
                frame_progress=motion['frame_progress'],runtime_hold_field=motion['runtime_hold_field'],
                runtime_distance_field=motion['runtime_distance_field'],runtime_code=motion['runtime_code'],
                vertical_curve=motion['vertical_curve'])
    # Index all cached OBJ definitions using exactly the same generic reader.
    for path in source.entries:
        if path.endswith('.obj'):graph.object(path)
    for s in catalog['skills']:
        counts[s['key']]=dict(total=len(s['effects_timeline']),als=sum('als_source' in e for e in s['effects_timeline']),
            entities=len({e['object_id'] for e in s['effects_timeline'] if 'object_id' in e}))
    catalog['summary']['with_als_effects']=sum(v['als']>0 for v in counts.values())
    catalog['summary']['effect_tracks']=sum(v['total'] for v in counts.values())
    catalog['summary']['verified_entity_skills']=sum(v['entities']>0 for v in counts.values())
    motions={s['key']:s['actor_motion'] for s in catalog['skills'] if 'actor_motion' in s}
    report=dict(schema='source-effect-graph-v1',dependencies=graph.dependencies,unresolved=graph.unresolved,skills=counts,
        actor_motion_profiles=motions,
        id_table_source=dict(path=lst['path'],raw_sha256=lst['raw_sha256']),controller_rules=config,
        policies=['ANI local clocks reset on add; attachments are clipped to parent lifetime.',
            'A source ANI cycle bounds entity preview; unresolved controller travel/overrides are not synthesized.',
            'Negative ALS events and unknown commands are preserved, not run as frame zero.'])
    (root/'reports/effect-graph.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf8')
    # Keep file-authored composition coverage separate from controller recovery.
    # A filename candidate is never promoted to a confirmed spawn dependency.
    coverage=[]
    for skill in catalog['skills']:
        if skill['type']!='[active]':continue
        entity_ids=sorted({e['object_id'] for e in skill['effects_timeline'] if 'object_id' in e})
        coverage.append(dict(skill=skill['key'],name=skill['name'],source=skill['source'],groups=skill['groups'],
            status=skill['status'],body_animations=len(skill['body_sequence']),
            effect_tracks=len(skill['effects_timeline']),als_tracks=counts[skill['key']]['als'],
            reviewed_entity_ids=entity_ids,horizontal_motion='actor_motion' in skill,
            full_controller_confirmed=False,
            limitations=skill.get('limitations',[]) or ['Controller spawn branches and complete effect composition have not been recovered.']))
    coverage_report=dict(client_exe_sha256=config['client_exe_sha256'],active_skills=coverage,
        unresolved_file_events=graph.unresolved,
        scope='Current Swordman catalog only. Cross-actor format scans do not establish skill controllers for other actors.')
    (root/'reports/effect-coverage.json').write_text(json.dumps(coverage_report,ensure_ascii=False,indent=2),encoding='utf8')
    return graph.unresolved
