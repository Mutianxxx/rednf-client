"""Exercise archive lookup/restoration for every major source family."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parents[1]
EXAMPLES = [
    ('pvf-audit', 'dnf-native-demo/reports/knowledge-base-audit/skill-audit.md'),
    ('native-reverse-60us', 'reverse-60us/releases/20261020-01/analysis/combat_progress/README.md'),
    ('android', 'dnf-result/research/android-native-recovered.json'),
    ('rep-player', 'rep-player-1031-pvf/docs/REP_PLAYER_CALL_CHAIN.md'),
    ('pvf-utils-info', 'dnf-部分知识库/pvf-utils-info/Resources/AgentKnowledge/README.zh-CN.md'),
    ('workbench-311', 'dnf-部分知识库/PVF-Ai-Agent-Workbench-3.1.1/knowledge-pack/README.zh-CN.md'),
    ('native-completed-node', 'dnf-native-demo/reports/seven-job-world-20261020/mage-upper457-node/COMPLETE.json'),
    ('native-unresolved-failure', 'dnf-native-demo/reports/seven-job-world-20261020/equipment458-integration/PAUSE-RECEIPT.json'),
    ('local-policy', 'skills/KNOWLEDGE_POLICY.md'),
]


def main():
    manifest = json.loads((ROOT / 'catalog/source-manifest.json').read_text(encoding='utf-8'))
    lookup = {e['source']: e for e in manifest}
    samples = list(EXAMPLES)
    compressed = next(e for e in manifest if e['archive_encoding'] == 'gzip' and e['bytes'] < 1000000)
    duplicate = next(e for e in manifest if e['deduplicated'] and e['bytes'] < 100000)
    samples.extend([('compressed-payload', compressed['source']), ('duplicate-alias', duplicate['source'])])
    results = []
    for domain, source in samples:
        result = subprocess.run([sys.executable, str(ROOT / 'tools/read_evidence.py'), '--extract', source], check=True, capture_output=True, text=True, encoding='utf-8')
        payload = json.loads(result.stdout)
        restored = Path(payload['restored'])
        actual = hashlib.sha256(restored.read_bytes()).hexdigest()
        original = hashlib.sha256((WORKSPACE / source).read_bytes()).hexdigest()
        expected = lookup[source]['sha256']
        if actual != expected or original != expected:
            raise RuntimeError('Representative restore mismatch: ' + source)
        results.append({'domain': domain, 'source': source, 'restored': str(restored.relative_to(ROOT)), 'sha256': actual, 'status': 'pass', 'archive_encoding': lookup[source]['archive_encoding'], 'deduplicated': lookup[source]['deduplicated']})
    policy = WORKSPACE / 'skills/KNOWLEDGE_POLICY.md'
    target = ROOT / 'policy/KNOWLEDGE_POLICY.md'
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(policy.read_bytes())
    report = {'status': 'pass', 'examples_verified': len(results), 'hash_mismatches': 0, 'results': results, 'scope': 'Archive restoration and source-byte equivalence only; no original-client dynamic or gameplay claim.'}
    (ROOT / 'catalog/restore-verification.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, ensure_ascii=False))


if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    main()
