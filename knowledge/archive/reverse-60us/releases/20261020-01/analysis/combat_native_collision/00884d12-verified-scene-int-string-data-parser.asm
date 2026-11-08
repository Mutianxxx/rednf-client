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
