"""Launch the skill previewer, locating its executable across build directories.

The previewer is a CMake target, so its binary can live in any build directory
depending on which ``--build-dir`` was last used. Resolving that here keeps
``Play-Skill-Preview.cmd`` a three-line shell instead of a batch file full of
``if exist`` branches, which cmd.exe mis-parses once the file contains
non-ASCII text under a non-UTF-8 code page.

Search order: the repository-level ``checkpoints/build`` release directory first,
then the legacy ``project/cache/*-build`` directories.
"""
from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REPO = ROOT.parent
EXE_NAME = "dnf_skill_previewer.exe"
REQUIRED_DLLS = ("SDL2.dll",)


def display(path: Path) -> str:
    """Path relative to project/ when possible, otherwise repository-relative."""
    try:
        return path.relative_to(ROOT).as_posix()
    except ValueError:
        return os.path.relpath(path, ROOT)


def candidate_directories() -> list[Path]:
    return [REPO / "checkpoints" / "build", ROOT / "cache" / "refactor-build", ROOT / "cache" / "skill-previewer-build"]


def locate_executable() -> tuple[Path | None, list[str]]:
    """Return the newest usable executable and a log of what was inspected."""
    notes: list[str] = []
    candidates: list[Path] = []
    for directory in candidate_directories():
        candidate = directory / EXE_NAME
        if candidate.is_file():
            candidates.append(candidate)
        else:
            notes.append(f"missing: {display(candidate)}")
    if not candidates:
        for search_root in (REPO / "checkpoints", ROOT / "cache"):
            if not search_root.is_dir():
                continue
            for candidate in sorted(search_root.rglob(EXE_NAME)):
                if candidate.is_file():
                    candidates.append(candidate)
        if candidates:
            notes.append(f"found {len(candidates)} candidate(s) by scanning checkpoints/ and cache/")
        else:
            notes.append("no executable found under checkpoints/ or cache/")
    if not candidates:
        return None, notes
    # Newest wins so a fresh incremental build is never shadowed by an old one.
    chosen = max(candidates, key=lambda item: item.stat().st_mtime)
    notes.append(f"selected {display(chosen)}")
    return chosen, notes


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("--dry-run", action="store_true", help="print the command instead of running it")
    known, forwarded = parser.parse_known_args(argv)

    executable, notes = locate_executable()
    for note in notes:
        if known.dry_run:
            print(f"[skill-previewer] {note}")
    if executable is None:
        print("[skill-previewer] dnf_skill_previewer.exe was not found.", file=sys.stderr)
        print("[skill-previewer] Build it first:", file=sys.stderr)
        print("    python tools\\build.py --build-dir ..\\checkpoints\\build", file=sys.stderr)
        return 1

    missing = [name for name in REQUIRED_DLLS if not (executable.parent / name).is_file()]
    if missing:
        print(
            f"[skill-previewer] {display(executable)} is missing runtime DLLs: "
            + ", ".join(missing)
            + ". Rebuild so the POST_BUILD copy runs.",
            file=sys.stderr,
        )
        return 1

    profile = ROOT / "content-profile.json"
    if not profile.is_file():
        print(f"[skill-previewer] content-profile.json not found at {profile}", file=sys.stderr)
        return 1

    command = [
        str(executable),
        "--content-profile",
        str(profile),
        "--report-dir",
        str(ROOT / "reports" / "skill-previewer"),
        *forwarded,
    ]
    print(f"[skill-previewer] {display(executable)}")
    if known.dry_run:
        print("[skill-previewer] " + " ".join(f'"{part}"' for part in command))
        return 0

    # Run from the project root so a relative --capture path lands where the
    # caller expects it; DLL lookup still resolves the application directory
    # first, so SDL2.dll next to the executable keeps working.
    try:
        return subprocess.call(command, cwd=str(ROOT))
    except OSError as error:
        print(f"[skill-previewer] failed to launch: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
