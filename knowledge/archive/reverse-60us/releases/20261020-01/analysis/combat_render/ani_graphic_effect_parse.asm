00a291d0 8d4db4                   lea        ecx, [ebp - 0x4c]
00a291d3 51                       push       ecx
00a291d4 e83775e0ff               call       0x830710
00a291d9 8d55b4                   lea        edx, [ebp - 0x4c]
00a291dc 68a4becc00               push       0xccbea4
00a291e1 52                       push       edx
00a291e2 e8e9b59dff               call       0x4047d0
00a291e7 83c40c                   add        esp, 0xc
00a291ea 84c0                     test       al, al
00a291ec 7410                     je         0xa291fe
00a291ee 3bf3                     cmp        esi, ebx
00a291f0 0f8494fcffff             je         0xa28e8a
00a291f6 895e28                   mov        dword ptr [esi + 0x28], ebx
00a291f9 e98cfcffff               jmp        0xa28e8a
00a291fe 8d45b4                   lea        eax, [ebp - 0x4c]
00a29201 68844ee400               push       0xe44e84
00a29206 50                       push       eax
00a29207 e8c4b59dff               call       0x4047d0
00a2920c 83c408                   add        esp, 8
00a2920f 84c0                     test       al, al
00a29211 7414                     je         0xa29227
00a29213 3bf3                     cmp        esi, ebx
00a29215 0f846ffcffff             je         0xa28e8a
00a2921b c7462801000000           mov        dword ptr [esi + 0x28], 1
00a29222 e963fcffff               jmp        0xa28e8a
00a29227 8d4db4                   lea        ecx, [ebp - 0x4c]
00a2922a 686c4ee400               push       0xe44e6c
00a2922f 51                       push       ecx
00a29230 e89bb59dff               call       0x4047d0
00a29235 83c408                   add        esp, 8
00a29238 84c0                     test       al, al
00a2923a 7414                     je         0xa29250
00a2923c 3bf3                     cmp        esi, ebx
00a2923e 0f8446fcffff             je         0xa28e8a
00a29244 c7462802000000           mov        dword ptr [esi + 0x28], 2
00a2924b e93afcffff               jmp        0xa28e8a
00a29250 8d55b4                   lea        edx, [ebp - 0x4c]
00a29253 68604ee400               push       0xe44e60
00a29258 52                       push       edx
00a29259 e872b59dff               call       0x4047d0
00a2925e 83c408                   add        esp, 8
00a29261 84c0                     test       al, al
00a29263 7414                     je         0xa29279
00a29265 3bf3                     cmp        esi, ebx
00a29267 0f841dfcffff             je         0xa28e8a
00a2926d c7462803000000           mov        dword ptr [esi + 0x28], 3
00a29274 e911fcffff               jmp        0xa28e8a
00a29279 8d45b4                   lea        eax, [ebp - 0x4c]
00a2927c 68584ee400               push       0xe44e58
00a29281 50                       push       eax
00a29282 e849b59dff               call       0x4047d0
00a29287 83c408                   add        esp, 8
00a2928a 84c0                     test       al, al
00a2928c 7414                     je         0xa292a2
00a2928e 3bf3                     cmp        esi, ebx
00a29290 0f84f4fbffff             je         0xa28e8a
00a29296 c7462804000000           mov        dword ptr [esi + 0x28], 4
00a2929d e9e8fbffff               jmp        0xa28e8a
00a292a2 8d4db4                   lea        ecx, [ebp - 0x4c]
00a292a5 68404ee400               push       0xe44e40
00a292aa 51                       push       ecx
00a292ab e820b59dff               call       0x4047d0
00a292b0 83c408                   add        esp, 8
00a292b3 84c0                     test       al, al
00a292b5 0f84cffbffff             je         0xa28e8a
00a292bb 53                       push       ebx
00a292bc e80f65e0ff               call       0x82f7d0
00a292c1 53                       push       ebx
00a292c2 8945b0                   mov        dword ptr [ebp - 0x50], eax
00a292c5 e80665e0ff               call       0x82f7d0
00a292ca 53                       push       ebx
00a292cb 89450c                   mov        dword ptr [ebp + 0xc], eax
00a292ce e8fd64e0ff               call       0x82f7d0
00a292d3 83c40c                   add        esp, 0xc
00a292d6 3bf3                     cmp        esi, ebx
00a292d8 0f84acfbffff             je         0xa28e8a
00a292de 0fb64db0                 movzx      ecx, byte ptr [ebp - 0x50]
00a292e2 0fb6d0                   movzx      edx, al
00a292e5 0fb6450c                 movzx      eax, byte ptr [ebp + 0xc]
00a292e9 81ca00ffffff             or         edx, 0xffffff00
00a292ef c1e208                   shl        edx, 8
00a292f2 0bd0                     or         edx, eax
00a292f4 c1e208                   shl        edx, 8
00a292f7 0bd1                     or         edx, ecx
00a292f9 c7462805000000           mov        dword ptr [esi + 0x28], 5
00a29300 89562c                   mov        dword ptr [esi + 0x2c], edx
00a29303 e982fbffff               jmp        0xa28e8a