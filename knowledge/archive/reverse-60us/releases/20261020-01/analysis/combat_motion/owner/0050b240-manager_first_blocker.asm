0050b240  55                       push       ebp
0050b241  8bec                     mov        ebp, esp
0050b243  53                       push       ebx
0050b244  8bd9                     mov        ebx, ecx
0050b246  8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
0050b249  85c9                     test       ecx, ecx
0050b24b  56                       push       esi
0050b24c  57                       push       edi
0050b24d  7504                     jne        0x50b253
0050b24f  33c0                     xor        eax, eax
0050b251  eb08                     jmp        0x50b25b
0050b253  8b4314                   mov        eax, dword ptr [ebx + 0x14]
0050b256  2bc1                     sub        eax, ecx
0050b258  c1f802                   sar        eax, 2
0050b25b  33c9                     xor        ecx, ecx
0050b25d  85c0                     test       eax, eax
0050b25f  7e12                     jle        0x50b273
0050b261  8b5310                   mov        edx, dword ptr [ebx + 0x10]
0050b264  8b7d08                   mov        edi, dword ptr [ebp + 8]
0050b267  393a                     cmp        dword ptr [edx], edi
0050b269  7411                     je         0x50b27c
0050b26b  41                       inc        ecx
0050b26c  83c204                   add        edx, 4
0050b26f  3bc8                     cmp        ecx, eax
0050b271  7cf4                     jl         0x50b267
0050b273  5f                       pop        edi
0050b274  5e                       pop        esi
0050b275  33c0                     xor        eax, eax
0050b277  5b                       pop        ebx
0050b278  5d                       pop        ebp
0050b279  c20400                   ret        4
0050b27c  8b07                     mov        eax, dword ptr [edi]
0050b27e  8bcf                     mov        ecx, edi
0050b280  ff90fc010000             call       dword ptr [eax + 0x1fc]
0050b286  85c0                     test       eax, eax
0050b288  750e                     jne        0x50b298
0050b28a  8b17                     mov        edx, dword ptr [edi]
0050b28c  8bcf                     mov        ecx, edi
0050b28e  ff9200020000             call       dword ptr [edx + 0x200]
0050b294  85c0                     test       eax, eax
0050b296  74db                     je         0x50b273
0050b298  8bb390000000             mov        esi, dword ptr [ebx + 0x90]
0050b29e  3bb394000000             cmp        esi, dword ptr [ebx + 0x94]
0050b2a4  74cd                     je         0x50b273
0050b2a6  8b06                     mov        eax, dword ptr [esi]
0050b2a8  3bc7                     cmp        eax, edi
0050b2aa  740f                     je         0x50b2bb
0050b2ac  8b17                     mov        edx, dword ptr [edi]
0050b2ae  50                       push       eax
0050b2af  8bcf                     mov        ecx, edi
0050b2b1  ff9244020000             call       dword ptr [edx + 0x244]
0050b2b7  84c0                     test       al, al
0050b2b9  7516                     jne        0x50b2d1
0050b2bb  8b8394000000             mov        eax, dword ptr [ebx + 0x94]
0050b2c1  83c604                   add        esi, 4
0050b2c4  3bf0                     cmp        esi, eax
0050b2c6  75de                     jne        0x50b2a6
0050b2c8  5f                       pop        edi
0050b2c9  5e                       pop        esi
0050b2ca  33c0                     xor        eax, eax
0050b2cc  5b                       pop        ebx
0050b2cd  5d                       pop        ebp
0050b2ce  c20400                   ret        4
0050b2d1  8b06                     mov        eax, dword ptr [esi]
0050b2d3  5f                       pop        edi
0050b2d4  5e                       pop        esi
0050b2d5  5b                       pop        ebx
0050b2d6  5d                       pop        ebp
0050b2d7  c20400                   ret        4
