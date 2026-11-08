004ac500 56                       push      esi
004ac501 8bf1                     mov       esi, ecx
004ac503 8b06                     mov       eax, dword ptr [esi]
004ac505 57                       push      edi
004ac506 ff5028                   call      dword ptr [eax + 0x28]
004ac509 8b00                     mov       eax, dword ptr [eax]
004ac50b 3d11010000               cmp       eax, 0x111
004ac510 744e                     je        0x4ac560
004ac512 3d11020000               cmp       eax, 0x211
004ac517 0f85be000000             jne       0x4ac5db
004ac51d 6a00                     push      0
004ac51f 682829f400               push      0xf42928
004ac524 686c52f500               push      0xf5526c
004ac529 6a00                     push      0
004ac52b 56                       push      esi
004ac52c e8da477500               call      0xc00d0b
004ac531 8bf0                     mov       esi, eax
004ac533 83c414                   add       esp, 0x14
004ac536 85f6                     test      esi, esi
004ac538 0f849d000000             je        0x4ac5db
004ac53e 8b16                     mov       edx, dword ptr [esi]
004ac540 8bce                     mov       ecx, esi
004ac542 ff92b0050000             call      dword ptr [edx + 0x5b0]
004ac548 85c0                     test      eax, eax
004ac54a 0f848b000000             je        0x4ac5db
004ac550 8b06                     mov       eax, dword ptr [esi]
004ac552 8bce                     mov       ecx, esi
004ac554 ff90b0050000             call      dword ptr [eax + 0x5b0]
004ac55a 8b4018                   mov       eax, dword ptr [eax + 0x18]
004ac55d 5f                       pop       edi
004ac55e 5e                       pop       esi
004ac55f c3                       ret       
004ac560 6a00                     push      0
004ac562 688c52f500               push      0xf5528c
004ac567 686c52f500               push      0xf5526c
004ac56c 6a00                     push      0
004ac56e 56                       push      esi
004ac56f e897477500               call      0xc00d0b
004ac574 8bf8                     mov       edi, eax
004ac576 83c414                   add       esp, 0x14
004ac579 85ff                     test      edi, edi
004ac57b 745e                     je        0x4ac5db
004ac57d 8b17                     mov       edx, dword ptr [edi]
004ac57f 8bcf                     mov       ecx, edi
004ac581 ff5234                   call      dword ptr [edx + 0x34]
004ac584 84c0                     test      al, al
004ac586 7413                     je        0x4ac59b
004ac588 8bb6a02a0000             mov       esi, dword ptr [esi + 0x2aa0]
004ac58e 85f6                     test      esi, esi
004ac590 7449                     je        0x4ac5db
004ac592 8b86d4020000             mov       eax, dword ptr [esi + 0x2d4]
004ac598 5f                       pop       edi
004ac599 5e                       pop       esi
004ac59a c3                       ret       
004ac59b 8d8750250000             lea       eax, [edi + 0x2550]
004ac5a1 85c0                     test      eax, eax
004ac5a3 7436                     je        0x4ac5db
004ac5a5 8b8f58250000             mov       ecx, dword ptr [edi + 0x2558]
004ac5ab 8b9754250000             mov       edx, dword ptr [edi + 0x2554]
004ac5b1 8b06                     mov       eax, dword ptr [esi]
004ac5b3 6a00                     push      0
004ac5b5 687c28f400               push      0xf4287c
004ac5ba 681009f400               push      0xf40910
004ac5bf 6a00                     push      0
004ac5c1 51                       push      ecx
004ac5c2 52                       push      edx
004ac5c3 8bce                     mov       ecx, esi
004ac5c5 ff505c                   call      dword ptr [eax + 0x5c]
004ac5c8 8bc8                     mov       ecx, eax
004ac5ca e851f20500               call      0x50b820
004ac5cf 50                       push      eax
004ac5d0 e836477500               call      0xc00d0b
004ac5d5 83c414                   add       esp, 0x14
004ac5d8 5f                       pop       edi
004ac5d9 5e                       pop       esi
004ac5da c3                       ret       
004ac5db 5f                       pop       edi
004ac5dc 33c0                     xor       eax, eax
004ac5de 5e                       pop       esi
004ac5df c3                       ret       
