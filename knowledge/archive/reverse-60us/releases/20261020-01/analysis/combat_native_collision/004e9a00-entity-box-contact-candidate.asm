004e9a00 83c064                   add       eax, 0x64
004e9a03 50                       push      eax
004e9a04 8bcf                     mov       ecx, edi
004e9a06 e8a599f4ff               call      0x4333b0
004e9a0b e8347b7100               call      0xc01544
004e9a10 50                       push      eax
004e9a11 68244ccd00               push      0xcd4c24
004e9a16 8d95f4f7ffff             lea       edx, [ebp - 0x80c]
004e9a1c 6800080000               push      0x800
004e9a21 52                       push      edx
004e9a22 e8c983f1ff               call      0x401df0
004e9a27 83c414                   add       esp, 0x14
004e9a2a 8b0d6c310001             mov       ecx, dword ptr [0x100316c]
004e9a30 8b4964                   mov       ecx, dword ptr [ecx + 0x64]
004e9a33 6a00                     push      0
004e9a35 6a00                     push      0
004e9a37 6a10                     push      0x10
004e9a39 68e6c89bff               push      0xff9bc8e6
004e9a3e 8d85f4f7ffff             lea       eax, [ebp - 0x80c]
004e9a44 50                       push      eax
004e9a45 e8c62c4d00               call      0x9bc710
004e9a4a 8d5f48                   lea       ebx, [edi + 0x48]
004e9a4d 8d776c                   lea       esi, [edi + 0x6c]
004e9a50 81c7b8000000             add       edi, 0xb8
004e9a56 c745fc03000000           mov       dword ptr [ebp - 4], 3
004e9a5d 8d4900                   lea       ecx, [ecx]
004e9a60 833b12                   cmp       dword ptr [ebx], 0x12
004e9a63 0f8480000000             je        0x4e9ae9
004e9a69 8b0f                     mov       ecx, dword ptr [edi]
004e9a6b 85c9                     test      ecx, ecx
004e9a6d 740c                     je        0x4e9a7b
004e9a6f 8b4704                   mov       eax, dword ptr [edi + 4]
004e9a72 2bc1                     sub       eax, ecx
004e9a74 c1f803                   sar       eax, 3
004e9a77 85c0                     test      eax, eax
004e9a79 7504                     jne       0x4e9a7f
004e9a7b 33c0                     xor       eax, eax
004e9a7d eb05                     jmp       0x4e9a84
004e9a7f e8dc85f1ff               call      0x402060
004e9a84 50                       push      eax
004e9a85 8d4e30                   lea       ecx, [esi + 0x30]
004e9a88 e8d385f1ff               call      0x402060
004e9a8d 50                       push      eax
004e9a8e 8bce                     mov       ecx, esi
004e9a90 e8cb85f1ff               call      0x402060
004e9a95 50                       push      eax
004e9a96 8d4ee8                   lea       ecx, [esi - 0x18]
004e9a99 e81299f4ff               call      0x4333b0
004e9a9e 8b13                     mov       edx, dword ptr [ebx]
004e9aa0 83ec08                   sub       esp, 8
004e9aa3 dd1c24                   fstp      qword ptr [esp]
004e9aa6 52                       push      edx
004e9aa7 e8a4970200               call      0x513250
004e9aac 83c404                   add       esp, 4
004e9aaf 50                       push      eax
004e9ab0 68d84bcd00               push      0xcd4bd8
004e9ab5 8d85f4f7ffff             lea       eax, [ebp - 0x80c]
004e9abb 6800080000               push      0x800
004e9ac0 50                       push      eax
004e9ac1 e82a83f1ff               call      0x401df0
004e9ac6 8b156c310001             mov       edx, dword ptr [0x100316c]
004e9acc 83c424                   add       esp, 0x24
004e9acf 6a00                     push      0
004e9ad1 6a00                     push      0
004e9ad3 6a10                     push      0x10
004e9ad5 68e6c89bff               push      0xff9bc8e6
004e9ada 8d8df4f7ffff             lea       ecx, [ebp - 0x80c]
004e9ae0 51                       push      ecx
004e9ae1 8b4a64                   mov       ecx, dword ptr [edx + 0x64]
004e9ae4 e8272c4d00               call      0x9bc710
004e9ae9 8b45fc                   mov       eax, dword ptr [ebp - 4]
004e9aec 83c304                   add       ebx, 4
004e9aef 83c710                   add       edi, 0x10
004e9af2 83c608                   add       esi, 8
004e9af5 48                       dec       eax
004e9af6 8945fc                   mov       dword ptr [ebp - 4], eax
004e9af9 0f8561ffffff             jne       0x4e9a60
004e9aff 5f                       pop       edi
004e9b00 5b                       pop       ebx
004e9b01 5e                       pop       esi
004e9b02 8be5                     mov       esp, ebp
004e9b04 5d                       pop       ebp
004e9b05 c3                       ret       
004e9b06 cc                       int3      
004e9b07 cc                       int3      
004e9b08 cc                       int3      
004e9b09 cc                       int3      
004e9b0a cc                       int3      
004e9b0b cc                       int3      
004e9b0c cc                       int3      
004e9b0d cc                       int3      
004e9b0e cc                       int3      
004e9b0f cc                       int3      
004e9b10 55                       push      ebp
004e9b11 8bec                     mov       ebp, esp
004e9b13 6aff                     push      -1
004e9b15 68a098c500               push      0xc598a0
004e9b1a 64a100000000             mov       eax, dword ptr fs:[0]
004e9b20 50                       push      eax
004e9b21 64892500000000           mov       dword ptr fs:[0], esp
004e9b28 83ec6c                   sub       esp, 0x6c
004e9b2b 56                       push      esi
004e9b2c 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004e9b2f 85f6                     test      esi, esi
004e9b31 0f8497020000             je        0x4e9dce
004e9b37 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004e9b3a 85c0                     test      eax, eax
004e9b3c 0f848c020000             je        0x4e9dce
004e9b42 53                       push      ebx
004e9b43 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004e9b46 8b03                     mov       eax, dword ptr [ebx]
004e9b48 57                       push      edi
004e9b49 8bcb                     mov       ecx, ebx
004e9b4b ff90d4020000             call      dword ptr [eax + 0x2d4]
004e9b51 84c0                     test      al, al
004e9b53 0f84a5000000             je        0x4e9bfe
004e9b59 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004e9b5c 8b17                     mov       edx, dword ptr [edi]
004e9b5e 8bcf                     mov       ecx, edi
004e9b60 ff92dc020000             call      dword ptr [edx + 0x2dc]
004e9b66 84c0                     test      al, al
004e9b68 0f8490000000             je        0x4e9bfe
004e9b6e 83be24010000ff           cmp       dword ptr [esi + 0x124], -1
004e9b75 7507                     jne       0x4e9b7e
004e9b77 8bce                     mov       ecx, esi
004e9b79 e8e2e35300               call      0xa27f60
004e9b7e 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004e9b81 8b8124010000             mov       eax, dword ptr [ecx + 0x124]
004e9b87 81c6e0000000             add       esi, 0xe0
004e9b8d 83f8ff                   cmp       eax, -1
004e9b90 8975e8                   mov       dword ptr [ebp - 0x18], esi
004e9b93 7508                     jne       0x4e9b9d
004e9b95 e8c6e35300               call      0xa27f60
004e9b9a 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004e9b9d 81c1f0000000             add       ecx, 0xf0
004e9ba3 894d0c                   mov       dword ptr [ebp + 0xc], ecx
004e9ba6 8bce                     mov       ecx, esi
004e9ba8 e803565000               call      0x9ef1b0
004e9bad 85c0                     test      eax, eax
004e9baf 744d                     je        0x4e9bfe
004e9bb1 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004e9bb4 e8f7555000               call      0x9ef1b0
004e9bb9 85c0                     test      eax, eax
004e9bbb 7441                     je        0x4e9bfe
004e9bbd 8d4d88                   lea       ecx, [ebp - 0x78]
004e9bc0 e8ebd6f7ff               call      0x4672b0
004e9bc5 8d4db8                   lea       ecx, [ebp - 0x48]
004e9bc8 c745fc00000000           mov       dword ptr [ebp - 4], 0
004e9bcf e8dcd6f7ff               call      0x4672b0
004e9bd4 8b4604                   mov       eax, dword ptr [esi + 4]
004e9bd7 3b4608                   cmp       eax, dword ptr [esi + 8]
004e9bda c645fc01                 mov       byte ptr [ebp - 4], 1
004e9bde 8945f0                   mov       dword ptr [ebp - 0x10], eax
004e9be1 7531                     jne       0x4e9c14
004e9be3 8d4db8                   lea       ecx, [ebp - 0x48]
004e9be6 c645fc00                 mov       byte ptr [ebp - 4], 0
004e9bea e811a7f1ff               call      0x404300
004e9bef 8d4d88                   lea       ecx, [ebp - 0x78]
004e9bf2 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004e9bf9 e802a7f1ff               call      0x404300
004e9bfe 5f                       pop       edi
004e9bff 5b                       pop       ebx
004e9c00 32c0                     xor       al, al
004e9c02 5e                       pop       esi
004e9c03 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004e9c06 64890d00000000           mov       dword ptr fs:[0], ecx
004e9c0d 8be5                     mov       esp, ebp
004e9c0f 5d                       pop       ebp
004e9c10 c3                       ret       
004e9c11 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004e9c14 50                       push      eax
004e9c15 8d4d88                   lea       ecx, [ebp - 0x78]
004e9c18 e803b8fcff               call      0x4b5420
004e9c1d 8b03                     mov       eax, dword ptr [ebx]
004e9c1f 8bcb                     mov       ecx, ebx
004e9c21 ff90c0000000             call      dword ptr [eax + 0xc0]
004e9c27 85c0                     test      eax, eax
004e9c29 7527                     jne       0x4e9c52
004e9c2b 8d4d88                   lea       ecx, [ebp - 0x78]
004e9c2e e87d97f4ff               call      0x4333b0
004e9c33 d9e0                     fchs      
004e9c35 8d4da0                   lea       ecx, [ebp - 0x60]
004e9c38 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9c3b e87097f4ff               call      0x4333b0
004e9c40 d86dec                   fsubr     dword ptr [ebp - 0x14]
004e9c43 8d4dec                   lea       ecx, [ebp - 0x14]
004e9c46 51                       push      ecx
004e9c47 8d4d88                   lea       ecx, [ebp - 0x78]
004e9c4a d95dec                   fstp      dword ptr [ebp - 0x14]
004e9c4d e80ea9f1ff               call      0x404560
004e9c52 8b13                     mov       edx, dword ptr [ebx]
004e9c54 8bcb                     mov       ecx, ebx
004e9c56 ff9294000000             call      dword ptr [edx + 0x94]
004e9c5c 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9c5f db45ec                   fild      dword ptr [ebp - 0x14]
004e9c62 8d45ec                   lea       eax, [ebp - 0x14]
004e9c65 50                       push      eax
004e9c66 8d4d88                   lea       ecx, [ebp - 0x78]
004e9c69 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9c6c e89fccf7ff               call      0x466910
004e9c71 8b13                     mov       edx, dword ptr [ebx]
004e9c73 8bcb                     mov       ecx, ebx
004e9c75 ff9298000000             call      dword ptr [edx + 0x98]
004e9c7b 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9c7e db45ec                   fild      dword ptr [ebp - 0x14]
004e9c81 8d45ec                   lea       eax, [ebp - 0x14]
004e9c84 50                       push      eax
004e9c85 8d4d90                   lea       ecx, [ebp - 0x70]
004e9c88 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9c8b e880ccf7ff               call      0x466910
004e9c90 8b13                     mov       edx, dword ptr [ebx]
004e9c92 8bcb                     mov       ecx, ebx
004e9c94 ff929c000000             call      dword ptr [edx + 0x9c]
004e9c9a 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9c9d db45ec                   fild      dword ptr [ebp - 0x14]
004e9ca0 8d45ec                   lea       eax, [ebp - 0x14]
004e9ca3 50                       push      eax
004e9ca4 8d4d98                   lea       ecx, [ebp - 0x68]
004e9ca7 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9caa e861ccf7ff               call      0x466910
004e9caf 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004e9cb2 8b7104                   mov       esi, dword ptr [ecx + 4]
004e9cb5 8bd1                     mov       edx, ecx
004e9cb7 3b7208                   cmp       esi, dword ptr [edx + 8]
004e9cba 0f84c4000000             je        0x4e9d84
004e9cc0 56                       push      esi
004e9cc1 8d4db8                   lea       ecx, [ebp - 0x48]
004e9cc4 e857b7fcff               call      0x4b5420
004e9cc9 8b07                     mov       eax, dword ptr [edi]
004e9ccb 8bcf                     mov       ecx, edi
004e9ccd ff90c0000000             call      dword ptr [eax + 0xc0]
004e9cd3 85c0                     test      eax, eax
004e9cd5 7527                     jne       0x4e9cfe
004e9cd7 8d4db8                   lea       ecx, [ebp - 0x48]
004e9cda e8d196f4ff               call      0x4333b0
004e9cdf d9e0                     fchs      
004e9ce1 8d4dd0                   lea       ecx, [ebp - 0x30]
004e9ce4 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9ce7 e8c496f4ff               call      0x4333b0
004e9cec d86dec                   fsubr     dword ptr [ebp - 0x14]
004e9cef 8d4dec                   lea       ecx, [ebp - 0x14]
004e9cf2 51                       push      ecx
004e9cf3 8d4db8                   lea       ecx, [ebp - 0x48]
004e9cf6 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9cf9 e862a8f1ff               call      0x404560
004e9cfe 8b17                     mov       edx, dword ptr [edi]
004e9d00 8bcf                     mov       ecx, edi
004e9d02 ff9294000000             call      dword ptr [edx + 0x94]
004e9d08 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9d0b db45ec                   fild      dword ptr [ebp - 0x14]
004e9d0e 8d45ec                   lea       eax, [ebp - 0x14]
004e9d11 50                       push      eax
004e9d12 8d4db8                   lea       ecx, [ebp - 0x48]
004e9d15 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9d18 e8f3cbf7ff               call      0x466910
004e9d1d 8b17                     mov       edx, dword ptr [edi]
004e9d1f 8bcf                     mov       ecx, edi
004e9d21 ff9298000000             call      dword ptr [edx + 0x98]
004e9d27 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9d2a db45ec                   fild      dword ptr [ebp - 0x14]
004e9d2d 8d45ec                   lea       eax, [ebp - 0x14]
004e9d30 50                       push      eax
004e9d31 8d4dc0                   lea       ecx, [ebp - 0x40]
004e9d34 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9d37 e8d4cbf7ff               call      0x466910
004e9d3c 8b17                     mov       edx, dword ptr [edi]
004e9d3e 8bcf                     mov       ecx, edi
004e9d40 ff929c000000             call      dword ptr [edx + 0x9c]
004e9d46 8945ec                   mov       dword ptr [ebp - 0x14], eax
004e9d49 db45ec                   fild      dword ptr [ebp - 0x14]
004e9d4c 8d45ec                   lea       eax, [ebp - 0x14]
004e9d4f 50                       push      eax
004e9d50 8d4dc8                   lea       ecx, [ebp - 0x38]
004e9d53 d95dec                   fstp      dword ptr [ebp - 0x14]
004e9d56 e8b5cbf7ff               call      0x466910
004e9d5b 8b4d18                   mov       ecx, dword ptr [ebp + 0x18]
004e9d5e 51                       push      ecx
004e9d5f 8d55b8                   lea       edx, [ebp - 0x48]
004e9d62 52                       push      edx
004e9d63 8d4588                   lea       eax, [ebp - 0x78]
004e9d66 50                       push      eax
004e9d67 e874a75300               call      0xa244e0
004e9d6c 83c40c                   add       esp, 0xc
004e9d6f 84c0                     test      al, al
004e9d71 752d                     jne       0x4e9da0
004e9d73 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004e9d76 8b4108                   mov       eax, dword ptr [ecx + 8]
004e9d79 83c630                   add       esi, 0x30
004e9d7c 3bf0                     cmp       esi, eax
004e9d7e 0f853cffffff             jne       0x4e9cc0
004e9d84 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004e9d87 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004e9d8a 8b4a08                   mov       ecx, dword ptr [edx + 8]
004e9d8d 83c030                   add       eax, 0x30
004e9d90 3bc1                     cmp       eax, ecx
004e9d92 8945f0                   mov       dword ptr [ebp - 0x10], eax
004e9d95 0f8576feffff             jne       0x4e9c11
004e9d9b e943feffff               jmp       0x4e9be3
004e9da0 8d4db8                   lea       ecx, [ebp - 0x48]
004e9da3 c645fc00                 mov       byte ptr [ebp - 4], 0
004e9da7 e854a5f1ff               call      0x404300
004e9dac 8d4d88                   lea       ecx, [ebp - 0x78]
004e9daf c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004e9db6 e845a5f1ff               call      0x404300
004e9dbb 5f                       pop       edi
004e9dbc 5b                       pop       ebx
004e9dbd b001                     mov       al, 1
004e9dbf 5e                       pop       esi
004e9dc0 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004e9dc3 64890d00000000           mov       dword ptr fs:[0], ecx
004e9dca 8be5                     mov       esp, ebp
004e9dcc 5d                       pop       ebp
004e9dcd c3                       ret       
004e9dce 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004e9dd1 32c0                     xor       al, al
004e9dd3 5e                       pop       esi
004e9dd4 64890d00000000           mov       dword ptr fs:[0], ecx
004e9ddb 8be5                     mov       esp, ebp
004e9ddd 5d                       pop       ebp
004e9dde c3                       ret       
004e9ddf cc                       int3      
004e9de0 55                       push      ebp
004e9de1 8bec                     mov       ebp, esp
004e9de3 53                       push      ebx
004e9de4 56                       push      esi
004e9de5 8bf1                     mov       esi, ecx
004e9de7 8b06                     mov       eax, dword ptr [esi]
004e9de9 57                       push      edi
004e9dea ff90a8020000             call      dword ptr [eax + 0x2a8]
004e9df0 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004e9df3 6a00                     push      0
004e9df5 686c52f500               push      0xf5526c
004e9dfa 687c28f400               push      0xf4287c
004e9dff 6a00                     push      0
004e9e01 51                       push      ecx
004e9e02 8bf8                     mov       edi, eax
004e9e04 e8026f7100               call      0xc00d0b
004e9e09 83c414                   add       esp, 0x14
004e9e0c 85ff                     test      edi, edi
004e9e0e 8bd8                     mov       ebx, eax
004e9e10 0f8483000000             je        0x4e9e99
004e9e16 85db                     test      ebx, ebx
004e9e18 747f                     je        0x4e9e99
004e9e1a 8bcf                     mov       ecx, edi
004e9e1c e86f22fbff               call      0x49c090
004e9e21 84c0                     test      al, al
004e9e23 7474                     je        0x4e9e99
004e9e25 56                       push      esi
004e9e26 53                       push      ebx
004e9e27 e8c4f2ffff               call      0x4e90f0
004e9e2c 83c408                   add       esp, 8
004e9e2f 84c0                     test      al, al
004e9e31 742c                     je        0x4e9e5f
004e9e33 8b9600010000             mov       edx, dword ptr [esi + 0x100]
004e9e39 8b8a14010000             mov       ecx, dword ptr [edx + 0x114]
004e9e3f 6a00                     push      0
004e9e41 6a01                     push      1
004e9e43 e828200500               call      0x53be70
004e9e48 8b07                     mov       eax, dword ptr [edi]
004e9e4a 8bcf                     mov       ecx, edi
004e9e4c ff5040                   call      dword ptr [eax + 0x40]
004e9e4f 8b0dd8e5ff00             mov       ecx, dword ptr [0xffe5d8]
004e9e55 50                       push      eax
004e9e56 6a05                     push      5
004e9e58 6a01                     push      1
004e9e5a e8b11b0300               call      0x51ba10
004e9e5f 56                       push      esi
004e9e60 53                       push      ebx
004e9e61 e8faf2ffff               call      0x4e9160
004e9e66 83c408                   add       esp, 8
004e9e69 84c0                     test      al, al
004e9e6b 742c                     je        0x4e9e99
004e9e6d 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004e9e73 8b8914010000             mov       ecx, dword ptr [ecx + 0x114]
004e9e79 6a00                     push      0
004e9e7b 6a02                     push      2
004e9e7d e8ee1f0500               call      0x53be70
004e9e82 8b17                     mov       edx, dword ptr [edi]
004e9e84 8bcf                     mov       ecx, edi
004e9e86 ff5240                   call      dword ptr [edx + 0x40]
004e9e89 8b0dd8e5ff00             mov       ecx, dword ptr [0xffe5d8]
004e9e8f 50                       push      eax
004e9e90 6a04                     push      4
004e9e92 6a01                     push      1
004e9e94 e8771b0300               call      0x51ba10
004e9e99 5f                       pop       edi
004e9e9a 5e                       pop       esi
004e9e9b 5b                       pop       ebx
004e9e9c 5d                       pop       ebp
004e9e9d c20400                   ret       4
004e9ea0 55                       push      ebp
004e9ea1 8bec                     mov       ebp, esp
004e9ea3 56                       push      esi
004e9ea4 8b7508                   mov       esi, dword ptr [ebp + 8]
004e9ea7 85f6                     test      esi, esi
004e9ea9 57                       push      edi
004e9eaa 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004e9ead 746c                     je        0x4e9f1b
004e9eaf 8b06                     mov       eax, dword ptr [esi]
004e9eb1 8bce                     mov       ecx, esi
004e9eb3 ff9068010000             call      dword ptr [eax + 0x168]
004e9eb9 84c0                     test      al, al
004e9ebb 0f85a0000000             jne       0x4e9f61
004e9ec1 8b16                     mov       edx, dword ptr [esi]
004e9ec3 8bce                     mov       ecx, esi
004e9ec5 ff5264                   call      dword ptr [edx + 0x64]
004e9ec8 84c0                     test      al, al
004e9eca 0f8491000000             je        0x4e9f61
004e9ed0 8b06                     mov       eax, dword ptr [esi]
004e9ed2 8bce                     mov       ecx, esi
004e9ed4 ff5034                   call      dword ptr [eax + 0x34]
004e9ed7 84c0                     test      al, al
004e9ed9 7440                     je        0x4e9f1b
004e9edb 6a00                     push      0
004e9edd 680829f400               push      0xf42908
004e9ee2 681009f400               push      0xf40910
004e9ee7 6a00                     push      0
004e9ee9 56                       push      esi
004e9eea e81c6e7100               call      0xc00d0b
004e9eef 83c414                   add       esp, 0x14
004e9ef2 85c0                     test      eax, eax
004e9ef4 7425                     je        0x4e9f1b
004e9ef6 8b8874280000             mov       ecx, dword ptr [eax + 0x2874]
004e9efc 8b81100b0000             mov       eax, dword ptr [ecx + 0xb10]
004e9f02 8b89140b0000             mov       ecx, dword ptr [ecx + 0xb14]
004e9f08 3bc1                     cmp       eax, ecx
004e9f0a 740f                     je        0x4e9f1b
004e9f0c 8d642400                 lea       esp, [esp]
004e9f10 3b38                     cmp       edi, dword ptr [eax]
004e9f12 744d                     je        0x4e9f61
004e9f14 83c004                   add       eax, 4
004e9f17 3bc1                     cmp       eax, ecx
004e9f19 75f5                     jne       0x4e9f10
004e9f1b 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9f21 8b11                     mov       edx, dword ptr [ecx]
004e9f23 53                       push      ebx
004e9f24 6a02                     push      2
004e9f26 6a15                     push      0x15
004e9f28 ff5208                   call      dword ptr [edx + 8]
004e9f2b 85f6                     test      esi, esi
004e9f2d 743b                     je        0x4e9f6a
004e9f2f a164310001               mov       eax, dword ptr [0x1003164]
004e9f34 8b16                     mov       edx, dword ptr [esi]
004e9f36 8b18                     mov       ebx, dword ptr [eax]
004e9f38 8bce                     mov       ecx, esi
004e9f3a ff523c                   call      dword ptr [edx + 0x3c]
004e9f3d 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9f43 50                       push      eax
004e9f44 ff5324                   call      dword ptr [ebx + 0x24]
004e9f47 a164310001               mov       eax, dword ptr [0x1003164]
004e9f4c 8b16                     mov       edx, dword ptr [esi]
004e9f4e 8b18                     mov       ebx, dword ptr [eax]
004e9f50 8bce                     mov       ecx, esi
004e9f52 ff5240                   call      dword ptr [edx + 0x40]
004e9f55 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9f5b 50                       push      eax
004e9f5c ff5324                   call      dword ptr [ebx + 0x24]
004e9f5f eb26                     jmp       0x4e9f87
004e9f61 5f                       pop       edi
004e9f62 b8ffff0000               mov       eax, 0xffff
004e9f67 5e                       pop       esi
004e9f68 5d                       pop       ebp
004e9f69 c3                       ret       
004e9f6a 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9f70 8b01                     mov       eax, dword ptr [ecx]
004e9f72 68ffff0000               push      0xffff
004e9f77 ff5024                   call      dword ptr [eax + 0x24]
004e9f7a 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9f80 8b11                     mov       edx, dword ptr [ecx]
004e9f82 6a00                     push      0
004e9f84 ff5224                   call      dword ptr [edx + 0x24]
004e9f87 8b7524                   mov       esi, dword ptr [ebp + 0x24]
004e9f8a 85f6                     test      esi, esi
004e9f8c 7432                     je        0x4e9fc0
004e9f8e a164310001               mov       eax, dword ptr [0x1003164]
004e9f93 8b16                     mov       edx, dword ptr [esi]
004e9f95 8b18                     mov       ebx, dword ptr [eax]
004e9f97 8bce                     mov       ecx, esi
004e9f99 ff523c                   call      dword ptr [edx + 0x3c]
004e9f9c 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9fa2 50                       push      eax
004e9fa3 ff5324                   call      dword ptr [ebx + 0x24]
004e9fa6 a164310001               mov       eax, dword ptr [0x1003164]
004e9fab 8b16                     mov       edx, dword ptr [esi]
004e9fad 8b18                     mov       ebx, dword ptr [eax]
004e9faf 8bce                     mov       ecx, esi
004e9fb1 ff5240                   call      dword ptr [edx + 0x40]
004e9fb4 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9fba 50                       push      eax
004e9fbb ff5324                   call      dword ptr [ebx + 0x24]
004e9fbe eb1d                     jmp       0x4e9fdd
004e9fc0 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9fc6 8b01                     mov       eax, dword ptr [ecx]
004e9fc8 68ffff0000               push      0xffff
004e9fcd ff5024                   call      dword ptr [eax + 0x24]
004e9fd0 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9fd6 8b11                     mov       edx, dword ptr [ecx]
004e9fd8 6a00                     push      0
004e9fda ff5224                   call      dword ptr [edx + 0x24]
004e9fdd 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9fe3 8b01                     mov       eax, dword ptr [ecx]
004e9fe5 6a01                     push      1
004e9fe7 ff5024                   call      dword ptr [eax + 0x24]
004e9fea 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9ff0 8b11                     mov       edx, dword ptr [ecx]
004e9ff2 57                       push      edi
004e9ff3 ff5224                   call      dword ptr [edx + 0x24]
004e9ff6 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e9ffc 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004e9fff 8b01                     mov       eax, dword ptr [ecx]
004ea001 52                       push      edx
004ea002 ff502c                   call      dword ptr [eax + 0x2c]
004ea005 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
004ea00b a164310001               mov       eax, dword ptr [0x1003164]
004ea010 8b11                     mov       edx, dword ptr [ecx]
004ea012 8b30                     mov       esi, dword ptr [eax]
004ea014 ff92e0060000             call      dword ptr [edx + 0x6e0]
004ea01a 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea020 50                       push      eax
004ea021 ff5624                   call      dword ptr [esi + 0x24]
004ea024 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea02a 8b01                     mov       eax, dword ptr [ecx]
004ea02c ff9088000000             call      dword ptr [eax + 0x88]
004ea032 8b88b0000000             mov       ecx, dword ptr [eax + 0xb0]
004ea038 e8f3330200               call      0x50d430
004ea03d 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea043 8b11                     mov       edx, dword ptr [ecx]
004ea045 8bf0                     mov       esi, eax
004ea047 56                       push      esi
004ea048 ff5224                   call      dword ptr [edx + 0x24]
004ea04b 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea051 8b01                     mov       eax, dword ptr [ecx]
004ea053 6a00                     push      0
004ea055 ff5020                   call      dword ptr [eax + 0x20]
004ea058 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea05e 8b4520                   mov       eax, dword ptr [ebp + 0x20]
004ea061 8b11                     mov       edx, dword ptr [ecx]
004ea063 50                       push      eax
004ea064 ff5220                   call      dword ptr [edx + 0x20]
004ea067 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea06d 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004ea070 8b11                     mov       edx, dword ptr [ecx]
004ea072 50                       push      eax
004ea073 ff5224                   call      dword ptr [edx + 0x24]
004ea076 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea07c 8b4518                   mov       eax, dword ptr [ebp + 0x18]
004ea07f 8b11                     mov       edx, dword ptr [ecx]
004ea081 50                       push      eax
004ea082 ff5224                   call      dword ptr [edx + 0x24]
004ea085 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea08b 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004ea08e 8b11                     mov       edx, dword ptr [ecx]
004ea090 50                       push      eax
004ea091 ff5224                   call      dword ptr [edx + 0x24]
004ea094 8b4528                   mov       eax, dword ptr [ebp + 0x28]
004ea097 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea09d 8b11                     mov       edx, dword ptr [ecx]
004ea09f 50                       push      eax
004ea0a0 8b452c                   mov       eax, dword ptr [ebp + 0x2c]
004ea0a3 50                       push      eax
004ea0a4 ff5238                   call      dword ptr [edx + 0x38]
004ea0a7 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea0ad 8b4530                   mov       eax, dword ptr [ebp + 0x30]
004ea0b0 8b11                     mov       edx, dword ptr [ecx]
004ea0b2 50                       push      eax
004ea0b3 ff5224                   call      dword ptr [edx + 0x24]
004ea0b6 8b7d34                   mov       edi, dword ptr [ebp + 0x34]
004ea0b9 85ff                     test      edi, edi
004ea0bb 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea0c1 8b11                     mov       edx, dword ptr [ecx]
004ea0c3 5b                       pop       ebx
004ea0c4 7415                     je        0x4ea0db
004ea0c6 6a01                     push      1
004ea0c8 ff5220                   call      dword ptr [edx + 0x20]
004ea0cb 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004ea0d1 8b01                     mov       eax, dword ptr [ecx]
004ea0d3 6a04                     push      4
004ea0d5 57                       push      edi
004ea0d6 ff5034                   call      dword ptr [eax + 0x34]
004ea0d9 eb05                     jmp       0x4ea0e0
004ea0db 6a00                     push      0
004ea0dd ff5220                   call      dword ptr [edx + 0x20]
004ea0e0 8b0d90070c01             mov       ecx, dword ptr [0x10c0790]
004ea0e6 8b01                     mov       eax, dword ptr [ecx]
004ea0e8 6a03                     push      3
004ea0ea 6a00                     push      0
004ea0ec 6aff                     push      -1
004ea0ee 6a01                     push      1
004ea0f0 ff5044                   call      dword ptr [eax + 0x44]
004ea0f3 5f                       pop       edi
004ea0f4 8bc6                     mov       eax, esi
004ea0f6 5e                       pop       esi
004ea0f7 5d                       pop       ebp
004ea0f8 c3                       ret       
004ea0f9 cc                       int3      
004ea0fa cc                       int3      
004ea0fb cc                       int3      
004ea0fc cc                       int3      
004ea0fd cc                       int3      
004ea0fe cc                       int3      
004ea0ff cc                       int3      
004ea100 55                       push      ebp
004ea101 8bec                     mov       ebp, esp
004ea103 56                       push      esi
004ea104 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004ea107 57                       push      edi
004ea108 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ea10b 85ff                     test      edi, edi
004ea10d 7470                     je        0x4ea17f
004ea10f 8b07                     mov       eax, dword ptr [edi]
004ea111 8bcf                     mov       ecx, edi
004ea113 ff9068010000             call      dword ptr [eax + 0x168]
004ea119 84c0                     test      al, al
004ea11b 0f8570010000             jne       0x4ea291
004ea121 8b17                     mov       edx, dword ptr [edi]
004ea123 8bcf                     mov       ecx, edi
004ea125 ff5264                   call      dword ptr [edx + 0x64]
004ea128 84c0                     test      al, al
004ea12a 0f8461010000             je        0x4ea291
004ea130 8b07                     mov       eax, dword ptr [edi]
004ea132 8bcf                     mov       ecx, edi
004ea134 ff5034                   call      dword ptr [eax + 0x34]
004ea137 84c0                     test      al, al
004ea139 7444                     je        0x4ea17f
004ea13b 6a00                     push      0
004ea13d 680829f400               push      0xf42908
004ea142 681009f400               push      0xf40910
004ea147 6a00                     push      0
004ea149 57                       push      edi
004ea14a e8bc6b7100               call      0xc00d0b
004ea14f 83c414                   add       esp, 0x14
004ea152 85c0                     test      eax, eax
004ea154 7429                     je        0x4ea17f
004ea156 8b8874280000             mov       ecx, dword ptr [eax + 0x2874]
004ea15c 8b81100b0000             mov       eax, dword ptr [ecx + 0xb10]
004ea162 8b89140b0000             mov       ecx, dword ptr [ecx + 0xb14]
004ea168 3bc1                     cmp       eax, ecx
004ea16a 7413                     je        0x4ea17f
004ea16c 8d642400                 lea       esp, [esp]
004ea170 3b30                     cmp       esi, dword ptr [eax]
004ea172 0f8419010000             je        0x4ea291
004ea178 83c004                   add       eax, 4
004ea17b 3bc1                     cmp       eax, ecx
004ea17d 75f1                     jne       0x4ea170
004ea17f 8b17                     mov       edx, dword ptr [edi]
004ea181 53                       push      ebx
004ea182 8bcf                     mov       ecx, edi
004ea184 ff523c                   call      dword ptr [edx + 0x3c]
004ea187 3d11010000               cmp       eax, 0x111
004ea18c 0f8578010000             jne       0x4ea30a
004ea192 8b07                     mov       eax, dword ptr [edi]
004ea194 8bcf                     mov       ecx, edi
004ea196 ff5034                   call      dword ptr [eax + 0x34]
004ea199 84c0                     test      al, al
004ea19b 0f8569010000             jne       0x4ea30a
004ea1a1 a1d4f10401               mov       eax, dword ptr [0x104f1d4]
004ea1a6 8b8894210000             mov       ecx, dword ptr [eax + 0x2194]
004ea1ac 85c9                     test      ecx, ecx
004ea1ae 0f8540010000             jne       0x4ea2f4
004ea1b4 39b09c210000             cmp       dword ptr [eax + 0x219c], esi
004ea1ba 0f8534010000             jne       0x4ea2f4
004ea1c0 81fee8560000             cmp       esi, 0x56e8
004ea1c6 0f843e010000             je        0x4ea30a
004ea1cc 81fee2590000             cmp       esi, 0x59e2
004ea1d2 0f8432010000             je        0x4ea30a
004ea1d8 81fe25520000             cmp       esi, 0x5225
004ea1de 0f8426010000             je        0x4ea30a
004ea1e4 81fe1a5a0000             cmp       esi, 0x5a1a
004ea1ea 0f841a010000             je        0x4ea30a
004ea1f0 81fe951f0000             cmp       esi, 0x1f95
004ea1f6 0f840e010000             je        0x4ea30a
004ea1fc 81fe50c30000             cmp       esi, 0xc350
004ea202 7c0c                     jl        0x4ea210
004ea204 81fe20cb0000             cmp       esi, 0xcb20
004ea20a 0f8efa000000             jle       0x4ea30a
004ea210 83b89821000006           cmp       dword ptr [eax + 0x2198], 6
004ea217 0f8ecf000000             jle       0x4ea2ec
004ea21d ff8090210000             inc       dword ptr [eax + 0x2190]
004ea223 a1d4f10401               mov       eax, dword ptr [0x104f1d4]
004ea228 81809021000010270000     add       dword ptr [eax + 0x2190], 0x2710
004ea232 a1d4f10401               mov       eax, dword ptr [0x104f1d4]
004ea237 8b8898210000             mov       ecx, dword ptr [eax + 0x2198]
004ea23d 41                       inc       ecx
004ea23e 81fef9590000             cmp       esi, 0x59f9
004ea244 898898210000             mov       dword ptr [eax + 0x2198], ecx
004ea24a a1d4f10401               mov       eax, dword ptr [0x104f1d4]
004ea24f 7c11                     jl        0x4ea262
004ea251 81fefc590000             cmp       esi, 0x59fc
004ea257 7f09                     jg        0x4ea262
004ea259 83b89821000032           cmp       dword ptr [eax + 0x2198], 0x32
004ea260 7e73                     jle       0x4ea2d5
004ea262 81fecb560000             cmp       esi, 0x56cb
004ea268 b914000000               mov       ecx, 0x14
004ea26d 7c10                     jl        0x4ea27f
004ea26f 81fecd560000             cmp       esi, 0x56cd
004ea275 7f08                     jg        0x4ea27f
004ea277 398898210000             cmp       dword ptr [eax + 0x2198], ecx
004ea27d 7e56                     jle       0x4ea2d5
004ea27f 81fef5560000             cmp       esi, 0x56f5
004ea285 7513                     jne       0x4ea29a
004ea287 398898210000             cmp       dword ptr [eax + 0x2198], ecx
004ea28d 7e46                     jle       0x4ea2d5
004ea28f eb79                     jmp       0x4ea30a
004ea291 5f                       pop       edi
004ea292 b8ffff0000               mov       eax, 0xffff
004ea297 5e                       pop       esi
004ea298 5d                       pop       ebp
004ea299 c3                       ret       
004ea29a 81fe165a0000             cmp       esi, 0x5a16
004ea2a0 7c11                     jl        0x4ea2b3
004ea2a2 81fe1b5a0000             cmp       esi, 0x5a1b
004ea2a8 7f09                     jg        0x4ea2b3
004ea2aa 83b89821000019           cmp       dword ptr [eax + 0x2198], 0x19
004ea2b1 7e22                     jle       0x4ea2d5
004ea2b3 81fe4d4e0000             cmp       esi, 0x4e4d
004ea2b9 750a                     jne       0x4ea2c5
004ea2bb 398898210000             cmp       dword ptr [eax + 0x2198], ecx
004ea2c1 7e12                     jle       0x4ea2d5
004ea2c3 eb45                     jmp       0x4ea30a
004ea2c5 81fe4e4e0000             cmp       esi, 0x4e4e
004ea2cb 753d                     jne       0x4ea30a
004ea2cd 398898210000             cmp       dword ptr [eax + 0x2198], ecx
004ea2d3 7f35                     jg        0x4ea30a
004ea2d5 818090210000f0d8ffff     add       dword ptr [eax + 0x2190], 0xffffd8f0
004ea2df a1d4f10401               mov       eax, dword ptr [0x104f1d4]
004ea2e4 ff8890210000             dec       dword ptr [eax + 0x2190]
004ea2ea eb1e                     jmp       0x4ea30a
004ea2ec ff8098210000             inc       dword ptr [eax + 0x2198]
004ea2f2 eb16                     jmp       0x4ea30a
004ea2f4 c7809421000000000000     mov       dword ptr [eax + 0x2194], 0
004ea2fe 8b                       .byte     0x8b
004ea2ff 0d                       .byte     0x0d
