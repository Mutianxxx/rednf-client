"""Run the real SDL application with per-run diagnostics."""
from pathlib import Path
from datetime import datetime, timezone
import subprocess
import sys
import json
import uuid
import hashlib
from test_window import show_test_window

root = Path(__file__).resolve().parents[1]
args = sys.argv[1:]
binary = root / 'build/dnf_native.exe'
if '--binary' in args:
    index = args.index('--binary')
    if index + 1 >= len(args):
        raise SystemExit('--binary requires a path')
    binary = Path(args[index + 1]).resolve()
    del args[index:index + 2]
run_id = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S') + '-' + uuid.uuid4().hex[:8]
report = root / 'reports' / 'runs' / run_id
report.mkdir(parents=True)
started = datetime.now(timezone.utc).isoformat()
command = [str(binary), *args, '--run-id', run_id,
           '--report-dir', str(report)]
binary_sha256 = hashlib.sha256(binary.read_bytes()).hexdigest()
process = subprocess.Popen(command, cwd=root, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
window = show_test_window(process) if any(a in args for a in ('--smoke', '--flow-smoke', '--quit-after', '--screenshot')) else None
stdout, stderr = process.communicate()
log = {'run_id': run_id, 'started_utc': started, 'finished_utc': datetime.now(timezone.utc).isoformat(),
       'binary_sha256': binary_sha256,
       'arguments': args, 'returncode': process.returncode,
       'report_directory': str(report.relative_to(root)),
       'stdout': stdout.decode('utf-8', 'replace'), 'stderr': stderr.decode('utf-8', 'replace'),
       'test_window': window}
(report / 'process-check.json').write_text(json.dumps(log, ensure_ascii=False, indent=2), encoding='utf-8')
(root / 'reports/latest-run.json').write_text(json.dumps(log, ensure_ascii=False, indent=2), encoding='utf-8')
print(json.dumps(log, ensure_ascii=False, indent=2))
raise SystemExit(process.returncode)
