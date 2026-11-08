"""Verify retained evidence identity, not original-client runtime equivalence."""
import hashlib
import json
import sys

from native60 import OUT, ROOT, SHA256, MD, data, u32, off, RAW


def main():
    checks = []
    def check(name, actual, expected):
        checks.append({"name": name, "passed": actual == expected,
                       "actual": actual, "expected": expected})
    manifest = json.loads((OUT / "evidence-index.json").read_text(encoding="utf-8"))
    check("binary_sha256", SHA256, manifest["source_sha256"])
    for row in manifest["captures"]:
        raw = (OUT / (row["stem"] + ".bin")).read_bytes()
        check(row["stem"] + ":source_bytes", raw == data(int(row["va"],16), row["length"]), True)
        check(row["stem"] + ":sha256", hashlib.sha256(raw).hexdigest(), row["bytes_sha256"])
        if row["disassembled"]:
            check(row["stem"] + ":decode_coverage", sum(i.size for i in MD.disasm(raw, int(row["va"],16))), len(raw))
    for row in manifest["vtable_slots"]:
        check("slot:" + row["slot_va"], hex(u32(int(row["slot_va"],16))), row["target"])
    for row in manifest["rea"]:
        path = (OUT / row["result"]).resolve()
        ev = json.loads(path.read_text(encoding="utf-8"))["structuredContent"]
        check(path.name + ":evidence_id", ev["evidence_id"], row["evidence_id"])
        check(path.name + ":source_sha256", ev["subject"]["digest"]["sha256"], SHA256)
        check(path.name + ":canonical_procedure", ev["normalized_result"]["procedure"]["address"], row["expected_function"])
    report = json.loads((OUT / "death-resources.json").read_text(encoding="utf-8"))
    sys.path.insert(0, str(ROOT / "analysis"))
    from pvf60 import Pvf60
    pvf = Pvf60(ROOT / "DFO/Script.pvf")
    check("pvf_sha256", hashlib.sha256(pvf.data).hexdigest(), report["archive_sha256"])
    for row in report["resources"] + report["sample_documents"]:
        raw = (OUT / row["raw_export"]).read_bytes()
        check(row["path"] + ":archive_bytes_crc_checked", pvf.read(row["path"]) == raw, True)
        check(row["path"] + ":sha256", hashlib.sha256(raw).hexdigest(), row["sha256"])
    check("resource_unresolved_edges", sum("unresolved" in e for e in report["resource_edges"]), 0)
    result = {"scope": "Source identity, capture bounds, disassembly coverage, exact vtable dispatch, retained REA function identity, PVF archive/entry CRC and exports. No runtime behavior equivalence asserted.",
              "passed": sum(x["passed"] for x in checks), "total": len(checks), "checks": checks}
    (OUT / "verification-result.json").write_text(json.dumps(result, indent=2)+"\n", encoding="utf-8")
    print(json.dumps({"passed": result["passed"], "total": len(checks),
                      "failures": [x for x in checks if not x["passed"]]}))
    if result["passed"] != len(checks):
        raise SystemExit(1)


if __name__ == "__main__":
    main()
