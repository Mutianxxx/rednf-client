004ae9a0  55                       push       ebp
004ae9a1  8bec                     mov        ebp, esp
004ae9a3  8b5138                   mov        edx, dword ptr [ecx + 0x38]
004ae9a6  85d2                     test       edx, edx
004ae9a8  741d                     je         0x4ae9c7
004ae9aa  8b413c                   mov        eax, dword ptr [ecx + 0x3c]
004ae9ad  2bc2                     sub        eax, edx
004ae9af  8b5508                   mov        edx, dword ptr [ebp + 8]
004ae9b2  c1f802                   sar        eax, 2
004ae9b5  3bd0                     cmp        edx, eax
004ae9b7  730e                     jae        0x4ae9c7
004ae9b9  8b4138                   mov        eax, dword ptr [ecx + 0x38]
004ae9bc  8b0c90                   mov        ecx, dword ptr [eax + edx*4]
004ae9bf  8d0490                   lea        eax, [eax + edx*4]
004ae9c2  e8c98c5700               call       0xa27690
004ae9c7  5d                       pop        ebp
004ae9c8  c2                       .byte      0xc2
