# -*- coding: utf-8 -*-
"""Full-file logic verification: every function in the three L1-refined files
must (after comment stripping and type normalisation) match the dump text."""
import io, re, os

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
SRC = os.path.join(ROOT, "src", "game", "parsers")
DUMP = os.path.join(ROOT, "work")
DUMPFILES = ["dump_full_0.txt", "dump_full_1.txt", "dump_full_2.txt",
             "dump_parsers.txt", "dump_misc_a.txt", "dump_tail_c.txt"]

TYPE_MAP = [
    ('unsigned __int64', 'uint64_t'), ('unsigned __int32', 'uint32_t'),
    ('unsigned __int16', 'uint16_t'), ('unsigned __int8', 'uint8_t'),
    ('__int64', 'int64_t'), ('__int32', 'int32_t'), ('__int16', 'int16_t'), ('__int8', 'int8_t'),
    ('_BYTE', 'uint8_t'), ('_DWORD', 'uint32_t'), ('_WORD', 'uint16_t'),
    ('unsigned int', 'uint32_t'), ('unsigned short', 'uint16_t'), ('unsigned char', 'uint8_t'),
    ('LONG', 'int32_t'), ('BOOL', 'int32_t'), ('size_t', 'uint32_t'),
]

def norm(s):
    s = re.sub(r'//[^\n]*', '', s)
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    for a, b in TYPE_MAP:
        s = s.replace(a, b)
    for cc in ['__cdecl', '__thiscall', '__stdcall', '__usercall', '__fastcall',
               '__noreturn', '__declspec(noreturn)']:
        s = s.replace(cc, '')
    s = re.sub(r'\s+', ' ', s)
    s = s.replace(';', ' ; ').replace('{', ' { ').replace('}', ' } ')
    s = re.sub(r'\s+', ' ', s)
    return s.strip()

def all_funcs_src(path):
    d = io.open(path, encoding='utf-8', errors='replace', newline='').read()
    marks = [(m.start(), m.group(1)) for m in re.finditer(r'^// (0x[0-9A-F]{6}) ', d, re.M)]
    out = {}
    for idx, (pos, va) in enumerate(marks):
        # body starts after the '// ----' line that follows the (possibly multi-line) header block
        j = d.find('\n// ------------------------------------------------------------', pos)
        if j < 0:
            j = d.find('\n// ------', pos)
        if j < 0: continue
        k = d.find('\n// ------------------------------------------------------------', j + 5)
        if k < 0: k = len(d)
        out[va] = d[j:k]
    return out

def dump_index():
    idx = {}
    for f in DUMPFILES:
        fp = os.path.join(DUMP, f)
        if not os.path.exists(fp): continue
        lines = io.open(fp, encoding='utf-8', errors='replace').read().splitlines()
        marks = []
        for i, l in enumerate(lines):
            m = re.match(r'^// ([0-9A-F]{8})\s+(\S+)', l)
            if m: marks.append((i, m.group(1)))
        for k, (i, va) in enumerate(marks):
            e = marks[k + 1][0] if k + 1 < len(marks) else len(lines)
            body = '\n'.join(lines[i + 1:e])
            vakey = '0x' + va[2:].lstrip('0').rjust(6, '0') if False else '0x' + va[2:]
            vakey = '0x' + va[2:]
            if vakey not in idx or len(body) > len(idx[vakey][1]):
                idx[vakey] = (f, body)
    return idx

IDX = dump_index()
total = ok = miss = diff = 0
diffs = []
for fn in ['item_parser.cpp', 'monster_parser.cpp', 'attackinfo_parser.cpp']:
    src = all_funcs_src(os.path.join(SRC, fn))
    for va, body in sorted(src.items()):
        total += 1
        if va not in IDX:
            miss += 1
            diffs.append((fn, va, 'NO-DUMP'))
            continue
        a, b = norm(body), norm(IDX[va][1])
        if a == b:
            ok += 1
        else:
            diff += 1
            k = 0
            while k < min(len(a), len(b)) and a[k] == b[k]:
                k += 1
            diffs.append((fn, va, 'DIFF@%d src=%r dump=%r' % (k, a[max(0,k-45):k+55], b[max(0,k-45):k+55])))

print('total=%d identical=%d diff=%d nodump=%d' % (total, ok, diff, miss))
for fn, va, msg in diffs[:40]:
    print(' ', fn, va, msg)
