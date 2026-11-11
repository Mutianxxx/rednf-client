#!/usr/bin/env python3
"""Audit and classify 1031 .act token scripts for the P0 runtime executor.

This is deliberately a structural pass: it preserves raw fields and classifies
commands/conditions without pretending to execute ACT behavior.
"""
from __future__ import annotations
import argparse, collections, hashlib, json, os, sys
from pathlib import PurePosixPath
HERE=os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), "..", "..", "dnf-result", "tools"))
from pvf_reader import Pvf, ScriptDecoder  # type: ignore

FAMILIES={
 "create_object":("CREATE PASSIVEOBJECT","CREATE OBJECT","CREATE DRAW ONLY OBJECT","SUMMON MONSTER","SUMMON APC"),
 "animation":("SUB ANI","SUB ANI WITH XY","SUB ANI WITH XYZ","PARTICLE FILENAME","USE ANI","ANI"),
 "movement":("MOVE UNIFORM","STRAIGHT MOVE","SET SPEED","SET POS FORCE","FOLLOWING TARGET","HOMING","GRAVITY","UNDER GRAVITY"),
 "judgment":("ATTACK","ATTACKRECT","SET DAMAGE BOX","SET DAMAGE CHECK","CHANGE ATTACKINFO","DAMAGE"),
 "trigger":("TRIGGER","CHECK TIME","CHECKUP","ON ATTACKSUCCESS","ON ATTACK SUCCESS","IF","ELSE"),
 "lifecycle":("DESTROY","REMOVE","VANISH","OBJECT DESTROY","SET STATE","STATE"),
 "structure":("MOTION","BEHAVIOR","DO BEHAVIOR","FRAME","ME","LEVEL","INDEX","POS","END","SOUND","PARTICLE","ON SET ACTION","SET ACTION","CHANGE ACTION FILE"),
 "condition":("CHECKED","CHECK TIME","IS INDEX","IS IN POS","IS OBJECT TYPE","TARGET","GET TARGET","PARTY TARGET","ALL CHARACTER TEAM","RANDOM SELECT","RANDOM","IF","ELSE","ON","NOW","ENABLE","DISABLE"),
 "transform":("X AXIS","Y AXIS","Z AXIS","XPOS","YPOS","ZPOS","ZPOS","DIRECTION","FIX DIRECTION","USE MY DIRECTION","USE MAP POS","USE OBJECT ZPOS","USE MY BASEPOS","TELEPORT","MOVE","TO TARGET","DISTANCE","SPEED"),
 "audio_ui":("SPEECH","SAY SPEECH","WARNING MARK","SHAKING","NO EFFECT"),
}

def family(tag):
 t=tag.upper().strip()
 for k,keys in FAMILIES.items():
  if any(x in t for x in keys): return k
 return "other"

def main():
 ap=argparse.ArgumentParser(); ap.add_argument("--pvf",default=r"D:\dnf-rebuild\DNF1031客户端\Script.pvf"); ap.add_argument("--out",required=True); args=ap.parse_args()
 pvf=Pvf(args.pvf); sd=ScriptDecoder(pvf); tags=collections.Counter(); fam=collections.Counter(); samples=collections.defaultdict(list); errors=[]; files=0; nonempty=0
 for e in pvf.entries:
  p=e["path"]
  if PurePosixPath(p).suffix.lower() != ".act": continue
  files+=1
  try:
   s=sd.script(p)
   if s.get("fields"): nonempty+=1
   for f in s.get("fields",[]):
    t=f.get("tag",""); tags[t]+=1; fam[family(t)]+=1
    if len(samples[t])<3: samples[t].append(p)
  except Exception as ex:
   if len(errors)<100: errors.append({"path":p,"error":str(ex)})
 with open(args.pvf,"rb") as f: sha=hashlib.sha256(f.read()).hexdigest()
 command_tags={t:n for t,n in tags.items() if family(t)!="other"}
 report={"pvf":{"path":args.pvf,"sha256":sha,"entryCount":len(pvf.entries)},"summary":{"actFiles":files,"nonEmptyFiles":nonempty,"distinctTags":len(tags),"classifiedTags":len(command_tags),"unknownTags":len(tags)-len(command_tags),"parseErrors":len(errors)},"families":dict(fam),"tags":dict(tags),"classifiedTags":{t:{"family":family(t),"count":n,"samples":samples[t]} for t,n in sorted(tags.items())},"parseErrors":errors,"runtimeContract":{"create_object":["CREATE PASSIVEOBJECT","CREATE DRAW ONLY OBJECT","SUMMON MONSTER","SUMMON APC"],"animation":["SUB ANI","SUB ANI WITH XY","SUB ANI WITH XYZ","PARTICLE FILENAME"],"movement":["MOVE UNIFORM","STRAIGHT MOVE","SET SPEED","SET POS FORCE","FOLLOWING TARGET","HOMING","GRAVITY"],"judgment":["ATTACK","ATTACKRECT","SET DAMAGE BOX","SET DAMAGE CHECK","CHANGE ATTACKINFO","DAMAGE"],"trigger":["TRIGGER","CHECK TIME","ON ATTACKSUCCESS","CHECKUP"],"lifecycle":["DESTROY","REMOVE","VANISH"]}}
 os.makedirs(os.path.dirname(args.out),exist_ok=True); json.dump(report,open(args.out,"w",encoding="utf8"),ensure_ascii=False,indent=2)
 print(json.dumps(report["summary"],ensure_ascii=False))
if __name__=="__main__": main()
