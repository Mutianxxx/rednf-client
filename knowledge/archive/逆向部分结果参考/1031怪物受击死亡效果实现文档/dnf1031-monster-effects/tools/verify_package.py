"""Verify portable handoff files and optionally exercise the built reference renderer."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
from urllib.parse import unquote

ROOT = Path(__file__).resolve().parents[1]

def load(path):
    return json.loads(path.read_text("utf-8"))

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--client", type=Path)
    parser.add_argument("--run-reference", action="store_true")
    parser.add_argument("--report", type=Path, help="write optional JSON report (prefer build/)")
    args = parser.parse_args()
    checks = []
    def passed(name, **detail):
        checks.append(dict(check=name, passed=True, **detail))
    manifest = load(ROOT/"manifest.json")
    for name, expected in manifest["files"].items():
        path = ROOT/name
        assert path.is_file(), name
        assert path.stat().st_size == expected["size"], name
        with path.open("rb") as stream:
            digest = hashlib.file_digest(stream, "sha256").hexdigest()
        assert digest == expected["sha256"], name
    actual = {p.relative_to(ROOT).as_posix() for p in ROOT.rglob("*") if p.is_file() and p.name != "manifest.json" and not any(v in ("build", "__pycache__") for v in p.relative_to(ROOT).parts)}
    assert actual == set(manifest["files"]), dict(unlisted=sorted(actual-set(manifest["files"])), missing=sorted(set(manifest["files"])-actual))
    passed("all_packaged_file_hashes_and_sizes", files=len(actual))
    links = 0
    for path in ROOT.glob("*.md"):
        for raw in re.findall(r"\]\(([^)]+)\)", path.read_text("utf-8")):
            target = unquote(raw.strip("<>"))
            if re.match(r"[a-zA-Z][a-zA-Z0-9+.-]*:", target) or target.startswith("#"):
                continue
            target = target.split("#", 1)[0]
            assert (path.parent/target).is_file(), (str(path), target)
            links += 1
    passed("all_top_level_markdown_relative_links", links=links)
    for row in load(ROOT/"code-map.json"):
        lines = (ROOT/row["file"]).read_text("utf-8").splitlines()
        assert row["symbol"] in lines[row["line"]-1], row
    passed("actual_source_symbol_line_locations")
    catalog = load(ROOT/"data/monsters.json")
    assert catalog["source"] == manifest["source"]
    assert len(catalog["monsters"]) == 2070
    assert sum(bool(row["states"].get("death", {}).get("tracks")) for row in catalog["monsters"]) == 357
    contract = load(ROOT/"effect-contract.json")
    assert contract["source"] == catalog["source"]
    assert contract["shared_timing_ms"]["white_at"] == 60
    assert contract["shared_timing_ms"]["burst_at"] == 220
    assert contract["shared_particle"]["count"] == 10
    passed("catalog_2070_and_explicit_death_357_contract_version")
    graphs = []
    for monster_id in (5001, 1, 61491, 56013, 59005, 62638):
        graph = load(ROOT/f"examples/{monster_id}/graph.json")
        assert graph["source"] == catalog["source"]
        assert monster_id in graph["monster"]["ids"]
        assert not graph["diagnostics"], (monster_id, graph["diagnostics"])
        assert not graph["npk_index_errors"]
        nodes = {node["path"]:node for node in graph["nodes"]}
        assert len(nodes) == len(graph["nodes"])
        assert all(edge["target"] in nodes for edge in graph["edges"])
        assert all(edge["source"] in nodes for edge in graph["edges"])
        for node in nodes.values():
            assert re.fullmatch(r"[a-f0-9]{64}", node["sha256"]), node["path"]
            assert "error" not in node and "img_error" not in node, node["path"]
            if node["path"].endswith(".ani"):
                assert node["animation"]["consumed_bytes"] == node["size"]
        graphs.append(dict(id=monster_id, nodes=len(nodes), edges=len(graph["edges"])))
    passed("six_monster_complete_resolved_graphs", examples=graphs)
    common = load(ROOT/"examples/common-images.json")
    assert common["source"] == catalog["source"]
    by_path = {row["path"]:row for row in common["resources"]}
    for palette in range(1, 30):
        row = by_path[f"monster/common/m{palette:04d}.img"]
        assert "error" not in row and row["img"]["frame_count"] == 4
        assert len(row["img"]["requested_frames"]) == 4
    assert all("error" not in row for row in common["resources"])
    assert len(load(ROOT/"evidence/common-death-resources.json")) == 23
    passed("all_29_palette_images_and_23_common_ani_ptl")
    for script in (ROOT/"tools").rglob("*.py"):
        compile(script.read_text("utf-8"), str(script), "exec")
    passed("portable_python_tools_compile_without_optional_packages")
    if args.run_reference:
        if not args.client:
            parser.error("--run-reference requires --client")
        exe = ROOT/"build/monster_demo.exe"
        assert exe.is_file(), "Run tools/build_reference.py first"
        out = ROOT/"build/package-runtime-verification"
        result = subprocess.run([str(exe), "--client", str(args.client.resolve()), "--verify", "--report", str(out)], timeout=180)
        assert result.returncode == 0, (out/"error.json").read_text("utf-8") if (out/"error.json").is_file() else result.returncode
        frames = load(out/"verification.json")
        shared = load(out/"shared-death-verification.json")
        reads = load(out/"resource-reads.json")
        assert frames["ok"] and len(frames["cases"]) == 6 and frames["rendered_main_animation_frames"] == 52
        assert shared["ok"] and len(shared["cases"]) == 4
        assert not reads["archive_index_errors"]
        assert not frames["unconsumed_render_nodes"]
        passed("independently_built_reference_actual_rendering", main_frames=52, shared_cases=4)
    report = dict(ok=True, source=catalog["source"], checks=checks,
                  scope="Package consistency and dependency resolution; optional exact reference behavior check, not original-client parity.")
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2)+"\n", "utf-8")
    print(json.dumps(report, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
