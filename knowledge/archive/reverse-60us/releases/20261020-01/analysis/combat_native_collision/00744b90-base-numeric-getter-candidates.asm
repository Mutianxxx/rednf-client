00744b90 81c130120000             add       ecx, 0x1230
00744b96 e9c5d4cbff               jmp       0x402060
00744b9b cc                       int3      
00744b9c cc                       int3      
00744b9d cc                       int3      
00744b9e cc                       int3      
00744b9f cc                       int3      
00744ba0 55                       push      ebp
00744ba1 8bec                     mov       ebp, esp
00744ba3 51                       push      ecx
00744ba4 8b01                     mov       eax, dword ptr [ecx]
00744ba6 56                       push      esi
00744ba7 6a03                     push      3
00744ba9 ff9044030000             call      dword ptr [eax + 0x344]
00744baf 8bf0                     mov       esi, eax
00744bb1 8d4e08                   lea       ecx, [esi + 8]
00744bb4 e8a7d4cbff               call      0x402060
00744bb9 8945fc                   mov       dword ptr [ebp - 4], eax
00744bbc db45fc                   fild      dword ptr [ebp - 4]
00744bbf 8d4e10                   lea       ecx, [esi + 0x10]
00744bc2 d95dfc                   fstp      dword ptr [ebp - 4]
00744bc5 e8e6e7ceff               call      0x4333b0
00744bca d84dfc                   fmul      dword ptr [ebp - 4]
00744bcd e872c94b00               call      0xc01544
00744bd2 5e                       pop       esi
00744bd3 8be5                     mov       esp, ebp
00744bd5 5d                       pop       ebp
00744bd6 c3                       ret       
00744bd7 cc                       int3      
00744bd8 cc                       int3      
00744bd9 cc                       int3      
00744bda cc                       int3      
00744bdb cc                       int3      
00744bdc cc                       int3      
00744bdd cc                       int3      
00744bde cc                       int3      
00744bdf cc                       int3      
