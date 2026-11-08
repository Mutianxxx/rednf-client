"""Compare regenerated content with the released upstream behavior baseline."""
from pathlib import Path
import hashlib, json

def canonical(value):return hashlib.sha256(json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':')).encode('utf8')).hexdigest()

def compare(root):
    baseline=json.loads((root/'reference/content-baseline.json').read_text('utf8'));results=[]
    for name,expected in baseline['content'].items():
        p=root/'demo/content'/name
        actual=canonical(json.loads(p.read_text('utf8'))) if name.endswith('.json') else hashlib.sha256(p.read_bytes()).hexdigest()
        results.append(dict(path=name,expected=expected,actual=actual,passed=actual==expected))
    return dict(passed=all(r['passed'] for r in results),files=results,
        scope='Canonical JSON equality, all arrays and values retained. Only eight evidence-link prefixes relocated in expected baseline; resources.bin must match byte-for-byte.')

if __name__=='__main__':
    root=Path(__file__).resolve().parents[1];r=compare(root)
    out=root/'demo/reports/content-comparison.json';out.parent.mkdir(parents=True,exist_ok=True);out.write_text(json.dumps(r,indent=2),encoding='utf8')
    print(json.dumps(r,indent=2));raise SystemExit(0 if r['passed'] else 1)
