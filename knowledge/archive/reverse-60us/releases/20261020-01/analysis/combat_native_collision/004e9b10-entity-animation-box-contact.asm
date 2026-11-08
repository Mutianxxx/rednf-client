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
