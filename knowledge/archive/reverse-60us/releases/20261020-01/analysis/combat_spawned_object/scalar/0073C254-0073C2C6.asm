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