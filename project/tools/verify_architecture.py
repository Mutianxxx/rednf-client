"""Check actual source ownership and build isolation; report transitional edges."""
from pathlib import Path
import argparse, json, re, sys

ROOT=Path(__file__).resolve().parents[1]

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir',type=Path,default=ROOT/'cache/refactor-build')
    args=parser.parse_args()
    ownership=json.loads((ROOT/'cmake/source-ownership.json').read_text(encoding='utf-8'))
    values=list(ownership.values());actual={p.relative_to(ROOT).as_posix() for p in (ROOT/'src').rglob('*.cpp')}
    checks=[]
    def check(ok,message):
        checks.append({'passed':bool(ok),'message':message})
        if not ok:raise RuntimeError(message)
    check(len(values)==len(set(values)),'Every implementation unit has one declared owner')
    check(set(values)==actual,'Every source unit is registered; no missing or stale module paths')
    escaped=[];sdl=[]
    for directory in ('src','include'):
        for path in (ROOT/directory).rglob('*'):
            if path.suffix not in ('.cpp','.hpp','.h'):continue
            text=path.read_text(encoding='utf-8')
            for include in re.findall(r'^\s*#include\s+"([^"]+)"',text,re.M):
                if '../' in include:escaped.append({'file':path.relative_to(ROOT).as_posix(),'include':include})
            if path.is_relative_to(ROOT/'src/simulation') and re.search(r'#include\s*[<"]SDL',text):sdl.append(str(path))
    check(not escaped,'Project includes do not escape to original source or reverse directories')
    check(not sdl,'Simulation implementation units do not directly include SDL')
    compile_path=args.build_dir/'compile_commands.json'
    compiled=set()
    if compile_path.is_file():
        for command in json.loads(compile_path.read_text(encoding='utf-8')):
            source=Path(command['file']).resolve()
            check(source.is_relative_to(ROOT),'Compiled game/dependency input belongs to the new project')
            if source.is_relative_to(ROOT/'src'):compiled.add(source.relative_to(ROOT).as_posix())
    inactive=sorted(actual-compiled)
    allowed_inactive={'src/simulation/jobs/releasewave_plan.cpp','src/simulation/jobs/swordman_stage_plan.cpp'}
    if compile_path.is_file():check(set(inactive)<=allowed_inactive,'New object implementations are actual build inputs')
    report={'schema':1,'status':'pass','checks':checks,'owned_source_units':len(actual),
        'compiled_source_units':len(compiled),'inactive_preserved_baseline_units':inactive,
        'transitional_boundaries':['dnf_core remains one link archive while its cross-module interfaces are narrowed',
            'include/dnf legacy names remain compatibility interfaces',
            'World still exposes legacy mutable state; full command/read-model migration remains pending'],
        'escaped_includes':escaped,'simulation_sdl_includes':sdl}
    target=ROOT/'reports/migration/architecture-check.json';target.parent.mkdir(parents=True,exist_ok=True)
    target.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:report[k] for k in ('status','owned_source_units','compiled_source_units','inactive_preserved_baseline_units')}))

if __name__=='__main__':main()
