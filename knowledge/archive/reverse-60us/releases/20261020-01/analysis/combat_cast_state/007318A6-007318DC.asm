007318a6  837d081c                 cmp        dword ptr [ebp + 8], 0x1c
007318aa  8b5de0                   mov        ebx, dword ptr [ebp - 0x20]
007318ad  7514                     jne        0x7318c3
007318af  83fb08                   cmp        ebx, 8
007318b2  c7450808000000           mov        dword ptr [ebp + 8], 8
007318b9  7508                     jne        0x7318c3
007318bb  bb1c000000               mov        ebx, 0x1c
007318c0  895de0                   mov        dword ptr [ebp - 0x20], ebx
007318c3  8b4508                   mov        eax, dword ptr [ebp + 8]
007318c6  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
007318c9  83c0f8                   add        eax, -8
007318cc  83f82e                   cmp        eax, 0x2e
007318cf  0f8793880000             ja         0x73a168
007318d5  ff248504d57300           jmp        dword ptr [eax*4 + 0x73d504]