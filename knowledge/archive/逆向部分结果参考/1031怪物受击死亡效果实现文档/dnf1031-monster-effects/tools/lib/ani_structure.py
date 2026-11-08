"""1031 structural ANI decoder; see README for semantic limits.
Source: combat_ui_1031/tools/catalog.py, animation().
Adapted there from attack_demo/src/resources.cpp; no enum proof implied.
"""
import struct

def animation(data):
    at=0
    def get(fmt):
        nonlocal at
        size=struct.calcsize('<'+fmt)
        if at+size>len(data):raise ValueError(f'ANI overrun at {at}')
        value=struct.unpack_from('<'+fmt,data,at);at+=size
        return value[0] if len(value)==1 else list(value)
    def text():
        nonlocal at
        n=get('i')
        if not 0<=n<=1048576 or at+n>len(data):raise ValueError('ANI string extent')
        value=data[at:at+n];at+=n
        return value.rstrip(b'\0').decode('gbk',errors='strict')
    def prop(k,global_):
        if k in (0,1,10):return get('B')
        if k in (3,13,24,28):return get('H')
        if k==7:return get('ff')
        if k==8:return get('f')
        if k==9:return get('BBBB')
        if k==11:
            effect=get('H');out={'effect_raw':effect}
            if effect==5:out['rgb']=get('BBB')
            elif effect==6:out['position']=get('hh')
            elif effect>6:raise ValueError('Unsupported graphic effect')
            return out
        if k in (12,23,26):return get('i')
        if k==16:return text()
        if k in (17,25):return True
        if k==27:return get('hhhh')
        if k==18 and global_:return dict(flag=get('B'),term=get('i'),life=get('i'),rgba=get('BBBB'),effect=get('H'))
        raise ValueError(f'Unsupported ANI node {k} at {at}')
    count,names_count=get('HH');names=[text() for _ in range(names_count)]
    globals_=[]
    for _ in range(get('H')):
        k=get('H');globals_.append(dict(node=k,value=prop(k,True)))
    frames=[]
    for number in range(count):
        begin=at;boxes=[]
        for _ in range(get('H')):
            kind=get('H');values=get('iiiiii');boxes.append(dict(type_raw=kind,coordinates_raw=values))
        image=get('h');image_frame=None
        if image>=0:
            image_frame=get('H')
            if image>=len(names):raise ValueError('ANI image index')
        x,y=get('ii');properties=[]
        for _ in range(get('H')):
            k=get('H');properties.append(dict(node=k,value=prop(k,False)))
        frames.append(dict(frame=number,offset=begin,boxes=boxes,image=names[image] if image>=0 else None,image_frame=image_frame,x=x,y=y,properties=properties))
    if at!=len(data):raise ValueError(f'ANI trailing bytes: {len(data)-at}')
    return dict(frame_count=count,image_names=names,globals=globals_,frames=frames,consumed_bytes=at,
                interpretation='Structure adapted from attack_demo/src/resources.cpp and checked for exact consumption. Node meanings and box types require native 1031 validation; type 14/15 are only local decoder candidates.')
