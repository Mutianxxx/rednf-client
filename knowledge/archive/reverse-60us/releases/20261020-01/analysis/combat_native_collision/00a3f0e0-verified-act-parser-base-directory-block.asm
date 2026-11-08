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
