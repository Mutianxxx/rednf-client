"""Create a source-only collaboration package without client or local state."""
from __future__ import annotations

from datetime import datetime, timezone
from pathlib import Path
import hashlib
import json
import re
import shutil
import zipfile


ROOT = Path(__file__).resolve().parents[1]
WORKSPACE = ROOT.parent
OUTPUT_ROOT = WORKSPACE / "delivery"
PACKAGE_NAME = "dnf-cpp-collaboration-20261103"

PROJECT_FILES = (
    ".gitignore", "CMakeLists.txt", "Build-And-Test.cmd", "Play.cmd",
    "Run-From-Source.cmd",
)
PROJECT_DIRS = ("cmake", "docs", "include", "licenses", "src", "tests")
TOOL_FILES = (
    "tools/build.py", "tools/inspect.cpp", "tools/verify_architecture.py",
    "tools/legacy/package_playable.py", "tools/legacy/README.md",
)
THIRD_PARTY_DIRS = (
    "third_party/SDL2-2.32.10", "third_party/squirrel-3.1-dnf",
    "third_party/zlib-1.3.1", "third_party/native-contracts",
)
THIRD_PARTY_FILES = (
    "third_party/dependencies.lock.json", "third_party/json.hpp",
    "third_party/stb_image_write.h", "third_party/stb_truetype.h",
    "third_party/stb_vorbis.c",
)
REFERENCE_DOCS = (
    "COMBAT-REDNF.md", "FIGHTER.md", "FIGHTER-COVERAGE.md",
    "FIGHTER-GRAB.md", "FIGHTER-VISUAL-MAPPING.md", "MONSTER.md", "RENDER.md",
)
LOCAL_PATH_PATTERNS = (
    (re.compile(r"(?i)D:\\dnf-rebuild\\DNF1031[^\\\s`<>\"']*(?:\\[^\s`<>\"']*)?"),
     "<LOCAL_1031_CLIENT>"),
    (re.compile(r"(?i)D:\\dnf-rebuild\\dnf-c\+\+-project\\knowledge\\archive\\40jp-reverse-source(?:\\[^\s`<>\"']*)?"),
     "<LOCAL_AUTHORIZED_40JP_ARCHIVE>"),
)


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def copy_file(source: Path, target: Path) -> None:
    if not source.is_file():
        raise FileNotFoundError(source)
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, target)


def copy_tree(relative: str, destination: Path) -> None:
    source = ROOT / relative
    if not source.is_dir():
        raise FileNotFoundError(source)
    for path in sorted(source.rglob("*")):
        if not path.is_file() or "__pycache__" in path.parts or path.suffix == ".pyc":
            continue
        target = destination / path.relative_to(ROOT)
        copy_file(path, target)


def write_text(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content.replace("\n", "\r\n"), encoding="utf-8", newline="")


def package_readme() -> str:
    return """# DNF C++ Collaboration Package

This is a source and engineering-documentation package for the independent C++17/SDL2 project. It is not a playable release and does not contain client data.

Start with `PROJECT-STATUS.md`, `MODULE-MAP.md`, `CONTRIBUTING.md`, and `BUILDING.md`. The skill behavior-family note is `project/docs/SKILL-BEHAVIOR-FAMILIES-40JP.md`. Runtime source is under `project/src/`; public headers are under `project/include/`; tests are under `project/tests/`.

The archive intentionally omits the original DNF client, Script.pvf, NPK files, user saves, build/cache directories, previous playable candidates, and the complete raw 40JP reverse-source archive and ARAD.exe. The `knowledge/` folder contains the architecture outline and this package's source/evidence boundaries only.

Project license status is unresolved. See `LICENSE-STATUS.md` before public hosting or redistribution. Third-party notices remain under `project/licenses/` and inside the relevant dependency directories.

Package manifest and SHA256 list: `DELIVERY-MANIFEST.json`, `SHA256SUMS.txt`.
"""


def portable_build_cmd() -> str:
    return """@echo off
setlocal
cd /d "%~dp0"
set "TEMP=%~dp0cache\build-tmp"
set "TMP=%TEMP%"
set "TMPDIR=%TEMP%"
if not exist "%TEMP%" mkdir "%TEMP%"
if defined PYTHON_EXE (
  "%PYTHON_EXE%" -X utf8 -B tools\build.py %*
  exit /b %errorlevel%
)
where py >nul 2>nul
if not errorlevel 1 (
  py -3.11 -X utf8 -B tools\build.py %*
  exit /b %errorlevel%
)
python -X utf8 -B tools\build.py %*
exit /b %errorlevel%
"""


def make_profile() -> str:
    return json.dumps({
        "profileId": "cpp-collaboration-1031-local",
        "pvfPath": "C:\\DNF1031_CLIENT\\Script.pvf",
        "resourceRoots": ["C:\\DNF1031_CLIENT"],
        "textEncoding": "CP936",
        "parserVersion": "dnf-source-v1",
        "compatibilityProfileId": "1031-v1",
        "ruleProfileId": "beta-foundation-v1",
    }, ensure_ascii=False, indent=2) + "\n"


def main() -> None:
    output = OUTPUT_ROOT / PACKAGE_NAME
    archive = OUTPUT_ROOT / f"{PACKAGE_NAME}.zip"
    if output.exists() or archive.exists():
        raise FileExistsError(f"Refusing to replace existing delivery output: {output} or {archive}")
    OUTPUT_ROOT.mkdir(parents=True, exist_ok=True)
    output.mkdir()
    project = output / "project"
    knowledge = output / "knowledge"
    project.mkdir()

    for name in PROJECT_FILES:
        copy_file(ROOT / name, project / name)
    for relative in PROJECT_DIRS:
        copy_tree(relative, project)
    for name in TOOL_FILES:
        copy_file(ROOT / name, project / name)
    for relative in (*THIRD_PARTY_DIRS,):
        copy_tree(relative, project)
    for name in THIRD_PARTY_FILES:
        copy_file(ROOT / name, project / name)

    write_text(project / "build.cmd", portable_build_cmd())
    write_text(project / "content-profile.json", make_profile())
    write_text(project / "toolchain.local.json.example", json.dumps({
        "toolchain_root": "C:\\dnf-toolchain",
        "client_root": "C:\\DNF1031_CLIENT",
    }, indent=2) + "\n")
    write_text(project / ".gitignore", "/cache/\n/build/\n/saves/\n/reports/\n/checkpoints/\n"
               "toolchain.local.json\n__pycache__/\n*.pyc\n")
    write_text(project / "AGENTS.md", """# Project Contributor Entry

Read package-root `CONTRIBUTING.md`, `MODULE-MAP.md`, `REFERENCE-BOUNDARIES.md`, and `BUILDING.md` before changing source. Current implementation scope is in package-root `PROJECT-STATUS.md`; the target OO architecture is in `../knowledge/architecture/ARCHITECTURE-REFACTOR-OUTLINE.md`.

Keep original source data and platform-neutral PVF semantics intact. Do not add client assets, PVF/NPK, user saves, raw reverse-source archives, cache, or generated candidates to the shared repository. Keep C++ simulation free of SDL and register every implementation source in `cmake/source-ownership.json`.
""")
    write_text(project / "MIGRATION.md", """# Independent Project Migration State

This project is an independent C++17/SDL2 migration from the verified `mage-upper457` source baseline. The original project and source archives remain separate and are not compiled into this project. A0-A2a introduced module ownership records, `GameApplication`, `CharacterPresentation`/`ICharacterDrawSink`, bounded frame statistics, isolated build paths, and source ownership checks.

This is a staged migration. `dnf_core` remains one link archive, `World` retains legacy mutable state, `Renderer` retains some high-level presentation paths, and UI command/read-model boundaries are incomplete. The directory layout must not be presented as fully decoupled architecture. See `docs/REFACTOR-NODE-A0-A2a.md` and package-root `PROJECT-STATUS.md`.
""")
    write_text(project / "README.md", """# DNF C++ Project Source

Build and contribution instructions are in the package root. This directory contains the game source, tests, vendored dependencies, and local-only build entry points.

Before building, copy `toolchain.local.json.example` to `toolchain.local.json` and fill local paths. Edit `content-profile.json` for a local read-only 1031 client. Do not commit either machine-specific file.

`Play.cmd` runs only a locally built executable and uses `saves/refactor/`. This package contains no prebuilt game executable or client resources.
""")
    write_text(project / "CURRENT_TASK.md", "# Collaboration Snapshot\n\nSee package-root `PROJECT-STATUS.md`. Current source evidence and module ownership are documented under `docs/`.\n")

    copy_file(WORKSPACE / "knowledge" / "architecture" / "ARCHITECTURE-REFACTOR-OUTLINE.md",
              knowledge / "architecture" / "ARCHITECTURE-REFACTOR-OUTLINE.md")
    write_text(knowledge / "INDEX.md", """# Shared Knowledge Index

This delivery package includes the architecture outline and selected 40JP/1031 analysis notes. It does not include the user's offline PVF knowledge libraries, original clients, PVF/NPK data, the raw 40JP reverse-source project, or ARAD.exe.

Read `../MODULE-MAP.md` and `../REFERENCE-BOUNDARIES.md` before changing code. Selected 40JP-derived notes are in `../project/docs/reference-40jp/`; they are cross-version structural evidence, not proof of 1031 behavior.
""")

    reference_root = project / "docs" / "reference-40jp"
    source_reports = ROOT / "reports" / "40jp-deep-merge"
    for name in REFERENCE_DOCS:
        content = (source_reports / name).read_text(encoding="utf-8")
        for pattern, replacement in LOCAL_PATH_PATTERNS:
            content = pattern.sub(replacement, content)
        if re.search(r"(?i)D:\\dnf-rebuild\\", content):
            raise ValueError(f"Local workspace path remains in selected reference: {name}")
        write_text(reference_root / name, content)
    write_text(reference_root / "README.md", """# Selected 40JP/1031 Reference Notes

These notes summarize selected structural research used by the project. The original reverse-source archive and target client bytes are intentionally not distributed here. Local member paths in source evidence are represented by placeholders. Confirm source version, target consumer and current PVF bytes before applying any behavior.

`FIGHTER-COVERAGE.md` is a source/adapter ledger, not a completion percentage. `FIGHTER-VISUAL-MAPPING.md` and `COMBAT-REDNF.md` retain cross-version and inference boundaries.

The shared skill behavior-family model is documented in `../SKILL-BEHAVIOR-FAMILIES-40JP.md`; it separates observed 40JP call sites from hypotheses and implementation guidance.
""")

    generated_docs = {
        "README.md": package_readme(),
        "MODULE-MAP.md": (ROOT / "docs" / "MODULE-MAP.md").read_text(encoding="utf-8").replace(
            "](SKILL-BEHAVIOR-FAMILIES-40JP.md)",
            "](project/docs/SKILL-BEHAVIOR-FAMILIES-40JP.md)"),
        "CONTRIBUTING.md": (ROOT / "docs" / "CONTRIBUTING.md").read_text(encoding="utf-8"),
        "BUILDING.md": (ROOT / "docs" / "BUILDING-SHARED.md").read_text(encoding="utf-8"),
        "REFERENCE-BOUNDARIES.md": (ROOT / "docs" / "REFERENCE-BOUNDARIES.md").read_text(encoding="utf-8"),
        "LICENSE-STATUS.md": (ROOT / "docs" / "LICENSE-STATUS.md").read_text(encoding="utf-8"),
        "PROJECT-STATUS.md": (ROOT / "docs" / "PROJECT-STATUS.md").read_text(encoding="utf-8"),
        "PROGRESS.md": """# Collaboration Package Snapshot

Package snapshot date: 2026-11-03. The current C++ source and evidence boundary is summarized in `PROJECT-STATUS.md`. The source-only package intentionally has no playable executable, PVF/NPK assets, runtime save, or build output.

For a new contribution, read `CONTRIBUTING.md` and `MODULE-MAP.md`. For a build, follow `BUILDING.md` and provide local client/toolchain paths without committing them.
""",
    }
    for name, content in generated_docs.items():
        write_text(output / name, content)

    rows = []
    for path in sorted(output.rglob("*")):
        if path.is_file():
            rows.append({"path": path.relative_to(output).as_posix(),
                         "size": path.stat().st_size, "sha256": sha256(path)})
    manifest = {
        "schema": 1,
        "package": PACKAGE_NAME,
        "created_utc": datetime.now(timezone.utc).isoformat(),
        "package_kind": "source-and-documentation-only",
        "game_executable_included": False,
        "client_resources_included": False,
        "raw_40jp_reverse_archive_included": False,
        "license_status": "project-license-not-specified",
        "file_count_before_manifest": len(rows),
        "bytes_before_manifest": sum(row["size"] for row in rows),
        "files": rows,
        "excluded": ["original DNF client", "Script.pvf", "NPK/image packs", "ARAD.exe",
                     "raw 40JP reverse source archive", "user saves", "build/cache", "playable candidates",
                     "local toolchain configuration", "local runtime reports"],
    }
    (output / "DELIVERY-MANIFEST.json").write_text(
        json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    checksum_lines = []
    for path in sorted(output.rglob("*")):
        if path.is_file() and path.name != "SHA256SUMS.txt":
            checksum_lines.append(f"{sha256(path)}  {path.relative_to(output).as_posix()}")
    write_text(output / "SHA256SUMS.txt", "\n".join(checksum_lines) + "\n")

    with zipfile.ZipFile(archive, "x", compression=zipfile.ZIP_DEFLATED, compresslevel=9) as zipped:
        for path in sorted(output.rglob("*")):
            if path.is_file():
                zipped.write(path, f"{PACKAGE_NAME}/{path.relative_to(output).as_posix()}")
    print(json.dumps({"directory": str(output), "archive": str(archive),
                      "files": sum(1 for path in output.rglob("*") if path.is_file()),
                      "source_bytes": sum(path.stat().st_size for path in output.rglob("*") if path.is_file()),
                      "archive_bytes": archive.stat().st_size,
                      "archive_sha256": sha256(archive)}, ensure_ascii=False))


if __name__ == "__main__":
    main()
