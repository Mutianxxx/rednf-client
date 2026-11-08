008c4d73 8b06                     mov       eax, dword ptr [esi]
008c4d75 8d4d0c                   lea       ecx, [ebp + 0xc]
008c4d78 33db                     xor       ebx, ebx
008c4d7a 51                       push      ecx
008c4d7b 8bce                     mov       ecx, esi
008c4d7d 895d0c                   mov       dword ptr [ebp + 0xc], ebx
008c4d80 895d08                   mov       dword ptr [ebp + 8], ebx
008c4d83 ff5054                   call      dword ptr [eax + 0x54]
008c4d86 8b16                     mov       edx, dword ptr [esi]
008c4d88 8d4508                   lea       eax, [ebp + 8]
008c4d8b 50                       push      eax
008c4d8c 8bce                     mov       ecx, esi
008c4d8e ff5254                   call      dword ptr [edx + 0x54]
008c4d91 8bb660a01000             mov       esi, dword ptr [esi + 0x10a060]
008c4d97 3bf3                     cmp       esi, ebx
008c4d99 0f84b1100000             je        0x8c5e50
008c4d9f 8b8eb0000000             mov       ecx, dword ptr [esi + 0xb0]
008c4da5 3bcb                     cmp       ecx, ebx
008c4da7 0f84a3100000             je        0x8c5e50
008c4dad 0fb75508                 movzx     edx, word ptr [ebp + 8]
008c4db1 0fb7450c                 movzx     eax, word ptr [ebp + 0xc]
008c4db5 52                       push      edx
008c4db6 50                       push      eax
008c4db7 e8646ac4ff               call      0x50b820
008c4dbc 8bf0                     mov       esi, eax
008c4dbe 3bf3                     cmp       esi, ebx
008c4dc0 0f848a100000             je        0x8c5e50
008c4dc6 8b16                     mov       edx, dword ptr [esi]
008c4dc8 53                       push      ebx
008c4dc9 8bce                     mov       ecx, esi
008c4dcb ff5260                   call      dword ptr [edx + 0x60]
008c4dce 8b06                     mov       eax, dword ptr [esi]
008c4dd0 6811020000               push      0x211
008c4dd5 8bce                     mov       ecx, esi
008c4dd7 ff502c                   call      dword ptr [eax + 0x2c]
008c4dda 3c01                     cmp       al, 1
008c4ddc 7537                     jne       0x8c4e15
008c4dde 8d8e08020000             lea       ecx, [esi + 0x208]
008c4de4 e807e31800               call      0xa530f0
008c4de9 0fb74d08                 movzx     ecx, word ptr [ebp + 8]
008c4ded 51                       push      ecx
008c4dee 50                       push      eax
008c4def 68240fe300               push      0xe30f24
008c4df4 68500ee300               push      0xe30e50
008c4df9 ff15bc2eff00             call      dword ptr [0xff2ebc]
008c4dff 83c410                   add       esp, 0x10
008c4e02 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
008c4e05 64890d00000000           mov       dword ptr fs:[0], ecx
008c4e0c 5f                       pop       edi
008c4e0d 5e                       pop       esi
008c4e0e 5b                       pop       ebx
008c4e0f 8be5                     mov       esp, ebp
008c4e11 5d                       pop       ebp
008c4e12 c20c00                   ret       0xc
008c4e15 8b16                     mov       edx, dword ptr [esi]
008c4e17 6a21                     push      0x21
008c4e19 8bce                     mov       ecx, esi
008c4e1b ff522c                   call      dword ptr [edx + 0x2c]
008c4e1e 84c0                     test      al, al
008c4e20 0f842a100000             je        0x8c5e50
008c4e26 8b0d64310001             mov       ecx, dword ptr [0x1003164]
008c4e2c 8b01                     mov       eax, dword ptr [ecx]
008c4e2e 8bb668080000             mov       esi, dword ptr [esi + 0x868]
008c4e34 ff9088000000             call      dword ptr [eax + 0x88]
008c4e3a 8bb8b4000000             mov       edi, dword ptr [eax + 0xb4]
008c4e40 56                       push      esi
008c4e41 e8da39bcff               call      0x488820
008c4e46 8b4f34                   mov       ecx, dword ptr [edi + 0x34]
008c4e49 50                       push      eax
008c4e4a 51                       push      ecx
008c4e4b 8b0d84310001             mov       ecx, dword ptr [0x1003184]
008c4e51 e83ad9c7ff               call      0x542790
008c4e56 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
008c4e59 64890d00000000           mov       dword ptr fs:[0], ecx
008c4e60 5f                       pop       edi
008c4e61 5e                       pop       esi
008c4e62 5b                       pop       ebx
008c4e63 8be5                     mov       esp, ebp
008c4e65 5d                       pop       ebp
008c4e66 c20c00                   ret       0xc
008c4e69 8b16                     mov       edx, dword ptr [esi]
008c4e6b 33db                     xor       ebx, ebx
008c4e6d 8d4510                   lea       eax, [ebp + 0x10]
008c4e70 50                       push      eax
008c4e71 8bce                     mov       ecx, esi
008c4e73 895d10                   mov       dword ptr [ebp + 0x10], ebx
008c4e76 895d0c                   mov       dword ptr [ebp + 0xc], ebx
008c4e79 895d08                   mov       dword ptr [ebp + 8], ebx
008c4e7c 895dec                   mov       dword ptr [ebp - 0x14], ebx
008c4e7f ff5254                   call      dword ptr [edx + 0x54]
008c4e82 8b16                     mov       edx, dword ptr [esi]
008c4e84 8d450c                   lea       eax, [ebp + 0xc]
008c4e87 50                       push      eax
008c4e88 8bce                     mov       ecx, esi
008c4e8a ff5254                   call      dword ptr [edx + 0x54]
008c4e8d 8b16                     mov       edx, dword ptr [esi]
008c4e8f 8d4508                   lea       eax, [ebp + 8]
008c4e92 50                       push      eax
008c4e93 8bce                     mov       ecx, esi
008c4e95 ff525c                   call      dword ptr [edx + 0x5c]
008c4e98 8b16                     mov       edx, dword ptr [esi]
008c4e9a 8d45ec                   lea       eax, [ebp - 0x14]
008c4e9d 50                       push      eax
008c4e9e 8bce                     mov       ecx, esi
008c4ea0 ff525c                   call      dword ptr [edx + 0x5c]
008c4ea3 8bb660a01000             mov       esi, dword ptr [esi + 0x10a060]
008c4ea9 3bf3                     cmp       esi, ebx
008c4eab 0f849f0f0000             je        0x8c5e50
008c4eb1 8b8eb0000000             mov       ecx, dword ptr [esi + 0xb0]
008c4eb7 3bcb                     cmp       ecx, ebx
008c4eb9 0f84910f0000             je        0x8c5e50
008c4ebf 0fb7550c                 movzx     edx, word ptr [ebp + 0xc]
008c4ec3 0fb74510                 movzx     eax, word ptr [ebp + 0x10]
008c4ec7 53                       push      ebx
008c4ec8 686c52f500               push      0xf5526c
008c4ecd 681009f400               push      0xf40910
008c4ed2 53                       push      ebx
008c4ed3 52                       push      edx
008c4ed4 50                       push      eax
008c4ed5 e84669c4ff               call      0x50b820
008c4eda 50                       push      eax
008c4edb e82bbe3300               call      0xc00d0b
008c4ee0 8bf8                     mov       edi, eax
008c4ee2 83c414                   add       esp, 0x14
008c4ee5 3bfb                     cmp       edi, ebx
008c4ee7 0f84630f0000             je        0x8c5e50
008c4eed 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008c4ef0 6a01                     push      1
008c4ef2 53                       push      ebx
008c4ef3 53                       push      ebx
008c4ef4 6aff                     push      -1
008c4ef6 53                       push      ebx
008c4ef7 53                       push      ebx
008c4ef8 6a01                     push      1
008c4efa 51                       push      ecx
008c4efb e820a5cbff               call      0x57f420
008c4f00 8bf0                     mov       esi, eax
008c4f02 83c420                   add       esp, 0x20
008c4f05 3bf3                     cmp       esi, ebx
008c4f07 7427                     je        0x8c4f30
008c4f09 8b16                     mov       edx, dword ptr [esi]
008c4f0b 6a01                     push      1
008c4f0d 8bce                     mov       ecx, esi
008c4f0f ff5218                   call      dword ptr [edx + 0x18]
008c4f12 84c0                     test      al, al
008c4f14 7411                     je        0x8c4f27
008c4f16 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
008c4f19 8b06                     mov       eax, dword ptr [esi]
008c4f1b 51                       push      ecx
008c4f1c 6a01                     push      1
008c4f1e 57                       push      edi
008c4f1f 8bce                     mov       ecx, esi
008c4f21 ff90b4000000             call      dword ptr [eax + 0xb4]
008c4f27 8b16                     mov       edx, dword ptr [esi]
008c4f29 6a01                     push      1
008c4f2b 8bce                     mov       ecx, esi
008c4f2d ff5208                   call      dword ptr [edx + 8]
008c4f30 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008c4f33 8b07                     mov       eax, dword ptr [edi]
008c4f35 51                       push      ecx
008c4f36 8bcf                     mov       ecx, edi
008c4f38 ff9080040000             call      dword ptr [eax + 0x480]
008c4f3e 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
008c4f41 64890d00000000           mov       dword ptr fs:[0], ecx
008c4f48 5f                       pop       edi
008c4f49 5e                       pop       esi
008c4f4a 5b                       pop       ebx
008c4f4b 8be5                     mov       esp, ebp
008c4f4d 5d                       pop       ebp
008c4f4e c20c00                   ret       0xc
008c4f51 8b16                     mov       edx, dword ptr [esi]
008c4f53 33db                     xor       ebx, ebx
008c4f55 8d45f0                   lea       eax, [ebp - 0x10]
008c4f58 50                       push      eax
008c4f59 8bce                     mov       ecx, esi
008c4f5b 885d0b                   mov       byte ptr [ebp + 0xb], bl
008c4f5e 885d0f                   mov       byte ptr [ebp + 0xf], bl
008c4f61 895df0                   mov       dword ptr [ebp - 0x10], ebx
008c4f64 895dec                   mov       dword ptr [ebp - 0x14], ebx
008c4f67 895dc8                   mov       dword ptr [ebp - 0x38], ebx
008c4f6a ff5254                   call      dword ptr [edx + 0x54]
008c4f6d 8b16                     mov       edx, dword ptr [esi]
008c4f6f 8d45ec                   lea       eax, [ebp - 0x14]
008c4f72 50                       push      eax
008c4f73 8bce                     mov       ecx, esi
008c4f75 ff5254                   call      dword ptr [edx + 0x54]
008c4f78 8b16                     mov       edx, dword ptr [esi]
008c4f7a 8d450b                   lea       eax, [ebp + 0xb]
008c4f7d 50                       push      eax
008c4f7e 8bce                     mov       ecx, esi
008c4f80 ff5250                   call      dword ptr [edx + 0x50]
008c4f83 8b16                     mov       edx, dword ptr [esi]
008c4f85 8d450f                   lea       eax, [ebp + 0xf]
008c4f88 50                       push      eax
008c4f89 8bce                     mov       ecx, esi
008c4f8b ff5250                   call      dword ptr [edx + 0x50]
008c4f8e 8b16                     mov       edx, dword ptr [esi]
008c4f90 8d45c8                   lea       eax, [ebp - 0x38]
008c4f93 50                       push      eax
008c4f94 8bce                     mov       ecx, esi
008c4f96 ff525c                   call      dword ptr [edx + 0x5c]
008c4f99 8b16                     mov       edx, dword ptr [esi]
008c4f9b 8d4513                   lea       eax, [ebp + 0x13]
008c4f9e 50                       push      eax
008c4f9f 8bce                     mov       ecx, esi
008c4fa1 88                       .byte     0x88
008c4fa2 5d                       pop       ebp
