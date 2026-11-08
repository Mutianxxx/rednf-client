"""Read-only, offline corpus inventory. Never imports or executes corpus code.

The full-byte census and text extraction are machine coverage, not a claim of
semantic review or proof of the target client's behavior. Sources stay intact.
"""
from pathlib import Path
from collections import Counter, defaultdict
from datetime import datetime, timezone
from html.parser import HTMLParser
import argparse
import hashlib
import json
import re
import zipfile
import xml.etree.ElementTree as ET

WORKSPACE = Path(__file__).resolve().parents[2]
TEXT_SUFFIXES = set(".md .txt .nut .c .json .ani .act .stk .mob .skl .equ .atk .etc .map .py .js .yml .yaml .als .lay .obj .bat .gitignore .dgn .ps1 .chr .tbl .html .gitattributes .sh .css .dockerignore .mm .npc .ptl .ui .shp .til .twn .wdm .pet .qst .dl".split())


class ArticleText(HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.parts = []
        self.hidden = 0

    def handle_starttag(self, tag, attrs):
        if tag in ("script", "style"):
            self.hidden += 1
        if tag in ("p", "div", "br", "li", "tr", "pre", "h1", "h2", "h3", "h4"):
            self.parts.append("\n")
        if tag == "img":
            self.parts.append("[image: " + dict(attrs).get("src", "") + "]")

    def handle_endtag(self, tag):
        if tag in ("script", "style"):
            self.hidden = max(0, self.hidden - 1)
        if tag in ("p", "div", "li", "tr", "pre"):
            self.parts.append("\n")

    def handle_data(self, data):
        if not self.hidden:
            self.parts.append(data)

    def text(self):
        return re.sub(r"\n[ \t]*\n(?:[ \t]*\n)+", "\n\n", "".join(self.parts)).strip()


def digest(data):
    return hashlib.sha256(data).hexdigest()


def decode(data):
    encodings = ["utf-16"] if data.startswith((b"\xff\xfe", b"\xfe\xff")) else ["utf-8-sig", "cp949", "gb18030"]
    for encoding in encodings:
        try:
            result = data.decode(encoding, errors="strict")
        except UnicodeError:
            continue
        if "\x00" not in result:
            return result, encoding
    return None, None


def domain(path):
    if any(term in path.lower() for term in ("ui", "界面", "npk", "imagepacks")):
        return "ui-resources"
    if any(term in path.lower() for term in ("技能", "skill", "nut", "sqr/", "ani", "act", "atk", "lay")):
        return "skills-actions-scripts"
    if any(term in path for term in ("装备", "时装", "附魔")):
        return "equipment"
    if any(term in path for term in ("地图", "城镇", "任务", "怪物", "宠物", "CHR", "MAP", "MOB")):
        return "world-units-quests"
    if any(term in path for term in ("物品", "商店", "STK", "SHO", "活动", "掉落")):
        return "items-economy"
    return "general-format-tools"


def extract(path, data):
    if not data:
        return "empty", "", None
    if path.suffix.lower() == ".xlsx":
        with zipfile.ZipFile(path) as archive:
            parts = []
            for name in sorted(archive.namelist()):
                if name.startswith("xl/") and name.endswith(".xml"):
                    root = ET.fromstring(archive.read(name))
                    parts.extend(node.text for node in root.iter() if node.text)
        return "xlsx-xml-extracted", "\n".join(parts), "XML in ZIP"
    if path.suffix.lower() not in TEXT_SUFFIXES and path.suffix:
        return "binary-indexed", None, None
    value, encoding = decode(data)
    if value is None:
        return "undecoded-indexed", None, None
    if path.suffix.lower() == ".json":
        payload = json.loads(value)
        if isinstance(payload, dict) and isinstance(payload.get("content"), str):
            parser = ArticleText()
            parser.feed(payload["content"])
            # Title stays independently traceable; no content is executed.
            title = str(payload.get("title", path.stem))
            return "json-article-extracted", title + "\n" + parser.text(), encoding
    return "text-extracted", value, encoding


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=WORKSPACE / "dnf-部分知识库")
    parser.add_argument("--output", type=Path, default=WORKSPACE / "dnf-native-demo/reports/knowledge-base-audit/corpus")
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if not source.is_dir() or not source.is_relative_to(WORKSPACE):
        parser.error("Source must be a workspace directory")
    if not output.is_relative_to(WORKSPACE) or output.is_relative_to(source) or source.is_relative_to(output):
        parser.error("Output must be separate from the source and inside this workspace")
    output.mkdir(parents=True, exist_ok=True)
    files, documents, problems = [], {}, []
    counts, extensions, roots, encodings = Counter(), Counter(), Counter(), Counter()
    text_characters = 0
    for path in sorted(p for p in source.rglob("*") if p.is_file()):
        if path.is_symlink():
            raise RuntimeError("Refuse corpus symlink: " + str(path))
        data = path.read_bytes()
        relative = path.relative_to(source).as_posix()
        row = {"path": relative, "sha256": digest(data), "bytes": len(data)}
        try:
            status, content, encoding = extract(path, data)
        except Exception as error:
            status, content, encoding = "extraction-error", None, None
            problems.append({"path": relative, "error": str(error)})
        row.update(status=status, encoding=encoding, domain=domain(relative))
        if encoding in ("cp949", "gb18030"):
            candidates = []
            for candidate in ("cp949", "gb18030", "cp932", "cp950"):
                try:
                    decoded = data.decode(candidate, errors="strict")
                except UnicodeError:
                    continue
                if "\x00" not in decoded:
                    candidates.append(candidate)
            row["encoding_candidates"] = candidates
            row["encoding_evidence"] = "strict-decoding candidate only; language/version review required"
        if content is not None:
            key = digest(content.encode("utf-8"))
            row.update(text_sha256=key, characters=len(content))
            text_characters += len(content)
            document = documents.setdefault(key, {"id": key, "sources": [], "domain": row["domain"], "text": content})
            document["sources"].append(relative)
        files.append(row)
        counts[status] += 1
        encodings[encoding or "none"] += 1
        extensions[path.suffix.lower() or "<none>"] += 1
        roots[Path(relative).parts[0]] += 1
    # Re-read every source after extraction so additions/changes cannot silently
    # borrow a previous census. This also proves this tool didn't change bytes.
    after = {p.relative_to(source).as_posix(): digest(p.read_bytes()) for p in source.rglob("*") if p.is_file()}
    if after != {row["path"]: row["sha256"] for row in files}:
        raise RuntimeError("Corpus changed during indexing")
    with (output / "reading-corpus.jsonl").open("w", encoding="utf-8", newline="\n") as stream:
        for key in sorted(documents):
            stream.write(json.dumps(documents[key], ensure_ascii=False) + "\n")
    manifest = {"schema": 1, "source": str(source), "files": files}
    (output / "source-manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    summary = {"schema": 1, "created_utc": datetime.now(timezone.utc).isoformat(), "source": str(source),
        "files": len(files), "bytes": sum(row["bytes"] for row in files), "statuses": dict(counts),
        "extensions": dict(extensions), "roots": dict(roots), "encodings": dict(encodings),
        "text_characters_before_deduplication": text_characters,
        "unique_extracted_documents": len(documents), "unique_text_characters": sum(len(d["text"]) for d in documents.values()),
        "duplicate_extracted_documents": sum(len(d["sources"]) - 1 for d in documents.values()),
        "source_unchanged_after_full_reread": True, "problems": problems,
        "coverage_kind": "all source bytes read and hashed; supported text extracted; semantic review is recorded separately",
        "executed_corpus_files": 0, "artifacts": {name: digest((output / name).read_bytes()) for name in ("source-manifest.json", "reading-corpus.jsonl")}}
    (output / "summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
