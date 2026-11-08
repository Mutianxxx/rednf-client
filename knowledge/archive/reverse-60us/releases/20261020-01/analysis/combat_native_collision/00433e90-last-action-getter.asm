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
00433efe 8a                       .byte     0x8a
00433eff 87                       .byte     0x87
