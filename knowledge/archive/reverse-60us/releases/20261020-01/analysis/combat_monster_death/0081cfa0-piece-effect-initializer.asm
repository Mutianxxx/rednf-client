0081cfa0 55                       push      ebp
0081cfa1 8bec                     mov       ebp, esp
0081cfa3 64a100000000             mov       eax, dword ptr fs:[0]
0081cfa9 6aff                     push      -1
0081cfab 6847c9c700               push      0xc7c947
0081cfb0 50                       push      eax
0081cfb1 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0081cfb4 3d30750000               cmp       eax, 0x7530
0081cfb9 64892500000000           mov       dword ptr fs:[0], esp
0081cfc0 53                       push      ebx
0081cfc1 56                       push      esi
0081cfc2 8bf1                     mov       esi, ecx
0081cfc4 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0081cfc7 57                       push      edi
0081cfc8 898efc010000             mov       dword ptr [esi + 0x1fc], ecx
0081cfce 7e73                     jle       0x81d043
0081cfd0 3d10980200               cmp       eax, 0x29810
0081cfd5 7c05                     jl        0x81cfdc
0081cfd7 b810980200               mov       eax, 0x29810
0081cfdc 8b5514                   mov       edx, dword ptr [ebp + 0x14]
0081cfdf 898600020000             mov       dword ptr [esi + 0x200], eax
0081cfe5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0081cfe8 898604020000             mov       dword ptr [esi + 0x204], eax
0081cfee 899608020000             mov       dword ptr [esi + 0x208], edx
0081cff4 c6860c02000000           mov       byte ptr [esi + 0x20c], 0
0081cffb a148280001               mov       eax, dword ptr [0x1002848]
0081d000 8b80a8190000             mov       eax, dword ptr [eax + 0x19a8]
0081d006 bb02000000               mov       ebx, 2
0081d00b 3bc3                     cmp       eax, ebx
0081d00d 68b4010000               push      0x1b4
0081d012 0f85f2000000             jne       0x81d10a
0081d018 83f901                   cmp       ecx, 1
0081d01b 7568                     jne       0x81d085
0081d01d e82e6cbeff               call      0x403c50
0081d022 83c404                   add       esp, 4
0081d025 894508                   mov       dword ptr [ebp + 8], eax
0081d028 85c0                     test      eax, eax
0081d02a c745fc00000000           mov       dword ptr [ebp - 4], 0
0081d031 7417                     je        0x81d04a
0081d033 6a00                     push      0
0081d035 6828b2e000               push      0xe0b228
0081d03a 8bc8                     mov       ecx, eax
0081d03c e8df62c3ff               call      0x453320
0081d041 eb09                     jmp       0x81d04c
0081d043 b830750000               mov       eax, 0x7530
0081d048 eb92                     jmp       0x81cfdc
0081d04a 33c0                     xor       eax, eax
0081d04c 83cbff                   or        ebx, 0xffffffff
0081d04f 8dbe14020000             lea       edi, [esi + 0x214]
0081d055 68b4010000               push      0x1b4
0081d05a 895dfc                   mov       dword ptr [ebp - 4], ebx
0081d05d 8907                     mov       dword ptr [edi], eax
0081d05f e8ec6bbeff               call      0x403c50
0081d064 83c404                   add       esp, 4
0081d067 894508                   mov       dword ptr [ebp + 8], eax
0081d06a 85c0                     test      eax, eax
0081d06c c745fc01000000           mov       dword ptr [ebp - 4], 1
0081d073 746d                     je        0x81d0e2
0081d075 6a00                     push      0
0081d077 68b8b1e000               push      0xe0b1b8
0081d07c 8bc8                     mov       ecx, eax
0081d07e e89d62c3ff               call      0x453320
0081d083 eb5f                     jmp       0x81d0e4
0081d085 e8c66bbeff               call      0x403c50
0081d08a 83c404                   add       esp, 4
0081d08d 894508                   mov       dword ptr [ebp + 8], eax
0081d090 85c0                     test      eax, eax
0081d092 895dfc                   mov       dword ptr [ebp - 4], ebx
0081d095 7410                     je        0x81d0a7
0081d097 6a00                     push      0
0081d099 6848b1e000               push      0xe0b148
0081d09e 8bc8                     mov       ecx, eax
0081d0a0 e87b62c3ff               call      0x453320
0081d0a5 eb02                     jmp       0x81d0a9
0081d0a7 33c0                     xor       eax, eax
0081d0a9 83cbff                   or        ebx, 0xffffffff
0081d0ac 8dbe14020000             lea       edi, [esi + 0x214]
0081d0b2 68b4010000               push      0x1b4
0081d0b7 895dfc                   mov       dword ptr [ebp - 4], ebx
0081d0ba 8907                     mov       dword ptr [edi], eax
0081d0bc e88f6bbeff               call      0x403c50
0081d0c1 83c404                   add       esp, 4
0081d0c4 894508                   mov       dword ptr [ebp + 8], eax
0081d0c7 85c0                     test      eax, eax
0081d0c9 c745fc03000000           mov       dword ptr [ebp - 4], 3
0081d0d0 7410                     je        0x81d0e2
0081d0d2 6a00                     push      0
0081d0d4 68d8b0e000               push      0xe0b0d8
0081d0d9 8bc8                     mov       ecx, eax
0081d0db e84062c3ff               call      0x453320
0081d0e0 eb02                     jmp       0x81d0e4
0081d0e2 33c0                     xor       eax, eax
0081d0e4 895dfc                   mov       dword ptr [ebp - 4], ebx
0081d0e7 898618020000             mov       dword ptr [esi + 0x218], eax
0081d0ed bb02000000               mov       ebx, 2
0081d0f2 8b0f                     mov       ecx, dword ptr [edi]
0081d0f4 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
0081d0f7 8b11                     mov       edx, dword ptr [ecx]
0081d0f9 50                       push      eax
0081d0fa ff5268                   call      dword ptr [edx + 0x68]
0081d0fd 83c704                   add       edi, 4
0081d100 4b                       dec       ebx
0081d101 75ef                     jne       0x81d0f2
0081d103 bb02000000               mov       ebx, 2
0081d108 eb35                     jmp       0x81d13f
0081d10a e8416bbeff               call      0x403c50
0081d10f 83c404                   add       esp, 4
0081d112 894508                   mov       dword ptr [ebp + 8], eax
0081d115 85c0                     test      eax, eax
0081d117 c745fc04000000           mov       dword ptr [ebp - 4], 4
0081d11e 7410                     je        0x81d130
0081d120 6a00                     push      0
0081d122 68f071df00               push      0xdf71f0
0081d127 8bc8                     mov       ecx, eax
0081d129 e8f261c3ff               call      0x453320
0081d12e eb02                     jmp       0x81d132
0081d130 33c0                     xor       eax, eax
0081d132 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0081d139 898610020000             mov       dword ptr [esi + 0x210], eax
0081d13f 8b0d48280001             mov       ecx, dword ptr [0x1002848]
0081d145 3999a8190000             cmp       dword ptr [ecx + 0x19a8], ebx
0081d14b 0f858d000000             jne       0x81d1de
0081d151 8dbe14020000             lea       edi, [esi + 0x214]
0081d157 895d08                   mov       dword ptr [ebp + 8], ebx
0081d15a 8d9b00000000             lea       ebx, [ebx]
0081d160 8b0f                     mov       ecx, dword ptr [edi]
0081d162 8b11                     mov       edx, dword ptr [ecx]
0081d164 ff521c                   call      dword ptr [edx + 0x1c]
0081d167 8b0f                     mov       ecx, dword ptr [edi]
0081d169 8b01                     mov       eax, dword ptr [ecx]
0081d16b ff5024                   call      dword ptr [eax + 0x24]
0081d16e 8bd8                     mov       ebx, eax
0081d170 8b8600020000             mov       eax, dword ptr [esi + 0x200]
0081d176 68e0220200               push      0x222e0
0081d17b 2d30750000               sub       eax, 0x7530
0081d180 50                       push      eax
0081d181 680000f041               push      0x41f00000
0081d186 6800002041               push      0x41200000
0081d18b e820c82e00               call      0xb099b0
0081d190 83c410                   add       esp, 0x10
0081d193 e8ac433e00               call      0xc01544
0081d198 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0081d19e 8b5244                   mov       edx, dword ptr [edx + 0x44]
0081d1a1 8b4b08                   mov       ecx, dword ptr [ebx + 8]
0081d1a4 8d0c8a                   lea       ecx, [edx + ecx*4]
0081d1a7 8bd1                     mov       edx, ecx
0081d1a9 3315dc012101             xor       edx, dword ptr [0x12101dc]
0081d1af 83c704                   add       edi, 4
0081d1b2 33d0                     xor       edx, eax
0081d1b4 8911                     mov       dword ptr [ecx], edx
0081d1b6 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0081d1bc 8b5248                   mov       edx, dword ptr [edx + 0x48]
0081d1bf 8b4b08                   mov       ecx, dword ptr [ebx + 8]
0081d1c2 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
0081d1c8 8d0c8a                   lea       ecx, [edx + ecx*4]
0081d1cb 8bd1                     mov       edx, ecx
0081d1cd 33d3                     xor       edx, ebx
0081d1cf 33d0                     xor       edx, eax
0081d1d1 8b4508                   mov       eax, dword ptr [ebp + 8]
0081d1d4 48                       dec       eax
0081d1d5 8911                     mov       dword ptr [ecx], edx
0081d1d7 894508                   mov       dword ptr [ebp + 8], eax
0081d1da 7584                     jne       0x81d160
0081d1dc eb6e                     jmp       0x81d24c
0081d1de 8b8e10020000             mov       ecx, dword ptr [esi + 0x210]
0081d1e4 8b01                     mov       eax, dword ptr [ecx]
0081d1e6 ff501c                   call      dword ptr [eax + 0x1c]
0081d1e9 8b8e10020000             mov       ecx, dword ptr [esi + 0x210]
0081d1ef 8b11                     mov       edx, dword ptr [ecx]
0081d1f1 ff5224                   call      dword ptr [edx + 0x24]
0081d1f4 8bf8                     mov       edi, eax
0081d1f6 8b8600020000             mov       eax, dword ptr [esi + 0x200]
0081d1fc 68e0220200               push      0x222e0
0081d201 2d30750000               sub       eax, 0x7530
0081d206 50                       push      eax
0081d207 6800007042               push      0x42700000
0081d20c 680000a041               push      0x41a00000
0081d211 e89ac72e00               call      0xb099b0
0081d216 d91f                     fstp      dword ptr [edi]
0081d218 8b8600020000             mov       eax, dword ptr [esi + 0x200]
0081d21e 68e0220200               push      0x222e0
0081d223 2d30750000               sub       eax, 0x7530
0081d228 50                       push      eax
0081d229 6800001643               push      0x43160000
0081d22e 6800004842               push      0x42480000
0081d233 e878c72e00               call      0xb099b0
0081d238 83c420                   add       esp, 0x20
0081d23b e804433e00               call      0xc01544
0081d240 8d0c00                   lea       ecx, [eax + eax]
0081d243 894710                   mov       dword ptr [edi + 0x10], eax
0081d246 894f14                   mov       dword ptr [edi + 0x14], ecx
0081d249 894718                   mov       dword ptr [edi + 0x18], eax
0081d24c 8b8600020000             mov       eax, dword ptr [esi + 0x200]
0081d252 68e0220200               push      0x222e0
0081d257 2d30750000               sub       eax, 0x7530
0081d25c 50                       push      eax
0081d25d 680000fa44               push      0x44fa0000
0081d262 6800007a44               push      0x447a0000
0081d267 e844c72e00               call      0xb099b0
0081d26c 83c410                   add       esp, 0x10
0081d26f e8d0423e00               call      0xc01544
0081d274 8b5518                   mov       edx, dword ptr [ebp + 0x18]
0081d277 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0081d27a 5f                       pop       edi
0081d27b 89861c020000             mov       dword ptr [esi + 0x21c], eax
0081d281 899620020000             mov       dword ptr [esi + 0x220], edx
0081d287 5e                       pop       esi
0081d288 64890d00000000           mov       dword ptr fs:[0], ecx
0081d28f 5b                       pop       ebx
0081d290 8be5                     mov       esp, ebp
0081d292 5d                       pop       ebp
0081d293 c21800                   ret       0x18
