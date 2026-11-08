00693960  55                       push       ebp
00693961  8bec                     mov        ebp, esp
00693963  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00693966  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00693969  53                       push       ebx
0069396a  56                       push       esi
0069396b  57                       push       edi
0069396c  8b7d08                   mov        edi, dword ptr [ebp + 8]
0069396f  8bf1                     mov        esi, ecx
00693971  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00693974  50                       push       eax
00693975  51                       push       ecx
00693976  52                       push       edx
00693977  57                       push       edi
00693978  8bce                     mov        ecx, esi
0069397a  e8b1e3e2ff               call       0x4c1d30
0069397f  8ad8                     mov        bl, al
00693981  84db                     test       bl, bl
00693983  885d17                   mov        byte ptr [ebp + 0x17], bl
00693986  0f84a9000000             je         0x693a35
0069398c  8b06                     mov        eax, dword ptr [esi]
0069398e  6a21                     push       0x21
00693990  8bce                     mov        ecx, esi
00693992  ff904c060000             call       dword ptr [eax + 0x64c]
00693998  85c0                     test       eax, eax
0069399a  0f8495000000             je         0x693a35
006939a0  8b16                     mov        edx, dword ptr [esi]
006939a2  57                       push       edi
006939a3  8bce                     mov        ecx, esi
006939a5  ff927c060000             call       dword ptr [edx + 0x67c]
006939ab  8d4870                   lea        ecx, [eax + 0x70]
006939ae  e8ade6d6ff               call       0x402060
006939b3  83f801                   cmp        eax, 1
006939b6  757d                     jne        0x693a35
006939b8  8b06                     mov        eax, dword ptr [esi]
006939ba  6a21                     push       0x21
006939bc  8bce                     mov        ecx, esi
006939be  ff907c060000             call       dword ptr [eax + 0x67c]
006939c4  8bf8                     mov        edi, eax
006939c6  56                       push       esi
006939c7  6a00                     push       0
006939c9  8bcf                     mov        ecx, edi
006939cb  e890c5ebff               call       0x54ff60
006939d0  6a00                     push       0
006939d2  8bd8                     mov        ebx, eax
006939d4  e817a72100               call       0x8ae0f0
006939d9  99                       cdq        
006939da  b9e8030000               mov        ecx, 0x3e8
006939df  f7f9                     idiv       ecx
006939e1  83c404                   add        esp, 4
006939e4  3bd3                     cmp        edx, ebx
006939e6  7d4a                     jge        0x693a32
006939e8  56                       push       esi
006939e9  6a01                     push       1
006939eb  8bcf                     mov        ecx, edi
006939ed  e86ec5ebff               call       0x54ff60
006939f2  56                       push       esi
006939f3  8bf8                     mov        edi, eax
006939f5  57                       push       edi
006939f6  6a03                     push       3
006939f8  b988ff0b01               mov        ecx, 0x10bff88
006939fd  e8ae5e2200               call       0x8b98b0
00693a02  8b16                     mov        edx, dword ptr [esi]
00693a04  6a00                     push       0
00693a06  6a00                     push       0
00693a08  50                       push       eax
00693a09  6a00                     push       0
00693a0b  56                       push       esi
00693a0c  57                       push       edi
00693a0d  6a03                     push       3
00693a0f  8bce                     mov        ecx, esi
00693a11  ff9204040000             call       dword ptr [edx + 0x404]
00693a17  8b06                     mov        eax, dword ptr [esi]
00693a19  6a01                     push       1
00693a1b  6a01                     push       1
00693a1d  6a01                     push       1
00693a1f  6a21                     push       0x21
00693a21  8bce                     mov        ecx, esi
00693a23  ff9068070000             call       dword ptr [eax + 0x768]
00693a29  5f                       pop        edi
00693a2a  5e                       pop        esi
00693a2b  32c0                     xor        al, al
00693a2d  5b                       pop        ebx
00693a2e  5d                       pop        ebp
00693a2f  c21000                   ret        0x10
00693a32  8a5d17                   mov        bl, byte ptr [ebp + 0x17]
00693a35  5f                       pop        edi
00693a36  5e                       pop        esi
00693a37  8ac3                     mov        al, bl
00693a39  5b                       pop        ebx
00693a3a  5d                       pop        ebp
00693a3b  c21000                   ret        0x10
00693a3e  cc                       int3       
00693a3f  cc                       int3       
00693a40  55                       push       ebp
00693a41  8bec                     mov        ebp, esp
00693a43  83ec28                   sub        esp, 0x28
00693a46  56                       push       esi
00693a47  8bf1                     mov        esi, ecx
00693a49  e84286e0ff               call       0x49c090
00693a4e  84c0                     test       al, al
00693a50  0f84f8040000             je         0x693f4e
00693a56  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00693a59  b864000000               mov        eax, 0x64
00693a5e  3bc8                     cmp        ecx, eax
00693a60  7c03                     jl         0x693a65
00693a62  894508                   mov        dword ptr [ebp + 8], eax
00693a65  8b06                     mov        eax, dword ptr [esi]
00693a67  53                       push       ebx
00693a68  57                       push       edi
00693a69  682038d600               push       0xd63820
00693a6e  8bce                     mov        ecx, esi
00693a70  ff90c0020000             call       dword ptr [eax + 0x2c0]
00693a76  8b16                     mov        edx, dword ptr [esi]
00693a78  6a0c                     push       0xc
00693a7a  8bce                     mov        ecx, esi
00693a7c  8945f8                   mov        dword ptr [ebp - 8], eax
00693a7f  ff                       .byte      0xff