00b12ab0  55                       push       ebp
00b12ab1  8bec                     mov        ebp, esp
00b12ab3  83ec0c                   sub        esp, 0xc
00b12ab6  56                       push       esi
00b12ab7  57                       push       edi
00b12ab8  e883420000               call       0xb16d40
00b12abd  84c0                     test       al, al
00b12abf  740f                     je         0xb12ad0
00b12ac1  8b0df07e2001             mov        ecx, dword ptr [0x1207ef0]
00b12ac7  e894f58eff               call       0x402060
00b12acc  8bf0                     mov        esi, eax
00b12ace  eb06                     jmp        0xb12ad6
00b12ad0  8b35f07e2001             mov        esi, dword ptr [0x1207ef0]
00b12ad6  ff15d8f04001             call       dword ptr [0x140f0d8]
00b12adc  2bc6                     sub        eax, esi
00b12ade  8945fc                   mov        dword ptr [ebp - 4], eax
00b12ae1  db45fc                   fild       dword ptr [ebp - 4]
00b12ae4  33f6                     xor        esi, esi
00b12ae6  53                       push       ebx
00b12ae7  d95df8                   fstp       dword ptr [ebp - 8]
00b12aea  8d9b00000000             lea        ebx, [ebx]
00b12af0  e84b420000               call       0xb16d40
00b12af5  84c0                     test       al, al
00b12af7  740d                     je         0xb12b06
00b12af9  8b8eb07e2001             mov        ecx, dword ptr [esi + 0x1207eb0]
00b12aff  e85cf58eff               call       0x402060
00b12b04  eb06                     jmp        0xb12b0c
00b12b06  8b86b07e2001             mov        eax, dword ptr [esi + 0x1207eb0]
00b12b0c  8945fc                   mov        dword ptr [ebp - 4], eax
00b12b0f  db45fc                   fild       dword ptr [ebp - 4]
00b12b12  d84df8                   fmul       dword ptr [ebp - 8]
00b12b15  d80dac10cc00             fmul       dword ptr [0xcc10ac]
00b12b1b  d95dfc                   fstp       dword ptr [ebp - 4]
00b12b1e  e81d420000               call       0xb16d40
00b12b23  84c0                     test       al, al
00b12b25  7411                     je         0xb12b38
00b12b27  8d4dfc                   lea        ecx, [ebp - 4]
00b12b2a  51                       push       ecx
00b12b2b  8b8e307e2001             mov        ecx, dword ptr [esi + 0x1207e30]
00b12b31  e8da3d95ff               call       0x466910
00b12b36  eb0f                     jmp        0xb12b47
00b12b38  d945fc                   fld        dword ptr [ebp - 4]
00b12b3b  d886307e2001             fadd       dword ptr [esi + 0x1207e30]
00b12b41  d99e307e2001             fstp       dword ptr [esi + 0x1207e30]
00b12b47  e8f4410000               call       0xb16d40
00b12b4c  84c0                     test       al, al
00b12b4e  740d                     je         0xb12b5d
00b12b50  8b8e307e2001             mov        ecx, dword ptr [esi + 0x1207e30]
00b12b56  e8550892ff               call       0x4333b0
00b12b5b  eb06                     jmp        0xb12b63
00b12b5d  d986307e2001             fld        dword ptr [esi + 0x1207e30]
00b12b63  e8dce90e00               call       0xc01544
00b12b68  8bf8                     mov        edi, eax
00b12b6a  e8d1410000               call       0xb16d40
00b12b6f  84c0                     test       al, al
00b12b71  744e                     je         0xb12bc1
00b12b73  8b8e707e2001             mov        ecx, dword ptr [esi + 0x1207e70]
00b12b79  8b5104                   mov        edx, dword ptr [ecx + 4]
00b12b7c  a1d8012101               mov        eax, dword ptr [0x12101d8]
00b12b81  8b4044                   mov        eax, dword ptr [eax + 0x44]
00b12b84  8d0490                   lea        eax, [eax + edx*4]
00b12b87  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00b12b8d  8bd8                     mov        ebx, eax
00b12b8f  33da                     xor        ebx, edx
00b12b91  3318                     xor        ebx, dword ptr [eax]
00b12b93  03df                     add        ebx, edi
00b12b95  33d8                     xor        ebx, eax
00b12b97  33da                     xor        ebx, edx
00b12b99  8918                     mov        dword ptr [eax], ebx
00b12b9b  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00b12ba1  8b4248                   mov        eax, dword ptr [edx + 0x48]
00b12ba4  8b4904                   mov        ecx, dword ptr [ecx + 4]
00b12ba7  8b1488                   mov        edx, dword ptr [eax + ecx*4]
00b12baa  8d0488                   lea        eax, [eax + ecx*4]
00b12bad  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
00b12bb3  33d0                     xor        edx, eax
00b12bb5  33d1                     xor        edx, ecx
00b12bb7  03d7                     add        edx, edi
00b12bb9  33d0                     xor        edx, eax
00b12bbb  33d1                     xor        edx, ecx
00b12bbd  8910                     mov        dword ptr [eax], edx
00b12bbf  eb06                     jmp        0xb12bc7
00b12bc1  01be707e2001             add        dword ptr [esi + 0x1207e70], edi
00b12bc7  e874410000               call       0xb16d40
00b12bcc  84c0                     test       al, al
00b12bce  740d                     je         0xb12bdd
00b12bd0  8b8e307e2001             mov        ecx, dword ptr [esi + 0x1207e30]
00b12bd6  e8d50792ff               call       0x4333b0
00b12bdb  eb06                     jmp        0xb12be3
00b12bdd  d986307e2001             fld        dword ptr [esi + 0x1207e30]
00b12be3  d955fc                   fst        dword ptr [ebp - 4]
00b12be6  d95df4                   fstp       dword ptr [ebp - 0xc]
00b12be9  e852410000               call       0xb16d40
00b12bee  84c0                     test       al, al
00b12bf0  7411                     je         0xb12c03
00b12bf2  8b8e307e2001             mov        ecx, dword ptr [esi + 0x1207e30]
00b12bf8  8d45f4                   lea        eax, [ebp - 0xc]
00b12bfb  50                       push       eax
00b12bfc  e89f279aff               call       0x4b53a0
00b12c01  eb0f                     jmp        0xb12c12
00b12c03  d986307e2001             fld        dword ptr [esi + 0x1207e30]
00b12c09  d865fc                   fsub       dword ptr [ebp - 4]
00b12c0c  d99e307e2001             fstp       dword ptr [esi + 0x1207e30]
00b12c12  83c604                   add        esi, 4
00b12c15  83fe40                   cmp        esi, 0x40
00b12c18  0f8cd2feffff             jl         0xb12af0
00b12c1e  ff15d8f04001             call       dword ptr [0x140f0d8]
00b12c24  8bf0                     mov        esi, eax
00b12c26  e815410000               call       0xb16d40
00b12c2b  84c0                     test       al, al
00b12c2d  5b                       pop        ebx
00b12c2e  7447                     je         0xb12c77
00b12c30  a1f07e2001               mov        eax, dword ptr [0x1207ef0]
00b12c35  8b4804                   mov        ecx, dword ptr [eax + 4]
00b12c38  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00b12c3e  8b5244                   mov        edx, dword ptr [edx + 0x44]
00b12c41  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
00b12c47  8d0c8a                   lea        ecx, [edx + ecx*4]
00b12c4a  83c004                   add        eax, 4
00b12c4d  8bd1                     mov        edx, ecx
00b12c4f  33d7                     xor        edx, edi
00b12c51  33d6                     xor        edx, esi
00b12c53  8911                     mov        dword ptr [ecx], edx
00b12c55  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00b12c5b  8b5148                   mov        edx, dword ptr [ecx + 0x48]
00b12c5e  8b00                     mov        eax, dword ptr [eax]
00b12c60  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
00b12c66  8d0482                   lea        eax, [edx + eax*4]
00b12c69  8bc8                     mov        ecx, eax
00b12c6b  33cf                     xor        ecx, edi
00b12c6d  33ce                     xor        ecx, esi
00b12c6f  5f                       pop        edi
00b12c70  8908                     mov        dword ptr [eax], ecx
00b12c72  5e                       pop        esi
00b12c73  8be5                     mov        esp, ebp
00b12c75  5d                       pop        ebp
00b12c76  c3                       ret        
00b12c77  5f                       pop        edi
00b12c78  8935f07e2001             mov        dword ptr [0x1207ef0], esi
00b12c7e  5e                       pop        esi
00b12c7f  8be5                     mov        esp, ebp
00b12c81  5d                       pop        ebp
00b12c82  c3                       ret        
