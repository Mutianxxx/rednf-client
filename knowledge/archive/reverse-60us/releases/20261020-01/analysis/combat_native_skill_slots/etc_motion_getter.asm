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
