00a3f0e0 55                       push      ebp
00a3f0e1 8bec                     mov       ebp, esp
00a3f0e3 64a100000000             mov       eax, dword ptr fs:[0]
00a3f0e9 6aff                     push      -1
00a3f0eb 6830f5c800               push      0xc8f530
00a3f0f0 50                       push      eax
00a3f0f1 b82c130000               mov       eax, 0x132c
00a3f0f6 64892500000000           mov       dword ptr fs:[0], esp
00a3f0fd e8ce1d1c00               call      0xc00ed0
00a3f102 53                       push      ebx
00a3f103 56                       push      esi
00a3f104 57                       push      edi
00a3f105 33ff                     xor       edi, edi
00a3f107 bb07000000               mov       ebx, 7
00a3f10c 899decfcffff             mov       dword ptr [ebp - 0x314], ebx
00a3f112 89bde8fcffff             mov       dword ptr [ebp - 0x318], edi
00a3f118 6689bdd8fcffff           mov       word ptr [ebp - 0x328], di
00a3f11f 897dfc                   mov       dword ptr [ebp - 4], edi
00a3f122 89bd54fdffff             mov       dword ptr [ebp - 0x2ac], edi
00a3f128 89bd58fdffff             mov       dword ptr [ebp - 0x2a8], edi
00a3f12e 89bd5cfdffff             mov       dword ptr [ebp - 0x2a4], edi
00a3f134 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00a3f137 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00a3f13a 50                       push      eax
00a3f13b 51                       push      ecx
00a3f13c 8d95d4fcffff             lea       edx, [ebp - 0x32c]
00a3f142 68f8b8ca00               push      0xcab8f8
00a3f147 52                       push      edx
00a3f148 be01000000               mov       esi, 1
00a3f14d c645fc01                 mov       byte ptr [ebp - 4], 1
00a3f151 e83a14dfff               call      0x830590
00a3f156 83c410                   add       esp, 0x10
00a3f159 899d58ffffff             mov       dword ptr [ebp - 0xa8], ebx
00a3f15f 89bd54ffffff             mov       dword ptr [ebp - 0xac], edi
00a3f165 6689bd44ffffff           mov       word ptr [ebp - 0xbc], di
00a3f16c 895dac                   mov       dword ptr [ebp - 0x54], ebx
00a3f16f 897da8                   mov       dword ptr [ebp - 0x58], edi
00a3f172 66897d98                 mov       word ptr [ebp - 0x68], di
00a3f176 895dcc                   mov       dword ptr [ebp - 0x34], ebx
00a3f179 897dc8                   mov       dword ptr [ebp - 0x38], edi
00a3f17c 66897db8                 mov       word ptr [ebp - 0x48], di
00a3f180 68e0baca00               push      0xcabae0
00a3f185 8d4db0                   lea       ecx, [ebp - 0x50]
00a3f188 c645fc04                 mov       byte ptr [ebp - 4], 4
00a3f18c 897db0                   mov       dword ptr [ebp - 0x50], edi
00a3f18f e80c470100               call      0xa538a0
00a3f194 899d3cfbffff             mov       dword ptr [ebp - 0x4c4], ebx
00a3f19a 89bd38fbffff             mov       dword ptr [ebp - 0x4c8], edi
00a3f1a0 6689bd28fbffff           mov       word ptr [ebp - 0x4d8], di
00a3f1a7 33db                     xor       ebx, ebx
00a3f1a9 895dd4                   mov       dword ptr [ebp - 0x2c], ebx
00a3f1ac 897dd8                   mov       dword ptr [ebp - 0x28], edi
00a3f1af 897ddc                   mov       dword ptr [ebp - 0x24], edi
00a3f1b2 8d8540ffffff             lea       eax, [ebp - 0xc0]
00a3f1b8 56                       push      esi
00a3f1b9 50                       push      eax
00a3f1ba c645fc07                 mov       byte ptr [ebp - 4], 7
00a3f1be e81d16dfff               call      0x8307e0
00a3f1c3 83c408                   add       esp, 8
00a3f1c6 84c0                     test      al, al
00a3f1c8 0f84fd7d0000             je        0xa46fcb
00a3f1ce 8bff                     mov       edi, edi
00a3f1d0 68b492e400               push      0xe492b4
00a3f1d5 e8f30b1c00               call      0xbffdcd
00a3f1da 8b8d54ffffff             mov       ecx, dword ptr [ebp - 0xac]
00a3f1e0 83c404                   add       esp, 4
00a3f1e3 50                       push      eax
00a3f1e4 68b492e400               push      0xe492b4
00a3f1e9 51                       push      ecx
00a3f1ea 57                       push      edi
00a3f1eb 8d8d40ffffff             lea       ecx, [ebp - 0xc0]
00a3f1f1 e8fa4d9cff               call      0x403ff0
00a3f1f6 85c0                     test      eax, eax
00a3f1f8 0f856c090000             jne       0xa3fb6a
00a3f1fe 8d5594                   lea       edx, [ebp - 0x6c]
00a3f201 56                       push      esi
00a3f202 52                       push      edx
00a3f203 e8d815dfff               call      0x8307e0
00a3f208 83c408                   add       esp, 8
00a3f20b 84c0                     test      al, al
00a3f20d 0f84a07d0000             je        0xa46fb3
00a3f213 68a092e400               push      0xe492a0
00a3f218 e8b00b1c00               call      0xbffdcd
00a3f21d 83c404                   add       esp, 4
00a3f220 50                       push      eax
00a3f221 8b45a8                   mov       eax, dword ptr [ebp - 0x58]
00a3f224 68a092e400               push      0xe492a0
00a3f229 50                       push      eax
00a3f22a 57                       push      edi
00a3f22b 8d4d94                   lea       ecx, [ebp - 0x6c]
00a3f22e e8bd4d9cff               call      0x403ff0
00a3f233 85c0                     test      eax, eax
00a3f235 0f84787d0000             je        0xa46fb3
