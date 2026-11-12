#!/usr/bin/env python3
"""清风 1031 技能级入口与消费者账本（P0-1 交付物）。

补充 V3 静态闭包缺失的「技能执行入口」边：技能整数注册、NUT
状态/被动对象注册表、exe setState 绑定、OBJ action 字面引用，以及
技能脚本内明确的被动对象创建 API。随后把这些边接到既有
ActWorldHost 静态准入结果，形成技能 / 资源 / 标签 / 消费者账本。

这是静态证据账本：不执行 NUT、不模拟 World、不证明原版表现等价。
"""
from __future__ import annotations

import argparse
import collections
import hashlib
import json
import os
import posixpath
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(os.path.dirname(HERE), "..", "..", "dnf-result", "tools"))

from pvf_reader import Pvf, ScriptDecoder  # type: ignore
from skill_closure import (  # type: ignore
    BASEJOB, PATH_RE, ResourceGraph, ext, file_hash, load_bindings, norm, stem,
)

WORKSPACE = os.path.dirname(os.path.dirname(HERE))
AUDIT_DIR = os.path.join(WORKSPACE, "checkpoints", "tests", "pvf-audit")
DEFAULT_PVF = "D:/dnf-rebuild/DNF1031客户端/Script.pvf"

# 只有明确的对象创建 API 才允许把 NUT 中的整数解释为被动对象 ID。
NUT_CREATE_RE = re.compile(
    r"\b(?:[A-Za-z_]\w*\s*\.\s*)?"
    r"(sq_(?:SendCreatePassiveObjectPacket(?:FromPassivePos|FromPassive|Pos)?"
    r"|p00_sendCreatePassiveObjectPacket|CreatePassiveObjectAfterWarning))\s*\(",
    re.I,
)
REGISTER_CALL_RE = re.compile(
    r"\b(?:IRDSQRCharacter|CNAvenger)\.(pushState|pushPassiveObj|pushScriptFiles)\s*\(",
    re.I,
)
SCRIPT_FILE_RE = re.compile(r'(?:pushScriptFiles|sq_RunScript)\s*\(\s*"([^"]+)"')
ASSIGN_RE = re.compile(r'(?:^|\n)\s*(?:local\s+)?([A-Za-z_]\w*)\s*=\s*"([^"]*)"\s*;')
CONST_RE = re.compile(
    r"^\s*(?:const\s+)?((?:SKILL|STATE|ENUM_CHARACTERJOB)_[A-Z0-9_]+)\s*(?:<-|=)\s*(-?\d+)",
    re.M,
)
CALL_KIND_RE = re.compile(r'kind\s*==\s*"([^"]+)"')
GLOBAL_HEADERS = {"sqr/dnf_enum_header.nut", "sqr/common.nut"}
OBJ_ACTION_TAGS = {"[basic action]", "[etc action]", "[last action]"}


def nut_text(pvf, decoder, path):
    raw = pvf.read(path)
    try:
        return raw.decode("utf-8-sig"), "utf-8-sig"
    except UnicodeDecodeError:
        return decoder.decode_text(raw, path), "gbk"


def strip_nut_comments(text):
    """把注释替换为等长空格，保留换行和字符串；offset/行号不变。"""
    out = list(text)
    i, n, state, quote = 0, len(text), None, None
    while i < n:
        c = text[i]
        nxt = text[i + 1] if i + 1 < n else ""
        if state == "line":
            if c == "\n":
                state = None
            else:
                out[i] = " "
            i += 1
            continue
        if state == "block":
            if c == "*" and nxt == "/":
                out[i] = out[i + 1] = " "
                i += 2
                state = None
                continue
            if c != "\n":
                out[i] = " "
            i += 1
            continue
        if state == "string":
            if c == "\\":
                i += 2
                continue
            if c == quote:
                state = None
            i += 1
            continue
        if c == "/" and nxt == "/":
            out[i] = out[i + 1] = " "
            i += 2
            state = "line"
            continue
        if c == "/" and nxt == "*":
            out[i] = out[i + 1] = " "
            i += 2
            state = "block"
            continue
        if c in ('"', "'"):
            quote, state = c, "string"
        i += 1
    return "".join(out)


def call_end(text, open_paren):
    depth, quote, i, n = 0, None, open_paren, len(text)
    while i < n:
        c = text[i]
        if quote:
            if c == "\\":
                i += 2
                continue
            if c == quote:
                quote = None
        elif c in ('"', "'"):
            quote = c
        elif c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return None


def split_args(text):
    args, cur, quote, depth = [], [], None, 0
    for c in text:
        if quote:
            cur.append(c)
            if c == quote:
                quote = None
            continue
        if c in ('"', "'"):
            quote = c
            cur.append(c)
            continue
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            args.append("".join(cur).strip())
            cur = []
        else:
            cur.append(c)
    tail = "".join(cur).strip()
    if tail or args:
        args.append(tail)
    return args


def line_of(text, offset):
    return text.count("\n", 0, offset) + 1


def literal_arg(arg, assignments, offset):
    if len(arg) >= 2 and arg[0] in ('"', "'") and arg[-1] == arg[0]:
        return arg[1:-1], "literal"
    if re.fullmatch(r"[A-Za-z_]\w*", arg or ""):
        prior = [a for a in assignments.get(arg, []) if a["offset"] < offset]
        if prior:
            a = prior[-1]
            return a["value"], "local-literal@%d" % a["line"]
    return None, "unresolved-expression"


def make_edge(edges, relation, classification, source, **fields):
    edge = {"id": len(edges), "relation": relation, "classification": classification,
            "source": source}
    edge.update(fields)
    edges.append(edge)
    return edge


def resolve_sqr(graph, value):
    if not value:
        return {"status": "unresolved", "value": value, "diagnostic": "empty-script-path"}
    candidate = "sqr/" + value.replace("\\", "/").lstrip("/")
    hit = norm(candidate)
    if hit in graph.by:
        return {"status": "resolved", "value": value, "target": graph.by[hit],
                "resolution": ["sqr-root"]}
    return {"status": "unresolved", "value": value, "candidate": candidate,
            "diagnostic": "script-not-in-pvf"}


def build(pvf, decoder, args):
    graph = ResourceGraph(pvf, decoder)
    by = graph.by
    edges = []
    diagnostics = []
    all_skl = sorted(p for p in by.values() if p.endswith(".skl"))

    # ---- 1. 技能整数注册表：skill/*.lst 的 (job, skillId) -> SKL ----
    skill_lists, skills = {}, {}
    lst_dir = {}
    for path in sorted(by):
        if not (path.startswith("skill/") and path.endswith(".lst")):
            continue
        try:
            rows = decoder.list_records(by[path])
        except (ValueError, KeyError) as error:
            diagnostics.append({"stage": "skill-lst", "path": by[path], "error": str(error)})
            continue
        dirs = collections.Counter(
            r["value"].split("/")[0].lower() for r in rows if "/" in r["value"]
        )
        job = dirs.most_common(1)[0][0] if dirs else stem(path).replace("skill", "")
        lst_dir[job] = by[path]
        skill_lists[by[path]] = rows
        for row in rows:
            if not row["value"].lower().endswith(".skl"):
                continue
            resolved = graph.resolve(by[path], row["value"], ["skill"])
            rec = {"job": job, "skillId": row["id"], "skl": None,
                   "list": by[path], "listOffset": row.get("token_index"),
                   "listValue": row["value"], "edges": [], "exeStates": [],
                   "nutStates": [], "objects": [], "acts": [], "coverage": []}
            if resolved["status"] == "resolved":
                rec["skl"] = by.get(resolved["target"], resolved["target"])
            key = (job, row["id"])
            skills[key] = rec
            make_edge(edges, "skill-registry", "evidence",
                      {"path": by[path], "tokenIndex": row.get("token_index")},
                      job=job, skillId=row["id"], value=row["value"],
                      target=rec["skl"], status=resolved["status"],
                      detail={k: v for k, v in resolved.items() if k != "value"})
            rec["edges"].append(edges[-1]["id"])

    # ---- 2. NUT 常量表（按定义文件保留作用域，冲突不任选） ----
    const_index = collections.defaultdict(list)
    nut_sources = {}
    for path in sorted(by.values()):
        if not path.endswith(".nut"):
            continue
        text, encoding = nut_text(pvf, decoder, path)
        nut_sources[path] = {"text": text, "encoding": encoding,
                             "clean": strip_nut_comments(text)}
        for m in CONST_RE.finditer(text):
            const_index[m.group(1)].append(
                {"value": int(m.group(2)), "source": path, "line": line_of(text, m.start())}
            )

    def resolve_const(name, scope_headers):
        entries = const_index.get(name, [])
        scoped = [e for e in entries if any(e["source"].startswith(h) for h in scope_headers)]
        pool, scope = (scoped, "job-header") if scoped else (
            [e for e in entries if e["source"] in GLOBAL_HEADERS], "global-header")
        if not pool:
            pool, scope = entries, "unscoped"
        values = {e["value"] for e in pool}
        if len(values) == 1:
            return {"status": "resolved", "value": next(iter(values)), "scope": scope,
                    "definitions": pool}
        return {"status": "ambiguous" if values else "unresolved", "value": None,
                "scope": scope, "definitions": pool,
                "diagnostic": "conflicting-or-missing-constant"}

    # ---- 3. exe setState 绑定（既有反汇编产物，不是 PVF 字面证据） ----
    bindings, binding_sources = load_bindings()
    by_skl = collections.defaultdict(list)
    for binding in bindings:
        value = binding["skl"] or ""
        path = norm(value if norm(value).startswith("skill/") else "skill/" + value)
        by_skl[path].append(binding)
    for (job, skill_id), rec in skills.items():
        if not rec["skl"]:
            continue
        for binding in by_skl.get(norm(rec["skl"]), []):
            states = [{"state": s.get("state"), "handler": s.get("handler")}
                      for s in binding.get("states", [])]
            rec["exeStates"].append({"source": binding["source"],
                                    "class": binding["class"], "states": states})
            e = make_edge(edges, "exe-state-binding", "exe-derived",
                          {"path": binding["source"]},
                          job=job, skillId=skill_id, target=rec["skl"], status="resolved",
                          bindingClass=binding["class"], states=states)
            rec["edges"].append(e["id"])

    # ---- 4. NUT 状态/对象注册表 ----
    load_states = sorted(p for p in by.values() if p.endswith("_load_state.nut"))
    register_scopes = {}
    for path in load_states:
        raw_text = nut_sources[path]["text"]
        clean = nut_sources[path]["clean"]
        # PVF 路径统一小写；NUT 字面量可能是 "Character/Priest/..."，不规范化会
        # 让职业作用域和常量定义文件永远匹配不上。
        headers = [
            norm("sqr/" + v.replace("\\", "/").lstrip("/").rsplit("/", 1)[0]).rstrip("/") + "/"
            for v in SCRIPT_FILE_RE.findall(clean) if "header" in v.lower()
        ]
        scope_job = None
        for h in headers:
            candidate = posixpath.basename(h.rstrip("/"))
            if candidate in lst_dir:
                scope_job = candidate
                break
        if scope_job is None:
            for candidate in ("atmage", "creatormage", "priest"):
                if candidate in path and candidate in lst_dir:
                    scope_job = candidate
                    break
        scope_headers = tuple(sorted(set(headers))) or (
            "sqr/character/%s/" % scope_job if scope_job else ()
        )
        register_scopes[path] = {"job": scope_job, "headers": scope_headers}
        assignments = collections.defaultdict(list)
        for m in ASSIGN_RE.finditer(clean):
            # m.start() 可能落在前导换行上；用变量名位置计算行号与先后。
            at = m.start(1)
            assignments[m.group(1)].append(
                {"value": m.group(2), "offset": at, "line": line_of(clean, at)}
            )
        for m in REGISTER_CALL_RE.finditer(clean):
            end = call_end(clean, m.end() - 1)
            if end is None:
                diagnostics.append({"stage": "register-call", "path": path,
                                    "line": line_of(clean, m.start()),
                                    "error": "unclosed-call"})
                continue
            params = split_args(clean[m.end():end])
            line = line_of(clean, m.start())
            kind = m.group(1).lower()
            src = {"path": path, "line": line, "offset": m.start()}
            if kind == "pushstate":
                if len(params) >= 5:
                    job_const, nut_arg, name_arg, state_const, skill_const = params[:5]
                elif len(params) >= 4:
                    job_const, nut_arg, name_arg, state_const, skill_const = (
                        None, params[0], params[1], params[2], params[3])
                else:
                    diagnostics.append({"stage": "pushState", **src,
                                        "error": "operand-count", "operands": params})
                    continue
                nut_value, nut_origin = literal_arg(nut_arg, assignments, m.start())
                script = resolve_sqr(graph, nut_value)
                skill_id, skill_status = None, "runtime-action"
                if re.fullmatch(r"SKILL_[A-Z0-9_]+", skill_const or ""):
                    c = resolve_const(skill_const, scope_headers)
                    skill_id = c["value"]
                    skill_status = c["status"]
                    if c["status"] != "resolved":
                        diagnostics.append({"stage": "pushState-skill-const", **src,
                                            "constant": skill_const, "detail": c})
                elif (skill_const or "").strip() == "-1":
                    pass
                else:
                    diagnostics.append({"stage": "pushState-skill-const", **src,
                                        "error": "non-standard-skill-operand",
                                        "operand": skill_const})
                state_c = (resolve_const(state_const, scope_headers)
                           if re.fullmatch(r"STATE_[A-Z0-9_]+", state_const or "")
                           else {"status": "unresolved", "value": None})
                target_skl = None
                key = (scope_job, skill_id)
                if skill_id is not None and key in skills:
                    target_skl = skills[key]["skl"]
                if skill_const and skill_const.strip() == "-1":
                    edge_status = "runtime-action"   # 通用动作无技能身份，不是解析缺口
                elif script["status"] == "resolved" and target_skl:
                    edge_status = "resolved"
                else:
                    edge_status = "partial"
                e = make_edge(edges, "nut-push-state", "evidence", src,
                              job=scope_job, jobConst=job_const, skillConst=skill_const,
                              skillId=skill_id, skillStatus=skill_status,
                              stateConst=state_const, stateValue=state_c.get("value"),
                              stateStatus=state_c.get("status"),
                              nut=script.get("target"), nutValue=nut_value,
                              nutOrigin=nut_origin, nutStatus=script["status"],
                              name=name_arg.strip('"'), target=target_skl,
                              headerScope=list(scope_headers),
                              status=edge_status,
                              diagnostic=(None if edge_status == "resolved" else
                                          "generic-action-without-skill-identity"
                                          if edge_status == "runtime-action" else
                                          "skill-or-script-not-resolved"))
                if target_skl:
                    skills[key]["nutStates"].append(e["id"])
                    skills[key]["edges"].append(e["id"])
            elif kind == "pushpassiveobj":
                if len(params) < 2:
                    diagnostics.append({"stage": "pushPassiveObj", **src,
                                        "error": "operand-count", "operands": params})
                    continue
                nut_value, nut_origin = literal_arg(params[0], assignments, m.start())
                script = resolve_sqr(graph, nut_value)
                try:
                    object_id = int(params[1].strip())
                except ValueError:
                    diagnostics.append({"stage": "pushPassiveObj", **src,
                                        "error": "non-integer-object-id",
                                        "operand": params[1]})
                    continue
                reg = graph.passive_registry.get(object_id)
                obj_target = reg["target"] if reg else None
                status = "resolved" if obj_target in by and script["status"] == "resolved" else "partial"
                e = make_edge(edges, "nut-push-passive-object", "evidence", src,
                              job=scope_job, objectId=object_id,
                              nut=script.get("target"), nutValue=nut_value,
                              nutOrigin=nut_origin, nutStatus=script["status"],
                              target=by.get(obj_target, obj_target),
                              registryValue=reg["value"] if reg else None,
                              registry="passiveobject/passiveobject.lst",
                              duplicate=object_id in graph.passive_registry_duplicates,
                              status=status)
            elif kind == "pushscriptfiles":
                value, origin = literal_arg(params[0], assignments, m.start())
                script = resolve_sqr(graph, value)
                make_edge(edges, "nut-push-script-file", "evidence", src,
                          job=scope_job, nut=script.get("target"), value=value,
                          origin=origin, status=script["status"])

    # ---- 5. 技能脚本内明确的对象创建 API（整数 ID -> 注册表） ----
    for path in sorted(nut_sources):
        clean = nut_sources[path]["clean"]
        for m in NUT_CREATE_RE.finditer(clean):
            end = call_end(clean, m.end() - 1)
            if end is None:
                continue
            params = split_args(clean[m.end():end])
            integers = [(p.strip(), int(p.strip())) for p in params
                        if re.fullmatch(r"\d+", p.strip())]
            candidates = [(raw, value) for raw, value in integers if value >= 10000]
            src = {"path": path, "line": line_of(clean, m.start()), "offset": m.start()}
            if not candidates:
                # 变量/表达式作为对象索引：这是有证据的未恢复动态边，不是解析错误。
                dynamic = next((p.strip() for p in params
                                if p.strip() and not re.fullmatch(r"-?\d+", p.strip())
                                and p.strip() not in ("obj", "null", "true", "false")), None)
                make_edge(edges, "nut-create-object-api", "evidence", src, api=m.group(1),
                          status="unresolved", diagnostic="dynamic-object-id-operand",
                          dynamicOperand=dynamic, operands=params[:8],
                          note="NUT variable/expression object index; no static evaluation performed")
                continue
            raw, object_id = candidates[0]
            reg = graph.passive_registry.get(object_id)
            e = make_edge(edges, "nut-create-object-api", "evidence", src, api=m.group(1),
                          objectId=object_id, target=by.get(reg["target"]) if reg else None,
                          registryValue=reg["value"] if reg else None,
                          registry="passiveobject/passiveobject.lst",
                          status="resolved" if reg and reg["target"] in by else "unresolved",
                          diagnostic=(None if reg and reg["target"] in by
                                      else "object-id-not-in-registry"))
            # 通过注册表 ID 与技能脚本路径关联：同一脚本若被 pushState 绑定，
            # 该创建调用即为该技能的证据边。
            for pe in edges:
                if pe["relation"] != "nut-push-state" or pe.get("nut") != path:
                    continue
                key = (pe.get("job"), pe.get("skillId"))
                if key in skills:
                    skills[key]["edges"].append(e["id"])
                    skills[key]["objects"].append({"objectId": object_id,
                                                   "edge": e["id"], "via": pe["id"]})

    # ---- 6. OBJ 资源链：动作/攻击信息/ANI/PTL 字面引用，并沿 OBJ/ACT 递归 ----
    def chain(start_obj):
        seen, acts, objs, action_refs, resource_refs = set(), set(), set(), [], []
        queue = collections.deque([start_obj])
        while queue:
            path = norm(queue.popleft())
            if path in seen or path not in by:
                continue
            seen.add(path)
            if path.endswith(".act"):
                acts.add(by[path])
            elif path.endswith(".obj"):
                objs.add(by[path])
            try:
                node = graph.node(by[path])
            except (ValueError, KeyError, UnicodeError) as error:
                diagnostics.append({"stage": "resource-node", "path": by[path],
                                    "error": str(error)})
                continue
            for edge in node["edges"]:
                if edge["relation"] != "literal-reference":
                    continue
                tag = edge.get("evidence", {}).get("tag")
                ref = {"path": by[path], "tag": tag, "value": edge["value"],
                       "status": edge["status"], "target": edge.get("target")}
                resource_refs.append(ref)
                if tag in OBJ_ACTION_TAGS:
                    action_refs.append(ref)
                if edge["status"] != "resolved" or not edge.get("target"):
                    continue
                target = norm(edge["target"])
                if target in by and (target.endswith(".act") or target.endswith(".obj")):
                    queue.append(by[target])
        return sorted(acts), sorted(objs), action_refs, resource_refs

    # 全包 OBJ 的 action 引用分布：证明 ACT 集中在怪物/地图对象，而非玩家技能对象。
    obj_action_roots = collections.Counter()
    obj_action_tags = collections.Counter()
    for path in sorted(by.values()):
        if not path.endswith(".obj"):
            continue
        try:
            node = graph.node(path)
        except (ValueError, KeyError, UnicodeError):
            continue
        for edge in node["edges"]:
            if (edge["relation"] == "literal-reference"
                    and edge.get("evidence", {}).get("tag") in OBJ_ACTION_TAGS
                    and str(edge["value"]).lower().endswith(".act")):
                obj_action_tags[edge["evidence"]["tag"]] += 1
                obj_action_roots["/".join(path.split("/")[:3])] += 1

    # ---- 7. 既有真实 World 静态准入结果 ----
    coverage, coverage_meta = {}, {"available": False}
    if os.path.isfile(args.act_coverage):
        with open(args.act_coverage, encoding="utf8") as stream:
            report = json.load(stream)
        for row in report.get("files", []):
            coverage[norm(row["path"])] = row
        coverage_meta = {"available": True, "path": os.path.abspath(args.act_coverage),
                         "sha256": file_hash(args.act_coverage),
                         "prefix": report.get("prefix"), "fileCount": report.get("file_count"),
                         "admittedCount": report.get("admitted_count"),
                         "exceptionCount": report.get("exception_count"),
                         "blockingCodes": report.get("blocking_diagnostic_codes")}
    act_audit_meta = {"available": False}
    tag_families = {}
    if os.path.isfile(args.act_audit):
        with open(args.act_audit, encoding="utf8") as stream:
            audit = json.load(stream)
        tag_families = {t: v.get("family") for t, v in audit.get("classifiedTags", {}).items()}
        act_audit_meta = {"available": True, "path": os.path.abspath(args.act_audit),
                          "sha256": file_hash(args.act_audit),
                          "summary": audit.get("summary"),
                          "families": audit.get("families"),
                          "plannedCommandFamilies": audit.get("plannedCommandFamilies")}

    # ---- 8. 技能级账本：把对象链、ACT 与准入结果挂到技能身份 ----
    object_edges = [e for e in edges if e["relation"] in
                    ("nut-create-object-api", "nut-push-passive-object")
                    and e.get("target")]
    for (job, skill_id), rec in skills.items():
        owned = {o["objectId"]: o for o in rec["objects"]}
        related = set()
        for e in object_edges:
            if e.get("objectId") in owned:
                related.add(norm(e["target"]))
        acts, objs, act_refs, resource_refs = set(), set(), [], []
        for obj in sorted(related):
            a, o, refs, res = chain(obj)
            acts.update(a)
            objs.update(o)
            act_refs.extend(refs)
            resource_refs.extend(res)
        rec["objectPaths"] = sorted(related)
        rec["objChainPaths"] = sorted(objs)
        rec["acts"] = sorted(acts)
        rec["objActionRefs"] = act_refs
        rec["objResourceRefs"] = resource_refs
        rec["objResourceKinds"] = dict(sorted(collections.Counter(
            ext(str(r["value"])) for r in resource_refs).items()))
        for act in sorted(acts):
            row = coverage.get(norm(act))
            if not row:
                rec["coverage"].append({"path": act, "status": "no-admission-report"})
                continue
            c = row.get("coverage", {})
            rec["coverage"].append({
                "path": act, "status": "reported", "ok": c.get("ok"),
                "syntaxComplete": c.get("syntax_complete"),
                "sourceReady": c.get("source_ready"),
                "runtimeReady": c.get("runtime_ready"),
                "blockingCodes": sorted({d.get("code") for d in c.get("diagnostics", [])
                                         if d.get("blocking")}),
            })
        rec["entryStatus"] = ("script-entry" if rec["nutStates"] else
                              "exe-entry-only" if rec["exeStates"] else "no-resolved-entry")
        rec.pop("edges_list", None)

    # ---- 9. 消费者账本（真实 World 消费者白名单 + 计划族 + 阻塞证据） ----
    known_consumers, host_meta = [], {"available": False}
    if os.path.isfile(args.host_source):
        with open(args.host_source, encoding="utf8", errors="replace") as stream:
            src = stream.read()
        block = re.search(r"bool\s+ActWorldHost::hasCommandConsumer.*?\{(.*?)\n\}", src, re.S)
        known_consumers = sorted(set(CALL_KIND_RE.findall(block.group(1)))) if block else []
        host_meta = {"available": True, "path": os.path.abspath(args.host_source),
                     "sha256": file_hash(args.host_source),
                     "extractor": "ActWorldHost::hasCommandConsumer kind== literals"}
    missing_consumer_messages = collections.Counter()
    for row in coverage.values():
        for d in row.get("coverage", {}).get("diagnostics", []):
            if d.get("code") == "missing_command_consumer":
                missing_consumer_messages[d.get("message", "")] += 1

    # ---- 10. V3 边界解释：SKL 字面引用到底有哪些类型 ----
    skl_literal_exts = collections.Counter()
    skl_tags_with_paths = collections.Counter()
    for path in sorted(by.values()):
        if not path.endswith(".skl"):
            continue
        tag = None
        for token in decoder.tokens(pvf.read(path)):
            if token["type"] == 5:
                tag = token["value"]
                continue
            value = token.get("value")
            if isinstance(value, str) and PATH_RE.fullmatch(value):
                skl_literal_exts[ext(value)] += 1
                skl_tags_with_paths[str(tag)] += 1
    v3_meta = {"available": False}
    if os.path.isfile(args.closure):
        with open(args.closure, encoding="utf8") as stream:
            v3 = json.load(stream)
        v3_meta = {"available": True, "path": os.path.abspath(args.closure),
                   "sha256": file_hash(args.closure), "summary": v3.get("summary")}

    relations = collections.Counter(e["relation"] for e in edges)
    statuses = collections.Counter(e.get("status") for e in edges)
    registered_skl = {norm(r["skl"]) for r in skills.values() if r["skl"]}
    summary = {
        "skills": len(skills), "sklFiles": len(all_skl),
        "unregisteredSkl": len([p for p in all_skl if norm(p) not in registered_skl]),
        "skillLists": len(skill_lists),
        "skillRegistryRows": sum(1 for e in edges if e["relation"] == "skill-registry"),
        "loadStateFiles": len(load_states),
        "nutConstants": len(const_index),
        "conflictingConstants": sum(1 for v in const_index.values()
                                    if len({x["value"] for x in v}) > 1),
        "exeBindings": len(bindings),
        "entryEdges": len(edges), "edgeRelations": dict(sorted(relations.items())),
        "edgeStatuses": dict(sorted(statuses.items())),
        "skillsWithExeStates": sum(bool(r["exeStates"]) for r in skills.values()),
        "skillsWithNutStates": sum(bool(r["nutStates"]) for r in skills.values()),
        "skillsWithObjects": sum(bool(r["objects"]) for r in skills.values()),
        "skillsWithActs": sum(bool(r["acts"]) for r in skills.values()),
        "skillsWithAdmittedActs": sum(any(c.get("ok") for c in r["coverage"])
                                      for r in skills.values()),
        "actPathsReached": len({a for r in skills.values() for a in r["acts"]}),
        "objActionRefs": sum(len(r["objActionRefs"]) for r in skills.values()),
        "objResourceRefs": sum(len(r["objResourceRefs"]) for r in skills.values()),
        "skillsWithObjResources": sum(bool(r["objResourceRefs"]) for r in skills.values()),
        "allObjActionRefs": sum(obj_action_tags.values()),
        "allObjActionTags": dict(sorted(obj_action_tags.items())),
        "allObjActionRoots": dict(obj_action_roots.most_common()),
        "diagnostics": len(diagnostics),
        "knownWorldConsumers": len(known_consumers),
    }

    report = {
        "schemaVersion": 1,
        "purpose": "Static skill-entry and consumer ledger; not runtime consumption or original-client equivalence.",
        "pvf": {"path": os.path.abspath(args.pvf), "sha256": file_hash(args.pvf),
                "entryCount": len(pvf.entries)},
        "inputs": {"scriptSha256": file_hash(__file__), "bindings": binding_sources,
                   "actCoverage": coverage_meta, "actAudit": act_audit_meta,
                   "hostSource": host_meta, "v3Closure": v3_meta},
        "method": {
            "entryEdges": "skill lst integers, exe setState bindings, NUT pushState/pushPassiveObj/pushScriptFiles, explicit NUT object-creation APIs, OBJ action literals.",
            "constantScope": "SKILL_/STATE_ constants resolve inside the load_state's job header scope first, then global headers; conflicting definitions are never chosen arbitrarily.",
            "stateJoin": "STATE_ numbers are job-local; they are recorded but never joined across jobs.",
            "nutEvaluation": "Only literal string operands and simple prior local string assignments are resolved; no NUT execution, concatenation, conditionals or dynamic formatting.",
            "objectIds": "Integers become object IDs only inside explicit create APIs or CREATE PASSIVEOBJECT blocks, then through passiveobject/passiveobject.lst.",
            "chain": "From a skill's object IDs, OBJ literal-reference edges (motion/attack info/action/particle) are recorded; OBJ/ACT targets are traversed recursively. ANI/PTL/ATK are leaves. A zero ACT count is a measured structure, not a parse failure: allObjActionRoots shows where ACT actually lives.",
            "scope": "Skill identity comes from skill/*.lst registrations, not all .skl files; unregisteredSkl counts the difference. This is a registry-scoped ledger, not an all-SKL ledger.",
            "coverage": "Per-ACT syntax/source/runtime flags come from the existing ActWorldHost static admission report; ok requires all three. No simulation advance.",
            "limits": ["Does not prove which state actually fires in game.", "exe binding is an entry candidate, not a play order.",
                       "NUT dynamic names, exe VM dispatch and ANI frame events remain unrecovered.",
                       "Static admission is not World execution and not 1031 visual equivalence."],
        },
        "explanation": {
            "v3ActEdgeZero": {
                "observation": "V3 skill graph has act-passiveobject-index edges = 0 while a full ACT scan resolves 13150 such edges.",
                "cause": "Two independent reasons. (1) V3 seeds are .skl files and expand only literal path references; SKL carries almost no executable resource paths, so the real entry chain (skill lst id, NUT SKILL_/STATE_ constants, passiveobject.lst id, exe setState dispatch) never enters the closure. (2) Within the skill chains that this ledger can close (NUT-scripted jobs), the passive objects created by explicit skill scripts do not use [basic action]/[etc action]/[last action]: they carry [basic motion]/[etc motion]/[attack info] ANI and ATK references instead. Package-wide ACT references are concentrated in monster/map/action objects. This is a scoped observation, not a proof that every PC skill in 1031 avoids ACT: the exe-dispatched jobs have no recovered object chain, and passiveobject/character/common still holds one ACT reference.",
                "evidence": {
                    "sklLiteralExtensions": dict(sorted(skl_literal_exts.items())),
                    "sklTagsWithPaths": dict(skl_tags_with_paths.most_common(20)),
                    "allObjActionRefs": sum(obj_action_tags.values()),
                    "allObjActionRoots": dict(obj_action_roots.most_common(12)),
                    "playerSkillObjActionRefs": sum(len(r["objActionRefs"])
                                                     for r in skills.values()),
                    "playerSkillObjResourceKinds": dict(sorted(collections.Counter(
                        kind for r in skills.values()
                        for kind in r["objResourceKinds"]).items())),
                },
                "conclusion": "For the NUT-scripted skills whose object chains are recovered here, ACT is not the entry; their objects are driven by [basic motion]/[etc motion]/[attack info] plus NUT host APIs. Package-wide ACT tag frequency therefore cannot be used to infer that a given PC skill must call ACT. P0-2 ACT consumers remain necessary for generic monster/map objects, but this ledger does not establish them as the fix for sword-array/awakening/ice-bow entries. The exe-dispatched jobs remain an unrecovered edge.",
                "bridges": {k: v for k, v in relations.items()
                            if k not in ("skill-registry", "exe-state-binding")},
                "unrecovered": [
                    {"code": "exe-native-dispatch",
                     "count": summary["skillsWithExeStates"] - summary["skillsWithNutStates"],
                     "evidence": "Only 3 *_load_state.nut registries exist (atmage/creatormage/priest-avenger); the other job binding files give setState entries but no script->object dispatch. ATK selector 0x70213F is in the unrestored exe VM region.",
                     "blocker": "No exe VM recovery; do not fabricate skill->OBJ/ACT edges for these jobs."},
                    {"code": "dynamic-object-id",
                     "count": sum(1 for e in edges if e.get("diagnostic") == "dynamic-object-id-operand"),
                     "evidence": "NUT create APIs pass a variable/expression (e.g. passiveObjectIndex) instead of an integer literal; source, line, api and operands are retained per edge.",
                     "blocker": "Requires bounded NUT evaluation or a runtime host API contract."},
                    {"code": "unregistered-skl",
                     "count": summary["unregisteredSkl"],
                     "evidence": "SKL files not referenced by any skill/*.lst registration (pet/event/legacy jobs); ledger identity is registry-scoped by design.",
                     "blocker": "Would need the native caller/index table, not a filename guess."},
                    {"code": "runtime-conditions",
                     "count": None,
                     "evidence": "pushState/SKL/exe bindings record entry identity and state numbers, not the condition or timing under which a state fires.",
                     "blocker": "No execution trace and no original-client frame comparison in this ledger."},
                ],
            }
        },
        "summary": summary,
        "registries": {
            "skillLists": {p: {"job": next((j for j, v in lst_dir.items() if v == p), None),
                               "rows": len(r)} for p, r in skill_lists.items()},
            "passiveObject": {"path": graph.passive_registry_path,
                              "uniqueIds": len(graph.passive_registry),
                              "duplicates": len(graph.passive_registry_duplicates),
                              "error": graph.passive_registry_error},
            "loadStateScopes": {p: {"job": v["job"], "headers": list(v["headers"])}
                                for p, v in register_scopes.items()},
            "conflictingConstants": {k: v for k, v in const_index.items()
                                     if len({x["value"] for x in v}) > 1},
        },
        "consumerLedger": {
            "knownWorldConsumers": known_consumers,
            "hostSource": host_meta,
            "tagFamilies": tag_families,
            "actAudit": act_audit_meta,
            "missingConsumerDiagnostics": [
                {"message": m, "count": n} for m, n in missing_consumer_messages.most_common()
            ],
            "gaps": [
                {"code": "spawn-passive-object-consumer",
                 "evidence": "act_world_host.cpp resource resolve keeps ACT/PTL/object factory unregistered; missing_resource_consumer appears in the admission report.",
                 "blocker": "No World factory for CREATE PASSIVEOBJECT / particle commands."},
                {"code": "exe-native-dispatch",
                 "evidence": "Only 3 *_load_state.nut registries exist; 10 job binding files provide setState entries but no object creation dispatch.",
                 "blocker": "exe VM region containing the ATK selector 0x70213F is unrestored."},
                {"code": "nut-dynamic-path",
                 "evidence": "pushPassiveObj uses local string variables; creation APIs use computed coordinates and conditional branches.",
                 "blocker": "No bounded NUT evaluation or runtime host API contract."},
                {"code": "skl-field-consumers",
                 "evidence": "SKL tags command / command customizing / executable states / active status have no per-skill consumer ledger yet.",
                 "blocker": "P2 field-by-field wiring not started."},
            ],
        },
        "entryEdges": edges,
        "skills": [
            {"job": k[0], "skillId": k[1], **v}
            for k, v in sorted(skills.items(), key=lambda item: (item[0][0], item[0][1]))
        ],
        "diagnostics": diagnostics,
        "decoderWarnings": decoder.warnings,
    }
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvf", default=DEFAULT_PVF)
    parser.add_argument("--out", required=True)
    parser.add_argument("--act-coverage", default=os.path.join(AUDIT_DIR, "act-prefix-coverage.json"))
    parser.add_argument("--act-audit", default=os.path.join(AUDIT_DIR, "act-audit.json"))
    parser.add_argument("--closure", default=os.path.join(AUDIT_DIR, "skill-closure-v3.json"))
    parser.add_argument("--host-source", default=os.path.join(
        WORKSPACE, "project", "src", "simulation", "scripting", "act_world_host.cpp"))
    args = parser.parse_args()
    pvf = Pvf(args.pvf)
    try:
        report = build(pvf, ScriptDecoder(pvf), args)
    finally:
        pvf.close()
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf8", newline="\n") as stream:
        json.dump(report, stream, ensure_ascii=False, indent=2, allow_nan=False)
        stream.write("\n")
    print(json.dumps(report["summary"], ensure_ascii=False))


if __name__ == "__main__":
    main()
