00a27870  55                       push       ebp
00a27871  8bec                     mov        ebp, esp
00a27873  51                       push       ecx
00a27874  53                       push       ebx
00a27875  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a27878  56                       push       esi
00a27879  8bf1                     mov        esi, ecx
00a2787b  3b9e24010000             cmp        ebx, dword ptr [esi + 0x124]
00a27881  0f8426010000             je         0xa279ad
00a27887  8b8e9c010000             mov        ecx, dword ptr [esi + 0x19c]
00a2788d  85c9                     test       ecx, ecx
00a2788f  7406                     je         0xa27897
00a27891  53                       push       ebx
00a27892  e8d9610000               call       0xa2da70
00a27897  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2789d  85c0                     test       eax, eax
00a2789f  741f                     je         0xa278c0
00a278a1  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a278a7  2bc8                     sub        ecx, eax
00a278a9  b843082184               mov        eax, 0x84210843
00a278ae  f7e9                     imul       ecx
00a278b0  03d1                     add        edx, ecx
00a278b2  c1fa06                   sar        edx, 6
00a278b5  8bc2                     mov        eax, edx
00a278b7  c1e81f                   shr        eax, 0x1f
00a278ba  03c2                     add        eax, edx
00a278bc  3bd8                     cmp        ebx, eax
00a278be  723f                     jb         0xa278ff
00a278c0  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a278c6  85c0                     test       eax, eax
00a278c8  741b                     je         0xa278e5
00a278ca  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a278d0  2bc8                     sub        ecx, eax
00a278d2  b843082184               mov        eax, 0x84210843
00a278d7  f7e9                     imul       ecx
00a278d9  03d1                     add        edx, ecx
00a278db  c1fa06                   sar        edx, 6
00a278de  8bc2                     mov        eax, edx
00a278e0  c1e81f                   shr        eax, 0x1f
00a278e3  03c2                     add        eax, edx
00a278e5  50                       push       eax
00a278e6  53                       push       ebx
00a278e7  68584ce400               push       0xe44c58
00a278ec  ff15bc2eff00             call       dword ptr [0xff2ebc]
00a278f2  c7450800000000           mov        dword ptr [ebp + 8], 0
00a278f9  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a278fc  83c40c                   add        esp, 0xc
00a278ff  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27905  899e24010000             mov        dword ptr [esi + 0x124], ebx
00a2790b  6bdb7c                   imul       ebx, ebx, 0x7c
00a2790e  03c3                     add        eax, ebx
00a27910  57                       push       edi
00a27911  8bbe2c010000             mov        edi, dword ptr [esi + 0x12c]
00a27917  83c030                   add        eax, 0x30
00a2791a  89be28010000             mov        dword ptr [esi + 0x128], edi
00a27920  8b08                     mov        ecx, dword ptr [eax]
00a27922  8b15f83e0d01             mov        edx, dword ptr [0x10d3ef8]
00a27928  2bc8                     sub        ecx, eax
00a2792a  33ca                     xor        ecx, edx
00a2792c  894dfc                   mov        dword ptr [ebp - 4], ecx
00a2792f  db45fc                   fild       dword ptr [ebp - 4]
00a27932  d8b634010000             fdiv       dword ptr [esi + 0x134]
00a27938  d80d3c05df00             fmul       dword ptr [0xdf053c]
00a2793e  e8019c1d00               call       0xc01544
00a27943  2bf8                     sub        edi, eax
00a27945  89be2c010000             mov        dword ptr [esi + 0x12c], edi
00a2794b  8dbea8000000             lea        edi, [esi + 0xa8]
00a27951  8bcf                     mov        ecx, edi
00a27953  e8386aa4ff               call       0x46e390
00a27958  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2795e  03c3                     add        eax, ebx
00a27960  50                       push       eax
00a27961  8bcf                     mov        ecx, edi
00a27963  e8987fc4ff               call       0x66f900
00a27968  8bbe9c010000             mov        edi, dword ptr [esi + 0x19c]
00a2796e  85ff                     test       edi, edi
00a27970  c7863c01000000000000     mov        dword ptr [esi + 0x13c], 0
00a2797a  7429                     je         0xa279a5
00a2797c  8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00a27982  85c9                     test       ecx, ecx
00a27984  7407                     je         0xa2798d
00a27986  e87530aaff               call       0x4caa00
00a2798b  eb06                     jmp        0xa27993
00a2798d  8b868c000000             mov        eax, dword ptr [esi + 0x8c]
00a27993  2b862c010000             sub        eax, dword ptr [esi + 0x12c]
00a27999  8b5508                   mov        edx, dword ptr [ebp + 8]
00a2799c  50                       push       eax
00a2799d  52                       push       edx
00a2799e  8bcf                     mov        ecx, edi
00a279a0  e85b9b0000               call       0xa31500
00a279a5  8bce                     mov        ecx, esi
00a279a7  e854240000               call       0xa29e00
00a279ac  5f                       pop        edi
00a279ad  5e                       pop        esi
00a279ae  5b                       pop        ebx
00a279af  8be5                     mov        esp, ebp
00a279b1  5d                       pop        ebp
