// Explicit clocks: equipment uses the body's frame/delays; generated effects use elapsed time.
export function durations(ani){return ani.frames.map(f=>Number.isFinite(f.duration_ms)&&f.duration_ms>0?f.duration_ms:0);}
export function length(ani){return durations(ani).reduce((a,b)=>a+b,0);}
export function indexAt(ani,time){
  let end=0;const delays=durations(ani);
  for(let i=0;i<delays.length;i++){end+=delays[i];if(time<end)return i;}
  return Math.max(0,ani.frames.length-1);
}
export function frameStart(ani,index){return durations(ani).slice(0,index).reduce((a,b)=>a+b,0);}
export function trackFrame(track,body,time){
  if(track.end_behavior==='remove'&&time>=track.end_time_ms)return null;
  if(track.clock==='frozen')return track.ani.frames[0]??null;
  if(track.clock==='body')return track.ani.frames[indexAt(body,time)]??null;
  // Native A27DC0 sets ended+13A and retains the final frame for LOOP=0.
  // Controller detach is a separate event. Manual segment inspection retains it.
  return track.ani.frames[indexAt(track.ani,time)]??null;
}
export function formatImage(template,variation){
  let i=0;
  return String(template).replace(/%0([24])d/g,(match,width)=>{
    if(!variation||i>=variation.length)throw new Error('IMG 模板缺少显式 variation: '+template);
    const value=variation[i++];
    if(!Number.isInteger(value)||value<0)throw new Error('不支持的 IMG variation 数值');
    return String(value).padStart(Number(width),'0');
  });
}
