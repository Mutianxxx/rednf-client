00745b80  55                       push       ebp
00745b81  8bec                     mov        ebp, esp
00745b83  8b4508                   mov        eax, dword ptr [ebp + 8]
00745b86  83f804                   cmp        eax, 4
00745b89  7d0b                     jge        0x745b96
00745b8b  8b8481e01b0000           mov        eax, dword ptr [ecx + eax*4 + 0x1be0]
00745b92  5d                       pop        ebp
00745b93  c20400                   ret        4
00745b96  33c0                     xor        eax, eax
00745b98  5d                       pop        ebp
00745b99  c20400                   ret        4
00745b9c  cc                       int3       
00745b9d  cc                       int3       
00745b9e  cc                       int3       
00745b9f  cc                       int3       
00745ba0  55                       push       ebp
00745ba1  8bec                     mov        ebp, esp
00745ba3  8b4508                   mov        eax, dword ptr [ebp + 8]
00745ba6  83f804                   cmp        eax, 4
00745ba9  7d0b                     jge        0x745bb6
00745bab  8b8481f01b0000           mov        eax, dword ptr [ecx + eax*4 + 0x1bf0]
00745bb2  5d                       pop        ebp
00745bb3  c20400                   ret        4
00745bb6  33c0                     xor        eax, eax
00745bb8  5d                       pop        ebp
00745bb9  c2                       .byte      0xc2