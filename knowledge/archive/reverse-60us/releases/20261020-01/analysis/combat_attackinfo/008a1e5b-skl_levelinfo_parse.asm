008a1e5b  8d45c8                   lea        eax, [ebp - 0x38]
008a1e5e  681092e200               push       0xe29210
008a1e63  50                       push       eax
008a1e64  e86729b6ff               call       0x4047d0
008a1e69  83c408                   add        esp, 8
008a1e6c  84c0                     test       al, al
008a1e6e  0f849e000000             je         0x8a1f12
008a1e74  8db768020000             lea        esi, [edi + 0x268]
008a1e7a  8bce                     mov        ecx, esi
008a1e7c  e8cfdabeff               call       0x48f950
008a1e81  6a00                     push       0
008a1e83  e848d9f8ff               call       0x82f7d0
008a1e88  83c404                   add        esp, 4
008a1e8b  8bd8                     mov        ebx, eax
008a1e8d  53                       push       ebx
008a1e8e  8bce                     mov        ecx, esi
008a1e90  e8db5ccbff               call       0x557b70
008a1e95  8d4df3                   lea        ecx, [ebp - 0xd]
008a1e98  51                       push       ecx
008a1e99  33f6                     xor        esi, esi
008a1e9b  e830d9f8ff               call       0x82f7d0
008a1ea0  8a4df3                   mov        cl, byte ptr [ebp - 0xd]
008a1ea3  83c404                   add        esp, 4
008a1ea6  84c9                     test       cl, cl
008a1ea8  0f843a040000             je         0x8a22e8
008a1eae  8bff                     mov        edi, edi
008a1eb0  8d55ec                   lea        edx, [ebp - 0x14]
008a1eb3  52                       push       edx
008a1eb4  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
008a1eba  8945ec                   mov        dword ptr [ebp - 0x14], eax
008a1ebd  e88e02b6ff               call       0x402150
008a1ec2  8b4508                   mov        eax, dword ptr [ebp + 8]
008a1ec5  8bb86c020000             mov        edi, dword ptr [eax + 0x26c]
008a1ecb  8bc6                     mov        eax, esi
008a1ecd  99                       cdq        
008a1ece  f7fb                     idiv       ebx
008a1ed0  c645fc0f                 mov        byte ptr [ebp - 4], 0xf
008a1ed4  8bca                     mov        ecx, edx
008a1ed6  c1e104                   shl        ecx, 4
008a1ed9  8d9540ffffff             lea        edx, [ebp - 0xc0]
008a1edf  03cf                     add        ecx, edi
008a1ee1  52                       push       edx
008a1ee2  e8c9b1bcff               call       0x46d0b0
008a1ee7  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
008a1eed  c645fc01                 mov        byte ptr [ebp - 4], 1
008a1ef1  e81a01b6ff               call       0x402010
008a1ef6  8d45f3                   lea        eax, [ebp - 0xd]
008a1ef9  50                       push       eax
008a1efa  46                       inc        esi
008a1efb  e8d0d8f8ff               call       0x82f7d0
008a1f00  8a4df3                   mov        cl, byte ptr [ebp - 0xd]
008a1f03  83c404                   add        esp, 4
008a1f06  84c9                     test       cl, cl
008a1f08  75a6                     jne        0x8a1eb0
008a1f0a  8b7d08                   mov        edi, dword ptr [ebp + 8]
008a1f0d  e9d6030000               jmp        0x8a22e8
