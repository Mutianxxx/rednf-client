"""One-time, verified source import; original projects and saves stay read-only."""
from pathlib import Path
import hashlib, json, re, shutil

ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parents[1]
OLD = WORKSPACE / 'dnf-native-demo'
NODE = OLD / 'checkpoints/20261020T224815926748Z-mage-upper457'
SOURCE = NODE / 'source'

GROUPS = {
    'app': 'main runtime_paths sdl_game_input sdl_text_input text_input',
    'content': 'content_profile content_catalog character character_entry skill_data audio_catalog business_ui_source hud_source',
    'resources': 'resources',
    'simulation/actors': 'axis_motion',
    'simulation/actions': 'character_attack skill_runtime skill_cost skill_input_feedback source_skill_action',
    'simulation/jobs': 'character_controller experimental_character experimental_world_adapter gunner_basic female_gunner female_gunner_world female_gunner_timing female_gunner_skill_layers female_gunner_entities female_gunner_modifiers source_watercannon source_mage_upper swordman_stage_plan releasewave_plan',
    'simulation/animation': 'animation_events equipment_motion particle_motion static_motion',
    'simulation/combat': 'combat combat_attributes monster_combat_attributes damage_contact damage_resolution damage_runtime attack_status skill_attack_status status_effects status_runtime player_reaction object_damage_runtime monster_damage_check',
    'simulation/entities': 'objects',
    'simulation/monsters': 'monster_action_ai monster_action_ai_world monster_behavior monster_event_ai monster_event_ai_service monster_event_ai_test_policy monster_event_ai_normal_policy monster_event_continuation monster_spawn',
    'simulation/world': 'simulation session scene region region_world region_generator dungeon_selection map_access map_exploration map_exploration_policy town_access walk_geometry',
    'simulation/progression': 'attributes speed_attributes equipment_attributes monster_attributes progression skill_learning skill_learning_transaction character_advancement character_advancement_world character_advancement_transaction',
    'simulation/scripting': 'act_collision act_runtime act_service act_world_host squirrel_action_service squirrel_host squirrel_platform_windows squirrel_service squirrel_world_bridge',
    'presentation/characters': 'appearance',
    'presentation/monsters': 'monster_equipment monster_effects',
    'presentation/maps': 'scene_camera scene_tiles scene_presentation object_presentation portal_visuals',
    'presentation/effects': 'effect_plan drop_presentation boss_aura_ui',
    'presentation/ui/windows': 'equipment_ui skill_configuration_ui skill_learning_ui region_ui selection_ui business_ui_render scene_presentation_ui world_map_ui',
    'presentation/ui/hud': 'hud target_hud',
    'presentation/audio': 'audio',
    'render': 'renderer font',
    'persistence': 'storage pending_rewards reward_recovery',
    'diagnostics': 'debug debug_window beta_branch beta_character beta_branch_exit',
    'tools': 'skill_preview',
}

def sha(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()

def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')

def main():
    receipt = ROOT / 'reports/migration/baseline-import.json'
    if receipt.exists():
        raise SystemExit('Import already recorded; refuse to overwrite refactored source')
    manifest = json.loads((NODE/'manifest.json').read_text(encoding='utf-8'))
    expected = {x['path']: x['sha256'] for x in manifest['files']}
    by_stem = {}
    for module, names in GROUPS.items():
        for stem in names.split():
            if stem in by_stem: raise ValueError(stem)
            by_stem[stem] = module
    rows = []
    module_map = {}
    def copy(source, target, original=None):
        digest = sha(source)
        relative = source.relative_to(NODE).as_posix() if source.is_relative_to(NODE) else None
        if relative and expected.get(relative) != digest:
            raise RuntimeError(f'Baseline hash mismatch or unlisted input: {relative}')
        target.parent.mkdir(parents=True, exist_ok=True)
        if target.exists():
            if sha(target) != digest: raise RuntimeError(f'Changed destination: {target}')
        else:
            shutil.copy2(source, target)
        if sha(target) != digest: raise RuntimeError(f'Copy mismatch: {target}')
        rows.append({'origin':str(source), 'original_relative_path':original,
                     'target':target.relative_to(ROOT).as_posix(), 'bytes':source.stat().st_size,
                     'sha256':digest, 'baseline_manifest_verified':bool(relative)})
    for folder in ('src', 'include', 'tests', 'third_party'):
        for source in sorted((SOURCE/folder).rglob('*')):
            if not source.is_file() or '__pycache__' in source.parts or source.suffix=='.pyc': continue
            relative = source.relative_to(SOURCE).as_posix()
            target = ROOT/relative
            if folder=='src':
                module = by_stem[source.stem]
                target = ROOT/'src'/module/source.name
                module_map[relative] = target.relative_to(ROOT).as_posix()
            copy(source, target, relative)
    # Runtime dependencies are copied; bulky compiler tools remain an explicit read-only toolchain.
    sdl = OLD/'third_party/SDL2-2.32.10/x86_64-w64-mingw32'
    for folder in ('include', 'lib', 'bin'):
        for source in sorted((sdl/folder).rglob('*')):
            if source.is_file(): copy(source,ROOT/'third_party/SDL2-2.32.10/x86_64-w64-mingw32'/source.relative_to(sdl))
    if not (ROOT/'third_party/dependencies.lock.json').exists():
        copy(OLD/'third_party/dependencies.lock.json', ROOT/'third_party/dependencies.lock.json')
    for name in ('dnf_ani_render.hpp','dnf_ani_clock.hpp'):
        copy(NODE/'reverse-60us/integration/include'/name, ROOT/'third_party/native-contracts/include'/name)
    for source in sorted((SOURCE/'tools').glob('*.py')):
        copy(source,ROOT/'tools/legacy'/source.name,'tools/'+source.name)
    copy(SOURCE/'tools/inspect.cpp',ROOT/'tools/inspect.cpp','tools/inspect.cpp')
    # Public header names remain a compatibility seam during the object migration.
    for name in ('resources.hpp','experimental_character.hpp'):
        target=ROOT/'include/dnf'/name
        text=target.read_text(encoding='utf-8').replace('../../../reverse-60us/integration/include/','')
        target.write_text(text,encoding='utf-8',newline='\n')
    text=(SOURCE/'CMakeLists.txt').read_text(encoding='utf-8')
    core=[]
    def first(match):
        core.extend(match.group(1).split()); return 'add_library(dnf_core)\ninclude(cmake/CoreModules.cmake)'
    text=re.sub(r'add_library\(dnf_core\s+([^)]*)\)',first,text)
    def more(match): core.extend(match.group(1).split()); return ''
    text=re.sub(r'target_sources\(dnf_core PRIVATE\s+([^)]*)\)',more,text)
    for old,new in sorted(module_map.items(),key=lambda kv:-len(kv[0])): text=text.replace(old,new)
    text=text.replace('project(dnf_native_demo LANGUAGES C CXX)','project(dnf_cpp_project LANGUAGES C CXX)')
    text=text.replace('target_include_directories(dnf_core PUBLIC include third_party ', 'target_include_directories(dnf_core PUBLIC include third_party third_party/native-contracts/include ')
    text=text.replace('"${CMAKE_CURRENT_SOURCE_DIR}/../DNF1031客户端"','"${DNF_CLIENT_ROOT}"')
    text=text.replace('${CMAKE_CURRENT_SOURCE_DIR}/third_party/llvm-mingw-20261006-ucrt-x86_64/bin/libunwind.dll','${DNF_TOOLCHAIN_ROOT}/llvm-mingw-20261006-ucrt-x86_64/bin/libunwind.dll')
    text=text.replace('set(CMAKE_CXX_STANDARD 17)', 'set(DNF_CLIENT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../DNF1031客户端" CACHE PATH "Read-only source client")\nset(DNF_TOOLCHAIN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../dnf-native-demo/third_party" CACHE PATH "Read-only compiler utilities")\nset(CMAKE_CXX_STANDARD 17)')
    (ROOT/'CMakeLists.txt').write_text(text,encoding='utf-8',newline='\n')
    modules={}
    for old in core:
        new=module_map[old];module='/'.join(Path(new).parts[1:-1]);modules.setdefault(module,[]).append(new)
    cmake=['# Explicit source ownership; generated by the one-time baseline importer.',
           '# A shared archive preserves existing link semantics while interfaces are migrated.']
    for module, files in sorted(modules.items()):
        cmake.extend(['\n# '+module,'target_sources(dnf_core PRIVATE',*['    '+name for name in files],')'])
    (ROOT/'cmake').mkdir(exist_ok=True)
    (ROOT/'cmake/CoreModules.cmake').write_text('\n'.join(cmake)+'\n',encoding='utf-8')
    write_json(ROOT/'cmake/source-ownership.json',module_map)
    write_json(ROOT/'toolchain.local.json',{'toolchain_root':str(OLD/'third_party'),'client_root':str(WORKSPACE/'DNF1031客户端')})
    write_json(ROOT/'content-profile.json',{'profileId':'cpp-refactor-1031','pvfPath':str(WORKSPACE/'DNF1031客户端/Script.pvf'),
        'resourceRoots':[str(WORKSPACE/'DNF1031客户端')],'textEncoding':'CP936','parserVersion':'dnf-cpp-refactor-v1','adapterPolicyVersion':'1031-preserved-v1'})
    (ROOT/'CURRENT_TASK.md').write_text('# C++ 独立重构\n\n以工作区 ../PROGRESS.md 为当前状态。457 为已验证迁入基线；原工程459未验证差异独立归档，不默认合入。\n',encoding='utf-8')
    write_json(receipt,{'schema':1,'node':'A0-A1-baseline-import','source_node':str(NODE),'source_manifest_sha256':sha(NODE/'manifest.json'),
        'source_binary_sha256':manifest['binary_sha256'],'runtime_saves_copied':False,'source_ownership':module_map,
        'files':rows,'copied_files':len(rows),'copied_bytes':sum(x['bytes'] for x in rows),
        'note':'Source paths/CMake and portable native contract includes deliberately adjusted after byte verification; current build hashes are recorded separately.'})
    print(json.dumps({'copied_files':len(rows),'bytes':sum(x['bytes'] for x in rows),'source_modules':len(modules),'source_units':len(module_map)},ensure_ascii=False))

if __name__=='__main__': main()
