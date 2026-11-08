00a27360  53                       push       ebx
00a27361  56                       push       esi
00a27362  8bf1                     mov        esi, ecx
00a27364  57                       push       edi
00a27365  8d4e48                   lea        ecx, [esi + 0x48]
00a27368  e883db9dff               call       0x404ef0
00a2736d  33db                     xor        ebx, ebx
00a2736f  8d8ea8000000             lea        ecx, [esi + 0xa8]
00a27375  899e88000000             mov        dword ptr [esi + 0x88], ebx
00a2737b  899e8c000000             mov        dword ptr [esi + 0x8c], ebx
00a27381  889e38010000             mov        byte ptr [esi + 0x138], bl
00a27387  889e39010000             mov        byte ptr [esi + 0x139], bl
00a2738d  889e3a010000             mov        byte ptr [esi + 0x13a], bl
00a27393  e8f86fa4ff               call       0x46e390
00a27398  399e84010000             cmp        dword ptr [esi + 0x184], ebx
00a2739e  c78624010000ffffffff     mov        dword ptr [esi + 0x124], 0xffffffff
00a273a8  899e28010000             mov        dword ptr [esi + 0x128], ebx
00a273ae  899e2c010000             mov        dword ptr [esi + 0x12c], ebx
00a273b4  7622                     jbe        0xa273d8
00a273b6  8b8680010000             mov        eax, dword ptr [esi + 0x180]
00a273bc  8b38                     mov        edi, dword ptr [eax]
00a273be  3bf8                     cmp        edi, eax
00a273c0  7416                     je         0xa273d8
00a273c2  8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00a273c5  3bcb                     cmp        ecx, ebx
00a273c7  7405                     je         0xa273ce
00a273c9  e892ffffff               call       0xa27360
00a273ce  8b3f                     mov        edi, dword ptr [edi]
00a273d0  3bbe80010000             cmp        edi, dword ptr [esi + 0x180]
00a273d6  75ea                     jne        0xa273c2
00a273d8  899e90000000             mov        dword ptr [esi + 0x90], ebx
00a273de  33ff                     xor        edi, edi
00a273e0  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a273e6  85c0                     test       eax, eax
00a273e8  741b                     je         0xa27405
00a273ea  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a273f0  2bc8                     sub        ecx, eax
00a273f2  b843082184               mov        eax, 0x84210843
00a273f7  f7e9                     imul       ecx
00a273f9  03d1                     add        edx, ecx
00a273fb  c1fa06                   sar        edx, 6
00a273fe  8bc2                     mov        eax, edx
00a27400  c1e81f                   shr        eax, 0x1f
00a27403  03c2                     add        eax, edx
00a27405  3bd8                     cmp        ebx, eax
00a27407  7d2a                     jge        0xa27433
00a27409  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2740f  8b9690000000             mov        edx, dword ptr [esi + 0x90]
00a27415  03c7                     add        eax, edi
00a27417  8b4830                   mov        ecx, dword ptr [eax + 0x30]
00a2741a  83c030                   add        eax, 0x30
00a2741d  2bc8                     sub        ecx, eax
00a2741f  330df83e0d01             xor        ecx, dword ptr [0x10d3ef8]
00a27425  03d1                     add        edx, ecx
00a27427  43                       inc        ebx
00a27428  899690000000             mov        dword ptr [esi + 0x90], edx
00a2742e  83c77c                   add        edi, 0x7c
00a27431  ebad                     jmp        0xa273e0
00a27433  33ff                     xor        edi, edi
00a27435  33db                     xor        ebx, ebx
00a27437  eb07                     jmp        0xa27440
00a27439  8da42400000000           lea        esp, [esp]
00a27440  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27446  85c0                     test       eax, eax
00a27448  741b                     je         0xa27465
00a2744a  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a27450  2bc8                     sub        ecx, eax
00a27452  b843082184               mov        eax, 0x84210843
00a27457  f7e9                     imul       ecx
00a27459  03d1                     add        edx, ecx
00a2745b  c1fa06                   sar        edx, 6
00a2745e  8bc2                     mov        eax, edx
00a27460  c1e81f                   shr        eax, 0x1f
00a27463  03c2                     add        eax, edx
00a27465  3bf8                     cmp        edi, eax
00a27467  0f8d88000000             jge        0xa274f5
00a2746d  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27473  85c0                     test       eax, eax
00a27475  741b                     je         0xa27492
00a27477  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a2747d  2bc8                     sub        ecx, eax
00a2747f  b843082184               mov        eax, 0x84210843
00a27484  f7e9                     imul       ecx
00a27486  03d1                     add        edx, ecx
00a27488  c1fa06                   sar        edx, 6
00a2748b  8bc2                     mov        eax, edx
00a2748d  c1e81f                   shr        eax, 0x1f
00a27490  03c2                     add        eax, edx
00a27492  3bf8                     cmp        edi, eax
00a27494  7d0a                     jge        0xa274a0
00a27496  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2749c  03c3                     add        eax, ebx
00a2749e  eb02                     jmp        0xa274a2
00a274a0  33c0                     xor        eax, eax
00a274a2  8a4878                   mov        cl, byte ptr [eax + 0x78]
00a274a5  84c9                     test       cl, cl
00a274a7  7443                     je         0xa274ec
00a274a9  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a274af  85c0                     test       eax, eax
00a274b1  741b                     je         0xa274ce
00a274b3  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a274b9  2bc8                     sub        ecx, eax
00a274bb  b843082184               mov        eax, 0x84210843
00a274c0  f7e9                     imul       ecx
00a274c2  03d1                     add        edx, ecx
00a274c4  c1fa06                   sar        edx, 6
00a274c7  8bc2                     mov        eax, edx
00a274c9  c1e81f                   shr        eax, 0x1f
00a274cc  03c2                     add        eax, edx
00a274ce  3bf8                     cmp        edi, eax
00a274d0  7d15                     jge        0xa274e7
00a274d2  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a274d8  03c3                     add        eax, ebx
00a274da  47                       inc        edi
00a274db  c6407800                 mov        byte ptr [eax + 0x78], 0
00a274df  83c37c                   add        ebx, 0x7c
00a274e2  e959ffffff               jmp        0xa27440
00a274e7  33c0                     xor        eax, eax
00a274e9  884078                   mov        byte ptr [eax + 0x78], al
00a274ec  47                       inc        edi
00a274ed  83c37c                   add        ebx, 0x7c
00a274f0  e94bffffff               jmp        0xa27440
00a274f5  5f                       pop        edi
00a274f6  8bce                     mov        ecx, esi
00a274f8  5e                       pop        esi
00a274f9  5b                       pop        ebx
00a274fa  e961050000               jmp        0xa27a60
00a274ff  cc                       int3       
