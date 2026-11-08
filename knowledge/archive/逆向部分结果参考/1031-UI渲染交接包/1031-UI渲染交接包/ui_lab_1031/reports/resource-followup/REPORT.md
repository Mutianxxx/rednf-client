# 1031 Resource-Side Follow-up

Generated from the fixed 1031 executable/PVF and the installed local resource index. This supplement is additive: the sealed `resource-audit` evidence is read-only and its manifest hash is recorded in `evidence.json`.

## Results

- NPK index: 90,799 normalized virtual paths and 90,848 physical members. The 49 duplicate-path groups contain 39 byte-identical groups and 10 content-conflict groups. [duplicate-resolution.csv](duplicate-resolution.csv) retains each archive, byte range, and member SHA-256. Identical bytes may be rendered without losing provenance. Conflicts require explicit archive selection in the resource panel; neither mode claims to reproduce native archive priority.
- ANI gaps: the original 1,402 distinct paths remain partitioned into 1,107 format templates and 295 literal references. [ani-template-candidates.json](ani-template-candidates.json) records concrete filename candidates and placeholder values where available. [ani-reference-usage.json](ani-reference-usage.json) records exact decoded ANI paths, referenced image-frame ranges, and examples. The native [per-path summary](ani-reference-usage-native.json) and [scan metadata](ani-reference-scan-input.json) bind counts to the actual helper run. Of 1,107 templates, 1,008 have at least one physical filename candidate (50,075 candidate path/member rows before runtime argument binding); the remaining candidates are not inferred. All 295 literals have no exact NPK or loose `.img` member in the audited installation. Nearby filenames are suggestions only.
- WDM/UI map IMG paths: `sprite/worldmap/selectdungeon02_cn.img` and `sprite/worldmap/timegate.img` remain missing. Same-basename/nearby resources are reported, not substituted.
- RTF: all 12 PVF documents yield non-empty Korean plain text using their declared CP949 plus RTF Unicode escapes. Source PVF member and output text hashes are retained in [rtf-extraction.json](rtf-extraction.json); extracted text files are under [rtf-extracts](rtf-extracts). Formatting, font layout, and embedded objects are not reproduced.
- Specialized PVF schemas: [pvf-resource-schema-census.json](pvf-resource-schema-census.json) inventories every `.gdata`, `.glist`, `.pos`, `.hsp`, and `.rep` member, observed tags, explicit IMG/ANI/ACT strings, and representative raw fields. It does not establish complete field semantics, native consumers, or render behavior.
- Empty members: [empty-resource-references.json](empty-resource-references.json) keeps all empty ANI/no-extension members and exact-string/token references. Thirteen token references were found; their reachability and interpretation are unproven. A zero-reference result is not proof of no reader.
- TenSLX: [loose-resource-structures.json](loose-resource-structures.json) records the CFB sector/directory chain, `TS0001.dat`, opaque nonzero bytes in two unreferenced sectors plus a 255-byte unaligned tail, the bounded LZMA wrapper, and static PE imports/exports/strings. No CFB stream points to those opaque bytes. The LZMA output starts with `TSIF2011`, but expands to 84,187 bytes versus 84,186 declared, does not reach LZMA EOF, and the wrapper checksum is unidentified. The DLL exports `GetTSObject`; no matching named DNF.exe import was found. No consumer callsite or TSIF record schema is claimed.
- Tenparty: `MOSANG00`, source hash, size, entropy, and printable strings are retained. Its record format and reader remain unknown.

The detailed per-path and per-container records are in [report.json](report.json). `evidence.json` binds them to the installed EXE/PVF, sealed audit hash, helper/decoder hashes, candidate index, modified Python/C++ sources, and every report output.

## Verification

Run the bounded follow-up and offline tests:

```powershell
& 'D:/ProgramData/anaconda3/python.exe' -X utf8 -B ui_lab_1031/tools/resource_followup.py
& 'D:/ProgramData/anaconda3/python.exe' -X utf8 -B ui_lab_1031/tools/verify_revision6.py
& 'D:/ProgramData/anaconda3/python.exe' -X utf8 -B ui_lab_1031/tools/verify_preview.py
```

The resource scan does not start the game, deploy a DLL, or modify the sealed audit or installed client files.
