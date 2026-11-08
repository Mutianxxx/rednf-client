import {worldBox,firstContact} from './geometry.js';
import {durations,length,indexAt,frameStart,trackFrame,formatImage} from './timeline.js';
import {drawSprite,sampleSpriteStyle} from './renderer.js';
const $=id=>document.getElementById(id);
const api=async(path,args={})=>{
  const response=await fetch('/api/'+path+'?'+new URLSearchParams(args));
  const data=await response.json();
  if(!response.ok)throw Object.assign(new Error(data.error),data);
  return data;
};
const state={summary:null,character:null,skills:[],tab:'skills',ani:null,target:null,
  time:0,playing:false,last:0,equipment:0,sources:new Map(),images:new Map(),metas:new Map(),
  sequence:0,frame:0,targetFrame:0,targetTime:0,targetPlaying:false,warnings:[],skill:null,contracts:null,casts:null,spawns:null,scene:null,tracks:[],objectId:null,objectEvents:[],targetMotion:null};
const mainLength=()=>state.scene?.duration_ms??(state.ani?length(state.ani):0);
const bodyIndex=()=>state.scene?.body_clock==='frozen-phase0-reference'?0:indexAt(state.ani,state.time);
const targetLength=()=>Math.max(state.target?length(state.target):0,state.targetMotion?.total_input_time??0);
function reactionSampleAt(){
  if(!state.targetMotion)return null;
  return [...state.targetMotion.samples].reverse().find(s=>s.time_input<=state.targetTime)??null;
}
const targetOffsetX=()=>reactionSampleAt()?.x_axis.position??0;
const canvas=$('canvas'),ctx=canvas.getContext('2d');
const labels={0:'鬼剑士 Swordman',1:'格斗家 Fighter',2:'男枪手 Gunner',3:'魔法师 Mage',4:'圣职者 Priest',5:'女枪手 ATGunner'};
const text=(node,value)=>node.textContent=value;
const pretty=value=>JSON.stringify(value,null,2);
const iconMetadata=new Map();
function addSkillIcon(skill,parent){
  const values=skill.icon_fields?.[0]?.values;
  const holder=document.createElement('span');holder.className='skillIcon';holder.setAttribute('aria-hidden','true');parent.append(holder);
  if(typeof values?.[0]!=='string'||!Number.isInteger(values[1]))return;
  const path=values[0].replaceAll('\\','/').toLowerCase();
  if(!iconMetadata.has(path))iconMetadata.set(path,api('resource',{path}).catch(()=>null));
  iconMetadata.get(path).then(meta=>{
    if(!meta||!holder.isConnected)return;
    const image=document.createElement('img');image.alt='';image.loading='lazy';
    image.src='/api/frame?'+new URLSearchParams({path,index:values[1]});
    image.onerror=()=>image.remove();holder.append(image);
  });
}
function skillEvidence(skill){
  const known=state.contracts?.source_compatible&&state.contracts.skills.some(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  const phase=state.casts?.entries.find(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  const spawn=state.spawns?.entries.find(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  return {known,phase,spawn,available:Boolean(known||phase||spawn)};
}
function button(label,action,parent,cls='item'){
  const b=document.createElement('button');b.className=cls;b.textContent=label;b.onclick=()=>Promise.resolve(action()).catch(showError);parent.append(b);return b;
}
function showError(error){text($('status'),error.message||String(error));console.error(error);}
function logical(frame,track=null){
  const image=frame.images[0];if(!image)return null;
  return formatImage(image[0],track?.variation??[state.equipment]).replaceAll('\\','/').toLowerCase();
}
function sourceFor(logical){return state.sources.get(logical)||'';}
function imageKey(frame,track=null){const path=logical(frame,track);return path+'|'+(frame.images[0]?.[1]??0)+'|'+sourceFor(path);}
async function metadata(path){
  const key=path+'|'+sourceFor(path);
  if(state.metas.has(key))return state.metas.get(key);
  const result=await api('resource',{path,...(sourceFor(path)?{package:sourceFor(path)}:{})});
  state.metas.set(key,result);return result;
}
function addSourceChoice(path,error){
  if([...$('sources').children].some(x=>x.dataset.path===path))return;
  const row=document.createElement('div');row.className='source';row.dataset.path=path;
  const label=document.createElement('div');label.textContent=path;row.append(label);
  const select=document.createElement('select');
  select.append(new Option('请选择 NPK 来源',''));
  for(const item of error.candidates)select.append(new Option(item.package+' · '+item.length+' bytes',item.package));
  select.value=sourceFor(path);
  select.onchange=async()=>{state.sources.set(path,select.value);state.images.clear();await prepareAll();draw();};
  row.append(select);$('sources').append(row);
}
async function prepare(ani,track=null){
  const groups=new Map();
  for(const frame of ani?.frames??[]){const path=logical(frame,track);if(path){if(!groups.has(path))groups.set(path,[]);groups.get(path).push(frame);}}
  await Promise.all([...groups].map(async([path,frames])=>{
    try{
      await metadata(path);
      await Promise.all(frames.map(async(frame)=>{
        const key=imageKey(frame,track);if(state.images.has(key))return;
        const args={path,index:frame.images[0][1],...(sourceFor(path)?{package:sourceFor(path)}:{})};
        const info=await api('frame-info',args);
        const image=new Image();image.src='/api/frame?'+new URLSearchParams(args);await image.decode();
        state.images.set(key,{image,info});
      }));
    }catch(e){
      if(e.kind==='resource_conflict')addSourceChoice(path,e);
      else state.warnings.push(path+': '+e.message);
    }
  }));
}
async function prepareAll(){
  state.warnings=[];text($('status'),'读取原 NPK 图像…');
  await Promise.all([prepare(state.ani),prepare(state.target),...state.tracks.map(t=>prepare(t.ani,t))]);
  state.frame=-1;
  const unresolved=[...document.querySelectorAll('#sources select')].some(s=>!s.value);
  text($('status'),state.warnings.length?state.warnings[0]:unresolved?'需要选择 NPK 来源':'资源就绪');
}
async function loadAnimation(path,target=false){
  state.playing=false;text($('play'),'播放');text($('status'),'读取 PVF…');
  const sequence=++state.sequence;
  const ani=await api('animation',{path});
  if(sequence!==state.sequence)return;
  if(target){state.target=ani;state.targetTime=0;state.targetPlaying=false;state.frame=-1;state.targetMotion=null;
    text($('reactionStatus'),'未启用水平运动');
    $('targetPath').value=path;$('targetTime').max=length(ani);text($('targetPlay'),'播放对象');}
  else{
    state.scene=null;state.tracks=[];text($('sceneStatus'),'独立 ANI 资源');
    state.ani=ani;state.time=0;state.frame=-1;
    text($('title'),path);$('time').max=length(ani);$('time').value=0;
    $('frames').replaceChildren();
    for(let i=0;i<ani.frames.length;i++)button(String(i),()=>seekFrame(i),$('frames'),'');
    api('script',{path}).then(d=>text($('script'),d.text)).catch(showError);
  }
  $('sources').replaceChildren();await prepareAll();draw();
}
async function selectClass(){
  state.skill=null;state.scene=null;state.tracks=[];$('selection').replaceChildren();
  state.character=await api('character',{id:$('character').value});
  state.skills=await api('skills',{class:$('character').value});
  renderList();
  text($('coverage'),`${state.character.label} · ${state.skills.length} 条技能注册`);
  const first=state.character.slots.find(s=>s.tag==='waiting motion'&&!s.empty);
  if(first)await loadAnimation(first.path);
}
function renderList(){
  $('items').replaceChildren();const query=$('filter').value.toLowerCase();
  $('skillType').disabled=state.tab!=='skills';
  if(state.tab==='skills'){
    const rows=state.skills.filter(s=>{
      const searchable=[s.display_name,s.secondary_name,s.label,s.path,'#'+s.skill_id,...s.type].join(' ').toLowerCase();
      const type=$('skillType').value;
      return searchable.includes(query)&&(type==='all'||(type==='preview'?skillEvidence(s).available:s.type.includes('['+type+']')));
    });
    text($('listCount'),`${rows.length} / ${state.skills.length}`);
    for(const s of rows){
      const b=button('',()=>selectSkill(s),$('items'),'item skillItem');
      b.dataset.skillId=s.skill_id;b.dataset.classId=s.class_id;
      b.classList.toggle('selected',state.skill?.skill_id===s.skill_id&&state.skill?.class_id===s.class_id);
      b.setAttribute('aria-pressed',String(b.classList.contains('selected')));
      addSkillIcon(s,b);
      const copy=document.createElement('span');copy.className='skillCopy';b.append(copy);
      const name=document.createElement('strong');name.textContent=s.display_name||s.label;copy.append(name);
      const key=document.createElement('small');key.className='skillKey';key.textContent=`#${s.skill_id} ${s.label}${s.secondary_name?' · '+s.secondary_name:''}`;copy.append(key);
      const {known,phase,spawn,available}=skillEvidence(s);
      const small=document.createElement('small');small.className=available?'skillState available':'skillState';
      small.textContent=`${s.type.includes('[passive]')?'被动':'主动'} · ${spawn?'效果轨可预览':known?'部分释放可预览':phase?'施法主体可检查':'释放链待恢复'}`;copy.append(small);
    }
    if(!rows.length){const p=document.createElement('p');p.className='notice';p.textContent='没有匹配的技能，试试中文名、英文名或 ID。';$('items').append(p);}
  }else{
    const rows=state.character.slots.filter(s=>s.kind==='animation'&&!s.empty&&(s.tag+' '+s.path).toLowerCase().includes(query));
    text($('listCount'),`${rows.length} 个动作`);
    for(const s of rows){
      const b=button(`${s.tag} [${s.index}]`,()=>loadAnimation(s.path),$('items'));
      const small=document.createElement('small');small.textContent=s.source_path;b.append(small);
    }
  }
}
async function selectSkill(skill){
  state.skill=skill;renderList();const d=await api('script',{path:skill.path});
  const panel=$('selection');panel.replaceChildren();
  const h=document.createElement('h3');h.className='skillHeading';h.textContent=skill.display_name||skill.label;panel.append(h);
  const meta=document.createElement('p');meta.className='skillSubtitle';meta.textContent=`#${skill.skill_id} · ${skill.secondary_name||skill.label}`;panel.append(meta);
  const source=document.createElement('details'),sourceTitle=document.createElement('summary'),sourceData=document.createElement('pre');
  sourceTitle.textContent='技能名称与 PVF 来源';sourceData.textContent=pretty({path:skill.path,name:skill.name_resolution,name2:skill.name2_resolution});source.append(sourceTitle,sourceData);panel.append(source);
  const contract=state.contracts?.source_compatible&&state.contracts.skills.find(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  const casting=state.casts?.entries.find(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  const spawn=state.spawns?.entries.find(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id);
  const badge=document.createElement('div');badge.className='badge';badge.textContent=spawn?'视觉与生成攻击实体已定位':contract?'部分释放链已确认':casting?'已定位施法主体阶段':'技能执行链待确认';panel.append(badge);
  const p=document.createElement('p');p.className='notice';p.textContent=contract?
    (skill.skill_id===8?'手动检查普通三段斩的单段身体、武器附层与特效。位移、接续输入、命中接受和怪物反应尚未执行；每段从第0帧检查。':
    '当前可检查普通鬼斩分支（技能 6 未学习）：身体、武器附层和两张特效。命中接受、伤害、受击/死亡状态尚未接入。'):
    spawn?'可以检查 phase0 两条视觉轨与独立攻击实体，或手动查看两个施法主体阶段。动态伤害、命中接受和完整阶段调度仍待恢复。':
    casting?'可以手动检查两个施法阶段的主体动画。阶段时长、速度、装备、攻击与最终技能效果尚未执行。':
    '已读取此技能的原 SKL。动作、ATK 与特效的控制器绑定尚未闭合；左侧“动作资源”可独立检查原动画。';panel.append(p);
  if(casting){
    if(casting.variant_guard_status!=='native_controller_class_confirmed'){
      const note=document.createElement('p');note.className='notice';note.textContent='此枪手技能来自男女共用的命令处理器，职业分支条件待核对；这里只检查当前 CHR 资源候选。';panel.append(note);
    }
    for(const phase of casting.phases)button(`检查施法阶段 ${phase.phase} 主体`,async()=>{
      const result=await api('cast-phase',{class:skill.class_id,skill:skill.skill_id,phase:phase.phase});
      await loadAnimation(result.animation_path);text($('sceneStatus'),result.notice);
      text($('phaseEvidence'),pretty(result));
    },panel,'');
    const details=document.createElement('details'),summary=document.createElement('summary'),pre=document.createElement('pre');
    summary.textContent='施法阶段与来源';pre.id='phaseEvidence';details.append(summary,pre);panel.append(details);
  }
  if(contract){
    const equip=document.createElement('select');equip.id='skillEquipment';
    equip.append(new Option('身体 + 特效（未装备武器）',''),new Option('斧棍 EQU：variation 2 / 6','equipment/character/swordman/weapon/club/n_club_axshauta.equ'));
    panel.append(equip);
    const level=document.createElement('input');level.id='skillLevel';level.type='number';level.min=1;level.max=30;level.value=1;
    const levelLabel=document.createElement('label');levelLabel.textContent='技能等级';levelLabel.append(level);panel.append(levelLabel);
    if(skill.skill_id===8){
      for(const c of state.contracts.skills.filter(c=>c.class_id===skill.class_id&&c.skill_id===skill.skill_id))
        button('检查第 '+(c.segment+1)+' 段资源',()=>loadScene(skill,equip.value,Number(level.value),c.variant),panel,'');
    }else button('预览普通鬼斩分支',()=>loadScene(skill,equip.value,Number(level.value),contract.variant),panel,'');
    const stage=document.createElement('p');stage.id='levelConsumption';stage.className='notice';panel.append(stage);
    const details=document.createElement('details'),summary=document.createElement('summary'),pre=document.createElement('pre');
    summary.textContent='分支范围与证据';pre.textContent=pretty(contract);details.append(summary,pre);panel.append(details);
  }
  if(spawn){
    const label=document.createElement('label'),gate=document.createElement('input');gate.type='checkbox';gate.checked=true;gate.id='spawnGate';
    label.append(gate,document.createTextNode('预览条件：攻击对象生成门通过'));panel.append(label);
    const previewButton=button(`检查${skill.display_name||skill.label}视觉与攻击实体`,()=>loadSpawnScene(skill,gate.checked),panel,'');previewButton.dataset.action='spawn-preview';
    const note=document.createElement('p');note.className='notice';note.textContent='主体冻结为 phase0 位置参考；独立播放两层原始特效与无图攻击实体。时间为源 DELAY 基准模型；不计算伤害或自动触发怪物反应。';panel.append(note);
  }
  const fields=d.fields.filter(x=>['type','maximum level','consume MP','cool time','static data','level info','weapon effect type'].includes(x.tag));
  const fieldsDetails=document.createElement('details'),fieldsTitle=document.createElement('summary'),pre=document.createElement('pre');
  fieldsTitle.textContent='技能原始参数';pre.textContent=pretty(fields.map(({tag,values,scope,start})=>({tag,values,scope,offset:start})));fieldsDetails.append(fieldsTitle,pre);panel.append(fieldsDetails);
  text($('script'),d.text);
}
async function loadScene(skill,equipment,level=1,variant='normal-no-charge'){
  const scene=await api('scene',{class:skill.class_id,skill:skill.skill_id,level,variant,...(equipment?{equipment}:{})});
  const body=scene.tracks.find(t=>t.role==='body');
  await loadAnimation(body.path);
  state.scene=scene;state.tracks=await Promise.all(scene.tracks.filter(t=>t.role!=='body').map(async t=>({...t,ani:await api('animation',{path:t.path})})));
  text($('sceneStatus'),scene.contract.label+' · 身体 + '+state.tracks.filter(t=>t.role==='equipment').length+' 装备层 + '+state.tracks.filter(t=>t.role==='effect').length+' 特效'+(skill.skill_id===8?' · 单段资源检查，位移/接续未执行':''));
  const consumed=scene.level_consumption;
  if($('levelConsumption'))text($('levelConsumption'),`等级 ${consumed.level}：PVF 第 ${consumed.column} 列 ${consumed.raw_value} → ATK bonus ${consumed.installed_atk_bonus} → 早期倍率 ${consumed.mathematical_early_ratio}。完整伤害公式待恢复。`);
  $('sources').replaceChildren();await prepareAll();state.frame=-1;draw();
}
async function loadSpawnScene(skill,gate){
  const scene=await api('spawn-scene',{class:skill.class_id,skill:skill.skill_id,spawn_gate:gate?'1':'0'});
  const body=scene.tracks.find(t=>t.role==='body');await loadAnimation(body.path);
  state.scene=scene;state.tracks=await Promise.all(scene.tracks.filter(t=>t.role!=='body').map(async t=>({...t,ani:await api('animation',{path:t.path})})));
  $('time').max=scene.duration_ms;$('frames').replaceChildren();
  for(const time of scene.sample_times)button(String(time),()=>{state.playing=false;state.time=time;state.frame=-1;text($('play'),'播放');draw();},$('frames'),'');
  text($('sceneStatus'),(skill.display_name||skill.label)+' · '+scene.notice);
  $('sources').replaceChildren();await prepareAll();state.frame=-1;draw();
}
function seekFrame(index){if(!state.ani)return;state.playing=false;text($('play'),'播放');state.time=frameStart(state.ani,Math.max(0,Math.min(index,state.ani.frames.length-1)));draw();}
function drawGrid(){
  ctx.fillStyle='#202939';ctx.fillRect(0,0,1000,600);
  ctx.strokeStyle='#304055';ctx.lineWidth=1;
  for(let x=0;x<=1000;x+=50){ctx.beginPath();ctx.moveTo(x,0);ctx.lineTo(x,600);ctx.stroke();}
  for(let y=0;y<=600;y+=50){ctx.beginPath();ctx.moveTo(0,y);ctx.lineTo(1000,y);ctx.stroke();}
  ctx.strokeStyle='#6b7c97';ctx.beginPath();ctx.moveTo(0,420);ctx.lineTo(1000,420);ctx.stroke();
}
function drawActor(ani,time,position,direction=1,track=null,frameOverride=null){
  if(!ani?.frames.length)return null;
  const frame=frameOverride??ani.frames[indexAt(ani,time)],index=ani.frames.indexOf(frame);
  if(!frame)return null;
  const item=state.images.get(imageKey(frame,track));let render=null;
  const sampled=sampleSpriteStyle(ani,index,time,{enabled:$('interpolation').checked,
    clockAni:track?.clock==='body'?state.ani:ani,
    imageRateOverride:track?.image_rate_override,
    frozen:track?.clock==='frozen'||(!track&&ani===state.ani&&state.scene?.body_clock==='frozen-phase0-reference')});
  if(item){
    render=drawSprite(ctx,item,frame,{position,direction,styleOverride:sampled});
    const effect=render.graphic_effect;
    if(!render.effect_supported&&!state.warnings.includes('图形效果 '+effect+' 待核对'))state.warnings.push('图形效果 '+effect+' 待核对');
  }
  if($('boxes').checked){
    for(const [boxes,color] of [[frame.damage_boxes,'#74dca6'],[frame.attack_boxes,'#fa7777']]){
      for(const raw of boxes){const b=worldBox(raw,position,direction);if(!b)continue;
        ctx.strokeStyle=color;ctx.fillStyle=color+'20';ctx.lineWidth=1;
        // Oblique projection of the source XYZ volume, without changing its collision coordinates.
        const x=b[0],y=b[1]-b[2]-b[5],w=b[3],h=b[5],dy=b[4];
        ctx.fillRect(x,y,w,h);ctx.strokeRect(x,y,w,h);ctx.strokeRect(x,y+dy,w,h);
        ctx.beginPath();for(const [px,py] of [[x,y],[x+w,y],[x,y+h],[x+w,y+h]]){ctx.moveTo(px,py);ctx.lineTo(px,py+dy);}ctx.stroke();
      }
    }
  }
  ctx.fillStyle='#e4eaf2';ctx.fillRect(position[0]-2,position[1]-2,4,4);
  return {frame,index,item,render};
}
function draw(){
  drawGrid();const zoom=Number($('zoom').value);ctx.save();ctx.translate(500,420);ctx.scale(zoom,zoom);ctx.translate(-500,-420);ctx.imageSmoothingEnabled=false;
  const direction=Number($('direction').value),sign=direction===0?-1:1;
  const layerFrames=[];
  // 49A359 draws negative attachment keys, then the body and its ANI children,
  // then nonnegative attachment keys. Equipment layers belong to the body tree;
  // their layer numbers are not entity attachment keys.
  const sorted=[...state.tracks].sort((a,b)=>a.layer-b.layer);
  function drawTrack(track){
    const frame=trackFrame(track,state.ani,state.time);if(!frame)return;
    const position=[380+track.offset[0]*sign,420+track.offset[1],track.offset[2]];
    const drawn=drawActor(track.ani,state.time,position,direction,track,frame);
    layerFrames.push({track,frame,drawn});
  }
  for(const track of sorted.filter(t=>t.role==='effect'&&t.layer<0))drawTrack(track);
  const a=drawActor(state.ani,state.time,[380,420,0],direction,null,state.ani?.frames[bodyIndex()]);
  for(const track of sorted.filter(t=>t.role==='equipment'))drawTrack(track);
  for(const track of sorted.filter(t=>t.role!=='equipment'&&!(t.role==='effect'&&t.layer<0)))drawTrack(track);
  const targetPos=[380+Number($('targetX').value)+targetOffsetX(),420+Number($('targetY').value),0];
  const targetDirection=Number($('targetDirection').value);
  const b=drawActor(state.target,state.targetTime,targetPos,targetDirection);ctx.restore();
  if(b){$('targetTime').value=state.targetTime;text($('targetClock'),`${Math.round(state.targetTime)} / ${targetLength()} ms · 帧 ${b.index}`);}
  if(state.targetMotion)text($('reactionStatus'),pretty({parameters:state.targetMotion.parameters,
    sampled_at:reactionSampleAt()?.time_input??0,x_offset:targetOffsetX(),
    sample:reactionSampleAt(),state_exit_executed:false}));
  let contact=null;
  const candidates=a?[{path:state.ani.path,frame:a.frame,offset:[0,0,0]},...layerFrames.filter(l=>['equipment','spawned_attack'].includes(l.track.role)).map(l=>({path:l.track.path,frame:l.frame,offset:l.track.offset}))]:[];
  if(a&&b)for(const candidate of candidates){
    const offset=[candidate.offset[0]*sign,candidate.offset[1],candidate.offset[2]];
    const hit=firstContact(candidate.frame.attack_boxes,b.frame.damage_boxes,offset,[Number($('targetX').value)+targetOffsetX(),Number($('targetY').value),0],direction,targetDirection);
    if(hit){contact={...hit,attack_animation:candidate.path};break;}
  }
  text($('contact'),contact?`几何接触：${contact.attack_animation} · 攻击盒 ${contact.attack_index} → 受击盒 ${contact.damage_index}。接受命中、扣血和状态变化尚未执行。`:'当前帧无几何接触。绿色：受击盒；红色：攻击盒。');
  $('contact').className=contact?'good':'';
  if(a){
    $('time').value=state.time;text($('clock'),`${Math.round(state.time)} / ${mainLength()} ${state.scene?.source_delay_model?'源 DELAY 单位':'ms'} · 主体帧 ${a.index}`);
    // Attachments and targets have independent clocks, so body frame alone
    // cannot identify the displayed composite frame.
    const frameKey=`${a.index}:${state.time}:${state.targetTime}`;
    if(state.frame!==frameKey){state.frame=frameKey;
      [...$('frames').children].forEach((b,i)=>b.classList.toggle('active',state.scene?.source_delay_model?state.scene.sample_times[i]===state.time:i===a.index));
      text($('frameData'),pretty({path:state.ani.path,frame:a.index,source:state.ani.source,values:a.frame,
        time:state.time,source_delay_model:state.scene?.source_delay_model??false,
        spawn_gate_assumed:state.scene?.spawn_gate_assumed??null,
        image_source:a.item?.info.source??null,render:a.render,geometry:contact,
        target:b?{path:state.target.path,frame:b.index,time_ms:state.targetTime,
          horizontal_motion:state.targetMotion?{inputs:state.targetMotion.inputs,parameters:state.targetMotion.parameters,
            x_offset:targetOffsetX(),sample:reactionSampleAt(),native_state_machine_executed:false}:null}:null,
        controller:state.scene?.contract??null,
        level_consumption:state.scene?.level_consumption??null,
        layers:layerFrames.map(l=>({path:l.track.path,role:l.track.role,frame:l.drawn?.index,
          attack_boxes:l.frame.attack_boxes,image_source:l.drawn?.item?.info.source??null,render:l.drawn?.render??null,binding:l.track.binding}))}));
    }
    text($('overlay'),[state.ani.path,`帧 ${a.index} · ${a.frame.duration_ms} ms`,
      ...state.ani.warnings.map(x=>x.kind),...state.warnings.slice(0,2),
      !a.item?'图像未载入，请检查下方来源选择。':''].filter(Boolean).join('\n'));
  }
}
function tick(now){
  const delta=Math.min(250,now-state.last)*Number($('speed').value);
  let changed=false;
  if(state.playing&&state.ani){
    state.time+=delta;
    const total=mainLength();
    if(state.time>=total){if($('loop').checked&&total>0)state.time%=total;else{state.time=total;state.playing=false;text($('play'),'播放');}}
    changed=true;
  }
  if(state.targetPlaying&&state.target){
    state.targetTime+=delta;const total=targetLength();
    if(state.targetTime>=total){state.targetTime=total;state.targetPlaying=false;text($('targetPlay'),'播放对象');}
    state.frame=-1;changed=true;
  }
  if(changed)draw();
  state.last=now;requestAnimationFrame(tick);
}
$('character').onchange=()=>selectClass().catch(showError);
$('skillsTab').onclick=()=>{state.tab='skills';$('skillsTab').classList.add('active');$('motionsTab').classList.remove('active');renderList();};
$('motionsTab').onclick=()=>{state.tab='motions';$('motionsTab').classList.add('active');$('skillsTab').classList.remove('active');renderList();};
$('filter').oninput=renderList;
$('skillType').onchange=renderList;
$('play').onclick=()=>{if(!state.ani)return;if(state.time>=mainLength())state.time=0;state.playing=!state.playing;text($('play'),state.playing?'暂停':'播放');};
$('restart').onclick=()=>{state.time=0;state.playing=true;text($('play'),'暂停');draw();};
function stepMain(direction){
  if(state.scene?.source_delay_model){
    const times=state.scene.sample_times;
    const time=direction>0?times.find(t=>t>state.time):[...times].reverse().find(t=>t<state.time);
    if(time!==undefined){state.playing=false;text($('play'),'播放');state.time=time;state.frame=-1;draw();}
  }else if(state.ani)seekFrame(indexAt(state.ani,state.time)+direction);
}
$('prev').onclick=()=>stepMain(-1);$('next').onclick=()=>stepMain(1);
$('time').oninput=()=>{state.playing=false;state.time=Number($('time').value);text($('play'),'播放');draw();};
for(const id of ['boxes','zoom','targetX','targetY','direction','targetDirection','interpolation'])$(id).oninput=()=>{state.frame=-1;draw();};
$('equipment').onchange=async()=>{state.equipment=Math.max(0,Math.min(9999,Number($('equipment').value)||0));$('sources').replaceChildren();await prepareAll();draw();};
$('targetLoad').onclick=()=>loadAnimation($('targetPath').value,true).catch(showError);
$('targetClear').onclick=()=>{state.target=null;state.targetMotion=null;state.targetPlaying=false;state.frame=-1;text($('targetClock'),'未载入对象');draw();};
$('targetPlay').onclick=()=>{if(!state.target)return;if(state.targetTime>=targetLength())state.targetTime=0;
  state.targetPlaying=!state.targetPlaying;text($('targetPlay'),state.targetPlaying?'暂停对象':'播放对象');};
$('targetRestart').onclick=()=>{if(!state.target)return;state.targetTime=0;state.targetPlaying=true;text($('targetPlay'),'暂停对象');state.frame=-1;draw();};
function seekTarget(index){if(!state.target)return;state.targetPlaying=false;text($('targetPlay'),'播放对象');
  state.targetTime=frameStart(state.target,Math.max(0,Math.min(index,state.target.frames.length-1)));state.frame=-1;draw();}
$('targetPrev').onclick=()=>{if(state.target)seekTarget(indexAt(state.target,state.targetTime)-1);};
$('targetNext').onclick=()=>{if(state.target)seekTarget(indexAt(state.target,state.targetTime)+1);};
$('targetTime').oninput=()=>{state.targetPlaying=false;state.targetTime=Number($('targetTime').value);text($('targetPlay'),'播放对象');state.frame=-1;draw();};
$('mobRoute').onclick=async()=>{
  try{
    const route=await api('monster-route',{path:$('mobPath').value,state:$('mobState').value,variant:$('mobVariant').value});
    text($('mobRouteData'),pretty(route));text($('mobNotice'),route.notice+(route.unresolved?'；'+route.unresolved:''));
    if(route.animation_path)await loadAnimation(route.animation_path,true);
  }catch(e){showError(e);}
};
$('mobLoad').onclick=async()=>{
  try{
    const mob=await api('monster',{path:$('mobPath').value});$('mobResources').replaceChildren();
    text($('mobNotice'),mob.notice);
    for(const ref of mob.resources){
      const label=ref.tag+' · '+ref.path;
      if(ref.kind==='animation'&&ref.exists)button(label,()=>loadAnimation(ref.path,true),$('mobResources'));
      else{const p=document.createElement('p');p.textContent=label+'（ACT 执行器待接入）';$('mobResources').append(p);}
    }
  }catch(e){showError(e);}
};
async function inspectObject(event=null){
  const id=event?state.objectId:Number($('objectId').value);
  const events=event?[...state.objectEvents,event]:[];
  const result=await api('scene-object',{id,events:JSON.stringify(events)});
  state.objectId=id;state.objectEvents=events;
  const current=result.current,grass=result.binding.config.kind==='grass';
  text($('objectData'),pretty(result));text($('objectNotice'),result.notice);
  text($('objectStatus'),pretty({id,active:current.active,hp:current.hp,max_hp:current.max_hp,
    count:current.count,animation:current.current_ani,
    last_outputs:result.trace.at(-1)?.output_events??[]}));
  $('objectHpWrite').disabled=!current.active||grass;
  $('objectContact').disabled=!current.active||!grass;
  $('objectAniEnd').disabled=!current.active;$('objectRemoved').disabled=!current.active;
  if(result.animation_path){
    const resetRequested=result.trace.at(-1)?.output_events.some(e=>e.kind==='select_ani'&&e.reset);
    // Repeated events that retain the same ANI do not restart the tree's loop.
    if(state.target?.path!==result.animation_path||!event||resetRequested)await loadAnimation(result.animation_path,true);
  }else{$('targetClear').click();}
  state.frame=-1;draw();
}
$('objectLoad').onclick=()=>inspectObject().catch(showError);
$('objectHpWrite').onclick=()=>inspectObject({kind:'native_absolute_hp_write',new_absolute_hp:Number($('objectHp').value)}).catch(showError);
$('objectContact').onclick=()=>inspectObject({kind:'native_accepted_contact'}).catch(showError);
$('objectAniEnd').onclick=()=>inspectObject({kind:'native_ani_ended'}).catch(showError);
$('objectRemoved').onclick=()=>inspectObject({kind:'native_self_removed'}).catch(showError);
$('reactionSample').onclick=async()=>{
  try{
    const [route,motion]=await Promise.all([
      api('monster-route',{path:$('mobPath').value,state:3,variant:$('mobVariant').value}),
      api('reaction-horizontal',{kind:$('reactionKind').value,scale_integer:$('reactionScale').value,
        stat218:$('reactionStat').value,stat220:$('reactionMultiplier').value,
        special_flag:$('reactionFlag').checked?'1':'0',motion_enabled:$('reactionEnabled').checked?'1':'0',
        direction:$('reactionDirection').value,step_delta:$('reactionDelta').value,steps:$('reactionSteps').value})]);
    if(!route.animation_path)throw new Error(route.unresolved??'受击资源未能确定');
    await loadAnimation(route.animation_path,true);
    state.targetMotion=motion;state.targetTime=0;$('targetTime').max=targetLength();state.frame=-1;
    text($('reactionData'),pretty({motion,route}));text($('reactionNotice'),motion.notice);draw();
  }catch(e){showError(e);}
};
$('reactionClear').onclick=()=>{state.targetMotion=null;state.frame=-1;
  if(state.target){$('targetTime').max=targetLength();state.targetTime=Math.min(state.targetTime,targetLength());}
  text($('reactionStatus'),'运动已清除');draw();};
let searchTimer;
$('pathSearch').oninput=()=>{clearTimeout(searchTimer);searchTimer=setTimeout(async()=>{
  try{const d=await api('paths',{q:$('pathSearch').value,ext:'.ani'});$('paths').replaceChildren();
    for(const path of d.paths){const b=button(path,()=>loadAnimation(path),$('paths'));b.title='点击在主对象播放';
      button('对照',()=>loadAnimation(path,true),$('paths'),'');}
  }catch(e){showError(e);}
},300);};
document.addEventListener('keydown',e=>{if(['INPUT','SELECT','TEXTAREA'].includes(e.target.tagName))return;
  if(e.code==='Space'){e.preventDefault();$('play').click();}if(e.code==='ArrowRight'){e.preventDefault();$('next').click();}if(e.code==='ArrowLeft'){e.preventDefault();$('prev').click();}});
async function start(){
  state.summary=await api('summary');
  state.contracts=await api('contracts');
  state.casts=await api('cast-bindings');
  state.spawns=await api('spawn-bindings');
  text($('identity'),`${state.summary.class_count} 职业 · ${state.summary.registered_skill_rows} 技能注册 · PVF ${state.summary.source.sha256.slice(0,12)}`);
  for(const c of state.summary.classes)$('character').append(new Option(labels[c.class_id]??c.label,c.class_id));
  await selectClass();requestAnimationFrame(tick);
}
start().catch(showError);
