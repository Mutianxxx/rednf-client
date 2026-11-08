004a0da0 55                       push      ebp
004a0da1 8bec                     mov       ebp, esp
004a0da3 51                       push      ecx
004a0da4 56                       push      esi
004a0da5 57                       push      edi
004a0da6 8b7d08                   mov       edi, dword ptr [ebp + 8]
004a0da9 8bf1                     mov       esi, ecx
004a0dab 8d4508                   lea       eax, [ebp + 8]
004a0dae 50                       push      eax
004a0daf 8d4dfc                   lea       ecx, [ebp - 4]
004a0db2 51                       push      ecx
004a0db3 b9e8e30b01               mov       ecx, 0x10be3e8
004a0db8 89be68080000             mov       dword ptr [esi + 0x868], edi
004a0dbe 897d08                   mov       dword ptr [ebp + 8], edi
004a0dc1 e84a35f9ff               call      0x434310
004a0dc6 8b45fc                   mov       eax, dword ptr [ebp - 4]
004a0dc9 3b05ece30b01             cmp       eax, dword ptr [0x10be3ec]
004a0dcf 7426                     je        0x4a0df7
004a0dd1 83782808                 cmp       dword ptr [eax + 0x28], 8
004a0dd5 7205                     jb        0x4a0ddc
004a0dd7 8b4014                   mov       eax, dword ptr [eax + 0x14]
004a0dda eb03                     jmp       0x4a0ddf
004a0ddc 83c014                   add       eax, 0x14
004a0ddf 85c0                     test      eax, eax
004a0de1 7414                     je        0x4a0df7
004a0de3 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004a0de6 52                       push      edx
004a0de7 50                       push      eax
004a0de8 8bce                     mov       ecx, esi
004a0dea e8e1e6ffff               call      0x49f4d0
004a0def 5f                       pop       edi
004a0df0 5e                       pop       esi
004a0df1 8be5                     mov       esp, ebp
004a0df3 5d                       pop       ebp
004a0df4 c20800                   ret       8
004a0df7 57                       push      edi
004a0df8 6848f1cc00               push      0xccf148
004a0dfd ff15bc2eff00             call      dword ptr [0xff2ebc]
004a0e03 83c408                   add       esp, 8
004a0e06 5f                       pop       edi
004a0e07 5e                       pop       esi
004a0e08 8be5                     mov       esp, ebp
004a0e0a 5d                       pop       ebp
004a0e0b c20800                   ret       8
004a0e0e cc                       int3      
004a0e0f cc                       int3      
004a0e10 8b4104                   mov       eax, dword ptr [ecx + 4]
004a0e13 85c0                     test      eax, eax
004a0e15 750a                     jne       0x4a0e21
004a0e17 33c9                     xor       ecx, ecx
004a0e19 85c0                     test      eax, eax
004a0e1b 0f94c1                   sete      cl
004a0e1e 8ac1                     mov       al, cl
004a0e20 c3                       ret       
004a0e21 8b4908                   mov       ecx, dword ptr [ecx + 8]
004a0e24 2bc8                     sub       ecx, eax
004a0e26 b8abaaaa2a               mov       eax, 0x2aaaaaab
004a0e2b f7e9                     imul      ecx
004a0e2d c1fa03                   sar       edx, 3
004a0e30 8bc2                     mov       eax, edx
004a0e32 c1e81f                   shr       eax, 0x1f
004a0e35 03c2                     add       eax, edx
004a0e37 33c9                     xor       ecx, ecx
004a0e39 85c0                     test      eax, eax
004a0e3b 0f94c1                   sete      cl
004a0e3e 8ac1                     mov       al, cl
004a0e40 c3                       ret       
004a0e41 cc                       int3      
004a0e42 cc                       int3      
004a0e43 cc                       int3      
004a0e44 cc                       int3      
004a0e45 cc                       int3      
004a0e46 cc                       int3      
004a0e47 cc                       int3      
004a0e48 cc                       int3      
004a0e49 cc                       int3      
004a0e4a cc                       int3      
004a0e4b cc                       int3      
004a0e4c cc                       int3      
004a0e4d cc                       int3      
004a0e4e cc                       int3      
004a0e4f cc                       int3      
004a0e50 8b4104                   mov       eax, dword ptr [ecx + 4]
004a0e53 8b5108                   mov       edx, dword ptr [ecx + 8]
004a0e56 2bd0                     sub       edx, eax
004a0e58 b895204f09               mov       eax, 0x94f2095
004a0e5d f7ea                     imul      edx
004a0e5f c1fa04                   sar       edx, 4
004a0e62 8bc2                     mov       eax, edx
004a0e64 c1e81f                   shr       eax, 0x1f
004a0e67 03c2                     add       eax, edx
004a0e69 c3                       ret       
004a0e6a cc                       int3      
004a0e6b cc                       int3      
004a0e6c cc                       int3      
004a0e6d cc                       int3      
004a0e6e cc                       int3      
004a0e6f cc                       int3      
004a0e70 8b5104                   mov       edx, dword ptr [ecx + 4]
004a0e73 85d2                     test      edx, edx
004a0e75 750c                     jne       0x4a0e83
004a0e77 33c0                     xor       eax, eax
004a0e79 33c9                     xor       ecx, ecx
004a0e7b 85c0                     test      eax, eax
004a0e7d 0f94c1                   sete      cl
004a0e80 8ac1                     mov       al, cl
004a0e82 c3                       ret       
004a0e83 8b4108                   mov       eax, dword ptr [ecx + 8]
004a0e86 2bc2                     sub       eax, edx
004a0e88 c1f804                   sar       eax, 4
004a0e8b 33c9                     xor       ecx, ecx
004a0e8d 85c0                     test      eax, eax
004a0e8f 0f94c1                   sete      cl
004a0e92 8ac1                     mov       al, cl
004a0e94 c3                       ret       
004a0e95 cc                       int3      
004a0e96 cc                       int3      
004a0e97 cc                       int3      
004a0e98 cc                       int3      
004a0e99 cc                       int3      
004a0e9a cc                       int3      
004a0e9b cc                       int3      
004a0e9c cc                       int3      
004a0e9d cc                       int3      
004a0e9e cc                       int3      
004a0e9f cc                       int3      
004a0ea0 55                       push      ebp
004a0ea1 8bec                     mov       ebp, esp
004a0ea3 8b510c                   mov       edx, dword ptr [ecx + 0xc]
004a0ea6 53                       push      ebx
004a0ea7 8b5904                   mov       ebx, dword ptr [ecx + 4]
004a0eaa 2bd3                     sub       edx, ebx
004a0eac b895204f09               mov       eax, 0x94f2095
004a0eb1 f7ea                     imul      edx
004a0eb3 c1fa04                   sar       edx, 4
004a0eb6 8bc2                     mov       eax, edx
004a0eb8 c1e81f                   shr       eax, 0x1f
004a0ebb 56                       push      esi
004a0ebc 8d740204                 lea       esi, [edx + eax + 4]
004a0ec0 8bd6                     mov       edx, esi
004a0ec2 d1ea                     shr       edx, 1
004a0ec4 03f2                     add       esi, edx
004a0ec6 57                       push      edi
004a0ec7 8b7908                   mov       edi, dword ptr [ecx + 8]
004a0eca 8bd7                     mov       edx, edi
004a0ecc 2bd3                     sub       edx, ebx
004a0ece 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a0ed1 b895204f09               mov       eax, 0x94f2095
004a0ed6 f7ea                     imul      edx
004a0ed8 c1fa04                   sar       edx, 4
004a0edb 8bc2                     mov       eax, edx
004a0edd c1e81f                   shr       eax, 0x1f
004a0ee0 03c2                     add       eax, edx
004a0ee2 03c3                     add       eax, ebx
004a0ee4 3bc6                     cmp       eax, esi
004a0ee6 731d                     jae       0x4a0f05
004a0ee8 81fe80000000             cmp       esi, 0x80
004a0eee 730c                     jae       0x4a0efc
004a0ef0 5f                       pop       edi
004a0ef1 5e                       pop       esi
004a0ef2 b880000000               mov       eax, 0x80
004a0ef7 5b                       pop       ebx
004a0ef8 5d                       pop       ebp
004a0ef9 c20400                   ret       4
004a0efc 5f                       pop       edi
004a0efd 8bc6                     mov       eax, esi
004a0eff 5e                       pop       esi
004a0f00 5b                       pop       ebx
004a0f01 5d                       pop       ebp
004a0f02 c20400                   ret       4
004a0f05 2b7904                   sub       edi, dword ptr [ecx + 4]
004a0f08 b895204f09               mov       eax, 0x94f2095
004a0f0d f7ef                     imul      edi
004a0f0f c1fa04                   sar       edx, 4
004a0f12 8bca                     mov       ecx, edx
004a0f14 c1e91f                   shr       ecx, 0x1f
004a0f17 03ca                     add       ecx, edx
004a0f19 03cb                     add       ecx, ebx
004a0f1b 85c9                     test      ecx, ecx
004a0f1d 894d08                   mov       dword ptr [ebp + 8], ecx
004a0f20 db4508                   fild      dword ptr [ebp + 8]
004a0f23 7d06                     jge       0x4a0f2b
004a0f25 d805cc46cc00             fadd      dword ptr [0xcc46cc]
004a0f2b d80d7881cc00             fmul      dword ptr [0xcc8178]
004a0f31 e80e067600               call      0xc01544
004a0f36 5f                       pop       edi
004a0f37 5e                       pop       esi
004a0f38 5b                       pop       ebx
004a0f39 5d                       pop       ebp
004a0f3a c20400                   ret       4
004a0f3d cc                       int3      
004a0f3e cc                       int3      
004a0f3f cc                       int3      
004a0f40 55                       push      ebp
004a0f41 8bec                     mov       ebp, esp
004a0f43 53                       push      ebx
004a0f44 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a0f47 56                       push      esi
004a0f48 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004a0f4b 3bde                     cmp       ebx, esi
004a0f4d 744a                     je        0x4a0f99
004a0f4f 57                       push      edi
004a0f50 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004a0f53 8b46e0                   mov       eax, dword ptr [esi - 0x20]
004a0f56 83ee20                   sub       esi, 0x20
004a0f59 8d4e04                   lea       ecx, [esi + 4]
004a0f5c 83ef20                   sub       edi, 0x20
004a0f5f 51                       push      ecx
004a0f60 8d4f04                   lea       ecx, [edi + 4]
004a0f63 8907                     mov       dword ptr [edi], eax
004a0f65 e826255b00               call      0xa53490
004a0f6a 3bf3                     cmp       esi, ebx
004a0f6c 8b5608                   mov       edx, dword ptr [esi + 8]
004a0f6f 895708                   mov       dword ptr [edi + 8], edx
004a0f72 8b460c                   mov       eax, dword ptr [esi + 0xc]
004a0f75 89470c                   mov       dword ptr [edi + 0xc], eax
004a0f78 8b4e10                   mov       ecx, dword ptr [esi + 0x10]
004a0f7b 894f10                   mov       dword ptr [edi + 0x10], ecx
004a0f7e 8b5614                   mov       edx, dword ptr [esi + 0x14]
004a0f81 895714                   mov       dword ptr [edi + 0x14], edx
004a0f84 8b4618                   mov       eax, dword ptr [esi + 0x18]
004a0f87 894718                   mov       dword ptr [edi + 0x18], eax
004a0f8a 8a4e1c                   mov       cl, byte ptr [esi + 0x1c]
004a0f8d 884f1c                   mov       byte ptr [edi + 0x1c], cl
004a0f90 75c1                     jne       0x4a0f53
004a0f92 8bc7                     mov       eax, edi
004a0f94 5f                       pop       edi
004a0f95 5e                       pop       esi
004a0f96 5b                       pop       ebx
004a0f97 5d                       pop       ebp
004a0f98 c3                       ret       
004a0f99 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004a0f9c 5e                       pop       esi
004a0f9d 5b                       pop       ebx
004a0f9e 5d                       pop       ebp
004a0f9f c3                       ret       
004a0fa0 55                       push      ebp
004a0fa1 8bec                     mov       ebp, esp
004a0fa3 51                       push      ecx
004a0fa4 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004a0faa 8b5244                   mov       edx, dword ptr [edx + 0x44]
004a0fad 8bc1                     mov       eax, ecx
004a0faf 8b4804                   mov       ecx, dword ptr [eax + 4]
004a0fb2 8d148a                   lea       edx, [edx + ecx*4]
004a0fb5 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004a0fbb 56                       push      esi
004a0fbc 8b32                     mov       esi, dword ptr [edx]
004a0fbe 33f2                     xor       esi, edx
004a0fc0 33f1                     xor       esi, ecx
004a0fc2 8975fc                   mov       dword ptr [ebp - 4], esi
004a0fc5 8b7508                   mov       esi, dword ptr [ebp + 8]
004a0fc8 d945fc                   fld       dword ptr [ebp - 4]
004a0fcb d80e                     fmul      dword ptr [esi]
004a0fcd 57                       push      edi
004a0fce 8bfa                     mov       edi, edx
004a0fd0 33f9                     xor       edi, ecx
004a0fd2 d95d08                   fstp      dword ptr [ebp + 8]
004a0fd5 337d08                   xor       edi, dword ptr [ebp + 8]
004a0fd8 893a                     mov       dword ptr [edx], edi
004a0fda 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004a0fe0 8b4804                   mov       ecx, dword ptr [eax + 4]
004a0fe3 8b5248                   mov       edx, dword ptr [edx + 0x48]
004a0fe6 8b3c8a                   mov       edi, dword ptr [edx + ecx*4]
004a0fe9 8d148a                   lea       edx, [edx + ecx*4]
004a0fec 8b                       .byte     0x8b
004a0fed 0d                       .byte     0x0d
004a0fee dc01                     fadd      qword ptr [ecx]
