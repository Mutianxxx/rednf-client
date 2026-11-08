004d3ce0  55                       push       ebp
004d3ce1  8bec                     mov        ebp, esp
004d3ce3  56                       push       esi
004d3ce4  8bf1                     mov        esi, ecx
004d3ce6  8b8e78120000             mov        ecx, dword ptr [esi + 0x1278]
004d3cec  85c9                     test       ecx, ecx
004d3cee  743f                     je         0x4d3d2f
004d3cf0  8b867c120000             mov        eax, dword ptr [esi + 0x127c]
004d3cf6  2bc1                     sub        eax, ecx
004d3cf8  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004d3cfb  c1f802                   sar        eax, 2
004d3cfe  3bc8                     cmp        ecx, eax
004d3d00  732d                     jae        0x4d3d2f
004d3d02  8b8678120000             mov        eax, dword ptr [esi + 0x1278]
004d3d08  57                       push       edi
004d3d09  8d3c8d00000000           lea        edi, [ecx*4]
004d3d10  03c7                     add        eax, edi
004d3d12  8b00                     mov        eax, dword ptr [eax]
004d3d14  6a13                     push       0x13
004d3d16  50                       push       eax
004d3d17  8bce                     mov        ecx, esi
004d3d19  e8620dfeff               call       0x4b4a80
004d3d1e  8bb678120000             mov        esi, dword ptr [esi + 0x1278]
004d3d24  8b043e                   mov        eax, dword ptr [esi + edi]
004d3d27  03f7                     add        esi, edi
004d3d29  5f                       pop        edi
004d3d2a  5e                       pop        esi
004d3d2b  5d                       pop        ebp
004d3d2c  c20400                   ret        4
004d3d2f  33c0                     xor        eax, eax
004d3d31  5e                       pop        esi
004d3d32  5d                       pop        ebp
004d3d33  c20400                   ret        4
004d3d36  cc                       int3       
004d3d37  cc                       int3       
004d3d38  cc                       int3       
004d3d39  cc                       int3       
004d3d3a  cc                       int3       
004d3d3b  cc                       int3       
004d3d3c  cc                       int3       
004d3d3d  cc                       int3       
004d3d3e  cc                       int3       
004d3d3f  cc                       int3       
004d3d40  55                       push       ebp
004d3d41  8bec                     mov        ebp, esp
004d3d43  51                       push       ecx
004d3d44  56                       push       esi
004d3d45  8bf1                     mov        esi, ecx
004d3d47  8b06                     mov        eax, dword ptr [esi]
004d3d49  ff90f4000000             call       dword ptr [eax + 0xf4]
004d3d4f  85c0                     test       eax, eax
004d3d51  7509                     jne        0x4d3d5c
004d3d53  32c0                     xor        al, al
004d3d55  5e                       pop        esi
004d3d56  8be5                     mov        esp, ebp
004d3d58  5d                       pop        ebp
004d3d59  c20c00                   ret        0xc
004d3d5c  57                       push       edi
004d3d5d  33ff                     xor        edi, edi
004d3d5f  897dfc                   mov        dword ptr [ebp - 4], edi
004d3d62  53                       push       ebx
004d3d63  8b86a4270000             mov        eax, dword ptr [esi + 0x27a4]
004d3d69  85c0                     test       eax, eax
004d3d6b  7465                     je         0x4d3dd2
004d3d6d  8b8ea8270000             mov        ecx, dword ptr [esi + 0x27a8]
004d3d73  2bc8                     sub        ecx, eax
004d3d75  b867666666               mov        eax, 0x66666667
004d3d7a  f7e9                     imul       ecx
004d3d7c  c1fa03                   sar        edx, 3
004d3d7f  8bc2                     mov        eax, edx
004d3d81  c1e81f                   shr        eax, 0x1f
004d3d84  03c2                     add        eax, edx
004d3d86  3bf8                     cmp        edi, eax
004d3d88  7348                     jae        0x4d3dd2
004d3d8a  8b9ea4270000             mov        ebx, dword ptr [esi + 0x27a4]
004d3d90  035dfc                   add        ebx, dword ptr [ebp - 4]
004d3d93  8b16                     mov        edx, dword ptr [esi]
004d3d95  8bce                     mov        ecx, esi
004d3d97  ff92f4000000             call       dword ptr [edx + 0xf4]
004d3d9d  3b03                     cmp        eax, dword ptr [ebx]
004d3d9f  75                       .byte      0x75