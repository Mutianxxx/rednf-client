# Evidence: 1031 DNF.exe 静态分诊（2026-11-03）

All measurements from D:/dnf-rebuild/DNF1031客户端/DNF.exe (41,978,368 B, 2021-09-21).

- PE32, 11 sections: 7 x nsn (all E00000E0 RWX), .idata 12KB, .rsrc 3.1MB.
- Section entropy: 6.661 / 6.299 / 2.354 (0x400000 VS, 0x70600 RAW = uncompress reserve)
  / 7.647 / 5.850 / 6.423 / 7.293 / 7.939 / 6.520 / 5.541 / 7.820.
- EP RVA 0x00FE06BA, file 0xFDFABA: E8 EC 5E 01 00 E9 89 FE FF FF then
  standard CRT case-fold code -> original code, not a packer stub.
- Import directory intact: 30 DLLs (advapi32, ddraw, d3d9, fmodex, ijl15, dbghelp, ...).
- TLS directory RVA 0x014C47C4, callbacks 0x145F2B0 / 0x145F2B8.
- 57,896 ASCII strings (RTTI, DNFLex::yylex, Neople Image File, OpenSSL DH/DSA/EC),
  2,988 UTF-16 strings.
- Strings matching .ani / skill/ / passiveobject/ / .skl / .chr / .atk / .als /
  motion names (windmill, headshot, ashenfork, tripleslash) = 0.
- Companion files: TenSLX.dll (.tvm0 Themida VM), TerSafe.dll (.txt$0..3),
  start/TenProtect, TenSLX.dat, Tenparty.dat.
- mutian.exe: UPX0/UPX1/.rsrc, imports gdiplus/COMCTL32/OLEACC -> login/UI tool.

Finding: partial encryption + anti-debug, NOT full virtualization; static unpacking
is feasible but would not surface plain-text animation bindings.

Path: full report docs/SKILL-DEMO-40JP-SPEC.md section 6.3.
