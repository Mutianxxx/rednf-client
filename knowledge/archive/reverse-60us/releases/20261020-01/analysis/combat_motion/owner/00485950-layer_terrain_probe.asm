00485950  55                       push       ebp
00485951  8bec                     mov        ebp, esp
00485953  83ec10                   sub        esp, 0x10
00485956  53                       push       ebx
00485957  56                       push       esi
00485958  8b7508                   mov        esi, dword ptr [ebp + 8]
0048595b  8b06                     mov        eax, dword ptr [esi]
0048595d  57                       push       edi
0048595e  8bd9                     mov        ebx, ecx
00485960  6a11                     push       0x11
00485962  8bce                     mov        ecx, esi
00485964  895dfc                   mov        dword ptr [ebp - 4], ebx
00485967  ff502c                   call       dword ptr [eax + 0x2c]
0048596a  84c0                     test       al, al
0048596c  7536                     jne        0x4859a4
0048596e  8b16                     mov        edx, dword ptr [esi]
00485970  6881000000               push       0x81
00485975  8bce                     mov        ecx, esi
00485977  ff522c                   call       dword ptr [edx + 0x2c]
0048597a  84c0                     test       al, al
0048597c  7526                     jne        0x4859a4
0048597e  8b06                     mov        eax, dword ptr [esi]
00485980  6a21                     push       0x21
00485982  8bce                     mov        ecx, esi
00485984  ff502c                   call       dword ptr [eax + 0x2c]
00485987  84c0                     test       al, al
00485989  0f849a000000             je         0x485a29
0048598f  8b16                     mov        edx, dword ptr [esi]
00485991  8bce                     mov        ecx, esi
00485993  ff923c030000             call       dword ptr [edx + 0x33c]
00485999  8a481d                   mov        cl, byte ptr [eax + 0x1d]
0048599c  84c9                     test       cl, cl
0048599e  0f8485000000             je         0x485a29
004859a4  8b06                     mov        eax, dword ptr [esi]
004859a6  8bce                     mov        ecx, esi
004859a8  ff9094000000             call       dword ptr [eax + 0x94]
004859ae  85c0                     test       eax, eax
004859b0  7d0b                     jge        0x4859bd
004859b2  5f                       pop        edi
004859b3  5e                       pop        esi
004859b4  32c0                     xor        al, al
004859b6  5b                       pop        ebx
004859b7  8be5                     mov        esp, ebp
004859b9  5d                       pop        ebp
004859ba  c20400                   ret        4
004859bd  8b8318020000             mov        eax, dword ptr [ebx + 0x218]
004859c3  85c0                     test       eax, eax
004859c5  7504                     jne        0x4859cb
004859c7  33ff                     xor        edi, edi
004859c9  eb19                     jmp        0x4859e4
004859cb  8b8b1c020000             mov        ecx, dword ptr [ebx + 0x21c]
004859d1  2bc8                     sub        ecx, eax
004859d3  b8398ee338               mov        eax, 0x38e38e39
004859d8  f7e9                     imul       ecx
004859da  c1fa03                   sar        edx, 3
004859dd  8bfa                     mov        edi, edx
004859df  c1ef1f                   shr        edi, 0x1f
004859e2  03fa                     add        edi, edx
004859e4  8b16                     mov        edx, dword ptr [esi]
004859e6  8bce                     mov        ecx, esi
004859e8  ff9294000000             call       dword ptr [edx + 0x94]
004859ee  69ffe0000000             imul       edi, edi, 0xe0
004859f4  3bc7                     cmp        eax, edi
004859f6  7dba                     jge        0x4859b2
004859f8  8b06                     mov        eax, dword ptr [esi]
004859fa  8bce                     mov        ecx, esi
004859fc  ff9098000000             call       dword ptr [eax + 0x98]
00485a02  85c0                     test       eax, eax
00485a04  7cac                     jl         0x4859b2
00485a06  8bcb                     mov        ecx, ebx
00485a08  e8c30f0000               call       0x4869d0
00485a0d  8bf8                     mov        edi, eax
00485a0f  8bcb                     mov        ecx, ebx
00485a11  6bff78                   imul       edi, edi, 0x78
00485a14  e887120000               call       0x486ca0
00485a19  8b16                     mov        edx, dword ptr [esi]
00485a1b  8bce                     mov        ecx, esi
00485a1d  03f8                     add        edi, eax
00485a1f  ff9298000000             call       dword ptr [edx + 0x98]
00485a25  3bc7                     cmp        eax, edi
00485a27  7d89                     jge        0x4859b2
00485a29  8b06                     mov        eax, dword ptr [esi]
00485a2b  8bce                     mov        ecx, esi
00485a2d  ff90fc010000             call       dword ptr [eax + 0x1fc]
00485a33  85c0                     test       eax, eax
00485a35  7512                     jne        0x485a49
00485a37  8b16                     mov        edx, dword ptr [esi]
00485a39  8bce                     mov        ecx, esi
00485a3b  ff9200020000             call       dword ptr [edx + 0x200]
00485a41  85c0                     test       eax, eax
00485a43  0f84db010000             je         0x485c24
00485a49  8b8374010000             mov        eax, dword ptr [ebx + 0x174]
00485a4f  33c9                     xor        ecx, ecx
00485a51  3bc1                     cmp        eax, ecx
00485a53  7477                     je         0x485acc
00485a55  8bbb78010000             mov        edi, dword ptr [ebx + 0x178]
00485a5b  2bf8                     sub        edi, eax
00485a5d  c1ff04                   sar        edi, 4
00485a60  3bf9                     cmp        edi, ecx
00485a62  7e68                     jle        0x485acc
00485a64  884d0b                   mov        byte ptr [ebp + 0xb], cl
00485a67  894df8                   mov        dword ptr [ebp - 8], ecx
00485a6a  894dfc                   mov        dword ptr [ebp - 4], ecx
00485a6d  8d4900                   lea        ecx, [ecx]
00485a70  8b8374010000             mov        eax, dword ptr [ebx + 0x174]
00485a76  0345fc                   add        eax, dword ptr [ebp - 4]
00485a79  50                       push       eax
00485a7a  8b06                     mov        eax, dword ptr [esi]
00485a7c  8bce                     mov        ecx, esi
00485a7e  ff9098000000             call       dword ptr [eax + 0x98]
00485a84  8b16                     mov        edx, dword ptr [esi]
00485a86  50                       push       eax
00485a87  8bce                     mov        ecx, esi
00485a89  ff9294000000             call       dword ptr [edx + 0x94]
00485a8f  50                       push       eax
00485a90  e81b804200               call       0x8adab0
00485a95  83c40c                   add        esp, 0xc
00485a98  84c0                     test       al, al
00485a9a  7520                     jne        0x485abc
00485a9c  8b45f8                   mov        eax, dword ptr [ebp - 8]
00485a9f  8b55fc                   mov        edx, dword ptr [ebp - 4]
00485aa2  40                       inc        eax
00485aa3  83c210                   add        edx, 0x10
00485aa6  3bc7                     cmp        eax, edi
00485aa8  8945f8                   mov        dword ptr [ebp - 8], eax
00485aab  8955fc                   mov        dword ptr [ebp - 4], edx
00485aae  7cc0                     jl         0x485a70
00485ab0  8a450b                   mov        al, byte ptr [ebp + 0xb]
00485ab3  5f                       pop        edi
00485ab4  5e                       pop        esi
00485ab5  5b                       pop        ebx
00485ab6  8be5                     mov        esp, ebp
00485ab8  5d                       pop        ebp
00485ab9  c20400                   ret        4
00485abc  5f                       pop        edi
00485abd  c6450b01                 mov        byte ptr [ebp + 0xb], 1
00485ac1  8a450b                   mov        al, byte ptr [ebp + 0xb]
00485ac4  5e                       pop        esi
00485ac5  5b                       pop        ebx
00485ac6  8be5                     mov        esp, ebp
00485ac8  5d                       pop        ebp
00485ac9  c20400                   ret        4
00485acc  8b06                     mov        eax, dword ptr [esi]
00485ace  8bce                     mov        ecx, esi
00485ad0  ff9014020000             call       dword ptr [eax + 0x214]
00485ad6  8b16                     mov        edx, dword ptr [esi]
00485ad8  8bce                     mov        ecx, esi
00485ada  8bf8                     mov        edi, eax
00485adc  ff920c020000             call       dword ptr [edx + 0x20c]
00485ae2  99                       cdq        
00485ae3  83e20f                   and        edx, 0xf
00485ae6  03c2                     add        eax, edx
00485ae8  8bd8                     mov        ebx, eax
00485aea  b8abaaaa2a               mov        eax, 0x2aaaaaab
00485aef  f7ef                     imul       edi
00485af1  8b06                     mov        eax, dword ptr [esi]
00485af3  d1fa                     sar        edx, 1
00485af5  8bfa                     mov        edi, edx
00485af7  c1ef1f                   shr        edi, 0x1f
00485afa  8bce                     mov        ecx, esi
00485afc  c1fb04                   sar        ebx, 4
00485aff  03fa                     add        edi, edx
00485b01  ff9018020000             call       dword ptr [eax + 0x218]
00485b07  8b16                     mov        edx, dword ptr [esi]
00485b09  8bce                     mov        ecx, esi
00485b0b  894508                   mov        dword ptr [ebp + 8], eax
00485b0e  ff9210020000             call       dword ptr [edx + 0x210]
00485b14  99                       cdq        
00485b15  83e20f                   and        edx, 0xf
00485b18  03c2                     add        eax, edx
00485b1a  8bc8                     mov        ecx, eax
00485b1c  b8abaaaa2a               mov        eax, 0x2aaaaaab
00485b21  f76d08                   imul       dword ptr [ebp + 8]
00485b24  d1fa                     sar        edx, 1
00485b26  8bc2                     mov        eax, edx
00485b28  c1e81f                   shr        eax, 0x1f
00485b2b  03c2                     add        eax, edx
00485b2d  c1f904                   sar        ecx, 4
00485b30  894508                   mov        dword ptr [ebp + 8], eax
00485b33  33c0                     xor        eax, eax
00485b35  85db                     test       ebx, ebx
00485b37  0f9cc0                   setl       al
00485b3a  33d2                     xor        edx, edx
00485b3c  894df8                   mov        dword ptr [ebp - 8], ecx
00485b3f  48                       dec        eax
00485b40  23c3                     and        eax, ebx
00485b42  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
00485b45  85ff                     test       edi, edi
00485b47  0f9cc2                   setl       dl
00485b4a  8945f0                   mov        dword ptr [ebp - 0x10], eax
00485b4d  8b8318020000             mov        eax, dword ptr [ebx + 0x218]
00485b53  4a                       dec        edx
00485b54  23d7                     and        edx, edi
00485b56  85c0                     test       eax, eax
00485b58  8955f4                   mov        dword ptr [ebp - 0xc], edx
00485b5b  7419                     je         0x485b76
00485b5d  8b931c020000             mov        edx, dword ptr [ebx + 0x21c]
00485b63  2bd0                     sub        edx, eax
00485b65  b8398ee338               mov        eax, 0x38e38e39
00485b6a  f7ea                     imul       edx
00485b6c  c1fa03                   sar        edx, 3
00485b6f  8bc2                     mov        eax, edx
00485b71  c1e81f                   shr        eax, 0x1f
00485b74  03c2                     add        eax, edx
00485b76  6bc00e                   imul       eax, eax, 0xe
00485b79  48                       dec        eax
00485b7a  3bc1                     cmp        eax, ecx
00485b7c  7d0b                     jge        0x485b89
00485b7e  8bcb                     mov        ecx, ebx
00485b80  e8eb0e0000               call       0x486a70
00485b85  48                       dec        eax
00485b86  8945f8                   mov        dword ptr [ebp - 8], eax
00485b89  8bcb                     mov        ecx, ebx
00485b8b  e8a0100000               call       0x486c30
00485b90  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00485b93  48                       dec        eax
00485b94  3bc1                     cmp        eax, ecx
00485b96  7d0b                     jge        0x485ba3
00485b98  8bcb                     mov        ecx, ebx
00485b9a  e891100000               call       0x486c30
00485b9f  48                       dec        eax
00485ba0  894508                   mov        dword ptr [ebp + 8], eax
00485ba3  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00485ba6  3b45f8                   cmp        eax, dword ptr [ebp - 8]
00485ba9  8945fc                   mov        dword ptr [ebp - 4], eax
00485bac  7f76                     jg         0x485c24
00485bae  8bff                     mov        edi, edi
00485bb0  8b7df4                   mov        edi, dword ptr [ebp - 0xc]
00485bb3  8b4508                   mov        eax, dword ptr [ebp + 8]
00485bb6  8bcf                     mov        ecx, edi
00485bb8  3bc8                     cmp        ecx, eax
00485bba  7f5a                     jg         0x485c16
00485bbc  8d642400                 lea        esp, [esp]
00485bc0  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00485bc3  57                       push       edi
00485bc4  51                       push       ecx
00485bc5  8bcb                     mov        ecx, ebx
00485bc7  e8b4f9ffff               call       0x485580
00485bcc  48                       dec        eax
00485bcd  83f803                   cmp        eax, 3
00485bd0  773c                     ja         0x485c0e
00485bd2  ff2485305c4800           jmp        dword ptr [eax*4 + 0x485c30]
00485bd9  8b16                     mov        edx, dword ptr [esi]
00485bdb  8bce                     mov        ecx, esi
00485bdd  ff9208020000             call       dword ptr [edx + 0x208]
00485be3  85c0                     test       eax, eax
00485be5  0f8ec7fdffff             jle        0x4859b2
00485beb  eb21                     jmp        0x485c0e
00485bed  8b06                     mov        eax, dword ptr [esi]
00485bef  8bce                     mov        ecx, esi
00485bf1  ff90c4010000             call       dword ptr [eax + 0x1c4]
00485bf7  85c0                     test       eax, eax
00485bf9  eb0d                     jmp        0x485c08
00485bfb  8b16                     mov        edx, dword ptr [esi]
00485bfd  8bce                     mov        ecx, esi
00485bff  ff92c4010000             call       dword ptr [edx + 0x1c4]
00485c05  83f801                   cmp        eax, 1
00485c08  0f85a4fdffff             jne        0x4859b2
00485c0e  8b4508                   mov        eax, dword ptr [ebp + 8]
00485c11  47                       inc        edi
00485c12  3bf8                     cmp        edi, eax
00485c14  7eaa                     jle        0x485bc0
00485c16  8b45fc                   mov        eax, dword ptr [ebp - 4]
00485c19  8b4df8                   mov        ecx, dword ptr [ebp - 8]
00485c1c  40                       inc        eax
00485c1d  3bc1                     cmp        eax, ecx
00485c1f  8945fc                   mov        dword ptr [ebp - 4], eax
00485c22  7e8c                     jle        0x485bb0
00485c24  5f                       pop        edi
00485c25  5e                       pop        esi
00485c26  b001                     mov        al, 1
00485c28  5b                       pop        ebx
00485c29  8be5                     mov        esp, ebp
00485c2b  5d                       pop        ebp
00485c2c  c20400                   ret        4
00485c2f  90                       nop        
00485c30  d95b48                   fstp       dword ptr [ebx + 0x48]
00485c33  00b2594800ed             add        byte ptr [edx - 0x12ffb7a7], dh
00485c39  5b                       pop        ebx
00485c3a  48                       dec        eax
00485c3b  00fb                     add        bl, bh
00485c3d  5b                       pop        ebx
00485c3e  48                       dec        eax
00485c3f  00                       .byte      0x00
