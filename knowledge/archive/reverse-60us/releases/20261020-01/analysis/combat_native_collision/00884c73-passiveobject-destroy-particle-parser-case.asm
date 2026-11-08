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
