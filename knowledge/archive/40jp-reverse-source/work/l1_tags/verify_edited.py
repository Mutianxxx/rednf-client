# -*- coding: utf-8 -*-
"""Strict verification for the functions touched by the L1 pass:
strip comments only, then compare against the dump text verbatim."""
import io, re, os

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
SRC = os.path.join(ROOT, "src", "game", "parsers")
DUMP = os.path.join(ROOT, "work")
DUMPFILES = ["dump_full_0.txt", "dump_full_1.txt", "dump_full_2.txt",
             "dump_parsers.txt", "dump_misc_a.txt", "dump_tail_c.txt"]

EDITED = {
 'item_parser.cpp': ['0x4F1A20', '0x4F2B90', '0x4F32A0', '0x4F43D0', '0x4F5B90',
                     '0x4F6790', '0x4F7C60', '0x4F8E20', '0x4F8FE0', '0x4F9240',
                     '0x4FA630', '0x4FA820', '0x4FAA40', '0x4FAC40', '0x4FB180', '0x4FBA70'],
 'monster_parser.cpp': ['0x4FC1E0', '0x4FD040', '0x4FD4C0', '0x4FE770', '0x4FF870',
                        '0x500330', '0x500B30', '0x502F00', '0x503BA0', '0x504500',
                        '0x504620', '0x507690', '0x5078C0', '0x509C90', '0x50AF40',
                        '0x50B400', '0x50B840'],
 'attackinfo_parser.cpp': ['0x50C290', '0x50D260', '0x50E7E0', '0x50EB40', '0x50F270'],
}

TYPE_MAP = [
    ('_BYTE', 'uint8_t'), ('_DWORD', 'uint32_t'), ('_WORD', 'uint16_t'),
    ('unsigned __int8', 'uint8_t'), ('unsigned __int16', 'uint16_t'),
    ('unsigned __int32', 'uint32_t'), ('unsigned int', 'uint32_t'),
    ('__int64', 'int64_t'), ('__int16', 'int16_t'), ('__int8', 'int8_t'),
    ('LONG', 'int32_t'), ('BOOL', 'int32_t'),
]

def norm(s):
    s = re.sub(r'//[^\n]*', '', s)
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    for a, b in TYPE_MAP:
        s = s.replace(a, b)
    s = s.replace('__cdecl', '').replace('__thiscall', '').replace('__stdcall', '')
    s = s.replace('__usercall', '').replace('__fastcall', '').replace('__noreturn', '')
    s = re.sub(r'\s+', ' ', s)
    return s.strip()

def src_body(path, va):
    d = io.open(path, encoding='utf-8', errors='replace', newline='').read()
    i = d.find('// %s ' % va)
    if i < 0: return None
    j = d.find('\n// ------------------------------------------------------------', i)
    if j < 0: return None
    k = d.find('\n// ------------------------------------------------------------', j + 5)
    if k < 0: k = len(d)
    return d[j:k]

def dump_bodies(va8):
    best = None
    for f in DUMPFILES:
        fp = os.path.join(DUMP, f)
        if not os.path.exists(fp): continue
        lines = io.open(fp, encoding='utf-8', errors='replace').read().splitlines()
        marks = [(i, m.group(1)) for i, l in enumerate(lines)
                 for m in [re.match(r'^// ([0-9A-F]{8})\s+(\S+)', l)] if m]
        for k, (i, v) in enumerate(marks):
            if v != va8: continue
            e = marks[k + 1][0] if k + 1 < len(marks) else len(lines)
            body = '\n'.join(lines[i + 1:e])
            if best is None or len(body) > len(best[1]):
                best = (f, body)
    return best

ok = diff = 0
for fn, vas in EDITED.items():
    for va in vas:
        b = src_body(os.path.join(SRC, fn), va)
        if b is None:
            print('SRC-MISS', fn, va); diff += 1; continue
        dm = dump_bodies(va[2:].rjust(8, '0'))
        if dm is None:
            print('DUMP-MISS', fn, va); diff += 1; continue
        a, c = norm(b), norm(dm[1])
        if a == c:
            ok += 1
        else:
            diff += 1
            k = 0
            while k < min(len(a), len(c)) and a[k] == c[k]:
                k += 1
            print('DIFF', fn, va, '(%s)' % dm[0])
            print('   src :', a[max(0, k - 50):k + 70])
            print('   dump:', c[max(0, k - 50):k + 70])
print('edited functions: identical=%d diff=%d' % (ok, diff))
