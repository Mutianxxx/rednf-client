0073c180  e8cb7accff               call       0x403c50
0073c185  8bf8                     mov        edi, eax
0073c187  83c404                   add        esp, 4
0073c18a  897d14                   mov        dword ptr [ebp + 0x14], edi
0073c18d  85ff                     test       edi, edi
0073c18f  c645fc91                 mov        byte ptr [ebp - 4], 0x91
0073c193  741c                     je         0x73c1b1
0073c195  6a01                     push       1
0073c197  6850c7d700               push       0xd7c750
0073c19c  8d8e44020000             lea        ecx, [esi + 0x244]
0073c1a2  e80973cfff               call       0x4334b0
0073c1a7  50                       push       eax
0073c1a8  8bcf                     mov        ecx, edi
0073c1aa  e8b168d3ff               call       0x472a60
0073c1af  eb02                     jmp        0x73c1b3
0073c1b1  33c0                     xor        eax, eax
0073c1b3  68e8010000               push       0x1e8
0073c1b8  c645fc00                 mov        byte ptr [ebp - 4], 0
0073c1bc  8986b82f0000             mov        dword ptr [esi + 0x2fb8], eax
0073c1c2  e8897accff               call       0x403c50
0073c1c7  8bf8                     mov        edi, eax
0073c1c9  83c404                   add        esp, 4
0073c1cc  897d14                   mov        dword ptr [ebp + 0x14], edi
0073c1cf  85ff                     test       edi, edi
0073c1d1  c645fc92                 mov        byte ptr [ebp - 4], 0x92
0073c1d5  741c                     je         0x73c1f3
0073c1d7  6a01                     push       1
0073c1d9  6808c7d700               push       0xd7c708
0073c1de  8d8e44020000             lea        ecx, [esi + 0x244]
0073c1e4  e8c772cfff               call       0x4334b0
0073c1e9  50                       push       eax
0073c1ea  8bcf                     mov        ecx, edi
0073c1ec  e86f68d3ff               call       0x472a60
0073c1f1  eb02                     jmp        0x73c1f5
0073c1f3  33c0                     xor        eax, eax
0073c1f5  c645fc00                 mov        byte ptr [ebp - 4], 0
0073c1f9  8986bc2f0000             mov        dword ptr [esi + 0x2fbc], eax
0073c1ff  8b86b82f0000             mov        eax, dword ptr [esi + 0x2fb8]
0073c205  8b16                     mov        edx, dword ptr [esi]
0073c207  6a01                     push       1
0073c209  6a00                     push       0
0073c20b  6a00                     push       0
0073c20d  6a00                     push       0
0073c20f  6a00                     push       0
0073c211  6a00                     push       0
0073c213  6a00                     push       0
0073c215  6a00                     push       0
0073c217  50                       push       eax
0073c218  6a01                     push       1
0073c21a  8bce                     mov        ecx, esi
0073c21c  ff92f8000000             call       dword ptr [edx + 0xf8]
0073c222  8b86bc2f0000             mov        eax, dword ptr [esi + 0x2fbc]
0073c228  8b16                     mov        edx, dword ptr [esi]
0073c22a  6a01                     push       1
0073c22c  6a00                     push       0
0073c22e  6a00                     push       0
0073c230  6a00                     push       0
0073c232  6a00                     push       0
0073c234  6a00                     push       0
0073c236  6a00                     push       0
0073c238  6a00                     push       0
0073c23a  50                       push       eax
0073c23b  6aff                     push       -1
0073c23d  8bce                     mov        ecx, esi
0073c23f  ff92f8000000             call       dword ptr [edx + 0xf8]
0073c245  8bce                     mov        ecx, esi
0073c247  e844fed5ff               call       0x49c090
0073c24c  84c0                     test       al, al
0073c24e  0f8472000000             je         0x73c2c6
0073c254  8b16                     mov        edx, dword ptr [esi]
0073c256  6a20                     push       0x20
0073c258  8bce                     mov        ecx, esi
0073c25a  ff927c060000             call       dword ptr [edx + 0x67c]
0073c260  894514                   mov        dword ptr [ebp + 0x14], eax
0073c263  8b06                     mov        eax, dword ptr [esi]
0073c265  6a20                     push       0x20
0073c267  8bce                     mov        ecx, esi
0073c269  ff904c060000             call       dword ptr [eax + 0x64c]
0073c26f  83f801                   cmp        eax, 1
0073c272  7e10                     jle        0x73c284
0073c274  8b16                     mov        edx, dword ptr [esi]
0073c276  6a20                     push       0x20
0073c278  8bce                     mov        ecx, esi
0073c27a  ff924c060000             call       dword ptr [edx + 0x64c]
0073c280  8bd8                     mov        ebx, eax
0073c282  eb05                     jmp        0x73c289
0073c284  bb01000000               mov        ebx, 1
0073c289  6a00                     push       0
0073c28b  8b3e                     mov        edi, dword ptr [esi]
0073c28d  6a00                     push       0
0073c28f  6a00                     push       0
0073c291  6a00                     push       0
0073c293  6a00                     push       0
0073c295  6a04                     push       4
0073c297  6a00                     push       0
0073c299  6a00                     push       0
0073c29b  6a00                     push       0
0073c29d  6a00                     push       0
0073c29f  6a00                     push       0
0073c2a1  6a00                     push       0
0073c2a3  8bce                     mov        ecx, esi
0073c2a5  ff97d0010000             call       dword ptr [edi + 0x1d0]
0073c2ab  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
0073c2ae  50                       push       eax
0073c2af  56                       push       esi
0073c2b0  53                       push       ebx
0073c2b1  6a00                     push       0
0073c2b3  e868e7d8ff               call       0x4caa20
0073c2b8  50                       push       eax
0073c2b9  68324e0000               push       0x4e32
0073c2be  8bce                     mov        ecx, esi
0073c2c0  ff97b8020000             call       dword ptr [edi + 0x2b8]
0073c2c6  8b06                     mov        eax, dword ptr [esi]
0073c2c8  6a01                     push       1
0073c2ca  6a01                     push       1
0073c2cc  8bce                     mov        ecx, esi
0073c2ce  ff90e0020000             call       dword ptr [eax + 0x2e0]
0073c2d4  e944110000               jmp        0x73d41d
0073c2d9  8d8e2c240000             lea        ecx, [esi + 0x242c]
0073c2df  e8                       .byte      0xe8