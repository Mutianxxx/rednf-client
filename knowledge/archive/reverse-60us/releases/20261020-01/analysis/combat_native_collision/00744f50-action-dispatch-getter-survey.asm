00744f50 55                       push      ebp
00744f51 8bec                     mov       ebp, esp
00744f53 56                       push      esi
00744f54 57                       push      edi
00744f55 8b7d08                   mov       edi, dword ptr [ebp + 8]
00744f58 8db130120000             lea       esi, [ecx + 0x1230]
00744f5e 57                       push      edi
00744f5f 8bce                     mov       ecx, esi
00744f61 e84af6cbff               call      0x4045b0
00744f66 83c708                   add       edi, 8
00744f69 57                       push      edi
00744f6a 8d4e08                   lea       ecx, [esi + 8]
00744f6d e83ef6cbff               call      0x4045b0
00744f72 5f                       pop       edi
00744f73 5e                       pop       esi
00744f74 5d                       pop       ebp
00744f75 c20400                   ret       4
00744f78 cc                       int3      
00744f79 cc                       int3      
00744f7a cc                       int3      
00744f7b cc                       int3      
00744f7c cc                       int3      
00744f7d cc                       int3      
00744f7e cc                       int3      
00744f7f cc                       int3      
00744f80 55                       push      ebp
00744f81 8bec                     mov       ebp, esp
00744f83 8b9108130000             mov       edx, dword ptr [ecx + 0x1308]
00744f89 85d2                     test      edx, edx
00744f8b 7421                     je        0x744fae
00744f8d 8b810c130000             mov       eax, dword ptr [ecx + 0x130c]
00744f93 2bc2                     sub       eax, edx
00744f95 8b5508                   mov       edx, dword ptr [ebp + 8]
00744f98 c1f802                   sar       eax, 2
00744f9b 3bd0                     cmp       edx, eax
00744f9d 730f                     jae       0x744fae
00744f9f 8b8108130000             mov       eax, dword ptr [ecx + 0x1308]
00744fa5 8d0490                   lea       eax, [eax + edx*4]
00744fa8 8b00                     mov       eax, dword ptr [eax]
00744faa 5d                       pop       ebp
00744fab c20400                   ret       4
00744fae 33c0                     xor       eax, eax
00744fb0 5d                       pop       ebp
00744fb1 c20400                   ret       4
00744fb4 cc                       int3      
00744fb5 cc                       int3      
00744fb6 cc                       int3      
00744fb7 cc                       int3      
00744fb8 cc                       int3      
00744fb9 cc                       int3      
00744fba cc                       int3      
00744fbb cc                       int3      
00744fbc cc                       int3      
00744fbd cc                       int3      
00744fbe cc                       int3      
00744fbf cc                       int3      
00744fc0 55                       push      ebp
00744fc1 8bec                     mov       ebp, esp
00744fc3 8b9118130000             mov       edx, dword ptr [ecx + 0x1318]
00744fc9 85d2                     test      edx, edx
00744fcb 7421                     je        0x744fee
00744fcd 8b                       .byte     0x8b
00744fce 81                       .byte     0x81
00744fcf 1c                       .byte     0x1c
