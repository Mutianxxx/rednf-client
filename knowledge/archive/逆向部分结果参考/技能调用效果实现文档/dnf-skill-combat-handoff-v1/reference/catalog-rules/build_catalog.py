"""Build a complete, source-qualified Swordman skill catalog; never invent IDs."""
from pathlib import Path
import collections
import hashlib
import json
import re

root=Path(__file__).resolve().parents[1]
source=root/'content/catalog-raw.json'
raw=json.loads(source.read_text(encoding='utf8'))
def values(script,tag):
    return next((f['values'] for f in script['fields'] if f['tag']==tag),[])
def first(script,tag,default=None):
    a=values(script,tag);return a[0] if a else default
tokens=raw['list']['tokens'];ids={}
for i,t in enumerate(tokens[:-1]):
    if isinstance(t.get('value'),int) and isinstance(tokens[i+1].get('value'),str):
        ids['skill/'+tokens[i+1]['value'].replace('\\','/').lower()]=t['value']
jobs=values(raw['character'],'[growtype name]')
awakening_names={};awakening_ids={};current=None
for f in raw['character']['fields']:
    match=re.fullmatch(r'\[growtype (\d+)\]',f['tag'])
    if match:current=int(match[1])-1
    if f['tag']=='[awakening name]' and current is not None:awakening_names[current]=f['values']
    if f['tag']=='[awakening skill]' and current is not None and f['values']:awakening_ids[f['values'][0]]=current
ani=sorted(set(raw['ani_paths']));all_ani=set(ani)
body_root='character/swordman/animation/'
# These aliases are reconstructed resource associations, never recovered controllers.
aliases={
 'upperslash':['attack3'], 'hardattack':['hardattack'], 'normalwave':['wave'],
 'tripleslash':['tripleslash1','tripleslash2','tripleslash3'],
 'moonlightslash':['moonlightslash1','moonlightslash2'], 'hopsmash':['hopsmashready','hopsmash'],
 'vaneslash':['vaneslashtry','vaneslash'], 'ashenfork':['jumpattack'],
 'backstep':['jump'], 'backstepcutter':['jumpattack'], 'jumpattackmulti':['jumpattackmultislash1','jumpattackmultislash2'],
 'blache':['blachecast','blachesmash'], 'bloodsword':['bloodswordmake','bloodswordcharge'],
 'bloodyrave':['bloodyraveinhale','bloodyraveslash'], 'chargecrash':['chargecrashdash','chargecrashupper','chargecrashfinish'],
 'chargecrashex':['chargecrashexshoulder','chargecrashexupper','chargecrashexpick'],
 'flowmind':['flowmindstart','flowmindstay'], 'flowmindthree':['flowmindthreeready','flowmindthreeattack'],
 'flowmindtwo':['flowmindtwojump','flowmindtwoattack1','flowmindtwoattack2','flowmindtwolanding'],
 'ghoststepslash':['ghoststepslashready','ghoststepslashmove'], 'hellbenter':['hellbenterfinish'],
 'hundredsword':['hundredswordready','hundredswordmoveready1','hundredswordmoveslash1','hundredswordfinish'],
 'illusionslash':['illusionslash1','illusionslash2','illusionslash3','illusionslash4','illusionslashfinal'],
 'kalla':['kallafinishready','kallafinish1','kallafinish2','kallafinish3'],
 'outragebreak':['outragebreakready','outragebreakslash'],
 'rapidmoveslash':['rapidmoveslashready1','rapidmoveslashmove1','rapidmoveslashready2','rapidmoveslashmove2'],
 'shockwavearea':['shockwaveareacast','shockwaveareasmash'], 'standalonewave':['standalonewaveready','standalonewavebasic','standalonewavestrong'],
 'waveeye':['waveeyecast','waveeyestart','waveeyeattack1','waveeyeattack2','waveeyeattack3','waveeyeclaw','waveeyespear','waveeyewing'],
 'wavespinarea':['wavespinareabomb'], 'weaponcombo':['weaponcomboblade1','weaponcomboblade2','weaponcomboblade3','weaponcomboblade4'],
 'tombstonerainex':['tombstoneex'],
}
# Fixed-order preview effects for already inspected low-level skills.
curated_effects={
 'upperslash':['character/swordman/effect/animation/upperslash1.ani'],
 'hardattack':['character/swordman/effect/animation/hardattack1.ani','character/swordman/effect/animation/hardattack2.ani'],
 'normalwave':['passiveobject/character/swordman/animation/normalwave.ani'],
}
skills=[]
for script in raw['skills']:
    path=script['path'];key=Path(path).stem;skill_id=ids.get(path)
    fit=[n for n in values(script,'[skill fitness growtype]') if isinstance(n,int)]
    second=values(script,'[second growtype maximum level]');grow_max=values(script,'[growtype maximum level]')
    groups=fit[:];basis='[skill fitness growtype]'
    if not groups and skill_id in awakening_ids:groups=[awakening_ids[skill_id]];basis='CHR [awakening skill] exact ID'
    elif not groups and len(second)==2*len(jobs) and any(isinstance(n,(int,float)) and n>0 for n in second):
        groups=sorted({i//2 for i,n in enumerate(second) if isinstance(n,(int,float)) and n>0})
        basis='inferred 2-per-growtype second-level table, cross-checked against CHR awakening IDs'
    active=first(script,'[type]')=='[active]'
    direct=[]
    for t in script['tokens']:
        value=t.get('value')
        if isinstance(value,str) and value.lower().endswith('.ani'):
            for candidate in [value.lower(),str(Path(path).parent/ value).replace('\\','/').lower()]:
                if candidate in all_ani:direct.append(candidate)
    body=[body_root+name+'.ani' for name in aliases.get(key,[key]) if body_root+name+'.ani' in all_ani] if active else []
    # Filename similarity is offered as a candidate list, not composited as a skill.
    stems={key}
    if key.endswith('exp'):stems.add(key[:-3])
    elif key.endswith('ex'):stems.add(key[:-2])
    candidates=[p for p in ani if not p.startswith('equipment/') and not p.startswith(body_root)
                and any(re.sub('[^a-z0-9]','',p.split('/animation/')[-1]).startswith(s) for s in stems)]
    effects=curated_effects.get(key,[])
    effects=[p for p in effects if p in all_ani]
    status='passive' if not active else 'reconstructed_preview' if body or effects else 'candidate_resources' if candidates or direct else 'controller_missing'
    title=first(script,'[name]',first(script,'[name2]',key))
    skills.append({'id':skill_id,'key':key,'name':title,'name2':first(script,'[name2]',''),'source':path,
        'listed':skill_id is not None,'type':first(script,'[type]','unknown'),'groups':groups,'classification_basis':basis,
        'fitness_growtypes':fit,'growtype_maximum_level':grow_max,'second_growtype_maximum_level':second,
        'fitness_second_growtype':values(script,'[skill fitness second growtype]'),
        'required_level':first(script,'[required level]',0),'cooldown_ms':first(script,'[cool time]',0),
        'mp_endpoints':values(script,'[consume MP]'),'icon':values(script,'[icon]'),'command':values(script,'[command]'),
        'status':status,'body_sequence':body,'effects':effects,'direct_ani_references':sorted(set(direct)),
        'candidate_animations':candidates,'controller_confirmed':False,
        'missing':['original controller events, spawn anchors, lifetime, phase conditions and combat formula'],
        'fields':script['fields']})
skills.sort(key=lambda s:(s['id'] is None,s['id'] or 0,s['key']))
catalog={'source_raw':str(source),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
    'list_source':'skill/swordmanskill.lst','character_source':'character/swordman/swordman.chr',
    'jobs':[{'id':i,'name':name,'awakening_names':awakening_names.get(i,[])} for i,name in enumerate(jobs)],
    'skills':skills,'summary':{'total':len(skills),'listed':sum(s['listed'] for s in skills),'active':sum(s['type']=='[active]' for s in skills),
                              'status_counts':dict(collections.Counter(s['status'] for s in skills))},
    'limits':'All source SKL records are catalogued. A source animation preview is not a complete skill simulation. Filename candidates are explicitly unconfirmed.'}
(root/'content/skills.json').write_text(json.dumps(catalog,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps(catalog['summary'],ensure_ascii=False,indent=2))
