00c04322  55                       push       ebp
00c04323  8bec                     mov        ebp, esp
00c04325  81ec54020000             sub        esp, 0x254
00c0432b  a13891ff00               mov        eax, dword ptr [0xff9138]
00c04330  56                       push       esi
00c04331  8945fc                   mov        dword ptr [ebp - 4], eax
00c04334  57                       push       edi
00c04335  8d85acfdffff             lea        eax, [ebp - 0x254]
00c0433b  50                       push       eax
00c0433c  ff7508                   push       dword ptr [ebp + 8]
00c0433f  ff1564f04001             call       dword ptr [0x140f064]
00c04345  8bf8                     mov        edi, eax
00c04347  83ffff                   cmp        edi, -1
00c0434a  7542                     jne        0xc0438e
00c0434c  ff157cf14001             call       dword ptr [0x140f17c]
00c04352  6a02                     push       2
00c04354  5e                       pop        esi
00c04355  3bc6                     cmp        eax, esi
00c04357  720f                     jb         0xc04368
00c04359  83f803                   cmp        eax, 3
00c0435c  7627                     jbe        0xc04385
00c0435e  83f808                   cmp        eax, 8
00c04361  7415                     je         0xc04378
00c04363  83f812                   cmp        eax, 0x12
00c04366  741d                     je         0xc04385
00c04368  e8d0350000               call       0xc0793d
00c0436d  c70016000000             mov        dword ptr [eax], 0x16
00c04373  83c8ff                   or         eax, 0xffffffff
00c04376  eb7b                     jmp        0xc043f3
00c04378  e8c0350000               call       0xc0793d
00c0437d  c7000c000000             mov        dword ptr [eax], 0xc
00c04383  ebee                     jmp        0xc04373
00c04385  e8b3350000               call       0xc0793d
00c0438a  8930                     mov        dword ptr [eax], esi
00c0438c  ebe5                     jmp        0xc04373
00c0438e  8b85acfdffff             mov        eax, dword ptr [ebp - 0x254]
00c04394  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00c04397  2d80000000               sub        eax, 0x80
00c0439c  f7d8                     neg        eax
00c0439e  1bc0                     sbb        eax, eax
00c043a0  2385acfdffff             and        eax, dword ptr [ebp - 0x254]
00c043a6  8906                     mov        dword ptr [esi], eax
00c043a8  8d85b0fdffff             lea        eax, [ebp - 0x250]
00c043ae  50                       push       eax
00c043af  e80affffff               call       0xc042be
00c043b4  894604                   mov        dword ptr [esi + 4], eax
00c043b7  8d85b8fdffff             lea        eax, [ebp - 0x248]
00c043bd  50                       push       eax
00c043be  e8fbfeffff               call       0xc042be
00c043c3  894608                   mov        dword ptr [esi + 8], eax
00c043c6  8d85c0fdffff             lea        eax, [ebp - 0x240]
00c043cc  50                       push       eax
00c043cd  e8ecfeffff               call       0xc042be
00c043d2  89460c                   mov        dword ptr [esi + 0xc], eax
00c043d5  8b85ccfdffff             mov        eax, dword ptr [ebp - 0x234]
00c043db  894610                   mov        dword ptr [esi + 0x10], eax
00c043de  8d85d8fdffff             lea        eax, [ebp - 0x228]
00c043e4  50                       push       eax
00c043e5  83c614                   add        esi, 0x14
00c043e8  56                       push       esi
00c043e9  e8bdcaffff               call       0xc00eab
00c043ee  83c414                   add        esp, 0x14
00c043f1  8bc7                     mov        eax, edi
00c043f3  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00c043f6  5f                       pop        edi
00c043f7  5e                       pop        esi
00c043f8  e8800e0000               call       0xc0527d
00c043fd  c9                       leave      
00c043fe  c3                       ret        