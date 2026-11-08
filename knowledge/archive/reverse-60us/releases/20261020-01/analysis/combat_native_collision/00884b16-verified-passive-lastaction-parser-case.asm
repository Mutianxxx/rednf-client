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
