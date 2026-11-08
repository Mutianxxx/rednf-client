"""Retain this client's ANI interpolation chain and reference-project boundaries."""
from pathlib import Path
import hashlib
import json
import sys

ROOT=Path(__file__).resolve().parents[2]
OUT=Path(__file__).resolve().parent/'interpolation'
sys.path[:0]=[str(ROOT/'analysis/deps'),str(ROOT/'analysis'),str(ROOT/'combat-preview')]
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from pvf60 import Pvf60
from executable_source import BACKUP,ORIGINAL_SHA256


def sha(data):return hashlib.sha256(data).hexdigest()


def main():
    raw=BACKUP.read_bytes();assert sha(raw)==ORIGINAL_SHA256
    pe=pefile.PE(data=raw);current=pefile.PE(str(ROOT/'DFO/DFO_fixed_v3.exe'))
    md=Cs(CS_ARCH_X86,CS_MODE_32);OUT.mkdir(parents=True,exist_ok=True)
    targets={'interpolation_parser':(0xA29191,0x1E),'pose_update':(0xA24950,0x260),
             'integer_lerp':(0x473F20,0x29),'float_lerp':(0xB099B0,0x2A),
             'truncate':(0xC01544,0x75),'frame_install':(0xA27870,0x13E),
             'snapshot_copy':(0x66F900,0xC0),'frame_defaults':(0x46E390,0x9F),
             'ani_update':(0xA27F60,0x11E),'frame_advance':(0xA27DC0,0x1A0)}
    slices=[]
    for name,(va,size) in targets.items():
        data=pe.get_data(va-0x400000,size);assert len(data)==size
        assert data==current.get_data(va-0x400000,size)
        (OUT/(name+'.bin')).write_bytes(data)
        (OUT/(name+'.asm')).write_text('\n'.join(
            f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}'
            for i in md.disasm(data,va))+'\n',encoding='utf-8')
        slices.append(dict(name=name,va=hex(va),size=size,file_offset=pe.get_offset_from_rva(va-0x400000),
                           sha256=sha(data),selected_disk_bytes_equal=True))
    pvf=Pvf60(ROOT/'DFO/Script.pvf');pvf_sha=sha(pvf.data)
    samples=[]
    for path in ['character/swordman/effect/animation/soulbringer1.ani',
                 'passiveobject/monster/goblin/animation/flybomb.ani']:
        data=pvf.read(path);(OUT/Path(path).name).write_bytes(data)
        samples.append(dict(path=path,entry=pvf.by_path[path],sha256=sha(data),
                            archive_sha256=pvf_sha,encoding='cp949',crc_verified=True))
    rea=[]
    for path in sorted(OUT.glob('00*.json')):
        obj=json.loads(path.read_text(encoding='utf-8'))
        if obj.get('structuredContent'):ev=obj['structuredContent']
        else:
            ev=next((json.loads(block['text']) for block in obj.get('content',[]) if block['type']=='text'),{})
        if ev.get('evidence_id'):
            rea.append(dict(file=path.name,evidence_id=ev['evidence_id'],operation=ev.get('operation'),
                            parameters=ev.get('parameters'),limitations=ev.get('limitations')))
    refs=[]
    for path in [Path('D:/dnf-rebuild/rep-player-1031-pvf/src/pvf_script_preview.cpp'),
                 Path('D:/dnf-rebuild/rep-player-1031-pvf/src/pvf_preview_scene.cpp'),
                 Path('D:/dnf-rebuild/逆向部分结果参考/1031-UI渲染交接包/1031-UI渲染交接包/monster_demo/src/resources.cpp')]:
        data=path.read_bytes()
        refs.append(dict(path=str(path),sha256=sha(data),role='read-only clue; different client version; not behavioral authority'))
    result=dict(source_path=str(BACKUP),source_sha256=ORIGINAL_SHA256,slices=slices,pvf_samples=samples,rea=rea,
        references=refs,fields={'keyframe_interpolation':'frame+0x20','current_snapshot':'ANI+0xa8',
            'current_flag':'ANI+0xc8','current_index':'ANI+0x124','start_deadline':'ANI+0x128',
            'next_deadline':'ANI+0x12c','loop':'ANI+0x130','ended':'ANI+0x13a'},
        contract={'elapsed':'selected ANI clock - frame start deadline',
            'duration':'next deadline - start deadline',
            'float':'t>=duration ? target : t<=0 ? source : source+(target-source)*t/duration',
            'integer':'truncate entire float-helper result toward zero',
            'position':'integer helper per axis','rate':'float helper then float32 memory write',
            'rotation':'direct numeric interpolation then float32 memory write; no shortest-angle normalization',
            'rgba':'integer helper per byte, repack low 8 bits',
            'retained_discrete':['image pointer/frame index','graphic effect','collision boxes'],
            'final_frame':'nonloop stays unchanged; loop targets frame0',
            'update_guards':['current interpolation enabled','not ended','nonempty frame vector']},
        limitations=['Local algorithm recovered from original instructions; this is not an actual DFO runtime draw trace.',
                     'Preview supplies source-DELAY rate-100 clock; character rate, pause and real skill scheduling remain unbound.',
                     'Synthetic PE32 validates the updater and helpers, not parser execution or original-game pixel equality.'])
    (OUT/'evidence-index.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(dict(native_slices=len(slices),rea_results=len(rea),samples=len(samples))))


if __name__=='__main__':main()
