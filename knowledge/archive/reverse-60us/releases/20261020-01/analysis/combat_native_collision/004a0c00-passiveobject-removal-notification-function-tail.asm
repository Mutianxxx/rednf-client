004a0c00 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004a0c06 8b3d0ce6ff00             mov       edi, dword ptr [0xffe60c]
004a0c0c 8b1510e6ff00             mov       edx, dword ptr [0xffe610]
004a0c12 8bcb                     mov       ecx, ebx
004a0c14 33cf                     xor       ecx, edi
004a0c16 81e90ce6ff00             sub       ecx, 0xffe60c
004a0c1c 3bca                     cmp       ecx, edx
004a0c1e 741e                     je        0x4a0c3e
004a0c20 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a0c26 6a3f                     push      0x3f
004a0c28 680ce6ff00               push      0xffe60c
004a0c2d e87e646700               call      0xb170b0
004a0c32 8b1510e6ff00             mov       edx, dword ptr [0xffe610]
004a0c38 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004a0c3e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a0c44 8b4144                   mov       eax, dword ptr [ecx + 0x44]
004a0c47 8b3c90                   mov       edi, dword ptr [eax + edx*4]
004a0c4a 8d0490                   lea       eax, [eax + edx*4]
004a0c4d 33f8                     xor       edi, eax
004a0c4f 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004a0c52 8d0490                   lea       eax, [eax + edx*4]
004a0c55 8b10                     mov       edx, dword ptr [eax]
004a0c57 33d0                     xor       edx, eax
004a0c59 33fb                     xor       edi, ebx
004a0c5b 33d3                     xor       edx, ebx
004a0c5d 3bfa                     cmp       edi, edx
004a0c5f 740c                     je        0x4a0c6d
004a0c61 6a40                     push      0x40
004a0c63 680ce6ff00               push      0xffe60c
004a0c68 e843646700               call      0xb170b0
004a0c6d 85ff                     test      edi, edi
004a0c6f 0f850d010000             jne       0x4a0d82
004a0c75 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004a0c7b 81c140100000             add       ecx, 0x1040
004a0c81 e8da13f6ff               call      0x402060
004a0c86 83f803                   cmp       eax, 3
004a0c89 742c                     je        0x4a0cb7
004a0c8b 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004a0c91 81c140100000             add       ecx, 0x1040
004a0c97 e8c413f6ff               call      0x402060
004a0c9c 83f80a                   cmp       eax, 0xa
004a0c9f 7416                     je        0x4a0cb7
004a0ca1 8d8efc010000             lea       ecx, [esi + 0x1fc]
004a0ca7 e8b413f6ff               call      0x402060
004a0cac 3df97f0000               cmp       eax, 0x7ff9
004a0cb1 0f85cb000000             jne       0x4a0d82
004a0cb7 8dbefc010000             lea       edi, [esi + 0x1fc]
004a0cbd 8bcf                     mov       ecx, edi
004a0cbf e89c13f6ff               call      0x402060
004a0cc4 3df97f0000               cmp       eax, 0x7ff9
004a0cc9 0f85b3000000             jne       0x4a0d82
004a0ccf 8bcf                     mov       ecx, edi
004a0cd1 e88a13f6ff               call      0x402060
004a0cd6 3df97f0000               cmp       eax, 0x7ff9
004a0cdb 750e                     jne       0x4a0ceb
004a0cdd 6800f1cc00               push      0xccf100
004a0ce2 ff15bc2eff00             call      dword ptr [0xff2ebc]
004a0ce8 83c404                   add       esp, 4
004a0ceb b9fc510001               mov       ecx, 0x10051fc
004a0cf0 e86b13f6ff               call      0x402060
004a0cf5 50                       push      eax
004a0cf6 68e0f0cc00               push      0xccf0e0
004a0cfb ff15bc2eff00             call      dword ptr [0xff2ebc]
004a0d01 83c408                   add       esp, 8
004a0d04 8d4508                   lea       eax, [ebp + 8]
004a0d07 50                       push      eax
004a0d08 b9fc510001               mov       ecx, 0x10051fc
004a0d0d c7450801000000           mov       dword ptr [ebp + 8], 1
004a0d14 e89769fcff               call      0x4676b0
004a0d19 b9fc510001               mov       ecx, 0x10051fc
004a0d1e e83d13f6ff               call      0x402060
004a0d23 85c0                     test      eax, eax
004a0d25 7f5b                     jg        0x4a0d82
004a0d27 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a0d2d 6a01                     push      1
004a0d2f e87ca00600               call      0x50adb0
004a0d34 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a0d3a 8b8914010000             mov       ecx, dword ptr [ecx + 0x114]
004a0d40 6a00                     push      0
004a0d42 6a1e                     push      0x1e
004a0d44 6870170000               push      0x1770
004a0d49 e8b28e0900               call      0x539c00
004a0d4e 6a00                     push      0
004a0d50 6a00                     push      0
004a0d52 6aff                     push      -1
004a0d54 68c0f0cc00               push      0xccf0c0
004a0d59 e8526cfaff               call      0x4479b0
004a0d5e 8b16                     mov       edx, dword ptr [esi]
004a0d60 83c410                   add       esp, 0x10
004a0d63 6a00                     push      0
004a0d65 8bce                     mov       ecx, esi
004a0d67 ff92d8020000             call      dword ptr [edx + 0x2d8]
004a0d6d 8b8600010000             mov       eax, dword ptr [esi + 0x100]
004a0d73 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
004a0d79 6a00                     push      0
004a0d7b 6a04                     push      4
004a0d7d e8eeb00900               call      0x53be70
004a0d82 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a0d85 5f                       pop       edi
004a0d86 5e                       pop       esi
004a0d87 5b                       pop       ebx
004a0d88 64890d00000000           mov       dword ptr fs:[0], ecx
004a0d8f 8be5                     mov       esp, ebp
004a0d91 5d                       pop       ebp
004a0d92 c20400                   ret       4
004a0d95 cc                       int3      
004a0d96 cc                       int3      
004a0d97 cc                       int3      
004a0d98 cc                       int3      
004a0d99 cc                       int3      
004a0d9a cc                       int3      
004a0d9b cc                       int3      
004a0d9c cc                       int3      
004a0d9d cc                       int3      
004a0d9e cc                       int3      
004a0d9f cc                       int3      
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
004a0e5f c1                       .byte     0xc1
