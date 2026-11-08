"""Read-only byte-addressed excerpts for the observed 60US slot consumer chain."""
from pathlib import Path
import hashlib
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT/"analysis"/"deps"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE = ROOT/"DFO"/"DFO_fixed_v3.exe"
DEST = Path(__file__).resolve().parent
raw = SOURCE.read_bytes()
pe = pefile.PE(data=raw)
base = pe.OPTIONAL_HEADER.ImageBase
md = Cs(CS_ARCH_X86, CS_MODE_32)
md.skipdata = True

excerpts = [
    ("chr_parser_entry", 0x88b2d0, 0xc8),
    ("chr_etc_motion_parse", 0x88c136, 0x5a),
    ("chr_etc_attack_parse", 0x88c238, 0x58),
    ("chr_factory", 0xa61910, 0x53),
    ("chr_materialize_entry", 0x4da140, 0x82),
    ("etc_motion_materialize", 0x4db255, 0x1b1),
    ("etc_attack_materialize", 0x4db594, 0xe0),
    ("attack_vector_append", 0x4a3630, 0x5d),
    ("etc_motion_getter", 0x4d3ce0, 0x56),
    ("etc_attack_getter", 0x5270f0, 0x41),
    ("attack_vector_index", 0x527090, 0x60),
    ("swordman_constructor_vtable", 0x7469b0, 0x43),
    ("swordman_atk_setter", 0x746c30, 0x1b),
    ("atk_normalizing_setter", 0x4cf680, 0x140),
    ("atk_setter_copy_bridge", 0x4afa10, 0x58),
    ("atk_install_current", 0x4edcd0, 0x3c),
    ("animation_setter", 0x4b4da0, 0x60),
    ("animation_install_current", 0x49b250, 0x7a),
    ("hardattack_slot_selection", 0x731f0c, 0xc4),
    ("chargeafter_slot_selection", 0x73219d, 0x2c),
    ("equipment_animation_bind", 0x4b4a80, 0x314),
    ("equipment_layer_variation_parse", 0x866600, 0x135),
    ("equipment_etc_motion_template_parse", 0x8679d5, 0x1b0),
    ("equipment_variation_parse", 0x867cea, 0x5b),
    ("equipment_effective_layer_vector", 0x455dd0, 0x11),
    ("equipment_layer_override_resolve", 0x4acd30, 0xfe),
    ("equipment_layer_attach_bridge", 0x4b8266, 0x99),
    ("equipment_layer_attach_etc", 0x4b89a2, 0x90),
    ("equipment_same_motion_attach", 0x4b8690, 0x3a2),
    ("equipment_layer_lazy_load", 0x4b2650, 0x190),
    ("equipment_lazy_placeholder_test", 0x4af8d0, 0x5a),
    ("equipment_same_motion_box_merge_gate", 0x4b4960, 0x116),
    ("equipment_same_motion_box_merge", 0x456770, 0xbe),
    ("motion_boxes_clear_bridge", 0x4ae9a0, 0x29),
    ("motion_boxes_append_bridge", 0x4aeb90, 0x77),
    ("animation_frame_box_append", 0xa27500, 0x188),
    ("animation_frame_box_clear", 0xa27690, 0xaa),
    ("animation_child_find_order", 0xa24dc0, 0x36),
    ("animation_child_remove", 0xa277c0, 0x67),
    ("animation_child_attach_sorted", 0xa29d70, 0x84),
    ("animation_body_delay_to_child", 0x4ccdb0, 0xe5),
    ("animation_child_root_time", 0x4caa00, 0x18),
    ("animation_frame_advance_parent_time", 0xa27dc0, 0x19a),
    ("animation_frame_set", 0xa27870, 0x13e),
    ("animation_reset_tree", 0xa27360, 0x1a0),
    ("animation_speed_tree", 0xa29c70, 0xf5),
    ("animation_child_draw_order", 0xa26220, 0x1ef),
    ("animation_frame_index", 0xa25c90, 0x46),
    ("animation_tag_ids_delay_and_boxes", 0xa288d6, 0x147),
    ("animation_tag_switch", 0xa28ca7, 0x13),
    ("animation_parse_delay", 0xa29308, 0x25),
    ("animation_parse_damage_box", 0xa293c8, 0xe2),
    ("animation_parse_attack_box", 0xa294aa, 0xe2),
    ("animation_image_format_arguments", 0xa28f64, 0xb3),
    ("animation_constructor_variation_forward", 0x472c74, 0x33),
    ("animation_loader_variation_forward", 0xa29ad0, 0x88),
    ("animation_cached_image_format", 0xa60810, 0x129),
    ("animation_directory_join", 0xa60940, 0x4c),
    ("wide_format_wrapper", 0x401df0, 0x2a),
    ("wide_format_vargs_wrapper", 0x4011f0, 0x5a),
]
index = []
for name, va, size in excerpts:
    offset = pe.get_offset_from_rva(va-base)
    data = raw[offset:offset+size]
    (DEST/(name+".bin")).write_bytes(data)
    lines = [f"{ins.address:08x}  {ins.bytes.hex():24} {ins.mnemonic:10} {ins.op_str}"
             for ins in md.disasm(data, va)]
    (DEST/(name+".asm")).write_text("\n".join(lines)+"\n", encoding="utf-8")
    index.append(dict(name=name, va=hex(va), rva=hex(va-base), file_offset=hex(offset),
                      size=size, sha256=hashlib.sha256(data).hexdigest(),
                      bin=name+".bin", asm=name+".asm"))

data_records = []
for name, va, size in [("swordman_type_descriptor",0xf6740c,0x20),
                       ("swordman_complete_object_locator",0xebb354,0x14),
                       ("swordman_vtable_prefix",0xd80f90,0x800),
                       ("etc_motion_tag_utf16",0xe1e88c,0x1a),
                       ("etc_attack_info_tag_utf16",0xe233ec,0x24),
                       ("ani_tag_switch_table",0xa29758,0x50),
                       ("ani_box_tags_utf16",0xe44f64,0x2e),
                       ("ani_delay_tag_utf16",0xe44fb8,0x10),
                       ("equipment_layer_tags_utf16",0xe1ebec,0x33)]:
    offset = pe.get_offset_from_rva(va-base)
    data = raw[offset:offset+size]
    (DEST/(name+".bin")).write_bytes(data)
    data_records.append(dict(name=name,va=hex(va),rva=hex(va-base),file_offset=hex(offset),
                             size=size,sha256=hashlib.sha256(data).hexdigest(),hex=data.hex()))

vtable = 0xd80f94
slots = []
for slot in [0xf0, 0x198, 0x38c, 0x67c, 0x694]:
    va = vtable+slot
    offset = pe.get_offset_from_rva(va-base)
    slots.append(dict(slot=hex(slot),va=hex(va),file_offset=hex(offset),
                      bytes_hex=raw[offset:offset+4].hex(),
                      target=hex(struct.unpack_from("<I",raw,offset)[0])))
report = dict(source=dict(path=str(SOURCE),size=len(raw),sha256=hashlib.sha256(raw).hexdigest(),
                          image_base=hex(base)),excerpts=index,data=data_records,
              rtti=dict(type_descriptor="0xf6740c",complete_object_locator="0xebb354",
                        vtable="0xd80f94",constructor_write_va="0x7469e8",slots=slots),
              limitations=["Static byte evidence; original game not executed",
                           "Function names are analyst labels, not recovered symbols",
                           "No claim of complete skill controller or hit acceptance recovery"])
(DEST/"evidence-index.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(source_sha256=report["source"]["sha256"],excerpts=len(index),data_records=len(data_records)),indent=2))
