00501c2d 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501c30 68e0baca00               push      0xcabae0
00501c35 81c148070000             add       ecx, 0x748
00501c3b e8b0145500               call      0xa530f0
00501c40 50                       push      eax
00501c41 e8a5f16f00               call      0xc00deb
00501c46 83c408                   add       esp, 8
00501c49 85c0                     test      eax, eax
00501c4b 0f8482000000             je        0x501cd3
00501c51 68e0020000               push      0x2e0
00501c56 e8f51ff0ff               call      0x403c50
00501c5b 8bf8                     mov       edi, eax
00501c5d 83c404                   add       esp, 4
00501c60 897de8                   mov       dword ptr [ebp - 0x18], edi
00501c63 85ff                     test      edi, edi
00501c65 c745fc16000000           mov       dword ptr [ebp - 4], 0x16
00501c6c 7432                     je        0x501ca0
00501c6e 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
00501c75 7208                     jb        0x501c7f
00501c77 8bb348020000             mov       esi, dword ptr [ebx + 0x248]
00501c7d eb06                     jmp       0x501c85
00501c7f 8db348020000             lea       esi, [ebx + 0x248]
00501c85 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501c88 6a00                     push      0
00501c8a 81c148070000             add       ecx, 0x748
00501c90 e85b145500               call      0xa530f0
00501c95 50                       push      eax
00501c96 56                       push      esi
00501c97 8bcf                     mov       ecx, edi
00501c99 e8621cfaff               call      0x4a3900
00501c9e eb02                     jmp       0x501ca2
00501ca0 33c0                     xor       eax, eax
00501ca2 85c0                     test      eax, eax
00501ca4 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00501cab 898350010000             mov       dword ptr [ebx + 0x150], eax
00501cb1 7420                     je        0x501cd3
00501cb3 c780cc0200000b000000     mov       dword ptr [eax + 0x2cc], 0xb
00501cbd c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
00501cc7 8b8b50010000             mov       ecx, dword ptr [ebx + 0x150]
00501ccd 53                       push      ebx
00501cce e84db35200               call      0xa2d020
