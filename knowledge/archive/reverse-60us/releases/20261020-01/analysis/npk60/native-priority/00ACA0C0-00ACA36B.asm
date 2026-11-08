00aca0c0  55                       push       ebp
00aca0c1  8bec                     mov        ebp, esp
00aca0c3  6aff                     push       -1
00aca0c5  64a100000000             mov        eax, dword ptr fs:[0]
00aca0cb  683c34c900               push       0xc9343c
00aca0d0  50                       push       eax
00aca0d1  b8541a0000               mov        eax, 0x1a54
00aca0d6  64892500000000           mov        dword ptr fs:[0], esp
00aca0dd  e8ee6d1300               call       0xc00ed0
00aca0e2  53                       push       ebx
00aca0e3  56                       push       esi
00aca0e4  8bd9                     mov        ebx, ecx
00aca0e6  57                       push       edi
00aca0e7  8d4dbc                   lea        ecx, [ebp - 0x44]
00aca0ea  e861ffffff               call       0xaca050
00aca0ef  8b7508                   mov        esi, dword ptr [ebp + 8]
00aca0f2  56                       push       esi
00aca0f3  6800040000               push       0x400
00aca0f8  8d85a0f5ffff             lea        eax, [ebp - 0xa60]
00aca0fe  33ff                     xor        edi, edi
00aca100  50                       push       eax
00aca101  897dfc                   mov        dword ptr [ebp - 4], edi
00aca104  e8877093ff               call       0x401190
00aca109  8d8da0f5ffff             lea        ecx, [ebp - 0xa60]
00aca10f  51                       push       ecx
00aca110  e8b85c1300               call       0xbffdcd
00aca115  83c404                   add        esp, 4
00aca118  3bc7                     cmp        eax, edi
00aca11a  7e26                     jle        0xaca142
00aca11c  668b8c459ef5ffff         mov        cx, word ptr [ebp + eax*2 - 0xa62]
00aca124  6683f95c                 cmp        cx, 0x5c
00aca128  7418                     je         0xaca142
00aca12a  6683f92f                 cmp        cx, 0x2f
00aca12e  7412                     je         0xaca142
00aca130  66c78445a0f5ffff5c00     mov        word ptr [ebp + eax*2 - 0xa60], 0x5c
00aca13a  6689bc45a2f5ffff         mov        word ptr [ebp + eax*2 - 0xa5e], di
00aca142  8d95a0e5ffff             lea        edx, [ebp - 0x1a60]
00aca148  52                       push       edx
00aca149  6800040000               push       0x400
00aca14e  ff1588f34001             call       dword ptr [0x140f388]
00aca154  56                       push       esi
00aca155  ff15e8f34001             call       dword ptr [0x140f3e8]
00aca15b  8d85a0fdffff             lea        eax, [ebp - 0x260]
00aca161  50                       push       eax
00aca162  68b07ce600               push       0xe67cb0
00aca167  897d08                   mov        dword ptr [ebp + 8], edi
00aca16a  e8b3a11300               call       0xc04322
00aca16f  8bf8                     mov        edi, eax
00aca171  83c408                   add        esp, 8
00aca174  83ffff                   cmp        edi, -1
00aca177  897de8                   mov        dword ptr [ebp - 0x18], edi
00aca17a  0f84b9010000             je         0xaca339
00aca180  8d8db4fdffff             lea        ecx, [ebp - 0x24c]
00aca186  68a036e100               push       0xe136a0
00aca18b  51                       push       ecx
00aca18c  e8987b1300               call       0xc01d29
00aca191  8bf0                     mov        esi, eax
00aca193  83c408                   add        esp, 8
00aca196  85f6                     test       esi, esi
00aca198  8975f0                   mov        dword ptr [ebp - 0x10], esi
00aca19b  0f8462010000             je         0xaca303
00aca1a1  56                       push       esi
00aca1a2  e859ecffff               call       0xac8e00
00aca1a7  83c404                   add        esp, 4
00aca1aa  85c0                     test       eax, eax
00aca1ac  7538                     jne        0xaca1e6
00aca1ae  56                       push       esi
00aca1af  e8c87a1300               call       0xc01c7c
00aca1b4  68707ce600               push       0xe67c70
00aca1b9  ff15bc2eff00             call       dword ptr [0xff2ebc]
00aca1bf  8d95b4fdffff             lea        edx, [ebp - 0x24c]
00aca1c5  52                       push       edx
00aca1c6  68347ce600               push       0xe67c34
00aca1cb  ff15bc2eff00             call       dword ptr [0xff2ebc]
00aca1d1  8d85a0fdffff             lea        eax, [ebp - 0x260]
00aca1d7  50                       push       eax
00aca1d8  57                       push       edi
00aca1d9  e821a21300               call       0xc043ff
00aca1de  83c418                   add        esp, 0x18
00aca1e1  e942010000               jmp        0xaca328
00aca1e6  6a00                     push       0
00aca1e8  6a00                     push       0
00aca1ea  56                       push       esi
00aca1eb  e8c4841300               call       0xc026b4
00aca1f0  83c40c                   add        esp, 0xc
00aca1f3  56                       push       esi
00aca1f4  8d4ddc                   lea        ecx, [ebp - 0x24]
00aca1f7  e834fcffff               call       0xac9e30
00aca1fc  85c0                     test       eax, eax
00aca1fe  0f84d4000000             je         0xaca2d8
00aca204  8d8da0f5ffff             lea        ecx, [ebp - 0xa60]
00aca20a  51                       push       ecx
00aca20b  6800040000               push       0x400
00aca210  8d95a0edffff             lea        edx, [ebp - 0x1260]
00aca216  52                       push       edx
00aca217  e8746f93ff               call       0x401190
00aca21c  8d45ec                   lea        eax, [ebp - 0x14]
00aca21f  50                       push       eax
00aca220  6800040000               push       0x400
00aca225  8d8da0edffff             lea        ecx, [ebp - 0x1260]
00aca22b  51                       push       ecx
00aca22c  e81f7093ff               call       0x401250
00aca231  85c0                     test       eax, eax
00aca233  7c1f                     jl         0xaca254
00aca235  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00aca238  8d95b4fdffff             lea        edx, [ebp - 0x24c]
00aca23e  52                       push       edx
00aca23f  b900040000               mov        ecx, 0x400
00aca244  2bc8                     sub        ecx, eax
00aca246  51                       push       ecx
00aca247  8d9445a0edffff           lea        edx, [ebp + eax*2 - 0x1260]
00aca24e  52                       push       edx
00aca24f  e83c6f93ff               call       0x401190
00aca254  8d85a0edffff             lea        eax, [ebp - 0x1260]
00aca25a  50                       push       eax
00aca25b  e86d5b1300               call       0xbffdcd
00aca260  83c404                   add        esp, 4
00aca263  50                       push       eax
00aca264  8d8da0edffff             lea        ecx, [ebp - 0x1260]
00aca26a  51                       push       ecx
00aca26b  8d4dc0                   lea        ecx, [ebp - 0x40]
00aca26e  e80d8c93ff               call       0x402e80
00aca273  8b7304                   mov        esi, dword ptr [ebx + 4]
00aca276  8b4604                   mov        eax, dword ptr [esi + 4]
00aca279  8d55bc                   lea        edx, [ebp - 0x44]
00aca27c  52                       push       edx
00aca27d  50                       push       eax
00aca27e  56                       push       esi
00aca27f  8bcb                     mov        ecx, ebx
00aca281  e8ba120000               call       0xacb540
00aca286  6a01                     push       1
00aca288  8bcb                     mov        ecx, ebx
00aca28a  8bf8                     mov        edi, eax
00aca28c  e81f070000               call       0xaca9b0
00aca291  897e04                   mov        dword ptr [esi + 4], edi
00aca294  8b4704                   mov        eax, dword ptr [edi + 4]
00aca297  8938                     mov        dword ptr [eax], edi
00aca299  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
00aca29c  8b5104                   mov        edx, dword ptr [ecx + 4]
00aca29f  52                       push       edx
00aca2a0  8d4ddc                   lea        ecx, [ebp - 0x24]
00aca2a3  e8480b0000               call       0xacadf0
00aca2a8  8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00aca2ab  8b75f0                   mov        esi, dword ptr [ebp - 0x10]
00aca2ae  8b7de8                   mov        edi, dword ptr [ebp - 0x18]
00aca2b1  894004                   mov        dword ptr [eax + 4], eax
00aca2b4  8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00aca2b7  c745e400000000           mov        dword ptr [ebp - 0x1c], 0
00aca2be  8900                     mov        dword ptr [eax], eax
00aca2c0  8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00aca2c3  894008                   mov        dword ptr [eax + 8], eax
00aca2c6  8b4508                   mov        eax, dword ptr [ebp + 8]
00aca2c9  40                       inc        eax
00aca2ca  56                       push       esi
00aca2cb  894508                   mov        dword ptr [ebp + 8], eax
00aca2ce  e8a9791300               call       0xc01c7c
00aca2d3  83c404                   add        esp, 4
00aca2d6  eb40                     jmp        0xaca318
00aca2d8  68f47be600               push       0xe67bf4
00aca2dd  ff15bc2eff00             call       dword ptr [0xff2ebc]
00aca2e3  8d85b4fdffff             lea        eax, [ebp - 0x24c]
00aca2e9  50                       push       eax
00aca2ea  68d87be600               push       0xe67bd8
00aca2ef  ff15bc2eff00             call       dword ptr [0xff2ebc]
00aca2f5  83c40c                   add        esp, 0xc
00aca2f8  56                       push       esi
00aca2f9  e87e791300               call       0xc01c7c
00aca2fe  83c404                   add        esp, 4
00aca301  eb15                     jmp        0xaca318
00aca303  8d8db4fdffff             lea        ecx, [ebp - 0x24c]
00aca309  51                       push       ecx
00aca30a  68a87be600               push       0xe67ba8
00aca30f  ff15bc2eff00             call       dword ptr [0xff2ebc]
00aca315  83c408                   add        esp, 8
00aca318  8d95a0fdffff             lea        edx, [ebp - 0x260]
00aca31e  52                       push       edx
00aca31f  57                       push       edi
00aca320  e8daa01300               call       0xc043ff
00aca325  83c408                   add        esp, 8
00aca328  85c0                     test       eax, eax
00aca32a  0f8450feffff             je         0xaca180
00aca330  57                       push       edi
00aca331  e8689f1300               call       0xc0429e
00aca336  83c404                   add        esp, 4
00aca339  8d85a0e5ffff             lea        eax, [ebp - 0x1a60]
00aca33f  50                       push       eax
00aca340  ff15e8f34001             call       dword ptr [0x140f3e8]
00aca346  8d4dbc                   lea        ecx, [ebp - 0x44]
00aca349  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00aca350  e8cb100000               call       0xacb420
00aca355  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00aca358  8b4508                   mov        eax, dword ptr [ebp + 8]
00aca35b  5f                       pop        edi
00aca35c  5e                       pop        esi
00aca35d  5b                       pop        ebx
00aca35e  64890d00000000           mov        dword ptr fs:[0], ecx
00aca365  8be5                     mov        esp, ebp
00aca367  5d                       pop        ebp
00aca368  c20400                   ret        4