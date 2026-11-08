004a3050 008b1c888d0c             add       byte ptr [ebx + 0xc8d881c], cl
004a3056 888d04908bd0             mov       byte ptr [ebp - 0x2f746ffc], cl
004a305c 33d1                     xor       edx, ecx
004a305e 33d3                     xor       edx, ebx
004a3060 8910                     mov       dword ptr [eax], edx
004a3062 8d9748010000             lea       edx, [edi + 0x148]
004a3068 8d9e48010000             lea       ebx, [esi + 0x148]
004a306e 3bda                     cmp       ebx, edx
004a3070 743e                     je        0x4a30b0
004a3072 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a3075 8b5b04                   mov       ebx, dword ptr [ebx + 4]
004a3078 a1d8012101               mov       eax, dword ptr [0x12101d8]
004a307d 8b4044                   mov       eax, dword ptr [eax + 0x44]
004a3080 8d0c88                   lea       ecx, [eax + ecx*4]
004a3083 8d0498                   lea       eax, [eax + ebx*4]
004a3086 8bd8                     mov       ebx, eax
004a3088 33d9                     xor       ebx, ecx
004a308a 3319                     xor       ebx, dword ptr [ecx]
004a308c 8918                     mov       dword ptr [eax], ebx
004a308e 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a3091 a1d8012101               mov       eax, dword ptr [0x12101d8]
004a3096 8b4048                   mov       eax, dword ptr [eax + 0x48]
004a3099 8b964c010000             mov       edx, dword ptr [esi + 0x14c]
004a309f 8b1c88                   mov       ebx, dword ptr [eax + ecx*4]
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
004a312c 8a877c010000             mov       al, byte ptr [edi + 0x17c]
004a3132 8d9780010000             lea       edx, [edi + 0x180]
004a3138 8d9e80010000             lea       ebx, [esi + 0x180]
004a313e 3bda                     cmp       ebx, edx
004a3140 88867c010000             mov       byte ptr [esi + 0x17c], al
004a3146 743f                     je        0x4a3187
004a3148 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a314e 8b4144                   mov       eax, dword ptr [ecx + 0x44]
004a3151 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a3154 8b5b04                   mov       ebx, dword ptr [ebx + 4]
004a3157 8d0c88                   lea       ecx, [eax + ecx*4]
004a315a 8d0498                   lea       eax, [eax + ebx*4]
004a315d 8bd8                     mov       ebx, eax
004a315f 33d9                     xor       ebx, ecx
004a3161 3319                     xor       ebx, dword ptr [ecx]
004a3163 8918                     mov       dword ptr [eax], ebx
004a3165 8b4a04                   mov       ecx, dword ptr [edx + 4]
004a3168 a1d8012101               mov       eax, dword ptr [0x12101d8]
004a316d 8b4048                   mov       eax, dword ptr [eax + 0x48]
