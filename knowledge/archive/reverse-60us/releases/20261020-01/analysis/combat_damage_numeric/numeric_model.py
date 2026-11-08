"""Bounded 60US numeric stages with explicit decoded runtime operands.

The initial input is B at 8B8808, after earlier element/RNG stages. The output
stops at 8B8B41; it is not the integer returned by 8B8650 or final HP damage.
"""
from pathlib import Path
from fractions import Fraction
import sys
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent/'combat_spawned_object/scalar'))
from scalar_model import f32,binary,PERCENT,need,NeedInput,int_result

def val(x):return Fraction(str(x))
def sf(x):return f32(val(x))
def n(data,offset):return need(data,'numeric_'+offset)
def nf(data,offset):return sf(n(data,offset))
def signed8(x):return ((int(x)+128)%256)-128
def signed16(x):return ((int(x)+32768)%65536)-32768
def signed32(x):return ((int(x)+2**31)%2**32)-2**31
def ni(data,offset):return signed32(n(data,offset))
POSTCRITICAL_MULTIPLIER=sf('1.100000023841858') # DF5190 bytes cdcc8c3f
def result(x,**extra):return dict(value_f32=float(f32(x)),exact_fraction=str(x),is_final_damage=False,**extra)
def op(precision):
 if precision not in (53,64):raise ValueError('only explicitly declared x87 significand precision 53 or 64 is supported')
 return lambda x:binary(x,precision)

def defense_ratio(numeric,external,*,precision=64):
 """8B7C90; output1 is defense ratio, output2 is extra percent/100."""
 e=op(precision);mode=signed8(n(numeric,'18a'));kind=signed8(n(numeric,'5'))
 if mode==4:level=50
 elif mode in (6,7):level=signed16(need(external,'mode'+str(mode)+'_table_level'))
 else:level=signed8(n(numeric,'18b'))
 if kind in (0,1):
  base=ni(numeric,'8b' if kind==0 else '97')
  bonus=ni(numeric,'8f' if kind==0 else '9b')
  defense=f32(e(e(e(bonus*PERCENT)+1)*base))
  scale=sf(need(external,'protected_global_10bfeb0' if kind==0 else 'protected_global_10bfed0'))
  extra=f32(e(nf(numeric,'93' if kind==0 else '9f')*PERCENT))
 else:defense=scale=extra=Fraction(0)
 defense=f32(e(val(need(external,'448c10_victim_1'))*defense))
 if n(numeric,'1bc'):scale=e(scale+scale)
 denominator=max(Fraction(1),e(e(scale*level)+defense))
 ratio=f32(e(defense/denominator))
 negative_low_level=defense<0 and level<10
 if negative_low_level:ratio=f32(e(defense*sf('0.0024999999441206455')))
 return dict(ratio_f32=float(ratio),ratio_exact=str(ratio),extra_f32=float(extra),extra_exact=str(extra),
  adjusted_defense_f32=float(defense),effective_level=level,denominator_exact=str(denominator),
  negative_defense_low_level_override=negative_low_level,is_final_damage=False)

def defense_stage(incoming,numeric,external,*,precision=64):
 """8B8808..8B88BF including caller's flags199 gate."""
 e=op(precision);b=sf(incoming);kind=signed8(n(numeric,'5'))
 entered=(int(n(numeric,'199'))&0x11)==0x11 and kind!=2 and not n(numeric,'e')
 ratio=None
 if entered:
  ratio=defense_ratio(numeric,external,precision=precision)
  reduction=e(e(1-Fraction(ratio['ratio_exact']))-e(Fraction(ratio['extra_exact'])*nf(numeric,'5f')))
  b=f32(e(reduction*b))
  if kind in (0,1):
   stat=nf(numeric,'a3' if kind==0 else 'a7')
   if signed8(n(numeric,'18a'))!=4:
    stat=f32(e(val(need(external,'448c10_victim_4' if kind==0 else '448c10_victim_6'))*stat))
   divisor=sf(need(external,'protected_global_10bfea8' if kind==0 else 'protected_global_10bfeb8'))
   if not divisor:raise ValueError('zero native divisor is outside the supported finite domain')
   b=f32(e(b-e(stat/divisor)))
 return result(b,entered=entered,ratio=ratio)

def attacker_stat_stage(incoming,numeric,external,*,precision=64):
 """8B88BF..8B893A; the magic 0xB3B2 exception is preserved."""
 e=op(precision);b=sf(incoming);kind=signed8(n(numeric,'5'));suppressed=False
 if kind in (0,1):
  stat=nf(numeric,'3f' if kind==0 else '43')
  if signed8(n(numeric,'18a'))!=4:
   stat=f32(e(val(need(external,'448c10_attacker_3' if kind==0 else '448c10_attacker_5'))*stat))
  suppressed=kind==1 and n(numeric,'1c1') and int(n(numeric,'1c2'))==0xB3B2
  if not suppressed:
   divisor=sf(need(external,'protected_global_10bfee0' if kind==0 else 'protected_global_10bfe80'))
   if not divisor:raise ValueError('zero native divisor is outside the supported finite domain')
   b=f32(e(e(stat/divisor)+b))
 return result(b,magic_exception=bool(suppressed))

def absolute_stage(incoming,numeric,external,*,precision=64):
 """8B893A..8B8A62 arithmetic; excludes side effects of victim.slot320."""
 e=op(precision);b=sf(incoming);kind=signed8(n(numeric,'5'));absolute=Fraction(0);subtract=Fraction(0)
 callback=False
 if kind in (0,1):
  absolute=nf(numeric,'f')
  if n(numeric,'4'):absolute=e(absolute+e(ni(numeric,'63' if kind==0 else '67')*nf(numeric,'ab')))
  factor=e(e(nf(numeric,'6')*PERCENT)+1)
  absolute=e(factor*absolute)
  factor=e(e(nf(numeric,'37' if kind==0 else '3b')*PERCENT)+1)
  absolute=f32(e(absolute*factor))
  added=e(val(need(external,'448c10_attacker_7' if kind==0 else '448c10_attacker_9'))*absolute)
  b=f32(e(added+b))
  if (int(n(numeric,'199'))&0x11)==0x11 and not n(numeric,'e'):
   subtract=e(ni(numeric,'af' if kind==0 else 'b3')*nf(numeric,'5f'))
   subtract=f32(e(subtract+ni(numeric,'b7' if kind==0 else 'bb')))
   subtract=e(val(need(external,'448c10_victim_8' if kind==0 else '448c10_victim_10'))*subtract)
   b=f32(e(b-subtract))
  callback=True
 return result(b,absolute_component_before_context_f32=float(absolute),absolute_subtraction_exact=str(subtract),victim_slot320_callback_reached=callback)

def critical_stage(incoming,numeric,external,*,precision=64):
 """8B7AB0. Caller supplies the signed EAX return of 8AE160."""
 e=op(precision);b=sf(incoming);kind=signed8(n(numeric,'5'));flags=int(n(numeric,'195'))
 rate=f32(e(nf(numeric,'13')+3))
 if not n(numeric,'18e'):
  if (flags&0x11)==0x11 and kind in (0,1):rate=f32(e(rate+nf(numeric,'4b' if kind==0 else '4f')))
 elif (flags&0x81)==0x81:rate=f32(e(rate+nf(numeric,'5b')))
 if n(numeric,'1b5'):
  rate=f32(e(rate+nf(numeric,'17')))
  if (flags&0x11)==0x11 and kind in (0,1):rate=f32(e(rate+nf(numeric,'53' if kind==0 else '57')))
 if (int(n(numeric,'199'))&0x11)==0x11:rate=f32(e(rate-nf(numeric,'bf')))
 random=signed32(need(external,'8ae160_return'))
 # IDIV truncates toward zero; Python's '%' alone is wrong for negative EAX.
 remainder=random-int(Fraction(random,10000))*10000
 critical=e(rate*100)>remainder
 multiplier=Fraction(1)
 if critical:
  multiplier=sf(need(external,'protected_global_10bfe90'))
  if (flags&0x11)==0x11:multiplier=e(multiplier*nf(numeric,'6f'))
  b=f32(e(multiplier*b))
 return result(b,critical=critical,numeric_1a5=int(critical),effective_rate_f32=float(rate),
  random_remainder=remainder,multiplier_exact=str(multiplier))

def postcritical_stage(incoming,numeric,external,*,precision=64):
 """8B8A87..8B8B41; FST stores do not reload/round the x87 stack."""
 e=op(precision);b=sf(incoming);extra=None
 if n(numeric,'1a6'):
  original=b;b=e(b*POSTCRITICAL_MULTIPLIER)
  extra=int_result(e(b-original))
 b=e(b*nf(numeric,'1b'));b=e(b*PERCENT)
 b=e(b*ni(numeric,'1ac'));b=e(b*PERCENT)
 stored=f32(b)
 for flag,amount in [('c3','1f'),('c4','23'),('c5','27')]:
  if n(numeric,flag):
   b=e(b*nf(numeric,amount));b=e(b*PERCENT);stored=f32(b)
 if (int(n(numeric,'195'))&0x111)==0x111:b=e(b*nf(numeric,'6b'));stored=f32(b)
 minimum_applied=b<1
 if minimum_applied:b=Fraction(1);stored=Fraction(1)
 return result(b,stored_f32=float(stored),stored_exact=str(stored),numeric_1a7=extra,minimum_one_applied=minimum_applied)

def bounded(incoming,numeric,external,*,precision=64):
 """Compute a declared snapshot from 8B8808 through 8B8B41."""
 a=defense_stage(incoming,numeric,external,precision=precision)
 b=attacker_stat_stage(a['exact_fraction'],numeric,external,precision=precision)
 c=absolute_stage(b['exact_fraction'],numeric,external,precision=precision)
 if c['victim_slot320_callback_reached'] and need(external,'victim_slot320_does_not_mutate_numeric_snapshot') is not True:
  raise NeedInput('provide numeric snapshot after victim.slot320 or establish no mutation for this bounded calculation')
 value=max(Fraction(0),Fraction(c['exact_fraction']))
 d=critical_stage(value,numeric,external,precision=precision)
 out=postcritical_stage(d['exact_fraction'],numeric,external,precision=precision)
 return dict(schema='60us-bounded-common-numeric-v1',incoming_at='8B8808',outgoing_at='8B8B41',
  **out,critical=d['critical'],numeric_1a5=d['numeric_1a5'],trace=dict(defense=a,attacker_stat=b,absolute=c,critical=d),
  final_victim_damage=None,observed_client_runtime=False,x87_precision_fixture=precision)
