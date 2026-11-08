004ba360 55                       push      ebp
004ba361 8bec                     mov       ebp, esp
004ba363 8b4508                   mov       eax, dword ptr [ebp + 8]
004ba366 56                       push      esi
004ba367 50                       push      eax
004ba368 8bf1                     mov       esi, ecx
004ba36a e871a95600               call      0xa24ce0
004ba36f 50                       push      eax
004ba370 8bce                     mov       ecx, esi
004ba372 e8c9df5600               call      0xa28340
004ba377 5e                       pop       esi
004ba378 5d                       pop       ebp
004ba379 c20400                   ret       4
004ba37c cc                       int3      
004ba37d cc                       int3      
004ba37e cc                       int3      
004ba37f cc                       int3      
004ba380 56                       push      esi
004ba381 8bf1                     mov       esi, ecx
004ba383 e8081dfeff               call      0x49c090
004ba388 84c0                     test      al, al
004ba38a 7460                     je        0x4ba3ec
004ba38c 8b06                     mov       eax, dword ptr [esi]
004ba38e 8bce                     mov       ecx, esi
004ba390 ff9090050000             call      dword ptr [eax + 0x590]
004ba396 84c0                     test      al, al
004ba398 8bce                     mov       ecx, esi
004ba39a 742e                     je        0x4ba3ca
004ba39c 8b16                     mov       edx, dword ptr [esi]
004ba39e ff926c030000             call      dword ptr [edx + 0x36c]
004ba3a4 85c0                     test      eax, eax
004ba3a6 6a00                     push      0
004ba3a8 6a00                     push      0
004ba3aa 6a00                     push      0
004ba3ac 8bce                     mov       ecx, esi
004ba3ae 6a00                     push      0
004ba3b0 740c                     je        0x4ba3be
004ba3b2 8b06                     mov       eax, dword ptr [esi]
004ba3b4 6a01                     push      1
004ba3b6 ff908c020000             call      dword ptr [eax + 0x28c]
004ba3bc 5e                       pop       esi
004ba3bd c3                       ret       
004ba3be 8b16                     mov       edx, dword ptr [esi]
004ba3c0 6a00                     push      0
004ba3c2 ff928c020000             call      dword ptr [edx + 0x28c]
004ba3c8 5e                       pop       esi
004ba3c9 c3                       ret       
004ba3ca 8b06                     mov       eax, dword ptr [esi]
004ba3cc 6a03                     push      3
004ba3ce ff9010040000             call      dword ptr [eax + 0x410]
004ba3d4 84c0                     test      al, al
004ba3d6 7414                     je        0x4ba3ec
004ba3d8 8b16                     mov       edx, dword ptr [esi]
004ba3da 6a00                     push      0
004ba3dc 6a00                     push      0
004ba3de 6a03                     push      3
004ba3e0 6a00                     push      0
004ba3e2 6a09                     push      9
004ba3e4 8bce                     mov       ecx, esi
004ba3e6 ff928c020000             call      dword ptr [edx + 0x28c]
004ba3ec 5e                       pop       esi
004ba3ed c3                       ret       
004ba3ee cc                       int3      
004ba3ef cc                       int3      
004ba3f0 55                       push      ebp
004ba3f1 8bec                     mov       ebp, esp
004ba3f3 53                       push      ebx
004ba3f4 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004ba3f7 84db                     test      bl, bl
004ba3f9 56                       push      esi
004ba3fa 57                       push      edi
004ba3fb 8bf9                     mov       edi, ecx
004ba3fd 0f859d010000             jne       0x4ba5a0
004ba403 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ba409 6aff                     push      -1
004ba40b e8e007f8ff               call      0x43abf0
004ba410 84c0                     test      al, al
004ba412 0f841e010000             je        0x4ba536
004ba418 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ba41e 81c140100000             add       ecx, 0x1040
004ba424 e8377cf4ff               call      0x402060
004ba429 83e804                   sub       eax, 4
004ba42c 742a                     je        0x4ba458
004ba42e 83e802                   sub       eax, 2
004ba431 7410                     je        0x4ba443
004ba433 48                       dec       eax
004ba434 0f85fc000000             jne       0x4ba536
004ba43a a1e0f70401               mov       eax, dword ptr [0x104f7e0]
004ba43f 85c0                     test      eax, eax
004ba441 eb2a                     jmp       0x4ba46d
004ba443 8b0dd4f30401             mov       ecx, dword ptr [0x104f3d4]
004ba449 85c9                     test      ecx, ecx
004ba44b 0f84e5000000             je        0x4ba536
004ba451 e8fac50a00               call      0x566a50
004ba456 eb13                     jmp       0x4ba46b
004ba458 8b0d88f10401             mov       ecx, dword ptr [0x104f188]
004ba45e 85c9                     test      ecx, ecx
004ba460 0f84d0000000             je        0x4ba536
004ba466 e8f5f60900               call      0x559b60
004ba46b 84c0                     test      al, al
004ba46d 0f84c3000000             je        0x4ba536
004ba473 8b07                     mov       eax, dword ptr [edi]
004ba475 8bcf                     mov       ecx, edi
004ba477 ff9034050000             call      dword ptr [eax + 0x534]
004ba47d 84c0                     test      al, al
004ba47f 0f84b1000000             je        0x4ba536
004ba485 8b0d3c310001             mov       ecx, dword ptr [0x100313c]
004ba48b e8d09ff4ff               call      0x404460
004ba490 8bb004020000             mov       esi, dword ptr [eax + 0x204]
004ba496 32db                     xor       bl, bl
004ba498 85f6                     test      esi, esi
004ba49a 7424                     je        0x4ba4c0
004ba49c 3bfe                     cmp       edi, esi
004ba49e 741e                     je        0x4ba4be
004ba4a0 8b17                     mov       edx, dword ptr [edi]
004ba4a2 8bcf                     mov       ecx, edi
004ba4a4 ff92c4010000             call      dword ptr [edx + 0x1c4]
004ba4aa 8b16                     mov       edx, dword ptr [esi]
004ba4ac 8bce                     mov       ecx, esi
004ba4ae 894508                   mov       dword ptr [ebp + 8], eax
004ba4b1 ff92c4010000             call      dword ptr [edx + 0x1c4]
004ba4b7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ba4ba 3bc8                     cmp       ecx, eax
004ba4bc 7502                     jne       0x4ba4c0
004ba4be b301                     mov       bl, 1
004ba4c0 8b07                     mov       eax, dword ptr [edi]
004ba4c2 8bcf                     mov       ecx, edi
004ba4c4 ff90c4010000             call      dword ptr [eax + 0x1c4]
004ba4ca 8bf0                     mov       esi, eax
004ba4cc 85f6                     test      esi, esi
004ba4ce 7c66                     jl        0x4ba536
004ba4d0 83fe04                   cmp       esi, 4
004ba4d3 7d61                     jge       0x4ba536
004ba4d5 84db                     test      bl, bl
004ba4d7 755d                     jne       0x4ba536
004ba4d9 8b0de0b80d01             mov       ecx, dword ptr [0x10db8e0]
004ba4df 6a02                     push      2
004ba4e1 e8cadf6400               call      0xb084b0
004ba4e6 8b0dc8e4ff00             mov       ecx, dword ptr [0xffe4c8]
004ba4ec 6a00                     push      0
004ba4ee 6a00                     push      0
004ba4f0 6a00                     push      0
004ba4f2 6aff                     push      -1
004ba4f4 6a00                     push      0
004ba4f6 680000803f               push      0x3f800000
004ba4fb 680000803f               push      0x3f800000
004ba500 83c627                   add       esi, 0x27
004ba503 56                       push      esi
004ba504 6a1c                     push      0x1c
004ba506 e8d5cc6300               call      0xaf71e0
004ba50b 8bc8                     mov       ecx, eax
004ba50d e8be7e6300               call      0xaf23d0
004ba512 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ba515 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba518 50                       push      eax
004ba519 83c1eb                   add       ecx, -0x15
004ba51c 51                       push      ecx
004ba51d 83c2c1                   add       edx, -0x3f
004ba520 52                       push      edx
004ba521 e8aade0700               call      0x5383d0
004ba526 8b0de0b80d01             mov       ecx, dword ptr [0x10db8e0]
004ba52c 83c428                   add       esp, 0x28
004ba52f 6a00                     push      0
004ba531 e87adf6400               call      0xb084b0
004ba536 8b5d14                   mov       ebx, dword ptr [ebp + 0x14]
004ba539 8b7510                   mov       esi, dword ptr [ebp + 0x10]
004ba53c 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ba53f 53                       push      ebx
004ba540 56                       push      esi
004ba541 50                       push      eax
004ba542 6a00                     push      0
004ba544 8bcf                     mov       ecx, edi
004ba546 e885eafdff               call      0x498fd0
004ba54b 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ba54e 53                       push      ebx
004ba54f 56                       push      esi
004ba550 51                       push      ecx
004ba551 8b8fdc120000             mov       ecx, dword ptr [edi + 0x12dc]
004ba557 6a00                     push      0
004ba559 e892b30a00               call      0x5658f0
004ba55e 8db7d8120000             lea       esi, [edi + 0x12d8]
004ba564 bf12000000               mov       edi, 0x12
004ba569 8da42400000000           lea       esp, [esp]
004ba570 8b06                     mov       eax, dword ptr [esi]
004ba572 85c0                     test      eax, eax
004ba574 741d                     je        0x4ba593
004ba576 8bc8                     mov       ecx, eax
004ba578 8b11                     mov       edx, dword ptr [ecx]
004ba57a ff5208                   call      dword ptr [edx + 8]
004ba57d 84c0                     test      al, al
004ba57f 7412                     je        0x4ba593
004ba581 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004ba584 8b0e                     mov       ecx, dword ptr [esi]
004ba586 8b01                     mov       eax, dword ptr [ecx]
004ba588 53                       push      ebx
004ba589 52                       push      edx
004ba58a 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba58d 52                       push      edx
004ba58e 6a00                     push      0
004ba590 ff503c                   call      dword ptr [eax + 0x3c]
004ba593 83ee04                   sub       esi, 4
004ba596 4f                       dec       edi
004ba597 75d7                     jne       0x4ba570
004ba599 5f                       pop       edi
004ba59a 5e                       pop       esi
004ba59b 5b                       pop       ebx
004ba59c 5d                       pop       ebp
004ba59d c21000                   ret       0x10
004ba5a0 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004ba5a3 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ba5a6 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba5a9 50                       push      eax
004ba5aa 51                       push      ecx
004ba5ab 52                       push      edx
004ba5ac 53                       push      ebx
004ba5ad 8bcf                     mov       ecx, edi
004ba5af e81ceafdff               call      0x498fd0
004ba5b4 8db794120000             lea       esi, [edi + 0x1294]
004ba5ba c7450812000000           mov       dword ptr [ebp + 8], 0x12
004ba5c1 8b06                     mov       eax, dword ptr [esi]
004ba5c3 85c0                     test      eax, eax
004ba5c5 741f                     je        0x4ba5e6
004ba5c7 8bc8                     mov       ecx, eax
004ba5c9 8b01                     mov       eax, dword ptr [ecx]
004ba5cb ff5008                   call      dword ptr [eax + 8]
004ba5ce 84c0                     test      al, al
004ba5d0 7414                     je        0x4ba5e6
004ba5d2 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004ba5d5 8b0e                     mov       ecx, dword ptr [esi]
004ba5d7 8b11                     mov       edx, dword ptr [ecx]
004ba5d9 50                       push      eax
004ba5da 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004ba5dd 50                       push      eax
004ba5de 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ba5e1 50                       push      eax
004ba5e2 53                       push      ebx
004ba5e3 ff523c                   call      dword ptr [edx + 0x3c]
004ba5e6 8b4508                   mov       eax, dword ptr [ebp + 8]
004ba5e9 83c604                   add       esi, 4
004ba5ec 48                       dec       eax
004ba5ed 894508                   mov       dword ptr [ebp + 8], eax
004ba5f0 75cf                     jne       0x4ba5c1
004ba5f2 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004ba5f5 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004ba5f8 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ba5fb 51                       push      ecx
004ba5fc 8b8fdc120000             mov       ecx, dword ptr [edi + 0x12dc]
004ba602 52                       push      edx
004ba603 50                       push      eax
004ba604 53                       push      ebx
004ba605 e8e6b20a00               call      0x5658f0
004ba60a 5f                       pop       edi
004ba60b 5e                       pop       esi
004ba60c 5b                       pop       ebx
004ba60d 5d                       pop       ebp
004ba60e c21000                   ret       0x10
004ba611 cc                       int3      
004ba612 cc                       int3      
004ba613 cc                       int3      
004ba614 cc                       int3      
004ba615 cc                       int3      
004ba616 cc                       int3      
004ba617 cc                       int3      
004ba618 cc                       int3      
004ba619 cc                       int3      
004ba61a cc                       int3      
004ba61b cc                       int3      
004ba61c cc                       int3      
004ba61d cc                       int3      
004ba61e cc                       int3      
004ba61f cc                       int3      
