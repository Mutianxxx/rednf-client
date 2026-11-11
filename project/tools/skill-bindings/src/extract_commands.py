"""Extract skill input-command (操作指令) evidence from the 1031 Script.pvf.

Each skill .skl carries a [command] block: a token list such as
[(UP), &, (SKILL)] and a [command key explain] human string
("操作指令 : ↑(按住状态下) + Z"). This is the AUTHORITATIVE key sequence the
client (exe) parses to register the input listener that, on match, activates the
skill -- which then enters the setState handler recorded in
state-handler-events.json. Together: command(PVF) -> skill -> state(exe) ->
attack launch(exe).

The .skl [command] is PVF source data; the exe-side parser that consumes it is
not decoded here (documented as a next step). Evidence grade: PVF source,
exe-validated by the state-handler correlation in judgment-events.json.

Output keyed by skill stem so the C++ previewer can join on stemOf(skillPath).
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BASE = os.path.dirname(HERE)  # .../skill-bindings
EVID = os.path.join(BASE, "evidence")
PVF = os.environ.get("DNF1031_PVF", r"D:\dnf-rebuild\DNF1031客户端\Script.pvf")

sys.path.insert(0, r"D:\dnf-rebuild\dnf-result\tools")
from pvf_reader import Pvf, ScriptDecoder  # noqa: E402


def stem_of(path):
    return os.path.basename(path).split(".", 1)[0].lower()


def decode_name(g):
    try:
        return g.encode("cp949").decode("gbk")
    except Exception:
        return g


# skl(lower) -> (class, id, name_garbled) from skill-names.json
SN = json.load(open(os.path.join(EVID, "skill-names.json")))
inv = {}
for cls, skills in SN.items():
    for sid, info in skills.items():
        inv[info["skl"].lower()] = (cls, int(sid), info.get("name", ""))

pvf = Pvf(PVF)
sd = ScriptDecoder(pvf)
skls = [e["path"] for e in pvf.entries if e["path"].lower().endswith(".skl")]

commands = {}
n_cmd = 0
for p in skls:
    try:
        s = sd.script(p)
    except Exception:
        continue
    cmd = [f for f in s["fields"] if f["tag"].lower() == "[command]"]
    if not cmd:
        continue
    tokens = cmd[0]["values"]
    expl = [f for f in s["fields"] if f["tag"].lower() == "[command key explain]"]
    explain = expl[0]["values"][0] if expl and expl[0]["values"] else ""
    meta = inv.get(p.lower(), (None, None, None))
    key = stem_of(p)
    commands[key] = {
        "skl": p,
        "class": meta[0],
        "skill_id": meta[1],
        "name": decode_name(meta[2]),
        "command_tokens": tokens,
        "command_explain": explain,
    }
    n_cmd += 1

summary = {
    "source": "1031 Script.pvf skill/*.skl [command] / [command key explain]",
    "exe_consumer": ("exe parses [command] to register the key listener that activates the skill "
                     "(state-handler correlation in judgment-events.json); exe-side parser not yet decoded"),
    "evidence_grade": "PVF source, exe-validated by state-handler correlation",
    "skl_total": len(skls),
    "skl_with_command": n_cmd,
}

out_path = os.path.join(EVID, "skill-commands.json")
json.dump({"summary": summary, "commands": commands},
          open(out_path, "w"), indent=1, ensure_ascii=False)
print("wrote", out_path, "with_command:", n_cmd, "/", len(skls))
for k in list(commands.keys())[:8]:
    print(" ", k, commands[k]["command_tokens"], "::", commands[k]["command_explain"])
