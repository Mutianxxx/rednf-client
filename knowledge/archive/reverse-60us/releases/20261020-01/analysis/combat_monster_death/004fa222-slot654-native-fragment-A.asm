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
004fa2e2 b90ce6ff00               mov       ecx, 0xffe60c
004fa2e7 e8747df0ff               call      0x402060
004fa2ec 85c0                     test      eax, eax
004fa2ee 0f8509050000             jne       0x4fa7fd
004fa2f4 8a86a8240000             mov       al, byte ptr [esi + 0x24a8]
004fa2fa 84c0                     test      al, al
004fa2fc 0f84fb040000             je        0x4fa7fd
004fa302 8b06                     mov       eax, dword ptr [esi]
004fa304 8bce                     mov       ecx, esi
004fa306 ff90b0050000             call      dword ptr [eax + 0x5b0]
004fa30c 8b4818                   mov       ecx, dword ptr [eax + 0x18]
004fa30f 85c9                     test      ecx, ecx
004fa311 741b                     je        0x4fa32e
004fa313 8b16                     mov       edx, dword ptr [esi]
004fa315 8bce                     mov       ecx, esi
004fa317 ff92b0050000             call      dword ptr [edx + 0x5b0]
004fa31d 8b4018                   mov       eax, dword ptr [eax + 0x18]
004fa320 8b10                     mov       edx, dword ptr [eax]
004fa322 8bc8                     mov       ecx, eax
004fa324 ff92a8020000             call      dword ptr [edx + 0x2a8]
004fa32a 8bf8                     mov       edi, eax
004fa32c eb02                     jmp       0x4fa330
004fa32e 33ff                     xor       edi, edi
004fa330 8b06                     mov       eax, dword ptr [esi]
004fa332 8bce                     mov       ecx, esi
004fa334 ff9094000000             call      dword ptr [eax + 0x94]
004fa33a 8b16                     mov       edx, dword ptr [esi]
004fa33c 8bce                     mov       ecx, esi
004fa33e 8945d8                   mov       dword ptr [ebp - 0x28], eax
004fa341 ff9298000000             call      dword ptr [edx + 0x98]
004fa347 8bce                     mov       ecx, esi
004fa349 8945d4                   mov       dword ptr [ebp - 0x2c], eax
004fa34c e83f1dfaff               call      0x49c090
004fa351 84c0                     test      al, al
004fa353 0f84e4040000             je        0x4fa83d
004fa359 8b06                     mov       eax, dword ptr [esi]
004fa35b 8bce                     mov       ecx, esi
004fa35d bbffff0000               mov       ebx, 0xffff
004fa362 ff90b0050000             call      dword ptr [eax + 0x5b0]
004fa368 8b4818                   mov       ecx, dword ptr [eax + 0x18]
004fa36b 85c9                     test      ecx, ecx
004fa36d 740d                     je        0x4fa37c
004fa36f 85ff                     test      edi, edi
004fa371 7409                     je        0x4fa37c
004fa373 8b17                     mov       edx, dword ptr [edi]
004fa375 8bcf                     mov       ecx, edi
004fa377 ff5240                   call      dword ptr [edx + 0x40]
004fa37a 8bd8                     mov       ebx, eax
004fa37c 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa382 6a2a                     push      0x2a
004fa384 e8673f5600               call      0xa5e2f0
004fa389 8b06                     mov       eax, dword ptr [esi]
004fa38b 8b3d80420d01             mov       edi, dword ptr [0x10d4280]
004fa391 8bce                     mov       ecx, esi
004fa393 ff5040                   call      dword ptr [eax + 0x40]
004fa396 6a02                     push      2
004fa398 8d4de8                   lea       ecx, [ebp - 0x18]
004fa39b 51                       push      ecx
004fa39c 8bcf                     mov       ecx, edi
004fa39e 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fa3a1 e82a405600               call      0xa5e3d0
004fa3a6 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3ac 6a02                     push      2
004fa3ae 8d55e8                   lea       edx, [ebp - 0x18]
004fa3b1 52                       push      edx
004fa3b2 895de8                   mov       dword ptr [ebp - 0x18], ebx
004fa3b5 e816405600               call      0xa5e3d0
004fa3ba 8b86cc220000             mov       eax, dword ptr [esi + 0x22cc]
004fa3c0 6a04                     push      4
004fa3c2 8d4de8                   lea       ecx, [ebp - 0x18]
004fa3c5 51                       push      ecx
004fa3c6 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3cc 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fa3cf e8fc3f5600               call      0xa5e3d0
004fa3d4 8b96d0220000             mov       edx, dword ptr [esi + 0x22d0]
004fa3da 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3e0 6a04                     push      4
004fa3e2 8d45e8                   lea       eax, [ebp - 0x18]
004fa3e5 50                       push      eax
004fa3e6 8955e8                   mov       dword ptr [ebp - 0x18], edx
004fa3e9 e8e23f5600               call      0xa5e3d0
004fa3ee 8bce                     mov       ecx, esi
004fa3f0 e87b5ffbff               call      0x4b0370
004fa3f5 8b16                     mov       edx, dword ptr [esi]
004fa3f7 8bce                     mov       ecx, esi
004fa3f9 8bf8                     mov       edi, eax
004fa3fb ff92b8050000             call      dword ptr [edx + 0x5b8]
004fa401 8d4864                   lea       ecx, [eax + 0x64]
004fa404 e8577cf0ff               call      0x402060
004fa409 8d8e541d0000             lea       ecx, [esi + 0x1d54]
004fa40f 8bd8                     mov       ebx, eax
004fa411 e84a7cf0ff               call      0x402060
004fa416 85c0                     test      eax, eax
004fa418 745c                     je        0x4fa476
004fa41a e9d047ec00               jmp       0x13bebef
