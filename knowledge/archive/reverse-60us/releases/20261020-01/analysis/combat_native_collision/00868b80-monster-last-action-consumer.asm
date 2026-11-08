00868b80 da3b                     fidivr    dword ptr [ebx]
00868b82 f3741c                   je        0x868ba1
00868b85 8b4508                   mov       eax, dword ptr [ebp + 8]
00868b88 6a40                     push      0x40
00868b8a 0540070000               add       eax, 0x740
00868b8f 50                       push      eax
00868b90 e81be52a00               call      0xb170b0
00868b95 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868b9b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868ba1 85f6                     test      esi, esi
00868ba3 0f8482000000             je        0x868c2b
00868ba9 8b7508                   mov       esi, dword ptr [ebp + 8]
00868bac 8b8640070000             mov       eax, dword ptr [esi + 0x740]
00868bb2 8b9e44070000             mov       ebx, dword ptr [esi + 0x744]
00868bb8 81c640070000             add       esi, 0x740
00868bbe 33c2                     xor       eax, edx
00868bc0 2bc6                     sub       eax, esi
00868bc2 3bc3                     cmp       eax, ebx
00868bc4 7414                     je        0x868bda
00868bc6 6a3f                     push      0x3f
00868bc8 56                       push      esi
00868bc9 e8e2e42a00               call      0xb170b0
00868bce 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868bd4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868bda 8b4604                   mov       eax, dword ptr [esi + 4]
00868bdd 8b5944                   mov       ebx, dword ptr [ecx + 0x44]
00868be0 c1e002                   shl       eax, 2
00868be3 8d3403                   lea       esi, [ebx + eax]
00868be6 333403                   xor       esi, dword ptr [ebx + eax]
00868be9 33f2                     xor       esi, edx
00868beb 8975f0                   mov       dword ptr [ebp - 0x10], esi
00868bee 8b7148                   mov       esi, dword ptr [ecx + 0x48]
00868bf1 8d1c06                   lea       ebx, [esi + eax]
00868bf4 331c06                   xor       ebx, dword ptr [esi + eax]
00868bf7 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
00868bfa 33da                     xor       ebx, edx
00868bfc 3bf3                     cmp       esi, ebx
00868bfe 7410                     je        0x868c10
00868c00 8b4508                   mov       eax, dword ptr [ebp + 8]
00868c03 6a40                     push      0x40
00868c05 0540070000               add       eax, 0x740
00868c0a 50                       push      eax
00868c0b e8a0e42a00               call      0xb170b0
00868c10 56                       push      esi
00868c11 68e0dde100               push      0xe1dde0
00868c16 57                       push      edi
00868c17 e8d3963900               call      0xc022ef
00868c1c 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868c22 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868c28 83c40c                   add       esp, 0xc
00868c2b 8b7508                   mov       esi, dword ptr [ebp + 8]
00868c2e 8b8648070000             mov       eax, dword ptr [esi + 0x748]
00868c34 8b9e4c070000             mov       ebx, dword ptr [esi + 0x74c]
00868c3a 81c648070000             add       esi, 0x748
00868c40 33c2                     xor       eax, edx
00868c42 2bc6                     sub       eax, esi
00868c44 3bc3                     cmp       eax, ebx
00868c46 7414                     je        0x868c5c
00868c48 6a3f                     push      0x3f
00868c4a 56                       push      esi
00868c4b e860e42a00               call      0xb170b0
00868c50 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868c56 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868c5c 8b4604                   mov       eax, dword ptr [esi + 4]
00868c5f 8b5944                   mov       ebx, dword ptr [ecx + 0x44]
00868c62 c1e002                   shl       eax, 2
00868c65 8d3403                   lea       esi, [ebx + eax]
00868c68 333403                   xor       esi, dword ptr [ebx + eax]
00868c6b 33f2                     xor       esi, edx
00868c6d 8975f0                   mov       dword ptr [ebp - 0x10], esi
00868c70 8b7148                   mov       esi, dword ptr [ecx + 0x48]
00868c73 8d1c06                   lea       ebx, [esi + eax]
00868c76 331c06                   xor       ebx, dword ptr [esi + eax]
00868c79 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
00868c7c 33da                     xor       ebx, edx
00868c7e 3bf3                     cmp       esi, ebx
00868c80 741c                     je        0x868c9e
00868c82 8b4508                   mov       eax, dword ptr [ebp + 8]
00868c85 6a40                     push      0x40
00868c87 0548070000               add       eax, 0x748
00868c8c 50                       push      eax
00868c8d e81ee42a00               call      0xb170b0
00868c92 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868c98 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868c9e 85f6                     test      esi, esi
00868ca0 0f8482000000             je        0x868d28
00868ca6 8b7508                   mov       esi, dword ptr [ebp + 8]
00868ca9 8b8648070000             mov       eax, dword ptr [esi + 0x748]
00868caf 8b9e4c070000             mov       ebx, dword ptr [esi + 0x74c]
00868cb5 81c648070000             add       esi, 0x748
00868cbb 33c2                     xor       eax, edx
00868cbd 2bc6                     sub       eax, esi
00868cbf 3bc3                     cmp       eax, ebx
00868cc1 7414                     je        0x868cd7
00868cc3 6a3f                     push      0x3f
00868cc5 56                       push      esi
00868cc6 e8e5e32a00               call      0xb170b0
00868ccb 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868cd1 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868cd7 8b4604                   mov       eax, dword ptr [esi + 4]
00868cda 8b5944                   mov       ebx, dword ptr [ecx + 0x44]
00868cdd c1e002                   shl       eax, 2
00868ce0 8d3403                   lea       esi, [ebx + eax]
00868ce3 333403                   xor       esi, dword ptr [ebx + eax]
00868ce6 33f2                     xor       esi, edx
00868ce8 8975f0                   mov       dword ptr [ebp - 0x10], esi
00868ceb 8b7148                   mov       esi, dword ptr [ecx + 0x48]
00868cee 8d1c06                   lea       ebx, [esi + eax]
00868cf1 331c06                   xor       ebx, dword ptr [esi + eax]
00868cf4 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
00868cf7 33da                     xor       ebx, edx
00868cf9 3bf3                     cmp       esi, ebx
00868cfb 7410                     je        0x868d0d
00868cfd 8b4508                   mov       eax, dword ptr [ebp + 8]
00868d00 6a40                     push      0x40
00868d02 0548070000               add       eax, 0x748
00868d07 50                       push      eax
00868d08 e8a3e32a00               call      0xb170b0
00868d0d 56                       push      esi
00868d0e 68b4dde100               push      0xe1ddb4
00868d13 57                       push      edi
00868d14 e8d6953900               call      0xc022ef
00868d19 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868d1f 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868d25 83c40c                   add       esp, 0xc
00868d28 8b7508                   mov       esi, dword ptr [ebp + 8]
00868d2b 8b86b4060000             mov       eax, dword ptr [esi + 0x6b4]
00868d31 8b9eb8060000             mov       ebx, dword ptr [esi + 0x6b8]
00868d37 81c6b4060000             add       esi, 0x6b4
00868d3d 33c2                     xor       eax, edx
00868d3f 2bc6                     sub       eax, esi
00868d41 3bc3                     cmp       eax, ebx
00868d43 7414                     je        0x868d59
00868d45 6a3f                     push      0x3f
00868d47 56                       push      esi
00868d48 e863e32a00               call      0xb170b0
00868d4d 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868d53 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868d59 8b4604                   mov       eax, dword ptr [esi + 4]
00868d5c 8b5944                   mov       ebx, dword ptr [ecx + 0x44]
00868d5f c1e002                   shl       eax, 2
00868d62 8d3403                   lea       esi, [ebx + eax]
00868d65 333403                   xor       esi, dword ptr [ebx + eax]
00868d68 33f2                     xor       esi, edx
00868d6a 8975f0                   mov       dword ptr [ebp - 0x10], esi
00868d6d 8b7148                   mov       esi, dword ptr [ecx + 0x48]
00868d70 8d1c06                   lea       ebx, [esi + eax]
00868d73 331c06                   xor       ebx, dword ptr [esi + eax]
00868d76 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
00868d79 33da                     xor       ebx, edx
00868d7b 3bf3                     cmp       esi, ebx
00868d7d 741c                     je        0x868d9b
00868d7f 8b4508                   mov       eax, dword ptr [ebp + 8]
00868d82 6a40                     push      0x40
00868d84 05b4060000               add       eax, 0x6b4
00868d89 50                       push      eax
00868d8a e821e32a00               call      0xb170b0
00868d8f 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00868d95 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00868d9b 85f6                     test      esi, esi
00868d9d 0f8482000000             je        0x868e25
00868da3 8b7508                   mov       esi, dword ptr [ebp + 8]
00868da6 8b86b4060000             mov       eax, dword ptr [esi + 0x6b4]
00868dac 8b9eb8060000             mov       ebx, dword ptr [esi + 0x6b8]
00868db2 81c6b4060000             add       esi, 0x6b4
00868db8 33c2                     xor       eax, edx
00868dba 2bc6                     sub       eax, esi
00868dbc 3bc3                     cmp       eax, ebx
00868dbe 7414                     je        0x868dd4
