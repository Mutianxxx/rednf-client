# -*- coding: utf-8 -*-
"""Reorder '---' separator lines that ended up above a section banner:
   SEP + BAR + banner-lines + BAR   ->   BAR + banner-lines + BAR + SEP
Also updates §-banner 'end' VA ranges to be accurate."""
import io, re, os

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】\src\game\parsers"
SEP = '// ------------------------------------------------------------'
BAR = '// ============================================================'

for fn in ['attackinfo_parser.cpp', 'monster_parser.cpp', 'item_parser.cpp']:
    p = os.path.join(ROOT, fn)
    d = io.open(p, encoding='utf-8', errors='replace', newline='').read()
    nl = '\r\n' if '\r\n' in d else '\n'
    pat = re.compile(re.escape(SEP) + nl + re.escape(BAR) + nl +
                     r'((?:// [^\n]*' + nl + r')+?)' + re.escape(BAR) + nl)
    def rep(m):
        return BAR + nl + m.group(1) + BAR + nl + SEP + nl
    d2, n = pat.subn(rep, d)
    io.open(p, 'w', encoding='utf-8', newline='').write(d2)
    print(fn, 'reordered', n)
