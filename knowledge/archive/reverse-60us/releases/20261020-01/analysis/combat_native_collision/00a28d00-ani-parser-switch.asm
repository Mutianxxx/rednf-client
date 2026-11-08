00a28d00 c194000000e8f62e         rcl       dword ptr [eax + eax - 0x9180000], 0x2e
00a28d08 0000                     add       byte ptr [eax], al
00a28d0a e97b010000               jmp       0xa28e8a
00a28d0f 53                       push      ebx
00a28d10 e8bb6ae0ff               call      0x82f7d0
00a28d15 8b4dd4                   mov       ecx, dword ptr [ebp - 0x2c]
00a28d18 83c404                   add       esp, 4
00a28d1b 894130                   mov       dword ptr [ecx + 0x30], eax
00a28d1e e967010000               jmp       0xa28e8a
00a28d23 53                       push      ebx
00a28d24 e8a76ae0ff               call      0x82f7d0
00a28d29 8b7dd4                   mov       edi, dword ptr [ebp - 0x2c]
00a28d2c 3bc3                     cmp       eax, ebx
00a28d2e 8d5594                   lea       edx, [ebp - 0x6c]
00a28d31 0f95c0                   setne     al
00a28d34 6a01                     push      1
00a28d36 52                       push      edx
00a28d37 884718                   mov       byte ptr [edi + 0x18], al
00a28d3a e8a17ae0ff               call      0x8307e0
00a28d3f 83c40c                   add       esp, 0xc
00a28d42 84c0                     test      al, al
00a28d44 0f849d090000             je        0xa296e7
00a28d4a 8d4594                   lea       eax, [ebp - 0x6c]
00a28d4d 68044fe400               push      0xe44f04
00a28d52 50                       push      eax
00a28d53 e818aca0ff               call      0x433970
00a28d58 83c408                   add       esp, 8
00a28d5b 84c0                     test      al, al
00a28d5d 0f8584090000             jne       0xa296e7
00a28d63 53                       push      ebx
00a28d64 e8676ae0ff               call      0x82f7d0
00a28d69 8d4d94                   lea       ecx, [ebp - 0x6c]
00a28d6c 6a01                     push      1
00a28d6e 51                       push      ecx
00a28d6f 894720                   mov       dword ptr [edi + 0x20], eax
00a28d72 e8697ae0ff               call      0x8307e0
00a28d77 83c40c                   add       esp, 0xc
00a28d7a 84c0                     test      al, al
00a28d7c 0f842e090000             je        0xa296b0
00a28d82 8d5594                   lea       edx, [ebp - 0x6c]
00a28d85 68d84ee400               push      0xe44ed8
00a28d8a 52                       push      edx
00a28d8b e8e0aba0ff               call      0x433970
00a28d90 83c408                   add       esp, 8
00a28d93 84c0                     test      al, al
00a28d95 0f8515090000             jne       0xa296b0
00a28d9b 53                       push      ebx
00a28d9c e82f6ae0ff               call      0x82f7d0
00a28da1 89471c                   mov       dword ptr [edi + 0x1c], eax
00a28da4 8d4594                   lea       eax, [ebp - 0x6c]
00a28da7 6a01                     push      1
00a28da9 50                       push      eax
00a28daa e8317ae0ff               call      0x8307e0
00a28daf 83c40c                   add       esp, 0xc
00a28db2 84c0                     test      al, al
00a28db4 0f84b7080000             je        0xa29671
00a28dba 8d4d94                   lea       ecx, [ebp - 0x6c]
00a28dbd 68b44ee400               push      0xe44eb4
00a28dc2 51                       push      ecx
00a28dc3 e8a8aba0ff               call      0x433970
00a28dc8 83c408                   add       esp, 8
00a28dcb 84c0                     test      al, al
00a28dcd 0f859e080000             jne       0xa29671
00a28dd3 53                       push      ebx
00a28dd4 e8f769e0ff               call      0x82f7d0
00a28dd9 33c9                     xor       ecx, ecx
00a28ddb 8ae8                     mov       ch, al
00a28ddd 53                       push      ebx
00a28dde 894d0c                   mov       dword ptr [ebp + 0xc], ecx
00a28de1 e8ea69e0ff               call      0x82f7d0
00a28de6 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00a28de9 8ac8                     mov       cl, al
00a28deb 6a00                     push      0
00a28ded c1e108                   shl       ecx, 8
00a28df0 894d0c                   mov       dword ptr [ebp + 0xc], ecx
00a28df3 e8d869e0ff               call      0x82f7d0
00a28df8 0fb6d0                   movzx     edx, al
00a28dfb 8b450c                   mov       eax, dword ptr [ebp + 0xc]
00a28dfe 0bc2                     or        eax, edx
00a28e00 c1e008                   shl       eax, 8
00a28e03 6a00                     push      0
00a28e05 89450c                   mov       dword ptr [ebp + 0xc], eax
00a28e08 e8c369e0ff               call      0x82f7d0
00a28e0d 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00a28e10 0fb6c0                   movzx     eax, al
00a28e13 0bc8                     or        ecx, eax
00a28e15 894f24                   mov       dword ptr [edi + 0x24], ecx
00a28e18 8d4d94                   lea       ecx, [ebp - 0x6c]
00a28e1b 6a01                     push      1
00a28e1d 51                       push      ecx
00a28e1e e8bd79e0ff               call      0x8307e0
00a28e23 83c418                   add       esp, 0x18
00a28e26 84c0                     test      al, al
00a28e28 0f8443080000             je        0xa29671
00a28e2e 8d5594                   lea       edx, [ebp - 0x6c]
00a28e31 68904ee400               push      0xe44e90
00a28e36 52                       push      edx
00a28e37 e834aba0ff               call      0x433970
00a28e3c 83c408                   add       esp, 8
00a28e3f 84c0                     test      al, al
00a28e41 0f852a080000             jne       0xa29671
00a28e47 8d45b4                   lea       eax, [ebp - 0x4c]
00a28e4a 50                       push      eax
00a28e4b e8c078e0ff               call      0x830710
00a28e50 8d4db4                   lea       ecx, [ebp - 0x4c]
00a28e53 68a4becc00               push      0xccbea4
00a28e58 51                       push      ecx
00a28e59 e872b99dff               call      0x4047d0
00a28e5e 83c40c                   add       esp, 0xc
00a28e61 84c0                     test      al, al
00a28e63 7407                     je        0xa28e6c
00a28e65 33db                     xor       ebx, ebx
00a28e67 895f28                   mov       dword ptr [edi + 0x28], ebx
00a28e6a eb1e                     jmp       0xa28e8a
00a28e6c 8d55b4                   lea       edx, [ebp - 0x4c]
00a28e6f 68844ee400               push      0xe44e84
00a28e74 52                       push      edx
00a28e75 e856b99dff               call      0x4047d0
00a28e7a 83c408                   add       esp, 8
00a28e7d 84c0                     test      al, al
00a28e7f 74                       .byte     0x74
