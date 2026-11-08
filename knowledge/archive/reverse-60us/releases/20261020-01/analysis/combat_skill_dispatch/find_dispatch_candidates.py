from pathlib import Path
import sys,struct,json,hashlib
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).parent;source=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe');raw=source.read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
md=Cs(CS_ARCH_X86,CS_MODE_32);md.skipdata=True
envelopes=[('Swordman',0x726150,0x730280),('Fighter',0x69d4f0,0x6a71e6),('Gunner_variants_2_5',0x6cfc30,0x6dac88),('Mage',0x6ebc60,0x6f3dfb),('Priest',0x70d7d0,0x711b83)]
def slot(i,s):return len(i.bytes)==6 and i.bytes[0]==0xff and 0x90<=i.bytes[1]<=0x97 and struct.unpack_from('<I',i.bytes,2)[0]==s
def immediate(i):
    if i.mnemonic!='push':return None
    if i.bytes[0]==0x6a:return struct.unpack('<b',i.bytes[1:2])[0]
    if i.bytes[0]==0x68:return struct.unpack('<i',i.bytes[1:5])[0]
    return None
def lastpush(ins,k):
    for j in range(k-1,max(-1,k-14),-1):
        if ins[j].mnemonic in ('call','ret','jmp'):break
        if ins[j].mnemonic=='push':return ins[j],immediate(ins[j])
    return None,None
def previous_pushes(ins,k,limit):
    out=[]
    for j in range(k-1,max(-1,k-40),-1):
        if ins[j].mnemonic in ('call','ret','jmp'):break
        if ins[j].mnemonic=='push':
            out.append({'va':hex(ins[j].address),'expression':ins[j].op_str,'literal':immediate(ins[j])})
            if len(out)==limit:break
    return out
def this_assignment(ins,k):
    for j in range(k-1,max(-1,k-15),-1):
        if ins[j].mnemonic in ('call','ret','jmp'):break
        if ins[j].mnemonic=='mov' and ins[j].op_str.startswith('ecx, '):
            return {'va':hex(ins[j].address),'expression':ins[j].op_str.split(', ',1)[1]}
    return None
def fmt(i):return f'{i.address:08X} {i.bytes.hex():20} {i.mnemonic:8} {i.op_str}'
rows=[];local_paths=[];rea_ranges=[]
for p in sorted((ROOT.parent/'rea'/'results').glob('0*-procedure.json')):
    d=json.loads(p.read_text(encoding='utf8'))['structuredContent']
    rea_ranges.append({'file':str(p),'evidence_id':d['evidence_id'],'procedure':d['parameters']['procedure'],'body':d['normalized_result']['body'],'source_sha256':d['subject']['digest']['sha256'],'limitations':'Ghidra address-set observations with Reference and decompiler switch analyzers disabled; absence from these ranges is not a negative code-ownership claim'})
for label,start,end in envelopes:
    off=pe.get_offset_from_rva(start-base);ins=list(md.disasm(raw[off:off+end-start],start));cons=[k for k,i in enumerate(ins) if slot(i,0x768)];states=[k for k,i in enumerate(ins) if slot(i,0x28c)]
    for ci,k in enumerate(cons):
        push,skill=lastpush(ins,k)
        if skill is None:continue
        nextk=cons[ci+1] if ci+1<len(cons) else len(ins)
        candidates=[z for z in states if k<z<nextk and ins[z].address-ins[k].address<0x600]
        for z in candidates:
            statepush,state=lastpush(ins,z)
            if state is None:continue
            low=max(0,k-18);hi=min(len(ins),z+9)
            record={'native_class':label,'search_envelope_start':hex(start),'search_envelope_end':hex(end),'skill_id':skill,'consume_call_va':hex(ins[k].address),'skill_push_va':hex(push.address),'state':state,'request_call_va':hex(ins[z].address),'state_push_va':hex(statepush.address),'distance':ins[z].address-ins[k].address,'status':'candidate; sequential proximity only; CFG, stack argument ownership and job-variant guards require manual verification','context_start_va':hex(ins[low].address),'context_end_va':hex(ins[hi-1].address+len(ins[hi-1].bytes)),'context_asm':'\n'.join(fmt(i) for i in ins[low:hi])}
            rows.append(record)
            # Strictly bounded proof: the consumption call's AL-failure branch skips
            # the request, while success falls through without any other branch.
            # This establishes a conditional local path, not global skill behavior.
            middle=ins[k+3:z]
            if k+2<z and ins[k+1].mnemonic=='test' and ins[k+1].op_str=='al, al' and ins[k+2].mnemonic=='je':
                fail=int(ins[k+2].op_str,0)
                if fail>=ins[z].address+len(ins[z].bytes) and all(not (i.mnemonic.startswith('j') or i.mnemonic.startswith('ret') or i.mnemonic.startswith('loop')) for i in middle):
                    body=next((r for r in rea_ranges if int(r['procedure'],0)==start),None)
                    member=body and all(any(int(b['start'],0)<=i.address and i.address+len(i.bytes)-1<=int(b['end'],0) for b in body['body']['ranges']) for i in ins[k:z+1])
                    if member:
                        rec={k:v for k,v in record.items() if k not in ('context_asm','status')}
                        pushes=previous_pushes(ins,k,4);consume_this=this_assignment(ins,k);request_this=this_assignment(ins,z)
                        if len(pushes)!=4:continue
                        if not consume_this or not request_this or consume_this['expression']!=request_this['expression'] or consume_this['expression'] not in ('esi','edi','ebx'):continue
                        thisreg=consume_this['expression']
                        if any(i.op_str.split(',',1)[0]==thisreg and i.mnemonic not in ('test','cmp','push','call') for i in middle):continue
                        path_start=pushes[-1]['va'];path_end=ins[z].address+len(ins[z].bytes);path_offset=pe.get_offset_from_rva(int(path_start,0)-base);path_bytes=raw[path_offset:path_offset+path_end-int(path_start,0)]
                        rec.update({'status':'local_success_fallthrough_verified','consume_this_assignment':consume_this,'request_this_assignment':request_this,'consume_stack_args_in_callee_order':pushes,'failure_branch_va':hex(ins[k+2].address),'failure_target_va':hex(fail),'path_asm':'\n'.join(fmt(i) for i in ins[k:z+1]),'path_bytes_start_va':path_start,'path_bytes_file_offset':path_offset,'path_bytes_length':len(path_bytes),'path_bytes_sha256':hashlib.sha256(path_bytes).hexdigest(),'path_bytes_hex':path_bytes.hex(),'rea_body_evidence_id':body['evidence_id'],'boundary':'Literal skill ID at +768 and literal state at +28C connected on AL-success fallthrough, both calls use the same explicit nonvolatile-register ECX assignment and the register is not written between calls (assuming standard MSVC x86 callee-save ABI); upstream state/input/job gates, vector contents and full controller semantics are separate; no claim of runtime execution'})
                        local_paths.append(rec)
    print(label,'consume_calls',len(cons),'state_calls',len(states),'candidate_pairs',sum(x['native_class']==label for x in rows))
(ROOT/'dispatch-candidates.json').write_text(json.dumps(rows,indent=2),encoding='utf8')
(ROOT/'local-dispatch-paths.json').write_text(json.dumps({'source':str(source),'source_sha256':hashlib.sha256(raw).hexdigest(),'method':'Capstone literal stack arguments plus AL-test/JE bypass and branch-free success fallthrough, constrained to observed Ghidra body ranges','rea_procedure_sources':rea_ranges,'paths':local_paths},indent=2),encoding='utf8')
for label,_,_ in envelopes:print(label,'local_success_fallthrough_verified',sum(x['native_class']==label for x in local_paths))
if '--list' in sys.argv:
    for x in local_paths:print(x['native_class'],x['skill_id'],'->',x['state'],x['consume_call_va'],x['request_call_va'])
