# -*- coding: utf-8 -*-
"""Brace/paren balance check per function for the three L1-refined files."""
import io, os, re

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】\src\game\parsers"
HDR = re.compile(r'^// (0x[0-9A-F]{6}) (\S+)')
SEP = '// ------------------------------------------------------------'

for fn in ['item_parser.cpp', 'monster_parser.cpp', 'attackinfo_parser.cpp']:
    p = os.path.join(ROOT, fn)
    d = io.open(p, encoding='utf-8', errors='replace', newline='').read()
    lines = d.splitlines()
    starts = [i for i, l in enumerate(lines) if HDR.match(l)]
    bad = 0
    for k, s in enumerate(starts):
        e = starts[k + 1] if k + 1 < len(starts) else len(lines)
        seg = '\n'.join(lines[s:e])
        seg = re.sub(r'//[^\n]*', '', seg)
        seg = re.sub(r'/\*.*?\*/', '', seg, flags=re.S)
        # strip string literals
        seg = re.sub(r'"(\\.|[^"\\])*"', '""', seg)
        seg = re.sub(r"'(\\.|[^'\\])*'", "''", seg)
        b = seg.count('{') - seg.count('}')
        pr = seg.count('(') - seg.count(')')
        if b != 0 or pr != 0:
            bad += 1
            print('%s %s braces=%+d parens=%+d' % (fn, HDR.match(lines[s]).group(1), b, pr))
    print('%s: %d functions, %d unbalanced' % (fn, len(starts), bad))
