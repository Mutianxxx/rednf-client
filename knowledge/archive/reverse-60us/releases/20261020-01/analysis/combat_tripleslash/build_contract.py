"""Build a source-bound TripleSlash contract; write only beside this script."""
from pathlib import Path, PurePosixPath
import hashlib
import json
import sys

ROOT = Path(__file__).resolve().parents[2]
DEST = Path(__file__).resolve().parent
sys.path[:0] = [str(ROOT / "analysis"), str(ROOT / "combat-preview")]
from pvf60 import Pvf60
from pvf_model import parse_document, parse_animation, listing_rows, node_record

pvf = Pvf60(ROOT / "DFO" / "Script.pvf")
archive_hash = hashlib.sha256(pvf.data).hexdigest()
assert archive_hash == "23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98"
native = json.loads((DEST / "evidence.json").read_text(encoding="utf-8"))
sources = {}
animations = {}


def source(path):
    path = path.replace("\\", "/").lower()
    if path not in sources:
        raw = pvf.read(path)  # includes seeded content CRC validation
        name = path.replace("/", "__")
        (DEST / (name + ".cp949")).write_bytes(raw)
        (DEST / (name + ".utf8.txt")).write_text(raw.decode("cp949"), encoding="utf-8")
        sources[path] = dict(**pvf.by_path[path], sha256=hashlib.sha256(raw).hexdigest(),
                             archive_sha256=archive_hash, encoding="cp949", crc_verified=True,
                             raw_export=name + ".cp949", readable_export=name + ".utf8.txt")
    return sources[path]


def doc(path):
    source(path)
    return parse_document(pvf.read(path), path)


def animation(path):
    path = path.lower()
    if path not in animations:
        source(path)
        result = parse_animation(pvf.read(path), path)
        assert not result["warnings"], (path, result["warnings"])
        animations[path] = result
    return animations[path]


def compact_animation(path):
    result = animation(path)
    return dict(path=path, source=sources[path], frame_count=result["frame_count"],
                header=result["header"],
                frames=[dict(index=f["index"], source_start=f["start"], source_end=f["end"],
                             delays=f["delays"], images=f["images"], image_positions=f["image_positions"],
                             attack_boxes=f["attack_boxes"], damage_boxes=f["damage_boxes"])
                        for f in result["frames"]])


chr_path = "character/swordman/swordman.chr"
chr_doc = doc(chr_path)
slots = {}
for tag, indices in [("etc motion", range(3, 8)), ("etc attack info", range(2, 8))]:
    field = chr_doc.find(tag)[0]
    assert len(chr_doc.find(tag)) == 1
    for index in indices:
        token = field.values[index]
        assert token.kind == "string"
        path = str(PurePosixPath(chr_path).parent / token.value).lower()
        source(path)
        slots[(tag, index)] = dict(tag=tag, zero_based_index=index, path=path,
                                   source_token=token.to_dict(), field_start=field.start)

listing_path = "skill/swordmanskill.lst"
rows = listing_rows(doc(listing_path))
registrations = [r for r in rows if r["id"] in [4, 8, 13, 27]]
skills = {}
for row in registrations:
    path = str(PurePosixPath("skill") / row["path"]).lower()
    document = doc(path)
    skills[row["id"]] = dict(id=row["id"], path=path, registration=row,
                              source=sources[path], fields=[node_record(n) for n in document.events])

skill_path = skills[8]["path"]
skill_doc = doc(skill_path)
modes = {}
for scope in ["dungeon", "pvp"]:
    fields = [n for n in skill_doc.events if n.scope == (scope,)]
    level_node = next(n for n in fields if n.name == "level info")
    count, *data = level_node.data
    assert count == 3 and len(data) == 90
    modes[scope] = dict(fields=[node_record(n) for n in fields],
                        level_column_count=count, rows=[data[i:i+count] for i in range(0, len(data), count)],
                        level_info_source=node_record(level_node))
assert modes["dungeon"]["rows"][0] == [100, 150, 200]
assert modes["dungeon"]["rows"][-1] == [253, 379, 505]
assert modes["pvp"]["rows"][0] == [60, 90, 120]

equipment_path = "equipment/character/swordman/weapon/club/n_club_axshauta.equ"
lay_path = "equipment/character/swordman.lay"
equ = doc(equipment_path)
lay = doc(lay_path)
variation = equ.find("variation")[0]
assert variation.data == [2, 6]
motion_templates = lay.find("etc motion")[0].values
assert len(motion_templates) == 97
assert len(equ.find("layer variation")) == 2
layers_by_slot = {}
for index in range(3, 8):
    layers = []
    template = motion_templates[index]
    assert template.value == f"%s/TripleSlash{index-2}.ani"
    for ordinal, node in enumerate(equ.find("layer variation")):
        order, folder, directive, include = node.values
        assert directive.value == "<include>" and include.value == lay_path
        path = str(PurePosixPath(equipment_path).parent / (template.value % folder.value)).lower()
        result = compact_animation(path)
        image_templates = sorted({str(image[0]) for f in result["frames"] for image in f["images"]})
        layers.append(dict(source_ordinal=ordinal, draw_order_key=order.value,
                           source_tokens=[t.to_dict() for t in node.values],
                           layer_template_token=template.to_dict(), motion_slot=index,
                           animation=result,
                           images=[dict(template=im, resolved=im % tuple(variation.data) if "%" in im else im)
                                   for im in image_templates]))
    layers_by_slot[index] = sorted(layers, key=lambda r: r["draw_order_key"])

segment_sets = {}
for count in [3, 5]:
    segments = []
    for segment in range(count):
        motion_slot = segment + 3
        atk_slot = 7 if count == 3 and segment == 2 else segment + 2
        body_path = slots[("etc motion", motion_slot)]["path"]
        atk_path = slots[("etc attack info", atk_slot)]["path"]
        body = compact_animation(body_path)
        assert body["frame_count"] == 5
        assert [f["delays"] for f in body["frames"]] == [[[70]], [[70]], [[70]], [[70]], [[300]]]
        assert all(not f["attack_boxes"] for f in body["frames"])
        slash_path = f"character/swordman/effect/animation/tripleslash/slash{segment+1}.ani"
        move_path = f"character/swordman/effect/animation/tripleslash/move{segment%2+1}.ani"
        slash = compact_animation(slash_path)
        move = compact_animation(move_path)
        for effect in [slash, move]:
            assert effect["frame_count"] == 5
            assert all(f["delays"] == [[70]] and not f["attack_boxes"] for f in effect["frames"])
        col = ([0, 0, 1] if count == 3 else [0, 0, 0, 1, 2])[segment]
        atk_doc = doc(atk_path)
        segments.append(dict(
            segment=segment, native_state=22, body_motion_slot=motion_slot, attack_info_slot=atk_slot,
            body_slot_source=slots[("etc motion", motion_slot)],
            attack_info_slot_source=slots[("etc attack info", atk_slot)],
            body=body, attack_info=dict(path=atk_path, source=sources[atk_path],
                                       fields=[node_record(n) for n in atk_doc.events]),
            level_column=col, fixed_damage_column=col+3,
            continuation_min_frame=3 if segment < count-1 else None,
            start_frame=dict(native_reset_marker=-1, logical_initial_frame=0,
                             body_dispatch_reset_flag_connection="unresolved",
                             effect_reset="0x49b84b -> 0xa27360 -> 0xa27f60 -> 0xa27dc0"),
            sound="SM_TRIPLE3" if segment == count-1 else ("SM_TRIPLE2" if segment%2 else "SM_TRIPLE1"),
            attack_sound="R_TSLASH",
            effects=[dict(attach_key=2, animation=slash), dict(attach_key=1, animation=move)],
            selected_club_layers=layers_by_slot[motion_slot],
            selected_club_variant_eligibility="ordinary three-hit configuration" if count == 3 else "resource-only; this club does not meet the five-hit weapon branch"))
    segment_sets[str(count)] = segments

# Bounded full catalog: these are candidates until selected EQU/LAY binds one.
candidate_rows = []
for entry in pvf.entries:
    path = entry["path"]
    if "tripleslash" not in path.lower() or not path.lower().endswith(".ani"):
        continue
    raw = pvf.read(path)
    parsed = parse_animation(raw, path)
    boxes = [dict(index=f["index"], attack_boxes=f["attack_boxes"], delays=f["delays"])
             for f in parsed["frames"] if f["attack_boxes"]]
    candidate_rows.append(dict(**entry, sha256=hashlib.sha256(raw).hexdigest(), crc_verified=True,
                               frame_count=parsed["frame_count"], box_count=sum(len(f["attack_boxes"]) for f in boxes),
                               attack_frames=boxes))
assert len(candidate_rows) == 464
assert sum(bool(row["box_count"]) for row in candidate_rows) == 66
(DEST / "tripleslash-animation-box-catalog.json").write_text(json.dumps(
    dict(source_pvf_sha256=archive_hash, search="every current PVF path containing tripleslash and suffix .ani",
         status="candidate_inventory_not_runtime_binding", ani_count=len(candidate_rows),
         with_attack_boxes=66, rows=candidate_rows), ensure_ascii=False, indent=2)+"\n", encoding="utf-8")

contract = dict(
    status="bounded_native_state22_contract_with_source_bound_ordinary_three_hit_equipment_example",
    source_exe=dict(path=native["source"], sha256=native["sha256"]),
    source_pvf=dict(path=str(pvf.path), sha256=archive_hash, header=pvf.header),
    skill=dict(id=8, class_name="swordman", source=skills[8], modes=modes),
    mastery_skills=[skills[i] for i in [27, 4, 13]],
    native_state=dict(id=22, transition_handler="0x7307b0", entry="0x7329cf",
                      command_and_tick="0x726150", fields=dict(segment="actor+0x2f1c", count="actor+0x2f20",
                      slash_pointers="actor+0x2f24[5]", move_pointers="actor+0x2f38[2]", particle_last_spawn="actor+0x2f40")),
    variant=dict(default_count=3, five_count=5, condition_all=[
        "skill[27] level > 0",
        "(weapon_type==5 and skill[4] level>=skill[4].static[1]) OR (weapon_type==1 and skill[13] level>=skill[13].static[0])",
        "corresponding mastery level is positive"],
        final_lift_override=dict(when="count==5 and segment==4", member="actor+0x358 = current ATK+0xf8",
                                 value="weapon_type5: skill4 level column3; weapon_type1: skill13 level column2"),
        weapon_type_enum_names="numeric branches proven; item category enum names not independently recovered here"),
    segments_by_count=segment_sets,
    movement=dict(native="0x732c63..0x732cda", skill_static_source=node_record(skill_doc.find("static data")[0]),
                  calls=[dict(vslot="0x488", target="0x4b9d80", args=[0, 600, 600, 0, -1000, 1]),
                         dict(vslot="0x488", target="0x4b9d80", args=[1, 0, 0, 0, 0, 0]),
                         dict(vslot="0x494", target="0x4b9c60", args=[2, 2, 1000, 1000, 1.0, 1.0]),
                         dict(vslot="0x49c", target="0x745c30", args=["direction getter vslot0xc0", 4, 0])],
                  limits="Setter field writes recovered. Per-update integration, clamping, time units and collision-constrained displacement are unresolved."),
    skill_consume=dict(percent_query="0x732bbe -> 0x4caa20(column, skill8 level, actor, context12, 12)",
                       bonus_write="query-100 -> protected current ATK+0x10 (actor+0x270)",
                       fixed_query="column+3 -> 0x4caa20", fixed_normalize="query*100/(percent_query) -> current ATK+0x0",
                       base_table_fixed_columns="Current dungeon and PvP tables have 3 columns; columns3..5 out of range yield zero before runtime modifiers.",
                       query_chain="0x4caa20 -> 0x550150 -> 0x550080 -> 0x54fc40",
                       final_damage_formula="not complete; use combat_attackinfo evidence for the proven early percentage stage"),
    input_chain=dict(start_states=[0, 11, 8], start_params=[0, "input selection from 0x559140"],
                     gate_calls=["virtual+0x73c(skill8,0)", "0x559140 result != -1", "virtual+0x768(skill8,1,1,1) true"],
                     next_segment=dict(state=22, frame_table=native["continuation_frame_gate"],
                                       condition="segment<count-1 AND current ANI+0x124 >= table[segment]",
                                       pre_input_call="virtual+0x67c(skill8,1); exact cooldown side effects not resolved here",
                                       params=["segment+1", "input selection"]),
                     request=dict(vslot="0x28c", target="0x4ed1d0", args=[22, "param vector", 1, 0, 0],
                                  behavior="queues state request; does not directly enter 0x7307b0"),
                     finish=dict(condition="current ANI+0x13a != 0", requested_state=0, priority=0,
                                 evaluation="completion test also runs after continuation request; pending priority1 survives later priority0 in 0x4ed283..0x4ed295")),
    cleanup=dict(native="0x730b30..0x730b83", on_each_exit=["detach slash[segment] via virtual+0xfc", "detach move[segment%2] via virtual+0xfc"],
                 when_leaving_state22="virtual+0x72c(skill8,current skill8 level,-1); exact cooldown side effect unresolved"),
    particle_tick=dict(switch=native["state22_tick_switch"], native="0x726c9e..0x726d93",
                       initialize_last_spawn=-200, interval=200,
                       behavior="If elapsed state timer >= last+200: select global object index2 using virtual+0x4d0; place at actor x +/-20, same y/z and direction; update last spawn to elapsed.",
                       limits="Spawn API index proven; exact particle asset/type and lifetime not yet identified."),
    equipment_example=dict(source=sources[equipment_path], lay_source=sources[lay_path],
                            variation=node_record(variation), layer_count=2,
                            native_binding_evidence="../combat_native_skill_slots/hardattack-equipment-contract.json",
                            chain="same native body motion slot -> EQU effective layers -> LAY etc-motion same slot -> 0x4b4a80 lazy bind -> 0x4ccdb0 copy body delays -> body ANI+0x180 child list -> 0x4aef80 collision",
                            clock="Parent body clock for equipment layers; copy five body delays, including frame4 delay300.",
                            caveat="This concrete club is a preview equipment selection, not an assertion about original player's equipped item."),
    limitations=[
        "Static evidence only. Original client has not run this skill for frame-by-frame comparison.",
        "State request transport/application to transition reset flags is not closed; choose logical frame0 for an independent preview and retain this distinction.",
        "Movement integration and collision-constrained displacement remain unknown; literal600/-1000 are setter inputs, not a proved x(t) equation.",
        "Five-hit resources/slots/columns are known; an eligible weapon EQU/LAY selection must be resolved separately. Club example is three-hit only.",
        "Mastery/stat/environment modifiers, hit acceptance, repeated-hit filtering, hit pause, target reactions and final damage rounding are separate chains.",
        "No missing body attack boxes are synthesized. Hit geometry comes from selected equipment layers.",
        "Every runtime claim derives from current EXE/PVF; no dnf-rebuild guesses are used."])
(DEST / "tripleslash-contract.json").write_text(json.dumps(contract, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
(DEST / "pvf-sources.json").write_text(json.dumps(dict(source_pvf_sha256=archive_hash, sources=list(sources.values())), ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
(DEST / "animations.json").write_text(json.dumps(dict(source_pvf_sha256=archive_hash, animations=animations), ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
for path, record in sources.items():
    raw = pvf.read(path)
    assert (DEST / record["raw_export"]).read_bytes() == raw
    assert hashlib.sha256(raw).hexdigest() == record["sha256"]
    parsed = parse_document(raw, path)
    for token in parsed.tokens:
        assert 0 <= token.start <= token.end <= len(raw)
print(json.dumps(dict(contract=str(DEST / "tripleslash-contract.json"),
                      verified_sources=len(sources), selected_animations=len(animations),
                      candidate_animations=len(candidate_rows), candidates_with_attack_boxes=66,
                      mode_rows={k:len(v["rows"]) for k,v in modes.items()}), ensure_ascii=False))
