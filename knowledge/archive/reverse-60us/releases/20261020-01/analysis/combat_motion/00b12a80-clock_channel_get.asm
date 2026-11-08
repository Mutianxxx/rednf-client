00b12a80  55                       push       ebp
00b12a81  8bec                     mov        ebp, esp
00b12a83  56                       push       esi
00b12a84  8b7508                   mov        esi, dword ptr [ebp + 8]
00b12a87  e8b4420000               call       0xb16d40
00b12a8c  84c0                     test       al, al
00b12a8e  740e                     je         0xb12a9e
00b12a90  8b0cb5707e2001           mov        ecx, dword ptr [esi*4 + 0x1207e70]
00b12a97  5e                       pop        esi
00b12a98  5d                       pop        ebp
00b12a99  e9c2f58eff               jmp        0x402060
00b12a9e  8b04b5707e2001           mov        eax, dword ptr [esi*4 + 0x1207e70]
00b12aa5  5e                       pop        esi
00b12aa6  5d                       pop        ebp
00b12aa7  c3                       ret        
