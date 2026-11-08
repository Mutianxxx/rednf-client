// 60US A23D60 -> 5383D0 -> B0E050 -> texture vslot+A0 (ADD3D0).
// See analysis/combat_render/transform: source values are radians, and the
// texture matrix scales its output axes after rotation by the negative angle.
const tints=new WeakMap();
const field=(frame,tag,fallback)=>frame.fields.findLast(f=>f.tag.toUpperCase()===tag)?.values??fallback;

export function spriteStyle(frame,imageRateOverride=null){
  const rgba=field(frame,'RGBA',[255,255,255,255]).map(v=>Math.trunc(v)&255);
  const rate=imageRateOverride??field(frame,'IMAGE RATE',[1,1]);
  const angle=field(frame,'IMAGE ROTATE',[0])[0];
  const effect=field(frame,'GRAPHIC EFFECT',['NONE'])[0];
  return {rgba,rate,source_rotation_radians:angle,canvas_rotation_radians:-angle,
    image_position:frame.image_positions[0]??[0,0],graphic_effect:effect,
    composite:effect==='LINEARDODGE'?'lighter':'source-over',
    effect_supported:['NONE','LINEARDODGE'].includes(effect)};
}

// A24950 updates only position, rate, raw angle and the four color bytes.
// The integer helper 473F20 truncates the entire interpolated coordinate.
// Timing here uses the existing source-DELAY resource clock at rate 100.
export function sampleSpriteStyle(ani,index,time,{enabled=true,clockAni=ani,imageRateOverride=null,frozen=false,ended=false}={}){
  const frame=ani.frames[index],style=spriteStyle(frame);
  const loop=ani.header?.findLast(f=>f.tag.toUpperCase()==='LOOP')?.values[0]??0;
  const next=index+1<ani.frames.length?index+1:loop?0:null;
  const delays=clockAni.frames.map(f=>Number.isFinite(f.duration_ms)&&f.duration_ms>0?f.duration_ms:0);
  const start=delays.slice(0,index).reduce((a,b)=>a+b,0),span=delays[index]??0;
  const elapsed=Math.trunc(time)-start;
  const requested=Boolean(field(frame,'INTERPOLATION',[0])[0]);
  const active=enabled&&requested&&!frozen&&!ended&&next!==null&&span>0;
  const ratio=span>0?Math.max(0,Math.min(1,elapsed/span)):0;
  style.interpolation={requested,enabled,active,next_frame:next,elapsed,span,ratio:active?ratio:0,
    clock:'source-delay-rate-100',native_game_clock_observed:false};
  if(active){
    const target=spriteStyle(ani.frames[next]);
    const linear=(a,b)=>{
      a=Math.fround(a);b=Math.fround(b);
      return elapsed>=span?b:elapsed<=0?a:a+(b-a)*elapsed/span;
    };
    style.image_position=style.image_position.map((v,i)=>Math.trunc(linear(v,target.image_position[i])));
    style.rate=style.rate.map((v,i)=>Math.fround(linear(v,target.rate[i])));
    style.rgba=style.rgba.map((v,i)=>Math.trunc(linear(v,target.rgba[i]))&255);
    style.source_rotation_radians=Math.fround(linear(style.source_rotation_radians,target.source_rotation_radians));
    style.canvas_rotation_radians=-style.source_rotation_radians;
  }
  if(imageRateOverride)style.rate=imageRateOverride;
  return style;
}

function tinted(image,rgb){
  if(rgb.every(v=>v===255))return image;
  let variants=tints.get(image);
  if(!variants){variants=new Map();tints.set(image,variants);}
  const key=rgb.join(',');
  if(variants.has(key))return variants.get(key);
  const canvas=document.createElement('canvas');
  canvas.width=image.naturalWidth??image.width;canvas.height=image.naturalHeight??image.height;
  const context=canvas.getContext('2d',{willReadFrequently:true});
  context.drawImage(image,0,0);
  const pixels=context.getImageData(0,0,canvas.width,canvas.height);
  for(let i=0;i<pixels.data.length;i+=4){
    for(let c=0;c<3;c++)pixels.data[i+c]=Math.round(pixels.data[i+c]*rgb[c]/255);
  }
  // Preserve texture alpha here. Frame alpha participates once, when compositing.
  context.putImageData(pixels,0,0);
  if(variants.size>=16)variants.delete(variants.keys().next().value);
  variants.set(key,canvas);
  return canvas;
}

export function drawSprite(context,item,frame,{position=[0,0,0],direction=1,imageRateOverride=null,styleOverride=null}={}){
  const style=styleOverride??spriteStyle(frame,imageRateOverride);
  const image=tinted(item.image,style.rgba.slice(0,3));
  context.save();
  try{
    context.translate(position[0],position[1]-position[2]);
    context.globalAlpha=style.rgba[3]/255;
    context.globalCompositeOperation=style.composite;
    context.scale((direction===0?-1:1)*style.rate[0],style.rate[1]);
    context.rotate(style.canvas_rotation_radians);
    context.translate(...style.image_position);
    context.drawImage(image,item.info.x,item.info.y);
  }finally{context.restore();}
  return style;
}
