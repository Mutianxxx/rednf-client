"""Build a source-bound new-client cache and complete Swordman catalog.

Input is the saved, read-only runtime snapshot, never the old client PVF.
The normalized cache is an intermediate representation, not a native PVF.
"""
from pathlib import Path
import sys, struct, json, hashlib, collections, re, math
ROOT=Path(__file__).resolve().parents[1]
from frozen_pvf import PackedPvf

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
