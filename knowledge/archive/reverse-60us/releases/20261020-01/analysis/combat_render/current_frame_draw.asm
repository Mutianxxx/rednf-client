00a23d60 55                       push       ebp
00a23d61 8bec                     mov        ebp, esp
00a23d63 56                       push       esi
00a23d64 8b7518                   mov        esi, dword ptr [ebp + 0x18]
00a23d67 85f6                     test       esi, esi
00a23d69 57                       push       edi
00a23d6a 8bf9                     mov        edi, ecx
00a23d6c 0f8414010000             je         0xa23e86
00a23d72 8b06                     mov        eax, dword ptr [esi]
00a23d74 85c0                     test       eax, eax
00a23d76 0f840a010000             je         0xa23e86
00a23d7c 8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a23d7f 3b0d2ca90d01             cmp        ecx, dword ptr [0x10da92c]
00a23d85 53                       push       ebx
00a23d86 0f85da000000             jne        0xa23e66
00a23d8c 8b462c                   mov        eax, dword ptr [esi + 0x2c]
00a23d8f 8b4e28                   mov        ecx, dword ptr [esi + 0x28]
00a23d92 56                       push       esi
00a23d93 50                       push       eax
00a23d94 51                       push       ecx
00a23d95 e886d29dff               call       0x401020
00a23d9a 8b460c                   mov        eax, dword ptr [esi + 0xc]
00a23d9d 8b5e08                   mov        ebx, dword ptr [esi + 8]
00a23da0 894518                   mov        dword ptr [ebp + 0x18], eax
00a23da3 f7d8                     neg        eax
00a23da5 8bd3                     mov        edx, ebx
00a23da7 a3d83c0d01               mov        dword ptr [0x10d3cd8], eax
00a23dac 8b4730                   mov        eax, dword ptr [edi + 0x30]
00a23daf f7da                     neg        edx
00a23db1 83c40c                   add        esp, 0xc
00a23db4 83f801                   cmp        eax, 1
00a23db7 8915d43c0d01             mov        dword ptr [0x10d3cd4], edx
00a23dbd 7522                     jne        0xa23de1
00a23dbf 8b06                     mov        eax, dword ptr [esi]
00a23dc1 8b4814                   mov        ecx, dword ptr [eax + 0x14]
00a23dc4 8b501c                   mov        edx, dword ptr [eax + 0x1c]
00a23dc7 d1e9                     shr        ecx, 1
00a23dc9 03ca                     add        ecx, edx
00a23dcb 8b5018                   mov        edx, dword ptr [eax + 0x18]
00a23dce 890dd43c0d01             mov        dword ptr [0x10d3cd4], ecx
00a23dd4 8b4820                   mov        ecx, dword ptr [eax + 0x20]
00a23dd7 d1ea                     shr        edx, 1
00a23dd9 03d1                     add        edx, ecx
00a23ddb 8915d83c0d01             mov        dword ptr [0x10d3cd8], edx
00a23de1 8a4514                   mov        al, byte ptr [ebp + 0x14]
00a23de4 8b3dfc3e0d01             mov        edi, dword ptr [0x10d3efc]
00a23dea 84c0                     test       al, al
00a23dec 8d4610                   lea        eax, [esi + 0x10]
00a23def 7416                     je         0xa23e07
00a23df1 8b08                     mov        ecx, dword ptr [eax]
00a23df3 2bc8                     sub        ecx, eax
00a23df5 33cf                     xor        ecx, edi
00a23df7 894d14                   mov        dword ptr [ebp + 0x14], ecx
00a23dfa d94514                   fld        dword ptr [ebp + 0x14]
00a23dfd d9e0                     fchs       
00a23dff d95d14                   fstp       dword ptr [ebp + 0x14]
00a23e02 8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a23e05 eb06                     jmp        0xa23e0d
00a23e07 8b10                     mov        edx, dword ptr [eax]
00a23e09 2bd0                     sub        edx, eax
00a23e0b 33d7                     xor        edx, edi
00a23e0d 8b4614                   mov        eax, dword ptr [esi + 0x14]
00a23e10 db05d83c0d01             fild       dword ptr [0x10d3cd8]
00a23e16 8d4e14                   lea        ecx, [esi + 0x14]
00a23e19 2bc1                     sub        eax, ecx
00a23e1b 8b4e58                   mov        ecx, dword ptr [esi + 0x58]
00a23e1e 51                       push       ecx
00a23e1f 8b4e1c                   mov        ecx, dword ptr [esi + 0x1c]
00a23e22 83ec08                   sub        esp, 8
00a23e25 d95c2404                 fstp       dword ptr [esp + 4]
00a23e29 33c7                     xor        eax, edi
00a23e2b db05d43c0d01             fild       dword ptr [0x10d3cd4]
00a23e31 d91c24                   fstp       dword ptr [esp]
00a23e34 51                       push       ecx
00a23e35 8b4e18                   mov        ecx, dword ptr [esi + 0x18]
00a23e38 51                       push       ecx
00a23e39 8b4d18                   mov        ecx, dword ptr [ebp + 0x18]
00a23e3c 50                       push       eax
00a23e3d 8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a23e40 52                       push       edx
00a23e41 8b16                     mov        edx, dword ptr [esi]
00a23e43 52                       push       edx
00a23e44 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a23e47 03c8                     add        ecx, eax
00a23e49 51                       push       ecx
00a23e4a 03da                     add        ebx, edx
00a23e4c 53                       push       ebx
00a23e4d e87e45b1ff               call       0x5383d0
00a23e52 8b4628                   mov        eax, dword ptr [esi + 0x28]
00a23e55 56                       push       esi
00a23e56 50                       push       eax
00a23e57 e854d29dff               call       0x4010b0
00a23e5c 83c430                   add        esp, 0x30
00a23e5f 5b                       pop        ebx
00a23e60 5f                       pop        edi
00a23e61 5e                       pop        esi
00a23e62 5d                       pop        ebp
00a23e63 c21400                   ret        0x14
00a23e66 8b5628                   mov        edx, dword ptr [esi + 0x28]
00a23e69 85d2                     test       edx, edx
00a23e6b 7518                     jne        0xa23e85
00a23e6d 8b560c                   mov        edx, dword ptr [esi + 0xc]
00a23e70 8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
00a23e73 50                       push       eax
00a23e74 8b4608                   mov        eax, dword ptr [esi + 8]
00a23e77 8b750c                   mov        esi, dword ptr [ebp + 0xc]
00a23e7a 03d3                     add        edx, ebx
00a23e7c 52                       push       edx
00a23e7d 03c6                     add        eax, esi
00a23e7f 50                       push       eax
00a23e80 e84ba00e00               call       0xb0ded0
00a23e85 5b                       pop        ebx
00a23e86 5f                       pop        edi
00a23e87 5e                       pop        esi
00a23e88 5d                       pop        ebp
00a23e89 c21400                   ret        0x14
00a23e8c cc                       int3       
00a23e8d cc                       int3       
00a23e8e cc                       int3       
00a23e8f cc                       int3       