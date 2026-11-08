00a29308  53                       push       ebx
00a29309  e8c264e0ff               call       0x82f7d0
00a2930e  83c404                   add        esp, 4
00a29311  3bf3                     cmp        esi, ebx
00a29313  0f8471fbffff             je         0xa28e8a
00a29319  8d550c                   lea        edx, [ebp + 0xc]
00a2931c  52                       push       edx
00a2931d  8d4e30                   lea        ecx, [esi + 0x30]
00a29320  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29323  e8e8c8a2ff               call       0x455c10
00a29328  e95dfbffff               jmp        0xa28e8a
