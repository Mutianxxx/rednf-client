004b4a80  55                       push       ebp
004b4a81  8bec                     mov        ebp, esp
004b4a83  83ec2c                   sub        esp, 0x2c
004b4a86  53                       push       ebx
004b4a87  8bd9                     mov        ebx, ecx
004b4a89  8b03                     mov        eax, dword ptr [ebx]
004b4a8b  6811010000               push       0x111
004b4a90  895dfc                   mov        dword ptr [ebp - 4], ebx
004b4a93  ff502c                   call       dword ptr [eax + 0x2c]
004b4a96  84c0                     test       al, al
004b4a98  0f84f2020000             je         0x4b4d90
004b4a9e  56                       push       esi
004b4a9f  8b750c                   mov        esi, dword ptr [ebp + 0xc]
004b4aa2  56                       push       esi
004b4aa3  e8185bfaff               call       0x45a5c0
004b4aa8  83c404                   add        esp, 4
004b4aab  84c0                     test       al, al
004b4aad  0f84dc020000             je         0x4b4d8f
004b4ab3  8b13                     mov        edx, dword ptr [ebx]
004b4ab5  57                       push       edi
004b4ab6  8bcb                     mov        ecx, ebx
004b4ab8  ff9264030000             call       dword ptr [edx + 0x364]
004b4abe  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b4ac1  51                       push       ecx
004b4ac2  8bc8                     mov        ecx, eax
004b4ac4  8945e4                   mov        dword ptr [ebp - 0x1c], eax
004b4ac7  e8c49dffff               call       0x4ae890
004b4acc  8bf8                     mov        edi, eax
004b4ace  83ffff                   cmp        edi, -1
004b4ad1  897df4                   mov        dword ptr [ebp - 0xc], edi
004b4ad4  c645dc00                 mov        byte ptr [ebp - 0x24], 0
004b4ad8  0f8402020000             je         0x4b4ce0
004b4ade  33c0                     xor        eax, eax
004b4ae0  83fe13                   cmp        esi, 0x13
004b4ae3  0f94c0                   sete       al
004b4ae6  48                       dec        eax
004b4ae7  23c6                     and        eax, esi
004b4ae9  83fe13                   cmp        esi, 0x13
004b4aec  8945f8                   mov        dword ptr [ebp - 8], eax
004b4aef  7509                     jne        0x4b4afa
004b4af1  c745ec0a000000           mov        dword ptr [ebp - 0x14], 0xa
004b4af8  eb04                     jmp        0x4b4afe
004b4afa  46                       inc        esi
004b4afb  8975ec                   mov        dword ptr [ebp - 0x14], esi
004b4afe  3b45ec                   cmp        eax, dword ptr [ebp - 0x14]
004b4b01  0f8dd9010000             jge        0x4b4ce0
004b4b07  eb07                     jmp        0x4b4b10
004b4b09  8da42400000000           lea        esp, [esp]
004b4b10  8b9c83ec140000           mov        ebx, dword ptr [ebx + eax*4 + 0x14ec]
004b4b17  85db                     test       ebx, ebx
004b4b19  895dd8                   mov        dword ptr [ebp - 0x28], ebx
004b4b1c  0f84ac010000             je         0x4b4cce
004b4b22  8b13                     mov        edx, dword ptr [ebx]
004b4b24  8bcb                     mov        ecx, ebx
004b4b26  c745f000000000           mov        dword ptr [ebp - 0x10], 0
004b4b2d  ff9238010000             call       dword ptr [edx + 0x138]
004b4b33  8b4808                   mov        ecx, dword ptr [eax + 8]
004b4b36  2b4804                   sub        ecx, dword ptr [eax + 4]
004b4b39  b8eba00eea               mov        eax, 0xea0ea0eb
004b4b3e  f7e9                     imul       ecx
004b4b40  03d1                     add        edx, ecx
004b4b42  c1fa07                   sar        edx, 7
004b4b45  8bc2                     mov        eax, edx
004b4b47  c1e81f                   shr        eax, 0x1f
004b4b4a  03c2                     add        eax, edx
004b4b4c  0f8479010000             je         0x4b4ccb
004b4b52  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004b4b55  8b13                     mov        edx, dword ptr [ebx]
004b4b57  51                       push       ecx
004b4b58  8bcb                     mov        ecx, ebx
004b4b5a  ff9238010000             call       dword ptr [edx + 0x138]
004b4b60  8bc8                     mov        ecx, eax
004b4b62  e8291afbff               call       0x466590
004b4b67  8bf0                     mov        esi, eax
004b4b69  8b4e3c                   mov        ecx, dword ptr [esi + 0x3c]
004b4b6c  83c604                   add        esi, 4
004b4b6f  85c9                     test       ecx, ecx
004b4b71  740c                     je         0x4b4b7f
004b4b73  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b4b76  2bc1                     sub        eax, ecx
004b4b78  c1f802                   sar        eax, 2
004b4b7b  3bf8                     cmp        edi, eax
004b4b7d  7228                     jb         0x4b4ba7
004b4b7f  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b4b82  85c0                     test       eax, eax
004b4b84  7504                     jne        0x4b4b8a
004b4b86  33f6                     xor        esi, esi
004b4b88  eb08                     jmp        0x4b4b92
004b4b8a  8b763c                   mov        esi, dword ptr [esi + 0x3c]
004b4b8d  2bf0                     sub        esi, eax
004b4b8f  c1fe02                   sar        esi, 2
004b4b92  56                       push       esi
004b4b93  57                       push       edi
004b4b94  682811cd00               push       0xcd1128
004b4b99  ff15bc2eff00             call       dword ptr [0xff2ebc]
004b4b9f  83c40c                   add        esp, 0xc
004b4ba2  e9f2000000               jmp        0x4b4c99
004b4ba7  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b4baa  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004b4bad  c1e702                   shl        edi, 2
004b4bb0  03c7                     add        eax, edi
004b4bb2  8b00                     mov        eax, dword ptr [eax]
004b4bb4  50                       push       eax
004b4bb5  8945e8                   mov        dword ptr [ebp - 0x18], eax
004b4bb8  e813adffff               call       0x4af8d0
004b4bbd  84c0                     test       al, al
004b4bbf  0f84d1000000             je         0x4b4c96
004b4bc5  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004b4bc8  8d450f                   lea        eax, [ebp + 0xf]
004b4bcb  50                       push       eax
004b4bcc  51                       push       ecx
004b4bcd  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b4bd0  c6450f00                 mov        byte ptr [ebp + 0xf], 0
004b4bd4  e8e7015700               call       0xa24dc0
004b4bd9  8945e0                   mov        dword ptr [ebp - 0x20], eax
004b4bdc  8a450f                   mov        al, byte ptr [ebp + 0xf]
004b4bdf  84c0                     test       al, al
004b4be1  0f84af000000             je         0x4b4c96
004b4be7  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
004b4bea  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b4bed  52                       push       edx
004b4bee  e8cd2b5700               call       0xa277c0
004b4bf3  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
004b4bf6  50                       push       eax
004b4bf7  8bce                     mov        ecx, esi
004b4bf9  e852daffff               call       0x4b2650
004b4bfe  3c01                     cmp        al, 1
004b4c00  7537                     jne        0x4b4c39
004b4c02  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004b4c05  8b4138                   mov        eax, dword ptr [ecx + 0x38]
004b4c08  8b1c38                   mov        ebx, dword ptr [eax + edi]
004b4c0b  03c7                     add        eax, edi
004b4c0d  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b4c10  03c7                     add        eax, edi
004b4c12  85db                     test       ebx, ebx
004b4c14  8b38                     mov        edi, dword ptr [eax]
004b4c16  741a                     je         0x4b4c32
004b4c18  85ff                     test       edi, edi
004b4c1a  7416                     je         0x4b4c32
004b4c1c  8b55e0                   mov        edx, dword ptr [ebp - 0x20]
004b4c1f  57                       push       edi
004b4c20  52                       push       edx
004b4c21  8bcb                     mov        ecx, ebx
004b4c23  e848515700               call       0xa29d70
004b4c28  57                       push       edi
004b4c29  53                       push       ebx
004b4c2a  e881810100               call       0x4ccdb0
004b4c2f  83c408                   add        esp, 8
004b4c32  8b5dd8                   mov        ebx, dword ptr [ebp - 0x28]
004b4c35  c645dc01                 mov        byte ptr [ebp - 0x24], 1
004b4c39  837df809                 cmp        dword ptr [ebp - 8], 9
004b4c3d  7557                     jne        0x4b4c96
004b4c3f  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b4c42  8b01                     mov        eax, dword ptr [ecx]
004b4c44  6811010000               push       0x111
004b4c49  ff502c                   call       dword ptr [eax + 0x2c]
004b4c4c  84c0                     test       al, al
004b4c4e  7446                     je         0x4b4c96
004b4c50  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004b4c56  e8155af8ff               call       0x43a670
004b4c5b  84c0                     test       al, al
004b4c5d  7537                     jne        0x4b4c96
004b4c5f  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b4c62  8b45e0                   mov        eax, dword ptr [ebp - 0x20]
004b4c65  8b11                     mov        edx, dword ptr [ecx]
004b4c67  50                       push       eax
004b4c68  ff9224050000             call       dword ptr [edx + 0x524]
004b4c6e  84c0                     test       al, al
004b4c70  7524                     jne        0x4b4c96
004b4c72  8b13                     mov        edx, dword ptr [ebx]
004b4c74  8bcb                     mov        ecx, ebx
004b4c76  ff92f4000000             call       dword ptr [edx + 0xf4]
004b4c7c  8bc8                     mov        ecx, eax
004b4c7e  83c108                   add        ecx, 8
004b4c81  e8dad3f4ff               call       0x402060
004b4c86  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b4c89  8845d4                   mov        byte ptr [ebp - 0x2c], al
004b4c8c  8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
004b4c8f  56                       push       esi
004b4c90  50                       push       eax
004b4c91  e80a410000               call       0x4b8da0
004b4c96  8b7df4                   mov        edi, dword ptr [ebp - 0xc]
004b4c99  8b75f0                   mov        esi, dword ptr [ebp - 0x10]
004b4c9c  8b13                     mov        edx, dword ptr [ebx]
004b4c9e  46                       inc        esi
004b4c9f  8bcb                     mov        ecx, ebx
004b4ca1  8975f0                   mov        dword ptr [ebp - 0x10], esi
004b4ca4  ff9238010000             call       dword ptr [edx + 0x138]
004b4caa  8b4808                   mov        ecx, dword ptr [eax + 8]
004b4cad  2b4804                   sub        ecx, dword ptr [eax + 4]
004b4cb0  b8eba00eea               mov        eax, 0xea0ea0eb
004b4cb5  f7e9                     imul       ecx
004b4cb7  03d1                     add        edx, ecx
004b4cb9  c1fa07                   sar        edx, 7
004b4cbc  8bc2                     mov        eax, edx
004b4cbe  c1e81f                   shr        eax, 0x1f
004b4cc1  03c2                     add        eax, edx
004b4cc3  3bf0                     cmp        esi, eax
004b4cc5  0f8287feffff             jb         0x4b4b52
004b4ccb  8b45f8                   mov        eax, dword ptr [ebp - 8]
004b4cce  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b4cd1  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
004b4cd4  40                       inc        eax
004b4cd5  3bc1                     cmp        eax, ecx
004b4cd7  8945f8                   mov        dword ptr [ebp - 8], eax
004b4cda  0f8c30feffff             jl         0x4b4b10
004b4ce0  8d83ec140000             lea        eax, [ebx + 0x14ec]
004b4ce6  89450c                   mov        dword ptr [ebp + 0xc], eax
004b4ce9  c745e00a000000           mov        dword ptr [ebp - 0x20], 0xa
004b4cf0  8b30                     mov        esi, dword ptr [eax]
004b4cf2  85f6                     test       esi, esi
004b4cf4  0f847e000000             je         0x4b4d78
004b4cfa  8a868c070000             mov        al, byte ptr [esi + 0x78c]
004b4d00  84c0                     test       al, al
004b4d02  0f8570000000             jne        0x4b4d78
004b4d08  8b16                     mov        edx, dword ptr [esi]
004b4d0a  8bce                     mov        ecx, esi
004b4d0c  ff9238010000             call       dword ptr [edx + 0x138]
004b4d12  85c0                     test       eax, eax
004b4d14  7462                     je         0x4b4d78
004b4d16  c7450800000000           mov        dword ptr [ebp + 8], 0
004b4d1d  81c3ec140000             add        ebx, 0x14ec
004b4d23  8b03                     mov        eax, dword ptr [ebx]
004b4d25  85c0                     test       eax, eax
004b4d27  742a                     je         0x4b4d53
004b4d29  8a888d070000             mov        cl, byte ptr [eax + 0x78d]
004b4d2f  84c9                     test       cl, cl
004b4d31  7420                     je         0x4b4d53
004b4d33  8bb890070000             mov        edi, dword ptr [eax + 0x790]
004b4d39  8b06                     mov        eax, dword ptr [esi]
004b4d3b  8bce                     mov        ecx, esi
004b4d3d  ff90e0000000             call       dword ptr [eax + 0xe0]
004b4d43  3b38                     cmp        edi, dword ptr [eax]
004b4d45  750c                     jne        0x4b4d53
004b4d47  8b0b                     mov        ecx, dword ptr [ebx]
004b4d49  8b8198070000             mov        eax, dword ptr [ecx + 0x798]
004b4d4f  85c0                     test       eax, eax
004b4d51  7411                     je         0x4b4d64
004b4d53  8b4508                   mov        eax, dword ptr [ebp + 8]
004b4d56  40                       inc        eax
004b4d57  83c304                   add        ebx, 4
004b4d5a  83f813                   cmp        eax, 0x13
004b4d5d  894508                   mov        dword ptr [ebp + 8], eax
004b4d60  7cc1                     jl         0x4b4d23
004b4d62  eb11                     jmp        0x4b4d75
004b4d64  8b55dc                   mov        edx, dword ptr [ebp - 0x24]
004b4d67  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
004b4d6a  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b4d6d  52                       push       edx
004b4d6e  50                       push       eax
004b4d6f  56                       push       esi
004b4d70  e8ebfbffff               call       0x4b4960
004b4d75  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
004b4d78  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b4d7b  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004b4d7e  83c004                   add        eax, 4
004b4d81  49                       dec        ecx
004b4d82  89450c                   mov        dword ptr [ebp + 0xc], eax
004b4d85  894de0                   mov        dword ptr [ebp - 0x20], ecx
004b4d88  0f8562ffffff             jne        0x4b4cf0
004b4d8e  5f                       pop        edi
004b4d8f  5e                       pop        esi
004b4d90  5b                       pop        ebx
004b4d91  8be5                     mov        esp, ebp
004b4d93  5d                       pop        ebp
