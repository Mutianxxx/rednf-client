004a0ab0 8b8e68050000             mov       ecx, dword ptr [esi + 0x568]
004a0ab6 85c9                     test      ecx, ecx
004a0ab8 745f                     je        0x4a0b19
004a0aba 8b866c050000             mov       eax, dword ptr [esi + 0x56c]
004a0ac0 2bc1                     sub       eax, ecx
004a0ac2 c1f802                   sar       eax, 2
004a0ac5 3bf8                     cmp       edi, eax
004a0ac7 7350                     jae       0x4a0b19
004a0ac9 8b16                     mov       edx, dword ptr [esi]
004a0acb 6a00                     push      0
004a0acd 6a00                     push      0
004a0acf 6a00                     push      0
004a0ad1 6a00                     push      0
004a0ad3 8d1cb9                   lea       ebx, [ecx + edi*4]
004a0ad6 6a00                     push      0
004a0ad8 8bce                     mov       ecx, esi
004a0ada ff92c0000000             call      dword ptr [edx + 0xc0]
004a0ae0 50                       push      eax
004a0ae1 8b06                     mov       eax, dword ptr [esi]
004a0ae3 8bce                     mov       ecx, esi
004a0ae5 ff909c000000             call      dword ptr [eax + 0x9c]
004a0aeb 8b16                     mov       edx, dword ptr [esi]
004a0aed 50                       push      eax
004a0aee 8bce                     mov       ecx, esi
004a0af0 ff9298000000             call      dword ptr [edx + 0x98]
004a0af6 50                       push      eax
004a0af7 8b06                     mov       eax, dword ptr [esi]
004a0af9 8bce                     mov       ecx, esi
004a0afb ff9094000000             call      dword ptr [eax + 0x94]
004a0b01 8b0b                     mov       ecx, dword ptr [ebx]
004a0b03 8b9630050000             mov       edx, dword ptr [esi + 0x530]
004a0b09 50                       push      eax
004a0b0a 6a00                     push      0
004a0b0c 51                       push      ecx
004a0b0d 52                       push      edx
004a0b0e e88d930400               call      0x4e9ea0
004a0b13 83c430                   add       esp, 0x30
004a0b16 47                       inc       edi
004a0b17 eb97                     jmp       0x4a0ab0
004a0b19 c686a405000001           mov       byte ptr [esi + 0x5a4], 1
004a0b20 8b8698050000             mov       eax, dword ptr [esi + 0x598]
004a0b26 85c0                     test      eax, eax
004a0b28 7504                     jne       0x4a0b2e
004a0b2a 33db                     xor       ebx, ebx
004a0b2c eb0b                     jmp       0x4a0b39
004a0b2e 8b9e9c050000             mov       ebx, dword ptr [esi + 0x59c]
004a0b34 2bd8                     sub       ebx, eax
004a0b36 c1fb02                   sar       ebx, 2
004a0b39 33ff                     xor       edi, edi
004a0b3b 85db                     test      ebx, ebx
004a0b3d 7e28                     jle       0x4a0b67
004a0b3f 90                       nop       
004a0b40 8b8698050000             mov       eax, dword ptr [esi + 0x598]
004a0b46 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004a0b49 85c9                     test      ecx, ecx
004a0b4b 8d04b8                   lea       eax, [eax + edi*4]
004a0b4e 7c12                     jl        0x4a0b62
004a0b50 83f9ff                   cmp       ecx, -1
004a0b53 740d                     je        0x4a0b62
004a0b55 8b16                     mov       edx, dword ptr [esi]
004a0b57 8bc1                     mov       eax, ecx
004a0b59 50                       push      eax
004a0b5a 8bce                     mov       ecx, esi
004a0b5c ff9210010000             call      dword ptr [edx + 0x110]
004a0b62 47                       inc       edi
004a0b63 3bfb                     cmp       edi, ebx
004a0b65 7cd9                     jl        0x4a0b40
004a0b67 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
004a0b6d 8b4810                   mov       ecx, dword ptr [eax + 0x10]
004a0b70 83c010                   add       eax, 0x10
004a0b73 85c9                     test      ecx, ecx
004a0b75 0f8585000000             jne       0x4a0c00
004a0b7b 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
004a0b81 85c9                     test      ecx, ecx
004a0b83 747b                     je        0x4a0c00
004a0b85 8b869c050000             mov       eax, dword ptr [esi + 0x59c]
004a0b8b 2bc1                     sub       eax, ecx
004a0b8d c1f802                   sar       eax, 2
004a0b90 85c0                     test      eax, eax
004a0b92 766c                     jbe       0x4a0c00
004a0b94 8bc1                     mov       eax, ecx
004a0b96 8b4810                   mov       ecx, dword ptr [eax + 0x10]
004a0b99 83f9fe                   cmp       ecx, -2
004a0b9c 7429                     je        0x4a0bc7
004a0b9e 83caff                   or        edx, 0xffffffff
004a0ba1 3bca                     cmp       ecx, edx
004a0ba3 7404                     je        0x4a0ba9
004a0ba5 3bca                     cmp       ecx, edx
004a0ba7 741e                     je        0x4a0bc7
004a0ba9 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
004a0baf 8b3e                     mov       edi, dword ptr [esi]
004a0bb1 6a00                     push      0
004a0bb3 6a00                     push      0
004a0bb5 83c110                   add       ecx, 0x10
004a0bb8 52                       push      edx
004a0bb9 e832255b00               call      0xa530f0
004a0bbe 50                       push      eax
004a0bbf 8bce                     mov       ecx, esi
004a0bc1 ff970c010000             call      dword ptr [edi + 0x10c]
004a0bc7 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
004a0bcd 83c010                   add       eax, 0x10
004a0bd0 c70001000000             mov       dword ptr [eax], 1
004a0bd6 eb28                     jmp       0x4a0c00
004a0bd8 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a0bde 8a8800010000             mov       cl, byte ptr [eax + 0x100]
004a0be4 84c9                     test      cl, cl
004a0be6 7418                     je        0x4a0c00
004a0be8 8b8818010000             mov       ecx, dword ptr [eax + 0x118]
004a0bee 85c9                     test      ecx, ecx
004a0bf0 740e                     je        0x4a0c00
004a0bf2 3bcb                     cmp       ecx, ebx
004a0bf4 750a                     jne       0x4a0c00
004a0bf6 c7801801000000000000     mov       dword ptr [eax + 0x118], 0
004a0c00 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004a0c06 8b3d0ce6ff00             mov       edi, dword ptr [0xffe60c]
004a0c0c 8b                       .byte     0x8b
004a0c0d 15                       .byte     0x15
004a0c0e 10e6                     adc       dh, ah
