004e1e80  55                       push       ebp
004e1e81  8bec                     mov        ebp, esp
004e1e83  51                       push       ecx
004e1e84  56                       push       esi
004e1e85  57                       push       edi
004e1e86  8b7d08                   mov        edi, dword ptr [ebp + 8]
004e1e89  8bf1                     mov        esi, ecx
004e1e8b  8d4508                   lea        eax, [ebp + 8]
004e1e8e  50                       push       eax
004e1e8f  8d4dfc                   lea        ecx, [ebp - 4]
004e1e92  51                       push       ecx
004e1e93  b9dce30b01               mov        ecx, 0x10be3dc
004e1e98  897d08                   mov        dword ptr [ebp + 8], edi
004e1e9b  e87024f5ff               call       0x434310
004e1ea0  8b45fc                   mov        eax, dword ptr [ebp - 4]
004e1ea3  3b05e0e30b01             cmp        eax, dword ptr [0x10be3e0]
004e1ea9  7426                     je         0x4e1ed1
004e1eab  83782808                 cmp        dword ptr [eax + 0x28], 8
004e1eaf  7205                     jb         0x4e1eb6
004e1eb1  8b4014                   mov        eax, dword ptr [eax + 0x14]
004e1eb4  eb03                     jmp        0x4e1eb9
004e1eb6  83c014                   add        eax, 0x14
004e1eb9  85c0                     test       eax, eax
004e1ebb  7414                     je         0x4e1ed1
004e1ebd  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004e1ec0  52                       push       edx
004e1ec1  50                       push       eax
004e1ec2  8bce                     mov        ecx, esi
004e1ec4  e87782ffff               call       0x4da140
004e1ec9  5f                       pop        edi
004e1eca  5e                       pop        esi
004e1ecb  8be5                     mov        esp, ebp
004e1ecd  5d                       pop        ebp
004e1ece  c20800                   ret        8
004e1ed1  57                       push       edi
004e1ed2  686849cd00               push       0xcd4968
004e1ed7  ff15bc2eff00             call       dword ptr [0xff2ebc]
004e1edd  83c408                   add        esp, 8
004e1ee0  5f                       pop        edi
004e1ee1  5e                       pop        esi
004e1ee2  8be5                     mov        esp, ebp
004e1ee4  5d                       pop        ebp
004e1ee5  c20800                   ret        8
004e1ee8  cc                       int3       
004e1ee9  cc                       int3       
004e1eea  cc                       int3       
004e1eeb  cc                       int3       
004e1eec  cc                       int3       
004e1eed  cc                       int3       
004e1eee  cc                       int3       
004e1eef  cc                       int3       
004e1ef0  55                       push       ebp
004e1ef1  8bec                     mov        ebp, esp
004e1ef3  6aff                     push       -1
004e1ef5  68f989c500               push       0xc589f9
004e1efa  64a100000000             mov        eax, dword ptr fs:[0]
004e1f00  50                       push       eax
004e1f01  64892500000000           mov        dword ptr fs:[0], esp
004e1f08  83ec18                   sub        esp, 0x18
004e1f0b  53                       push       ebx
004e1f0c  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004e1f0f  56                       push       esi
004e1f10  8bf1                     mov        esi, ecx
004e1f12  8b866c1b0000             mov        eax, dword ptr [esi + 0x1b6c]
004e1f18  3bc3                     cmp        eax, ebx
004e1f1a  751a                     jne        0x4e1f36
004e1f1c  8b8e701b0000             mov        ecx, dword ptr [esi + 0x1b70]
004e1f22  3b4d0c                   cmp        ecx, dword ptr [ebp + 0xc]
004e1f25  750f                     jne        0x4e1f36
004e1f27  8a96741b0000             mov        dl, byte ptr [esi + 0x1b74]
004e1f2d  3a5510                   cmp        dl, byte ptr [ebp + 0x10]
004e1f30  0f8498050000             je         0x4e24ce
004e1f36  3bc3                     cmp        eax, ebx
004e1f38  57                       push       edi
004e1f39  0f84c0030000             je         0x4e22ff
004e1f3f  8b86641b0000             mov        eax, dword ptr [esi + 0x1b64]
004e1f45  8b0ddc300001             mov        ecx, dword ptr [0x10030dc]
004e1f4b  50                       push       eax
004e1f4c  e8cff55700               call       0xa61520
004e1f51  8bd0                     mov        edx, eax
004e1f53  85d2                     test       edx, edx
004e1f55  8955ec                   mov        dword ptr [ebp - 0x14], edx
004e1f58  7528                     jne        0x4e1f82
004e1f5a  8b8e641b0000             mov        ecx, dword ptr [esi + 0x1b64]
004e1f60  51                       push       ecx
004e1f61  68584bcd00               push       0xcd4b58
004e1f66  ff15bc2eff00             call       dword ptr [0xff2ebc]
004e1f6c  83c408                   add        esp, 8
004e1f6f  5f                       pop        edi
004e1f70  5e                       pop        esi
004e1f71  5b                       pop        ebx
004e1f72  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004e1f75  64890d00000000           mov        dword ptr fs:[0], ecx
004e1f7c  8be5                     mov        esp, ebp
004e1f7e  5d                       pop        ebp
004e1f7f  c20c00                   ret        0xc
004e1f82  8b866c1b0000             mov        eax, dword ptr [esi + 0x1b6c]
004e1f88  85c0                     test       eax, eax
004e1f8a  7e48                     jle        0x4e1fd4
004e1f8c  33db                     xor        ebx, ebx
004e1f8e  8bff                     mov        edi, edi
004e1f90  8b866c1b0000             mov        eax, dword ptr [esi + 0x1b6c]
004e1f96  8d4c8055                 lea        ecx, [eax + eax*4 + 0x55]
004e1f9a  8b7cca04                 mov        edi, dword ptr [edx + ecx*8 + 4]
004e1f9e  85ff                     test       edi, edi