"""Read the local PVF sample corpus without changing source bytes.

Only plain-text sources are decoded. OLE DOC and RTF stay explicitly distinct.
The directory contains mixed encodings; never silently replace undecodable bytes.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re


def source_info(path: Path) -> tuple[dict, str | None]:
    raw = path.read_bytes()
    info = {"bytes": len(raw), "sha256": hashlib.sha256(raw).hexdigest()}
    if not raw:
        return dict(info, kind="empty", encoding=None, lines=0), ""
    if raw.startswith(bytes.fromhex("d0cf11e0a1b11ae1")):
        return dict(info, kind="ole-doc", encoding=None, lines=None), None
    if raw.startswith(b"{\\rtf"):
        match = re.search(rb"\\ansicpg(\d+)", raw[:200])
        codepage = int(match[1]) if match else None
        return dict(info, kind="rtf", encoding=None, rtf_ansi_codepage=codepage,
                    lines=None), None
    if raw.isascii():
        encoding = "ascii"
    elif raw.startswith(b"\xef\xbb\xbf"):
        encoding = "utf-8-sig"
    elif path.name.lower() == "equipmentsamplebytool.equ":
        encoding = "utf-8"
    else:
        encoding = "cp949"
    decoded = raw.decode(encoding, errors="strict")
    compatible = []
    for candidate in ("utf-8", "cp949", "euc_kr"):
        try:
            raw.decode(candidate, errors="strict")
            compatible.append(candidate)
        except UnicodeError:
            pass
    return dict(info, kind="text", encoding=encoding,
                strict_decodable_as=compatible, lines=len(decoded.splitlines())), decoded


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, required=True,
                        help="Path to pvf官方文档 or its sample(官方注释) directory")
    commands = parser.add_subparsers(dest="command", required=True)
    catalog = commands.add_parser("catalog")
    catalog.add_argument("--output", type=Path,
                         help="Write JSON here; omit to print. Never target a source file.")
    show = commands.add_parser("show")
    show.add_argument("file", help="Relative file path inside the source root")
    show.add_argument("--start", type=int, default=1)
    show.add_argument("--end", type=int)
    show.add_argument("--find", help="Only show matching lines (case-insensitive text)")
    args = parser.parse_args()
    root = args.root.resolve(strict=True)
    if args.command == "catalog":
        entries = []
        for path in sorted(root.rglob("*")):
            if path.is_file():
                entry, _ = source_info(path)
                entries.append(dict(path=path.relative_to(root).as_posix(), **entry))
        result = {"schema": 1, "source_root": str(root),
                  "line_numbering": "1-based decoded text splitlines; no replacement decoding",
                  "encoding_note": "CP949 for Korean samples; UTF-8 equipment tool sample; ASCII detected first; binary formats not flattened",
                  "files": entries}
        rendered = json.dumps(result, ensure_ascii=False, indent=2) + "\n"
        if args.output:
            target = args.output.resolve()
            if target == root or root in target.parents:
                parser.error("Output must be outside the read-only source tree")
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(rendered, encoding="utf-8")
            print(f"Cataloged {len(entries)} files to {target}")
        else:
            print(rendered, end="")
    else:
        path = (root / args.file).resolve(strict=True)
        if root not in path.parents:
            parser.error("File must remain inside the source root")
        info, decoded = source_info(path)
        if decoded is None:
            parser.error(f"{info['kind']} needs a format-aware extractor, not text decoding")
        print(f"{path}\nencoding={info['encoding']} sha256={info['sha256']}")
        for number, line in enumerate(decoded.splitlines(), 1):
            if number < args.start or (args.end is not None and number > args.end):
                continue
            if args.find is not None and args.find.casefold() not in line.casefold():
                continue
            print(f"{number:4}: {line}")


if __name__ == "__main__":
    main()
