004a30a0 1c88                     sbb       al, 0x88
004a30a2 8d0c88                   lea       ecx, [eax + ecx*4]
004a30a5 8d0490                   lea       eax, [eax + edx*4]
004a30a8 8bd0                     mov       edx, eax
004a30aa 33d1                     xor       edx, ecx
004a30ac 33d3                     xor       edx, ebx
004a30ae 8910                     mov       dword ptr [eax], edx
004a30b0 8d9750010000             lea       edx, [edi + 0x150]
004a30b6 8d9e50010000             lea       ebx, [esi + 0x150]
004a30bc 3bda                     cmp       ebx, edx
004a30be 743e                     je        0x4a30fe
004a30c0 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a30c3 8b5b04                   mov       ebx, dword ptr [ebx + 4]
004a30c6 a1d8012101               mov       eax, dword ptr [0x12101d8]
004a30cb 8b4044                   mov       eax, dword ptr [eax + 0x44]
004a30ce 8d0c88                   lea       ecx, [eax + ecx*4]
004a30d1 8d0498                   lea       eax, [eax + ebx*4]
004a30d4 8bd8                     mov       ebx, eax
004a30d6 33d9                     xor       ebx, ecx
004a30d8 3319                     xor       ebx, dword ptr [ecx]
004a30da 8918                     mov       dword ptr [eax], ebx
004a30dc 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a30df a1d8012101               mov       eax, dword ptr [0x12101d8]
004a30e4 8b4048                   mov       eax, dword ptr [eax + 0x48]
004a30e7 8b9654010000             mov       edx, dword ptr [esi + 0x154]
004a30ed 8b1c88                   mov       ebx, dword ptr [eax + ecx*4]
004a30f0 8d0c88                   lea       ecx, [eax + ecx*4]
004a30f3 8d0490                   lea       eax, [eax + edx*4]
004a30f6 8bd0                     mov       edx, eax
004a30f8 33d1                     xor       edx, ecx
004a30fa 33d3                     xor       edx, ebx
004a30fc 8910                     mov       dword ptr [eax], edx
004a30fe 6aff                     push      -1
004a3100 6a00                     push      0
004a3102 8d8758010000             lea       eax, [edi + 0x158]
004a3108 50                       push      eax
004a3109 8d8e58010000             lea       ecx, [esi + 0x158]
004a310f e84cfcf5ff               call      0x402d60
004a3114 8b8f74010000             mov       ecx, dword ptr [edi + 0x174]
004a311a 898e74010000             mov       dword ptr [esi + 0x174], ecx
004a3120 8b9778010000             mov       edx, dword ptr [edi + 0x178]
004a3126 899678010000             mov       dword ptr [esi + 0x178], edx
004a312c 8a                       .byte     0x8a
004a312d 87                       .byte     0x87
004a312e 7c01                     jl        0x4a3131
