"""Resource based Qt preview. No screenshots and no game function calls."""
import json, math, posixpath, shutil, time
from pathlib import Path
from PySide6 import QtCore as C, QtGui as G, QtWidgets as W
from common import ROOT, EXE_HASH, PVF_HASH, digest
from model import signed, floating
from preview_layout import board_frames, radio_entries, sample_animation
from board_layout import board_layout
from preview_diagnostics import issue, diagnostics
from native_geometry import image_affine, signed_word
from image_contract import context_type, unsupported_image_reason, EVIDENCE as IMAGE_CONTRACT_EVIDENCE

def asset_key(path,frame):return path.replace('\\','/').lower()+':'+str(int(frame))
def animation_key(path):return 'ani:'+path.replace('\\','/').lower()

class AssetThread(C.QThread):
    result=C.Signal(str,dict);error=C.Signal(str,str)
    def __init__(self):
        super().__init__();import queue
        self.queue=queue.Queue();self.requested=set();self.stopping=False;self.source_overrides={}
    def ask(self,path,frame,archive=None,force=False):
        key=asset_key(path,frame)
        logical=path.replace('\\','/').lower()
        if logical.startswith('sprite/'):logical=logical[7:]
        archive=archive or self.source_overrides.get(logical)
        request=(key,archive or '')
        if force or request not in self.requested:self.requested.add(request);self.queue.put((path,frame,archive))
    def ask_animation(self,path):
        key=animation_key(path)
        request=(key,'')
        if request not in self.requested:self.requested.add(request);self.queue.put((path,None,None))
    def run(self):
        from assets import Assets
        service=None
        try:
            while not self.stopping:
                job=self.queue.get()
                if job is None:break
                path,frame,archive=job;key=animation_key(path) if frame is None else asset_key(path,frame)
                try:
                    if service is None:service=Assets()
                    result=service.animation(path) if frame is None else service.image(path,frame,archive)
                    logical=path.replace('\\','/').lower()
                    if logical.startswith('sprite/'):logical=logical[7:]
                    if frame is None or self.source_overrides.get(logical,archive)==archive:self.result.emit(key,result)
                except Exception as exc:
                    logical=path.replace('\\','/').lower()
                    if logical.startswith('sprite/'):logical=logical[7:]
                    if frame is None or self.source_overrides.get(logical,archive)==archive:self.error.emit(key,str(exc))
        finally:
            if service:service.close()
    def stop(self):self.stopping=True;self.queue.put(None)

class SpriteItem(W.QGraphicsPixmapItem):
    def __init__(self,pixmap,frames,owner,group,click=None):
        super().__init__(pixmap);self.frames=frames;self.owner=owner;self.group=group;self.click=click;self.blend=0;self.scene_clip=None
        self.setAcceptHoverEvents(bool(frames));self.setAcceptedMouseButtons(C.Qt.LeftButton if frames or click else C.Qt.NoButton)
    def switch(self,index):
        if index<len(self.frames):
            data=self.owner.assets.get(self.frames[index])
            if data:self.setPixmap(G.QPixmap(data['png']));self.setOffset(data['x'],data['y'])
    def paint(self,painter,option,widget=None):
        painter.save()
        if self.scene_clip is not None:
            inverse,valid=self.sceneTransform().inverted()
            if valid:painter.setClipPath(inverse.map(self.scene_clip),C.Qt.IntersectClip)
            else:painter.setClipRect(C.QRectF())
        if self.blend in (1,2):painter.setCompositionMode(G.QPainter.CompositionMode_Plus)
        super().paint(painter,option,widget);painter.restore()
    def hoverEnterEvent(self,e):self.switch(1)
    def hoverLeaveEvent(self,e):self.switch(0)
    def mousePressEvent(self,e):self.switch(2);self.owner.interaction('本地按下 '+self.group);e.accept()
    def mouseReleaseEvent(self,e):
        self.switch(1)
        if self.click:self.click()
        self.owner.interaction('本地点击 '+self.group+'（无业务调用）');e.accept()

class Canvas(W.QGraphicsView):
    changed=C.Signal(str)
    diagnostics_changed=C.Signal(dict)
    def __init__(self,worker=None):
        super().__init__();self.setScene(W.QGraphicsScene(self));self.setBackgroundBrush(G.QColor('#20242c'))
        self.setRenderHint(G.QPainter.Antialiasing);self.setAlignment(C.Qt.AlignLeft|C.Qt.AlignTop)
        self.worker=worker;self.assets={};self.failures={};self.view_data={};self.definitions=[];self.local=False;self.used_keys=set()
        self.setSceneRect(0,0,800,600);self.rebuild_pending=False;self.bundle_root=None;self.tab_values={};self.scroll_values={}
        self.animations={};self.animation_items=[];self.used_animations=set();self.animation_loop=False;self.animation_started=time.monotonic();self.show_gaps=False;self.issues=[];self.tint_cache={}
        self.animation_timer=C.QTimer(self);self.animation_timer.setInterval(40);self.animation_timer.timeout.connect(self.animate)
        if worker:worker.result.connect(self.asset_result);worker.error.connect(self.asset_error)
    def interaction(self,message):self.changed.emit(message)
    def asset_result(self,key,data):
        self.failures.pop(key,None)
        if key.startswith('ani:'):self.animations[key]=data
        else:self.assets[key]=data
        self.schedule()
    def asset_error(self,key,error):self.failures[key]=error;self.changed.emit('资源缺项：'+error);self.schedule()
    def schedule(self):
        if self.rebuild_pending:return
        self.rebuild_pending=True;C.QTimer.singleShot(100,self.rebuild)
    def find(self,path,frame):
        key=asset_key(path,frame)
        self.used_keys.add(key)
        resolution=self.assets.get(key,{}).get('source_resolution',{})
        if resolution.get('status')=='explicit-conflict-choice' and not any(row.get('key')==key and row.get('category')=='resource_ambiguity' for row in self.issues):
            self.issues.append(issue('resource_ambiguity','Explicit physical NPK candidate selected for preview; native archive priority remains unconfirmed',key=key,selected_archive=resolution.get('selected_archive'),candidates=resolution.get('candidates',[])))
        if key not in self.assets and key not in self.failures and self.worker:self.worker.ask(path,frame)
        return self.assets.get(key)
    def set_data(self,view,definitions=None,local=False):
        if view.get('source')!=self.view_data.get('source'):self.animation_started=time.monotonic()
        self.view_data=view;self.definitions=definitions or [];self.local=local;self.rebuild()
    def sprite(self,path,frame,x,y,frames=None,group='',transform=None,click=None,native=False,native_state=None):
        if frame<0:
            self.issues.append(issue('unknown_state','Absent IMG frame',path=path,frame=frame));return
        data=self.find(path,frame)
        if not data:return
        keys=[]
        for f in frames or []:
            self.find(path,f);keys.append(asset_key(path,f))
        item=SpriteItem(G.QPixmap(data['png']),keys if self.local else [],self,group,click if self.local else None)
        item.setOffset(data['x'],data['y'])
        if native and native_state and 'image_crop' in native_state:item.setOffset(*native_state['image_crop'])
        if transform:
            sx,sy,rotation,color,cx,cy=transform
            if not all(math.isfinite(value) for value in (sx,sy,rotation,cx,cy)) or abs(sx)>32 or abs(sy)>32:
                self.issues.append(issue('unconfirmed_geometry','Nonfinite or out-of-preview-bound transform',path=path));return
            if native:
                dimensions=(native_state or {}).get('image_dimensions',[data['logical_width'],data['logical_height']])
                try:item.setTransform(G.QTransform(*image_affine(sx,sy,rotation,cx,cy,*dimensions)))
                except ValueError as exc:self.issues.append(issue('unconfirmed_geometry',str(exc),path=path));return
                rgb=(color&255,(color>>8)&255,(color>>16)&255)
                if rgb!=(255,255,255):
                    from PIL import Image,ImageChops
                    with Image.open(data['png']) as pixels:
                        tinted=ImageChops.multiply(pixels.convert('RGBA'),Image.new('RGBA',pixels.size,(*rgb,255)))
                    raw=tinted.tobytes();item.setPixmap(G.QPixmap.fromImage(G.QImage(raw,tinted.width,tinted.height,G.QImage.Format_RGBA8888).copy()))
            else:
                item.setTransformOriginPoint(cx,cy);item.setTransform(G.QTransform().scale(sx,sy));item.setRotation(rotation*180/math.pi)
            item.setOpacity(((color>>24)&255)/255)
        item.setPos(x,y);item.setData(0,group);self.scene().addItem(item);return item
    def rebuild(self):
        # Qt can emit state changes while embedded widgets are being destroyed.
        # Those callbacks must not schedule work against a half-cleared scene.
        for item in self.scene().items():
            if isinstance(item,W.QGraphicsProxyWidget) and item.widget():item.widget().blockSignals(True)
        self.rebuild_pending=False;self.animation_timer.stop();self.animation_items=[];self.scene().clear();self.used_keys=set();self.used_animations=set();self.issues=[]
        self.issues=copy_issues=json.loads(json.dumps(self.view_data.get('base_diagnostics',self.view_data.get('preview_diagnostics',{})).get('issues',[])))
        if 'base_diagnostics' not in self.view_data:self.view_data['base_diagnostics']=dict(issues=copy_issues[:],support=self.view_data.get('preview_diagnostics',{}).get('support','partial captured requests'))
        if self.view_data.get('mode') in ('static','config'):
            self.view_data['board_previews']={};self.draw_static()
        if self.view_data.get('mode')=='config':
            for operation in self.view_data.get('draw_ops',[]):
                if operation['event']=='config_image':
                    item=self.sprite(operation['path'],operation['frame'],operation['x'],operation['y'],group=operation['instance'])
                    if item:item.setZValue(operation['order'])
            self.text('配置示意 · 手动选择 · 原生可见项和业务状态待验证',5,-58)
        elif self.view_data.get('mode')!='static':
            operations=self.view_data.get('draw_ops',self.view_data.get('images',[]))
            for order,image in enumerate(operations):
                if image.get('event','image')!='image':continue
                if not image.get('flags',0)&1:
                    self.issues.append(issue('unknown_structure','IMG frame-vector back reference was not verified',order=order));continue
                a=image['args'];transform=None;state=dict(image.get('draw_state',{}))
                destination_type=context_type(image)
                if destination_type is not None:state['context_type']=destination_type
                verified=state.get('image_vtable')==0x185c76c and state.get('image_type')==7 and state.get('consumer_verified') is True and state.get('context_type') in (None,7)
                if state and not verified:
                    self.issues.append(issue('unknown_structure',unsupported_image_reason(state,image['site']),order=order,state=state,evidence=IMAGE_CONTRACT_EVIDENCE));continue
                if verified and state.get('context_type') is None:
                    self.issues.append(issue('runtime_evidence','Destination context type absent; legacy partial replay retained without confirming the destination consumer',order=order))
                if image['site']==8:
                    transform=(floating(a[3]),floating(a[4]),floating(a[5]),a[6],floating(a[7]),floating(a[8]))
                    if not verified:
                        self.issues.append(issue('unconfirmed_geometry','Transformed image consumer not verified in this capture',order=order))
                        if state:continue
                        if max(abs(transform[4]),abs(transform[5]))>4096:
                            self.issues.append(issue('unconfirmed_geometry','Legacy capture lacks dimensions for special center',order=order));continue
                item=self.sprite(image['path'],a[12],signed(a[0]),signed(a[1]),group=str(image['parent']),transform=transform,native=verified,native_state=state)
                if item:
                    item.setZValue(order)
                    rectangle=state.get('rectangle_words')
                    if verified and rectangle and (transform is None or transform[:3]==(1.0,1.0,0.0)):
                        left,top,right,bottom=map(signed_word,rectangle)
                        clip=G.QPainterPath()
                        if right>left and bottom>top:clip.addRect(C.QRectF(left,top,right-left,bottom-top))
                        item.scene_clip=clip
                    elif rectangle:self.issues.append(issue('unconfirmed_geometry','Transformed clipping consumer remains unconfirmed',order=order,rectangle=rectangle))
            if self.local:self.draw_live_controls()
        bounds=self.scene().itemsBoundingRect();self.scene().setSceneRect(bounds.united(C.QRectF(0,0,800,600)).adjusted(-15,-15,15,15))
        if self.animation_items:self.animate();self.animation_timer.start()
        for key in self.used_keys|self.used_animations:
            if key in self.failures:self.issues.append(issue('resource_ambiguity' if 'ambig' in self.failures[key].lower() else 'missing_resource',self.failures[key],key=key))
        self.view_data['preview_diagnostics']=diagnostics(self.issues,support=self.view_data['base_diagnostics'].get('support','partial captured requests'),native_visual_acceptance='pending',failed_resources={k:v for k,v in self.failures.items() if k in self.used_keys or k in self.used_animations},
                pending_resources=sorted(self.used_keys-set(self.assets)-set(self.failures)),pending_animations=sorted(self.used_animations-set(self.animations)-set(self.failures)),
                animation_playback='external timer; one shot unless loop preview enabled',render_contract='resource reconstruction; confirmed native geometry only when consumer_verified; native visual acceptance pending')
        self.diagnostics_changed.emit(self.view_data)
    def text(self,text,x,y,width=None,color='#eeeeee'):
        item=self.scene().addText(text.replace('\\n','\n'),G.QFont('Microsoft YaHei UI',9));item.document().setDocumentMargin(0)
        item.setDefaultTextColor(G.QColor(color));item.setPos(x,y)
        if width is not None and 0<width<=4096:item.setTextWidth(width)
        return item
    def gap(self,control,reason,category='unknown_structure'):
        self.issues.append(issue(category,reason,key=control['key'],type=control['type'],name=control['name']))
        if self.show_gaps:
            item=self.scene().addRect(0,0,80,15,G.QPen(G.QColor('#f9ad54'),1,C.Qt.DashLine));item.setPos(control['absolute_x'],control['absolute_y']);item.setToolTip(control['name']+' '+reason);item.setZValue(10000)
    def board(self,control,image):
        width,height,frames=board_frames(control)
        previews=self.view_data.setdefault('board_previews',{})
        previews[control['key']]=dict(status='waiting for all nine image objects',raw_parameters=control['parameters'][:],raw_strings=control['strings'][:])
        data=[self.find(image,f) for f in frames]
        if not all(data):
            missing=[dict(frame=frame,key=asset_key(image,frame),reason=self.failures.get(asset_key(image,frame),'pending decode')) for frame,resource in zip(frames,data) if not resource]
            previews[control['key']].update(status='missing or pending images; native board not partially drawn',missing_images=missing)
            return
        try:layout=board_layout(control,data)
        except ValueError as exc:
            previews[control['key']].update(status='preview refused',reason=str(exc));raise
        previews[control['key']]=layout
        if not layout['draw_ops']:return
        left,top,right,bottom=layout['pixel_bounds']
        pix=G.QPixmap(right-left,bottom-top);pix.fill(C.Qt.transparent);painter=G.QPainter(pix)
        sprites=[G.QPixmap(resource['png']) for resource in data]
        try:
            for operation in layout['draw_ops']:
                resource=data[operation['slot']]
                painter.save();painter.translate(operation['x']-left,operation['y']-top);painter.scale(operation['scale_x'],operation['scale_y'])
                painter.drawPixmap(resource['x'],resource['y'],sprites[operation['slot']]);painter.restore()
        finally:painter.end()
        item=self.scene().addPixmap(pix);item.setPos(control['absolute_x'],control['absolute_y'])
        item.setOffset(left-control['absolute_x'],top-control['absolute_y']);item.setData(0,control['key'])
    def add_animation(self,control,path):
        key=animation_key(path);self.used_animations.add(key);data=self.animations.get(key)
        if not data:
            if key not in self.failures and self.worker:self.worker.ask_animation(path)
            return
        for f in data['frames']:
            pose=f['pose']
            if pose['image']:self.find(pose['image'],pose['image_frame'])
        item=SpriteItem(G.QPixmap(),[],self,control['key']);self.scene().addItem(item)
        self.animation_items.append((item,control,data))
        unknown=[f['pose']['unsupported'] for f in data['frames'] if f['pose'].get('unsupported')]
        if unknown:self.gap(control,'ANI contains unimplemented controls; see exported frame properties')
        if any(f['pose'].get('blend',0) not in (0,1,2) for f in data['frames']):self.gap(control,'ANI blend mode not implemented')
    def animate(self):
        ms=(time.monotonic()-self.animation_started)*1000
        for item,c,animation in self.animation_items:
            pose=sample_animation(animation,ms,self.animation_loop)
            if not pose or not pose['image']:item.setVisible(False);continue
            data=self.assets.get(asset_key(pose['image'],pose['image_frame']))
            if not data:item.setVisible(False);continue
            sx=pose['scale_x']*(-1 if pose['flip']&1 else 1);sy=pose['scale_y']*(-1 if pose['flip']&2 else 1)
            if not all(math.isfinite(v) for v in (sx,sy,pose['rotation'],pose['x'],pose['y'])) or max(abs(sx),abs(sy))>32:item.setVisible(False);continue
            rgb=tuple(max(0,min(255,round(v))) for v in pose['rgba'][:3]);tint=(data['png'],rgb)
            pix=self.tint_cache.get(tint)
            if pix is None:
                pix=G.QPixmap(data['png'])
                if rgb!=(255,255,255):
                    img=pix.toImage().convertToFormat(G.QImage.Format_RGBA8888);from PIL import Image,ImageChops
                    source=Image.frombytes('RGBA',(img.width(),img.height()),bytes(img.constBits()))
                    tinted=ImageChops.multiply(source,Image.new('RGBA',source.size,(*rgb,255)));raw=tinted.tobytes()
                    pix=G.QPixmap.fromImage(G.QImage(raw,img.width(),img.height(),G.QImage.Format_RGBA8888).copy())
                if len(self.tint_cache)>128:self.tint_cache.clear()
                self.tint_cache[tint]=pix
            item.setVisible(True);item.setPixmap(pix);item.setOffset(data['x'],data['y']);item.setTransform(G.QTransform().rotate(pose['rotation']*180/math.pi).scale(sx,sy))
            item.setPos(c['absolute_x']+pose['x'],c['absolute_y']+pose['y']);item.setOpacity(max(0,min(1,pose['rgba'][3]/255)));item.blend=pose['blend'];item.update()
    def replay_animations(self):self.animation_started=time.monotonic();self.animate()
    def button(self,label,x,y,width,key):
        button=W.QPushButton(label);button.setFixedSize(max(30,min(width,500)),24)
        button.clicked.connect(lambda:self.interaction('本地点击 '+key+'（不执行游戏业务）'))
        proxy=self.scene().addWidget(button);proxy.setPos(x,y);proxy.setData(0,key);return proxy
    def tabs(self,labels,x,y,key):
        tabs=W.QTabBar();tabs.setObjectName(key);tabs.setExpanding(False)
        for label in labels:tabs.addTab(label)
        tabs.setCurrentIndex(self.tab_values.get(key,0))
        def changed(index):
            self.tab_values[key]=index;self.interaction('本地页签 '+key+' = '+str(index));self.schedule()
        tabs.currentChanged.connect(changed)
        proxy=self.scene().addWidget(tabs);proxy.setPos(x,y);proxy.setData(0,key);return tabs
    def draw_static(self):
        # This view is explicitly a PVF layout candidate, not a captured native window.
        for c in self.view_data.get('static_controls',[]):
            if c['type'].lower()=='[radiobutton]':
                try:self.tab_values.setdefault(c['key'],radio_entries(c)[1])
                except ValueError:pass
        for control in self.view_data.get('static_controls',[]):
            if any(self.tab_values.get(key,0)!=index for key,index in control.get('conditions',[])):continue
            kind=control['type'].lower();ss=control['strings'];p=control['parameters'];x=control['absolute_x'];y=control['absolute_y'];key=control['key']
            image=next((s for s in ss if s.lower().endswith('.img')),None)
            if kind in ('[control]','[control group]'):continue # Nonvisual anchors, not missing images.
            if kind=='[tooltips]':continue # Hover metadata, not a permanently visible panel.
            if kind=='[board image]' and image:
                try:self.board(control,image)
                except ValueError as exc:
                    self.view_data['board_previews'].setdefault(key,dict(raw_parameters=p[:],raw_strings=ss[:])).update(status='preview refused',reason=str(exc))
                    self.gap(control,str(exc),'unconfirmed_geometry')
            elif kind=='[radiobutton]' and image:
                try:
                    entries,initial=radio_entries(control);selected=self.tab_values.get(key,initial)
                    for index,entry in enumerate(entries):
                        frames=entry['frames'];frame=frames[2] if index==selected else frames[0]
                        def select(index=index,key=key):self.tab_values[key]=index;self.schedule()
                        if frame>=0:self.sprite(image,frame,x+entry['x'],y+entry['y'],group=key,click=select)
                except ValueError as exc:self.gap(control,str(exc))
            elif kind=='[animation]':
                ani=next((s for s in ss if s.lower().endswith('.ani')),None)
                if ani:self.add_animation(control,ani)
                else:self.gap(control,'no ANI path')
            elif kind in ('[image]','[button]','[text button]','[highlight button]','[checkbox]') and image and p and isinstance(p[0],int) and p[0]>=0:
                frames=p[:4] if kind!='[image]' and len(p)>=4 and all(isinstance(n,int) and n>=0 for n in p[:4]) else []
                item=self.sprite(image,p[0],x,y,frames,key)
                if item and any(s.lower()=='lineardodge' for s in ss):item.blend=2
                if kind=='[text button]':
                    label=next((s for s in ss if s!=image),'')
                    data=self.find(image,p[0])
                    if label and data:
                        item=self.text(label,0,0);item.setPos(x+(data['logical_width']-item.boundingRect().width())/2,y+(data['logical_height']-item.boundingRect().height())/2);item.setAcceptedMouseButtons(C.Qt.NoButton)
            elif kind=='[text]':
                label=ss[0] if ss else None
                if label is None:self.gap(control,'native string ID unresolved: '+str(p[0] if p else None));continue
                color=G.QColor(*p[-3:]) if len(p)>=9 and all(isinstance(n,int) and 0<=n<=255 for n in p[-3:]) else G.QColor('#eeeeee')
                self.text(label,x,y,p[1] if len(p)>1 else None,color)
            elif kind=='[tab group]':self.tabs(ss,x,y,key)
            elif self.local and kind=='[basic button]' and ss:self.button(ss[0],x,y,80,key)
            elif self.local and 'scroll' in kind:
                scroll=W.QScrollBar(C.Qt.Vertical);scroll.setRange(0,100);scroll.setFixedSize(18,100);scroll.setValue(self.scroll_values.get(key,0))
                def changed(value,key=key):self.scroll_values[key]=value;self.interaction('本地滚动示意 '+key+' = '+str(value))
                scroll.valueChanged.connect(changed);proxy=self.scene().addWidget(scroll);proxy.setPos(x,y)
                self.gap(control,'local Qt scrollbar; native skin and range unresolved')
            else:self.gap(control,'dedicated control schema not implemented; raw fields retained')
        if self.view_data.get('mode')=='static':self.text('PVF 资源布局候选 · ANI 为外部时钟预览 · 原生字体/状态/专用绘制仍待核验',5,-36)
    def draw_live_controls(self):
        by_name={c.get('name'):c for c in self.definitions if c.get('decoded')}
        binding=self.view_data.get('binding_names',{})
        for row in self.view_data.get('controls',[]):
            name=binding.get(str(row['object']));control=by_name.get(name)
            if not control:continue
            kind=control['type'].lower();a=row['args'];x=signed(a[1]);y=signed(a[2]);ss=control['strings']
            if kind=='[tab group]':self.tabs(ss,x,y,name)
            elif 'button' in kind:
                label=next((s for s in ss if not s.lower().endswith('.img')),name)
                self.button(label,x,y,80,name)
        self.text('本地交互示意 · 真实皮肤状态和裁剪尚未验收',5,-36)
    def export(self,directory):
        output=Path(directory);output.mkdir(parents=True,exist_ok=True);assets={}
        (output/'images').mkdir(exist_ok=True)
        for key,data in self.assets.items():
            if key not in self.used_keys:continue
            target=output/'images'/Path(data['png']).name;shutil.copyfile(data['png'],target)
            assets[key]={**data,'file':target.relative_to(output).as_posix()};assets[key].pop('png',None)
        manifest=dict(version=1,exe_sha256=EXE_HASH,pvf_sha256=PVF_HASH,view=self.view_data,definitions=self.definitions,
            assets=assets,failures={k:v for k,v in self.failures.items() if k in self.used_keys},unresolved_assets=sorted(self.used_keys-set(assets)),capability=self.view_data.get('capability',{}),
            animations={k:v for k,v in self.animations.items() if k in self.used_animations},unresolved_animations=sorted(self.used_animations-set(self.animations)),
            limitation='Resource/call reconstruction; no original screenshot. Local interactions do not implement business behavior.')
        (output/'window.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),'utf8');return output

def static_view(path,catalog):
    by_path={w['path'].replace('\\','/').lower():w for w in catalog['windows']};controls=[];missing=[];instances=[];issues=[]
    def visit(path,x,y,stack,inherited,instance):
        path=path.replace('\\','/').lower()
        if path in stack or len(stack)>16:missing.append('recursive child '+path);return
        node=by_path.get(path)
        if not node:missing.append('missing child '+path);return
        instances.append(dict(path=path,instance=instance,x=x,y=y,window_fields=node.get('window_fields',[])))
        named={c['name']:c for c in node['controls'] if c.get('decoded') and c['name']!='-1'}
        def position(c,seen=None):
            seen=set(seen or []);key=instance+'#'+str(c.get('offset',0))
            if key in seen:missing.append('cyclic parent '+key);return (0,0,[])
            seen.add(key);cx=c.get('x',0);cy=c.get('y',0);conditions=[];position_parents=set()
            for parent in c.get('parents',[]):
                values=parent['values'];anchor=named.get(values[0]) if values else None
                if anchor:
                    anchor_key=instance+'#'+str(anchor['offset'])
                    if anchor_key not in position_parents:
                        px,py,pc=position(anchor,seen);cx+=px;cy+=py;conditions+=pc;position_parents.add(anchor_key)
                    if parent['tag'] in ('[parent tab]','[parent radio]','[parent page]') and len(values)>1:conditions.append((anchor_key,values[1]))
                else:missing.append('unresolved parent '+key+' '+str(values))
            return cx,cy,list(dict.fromkeys(tuple(c) for c in conditions))
        for c in node['controls']:
            if c.get('decoded'):
                cx,cy,conditions=position(c);controls.append({**c,'source':path,'instance':instance,'absolute_x':x+cx,'absolute_y':y+cy,'key':instance+'#'+str(c['offset']),'conditions':list(dict.fromkeys(tuple(c) for c in inherited+conditions))})
            else:issues.append(issue('unknown_structure','Undecoded control prefix',source=path,instance=instance,raw=c))
        for child_index,f in enumerate(node['children']):
            values=f['values']
            for i,value in enumerate(values):
                if isinstance(value,str) and value.lower().endswith('.ui'):
                    name=values[i+1] if i+1<len(values) else None
                    anchor=next((c for c in node['controls'] if c.get('name')==name),{})
                    child=value.lower().replace('\\','/')
                    if child not in by_path:child=posixpath.normpath(posixpath.join(posixpath.dirname(path),child))
                    cx,cy,conditions=position(anchor)
                    visit(child,x+cx,y+cy,stack+[path],list(dict.fromkeys(tuple(c) for c in inherited+conditions)),instance+'/child'+str(child_index)+'-'+str(i))
    visit(path,20,40,[],[],path.replace('\\','/').lower())
    issues.extend(issue('unconfirmed_geometry',reason) for reason in dict.fromkeys(missing))
    issues.append(issue('runtime_evidence','Static UI candidate; native state and visual acceptance pending'))
    return dict(mode='static',source=path,static_controls=controls,instances=instances,images=[],controls=[],preview_diagnostics=diagnostics(issues,support='partial PVF layout candidate'),
        capability=dict(identified=False,replayable=False,partial_replay=True,independently_rebuildable=False,locally_interactive=False),
        missing=list(dict.fromkeys(missing))+['PVF 布局候选，未与本次原生实例绑定','根窗口 tile type/size、对齐、裁剪、控件状态与字体待核验；原值保存在 instances'])
