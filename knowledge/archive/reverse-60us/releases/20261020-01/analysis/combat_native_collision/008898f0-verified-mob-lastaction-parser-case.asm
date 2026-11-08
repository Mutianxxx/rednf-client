008898f0 68e434e200               push      0xe234e4
008898f5 56                       push      esi
008898f6 e8d5aeb7ff               call      0x4047d0
008898fb 83c408                   add       esp, 8
008898fe 84c0                     test      al, al
00889900 7417                     je        0x889919
00889902 8b5508                   mov       edx, dword ptr [ebp + 8]
00889905 81c248070000             add       edx, 0x748
0088990b 52                       push      edx
0088990c e8cf6bfaff               call      0x8304e0
00889911 83c404                   add       esp, 4
00889914 e992190000               jmp       0x88b2ab
