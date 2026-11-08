00884b00 0884c074118d46           or        byte ptr [eax + eax*8 + 0x468d1174], al
00884b07 48                       dec       eax
00884b08 50                       push      eax
00884b09 e8d2b9faff               call      0x8304e0
00884b0e 83c404                   add       esp, 4
00884b11 e9060e0000               jmp       0x88591c
00884b16 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884b19 68e434e200               push      0xe234e4
00884b1e 51                       push      ecx
00884b1f e8acfcb7ff               call      0x4047d0
00884b24 83c408                   add       esp, 8
00884b27 84c0                     test      al, al
00884b29 7411                     je        0x884b3c
00884b2b 8d565c                   lea       edx, [esi + 0x5c]
00884b2e 52                       push      edx
00884b2f e8acb9faff               call      0x8304e0
00884b34 83c404                   add       esp, 4
00884b37 e9e00d0000               jmp       0x88591c
00884b3c 8d45c4                   lea       eax, [ebp - 0x3c]
00884b3f 68c834e200               push      0xe234c8
00884b44 50                       push      eax
00884b45 e886fcb7ff               call      0x4047d0
00884b4a 83c408                   add       esp, 8
00884b4d 84c0                     test      al, al
00884b4f 743f                     je        0x884b90
00884b51 8d7e4c                   lea       edi, [esi + 0x4c]
00884b54 8bcf                     mov       ecx, edi
00884b56 e8d5eab7ff               call      0x403630
00884b5b 8d4df0                   lea       ecx, [ebp - 0x10]
00884b5e 51                       push      ecx
00884b5f e87cb9faff               call      0x8304e0
00884b64 83c404                   add       esp, 4
00884b67 84c0                     test      al, al
00884b69 0f84ad0d0000             je        0x88591c
00884b6f 90                       nop       
00884b70 8d55f0                   lea       edx, [ebp - 0x10]
00884b73 52                       push      edx
00884b74 8bcf                     mov       ecx, edi
00884b76 e865f0b7ff               call      0x403be0
00884b7b 8d45f0                   lea       eax, [ebp - 0x10]
00884b7e 50                       push      eax
00884b7f e85cb9faff               call      0x8304e0
00884b84 83c404                   add       esp, 4
00884b87 84c0                     test      al, al
00884b89 75e5                     jne       0x884b70
00884b8b e98c0d0000               jmp       0x88591c
00884b90 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884b93 68a834e200               push      0xe234a8
00884b98 51                       push      ecx
00884b99 e832fcb7ff               call      0x4047d0
00884b9e 83c408                   add       esp, 8
00884ba1 84c0                     test      al, al
00884ba3 741a                     je        0x884bbf
00884ba5 57                       push      edi
00884ba6 e825acfaff               call      0x82f7d0
00884bab 83c404                   add       esp, 4
00884bae 83f801                   cmp       eax, 1
00884bb1 0f85650d0000             jne       0x88591c
00884bb7 884660                   mov       byte ptr [esi + 0x60], al
00884bba e95d0d0000               jmp       0x88591c
00884bbf 8d55c4                   lea       edx, [ebp - 0x3c]
00884bc2 687034e200               push      0xe23470
00884bc7 52                       push      edx
00884bc8 e803fcb7ff               call      0x4047d0
00884bcd 83c408                   add       esp, 8
00884bd0 84c0                     test      al, al
00884bd2 741b                     je        0x884bef
00884bd4 57                       push      edi
00884bd5 e8f6abfaff               call      0x82f7d0
00884bda 83c404                   add       esp, 4
00884bdd 83f801                   cmp       eax, 1
00884be0 0f94c0                   sete      al
00884be3 c6466901                 mov       byte ptr [esi + 0x69], 1
00884be7 884668                   mov       byte ptr [esi + 0x68], al
00884bea e92d0d0000               jmp       0x88591c
00884bef 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884bf2 68a403e200               push      0xe203a4
00884bf7 51                       push      ecx
00884bf8 e8d3fbb7ff               call      0x4047d0
00884bfd 83c408                   add       esp, 8
00884c00 84c0                     test      al, al
00884c02 741a                     je        0x884c1e
00884c04 57                       push      edi
00884c05 e8c6abfaff               call      0x82f7d0
00884c0a 83c404                   add       esp, 4
00884c0d 83f801                   cmp       eax, 1
00884c10 0f85060d0000             jne       0x88591c
00884c16 884662                   mov       byte ptr [esi + 0x62], al
00884c19 e9fe0c0000               jmp       0x88591c
00884c1e 8d55c4                   lea       edx, [ebp - 0x3c]
00884c21 684834e200               push      0xe23448
00884c26 52                       push      edx
00884c27 e8a4fbb7ff               call      0x4047d0
00884c2c 83c408                   add       esp, 8
00884c2f 84c0                     test      al, al
00884c31 741a                     je        0x884c4d
00884c33 57                       push      edi
00884c34 e897abfaff               call      0x82f7d0
00884c39 83c404                   add       esp, 4
00884c3c 83f801                   cmp       eax, 1
00884c3f 0f85d70c0000             jne       0x88591c
00884c45 88466a                   mov       byte ptr [esi + 0x6a], al
00884c48 e9cf0c0000               jmp       0x88591c
00884c4d 8d45c4                   lea       eax, [ebp - 0x3c]
00884c50 683834e200               push      0xe23438
00884c55 50                       push      eax
00884c56 e875fbb7ff               call      0x4047d0
00884c5b 83c408                   add       esp, 8
00884c5e 84c0                     test      al, al
00884c60 7411                     je        0x884c73
00884c62 57                       push      edi
00884c63 e868abfaff               call      0x82f7d0
00884c68 83c404                   add       esp, 4
00884c6b 894664                   mov       dword ptr [esi + 0x64], eax
00884c6e e9a90c0000               jmp       0x88591c
00884c73 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884c76 681034e200               push      0xe23410
00884c7b 51                       push      ecx
00884c7c e84ffbb7ff               call      0x4047d0
00884c81 83c408                   add       esp, 8
00884c84 84c0                     test      al, al
00884c86 7411                     je        0x884c99
00884c88 8d566c                   lea       edx, [esi + 0x6c]
00884c8b 52                       push      edx
00884c8c e84fb8faff               call      0x8304e0
00884c91 83c404                   add       esp, 4
00884c94 e9830c0000               jmp       0x88591c
00884c99 8d45c4                   lea       eax, [ebp - 0x3c]
00884c9c 685cf1e100               push      0xe1f15c
00884ca1 50                       push      eax
00884ca2 e829fbb7ff               call      0x4047d0
00884ca7 83c408                   add       esp, 8
00884caa 84c0                     test      al, al
00884cac 7411                     je        0x884cbf
00884cae 8d4e70                   lea       ecx, [esi + 0x70]
00884cb1 51                       push      ecx
00884cb2 e829b8faff               call      0x8304e0
00884cb7 83c404                   add       esp, 4
00884cba e95d0c0000               jmp       0x88591c
00884cbf 8d55c4                   lea       edx, [ebp - 0x3c]
00884cc2 68ec33e200               push      0xe233ec
00884cc7 52                       push      edx
00884cc8 e803fbb7ff               call      0x4047d0
00884ccd 83c408                   add       esp, 8
00884cd0 84c0                     test      al, al
00884cd2 743e                     je        0x884d12
00884cd4 8d7e74                   lea       edi, [esi + 0x74]
00884cd7 8bcf                     mov       ecx, edi
00884cd9 e852e9b7ff               call      0x403630
00884cde 8d45f0                   lea       eax, [ebp - 0x10]
00884ce1 50                       push      eax
00884ce2 e8f9b7faff               call      0x8304e0
00884ce7 83c404                   add       esp, 4
00884cea 84c0                     test      al, al
00884cec 0f842a0c0000             je        0x88591c
00884cf2 8d4df0                   lea       ecx, [ebp - 0x10]
00884cf5 51                       push      ecx
00884cf6 8bcf                     mov       ecx, edi
00884cf8 e8e3eeb7ff               call      0x403be0
00884cfd 8d55f0                   lea       edx, [ebp - 0x10]
00884d00 52                       push      edx
00884d01 e8dab7faff               call      0x8304e0
00884d06 83c404                   add       esp, 4
00884d09 84c0                     test      al, al
00884d0b 75e5                     jne       0x884cf2
00884d0d e90a0c0000               jmp       0x88591c
00884d12 8d45c4                   lea       eax, [ebp - 0x3c]
00884d15 68e8d8e100               push      0xe1d8e8
00884d1a 50                       push      eax
00884d1b e8b0fab7ff               call      0x4047d0
00884d20 83c408                   add       esp, 8
00884d23 84c0                     test      al, al
00884d25 744f                     je        0x884d76
00884d27 8dbe84000000             lea       edi, [esi + 0x84]
00884d2d 8bcf                     mov       ecx, edi
00884d2f e81c00dcff               call      0x644d50
00884d34 8d4deb                   lea       ecx, [ebp - 0x15]
00884d37 51                       push      ecx
00884d38 e893aafaff               call      0x82f7d0
00884d3d 8945ec                   mov       dword ptr [ebp - 0x14], eax
00884d40 8a45eb                   mov       al, byte ptr [ebp - 0x15]
00884d43 83c404                   add       esp, 4
00884d46 84c0                     test      al, al
00884d48 0f84ce0b0000             je        0x88591c
00884d4e 8bff                     mov       edi, edi
00884d50 8d55ec                   lea       edx, [ebp - 0x14]
00884d53 52                       push      edx
00884d54 8bcf                     mov       ecx, edi
00884d56 e8c523b8ff               call      0x407120
00884d5b 8d45eb                   lea       eax, [ebp - 0x15]
00884d5e 50                       push      eax
00884d5f e86caafaff               call      0x82f7d0
00884d64 8945ec                   mov       dword ptr [ebp - 0x14], eax
00884d67 8a45eb                   mov       al, byte ptr [ebp - 0x15]
00884d6a 83c404                   add       esp, 4
00884d6d 84c0                     test      al, al
00884d6f 75df                     jne       0x884d50
00884d71 e9a60b0000               jmp       0x88591c
00884d76 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884d79 68ccd8e100               push      0xe1d8cc
00884d7e 51                       push      ecx
00884d7f e84cfab7ff               call      0x4047d0
00884d84 83c408                   add       esp, 8
00884d87 84c0                     test      al, al
00884d89 7445                     je        0x884dd0
00884d8b 8dbe94000000             lea       edi, [esi + 0x94]
00884d91 8bcf                     mov       ecx, edi
00884d93 e898e8b7ff               call      0x403630
00884d98 8d55f0                   lea       edx, [ebp - 0x10]
00884d9b 52                       push      edx
00884d9c e83fb7faff               call      0x8304e0
00884da1 83c404                   add       esp, 4
00884da4 84c0                     test      al, al
00884da6 0f84700b0000             je        0x88591c
00884dac 8d642400                 lea       esp, [esp]
00884db0 8d45f0                   lea       eax, [ebp - 0x10]
00884db3 50                       push      eax
00884db4 8bcf                     mov       ecx, edi
00884db6 e825eeb7ff               call      0x403be0
00884dbb 8d4df0                   lea       ecx, [ebp - 0x10]
00884dbe 51                       push      ecx
00884dbf e81cb7faff               call      0x8304e0
00884dc4 83c404                   add       esp, 4
00884dc7 84c0                     test      al, al
00884dc9 75e5                     jne       0x884db0
00884dcb e94c0b0000               jmp       0x88591c
00884dd0 8d55c4                   lea       edx, [ebp - 0x3c]
00884dd3 68d033e200               push      0xe233d0
00884dd8 52                       push      edx
00884dd9 e8f2f9b7ff               call      0x4047d0
00884dde 83c408                   add       esp, 8
00884de1 84c0                     test      al, al
00884de3 746c                     je        0x884e51
00884de5 8d45f0                   lea       eax, [ebp - 0x10]
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
00884e3c 0f                       .byte     0x0f
00884e3d 84da                     test      dl, bl
00884e3f 0a                       .byte     0x0a
