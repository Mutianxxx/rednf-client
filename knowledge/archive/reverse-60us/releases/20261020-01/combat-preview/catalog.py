"""Source-bound class, skill and animation catalog for the current 60US PVF.

Controllers deliberately remain unknown until evidence from this client's EXE
binds a skill/state to its motion, attack information and spawned objects.
"""
from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path, PurePosixPath
import sys
from typing import Any

_ANALYSIS = Path(__file__).resolve().parent.parent / "analysis"
if str(_ANALYSIS) not in sys.path:
    sys.path.insert(0, str(_ANALYSIS))
from pvf60 import Pvf60
from pvf_model import Document, listing_rows, node_record, parse_animation, parse_document
from string_names import StringNames


def normalize_path(path: str) -> str:
    return path.replace("\\", "/").lower()


def resolve_relative(owner: str, path: str) -> str:
    # PVF scripts use paths relative to their owning CHR/SKL directory here.
    return normalize_path(str(PurePosixPath(owner).parent / path.replace("\\", "/")))


class Catalog:
    def __init__(self, pvf_path: str | Path):
        self.pvf = Pvf60(pvf_path)
        self.source = dict(path=str(self.pvf.path.resolve()), size=len(self.pvf.data),
                           sha256=hashlib.sha256(self.pvf.data).hexdigest(),
                           header=self.pvf.header)
        self._documents: dict[str, Document] = {}
        self.string_names = StringNames(self.pvf, self.source['sha256'])
        self.characters: list[dict[str, Any]] = []
        self.skills: list[dict[str, Any]] = []
        self.warnings: list[dict[str, Any]] = []
        self.character_registration_path = "character/character.usa.lst"
        self.skill_registration_path = "skill/skilllist.usa.lst"
        self._build()

    def document(self, path: str) -> Document:
        path = normalize_path(path)
        if path not in self._documents:
            self._documents[path] = parse_document(self.pvf.read(path), path)
        return self._documents[path]

    def identity(self, path: str, *, document: Document | None = None) -> dict[str, Any]:
        path = normalize_path(path)
        entry = dict(self.pvf.by_path[path])
        document = document or self._documents.get(path)
        digest = document.sha256 if document is not None else hashlib.sha256(self.pvf.read(path)).hexdigest()
        entry.update(sha256=digest, encoding="cp949",
                     crc_verified=True, archive_sha256=self.source["sha256"])
        return entry

    def _build(self) -> None:
        chr_doc = self.document(self.character_registration_path)
        skl_doc = self.document(self.skill_registration_path)
        registrations = listing_rows(chr_doc)
        skill_lists = listing_rows(skl_doc)
        lists_by_class = {r["id"]: r for r in skill_lists}
        for registration in registrations:
            class_id = registration["id"]
            path = normalize_path("character/"+registration["path"])
            document = self.document(path)
            slots = []
            fields = []
            for node in document.events:
                # Resource extension tests classify literal CHR references only.
                # They do not bind these references to a skill controller.
                name = node.name.lower()
                resource_field = "motion" in name or name in ("attack info", "etc attack info",
                                                               "jumpattack info", "dashattack info")
                slot_values = [token for token in node.values if token.kind == "string"
                               and (resource_field or token.text.lower().endswith((".ani", ".atk")))]
                if not slot_values:
                    continue
                field = node_record(node)
                field["slot_count"] = len(slot_values)
                fields.append(field)
                for index, token in enumerate(slot_values):
                    resource = resolve_relative(path, token.text) if token.text else None
                    kind = "animation" if "motion" in name or (resource and resource.endswith(".ani")) else "attack_info"
                    slots.append(dict(tag=node.name, index=index, path=resource,
                                      source_path=token.text, empty=not token.text,
                                      exists=resource in self.pvf.by_path if resource else False,
                                      source_token=token.to_dict(),
                                      field_start=node.start, scope=list(node.scope),
                                      kind=kind))
            item = dict(class_id=class_id, label=PurePosixPath(registration["path"]).stem,
                        path=path, source=self.identity(path, document=document),
                        registration=registration, registration_source=self.identity(self.character_registration_path),
                        slots=slots, resource_fields=fields, warnings=document.warnings,
                        controller_status="unknown")
            self.characters.append(item)
            if class_id not in lists_by_class:
                self.warnings.append(dict(kind="no_skill_registration_for_class", class_id=class_id))
                continue
            list_registration = lists_by_class[class_id]
            list_path = normalize_path("skill/"+list_registration["path"])
            list_document = self.document(list_path)
            item["skill_list_path"] = list_path
            item["skill_list_source"] = self.identity(list_path, document=list_document)
            item["skill_list_registration"] = list_registration
            rows = listing_rows(list_document)
            item["registered_skill_count"] = len(rows)
            for order, row in enumerate(rows):
                skill_path = resolve_relative(list_path, row["path"])
                skill = dict(class_id=class_id, class_label=item["label"], skill_id=row["id"],
                             list_order=order, path=skill_path, registration=row,
                             registration_source=self.identity(list_path, document=list_document),
                             controller_status="unknown", controller_evidence=[],
                             animation_binding_status="unknown", attack_binding_status="unknown",
                             hit_acceptance_status="unknown", source_exists=skill_path in self.pvf.by_path)
                if skill["source_exists"]:
                    skill_document = self.document(skill_path)
                    fields = [node_record(n) for n in skill_document.events]
                    skill.update(source=self.identity(skill_path, document=skill_document),
                                 fields=fields, warnings=skill_document.warnings,
                                 type_fields=[node_record(n) for n in skill_document.find("type")],
                                 name_fields=[node_record(n) for n in skill_document.find("name")],
                                 name2_fields=[node_record(n) for n in skill_document.find("name2")],
                                 static_data=[node_record(n) for n in skill_document.find("static data")],
                                 level_info=[node_record(n) for n in skill_document.find("level info")],
                                 mode_blocks=[n.to_dict() for n in skill_document.nodes
                                              if n.name.lower() in ("dungeon", "pvp", "death tower", "warroom")])
                    primary = self.string_names.resolve(skill['name_fields'])
                    secondary = self.string_names.resolve(skill['name2_fields'])
                    skill.update(display_name=primary['text'] or PurePosixPath(skill_path).stem,
                                 secondary_name=secondary['text'], name_resolution=primary,
                                 name2_resolution=secondary,
                                 icon_fields=[node_record(n) for n in skill_document.find('icon')])
                self.skills.append(skill)

    def animation(self, path: str) -> dict[str, Any]:
        path = normalize_path(path)
        animation = parse_animation(self.pvf.read(path), path)
        animation["source"] = self.identity(path)
        return animation

    def summary(self) -> dict[str, Any]:
        archive_skills = {e["path"] for e in self.pvf.entries if e["path"].endswith(".skl")}
        registered = {s["path"] for s in self.skills}
        counts = collections.Counter(s["controller_status"] for s in self.skills)
        types = collections.Counter(str(n["values"]) for s in self.skills for n in s.get("type_fields", []))
        missing_slots = [dict(class_id=c["class_id"], tag=s["tag"], index=s["index"], path=s["path"])
                         for c in self.characters for s in c["slots"] if not s["exists"] and not s["empty"]]
        return dict(source=self.source, class_count=len(self.characters),
                    classes=[dict(class_id=c["class_id"], label=c["label"], path=c["path"],
                                  registered_skill_count=c["registered_skill_count"],
                                  animation_slots=sum(s["kind"] == "animation" for s in c["slots"]),
                                  attack_info_slots=sum(s["kind"] == "attack_info" for s in c["slots"]),
                                  empty_slots=sum(s["empty"] for s in c["slots"]))
                             for c in self.characters],
                    registered_skill_rows=len(self.skills), registered_distinct_skill_paths=len(registered),
                    archive_skill_files=len(archive_skills),
                    unregistered_skill_files=sorted(archive_skills-registered),
                    missing_registered_skills=[s["path"] for s in self.skills if not s["source_exists"]],
                    controller_status=dict(counts), type_field_counts=dict(types),
                    skill_name_status=dict(collections.Counter(s.get('name_resolution', {}).get('status', 'missing-source') for s in self.skills)),
                    missing_chr_slots=missing_slots,
                    parsed_document_count=len(self._documents),
                    parse_warnings=[dict(path=p, **w) for p, d in self._documents.items() for w in d.warnings],
                    warnings=self.warnings,
                    evidence_boundary="PVF registration and ordered resource slots only; skill controllers, hit rules and runtime behavior unknown")

    def export(self, directory: str | Path) -> dict[str, Any]:
        target = Path(directory)
        target.mkdir(parents=True, exist_ok=True)
        def write(name: str, value: Any) -> None:
            (target/name).write_text(json.dumps(value, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
        summary = self.summary()
        write("summary.json", summary)
        write("characters.json", self.characters)
        write("skills.json", self.skills)
        write("document-index.json", [self.identity(p, document=d) for p, d in self._documents.items()])
        with (target/"skill-coverage.csv").open("w", encoding="utf-8-sig", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=["class_id", "class_label", "skill_id", "path",
                                                        "type", "name_token", "controller_status",
                                                        "animation_binding_status", "attack_binding_status",
                                                        "hit_acceptance_status", "source_sha256"])
            writer.writeheader()
            for skill in self.skills:
                writer.writerow({key: skill[key] for key in ("class_id", "class_label", "skill_id", "path",
                                                             "controller_status", "animation_binding_status",
                                                             "attack_binding_status", "hit_acceptance_status")}
                                | dict(type=" | ".join(str(v) for f in skill.get("type_fields", []) for v in f["values"]),
                                       name_token=" | ".join(str(v) for f in skill.get("name_fields", []) for v in f["values"]),
                                       source_sha256=skill.get("source", {}).get("sha256", "")))
        return summary


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvf", default=str(Path(__file__).resolve().parent.parent/"DFO"/"Script.pvf"))
    parser.add_argument("--out", default=str(_ANALYSIS/"combat_catalog"))
    parser.add_argument("--animation", action="append", default=[])
    args = parser.parse_args()
    catalog = Catalog(args.pvf)
    summary = catalog.export(args.out)
    for path in args.animation:
        animation = catalog.animation(path)
        target = Path(args.out)/(normalize_path(path).replace("/", "__")+".json")
        target.write_text(json.dumps(animation, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
    print(json.dumps(summary, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
