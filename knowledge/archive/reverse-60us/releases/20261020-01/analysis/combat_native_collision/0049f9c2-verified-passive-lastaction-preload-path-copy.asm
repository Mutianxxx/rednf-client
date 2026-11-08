0049f9c2 8d5f5c                   lea       ebx, [edi + 0x5c]
0049f9c5 68e0baca00               push      0xcabae0
0049f9ca 8bcb                     mov       ecx, ebx
0049f9cc e81f375b00               call      0xa530f0
0049f9d1 50                       push      eax
0049f9d2 e814147600               call      0xc00deb
0049f9d7 83c408                   add       esp, 8
0049f9da 85c0                     test      eax, eax
0049f9dc 0f8491000000             je        0x49fa73
0049f9e2 68e0020000               push      0x2e0
0049f9e7 e86442f6ff               call      0x403c50
0049f9ec 83c404                   add       esp, 4
0049f9ef 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f9f2 85c0                     test      eax, eax
0049f9f4 c745fc04000000           mov       dword ptr [ebp - 4], 4
0049f9fb 7426                     je        0x49fa23
0049f9fd 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049fa03 e8e8365b00               call      0xa530f0
0049fa08 6a00                     push      0
0049fa0a 8bcb                     mov       ecx, ebx
0049fa0c 894508                   mov       dword ptr [ebp + 8], eax
0049fa0f e8dc365b00               call      0xa530f0
0049fa14 8b5508                   mov       edx, dword ptr [ebp + 8]
0049fa17 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049fa1a 50                       push      eax
0049fa1b 52                       push      edx
0049fa1c e8df3e0000               call      0x4a3900
0049fa21 eb02                     jmp       0x49fa25
0049fa23 33c0                     xor       eax, eax
0049fa25 56                       push      esi
0049fa26 8bc8                     mov       ecx, eax
0049fa28 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fa2f 898650010000             mov       dword ptr [esi + 0x150], eax
0049fa35 e8e6d55800               call      0xa2d020
0049fa3a 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0049fa40 8bcb                     mov       ecx, ebx
0049fa42 c780cc0200000b000000     mov       dword ptr [eax + 0x2cc], 0xb
0049fa4c c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
0049fa56 e895365b00               call      0xa530f0
0049fa5b 8bd8                     mov       ebx, eax
0049fa5d 53                       push      ebx
0049fa5e e86a037600               call      0xbffdcd
0049fa63 83c404                   add       esp, 4
0049fa66 50                       push      eax
0049fa67 53                       push      ebx
0049fa68 8d8ef4070000             lea       ecx, [esi + 0x7f4]
0049fa6e e80d34f6ff               call      0x402e80
