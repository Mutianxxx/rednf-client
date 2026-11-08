004b4e00 55                       push      ebp
004b4e01 8bec                     mov       ebp, esp
004b4e03 6aff                     push      -1
004b4e05 68e776c500               push      0xc576e7
004b4e0a 64a100000000             mov       eax, dword ptr fs:[0]
004b4e10 50                       push      eax
004b4e11 64892500000000           mov       dword ptr fs:[0], esp
004b4e18 83ec0c                   sub       esp, 0xc
004b4e1b 53                       push      ebx
004b4e1c 8bd9                     mov       ebx, ecx
004b4e1e 8b8bdc120000             mov       ecx, dword ptr [ebx + 0x12dc]
004b4e24 85c9                     test      ecx, ecx
004b4e26 56                       push      esi
004b4e27 57                       push      edi
004b4e28 7409                     je        0x4b4e33
004b4e2a 8d4508                   lea       eax, [ebp + 8]
004b4e2d 50                       push      eax
004b4e2e e8dd1e0000               call      0x4b6d10
004b4e33 8b13                     mov       edx, dword ptr [ebx]
004b4e35 8bcb                     mov       ecx, ebx
004b4e37 ff9260030000             call      dword ptr [edx + 0x360]
004b4e3d 8bc8                     mov       ecx, eax
004b4e3f e81cd2f4ff               call      0x402060
004b4e44 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004b4e47 8b13                     mov       edx, dword ptr [ebx]
004b4e49 2bc1                     sub       eax, ecx
004b4e4b 8945f0                   mov       dword ptr [ebp - 0x10], eax
004b4e4e 33c0                     xor       eax, eax
004b4e50 85c9                     test      ecx, ecx
004b4e52 0f9cc0                   setl      al
004b4e55 48                       dec       eax
004b4e56 23c1                     and       eax, ecx
004b4e58 8bcb                     mov       ecx, ebx
004b4e5a 894508                   mov       dword ptr [ebp + 8], eax
004b4e5d ff9238020000             call      dword ptr [edx + 0x238]
004b4e63 8b5508                   mov       edx, dword ptr [ebp + 8]
004b4e66 3bc2                     cmp       eax, edx
004b4e68 7d0f                     jge       0x4b4e79
004b4e6a 8b03                     mov       eax, dword ptr [ebx]
004b4e6c 8bcb                     mov       ecx, ebx
004b4e6e ff9038020000             call      dword ptr [eax + 0x238]
004b4e74 8bd0                     mov       edx, eax
004b4e76 895508                   mov       dword ptr [ebp + 8], edx
004b4e79 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b4e7f 8b8334120000             mov       eax, dword ptr [ebx + 0x1234]
004b4e85 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004b4e88 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004b4e8e c1e002                   shl       eax, 2
004b4e91 8d3408                   lea       esi, [eax + ecx]
004b4e94 33f7                     xor       esi, edi
004b4e96 33f2                     xor       esi, edx
004b4e98 893408                   mov       dword ptr [eax + ecx], esi
004b4e9b a1d8012101               mov       eax, dword ptr [0x12101d8]
004b4ea0 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004b4ea3 8b8334120000             mov       eax, dword ptr [ebx + 0x1234]
004b4ea9 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004b4eaf c1e002                   shl       eax, 2
004b4eb2 8d3408                   lea       esi, [eax + ecx]
004b4eb5 33f7                     xor       esi, edi
004b4eb7 33f2                     xor       esi, edx
004b4eb9 893408                   mov       dword ptr [eax + ecx], esi
004b4ebc 8b4508                   mov       eax, dword ptr [ebp + 8]
004b4ebf 33ff                     xor       edi, edi
004b4ec1 3bc7                     cmp       eax, edi
004b4ec3 7f0c                     jg        0x4b4ed1
004b4ec5 8b13                     mov       edx, dword ptr [ebx]
004b4ec7 6a01                     push      1
004b4ec9 8bcb                     mov       ecx, ebx
004b4ecb ff92d8030000             call      dword ptr [edx + 0x3d8]
004b4ed1 8a4510                   mov       al, byte ptr [ebp + 0x10]
004b4ed4 84c0                     test      al, al
004b4ed6 7442                     je        0x4b4f1a
004b4ed8 a1d8012101               mov       eax, dword ptr [0x12101d8]
004b4edd 8b4844                   mov       ecx, dword ptr [eax + 0x44]
004b4ee0 8b83c8150000             mov       eax, dword ptr [ebx + 0x15c8]
004b4ee6 8b35dc012101             mov       esi, dword ptr [0x12101dc]
004b4eec c1e002                   shl       eax, 2
004b4eef 8d1408                   lea       edx, [eax + ecx]
004b4ef2 f7d2                     not       edx
004b4ef4 33d6                     xor       edx, esi
004b4ef6 891408                   mov       dword ptr [eax + ecx], edx
004b4ef9 a1d8012101               mov       eax, dword ptr [0x12101d8]
004b4efe 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004b4f01 8b83c8150000             mov       eax, dword ptr [ebx + 0x15c8]
004b4f07 8b35dc012101             mov       esi, dword ptr [0x12101dc]
004b4f0d c1e002                   shl       eax, 2
004b4f10 8d1408                   lea       edx, [eax + ecx]
004b4f13 f7d2                     not       edx
004b4f15 33d6                     xor       edx, esi
004b4f17 891408                   mov       dword ptr [eax + ecx], edx
004b4f1a 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004b4f1d 3bc7                     cmp       eax, edi
004b4f1f 7e0f                     jle       0x4b4f30
004b4f21 8b13                     mov       edx, dword ptr [ebx]
004b4f23 50                       push      eax
004b4f24 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004b4f27 50                       push      eax
004b4f28 8bcb                     mov       ecx, ebx
004b4f2a ff923c050000             call      dword ptr [edx + 0x53c]
004b4f30 8b13                     mov       edx, dword ptr [ebx]
004b4f32 6811010000               push      0x111
004b4f37 8bcb                     mov       ecx, ebx
004b4f39 ff522c                   call      dword ptr [edx + 0x2c]
004b4f3c 84c0                     test      al, al
004b4f3e 0f85b2020000             jne       0x4b51f6
004b4f44 b90ce6ff00               mov       ecx, 0xffe60c
004b4f49 e812d1f4ff               call      0x402060
004b4f4e 85c0                     test      eax, eax
004b4f50 0f85a0020000             jne       0x4b51f6
004b4f56 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004b4f5c 3bc7                     cmp       eax, edi
004b4f5e 0f8492020000             je        0x4b51f6
004b4f64 39b814010000             cmp       dword ptr [eax + 0x114], edi
004b4f6a 0f8486020000             je        0x4b51f6
004b4f70 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004b4f76 81c140100000             add       ecx, 0x1040
004b4f7c e8dfd0f4ff               call      0x402060
004b4f81 83f803                   cmp       eax, 3
004b4f84 0f856c020000             jne       0x4b51f6
004b4f8a 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004b4f90 8b8014010000             mov       eax, dword ptr [eax + 0x114]
004b4f96 8bb0b4000000             mov       esi, dword ptr [eax + 0xb4]
004b4f9c 397d08                   cmp       dword ptr [ebp + 8], edi
004b4f9f 0f8f51020000             jg        0x4b51f6
004b4fa5 3bf7                     cmp       esi, edi
004b4fa7 0f8449020000             je        0x4b51f6
004b4fad b9604c0001               mov       ecx, 0x1004c60
004b4fb2 e8a9d0f4ff               call      0x402060
004b4fb7 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b4fba c1e004                   shl       eax, 4
004b4fbd 03c1                     add       eax, ecx
004b4fbf 8bc8                     mov       ecx, eax
004b4fc1 e8aaf71f00               call      0x6b4770
004b4fc6 84c0                     test      al, al
004b4fc8 0f8528020000             jne       0x4b51f6
004b4fce 8b0d644c0001             mov       ecx, dword ptr [0x1004c64]
004b4fd4 8b15604c0001             mov       edx, dword ptr [0x1004c60]
004b4fda 51                       push      ecx
004b4fdb 52                       push      edx
004b4fdc 680012cd00               push      0xcd1200
004b4fe1 ff15bc2eff00             call      dword ptr [0xff2ebc]
004b4fe7 83c40c                   add       esp, 0xc
004b4fea 8d4510                   lea       eax, [ebp + 0x10]
004b4fed 50                       push      eax
004b4fee 8d4de8                   lea       ecx, [ebp - 0x18]
004b4ff1 897d10                   mov       dword ptr [ebp + 0x10], edi
004b4ff4 e857d1f4ff               call      0x402150
004b4ff9 b9604c0001               mov       ecx, 0x1004c60
004b4ffe 897dfc                   mov       dword ptr [ebp - 4], edi
004b5001 c6451300                 mov       byte ptr [ebp + 0x13], 0
004b5005 897d0c                   mov       dword ptr [ebp + 0xc], edi
004b5008 e853d0f4ff               call      0x402060
004b500d 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5010 c1e004                   shl       eax, 4
004b5013 03c1                     add       eax, ecx
004b5015 8bc8                     mov       ecx, eax
004b5017 e834462600               call      0x719650
004b501c 85c0                     test      eax, eax
004b501e 0f86a7010000             jbe       0x4b51cb
004b5024 b9604c0001               mov       ecx, 0x1004c60
004b5029 e832d0f4ff               call      0x402060
004b502e 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5031 c1e004                   shl       eax, 4
004b5034 03c1                     add       eax, ecx
004b5036 8b4004                   mov       eax, dword ptr [eax + 4]
004b5039 833c0704                 cmp       dword ptr [edi + eax], 4
004b503d 7556                     jne       0x4b5095
004b503f 8bcb                     mov       ecx, ebx
004b5041 e81aacf6ff               call      0x41fc60
004b5046 84c0                     test      al, al
004b5048 744b                     je        0x4b5095
004b504a 8b13                     mov       edx, dword ptr [ebx]
004b504c 8bcb                     mov       ecx, ebx
004b504e ff92dc030000             call      dword ptr [edx + 0x3dc]
004b5054 84c0                     test      al, al
004b5056 743d                     je        0x4b5095
004b5058 b9604c0001               mov       ecx, 0x1004c60
004b505d e8                       .byte     0xe8
004b505e fecf                     dec       bh
