"""Export the current PVF resources named by native Monster death code.

This preserves declarations and dependency candidates. It does not implement
the particle interpreter or establish native execution from declaration alone.
"""
from collections import deque
from pathlib import Path
import hashlib
import json
import posixpath
import sys

from native60 import ROOT, OUT
sys.path.insert(0, str(ROOT / "analysis"))
sys.path.insert(0, str(ROOT / "combat-preview"))
from pvf60 import Pvf60
from pvf_model import parse_document, node_record

PVF_SHA256 = "23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98"
SEEDS = [
    (0xcc9f70, "monster/common/particle/monsterdieblood.ptl"),
    (0xcc9f08, "monster/common/particle/monsterdiebloodyoung.ptl"),
    (0xcc9eb0, "monster/common/particle/monsterdiepiece.ptl"),
    (0xcc9e48, "monster/common/particle/monsterdiepieceyoung.ptl"),
    (0xcc9dd8, "monster/common/particle/monsterdiepieceveryyoung.ptl"),
    (0xcc9d70, "monster/common/particle/monsterdieflashyoung.ptl"),
    (0xe0b228, "monster/common/particle/teen_monster_die_down_01.ptl"),
    (0xe0b1b8, "monster/common/particle/teen_monster_die_down_02.ptl"),
    (0xe0b148, "monster/common/particle/teen_monster_die_stand_01.ptl"),
    (0xe0b0d8, "monster/common/particle/teen_monster_die_stand_02.ptl"),
    (0xdf71f0, "monster/common/particle/monsterdiesmoke.ptl"),
    (0xe0b390, "monster/common/animation/monsterdieflash.ani"),
]
SUFFIXES = {".ani", ".als", ".ptl", ".act", ".atk", ".obj"}
SAMPLES = ["monster/goblin/goblin.mob", "monster/newmonsters/goblinkingdom/redgoblin/redgoblin.mob"]


def main():
    pvf = Pvf60(ROOT / "DFO/Script.pvf")
    digest = hashlib.sha256(pvf.data).hexdigest()
    if digest != PVF_SHA256:
        raise ValueError("The current PVF differs from the reviewed target")
    dest = OUT / "pvf"
    dest.mkdir(exist_ok=True)
    queue = deque(path for _, path in SEEDS)
    seen, resources, edges, images = set(), [], [], []
    while queue:
        path = queue.popleft()
        if path in seen:
            continue
        seen.add(path)
        raw = pvf.read(path)
        doc = parse_document(raw, path)
        stem = path.replace("/", "__")
        (dest / (stem + ".raw")).write_bytes(raw)
        (dest / (stem + ".utf8.txt")).write_text(doc.text, encoding="utf-8")
        resources.append({
            "path": path, "sha256": doc.sha256, "size": len(raw),
            "encoding": doc.encoding, "archive_entry": pvf.by_path[path],
            "entry_crc_verified": True,
            "raw_export": "pvf/" + stem + ".raw",
            "text_export": "pvf/" + stem + ".utf8.txt",
            "fields": [node_record(node) for node in doc.events],
            "parse_warnings": doc.warnings,
        })
        for token in doc.tokens:
            if token.kind != "string":
                continue
            value = token.text.replace("\\", "/")
            suffix = posixpath.splitext(value.lower())[1]
            if suffix == ".img":
                images.append({"source": path, "raw_token": token.to_dict()})
            if suffix not in SUFFIXES:
                continue
            relative = posixpath.normpath(posixpath.join(posixpath.dirname(path), value)).lower()
            candidates = [p for p in dict.fromkeys([relative, value.lower()]) if p in pvf.by_path]
            edge = {"source": path, "raw_token": token.to_dict(),
                    "relative_candidate": relative, "resolver_candidates": candidates,
                    "native_execution_established_by_this_edge": False}
            edges.append(edge)
            if len(candidates) == 1:
                queue.append(candidates[0])
            else:
                edge["unresolved"] = "missing" if not candidates else "ambiguous"
    samples = []
    for path in SAMPLES:
        raw = pvf.read(path)
        doc = parse_document(raw, path)
        stem = path.replace("/", "__")
        (dest / (stem + ".raw")).write_bytes(raw)
        (dest / (stem + ".utf8.txt")).write_text(doc.text, encoding="utf-8")
        samples.append({"path": path, "sha256": doc.sha256, "size": len(raw),
                        "encoding": doc.encoding, "archive_entry": pvf.by_path[path],
                        "entry_crc_verified": True,
                        "raw_export": "pvf/" + stem + ".raw", "text_export": "pvf/" + stem + ".utf8.txt",
                        "selected_fields": [node_record(node) for node in doc.events if node.name.lower() in
                                            {"die effect", "last action", "down animation", "down action"}]})
    report = {
        "schema": "60us-native-monster-death-resource-declarations-v1",
        "archive": "DFO/Script.pvf", "archive_sha256": digest,
        "native_seeds": [{"utf16le_va": hex(va), "path": path} for va, path in SEEDS],
        "resources": resources, "resource_edges": edges, "image_declarations": images,
        "sample_documents": samples,
        "resolver_policy": "Report policy only: normalize relative and archive-root candidates; enqueue a single existing match. Native path normalization is not asserted.",
        "limitations": [
            "PTL fields and dependencies are declarations; the particle VM is not recovered here.",
            "These hardcoded resources belong to CNPieceDestroyEffect and do not establish Monster last ACT playback.",
            "This is static evidence; native rendering and original-client visual equivalence are not observed.",
        ],
    }
    (OUT / "death-resources.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"resources": len(resources), "edges": len(edges),
                      "unresolved": sum("unresolved" in edge for edge in edges),
                      "image_declarations": len(images)}))


if __name__ == "__main__":
    main()
