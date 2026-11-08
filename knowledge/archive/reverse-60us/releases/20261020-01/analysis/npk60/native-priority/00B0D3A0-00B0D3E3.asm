00b0d3a0  55                       push       ebp
00b0d3a1  8bec                     mov        ebp, esp
00b0d3a3  56                       push       esi
00b0d3a4  57                       push       edi
00b0d3a5  8b7d08                   mov        edi, dword ptr [ebp + 8]
00b0d3a8  c6410c01                 mov        byte ptr [ecx + 0xc], 1
00b0d3ac  837f1808                 cmp        dword ptr [edi + 0x18], 8
00b0d3b0  8d7704                   lea        esi, [edi + 4]
00b0d3b3  7204                     jb         0xb0d3b9
00b0d3b5  8b06                     mov        eax, dword ptr [esi]
00b0d3b7  eb02                     jmp        0xb0d3bb
00b0d3b9  8bc6                     mov        eax, esi
00b0d3bb  6a00                     push       0
00b0d3bd  50                       push       eax
00b0d3be  e8bdcffbff               call       0xaca380
00b0d3c3  8b4718                   mov        eax, dword ptr [edi + 0x18]
00b0d3c6  83c408                   add        esp, 8
00b0d3c9  83f808                   cmp        eax, 8
00b0d3cc  7202                     jb         0xb0d3d0
00b0d3ce  8b36                     mov        esi, dword ptr [esi]
00b0d3d0  6a02                     push       2
00b0d3d2  56                       push       esi
00b0d3d3  e8a8cffbff               call       0xaca380
00b0d3d8  83c408                   add        esp, 8
00b0d3db  5f                       pop        edi
00b0d3dc  b001                     mov        al, 1
00b0d3de  5e                       pop        esi
00b0d3df  5d                       pop        ebp
00b0d3e0  c20400                   ret        4