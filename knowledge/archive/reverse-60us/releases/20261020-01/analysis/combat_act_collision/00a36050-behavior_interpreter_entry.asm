00a36050 55                       push       ebp
00a36051 8bec                     mov        ebp, esp
00a36053 6aff                     push       -1
00a36055 6891efc800               push       0xc8ef91
00a3605a 64a100000000             mov        eax, dword ptr fs:[0]
00a36060 50                       push       eax
00a36061 64892500000000           mov        dword ptr fs:[0], esp
00a36068 81ecf4040000             sub        esp, 0x4f4
00a3606e 53                       push       ebx
00a3606f 56                       push       esi
00a36070 57                       push       edi
00a36071 8bf9                     mov        edi, ecx
00a36073 33db                     xor        ebx, ebx
00a36075 8d8f9c000000             lea        ecx, [edi + 0x9c]
00a3607b 899d58ffffff             mov        dword ptr [ebp - 0xa8], ebx
00a36081 8b4104                   mov        eax, dword ptr [ecx + 4]
00a36084 3bc3                     cmp        eax, ebx
00a36086 897de0                   mov        dword ptr [ebp - 0x20], edi
00a36089 0f84785d0000             je         0xa3be07
00a3608f 8b7108                   mov        esi, dword ptr [ecx + 8]
00a36092 2bf0                     sub        esi, eax
00a36094 b893244992               mov        eax, 0x92492493
00a36099 f7ee                     imul       esi
00a3609b 03d6                     add        edx, esi
00a3609d c1fa04                   sar        edx, 4
00a360a0 8bc2                     mov        eax, edx
00a360a2 c1e81f                   shr        eax, 0x1f
00a360a5 03c2                     add        eax, edx
00a360a7 8b5508                   mov        edx, dword ptr [ebp + 8]
00a360aa 3bd0                     cmp        edx, eax
00a360ac 0f83555d0000             jae        0xa3be07
00a360b2 52                       push       edx
00a360b3 e8a8d3ffff               call       0xa33460
00a360b8 8b7004                   mov        esi, dword ptr [eax + 4]
00a360bb 8985acfeffff             mov        dword ptr [ebp - 0x154], eax
00a360c1 8b5008                   mov        edx, dword ptr [eax + 8]
00a360c4 83c9ff                   or         ecx, 0xffffffff
00a360c7 3bf2                     cmp        esi, edx
00a360c9 0f84385d0000             je         0xa3be07
00a360cf 8b06                     mov        eax, dword ptr [esi]
00a360d1 3bc3                     cmp        eax, ebx
00a360d3 0f                       .byte      0x0f
00a360d4 85                       .byte      0x85
