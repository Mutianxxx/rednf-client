import re, os, sys, collections, random, hashlib, statistics, datetime

SRC_ROOT = sys.argv[1]          # root containing src/
IDA_PATH = sys.argv[2]          # path to ida_all_functions.txt
OUT_ROOT = sys.argv[3]          # real project root for data/audit_*.txt
SEP = os.sep

# ---------- IDA table ----------
ida = {}
for line in open(IDA_PATH, encoding='utf-8', errors='replace'):
    p = line.rstrip('\r\n').split('\t')
    if len(p) >= 2 and p[0].strip():
        ida[p[0].strip().upper()] = (int(p[1]) if p[1].isdigit() else -1, p[2].strip() if len(p) > 2 else '')

marker_start = re.compile(r'^\s*//\s*(0x[0-9A-Fa-f]{6,8})')
marker_any = re.compile(r'//\s*(0x[0-9A-Fa-f]{6,8})')
TRUNC = re.compile(r'\(\.\.\.truncated,\s*total\s+(\d+)\s+lines\)')
DECOMP_FAIL = re.compile(r'\(decomp failed\)')
EXCEPTION = re.compile(r'\(exception')
codelike = re.compile(r'^[A-Za-z_#].*[({;]')

srcfiles = []
for dirpath, _, files in os.walk(os.path.join(SRC_ROOT, 'src')):
    for fn in files:
        if fn.endswith('.cpp'):
            srcfiles.append(os.path.join(dirpath, fn))
srcfiles.sort()

# dynamic tree hash for provenance
_th = hashlib.md5()
for fp in srcfiles:
    _th.update(open(fp, 'rb').read())
TREE_MD5 = _th.hexdigest()

# ---------- parse ----------
header_occ = collections.defaultdict(list)   # va -> [(rel, lineno, blocktext, lookahead)]
inline_occ = collections.defaultdict(list)   # va -> [(rel, lineno)]
file_stats = []
total_lines = 0
for fp in srcfiles:
    rel = fp.replace(SRC_ROOT + SEP, '').replace('\\', '/')
    lines = open(fp, encoding='utf-8', errors='replace').readlines()
    total_lines += len(lines)
    hdrs = [(i, m.group(1)[2:].upper().zfill(8)) for i, line in enumerate(lines)
            for m in [marker_start.match(line)] if m]
    file_stats.append((rel, len(hdrs), len(lines)))
    for i, line in enumerate(lines):
        m = marker_any.search(line)
        if m and not marker_start.match(line):
            inline_occ[m.group(1)[2:].upper().zfill(8)].append((rel, i + 1))
    for idx, (i, va) in enumerate(hdrs):
        end = hdrs[idx + 1][0] if idx + 1 < len(hdrs) else len(lines)
        block = lines[i:end]
        la = lines[i + 1:i + 5]
        header_occ[va].append((rel, i + 1, ''.join(block), ''.join(la), len(block), len([l for l in block if l.strip()])))

def has_real_body(blocktext, lookahead):
    if '{' in blocktext:
        return True
    if '{' in lookahead:
        return True
    return False

ida_set = set(ida)
hdr_set = set(header_occ)
inline_set = set(inline_occ)

missing = sorted(ida_set - hdr_set)
phantom_hdr = sorted(hdr_set - ida_set)
phantom_inline = sorted(inline_set - ida_set)

# ---------- A. coverage ----------
ts = datetime.datetime.now().isoformat(timespec='seconds')
with open(os.path.join(OUT_ROOT, 'data/audit_missing.txt'), 'w', encoding='utf-8') as f:
    f.write("# audit snapshot: %s  src tree md5(%s)\n" % (ts, TREE_MD5))
    f.write("# Missing VAs (IDA table minus source header markers): %d / %d\n" % (len(missing), len(ida_set)))
    f.write("# strict marker coverage: %.4f%%\n" % (100.0 * (len(ida_set) - len(missing)) / len(ida_set)))
    f.write("# VA\tsize\tname\n")
    for va in missing:
        s, n = ida[va]
        f.write("%s\t%d\t%s\n" % (va, s, n))

# ---------- phantom ----------
def covered_by_addr(v):
    import bisect
    keys = sorted(int(x, 16) for x in ida_set)
    i = bisect.bisect_right(keys, v) - 1
    if i >= 0:
        a = keys[i]
        va = "%08X" % a
        s, n = ida[va]
        if a <= v < a + s:
            return "%s %s +0x%X" % (va, n, v - a)
    return None

with open(os.path.join(OUT_ROOT, 'data/audit_phantom.txt'), 'w', encoding='utf-8') as f:
    f.write("# Phantom VAs (source marker, not an IDA function-table entry)\n")
    f.write("# header-marker phantoms: %d ; inline-comment phantoms: %d\n" % (len(phantom_hdr), len(phantom_inline)))
    f.write("\n# --- A) header-marker phantoms (function claims) ---\n")
    for va in phantom_hdr:
        occ = header_occ[va]
        inside = covered_by_addr(int(va, 16))
        f.write("%s\tinside=%s\t%s:%d\n" % (va, inside or 'NO_OWNER', occ[0][0], occ[0][1]))
    f.write("\n# --- B) inline data-address phantoms (likely .data globals, benign) ---\n")
    for va in phantom_inline:
        occ = inline_occ[va]
        f.write("%s\t%s:%d\n" % (va, occ[0][0], occ[0][1]))

# ---------- B. duplicates ----------
dups = {va: occ for va, occ in header_occ.items() if len(occ) > 1}
def layer(rel):
    return 'L1' if (rel.startswith('src/nengine/') or rel.startswith('src/cnrd/') or rel.startswith('src/game/module/')) else 'L2'
kinds = collections.Counter()
detail_rows = []
for va in sorted(dups):
    occ = dups[va]
    files = set(o[0] for o in occ)
    lays = set(layer(o[0]) for o in occ)
    if len(files) == 1:
        kind = 'SAME-FILE'
    elif len(lays) > 1:
        kind = 'CROSS-LAYER(L1+L2)'
    else:
        kind = 'CROSS-FILE(%s)' % list(lays)[0]
    kinds[kind] += 1
    detail_rows.append((va, kind, occ))
with open(os.path.join(OUT_ROOT, 'data/audit_duplicates.txt'), 'w', encoding='utf-8') as f:
    f.write("# Duplicate VA coverage (header markers only) — tree md5=%s @ %s\n" % (TREE_MD5, ts))
    f.write("# VAs with >1 header marker: %d ; total header marker occurrences: %d ; extra occurrences: %d\n" %
            (len(dups), sum(len(v) for v in header_occ.values()), sum(len(v) - 1 for v in dups.values())))
    f.write("# L1 = src/nengine|cnrd|game/module ; L2 = rest. CROSS-LAYER = intended dual coverage.\n")
    for k, c in kinds.most_common():
        f.write("#   %s\t%d\n" % (k, c))
    f.write("\n")
    for va, kind, occ in detail_rows:
        f.write("%s\t%s\tcnt=%d\n" % (va, kind, len(occ)))
        for rel, ln, bt, la, nb_lines, nb_nonblank in occ:
            mk = 'TRUNC' if 'truncated, total' in bt else ('NOBODY' if not has_real_body(bt, la) else '')
            f.write("    %s:%d (lines=%d, nonblank=%d) %s\n" % (rel, ln, nb_lines, nb_nonblank, mk))
print("A/B done. strict coverage %.4f%% missing=%d phantom_hdr=%d phantom_inline=%d dupVA=%d" % (
    100.0 * (len(ida_set) - len(missing)) / len(ida_set), len(missing), len(phantom_hdr), len(phantom_inline), len(dups)))
print("dup kinds:", dict(kinds))
for va in phantom_hdr:
    occ = header_occ[va]
    print("PHANTOM-HDR", va, 'inside=', covered_by_addr(int(va, 16)), occ[0][0] + ':' + str(occ[0][1]))

# ---------- C. spotcheck ----------
random.seed(40)
ida_items = sorted((int(va, 16), va) for va in ida)
bucket = len(ida_items) // 20
picks = []
for b in range(20):
    seg = ida_items[b * bucket:] if b == 19 else ida_items[b * bucket:(b + 1) * bucket]
    picks.append(random.choice(seg))
lines_out = []
ok = 0
for v, va in picks:
    sz, nm = ida[va]
    if va not in header_occ:
        lines_out.append("%s\t%s\tsize=%d\tMISSING_IN_SOURCE\tFAIL" % (va, nm, sz))
        continue
    rel, ln, bt, la, nb_lines, nb_nonblank = header_occ[va][0]
    verdict = []
    if not has_real_body(bt, la):
        verdict.append('NO_BODY')
    if nb_nonblank < 3:
        verdict.append('LT3_NONBLANK')
    if DECOMP_FAIL.search(bt):
        verdict.append('DECOMP_FAILED')
    if EXCEPTION.search(bt):
        verdict.append('EXCEPTION')
    if TRUNC.search(bt):
        verdict.append('TRUNCATED')
    status = 'PASS' if not verdict else 'FAIL:' + ','.join(verdict)
    if status == 'PASS':
        ok += 1
    lines_out.append("%s\t%s\tsize=%d\t%s:%d\tnonblank=%d\ttrunc=%s\t%s" % (
        va, nm, sz, rel, ln, nb_nonblank, 'Y' if 'TRUNCATED' in verdict else 'N', status))
with open(os.path.join(OUT_ROOT, 'data/audit_spotcheck.txt'), 'w', encoding='utf-8') as f:
    f.write("# Random spotcheck 20 functions (one per VA-space bucket, seed=40) — tree md5=%s\n" % TREE_MD5)
    f.write("# verdict FAIL if: no body / <3 nonblank lines / (decomp failed) / (exception / truncated marker\n")
    f.write("# VA\tname\tida_size\tsrc_loc\tnonblank\ttrunc\tverdict\n")
    f.write("\n".join(lines_out) + "\n")
    f.write("\n# PASS %d / 20\n" % ok)
print("C spotcheck PASS %d/20" % ok)

# ---------- D. shells ----------
stats = collections.Counter()
df_list, ex_list, nb_list, lt3_list, trunc_list = [], [], [], [], []
for va in sorted(header_occ):
    for rel, ln, bt, la, nb_lines, nb_nonblank in header_occ[va]:
        if DECOMP_FAIL.search(bt):
            stats['decomp_failed'] += 1
            df_list.append((va, rel, ln))
        if EXCEPTION.search(bt):
            stats['exception'] += 1
            ex_list.append((va, rel, ln))
        m = TRUNC.search(bt)
        if m:
            stats['truncated'] += 1
            trunc_list.append((va, rel, ln, int(m.group(1)), nb_lines, nb_nonblank))
        if not has_real_body(bt, la):
            stats['no_body'] += 1
            nb_list.append((va, rel, ln))
        if nb_nonblank < 3:
            stats['lt3'] += 1
            lt3_list.append((va, rel, ln, nb_nonblank))
        if nb_nonblank <= 1:
            stats['empty'] += 1
# VAs with no complete body anywhere
gap_va = []
for va in sorted(header_occ):
    occ = header_occ[va]
    complete = [o for o in occ if has_real_body(o[2], o[3]) and not TRUNC.search(o[2])]
    if not complete:
        gap_va.append(va)
dropped = sum(t[3] - t[4] for t in trunc_list)
with open(os.path.join(OUT_ROOT, 'data/audit_shells.txt'), 'w', encoding='utf-8') as f:
    f.write("# Shell/anomaly scan — tree md5=%s @ %s\n" % (TREE_MD5, ts))
    f.write("# header blocks: %d ; unique VAs: %d ; files: %d ; total lines: %d\n" %
            (sum(len(v) for v in header_occ.values()), len(header_occ), len(srcfiles), total_lines))
    f.write("# (decomp failed) blocks: %d\n" % stats['decomp_failed'])
    f.write("# (exception blocks: %d\n" % stats['exception'])
    f.write("# truncated blocks: %d (declared-dropped lines: %d, avg %.1f)\n" %
            (stats['truncated'], dropped, dropped / max(stats['truncated'], 1)))
    f.write("# no-body blocks (index-only comments): %d\n" % stats['no_body'])
    f.write("# blocks with <3 nonblank lines: %d ; <=1 line: %d\n" % (stats['lt3'], stats['empty']))
    f.write("# VAs with NO complete body anywhere (all truncated or no-body): %d\n" % len(gap_va))
    f.write("# effective deep coverage = (12172 - %d)/12172 = %.4f%%\n" %
            (len(gap_va), 100.0 * (12172 - len(gap_va)) / 12172))
    f.write("\n# --- (decomp failed) VAs ---\n")
    for x in df_list:
        f.write("%s\t%s:%d\n" % x)
    f.write("\n# --- (exception VAs ---\n")
    for x in ex_list:
        f.write("%s\t%s:%d\n" % x)
    f.write("\n# --- no-body VAs ---\n")
    for x in nb_list:
        f.write("%s\t%s:%d\n" % x)
    f.write("\n# --- <3 nonblank VAs ---\n")
    for x in lt3_list:
        f.write("%s\t%s:%d\tnonblank=%d\n" % x)
    f.write("\n# --- truncated blocks (VA, loc, declared_total, block_lines) ---\n")
    for x in sorted(trunc_list, key=lambda z: -(z[3] - z[4])):
        f.write("%s\t%s:%d\tdeclared=%d\tactual=%d\tdropped=%d\n" % (x[0], x[1], x[2], x[3], x[4], x[3] - x[4]))
    f.write("\n# --- VAs with NO complete body anywhere ---\n")
    for va in gap_va:
        sz, nm = ida.get(va, (-1, '?'))
        locs = '; '.join('%s:%d' % (o[0], o[1]) for o in header_occ[va])
        f.write("%s\tsize=%d\t%s\t%s\n" % (va, sz, nm, locs))
print("D done: df=%d ex=%d trunc=%d nobody=%d lt3=%d gapVA=%d dropped_lines=%d" % (
    stats['decomp_failed'], stats['exception'], stats['truncated'], stats['no_body'], stats['lt3'], len(gap_va), dropped))

# ---------- E. file stats ----------
zeros = [fs for fs in file_stats if fs[1] == 0]
with open(os.path.join(OUT_ROOT, 'data/audit_file_stats.txt'), 'w', encoding='utf-8') as f:
    f.write("# File stats — tree md5=%s @ %s\n" % (TREE_MD5, ts))
    f.write("# files: %d ; total lines: %d ; total header functions: %d\n" % (len(file_stats), total_lines, sum(fs[1] for fs in file_stats)))
    f.write("# file\tfunctions\tlines\tbytes\n")
    for rel, nf, nl in sorted(file_stats, key=lambda x: -x[1]):
        f.write("%s\t%d\t%d\t%d\n" % (rel, nf, nl, os.path.getsize(os.path.join(SRC_ROOT, rel))))
    f.write("\n# zero-function files: %d\n" % len(zeros))
    for rel, nf, nl in zeros:
        f.write("ZERO-FUNC\t%s\tlines=%d\n" % (rel, nl))
    # small files
    small = [(rel, nf, nl) for rel, nf, nl in file_stats if nf > 0 and nl / max(nf, 1) < 8]
    f.write("\n# dense/small files (lines/function < 8): %d\n" % len(small))
    for rel, nf, nl in small:
        f.write("SMALL\t%s\tfuncs=%d\tlines=%d\tlines/func=%.1f\n" % (rel, nf, nl, nl / nf))
print("E done: zero-func=%d small=%d" % (len(zeros), len(small)))
print("SNAPSHOT-OK")
