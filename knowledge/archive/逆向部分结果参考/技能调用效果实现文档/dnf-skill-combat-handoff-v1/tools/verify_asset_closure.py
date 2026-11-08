"""Check every statically reachable image frame of the packaged current flows.
This checks identity/ranges, not visual equivalence with all original skills.
"""
from pathlib import Path
import json, posixpath, struct

def verify(root):
    demo=root/'demo';load=lambda p:json.loads(p.read_text('utf8'))
    index=load(demo/'content/cache/index.json');profile=load(demo/'content/profile.json')
    assets=load(demo/'client-assets/asset-manifest.json');members={e['logical_path']:e for e in assets['members']}
    data=(demo/'content/cache/resources.bin').read_bytes();parsed={};images={};errors=[];refs=set()
    def ani(path):
        if path not in parsed:
            e=index['entries'][path];parsed[path]=json.loads(data[e['offset']:e['offset']+e['size']])
        return parsed[path]
    def check(image,frame,source):
        if not image:return
        image=posixpath.normpath(image.replace('\\','/')).lower()
        image=profile['image_substitutions'].get(image,image).replace('%04d','0000').replace('%02d','00')
        if image not in members:errors.append(dict(source=source,missing_image=image));return
        if image not in images:
            e=members[image]
            with (demo/'client-assets'/e['archive']).open('rb') as f:
                f.seek(e['offset']);head=f.read(32)
            version,count=struct.unpack_from('<ii',head,24);images[image]=dict(version=version,count=count)
        if not 0<=frame<images[image]['count']:errors.append(dict(source=source,image=image,frame=frame,count=images[image]['count']))
        refs.add((image,frame))
    roots=assets['animation_roots']
    for path in roots['effects']:
        for f in ani(path)['frames']:check(f['image'],f['imageFrame'],path)
    for path in roots['body']:
        frames=ani(path)['frames'];wp='equipment/character/swordman/weapon/katana/katana/'+posixpath.basename(path)
        for layer in profile['body_layers']:
            motion=wp if layer['motion']=='katana' and wp in index['entries'] else path
            m=ani(motion)['frames']
            for n,f in enumerate(frames):
                chosen=m[min(n,len(m)-1)]
                if chosen['image']:check(layer['image'],chosen['imageFrame'],path+' / '+motion)
    for image in ['monster/common/m0001.img','monster/common/m0009.img']:
        for frame in range(4):check(image,frame,'shared death particles')
    check('monster/common/monsterdiesmoke.img',0,'shared death smoke')
    return dict(passed=not errors,animations=len(parsed),logical_images=len(images),unique_image_frames=len(refs),errors=errors,
        scope='All ANI frames of packaged current body/effect roots, all appearance layer frame mappings, shared death frames. Does not validate visual equivalence or unsupported source semantics.')

if __name__=='__main__':
    root=Path(__file__).resolve().parents[1];r=verify(root)
    p=root/'demo/reports/asset-closure.json';p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(r,ensure_ascii=False,indent=2),encoding='utf8')
    print(json.dumps(r,ensure_ascii=False,indent=2));raise SystemExit(0 if r['passed'] else 1)
