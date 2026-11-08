004db255  8b83c00b0000             mov        eax, dword ptr [ebx + 0xbc0]
004db25b  3b83c40b0000             cmp        eax, dword ptr [ebx + 0xbc4]
004db261  89450c                   mov        dword ptr [ebp + 0xc], eax
004db264  0f849c010000             je         0x4db406
004db26a  8d9b00000000             lea        ebx, [ebx]
004db270  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004db273  68e0baca00               push       0xcabae0
004db278  e8737e5700               call       0xa530f0
004db27d  50                       push       eax
004db27e  e8685b7200               call       0xc00deb
004db283  83c408                   add        esp, 8
004db286  85c0                     test       eax, eax
004db288  0f840e010000             je         0x4db39c
004db28e  68e8010000               push       0x1e8
004db293  e8b889f2ff               call       0x403c50
004db298  83c404                   add        esp, 4
004db29b  8945e0                   mov        dword ptr [ebp - 0x20], eax
004db29e  85c0                     test       eax, eax
004db2a0  c745fc10000000           mov        dword ptr [ebp - 4], 0x10
004db2a7  0f8493000000             je         0x4db340
004db2ad  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004db2b0  81c1040c0000             add        ecx, 0xc04
004db2b6  e8357e5700               call       0xa530f0
004db2bb  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004db2c1  8b8e90260000             mov        ecx, dword ptr [esi + 0x2690]
004db2c7  8d9e8c260000             lea        ebx, [esi + 0x268c]
004db2cd  8945f0                   mov        dword ptr [ebp - 0x10], eax
004db2d0  8b03                     mov        eax, dword ptr [ebx]
004db2d2  33c7                     xor        eax, edi
004db2d4  2bc3                     sub        eax, ebx
004db2d6  3bc1                     cmp        eax, ecx
004db2d8  740e                     je         0x4db2e8
004db2da  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004db2e0  6a3f                     push       0x3f
004db2e2  53                       push       ebx
004db2e3  e8c8bd6300               call       0xb170b0
004db2e8  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004db2ee  8b4a44                   mov        ecx, dword ptr [edx + 0x44]
004db2f1  8b4304                   mov        eax, dword ptr [ebx + 4]
004db2f4  c1e002                   shl        eax, 2
004db2f7  8d3c08                   lea        edi, [eax + ecx]
004db2fa  333c08                   xor        edi, dword ptr [eax + ecx]
004db2fd  333ddc012101             xor        edi, dword ptr [0x12101dc]
004db303  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
004db306  8d1408                   lea        edx, [eax + ecx]
004db309  331408                   xor        edx, dword ptr [eax + ecx]
004db30c  3315dc012101             xor        edx, dword ptr [0x12101dc]
004db312  3bfa                     cmp        edi, edx
004db314  740e                     je         0x4db324
004db316  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004db31c  6a40                     push       0x40
004db31e  53                       push       ebx
004db31f  e88cbd6300               call       0xb170b0
004db324  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004db327  6a01                     push       1
004db329  e8c27d5700               call       0xa530f0
004db32e  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004db331  50                       push       eax
004db332  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004db335  50                       push       eax
004db336  6a00                     push       0
004db338  57                       push       edi
004db339  e84278f9ff               call       0x472b80
004db33e  eb02                     jmp        0x4db342
004db340  33c0                     xor        eax, eax
004db342  8bbe78120000             mov        edi, dword ptr [esi + 0x1278]
004db348  85ff                     test       edi, edi
004db34a  8d8e74120000             lea        ecx, [esi + 0x1274]
004db350  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004db357  8945f0                   mov        dword ptr [ebp - 0x10], eax
004db35a  7504                     jne        0x4db360
004db35c  33db                     xor        ebx, ebx
004db35e  eb08                     jmp        0x4db368
004db360  8b5908                   mov        ebx, dword ptr [ecx + 8]
004db363  2bdf                     sub        ebx, edi
004db365  c1fb02                   sar        ebx, 2
004db368  85ff                     test       edi, edi
004db36a  741c                     je         0x4db388
004db36c  8b510c                   mov        edx, dword ptr [ecx + 0xc]
004db36f  2bd7                     sub        edx, edi
004db371  c1fa02                   sar        edx, 2
004db374  3bda                     cmp        ebx, edx
004db376  7310                     jae        0x4db388
004db378  8b5108                   mov        edx, dword ptr [ecx + 8]
004db37b  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004db37e  8902                     mov        dword ptr [edx], eax
004db380  83c204                   add        edx, 4
004db383  895108                   mov        dword ptr [ecx + 8], edx
004db386  eb67                     jmp        0x4db3ef
004db388  8b4108                   mov        eax, dword ptr [ecx + 8]
004db38b  8d55f0                   lea        edx, [ebp - 0x10]
004db38e  52                       push       edx
004db38f  6a01                     push       1
004db391  50                       push       eax
004db392  e8c9cdf2ff               call       0x408160
004db397  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004db39a  eb53                     jmp        0x4db3ef
004db39c  8bbe78120000             mov        edi, dword ptr [esi + 0x1278]
004db3a2  85ff                     test       edi, edi
004db3a4  8d8e74120000             lea        ecx, [esi + 0x1274]
004db3aa  c745f000000000           mov        dword ptr [ebp - 0x10], 0
004db3b1  7504                     jne        0x4db3b7
004db3b3  33d2                     xor        edx, edx
004db3b5  eb08                     jmp        0x4db3bf
004db3b7  8b5108                   mov        edx, dword ptr [ecx + 8]
004db3ba  2bd7                     sub        edx, edi
004db3bc  c1fa02                   sar        edx, 2
004db3bf  85ff                     test       edi, edi
004db3c1  741d                     je         0x4db3e0
004db3c3  8b410c                   mov        eax, dword ptr [ecx + 0xc]
004db3c6  2bc7                     sub        eax, edi
004db3c8  c1f802                   sar        eax, 2
004db3cb  3bd0                     cmp        edx, eax
004db3cd  7311                     jae        0x4db3e0
004db3cf  8b4108                   mov        eax, dword ptr [ecx + 8]
004db3d2  c70000000000             mov        dword ptr [eax], 0
004db3d8  83c004                   add        eax, 4
004db3db  894108                   mov        dword ptr [ecx + 8], eax
004db3de  eb0f                     jmp        0x4db3ef
004db3e0  8b4108                   mov        eax, dword ptr [ecx + 8]
004db3e3  8d55f0                   lea        edx, [ebp - 0x10]
004db3e6  52                       push       edx
004db3e7  6a01                     push       1
004db3e9  50                       push       eax
004db3ea  e871cdf2ff               call       0x408160
004db3ef  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004db3f2  8b8bc40b0000             mov        ecx, dword ptr [ebx + 0xbc4]
004db3f8  83c004                   add        eax, 4
004db3fb  3bc1                     cmp        eax, ecx
004db3fd  89450c                   mov        dword ptr [ebp + 0xc], eax
004db400  0f856afeffff             jne        0x4db270
