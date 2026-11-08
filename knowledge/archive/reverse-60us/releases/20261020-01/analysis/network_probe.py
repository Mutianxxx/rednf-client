import json
import requests
queries = ['rep skill reverse engineering', 'reverse engineering skills ghidra']
for q in queries:
    r = requests.get('https://api.github.com/search/repositories', params={'q': q, 'per_page': 5}, timeout=30)
    print(q, r.status_code)
    if r.ok:
        print(json.dumps([{'name': i['full_name'], 'description': i['description']} for i in r.json()['items']], ensure_ascii=True))
r = requests.get('https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/tags/Ghidra_11.3.2_build', timeout=30)
print('Ghidra', r.status_code)
if r.ok:
    print(json.dumps([{k: a[k] for k in ['name','size','browser_download_url']} for a in r.json()['assets']]))
