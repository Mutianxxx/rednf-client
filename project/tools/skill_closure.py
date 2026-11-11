#!/usr/bin/env python3
"""生成可复现的 PVF 静态候选闭包；不证明任何运行时消费关系。"""
from __future__ import annotations

import argparse
import collections
import hashlib
import json
import os
import posixpath
import re
import struct
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(ROOT), "..", "..", "dnf-result", "tools"))
from pvf_reader import Pvf, ScriptDecoder  # type: ignore

BIND = os.path.join(ROOT, "skill-bindings", "bindings")
BASEJOB = {"atmage": "mage", "atfighter": "fighter", "atgunner": "gunner",
           "demonicswordman": "swordman"}
RESOURCE_EXTS = {".ani", ".als", ".atk", ".obj", ".ptl", ".nut", ".act", ".chr"}
TOKEN_EXTS = RESOURCE_EXTS - {".ani", ".nut"} | {".skl", ".lst", ".mob"}
PATH_RE = re.compile(r"[^\s\x00\"'`<>|]+\.(?:ani|als|atk|obj|ptl|nut|act|skl|chr|img|lst|mob)$", re.I)
# 将注释和字符串一起词法扫描，避免从注释内误提取字符串。
NUT_RE = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


def norm(path):
    return posixpath.normpath(path.replace("\\", "/")).lstrip("/").lower()


def ext(path):
    return posixpath.splitext(path)[1].lower()


def stem(path):
    name = posixpath.basename(path).lower()
    return name[:-8] if name.endswith(".ani.als") else posixpath.splitext(name)[0]


def file_hash(path):
    with open(path, "rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def load_bindings():
    records, sources = [], []
    for name in sorted(os.listdir(BIND)):
        if not name.endswith(".json"):
            continue
        path = os.path.join(BIND, name)
        sources.append({"path": "skill-bindings/bindings/" + name, "sha256": file_hash(path)})
        with open(path, encoding="utf8") as stream:
            data = json.load(stream)
        for sid, skill in sorted(data.get("skills", {}).items(), key=lambda item: int(item[0])):
            records.append({"class": data.get("class", name.split("-skill-binding")[0]),
                            "skillId": int(sid), "skl": skill.get("skl"),
                            "states": skill.get("states") or [],
                            "effectAnis": skill.get("effect_anis") or [],
                            "source": sources[-1]["path"]})
    return records, sources


class ResourceGraph:
    def __init__(self, pvf, decoder):
        self.pvf, self.decoder = pvf, decoder
        self.by = {norm(e["path"]): e["path"] for e in pvf.entries}
        self.nodes = {}
        self.resolve_cache = {}
        self.passive_registry = {}
        self.passive_registry_duplicates = {}
        self.passive_registry_path = "passiveobject/passiveobject.lst"
        if self.passive_registry_path in self.by:
            try:
                for row in decoder.list_records(self.passive_registry_path):
                    oid = row["id"]
                    if oid in self.passive_registry:
                        self.passive_registry_duplicates.setdefault(oid, [self.passive_registry[oid]]).append(row)
                    else:
                        value = norm(row["value"])
                        if value not in self.by:
                            value = norm(posixpath.join("passiveobject", value))
                        self.passive_registry[oid] = {"value": row["value"], "target": value,
                                                      "tokenIndex": row.get("token_index")}
            except (ValueError, KeyError) as error:
                self.passive_registry_error = str(error)
                self.passive_registry.clear()
                self.passive_registry_duplicates.clear()
            else:
                self.passive_registry_error = None
        else:
            self.passive_registry_error = "registry-missing"

    def roots(self, source):
        parts = norm(source).split("/")
        if parts[0] == "skill" and len(parts) > 2:
            job = parts[1]
            return ["skill/" + job, "character/" + BASEJOB.get(job, job),
                    "passiveobject/character/" + BASEJOB.get(job, job), "sqr/character/" + job]
        if parts[0] in {"passiveobject", "sqr"} and len(parts) > 3 and parts[1] == "character":
            return ["/".join(parts[:3])]
        if len(parts) > 2:
            return ["/".join(parts[:2])]
        return []

    def resolve(self, source, value, roots=None):
        roots = self.roots(source) if roots is None else roots
        key = (norm(source), value, tuple(roots))
        if key in self.resolve_cache:
            return dict(self.resolve_cache[key])
        value_path = value.replace("\\", "/")
        options = [("direct", norm(value_path)),
                   ("same-directory", norm(posixpath.join(posixpath.dirname(source), value_path)))]
        options.extend(("job-root", norm(posixpath.join(root, value_path))) for root in roots)
        tested = list(dict.fromkeys(path for _, path in options))
        matches = collections.defaultdict(list)
        for mode, path in options:
            if path in self.by and mode not in matches[path]:
                matches[path].append(mode)
        result = {"value": value, "attempted": tested}
        if len(matches) == 1:
            path = next(iter(matches))
            result.update(status="resolved", target=path, resolution=matches[path])
        elif matches:
            result.update(status="ambiguous", matches=[{"path": path, "resolution": matches[path]}
                                                        for path in sorted(matches)])
        else:
            result["status"] = "external-image" if ext(value_path) == ".img" else "unresolved"
        self.resolve_cache[key] = result
        return dict(result)

    def node(self, path):
        path = norm(path)
        if path in self.nodes:
            return self.nodes[path]
        node = {"path": path, "kind": ext(path), "edges": [], "errors": []}
        self.nodes[path] = node
        suffix = ext(path)
        references = []
        passive_references = []
        try:
            raw = self.pvf.read(self.by[path])
            node["sha256"] = hashlib.sha256(raw).hexdigest()
            if suffix == ".nut":
                try:
                    text = raw.decode("utf-8-sig")
                    node["encoding"] = "utf-8-sig"
                except UnicodeDecodeError:
                    text = self.decoder.decode_text(raw, path)
                    node["encoding"] = "gbk"
                for match in NUT_RE.finditer(text):
                    literal = match.group(0)
                    if literal.startswith(("\"", "'")):
                        value = literal[1:-1].replace("\\\\", "\\").replace('\\"', '"').replace("\\'", "'")
                        if PATH_RE.fullmatch(value):
                            references.append((value, {"type": "nut-string", "offset": match.start(),
                                                       "line": text.count("\n", 0, match.start()) + 1}))
            elif suffix == ".ani":
                # 1031 二进制 ANI：帧数 u16、图像表项数 u16、逐项 i32 长度 + 字节串。
                if len(raw) < 4:
                    raise ValueError("ANI 图像表头截断")
                frame_count, count = struct.unpack_from("<HH", raw)
                if frame_count > 30000 or count > 10000:
                    raise ValueError("ANI 图像表头数目异常")
                node["frameCount"] = frame_count
                at = 4
                for index in range(count):
                    length = struct.unpack_from("<i", raw, at)[0]
                    at += 4
                    if length < 0 or at + length > len(raw):
                        raise ValueError("ANI 图像表越界")
                    value = self.decoder.decode_text(raw[at:at + length].rstrip(b"\0"), path)
                    references.append((value, {"type": "ani-image-table", "index": index, "offset": at}))
                    at += length
            elif suffix in TOKEN_EXTS:
                tag = None
                tokens = self.decoder.tokens(raw)
                # ACT 的被动对象 ID 只接受 CREATE PASSIVEOBJECT block 内显式 [INDEX]。
                if suffix == ".act":
                    depth = 0
                    pending = []
                    for token_index, token in enumerate(tokens):
                        if token["type"] == 5:
                            tag_name = str(token.get("value") or "").upper().strip()
                            if tag_name == "[CREATE PASSIVEOBJECT]":
                                depth += 1
                            elif tag_name == "[/CREATE PASSIVEOBJECT]" and depth:
                                depth -= 1
                                if not depth:
                                    passive_references.extend(pending)
                                    pending = []
                            elif tag_name == "[INDEX]" and depth:
                                # INDEX 的值必须是 decoder 给出的整数 literal。
                                continue
                        elif depth and token["type"] == 2 and isinstance(token.get("value"), int):
                            # 由紧随 INDEX 标签后的第一个整数 token 消费。
                            prev = tokens[token_index - 1] if token_index else None
                            if prev and prev.get("type") == 5 and str(prev.get("value") or "").upper().strip() == "[INDEX]":
                                pending.append((token["value"], {"type": "act-passiveobject-index", "offset": token["offset"], "registry": self.passive_registry_path}))
                    if depth:
                        node["errors"].append({"error": "unclosed-create-passiveobject", "discardedReferences": len(pending)})
                for token in tokens:
                    if token["type"] == 5:
                        tag = token["value"]
                        continue
                    value = token.get("value")
                    if isinstance(value, str) and PATH_RE.fullmatch(value):
                        references.append((value, {"type": "token-field", "tag": tag,
                                                   "offset": token["offset"], "tokenType": token["type"]}))
                    if token.get("unresolved"):
                        node["errors"].append({"offset": token["offset"], "error": token["unresolved"]})
            else:
                node["parseStatus"] = "unsupported-leaf"
        except (ValueError, KeyError, UnicodeError, struct.error) as error:
            node["errors"].append({"error": str(error)})
        for value, evidence in references:
            edge = self.resolve(path, value)
            edge.update(relation="literal-reference", evidence=evidence, classification="evidence")
            node["edges"].append(edge)
        for object_id, evidence in passive_references:
            reg = self.passive_registry.get(object_id)
            if reg is None:
                node["edges"].append({"value": object_id, "objectId": object_id, "status": "unresolved",
                                      "relation": "act-passiveobject-index", "classification": "evidence",
                                      "evidence": evidence, "registry": self.passive_registry_path,
                                      "diagnostic": ("registry-missing" if self.passive_registry_error == "registry-missing" else
                                                     "registry-read-error" if self.passive_registry_error else "unknown-passiveobject-id"),
                                      **({"registryError": self.passive_registry_error} if self.passive_registry_error else {})})
            elif object_id in self.passive_registry_duplicates:
                node["edges"].append({"value": object_id, "objectId": object_id, "status": "ambiguous",
                                      "relation": "act-passiveobject-index", "classification": "evidence",
                                      "evidence": evidence, "registry": self.passive_registry_path,
                                      "matches": self.passive_registry_duplicates[object_id],
                                      "diagnostic": "duplicate-passiveobject-id"})
            else:
                target = reg["target"]
                status = "resolved" if target in self.by else "unresolved"
                node["edges"].append({"value": object_id, "objectId": object_id, "target": target,
                                      "status": status, "relation": "act-passiveobject-index",
                                      "classification": "evidence", "evidence": evidence,
                                      "registry": self.passive_registry_path,
                                      "registryValue": reg["value"],
                                      **({"diagnostic": "registry-target-missing"} if status != "resolved" else {})})
        if suffix == ".ani":
            for sidecar in (path + ".als", posixpath.splitext(path)[0] + ".als"):
                if sidecar in self.by:
                    node["edges"].append({"value": sidecar, "target": sidecar, "status": "resolved",
                                          "relation": "ani-sidecar", "classification": "candidate",
                                          "resolution": ["sidecar-convention"]})
        return node

    def closure(self, seeds):
        # 同一节点可由直引与候选两条路线到达；保留两种来源，不让候选提升成证据。
        reached = {"evidence": set(), "candidate": set()}
        queue = collections.deque(seeds)
        while queue:
            path, classification = queue.popleft()
            if path in reached[classification]:
                continue
            reached[classification].add(path)
            for edge in self.node(path)["edges"]:
                if edge["status"] == "resolved":
                    level = "candidate" if classification == "candidate" or edge["classification"] == "candidate" else "evidence"
                    queue.append((edge["target"], level))
        return reached


def family_indexes(paths, jobs):
    index = collections.defaultdict(set)
    scope = set()
    scopes = collections.defaultdict(set)
    for job in jobs:
        base = BASEJOB.get(job, job)
        for root in (f"character/{base}", f"passiveobject/character/{base}", f"sqr/character/{job}"):
            scopes[root].add(job)
    for path in paths:
        if ext(path) not in RESOURCE_EXTS:
            continue
        parts = path.split("/")
        width = 3 if parts[0] in {"passiveobject", "sqr"} else 2
        root = "/".join(parts[:width])
        if root not in scopes:
            continue
        scope.add(path)
        # 精确目录段或文件 stem；不使用前缀，更不将整个职业 sqr 根加入技能。
        keys = set(parts[width:-1]) | {stem(path)}
        for job in scopes[root]:
            for key in keys:
                index[(job, key)].add(path)
    return index, scope


def skill_stats(records):
    return {"skills": len(records),
            "sklOnly": sum(not r["resources"] for r in records),
            "skillsWithResources": sum(bool(r["resources"]) for r in records),
            "skillsWithAni": sum(any(p.endswith(".ani") for p in r["resources"]) for r in records),
            "skillsWithEvidence": sum(bool(r["evidenceResources"]) for r in records),
            "skillsWithEvidenceAni": sum(any(p.endswith(".ani") for p in r["evidenceResources"]) for r in records),
            "skillsWithCandidates": sum(bool(r["candidateResources"]) for r in records),
            "skillsWithBindingCandidates": sum(bool(r["bindingCandidates"]) for r in records),
            "skillsWithResolvedBindingCandidates": sum(any(e["status"] == "resolved" for e in r["bindingCandidates"]) for r in records),
            "skillsWithFamilyCandidates": sum(bool(r["familyCandidates"]) for r in records)}


def build_report(pvf, decoder, pvf_path):
    graph = ResourceGraph(pvf, decoder)
    roots = sorted(path for path in graph.by if ext(path) == ".skl")
    jobs = sorted({path.split("/")[1] for path in roots})
    family_index, scope = family_indexes(sorted(graph.by), jobs)
    bindings, binding_sources = load_bindings()
    by_skl = collections.defaultdict(list)
    unmatched_bindings = []
    for binding in bindings:
        value = binding["skl"] or ""
        path = norm(value if norm(value).startswith("skill/") else "skill/" + value)
        if path in graph.by and ext(path) == ".skl":
            by_skl[path].append(binding)
        else:
            unmatched_bindings.append(binding)
    registry = collections.defaultdict(list)
    registry_errors = []
    for path in sorted(graph.by):
        if path.startswith("skill/") and path.endswith(".lst"):
            try:
                for row in decoder.list_records(path):
                    if ext(row["value"]) != ".skl":
                        continue
                    result = graph.resolve(path, row["value"], ["skill"])
                    if result["status"] == "resolved":
                        registry[result["target"]].append({"list": path, "skillId": row["id"]})
                    else:
                        registry_errors.append({"list": path, "skillId": row["id"], **result})
            except (ValueError, KeyError) as error:
                registry_errors.append({"list": path, "error": str(error)})
    records = []
    joined = set()
    for skl in roots:
        job = skl.split("/")[1]
        base = BASEJOB.get(job, job)
        record = {"class": job, "basejob": base, "skl": skl, "stem": stem(skl),
                  "registry": registry[skl], "bindingCandidates": [], "familyCandidates": []}
        seeds = [(skl, "evidence")]
        for binding in by_skl[skl]:
            for state in binding["states"]:
                for motion in state.get("entry_motions") or []:
                    value = motion.get("ani") or ""
                    if value:
                        edge = graph.resolve(f"character/{base}/{base}.chr", value, [f"character/{base}"])
                        edge.update(classification="candidate", relation="binding-entry-motion",
                                    bindingSource=binding["source"], bindingClass=binding["class"],
                                    skillId=binding["skillId"], state=state.get("state"),
                                    motionIndex=motion.get("index"), handler=state.get("handler"))
                        record["bindingCandidates"].append(edge)
            for value in binding["effectAnis"]:
                edge = graph.resolve(f"character/{base}/{base}.chr", value,
                                     [f"character/{base}", f"character/{base}/effect"])
                edge.update(classification="candidate", relation="binding-effect-ani",
                            bindingSource=binding["source"], bindingClass=binding["class"], skillId=binding["skillId"])
                record["bindingCandidates"].append(edge)
        names = [stem(skl)]
        if job in BASEJOB and job.startswith("at") and not stem(skl).startswith("at"):
            names.append("at" + stem(skl))
        families = set()
        for name in names:
            families.update(family_index.get((job, name), ()))
        record["familyCandidates"] = sorted(families)
        record["familyMatchKeys"] = names
        seeds.extend((path, "candidate") for path in sorted(families))
        seeds.extend((edge["target"], "candidate") for edge in record["bindingCandidates"] if edge["status"] == "resolved")
        reached = graph.closure(seeds)
        record["evidenceResources"] = sorted(reached["evidence"] - {skl})
        record["candidateResources"] = sorted(reached["candidate"] - {skl})
        record["resources"] = sorted((reached["evidence"] | reached["candidate"]) - {skl})
        # SKL 定义无论通过何种路线到达，都不算技能的额外资源。
        for key in ("evidenceResources", "candidateResources", "resources"):
            record[key] = [path for path in record[key] if ext(path) != ".skl"]
        record["graphRoots"] = [{"path": path, "classification": level} for path, level in seeds]
        record["graphNodes"] = sorted(reached["evidence"] | reached["candidate"])
        joined.update(record["resources"])
        records.append(record)
    statuses = collections.Counter({status: 0 for status in ("resolved", "ambiguous", "unresolved", "external-image")})
    by_kind = collections.defaultdict(collections.Counter)
    relations = collections.Counter()
    for node in graph.nodes.values():
        for edge in node["edges"]:
            statuses[edge["status"]] += 1
            by_kind[edge["status"]][ext(edge["value"]) if isinstance(edge["value"], str) else "passiveobject-id"] += 1
            relations[edge["relation"]] += 1
    summary = skill_stats(records)
    summary.update(bindingCount=len(bindings), matchedBindingCount=sum(map(len, by_skl.values())),
                   skillsWithBindingRecords=sum(bool(by_skl[path]) for path in roots),
                   graphNodes=len(graph.nodes), graphEdges=sum(statuses.values()),
                   graphEdgeStatuses=dict(sorted(statuses.items())),
                   graphEdgeStatusesByKind={k: dict(sorted(v.items())) for k, v in sorted(by_kind.items())},
                   graphRelations=dict(sorted(relations.items())),
                   graphNodesWithErrors=sum(bool(node["errors"]) for node in graph.nodes.values()),
                   scopedCandidateFiles=len(scope), unassignedScopedCandidates=len(scope - joined),
                   bindingCandidateStatuses=dict(sorted(collections.Counter(
                       edge["status"] for r in records for edge in r["bindingCandidates"]).items())),
                   passiveObjectRegistryPath=graph.passive_registry_path,
                   passiveObjectRegistryCount=len(graph.passive_registry),
                   passiveObjectRegistryDuplicates=len(graph.passive_registry_duplicates),
                   passiveObjectRegistryError=graph.passive_registry_error,
                   actPassiveObjectEdges=sum(1 for node in graph.nodes.values() for edge in node["edges"] if edge["relation"] == "act-passiveobject-index"),
                   actPassiveObjectResolved=sum(1 for node in graph.nodes.values() for edge in node["edges"] if edge["relation"] == "act-passiveobject-index" and edge["status"] == "resolved"),
                   actPassiveObjectDiagnostics=sum(1 for node in graph.nodes.values() for edge in node["edges"] if edge["relation"] == "act-passiveobject-index" and edge.get("diagnostic")))
    return {"schemaVersion": 3,
            "pvf": {"path": os.path.abspath(pvf_path), "sha256": file_hash(pvf_path), "entryCount": len(pvf.entries)},
            "inputs": {"scriptSha256": file_hash(__file__), "bindings": binding_sources},
            "method": {"important": "静态候选闭包，不证明运行消费；evidence 表示字面路径或 ACT 显式被动对象 ID 注册引用。",
                       "roots": "PVF 全部 .skl，包含非玩家职业；SKL 本身不计 resources。",
                       "basejob": BASEJOB, "family": "职业范围内精确目录段/文件 stem；at 职业可额外匹配 at+stem，全部为 candidate。",
                       "resolution": "direct、同目录、职业根收集全部命中；多命中为 ambiguous，不任选、不递归。",
                       "sidecars": "存在的 .ani.als 与同 stem .als 作为 candidate 递归。",
                       "diagnostics": "完整共享 graph 保存每条引用的字段/偏移、ambiguous、unresolved、external-image；技能 graphNodes 可连接查询，无截断。",
                       "unassigned": "仅玩家/技能职业 character、passiveobject/character、sqr/character 范围的未关联候选，不叫未消费。",
                       "passiveObjects": "仅 ACT [CREATE PASSIVEOBJECT] 内紧随 [INDEX] 的 type-2 整数经 passiveobject/passiveobject.lst 解析；重复 ID 和未知 ID 不递归。",
                       "limitations": ["未恢复 native caller、通用数字索引到资源的桥、对象创建条件、时序或运行时消费。",
                                       "不执行 NUT；动态拼接、变量、格式化路径、数字对象 ID 不求值。",
                                       "IMG/格式化 IMG 模板仅记录外部引用，未打开 NPK 验证。",
                                       "精确 stem 与 sidecar 均为候选约定；共享 basejob 目录可能含另一职业资源。",
                                       "ANI 仅读取二进制图像表，不解释帧事件；格式错误记录 errors。",
                                       "缺失和歧义不自动补全；未关联范围不包含全体怪物 ANI。"]},
            "summary": summary,
            "byClass": {job: skill_stats([r for r in records if r["class"] == job]) for job in jobs},
            "skills": records, "graph": {path: graph.nodes[path] for path in sorted(graph.nodes)},
            "unmatchedBindings": unmatched_bindings, "registryErrors": registry_errors,
            "decoderWarnings": decoder.warnings,
            "unassignedScopedCandidates": sorted(scope - joined)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvf", default="D:/dnf-rebuild/DNF1031客户端/Script.pvf")
    parser.add_argument("--out", required=True)
    args = parser.parse_args()
    pvf = Pvf(args.pvf)
    try:
        report = build_report(pvf, ScriptDecoder(pvf), args.pvf)
    finally:
        pvf.close()
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf8", newline="\n") as stream:
        json.dump(report, stream, ensure_ascii=False, indent=2, allow_nan=False)
        stream.write("\n")
    print(json.dumps(report["summary"], ensure_ascii=False))


if __name__ == "__main__":
    main()
