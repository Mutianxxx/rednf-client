00731fa7  8b1e                     mov        ebx, dword ptr [esi]
00731fa9  6a01                     push       1
00731fab  8bce                     mov        ecx, esi
00731fad  ff938c030000             call       dword ptr [ebx + 0x38c]
00731fb3  50                       push       eax
00731fb4  8bce                     mov        ecx, esi
00731fb6  ff93f0000000             call       dword ptr [ebx + 0xf0]
00731fbc  8b1e                     mov        ebx, dword ptr [esi]
00731fbe  6a00                     push       0
00731fc0  8bce                     mov        ecx, esi
00731fc2  e82951dfff               call       0x5270f0
00731fc7  50                       push       eax
00731fc8  8bce                     mov        ecx, esi
00731fca  ff9398010000             call       dword ptr [ebx + 0x198]
00731fd0  8b16                     mov        edx, dword ptr [esi]
00731fd2  6a00                     push       0
00731fd4  6a00                     push       0
00731fd6  6a00                     push       0
00731fd8  6a00                     push       0
00731fda  6a00                     push       0
00731fdc  6a00                     push       0
00731fde  8bce                     mov        ecx, esi
00731fe0  ff9288040000             call       dword ptr [edx + 0x488]
00731fe6  8b06                     mov        eax, dword ptr [esi]
00731fe8  6a00                     push       0
00731fea  6a00                     push       0
00731fec  6a00                     push       0
00731fee  6a00                     push       0
00731ff0  6a00                     push       0
00731ff2  6a01                     push       1
00731ff4  8bce                     mov        ecx, esi
00731ff6  ff9088040000             call       dword ptr [eax + 0x488]
00731ffc  8b16                     mov        edx, dword ptr [esi]
00731ffe  680000803f               push       0x3f800000
00732003  680000803f               push       0x3f800000
00732008  68e8030000               push       0x3e8
0073200d  68e8030000               push       0x3e8
00732012  6a02                     push       2
00732014  6a00                     push       0
00732016  8bce                     mov        ecx, esi
00732018  ff9294040000             call       dword ptr [edx + 0x494]
0073201e  8b06                     mov        eax, dword ptr [esi]
00732020  6a00                     push       0
00732022  6a04                     push       4
00732024  6a04                     push       4
00732026  8bce                     mov        ecx, esi
00732028  ff909c040000             call       dword ptr [eax + 0x49c]
0073202e  8b86ec2e0000             mov        eax, dword ptr [esi + 0x2eec]
00732034  85c0                     test       eax, eax
00732036  7409                     je         0x732041
00732038  83f802                   cmp        eax, 2
0073203b  0f859a000000             jne        0x7320db
00732041  8b16                     mov        edx, dword ptr [esi]
00732043  6a05                     push       5
00732045  8bce                     mov        ecx, esi
00732047  ff927c060000             call       dword ptr [edx + 0x67c]
0073204d  8bd8                     mov        ebx, eax
0073204f  8b06                     mov        eax, dword ptr [esi]
00732051  6a05                     push       5
00732053  8bce                     mov        ecx, esi
00732055  ff904c060000             call       dword ptr [eax + 0x64c]
0073205b  8b16                     mov        edx, dword ptr [esi]
0073205d  6a0c                     push       0xc
0073205f  8bce                     mov        ecx, esi
00732061  8945dc                   mov        dword ptr [ebp - 0x24], eax
00732064  ff92d0010000             call       dword ptr [edx + 0x1d0]
0073206a  50                       push       eax
0073206b  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
0073206e  56                       push       esi
0073206f  50                       push       eax
00732070  6a00                     push       0
00732072  8bcb                     mov        ecx, ebx
00732074  e8a789d9ff               call       0x4caa20
00732079  8d55f0                   lea        edx, [ebp - 0x10]
0073207c  83e864                   sub        eax, 0x64
0073207f  8d8e70020000             lea        ecx, [esi + 0x270]
00732085  52                       push       edx
00732086  8945f0                   mov        dword ptr [ebp - 0x10], eax
00732089  e8d224cdff               call       0x404560
0073208e  8b06                     mov        eax, dword ptr [esi]
00732090  6a00                     push       0
00732092  8bce                     mov        ecx, esi
00732094  ff90d0010000             call       dword ptr [eax + 0x1d0]
0073209a  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
0073209d  50                       push       eax
0073209e  56                       push       esi
0073209f  51                       push       ecx
007320a0  6a01                     push       1
007320a2  8bcb                     mov        ecx, ebx
007320a4  e87789d9ff               call       0x4caa20
007320a9  8bd8                     mov        ebx, eax
007320ab  8d8e70020000             lea        ecx, [esi + 0x270]
007320b1  6bdb64                   imul       ebx, ebx, 0x64
007320b4  e8a7ffccff               call       0x402060
007320b9  8bc8                     mov        ecx, eax
007320bb  8bc3                     mov        eax, ebx
007320bd  83c164                   add        ecx, 0x64
007320c0  99                       cdq        
007320c1  f7f9                     idiv       ecx
007320c3  8d55f0                   lea        edx, [ebp - 0x10]
007320c6  52                       push       edx
007320c7  8d8e60020000             lea        ecx, [esi + 0x260]
007320cd  8945f0                   mov        dword ptr [ebp - 0x10], eax
007320d0  db45f0                   fild       dword ptr [ebp - 0x10]
007320d3  d95df0                   fstp       dword ptr [ebp - 0x10]
