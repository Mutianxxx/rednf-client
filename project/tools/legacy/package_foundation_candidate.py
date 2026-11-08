"""Archive a verified intermediate candidate without replacing any release or saves.

This is preparation for P19, not the full ten-character beta acceptance gate.
All inputs and output must be under this project; an existing output is refused.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import json
from pathlib import Path
import shutil

from package_playable import require_game_closed, sha256

ROOT = Path(__file__).resolve().parents[1]


def local(value: Path) -> Path:
    path = (ROOT / value).resolve()
    path.relative_to(ROOT)
    return path


def read(path: Path):
    return json.loads(path.read_text(encoding='utf-8'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--test-dir', type=Path, required=True)
    parser.add_argument('--audit-dir', type=Path, required=True)
    parser.add_argument('--build-log', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, required=True)
    parser.add_argument('--version', default='v0.1-beta-foundation.3')
    args = parser.parse_args()
    build, tests, audit, output = (local(value) for value in
                                 (args.build_dir, args.test_dir, args.audit_dir, args.output_dir))
    build_log = local(args.build_log)
    output.relative_to(ROOT / 'candidates')
    if output.exists():
        raise RuntimeError('Refusing to replace a historical candidate: ' + str(output))
    require_game_closed()
    verification = read(build / 'build-verification.json')
    if verification['status'] != 'pass' or not verification['tests_requested']:
        raise RuntimeError('The latest build must have completed core and audio checks')
    if verification['test_directory'] != tests.relative_to(ROOT).as_posix():
        raise RuntimeError('Test directory does not match the successful build')
    for name, expected in verification['binaries'].items():
        if sha256(build / name) != expected:
            raise RuntimeError('Executable no longer matches its tests: ' + name)
    for name, expected in verification['sources'].items():
        if sha256(ROOT / name) != expected:
            raise RuntimeError('Source no longer matches its build: ' + name)
    for name, expected in verification['reports'].items():
        if sha256(tests / name) != expected:
            raise RuntimeError('Test report changed after verification: ' + name)
    for name in ('core-tests.json', 'audio-tests.json'):
        if read(tests / 'reports' / name)['status'] != 'pass':
            raise RuntimeError('Required test report is not passing: ' + name)
        if 'reports/' + name not in verification['reports']:
            raise RuntimeError('Required report was not produced by this build: ' + name)
    binary_hash = verification['binaries']['dnf_native.exe']
    profile_run, content_run = (read(audit / name / 'run.json') for name in ('profile', 'content'))
    for report, mode in ((profile_run,'profile-audit'), (content_run,'content-audit')):
        if (report.get('binary_sha256') != binary_hash or report.get('status') != 'completed' or
                report.get('frontend_started') is not False or report.get('mode')!=mode):
            raise RuntimeError('Audit does not belong to this binary or unexpectedly started a frontend')
    if profile_run['identity'] != content_run['identity']:
        raise RuntimeError('Profile and content audit identities differ')
    if verification['test_pvf_sha256'] != profile_run['identity']['pvf_sha256']:
        raise RuntimeError('Audit PVF differs from tested PVF')
    for key in ('content_id','pvf_sha256','archive_manifest_hash'):
        if verification['test_content_identity'][key]!=profile_run['identity'][key]:
            raise RuntimeError('Audit content differs from the tested static/PVF sources: '+key)
    effective = read(audit / 'profile' / 'effective-profile.json')
    if effective['identity']!=profile_run['identity']:
        raise RuntimeError('Effective content profile identity differs from its audit')
    if effective['ruleProfileId'] != 'beta-foundation-v1':
        raise RuntimeError('This intermediate candidate requires beta-foundation-v1 rules')
    protected = read(audit / 'protected-before.json')
    for name, expected in protected.items():
        if sha256(ROOT / name) != expected:
            raise RuntimeError('Protected save/release/launcher changed after the recorded packaging baseline: ' + name)

    # No original resource or user save is copied. The new directory is never
    # replaced; a failed attempt remains inspectable and needs a fresh output.
    output.mkdir(parents=True)
    payload = ['dnf_native.exe', 'SDL2.dll', 'libunwind.dll']
    for name in payload:
        shutil.copy2(build / name, output / name)
        if sha256(output / name) != verification['binaries'][name]:
            raise RuntimeError('Executable/runtime changed while copying: ' + name)
    config = {key: effective[key] for key in ('profileId', 'pvfPath', 'resourceRoots', 'textEncoding',
                                            'parserVersion', 'compatibilityProfileId', 'ruleProfileId')}
    (output / 'content-profile.json').write_text(json.dumps(config,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    for name, expected in verification['sources'].items():
        target = output / 'source' / name
        target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(ROOT / name, target)
        if sha256(target) != expected:
            raise RuntimeError('Source changed during archive: ' + name)
    evidence = output / 'evidence'
    shutil.copytree(audit,evidence / 'audits')
    for name, expected in verification['reports'].items():
        target = evidence / name
        target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(tests / name,target)
        if sha256(target) != expected:
            raise RuntimeError('Report changed during archive: ' + name)
    shutil.copy2(build / 'build-verification.json',evidence / 'build-verification.json')
    shutil.copy2(build_log,evidence / 'build.log')
    launcher = '''@echo off
setlocal
cd /d "%~dp0"
echo Intermediate foundation candidate. Full v0.1 beta is incomplete.
"%~dp0dnf_native.exe" --content-profile "%~dp0content-profile.json" --save-dir "%~dp0saves" %*
set "_dnf_candidate_exit=%errorlevel%"
if not "%_dnf_candidate_exit%"=="0" pause
exit /b %_dnf_candidate_exit%
'''
    (output / 'play.cmd').write_bytes(launcher.replace('\n','\r\n').encode('ascii'))
    instructions = '''基础设施中间候选：不是完整 v0.1 beta。
双击 play.cmd；无需 Python。默认仅写本候选 saves，旧存档不会自动导入。
完整原客户端仍在 content-profile.json 指定的外部目录，以只读方式使用。
如需迁移目录，分别调整 pvfPath 与 resourceRoots，重启后重新计算身份。

用户约5分钟检查：
1. 切英文输入法，新建男鬼剑士，进入赛丽亚房间，确认 HP180/MP140。
2. K 查看正常技能、SP/TP余额、下一等级费用及不可购买原因。新角色只领CHR初始技能；
   用上挑与鬼斩测试，未学技能不能释放。获得足够等级与SP后在城镇购买，退出重开检查等级/余额不重复扣除。
3. 到艾尔文防线接任务，商店买卖/装备；前往洛兰清房、拾取、首领结算。
4. 升级后检查 HP/MP 上限增加且保留此前已损失的绝对值；装备不会无故回满。
   有来源 HP/MP 增量的已支持装备会改变上限；卸下/破损移除贡献，维修后恢复，不额外回血。
5. 回城，退出后重开本启动器；检查角色、等级、装备、技能和副本进度恢复。
6. F9 打开独立测试窗口，开启总开关后分别切换 HP/MP 锁、无CD、AI暂停和等级覆盖。
   开启前自动保存正常进度，随后只写本候选 saves/beta-tests 的独立测试分支。
   关闭子开关仍在测试分支；返回选角、重新选择角色后恢复正常进度。
7. 在测试窗口暂停模拟并单步，确认每次只推进一个 tick；关闭窗口只隐藏，不退出游戏。
8. 测试设级后，K 使用独立测试点池学习；关闭测试总开关后恢复正常技能，正常购买历史不得改变。
   临时降低有效等级后，即使开启无CD，高于当前等级门槛的已学技能也不能释放。
9. 新副本人物与怪物伤害由逐目标推理链计算，检查换武器、护甲与升级的影响；旧快照保留旧策略。
   本策略尚未通过原版数值/手感对照，反馈包内保留双方来源、ATK、技能列、随机与伤害trace。
   若提示保存未完成，模拟和业务暂停；点击“重试当前保存”，不重新购买或重新扣点。
F8 导出本次反馈；F12 截图。自动检查未启动前台；画面/听音/手感待用户测试。

当前实际可玩仍仅未转职鬼剑士与原洛兰流程。来源审计保留其他职业，不赋予可玩状态。
已接入独立内容身份、固定模拟、存档/布局/随机恢复、技能成本和基础 HP/MP 成长。
装备 HP/MP 固定增量和 MP 百分比已通过同一重算入口；尚未完成套装、条件和完整被动链。
新 beta 副本使用 MOB/成长表来源 HP，副本内冻结策略；旧快照保留演示策略与既存血量。
独立测试窗口已接入命令接口；普通移动与基础攻击消费来源速度，技能专用速度尚未完成。
正常SP/TP学习、来源初始赠送、单一技能账本与持久化优先购买已接入；测试点池/覆盖独立保存。
人物CHR/EQU攻防和怪物成长系数/装备攻防分层汇总，ATK逐目标物魔/防御/元素/暴击等进入具名推理链。
完整被动/装备效果、脚本/ACT、其他职业/转职/觉醒技能和全域业务未完成。
历史快照仍含明确 legacy 策略，不能用于原版平衡验收。
人物成长采用 inferred-chr-growth-v1，MP/CD采用具名推理策略；完整原生数值链未恢复。
装备资源采用 inferred-equipment-resource-flat-rate-v1；怪物采用 inferred-mob-table-hp-v1。
evidence/ 保存当前自动检查、来源/能力审计和构建身份。历史失败日志留在工程 reports。
'''
    (output / 'README.txt').write_text(instructions,encoding='utf-8-sig')
    manifest = {'schema':1,'version':args.version,'release_kind':'intermediate-foundation-candidate',
                'full_beta_gate_passed':False,'created_utc':datetime.now(timezone.utc).isoformat(),
                'binary_sha256':binary_hash,'content_identity':profile_run['identity'],
                'rule_profile':effective['ruleProfileId'],'automatic_checks':'core/audio and read-only profile/content audit passed',
                'user_play_visual_audio_feel':'pending','original_client_dynamic_comparison':'pending',
                'protected_existing_files_verified':len(protected),
                'protection_scope':'Since evidence/audits/protected-before.json was recorded; historical deltas, if any, are retained separately in the audit archive',
                'save_directory':'saves (inside this candidate; no old save copied)',
                'work_package_status':{'P01':'implemented with automated checks; second real PVF version pending',
                                       'P02':'partial source catalog and gap audit; full closure and runtime admission pending',
                                       'P03':'partial fixed simulation/IDs/RNG; complete animation/entity lifecycle pending',
                                       'P04':'partial same-generation storage/reward/layout recovery; full persistent entity graph pending',
                                       'P05':'partial source growth, resources/speed, combat attributes and per-target inferred damage; complete attribute/effect chain pending',
                                       'P06-P16':'incomplete; only the existing unadvanced Swordman/Lorien runtime is playable',
                                       'P17':'partial command service, independent window and isolated test-save branch; full strategies and tools pending',
                                       'P18-P19':'incomplete; intermediate packaging does not pass full beta/release gate'}}
    manifest['files']=[{'path':path.relative_to(output).as_posix(),'size':path.stat().st_size,'sha256':sha256(path)}
                       for path in sorted(output.rglob('*')) if path.is_file()]
    manifest['manifest_hash_scope']='All archived files except manifest.json itself; runtime saves/reports are separate.'
    (output/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(output)


if __name__=='__main__':
    main()
