#!/usr/bin/env python3
"""Read-only audit of the hash-bound 1031 Script.pvf.

Reports extension/path topology, token-script tag coverage, parser failures, and
skill dependency references. It never modifies the PVF or client files.
"""
from __future__ import annotations
import argparse, collections, hashlib, json, os, re, sys
from pathlib import PurePosixPath

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), "..", "..", "dnf-result", "tools"))
from pvf_reader import Pvf, ScriptDecoder  # type: ignore

SCRIPT_EXTS = {".act", ".ai", ".aic", ".als", ".apd", ".atk", ".bt", ".cbt", ".cmb", ".co", ".cre", ".dgn", ".equ", ".etc", ".evt", ".exj", ".gdata", ".glist", ".hsp", ".key", ".lay", ".lst", ".map", ".mob", ".msn", ".npc", ".obj", ".ora", ".pet", ".qst", ".rep", ".rgn", ".sd", ".shp", ".skl", ".stk", ".str", ".stm", ".tbl", ".til", ".twn", ".ui", ".vm", ".wdm", ".wrd"}
BINARY_EXTS = {".ani", ".ani__", ".ani_new", ".ptl", ".bin", ".dl", ".blu", ".img", ".npk"}
SKILL_ROOTS = ("skill/", "sqr/character/", "sqr/passiveobject/", "character/", "passiveobject/")
PATH_RE = re.compile(r"(?:[A-Za-z0-9_%-]+/)+[A-Za-z0-9_.%-]+\.(?:ani|als|atk|obj|ptl|nut|act|skl|sqr|mob|chr|equ|img|wav|ogg)", re.I)
NORMALIZED_PATH_KEYS = {"/" + x for x in ()}

def path_candidates(value):
    """Yield literal and common PVF-relative forms without changing source bytes."""
    if not isinstance(value, str): return []
    out = [value.replace("\\", "/")]
    for prefix in ("character/", "passiveobject/", "skill/", "sqr/"):
        if value.lower().startswith(prefix): out.append(value)
    return out

def ext(path):
    return PurePosixPath(path).suffix.lower() or "<none>"

def root(path):
    return path.split("/", 1)[0].lower()

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pvf", default=r"D:\dnf-rebuild\DNF1031客户端\Script.pvf")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()
    pvf = Pvf(args.pvf)
    sd = ScriptDecoder(pvf)
    entries = pvf.entries
    by_path = {e["path"].lower(): e["path"] for e in entries}
    extension_counts = collections.Counter(ext(e["path"]) for e in entries)
    root_counts = collections.Counter(root(e["path"]) for e in entries)
    tag_counts = collections.defaultdict(collections.Counter)
    parsed_counts = collections.Counter()
    parse_errors = collections.defaultdict(list)
    tag_samples = collections.defaultdict(lambda: collections.defaultdict(list))
    refs = collections.defaultdict(collections.Counter)
    skill_files = []
    known_tag_status = {}
    for e in entries:
        path = e["path"]
        x = ext(path)
        if x == ".skl": skill_files.append(path)
        if x not in SCRIPT_EXTS:
            parsed_counts[x + ":binary_or_non_token"] += 1
            continue
        try:
            s = sd.script(path)
            parsed_counts[x + ":parsed"] += 1
            tags = [f["tag"] for f in s["fields"]]
            for tag in tags:
                tag_counts[x][tag] += 1
                known_tag_status.setdefault(tag, "observed; semantic coverage must be checked by consumer")
                if len(tag_samples[x][tag]) < 3:
                    tag_samples[x][tag].append(path)
            for tok in s["tokens"]:
                v = tok.get("value")
                if isinstance(v, str):
                    for m in PATH_RE.finditer(v):
                        ref = m.group(0).replace("\\", "/").lower()
                        if ref in by_path:
                            refs[path][ext(ref)] += 1
        except Exception as exc:
            parsed_counts[x + ":parse_error"] += 1
            if len(parse_errors[x]) < 30:
                parse_errors[x].append({"path": path, "error": str(exc)})
    # Skill dependency closure: all references from skill/*.skl and skill-adjacent sqr.
    skill_refs = collections.defaultdict(collections.Counter)
    for parent, counts in refs.items():
        lp = parent.lower()
        if lp.startswith("skill/") or lp.startswith("sqr/"):
            skill_refs[parent] = counts
    with open(args.pvf, "rb") as raw_pvf:
        pvf_sha256 = hashlib.file_digest(raw_pvf, "sha256").hexdigest()
    report = {
        "pvf": {"path": args.pvf, "sha256": pvf_sha256, "entry_count": len(entries), "reader_warnings": sd.warnings[:100]},
        "topology": {"extensions": extension_counts, "roots": root_counts},
        "parser": {"script_extensions": sorted(SCRIPT_EXTS), "binary_extensions": sorted(BINARY_EXTS), "counts": parsed_counts, "parse_errors": parse_errors},
        "tags": {x: {k: v for k, v in sorted(c.items(), key=lambda z: (-z[1], z[0]))} for x, c in tag_counts.items()},
        "tag_samples": {x: {k: v for k, v in samples.items()} for x, samples in tag_samples.items()},
        "skill_files": {"count": len(skill_files), "paths": skill_files},
        "skill_dependency_refs": {p: dict(c) for p, c in sorted(skill_refs.items())},
        "interpretation": {
            "known": [".ani binary animation frames/boxes/properties", ".skl skill fields", ".obj passive object fields", ".atk attack payload fields", ".als animation-layer commands", ".act action timeline commands", ".nut NUT source text (under sqr/)"],
            "not_fully_decoded": [".ptl particle bytecode/particle resources", ".equ/.stk/.key/.ai/.aic/.evt and other script families: token syntax is decoded, but every tag's runtime consumer is not yet mapped", "ANI property IDs beyond the currently mapped render subset", "NUT runtime semantics: source text is available but no complete Squirrel VM/host execution"],
            "important": "A token parser successfully reading a file does not mean its tags or runtime commands are semantically implemented. This audit separates syntax coverage from consumer coverage."
        }
    }
    def plain(v):
        if isinstance(v, collections.Counter): return dict(v)
        if isinstance(v, dict): return {k: plain(x) for k,x in v.items()}
        if isinstance(v, list): return [plain(x) for x in v]
        return v
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as f: json.dump(plain(report), f, ensure_ascii=False, indent=2)
    print(json.dumps({"entries": len(entries), "parsed": dict(parsed_counts), "extensions": dict(extension_counts), "tag_families": sorted(tag_counts)}, ensure_ascii=False))

if __name__ == "__main__": main()
