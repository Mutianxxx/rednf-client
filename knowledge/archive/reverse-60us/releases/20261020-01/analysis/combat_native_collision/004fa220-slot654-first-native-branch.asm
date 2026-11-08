004fa220 0000                     add       byte ptr [eax], al
004fa222 84c0                     test      al, al
004fa224 0f8513060000             jne       0x4fa83d
004fa22a 8b06                     mov       eax, dword ptr [esi]
004fa22c ff90a0050000             call      dword ptr [eax + 0x5a0]
004fa232 84c0                     test      al, al
004fa234 0f849e000000             je        0x4fa2d8
004fa23a 8b16                     mov       edx, dword ptr [esi]
004fa23c 8bce                     mov       ecx, esi
004fa23e ff92a0030000             call      dword ptr [edx + 0x3a0]
004fa244 85c0                     test      eax, eax
004fa246 8b06                     mov       eax, dword ptr [esi]
004fa248 8bce                     mov       ecx, esi
004fa24a 7440                     je        0x4fa28c
004fa24c ff90a0030000             call      dword ptr [eax + 0x3a0]
004fa252 398648010000             cmp       dword ptr [esi + 0x148], eax
004fa258 747e                     je        0x4fa2d8
004fa25a 8d8e04170000             lea       ecx, [esi + 0x1704]
004fa260 e8fb7df0ff               call      0x402060
004fa265 8b16                     mov       edx, dword ptr [esi]
004fa267 50                       push      eax
004fa268 8bce                     mov       ecx, esi
004fa26a ff92a0030000             call      dword ptr [edx + 0x3a0]
004fa270 8bc8                     mov       ecx, eax
004fa272 e839635300               call      0xa305b0
004fa277 8b3e                     mov       edi, dword ptr [esi]
004fa279 8bce                     mov       ecx, esi
004fa27b ff97a0030000             call      dword ptr [edi + 0x3a0]
004fa281 50                       push      eax
004fa282 8bce                     mov       ecx, esi
004fa284 ff9700010000             call      dword ptr [edi + 0x100]
004fa28a eb4c                     jmp       0x4fa2d8
004fa28c ff9078030000             call      dword ptr [eax + 0x378]
004fa292 85c0                     test      eax, eax
004fa294 7442                     je        0x4fa2d8
004fa296 8b16                     mov       edx, dword ptr [esi]
004fa298 8bce                     mov       ecx, esi
004fa29a ff9278030000             call      dword ptr [edx + 0x378]
004fa2a0 398604010000             cmp       dword ptr [esi + 0x104], eax
004fa2a6 7430                     je        0x4fa2d8
004fa2a8 8d8e04170000             lea       ecx, [esi + 0x1704]
004fa2ae e8ad7df0ff               call      0x402060
004fa2b3 50                       push      eax
004fa2b4 8b06                     mov       eax, dword ptr [esi]
004fa2b6 8bce                     mov       ecx, esi
004fa2b8 ff9078030000             call      dword ptr [eax + 0x378]
004fa2be 8bc8                     mov       ecx, eax
004fa2c0 e8abd55200               call      0xa27870
004fa2c5 8b3e                     mov       edi, dword ptr [esi]
004fa2c7 8bce                     mov       ecx, esi
004fa2c9 ff9778030000             call      dword ptr [edi + 0x378]
004fa2cf 50                       push      eax
004fa2d0 8bce                     mov       ecx, esi
004fa2d2 ff97f0000000             call      dword ptr [edi + 0xf0]
004fa2d8 8b16                     mov       edx, dword ptr [esi]
004fa2da 8bce                     mov       ecx, esi
004fa2dc ff92d0050000             call      dword ptr [edx + 0x5d0]
