00a27f60  55                       push       ebp
00a27f61  8bec                     mov        ebp, esp
00a27f63  51                       push       ecx
00a27f64  56                       push       esi
00a27f65  8bf1                     mov        esi, ecx
00a27f67  8b8698010000             mov        eax, dword ptr [esi + 0x198]
00a27f6d  85c0                     test       eax, eax
00a27f6f  57                       push       edi
00a27f70  0f84a3000000             je         0xa28019
00a27f76  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27f7c  85c0                     test       eax, eax
00a27f7e  0f8495000000             je         0xa28019
00a27f84  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a27f8a  2bc8                     sub        ecx, eax
00a27f8c  b843082184               mov        eax, 0x84210843
00a27f91  f7e9                     imul       ecx
00a27f93  03d1                     add        edx, ecx
00a27f95  c1fa06                   sar        edx, 6
00a27f98  8bc2                     mov        eax, edx
00a27f9a  c1e81f                   shr        eax, 0x1f
00a27f9d  03c2                     add        eax, edx
00a27f9f  8945fc                   mov        dword ptr [ebp - 4], eax
00a27fa2  7475                     je         0xa28019
00a27fa4  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27faa  8b08                     mov        ecx, dword ptr [eax]
00a27fac  85c9                     test       ecx, ecx
00a27fae  7469                     je         0xa28019
00a27fb0  e87b5c0e00               call       0xb0dc30
00a27fb5  85c0                     test       eax, eax
00a27fb7  7560                     jne        0xa28019
00a27fb9  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27fbf  8b08                     mov        ecx, dword ptr [eax]
00a27fc1  8b11                     mov        edx, dword ptr [ecx]
00a27fc3  ff9290000000             call       dword ptr [edx + 0x90]
00a27fc9  84c0                     test       al, al
00a27fcb  754c                     jne        0xa28019
00a27fcd  53                       push       ebx
00a27fce  33ff                     xor        edi, edi
00a27fd0  33db                     xor        ebx, ebx
00a27fd2  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a27fd8  85c0                     test       eax, eax
00a27fda  743c                     je         0xa28018
00a27fdc  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a27fe2  2bc8                     sub        ecx, eax
00a27fe4  b843082184               mov        eax, 0x84210843
00a27fe9  f7e9                     imul       ecx
00a27feb  03d1                     add        edx, ecx
00a27fed  c1fa06                   sar        edx, 6
00a27ff0  8bc2                     mov        eax, edx
00a27ff2  c1e81f                   shr        eax, 0x1f
00a27ff5  03c2                     add        eax, edx
00a27ff7  3bf8                     cmp        edi, eax
00a27ff9  731d                     jae        0xa28018
00a27ffb  8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a28001  8b8e98010000             mov        ecx, dword ptr [esi + 0x198]
00a28007  03c3                     add        eax, ebx
00a28009  8b4004                   mov        eax, dword ptr [eax + 4]
00a2800c  50                       push       eax
00a2800d  e86edd0c00               call       0xaf5d80
00a28012  47                       inc        edi
00a28013  83c37c                   add        ebx, 0x7c
00a28016  ebba                     jmp        0xa27fd2
00a28018  5b                       pop        ebx
00a28019  8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00a2801f  85c9                     test       ecx, ecx
00a28021  7407                     je         0xa2802a
00a28023  e8180ea7ff               call       0x498e40
00a28028  eb06                     jmp        0xa28030
00a2802a  8a8639010000             mov        al, byte ptr [esi + 0x139]
00a28030  84c0                     test       al, al
00a28032  750b                     jne        0xa2803f
00a28034  8bce                     mov        ecx, esi
00a28036  e855bcffff               call       0xa23c90
00a2803b  84c0                     test       al, al
00a2803d  7509                     jne        0xa28048
00a2803f  83be24010000ff           cmp        dword ptr [esi + 0x124], -1
00a28046  750e                     jne        0xa28056
00a28048  8bce                     mov        ecx, esi
00a2804a  e871fdffff               call       0xa27dc0
00a2804f  8bce                     mov        ecx, esi
00a28051  e8fac8ffff               call       0xa24950
00a28056  8b8680010000             mov        eax, dword ptr [esi + 0x180]
00a2805c  8b38                     mov        edi, dword ptr [eax]
00a2805e  3bf8                     cmp        edi, eax
00a28060  7416                     je         0xa28078
00a28062  8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00a28065  85c9                     test       ecx, ecx
00a28067  7405                     je         0xa2806e
00a28069  e8f2feffff               call       0xa27f60
00a2806e  8b3f                     mov        edi, dword ptr [edi]
00a28070  3bbe80010000             cmp        edi, dword ptr [esi + 0x180]
00a28076  75ea                     jne        0xa28062
00a28078  5f                       pop        edi
00a28079  5e                       pop        esi
00a2807a  8be5                     mov        esp, ebp
00a2807c  5d                       pop        ebp
00a2807d  c3                       ret        
