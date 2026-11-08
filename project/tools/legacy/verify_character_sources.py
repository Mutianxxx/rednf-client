"""Cross-check C++ CharacterCatalog source export against independent PVF reads.

No build, packaging, GUI, game-state injection, or save access. Outputs stay in
reports/combat-native-reverse/catalog-crosscheck; each run preserves failures.
This checks source fidelity, not playable character/controller completeness.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import posixpath
import re
import subprocess
import sys

PROJECT = Path(__file__).resolve().parents[1]
REPORT_ROOT = PROJECT/'reports/combat-native-reverse/catalog-crosscheck'
BASELINE = PROJECT/'reports/combat-native-reverse/all-characters'
PVF_SHA256 = 'd13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d'
sys.path.insert(0, str(PROJECT.parent/'dnf-result/tools'))
from pvf_reader import Pvf, ScriptDecoder, normalized


def file_hash(path):
    with Path(path).open('rb') as handle:
        return hashlib.file_digest(handle,'sha256').hexdigest()


def digest(data):
    return hashlib.sha256(data).hexdigest()


def dump(path, data):
    path.write_text(json.dumps(data,ensure_ascii=False,indent=2,allow_nan=False)+'\n',encoding='utf-8')


def field_view(field):
    return {k:field[k] for k in ('tag','offset','values')}


def value_fields(model, wanted):
    return next((f['values'] for f in model['fields'] if f['tag'].lower()==wanted.lower()),[])


def resource_tag(tag):
    return (not tag.startswith('[/') and 'motion' in tag) or tag.lower() in ('[attack info]','[etc attack info]','[jumpattack info]','[dashattack info]')


def resource_view(model, entries):
    result = []
    parent = str(PurePosixPath(model['path']).parent)
    for field in model['fields']:
        if not resource_tag(field['tag']):
            continue
        for index,literal in enumerate(field['values']):
            if not isinstance(literal,str):
                continue
            path = normalized(posixpath.normpath(parent+'/'+literal)) if literal else ''
            result.append(dict(tag=field['tag'],field_offset=field['offset'],value_index=index,literal=literal,path=path,exists=bool(path) and path in entries))
    return result


def expected_stats(model):
    # Slice the independent decoded field stream by source headers. The numeric
    # growth/awakening labels are preserved, not evaluated as class inheritance.
    fields, result, growth = model['fields'], [], 0
    for index,field in enumerate(fields):
        tag = field['tag'].lower()
        grow = re.fullmatch(r'\[growtype (\d+)\]',tag)
        awake = re.fullmatch(r'\[awakening (\d+)\]',tag)
        if tag != '[initial value]' and not grow and not awake:
            continue
        if tag == '[initial value]':
            growth = 0
        elif grow:
            growth = int(grow[1])
        stop, body = model['size'], []
        for following in fields[index+1:]:
            following_tag = following['tag'].lower()
            if following_tag=='[initial value]' or re.fullmatch(r'\[(growtype|awakening) \d+\]',following_tag) or resource_tag(following_tag):
                stop=following['offset']
                break
            body.append(field_view(following))
        result.append(dict(tag=field['tag'],growtype=growth,awakening=int(awake[1]) if awake else 0,offset=field['offset'],end_offset=stop,fields=body))
    return result


def differences(expected, actual, path='$', limit=12):
    found=[]
    def add(location, kind, left=None, right=None):
        if len(found)<limit:
            item=dict(path=location,kind=kind)
            if left is not None:item['expected']=left
            if right is not None:item['actual']=right
            found.append(item)
    def visit(left,right,location):
        if len(found)>=limit:return
        if isinstance(left,dict) and isinstance(right,dict):
            for key in sorted(set(left)|set(right)):
                if key not in right:add(location+'.'+key,'missing_key',left[key])
                elif key not in left:add(location+'.'+key,'unexpected_key',right=right[key])
                else:visit(left[key],right[key],location+'.'+key)
        elif isinstance(left,list) and isinstance(right,list):
            if len(left)!=len(right):add(location,'length',len(left),len(right))
            for index,(lv,rv) in enumerate(zip(left,right)):
                visit(lv,rv,f'{location}[{index}]')
                if len(found)>=limit:break
        elif left != right or (isinstance(left,bool) != isinstance(right,bool)):
            add(location,'value',left,right)
    visit(expected,actual,path)
    return found


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,default=PROJECT/'build/dnf_inspect.exe')
    parser.add_argument('--client',type=Path)
    args=parser.parse_args()
    binary=args.binary.resolve()
    client=(args.client or next(PROJECT.parent.glob('DNF1031*'))).resolve()
    pvf_path=client/'Script.pvf'
    binary_hash, source_hash=file_hash(binary),file_hash(pvf_path)
    stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ')
    report=REPORT_ROOT/(stamp+'-'+binary_hash[:8])
    report.mkdir(parents=True,exist_ok=False)
    if source_hash!=PVF_SHA256:
        dump(report/'failure.json',dict(kind='source_version_changed',expected=PVF_SHA256,actual=source_hash))
        raise RuntimeError('PVF version changed; no cross-version comparison permitted')
    command=[str(binary),str(client),'--characters','source','_',str(report/'catalog-source.json')]
    result=subprocess.run(command,cwd=PROJECT,capture_output=True,timeout=90)
    (report/'inspector.stdout.log').write_bytes(result.stdout)
    (report/'inspector.stderr.log').write_bytes(result.stderr)
    checks=[]
    def check(name,expected,actual):
        diffs=differences(expected,actual)
        item=dict(name=name,passed=not diffs)
        if diffs:item['differences']=diffs
        checks.append(item)
    check('inspector exit code',0,result.returncode)
    if result.returncode or not (report/'catalog-source.json').exists():
        payload=dict(binary=str(binary),binary_sha256=binary_hash,checks=checks,status='failed',source_only=True)
        dump(report/'verification.json',payload)
        print(json.dumps(payload,ensure_ascii=False));return 1
    cpp=json.loads((report/'catalog-source.json').read_text(encoding='utf-8'))
    check('export has native skill SD sources',True,'native_skill_data' in cpp)
    check('native SD source count',7,len(cpp.get('native_skill_data',[])))
    if 'native_skill_data' not in cpp:
        dump(report/'binary-outdated.json',dict(binary_sha256=binary_hash,reason='Missing native_skill_data export; request coordinated rebuild.'))
    pvf=Pvf(pvf_path)
    decoder=ScriptDecoder(pvf)
    old_inventory=json.loads((BASELINE/'inventory.json').read_text(encoding='utf-8'))
    old_manifest=json.loads((BASELINE/'source-manifest.json').read_text(encoding='utf-8'))
    manifest_rows={row['path']:row for row in old_manifest['raw_sources']}
    check('prior independent baseline PVF identity',source_hash,old_inventory['pvf']['sha256'])
    source_records=[]
    source_models={}
    def verify_source(label,actual,path):
        path=normalized(path)
        model=decoder.script(path)
        source_models[path]=model
        raw=pvf.read(path)
        try:
            raw_cpp=bytes(actual.get('bytes',[]))
        except (TypeError,ValueError):
            raw_cpp=b''
        check(label+' path',path,actual.get('path'))
        check(label+' byte_count',len(raw),actual.get('byte_count'))
        check(label+' exact original decrypted bytes',list(raw),list(raw_cpp))
        check(label+' original bytes SHA256',digest(raw),digest(raw_cpp))
        expected_tokens=[{k:t[k] for k in ('offset','type','value')}|{'raw':t['raw_int']} for t in model['tokens']]
        actual_tokens=[{k:t.get(k) for k in ('offset','type','raw','value')} for t in actual.get('tokens',[])]
        check(label+' all ordered token offsets/types/raw/value',expected_tokens,actual_tokens)
        check(label+' ordered fields/offsets/resolved values',[field_view(f) for f in model['fields']],actual.get('fields'))
        entry=pvf.by_name[path]
        provenance=actual.get('provenance',{})
        check(label+' PVF member offset/size/checksum',dict(offset=entry['offset'],size=entry['size'],crc=entry['checksum']),{k:provenance.get(k) for k in ('offset','size','crc')})
        if path in manifest_rows:
            check(label+' previously delivered independent raw hash',manifest_rows[path]['sha256'],digest(raw))
        source_records.append(dict(label=label,path=path,size=len(raw),sha256=digest(raw),token_count=len(expected_tokens),field_count=len(model['fields']),provenance=dict(offset=entry['offset'],size=entry['size'],crc=entry['checksum'])))
        return model
    def registration_rows(path,base):
        model=source_models.get(path) or decoder.script(path)
        records=decoder.list_records(path)
        result=[]
        for ordinal,row in enumerate(records):
            idx=row['token_index']
            target=normalized(posixpath.normpath(base+'/'+row['value']))
            result.append(dict(id=row['id'],ordinal=ordinal,offset=model['tokens'][idx]['offset'],path_offset=model['tokens'][idx+1]['offset'],literal=row['value'],path=target,exists=target in pvf.by_name))
        return result
    root_char=verify_source('character root list',cpp['characters']['source'],'character/character.lst')
    root_skill=verify_source('skill root list',cpp['skill_lists']['source'],'skill/skilllist.lst')
    char_regs=registration_rows(root_char['path'],'character')
    skill_regs=registration_rows(root_skill['path'],'skill')
    check('all character registry rows with ID/ordinal/offset/path',char_regs,cpp['characters'].get('entries'))
    check('all skill root registry rows with ID/ordinal/offset/path',skill_regs,cpp['skill_lists'].get('entries'))
    check('character root issues',[],cpp['characters'].get('issues'))
    check('skill root issues',[],cpp['skill_lists'].get('issues'))
    verify_source('default character settings',cpp['default_settings'],'character/characteretc/default.etc')
    sd_paths=sorted(p for p in pvf.by_name if p.startswith('data/skill/') and p.endswith('.sd'))
    check('all SD paths and source order',sd_paths,[r.get('path') for r in cpp.get('native_skill_data',[])])
    for actual in cpp.get('native_skill_data',[]):
        path=actual.get('path','')
        if path in sd_paths:verify_source(path,actual,path)
    definitions=cpp.get('definitions',[])
    check('definition count',len(char_regs),len(definitions))
    check('definition IDs and source order',[r['id'] for r in char_regs],[r.get('registration',{}).get('id') for r in definitions])
    independent_resources=[]
    motion_slots=attack_slots=empty_slots=empty_motion_slots=empty_attack_slots=registered_skills=stat_blocks=0
    for position,reg in enumerate(char_regs):
        if position>=len(definitions):break
        actual=definitions[position]
        job=reg['id'];label=f'job {job}'
        check(label+' original registration',reg,actual.get('registration'))
        model=verify_source(label+' CHR',actual.get('source',{}),reg['path'])
        old_path=BASELINE/old_inventory['characters'][position]['model_file']
        old_model=json.loads(old_path.read_text(encoding='utf-8'))['chr_model']
        check(label+' previously delivered independent CHR tokens',old_model['tokens'],model['tokens'])
        setting_path='character/characteretc/'+PurePosixPath(reg['path']).stem+'.etc'
        verify_source(label+' characteretc',actual.get('settings',{}),setting_path)
        skill_list=next(r for r in skill_regs if r['id']==job)
        verify_source(label+' skill list',actual.get('skills',{}).get('source',{}),skill_list['path'])
        rows=registration_rows(skill_list['path'],'skill')
        registered_skills+=len(rows)
        check(label+' complete ordered skill registrations',rows,actual.get('skills',{}).get('entries'))
        check(label+' skill list issues',[],actual.get('skills',{}).get('issues'))
        expected_resources=resource_view(model,pvf.by_name)
        check(label+' complete ordered motion and ATK slots',expected_resources,actual.get('resources'))
        independent_resources.append(dict(job_id=job,resources=expected_resources))
        motion_slots+=sum('motion' in r['tag'] for r in expected_resources)
        attack_slots+=sum('motion' not in r['tag'] for r in expected_resources)
        empty_slots+=sum(not r['literal'] for r in expected_resources)
        empty_motion_slots+=sum(not r['literal'] and 'motion' in r['tag'] for r in expected_resources)
        empty_attack_slots+=sum(not r['literal'] and 'motion' not in r['tag'] for r in expected_resources)
        expected=expected_stats(model)
        stat_blocks+=len(expected)
        check(label+' source stat block boundaries and growth context',expected,actual.get('stat_blocks'))
        job_values=value_fields(model,'[job]')
        check(label+' job tag',job_values[0] if job_values else '',actual.get('job'))
        check(label+' ordered growth names',value_fields(model,'[growtype name]'),actual.get('growtype_names'))
        check(label+' Creator deferred only for job ID 10',job==10,actual.get('runtime_deferred_by_user'))
        check(label+' definition issues (empty slots are retained)',[],actual.get('issues'))
    check('catalog issues',[],cpp.get('issues'))
    check('independent motion slot total',old_inventory['counts']['registered_motion_reference_slots'],motion_slots)
    check('independent attackinfo slot total',old_inventory['counts']['registered_attackinfo_reference_slots'],attack_slots)
    check('independent empty motion slot total',old_inventory['counts']['empty_motion_reference_slots'],empty_motion_slots)
    check('independent registered skill row total',old_inventory['counts']['registered_skill_rows'],registered_skills)
    check('inspector binary unchanged during run',binary_hash,file_hash(binary))
    check('original PVF unchanged during run',source_hash,file_hash(pvf_path))
    pvf.close()
    counts=dict(characters=len(definitions),source_files=len(source_records),tokens=sum(s['token_count'] for s in source_records),fields=sum(s['field_count'] for s in source_records),decrypted_bytes=sum(s['size'] for s in source_records),skill_registration_rows=registered_skills,motion_slots=motion_slots,attackinfo_slots=attack_slots,empty_slots=empty_slots,empty_motion_slots=empty_motion_slots,empty_attackinfo_slots=empty_attack_slots,stat_blocks=stat_blocks,native_sd=len(cpp.get('native_skill_data',[])))
    payload=dict(scope='Independent source fidelity cross-check only; not playable characters, controllers, balance, visuals or physical-input acceptance.',status='passed' if all(c['passed'] for c in checks) else 'failed',binary=dict(path=str(binary),sha256=binary_hash),pvf=dict(path=str(pvf_path),sha256=source_hash),command=command,counts=counts,passed=sum(c['passed'] for c in checks),failed=sum(not c['passed'] for c in checks),checks=checks,source_records=source_records,tool_sha256=file_hash(Path(__file__)),independent_parser=dict(path='../dnf-result/tools/pvf_reader.py',sha256=file_hash(PROJECT.parent/'dnf-result/tools/pvf_reader.py')))
    dump(report/'verification.json',payload)
    dump(report/'independent-resource-slots.json',independent_resources)
    failures=[c for c in checks if not c['passed']]
    dump(report/'differences.json',failures)
    dump(REPORT_ROOT/'latest.json',dict(run=str(report.relative_to(PROJECT)).replace('\\','/'),status=payload['status'],binary_sha256=binary_hash,pvf_sha256=source_hash,counts=counts,passed=payload['passed'],failed=payload['failed']))
    description=f'''# C++ CharacterCatalog 与当前PVF独立来源交叉核对

本次状态：**{payload['status']}**，{payload['passed']}项通过、{payload['failed']}项失败。运行目录：`{report.relative_to(PROJECT).as_posix()}`。

使用现有`dnf_inspect.exe --characters source`导出，独立Python解析器再次只读打开当前PVF，对比43份源文件：11 CHR、两份根list、11职业技能list、11 characteretc、default.etc及7份SD。逐项比较原字节、SHA256、PVF成员offset/size/checksum、全部有序token的offset/type/raw/value、字段及解析文本；没有从C++导出反推期望值。

实际比较{counts['tokens']}个token、{counts['fields']}个字段、{counts['decrypted_bytes']}字节、{counts['skill_registration_rows']}条局部技能注册、{counts['motion_slots']}个motion槽和{counts['attackinfo_slots']}个ATK槽；{counts['empty_slots']}个空槽（motion {counts['empty_motion_slots']}、ATK {counts['empty_attackinfo_slots']}）及原重复ATK项保持顺序。另比较{counts['stat_blocks']}个原始成长/觉醒字段区间、职业tag/成长名称和仅ID10暂缓的标记。

检查用inspector SHA256：`{binary_hash}`；当前PVF SHA256：`{source_hash}`。运行前后两者hash未变。没有构建、打包、启动GUI或读写用户存档。

每轮保存独立目录及`differences.json`，失败记录不被后续通过覆盖。`verification.json`保留所有逐项检查、来源成员hash和工具身份。`latest.json`仅指向最新结果；当前目录最初直接采样的`catalog-source.json`不代替最新run身份。

本核对只证明CharacterCatalog的源导出和绑定保真。它不表示11个角色都能创建或战斗，不表示转职、技能控制器、伤害公式、画面或操作手感已经还原。缔造者完整保留来源，按用户要求暂缓运行时实现。

复跑：`D:/ProgramData/anaconda3/python.exe -X utf8 -B tools/verify_character_sources.py`。
'''
    (REPORT_ROOT/'README.md').write_text(description,encoding='utf-8')
    print(json.dumps(dict(status=payload['status'],passed=payload['passed'],failed=payload['failed'],counts=counts,run=str(report),failures=failures),ensure_ascii=False))
    return 0 if payload['status']=='passed' else 1


if __name__=='__main__':
    raise SystemExit(main())
