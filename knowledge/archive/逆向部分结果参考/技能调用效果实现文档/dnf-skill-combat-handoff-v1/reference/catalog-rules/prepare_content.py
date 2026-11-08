"""Build a source-bound new-client cache and complete Swordman catalog.

Input is the saved, read-only runtime snapshot, never the old client PVF.
The normalized cache is an intermediate representation, not a native PVF.
"""
from pathlib import Path
import sys, struct, json, hashlib, collections, re, math
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT.parent/'reverse_lab/v2/tools'))
from packed_pvf import PackedPvf

def dump(path,obj):
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(json.dumps(obj,ensure_ascii=False,separators=(',',':')),encoding='utf8')

def script(p,path):
    raw=p.read(path)
    if len(raw)%5:raise ValueError(f'Not packed token5: {path}')
    fields=[];tokens=[]
    for off in range(0,len(raw),5):
        typ,val=struct.unpack_from('<BI',raw,off)
        if typ==0:v=struct.unpack('<i',struct.pack('<I',val))[0]
        elif typ==2:
            v=struct.unpack('<f',struct.pack('<I',val))[0]
            if not math.isfinite(v):raise ValueError('Nonfinite packed float')
        elif typ in (3,5,6,7,8,10):v=p.string(val)
        else:raise ValueError(f'Unknown token {typ} in {path} at {off}')
        tokens.append(dict(offset=off,type=typ,raw=val,value=v))
        if typ==3:fields.append(dict(tag=v,values=[],offset=off))
        elif fields:fields[-1]['values'].append(v)
    return dict(path=path,fields=fields,tokens=tokens,raw_sha256=hashlib.sha256(raw).hexdigest())

def values(s,tag):return next((f['values'] for f in s['fields'] if f['tag']==tag),[])
def first(s,tag,default=None):
    v=values(s,tag);return v[0] if v else default

def animation(s,tag_stats):
    out=dict(format='dnf-normalized-ani-v3',globals={},frames=[],source_fields=s['fields'])
    frame=None;expected=None
    # Node names are read directly from this client's token ANI, rather than
    # assigning unverified binary offsets to the new format.
    def props():return frame['properties'] if frame is not None else out['globals']
    for f in s['fields']:
        tag,v=f['tag'],f['values'];tag_stats[tag]+=1
        if tag=='[FRAME MAX]':expected=v[0]
        elif re.fullmatch(r'\[FRAME\d+\]',tag):
            frame=dict(image='',imageFrame=0,x=0,y=0,duration=50,boxes=[],properties={})
            out['frames'].append(frame)
        elif tag=='[IMAGE]' and frame is not None:
            frame['image'],frame['imageFrame']=v
        elif tag=='[IMAGE POS]' and frame is not None:frame['x'],frame['y']=v
        elif tag=='[DELAY]':
            props()['12']=v[0]
            if frame is not None:frame['duration']=v[0]
        elif tag in ('[ATTACK BOX]','[DAMAGE BOX]') and frame is not None:
            assert len(v)==6
            frame['boxes'].append(dict(zip(('type','x','y','z','w','h','d'),[15 if tag=='[ATTACK BOX]' else 14]+v)))
        elif tag=='[LOOP]':props()['0']=bool(v[0])
        elif tag=='[SHADOW]':props()['shadow']=v
        elif tag in ('[INTERPOLATION]','[INTERPOLATION IN FRAME]'):props()['10']=bool(v[0])
        elif tag=='[RGBA]':props()['9']=v
        elif tag=='[GRAPHIC EFFECT]':
            modes={'NORMAL':0,'NONE':0,'LINEARDODGE':1,'ADDITIVE':2,'MULTIPLY':3,'SCREEN':4}
            mode=modes.get(v[0],-1)
            if mode in (0,1,2):props()['11']={'effect':mode}
            else:props().setdefault('unconsumed',[]).append(f)
        elif tag=='[IMAGE RATE]':props()['7']=v
        elif tag=='[IMAGE ROTATE]':props()['8']=v[0]
        elif tag=='[FLIP TYPE]' and v[0] in ('HORIZON','VERTICAL','ALL'):props()['24']={'HORIZON':1,'VERTICAL':2,'ALL':3}[v[0]]
        elif tag=='[DAMAGE TYPE]':pass # combat metadata retained in source_fields
        else:props().setdefault('unconsumed',[]).append(f)
    if expected!=len(out['frames']):raise ValueError(f'Frame count {s["path"]}: {expected} vs {len(out["frames"])}')
    for f in out['frames']:
        if f['duration']<0:raise ValueError('Negative delay')
        if '12' not in f['properties']:f['duration']=out['globals'].get('12',50)
    return out

def main():
    p=PackedPvf(); paths=sorted(k for k in p.entries if
        k.startswith(('character/swordman/','passiveobject/character/swordman/')) or
        k.startswith('equipment/character/swordman/') and k.endswith(('.ani','.als')) or
        k.startswith('skill/swordman/') or k=='skill/swordmanskill.lst')
    # Unrelated equipment item definitions are not exported.
    paths=[k for k in paths if k.endswith(('.ani','.als','.act','.obj','.chr','.skl','.lst','.atk'))]
    print(f'Decoding {len(paths)} resources',flush=True)
    cache=ROOT/'content/cache';cache.mkdir(parents=True,exist_ok=True)
    string_ids={};strings=[];entries={};tag_stats=collections.Counter();scripts={};errors=[]
    def intern(s):
        if s not in string_ids:string_ids[s]=len(strings);strings.append(s)
        return string_ids[s]
    with (cache/'resources.bin').open('wb') as output:
        for index,path in enumerate(paths):
            try:
                s=script(p,path)
                if path.endswith('.ani'):data=json.dumps(animation(s,tag_stats),ensure_ascii=False,separators=(',',':')).encode('utf8')
                else:
                    data=bytearray(b'\xb0\xd0')
                    for t in s['tokens']:
                        typ=t['type'];value=t['value']
                        if typ==0:nt,nv=2,t['raw']
                        elif typ==2:nt,nv=4,t['raw']
                        else:nt,nv=(5 if typ==3 else 6),intern(value)
                        data.extend(struct.pack('<BI',nt,nv))
                entries[path]=dict(offset=output.tell(),size=len(data),raw_sha256=s['raw_sha256'],record=p.entries[path]['record'])
                output.write(data)
                if path.startswith('skill/') or path.endswith('swordman.chr'):scripts[path]=s
            except Exception as e:errors.append(dict(path=path,error=str(e)))
            if index%2000==0:print(index,flush=True)
    provenance=dict(format='dnf-source-cache-v3',snapshot=str(p.source.relative_to(ROOT.parent)),
        snapshot_sha256=hashlib.sha256((p.source/'snapshot.json').read_bytes()).hexdigest(),
        client_exe_sha256='1f8244d3f7309bbe2fde4299e1863a894f6b28d5707bf01732980585b20b00dd',
        pvf_sha256='1cd52a54358738dbfea309f15ee861386f0b32e30f59e58fb4c41d73b911314a',
        entries=entries,strings=strings,normalization='packed token5 decoded; ANI JSON retains source field order, repeats, original offsets and raw SHA256')
    dump(cache/'index.json',provenance)
    dump(ROOT/'reports/decode.json',dict(exported=len(entries),failed=errors,chunk_modes=p.chunk_modes,ani_tags=tag_stats))
    ani=sorted(k for k in entries if k.endswith('.ani'))
    raw=dict(skills=[v for k,v in scripts.items() if k.endswith('.skl')],
             list=scripts['skill/swordmanskill.lst'],character=scripts['character/swordman/swordman.chr'],ani_paths=ani)
    dump(ROOT/'content/catalog-raw.json',raw)
    # Reuse only the transparent association rules, never old source content.
    import runpy
    runpy.run_path(str(ROOT/'tools/build_catalog.py'),run_name='__main__')
    print('cache bytes', (cache/'resources.bin').stat().st_size,'errors',len(errors),flush=True)

if __name__=='__main__':main()
