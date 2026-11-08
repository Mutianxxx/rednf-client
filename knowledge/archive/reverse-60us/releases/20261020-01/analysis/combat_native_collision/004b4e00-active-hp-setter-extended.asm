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
004b505d e8fecff4ff               call      0x402060
004b5062 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5065 c1e004                   shl       eax, 4
004b5068 03c1                     add       eax, ecx
004b506a 8b4004                   mov       eax, dword ptr [eax + 4]
004b506d 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004b5071 85c9                     test      ecx, ecx
004b5073 7420                     je        0x4b5095
004b5075 b9604c0001               mov       ecx, 0x1004c60
004b507a e8e1cff4ff               call      0x402060
004b507f 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5082 c1e004                   shl       eax, 4
004b5085 03c1                     add       eax, ecx
004b5087 8b4004                   mov       eax, dword ptr [eax + 4]
004b508a 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004b508e 8d440708                 lea       eax, [edi + eax + 8]
004b5092 49                       dec       ecx
004b5093 8908                     mov       dword ptr [eax], ecx
004b5095 b9604c0001               mov       ecx, 0x1004c60
004b509a e8c1cff4ff               call      0x402060
004b509f 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b50a2 c1e004                   shl       eax, 4
004b50a5 03c1                     add       eax, ecx
004b50a7 8b4004                   mov       eax, dword ptr [eax + 4]
004b50aa 833c0703                 cmp       dword ptr [edi + eax], 3
004b50ae 0f85c5000000             jne       0x4b5179
004b50b4 6a00                     push      0
004b50b6 688c52f500               push      0xf5528c
004b50bb 686c52f500               push      0xf5526c
004b50c0 6a00                     push      0
004b50c2 53                       push      ebx
004b50c3 e843bc7400               call      0xc00d0b
004b50c8 83c414                   add       esp, 0x14
004b50cb 85c0                     test      eax, eax
004b50cd 0f84a6000000             je        0x4b5179
004b50d3 8b10                     mov       edx, dword ptr [eax]
004b50d5 8bc8                     mov       ecx, eax
004b50d7 ff5234                   call      dword ptr [edx + 0x34]
004b50da 84c0                     test      al, al
004b50dc 0f8497000000             je        0x4b5179
004b50e2 8b83a02a0000             mov       eax, dword ptr [ebx + 0x2aa0]
004b50e8 85c0                     test      eax, eax
004b50ea 0f8489000000             je        0x4b5179
004b50f0 a1644c0001               mov       eax, dword ptr [0x1004c64]
004b50f5 8b0d604c0001             mov       ecx, dword ptr [0x1004c60]
004b50fb 50                       push      eax
004b50fc 51                       push      ecx
004b50fd 68b811cd00               push      0xcd11b8
004b5102 ff15bc2eff00             call      dword ptr [0xff2ebc]
004b5108 83c40c                   add       esp, 0xc
004b510b b9604c0001               mov       ecx, 0x1004c60
004b5110 e84bcff4ff               call      0x402060
004b5115 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5118 c1e004                   shl       eax, 4
004b511b 8b540804                 mov       edx, dword ptr [eax + ecx + 4]
004b511f 03c1                     add       eax, ecx
004b5121 8d8b78280000             lea       ecx, [ebx + 0x2878]
004b5127 8955f0                   mov       dword ptr [ebp - 0x10], edx
004b512a e831cff4ff               call      0x402060
004b512f 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004b5132 39440f04                 cmp       dword ptr [edi + ecx + 4], eax
004b5136 7541                     jne       0x4b5179
004b5138 b9604c0001               mov       ecx, 0x1004c60
004b513d e81ecff4ff               call      0x402060
004b5142 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5145 c1e004                   shl       eax, 4
004b5148 03c1                     add       eax, ecx
004b514a 8b4004                   mov       eax, dword ptr [eax + 4]
004b514d 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004b5151 85c9                     test      ecx, ecx
004b5153 7424                     je        0x4b5179
004b5155 b9604c0001               mov       ecx, 0x1004c60
004b515a e801cff4ff               call      0x402060
004b515f 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5162 c1e004                   shl       eax, 4
004b5165 03c1                     add       eax, ecx
004b5167 8b4004                   mov       eax, dword ptr [eax + 4]
004b516a 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004b516e 8d440708                 lea       eax, [edi + eax + 8]
004b5172 49                       dec       ecx
004b5173 8908                     mov       dword ptr [eax], ecx
004b5175 c6451301                 mov       byte ptr [ebp + 0x13], 1
004b5179 b9604c0001               mov       ecx, 0x1004c60
004b517e e8ddcef4ff               call      0x402060
004b5183 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b5186 c1e004                   shl       eax, 4
004b5189 03c1                     add       eax, ecx
004b518b 8b4004                   mov       eax, dword ptr [eax + 4]
004b518e 8b540708                 mov       edx, dword ptr [edi + eax + 8]
004b5192 8d45f0                   lea       eax, [ebp - 0x10]
004b5195 50                       push      eax
004b5196 8d4de8                   lea       ecx, [ebp - 0x18]
004b5199 8955f0                   mov       dword ptr [ebp - 0x10], edx
004b519c e86faaf5ff               call      0x40fc10
004b51a1 ff450c                   inc       dword ptr [ebp + 0xc]
004b51a4 b9604c0001               mov       ecx, 0x1004c60
004b51a9 83c70c                   add       edi, 0xc
004b51ac e8afcef4ff               call      0x402060
004b51b1 8b4e04                   mov       ecx, dword ptr [esi + 4]
004b51b4 c1e004                   shl       eax, 4
004b51b7 03c1                     add       eax, ecx
004b51b9 8bc8                     mov       ecx, eax
004b51bb e890442600               call      0x719650
004b51c0 39450c                   cmp       dword ptr [ebp + 0xc], eax
004b51c3 0f825bfeffff             jb        0x4b5024
004b51c9 33ff                     xor       edi, edi
004b51cb 8d4de8                   lea       ecx, [ebp - 0x18]
004b51ce e88dcef4ff               call      0x402060
004b51d3 85c0                     test      eax, eax
004b51d5 7510                     jne       0x4b51e7
004b51d7 8a4513                   mov       al, byte ptr [ebp + 0x13]
004b51da 84c0                     test      al, al
004b51dc 7409                     je        0x4b51e7
004b51de 6a01                     push      1
004b51e0 8bcb                     mov       ecx, ebx
004b51e2 e849c1feff               call      0x4a1330
004b51e7 8d4de8                   lea       ecx, [ebp - 0x18]
004b51ea c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004b51f1 e81acef4ff               call      0x402010
004b51f6 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004b51fc 81c140100000             add       ecx, 0x1040
004b5202 e859cef4ff               call      0x402060
004b5207 83f803                   cmp       eax, 3
004b520a 742c                     je        0x4b5238
004b520c 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004b5212 81c140100000             add       ecx, 0x1040
004b5218 e843cef4ff               call      0x402060
004b521d 83f80a                   cmp       eax, 0xa
004b5220 7416                     je        0x4b5238
004b5222 8d8bfc010000             lea       ecx, [ebx + 0x1fc]
004b5228 e833cef4ff               call      0x402060
004b522d 3df97f0000               cmp       eax, 0x7ff9
004b5232 0f8510010000             jne       0x4b5348
004b5238 8b83e4190000             mov       eax, dword ptr [ebx + 0x19e4]
004b523e 83f803                   cmp       eax, 3
004b5241 7405                     je        0x4b5248
004b5243 83f808                   cmp       eax, 8
004b5246 750e                     jne       0x4b5256
004b5248 8b13                     mov       edx, dword ptr [ebx]
004b524a 8bcb                     mov       ecx, ebx
004b524c ff92dc030000             call      dword ptr [edx + 0x3dc]
004b5252 84c0                     test      al, al
004b5254 7516                     jne       0x4b526c
004b5256 8d8bfc010000             lea       ecx, [ebx + 0x1fc]
004b525c e8ffcdf4ff               call      0x402060
004b5261 3df97f0000               cmp       eax, 0x7ff9
004b5266 0f85dc000000             jne       0x4b5348
004b526c 8b03                     mov       eax, dword ptr [ebx]
004b526e 8bcb                     mov       ecx, ebx
004b5270 ff9048050000             call      dword ptr [eax + 0x548]
004b5276 8d8bfc010000             lea       ecx, [ebx + 0x1fc]
004b527c e8dfcdf4ff               call      0x402060
004b5281 3df97f0000               cmp       eax, 0x7ff9
004b5286 750e                     jne       0x4b5296
004b5288 6800f1cc00               push      0xccf100
004b528d ff15bc2eff00             call      dword ptr [0xff2ebc]
004b5293 83c404                   add       esp, 4
004b5296 b9fc510001               mov       ecx, 0x10051fc
004b529b e8c0cdf4ff               call      0x402060
004b52a0 50                       push      eax
004b52a1 68e0f0cc00               push      0xccf0e0
004b52a6 ff15bc2eff00             call      dword ptr [0xff2ebc]
004b52ac 83c408                   add       esp, 8
004b52af 8d4d10                   lea       ecx, [ebp + 0x10]
004b52b2 51                       push      ecx
004b52b3 b9fc510001               mov       ecx, 0x10051fc
004b52b8 c7451001000000           mov       dword ptr [ebp + 0x10], 1
004b52bf e8ec23fbff               call      0x4676b0
004b52c4 b9fc510001               mov       ecx, 0x10051fc
004b52c9 e892cdf4ff               call      0x402060
004b52ce 85c0                     test      eax, eax
004b52d0 7f76                     jg        0x4b5348
004b52d2 8b8b00010000             mov       ecx, dword ptr [ebx + 0x100]
004b52d8 6a01                     push      1
004b52da e8d15a0500               call      0x50adb0
004b52df 8b9300010000             mov       edx, dword ptr [ebx + 0x100]
004b52e5 8bb214010000             mov       esi, dword ptr [edx + 0x114]
004b52eb 8bcb                     mov       ecx, ebx
004b52ed e80e72ffff               call      0x4ac500
004b52f2 3b05d4f10401             cmp       eax, dword ptr [0x104f1d4]
004b52f8 0f94c0                   sete      al
004b52fb 8bce                     mov       ecx, esi
004b52fd 50                       push      eax
004b52fe 6a1e                     push      0x1e
004b5300 6870170000               push      0x1770
004b5305 e8f6480800               call      0x539c00
004b530a 57                       push      edi
004b530b 57                       push      edi
004b530c 6aff                     push      -1
004b530e 68c0f0cc00               push      0xccf0c0
004b5313 e89826f9ff               call      0x4479b0
004b5318 83c410                   add       esp, 0x10
004b531b 8d8be8190000             lea       ecx, [ebx + 0x19e8]
004b5321 51                       push      ecx
004b5322 8bcb                     mov       ecx, ebx
004b5324 e847f5ffff               call      0x4b4870
004b5329 8b13                     mov       edx, dword ptr [ebx]
004b532b 57                       push      edi
004b532c 8bcb                     mov       ecx, ebx
004b532e ff92d8020000             call      dword ptr [edx + 0x2d8]
004b5334 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004b533a 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
004b5340 57                       push      edi
004b5341 6a04                     push      4
004b5343 e8286b0800               call      0x53be70
004b5348 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004b534b 5f                       pop       edi
004b534c 5e                       pop       esi
004b534d 5b                       pop       ebx
004b534e 64890d00000000           mov       dword ptr fs:[0], ecx
004b5355 8be5                     mov       esp, ebp
004b5357 5d                       pop       ebp
004b5358 c20c00                   ret       0xc
004b535b cc                       int3      
004b535c cc                       int3      
004b535d cc                       int3      
004b535e cc                       int3      
004b535f cc                       int3      
004b5360 55                       push      ebp
004b5361 8bec                     mov       ebp, esp
004b5363 d94508                   fld       dword ptr [ebp + 8]
004b5366 dc25f0b8ca00             fsub      qword ptr [0xcab8f0]
004b536c d9e1                     fabs      
004b536e d94508                   fld       dword ptr [ebp + 8]
004b5371 d9e1                     fabs      
004b5373 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
004b5379 ded9                     fcompp    
004b537b dfe0                     fnstsw    ax
004b537d f6c401                   test      ah, 1
004b5380 750e                     jne       0x4b5390
004b5382 c781401900000000803f     mov       dword ptr [ecx + 0x1940], 0x3f800000
004b538c 5d                       pop       ebp
004b538d c20400                   ret       4
004b5390 8b4508                   mov       eax, dword ptr [ebp + 8]
004b5393 898140190000             mov       dword ptr [ecx + 0x1940], eax
004b5399 5d                       pop       ebp
004b539a c20400                   ret       4
004b539d cc                       int3      
004b539e cc                       int3      
004b539f cc                       int3      
004b53a0 55                       push      ebp
004b53a1 8bec                     mov       ebp, esp
004b53a3 51                       push      ecx
004b53a4 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004b53aa 8b5244                   mov       edx, dword ptr [edx + 0x44]
004b53ad 8bc1                     mov       eax, ecx
004b53af 8b4804                   mov       ecx, dword ptr [eax + 4]
004b53b2 8d148a                   lea       edx, [edx + ecx*4]
004b53b5 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004b53bb 56                       push      esi
004b53bc 8b32                     mov       esi, dword ptr [edx]
004b53be 33f2                     xor       esi, edx
004b53c0 33f1                     xor       esi, ecx
004b53c2 8975fc                   mov       dword ptr [ebp - 4], esi
004b53c5 8b7508                   mov       esi, dword ptr [ebp + 8]
004b53c8 d945fc                   fld       dword ptr [ebp - 4]
004b53cb d826                     fsub      dword ptr [esi]
004b53cd 57                       push      edi
004b53ce 8bfa                     mov       edi, edx
004b53d0 33f9                     xor       edi, ecx
004b53d2 d95d08                   fstp      dword ptr [ebp + 8]
004b53d5 337d08                   xor       edi, dword ptr [ebp + 8]
004b53d8 893a                     mov       dword ptr [edx], edi
004b53da 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004b53e0 8b4804                   mov       ecx, dword ptr [eax + 4]
004b53e3 8b5248                   mov       edx, dword ptr [edx + 0x48]
004b53e6 8b3c8a                   mov       edi, dword ptr [edx + ecx*4]
004b53e9 8d148a                   lea       edx, [edx + ecx*4]
004b53ec 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004b53f2 33fa                     xor       edi, edx
004b53f4 33f9                     xor       edi, ecx
004b53f6 897d08                   mov       dword ptr [ebp + 8], edi
004b53f9 d94508                   fld       dword ptr [ebp + 8]
004b53fc 5f                       pop       edi
004b53fd d826                     fsub      dword ptr [esi]
004b53ff 8bf2                     mov       esi, edx
004b5401 33f1                     xor       esi, ecx
004b5403 d95d08                   fstp      dword ptr [ebp + 8]
004b5406 337508                   xor       esi, dword ptr [ebp + 8]
004b5409 8932                     mov       dword ptr [edx], esi
004b540b 5e                       pop       esi
004b540c 8be5                     mov       esp, ebp
004b540e 5d                       pop       ebp
004b540f c20400                   ret       4
004b5412 cc                       int3      
004b5413 cc                       int3      
004b5414 cc                       int3      
004b5415 cc                       int3      
004b5416 cc                       int3      
004b5417 cc                       int3      
004b5418 cc                       int3      
004b5419 cc                       int3      
004b541a cc                       int3      
004b541b cc                       int3      
004b541c cc                       int3      
004b541d cc                       int3      
004b541e cc                       int3      
004b541f cc                       int3      
004b5420 55                       push      ebp
004b5421 8bec                     mov       ebp, esp
004b5423 56                       push      esi
004b5424 57                       push      edi
004b5425 8b7d08                   mov       edi, dword ptr [ebp + 8]
004b5428 57                       push      edi
004b5429 8bf1                     mov       esi, ecx
004b542b e880f1f4ff               call      0x4045b0
004b5430 8d4708                   lea       eax, [edi + 8]
004b5433 50                       push      eax
004b5434 8d4e08                   lea       ecx, [esi + 8]
004b5437 e874f1f4ff               call      0x4045b0
004b543c 8d4f10                   lea       ecx, [edi + 0x10]
004b543f 51                       push      ecx
004b5440 8d4e10                   lea       ecx, [esi + 0x10]
004b5443 e868f1f4ff               call      0x4045b0
004b5448 8d5718                   lea       edx, [edi + 0x18]
004b544b 52                       push      edx
004b544c 8d4e18                   lea       ecx, [esi + 0x18]
004b544f e8                       .byte     0xe8
