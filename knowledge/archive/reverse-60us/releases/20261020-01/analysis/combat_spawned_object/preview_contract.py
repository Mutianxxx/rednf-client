"""Execute the limited resource timeline; never synthesize a native accepted hit.

Input time is normalized source DELAY units, with phase0 application at zero.
The native scalar/transport/hit controller remains outside this sampler.
"""
from pathlib import Path
import json, struct, argparse, math
ROOT = Path(__file__).resolve().parent

def f32(value):
    return struct.unpack('<f',struct.pack('<f',value))[0]

def sample(time, xyz=(0,0,0), direction=1, *, spawn_gate=True, contract=None):
    if contract is None:
        contract=json.loads((ROOT/'preview-contract.json').read_text(encoding='utf-8'))
    if not math.isfinite(time) or time<0:
        raise ValueError('time must be finite and nonnegative')
    if direction not in (0,1):
        raise ValueError('selected native contact domain requires direction 0 or 1')
    if len(xyz)!=3 or not all(math.isfinite(v) for v in xyz):
        raise ValueError('xyz must contain three finite coordinates')
    active=[]
    contacts=[]
    for track in contract['tracks']:
        attack_entity=track['role']=='spawned_invisible_attack_entity'
        if attack_entity and not spawn_gate:
            continue
        # Final frame is retained by native nonlooping ANI. The attack object
        # requests removal when ended; sampling omits it from its end deadline.
        frame=next((f for f in track['frames'] if f['start']<=time<f['end']),None)
        if frame is None:
            if attack_entity:
                continue
            frame=track['frames'][-1]
        record=dict(path=track['path'],role=track['role'],frame=frame['index'],
                    source_frame_range=[frame['source_start'],frame['source_end']],
                    images=frame['images'],image_positions=frame['image_positions'],
                    ended=time>=track['frame_delay_sum'])
        active.append(record)
        if attack_entity:
            for box in frame['attack_boxes']:
                x,y,z,w,h,d=map(f32,box)
                if direction==0:x=f32(f32(-x)-w)
                contacts.append([f32(x+f32(xyz[0])),f32(y+f32(xyz[1])),f32(z+f32(xyz[2])),w,h,d])
    return dict(schema='60us-skill32-timeline-sample-v1',time=time,time_origin='phase0.apply',
                native_time_observed=False,spawn_gate_considered_passed=spawn_gate,
                tracks=active,attack_boxes_world=contacts,
                emitted_native_hit=False,damage=None,monster_reaction=None,
                limitation='This reports resource frames and transformed geometry only. Native eligibility, target history, HP and reaction are separate.')

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--time',type=float,nargs='+',default=[0,79,80,399,400,490])
    parser.add_argument('--xyz',type=float,nargs=3,default=[0,0,0])
    parser.add_argument('--direction',type=int,default=1)
    parser.add_argument('--spawn-gate-failed',action='store_true')
    args=parser.parse_args()
    print(json.dumps([sample(t,args.xyz,args.direction,spawn_gate=not args.spawn_gate_failed)
                      for t in args.time],ensure_ascii=False,indent=2))

if __name__=='__main__':main()
