00ac9a10  50                       push       eax
00ac9a11  64892500000000           mov        dword ptr fs:[0], esp
00ac9a18  83ec3c                   sub        esp, 0x3c
00ac9a1b  53                       push       ebx
00ac9a1c  56                       push       esi
00ac9a1d  8b7518                   mov        esi, dword ptr [ebp + 0x18]
00ac9a20  33db                     xor        ebx, ebx
00ac9a22  8bc6                     mov        eax, esi
00ac9a24  2bc3                     sub        eax, ebx
00ac9a26  57                       push       edi
00ac9a27  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00ac9a2a  895df0                   mov        dword ptr [ebp - 0x10], ebx
00ac9a2d  7408                     je         0xac9a37
00ac9a2f  48                       dec        eax
00ac9a30  7513                     jne        0xac9a45
00ac9a32  57                       push       edi
00ac9a33  6a01                     push       1
00ac9a35  eb02                     jmp        0xac9a39
00ac9a37  57                       push       edi
00ac9a38  53                       push       ebx
00ac9a39  e8820a0000               call       0xaca4c0
00ac9a3e  8bc8                     mov        ecx, eax
00ac9a40  e8abb1fcff               call       0xa94bf0
00ac9a45  c1e604                   shl        esi, 4
00ac9a48  399e6cab0d01             cmp        dword ptr [esi + 0x10dab6c], ebx
00ac9a4e  0f8450010000             je         0xac9ba4
00ac9a54  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00ac9a57  3bc3                     cmp        eax, ebx
00ac9a59  0f84b2000000             je         0xac9b11
00ac9a5f  8b00                     mov        eax, dword ptr [eax]
00ac9a61  3bc3                     cmp        eax, ebx
00ac9a63  0f84a8000000             je         0xac9b11
00ac9a69  83f802                   cmp        eax, 2
00ac9a6c  755c                     jne        0xac9aca
00ac9a6e  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00ac9a71  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00ac9a74  57                       push       edi
00ac9a75  50                       push       eax
00ac9a76  51                       push       ecx
00ac9a77  8d55b8                   lea        edx, [ebp - 0x48]
00ac9a7a  52                       push       edx
00ac9a7b  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9a81  e8caf9ffff               call       0xac9450
00ac9a86  395dcc                   cmp        dword ptr [ebp - 0x34], ebx
00ac9a89  c745fc01000000           mov        dword ptr [ebp - 4], 1
00ac9a90  7429                     je         0xac9abb
00ac9a92  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9a95  8d45b8                   lea        eax, [ebp - 0x48]
00ac9a98  50                       push       eax
00ac9a99  8bce                     mov        ecx, esi
00ac9a9b  e8705094ff               call       0x40eb10
00ac9aa0  8d4db8                   lea        ecx, [ebp - 0x48]
00ac9aa3  e8c8450c00               call       0xb8e070
00ac9aa8  5f                       pop        edi
00ac9aa9  8bc6                     mov        eax, esi
00ac9aab  5e                       pop        esi
00ac9aac  5b                       pop        ebx
00ac9aad  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac9ab0  64890d00000000           mov        dword ptr fs:[0], ecx
00ac9ab7  8be5                     mov        esp, ebp
00ac9ab9  5d                       pop        ebp
00ac9aba  c3                       ret        
00ac9abb  8d4db8                   lea        ecx, [ebp - 0x48]
00ac9abe  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00ac9ac5  e8a6450c00               call       0xb8e070
00ac9aca  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00ac9acd  3bc3                     cmp        eax, ebx
00ac9acf  7402                     je         0xac9ad3
00ac9ad1  8918                     mov        dword ptr [eax], ebx
00ac9ad3  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9ad6  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9add  895e14                   mov        dword ptr [esi + 0x14], ebx
00ac9ae0  68e0baca00               push       0xcabae0
00ac9ae5  66895e04                 mov        word ptr [esi + 4], bx
00ac9ae9  e8df621300               call       0xbffdcd
00ac9aee  83c404                   add        esp, 4
00ac9af1  50                       push       eax
00ac9af2  68e0baca00               push       0xcabae0
00ac9af7  8bce                     mov        ecx, esi
00ac9af9  e8829393ff               call       0x402e80
00ac9afe  5f                       pop        edi
00ac9aff  8bc6                     mov        eax, esi
00ac9b01  5e                       pop        esi
00ac9b02  5b                       pop        ebx
00ac9b03  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac9b06  64890d00000000           mov        dword ptr fs:[0], ecx
00ac9b0d  8be5                     mov        esp, ebp
00ac9b0f  5d                       pop        ebp
00ac9b10  c3                       ret        
00ac9b11  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00ac9b14  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac9b17  57                       push       edi
00ac9b18  51                       push       ecx
00ac9b19  52                       push       edx
00ac9b1a  8d45d4                   lea        eax, [ebp - 0x2c]
00ac9b1d  50                       push       eax
00ac9b1e  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9b24  e827f9ffff               call       0xac9450
00ac9b29  395de8                   cmp        dword ptr [ebp - 0x18], ebx
00ac9b2c  895dfc                   mov        dword ptr [ebp - 4], ebx
00ac9b2f  7451                     je         0xac9b82
00ac9b31  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00ac9b34  3bc3                     cmp        eax, ebx
00ac9b36  7406                     je         0xac9b3e
00ac9b38  c70002000000             mov        dword ptr [eax], 2
00ac9b3e  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9b41  6aff                     push       -1
00ac9b43  53                       push       ebx
00ac9b44  8d4dd4                   lea        ecx, [ebp - 0x2c]
00ac9b47  51                       push       ecx
00ac9b48  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9b4f  895e14                   mov        dword ptr [esi + 0x14], ebx
00ac9b52  8bce                     mov        ecx, esi
00ac9b54  66895e04                 mov        word ptr [esi + 4], bx
00ac9b58  e8039293ff               call       0x402d60
00ac9b5d  837dec08                 cmp        dword ptr [ebp - 0x14], 8
00ac9b61  729b                     jb         0xac9afe
00ac9b63  8b55d8                   mov        edx, dword ptr [ebp - 0x28]
00ac9b66  52                       push       edx
00ac9b67  e871641300               call       0xbfffdd
00ac9b6c  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac9b6f  83c404                   add        esp, 4
00ac9b72  5f                       pop        edi
00ac9b73  8bc6                     mov        eax, esi
00ac9b75  5e                       pop        esi
00ac9b76  5b                       pop        ebx
00ac9b77  64890d00000000           mov        dword ptr fs:[0], ecx
00ac9b7e  8be5                     mov        esp, ebp
00ac9b80  5d                       pop        ebp
00ac9b81  c3                       ret        
00ac9b82  837dec08                 cmp        dword ptr [ebp - 0x14], 8
00ac9b86  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00ac9b8d  0f8237ffffff             jb         0xac9aca
00ac9b93  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00ac9b96  50                       push       eax
00ac9b97  e841641300               call       0xbfffdd
00ac9b9c  83c404                   add        esp, 4
00ac9b9f  e926ffffff               jmp        0xac9aca
00ac9ba4  68a036e100               push       0xe136a0
00ac9ba9  57                       push       edi
00ac9baa  e87a811300               call       0xc01d29
00ac9baf  8bf0                     mov        esi, eax
00ac9bb1  83c408                   add        esp, 8
00ac9bb4  3bf3                     cmp        esi, ebx
00ac9bb6  0f840effffff             je         0xac9aca
00ac9bbc  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00ac9bbf  3bc3                     cmp        eax, ebx
00ac9bc1  7406                     je         0xac9bc9
00ac9bc3  c70001000000             mov        dword ptr [eax], 1
00ac9bc9  395d14                   cmp        dword ptr [ebp + 0x14], ebx
00ac9bcc  7411                     je         0xac9bdf
00ac9bce  8b4e10                   mov        ecx, dword ptr [esi + 0x10]
00ac9bd1  51                       push       ecx
00ac9bd2  e8f3a51300               call       0xc041ca
00ac9bd7  8b5514                   mov        edx, dword ptr [ebp + 0x14]
00ac9bda  83c404                   add        esp, 4
00ac9bdd  8902                     mov        dword ptr [edx], eax
00ac9bdf  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac9be2  3bc3                     cmp        eax, ebx
00ac9be4  7402                     je         0xac9be8
00ac9be6  8918                     mov        dword ptr [eax], ebx
00ac9be8  56                       push       esi
00ac9be9  e88e801300               call       0xc01c7c
00ac9bee  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9bf1  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9bf8  895e14                   mov        dword ptr [esi + 0x14], ebx
00ac9bfb  57                       push       edi
00ac9bfc  66895e04                 mov        word ptr [esi + 4], bx
00ac9c00  e8c8611300               call       0xbffdcd
00ac9c05  83c408                   add        esp, 8
00ac9c08  50                       push       eax
00ac9c09  57                       push       edi
00ac9c0a  e9e8feffff               jmp        0xac9af7
00ac9c0f  cc                       int3       
00ac9c10  55                       push       ebp
00ac9c11  8bec                     mov        ebp, esp
00ac9c13  53                       push       ebx
00ac9c14  56                       push       esi
00ac9c15  8b7514                   mov        esi, dword ptr [ebp + 0x14]
00ac9c18  8bc6                     mov        eax, esi
00ac9c1a  83e800                   sub        eax, 0
00ac9c1d  57                       push       edi
00ac9c1e  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00ac9c21  7408                     je         0xac9c2b
00ac9c23  48                       dec        eax
00ac9c24  7514                     jne        0xac9c3a
00ac9c26  57                       push       edi
00ac9c27  6a01                     push       1
00ac9c29  eb03                     jmp        0xac9c2e
00ac9c2b  57                       push       edi
00ac9c2c  6a00                     push       0
00ac9c2e  e88d080000               call       0xaca4c0
00ac9c33  8bc8                     mov        ecx, eax
00ac9c35  e8b6affcff               call       0xa94bf0
00ac9c3a  8b5d18                   mov        ebx, dword ptr [ebp + 0x18]
00ac9c3d  c1e604                   shl        esi, 4
00ac9c40  8b866cab0d01             mov        eax, dword ptr [esi + 0x10dab6c]
00ac9c46  85c0                     test       eax, eax
00ac9c48  745f                     je         0xac9ca9
00ac9c4a  85db                     test       ebx, ebx
00ac9c4c  7434                     je         0xac9c82
00ac9c4e  8b03                     mov        eax, dword ptr [ebx]
00ac9c50  85c0                     test       eax, eax
00ac9c52  742e                     je         0xac9c82
00ac9c54  83f802                   cmp        eax, 2
00ac9c57  7518                     jne        0xac9c71
00ac9c59  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac9c5c  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00ac9c5f  57                       push       edi
00ac9c60  50                       push       eax
00ac9c61  51                       push       ecx
00ac9c62  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9c68  e843f9ffff               call       0xac95b0
00ac9c6d  85c0                     test       eax, eax
00ac9c6f  750c                     jne        0xac9c7d
00ac9c71  85db                     test       ebx, ebx
00ac9c73  7406                     je         0xac9c7b
00ac9c75  c70300000000             mov        dword ptr [ebx], 0
00ac9c7b  33c0                     xor        eax, eax
00ac9c7d  5f                       pop        edi
00ac9c7e  5e                       pop        esi
00ac9c7f  5b                       pop        ebx
00ac9c80  5d                       pop        ebp
00ac9c81  c3                       ret        
00ac9c82  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac9c85  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9c88  57                       push       edi
00ac9c89  52                       push       edx
00ac9c8a  50                       push       eax
00ac9c8b  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9c91  e81af9ffff               call       0xac95b0
00ac9c96  85c0                     test       eax, eax
00ac9c98  74d7                     je         0xac9c71
00ac9c9a  85db                     test       ebx, ebx
00ac9c9c  74df                     je         0xac9c7d
00ac9c9e  5f                       pop        edi
00ac9c9f  5e                       pop        esi
00ac9ca0  c70302000000             mov        dword ptr [ebx], 2
00ac9ca6  5b                       pop        ebx
00ac9ca7  5d                       pop        ebp
00ac9ca8  c3                       ret        
00ac9ca9  68a036e100               push       0xe136a0
00ac9cae  57                       push       edi
00ac9caf  e875801300               call       0xc01d29
00ac9cb4  8bf8                     mov        edi, eax
00ac9cb6  83c408                   add        esp, 8
00ac9cb9  85ff                     test       edi, edi
00ac9cbb  74b4                     je         0xac9c71
00ac9cbd  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00ac9cc0  85c0                     test       eax, eax
00ac9cc2  7406                     je         0xac9cca
00ac9cc4  c70001000000             mov        dword ptr [eax], 1
00ac9cca  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00ac9ccd  85f6                     test       esi, esi
00ac9ccf  740e                     je         0xac9cdf
00ac9cd1  8b4f10                   mov        ecx, dword ptr [edi + 0x10]
00ac9cd4  51                       push       ecx
00ac9cd5  e8f0a41300               call       0xc041ca
00ac9cda  83c404                   add        esp, 4
00ac9cdd  8906                     mov        dword ptr [esi], eax
00ac9cdf  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9ce2  85c0                     test       eax, eax
00ac9ce4  7406                     je         0xac9cec
00ac9ce6  c70000000000             mov        dword ptr [eax], 0
00ac9cec  8bc7                     mov        eax, edi
00ac9cee  5f                       pop        edi
00ac9cef  5e                       pop        esi
00ac9cf0  5b                       pop        ebx
00ac9cf1  5d                       pop        ebp
00ac9cf2  c3                       ret        