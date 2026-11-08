004d80f0  55                       push       ebp
004d80f1  8bec                     mov        ebp, esp
004d80f3  6aff                     push       -1
004d80f5  684685c500               push       0xc58546
004d80fa  64a100000000             mov        eax, dword ptr fs:[0]
004d8100  50                       push       eax
004d8101  64892500000000           mov        dword ptr fs:[0], esp
004d8108  83ec10                   sub        esp, 0x10
004d810b  56                       push       esi
004d810c  8bf1                     mov        esi, ecx
004d810e  e87d3ffcff               call       0x49c090
004d8113  84c0                     test       al, al
004d8115  0f84dd000000             je         0x4d81f8
004d811b  837d08ff                 cmp        dword ptr [ebp + 8], -1
004d811f  57                       push       edi
004d8120  7579                     jne        0x4d819b
004d8122  8b06                     mov        eax, dword ptr [esi]
004d8124  8bce                     mov        ecx, esi
004d8126  ff909c000000             call       dword ptr [eax + 0x9c]
004d812c  33ff                     xor        edi, edi
004d812e  85c0                     test       eax, eax
004d8130  7e48                     jle        0x4d817a
004d8132  897de8                   mov        dword ptr [ebp - 0x18], edi
004d8135  897dec                   mov        dword ptr [ebp - 0x14], edi
004d8138  897df0                   mov        dword ptr [ebp - 0x10], edi
004d813b  8d4d08                   lea        ecx, [ebp + 8]
004d813e  51                       push       ecx
004d813f  8d4de4                   lea        ecx, [ebp - 0x1c]
004d8142  897dfc                   mov        dword ptr [ebp - 4], edi
004d8145  c7450801000000           mov        dword ptr [ebp + 8], 1
004d814c  e8cfeff2ff               call       0x407120
004d8151  8d5508                   lea        edx, [ebp + 8]
004d8154  52                       push       edx
004d8155  8d4de4                   lea        ecx, [ebp - 0x1c]
004d8158  897d08                   mov        dword ptr [ebp + 8], edi
004d815b  e8c0eff2ff               call       0x407120
004d8160  8d4508                   lea        eax, [ebp + 8]
004d8163  50                       push       eax
004d8164  8d4de4                   lea        ecx, [ebp - 0x1c]
004d8167  897d08                   mov        dword ptr [ebp + 8], edi
004d816a  e8b1eff2ff               call       0x407120
004d816f  57                       push       edi
004d8170  57                       push       edi
004d8171  57                       push       edi
004d8172  8d45e4                   lea        eax, [ebp - 0x1c]
004d8175  50                       push       eax
004d8176  6a06                     push       6
004d8178  eb63                     jmp        0x4d81dd
004d817a  8b16                     mov        edx, dword ptr [esi]
004d817c  57                       push       edi
004d817d  57                       push       edi
004d817e  57                       push       edi
004d817f  57                       push       edi
004d8180  57                       push       edi
004d8181  8bce                     mov        ecx, esi
004d8183  ff928c020000             call       dword ptr [edx + 0x28c]
004d8189  5f                       pop        edi
004d818a  5e                       pop        esi
004d818b  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d818e  64890d00000000           mov        dword ptr fs:[0], ecx
004d8195  8be5                     mov        esp, ebp
004d8197  5d                       pop        ebp
004d8198  c20800                   ret        8
004d819b  33ff                     xor        edi, edi
004d819d  897de8                   mov        dword ptr [ebp - 0x18], edi
004d81a0  897dec                   mov        dword ptr [ebp - 0x14], edi
004d81a3  897df0                   mov        dword ptr [ebp - 0x10], edi
004d81a6  8d4508                   lea        eax, [ebp + 8]
004d81a9  50                       push       eax
004d81aa  8d4de4                   lea        ecx, [ebp - 0x1c]
004d81ad  c745fc01000000           mov        dword ptr [ebp - 4], 1
004d81b4  e867eff2ff               call       0x407120
004d81b9  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004d81bc  3bcf                     cmp        ecx, edi
004d81be  7414                     je         0x4d81d4
004d81c0  8b11                     mov        edx, dword ptr [ecx]
004d81c2  ff5244                   call       dword ptr [edx + 0x44]
004d81c5  894508                   mov        dword ptr [ebp + 8], eax
004d81c8  8d4508                   lea        eax, [ebp + 8]
004d81cb  50                       push       eax
004d81cc  8d4de4                   lea        ecx, [ebp - 0x1c]
004d81cf  e84ceff2ff               call       0x407120
004d81d4  57                       push       edi
004d81d5  57                       push       edi
004d81d6  57                       push       edi
004d81d7  8d45e4                   lea        eax, [ebp - 0x1c]
004d81da  50                       push       eax
004d81db  6a0a                     push       0xa
004d81dd  8b16                     mov        edx, dword ptr [esi]
004d81df  8bce                     mov        ecx, esi
004d81e1  ff928c020000             call       dword ptr [edx + 0x28c]
004d81e7  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004d81ea  3bc7                     cmp        eax, edi
004d81ec  7409                     je         0x4d81f7
004d81ee  50                       push       eax
004d81ef  e8e97d7200               call       0xbfffdd
004d81f4  83c404                   add        esp, 4
004d81f7  5f                       pop        edi
004d81f8  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d81fb  5e                       pop        esi
004d81fc  64890d00000000           mov        dword ptr fs:[0], ecx
004d8203  8be5                     mov        esp, ebp
004d8205  5d                       pop        ebp
004d8206  c20800                   ret        8