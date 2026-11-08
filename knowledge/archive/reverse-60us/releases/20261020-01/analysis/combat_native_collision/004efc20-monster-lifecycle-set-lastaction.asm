004efc20 55                       push      ebp
004efc21 8bec                     mov       ebp, esp
004efc23 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004efc26 53                       push      ebx
004efc27 56                       push      esi
004efc28 8b7508                   mov       esi, dword ptr [ebp + 8]
004efc2b 57                       push      edi
004efc2c 8bf9                     mov       edi, ecx
004efc2e 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efc31 8b9fb0010000             mov       ebx, dword ptr [edi + 0x1b0]
004efc37 50                       push      eax
004efc38 51                       push      ecx
004efc39 56                       push      esi
004efc3a 8bcf                     mov       ecx, edi
004efc3c e82fb7faff               call      0x49b370
004efc41 3bde                     cmp       ebx, esi
004efc43 742c                     je        0x4efc71
004efc45 83fb01                   cmp       ebx, 1
004efc48 7d17                     jge       0x4efc61
004efc4a 83fe01                   cmp       esi, 1
004efc4d 7c22                     jl        0x4efc71
004efc4f 8d8f741d0000             lea       ecx, [edi + 0x1d74]
004efc55 e886736100               call      0xb06fe0
004efc5a 5f                       pop       edi
004efc5b 5e                       pop       esi
004efc5c 5b                       pop       ebx
004efc5d 5d                       pop       ebp
004efc5e c20c00                   ret       0xc
004efc61 83fe01                   cmp       esi, 1
004efc64 7d0b                     jge       0x4efc71
004efc66 8d8f741d0000             lea       ecx, [edi + 0x1d74]
004efc6c e80f746100               call      0xb07080
004efc71 5f                       pop       edi
004efc72 5e                       pop       esi
004efc73 5b                       pop       ebx
004efc74 5d                       pop       ebp
004efc75 c20c00                   ret       0xc
004efc78 cc                       int3      
004efc79 cc                       int3      
004efc7a cc                       int3      
004efc7b cc                       int3      
004efc7c cc                       int3      
004efc7d cc                       int3      
004efc7e cc                       int3      
004efc7f cc                       int3      
004efc80 55                       push      ebp
004efc81 8bec                     mov       ebp, esp
004efc83 56                       push      esi
004efc84 8bf1                     mov       esi, ecx
004efc86 8b06                     mov       eax, dword ptr [esi]
004efc88 ff90a0050000             call      dword ptr [eax + 0x5a0]
004efc8e 84c0                     test      al, al
004efc90 8a4508                   mov       al, byte ptr [ebp + 8]
004efc93 741b                     je        0x4efcb0
004efc95 84c0                     test      al, al
004efc97 7517                     jne       0x4efcb0
004efc99 8b16                     mov       edx, dword ptr [esi]
004efc9b 56                       push      esi
004efc9c 8bce                     mov       ecx, esi
004efc9e ff92c4030000             call      dword ptr [edx + 0x3c4]
004efca4 8bc8                     mov       ecx, eax
004efca6 e8955a0700               call      0x565740
004efcab 5e                       pop       esi
004efcac 5d                       pop       ebp
004efcad c20400                   ret       4
004efcb0 888684010000             mov       byte ptr [esi + 0x184], al
004efcb6 5e                       pop       esi
004efcb7 5d                       pop       ebp
004efcb8 c20400                   ret       4
004efcbb cc                       int3      
004efcbc cc                       int3      
004efcbd cc                       int3      
004efcbe cc                       int3      
004efcbf cc                       int3      
004efcc0 55                       push      ebp
004efcc1 8bec                     mov       ebp, esp
004efcc3 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efcc6 8b4508                   mov       eax, dword ptr [ebp + 8]
004efcc9 3981301a0000             cmp       dword ptr [ecx + 0x1a30], eax
004efccf 741b                     je        0x4efcec
004efcd1 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004efcd4 8991bc1d0000             mov       dword ptr [ecx + 0x1dbc], edx
004efcda 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004efcdd 8991b81d0000             mov       dword ptr [ecx + 0x1db8], edx
004efce3 8b11                     mov       edx, dword ptr [ecx]
004efce5 50                       push      eax
004efce6 ff92f0050000             call      dword ptr [edx + 0x5f0]
004efcec 5d                       pop       ebp
004efced c21000                   ret       0x10
004efcf0 55                       push      ebp
004efcf1 8bec                     mov       ebp, esp
004efcf3 56                       push      esi
004efcf4 8bf1                     mov       esi, ecx
004efcf6 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004efcfc 85c9                     test      ecx, ecx
004efcfe 7507                     jne       0x4efd07
004efd00 32c0                     xor       al, al
004efd02 5e                       pop       esi
004efd03 5d                       pop       ebp
004efd04 c20800                   ret       8
004efd07 8b4508                   mov       eax, dword ptr [ebp + 8]
004efd0a 83f8ff                   cmp       eax, -1
004efd0d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004efd10 0f858d000000             jne       0x4efda3
004efd16 83faff                   cmp       edx, -1
004efd19 0f8584000000             jne       0x4efda3
004efd1f 8b01                     mov       eax, dword ptr [ecx]
004efd21 57                       push      edi
004efd22 ff9094000000             call      dword ptr [eax + 0x94]
004efd28 8b16                     mov       edx, dword ptr [esi]
004efd2a 8bce                     mov       ecx, esi
004efd2c 8bf8                     mov       edi, eax
004efd2e ff9294000000             call      dword ptr [edx + 0x94]
004efd34 3bc7                     cmp       eax, edi
004efd36 8bce                     mov       ecx, esi
004efd38 7d0f                     jge       0x4efd49
004efd3a 8b06                     mov       eax, dword ptr [esi]
004efd3c ff9094000000             call      dword ptr [eax + 0x94]
004efd42 2d2c010000               sub       eax, 0x12c
004efd47 eb0d                     jmp       0x4efd56
004efd49 8b16                     mov       edx, dword ptr [esi]
004efd4b ff9294000000             call      dword ptr [edx + 0x94]
004efd51 052c010000               add       eax, 0x12c
004efd56 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004efd5c 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efd62 8b01                     mov       eax, dword ptr [ecx]
004efd64 ff9098000000             call      dword ptr [eax + 0x98]
004efd6a 8b16                     mov       edx, dword ptr [esi]
004efd6c 8bce                     mov       ecx, esi
004efd6e 8bf8                     mov       edi, eax
004efd70 ff9298000000             call      dword ptr [edx + 0x98]
004efd76 3bc7                     cmp       eax, edi
004efd78 5f                       pop       edi
004efd79 8bce                     mov       ecx, esi
004efd7b 7d13                     jge       0x4efd90
004efd7d 8b06                     mov       eax, dword ptr [esi]
004efd7f ff9098000000             call      dword ptr [eax + 0x98]
004efd85 83c032                   add       eax, 0x32
004efd88 8986b81d0000             mov       dword ptr [esi + 0x1db8], eax
004efd8e eb1f                     jmp       0x4efdaf
004efd90 8b16                     mov       edx, dword ptr [esi]
004efd92 ff9298000000             call      dword ptr [edx + 0x98]
004efd98 83e832                   sub       eax, 0x32
004efd9b 8986b81d0000             mov       dword ptr [esi + 0x1db8], eax
004efda1 eb0c                     jmp       0x4efdaf
004efda3 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efda9 8996b81d0000             mov       dword ptr [esi + 0x1db8], edx
004efdaf 8b06                     mov       eax, dword ptr [esi]
004efdb1 8bce                     mov       ecx, esi
004efdb3 ff9094000000             call      dword ptr [eax + 0x94]
004efdb9 8b16                     mov       edx, dword ptr [esi]
004efdbb 8bce                     mov       ecx, esi
004efdbd 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efdc3 ff9298000000             call      dword ptr [edx + 0x98]
004efdc9 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efdcf 8b06                     mov       eax, dword ptr [esi]
004efdd1 6a06                     push      6
004efdd3 8bce                     mov       ecx, esi
004efdd5 ff90f0050000             call      dword ptr [eax + 0x5f0]
004efddb b001                     mov       al, 1
004efddd 5e                       pop       esi
004efdde 5d                       pop       ebp
004efddf c20800                   ret       8
004efde2 cc                       int3      
004efde3 cc                       int3      
004efde4 cc                       int3      
004efde5 cc                       int3      
004efde6 cc                       int3      
004efde7 cc                       int3      
004efde8 cc                       int3      
004efde9 cc                       int3      
004efdea cc                       int3      
004efdeb cc                       int3      
004efdec cc                       int3      
004efded cc                       int3      
004efdee cc                       int3      
004efdef cc                       int3      
004efdf0 55                       push      ebp
004efdf1 8bec                     mov       ebp, esp
004efdf3 8b4508                   mov       eax, dword ptr [ebp + 8]
004efdf6 56                       push      esi
004efdf7 8bf1                     mov       esi, ecx
004efdf9 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efdfc 8b16                     mov       edx, dword ptr [esi]
004efdfe 898eb81d0000             mov       dword ptr [esi + 0x1db8], ecx
004efe04 8bce                     mov       ecx, esi
004efe06 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efe0c ff9294000000             call      dword ptr [edx + 0x94]
004efe12 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efe18 8b06                     mov       eax, dword ptr [esi]
004efe1a 8bce                     mov       ecx, esi
004efe1c ff9098000000             call      dword ptr [eax + 0x98]
004efe22 8b16                     mov       edx, dword ptr [esi]
004efe24 6a19                     push      0x19
004efe26 8bce                     mov       ecx, esi
004efe28 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efe2e ff92f0050000             call      dword ptr [edx + 0x5f0]
004efe34 5e                       pop       esi
004efe35 5d                       pop       ebp
004efe36 c20800                   ret       8
004efe39 cc                       int3      
004efe3a cc                       int3      
004efe3b cc                       int3      
004efe3c cc                       int3      
004efe3d cc                       int3      
004efe3e cc                       int3      
004efe3f cc                       int3      
004efe40 55                       push      ebp
004efe41 8bec                     mov       ebp, esp
004efe43 8b4508                   mov       eax, dword ptr [ebp + 8]
004efe46 56                       push      esi
004efe47 8bf1                     mov       esi, ecx
004efe49 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efe4c 8b16                     mov       edx, dword ptr [esi]
004efe4e 898eb81d0000             mov       dword ptr [esi + 0x1db8], ecx
004efe54 8bce                     mov       ecx, esi
004efe56 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efe5c ff9294000000             call      dword ptr [edx + 0x94]
004efe62 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efe68 8b06                     mov       eax, dword ptr [esi]
004efe6a 8bce                     mov       ecx, esi
004efe6c ff9098000000             call      dword ptr [eax + 0x98]
004efe72 8b16                     mov       edx, dword ptr [esi]
004efe74 6a1a                     push      0x1a
004efe76 8bce                     mov       ecx, esi
004efe78 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efe7e ff                       .byte     0xff
004efe7f 92                       xchg      edx, eax
