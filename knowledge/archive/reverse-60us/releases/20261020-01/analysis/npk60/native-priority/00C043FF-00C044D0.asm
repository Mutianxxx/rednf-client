00c043ff  55                       push       ebp
00c04400  8bec                     mov        ebp, esp
00c04402  81ec54020000             sub        esp, 0x254
00c04408  a13891ff00               mov        eax, dword ptr [0xff9138]
00c0440d  8945fc                   mov        dword ptr [ebp - 4], eax
00c04410  56                       push       esi
00c04411  8d85acfdffff             lea        eax, [ebp - 0x254]
00c04417  50                       push       eax
00c04418  ff7508                   push       dword ptr [ebp + 8]
00c0441b  ff1574f04001             call       dword ptr [0x140f074]
00c04421  85c0                     test       eax, eax
00c04423  7542                     jne        0xc04467
00c04425  ff157cf14001             call       dword ptr [0x140f17c]
00c0442b  6a02                     push       2
00c0442d  5e                       pop        esi
00c0442e  3bc6                     cmp        eax, esi
00c04430  720f                     jb         0xc04441
00c04432  83f803                   cmp        eax, 3
00c04435  7627                     jbe        0xc0445e
00c04437  83f808                   cmp        eax, 8
00c0443a  7415                     je         0xc04451
00c0443c  83f812                   cmp        eax, 0x12
00c0443f  741d                     je         0xc0445e
00c04441  e8f7340000               call       0xc0793d
00c04446  c70016000000             mov        dword ptr [eax], 0x16
00c0444c  83c8ff                   or         eax, 0xffffffff
00c0444f  eb7b                     jmp        0xc044cc
00c04451  e8e7340000               call       0xc0793d
00c04456  c7000c000000             mov        dword ptr [eax], 0xc
00c0445c  ebee                     jmp        0xc0444c
00c0445e  e8da340000               call       0xc0793d
00c04463  8930                     mov        dword ptr [eax], esi
00c04465  ebe5                     jmp        0xc0444c
00c04467  8b85acfdffff             mov        eax, dword ptr [ebp - 0x254]
00c0446d  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00c04470  2d80000000               sub        eax, 0x80
00c04475  f7d8                     neg        eax
00c04477  1bc0                     sbb        eax, eax
00c04479  2385acfdffff             and        eax, dword ptr [ebp - 0x254]
00c0447f  8906                     mov        dword ptr [esi], eax
00c04481  8d85b0fdffff             lea        eax, [ebp - 0x250]
00c04487  50                       push       eax
00c04488  e831feffff               call       0xc042be
00c0448d  894604                   mov        dword ptr [esi + 4], eax
00c04490  8d85b8fdffff             lea        eax, [ebp - 0x248]
00c04496  50                       push       eax
00c04497  e822feffff               call       0xc042be
00c0449c  894608                   mov        dword ptr [esi + 8], eax
00c0449f  8d85c0fdffff             lea        eax, [ebp - 0x240]
00c044a5  50                       push       eax
00c044a6  e813feffff               call       0xc042be
00c044ab  89460c                   mov        dword ptr [esi + 0xc], eax
00c044ae  8b85ccfdffff             mov        eax, dword ptr [ebp - 0x234]
00c044b4  894610                   mov        dword ptr [esi + 0x10], eax
00c044b7  8d85d8fdffff             lea        eax, [ebp - 0x228]
00c044bd  50                       push       eax
00c044be  83c614                   add        esi, 0x14
00c044c1  56                       push       esi
00c044c2  e8e4c9ffff               call       0xc00eab
00c044c7  83c414                   add        esp, 0x14
00c044ca  33c0                     xor        eax, eax
00c044cc  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00c044cf  5e                       pop        esi