004afd90 55                       push      ebp
004afd91 8bec                     mov       ebp, esp
004afd93 83ec10                   sub       esp, 0x10
004afd96 53                       push      ebx
004afd97 56                       push      esi
004afd98 8bf1                     mov       esi, ecx
004afd9a 8b8edc120000             mov       ecx, dword ptr [esi + 0x12dc]
004afda0 85c9                     test      ecx, ecx
004afda2 57                       push      edi
004afda3 7405                     je        0x4afdaa
004afda5 e8066e0000               call      0x4b6bb0
004afdaa 8b06                     mov       eax, dword ptr [esi]
004afdac 8bce                     mov       ecx, esi
004afdae ff90f4040000             call      dword ptr [eax + 0x4f4]
004afdb4 84c0                     test      al, al
004afdb6 0f846b020000             je        0x4b0027
004afdbc 33db                     xor       ebx, ebx
004afdbe 8d8e88180000             lea       ecx, [esi + 0x1888]
004afdc4 895dfc                   mov       dword ptr [ebp - 4], ebx
004afdc7 8d7e60                   lea       edi, [esi + 0x60]
004afdca e89122f5ff               call      0x402060
004afdcf 8bcf                     mov       ecx, edi
004afdd1 8945f0                   mov       dword ptr [ebp - 0x10], eax
004afdd4 e827716500               call      0xb06f00
004afdd9 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004afddc 2bc1                     sub       eax, ecx
004afdde 3de8030000               cmp       eax, 0x3e8
004afde3 7f1e                     jg        0x4afe03
004afde5 68e8030000               push      0x3e8
004afdea 50                       push      eax
004afdeb 53                       push      ebx
004afdec 6800007f43               push      0x437f0000
004afdf1 e8ba9b6500               call      0xb099b0
004afdf6 83c410                   add       esp, 0x10
004afdf9 e846177500               call      0xc01544
004afdfe 8945fc                   mov       dword ptr [ebp - 4], eax
004afe01 8bd8                     mov       ebx, eax
004afe03 8b16                     mov       edx, dword ptr [esi]
004afe05 8bce                     mov       ecx, esi
004afe07 ff92f4000000             call      dword ptr [edx + 0xf4]
004afe0d 85c0                     test      eax, eax
004afe0f 7477                     je        0x4afe88
004afe11 8b06                     mov       eax, dword ptr [esi]
004afe13 8bce                     mov       ecx, esi
004afe15 ff90f4000000             call      dword ptr [eax + 0xf4]
004afe1b 8bc8                     mov       ecx, eax
004afe1d e83e815700               call      0xa27f60
004afe22 3935d4f10401             cmp       dword ptr [0x104f1d4], esi
004afe28 742d                     je        0x4afe57
004afe2a 8b16                     mov       edx, dword ptr [esi]
004afe2c 8bce                     mov       ecx, esi
004afe2e ff92c4010000             call      dword ptr [edx + 0x1c4]
004afe34 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
004afe3a 8bf8                     mov       edi, eax
004afe3c 8b01                     mov       eax, dword ptr [ecx]
004afe3e ff90c4010000             call      dword ptr [eax + 0x1c4]
004afe44 3bf8                     cmp       edi, eax
004afe46 740f                     je        0x4afe57
004afe48 0fb6cb                   movzx     ecx, bl
004afe4b c1e118                   shl       ecx, 0x18
004afe4e 81c9ffffff00             or        ecx, 0xffffff
004afe54 51                       push      ecx
004afe55 eb1b                     jmp       0x4afe72
004afe57 81fb80000000             cmp       ebx, 0x80
004afe5d 8bc3                     mov       eax, ebx
004afe5f 7f05                     jg        0x4afe66
004afe61 b880000000               mov       eax, 0x80
004afe66 0fb6c0                   movzx     eax, al
004afe69 c1e018                   shl       eax, 0x18
004afe6c 0dffffff00               or        eax, 0xffffff
004afe71 50                       push      eax
004afe72 8b16                     mov       edx, dword ptr [esi]
004afe74 8bce                     mov       ecx, esi
004afe76 68000000ff               push      0xff000000
004afe7b ff92f4000000             call      dword ptr [edx + 0xf4]
004afe81 8bc8                     mov       ecx, eax
004afe83 e848595700               call      0xa257d0
004afe88 8b06                     mov       eax, dword ptr [esi]
004afe8a 8bce                     mov       ecx, esi
004afe8c ff9004010000             call      dword ptr [eax + 0x104]
004afe92 85c0                     test      eax, eax
004afe94 0f845b010000             je        0x4afff5
004afe9a 8b16                     mov       edx, dword ptr [esi]
004afe9c 8bce                     mov       ecx, esi
004afe9e ff9204010000             call      dword ptr [edx + 0x104]
004afea4 8b5028                   mov       edx, dword ptr [eax + 0x28]
004afea7 83c024                   add       eax, 0x24
004afeaa 85d2                     test      edx, edx
004afeac 0f8443010000             je        0x4afff5
004afeb2 8b4808                   mov       ecx, dword ptr [eax + 8]
004afeb5 2bca                     sub       ecx, edx
004afeb7 b8abaaaa2a               mov       eax, 0x2aaaaaab
004afebc f7e9                     imul      ecx
004afebe c1fa02                   sar       edx, 2
004afec1 8bc2                     mov       eax, edx
004afec3 c1e81f                   shr       eax, 0x1f
004afec6 03c2                     add       eax, edx
004afec8 85c0                     test      eax, eax
004afeca 0f8e25010000             jle       0x4afff5
004afed0 8b06                     mov       eax, dword ptr [esi]
004afed2 8bce                     mov       ecx, esi
004afed4 ff9004010000             call      dword ptr [eax + 0x104]
004afeda 8b5028                   mov       edx, dword ptr [eax + 0x28]
004afedd 83c024                   add       eax, 0x24
004afee0 85d2                     test      edx, edx
004afee2 7504                     jne       0x4afee8
004afee4 33db                     xor       ebx, ebx
004afee6 eb16                     jmp       0x4afefe
004afee8 8b4808                   mov       ecx, dword ptr [eax + 8]
004afeeb 2bca                     sub       ecx, edx
004afeed b8                       .byte     0xb8
004afeee ab                       stosd     dword ptr es:[edi], eax
004afeef aa                       stosb     byte ptr es:[edi], al
