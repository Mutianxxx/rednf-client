00a27dc0  55                       push       ebp
00a27dc1  8bec                     mov        ebp, esp
00a27dc3  83ec0c                   sub        esp, 0xc
00a27dc6  56                       push       esi
00a27dc7  8bf1                     mov        esi, ecx
00a27dc9  8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00a27dcf  85c9                     test       ecx, ecx
00a27dd1  7407                     je         0xa27dda
00a27dd3  e8282caaff               call       0x4caa00
00a27dd8  eb06                     jmp        0xa27de0
00a27dda  8b868c000000             mov        eax, dword ptr [esi + 0x8c]
00a27de0  8b8e24010000             mov        ecx, dword ptr [esi + 0x124]
00a27de6  8945f8                   mov        dword ptr [ebp - 8], eax
00a27de9  80be3a01000001           cmp        byte ptr [esi + 0x13a], 1
00a27df0  894dfc                   mov        dword ptr [ebp - 4], ecx
00a27df3  0f845d010000             je         0xa27f56
00a27df9  53                       push       ebx
00a27dfa  57                       push       edi
00a27dfb  6a00                     push       0
00a27dfd  8bce                     mov        ecx, esi
00a27dff  e8accdffff               call       0xa24bb0
00a27e04  8dbe94000000             lea        edi, [esi + 0x94]
00a27e0a  8bd8                     mov        ebx, eax
00a27e0c  8b4704                   mov        eax, dword ptr [edi + 4]
00a27e0f  85c0                     test       eax, eax
00a27e11  0f8413010000             je         0xa27f2a
00a27e17  8b4f08                   mov        ecx, dword ptr [edi + 8]
00a27e1a  2bc8                     sub        ecx, eax
00a27e1c  b843082184               mov        eax, 0x84210843
00a27e21  f7e9                     imul       ecx
00a27e23  03d1                     add        edx, ecx
00a27e25  c1fa06                   sar        edx, 6
00a27e28  8bc2                     mov        eax, edx
00a27e2a  c1e81f                   shr        eax, 0x1f
00a27e2d  03c2                     add        eax, edx
00a27e2f  8945f4                   mov        dword ptr [ebp - 0xc], eax
00a27e32  0f84f2000000             je         0xa27f2a
00a27e38  85db                     test       ebx, ebx
00a27e3a  0f8cea000000             jl         0xa27f2a
00a27e40  8b4df8                   mov        ecx, dword ptr [ebp - 8]
00a27e43  7449                     je         0xa27e8e
00a27e45  8b962c010000             mov        edx, dword ptr [esi + 0x12c]
00a27e4b  8bc1                     mov        eax, ecx
00a27e4d  2bc2                     sub        eax, edx
00a27e4f  3bc3                     cmp        eax, ebx
00a27e51  7e3b                     jle        0xa27e8e
00a27e53  8a9630010000             mov        dl, byte ptr [esi + 0x130]
00a27e59  84d2                     test       dl, dl
00a27e5b  7524                     jne        0xa27e81
00a27e5d  898e2c010000             mov        dword ptr [esi + 0x12c], ecx
00a27e63  8bcf                     mov        ecx, edi
00a27e65  e8c6b7a6ff               call       0x493630
00a27e6a  48                       dec        eax
00a27e6b  50                       push       eax
00a27e6c  8bce                     mov        ecx, esi
00a27e6e  e8fdf9ffff               call       0xa27870
00a27e73  5f                       pop        edi
00a27e74  5b                       pop        ebx
00a27e75  c6863a01000001           mov        byte ptr [esi + 0x13a], 1
00a27e7c  5e                       pop        esi
00a27e7d  8be5                     mov        esp, ebp
00a27e7f  5d                       pop        ebp
00a27e80  c3                       ret        
00a27e81  99                       cdq        
00a27e82  f7fb                     idiv       ebx
00a27e84  8bc1                     mov        eax, ecx
00a27e86  2bc2                     sub        eax, edx
00a27e88  89862c010000             mov        dword ptr [esi + 0x12c], eax
00a27e8e  8a863a010000             mov        al, byte ptr [esi + 0x13a]
00a27e94  84c0                     test       al, al
00a27e96  0f85b8000000             jne        0xa27f54
00a27e9c  8d642400                 lea        esp, [esp]
00a27ea0  3b8e2c010000             cmp        ecx, dword ptr [esi + 0x12c]
00a27ea6  0f8ca8000000             jl         0xa27f54
00a27eac  8b4704                   mov        eax, dword ptr [edi + 4]
00a27eaf  85c0                     test       eax, eax
00a27eb1  7418                     je         0xa27ecb
00a27eb3  8b4f08                   mov        ecx, dword ptr [edi + 8]
00a27eb6  2bc8                     sub        ecx, eax
00a27eb8  b843082184               mov        eax, 0x84210843
00a27ebd  f7e9                     imul       ecx
00a27ebf  03d1                     add        edx, ecx
00a27ec1  c1fa06                   sar        edx, 6
00a27ec4  8bc2                     mov        eax, edx
00a27ec6  c1e81f                   shr        eax, 0x1f
00a27ec9  03c2                     add        eax, edx
00a27ecb  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a27ece  48                       dec        eax
00a27ecf  3bc8                     cmp        ecx, eax
00a27ed1  7537                     jne        0xa27f0a
00a27ed3  8a8630010000             mov        al, byte ptr [esi + 0x130]
00a27ed9  84c0                     test       al, al
00a27edb  7470                     je         0xa27f4d
00a27edd  8b4704                   mov        eax, dword ptr [edi + 4]
00a27ee0  85c0                     test       eax, eax
00a27ee2  7470                     je         0xa27f54
00a27ee4  8b4f08                   mov        ecx, dword ptr [edi + 8]
00a27ee7  2bc8                     sub        ecx, eax
00a27ee9  b843082184               mov        eax, 0x84210843
00a27eee  f7e9                     imul       ecx
00a27ef0  03d1                     add        edx, ecx
00a27ef2  c1fa06                   sar        edx, 6
00a27ef5  8bc2                     mov        eax, edx
00a27ef7  c1e81f                   shr        eax, 0x1f
00a27efa  03c2                     add        eax, edx
00a27efc  83f801                   cmp        eax, 1
00a27eff  7653                     jbe        0xa27f54
00a27f01  c745fc00000000           mov        dword ptr [ebp - 4], 0
00a27f08  eb03                     jmp        0xa27f0d
00a27f0a  ff45fc                   inc        dword ptr [ebp - 4]
00a27f0d  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a27f10  51                       push       ecx
00a27f11  8bce                     mov        ecx, esi
00a27f13  e858f9ffff               call       0xa27870
00a27f18  8a863a010000             mov        al, byte ptr [esi + 0x13a]
00a27f1e  84c0                     test       al, al
00a27f20  7532                     jne        0xa27f54
00a27f22  8b4df8                   mov        ecx, dword ptr [ebp - 8]
00a27f25  e976ffffff               jmp        0xa27ea0
00a27f2a  68584de400               push       0xe44d58
00a27f2f  68c84ce400               push       0xe44cc8
00a27f34  ff15bc2eff00             call       dword ptr [0xff2ebc]
00a27f3a  83c408                   add        esp, 8
00a27f3d  6a00                     push       0
00a27f3f  8bce                     mov        ecx, esi
00a27f41  e8fae0ffff               call       0xa26040
00a27f46  8bce                     mov        ecx, esi
00a27f48  e813fcffff               call       0xa27b60
00a27f4d  c6863a01000001           mov        byte ptr [esi + 0x13a], 1
00a27f54  5f                       pop        edi
00a27f55  5b                       pop        ebx
00a27f56  5e                       pop        esi
00a27f57  8be5                     mov        esp, ebp
00a27f59  5d                       pop        ebp
00a27f5a  c3                       ret        
00a27f5b  cc                       int3       
00a27f5c  cc                       int3       
00a27f5d  cc                       int3       
00a27f5e  cc                       int3       
00a27f5f  cc                       int3       
