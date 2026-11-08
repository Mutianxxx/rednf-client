# -*- coding: utf-8 -*-
"""Verify: after stripping comments and normalizing types, the edited functions
match the dump text exactly (code unchanged by L1 pass)."""
import io, re, os

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
SRC = os.path.join(ROOT, "src", "game", "parsers")
DUMP = os.path.join(ROOT, "work")

def norm(s):
    s = re.sub(r'//[^\n]*', '', s)
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    # type cleaning done by L2 transcribe: -> keep both sides comparable
    for a, b in [('_BYTE', 'uint8_t'), ('_DWORD', 'uint32_t'), ('_WORD', 'uint16_t'),
                 ('unsigned __int8', 'uint8_t'), ('unsigned __int16', 'uint16_t'),
                 ('unsigned __int32', 'uint32_t'), ('unsigned int', 'uint32_t'),
                 ('__int64', 'int64_t'), ('__int16', 'int16_t'), ('__int8', 'int8_t'),
                 ('unsigned __int64', 'uint64_t'), ('int __cdecl', 'int /*cdecl*/'),
                 ('char __cdecl', 'char /*cdecl*/'), ('void __cdecl', 'void /*cdecl*/'),
                 ('__thiscall', '/*thiscall*/'), ('__stdcall', '/*stdcall*/'),
                 ('__usercall', '/*usercall*/'), ('__noreturn', '/*noreturn*/')]:
        s = s.replace(a, b)
    s = re.sub(r'\s+', ' ', s)
    s = s.replace('/*cdecl*/', '').replace('/*thiscall*/', '').replace('/*stdcall*/', '')
    s = s.replace('/**/', '')
    s = re.sub(r'/\*[a-z]*\*/', '', s)
    s = re.sub(r'\s+', ' ', s)
    return s.strip()

def func_from_src(path, va):
    d = io.open(path, encoding='utf-8', errors='replace', newline='').read()
    i = d.find('// %s ' % va)
    if i < 0: return None
    # skip the trailing '// ----' separator, then take the body up to the next separator
    j = d.find('\n// -----', i + 10)
    if j < 0: return None
    k = d.find('\n// -----', j + 5)
    if k < 0: k = len(d)
    return d[j:k]

def func_from_dump(path, va8):
    lines = io.open(path, encoding='utf-8', errors='replace').read().splitlines()
    for i, l in enumerate(lines):
        if l.startswith('// %s' % va8) and '=' not in l:
            j = i
            while j < len(lines) and not (lines[j].startswith('// ====') and j > i + 2):
                j += 1
            return '\n'.join(lines[i:j])
    return None

CASES = [
    ("monster_parser.cpp", "0x503BA0", "004F6790", None),
    ("monster_parser.cpp", "0x4FC1E0", None, None),
    ("item_parser.cpp", "0x4F6790", None, None),
]

# manual paired checks: (srcfile, srcva, dumpfile, dumpva)
PAIRS = [
    ("monster_parser.cpp", "0x503BA0", "dump_full_2.txt", "00503BA0"),
    ("monster_parser.cpp", "0x5078C0", "dump_full_2.txt", "005078C0"),
    ("monster_parser.cpp", "0x50B840", "dump_full_1.txt", "0050B840"),
    ("monster_parser.cpp", "0x4FD040", "dump_full_1.txt", "004FD040"),
    ("monster_parser.cpp", "0x509C90", "dump_full_1.txt", "00509C90"),
    ("item_parser.cpp", "0x4F6790", "dump_full_1.txt", "004F6790"),
    ("item_parser.cpp", "0x4F7C60", "dump_full_0.txt", "004F7C60"),
    ("item_parser.cpp", "0x4F1A20", "dump_full_2.txt", "004F1A20"),
    ("item_parser.cpp", "0x4F5B90", "dump_full_2.txt", "004F5B90"),
    ("attackinfo_parser.cpp", "0x50C290", "dump_full_0.txt", "0050C290"),
]

for sf, sva, df, dva in PAIRS:
    s = func_from_src(os.path.join(SRC, sf), sva)
    d = func_from_dump(os.path.join(DUMP, df), dva)
    if s is None or d is None:
        print("SKIP", sf, sva, "src-found" if s else "src-MISS", "dump-found" if d else "dump-MISS")
        continue
    ns, nd = norm(s), norm(d)
    same = ns == nd
    print("%-28s %-10s vs %s: %s" % (sf, sva, df, "IDENTICAL" if same else "DIFF"))
    if not same:
        # find first divergence
        k = 0
        while k < min(len(ns), len(nd)) and ns[k] == nd[k]:
            k += 1
        print("   src :", ns[max(0,k-60):k+90].replace('\n',' '))
        print("   dump:", nd[max(0,k-60):k+90].replace('\n',' '))
