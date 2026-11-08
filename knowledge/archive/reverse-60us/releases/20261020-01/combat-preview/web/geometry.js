// 60US static contract: 4E9B10 world boxes -> A244E0 inclusive AABB.
// Native x87 rounding mode is unresolved; Math.fround uses nearest-even.
export function worldBox(raw,position=[0,0,0],direction=1){
  if(raw.length!==6||position.length!==3||![...raw,...position].every(Number.isFinite))return null;
  const b=raw.map(Math.fround);
  if(!b.every(Number.isFinite)||!b.slice(3).every(x=>x>0))return null;
  if(direction===0)b[0]=Math.fround(Math.fround(-b[0])-b[3]);
  for(let a=0;a<3;a++)b[a]=Math.fround(b[a]+Math.fround(position[a]));
  return b.every(Number.isFinite)?b:null;
}
export function intersection(a,b){
  if(!a||!b||a.length!==6||b.length!==6||[...a,...b].some(x=>!Number.isFinite(x))||![...a.slice(3),...b.slice(3)].every(x=>x>0))return null;
  const result=[];
  for(let i=0;i<3;i++){
    const amax=Math.fround(a[i]+a[i+3]),bmax=Math.fround(b[i]+b[i+3]);
    if(!Number.isFinite(amax)||!Number.isFinite(bmax)||b[i]>amax||a[i]>bmax)return null;
    result[i]=Math.max(a[i],b[i]);
    result[i+3]=Math.fround(Math.min(amax,bmax)-result[i]);
  }
  return result;
}
export function firstContact(attack,damage,apos,bpos,adir=1,bdir=1){
  for(let i=0;i<attack.length;i++)for(let j=0;j<damage.length;j++){
    const a=worldBox(attack[i],apos,adir),b=worldBox(damage[j],bpos,bdir),overlap=intersection(a,b);
    if(overlap)return {attack_index:i,damage_index:j,a,b,overlap};
  }
  return null;
}
