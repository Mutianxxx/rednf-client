"""Export traceable offline UI sources/mappings without copying or launching the client."""
import argparse
from collections import Counter
import csv
import hashlib
import io
import json
from pathlib import Path
import struct
import zipfile
from common import ROOT, WORK, CLIENT, EXE_HASH, PVF_HASH, SNAPSHOT_HASH, digest


GUIDE = '1031-UI层跨项目复刻规范.md'
DEFAULT_OUTPUT = WORK/'deliveries/1031-UI渲染交接包'
RULES = {
    'ui_load': dict(level='native-confirmed', consumers=['01067EC0', '01064D20', '01074B70', '010669F0'],
        implementation=['tools/model.py', 'tools/assets.py'], evidence=['reports/static/profile.json'],
        scope='Observed binding is not a complete lifecycle; counted prefix is not a per-type schema'),
    'geometry': dict(level='native-confirmed', consumers=['011B3950', '011B41E0', '011DB510'],
        implementation=['tools/native_geometry.py', 'tools/image_contract.py'],
        evidence=['reports/geometry-revision6/evidence.json', 'reports/remaining-followup/evidence.json'],
        scope='Verified source type7; request-local identity clip only; destination surface branches incomplete'),
    'board': dict(level='native-confirmed', consumers=['01072820', '011EA1D0', '011E9C30', '011E9E20'],
        implementation=['tools/board_layout.py'], evidence=['reports/board-followup/evidence.json'],
        scope='Authored board layout/order; not business visibility, dynamic resize or GPU rasterization'),
    'cbt': dict(level='native-confirmed', consumers=['01003770', '01002C40', '011C35D0'],
        implementation=['tools/cbt_schema.py', 'tools/config_preview.py'],
        evidence=['reports/followup-20261018/cbt-chain-evidence.json', 'reports/remaining-followup/evidence.json'],
        scope='Manual native group/predicate only; numeric IMG index and alternate mode unresolved'),
    'evn': dict(level='native-confirmed', consumers=['004EB120', '004E9520', '004E7790'],
        implementation=['tools/evn_schema.py', 'tools/config_preview.py'],
        evidence=['reports/followup-20261018/evn-chain-evidence.json'],
        scope='Frame/path selection and local arrangement, not actual visible/business list'),
    'wdm': dict(level='native-confirmed', consumers=['012EC6C0', '0111A374', '0111A393'],
        implementation=['tools/spatial_schema.py', 'tools/config_preview.py'],
        evidence=['reports/followup-20261018/spatial-chain-evidence.json'],
        scope='Region/Common independent loads; not balloon, switchbox, ACT, visibility or z-order'),
    'stm': dict(level='native-confirmed', consumers=['01314800', '00575EA0'],
        implementation=['tools/spatial_schema.py', 'tools/config_preview.py'],
        evidence=['reports/followup-20261018/spatial-chain-evidence.json'],
        scope='Five/four column schema and ID index; no inferred stage coordinates or main/append alignment'),
    'asset_decode': dict(level='resource-decoder', consumers=[],
        implementation=['src/assets.cpp', '../monster_demo/src/resources.cpp', 'tools/assets.py'],
        evidence=['reports/resource-followup/evidence.json'],
        scope='Implemented resource decoding/provenance, not all native pixel consumers'),
    'ani_sample': dict(level='resource-decoder', consumers=[],
        implementation=['../monster_demo/src/resources.cpp', 'tools/preview_layout.py'],
        evidence=['reports/preview-verification/verification.json'],
        scope='External time/loop and pose sampling; native ACT scheduling and complete blending unresolved'),
    'static_candidate': dict(level='candidate', consumers=[],
        implementation=['tools/preview.py', 'tools/preview_layout.py'],
        evidence=['reports/PREVIEW-FIXES.md'],
        scope='Authored parent/resource candidates and Qt substitutes; no universal native layer order'),
}


def normalize(value):
    return value.replace('\\', '/').lower()


def referenced_paths(value):
    found = set()
    if isinstance(value, str) and value.lower().endswith(('.img', '.ani', '.act', '.ui', '.cbt')):
        found.add(normalize(value))
    elif isinstance(value, dict):
        for child in value.values():
            found.update(referenced_paths(child))
    elif isinstance(value, list):
        for child in value:
            found.update(referenced_paths(child))
    return sorted(found)


def control_support(control):
    kind = control.get('type', '<raw>').lower()
    if not control.get('decoded'):
        return dict(status='unknown_structure', rule=None, reason='Undecoded counted prefix; raw retained')
    if kind == '[board image]':
        return dict(status='native_layout', rule='board', reason='Requires all nine images and supported parameters; no runtime state')
    if kind in ('[control]', '[control group]', '[tooltips]'):
        return dict(status='nonvisual_or_metadata', rule='static_candidate', reason='Not an unconditional image layer')
    if kind == '[animation]':
        return dict(status='resource_animation_candidate', rule='ani_sample', reason='External time; native attachment/scheduling unconfirmed')
    if kind in ('[text]', '[tab group]', '[basic button]') or 'scroll' in kind:
        return dict(status='external_substitute', rule='static_candidate', reason='Qt text/widget is not native skin/font/state')
    if kind in ('[image]', '[button]', '[text button]', '[highlight button]', '[checkbox]', '[radiobutton]'):
        return dict(status='resource_layout_candidate', rule='static_candidate', reason='Authored resource/initial frame; native state and full layer order unconfirmed')
    return dict(status='unknown_structure', rule=None, reason='Dedicated native control consumer not reconstructed')


def portable_index():
    result = json.loads((ROOT/'catalog/npk-index.json').read_text('utf8'))
    for rows in result.values():
        for row in rows:
            path = Path(row['archive'])
            if path.is_absolute():
                path = path.relative_to(CLIENT)
            if '..' in path.parts:
                raise ValueError('Archive path escapes client')
            row['archive'] = path.as_posix()
    return result


def make_maps(index):
    from preview import static_view
    from config_preview import ConfigLibrary
    catalog = json.loads((ROOT/'catalog/index.json').read_text('utf8'))
    scripts = json.loads((ROOT/'catalog/scripts.json').read_text('utf8'))
    script_by_path = {row['path']: row for row in scripts}
    duplicates = {}
    with (ROOT/'reports/resource-followup/duplicate-resolution.csv').open(encoding='utf-8-sig', newline='') as stream:
        for row in csv.DictReader(stream):
            duplicates.setdefault(row['path'], []).append(row)
    all_resources = set()
    windows = []
    for window in catalog['windows']:
        script = script_by_path[window['path']]
        raw = (ROOT/window['raw_file']).read_bytes()
        if hashlib.sha256(raw).hexdigest() != window['sha256']:
            raise ValueError('UI raw hash mismatch: '+window['path'])
        rebuilt = b''.join(struct.pack('<Bi', token['type'], token['raw']) for token in script.get('tokens', []))
        if raw and raw[2:] != rebuilt:
            raise ValueError('UI token roundtrip mismatch: '+window['path'])
        view = static_view(window['path'], catalog)
        controls = []
        for control in window['controls']:
            references = referenced_paths(control)
            all_resources.update(references)
            controls.append(dict(control, support=control_support(control), resource_references=references))
        references = referenced_paths(script.get('fields', []))
        all_resources.update(references)
        windows.append(dict(path=window['path'], member_sha256=window['sha256'],
            raw_file=window['raw_file'], pvf_entry=window['pvf_entry'], empty=window.get('empty', False),
            window_fields=window['window_fields'], authored_controls=controls, children=window['children'],
            resource_references=references, authored_control_count=len(controls),
            support_counts=dict(Counter(row['support']['status'] for row in controls)),
            instances=view['instances'], expanded_control_count=len(view['static_controls']),
            expanded_controls=[dict(row, support=control_support(row)) for row in view['static_controls']],
            diagnostics=view['preview_diagnostics'], layout_warnings=view['missing'],
            full_native_reconstruction=False,
            blocking_rules=['root window skin/title/alignment', 'native text/font', 'business state and ACT',
                            'complete control/window layer order', 'original-client visual acceptance']))
    library = ConfigLibrary()
    configurations = []
    for path, decoded in sorted(library.configs.items()):
        references = referenced_paths(decoded)
        all_resources.update(references)
        configurations.append(dict(path=path, kind=path.rsplit('.', 1)[-1], decoded=decoded,
            evidence=library.sources[path], resource_references=references,
            full_native_reconstruction=False, rule=path.rsplit('.', 1)[-1]))
    resources = {}
    animations = {}
    pvf = None
    service = None
    try:
        from pvf_inspect import open_pvf
        pvf = open_pvf()
        animation_paths = sorted(path for path in all_resources if path.endswith('.ani') and path in pvf.by_name)
        if animation_paths:
            from assets import Assets
            service = Assets(ROOT/'cache/render-handoff')
        for path in animation_paths:
            try:
                decoded = service.request(dict(op='animation', path=path))
                decoded.update(member_sha256=hashlib.sha256(pvf.read(path)).hexdigest(),
                    pvf_sha256=PVF_HASH, decoder='monster_demo/src/resources.cpp',
                    scope='Decoded resource poses only; native instance, trigger and clock unconfirmed')
                for frame in decoded['frames']:
                    all_resources.update(referenced_paths(frame['pose'].get('image', '')))
                animations[path] = decoded
            except ValueError as error:
                animations[path] = dict(ok=False, error=str(error),
                    member_sha256=hashlib.sha256(pvf.read(path)).hexdigest())
        for path in sorted(all_resources):
            if path.endswith('.img'):
                physical = path if path.startswith('sprite/') else 'sprite/'+path
                candidates = [dict(row) for row in index.get(physical, [])]
                duplicate_rows = duplicates.get(physical, [])
                for candidate in candidates:
                    matching = next((row for row in duplicate_rows if normalize(row['archive']) == normalize(candidate['archive'])
                        and int(row['offset']) == candidate['offset'] and int(row['length']) == candidate['length']), None)
                    candidate['member_sha256'] = matching['member_sha256'] if matching else None
                status = duplicate_rows[0]['status'] if duplicate_rows else 'unique' if candidates else 'missing_exact_member'
                resources[path] = dict(kind='img', physical_path=physical, candidates=candidates, status=status,
                    native_priority_verified=False, content_hash_policy='Re-read and hash selected member on every decode; export does not rescan all NPK bytes')
            else:
                exists = path in pvf.by_name
                resources[path] = dict(kind=path.rsplit('.', 1)[-1], exact_pvf_member=exists,
                    member_sha256=hashlib.sha256(pvf.read(path)).hexdigest() if exists else None,
                    status='exact_member' if exists else 'unlocated_literal_reference')
                if path in animations:
                    resources[path]['animation_metadata'] = 'animations.json#'+path
                    resources[path]['decoder_ok'] = animations[path]['ok']
    finally:
        if service:
            service.close()
        if pvf:
            pvf.close()
    identity = dict(exe_sha256=EXE_HASH, pvf_sha256=PVF_HASH, snapshot_sha256=SNAPSHOT_HASH)
    ui_map = dict(version=1, **identity, windows=windows, resources=resources,
        totals=dict(windows=len(windows), authored_controls=sum(row['authored_control_count'] for row in windows),
            decoded_prefixes=sum(control.get('decoded', False) for row in windows for control in row['authored_controls']),
            control_types=dict(Counter(control.get('type', '<raw>') for row in windows for control in row['authored_controls']))),
        full_native_reconstruction=False, provenance='Derived index of existing evidence, not new native proof')
    return ui_map, dict(version=1, **identity, configurations=configurations), dict(version=1, **identity, animations=animations)


def export(output):
    output = Path(output).resolve()
    output.relative_to((WORK/'deliveries').resolve())
    if output == (WORK/'deliveries').resolve():
        raise ValueError('Use a dedicated delivery subdirectory')
    inventory = {}

    def write(relative, raw, source=None, adaptation=None):
        target = (output/relative).resolve()
        target.relative_to(output)
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(raw)
        inventory[relative] = dict(sha256=hashlib.sha256(raw).hexdigest(), size=len(raw))
        if source:
            inventory[relative].update(source=source.relative_to(WORK).as_posix(), source_sha256=digest(source))
        if adaptation:
            inventory[relative]['adaptation'] = adaptation

    def copy(source):
        write(source.relative_to(WORK).as_posix(), source.read_bytes(), source)

    def write_json(relative, value):
        write(relative, json.dumps(value, ensure_ascii=False, indent=2).encode('utf8'))

    tools = ['common', 'assets', 'preview', 'model', 'preview_layout', 'board_layout', 'native_geometry',
        'image_contract', 'preview_diagnostics', 'config_preview', 'cbt_schema', 'evn_schema',
        'spatial_schema', 'pvf_inspect', 'resource_formats', 'render_reference', 'build_render_helper',
        'export_render_handoff', 'verify_render_handoff', 'catalog_evidence', 'exe_image']
    for name in tools:
        source = ROOT/'tools'/(name+'.py')
        if name == 'assets':
            text = source.read_text('utf8')
            needle = "CLIENT.parent/'monster_demo/src/resources.cpp'"
            if text.count(needle) != 1:
                raise ValueError('Unexpected decoder fingerprint path contract')
            write('ui_lab_1031/tools/assets.py', text.replace(needle, "ROOT.parent/'monster_demo/src/resources.cpp'").encode('utf8'),
                source, 'Only decoder source lookup is package-relative; image/resource algorithms unchanged')
        else:
            copy(source)
    for relative in ['monster_demo/src/resources.cpp', 'monster_demo/include/dnf/resources.hpp',
        'combat_ui_1031/tools/pvf_reader.py']:
        copy(WORK/relative)
    for name in ['json.hpp', 'stb_image_write.h', 'zlib.h', 'zconf.h', 'libzlibstatic.a']:
        copy(WORK/'attack_demo/vendor'/name)
    for name in ['ui_assets.exe', 'libunwind.dll']:
        copy(ROOT/'bin'/name)
    for source in sorted((ROOT/'docs').glob('*.md')):
        copy(source)
    for name in ['assets.cpp', 'observer.cpp', 'geometry_profile.hpp', 'profile.hpp']:
        source = ROOT/'src'/name
        if source.is_file():
            copy(source)
    for name in ['index.json', 'scripts.json']:
        copy(ROOT/'catalog'/name)
    for source in sorted((ROOT/'catalog/raw').rglob('*.bin')):
        copy(source)
    index = portable_index()
    index_source = ROOT/'catalog/npk-index.json'
    write('ui_lab_1031/catalog/npk-index.json', json.dumps(index, ensure_ascii=False, indent=2).encode('utf8'),
        index_source, 'Absolute archive paths rebased to client-relative paths; virtual keys/offset/length unchanged')
    for folder in ['static', 'geometry-code', 'continuation-code', 'ui-layout-code', 'geometry-revision6',
        'board-followup', 'remaining-followup', 'followup-20261018', 'resource-followup']:
        for source in sorted((ROOT/'reports'/folder).rglob('*')):
            if source.is_file() and source.suffix in ('.json', '.md', '.csv', '.bin', '.asm', '.txt', '.png'):
                copy(source)
    for name in ['PREVIEW-FIXES.md', 'BOARD-FOLLOWUP.md', 'REMAINING-FOLLOWUP.md', 'REVISION6.md',
        '1031-未完成清单与补采计划.md', 'session-analysis-20261018T071256-61396/selected-pvf-scripts.json']:
        copy(ROOT/'reports'/name)
    for folder in ['preview-verification', 'revision6-verification', 'resource-verification-followup']:
        for source in sorted((ROOT/'reports'/folder).iterdir()):
            if source.is_file() and source.suffix in ('.json', '.png'):
                copy(source)
    ui_map, config_map, animations = make_maps(index)
    write_json('ui_lab_1031/handoff/ui-map.json', ui_map)
    write_json('ui_lab_1031/handoff/config-map.json', config_map)
    write_json('ui_lab_1031/handoff/animations.json', animations)
    write_json('ui_lab_1031/handoff/native-rules.json', dict(version=1, exe_sha256=EXE_HASH,
        pvf_sha256=PVF_HASH, rules=RULES, full_native_reconstruction=False))
    table = io.StringIO(newline='')
    writer = csv.writer(table)
    writer.writerow(['path', 'member_sha256', 'authored_controls', 'expanded_controls', 'instances',
                     'support_counts', 'full_native_reconstruction'])
    for window in ui_map['windows']:
        writer.writerow([window['path'], window['member_sha256'], window['authored_control_count'],
            window['expanded_control_count'], len(window['instances']), json.dumps(window['support_counts']), False])
    write('ui_lab_1031/handoff/ui-map.csv', table.getvalue().encode('utf-8-sig'))
    write('requirements.txt', b'PySide6==6.9.2\nPillow>=10\n')
    write_json('examples/inventory-tabs.json', {'ui/inventory/iteminventorywindow.ui#97':1})
    write_json('examples/cbt-branch.json', dict(active_id=1, input_1b5650c=1))
    readme = '''# 1031 UI 渲染源码与证据交接包

主规范：[1031-UI层跨项目复刻规范](ui_lab_1031/docs/1031-UI层跨项目复刻规范.md)。
全部322 UI、36配置、物理资源候选和逐控件支持表在 `ui_lab_1031/handoff/`。
**不是所有UI完整复刻的完成证明**；所有窗口均保留缺项。原生已证规则、资源解码与Qt候选明确区分。

## 离线运行

Windows x64 / Python 3.11+。持有固定版客户端；ZIP不重复分发客户端、完整内存快照或采集日志。

```powershell
python -m pip install -r requirements.txt
python ui_lab_1031/tools/render_reference.py list
python ui_lab_1031/tools/render_reference.py render --client "D:/你的客户端目录" --ui ui/boosterselect/boosterselectpass.ui --out output/select
python ui_lab_1031/tools/render_reference.py render --client "D:/你的客户端目录" --config ui/pvp/channel/channelbutton.cbt --group 1 --highlight --out output/cbt
python ui_lab_1031/tools/render_reference.py bundle --input output/select --out output/reopened
```

输出PNG、version1离线包、物理来源/诊断；不是原生截图。`--client`只读取，不运行DNF.exe。
`manifest.json`对所有交付文件保存SHA256及原文件SHA256；不包括自身哈希，ZIP外层SHA在交付验证报告。
只有npk-index归档路径和assets.py的decoder源码查找有路径适配，manifest记录变换，不改资源/绘制算法。
`src/observer.cpp`只供审阅来源，不参与离线执行；未包含observer DLL和部署入口。
历史证据可能引用未打包的大归档/快照或旧绝对路径；这些引用保留历史身份，不是运行依赖。

## 重建独立helper（可选）

已有Windows x64二进制可直接使用；要重建使用与静态zlib库ABI兼容的LLVM-MinGW x64工具链：

```powershell
python ui_lab_1031/tools/build_render_helper.py --compiler "<toolchain>/bin/x86_64-w64-mingw32-clang++.exe"
```

重建后helper哈希改变是正常现象；需重验对应资源样本，不将旧manifest当新二进制证明。
第三方头文件保持原有许可声明，未另造版权或许可。
'''
    write('README.md', readme.encode('utf8'))
    manifest = dict(version=1, exe_sha256=EXE_HASH, pvf_sha256=PVF_HASH, files=inventory,
        totals=ui_map['totals'], configurations=len(config_map['configurations']),
        full_native_reconstruction=False, client_included=False, observer_dll_included=False,
        limitation='Evidence/source handoff; no full-native or original-client visual acceptance claim')
    manifest_raw = json.dumps(manifest, ensure_ascii=False, indent=2).encode('utf8')
    (output/'manifest.json').write_bytes(manifest_raw)
    archive = output.with_suffix('.zip')
    with zipfile.ZipFile(archive, 'w', compression=zipfile.ZIP_DEFLATED, compresslevel=6) as stream:
        for relative in sorted(inventory):
            stream.write(output/relative, output.name+'/'+relative)
        stream.write(output/'manifest.json', output.name+'/manifest.json')
    return dict(output=str(output), archive=str(archive), archive_sha256=digest(archive),
        manifest_sha256=hashlib.sha256(manifest_raw).hexdigest(), files=len(inventory),
        windows=len(ui_map['windows']), configurations=len(config_map['configurations']),
        full_native_reconstruction=False)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', default=str(DEFAULT_OUTPUT))
    args = parser.parse_args()
    print(json.dumps(export(args.out), ensure_ascii=False))


if __name__ == '__main__':
    main()
