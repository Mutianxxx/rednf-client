"""Create an immutable source/artifact/evidence checkpoint after actual verification."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,shutil

ROOT=Path(__file__).resolve().parent
PROJECT=ROOT/'project'

def digest(path):
    with path.open('rb') as stream:return hashlib.file_digest(stream,'sha256').hexdigest()

def main():
    build=ROOT/'checkpoints/build'
    verification=json.loads((build/'build-verification.json').read_text(encoding='utf-8'))
    if verification['status']!='pass':raise RuntimeError('Full automated verification must pass before checkpoint')
    for name,expected in verification['sources'].items():
        if digest(PROJECT/name)!=expected:raise RuntimeError(f'Changed verified input: {name}')
    for name,expected in verification['binaries'].items():
        if digest(build/name)!=expected:raise RuntimeError(f'Changed binary: {name}')
    for name,expected in verification['compiled_libraries'].items():
        if digest(build/name)!=expected:raise RuntimeError(f'Changed compiled library: {name}')
    tests=PROJECT/verification['test_directory']
    for name,expected in verification.get('reports',{}).items():
        if digest(tests/name)!=expected:raise RuntimeError(f'Changed verification report: {name}')
    audit_path=PROJECT/'reports/migration/application-audit/run.json'
    audit=json.loads(audit_path.read_text(encoding='utf-8'))
    if audit.get('status')!='completed' or audit.get('mode')!='profile-audit' or audit.get('frontend_started') is not False:
        raise RuntimeError('Completed no-window application profile audit is required')
    if audit.get('binary_sha256')!=verification['binaries']['dnf_native.exe']:
        raise RuntimeError('Application audit used a different binary')
    if audit.get('identity')!=verification['test_content_identity']:
        raise RuntimeError('Application audit used a different content identity')
    stamp=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    out=ROOT/'checkpoints'/(stamp+'-architecture-A0-A2a')
    out.mkdir(parents=True,exist_ok=False)
    (out/'INCOMPLETE').write_text('Checkpoint not yet verified\n',encoding='utf-8')
    rows=[]
    def copy(source,target):
        target.parent.mkdir(parents=True,exist_ok=True)
        expected=digest(source);shutil.copy2(source,target)
        if digest(target)!=expected:raise RuntimeError(f'Copy mismatch: {target}')
        rows.append({'path':target.relative_to(out).as_posix(),'size':target.stat().st_size,'sha256':expected})
    for directory in ('include','src','tests','cmake','third_party','tools','docs','licenses'):
        source=PROJECT/directory
        if not source.exists():continue
        for path in sorted(source.rglob('*')):
            if path.is_file() and '__pycache__' not in path.parts and path.suffix!='.pyc':
                copy(path,out/'source'/path.relative_to(PROJECT))
    for path in sorted(PROJECT.iterdir()):
        if path.is_file():copy(path,out/'source'/path.name)
    for name in verification['binaries']:copy(build/name,out/'runtime'/name)
    for path in sorted((PROJECT/'licenses').glob('*')):
        if path.is_file():copy(path,out/'runtime/licenses'/path.name)
    for name in verification['compiled_libraries']:copy(build/name,out/'compiled-libraries'/name)
    for path in sorted((PROJECT/'reports/migration').rglob('*')):
        if path.is_file():copy(path,out/'evidence/migration'/path.relative_to(PROJECT/'reports/migration'))
    copy(build/'build-verification.json',out/'evidence/build-verification.json')
    copy(build/'compile_commands.json',out/'evidence/compile_commands.json')
    for name in verification.get('reports',{}):copy(tests/name,out/'evidence/tests'/name)
    for name in ('PROGRESS.md','AGENTS.md','README.md','checkpoint_refactor.py'):
        copy(ROOT/name,out/'workspace'/name)
    for name in ('catalog/archive-summary.json','catalog/source-manifest.json',
                 'catalog/full-payload-verification.json','catalog/restore-verification.json',
                 'catalog/restore-verification-initial-failure.json','catalog/canonical-storage-repair.json',
                 'catalog/exclusion-summary.json','INDEX.md','architecture/ARCHITECTURE-REFACTOR-OUTLINE.md'):
        path=ROOT/'knowledge'/name
        if path.is_file():copy(path,out/'evidence/knowledge'/name)
    for path in sorted((PROJECT/'cache').glob('refactor-build-attempt*.log')):
        copy(path,out/'evidence/build-logs'/path.name)
    for directory in ('baseline-457','unvalidated-native-delta'):
        for path in sorted((ROOT/'knowledge'/directory).rglob('*')):
            if path.is_file():copy(path,out/'evidence/knowledge'/directory/path.relative_to(ROOT/'knowledge'/directory))
    copy(PROJECT/'content-profile.json',out/'runtime/content-profile.json')
    launcher='@echo off\nsetlocal\ncd /d "%~dp0"\n"%~dp0dnf_native.exe" --content-profile "%~dp0content-profile.json" --save-dir "%~dp0saves" --report-dir "%~dp0reports" %*\nset "dnf_exit=%errorlevel%"\nif not "%dnf_exit%"=="0" pause\nexit /b %dnf_exit%\n'
    (out/'runtime/play.cmd').write_text(launcher,encoding='ascii',newline='\r\n')
    rows.append({'path':'runtime/play.cmd','size':(out/'runtime/play.cmd').stat().st_size,'sha256':digest(out/'runtime/play.cmd')})
    progress='''# A0–A2a 重构节点

自动构建、人物表现组合、帧统计、核心、音频、隐藏UI与源码归属检查通过。
实际验证身份见 evidence/build-verification.json；源码与产物逐份列于 manifest.json。
启动 runtime/play.cmd，使用本节点私有存档；旧用户存档未复制。

本节点完成独立资料/源码迁入、全源码职责分组和首批OO提取。A0实际渲染性能基线、
A1公共接口收敛、完整A2–A6、World状态封装、业务命令/只读模型和其余表现对象仍需继续。
前台画面、声音、手感及原版动态比较待用户；未声称全职业技能或旧堆异常已修复。

恢复：读工作区 PROGRESS.md → 核对此节点manifest和实际验证 → 在project源码继续，
不要把原工程未验证459差异直接合入。
'''
    (out/'PROGRESS.md').write_text(progress,encoding='utf-8')
    rows.append({'path':'PROGRESS.md','size':(out/'PROGRESS.md').stat().st_size,'sha256':digest(out/'PROGRESS.md')})
    # A second independent read validates every copied byte before publishing latest.
    for row in rows:
        if digest(out/row['path'])!=row['sha256']:raise RuntimeError('Second hash pass failed: '+row['path'])
    manifest={'schema':1,'kind':'development-node-backup','node':'architecture-A0-A2a',
        'created_utc':datetime.now(timezone.utc).isoformat(),'build_status':'pass',
        'binary_sha256':verification['binaries']['dnf_native.exe'],'full_beta_gate_passed':False,
        'source_baseline':'mage-upper457','user_frontend_validation':'pending',
        'files':rows,'file_count':len(rows),'bytes':sum(x['size'] for x in rows),'hash_passes':2}
    (out/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    (out/'INCOMPLETE').unlink()
    (PROJECT/'LATEST_CHECKPOINT.json').write_text(json.dumps({'directory':str(out),'manifest_sha256':digest(out/'manifest.json')},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    relative=out.relative_to(PROJECT)
    (PROJECT/'Play-Latest-Verified.cmd').write_text('@echo off\ncall "%~dp0'+str(relative)+'\\runtime\\play.cmd" %*\n',encoding='ascii',newline='\r\n')
    print(json.dumps({'checkpoint':str(out),'files':len(rows),'bytes':manifest['bytes'],'hash_passes':2},ensure_ascii=False))

if __name__=='__main__':main()
