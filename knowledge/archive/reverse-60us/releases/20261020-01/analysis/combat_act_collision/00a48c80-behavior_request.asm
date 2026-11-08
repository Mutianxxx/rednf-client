00a48c80 55                       push       ebp
00a48c81 8bec                     mov        ebp, esp
00a48c83 56                       push       esi
00a48c84 57                       push       edi
00a48c85 8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a48c88 8bf1                     mov        esi, ecx
00a48c8a 8b4f04                   mov        ecx, dword ptr [edi + 4]
00a48c8d 85c9                     test       ecx, ecx
00a48c8f 0f846e010000             je         0xa48e03
00a48c95 8b4708                   mov        eax, dword ptr [edi + 8]
00a48c98 2bc1                     sub        eax, ecx
00a48c9a c1f802                   sar        eax, 2
00a48c9d 83f801                   cmp        eax, 1
00a48ca0 0f825d010000             jb         0xa48e03
00a48ca6 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48ca9 8b01                     mov        eax, dword ptr [ecx]
00a48cab ff5064                   call       dword ptr [eax + 0x64]
00a48cae 84c0                     test       al, al
00a48cb0 0f844d010000             je         0xa48e03
00a48cb6 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48cb9 e8d233a5ff               call       0x49c090
00a48cbe 84c0                     test       al, al
00a48cc0 0f843d010000             je         0xa48e03
00a48cc6 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48ccc 8b11                     mov        edx, dword ptr [ecx]
00a48cce 53                       push       ebx
00a48ccf 6a01                     push       1
00a48cd1 6a33                     push       0x33
00a48cd3 ff5208                   call       dword ptr [edx + 8]
00a48cd6 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48cd9 a164310001               mov        eax, dword ptr [0x1003164]
00a48cde 8b11                     mov        edx, dword ptr [ecx]
00a48ce0 8b18                     mov        ebx, dword ptr [eax]
00a48ce2 ff523c                   call       dword ptr [edx + 0x3c]
00a48ce5 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48ceb 50                       push       eax
00a48cec ff5324                   call       dword ptr [ebx + 0x24]
00a48cef 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48cf2 a164310001               mov        eax, dword ptr [0x1003164]
00a48cf7 8b11                     mov        edx, dword ptr [ecx]
00a48cf9 8b18                     mov        ebx, dword ptr [eax]
00a48cfb ff5240                   call       dword ptr [edx + 0x40]
00a48cfe 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d04 50                       push       eax
00a48d05 ff5324                   call       dword ptr [ebx + 0x24]
00a48d08 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d0e 8b01                     mov        eax, dword ptr [ecx]
00a48d10 33d2                     xor        edx, edx
00a48d12 668b96cc020000           mov        dx, word ptr [esi + 0x2cc]
00a48d19 52                       push       edx
00a48d1a ff5024                   call       dword ptr [eax + 0x24]
00a48d1d 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d23 8b01                     mov        eax, dword ptr [ecx]
00a48d25 33d2                     xor        edx, edx
00a48d27 668b96d0020000           mov        dx, word ptr [esi + 0x2d0]
00a48d2e 52                       push       edx
00a48d2f ff5024                   call       dword ptr [eax + 0x24]
00a48d32 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d38 8b5508                   mov        edx, dword ptr [ebp + 8]
00a48d3b 8b01                     mov        eax, dword ptr [ecx]
00a48d3d 52                       push       edx
00a48d3e ff5024                   call       dword ptr [eax + 0x24]
00a48d41 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d47 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a48d4a 8b01                     mov        eax, dword ptr [ecx]
00a48d4c 52                       push       edx
00a48d4d ff5024                   call       dword ptr [eax + 0x24]
00a48d50 8b4704                   mov        eax, dword ptr [edi + 4]
00a48d53 85c0                     test       eax, eax
00a48d55 7504                     jne        0xa48d5b
00a48d57 33d2                     xor        edx, edx
00a48d59 eb08                     jmp        0xa48d63
00a48d5b 8b5708                   mov        edx, dword ptr [edi + 8]
00a48d5e 2bd0                     sub        edx, eax
00a48d60 c1fa02                   sar        edx, 2
00a48d63 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48d69 8b01                     mov        eax, dword ptr [ecx]
00a48d6b 52                       push       edx
00a48d6c ff5024                   call       dword ptr [eax + 0x24]
00a48d6f 8b5f04                   mov        ebx, dword ptr [edi + 4]
00a48d72 3b5f08                   cmp        ebx, dword ptr [edi + 8]
00a48d75 895d10                   mov        dword ptr [ebp + 0x10], ebx
00a48d78 7457                     je         0xa48dd1
00a48d7a 8d9b00000000             lea        ebx, [ebx]
00a48d80 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48d83 e80833a5ff               call       0x49c090
00a48d88 84c0                     test       al, al
00a48d8a 7438                     je         0xa48dc4
00a48d8c 8b0b                     mov        ecx, dword ptr [ebx]
00a48d8e 8b1564310001             mov        edx, dword ptr [0x1003164]
00a48d94 8b01                     mov        eax, dword ptr [ecx]
00a48d96 8b1a                     mov        ebx, dword ptr [edx]
00a48d98 ff503c                   call       dword ptr [eax + 0x3c]
00a48d9b 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48da1 50                       push       eax
00a48da2 ff5324                   call       dword ptr [ebx + 0x24]
00a48da5 8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00a48da8 8b09                     mov        ecx, dword ptr [ecx]
00a48daa 8b1564310001             mov        edx, dword ptr [0x1003164]
00a48db0 8b01                     mov        eax, dword ptr [ecx]
00a48db2 8b1a                     mov        ebx, dword ptr [edx]
00a48db4 ff5040                   call       dword ptr [eax + 0x40]
00a48db7 8b0d64310001             mov        ecx, dword ptr [0x1003164]
00a48dbd 50                       push       eax
00a48dbe ff5324                   call       dword ptr [ebx + 0x24]
00a48dc1 8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
00a48dc4 8b4708                   mov        eax, dword ptr [edi + 8]
00a48dc7 83c304                   add        ebx, 4
00a48dca 3bd8                     cmp        ebx, eax
00a48dcc 895d10                   mov        dword ptr [ebp + 0x10], ebx
00a48dcf 75af                     jne        0xa48d80
00a48dd1 8b0d90070c01             mov        ecx, dword ptr [0x10c0790]
00a48dd7 8b11                     mov        edx, dword ptr [ecx]
00a48dd9 6a03                     push       3
00a48ddb 6a00                     push       0
00a48ddd 6aff                     push       -1
00a48ddf 6a01                     push       1
00a48de1 ff5244                   call       dword ptr [edx + 0x44]
00a48de4 8b96d0020000             mov        edx, dword ptr [esi + 0x2d0]
00a48dea 8b4e7c                   mov        ecx, dword ptr [esi + 0x7c]
00a48ded 8b01                     mov        eax, dword ptr [ecx]
00a48def 52                       push       edx
00a48df0 8b96cc020000             mov        edx, dword ptr [esi + 0x2cc]
00a48df6 52                       push       edx
00a48df7 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a48dfa 57                       push       edi
00a48dfb 52                       push       edx
00a48dfc ff9078010000             call       dword ptr [eax + 0x178]
00a48e02 5b                       pop        ebx
00a48e03 5f                       pop        edi
00a48e04 5e                       pop        esi
00a48e05 5d                       pop        ebp
00a48e06 c21000                   ret        0x10
