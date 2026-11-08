00551ca9  8d7338                   lea        esi, [ebx + 0x38]
00551cac  8d85c0fcffff             lea        eax, [ebp - 0x340]
00551cb2  3bf0                     cmp        esi, eax
00551cb4  7462                     je         0x551d18
00551cb6  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00551cbc  8b4944                   mov        ecx, dword ptr [ecx + 0x44]
00551cbf  8b95c4fcffff             mov        edx, dword ptr [ebp - 0x33c]
00551cc5  8b3c91                   mov        edi, dword ptr [ecx + edx*4]
00551cc8  8d0491                   lea        eax, [ecx + edx*4]
00551ccb  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00551cd1  33c7                     xor        eax, edi
00551cd3  33c2                     xor        eax, edx
00551cd5  8b5604                   mov        edx, dword ptr [esi + 4]
00551cd8  c1e202                   shl        edx, 2
00551cdb  8d3c0a                   lea        edi, [edx + ecx]
00551cde  33f8                     xor        edi, eax
00551ce0  333ddc012101             xor        edi, dword ptr [0x12101dc]
00551ce6  893c0a                   mov        dword ptr [edx + ecx], edi
00551ce9  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00551cef  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
00551cf2  8b95c4fcffff             mov        edx, dword ptr [ebp - 0x33c]
00551cf8  8b3c91                   mov        edi, dword ptr [ecx + edx*4]
00551cfb  8d0491                   lea        eax, [ecx + edx*4]
00551cfe  8b5604                   mov        edx, dword ptr [esi + 4]
00551d01  33c7                     xor        eax, edi
00551d03  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
00551d09  c1e202                   shl        edx, 2
00551d0c  33c7                     xor        eax, edi
00551d0e  8d340a                   lea        esi, [edx + ecx]
00551d11  33f0                     xor        esi, eax
00551d13  33f7                     xor        esi, edi
00551d15  89340a                   mov        dword ptr [edx + ecx], esi
00551d18  8d7340                   lea        esi, [ebx + 0x40]
00551d1b  8d85c8fcffff             lea        eax, [ebp - 0x338]
00551d21  3bf0                     cmp        esi, eax
00551d23  7462                     je         0x551d87
00551d25  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00551d2b  8b4944                   mov        ecx, dword ptr [ecx + 0x44]
00551d2e  8b95ccfcffff             mov        edx, dword ptr [ebp - 0x334]
00551d34  8b3c91                   mov        edi, dword ptr [ecx + edx*4]
00551d37  8d0491                   lea        eax, [ecx + edx*4]
00551d3a  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00551d40  33c7                     xor        eax, edi
00551d42  33c2                     xor        eax, edx
00551d44  8b5604                   mov        edx, dword ptr [esi + 4]
00551d47  c1e202                   shl        edx, 2
00551d4a  8d3c0a                   lea        edi, [edx + ecx]
00551d4d  33f8                     xor        edi, eax
00551d4f  333ddc012101             xor        edi, dword ptr [0x12101dc]
00551d55  893c0a                   mov        dword ptr [edx + ecx], edi
00551d58  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00551d5e  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
00551d61  8b95ccfcffff             mov        edx, dword ptr [ebp - 0x334]
00551d67  8b3c91                   mov        edi, dword ptr [ecx + edx*4]
00551d6a  8d0491                   lea        eax, [ecx + edx*4]
00551d6d  8b5604                   mov        edx, dword ptr [esi + 4]
00551d70  33c7                     xor        eax, edi
00551d72  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
00551d78  c1e202                   shl        edx, 2
00551d7b  33c7                     xor        eax, edi
00551d7d  8d3411                   lea        esi, [ecx + edx]
00551d80  33f0                     xor        esi, eax
00551d82  33f7                     xor        esi, edi
00551d84  893411                   mov        dword ptr [ecx + edx], esi