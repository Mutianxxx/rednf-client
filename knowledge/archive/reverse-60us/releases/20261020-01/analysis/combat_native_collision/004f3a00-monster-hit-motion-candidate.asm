004f3a00 55                       push      ebp
004f3a01 8bec                     mov       ebp, esp
004f3a03 8b4508                   mov       eax, dword ptr [ebp + 8]
004f3a06 84c0                     test      al, al
004f3a08 56                       push      esi
004f3a09 8bf1                     mov       esi, ecx
004f3a0b 751a                     jne       0x4f3a27
004f3a0d 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004f3a10 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004f3a13 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f3a16 50                       push      eax
004f3a17 51                       push      ecx
004f3a18 52                       push      edx
004f3a19 6a00                     push      0
004f3a1b 8bce                     mov       ecx, esi
004f3a1d e88e71fcff               call      0x4babb0
004f3a22 5e                       pop       esi
004f3a23 5d                       pop       ebp
004f3a24 c21000                   ret       0x10
004f3a27 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004f3a2a 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004f3a2d 51                       push      ecx
004f3a2e 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f3a31 52                       push      edx
004f3a32 51                       push      ecx
004f3a33 50                       push      eax
004f3a34 8bce                     mov       ecx, esi
004f3a36 e87571fcff               call      0x4babb0
004f3a3b 8a8608050000             mov       al, byte ptr [esi + 0x508]
004f3a41 84c0                     test      al, al
004f3a43 0f841c040000             je        0x4f3e65
004f3a49 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f3a4f 84c0                     test      al, al
004f3a51 53                       push      ebx
004f3a52 57                       push      edi
004f3a53 0f840a040000             je        0x4f3e63
004f3a59 6a00                     push      0
004f3a5b 8bce                     mov       ecx, esi
004f3a5d e80e4fffff               call      0x4e8970
004f3a62 84c0                     test      al, al
004f3a64 0f84ed010000             je        0x4f3c57
004f3a6a 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f3a70 85c0                     test      eax, eax
004f3a72 750e                     jne       0x4f3a82
004f3a74 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004f3a7a 85c0                     test      eax, eax
004f3a7c 0f84d5010000             je        0x4f3c57
004f3a82 8b16                     mov       edx, dword ptr [esi]
004f3a84 8bce                     mov       ecx, esi
004f3a86 ff92dc030000             call      dword ptr [edx + 0x3dc]
004f3a8c 84c0                     test      al, al
004f3a8e 0f85c3010000             jne       0x4f3c57
004f3a94 8b06                     mov       eax, dword ptr [esi]
004f3a96 8bce                     mov       ecx, esi
004f3a98 ff9078030000             call      dword ptr [eax + 0x378]
004f3a9e 398604010000             cmp       dword ptr [esi + 0x104], eax
004f3aa4 7516                     jne       0x4f3abc
004f3aa6 8b16                     mov       edx, dword ptr [esi]
004f3aa8 8bce                     mov       ecx, esi
004f3aaa ff92a0030000             call      dword ptr [edx + 0x3a0]
004f3ab0 398648010000             cmp       dword ptr [esi + 0x148], eax
004f3ab6 0f849b010000             je        0x4f3c57
004f3abc 8b06                     mov       eax, dword ptr [esi]
004f3abe 8bce                     mov       ecx, esi
004f3ac0 ff907c030000             call      dword ptr [eax + 0x37c]
004f3ac6 398604010000             cmp       dword ptr [esi + 0x104], eax
004f3acc 7516                     jne       0x4f3ae4
004f3ace 8b16                     mov       edx, dword ptr [esi]
004f3ad0 8bce                     mov       ecx, esi
004f3ad2 ff92a4030000             call      dword ptr [edx + 0x3a4]
004f3ad8 398648010000             cmp       dword ptr [esi + 0x148], eax
004f3ade 0f8473010000             je        0x4f3c57
004f3ae4 6a00                     push      0
004f3ae6 6a00                     push      0
004f3ae8 8d4510                   lea       eax, [ebp + 0x10]
004f3aeb 50                       push      eax
004f3aec 8d4d0c                   lea       ecx, [ebp + 0xc]
004f3aef 51                       push      ecx
004f3af0 e8bb3c0400               call      0x5377b0
004f3af5 8b16                     mov       edx, dword ptr [esi]
004f3af7 83c410                   add       esp, 0x10
004f3afa 8bce                     mov       ecx, esi
004f3afc ff92e4000000             call      dword ptr [edx + 0xe4]
004f3b02 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004f3b05 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3b0b 6a00                     push      0
004f3b0d 2bf8                     sub       edi, eax
004f3b0f 6a3a                     push      0x3a
004f3b11 81ef80000000             sub       edi, 0x80
004f3b17 e8c4366000               call      0xaf71e0
004f3b1c 8bc8                     mov       ecx, eax
004f3b1e e8ade85f00               call      0xaf23d0
004f3b23 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3b29 8b5814                   mov       ebx, dword ptr [eax + 0x14]
004f3b2c 680000804f               push      0x4f800000
004f3b31 680000804f               push      0x4f800000
004f3b36 6aff                     push      -1
004f3b38 6a00                     push      0
004f3b3a 680000803f               push      0x3f800000
004f3b3f 680000803f               push      0x3f800000
004f3b44 6a00                     push      0
004f3b46 6a3a                     push      0x3a
004f3b48 e893366000               call      0xaf71e0
004f3b4d 8bc8                     mov       ecx, eax
004f3b4f e87ce85f00               call      0xaf23d0
004f3b54 8b0d2ca90d01             mov       ecx, dword ptr [0x10da92c]
004f3b5a 50                       push      eax
004f3b5b 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004f3b5e d1eb                     shr       ebx, 1
004f3b60 2bc3                     sub       eax, ebx
004f3b62 57                       push      edi
004f3b63 2d82000000               sub       eax, 0x82
004f3b68 50                       push      eax
004f3b69 e852a46100               call      0xb0dfc0
004f3b6e 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3b74 6a01                     push      1
004f3b76 6a3a                     push      0x3a
004f3b78 e863366000               call      0xaf71e0
004f3b7d 8bc8                     mov       ecx, eax
004f3b7f e84ce85f00               call      0xaf23d0
004f3b84 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004f3b87 8b9604050000             mov       edx, dword ptr [esi + 0x504]
004f3b8d 8b86381a0000             mov       eax, dword ptr [esi + 0x1a38]
004f3b93 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
004f3b96 d1e9                     shr       ecx, 1
004f3b98 8d0490                   lea       eax, [eax + edx*4]
004f3b9b 8b10                     mov       edx, dword ptr [eax]
004f3b9d 2bd9                     sub       ebx, ecx
004f3b9f 8b08                     mov       ecx, dword ptr [eax]
004f3ba1 8b892c010000             mov       ecx, dword ptr [ecx + 0x12c]
004f3ba7 8b821c010000             mov       eax, dword ptr [edx + 0x11c]
004f3bad 51                       push      ecx
004f3bae 50                       push      eax
004f3baf 6a55                     push      0x55
004f3bb1 6a00                     push      0
004f3bb3 e86803f8ff               call      0x473f20
004f3bb8 83c410                   add       esp, 0x10
004f3bbb 8d8ec01a0000             lea       ecx, [esi + 0x1ac0]
004f3bc1 894514                   mov       dword ptr [ebp + 0x14], eax
004f3bc4 e897e4f0ff               call      0x402060
004f3bc9 85c0                     test      eax, eax
004f3bcb 7444                     je        0x4f3c11
004f3bcd 8d8ea81a0000             lea       ecx, [esi + 0x1aa8]
004f3bd3 e828bbf4ff               call      0x43f700
004f3bd8 84c0                     test      al, al
004f3bda 751b                     jne       0x4f3bf7
004f3bdc 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004f3bdf 68e0010000               push      0x1e0
004f3be4 03c3                     add       eax, ebx
004f3be6 50                       push      eax
004f3be7 6a00                     push      0
004f3be9 6a00                     push      0
004f3beb e8d0d8f0ff               call      0x4014c0
004f3bf0 83c410                   add       esp, 0x10
004f3bf3 6a02                     push      2
004f3bf5 eb33                     jmp       0x4f3c2a
004f3bf7 8dbea81a0000             lea       edi, [esi + 0x1aa8]
004f3bfd 8bcf                     mov       ecx, edi
004f3bff e8fcbaf4ff               call      0x43f700
004f3c04 84c0                     test      al, al
004f3c06 744f                     je        0x4f3c57
004f3c08 8bcf                     mov       ecx, edi
004f3c0a e8e112f1ff               call      0x404ef0
004f3c0f eb46                     jmp       0x4f3c57
004f3c11 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004f3c14 68e0010000               push      0x1e0
004f3c19 03cb                     add       ecx, ebx
004f3c1b 51                       push      ecx
004f3c1c 6a00                     push      0
004f3c1e 6a00                     push      0
004f3c20 e89bd8f0ff               call      0x4014c0
004f3c25 83c410                   add       esp, 0x10
004f3c28 6a01                     push      1
004f3c2a 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3c30 6a3a                     push      0x3a
004f3c32 e8a9356000               call      0xaf71e0
004f3c37 8bc8                     mov       ecx, eax
004f3c39 e892e75f00               call      0xaf23d0
004f3c3e 8b0d2ca90d01             mov       ecx, dword ptr [0x10da92c]
004f3c44 50                       push      eax
004f3c45 57                       push      edi
004f3c46 81c379ffffff             add       ebx, 0xffffff79
004f3c4c 53                       push      ebx
004f3c4d e87ea26100               call      0xb0ded0
004f3c52 e8b9d8f0ff               call      0x401510
004f3c57 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f3c5d 84c0                     test      al, al
004f3c5f 0f84fe010000             je        0x4f3e63
004f3c65 6a0d                     push      0xd
004f3c67 8bce                     mov       ecx, esi
004f3c69 e8024dffff               call      0x4e8970
004f3c6e 84c0                     test      al, al
004f3c70 0f84ed010000             je        0x4f3e63
004f3c76 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f3c7c 85c0                     test      eax, eax
004f3c7e 750e                     jne       0x4f3c8e
004f3c80 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004f3c86 85c0                     test      eax, eax
004f3c88 0f84d5010000             je        0x4f3e63
004f3c8e 8b16                     mov       edx, dword ptr [esi]
004f3c90 8bce                     mov       ecx, esi
004f3c92 ff92dc030000             call      dword ptr [edx + 0x3dc]
004f3c98 84c0                     test      al, al
004f3c9a 0f85c3010000             jne       0x4f3e63
004f3ca0 8b06                     mov       eax, dword ptr [esi]
004f3ca2 8bce                     mov       ecx, esi
004f3ca4 ff9078030000             call      dword ptr [eax + 0x378]
004f3caa 398604010000             cmp       dword ptr [esi + 0x104], eax
004f3cb0 7516                     jne       0x4f3cc8
004f3cb2 8b16                     mov       edx, dword ptr [esi]
004f3cb4 8bce                     mov       ecx, esi
004f3cb6 ff92a0030000             call      dword ptr [edx + 0x3a0]
004f3cbc 398648010000             cmp       dword ptr [esi + 0x148], eax
004f3cc2 0f849b010000             je        0x4f3e63
004f3cc8 8b06                     mov       eax, dword ptr [esi]
004f3cca 8bce                     mov       ecx, esi
004f3ccc ff907c030000             call      dword ptr [eax + 0x37c]
004f3cd2 398604010000             cmp       dword ptr [esi + 0x104], eax
004f3cd8 7516                     jne       0x4f3cf0
004f3cda 8b16                     mov       edx, dword ptr [esi]
004f3cdc 8bce                     mov       ecx, esi
004f3cde ff92a4030000             call      dword ptr [edx + 0x3a4]
004f3ce4 398648010000             cmp       dword ptr [esi + 0x148], eax
004f3cea 0f8473010000             je        0x4f3e63
004f3cf0 6a00                     push      0
004f3cf2 6a00                     push      0
004f3cf4 8d4510                   lea       eax, [ebp + 0x10]
004f3cf7 50                       push      eax
004f3cf8 8d4d0c                   lea       ecx, [ebp + 0xc]
004f3cfb 51                       push      ecx
004f3cfc e8af3a0400               call      0x5377b0
004f3d01 8b16                     mov       edx, dword ptr [esi]
004f3d03 83c410                   add       esp, 0x10
004f3d06 8bce                     mov       ecx, esi
004f3d08 ff92e4000000             call      dword ptr [edx + 0xe4]
004f3d0e 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004f3d11 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3d17 6a00                     push      0
004f3d19 2bf8                     sub       edi, eax
004f3d1b 6a3a                     push      0x3a
004f3d1d 81ef80000000             sub       edi, 0x80
004f3d23 e8b8346000               call      0xaf71e0
004f3d28 8bc8                     mov       ecx, eax
004f3d2a e8a1e65f00               call      0xaf23d0
004f3d2f 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3d35 8b5814                   mov       ebx, dword ptr [eax + 0x14]
004f3d38 680000804f               push      0x4f800000
004f3d3d 680000804f               push      0x4f800000
004f3d42 6aff                     push      -1
004f3d44 6a00                     push      0
004f3d46 680000803f               push      0x3f800000
004f3d4b 680000803f               push      0x3f800000
004f3d50 6a00                     push      0
004f3d52 6a3a                     push      0x3a
004f3d54 e887346000               call      0xaf71e0
004f3d59 8bc8                     mov       ecx, eax
004f3d5b e870e65f00               call      0xaf23d0
004f3d60 8b0d2ca90d01             mov       ecx, dword ptr [0x10da92c]
004f3d66 50                       push      eax
004f3d67 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004f3d6a d1eb                     shr       ebx, 1
004f3d6c 2bc3                     sub       eax, ebx
004f3d6e 57                       push      edi
004f3d6f 2d82000000               sub       eax, 0x82
004f3d74 50                       push      eax
004f3d75 e846a26100               call      0xb0dfc0
004f3d7a 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3d80 6a01                     push      1
004f3d82 6a3a                     push      0x3a
004f3d84 e857346000               call      0xaf71e0
004f3d89 8bc8                     mov       ecx, eax
004f3d8b e840e65f00               call      0xaf23d0
004f3d90 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004f3d93 8b9604050000             mov       edx, dword ptr [esi + 0x504]
004f3d99 8b86481a0000             mov       eax, dword ptr [esi + 0x1a48]
004f3d9f 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
004f3da2 d1e9                     shr       ecx, 1
004f3da4 8d0490                   lea       eax, [eax + edx*4]
004f3da7 8b10                     mov       edx, dword ptr [eax]
004f3da9 2bd9                     sub       ebx, ecx
004f3dab 8b08                     mov       ecx, dword ptr [eax]
004f3dad 8b892c010000             mov       ecx, dword ptr [ecx + 0x12c]
004f3db3 8b821c010000             mov       eax, dword ptr [edx + 0x11c]
004f3db9 51                       push      ecx
004f3dba 50                       push      eax
004f3dbb 6a55                     push      0x55
004f3dbd 6a00                     push      0
004f3dbf e85c01f8ff               call      0x473f20
004f3dc4 83c410                   add       esp, 0x10
004f3dc7 8d8ec01a0000             lea       ecx, [esi + 0x1ac0]
004f3dcd 894514                   mov       dword ptr [ebp + 0x14], eax
004f3dd0 e88be2f0ff               call      0x402060
004f3dd5 85c0                     test      eax, eax
004f3dd7 7444                     je        0x4f3e1d
004f3dd9 8d8ea81a0000             lea       ecx, [esi + 0x1aa8]
004f3ddf e81cb9f4ff               call      0x43f700
004f3de4 84c0                     test      al, al
004f3de6 751b                     jne       0x4f3e03
004f3de8 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004f3deb 68e0010000               push      0x1e0
004f3df0 03c3                     add       eax, ebx
004f3df2 50                       push      eax
004f3df3 6a00                     push      0
004f3df5 6a00                     push      0
004f3df7 e8c4d6f0ff               call      0x4014c0
004f3dfc 83c410                   add       esp, 0x10
004f3dff 6a02                     push      2
004f3e01 eb33                     jmp       0x4f3e36
004f3e03 8dbea81a0000             lea       edi, [esi + 0x1aa8]
004f3e09 8bcf                     mov       ecx, edi
004f3e0b e8f0b8f4ff               call      0x43f700
004f3e10 84c0                     test      al, al
004f3e12 744f                     je        0x4f3e63
004f3e14 8bcf                     mov       ecx, edi
004f3e16 e8d510f1ff               call      0x404ef0
004f3e1b eb46                     jmp       0x4f3e63
004f3e1d 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004f3e20 68e0010000               push      0x1e0
004f3e25 03cb                     add       ecx, ebx
004f3e27 51                       push      ecx
004f3e28 6a00                     push      0
004f3e2a 6a00                     push      0
004f3e2c e88fd6f0ff               call      0x4014c0
004f3e31 83c410                   add       esp, 0x10
004f3e34 6a01                     push      1
004f3e36 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004f3e3c 6a3a                     push      0x3a
004f3e3e e89d336000               call      0xaf71e0
004f3e43 8bc8                     mov       ecx, eax
004f3e45 e886e55f00               call      0xaf23d0
004f3e4a 8b0d2ca90d01             mov       ecx, dword ptr [0x10da92c]
004f3e50 50                       push      eax
004f3e51 57                       push      edi
004f3e52 81c379ffffff             add       ebx, 0xffffff79
004f3e58 53                       push      ebx
004f3e59 e872a06100               call      0xb0ded0
004f3e5e e8add6f0ff               call      0x401510
004f3e63 5f                       pop       edi
004f3e64 5b                       pop       ebx
004f3e65 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004f3e68 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f3e6b 8b16                     mov       edx, dword ptr [esi]
004f3e6d 50                       push      eax
004f3e6e 51                       push      ecx
004f3e6f 8bce                     mov       ecx, esi
004f3e71 ff924c050000             call      dword ptr [edx + 0x54c]
004f3e77 5e                       pop       esi
004f3e78 5d                       pop       ebp
004f3e79 c21000                   ret       0x10
004f3e7c cc                       int3      
004f3e7d cc                       int3      
004f3e7e cc                       int3      
004f3e7f cc                       int3      
004f3e80 55                       push      ebp
004f3e81 8bec                     mov       ebp, esp
004f3e83 57                       push      edi
004f3e84 8bf9                     mov       edi, ecx
004f3e86 8b8700010000             mov       eax, dword ptr [edi + 0x100]
004f3e8c 85c0                     test      eax, eax
004f3e8e 0f8492000000             je        0x4f3f26
004f3e94 53                       push      ebx
004f3e95 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
004f3e98 56                       push      esi
004f3e99 33f6                     xor       esi, esi
004f3e9b eb03                     jmp       0x4f3ea0
004f3e9d 8d4900                   lea       ecx, [ecx]
004f3ea0 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f3ea6 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f3ea9 85d2                     test      edx, edx
004f3eab 7504                     jne       0x4f3eb1
004f3ead 33c0                     xor       eax, eax
004f3eaf eb08                     jmp       0x4f3eb9
004f3eb1 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f3eb4 2bc2                     sub       eax, edx
004f3eb6 c1f802                   sar       eax, 2
004f3eb9 3bf0                     cmp       esi, eax
004f3ebb 7d67                     jge       0x4f3f24
004f3ebd 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f3ec0 85d2                     test      edx, edx
004f3ec2 7416                     je        0x4f3eda
004f3ec4 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f3ec7 2bc2                     sub       eax, edx
004f3ec9 c1f802                   sar       eax, 2
004f3ecc 3bf0                     cmp       esi, eax
004f3ece 730a                     jae       0x4f3eda
004f3ed0 8bc2                     mov       eax, edx
004f3ed2 8b0cb0                   mov       ecx, dword ptr [eax + esi*4]
004f3ed5 8d04b0                   lea       eax, [eax + esi*4]
004f3ed8 eb02                     jmp       0x4f3edc
004f3eda 33c9                     xor       ecx, ecx
004f3edc 8b11                     mov       edx, dword ptr [ecx]
004f3ede 6a11                     push      0x11
004f3ee0 ff522c                   call      dword ptr [edx + 0x2c]
004f3ee3 84c0                     test      al, al
004f3ee5 7437                     je        0x4f3f1e
004f3ee7 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f3eed 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f3ef0 85d2                     test      edx, edx
004f3ef2 7416                     je        0x4f3f0a
004f3ef4 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f3ef7 2bc2                     sub       eax, edx
004f3ef9 c1f802                   sar       eax, 2
004f3efc 3bf0                     cmp       esi, eax
004f3efe 730a                     jae       0x4f3f0a
004f3f00 8bc2                     mov       eax, edx
004f3f02 8b0cb0                   mov       ecx, dword ptr [eax + esi*4]
004f3f05 8d04b0                   lea       eax, [eax + esi*4]
004f3f08 eb02                     jmp       0x4f3f0c
004f3f0a 33c9                     xor       ecx, ecx
004f3f0c 3bcf                     cmp       ecx, edi
004f3f0e 740e                     je        0x4f3f1e
004f3f10 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f3f13 8b4508                   mov       eax, dword ptr [ebp + 8]
004f3f16 53                       push      ebx
004f3f17 52                       push      edx
004f3f18 50                       push      eax
004f3f19 e8326e5700               call      0xa6ad50
004f3f1e 46                       inc       esi
004f3f1f e97cffffff               jmp       0x4f3ea0
004f3f24 5e                       pop       esi
004f3f25 5b                       pop       ebx
004f3f26 5f                       pop       edi
004f3f27 5d                       pop       ebp
004f3f28 c20c00                   ret       0xc
004f3f2b cc                       int3      
004f3f2c cc                       int3      
004f3f2d cc                       int3      
004f3f2e cc                       int3      
004f3f2f cc                       int3      
