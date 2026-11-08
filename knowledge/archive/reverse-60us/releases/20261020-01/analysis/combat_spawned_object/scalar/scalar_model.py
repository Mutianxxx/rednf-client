"""Conservative executable 60US skill32 scalar model; runtime inputs are explicit.

Arithmetic uses a declared x87 nearest-even, 64-significand-bit reconstruction
with explicit float32 stores. This is not observed target floating-point state.
"""
from pathlib import Path
from fractions import Fraction
import json,argparse,struct
ROOT=Path(__file__).resolve().parent

class NeedInput(ValueError):pass

def need(data,key):
    if key not in data:raise NeedInput('missing runtime input: '+key)
    return data[key]

def i32(value):
    return ((int(value)+2**31)%2**32)-2**31

def int_result(value):
    n=int(value) # Fraction.__int__ truncates toward zero.
    if not -2**31<=n<2**31:raise ValueError('native integer overflow domain is unsupported')
    return n

def idiv(a,b):
    if b==0:raise ValueError('native signed division by zero')
    return int_result(Fraction(a,b))

def binary(value,precision):
    value=Fraction(value)
    if not value:return value
    sign=-1 if value<0 else 1
    value=abs(value)
    exponent=value.numerator.bit_length()-value.denominator.bit_length()
    def power(n):return Fraction(2**n,1) if n>=0 else Fraction(1,2**(-n))
    if value<power(exponent):exponent-=1
    step=power(exponent-precision+1)
    scaled=value/step
    whole,remainder=divmod(scaled.numerator,scaled.denominator)
    if remainder*2>scaled.denominator or (remainder*2==scaled.denominator and whole%2):whole+=1
    return sign*whole*step

def f32(value):
    # IEEE754 binary32 stores also round subnormal values. Keep this exact so
    # host double rounding does not decide a native float32 tie for us.
    value=Fraction(value)
    minimum_normal=Fraction(1,2**126)
    if value and abs(value)<minimum_normal:
        unit=Fraction(1,2**149)
        scaled=abs(value)/unit
        whole,remainder=divmod(scaled.numerator,scaled.denominator)
        if remainder*2>scaled.denominator or (remainder*2==scaled.denominator and whole%2):whole+=1
        return (-1 if value<0 else 1)*whole*unit
    result=binary(value,24)
    if abs(result)>=2**128:raise ValueError('native float32 overflow/Infinity domain is unsupported')
    return result
def ext(value):return binary(value,64)
PERCENT=Fraction.from_float(struct.unpack('<f',bytes.fromhex('0ad7233c'))[0])

def native_round_model(value,half):
    value=f32(value)
    delta=f32(Fraction(str(half)))
    return int_result(ext(value+delta if value>=0 else value-delta))

def model(level,context,*,section='dungeon',contract=None):
    if contract is None:contract=json.loads((ROOT/'scalar-contract.json').read_text(encoding='utf-8'))
    values=contract['tables'][section]['columns'][0]
    # The callsite passes max(learned level,1), not a hard cap to maximum level20.
    learned=max(int(level),1)
    mode=need(context,'mode_id')
    secondary_mode=need(context,'secondary_mode_gate')
    mode_gate=mode in (4,6,7,9)
    if need(context,'modifier_snapshot_complete') is not True:
        raise NeedInput('a complete modifier snapshot or explicitly declared empty snapshot is required')
    sources=need(context,'modifier_sources')
    if [s['slot'] for s in sources]!=sorted(set(s['slot'] for s in sources)):
        raise ValueError('source slots must be unique and ascending in native 0..22 order')
    if any(not 0<=s['slot']<23 for s in sources):raise ValueError('source slot outside native 0..22')
    for source in sources:
        need(source,'primary')
        need(source,'secondary')
    trace=[]
    def raw_query(lvl):return values[lvl-1] if 1<=lvl<=len(values) else 0
    def query(lvl,with_actor):
        raw=raw_query(lvl)
        if not 1<=lvl<=len(values):
            trace.append(dict(event='query',level=lvl,raw=0,reason='unsigned index outside current table',with_actor=with_actor))
            return 0
        result=raw
        if with_actor:
            for source in sources:
                for group in ('primary','secondary'):
                    rows=source[group]
                    if group=='secondary' and rows:
                        if not need(source,'secondary_gate_12c') or not need(source,'secondary_gate_118'):continue
                    for row_index,row in enumerate(rows):
                        if row['query_kind']!=1 or row['column']!=0:continue
                        if row['skill_key']!=need(context,'runtime_skill_key'):continue
                        if group=='primary' and row['mode_filter']==2 and not mode_gate:continue
                        if row['actor_filter']!=6 and row['actor_filter']!=need(context,'actor_filter'):continue
                        before=result
                        amount=int(row['amount'])
                        if row['percent_mode']!=0:
                            # 54FDB0 stores original signed int as f32, computes
                            # amount*f32(.01)*old+old in x87 then truncates.
                            old=f32(result)
                            percent=ext(ext(amount)*PERCENT)
                            result=int_result(ext(ext(percent*old)+old))
                        else:result=i32(result+amount)
                        trace.append(dict(event='modifier',slot=source['slot'],group=group,row=row_index,
                                          before=before,amount=amount,percent_mode=row['percent_mode'],after=result))
        trace.append(dict(event='query',level=lvl,raw=raw,value=result,with_actor=with_actor))
        return result
    first=query(learned,True)
    metadata=contract['runtime_metadata']
    maximum=need(context,'runtime_maximum_level') if 'runtime_maximum_level' in context else metadata['maximum_level']['current_pvf']
    required=need(context,'runtime_required_level') if 'runtime_required_level' in context else metadata['required_level']['current_pvf']
    step=need(context,'runtime_required_level_range') if 'runtime_required_level_range' in context else metadata['required_level_range']['current_pvf']
    result=first
    env_entered=False
    # Native short-circuit order: context value is not consulted unless both
    # mode and static/runtime metadata gates allow the branch.
    if (mode_gate or secondary_mode) and maximum>1 and step!=0:
        actor_context=need(context,'actor_context_stat')
        if actor_context!=-1:
            env_entered=True
            cap=need(context,'runtime_reference_cap_178')
            if not isinstance(cap,int) or cap<1:raise ValueError('reference cap must be a positive integer in supported domain')
            quotient=i32(idiv(i32(actor_context-required),step)+1)
            effective=min(quotient,cap) # No lower bound clamp is present.
            cap_with_actor=query(cap,True)
            if cap==1:slope=i32(query(2,False)-query(1,False))
            else:slope=idiv(i32(query(cap,False)-query(1,False)),i32(cap-1))
            difference=i32(effective-learned)
            projected=f32(ext(f32(cap_with_actor)-ext(ext(difference)*ext(slope))))
            half=need(context,'rounding_half_global')
            result=native_round_model(projected,half)
            trace.append(dict(event='environment_projection',cap=cap,effective=effective,slope=slope,
                              projected_f32=float(projected),value=result))
            # Bridge mode/type is literal zero and both initial context values
            # are copied. Base550080 ratio is skipped; environment has its own.
            required_at_cap=i32(i32(i32(cap-1)*step)+required)
            if actor_context<required_at_cap:
                factors=need(context,'context_factor_448150')
                a=Fraction(str(need(factors,str(required_at_cap))))
                b=Fraction(str(need(factors,str(actor_context))))
                if b==0:raise ValueError('zero native context denominator unsupported')
                projected=f32(ext(f32(ext(a*ext(result)))/b))
                trace.append(dict(event='environment_context_ratio',numerator_context=required_at_cap,
                                  denominator_context=actor_context,ratio_result_f32=float(projected)))
            else:projected=f32(result)
            multiplier=f32(Fraction(str(need(context,'environment_global_f5e958' if secondary_mode else 'environment_global_f5e954'))))
            result=native_round_model(f32(ext(multiplier*projected)),half)
            trace.append(dict(event='environment_global_multiplier',value=float(multiplier),result=result))
    return dict(schema='60us-skill32-scalar-result-v1',skill_id=32,section=section,
                input_level=int(level),native_query_level=learned,raw_table_value=raw_query(learned),
                raw_table_rows=len(values),beyond_current_maximum=learned>metadata['maximum_level']['current_pvf'],
                initial_modified_value=first,environment_branch_entered=env_entered,scalar=result,
                constructor_atk_damage_float32=float(f32(result)),trace=trace,
                observed_runtime=False,arithmetic_model=contract['arithmetic_model'],
                scope='Generated object ATK.damage scalar only; does not compute final victim damage or prove learnability.')

def evaluate(level,context,**kwargs):
    try:return model(level,context,**kwargs)
    except NeedInput as error:
        return dict(schema='60us-skill32-scalar-result-v1',skill_id=32,input_level=level,
                    status='needs_explicit_runtime_input',reason=str(error),scalar=None,observed_runtime=False)

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--level',type=int,nargs='+',default=[1,30])
    p.add_argument('--section',choices=['dungeon','pvp'],default='dungeon')
    p.add_argument('--context',type=Path,default=ROOT/'unmodified-baseline-context.json')
    args=p.parse_args();context=json.loads(args.context.read_text(encoding='utf-8'))
    print(json.dumps([evaluate(level,context,section=args.section) for level in args.level],ensure_ascii=False,indent=2))

if __name__=='__main__':main()
