"""Read-only UI/map contract checks for the independent C++ project."""
from __future__ import annotations
import argparse
import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parents[1]
SRC = ROOT / "src"
AUDIT = WORKSPACE / "dnf-native-demo/reports/knowledge-base-audit/ui-source-1031"

def check(ok: bool, message: str) -> None:
    if not ok:
        raise AssertionError(message)

def text(path: Path) -> str:
    return path.read_text(encoding="utf-8")

def static_contracts() -> list[str]:
    world_map = text(SRC / "presentation/ui/windows/world_map_ui.cpp")
    region_ui = text(SRC / "presentation/ui/windows/region_ui.cpp")
    scene = text(SRC / "render/renderer.cpp")
    camera = text(SRC / "presentation/maps/scene_camera.cpp")
    region = text(SRC / "simulation/world/region.cpp")
    checks = []
    check("{255,217,99,255}" not in world_map, "yellow area overlay removed")
    check('minimap/dungeon/minimap.img",196' in world_map, "player marker retained")
    check('BusinessUiGrid::from(itemLayout,"1114")' in region_ui, "shop consumes PVF grid")
    check("si->second.items" in region_ui and "p.item(list[index])" in region_ui, "shop consumes .shp IDs")
    check("trialIds[]" not in region_ui, "shop has no hard-coded products")
    check("sceneDrawCommands(*this, front)" in scene and "- cameraY - 120" in scene, "tile projection retained")
    check("repeatWidth <= 0" in scene and "layer.loopY" in scene, "background repeat guards retained")
    check("sourceVisualGap" in camera and "sourceFloorCovered" in camera, "camera coverage diagnostics retained")
    check("RegionPreparation::OnDemand" in region or "RegionPreparation preparation" in region, "on-demand region mode retained")
    item_json = json.loads((AUDIT / "ui__inventory__inventory_item.ui.json").read_text(encoding="utf-8"))
    vals = item_json["tokens"]
    at = next(i for i, token in enumerate(vals) if token.get("value") == "[grid data]")
    check([vals[at + 1]["value"], vals[at + 2]["value"]] == [8, 4], "audit source grid is 8x4")
    check([vals[at + 6]["value"], vals[at + 7]["value"], vals[at + 8]["value"], vals[at + 9]["value"]] == [0, 0, 30, 30], "audit source cell is 30x30")
    checks.extend(["world-map yellow area overlay removed", "PVF shop grid and catalog IDs", "map projection/layer/repeat guards", "camera coverage diagnostics", "audit source grid 8x4 30px"])
    return checks

def inspect_source(client: Path, inspector: Path) -> dict:
    def invoke(*args: str):
        proc = subprocess.run([str(inspector), str(client), *args], check=True, capture_output=True, text=True, encoding="utf-8")
        return json.loads(proc.stdout)
    paths = invoke("--paths", "itemshop/", "")
    paths = [p for p in paths if str(p).endswith(".shp")]
    check(isinstance(paths, list) and paths, "itemshop registry exposes .shp")
    selected = None
    for path in paths:
        report = invoke("--script", str(path))
        if any(f.get("tag") == "[sell item]" for f in report.get("fields", [])):
            selected = report
            break
    check(selected is not None, "registered .shp exposes [sell item]")
    sell = [f for f in selected["fields"] if f["tag"] == "[sell item]"]
    check(all(isinstance(v, int) for f in sell for v in f["values"]), "sell item values are integers")
    return {"shop_members": len(paths), "sample": selected["path"], "sell_item_records": len(sell), "source": "current 1031 PVF via dnf_inspect"}

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--client", type=Path)
    parser.add_argument("--inspector", type=Path, default=ROOT / "cache/swordman-shop-build/dnf_inspect.exe")
    args = parser.parse_args()
    result = {"status": "pass", "static_checks": static_contracts(), "runtime_source": None, "build_started": False}
    if args.client is None:
        candidates = [p for p in WORKSPACE.iterdir() if p.is_dir() and p.name.startswith("DNF1031") and (p / "Script.pvf").exists()]
        if len(candidates) == 1:
            args.client = candidates[0]
    if args.client:
        if not args.client.exists():
            candidates = [p for p in WORKSPACE.iterdir() if p.is_dir() and p.name.startswith("DNF1031") and (p / "Script.pvf").exists()]
            if len(candidates) == 1:
                args.client = candidates[0]
        check(args.inspector.exists(), f"missing inspector: {args.inspector}")
        check(args.client.exists() and (args.client / "Script.pvf").exists(), f"missing client PVF: {args.client}")
        result["runtime_source"] = inspect_source(args.client, args.inspector)
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
