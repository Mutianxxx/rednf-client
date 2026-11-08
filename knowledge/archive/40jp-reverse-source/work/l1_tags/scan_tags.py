# -*- coding: utf-8 -*-
import re, io, os, json

FILES = [
 r"E:\DOF LX\【40JP逆向源代码工程】\src\game\parsers\item_parser.cpp",
 r"E:\DOF LX\【40JP逆向源代码工程】\src\game\parsers\monster_parser.cpp",
 r"E:\DOF LX\【40JP逆向源代码工程】\src\game\parsers\attackinfo_parser.cpp",
]
OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\l1_tags"

hdr = re.compile(r'^//\s*(0x[0-9A-Fa-f]{6,8})\s*(\S*)\s*(.*)$')
lit = re.compile(r'"((?:[^"\\]|\\.)*?)"')
tagre = re.compile(r'^\[[A-Za-z][^\]]*\]$')

for f in FILES:
    with io.open(f, 'r', encoding='utf-8', errors='replace') as fh:
        lines = fh.readlines()
    funcs = []
    cur = None
    for i, ln in enumerate(lines):
        m = hdr.match(ln.rstrip('\n'))
        if m and ln.startswith('//'):
            cur = {'va': m.group(1), 'name': m.group(2), 'extra': m.group(3), 'start': i, 'tags': []}
            funcs.append(cur)
        elif cur is not None:
            for lm in lit.finditer(ln):
                s = lm.group(1).strip()
                if tagre.match(s) and not s.startswith('[esp') and not s.startswith('[ebp'):
                    if s not in cur['tags']:
                        cur['tags'].append(s)
    print("=" * 70)
    print(os.path.basename(f), "funcs:", len(funcs))
    ntag = sum(1 for fn in funcs if fn['tags'])
    print("funcs with tags:", ntag)
    print("-" * 70)
    for fn in funcs:
        if fn['tags']:
            print("%s %-42s | %s" % (fn['va'], fn['name'], " ".join(fn['tags'])))
    with io.open(os.path.join(OUT, os.path.basename(f) + '.json'), 'w', encoding='utf-8') as jf:
        json.dump(funcs, jf, ensure_ascii=False, indent=1)
