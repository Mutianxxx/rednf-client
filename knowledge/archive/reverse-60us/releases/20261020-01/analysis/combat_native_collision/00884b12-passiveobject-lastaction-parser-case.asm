00884b12 06                       push      es
00884b13 0e                       push      cs
00884b14 0000                     add       byte ptr [eax], al
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
00884b45 e8                       .byte     0xe8
