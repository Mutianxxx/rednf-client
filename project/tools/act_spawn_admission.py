#!/usr/bin/env python3
"""清风 1031 ACT 被动对象工厂的静态准入基线（P0-2 证据工具）。

回答一个具体问题：给 ACT 的 CREATE PASSIVEOBJECT 接上 World 工厂之后，
哪些文件能诚实准入，哪些必须继续显式阻塞，阻塞原因分别是什么。

本工具只做静态证据账本：
- 不执行 ACT、不创建实体、不模拟 World、不证明 1031 原版表现等价；
- 对象 ID 只来自 ACT 依赖表里的显式 passive_object 索引，并经
  passiveobject/passiveobject.lst 解析到 .obj；
- OBJ 依赖按字面路径分类；PTL 解释器、通用 OBJ→ACT 递归未注册的对象
  保持 blocked，不靠文件名猜测或忽略未知依赖来制造覆盖率。

P0-2 修订：1031 PVF 的 CREATE PASSIVEOBJECT [WARNING MARK] 实测有 2 或 4
个整数操作数（303 个 ACT、1580 处），旧编译器按 0 操作数误判为语法错误。
工具把 C++ 侧真实准入旗标并列记录，但不把 `ok`/`runtime_ready` 当成
World 已执行；`warning_mark_consumer_unregistered` 是非阻塞诊断，代表
预警贴花消费者仍未注册，不能计为已实现。
"""
from __future__ import annotations

import argparse
import collections
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(os.path.dirname(HERE), "..", "..", "dnf-result", "tools"))

from pvf_reader import Pvf, ScriptDecoder  # type: ignore
from skill_closure import ext, norm  # type: ignore

WORKSPACE = os.path.dirname(os.path.dirname(HERE))
AUDIT_DIR = os.path.join(WORKSPACE, "checkpoints", "tests", "pvf-audit")
DEFAULT_PVF = "D:/dnf-rebuild/DNF1031客户端/Script.pvf"
SUPPORTED_EXTS = {".ani", ".atk", ".img"}
OPCODE_BLOCKERS = {"operand_count", "unclosed_spawn", "missing_spawn_field",
                   "spawn_field_order", "conflicting_coordinate_flags",
                   "unsupported_spawn_opcode", "repeated_spawn_field"}
STAGES = ("ok", "syntax_complete", "source_ready", "runtime_ready")
NON_BLOCKING_GAPS = {"warning_mark_consumer_unregistered"}
BUCKETS = ("admissible", "blocked-ptl", "blocked-act-object-recursion",
           "blocked-unknown-dependency", "blocked-act-opcode",
           "blocked-act-particle", "blocked-registry", "blocked-object-parse")


def classify(obj_exts, obj_tags, act_opcode_blocked, act_has_ptl, registry_error):
    """纯函数：返回 (bucket, reasons)，按最具体的阻塞原因排序。"""
    reasons = []
    if registry_error:
        reasons.append("registry:" + registry_error)
    tags = {str(t).lower() for t in obj_tags}
    if any("action" in t for t in tags) or ".act" in obj_exts:
        reasons.append("act-object-recursion-missing")
    unsupported = sorted(e for e in obj_exts if e not in SUPPORTED_EXTS | {".act", ".ptl"})
    if unsupported:
        reasons.append("unsupported-dependency:" + ",".join(unsupported))
    if ".ptl" in obj_exts:
        reasons.append("ptl-interpreter-missing")
    if act_has_ptl:
        reasons.append("act-particle-dependency")
    if act_opcode_blocked:
        reasons.append("act-opcode-blocked")
    if not obj_exts and not registry_error:
        reasons.append("no-executable-obj-leaf")
    if not reasons:
        return "admissible", []
    if registry_error:
        return "blocked-registry", reasons
    if "ptl-interpreter-missing" in reasons or "act-particle-dependency" in reasons:
        return "blocked-ptl", reasons
    if "act-object-recursion-missing" in reasons:
        return "blocked-act-object-recursion", reasons
    if any(r.startswith("unsupported-dependency") or r == "no-executable-obj-leaf" for r in reasons):
        return "blocked-unknown-dependency", reasons
    if "act-opcode-blocked" in reasons:
        return "blocked-act-opcode", reasons
    return "blocked-unknown-dependency", reasons


def stage(coverage):
    """纯函数：抽取 C++ 静态准入旗标与非阻塞缺口诊断码。"""
    if not isinstance(coverage, dict):
        return {k: None for k in STAGES} | {"nonBlockingGaps": []}
    diags = coverage.get("diagnostics") or []
    gaps = sorted({str(d.get("code")) for d in diags if isinstance(d, dict)
                   and not d.get("blocking", True) and d.get("code") in NON_BLOCKING_GAPS})
    return {k: coverage.get(k) for k in STAGES} | {"nonBlockingGaps": gaps}


def merge_reports(reports):
    """纯函数：按路径合并多份批量准入报告，后传入的覆盖先传入的。"""
    merged = {}
    for report in reports:
        for file in report.get("files", []):
            if not isinstance(file, dict) or "path" not in file:
                continue
            merged[file["path"]] = file
    return [merged[p] for p in sorted(merged)]


def self_test():
    assert classify({".ani", ".atk"}, ["[basic motion]"], False, False, None)[0] == "admissible"
    assert classify({".ani", ".ptl"}, ["[string data]"], False, False, None)[0] == "blocked-ptl"
    assert classify({".act"}, ["[basic action]"], False, False, None)[0] == "blocked-act-object-recursion"
    assert classify({".ani"}, [], False, True, None)[0] == "blocked-ptl"
    assert classify({".ani"}, [], True, False, None)[0] == "blocked-act-opcode"
    assert classify(set(), [], False, False, "unregistered-id")[0] == "blocked-registry"
    assert classify({".obj"}, ["[name]"], False, False, None)[0] == "blocked-unknown-dependency"
    assert set(BUCKETS) >= {x[0] for x in [
        classify({".ani"}, [], False, False, None),
        classify({".ptl"}, [], False, False, None),
        classify({".act"}, [], False, False, None),
        classify({".obj"}, [], False, False, None),
        classify({".ani"}, [], True, False, None),
        classify({".ani"}, [], False, True, None),
        classify(set(), [], False, False, "missing"),
    ]}
    assert stage({"ok": True, "syntax_complete": True, "source_ready": True,
                  "runtime_ready": True, "diagnostics": [
                      {"code": "warning_mark_consumer_unregistered", "blocking": False},
                      {"code": "missing_resource_consumer", "blocking": True}]}) == {
        "ok": True, "syntax_complete": True, "source_ready": True, "runtime_ready": True,
        "nonBlockingGaps": ["warning_mark_consumer_unregistered"]}
    assert stage(None)["ok"] is None
    a = [{"path": "b.act", "coverage": {"ok": False}}, {"path": "a.act", "coverage": {"ok": True}}]
    b = [{"path": "a.act", "coverage": {"ok": False, "syntax_complete": True}}]
    merged = merge_reports([{"files": a}, {"files": b}])
    assert [f["path"] for f in merged] == ["a.act", "b.act"]
    assert merged[0]["coverage"]["ok"] is False and merged[0]["coverage"]["syntax_complete"] is True
    print("PASS: ACT spawn admission classification, stage extraction, report merge")


def object_ids(coverage):
    deps = coverage.get("dependencies") or []
    ids = {int(d["index"]) for d in deps
           if isinstance(d, dict) and d.get("kind") == "passive_object"
           and isinstance(d.get("index"), int)}
    return sorted(ids)


def act_blocked(coverage):
    diags = coverage.get("diagnostics") or []
    codes = [d.get("code", "") for d in diags if isinstance(d, dict)]
    messages = " ".join(str(d.get("message", "")) for d in diags if isinstance(d, dict))
    opcode = any(c.startswith("unsupported_") or c in OPCODE_BLOCKERS for c in codes)
    return opcode, "particle:" in messages


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvf", default=DEFAULT_PVF)
    parser.add_argument("--coverage", action="append", default=None,
                        help="批量准入报告，可多次传入；同路径以后传入的为准")
    parser.add_argument("--before", action="append", default=None,
                        help="修正前的批量准入报告，可多次传入，用于计算准入增量")
    parser.add_argument("--out")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        return
    if not args.out:
        parser.error("--out is required unless --self-test is used")
    coverage_paths = args.coverage or [os.path.join(AUDIT_DIR, "act-prefix-coverage.json")]
    reports = []
    for path in coverage_paths:
        with open(path, encoding="utf8") as stream:
            reports.append(json.load(stream))
    files = merge_reports(reports)
    before_stages = {}
    if args.before:
        before_reports = []
        for path in args.before:
            with open(path, encoding="utf8") as stream:
                before_reports.append(json.load(stream))
        for file in merge_reports(before_reports):
            before_stages[file["path"]] = stage(file.get("coverage"))

    pvf = Pvf(args.pvf)
    decoder = ScriptDecoder(pvf)
    try:
        by = {norm(e["path"]): e["path"] for e in pvf.entries}
        registry, duplicates = {}, set()
        for row in decoder.list_records("passiveobject/passiveobject.lst"):
            if row["id"] in registry:
                duplicates.add(row["id"])
                continue
            registry[row["id"]] = row["value"]

        cache = {}
        records = []
        for file in files:
            cov = file.get("coverage") or {}
            ids = object_ids(cov)
            if not ids:
                continue
            opcode, act_ptl = act_blocked(cov)
            exts, tags, obj_paths, registry_errors = set(), set(), [], []
            for oid in ids:
                if oid not in cache:
                    value = registry.get(oid)
                    path = None
                    if value:
                        raw = str(value).replace("\\", "/")
                        for candidate in (norm("passiveobject/" + raw), norm(raw)):
                            if candidate in by:
                                path = by[candidate]
                                break
                    if oid in duplicates:
                        error, found_exts, found_tags = "duplicate-id", set(), set()
                    elif not path:
                        error, found_exts, found_tags = "unregistered-or-missing-obj", set(), set()
                    else:
                        error = None
                        found_exts, found_tags = set(), set()
                        try:
                            for token in decoder.tokens(pvf.read(path)):
                                if token.get("type") == 5:
                                    found_tags.add(str(token.get("value") or "").strip())
                                value = token.get("value")
                                if isinstance(value, str) and "." in value:
                                    found_exts.add(ext(value))
                        except (ValueError, KeyError, UnicodeError, IndexError):
                            error = "object-parse-error"
                    cache[oid] = (path, found_exts, found_tags, error)
                path, found_exts, found_tags, error = cache[oid]
                if path:
                    obj_paths.append(path)
                if error:
                    registry_errors.append(error)
                exts |= found_exts
                tags |= found_tags
            bucket, reasons = classify(exts, tags, opcode, act_ptl,
                                       ",".join(sorted(set(registry_errors))) or None)
            records.append({"path": file["path"], "objectIds": ids, "objectPaths": obj_paths,
                            "objectExtensions": sorted(exts), "objectActionTags":
                                sorted(t for t in tags if "action" in str(t).lower()),
                            "actOpcodeBlocked": opcode, "actHasParticleDependency": act_ptl,
                            "cppAdmission": stage(cov),
                            "bucket": bucket, "reasons": reasons})
        records.sort(key=lambda r: r["path"])
        counts = collections.Counter(r["bucket"] for r in records)
        reason_counts = collections.Counter(x for r in records for x in r["reasons"])
        ext_counts = collections.Counter(x for r in records for x in r["objectExtensions"])
        cpp_counts = {k: sum(1 for r in records if r["cppAdmission"].get(k) is True) for k in STAGES}
        gap_files = sum(1 for r in records if r["cppAdmission"].get("nonBlockingGaps"))
        gains = None
        if before_stages:
            gains = {k: [r["path"] for r in records
                         if before_stages.get(r["path"], {}).get(k) is False
                         and r["cppAdmission"].get(k) is True]
                     for k in STAGES}
        report = {
            "schemaVersion": 2,
            "purpose": "静态准入基线；不执行 ACT、不创建 World 实体、不证明原版等价。",
            "pvf": {"path": os.path.abspath(args.pvf), "entryCount": len(pvf.entries)},
            "inputs": {"coverage": [os.path.abspath(p) for p in coverage_paths],
                       "before": [os.path.abspath(p) for p in (args.before or [])],
                       "scriptSha256": __import__("hashlib").sha256(
                           open(__file__, "rb").read()).hexdigest()},
            "method": {
                "objectIds": "ACT dependencies 中显式 passive_object index，经 passiveobject.lst 解析",
                "supportedObjLeaves": sorted(SUPPORTED_EXTS),
                "blocked": ["PTL 解释器未注册", "OBJ→ACT 通用递归未注册",
                            "ACT 自身 opcode/particle 未支持", "注册表缺失/重复/解析失败"],
                "warningMark": "1031 PVF 实测 303 个 ACT / 1580 处，操作数为 2 或 4；"
                               "warning_mark_consumer_unregistered 是显式非阻塞缺口，不是已实现",
                "cppAdmission": "并列记录 dnf_inspect --act-coverage-prefix 的三阶段与整体静态准入；"
                                "ok 只代表静态准入，不代表 bind/World 执行",
                "limits": ["不读取 NUT/exe 动态对象创建", "不证明对象在实机被创建或命中",
                           "静态准入 ok 不等于 World 执行或 1031 视觉等价",
                           "bucket=admissible 是 OBJ 字面依赖分桶，不等于 C++ 侧 ok=true"],
            },
            "summary": {
                "actsWithPassiveObject": len(records),
                "uniqueObjectIds": len({i for r in records for i in r["objectIds"]}),
                "buckets": dict(sorted(counts.items())),
                "reasonCounts": dict(sorted(reason_counts.items())),
                "objectExtensionCounts": dict(sorted(ext_counts.items())),
                "admissibleSamples": [r["path"] for r in records if r["bucket"] == "admissible"][:25],
                "cppStageCounts": cpp_counts,
                "cppAdmittedSamples": [r["path"] for r in records if r["cppAdmission"].get("ok") is True][:25],
                "warningMarkGapFiles": gap_files,
                "gainsVsBefore": ({k: {"count": len(v), "samples": v[:25]} for k, v in gains.items()}
                                  if gains is not None else None),
            },
            "records": records,
            "decoderWarnings": decoder.warnings,
        }
        os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
        with open(args.out, "w", encoding="utf8", newline="\n") as stream:
            json.dump(report, stream, ensure_ascii=False, indent=2, allow_nan=False)
            stream.write("\n")
        print(json.dumps(report["summary"], ensure_ascii=False))
    finally:
        pvf.close()


if __name__ == "__main__":
    main()
