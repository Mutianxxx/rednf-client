"""Run the exact same World regression against a caller-selected core build."""
import argparse
from pathlib import Path
import hashlib
import json
import os
import subprocess
from datetime import datetime, timezone

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser()
parser.add_argument('--core-build', required=True, type=Path)
parser.add_argument('--output', required=True, type=Path)
args = parser.parse_args()
build = (root / args.core_build).resolve()
output = (root / args.output).resolve()
if not output.is_relative_to(root) or output.exists():
    raise SystemExit('Select a fresh project-local evidence directory')
output.mkdir(parents=True)
compiler = next((root / 'third_party').glob('llvm-mingw-*-ucrt-x86_64')) / 'bin/clang++.exe'
env = os.environ.copy()
(output / 'tmp').mkdir()
for name in ('TEMP', 'TMP', 'TMPDIR'):
    env[name] = str(output / 'tmp')
harness = output / 'main.cpp'
harness.write_text('''#include "dnf/combat.hpp"
#include "dnf/entry.hpp"
#include <iostream>
namespace dnf { Json runSkillReleaseRegressionTests(Pvf &, Assets &); }
int run(int argc, char **argv) {
    using namespace dnf;
    try {
        auto client = std::filesystem::u8path(argv[1]);
        Pvf pvf(client / "Script.pvf"); Assets assets(client, pvf);
        writeJson("result.json", runSkillReleaseRegressionTests(pvf, assets));
        return 0;
    } catch (const std::exception &error) {
        writeJson("result.json", {{"status","failed"},{"error",error.what()}});
        std::cerr << error.what() << std::endl; return 1;
    }
}
DNF_ENTRY(run)
''', encoding='utf-8')
test = root / 'tests/test_skill_release_regression.cpp'
core = build / 'libdnf_core.a'
command = [str(compiler), '-std=c++17', '-O1', '-g', '-DNOMINMAX', '-DWIN32_LEAN_AND_MEAN',
    '-DSQUNICODE', '-DSQINTEGER32', '-DSQSTRINGHASH32', '-DDNF_SQ_BUDGET', '-DSQ_EXCLUDE_DEFAULT_MEMFUNCTIONS',
    '-I' + str(root / 'include'), '-I' + str(root / 'third_party'),
    str(harness), str(test), str(core), str(build / 'libdnf_squirrel_vm.a'),
    str(build / 'third_party/zlib-1.3.1/libzlibstatic.a'), '-lbcrypt', '-lgdi32', '-municode', '-static-libstdc++',
    '-o', str(output / 'regression.exe')]
digest = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
identity = {'started_utc': datetime.now(timezone.utc).isoformat(), 'command': command,
    'core_sha256': digest(core), 'test_sha256': digest(test), 'build': str(build)}
with (output / 'compile.log').open('w', encoding='utf-8') as log:
    subprocess.run(command, check=True, env=env, stdout=log, stderr=subprocess.STDOUT)
unwind = compiler.parent / 'libunwind.dll'
(output / 'libunwind.dll').write_bytes(unwind.read_bytes())
with (output / 'run.log').open('w', encoding='utf-8') as log:
    completed = subprocess.run([str(output / 'regression.exe'), str(root.parent / 'DNF1031客户端')],
        env=env, cwd=output, stdout=log, stderr=subprocess.STDOUT)
identity.update(exit_code=completed.returncode, result=json.loads((output / 'result.json').read_text(encoding='utf-8')))
(output / 'identity.json').write_text(json.dumps(identity, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'output': str(output), 'exit_code': completed.returncode,
    'result': {k:v for k,v in identity['result'].items() if k not in ('checks', 'cases')}}, ensure_ascii=False))
raise SystemExit(completed.returncode)
