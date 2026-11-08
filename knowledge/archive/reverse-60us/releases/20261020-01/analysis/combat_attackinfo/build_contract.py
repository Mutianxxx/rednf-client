"""Preserve current PVF tokens and the minimum native HardAttack numeric contract.

No final damage formula or victim-state/HP transition is asserted here.
"""
from pathlib import Path
import hashlib
import json
import sys

ROOT = Path(__file__).resolve().parents[2]
DEST = Path(__file__).resolve().parent
sys.path[:0] = [str(ROOT / "analysis"), str(ROOT / "combat-preview")]
from pvf60 import Pvf60
from pvf_model import parse_document, listing_rows

pvf = Pvf60(ROOT / "DFO" / "Script.pvf")
pvf_hash = hashlib.sha256(pvf.data).hexdigest()

def source(path):
    raw = pvf.read(path)
    return dict(**pvf.by_path[path.lower()], sha256=hashlib.sha256(raw).hexdigest(),
                archive_sha256=pvf_hash, encoding="cp949", crc_verified=True)

atk_path = "character/swordman/attackinfo/hardattack.atk"
skl_path = "skill/swordman/hardattack.skl"
atk = parse_document(pvf.read(atk_path), atk_path)
skl = parse_document(pvf.read(skl_path), skl_path)
list_path = "skill/swordmanskill.lst"
lst = parse_document(pvf.read(list_path), list_path)
registration = next(row for row in listing_rows(lst) if row["id"] == 5)
assert registration["path"].lower() == "swordman/hardattack.skl"
level = next(n for n in skl.find("level info") if n.scope == ("dungeon",))
assert level.data[0] == 1 and len(level.data) == 31
assert level.data[1] == 250 and level.data[-1] == 632
values = level.data[1:]
expected = {
    "attack type": ["[magic]"], "weapon damage apply": [1],
    "elemental property": ["[dark element]"], "damage reaction": ["[down]"],
    "push aside": [300], "lift up": [300], "attack direction": ["[hit down]"],
}
for tag, data in expected.items():
    assert atk.find(tag)[0].data == data
assert not atk.find("damage") and not atk.find("damage bonus")

mapping = [
    dict(tag="damage", offset="0x0", storage="protected float32", parser="0x836cd8", sample="absent; reset to 0"),
    dict(tag="absolute damage", offset="0x8", storage="protected int32", parser="0x836d46", sample="absent; reset to 0"),
    dict(tag="damage bonus", offset="0x10", storage="protected int32", parser="0x836dae", sample="absent in ATK; HardAttack writes queried percent minus 100"),
    dict(tag="attack type", offset="0x18", storage="plain int32", parser="0x836dcb", enumeration={"[physic]":0,"[magic]":1,"[ignore defense]":2}),
    dict(tag="weapon damage apply", offset="0x1c", storage="protected int32 boolean", parser="0x836e57", normalization="value != 0"),
    dict(tag="elemental property", offset="0x3c", storage="native ordered tree/set header; sentinel pointer +0x40", parser="0x836f3f", setter="0x46d830", enumeration={"[fire element]":0,"[water element]":1,"[dark element]":2,"[light element]":3,"other/no element":4}),
    dict(tag="damage reaction", offset="0xec", storage="plain int32", parser="0x8376e5", enumeration={"[none]":0,"[damage]":1,"[down]":2,"[damage except human]":3}),
    dict(tag="push aside", offset="0xf0", storage="protected int32", parser="0x837793"),
    dict(tag="lift up", offset="0xf8", storage="protected int32", parser="0x8377c8"),
]
contract = dict(
    status="native_static_parser_levelinfo_install_and_early_numeric_stage_verified_not_complete_damage_formula",
    source_exe=dict(path=str(ROOT / "DFO" / "DFO_fixed_v3.exe"),
                    sha256=hashlib.sha256((ROOT / "DFO" / "DFO_fixed_v3.exe").read_bytes()).hexdigest()),
    source_pvf=dict(path=str(pvf.path), sha256=pvf_hash, header=pvf.header),
    source_atk=source(atk_path), source_skill=source(skl_path),
    source_skill_list=source(list_path), skill_registration=registration,
    attackinfo_stride="0x1b8", actor_current_attackinfo_offset="0x260",
    parser="0x836c20", fields=mapping,
    atk_tokens=[n.to_dict() for n in atk.events],
    skill_levelinfo=level.to_dict(),
    native_levelinfo=dict(parser="0x8a0da0", parse_block="0x8a1e5b",
        source_columns_header="script+0x268", source_columns_begin="script+0x26c",
        input_order="first integer column count N; subsequent tokens appended to column token_index % N",
        outer_stride=16, inner_stride=8, inner_storage="protected int32",
        loader="0x551ad0", script_local="ebp-0x370",
        script_levelinfo_local_header="ebp-0x108", script_levelinfo_local_begin="ebp-0x104",
        materializer="0x55326c..0x55343f", runtime_columns_header="skill+0x23c",
        runtime_columns_begin="skill+0x240", runtime_columns_end="skill+0x244",
        value_copy="0x55340b -> 0x4045b0", query_bridge="0x4caa20",
        query="0x550150", direct_value_query="0x550080",
        addressing="column = skill.begin + col * 16; value = column.begin + (level - 1) * 8",
        out_of_range="direct value query returns 0",
        modifiers="0x54fc40 per-skill modification and 0x550150 environment scaling remain observable; raw PVF is not asserted to bypass these"),
    ordinary_hardattack=dict(state=20, skill_id=5, motion_index=1, attackinfo_index=0,
        install_site="0x731fbe..0x731fca", skill_query_site="0x732041..0x732074",
        column0_write=dict(query_column=0, code="0x73207c..0x732089",
                           attackinfo_offset="0x10", actor_offset="0x270",
                           operation="protectedIntSet(query_result - 100)"),
        column1_write=dict(query_column=1, code="0x73208e..0x7320d6",
                           attackinfo_offset="0x0", actor_offset="0x260",
                           operation="protectedFloatSet(float32(signedIntDivide(query_col1 * 100, readInt(atk+0x10) + 100)))",
                           source_column_status="absent in current one-column HardAttack table; direct getter returns 0"),
        raw_level_examples=[dict(level=i+1, raw_column0=v, installed_bonus=v-100,
                                 mathematical_ratio=v/100) for i,v in enumerate(values)],
        separate_branch="this+0x2eec == 2 has an additional charge-ratio rewrite at 0x7320db..0x732176; not included in the ordinary examples"),
    damage_pack=dict(function="0x4eb780", attacker_argument=4, receiver="ECX; victim/context",
        attackinfo_get="attacker virtual+0x19c", local_struct="ebp-0x1d8",
        maps=[dict(atk="0x0", numeric="0x0", type="float32", read="0x4eb974"),
              dict(atk="0x1c", numeric="0x4", type="byte boolean", read="0x4eb982"),
              dict(atk="0x18", numeric="0x5", type="byte attack type", read="0x4eb98d"),
              dict(atk="0x10", numeric="0x6", type="int32 converted to float32", read="0x4eb999"),
              dict(atk="0x40 tree node+0xc", numeric="0xa+element_enum", type="byte flags", read="0x4eb9aa..0x4eb9d4")],
        weapon_operands=[dict(numeric="0x2f", source="attacker virtual+0x1d8", site="0x4ebc3a"),
                         dict(numeric="0x33", source="attacker virtual+0x1e8", site="0x4ebc50")],
        swordman_operand_paths=[
            dict(slot="0x1d8", bridge="0x744a90", consumer="0x4b5610",
                 stat_base_int="statObject+0x258", stat_scale_float="statObject+0x260"),
            dict(slot="0x1e8", bridge="0x744b10", consumer="0x4b56f0",
                 stat_base_int="statObject+0x278", stat_scale_float="statObject+0x280")],
        swordman_operand_operation="virtual+0x344(3) returns statObject; convert protected-int base to float32, multiply protected-float scale, call 0xc01544; lower bound -1500; conversion helper semantics are not asserted",
        common_consumer_call="0x4ec9f4 -> 0x8b8650", base_dispatch="0x8b85f0",
        ordinary_base_stage="0x8b79c0"),
    early_numeric_stage=dict(code="0x8b79c0..0x8b7a02",
        operation="base = numeric[0x0]; if weapon_apply: add numeric[0x33] for type1, numeric[0x2f] for type0 or type2; base *= (1.0 + numeric[0x6] * float32_constant_0_01)",
        literal_float32_0_01=dict(va="0xcc10ac", hex="0ad7233c", exact_value=0.009999999776482582),
        literal_float32_1=dict(va="0xcc1f58", hex="0000803f", exact_value=1.0),
        mathematical_baseline="with the current ATK base0, weapon_apply1, type1, and raw-query result S: attacker_virtual_1e8_value * S/100",
        precision="instruction-level x87 arithmetic with explicit float32 stores; decimal S/100 is explanatory, not a bit-exact emulation claim",
        subsequent_processing="0x8b79c0 continues with additional percentage/stat/context factors; 0x8b8650 continues element, defense, random and other branches; not recovered as a complete formula here"),
    limitations=[
        "Static code evidence; no current live-client trace or memory snapshot is claimed.",
        "Protected values are handle/index wrappers, not inline plaintext words at the documented offsets.",
        "The semantic source names of virtual+0x1d8/+0x1e8 are supported by type-specific consumer use; all upstream stat construction is outside this contract.",
        "No complete damage formula, final rounding, critical/random distribution, elemental resistance formula, or HP/state transition is claimed.",
        "Reaction/push/lift mapping ends at AttackInfo; downstream victim-state and HP evidence belongs to the collision branch.",
        "The ordinary HardAttack proof does not generalize native controllers to all registered skills.",
    ])
(DEST / "hardattack-attackinfo-contract.json").write_text(json.dumps(contract, ensure_ascii=False, indent=2), encoding="utf-8")
for name,path in [("hardattack.atk",atk_path),("hardattack.skl",skl_path)]:
    (DEST / name).write_bytes(pvf.read(path))
print(json.dumps(dict(field_count=len(mapping), level_count=len(values),
                      level_first=values[0], level_last=values[-1],
                      contract=str(DEST / "hardattack-attackinfo-contract.json")),ensure_ascii=False))
