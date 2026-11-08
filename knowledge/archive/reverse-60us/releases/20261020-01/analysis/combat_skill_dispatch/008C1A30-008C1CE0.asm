008c1a30  55                       push       ebp
008c1a31  8bec                     mov        ebp, esp
008c1a33  6aff                     push       -1
008c1a35  68ad30c800               push       0xc830ad
008c1a3a  64a100000000             mov        eax, dword ptr fs:[0]
008c1a40  50                       push       eax
008c1a41  64892500000000           mov        dword ptr fs:[0], esp
008c1a48  81ec4c0b0000             sub        esp, 0xb4c
008c1a4e  53                       push       ebx
008c1a4f  56                       push       esi
008c1a50  57                       push       edi
008c1a51  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
008c1a54  8bf1                     mov        esi, ecx
008c1a56  8b06                     mov        eax, dword ptr [esi]
008c1a58  83c707                   add        edi, 7
008c1a5b  57                       push       edi
008c1a5c  ff5048                   call       dword ptr [eax + 0x48]
008c1a5f  8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
008c1a62  b994070c01               mov        ecx, 0x10c0794
008c1a67  83c3f9                   add        ebx, -7
008c1a6a  e8f105b4ff               call       0x402060
008c1a6f  8d8d48ffffff             lea        ecx, [ebp - 0xb8]
008c1a75  51                       push       ecx
008c1a76  53                       push       ebx
008c1a77  57                       push       edi
008c1a78  898548ffffff             mov        dword ptr [ebp - 0xb8], eax
008c1a7e  e82dc3feff               call       0x8addb0
008c1a83  53                       push       ebx
008c1a84  57                       push       edi
008c1a85  e836c61900               call       0xa5e0c0
008c1a8a  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
008c1a8d  8b4f03                   mov        ecx, dword ptr [edi + 3]
008c1a90  83c414                   add        esp, 0x14
008c1a93  3bc1                     cmp        eax, ecx
008c1a95  7424                     je         0x8c1abb
008c1a97  51                       push       ecx
008c1a98  50                       push       eax
008c1a99  53                       push       ebx
008c1a9a  68c013e300               push       0xe313c0
008c1a9f  ff15bc2eff00             call       dword ptr [0xff2ebc]
008c1aa5  83c410                   add        esp, 0x10
008c1aa8  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1aab  64890d00000000           mov        dword ptr fs:[0], ecx
008c1ab2  5f                       pop        edi
008c1ab3  5e                       pop        esi
008c1ab4  5b                       pop        ebx
008c1ab5  8be5                     mov        esp, ebp
008c1ab7  5d                       pop        ebp
008c1ab8  c20c00                   ret        0xc
008c1abb  33d2                     xor        edx, edx
008c1abd  668b5701                 mov        dx, word ptr [edi + 1]
008c1ac1  52                       push       edx
008c1ac2  53                       push       ebx
008c1ac3  e8e84e0000               call       0x8c69b0
008c1ac8  0fb74701                 movzx      eax, word ptr [edi + 1]
008c1acc  83c408                   add        esp, 8
008c1acf  83f837                   cmp        eax, 0x37
008c1ad2  0f8778430000             ja         0x8c5e50
008c1ad8  ff2485645e8c00           jmp        dword ptr [eax*4 + 0x8c5e64]
008c1adf  8b06                     mov        eax, dword ptr [esi]
008c1ae1  8d4d0c                   lea        ecx, [ebp + 0xc]
008c1ae4  51                       push       ecx
008c1ae5  8bce                     mov        ecx, esi
008c1ae7  c7450c00000000           mov        dword ptr [ebp + 0xc], 0
008c1aee  ff505c                   call       dword ptr [eax + 0x5c]
008c1af1  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008c1af4  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1af7  8b11                     mov        edx, dword ptr [ecx]
008c1af9  50                       push       eax
008c1afa  8b4508                   mov        eax, dword ptr [ebp + 8]
008c1afd  50                       push       eax
008c1afe  ff12                     call       dword ptr [edx]
008c1b00  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1b03  64890d00000000           mov        dword ptr fs:[0], ecx
008c1b0a  5f                       pop        edi
008c1b0b  5e                       pop        esi
008c1b0c  5b                       pop        ebx
008c1b0d  8be5                     mov        esp, ebp
008c1b0f  5d                       pop        ebp
008c1b10  c20c00                   ret        0xc
008c1b13  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1b16  8b4508                   mov        eax, dword ptr [ebp + 8]
008c1b19  8b11                     mov        edx, dword ptr [ecx]
008c1b1b  50                       push       eax
008c1b1c  ff5204                   call       dword ptr [edx + 4]
008c1b1f  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1b22  64890d00000000           mov        dword ptr fs:[0], ecx
008c1b29  5f                       pop        edi
008c1b2a  5e                       pop        esi
008c1b2b  5b                       pop        ebx
008c1b2c  8be5                     mov        esp, ebp
008c1b2e  5d                       pop        ebp
008c1b2f  c20c00                   ret        0xc
008c1b32  8b16                     mov        edx, dword ptr [esi]
008c1b34  8d450c                   lea        eax, [ebp + 0xc]
008c1b37  50                       push       eax
008c1b38  8bce                     mov        ecx, esi
008c1b3a  c7450c00000000           mov        dword ptr [ebp + 0xc], 0
008c1b41  ff525c                   call       dword ptr [edx + 0x5c]
008c1b44  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008c1b47  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1b4a  8b11                     mov        edx, dword ptr [ecx]
008c1b4c  50                       push       eax
008c1b4d  8b4508                   mov        eax, dword ptr [ebp + 8]
008c1b50  50                       push       eax
008c1b51  ff5208                   call       dword ptr [edx + 8]
008c1b54  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1b57  64890d00000000           mov        dword ptr fs:[0], ecx
008c1b5e  5f                       pop        edi
008c1b5f  5e                       pop        esi
008c1b60  5b                       pop        ebx
008c1b61  8be5                     mov        esp, ebp
008c1b63  5d                       pop        ebp
008c1b64  c20c00                   ret        0xc
008c1b67  8b4d08                   mov        ecx, dword ptr [ebp + 8]
008c1b6a  51                       push       ecx
008c1b6b  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1b6e  e85d6a2c00               call       0xb885d0
008c1b73  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1b76  64890d00000000           mov        dword ptr fs:[0], ecx
008c1b7d  5f                       pop        edi
008c1b7e  5e                       pop        esi
008c1b7f  5b                       pop        ebx
008c1b80  8be5                     mov        esp, ebp
008c1b82  5d                       pop        ebp
008c1b83  c20c00                   ret        0xc
008c1b86  8b16                     mov        edx, dword ptr [esi]
008c1b88  8d450b                   lea        eax, [ebp + 0xb]
008c1b8b  50                       push       eax
008c1b8c  8bce                     mov        ecx, esi
008c1b8e  c6450b00                 mov        byte ptr [ebp + 0xb], 0
008c1b92  ff5250                   call       dword ptr [edx + 0x50]
008c1b95  8b16                     mov        edx, dword ptr [esi]
008c1b97  8d450c                   lea        eax, [ebp + 0xc]
008c1b9a  50                       push       eax
008c1b9b  8bce                     mov        ecx, esi
008c1b9d  ff5268                   call       dword ptr [edx + 0x68]
008c1ba0  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008c1ba3  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1ba6  8b11                     mov        edx, dword ptr [ecx]
008c1ba8  50                       push       eax
008c1ba9  0fb6450b                 movzx      eax, byte ptr [ebp + 0xb]
008c1bad  50                       push       eax
008c1bae  ff520c                   call       dword ptr [edx + 0xc]
008c1bb1  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1bb4  64890d00000000           mov        dword ptr fs:[0], ecx
008c1bbb  5f                       pop        edi
008c1bbc  5e                       pop        esi
008c1bbd  5b                       pop        ebx
008c1bbe  8be5                     mov        esp, ebp
008c1bc0  5d                       pop        ebp
008c1bc1  c20c00                   ret        0xc
008c1bc4  8b16                     mov        edx, dword ptr [esi]
008c1bc6  8d450c                   lea        eax, [ebp + 0xc]
008c1bc9  33db                     xor        ebx, ebx
008c1bcb  50                       push       eax
008c1bcc  8bce                     mov        ecx, esi
008c1bce  895d0c                   mov        dword ptr [ebp + 0xc], ebx
008c1bd1  885d0b                   mov        byte ptr [ebp + 0xb], bl
008c1bd4  ff525c                   call       dword ptr [edx + 0x5c]
008c1bd7  8b16                     mov        edx, dword ptr [esi]
008c1bd9  8d450b                   lea        eax, [ebp + 0xb]
008c1bdc  50                       push       eax
008c1bdd  8bce                     mov        ecx, esi
008c1bdf  ff5250                   call       dword ptr [edx + 0x50]
008c1be2  0fb6450b                 movzx      eax, byte ptr [ebp + 0xb]
008c1be6  8b4e54                   mov        ecx, dword ptr [esi + 0x54]
008c1be9  8b11                     mov        edx, dword ptr [ecx]
008c1beb  50                       push       eax
008c1bec  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008c1bef  50                       push       eax
008c1bf0  ff5210                   call       dword ptr [edx + 0x10]
008c1bf3  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c1bf6  64890d00000000           mov        dword ptr fs:[0], ecx
008c1bfd  5f                       pop        edi
008c1bfe  5e                       pop        esi
008c1bff  5b                       pop        ebx
008c1c00  8be5                     mov        esp, ebp
008c1c02  5d                       pop        ebp
008c1c03  c20c00                   ret        0xc
008c1c06  8b16                     mov        edx, dword ptr [esi]
008c1c08  8d450b                   lea        eax, [ebp + 0xb]
008c1c0b  33db                     xor        ebx, ebx
008c1c0d  50                       push       eax
008c1c0e  8bce                     mov        ecx, esi
008c1c10  885d0b                   mov        byte ptr [ebp + 0xb], bl
008c1c13  885d13                   mov        byte ptr [ebp + 0x13], bl
008c1c16  ff5250                   call       dword ptr [edx + 0x50]
008c1c19  8b16                     mov        edx, dword ptr [esi]
008c1c1b  8d4513                   lea        eax, [ebp + 0x13]
008c1c1e  50                       push       eax
008c1c1f  8bce                     mov        ecx, esi
008c1c21  ff5250                   call       dword ptr [edx + 0x50]
008c1c24  8b16                     mov        edx, dword ptr [esi]
008c1c26  8d450f                   lea        eax, [ebp + 0xf]
008c1c29  50                       push       eax
008c1c2a  8bce                     mov        ecx, esi
008c1c2c  885d0f                   mov        byte ptr [ebp + 0xf], bl
008c1c2f  ff5250                   call       dword ptr [edx + 0x50]
008c1c32  0fb64d0f                 movzx      ecx, byte ptr [ebp + 0xf]
008c1c36  0fb65513                 movzx      edx, byte ptr [ebp + 0x13]
008c1c3a  0fb6450b                 movzx      eax, byte ptr [ebp + 0xb]
008c1c3e  51                       push       ecx
008c1c3f  52                       push       edx
008c1c40  50                       push       eax
008c1c41  689413e300               push       0xe31394
008c1c46  ff15bc2eff00             call       dword ptr [0xff2ebc]
008c1c4c  8a4513                   mov        al, byte ptr [ebp + 0x13]
008c1c4f  83c410                   add        esp, 0x10
008c1c52  3ac3                     cmp        al, bl
008c1c54  7534                     jne        0x8c1c8a
008c1c56  0fb64d0f                 movzx      ecx, byte ptr [ebp + 0xf]
008c1c5a  0fb6550b                 movzx      edx, byte ptr [ebp + 0xb]
008c1c5e  51                       push       ecx
008c1c5f  6a01                     push       1
008c1c61  52                       push       edx
008c1c62  8bce                     mov        ecx, esi
008c1c64  e837cfffff               call       0x8beba0
008c1c69  0fb6450f                 movzx      eax, byte ptr [ebp + 0xf]
008c1c6d  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c1c71  50                       push       eax
008c1c72  51                       push       ecx
008c1c73  8bce                     mov        ecx, esi
008c1c75  e8565dbfff               call       0x4b79d0
008c1c7a  0fb6550b                 movzx      edx, byte ptr [ebp + 0xb]
008c1c7e  50                       push       eax
008c1c7f  52                       push       edx
008c1c80  684813e300               push       0xe31348
008c1c85  e9e8000000               jmp        0x8c1d72
008c1c8a  3c01                     cmp        al, 1
008c1c8c  0f8508010000             jne        0x8c1d9a
008c1c92  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c1c96  51                       push       ecx
008c1c97  8bce                     mov        ecx, esi
008c1c99  e8325dbfff               call       0x4b79d0
008c1c9e  85c0                     test       eax, eax
008c1ca0  7520                     jne        0x8c1cc2
008c1ca2  0fb67d0b                 movzx      edi, byte ptr [ebp + 0xb]
008c1ca6  e8d51d2c00               call       0xb83a80
008c1cab  8b4020                   mov        eax, dword ptr [eax + 0x20]
008c1cae  57                       push       edi
008c1caf  8bc8                     mov        ecx, eax
008c1cb1  e87a462c00               call       0xb86330
008c1cb6  0fb6550f                 movzx      edx, byte ptr [ebp + 0xf]
008c1cba  3bc2                     cmp        eax, edx
008c1cbc  0f8e8e410000             jle        0x8c5e50
008c1cc2  807d0f02                 cmp        byte ptr [ebp + 0xf], 2
008c1cc6  740b                     je         0x8c1cd3
008c1cc8  0fb6450b                 movzx      eax, byte ptr [ebp + 0xb]
008c1ccc  889c3008a61000           mov        byte ptr [eax + esi + 0x10a608], bl
008c1cd3  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c1cd7  0fb67d0f                 movzx      edi, byte ptr [ebp + 0xf]
008c1cdb  894dec                   mov        dword ptr [ebp - 0x14], ecx
008c1cde  e8                       .byte      0xe8
008c1cdf  9d                       popfd      