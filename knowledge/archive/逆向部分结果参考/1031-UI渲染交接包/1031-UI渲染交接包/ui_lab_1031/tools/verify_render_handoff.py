"""Verify source handoff, full catalog coverage and independent offline examples."""
import argparse
import hashlib
import json
import math
from pathlib import Path
import struct
import subprocess
import sys
import zipfile
from common import ROOT, WORK, CLIENT, EXE_HASH, PVF_HASH, digest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--package', default=str(WORK/'deliveries/1031-UI渲染交接包'))
    parser.add_argument('--client', default=str(CLIENT))
    parser.add_argument('--out', default=str(ROOT/'reports/render-handoff-verification'))
    parser.add_argument('--compiler', help='Optionally rebuild helper with Windows x64 LLVM-MinGW')
    args = parser.parse_args()
    package, output = Path(args.package).resolve(), Path(args.out).resolve()
    output.mkdir(parents=True, exist_ok=True)
    manifest = json.loads((package/'manifest.json').read_text('utf8'))
    checks = []

    def check(name, condition):
        checks.append(dict(name=name, passed=bool(condition)))
        if not condition:
            raise AssertionError(name)
        print('PASS '+name, flush=True)

    check('exact EXE and PVF identity', (manifest['exe_sha256'], manifest['pvf_sha256']) == (EXE_HASH, PVF_HASH))
    for relative, record in manifest['files'].items():
        target = (package/relative).resolve()
        target.relative_to(package)
        if digest(target) != record['sha256'] or target.stat().st_size != record['size']:
            raise AssertionError('Package file mismatch: '+relative)
    check('all delivered file hashes and path boundaries', True)
    check('no observer DLL or client is shipped', not manifest['observer_dll_included'] and not manifest['client_included']
        and not any(name.lower().endswith(('dnf.exe', 'script.pvf', 'ui_observer_1031.dll')) for name in manifest['files']))
    archive = package.with_suffix('.zip')
    with zipfile.ZipFile(archive) as stream:
        check('zip contains exactly the declared delivery', set(stream.namelist()) ==
            {package.name+'/'+relative for relative in manifest['files']} | {package.name+'/manifest.json'})
        check('zip CRC and source manifest match', stream.testzip() is None and
            stream.read(package.name+'/manifest.json') == (package/'manifest.json').read_bytes())
    lab = package/'ui_lab_1031'
    mappings = json.loads((lab/'handoff/ui-map.json').read_text('utf8'))
    windows = mappings['windows']
    check('all 322 UI and 4013 control records retained', len(windows) == 322 and
        sum(len(window['authored_controls']) for window in windows) == 4013 and mappings['totals']['decoded_prefixes'] == 4006)
    check('every UI explicitly retains reconstruction limits', all(window['full_native_reconstruction'] is False
        and window['blocking_rules'] and window['diagnostics']['summary']['runtime_evidence'] for window in windows))
    scripts = json.loads((lab/'catalog/scripts.json').read_text('utf8'))
    by_path = {row['path']: row for row in scripts}
    for window in windows:
        raw = (lab/window['raw_file']).read_bytes()
        rebuilt = b''.join(struct.pack('<Bi', token['type'], token['raw']) for token in by_path[window['path']].get('tokens', []))
        if hashlib.sha256(raw).hexdigest() != window['member_sha256'] or raw and raw[2:] != rebuilt:
            raise AssertionError('Lossless UI mapping mismatch: '+window['path'])
    check('all 322 decrypted UI hashes and token roundtrips', True)
    check('expanded repeated child instances have distinct keys', all(len(window['expanded_controls']) ==
        len({row['key'] for row in window['expanded_controls']}) for window in windows))
    check('all authored resource references resolve to explicit mapping records', all(path in mappings['resources']
        for window in windows for path in window['resource_references']))
    index = json.loads((lab/'catalog/npk-index.json').read_text('utf8'))
    check('all NPK candidates use relative paths without traversal', len(index) == 90799 and
        all(not Path(row['archive']).is_absolute() and '..' not in Path(row['archive']).parts for rows in index.values() for row in rows))
    check('both missing map resources have no substitute', all(not mappings['resources'][path]['candidates']
        and mappings['resources'][path]['status'] == 'missing_exact_member'
        for path in ('worldmap/selectdungeon02_cn.img', 'worldmap/timegate.img')))
    configurations = json.loads((lab/'handoff/config-map.json').read_text('utf8'))['configurations']
    check('36 configurations retain exact type counts', {kind:sum(row['kind'] == kind for row in configurations)
        for kind in ('cbt', 'evn', 'wdm', 'stm')} == dict(cbt=8, evn=1, wdm=26, stm=1))
    check('config dependencies are included in the resource table', all(path in mappings['resources']
        for row in configurations for path in row['resource_references']))
    animations = json.loads((lab/'handoff/animations.json').read_text('utf8'))['animations']
    check('UI ANI poses retain member hashes and complete IMG dependency links', bool(animations) and
        all(len(row['member_sha256']) == 64 and (not row['ok'] or all(not frame['pose']['image'] or
            frame['pose']['image'].replace('\\','/').lower() in mappings['resources'] for frame in row['frames']))
            for row in animations.values()))
    wdm = [row['decoded'] for row in configurations if row['kind'] == 'wdm']
    check('WDM keeps 216 dungeon records and 100 internal markers', sum(len(row['dungeons']) for row in wdm) == 216
        and sum(item['in_progress'] for row in wdm for item in row['dungeons']) == 100)
    rules = json.loads((lab/'handoff/native-rules.json').read_text('utf8'))['rules']
    check('rule code/evidence paths are present', all((lab/path).is_file()
        for row in rules.values() for key in ('implementation', 'evidence') for path in row[key]))
    adapted = {name:row for name, row in manifest['files'].items() if row.get('adaptation')}
    check('only two documented path adaptations', set(adapted) == {'ui_lab_1031/tools/assets.py', 'ui_lab_1031/catalog/npk-index.json'})

    def invoke(arguments):
        result = subprocess.run([sys.executable, '-X', 'utf8', '-B', str(lab/'tools/render_reference.py')]+arguments,
            cwd=package, capture_output=True, text=True, encoding='utf8', timeout=180)
        if result.returncode:
            raise AssertionError(result.stdout+'\n'+result.stderr)
        return json.loads(result.stdout)

    listed = invoke(['list'])
    check('portable entry point lists all inputs without a client', len(listed['ui']) == 322 and len(listed['configurations']) == 36)
    cases = [('board', ['--ui', 'ui/boosterselect/boosterselectpass.ui']),
             ('cbt', ['--config', 'ui/pvp/channel/channelbutton.cbt', '--group', '1', '--highlight']),
             ('cbt-active', ['--config', 'ui/pvp/channel/channelbutton.cbt', '--group', '1',
                             '--branch', '@examples/cbt-branch.json']),
             ('evn', ['--config', 'ui/event/informationbuttoninfo.evn', '--overview']),
             ('stm', ['--config', 'stagemap/advancealtar.stm', '--district', '2'])]
    renders = []
    for name, arguments in cases:
        destination = output/name
        result = invoke(['render', '--client', str(Path(args.client).resolve()), '--out', str(destination)]+arguments)
        bundle = json.loads((destination/'window.json').read_text('utf8'))
        check('portable real-resource '+name+' export keeps provenance and diagnostics', result['full_native_reconstruction'] is False
            and bool(bundle['assets']) and all(row.get('source_reads') for row in bundle['assets'].values())
            and (destination/'preview.png').stat().st_size > 1000)
        renders.append(dict(name=name, result=result, image_sha256=digest(destination/'preview.png')))
    reopened = invoke(['bundle', '--input', str(output/'board'), '--out', str(output/'reopened')])
    check('offline bundle reopens without client access', reopened['full_native_reconstruction'] is False and
        digest(output/'board/preview.png') == digest(output/'reopened/preview.png'))
    selected = invoke(['render', '--client', str(Path(args.client).resolve()), '--ui',
        'ui/inventory/iteminventorywindow.ui', '--tabs', '@examples/inventory-tabs.json', '--out', str(output/'inventory')])
    selected_bundle = json.loads((output/'inventory/window.json').read_text('utf8'))
    check('file-based JSON selects a conditional child without shell quoting assumptions',
        any('inventory_avatar.ui' in row['source'] for row in selected_bundle['view']['static_controls'])
        and bool(selected_bundle['assets']) and selected['full_native_reconstruction'] is False
        and selected_bundle['view']['reference_selection']['tabs'] == {'ui/inventory/iteminventorywindow.ui#97':1})
    invoke(['bundle', '--input', str(output/'inventory'), '--out', str(output/'inventory-reopened')])
    selected_reopened = json.loads((output/'inventory-reopened/window.json').read_text('utf8'))
    check('offline reopen retains explicit local selection without inventing native state',
        selected_reopened['view']['reference_selection'] == selected_bundle['view']['reference_selection'])
    if args.compiler:
        rebuilt = output/'rebuilt/ui_assets.exe'
        result = subprocess.run([sys.executable, '-X', 'utf8', '-B', str(lab/'tools/build_render_helper.py'),
            '--compiler', args.compiler, '--out', str(rebuilt)], cwd=package, capture_output=True,
            text=True, encoding='utf8', timeout=180)
        check('offline helper independently compiles from delivered sources', result.returncode == 0 and rebuilt.is_file())
        decode_output = output/'rebuilt/decode'
        decode_output.mkdir(parents=True, exist_ok=True)
        target = json.loads((output/'board/window.json').read_text('utf8'))
        resource = next(row for row in target['assets'].values() if row['resource'].lower().endswith('windowcommon.img') and row['frame'] == 213)
        request = dict(op='image', path=resource['resource'], frame=213, key='0123456789abcdef')
        result = subprocess.run([str(rebuilt), str(Path(args.client).resolve()), str(decode_output)],
            input=json.dumps(request)+'\n'+json.dumps(dict(op='quit'))+'\n', capture_output=True,
            text=True, encoding='utf8', timeout=180)
        response = [json.loads(line) for line in result.stdout.splitlines()]
        check('rebuilt helper reproduces real board frame metadata and PNG bytes', result.returncode == 0 and
            len(response) == 2 and response[0].get('ready') and response[1].get('ok') and
            all(response[1][key] == resource[key] for key in ('width','height','x','y','logical_width','logical_height'))
            and digest(response[1]['png']) == resource['png_sha256'])
    sys.path.insert(0, str(lab/'tools'))
    from native_geometry import image_affine, rectangle_words, CENTER_SENTINEL
    check('documented matrix and rectangle examples', image_affine(2,3,0,CENTER_SENTINEL,CENTER_SENTINEL,21,31) ==
        (2.0, -0.0, 0.0, 3.0, -10.0, -30.0) and rectangle_words([-5,2,65537,0xffffffff]) == [0,2,1,0])
    matrix = image_affine(2,3,math.pi/2,5,7,21,31)
    check('documented screen-axis scaling example', abs(matrix[0]*8+matrix[2]*11+matrix[4]-13) < 1e-6
        and abs(matrix[1]*8+matrix[3]*11+matrix[5]+2) < 1e-6)
    document = (lab/'docs/1031-UI层跨项目复刻规范.md').read_text('utf8')
    check('guide separates full reconstruction limits and key consumers', all(word in document for word in
        ('不能保证复刻', '011B41E5', '011DADE0', '011E9C30', 'full_native_reconstruction=false', '673,611')))
    report = dict(passed=all(row['passed'] for row in checks), checks=checks, renders=renders,
        package=str(package), manifest_sha256=digest(package/'manifest.json'), archive_sha256=digest(archive),
        full_native_reconstruction=False, native_visual_acceptance='pending',
        limitation='Only package, mapping and offline resource rendering verified; no client started')
    (output/'verification.json').write_text(json.dumps(report, ensure_ascii=False, indent=2), 'utf8')
    print(json.dumps(dict(passed=report['passed'], checks=len(checks), output=str(output)), ensure_ascii=False))


if __name__ == '__main__':
    main()
