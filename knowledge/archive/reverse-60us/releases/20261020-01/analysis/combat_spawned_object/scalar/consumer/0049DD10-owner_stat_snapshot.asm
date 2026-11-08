0049dd10  55                       push       ebp
0049dd11  8bec                     mov        ebp, esp
0049dd13  56                       push       esi
0049dd14  8b7508                   mov        esi, dword ptr [ebp + 8]
0049dd17  85f6                     test       esi, esi
0049dd19  57                       push       edi
0049dd1a  8bf9                     mov        edi, ecx
0049dd1c  89b730050000             mov        dword ptr [edi + 0x530], esi
0049dd22  0f847e010000             je         0x49dea6
0049dd28  8b06                     mov        eax, dword ptr [esi]
0049dd2a  53                       push       ebx
0049dd2b  8bce                     mov        ecx, esi
0049dd2d  ff90c4010000             call       dword ptr [eax + 0x1c4]
0049dd33  898798040000             mov        dword ptr [edi + 0x498], eax
0049dd39  8b16                     mov        edx, dword ptr [esi]
0049dd3b  8bce                     mov        ecx, esi
0049dd3d  ff92a8020000             call       dword ptr [edx + 0x2a8]
0049dd43  898734050000             mov        dword ptr [edi + 0x534], eax
0049dd49  8b06                     mov        eax, dword ptr [esi]
0049dd4b  8bce                     mov        ecx, esi
0049dd4d  ff90d0010000             call       dword ptr [eax + 0x1d0]
0049dd53  898798070000             mov        dword ptr [edi + 0x798], eax
0049dd59  8b16                     mov        edx, dword ptr [esi]
0049dd5b  8bce                     mov        ecx, esi
0049dd5d  ff92d4010000             call       dword ptr [edx + 0x1d4]
0049dd63  89879c070000             mov        dword ptr [edi + 0x79c], eax
0049dd69  8b06                     mov        eax, dword ptr [esi]
0049dd6b  8bce                     mov        ecx, esi
0049dd6d  ff90d8010000             call       dword ptr [eax + 0x1d8]
0049dd73  8987a0070000             mov        dword ptr [edi + 0x7a0], eax
0049dd79  8b16                     mov        edx, dword ptr [esi]
0049dd7b  8bce                     mov        ecx, esi
0049dd7d  ff92dc010000             call       dword ptr [edx + 0x1dc]
0049dd83  8987a4070000             mov        dword ptr [edi + 0x7a4], eax
0049dd89  8b06                     mov        eax, dword ptr [esi]
0049dd8b  8bce                     mov        ecx, esi
0049dd8d  ff90e0010000             call       dword ptr [eax + 0x1e0]
0049dd93  8987a8070000             mov        dword ptr [edi + 0x7a8], eax
0049dd99  8b16                     mov        edx, dword ptr [esi]
0049dd9b  8bce                     mov        ecx, esi
0049dd9d  ff92e4010000             call       dword ptr [edx + 0x1e4]
0049dda3  8987ac070000             mov        dword ptr [edi + 0x7ac], eax
0049dda9  8b06                     mov        eax, dword ptr [esi]
0049ddab  8bce                     mov        ecx, esi
0049ddad  ff90e8010000             call       dword ptr [eax + 0x1e8]
0049ddb3  8987b0070000             mov        dword ptr [edi + 0x7b0], eax
0049ddb9  8b16                     mov        edx, dword ptr [esi]
0049ddbb  8bce                     mov        ecx, esi
0049ddbd  ff92ec010000             call       dword ptr [edx + 0x1ec]
0049ddc3  8987b4070000             mov        dword ptr [edi + 0x7b4], eax
0049ddc9  8b06                     mov        eax, dword ptr [esi]
0049ddcb  8bce                     mov        ecx, esi
0049ddcd  ff90f0010000             call       dword ptr [eax + 0x1f0]
0049ddd3  6a00                     push       0
0049ddd5  682829f400               push       0xf42928
0049ddda  687c28f400               push       0xf4287c
0049dddf  6a00                     push       0
0049dde1  56                       push       esi
0049dde2  8987b8070000             mov        dword ptr [edi + 0x7b8], eax
0049dde8  e81e2f7600               call       0xc00d0b
0049dded  83c414                   add        esp, 0x14
0049ddf0  85c0                     test       eax, eax
0049ddf2  747c                     je         0x49de70
0049ddf4  8d9f24060000             lea        ebx, [edi + 0x624]
0049ddfa  8db74c060000             lea        esi, [edi + 0x64c]
0049de00  c7450803000000           mov        dword ptr [ebp + 8], 3
0049de07  833b12                   cmp        dword ptr [ebx], 0x12
0049de0a  7447                     je         0x49de53
0049de0c  8d8e04020000             lea        ecx, [esi + 0x204]
0049de12  e84942f6ff               call       0x402060
0049de17  8b8f98070000             mov        ecx, dword ptr [edi + 0x798]
0049de1d  8b15d8012101             mov        edx, dword ptr [0x12101d8]
0049de23  8b5244                   mov        edx, dword ptr [edx + 0x44]
0049de26  03c1                     add        eax, ecx
0049de28  8b0e                     mov        ecx, dword ptr [esi]
0049de2a  8d0c8a                   lea        ecx, [edx + ecx*4]
0049de2d  8bd1                     mov        edx, ecx
0049de2f  3315dc012101             xor        edx, dword ptr [0x12101dc]
0049de35  33d0                     xor        edx, eax
0049de37  8911                     mov        dword ptr [ecx], edx
0049de39  8b15d8012101             mov        edx, dword ptr [0x12101d8]
0049de3f  8b5248                   mov        edx, dword ptr [edx + 0x48]
0049de42  8b0e                     mov        ecx, dword ptr [esi]
0049de44  8d0c8a                   lea        ecx, [edx + ecx*4]
0049de47  8bd1                     mov        edx, ecx
0049de49  3315dc012101             xor        edx, dword ptr [0x12101dc]
0049de4f  33d0                     xor        edx, eax
0049de51  8911                     mov        dword ptr [ecx], edx
0049de53  8b4508                   mov        eax, dword ptr [ebp + 8]
0049de56  83c304                   add        ebx, 4
0049de59  83c608                   add        esi, 8
0049de5c  48                       dec        eax
0049de5d  894508                   mov        dword ptr [ebp + 8], eax
0049de60  75a5                     jne        0x49de07
0049de62  5b                       pop        ebx
0049de63  8bcf                     mov        ecx, edi
0049de65  e806ad0400               call       0x4e8b70
0049de6a  5f                       pop        edi
0049de6b  5e                       pop        esi
0049de6c  5d                       pop        ebp
0049de6d  c20400                   ret        4
0049de70  8d9f48060000             lea        ebx, [edi + 0x648]
0049de76  8db724060000             lea        esi, [edi + 0x624]
0049de7c  c7450803000000           mov        dword ptr [ebp + 8], 3
0049de83  833e12                   cmp        dword ptr [esi], 0x12
0049de86  740e                     je         0x49de96
0049de88  8d8308020000             lea        eax, [ebx + 0x208]
0049de8e  50                       push       eax
0049de8f  8bcb                     mov        ecx, ebx
0049de91  e81a67f6ff               call       0x4045b0
0049de96  8b4508                   mov        eax, dword ptr [ebp + 8]
0049de99  83c604                   add        esi, 4
0049de9c  83c308                   add        ebx, 8
0049de9f  48                       dec        eax
0049dea0  894508                   mov        dword ptr [ebp + 8], eax
0049dea3  75de                     jne        0x49de83
0049dea5  5b                       pop        ebx
0049dea6  8bcf                     mov        ecx, edi
0049dea8  e8c3ac0400               call       0x4e8b70
0049dead  5f                       pop        edi
0049deae  5e                       pop        esi
0049deaf  5d                       pop        ebp
0049deb0  c20400                   ret        4