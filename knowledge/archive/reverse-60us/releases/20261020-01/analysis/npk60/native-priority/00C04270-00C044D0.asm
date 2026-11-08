00c04270  0000                     add        byte ptr [eax], al
00c04272  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
00c04275  eb21                     jmp        0xc04298
00c04277  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00c0427a  53                       push       ebx
00c0427b  e801dc0000               call       0xc11e81
00c04280  59                       pop        ecx
00c04281  c3                       ret        
00c04282  e8b6360000               call       0xc0793d
00c04287  c70009000000             mov        dword ptr [eax], 9
00c0428d  e8b4360000               call       0xc07946
00c04292  832000                   and        dword ptr [eax], 0
00c04295  83c8ff                   or         eax, 0xffffffff
00c04298  e8ae2c0000               call       0xc06f4b
00c0429d  c3                       ret        
00c0429e  ff742404                 push       dword ptr [esp + 4]
00c042a2  ff1578f04001             call       dword ptr [0x140f078]
00c042a8  85c0                     test       eax, eax
00c042aa  750f                     jne        0xc042bb
00c042ac  e88c360000               call       0xc0793d
00c042b1  c70016000000             mov        dword ptr [eax], 0x16
00c042b7  83c8ff                   or         eax, 0xffffffff
00c042ba  c3                       ret        
00c042bb  33c0                     xor        eax, eax
00c042bd  c3                       ret        
00c042be  55                       push       ebp
00c042bf  8bec                     mov        ebp, esp
00c042c1  83ec18                   sub        esp, 0x18
00c042c4  8b4508                   mov        eax, dword ptr [ebp + 8]
00c042c7  833800                   cmp        dword ptr [eax], 0
00c042ca  7506                     jne        0xc042d2
00c042cc  83780400                 cmp        dword ptr [eax + 4], 0
00c042d0  744b                     je         0xc0431d
00c042d2  8d4df8                   lea        ecx, [ebp - 8]
00c042d5  51                       push       ecx
00c042d6  50                       push       eax
00c042d7  ff15a8f54001             call       dword ptr [0x140f5a8]
00c042dd  85c0                     test       eax, eax
00c042df  743c                     je         0xc0431d
00c042e1  8d45e8                   lea        eax, [ebp - 0x18]
00c042e4  50                       push       eax
00c042e5  8d45f8                   lea        eax, [ebp - 8]
00c042e8  50                       push       eax
00c042e9  ff15acf54001             call       dword ptr [0x140f5ac]
00c042ef  85c0                     test       eax, eax
00c042f1  742a                     je         0xc0431d
00c042f3  0fb745f4                 movzx      eax, word ptr [ebp - 0xc]
00c042f7  6aff                     push       -1
00c042f9  50                       push       eax
00c042fa  0fb745f2                 movzx      eax, word ptr [ebp - 0xe]
00c042fe  50                       push       eax
00c042ff  0fb745f0                 movzx      eax, word ptr [ebp - 0x10]
00c04303  50                       push       eax
00c04304  0fb745ee                 movzx      eax, word ptr [ebp - 0x12]
00c04308  50                       push       eax
00c04309  0fb745ea                 movzx      eax, word ptr [ebp - 0x16]
00c0430d  50                       push       eax
00c0430e  0fb745e8                 movzx      eax, word ptr [ebp - 0x18]
00c04312  50                       push       eax
00c04313  e891d70000               call       0xc11aa9
00c04318  83c41c                   add        esp, 0x1c
00c0431b  c9                       leave      
00c0431c  c3                       ret        
00c0431d  83c8ff                   or         eax, 0xffffffff
00c04320  c9                       leave      
00c04321  c3                       ret        
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