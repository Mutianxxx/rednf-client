008898fe 84c0                     test      al, al
00889900 7417                     je        0x889919
00889902 8b5508                   mov       edx, dword ptr [ebp + 8]
00889905 81c248070000             add       edx, 0x748
0088990b 52                       push      edx
0088990c e8cf6bfaff               call      0x8304e0
00889911 83c404                   add       esp, 4
00889914 e9                       .byte     0xe9
00889915 92                       xchg      edx, eax
00889916 1900                     sbb       dword ptr [eax], eax
