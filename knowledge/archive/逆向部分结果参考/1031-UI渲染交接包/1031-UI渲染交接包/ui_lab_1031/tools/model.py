"""Evidence model. Frame completeness and instance identity are explicit."""
import copy, json, struct
from preview_diagnostics import issue, diagnostics
from image_contract import context_type

def signed(v):return v-0x100000000 if v>=0x80000000 else v
def floating(v):return struct.unpack('<f',struct.pack('<I',v))[0]

class FrameAssembler:
    def __init__(self):self.pending={};self.completed={};self.rejected=0
    def feed(self,row):
        frame=row.get('frame',0);kind=row.get('event')
        if not frame or kind not in ('control','image','clip_raw','tree_end'):return None
        if frame in self.completed:return None
        if kind=='control' and row.get('flags',0)&0x100:self.pending[frame]=[]
        if frame not in self.pending:return None
        rows=self.pending[frame]
        if kind=='tree_end':
            del self.pending[frame];args=row['args']
            good=args[0]==args[1] and len(rows)==args[2]
            if not good:self.rejected+=1;return None
            result=dict(frame=frame,detailed=bool(row.get('flags',0)&1),rows=rows,end=row)
            self.completed[frame]=result
            while len(self.completed)>32:del self.completed[next(iter(self.completed))]
            return result
        if len(rows)<8192:rows.append(copy.deepcopy(row))
        else:del self.pending[frame];self.rejected+=1
        while len(self.pending)>64:del self.pending[next(iter(self.pending))];self.rejected+=1

class Registry:
    def __init__(self,session):self.session=session;self.objects={};self.seen_revisions=set();self.epochs={}
    def bind(self,row):
        revision=row.get('binding_revision',row.get('span',0));key=(row['object'],revision)
        if key in self.seen_revisions:return
        self.seen_revisions.add(key);pointer=row['object'];old=self.objects.get(pointer)
        # Each observed binding creates a conservative observation generation.
        generation=row.get('observation_generation',self.epochs.get(pointer,0)+1);self.epochs[pointer]=generation
        self.objects[pointer]=dict(id=f'{self.session}:control:{pointer:08x}:{generation}',generation=generation,
            pointer=pointer,vtable=row.get('vtable',0),source=row.get('path'),name=row.get('name'),span=row.get('span'),
            status='bound',lifetime='binding generation; destruction unobserved',binding=copy.deepcopy(row))
    def frame(self,frame):
        present={r['object'] for r in frame['rows'] if r['event']=='control'}
        for pointer,obj in self.objects.items():obj['status']='drawn' if pointer in present else 'absent_from_this_traversal'

def window_view(frame,registry,source=None,span=None):
    """Filter by verified binding or parent ancestry; no time based resource joins."""
    rows=frame['rows'];control_rows={r['object']:r for r in rows if r['event']=='control'}
    direct=set()
    if source:
        for pointer,row in control_rows.items():
            binding=row.get('binding',{})
            if binding.get('path')==source and (span is None or binding.get('span')==span):direct.add(pointer)
    else:direct=set(control_rows)
    owned=set(direct)
    for _ in range(64):
        extra={p for p,r in control_rows.items() if r.get('parent') in owned}
        if extra<=owned:break
        owned|=extra
    controls=[r for r in rows if r['event']=='control' and r['object'] in owned]
    images=[r for r in rows if r['event']=='image' and r.get('parent') in owned]
    clips=[r for r in rows if r['event']=='clip_raw' and r.get('parent') in owned]
    draw_ops=[];issues=[]
    for index,row in enumerate(rows):
        if row['event'] not in ('image','clip_raw') or row.get('parent') not in owned:continue
        control=control_rows[row['parent']];binding=control.get('binding',{})
        operation=copy.deepcopy(row)
        if row['event']=='image':
            destination_type=context_type(row)
            if destination_type is not None:
                operation.setdefault('draw_state',{})['context_type']=destination_type
        operation.update(order=index,source_event=copy.deepcopy(row),instance=dict(pointer=row['parent'],
            generation=binding.get('generation'),binding_revision=binding.get('revision'),span=binding.get('span')),
            traversal_frame=frame['frame'])
        if not binding or binding.get('generation') is None:
            issues.append(issue('runtime_evidence','Operation owner lacks a captured binding generation',order=index,pointer=row['parent']))
        if row['event']=='clip_raw':
            operation['association']='object member write' if row.get('object') else 'missing target ECX in legacy capture'
            if not row.get('object') or not row.get('draw_state',{}).get('consumer_verified'):
                issues.append(issue('unconfirmed_geometry','Rectangle target or consumer unverified; no global clipping stack inferred',order=index,
                    target=row.get('object'),state=row.get('draw_state')))
        elif not row.get('draw_state'):
            issues.append(issue('unconfirmed_geometry','Legacy image request has no drawing-context snapshot',order=index))
        draw_ops.append(operation)
    issues.append(issue('runtime_evidence','Native text, complete lifetime and GPU ownership remain unobserved'))
    missing=['原生文字、字体和字形图集尚未恢复','窗口背景、专用绘制与 ANI 分支可能未覆盖','缺少已验证的完整销毁通知']
    if clips:missing.append('矩形按图像自身已核验上下文应用；旧记录及变换裁剪仍有缺项，不推测全局栈')
    if any(not i.get('flags',0)&1 for i in images):missing.append('部分图像没有通过帧表反向引用校验')
    return dict(source=source,span=span,frame=frame['frame'],controls=controls,images=images,clips=clips,draw_ops=draw_ops,
        preview_diagnostics=diagnostics(issues),
        capability=dict(identified=bool(source),replayable=False,partial_replay=bool(images),independently_rebuildable=False,locally_interactive=False),missing=missing)

class LocalControls:
    """Pure local semantic controls; no IPC, game calls or business actions."""
    def __init__(self,controls):
        self.controls=copy.deepcopy(controls);self.tabs={};self.scroll={};self.pressed=None;self.hover=None;self.clicks=[]
    def move(self,key):self.hover=key
    def press(self,key):self.pressed=key
    def release(self,key):
        if key is not None and key==self.pressed:self.clicks.append(key)
        self.pressed=None
    def select_tab(self,key,index,count):
        if not 0<=index<count:raise ValueError('tab range')
        self.tabs[key]=index
    def wheel(self,key,delta,maximum):self.scroll[key]=max(0,min(maximum,self.scroll.get(key,0)+delta))

def load_bundle(path):
    from pathlib import Path
    p=Path(path).resolve();manifest=json.loads((p/'window.json').read_text('utf8'))
    from common import EXE_HASH,PVF_HASH,digest
    if manifest['exe_sha256']!=EXE_HASH or manifest['pvf_sha256']!=PVF_HASH:raise ValueError('bundle version mismatch')
    for image in manifest.get('assets',{}).values():
        target=(p/image['file']).resolve();target.relative_to(p)
        if digest(target)!=image['png_sha256']:raise ValueError('bundle asset hash mismatch')
    return manifest
