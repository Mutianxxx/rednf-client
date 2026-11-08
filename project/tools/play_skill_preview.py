"""Launch the skill previewer, locating its executable across build directories.

The previewer is a CMake target, so its binary can live in any ``cache/*-build``
directory depending on which ``--build-dir`` was last used. Resolving that here
keeps ``Play-Skill-Preview.cmd`` a three-line shell instead of a batch file full
of ``if exist`` branches, which cmd.exe mis-parses once the file contains
non-ASCII text under a non-UTF-8 code page.
"""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EXE_NAME = "dnf_skill_previewer.exe"
# Preferred order: the documented build directory first, then the directory the
# previewer was originally developed against.
PREFERRED = ("cache/refactor-build", "cache/skill-previewer-build")
REQUIRED_DLLS = ("SDL2.dll",)


def locate_executable() -> tuple[Path | None, list[str]]:
    """Return the newest usable executable and a log of what was inspected."""
    notes: list[str] = []
    candidates: list[Path] = []
    for relative in PREFERRED:
        candidate = ROOT / relative / EXE_NAME
        if candidate.is_file():
            candidates.append(candidate)
        else:
            notes.append(f"missing: {candidate.relative_to(ROOT)}")
    if not candidates:
        for candidate in sorted((ROOT / "cache").rglob(EXE_NAME)):
            if candidate.is_file():
                candidates.append(candidate)
        if candidates:
            notes.append(f"found {len(candidates)} candidate(s) by scanning cache/")
        else:
            notes.append("no executable found under cache/")
    if not candidates:
        return None, notes
    # Newest wins so a fresh incremental build is never shadowed by an old one.
    chosen = max(candidates, key=lambda item: item.stat().st_mtime)
    notes.append(f"selected {chosen.relative_to(ROOT)}")
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
        print("[skill-previewer] dnf_skill_previewer.exe was not found under cache/.", file=sys.stderr)
        print("[skill-previewer] Build it first:", file=sys.stderr)
        print("    python tools\\build.py --build-dir cache\\refactor-build", file=sys.stderr)
        return 1

    missing = [name for name in REQUIRED_DLLS if not (executable.parent / name).is_file()]
    if missing:
        print(
            f"[skill-previewer] {executable.relative_to(ROOT)} is missing runtime DLLs: "
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
    print(f"[skill-previewer] {executable.relative_to(ROOT)}")
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
