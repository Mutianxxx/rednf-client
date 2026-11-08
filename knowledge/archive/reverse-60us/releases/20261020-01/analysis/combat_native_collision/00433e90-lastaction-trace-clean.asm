00433e90 0000                     add       byte ptr [eax], al
00433e92 3bda                     cmp       ebx, edx
00433e94 743e                     je        0x433ed4
00433e96 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433e99 8b5b04                   mov       ebx, dword ptr [ebx + 4]
00433e9c a1d8012101               mov       eax, dword ptr [0x12101d8]
00433ea1 8b4044                   mov       eax, dword ptr [eax + 0x44]
00433ea4 8d0c88                   lea       ecx, [eax + ecx*4]
00433ea7 8d0498                   lea       eax, [eax + ebx*4]
00433eaa 8bd8                     mov       ebx, eax
00433eac 33d9                     xor       ebx, ecx
00433eae 3319                     xor       ebx, dword ptr [ecx]
00433eb0 8918                     mov       dword ptr [eax], ebx
00433eb2 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433eb5 a1d8012101               mov       eax, dword ptr [0x12101d8]
00433eba 8b4048                   mov       eax, dword ptr [eax + 0x48]
00433ebd 8b9650010000             mov       edx, dword ptr [esi + 0x150]
00433ec3 8b1c88                   mov       ebx, dword ptr [eax + ecx*4]
00433ec6 8d0c88                   lea       ecx, [eax + ecx*4]
00433ec9 8d0490                   lea       eax, [eax + edx*4]
00433ecc 8bd0                     mov       edx, eax
00433ece 33d1                     xor       edx, ecx
00433ed0 33d3                     xor       edx, ebx
00433ed2 8910                     mov       dword ptr [eax], edx
00433ed4 8a8754010000             mov       al, byte ptr [edi + 0x154]
00433eda 888654010000             mov       byte ptr [esi + 0x154], al
00433ee0 8b8f58010000             mov       ecx, dword ptr [edi + 0x158]
00433ee6 8d975c010000             lea       edx, [edi + 0x15c]
00433eec 898e58010000             mov       dword ptr [esi + 0x158], ecx
00433ef2 52                       push      edx
00433ef3 8d8e5c010000             lea       ecx, [esi + 0x15c]
00433ef9 e892f56100               call      0xa53490
00433efe 8a8760010000             mov       al, byte ptr [edi + 0x160]
00433f04 8d9764010000             lea       edx, [edi + 0x164]
00433f0a 8d9e64010000             lea       ebx, [esi + 0x164]
00433f10 3bda                     cmp       ebx, edx
00433f12 888660010000             mov       byte ptr [esi + 0x160], al
00433f18 743f                     je        0x433f59
00433f1a 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00433f20 8b4144                   mov       eax, dword ptr [ecx + 0x44]
00433f23 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433f26 8b5b04                   mov       ebx, dword ptr [ebx + 4]
00433f29 8d0c88                   lea       ecx, [eax + ecx*4]
00433f2c 8d0498                   lea       eax, [eax + ebx*4]
00433f2f 8bd8                     mov       ebx, eax
00433f31 33d9                     xor       ebx, ecx
00433f33 3319                     xor       ebx, dword ptr [ecx]
00433f35 8918                     mov       dword ptr [eax], ebx
00433f37 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433f3a a1d8012101               mov       eax, dword ptr [0x12101d8]
00433f3f 8b4048                   mov       eax, dword ptr [eax + 0x48]
00433f42 8b9668010000             mov       edx, dword ptr [esi + 0x168]
00433f48 8b1c88                   mov       ebx, dword ptr [eax + ecx*4]
00433f4b 8d0c88                   lea       ecx, [eax + ecx*4]
00433f4e 8d0490                   lea       eax, [eax + edx*4]
00433f51 8bd0                     mov       edx, eax
00433f53 33d1                     xor       edx, ecx
00433f55 33d3                     xor       edx, ebx
00433f57 8910                     mov       dword ptr [eax], edx
00433f59 8b876c010000             mov       eax, dword ptr [edi + 0x16c]
00433f5f 89866c010000             mov       dword ptr [esi + 0x16c], eax
00433f65 8b8f70010000             mov       ecx, dword ptr [edi + 0x170]
00433f6b 898e70010000             mov       dword ptr [esi + 0x170], ecx
00433f71 8a9774010000             mov       dl, byte ptr [edi + 0x174]
00433f77 889674010000             mov       byte ptr [esi + 0x174], dl
00433f7d 8b8778010000             mov       eax, dword ptr [edi + 0x178]
00433f83 898678010000             mov       dword ptr [esi + 0x178], eax
00433f89 8b8f7c010000             mov       ecx, dword ptr [edi + 0x17c]
00433f8f 898e7c010000             mov       dword ptr [esi + 0x17c], ecx
00433f95 8b9780010000             mov       edx, dword ptr [edi + 0x180]
00433f9b 899680010000             mov       dword ptr [esi + 0x180], edx
00433fa1 8d9784010000             lea       edx, [edi + 0x184]
00433fa7 8d9e84010000             lea       ebx, [esi + 0x184]
00433fad 3bda                     cmp       ebx, edx
00433faf 743b                     je        0x433fec
00433fb1 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433fb4 a1d8012101               mov       eax, dword ptr [0x12101d8]
00433fb9 8b4044                   mov       eax, dword ptr [eax + 0x44]
00433fbc 8b5b04                   mov       ebx, dword ptr [ebx + 4]
00433fbf 8d0c88                   lea       ecx, [eax + ecx*4]
00433fc2 8d0498                   lea       eax, [eax + ebx*4]
00433fc5 8b19                     mov       ebx, dword ptr [ecx]
00433fc7 33d8                     xor       ebx, eax
00433fc9 33d9                     xor       ebx, ecx
00433fcb 8918                     mov       dword ptr [eax], ebx
00433fcd 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433fd0 a1d8012101               mov       eax, dword ptr [0x12101d8]
00433fd5 8b4048                   mov       eax, dword ptr [eax + 0x48]
00433fd8 8b9688010000             mov       edx, dword ptr [esi + 0x188]
00433fde 8d0c88                   lea       ecx, [eax + ecx*4]
00433fe1 8d0490                   lea       eax, [eax + edx*4]
00433fe4 8b11                     mov       edx, dword ptr [ecx]
00433fe6 33d0                     xor       edx, eax
00433fe8 33d1                     xor       edx, ecx
00433fea 8910                     mov       dword ptr [eax], edx
00433fec 8d978c010000             lea       edx, [edi + 0x18c]
00433ff2 8d9e8c010000             lea       ebx, [esi + 0x18c]
00433ff8 3bda                     cmp       ebx, edx
00433ffa 743e                     je        0x43403a
00433ffc 8b4a04                   mov       ecx, dword ptr [edx + 4]
00433fff 8b5b04                   mov       ebx, dword ptr [ebx + 4]
00434002 a1d8012101               mov       eax, dword ptr [0x12101d8]
00434007 8b4044                   mov       eax, dword ptr [eax + 0x44]
0043400a 8d0c88                   lea       ecx, [eax + ecx*4]
0043400d 8d0498                   lea       eax, [eax + ebx*4]
