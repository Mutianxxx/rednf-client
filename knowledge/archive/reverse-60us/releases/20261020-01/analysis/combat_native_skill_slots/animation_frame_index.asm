00a25c90  55                       push       ebp
00a25c91  8bec                     mov        ebp, esp
00a25c93  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a25c99  85c0                     test       eax, eax
00a25c9b  741d                     je         0xa25cba
00a25c9d  56                       push       esi
00a25c9e  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
00a25ca4  2bf0                     sub        esi, eax
00a25ca6  b843082184               mov        eax, 0x84210843
00a25cab  f7ee                     imul       esi
00a25cad  03d6                     add        edx, esi
00a25caf  c1fa06                   sar        edx, 6
00a25cb2  8bc2                     mov        eax, edx
00a25cb4  c1e81f                   shr        eax, 0x1f
00a25cb7  03c2                     add        eax, edx
00a25cb9  5e                       pop        esi
00a25cba  8b5508                   mov        edx, dword ptr [ebp + 8]
00a25cbd  3bd0                     cmp        edx, eax
00a25cbf  7d11                     jge        0xa25cd2
00a25cc1  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a25cc7  6bd27c                   imul       edx, edx, 0x7c
00a25cca  03d0                     add        edx, eax
00a25ccc  8bc2                     mov        eax, edx
00a25cce  5d                       pop        ebp
00a25ccf  c20400                   ret        4
00a25cd2  33c0                     xor        eax, eax
00a25cd4  5d                       pop        ebp
00a25cd5  c2                       .byte      0xc2
