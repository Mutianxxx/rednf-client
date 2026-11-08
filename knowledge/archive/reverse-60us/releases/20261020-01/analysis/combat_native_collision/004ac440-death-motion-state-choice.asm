004ac440 55                       push      ebp
004ac441 8bec                     mov       ebp, esp
004ac443 56                       push      esi
004ac444 8bf1                     mov       esi, ecx
004ac446 8b06                     mov       eax, dword ptr [esi]
004ac448 ff90dc030000             call      dword ptr [eax + 0x3dc]
004ac44e 84c0                     test      al, al
004ac450 750a                     jne       0x4ac45c
004ac452 b804000000               mov       eax, 4
004ac457 5e                       pop       esi
004ac458 5d                       pop       ebp
004ac459 c20800                   ret       8
004ac45c 57                       push      edi
004ac45d 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ac460 83ff05                   cmp       edi, 5
004ac463 7475                     je        0x4ac4da
004ac465 83bea004000005           cmp       dword ptr [esi + 0x4a0], 5
004ac46c 746c                     je        0x4ac4da
004ac46e 8b16                     mov       edx, dword ptr [esi]
004ac470 6811010000               push      0x111
004ac475 8bce                     mov       ecx, esi
004ac477 ff522c                   call      dword ptr [edx + 0x2c]
004ac47a 84c0                     test      al, al
004ac47c 740b                     je        0x4ac489
004ac47e 5f                       pop       edi
004ac47f b804000000               mov       eax, 4
004ac484 5e                       pop       esi
004ac485 5d                       pop       ebp
004ac486 c20800                   ret       8
004ac489 8b06                     mov       eax, dword ptr [esi]
004ac48b 6811020000               push      0x211
004ac490 8bce                     mov       ecx, esi
004ac492 ff502c                   call      dword ptr [eax + 0x2c]
004ac495 84c0                     test      al, al
004ac497 74e5                     je        0x4ac47e
004ac499 8a450c                   mov       al, byte ptr [ebp + 0xc]
004ac49c 84c0                     test      al, al
004ac49e 7505                     jne       0x4ac4a5
004ac4a0 83ff09                   cmp       edi, 9
004ac4a3 750e                     jne       0x4ac4b3
004ac4a5 8b16                     mov       edx, dword ptr [esi]
004ac4a7 8bce                     mov       ecx, esi
004ac4a9 ff92a0050000             call      dword ptr [edx + 0x5a0]
004ac4af 84c0                     test      al, al
004ac4b1 741c                     je        0x4ac4cf
004ac4b3 8b06                     mov       eax, dword ptr [esi]
004ac4b5 8bce                     mov       ecx, esi
004ac4b7 ff9078030000             call      dword ptr [eax + 0x378]
004ac4bd 85c0                     test      eax, eax
004ac4bf 75bd                     jne       0x4ac47e
004ac4c1 8b16                     mov       edx, dword ptr [esi]
004ac4c3 8bce                     mov       ecx, esi
004ac4c5 ff92a0030000             call      dword ptr [edx + 0x3a0]
004ac4cb 85c0                     test      eax, eax
004ac4cd 75af                     jne       0x4ac47e
004ac4cf 5f                       pop       edi
004ac4d0 b805000000               mov       eax, 5
004ac4d5 5e                       pop       esi
004ac4d6 5d                       pop       ebp
004ac4d7 c20800                   ret       8
004ac4da 5f                       pop       edi
004ac4db 83c8ff                   or        eax, 0xffffffff
004ac4de 5e                       pop       esi
004ac4df 5d                       pop       ebp
004ac4e0 c20800                   ret       8
004ac4e3 cc                       int3      
004ac4e4 cc                       int3      
004ac4e5 cc                       int3      
004ac4e6 cc                       int3      
004ac4e7 cc                       int3      
004ac4e8 cc                       int3      
004ac4e9 cc                       int3      
004ac4ea cc                       int3      
004ac4eb cc                       int3      
004ac4ec cc                       int3      
004ac4ed cc                       int3      
004ac4ee cc                       int3      
004ac4ef cc                       int3      
004ac4f0 8b81f0040000             mov       eax, dword ptr [ecx + 0x4f0]
004ac4f6 c3                       ret       
004ac4f7 cc                       int3      
004ac4f8 cc                       int3      
004ac4f9 cc                       int3      
004ac4fa cc                       int3      
004ac4fb cc                       int3      
004ac4fc cc                       int3      
004ac4fd cc                       int3      
004ac4fe cc                       int3      
004ac4ff cc                       int3      
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
004ac5e0 c20800                   ret       8
004ac5e3 cc                       int3      
004ac5e4 cc                       int3      
004ac5e5 cc                       int3      
004ac5e6 cc                       int3      
004ac5e7 cc                       int3      
004ac5e8 cc                       int3      
004ac5e9 cc                       int3      
004ac5ea cc                       int3      
004ac5eb cc                       int3      
004ac5ec cc                       int3      
004ac5ed cc                       int3      
004ac5ee cc                       int3      
004ac5ef cc                       int3      
004ac5f0 55                       push      ebp
004ac5f1 8bec                     mov       ebp, esp
004ac5f3 83ec08                   sub       esp, 8
004ac5f6 56                       push      esi
004ac5f7 8bf1                     mov       esi, ecx
004ac5f9 8b06                     mov       eax, dword ptr [esi]
004ac5fb ff9060010000             call      dword ptr [eax + 0x160]
004ac601 85c0                     test      eax, eax
004ac603 7544                     jne       0x4ac649
004ac605 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac60b 6881000000               push      0x81
004ac610 e8db1c5b00               call      0xa5e2f0
004ac615 6a01                     push      1
004ac617 8d4dfc                   lea       ecx, [ebp - 4]
004ac61a 51                       push      ecx
004ac61b 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac621 c645fc02                 mov       byte ptr [ebp - 4], 2
004ac625 e8a61d5b00               call      0xa5e3d0
004ac62a 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac630 6a01                     push      1
004ac632 8d55fc                   lea       edx, [ebp - 4]
004ac635 52                       push      edx
004ac636 c645fc15                 mov       byte ptr [ebp - 4], 0x15
004ac63a e8911d5b00               call      0xa5e3d0
004ac63f e85c2e5b00               call      0xa5f4a0
004ac644 5e                       pop       esi
004ac645 8be5                     mov       esp, ebp
004ac647 5d                       pop       ebp
004ac648 c3                       ret       
004ac649 57                       push      edi
004ac64a bf10000000               mov       edi, 0x10
004ac64f 83ff20                   cmp       edi, 0x20
004ac652 53                       push      ebx
004ac653 7d20                     jge       0x4ac675
004ac655 a14c310001               mov       eax, dword ptr [0x100314c]
004ac65a 8b0407                   mov       eax, dword ptr [edi + eax]
004ac65d 85c0                     test      eax, eax
004ac65f 7414                     je        0x4ac675
004ac661 8b16                     mov       edx, dword ptr [esi]
004ac663 8b9804020000             mov       ebx, dword ptr [eax + 0x204]
004ac669 8bce                     mov       ecx, esi
004ac66b ff9260010000             call      dword ptr [edx + 0x160]
004ac671 3bd8                     cmp       ebx, eax
004ac673 744e                     je        0x4ac6c3
004ac675 83c704                   add       edi, 4
004ac678 83ff20                   cmp       edi, 0x20
004ac67b 7cd8                     jl        0x4ac655
004ac67d 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac683 6881000000               push      0x81
004ac688 e8631c5b00               call      0xa5e2f0
004ac68d 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac693 6a01                     push      1
004ac695 8d45fc                   lea       eax, [ebp - 4]
004ac698 50                       push      eax
004ac699 c645fc02                 mov       byte ptr [ebp - 4], 2
004ac69d e82e1d5b00               call      0xa5e3d0
004ac6a2 6a01                     push      1
004ac6a4 8d4dfc                   lea       ecx, [ebp - 4]
004ac6a7 51                       push      ecx
004ac6a8 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac6ae c645fc03                 mov       byte ptr [ebp - 4], 3
004ac6b2 e8191d5b00               call      0xa5e3d0
004ac6b7 e8e42d5b00               call      0xa5f4a0
004ac6bc 5b                       pop       ebx
004ac6bd 5f                       pop       edi
004ac6be 5e                       pop       esi
004ac6bf 8be5                     mov       esp, ebp
004ac6c1 5d                       pop       ebp
004ac6c2 c3                       ret       
004ac6c3 8bce                     mov       ecx, esi
004ac6c5 e8c6f9feff               call      0x49c090
004ac6ca 84c0                     test      al, al
004ac6cc 7479                     je        0x4ac747
004ac6ce 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004ac6d4 6883000000               push      0x83
004ac6d9 e8121c5b00               call      0xa5e2f0
004ac6de 8b16                     mov       edx, dword ptr [esi]
004ac6e0 8bce                     mov       ecx, esi
004ac6e2 ff9260010000             call      dword ptr [edx + 0x160]
004ac6e8 8b10                     mov       edx, dword ptr [eax]
004ac6ea 8b3d80420d01             mov       edi, dword ptr [0x10d4280]
