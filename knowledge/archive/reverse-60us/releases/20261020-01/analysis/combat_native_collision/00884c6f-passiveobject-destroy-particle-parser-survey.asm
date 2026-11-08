00884c6f a90c00008d               test      eax, 0x8d00000c
00884c74 4d                       dec       ebp
00884c75 c46810                   les       ebp, ptr [eax + 0x10]
00884c78 34e2                     xor       al, 0xe2
00884c7a 0051e8                   add       byte ptr [ecx - 0x18], dl
00884c7d 4f                       dec       edi
00884c7e fb                       sti       
00884c7f b7ff                     mov       bh, 0xff
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
00884d5f e8                       .byte     0xe8
