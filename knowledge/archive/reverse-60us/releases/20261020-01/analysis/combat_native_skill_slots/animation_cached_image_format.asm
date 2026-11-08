00a60810  55                       push       ebp
00a60811  8bec                     mov        ebp, esp
00a60813  81ec00020000             sub        esp, 0x200
00a60819  8b4508                   mov        eax, dword ptr [ebp + 8]
00a6081c  53                       push       ebx
00a6081d  8a5d0c                   mov        bl, byte ptr [ebp + 0xc]
00a60820  33d2                     xor        edx, edx
00a60822  84db                     test       bl, bl
00a60824  0f95c2                   setne      dl
00a60827  56                       push       esi
00a60828  50                       push       eax
00a60829  52                       push       edx
00a6082a  e801c61100               call       0xb7ce30
00a6082f  8bf0                     mov        esi, eax
00a60831  85f6                     test       esi, esi
00a60833  7508                     jne        0xa6083d
00a60835  5e                       pop        esi
00a60836  5b                       pop        ebx
00a60837  8be5                     mov        esp, ebp
00a60839  5d                       pop        ebp
00a6083a  c21000                   ret        0x10
00a6083d  84db                     test       bl, bl
00a6083f  0f84ec000000             je         0xa60931
00a60845  8b4e08                   mov        ecx, dword ptr [esi + 8]
00a60848  85c9                     test       ecx, ecx
00a6084a  7504                     jne        0xa60850
00a6084c  33c0                     xor        eax, eax
00a6084e  eb08                     jmp        0xa60858
00a60850  8b460c                   mov        eax, dword ptr [esi + 0xc]
00a60853  2bc1                     sub        eax, ecx
00a60855  c1f805                   sar        eax, 5
00a60858  85c0                     test       eax, eax
00a6085a  0f8ed1000000             jle        0xa60931
00a60860  c7450c00000000           mov        dword ptr [ebp + 0xc], 0
00a60867  33db                     xor        ebx, ebx
00a60869  894508                   mov        dword ptr [ebp + 8], eax
00a6086c  57                       push       edi
00a6086d  8d4900                   lea        ecx, [ecx]
00a60870  8b7e08                   mov        edi, dword ptr [esi + 8]
00a60873  68e0baca00               push       0xcabae0
00a60878  03fb                     add        edi, ebx
00a6087a  e84ef51900               call       0xbffdcd
00a6087f  83c404                   add        esp, 4
00a60882  50                       push       eax
00a60883  8b4714                   mov        eax, dword ptr [edi + 0x14]
00a60886  68e0baca00               push       0xcabae0
00a6088b  50                       push       eax
00a6088c  6a00                     push       0
00a6088e  8bcf                     mov        ecx, edi
00a60890  e85b379aff               call       0x403ff0
00a60895  85c0                     test       eax, eax
00a60897  747e                     je         0xa60917
00a60899  8b4608                   mov        eax, dword ptr [esi + 8]
00a6089c  8b4c1818                 mov        ecx, dword ptr [eax + ebx + 0x18]
00a608a0  03c3                     add        eax, ebx
00a608a2  83f908                   cmp        ecx, 8
00a608a5  7205                     jb         0xa608ac
00a608a7  8b4004                   mov        eax, dword ptr [eax + 4]
00a608aa  eb03                     jmp        0xa608af
00a608ac  83c004                   add        eax, 4
00a608af  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a608b2  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a608b5  51                       push       ecx
00a608b6  52                       push       edx
00a608b7  50                       push       eax
00a608b8  8d8500feffff             lea        eax, [ebp - 0x200]
00a608be  6800020000               push       0x200
00a608c3  50                       push       eax
00a608c4  e827159aff               call       0x401df0
00a608c9  8b4608                   mov        eax, dword ptr [esi + 8]
00a608cc  8b0e                     mov        ecx, dword ptr [esi]
00a608ce  8b8998000000             mov        ecx, dword ptr [ecx + 0x98]
00a608d4  8b54181c                 mov        edx, dword ptr [eax + ebx + 0x1c]
00a608d8  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00a608db  03c3                     add        eax, ebx
00a608dd  03cf                     add        ecx, edi
00a608df  895104                   mov        dword ptr [ecx + 4], edx
00a608e2  8b4608                   mov        eax, dword ptr [esi + 8]
00a608e5  8b0e                     mov        ecx, dword ptr [esi]
00a608e7  8bb998000000             mov        edi, dword ptr [ecx + 0x98]
00a608ed  8b54181c                 mov        edx, dword ptr [eax + ebx + 0x1c]
00a608f1  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a608f4  03c3                     add        eax, ebx
00a608f6  83c414                   add        esp, 0x14
00a608f9  52                       push       edx
00a608fa  03f9                     add        edi, ecx
00a608fc  8b0dd8300001             mov        ecx, dword ptr [0x10030d8]
00a60902  8b01                     mov        eax, dword ptr [ecx]
00a60904  8d9500feffff             lea        edx, [ebp - 0x200]
00a6090a  52                       push       edx
00a6090b  ff5010                   call       dword ptr [eax + 0x10]
00a6090e  8bc8                     mov        ecx, eax
00a60910  e8bb1a0900               call       0xaf23d0
00a60915  8907                     mov        dword ptr [edi], eax
00a60917  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a6091a  8b4508                   mov        eax, dword ptr [ebp + 8]
00a6091d  83c17c                   add        ecx, 0x7c
00a60920  83c320                   add        ebx, 0x20
00a60923  48                       dec        eax
00a60924  894d0c                   mov        dword ptr [ebp + 0xc], ecx
00a60927  894508                   mov        dword ptr [ebp + 8], eax
00a6092a  0f8540ffffff             jne        0xa60870
00a60930  5f                       pop        edi
00a60931  8b06                     mov        eax, dword ptr [esi]
00a60933  5e                       pop        esi
00a60934  5b                       pop        ebx
00a60935  8be5                     mov        esp, ebp
00a60937  5d                       pop        ebp
00a60938  c2                       .byte      0xc2
