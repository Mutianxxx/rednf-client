"""Export one source-bound ordinary HardAttack weapon-layer configuration.

Read only the current PVF. Do not infer a skill controller from resource names.
Native address claims are documented in equipment-contract.md and raw excerpts.
"""
from pathlib import Path, PurePosixPath
import hashlib
import json
import sys

ROOT = Path(__file__).resolve().parents[2]
DEST = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "analysis"))
sys.path.insert(0, str(ROOT / "combat-preview"))
from pvf60 import Pvf60
from pvf_model import parse_document, parse_animation

pvf = Pvf60(ROOT / "DFO" / "Script.pvf")
archive_hash = hashlib.sha256(pvf.data).hexdigest()
source_path = "equipment/character/swordman/weapon/club/n_club_axshauta.equ"
include_path = "equipment/character/swordman.lay"


def source(path):
    raw = pvf.read(path)
    return dict(**pvf.by_path[path.lower()], sha256=hashlib.sha256(raw).hexdigest(),
                archive_sha256=archive_hash, encoding="cp949", crc_verified=True)


equ = parse_document(pvf.read(source_path), source_path)
lay = parse_document(pvf.read(include_path), include_path)
variation = equ.find("variation")[0]
assert variation.data == [2, 6]
motion_tokens = [t for t in lay.find("etc motion")[0].values if t.kind == "string"]
template = motion_tokens[1]
assert template.value == "%s/HardAttack.ani"
records = []
for ordinal, node in enumerate(equ.find("layer variation")):
    order_token, folder_token, directive, include_token = node.values
    assert directive.value == "<include>" and include_token.value == include_path
    path = str(PurePosixPath(source_path).parent / (template.value % folder_token.value)).lower()
    ani = parse_animation(pvf.read(path), path)
    images = sorted(set(str(im[0]) for frame in ani["frames"] for im in frame["images"]))
    formatted = [im % tuple(variation.data) if "%" in im else im for im in images]
    records.append(dict(
        source_ordinal=ordinal, order_key=order_token.value,
        layer_variation_tag_offset=node.start,
        order_key_token=order_token.to_dict(), folder_token=folder_token.to_dict(),
        include_token=include_token.to_dict(),
        layer_template=template.to_dict(), etc_motion_index=1,
        resolved_animation_path=path, animation_source=source(path),
        image_templates=images, resolved_images=formatted,
        frame_count=len(ani["frames"]),
        frame_fields=[dict(index=f["index"], delay=f["delays"], images=f["images"],
                           image_positions=f["image_positions"],
                           attack_boxes=f["attack_boxes"], damage_boxes=f["damage_boxes"])
                      for f in ani["frames"]]))
assert len(records) == 2
body_path = "character/swordman/animation/hardattack.ani"
body = parse_animation(pvf.read(body_path), body_path)
assert not any(frame["attack_boxes"] for frame in body["frames"])
contract = dict(
    status="source_bound_resource_and_native_layer_contract_not_complete_hit_controller",
    source_exe=dict(path=str(ROOT / "DFO" / "DFO_fixed_v3.exe"),
                    sha256=hashlib.sha256((ROOT / "DFO" / "DFO_fixed_v3.exe").read_bytes()).hexdigest()),
    source_pvf=dict(path=str(pvf.path), sha256=archive_hash, header=pvf.header),
    equipment_source=source(source_path), lay_source=source(include_path),
    equipment_variation=dict(tag_offset=variation.start, values=variation.data,
                             tokens=[t.to_dict() for t in variation.values]),
    lay_etc_motion_count=len(motion_tokens), layer_records=records,
    draw_sequence=[dict(kind="body", path=body_path, order_key=None)] + [
        dict(kind="weapon", order_key=x["order_key"], path=x["resolved_animation_path"],
             source_ordinal=x["source_ordinal"])
        for x in sorted(records, key=lambda r:r["order_key"])],
    body=dict(source=source(body_path), frame_count=len(body["frames"]),
              original_attack_box_count=0,
              delay_by_frame=[dict(index=f["index"],delay=f["delays"]) for f in body["frames"]]),
    native_contract=dict(
        motion_selection=dict(body_motion_slot=1, attack_info_slot=0,
                              selection_va="0x731fa9", ani_getter="0x4d3ce0"),
        layer_order=dict(attach="0xa29d70", field="node+0x8", comparison="signed ascending",
                         tie="insert after existing equal keys", draw="0xa26220",
                         phases="negative keys, body current frame, nonnegative keys"),
        same_motion=dict(actor_vslot="0x3bc", target="0x4b8690", actor_vtable_pointer="0xd81350",
                         table_etc_motion_begin="+0x38", table_etc_motion_end="+0x3c",
                         layer_record_stride="0x8c", layer_record_motion_table="+0x4",
                         etc_attach_loop="0x4b8a00..0x4b8a20"),
        image_format=dict(variation_values=[2,6], printf_arguments="first=2, second=6",
                           cached_formatter_call="0xa608c4", format_function="0x401df0",
                           text_parser_formatter_call="0xa29004",
                           constructors=["0x472b80","0xa29ad0","0xa60940","0xa60810"]),
        synchronization=dict(delay_copy="0x4ccdb0", delay_field="frame+0x30",
                             count="min(body frame count, child frame count)",
                             frame_stride="0x7c", child_parent="ANI+0x188",
                             root_clock="0x4caa00", clock_field="root ANI+0x8c",
                             child_advance="0xa27dc0", speed_copy="0xa29d70->0xa29c70",
                             speed_field="ANI+0x134", reset="0xa27360"),
        frame_vectors=dict(attack=dict(tag_id=16,parser="0xa294aa",vector="frame+0x38",begin="+0x3c",end="+0x40"),
                           damage=dict(tag_id=15,parser="0xa293c8",vector="frame+0x48",begin="+0x4c",end="+0x50"),
                           entry_size="0x30", scalar_layout="six 8-byte float wrappers, integer script inputs"),
        conditional_override_merge=dict(gate="0x4b4ce0..0x4b4d88", worker="0x4b4960",
                           merge="0x456770", effective_layers="equipment virtual+0x138",
                           source_layers="equipment+0x758", override="equipment+0x7a0",
                           resolver="0x4acd30", summary="clear selected ANI attack boxes in effective_layers[0]; append same-frame source-layer boxes; only when override gates select this branch"),
        collision_consumer=dict(function="0x4aef80", list="body ANI+0x180",
                           child_pointer="node+0x0c", order="primary ANI pair, then attacker child ANI list order",
                           geometry_call="0x4e9b10->0xa244e0",
                           separate_evidence="../combat_native_collision/geometry-contract.json")),
    limitations=[
        "Static evidence; original client not executed.",
        "This explicit EQU is a preview selection, not a claim that every Swordman equips this item.",
        "Original body ATTACK BOX remains absent; do not synthesize a body substitute.",
        "ATTACK BOX coordinates are retained as six raw numbers; world transform is documented in the separate geometry-contract.json and hit acceptance remains unknown.",
        "Ordinary no-override equipment renders these source layers; do not unconditionally run the conditional override merge on identical input/output vectors.",
        "Native asset formatting and binding are established; target screenshots have not validated final sprite pixels."])
(DEST / "hardattack-equipment-contract.json").write_text(json.dumps(contract, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
for label, document in [("club-equipment-source", equ), ("swordman-layer-source", lay)]:
    (DEST/(label+".cp949")).write_bytes(document.raw)
    (DEST/(label+".utf8.txt")).write_text(document.text, encoding="utf-8")
print(json.dumps(dict(path=str(DEST/"hardattack-equipment-contract.json"),
                     lay_etc_motion_count=len(motion_tokens),
                     layers=[dict(order_key=x["order_key"], path=x["resolved_animation_path"],
                                  images=x["resolved_images"],
                                  attack_box_count=sum(len(f["attack_boxes"]) for f in x["frame_fields"]))
                             for x in records]),ensure_ascii=False,indent=2))
