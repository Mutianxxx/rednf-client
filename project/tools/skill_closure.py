#!/usr/bin/env python3
"""Build a reproducible 1031 skill resource closure report.

The 1031 SKL files normally do not contain ANI/OBJ/ACT references. The
runtime bridge is exe setState -> CHR motion -> ANI; this tool therefore joins
exe binding evidence with PVF path families instead of claiming SKL references
that are not present.
"""
from __future__ import annotations
import argparse, collections, hashlib, json, os, re, sys
from pathlib import PurePosixPath

ROOT = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(ROOT), "..", "..", "dnf-result", "tools"))
from pvf_reader import Pvf, ScriptDecoder  # type: ignore

BIND = os.path.join(ROOT, "skill-bindings", "bindings")
PATH_RE = re.compile(r"(?:[A-Za-z0-9_%-]+/)+[A-Za-z0-9_.%-]+\.(?:ani|als|atk|obj|ptl|nut|act|skl|chr|img)", re.I)

def ext(p):
    s = PurePosixPath(p).suffix.lower()
    return s or "<none>"

def stem(p):
    return PurePosixPath(p).stem.lower()

def norm(p):
    return p.replace("\\", "/").lstrip("/").lower()

def load_bindings():
    out=[]
    for fn in sorted(os.listdir(BIND)):
        if not fn.endswith(".json"): continue
        d=json.load(open(os.path.join(BIND,fn),encoding="utf8"))
        for sid,sk in d.get("skills",{}).items():
            out.append({"class":d.get("class",fn[:-5]),"skillId":int(sid),"skl":sk.get("skl"),"states":sk.get("states") or [],"effectAnis":sk.get("effect_anis") or []})
    return out

def add_family(rec, kind, path, reason):
    p=rec["resources"].setdefault(kind,[])
    item={"path":path,"reason":reason}
    if item not in p: p.append(item)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--pvf",default=r"D:\dnf-rebuild\DNF1031客户端\Script.pvf")
    ap.add_argument("--out",required=True)
    args=ap.parse_args()
    pvf=Pvf(args.pvf); sd=ScriptDecoder(pvf)
    entries=[e["path"] for e in pvf.entries]
    by={norm(p):p for p in entries}
    by_ext=collections.defaultdict(list)
    for p in entries: by_ext[ext(p)].append(p)
    bindings=load_bindings()
    # Pre-index family candidates once; scanning all 335k entries per skill is too expensive.
    family_index=collections.defaultdict(list)
    for p in entries:
        q=norm(p)
        if ext(p) in {".ani",".als",".obj",".ptl",".atk",".act",".nut"} and ("/effect/animation/" in q or "/animation/" in q or q.startswith("sqr/")):
            family_index[ext(p)].append(p)
    records=[]; consumed=collections.Counter(); unresolved=collections.Counter(); direct_refs=collections.Counter()
    for b in bindings:
        skl=b["skl"] or ""
        base=stem(skl); cls=b["class"]; rec={"class":cls,"skillId":b["skillId"],"skl":skl,"stem":base,"resources":{},"unresolved":[]}
        # SKL itself is a source record; preserve its actual case-insensitive path.
        if norm("skill/"+skl) in by: add_family(rec,"skl",by[norm("skill/"+skl)],"skill definition")
        # Direct exe setState evidence: entry motions are CHR-relative names.
        for st in b["states"]:
            for m in st.get("entry_motions") or []:
                ani=m.get("ani") or ""
                candidates=[f"character/{cls}/{ani}",f"character/{'swordman' if cls=='demonicswordman' else cls}/{ani}"]
                hit=next((by[norm(x)] for x in candidates if norm(x) in by),None)
                if hit: add_family(rec,"ani",hit,f"exe state {st.get('state')} entry motion index {m.get('index')}")
                else: rec["unresolved"].append({"kind":"ani","value":ani,"source":"exe entry_motions","state":st.get("state")}); unresolved["ani"]+=1
        # Generated/sidecar families used by the current mapper.
        jobs=[cls, "swordman" if cls=="demonicswordman" else cls]
        for job in dict.fromkeys(jobs):
            roots=[f"character/{job}/effect/animation/{base}/",f"character/{job}/effect/animation/at{base}/",f"passiveobject/character/{job}/{base}",f"passiveobject/character/{job}/animation/{base}/",f"sqr/character/{job}/{base}/",f"sqr/character/{job}/"]
            for p in family_index[".ani"] + family_index[".als"] + family_index[".obj"] + family_index[".ptl"] + family_index[".atk"] + family_index[".act"] + family_index[".nut"]:
                q=norm(p)
                if any(q==norm(r) or q.startswith(norm(r)) for r in roots):
                    e=ext(p)
                    kind={".ani":"ani",".als":"als",".obj":"obj",".ptl":"ptl",".atk":"atk",".act":"act",".nut":"nut"}.get(e)
                    if kind: add_family(rec,kind,p,"skill stem family")
        # Explicit effect ANI names from exe extraction.
        for value in b["effectAnis"]:
            candidates=[]
            for job in jobs:
                candidates += [f"character/{job}/{value}",f"character/{job}/effect/{value}"]
            hit=next((by[norm(x)] for x in candidates if norm(x) in by),None)
            if hit: add_family(rec,"ani",hit,"exe effect_anis")
            else: rec["unresolved"].append({"kind":"ani","value":value,"source":"exe effect_anis"}); unresolved["ani"]+=1
        # Parse adjacent NUT text and record literal PVF references.
        for p in list(rec["resources"].get("nut",[])):
            try:
                raw=pvf.read(p).decode("utf8","replace")
                for m in PATH_RE.finditer(raw):
                    val=m.group(0); direct_refs[ext(val)]+=1
                    if norm(val) in by: add_family(rec,{".ani":"ani",".obj":"obj",".als":"als",".atk":"atk",".ptl":"ptl",".act":"act",".skl":"skl"}.get(ext(val),"raw"),by[norm(val)],"literal NUT reference")
                    else: rec["unresolved"].append({"kind":ext(val),"value":val,"source":"NUT literal"}); unresolved[ext(val)]+=1
            except Exception: pass
        for kind, items in rec["resources"].items(): consumed.update((kind,p["path"]) for p in items)
        records.append(rec)
    # Candidate files in skill families not consumed by any skill record.
    candidates=[]
    for p in family_index[".ani"] + family_index[".als"] + family_index[".obj"] + family_index[".ptl"] + family_index[".atk"] + family_index[".act"]:
        q=norm(p)
        if any(x in q for x in ("/effect/animation/","/animation/")):
            candidates.append({"path":p,"kind":ext(p),"reason":"family candidate not joined to a binding"})
    uncons=[x for x in candidates if ( {".ani":"ani",".als":"als",".obj":"obj",".ptl":"ptl",".atk":"atk",".act":"act"}[x["kind"]],x["path"]) not in consumed]
    with open(args.pvf,"rb") as f: sha=hashlib.sha256(f.read()).hexdigest()
    report={"pvf":{"path":args.pvf,"sha256":sha,"entryCount":len(entries)},"method":{"important":"SKL usually has no ANI/OBJ/ACT references; exe setState entry_motions and stem families are separate joins","bindingCount":len(bindings)},"summary":{"skills":len(records),"skillsWithResources":sum(bool(r["resources"]) for r in records),"unresolvedByKind":dict(unresolved),"unconsumedFamilyCandidates":len(uncons)},"skills":records,"unconsumedFamilyCandidates":uncons[:5000],"directNutReferenceCounts":dict(direct_refs)}
    os.makedirs(os.path.dirname(args.out),exist_ok=True)
    json.dump(report,open(args.out,"w",encoding="utf8"),ensure_ascii=False,indent=2)
    print(json.dumps(report["summary"],ensure_ascii=False))
if __name__=="__main__": main()
