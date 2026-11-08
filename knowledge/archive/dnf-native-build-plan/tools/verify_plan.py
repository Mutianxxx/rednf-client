"""Verify plan coverage, local links, evidence, and task DAG; no game execution."""
from pathlib import Path
from urllib.parse import unquote, urlsplit
import datetime
import hashlib
import json
import re

PLAN = Path(__file__).resolve().parents[1]
WORKSPACE = PLAN.parent


def main():
    errors, checks = [], []
    def check(label, condition, detail=""):
        checks.append({"check": label, "passed": bool(condition), "detail": detail})
        if not condition:
            errors.append(label + (": " + detail if detail else ""))
    def read(name):
        try:
            return json.loads((PLAN / "appendices" / name).read_text(encoding="utf-8"))
        except (OSError, ValueError) as exc:
            check("json:" + name, False, str(exc))
            return {}

    documents = sorted(PLAN.rglob("*.md"))
    check("numbered_documents", len(list(PLAN.glob("[0-9][0-9]-*.md"))) == 14)
    check("readme_present", (PLAN / "README.md").is_file())
    for required in ("core-pseudocode.md", "recommended-decisions.md", "completeness-review.md"):
        check("appendix:" + required, (PLAN / "appendices" / required).is_file())

    local_link_count = 0
    for path in documents:
        content = path.read_text(encoding="utf-8")
        rel = path.relative_to(PLAN).as_posix()
        check("utf8:" + rel, "\ufffd" not in content and "\x00" not in content)
        check("substantial:" + rel, len(content) > 450)
        check("no_empty_placeholder:" + rel, re.search(r"(?im)^\s*(TODO|TBD|待补充|待填写)\s*$", content) is None)
        check("fenced_blocks:" + rel, sum(line.lstrip().startswith("```") for line in content.splitlines()) % 2 == 0)
        # These plan files use ordinary inline links with no parentheses in targets.
        for target in re.findall(r"\[[^\]\n]+\]\(([^)\n]+)\)", content):
            target = target.strip().strip("<>")
            if target.startswith("#") or urlsplit(target).scheme:
                continue
            destination = unquote(target.split("#", 1)[0])
            if not destination:
                continue
            local_link_count += 1
            check("link:" + rel, (path.parent / destination).exists(), destination)

    task_data = read("task-graph.json")
    tasks = task_data.get("tasks", [])
    task_map = {t["id"]: t for t in tasks}
    check("tasks_P00_P19", len(tasks) == 20 and set(task_map) == {f"P{i:02d}" for i in range(20)})
    check("only_documentation_delivered", all(t.get("status") == ("documentation_delivered" if t["id"] == "P00" else "planned") for t in tasks))
    visited, visiting, order = set(), set(), []
    def visit(i):
        if i in visited:
            return
        if i in visiting:
            raise ValueError("cycle at " + i)
        if i not in task_map:
            raise ValueError("unknown dependency " + i)
        visiting.add(i)
        for dep in task_map[i]["depends_on"]:
            visit(dep)
        visiting.remove(i)
        visited.add(i)
        order.append(i)
    try:
        for task_id in task_map:
            visit(task_id)
        check("task_graph_acyclic", True)
    except ValueError as exc:
        check("task_graph_acyclic", False, str(exc))

    execution_text = (PLAN / "13-execution-plan-and-acceptance.md").read_text(encoding="utf-8")
    acceptance_ids = set(re.findall(r"\bA-[A-Z]+\b", execution_text))
    # Check that each prose table dependency agrees with the machine DAG.
    for t in tasks:
        row = re.search(r"^\| " + t["id"] + r" \|[^\n]+$", execution_text, re.M)
        check("task_in_execution_table:" + t["id"], row is not None)
        if row:
            cells = row.group().split("|")
            prose_dependencies = set(re.findall(r"\bP\d{2}\b", cells[3]))
            check("task_dependencies_match:" + t["id"], prose_dependencies == set(t["depends_on"]))

    requirements = read("requirements-traceability.json").get("requirements", [])
    ids = [r["id"] for r in requirements]
    check("eleven_principles_plus_confirmations", len(ids) == len(set(ids)) == 16 and set(ids) == {f"U{i:02d}" for i in range(1, 12)} | {f"C{i:02d}" for i in range(1, 6)})
    modules = read("module-coverage.json").get("modules", [])
    baseline = json.loads((WORKSPACE / "dnf-result/research/new-version-readiness.json").read_text(encoding="utf-8-sig"))
    domains = {x["domain"] for x in baseline["systems"]}
    check("all_research_domains", len(modules) == len(domains) == 25 and {x["domain"] for x in modules} == domains)
    for record in tasks + requirements + modules:
        key = record.get("id", record.get("domain"))
        check("nonempty_documents:" + key, bool(record.get("documents")))
        for path in record.get("documents", []):
            check("mapped_document:" + key, (PLAN / path).is_file(), path)
        for t in record.get("tasks", []):
            check("mapped_task:" + key, t in task_map, t)
        for a in record.get("acceptance", []):
            check("mapped_acceptance:" + key, a in acceptance_ids, a)
    for record in modules:
        check("scope_reason:" + record["domain"], bool(record.get("scope_reason")) and record.get("scope") in {"required", "conditional", "deferred_boundary"})

    evidence = read("evidence-index.json").get("source_files", [])
    for item in evidence:
        p = WORKSPACE / item["workspace_relative_path"]
        check("evidence_exists:" + item["id"], p.is_file(), str(p))
        if p.is_file():
            check("evidence_hash:" + item["id"], hashlib.sha256(p.read_bytes()).hexdigest() == item["sha256"])
    schema = read("skill-coverage.schema.json")
    check("skill_schema_required_dimensions", {"implementation", "evidence", "verification", "lifecycle"} <= set(schema.get("required", [])))
    schema_validation = "structural checks only"
    try:
        from jsonschema import Draft202012Validator
        Draft202012Validator.check_schema(schema)
        schema_validation = "Draft202012Validator.check_schema passed"
        check("skill_schema_draft202012", True)
    except ImportError:
        check("skill_schema_core_structure", schema.get("type") == "object" and "$defs" in schema)
    except Exception as exc:
        check("skill_schema_draft202012", False, str(exc))

    # Any referenced top-level task must exist, including subtask prefixes.
    for p in documents:
        for task_id in set(re.findall(r"\bP\d{2}\b", p.read_text(encoding="utf-8"))):
            check("known_task:" + p.name, task_id in task_map, task_id)

    inventory = []
    for p in sorted(PLAN.rglob("*")):
        if p.is_file() and "verification" not in p.relative_to(PLAN).parts and "__pycache__" not in p.parts:
            raw = p.read_bytes()
            inventory.append({"path": p.relative_to(PLAN).as_posix(), "bytes": len(raw), "sha256": hashlib.sha256(raw).hexdigest()})
    report = {"plan_version": "v1.1", "scope": "documentation_structure_and_traceability_not_game_runtime",
              "checked_at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "passed": not errors, "summary": {"markdown_files": len(documents), "local_links": local_link_count,
              "tasks": len(tasks), "requirements": len(requirements), "systems": len(modules), "evidence_files": len(evidence),
              "checks": len(checks), "failed_checks": len(errors)},
              "skill_schema_validation": schema_validation, "topological_order": order,
              "limitations": ["No native executable or frontend run", "Source evidence documents hashed; full PVF/EXE identity not rehashed", "Semantic completeness additionally reviewed by humans/agents; link checks alone do not prove algorithms"],
              "errors": errors, "checks": checks, "document_inventory": inventory}
    output = PLAN / "verification/plan-validation.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"passed": report["passed"], **report["summary"], "errors": errors}, ensure_ascii=False))
    raise SystemExit(0 if not errors else 1)


if __name__ == "__main__":
    main()
