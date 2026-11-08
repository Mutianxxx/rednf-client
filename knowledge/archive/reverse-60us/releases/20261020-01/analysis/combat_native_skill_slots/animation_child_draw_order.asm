00a26220  55                       push       ebp
00a26221  8bec                     mov        ebp, esp
00a26223  83ec08                   sub        esp, 8
00a26226  53                       push       ebx
00a26227  56                       push       esi
00a26228  57                       push       edi
00a26229  8bf9                     mov        edi, ecx
00a2622b  e830e2ffff               call       0xa24460
00a26230  8b8780010000             mov        eax, dword ptr [edi + 0x180]
00a26236  8b18                     mov        ebx, dword ptr [eax]
00a26238  3bd8                     cmp        ebx, eax
00a2623a  c645ff01                 mov        byte ptr [ebp - 1], 1
00a2623e  0f8498000000             je         0xa262dc
00a26244  8b4308                   mov        eax, dword ptr [ebx + 8]
00a26247  85c0                     test       eax, eax
00a26249  0f8d8d000000             jge        0xa262dc
00a2624f  8b4b0c                   mov        ecx, dword ptr [ebx + 0xc]
00a26252  85c9                     test       ecx, ecx
00a26254  7478                     je         0xa262ce
00a26256  8a452c                   mov        al, byte ptr [ebp + 0x2c]
00a26259  84c0                     test       al, al
00a2625b  743d                     je         0xa2629a
00a2625d  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a26263  85c0                     test       eax, eax
00a26265  7433                     je         0xa2629a
00a26267  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
00a2626d  2bf0                     sub        esi, eax
00a2626f  b843082184               mov        eax, 0x84210843
00a26274  f7ee                     imul       esi
00a26276  03d6                     add        edx, esi
00a26278  c1fa06                   sar        edx, 6
00a2627b  8bc2                     mov        eax, edx
00a2627d  c1e81f                   shr        eax, 0x1f
00a26280  03c2                     add        eax, edx
00a26282  8945f8                   mov        dword ptr [ebp - 8], eax
00a26285  7413                     je         0xa2629a
00a26287  6a00                     push       0
00a26289  e802faffff               call       0xa25c90
00a2628e  83782802                 cmp        dword ptr [eax + 0x28], 2
00a26292  7506                     jne        0xa2629a
00a26294  c645ff00                 mov        byte ptr [ebp - 1], 0
00a26298  eb34                     jmp        0xa262ce
00a2629a  8a45ff                   mov        al, byte ptr [ebp - 1]
00a2629d  84c0                     test       al, al
00a2629f  742d                     je         0xa262ce
00a262a1  8b552c                   mov        edx, dword ptr [ebp + 0x2c]
00a262a4  8b4528                   mov        eax, dword ptr [ebp + 0x28]
00a262a7  52                       push       edx
00a262a8  8b5524                   mov        edx, dword ptr [ebp + 0x24]
00a262ab  50                       push       eax
00a262ac  8b4520                   mov        eax, dword ptr [ebp + 0x20]
00a262af  52                       push       edx
00a262b0  8b551c                   mov        edx, dword ptr [ebp + 0x1c]
00a262b3  50                       push       eax
00a262b4  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a262b7  52                       push       edx
00a262b8  8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a262bb  50                       push       eax
00a262bc  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a262bf  52                       push       edx
00a262c0  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a262c3  50                       push       eax
00a262c4  8b4508                   mov        eax, dword ptr [ebp + 8]
00a262c7  52                       push       edx
00a262c8  50                       push       eax
00a262c9  e852ffffff               call       0xa26220
00a262ce  8b1b                     mov        ebx, dword ptr [ebx]
00a262d0  3b9f80010000             cmp        ebx, dword ptr [edi + 0x180]
00a262d6  0f8568ffffff             jne        0xa26244
00a262dc  8b4d28                   mov        ecx, dword ptr [ebp + 0x28]
00a262df  8b5524                   mov        edx, dword ptr [ebp + 0x24]
00a262e2  8b4520                   mov        eax, dword ptr [ebp + 0x20]
00a262e5  51                       push       ecx
00a262e6  8b4d1c                   mov        ecx, dword ptr [ebp + 0x1c]
00a262e9  52                       push       edx
00a262ea  8b5518                   mov        edx, dword ptr [ebp + 0x18]
00a262ed  50                       push       eax
00a262ee  51                       push       ecx
00a262ef  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a262f2  52                       push       edx
00a262f3  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a262f6  8d87a8000000             lea        eax, [edi + 0xa8]
00a262fc  50                       push       eax
00a262fd  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a26300  51                       push       ecx
00a26301  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a26304  52                       push       edx
00a26305  50                       push       eax
00a26306  51                       push       ecx
00a26307  8bcf                     mov        ecx, edi
00a26309  e882dbffff               call       0xa23e90
00a2630e  3b9f80010000             cmp        ebx, dword ptr [edi + 0x180]
00a26314  0f84b6000000             je         0xa263d0
00a2631a  8d9b00000000             lea        ebx, [ebx]
00a26320  8b4b0c                   mov        ecx, dword ptr [ebx + 0xc]
00a26323  85c9                     test       ecx, ecx
00a26325  0f8497000000             je         0xa263c2
00a2632b  8a452c                   mov        al, byte ptr [ebp + 0x2c]
00a2632e  84c0                     test       al, al
00a26330  7463                     je         0xa26395
00a26332  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a26338  85c0                     test       eax, eax
00a2633a  7459                     je         0xa26395
00a2633c  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
00a26342  2bf0                     sub        esi, eax
00a26344  b843082184               mov        eax, 0x84210843
00a26349  f7ee                     imul       esi
00a2634b  03d6                     add        edx, esi
00a2634d  c1fa06                   sar        edx, 6
00a26350  8bc2                     mov        eax, edx
00a26352  c1e81f                   shr        eax, 0x1f
00a26355  03c2                     add        eax, edx
00a26357  8945f8                   mov        dword ptr [ebp - 8], eax
00a2635a  7439                     je         0xa26395
00a2635c  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a26362  85c0                     test       eax, eax
00a26364  7427                     je         0xa2638d
00a26366  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
00a2636c  2bf0                     sub        esi, eax
00a2636e  b843082184               mov        eax, 0x84210843
00a26373  f7ee                     imul       esi
00a26375  03d6                     add        edx, esi
00a26377  c1fa06                   sar        edx, 6
00a2637a  8bc2                     mov        eax, edx
00a2637c  c1e81f                   shr        eax, 0x1f
00a2637f  03c2                     add        eax, edx
00a26381  85c0                     test       eax, eax
00a26383  7e08                     jle        0xa2638d
00a26385  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a2638b  eb02                     jmp        0xa2638f
00a2638d  33c0                     xor        eax, eax
00a2638f  83782802                 cmp        dword ptr [eax + 0x28], 2
00a26393  742d                     je         0xa263c2
00a26395  8b552c                   mov        edx, dword ptr [ebp + 0x2c]
00a26398  8b4528                   mov        eax, dword ptr [ebp + 0x28]
00a2639b  52                       push       edx
00a2639c  8b5524                   mov        edx, dword ptr [ebp + 0x24]
00a2639f  50                       push       eax
00a263a0  8b4520                   mov        eax, dword ptr [ebp + 0x20]
00a263a3  52                       push       edx
00a263a4  8b551c                   mov        edx, dword ptr [ebp + 0x1c]
00a263a7  50                       push       eax
00a263a8  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a263ab  52                       push       edx
00a263ac  8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a263af  50                       push       eax
00a263b0  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a263b3  52                       push       edx
00a263b4  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a263b7  50                       push       eax
00a263b8  8b4508                   mov        eax, dword ptr [ebp + 8]
00a263bb  52                       push       edx
00a263bc  50                       push       eax
00a263bd  e85efeffff               call       0xa26220
00a263c2  8b1b                     mov        ebx, dword ptr [ebx]
00a263c4  3b9f80010000             cmp        ebx, dword ptr [edi + 0x180]
00a263ca  0f8550ffffff             jne        0xa26320
00a263d0  8b8788010000             mov        eax, dword ptr [edi + 0x188]
00a263d6  85c0                     test       eax, eax
00a263d8  752e                     jne        0xa26408
00a263da  8a8740010000             mov        al, byte ptr [edi + 0x140]
00a263e0  84c0                     test       al, al
00a263e2  7424                     je         0xa26408
00a263e4  8b8f60010000             mov        ecx, dword ptr [edi + 0x160]
00a263ea  8b975c010000             mov        edx, dword ptr [edi + 0x15c]
00a263f0  8b8758010000             mov        eax, dword ptr [edi + 0x158]
00a263f6  51                       push       ecx
00a263f7  8b8f54010000             mov        ecx, dword ptr [edi + 0x154]
00a263fd  52                       push       edx
00a263fe  50                       push       eax
00a263ff  51                       push       ecx
00a26400  e88b14b1ff               call       0x537890
00a26405  83c410                   add        esp, 0x10
00a26408  5f                       pop        edi
00a26409  5e                       pop        esi
00a2640a  5b                       pop        ebx
00a2640b  8be5                     mov        esp, ebp
00a2640d  5d                       pop        ebp
00a2640e  c2                       .byte      0xc2
