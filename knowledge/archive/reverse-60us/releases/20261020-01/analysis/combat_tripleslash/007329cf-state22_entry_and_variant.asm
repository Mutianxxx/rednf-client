007329cf  8b4704                   mov        eax, dword ptr [edi + 4]
007329d2  8b00                     mov        eax, dword ptr [eax]
007329d4  89861c2f0000             mov        dword ptr [esi + 0x2f1c], eax
007329da  8b7f04                   mov        edi, dword ptr [edi + 4]
007329dd  8b4704                   mov        eax, dword ptr [edi + 4]
007329e0  8b16                     mov        edx, dword ptr [esi]
007329e2  50                       push       eax
007329e3  8bce                     mov        ecx, esi
007329e5  ff92b8000000             call       dword ptr [edx + 0xb8]
007329eb  c786202f000003000000     mov        dword ptr [esi + 0x2f20], 3
007329f5  8b16                     mov        edx, dword ptr [esi]
007329f7  6a1b                     push       0x1b
007329f9  8bce                     mov        ecx, esi
007329fb  c745d800000000           mov        dword ptr [ebp - 0x28], 0
00732a02  ff924c060000             call       dword ptr [edx + 0x64c]
00732a08  85c0                     test       eax, eax
00732a0a  0f8eea000000             jle        0x732afa
00732a10  8b06                     mov        eax, dword ptr [esi]
00732a12  8bce                     mov        ecx, esi
00732a14  ff9020060000             call       dword ptr [eax + 0x620]
00732a1a  83f805                   cmp        eax, 5
00732a1d  7564                     jne        0x732a83
00732a1f  8b16                     mov        edx, dword ptr [esi]
00732a21  6a04                     push       4
00732a23  8bce                     mov        ecx, esi
00732a25  ff924c060000             call       dword ptr [edx + 0x64c]
00732a2b  85c0                     test       eax, eax
00732a2d  7e54                     jle        0x732a83
00732a2f  8b06                     mov        eax, dword ptr [esi]
00732a31  6a04                     push       4
00732a33  8bce                     mov        ecx, esi
00732a35  ff907c060000             call       dword ptr [eax + 0x67c]
00732a3b  8bf8                     mov        edi, eax
00732a3d  56                       push       esi
00732a3e  6a01                     push       1
00732a40  8bcf                     mov        ecx, edi
00732a42  e819d5e1ff               call       0x54ff60
00732a47  8b16                     mov        edx, dword ptr [esi]
00732a49  6a04                     push       4
00732a4b  8bce                     mov        ecx, esi
00732a4d  8bd8                     mov        ebx, eax
00732a4f  ff924c060000             call       dword ptr [edx + 0x64c]
00732a55  3bc3                     cmp        eax, ebx
00732a57  0f8c9d000000             jl         0x732afa
00732a5d  6a00                     push       0
00732a5f  6a00                     push       0
00732a61  6a0c                     push       0xc
00732a63  6aff                     push       -1
00732a65  6aff                     push       -1
00732a67  56                       push       esi
00732a68  c786202f000005000000     mov        dword ptr [esi + 0x2f20], 5
00732a72  8b06                     mov        eax, dword ptr [esi]
00732a74  6a04                     push       4
00732a76  8bce                     mov        ecx, esi
00732a78  ff904c060000             call       dword ptr [eax + 0x64c]
00732a7e  50                       push       eax
00732a7f  6a03                     push       3
00732a81  eb6d                     jmp        0x732af0
00732a83  8b16                     mov        edx, dword ptr [esi]
00732a85  8bce                     mov        ecx, esi
00732a87  ff9220060000             call       dword ptr [edx + 0x620]
00732a8d  83f801                   cmp        eax, 1
00732a90  7568                     jne        0x732afa
00732a92  8b06                     mov        eax, dword ptr [esi]
00732a94  6a0d                     push       0xd
00732a96  8bce                     mov        ecx, esi
00732a98  ff904c060000             call       dword ptr [eax + 0x64c]
00732a9e  85c0                     test       eax, eax
00732aa0  7e58                     jle        0x732afa
00732aa2  8b16                     mov        edx, dword ptr [esi]
00732aa4  6a0d                     push       0xd
00732aa6  8bce                     mov        ecx, esi
00732aa8  ff927c060000             call       dword ptr [edx + 0x67c]
00732aae  8bf8                     mov        edi, eax
00732ab0  56                       push       esi
00732ab1  6a00                     push       0
00732ab3  8bcf                     mov        ecx, edi
00732ab5  e8a6d4e1ff               call       0x54ff60
00732aba  8bd8                     mov        ebx, eax
00732abc  8b06                     mov        eax, dword ptr [esi]
00732abe  6a0d                     push       0xd
00732ac0  8bce                     mov        ecx, esi
00732ac2  ff904c060000             call       dword ptr [eax + 0x64c]
00732ac8  3bc3                     cmp        eax, ebx
00732aca  7c2e                     jl         0x732afa
00732acc  6a00                     push       0
00732ace  6a00                     push       0
00732ad0  6a0c                     push       0xc
00732ad2  6aff                     push       -1
00732ad4  6aff                     push       -1
00732ad6  56                       push       esi
00732ad7  c786202f000005000000     mov        dword ptr [esi + 0x2f20], 5
00732ae1  8b16                     mov        edx, dword ptr [esi]
00732ae3  6a0d                     push       0xd
00732ae5  8bce                     mov        ecx, esi
00732ae7  ff924c060000             call       dword ptr [edx + 0x64c]
00732aed  50                       push       eax
00732aee  6a02                     push       2
00732af0  8bcf                     mov        ecx, edi
00732af2  e889d5e1ff               call       0x550080
00732af7  8945d8                   mov        dword ptr [ebp - 0x28], eax
00732afa  8b06                     mov        eax, dword ptr [esi]
00732afc  6a08                     push       8
00732afe  8bce                     mov        ecx, esi
00732b00  ff907c060000             call       dword ptr [eax + 0x67c]
00732b06  8b16                     mov        edx, dword ptr [esi]
00732b08  6a08                     push       8
00732b0a  8bce                     mov        ecx, esi
00732b0c  8bd8                     mov        ebx, eax
00732b0e  ff924c060000             call       dword ptr [edx + 0x64c]
00732b14  8b3e                     mov        edi, dword ptr [esi]
00732b16  8945dc                   mov        dword ptr [ebp - 0x24], eax
