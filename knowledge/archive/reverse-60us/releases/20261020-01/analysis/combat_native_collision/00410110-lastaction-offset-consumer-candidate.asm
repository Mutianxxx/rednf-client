00410110 55                       push      ebp
00410111 8bec                     mov       ebp, esp
00410113 8b914c010000             mov       edx, dword ptr [ecx + 0x14c]
00410119 0fb64508                 movzx     eax, byte ptr [ebp + 8]
0041011d 56                       push      esi
0041011e 8b35d8012101             mov       esi, dword ptr [0x12101d8]
00410124 8b7644                   mov       esi, dword ptr [esi + 0x44]
00410127 8d1496                   lea       edx, [esi + edx*4]
0041012a 8bf2                     mov       esi, edx
0041012c 3335dc012101             xor       esi, dword ptr [0x12101dc]
00410132 33f0                     xor       esi, eax
00410134 8932                     mov       dword ptr [edx], esi
00410136 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0041013c 8b5248                   mov       edx, dword ptr [edx + 0x48]
0041013f 8b894c010000             mov       ecx, dword ptr [ecx + 0x14c]
00410145 8b35dc012101             mov       esi, dword ptr [0x12101dc]
0041014b 8d0c8a                   lea       ecx, [edx + ecx*4]
0041014e 8bd1                     mov       edx, ecx
00410150 33d6                     xor       edx, esi
00410152 33d0                     xor       edx, eax
00410154 8911                     mov       dword ptr [ecx], edx
00410156 5e                       pop       esi
00410157 5d                       pop       ebp
00410158 c20400                   ret       4
0041015b cc                       int3      
0041015c cc                       int3      
0041015d cc                       int3      
0041015e cc                       int3      
0041015f cc                       int3      
00410160 55                       push      ebp
00410161 8bec                     mov       ebp, esp
00410163 56                       push      esi
00410164 8bf1                     mov       esi, ecx
00410166 8d4e20                   lea       ecx, [esi + 0x20]
00410169 e8f21effff               call      0x402060
0041016e 85c0                     test      eax, eax
00410170 7425                     je        0x410197
00410172 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00410178 8b5144                   mov       edx, dword ptr [ecx + 0x44]
0041017b 8b4634                   mov       eax, dword ptr [esi + 0x34]
0041017e 8b                       .byte     0x8b
0041017f 0d                       .byte     0x0d
