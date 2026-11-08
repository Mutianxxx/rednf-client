"""Capture only reviewed native slices; opaque regions remain undecoded."""
import json

from native60 import OUT, ROOT, RAW, SHA256, off, u32, data, capture

RANGES = [
    (0x889440, 0x889481, "mob-die-effect-parser", "Tag match, three integers to template+7B4/+7B8/+7BC."),
    (0x44be53, 0x44bf86, "death-global-particle-creators", "Six global PTL creator loads/stores; bounded native fragment, not whole enclosing initializer."),
    (0x4f4440, 0x4f4556, "monster-notification", "Exact body; Monster slot15C, not state application."),
    (0x4b20d0, 0x4b22d1, "active-notification", "Exact body; inherited callback and reference cleanup."),
    (0x4edd10, 0x4ede14, "common-notification", "Exact body; inherited callback and reference cleanup."),
    (0x49bc20, 0x49bd7c, "base-notification", "Exact body; calls current ACT and secondary ACT slot8, not last ACT."),
    (0x4f2a40, 0x4f2ae9, "monster-retention-gate", "Exact body; Monster slot5A0."),
    (0x8e49b0, 0x8e49b3, "monster-slot38-false", "Exact Monster slot38 false stub."),
    (0x50155b, 0x501599, "monster-lastpath-copy", "MOB template+748 to Monster wstring+1AF0; no playback."),
    (0x501c2d, 0x501cd3, "monster-lastact-preload", "MOB+748 to object+150; ACT type11, owner attached; no playback."),
    (0x49bb48, 0x49bb66, "lastact-destruction", "ACT destructor call and pointer clear; no playback."),
    (0x407e90, 0x407e97, "current-act-getter", "Object.slot104 returns+148, not+150."),
    (0x407ea0, 0x407ea7, "secondary-act-getter", "Object.slot108 returns+154, not+150."),
    (0x4fe547, 0x4fe567, "monster-state-switch", "State minus3 remap then table dispatch."),
    (0x4fe7e7, 0x4feb8e, "monster-state5-case", "Cleanup, lifetime, protected slot654 or separate PieceDestroyEffect, masks."),
    (0x4feb8e, 0x4feba5, "monster-base-state-apply", "Pass unchanged four args to base4BAD60."),
    (0x4bb976, 0x4bbacc, "base-state5-case", "Pause current ANI and stop/reset movement; conditional vertical stop."),
    (0x4bc645, 0x4bc664, "base-state-timer-reset", "Conditional reset via param3; common to state applications."),
    (0x4bd649, 0x4bd696, "base-state5-tick", "Conditional Monster Z speed zero; no last action switch."),
    (0x4fc892, 0x4fc8b4, "monster-tick-state-switch", "Protected current state read, remap, jump-table dispatch."),
    (0x4fcb2a, 0x4fcd6c, "monster-state5-tick", "Native fade/gray/scale and expiry call to protected slot654."),
    (0x4fa1d0, 0x4fa1f5, "slot654-protected-entry", "The entry jumps to a protection thunk. Do not linear-decode the following opaque bytes."),
    (0x13baa5f, 0x13baa69, "slot654-entry-thunk", "Push opaque token08100E7E and jump12EE7C9."),
    (0x4fa222, 0x4fa41f, "slot654-native-fragment-A", "Local native CFG only; original entry reachability unknown. Ends at protection jump."),
    (0x13bebef, 0x13bebf9, "slot654-fragment-A-thunk", "Push opaque token08104A87 and jump12EE7C9."),
    (0x4fa476, 0x4fa47b, "slot654-native-fragment-B", "Conditional target of4FA418; immediately jumps to protection thunk."),
    (0x13c22f9, 0x13c2303, "slot654-fragment-B-thunk", "Push opaque token08108C14 and jump12EE7C9."),
    (0x4fa7fd, 0x4fa84e, "slot654-native-removal-tail", "Local authority check and slot164(0). Entry-to-tail reachability unknown."),
    (0x4f0480, 0x4f0490, "monster-slot548-gate", "Reads byte24FC before dispatching4AC5F0; no field write here."),
    (0x4fdbb6, 0x4fdbde, "monster-field24fc-initializer", "Zero initialization; no native setter-to-one established."),
    (0x500b78, 0x500b9c, "piece-config-template-copy", "MOB+7B4/+7B8/+7BC to Monster+1BA0/+1BA4/+1BA8."),
    (0x509a90, 0x509afa, "piece-effect-constructor", "Installs exact vtableCD5B5C then81CFA0 with six explicit arguments."),
    (0x81cfa0, 0x81d296, "piece-effect-initializer", "Resource selection, raw fields, source-bound numeric interpolation."),
    (0x81d2a0, 0x81e0f9, "piece-effect-tick", "Separate effect object, emissions, completion and slot60(0) gates; not a Monster last ACT."),
]
REA = [
    ("050-monster-death-callback", "0x4fa1d0"),
    ("053-monster-state-tick", "0x4fb720"),
    ("091-active-state-apply", "0x4bad60"),
    ("099-monster-death-apply", "0x4f4440"),
    ("100-active-death-common", "0x4b20d0"),
    ("101-removal-notification", "0x4edd10"),
    ("102-monster-destroy-request", "0x4f2a40"),
    ("107-monster-state-apply", "0x4fe290"),
    ("108-monster-death-attachment", "0x509a90"),
    ("109-base-remove-notify", "0x49bc20"),
    ("110-piece-effect-init", "0x81cfa0"),
    ("111-piece-effect-tick", "0x81d2a0"),
]


def main():
    captures = []
    for start, end, label, note in RANGES:
        row = capture(start, end-start, label, note=note)
        row["stem"] = f"{start:08x}-{label}"
        captures.append(row)
    tables = []
    for start, length, label in [(0x4fef68, 0x23, "monster-apply-dispatch-tables"),
                                 (0x4fce68, 0x2a, "monster-tick-dispatch-tables")]:
        row = capture(start, length, label, status="data_table", disassemble=False)
        row["stem"] = f"{start:08x}-{label}"
        captures.append(row)
        tables.append(row)
    slots = []
    for vt, wanted in [(0xd8385c, [0x38,0x60,0x100,0x104,0x108,0x15c,0x164,0x188,0x378,0x3a0,0x548,0x5a0,0x5d0,0x654]),
                       (0xcbb7d4, [0x15c]),
                       (0xcd5b5c, [0x60,0x104,0x108,0x15c,0x164,0x188])]:
        for slot in wanted:
            slots.append({"vtable": hex(vt), "slot": hex(slot), "slot_va": hex(vt+slot),
                          "file_offset": off(vt+slot), "target": hex(u32(vt+slot))})
    rea = []
    for name, expected in REA:
        result_path = ROOT / "analysis/rea/results" / (name + ".json")
        if not result_path.exists():
            # Names are chosen by the shared-session owner; resolve by prefix.
            matches = list(result_path.parent.glob(name[:3] + "-*.json"))
            if len(matches) != 1:
                continue
            result_path = matches[0]
        evidence = json.loads(result_path.read_text(encoding="utf-8"))["structuredContent"]
        rea.append({"evidence_id": evidence["evidence_id"], "expected_function": expected,
                    "result": "../rea/results/" + result_path.name,
                    "source_sha256": evidence["subject"]["digest"]["sha256"],
                    "note": "Canonical address, not the historical artifact filename, identifies the function."})
    strings = []
    from extract_resources import SEEDS
    for addr, expected in SEEDS:
        pos, end = off(addr), off(addr)
        while RAW[end:end+2] != b"\x00\x00":
            end += 2
        value = RAW[pos:end].decode("utf-16-le")
        if value.lower() != expected:
            raise ValueError("Resource constant no longer matches the selected path")
        strings.append({"va": hex(addr), "file_offset": pos, "encoding": "utf-16-le", "value": value})
    vt = 0xcd5b5c
    col = u32(vt-4)
    descriptor = u32(col+12)
    pos = off(descriptor)+8
    type_name = RAW[pos:RAW.index(0, pos)].decode("ascii")
    manifest = {"schema": "60us-monster-death-native-evidence-v1",
                "source": "DFO/DFO_fixed_v3.exe", "source_sha256": SHA256,
                "runtime_observed": False, "captures": captures, "vtable_slots": slots,
                "native_resource_strings": strings,
                "piece_effect_rtti": {"vtable": hex(vt), "COL": hex(col),
                                      "descriptor": hex(descriptor), "type": type_name},
                "rea": rea,
                "decoding_boundary": "Protected instruction payloads are excluded. Native islands retain unproven entry reachability."}
    (OUT / "evidence-index.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"captures": len(captures), "slots": len(slots), "rea": len(rea), "rtti": type_name}))


if __name__ == "__main__":
    main()
