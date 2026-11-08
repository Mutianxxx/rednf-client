"""Check shipped dependencies, actual frame rendering and normal-window playback."""
import hashlib
import json
import subprocess
from PIL import Image
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load(path):
    return json.loads(path.read_text("utf-8"))


def main():
    out = ROOT / "reports/validation" / datetime.now().strftime("%Y%m%d-%H%M%S")
    out.mkdir(parents=True)
    checks = []
    def passed(name, **detail):
        checks.append(dict(check=name, passed=True, **detail))
    build = load(ROOT / "reports/build-manifest.json")
    for name, expected in build["files"].items():
        assert hashlib.sha256((ROOT / name).read_bytes()).hexdigest() == expected, name
    assert (ROOT.parent / "1031怪物受击死亡演示.cmd").is_file()
    passed("build_hashes_dependencies_and_launcher", files=len(build["files"]))
    catalog = load(ROOT / "content/monsters.json")
    assert len(catalog["monsters"]) == 2070
    assert sum(bool(r["states"].get("death", {}).get("tracks")) for r in catalog["monsters"]) == 357
    passed("all_monster_catalog_and_explicit_death_binding")
    result = subprocess.run([str(ROOT / "monster_demo.exe"), "--verify", "--report", str(out / "frames")], timeout=180)
    assert result.returncode == 0, (out / "frames/error.json").read_text("utf-8")
    frames = load(out / "frames/verification.json")
    assert frames["ok"] and len(frames["cases"]) == 6
    assert frames["rendered_main_animation_frames"] >= 40
    assert not frames["unconsumed_render_nodes"]
    passed("real_sdl_frame_rendering", monsters=6, main_frames=frames["rendered_main_animation_frames"])
    placeholder = next(r for r in frames["cases"] if r["id"] == 59001)
    assert not placeholder["bindings"]["death"]["available"]
    assert "transparent placeholders" in placeholder["bindings"]["death"]["error"]
    passed("transparent_source_placeholder_diagnosed_instead_of_empty_playback")
    shared = load(out / "frames/shared-death-verification.json")
    assert shared["ok"] and len(shared["cases"]) == 4
    for row in shared["cases"]:
        assert row["frozen_pose_stable"] and row["white_changes_source"] and row["seek_deterministic"] and row["completed"]
        assert row["profile"]["frozen"]["state"] == "damage1"
    cat = next(r for r in shared["cases"] if r["id"] == 5001)
    assert cat["profile"]["piece_image"] == "monster/common/m0009.img" and cat["profile"]["pieces"]
    boss = next(r for r in shared["cases"] if r["id"] == 61491)
    assert not boss["profile"]["pieces"] and boss["profile"]["raw"][2] & 1
    passed("shared_death_current_pose_hold_seek_reset_facing_and_per_monster_piece_flags", monsters=4)
    # Inspect actual rendered pixels: white body keeps the source silhouette,
    # and does not produce an opaque rectangular sprite background.
    with Image.open(out / "frames/5001-shared-white.png") as image:
        crop = image.convert("RGB").crop((500,230,1100,550))
        white_mask = Image.new("L", crop.size)
        white_mask.putdata([255 if min(rgb)>245 else 0 for rgb in crop.getdata()])
        box = white_mask.getbbox()
        assert box
        pixels = sum(v>0 for v in white_mask.getdata())
        area = (box[2]-box[0])*(box[3]-box[1])
        assert 1500<pixels<area*.85, (pixels, area)
    passed("white_silhouette_visible_and_transparent_holes_preserved", white_pixels=pixels, bounding_area=area)
    reads = load(out / "frames/resource-reads.json")
    assert not reads["archive_index_errors"] and reads["npk"]
    passed("source_npk_decoding_and_no_archive_index_errors", npk_reads=len(reads["npk"]))
    states = {e["state"] for e in frames["events"] if e["event"] == "action_started"}
    assert {"damage1", "damage2", "death"}.issubset(states)
    assert any(e["event"] == "action_rejected" and e["result"] == "dead" for e in frames["events"])
    assert any(e["event"] == "action_rejected" and e["result"] == "death" for e in frames["events"])
    passed("sdl_keyboard_mouse_reset_death_gates_seek_and_missing_state_diagnostics")
    # Use the normal visible window to exercise its real wall-clock playback.
    result = subprocess.run([str(ROOT / "monster_demo.exe"), "--id", "61491", "--smoke", "7", "--report", str(out / "smoke")], timeout=60)
    assert result.returncode == 0
    smoke = load(out / "smoke/run.json")
    started = [e["state"] for e in smoke["events"] if e["event"] == "action_started"]
    assert started == ["damage1", "damage2", "death"], started
    assert smoke["state"] == "death" and smoke["completed"]
    assert smoke["time_ms"] == smoke["bindings"]["death"]["duration_ms"]
    assert sum(e["event"] == "action_completed" and e["state"] == "death" for e in smoke["events"]) == 1
    assert (out / "smoke/smoke-damage.png").stat().st_size > 10000
    assert (out / "smoke/smoke-death.png").stat().st_size > 10000
    passed("normal_window_full_sequence_and_stable_completed_time", sequence=started, wall_ms=smoke["wall_ms"])
    result = subprocess.run([str(ROOT / "monster_demo.exe"), "--smoke", "8", "--report", str(out / "shared-smoke")], timeout=60)
    assert result.returncode == 0
    ordinary = load(out / "shared-smoke/run.json")
    assert ordinary["shared_active"] and ordinary["completed"] and ordinary["state"] == "death"
    assert ordinary["time_ms"] == ordinary["duration_ms"] == 3220
    assert ordinary["shared_death"]["frozen"]["state"] == "damage1"
    assert ordinary["shared_death"]["piece_image"] == "monster/common/m0009.img"
    passed("default_cat_normal_window_shared_death_sequence", wall_ms=ordinary["wall_ms"])
    wrong = out / "wrong-client"
    wrong.mkdir()
    (wrong / "Script.pvf").write_bytes(b"wrong version test fixture")
    result = subprocess.run([str(ROOT / "monster_demo.exe"), "--verify", "--client", str(wrong), "--report", str(out / "version-rejected")], timeout=30)
    assert result.returncode == 1
    assert "version mismatch" in load(out / "version-rejected/error.json")["error"]
    passed("wrong_version_rejected_before_resource_load")
    report = dict(ok=True, checks=checks, checks_passed=len(checks), report_directory=str(out),
                  exe_sha256=hashlib.sha256((ROOT / "monster_demo.exe").read_bytes()).hexdigest(),
                  scope="Six resource examples plus four shared-death cases and generic controls; not all monsters or native controller/pixel/timing parity")
    (ROOT / "reports/delivery-verification.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", "utf-8")
    relative = out.relative_to(ROOT / "reports").as_posix()
    markdown = ("# 1031 怪物动画 Demo 验证\n\n"
                f"交付检查通过。已实际检查巨灵布鲁、伪装树魔、首领萨斯、杰诺、猫妖、拉宾特的灵魂六个案例，合计{frames['rendered_main_animation_frames']}个可用基础动画帧。拉宾特的灵魂死亡动作引用透明占位图，已禁用并显示诊断。\n\n"
                "通用死亡另检查猫妖、哥布林、首领萨斯、巨灵布鲁四个案例：当前受击姿态定格、白色轮廓透明区域、原始石块、禁止碎块标志、确定性时间轴、镜像朝向、死亡完成与复活清理。默认猫妖和独立末尾动作都通过真实可见窗口自动播放。通用效果时序/弹道属于重建预览参数。\n\n"
                f"- [机器验证记录](delivery-verification.json)\n"
                f"- [逐帧与状态记录]({relative}/frames/verification.json)\n"
                f"- [正常窗口运行记录]({relative}/smoke/run.json)\n"
                f"- [通用死亡验证]({relative}/frames/shared-death-verification.json)\n"
                f"- [白色定格]({relative}/frames/5001-shared-white.png)\n"
                f"- [石块飞散]({relative}/frames/5001-shared-flight.png)\n"
                f"- [受击截图]({relative}/smoke/smoke-damage.png)\n"
                f"- [死亡截图]({relative}/smoke/smoke-death.png)\n\n"
                "2,070个定义可供选择、357个配置含独立末尾动作，仅表示数据覆盖；不是所有怪物运行验收。原版伤害、脚本与完整死亡流程不在此次演示验证范围。\n")
    (ROOT / "reports/VERIFICATION.md").write_text(markdown, "utf-8")
    print(json.dumps(report, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
