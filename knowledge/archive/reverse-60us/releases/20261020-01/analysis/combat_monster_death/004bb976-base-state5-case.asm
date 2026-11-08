004bb976 8bce                     mov       ecx, esi
004bb978 e8830bffff               call      0x4ac500
004bb97d 85c0                     test      eax, eax
004bb97f 742c                     je        0x4bb9ad
004bb981 8b10                     mov       edx, dword ptr [eax]
004bb983 8bc8                     mov       ecx, eax
004bb985 ff92a4020000             call      dword ptr [edx + 0x2a4]
004bb98b 8bf8                     mov       edi, eax
004bb98d 85ff                     test      edi, edi
004bb98f 741c                     je        0x4bb9ad
004bb991 8b1f                     mov       ebx, dword ptr [edi]
004bb993 8d8e60180000             lea       ecx, [esi + 0x1860]
004bb999 e8c266f4ff               call      0x402060
004bb99e 85c0                     test      eax, eax
004bb9a0 0f95c0                   setne     al
004bb9a3 8bcf                     mov       ecx, edi
004bb9a5 50                       push      eax
004bb9a6 56                       push      esi
004bb9a7 ff93b0040000             call      dword ptr [ebx + 0x4b0]
004bb9ad 8b8edc120000             mov       ecx, dword ptr [esi + 0x12dc]
004bb9b3 e888250000               call      0x4bdf40
004bb9b8 83be5817000008           cmp       dword ptr [esi + 0x1758], 8
004bb9bf 7208                     jb        0x4bb9c9
004bb9c1 8b8644170000             mov       eax, dword ptr [esi + 0x1744]
004bb9c7 eb06                     jmp       0x4bb9cf
004bb9c9 8d8644170000             lea       eax, [esi + 0x1744]
004bb9cf 8b16                     mov       edx, dword ptr [esi]
004bb9d1 6a00                     push      0
004bb9d3 6a00                     push      0
004bb9d5 6aff                     push      -1
004bb9d7 50                       push      eax
004bb9d8 8bce                     mov       ecx, esi
004bb9da ff920c010000             call      dword ptr [edx + 0x10c]
004bb9e0 8b06                     mov       eax, dword ptr [esi]
004bb9e2 6a00                     push      0
004bb9e4 8bce                     mov       ecx, esi
004bb9e6 ff9010010000             call      dword ptr [eax + 0x110]
004bb9ec 8b16                     mov       edx, dword ptr [esi]
004bb9ee 6a00                     push      0
004bb9f0 8bce                     mov       ecx, esi
004bb9f2 ff92d0020000             call      dword ptr [edx + 0x2d0]
004bb9f8 8b06                     mov       eax, dword ptr [esi]
004bb9fa 6a00                     push      0
004bb9fc 8bce                     mov       ecx, esi
004bb9fe ff90d8020000             call      dword ptr [eax + 0x2d8]
004bba04 8b16                     mov       edx, dword ptr [esi]
004bba06 8bce                     mov       ecx, esi
004bba08 c6451400                 mov       byte ptr [ebp + 0x14], 0
004bba0c ff92f4000000             call      dword ptr [edx + 0xf4]
004bba12 85c0                     test      eax, eax
004bba14 7413                     je        0x4bba29
004bba16 8b06                     mov       eax, dword ptr [esi]
004bba18 6a01                     push      1
004bba1a 8bce                     mov       ecx, esi
004bba1c ff90f4000000             call      dword ptr [eax + 0xf4]
004bba22 8bc8                     mov       ecx, eax
004bba24 e8e7c65600               call      0xa28110
004bba29 8b16                     mov       edx, dword ptr [esi]
004bba2b 6a00                     push      0
004bba2d 6a00                     push      0
004bba2f 6a00                     push      0
004bba31 6a00                     push      0
004bba33 6a00                     push      0
004bba35 6a00                     push      0
004bba37 8bce                     mov       ecx, esi
004bba39 ff9288040000             call      dword ptr [edx + 0x488]
004bba3f 8b06                     mov       eax, dword ptr [esi]
004bba41 6a00                     push      0
004bba43 6a00                     push      0
004bba45 6a00                     push      0
004bba47 6a00                     push      0
004bba49 6a00                     push      0
004bba4b 6a01                     push      1
004bba4d 8bce                     mov       ecx, esi
004bba4f ff9088040000             call      dword ptr [eax + 0x488]
004bba55 8b16                     mov       edx, dword ptr [esi]
004bba57 680000803f               push      0x3f800000
004bba5c 680000803f               push      0x3f800000
004bba61 68e8030000               push      0x3e8
004bba66 68e8030000               push      0x3e8
004bba6b 6a00                     push      0
004bba6d 6a00                     push      0
004bba6f 8bce                     mov       ecx, esi
004bba71 ff9294040000             call      dword ptr [edx + 0x494]
004bba77 8b06                     mov       eax, dword ptr [esi]
004bba79 6a00                     push      0
004bba7b 6a04                     push      4
004bba7d 6a04                     push      4
004bba7f 8bce                     mov       ecx, esi
004bba81 ff909c040000             call      dword ptr [eax + 0x49c]
004bba87 8b16                     mov       edx, dword ptr [esi]
004bba89 6811020000               push      0x211
004bba8e 8bce                     mov       ecx, esi
004bba90 ff522c                   call      dword ptr [edx + 0x2c]
004bba93 84c0                     test      al, al
004bba95 0f84aa0b0000             je        0x4bc645
004bba9b 8b06                     mov       eax, dword ptr [esi]
004bba9d 8bce                     mov       ecx, esi
004bba9f ff90a0050000             call      dword ptr [eax + 0x5a0]
004bbaa5 84c0                     test      al, al
004bbaa7 0f85980b0000             jne       0x4bc645
004bbaad 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004bbab3 6a00                     push      0
004bbab5 6a02                     push      2
004bbab7 e884550500               call      0x511040
004bbabc 6a00                     push      0
004bbabe 6a00                     push      0
004bbac0 8bce                     mov       ecx, esi
004bbac2 e8f9e5ffff               call      0x4ba0c0
004bbac7 e9790b0000               jmp       0x4bc645
