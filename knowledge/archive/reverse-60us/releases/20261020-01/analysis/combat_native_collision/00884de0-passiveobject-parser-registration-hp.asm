00884de0 0884c0746c8d45           or        byte ptr [eax + eax*8 + 0x458d6c74], al
00884de7 f0                       .byte     0xf0
00884de8 50                       push      eax
00884de9 e8f2b6faff               call      0x8304e0
00884dee 83c404                   add       esp, 4
00884df1 68743dcc00               push      0xcc3d74
00884df6 8d4df0                   lea       ecx, [ebp - 0x10]
00884df9 e8f299b8ff               call      0x40e7f0
00884dfe 84c0                     test      al, al
00884e00 740b                     je        0x884e0d
00884e02 89bea8000000             mov       dword ptr [esi + 0xa8], edi
00884e08 e90f0b0000               jmp       0x88591c
00884e0d 68a833e200               push      0xe233a8
00884e12 8d4df0                   lea       ecx, [ebp - 0x10]
00884e15 e8d699b8ff               call      0x40e7f0
00884e1a 84c0                     test      al, al
00884e1c 740f                     je        0x884e2d
00884e1e c786a800000001000000     mov       dword ptr [esi + 0xa8], 1
00884e28 e9ef0a0000               jmp       0x88591c
00884e2d 688833e200               push      0xe23388
00884e32 8d4df0                   lea       ecx, [ebp - 0x10]
00884e35 e8b699b8ff               call      0x40e7f0
00884e3a 84c0                     test      al, al
00884e3c 0f84da0a0000             je        0x88591c
00884e42 c786a800000002000000     mov       dword ptr [esi + 0xa8], 2
00884e4c e9cb0a0000               jmp       0x88591c
00884e51 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884e54 687433e200               push      0xe23374
00884e59 51                       push      ecx
00884e5a e871f9b7ff               call      0x4047d0
00884e5f 83c408                   add       esp, 8
00884e62 84c0                     test      al, al
00884e64 7420                     je        0x884e86
00884e66 57                       push      edi
00884e67 e864a9faff               call      0x82f7d0
00884e6c 83c404                   add       esp, 4
00884e6f 8d55ec                   lea       edx, [ebp - 0x14]
00884e72 52                       push      edx
00884e73 8d8eac000000             lea       ecx, [esi + 0xac]
00884e79 8945ec                   mov       dword ptr [ebp - 0x14], eax
00884e7c e8dff6b7ff               call      0x404560
00884e81 e9960a0000               jmp       0x88591c
00884e86 8d45c4                   lea       eax, [ebp - 0x3c]
00884e89 685833e200               push      0xe23358
00884e8e 50                       push      eax
00884e8f e83cf9b7ff               call      0x4047d0
00884e94 83c408                   add       esp, 8
00884e97 84c0                     test      al, al
00884e99 7417                     je        0x884eb2
00884e9b 57                       push      edi
00884e9c e82fa9faff               call      0x82f7d0
00884ea1 83c404                   add       esp, 4
00884ea4 83f801                   cmp       eax, 1
00884ea7 0f94c1                   sete      cl
00884eaa 884e61                   mov       byte ptr [esi + 0x61], cl
00884ead e96a0a0000               jmp       0x88591c
00884eb2 8d55c4                   lea       edx, [ebp - 0x3c]
00884eb5 682033e200               push      0xe23320
00884eba 52                       push      edx
00884ebb e810f9b7ff               call      0x4047d0
00884ec0 83c408                   add       esp, 8
00884ec3 84c0                     test      al, al
00884ec5 0f8488020000             je        0x885153
00884ecb 8d4de0                   lea       ecx, [ebp - 0x20]
00884ece e82df0b7ff               call      0x403f00
00884ed3 8d45f0                   lea       eax, [ebp - 0x10]
00884ed6 50                       push      eax
00884ed7 c645fc02                 mov       byte ptr [ebp - 4], 2
00884edb e800b6faff               call      0x8304e0
00884ee0 83c404                   add       esp, 4
00884ee3 84c0                     test      al, al
00884ee5 0f8457020000             je        0x885142
00884eeb eb03                     jmp       0x884ef0
00884eed 8d4900                   lea       ecx, [ecx]
00884ef0 68f832e200               push      0xe232f8
00884ef5 8d4df0                   lea       ecx, [ebp - 0x10]
00884ef8 e8f398b8ff               call      0x40e7f0
00884efd 84c0                     test      al, al
00884eff 0f849c000000             je        0x884fa1
00884f05 8d4de0                   lea       ecx, [ebp - 0x20]
00884f08 51                       push      ecx
00884f09 e8d2b5faff               call      0x8304e0
00884f0e 83c404                   add       esp, 4
00884f11 68cc32e200               push      0xe232cc
00884f16 8d4de0                   lea       ecx, [ebp - 0x20]
00884f19 e8d298b8ff               call      0x40e7f0
00884f1e 84c0                     test      al, al
00884f20 740f                     je        0x884f31
00884f22 c786e000000000000000     mov       dword ptr [esi + 0xe0], 0
00884f2c e9fd010000               jmp       0x88512e
00884f31 68a432e200               push      0xe232a4
00884f36 8d4de0                   lea       ecx, [ebp - 0x20]
00884f39 e8b298b8ff               call      0x40e7f0
00884f3e 84c0                     test      al, al
00884f40 740f                     je        0x884f51
00884f42 c786e000000001000000     mov       dword ptr [esi + 0xe0], 1
00884f4c e9dd010000               jmp       0x88512e
00884f51 688832e200               push      0xe23288
00884f56 8d4de0                   lea       ecx, [ebp - 0x20]
00884f59 e89298b8ff               call      0x40e7f0
00884f5e 84c0                     test      al, al
00884f60 741f                     je        0x884f81
00884f62 6a00                     push      0
00884f64 c786e000000002000000     mov       dword ptr [esi + 0xe0], 2
00884f6e e85da8faff               call      0x82f7d0
00884f73 83c404                   add       esp, 4
00884f76 89862c010000             mov       dword ptr [esi + 0x12c], eax
00884f7c e9ad010000               jmp       0x88512e
00884f81 684032e200               push      0xe23240
00884f86 8d4de0                   lea       ecx, [ebp - 0x20]
00884f89 e86298b8ff               call      0x40e7f0
00884f8e f6d8                     neg       al
00884f90 1bc0                     sbb       eax, eax
00884f92 83e004                   and       eax, 4
00884f95 48                       dec       eax
00884f96 8986e0000000             mov       dword ptr [esi + 0xe0], eax
00884f9c e98d010000               jmp       0x88512e
00884fa1 681c32e200               push      0xe2321c
00884fa6 8d4df0                   lea       ecx, [ebp - 0x10]
00884fa9 e84298b8ff               call      0x40e7f0
00884fae 84c0                     test      al, al
00884fb0 744c                     je        0x884ffe
00884fb2 8d55e0                   lea       edx, [ebp - 0x20]
00884fb5 52                       push      edx
00884fb6 e825b5faff               call      0x8304e0
00884fbb 83c404                   add       esp, 4
00884fbe 68fc31e200               push      0xe231fc
00884fc3 8d4de0                   lea       ecx, [ebp - 0x20]
00884fc6 e82598b8ff               call      0x40e7f0
00884fcb 84c0                     test      al, al
00884fcd 740f                     je        0x884fde
00884fcf c786e400000000000000     mov       dword ptr [esi + 0xe4], 0
00884fd9 e950010000               jmp       0x88512e
00884fde 68c031e200               push      0xe231c0
00884fe3 8d4de0                   lea       ecx, [ebp - 0x20]
00884fe6 e80598b8ff               call      0x40e7f0
00884feb f6d8                     neg       al
00884fed 1bc0                     sbb       eax, eax
00884fef 83e002                   and       eax, 2
00884ff2 48                       dec       eax
00884ff3 8986e4000000             mov       dword ptr [esi + 0xe4], eax
00884ff9 e930010000               jmp       0x88512e
00884ffe 686c43e100               push      0xe1436c
00885003 8d4df0                   lea       ecx, [ebp - 0x10]
00885006 e8e597b8ff               call      0x40e7f0
0088500b 84c0                     test      al, al
0088500d 744c                     je        0x88505b
0088500f 8d45e0                   lea       eax, [ebp - 0x20]
00885012 50                       push      eax
00885013 e8c8b4faff               call      0x8304e0
00885018 83c404                   add       esp, 4
0088501b 68fc31e200               push      0xe231fc
00885020 8d4de0                   lea       ecx, [ebp - 0x20]
00885023 e8c897b8ff               call      0x40e7f0
00885028 84c0                     test      al, al
0088502a 740f                     je        0x88503b
0088502c c7863001000000000000     mov       dword ptr [esi + 0x130], 0
00885036 e9f3000000               jmp       0x88512e
0088503b 68c031e200               push      0xe231c0
00885040 8d4de0                   lea       ecx, [ebp - 0x20]
00885043 e8a897b8ff               call      0x40e7f0
00885048 f6d8                     neg       al
0088504a 1bc0                     sbb       eax, eax
0088504c 83e002                   and       eax, 2
0088504f 48                       dec       eax
