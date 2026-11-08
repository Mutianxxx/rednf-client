; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00b099b0..00b099da (end exclusive); file offset 007099b0
; This is an instruction excerpt, not a recovered original source file.
00b099b0  55                       push       ebp
00b099b1  8bec                     mov        ebp, esp
00b099b3  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00b099b6  3b4514                   cmp        eax, dword ptr [ebp + 0x14]
00b099b9  7c05                     jl         0xb099c0
00b099bb  d9450c                   fld        dword ptr [ebp + 0xc]
00b099be  5d                       pop        ebp
00b099bf  c3                       ret        
00b099c0  85c0                     test       eax, eax
00b099c2  7f05                     jg         0xb099c9
00b099c4  d94508                   fld        dword ptr [ebp + 8]
00b099c7  5d                       pop        ebp
00b099c8  c3                       ret        
00b099c9  d9450c                   fld        dword ptr [ebp + 0xc]
00b099cc  d86508                   fsub       dword ptr [ebp + 8]
00b099cf  da4d10                   fimul      dword ptr [ebp + 0x10]
00b099d2  da7514                   fidiv      dword ptr [ebp + 0x14]
00b099d5  d84508                   fadd       dword ptr [ebp + 8]
00b099d8  5d                       pop        ebp
00b099d9  c3                       ret        
