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
