"""Bounded executable bridge and first native numeric stages, not final damage."""
from pathlib import Path
from fractions import Fraction
import sys,json,argparse
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent))
from scalar_model import f32,ext,PERCENT,NeedInput,need


def value(x):return Fraction(str(x))


def initial_multiplier(atk,operands):
    """8B79C8..8B7A02; result is explicitly stored as binary32."""
    base=f32(value(need(atk,'damage')))
    attack_type=need(atk,'attack_type')
    if need(atk,'weapon_damage_apply'):
        if attack_type==1:base=ext(base+f32(value(need(operands,'numeric_33'))))
        elif attack_type in (0,2):base=ext(base+f32(value(need(operands,'numeric_2f'))))
    bonus=f32(value(need(atk,'damage_bonus')))
    factor=ext(ext(bonus*PERCENT)+1)
    result=f32(ext(base*factor))
    return dict(stage='8B79C8..8B7A02',value_f32=float(result),exact_fraction=str(result),
                is_final_damage=False)


def normal_base(atk,numeric,external):
    """8B79C0 through 8B866F, with raw operand/factor samples explicit.

    Numeric names are byte offsets, not inferred source names. 448C10 returns
    x87 values; supplied decimal strings are assumed exact return samples.
    """
    first=initial_multiplier(atk,numeric)
    result=Fraction(first['exact_fraction'])
    attack_type=atk['attack_type'];trace=[first]
    if attack_type in (0,1):
        offset='numeric_37' if attack_type==0 else 'numeric_3b'
        amount=f32(value(need(numeric,offset)))
        result=f32(ext(ext(ext(amount*PERCENT)+1)*result))
        trace.append(dict(stage='8B7A04..8B7A21',value_f32=float(result)))
        stat=f32(value(need(numeric,'numeric_3f' if attack_type==0 else 'numeric_43')))
        if need(numeric,'numeric_18a')!=4:
            sample=value(need(external,'448c10_attacker_3' if attack_type==0 else '448c10_attacker_5'))
            stat=f32(ext(sample*stat))
        denominator=f32(value(need(external,'protected_global_10bfed8' if attack_type==0 else 'protected_global_10bfe78')))
        if not denominator:raise ValueError('native zero denominator unsupported')
        factor=ext(ext(stat/denominator)+1)
        result=f32(ext(factor*result))
        trace.append(dict(stage='8B7A24..8B7A8C',value_f32=float(result)))
    context_factor=value(need(external,'448c10_attacker_0'))
    final_factor=ext(f32(value(need(numeric,'numeric_47')))+1)
    result=f32(ext(ext(context_factor*result)*final_factor))
    trace.append(dict(stage='8B7A8F..8B7AAD then8B866F',value_f32=float(result)))
    return dict(value_f32=float(result),exact_fraction=str(result),trace=trace,is_final_damage=False)


def bridge(dynamic_scalar,context):
    if need(context,'slot10_registration_reached') is not True:
        raise NeedInput('current ATK installation through slot10 must be established')
    if need(context,'current_atk_snapshot_unchanged') is not True:
        raise NeedInput('provide a current ATK snapshot after later installation/mutation')
    atk=dict(damage=float(f32(int(dynamic_scalar))),absolute_damage=0,damage_bonus=0,attack_type=1,
             weapon_damage_apply=False,elemental_properties=[])
    override=need(context,'action_atk_override')
    if override is not None:
        for field in ('damage','absolute_damage','damage_bonus','attack_type','weapon_damage_apply'):
            need(override,field)
        atk=dict(override)
    if need(context,'normal_base_route_established') is not True:
        raise NeedInput('8B85F0 normal base route must be established; alternate path is outside this model')
    if not atk['weapon_damage_apply'] and atk['damage']<=0 and atk['absolute_damage']<=0:
        return dict(schema='60us-skill32-scalar-consumer-result-v1',input_dynamic_scalar=int(dynamic_scalar),
                    installed_current_atk=atk,common_numeric_entry_result=0,first_numeric_stage=None,
                    reason='467480 rejects nonpositive damage with no weapon apply or positive absolute damage',
                    final_victim_damage=None,observed_runtime=False)
    first=initial_multiplier(atk,context.get('numeric_operands',{}))
    return dict(schema='60us-skill32-scalar-consumer-result-v1',input_dynamic_scalar=int(dynamic_scalar),
        installed_current_atk=atk,source='template+5DC via49F010/4EDCD0 to current+260' if override is None else 'explicit action ATK override',
        first_numeric_stage=first,final_victim_damage=None,
        final_damage_boundary='8B79C0 continues attacker factors;8B8650 continues random/defense/other factors and C01544;4B28D0 may modify the returned integer before HP subtraction.',
        observed_runtime=False)


def evaluate(dynamic_scalar,context):
    try:return bridge(dynamic_scalar,context)
    except NeedInput as error:return dict(status='needs_explicit_runtime_input',reason=str(error),final_victim_damage=None)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--scalar',nargs='+',type=int,default=[552,5158])
    parser.add_argument('--context',type=Path,default=ROOT/'declared-template-context.json')
    args=parser.parse_args();context=json.loads(args.context.read_text(encoding='utf-8'))
    print(json.dumps([evaluate(x,context) for x in args.scalar],indent=2,ensure_ascii=False))

if __name__=='__main__':main()
