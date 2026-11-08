00732c63  56                       push       esi
00732c64  6a00                     push       0
00732c66  8bcb                     mov        ecx, ebx
00732c68  e8f3d2e1ff               call       0x54ff60
00732c6d  56                       push       esi
00732c6e  6a01                     push       1
00732c70  8bcb                     mov        ecx, ebx
00732c72  8bf8                     mov        edi, eax
00732c74  e8e7d2e1ff               call       0x54ff60
00732c79  8b16                     mov        edx, dword ptr [esi]
00732c7b  6a01                     push       1
00732c7d  50                       push       eax
00732c7e  6a00                     push       0
00732c80  57                       push       edi
00732c81  57                       push       edi
00732c82  6a00                     push       0
00732c84  8bce                     mov        ecx, esi
00732c86  ff9288040000             call       dword ptr [edx + 0x488]
00732c8c  8b06                     mov        eax, dword ptr [esi]
00732c8e  6a00                     push       0
00732c90  6a00                     push       0
00732c92  6a00                     push       0
00732c94  6a00                     push       0
00732c96  6a00                     push       0
00732c98  6a01                     push       1
00732c9a  8bce                     mov        ecx, esi
00732c9c  ff9088040000             call       dword ptr [eax + 0x488]
00732ca2  8b16                     mov        edx, dword ptr [esi]
00732ca4  680000803f               push       0x3f800000
00732ca9  680000803f               push       0x3f800000
00732cae  68e8030000               push       0x3e8
00732cb3  68e8030000               push       0x3e8
00732cb8  6a02                     push       2
00732cba  6a02                     push       2
00732cbc  8bce                     mov        ecx, esi
00732cbe  ff9294040000             call       dword ptr [edx + 0x494]
00732cc4  8b3e                     mov        edi, dword ptr [esi]
00732cc6  6a00                     push       0
00732cc8  6a04                     push       4
00732cca  8bce                     mov        ecx, esi
00732ccc  ff97c0000000             call       dword ptr [edi + 0xc0]
00732cd2  50                       push       eax
00732cd3  8bce                     mov        ecx, esi
00732cd5  ff979c040000             call       dword ptr [edi + 0x49c]
