; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a54f80..00a54fa1 (end exclusive); file offset 00654f80
; This is an instruction excerpt, not a recovered original source file.
00a54f80  803a00                   cmp        byte ptr [edx], 0
00a54f83  b805150000               mov        eax, 0x1505
00a54f88  7416                     je         0xa54fa0
00a54f8a  56                       push       esi
00a54f8b  eb03                     jmp        0xa54f90
00a54f8d  8d4900                   lea        ecx, [ecx]
00a54f90  8a0a                     mov        cl, byte ptr [edx]
00a54f92  6bc021                   imul       eax, eax, 0x21
00a54f95  0fbef1                   movsx      esi, cl
00a54f98  42                       inc        edx
00a54f99  03c6                     add        eax, esi
00a54f9b  84c9                     test       cl, cl
00a54f9d  75f1                     jne        0xa54f90
00a54f9f  5e                       pop        esi
00a54fa0  c3                       ret        
