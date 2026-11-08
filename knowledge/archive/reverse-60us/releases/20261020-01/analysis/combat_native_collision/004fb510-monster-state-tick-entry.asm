004fb510 55                       push      ebp
004fb511 8bec                     mov       ebp, esp
004fb513 6aff                     push      -1
004fb515 68ae9cc500               push      0xc59cae
004fb51a 64a100000000             mov       eax, dword ptr fs:[0]
004fb520 50                       push      eax
004fb521 64892500000000           mov       dword ptr fs:[0], esp
004fb528 83ec10                   sub       esp, 0x10
004fb52b 56                       push      esi
004fb52c 8bf1                     mov       esi, ecx
004fb52e e85d0bfaff               call      0x49c090
004fb533 84c0                     test      al, al
004fb535 0f84d2010000             je        0x4fb70d
004fb53b 8b06                     mov       eax, dword ptr [esi]
004fb53d 8bce                     mov       ecx, esi
004fb53f ff9030020000             call      dword ptr [eax + 0x230]
004fb545 85c0                     test      eax, eax
004fb547 0f85c0010000             jne       0x4fb70d
004fb54d 50                       push      eax
004fb54e e89d2b3b00               call      0x8ae0f0
004fb553 99                       cdq       
004fb554 b964000000               mov       ecx, 0x64
004fb559 f7f9                     idiv      ecx
004fb55b 8b860c210000             mov       eax, dword ptr [esi + 0x210c]
004fb561 83c404                   add       esp, 4
004fb564 3bd0                     cmp       edx, eax
004fb566 0f8da1010000             jge       0x4fb70d
004fb56c 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004fb572 85c0                     test      eax, eax
004fb574 7419                     je        0x4fb58f
004fb576 8b8e641d0000             mov       ecx, dword ptr [esi + 0x1d64]
004fb57c 2bc8                     sub       ecx, eax
004fb57e b8abaaaa2a               mov       eax, 0x2aaaaaab
004fb583 f7e9                     imul      ecx
004fb585 c1fa04                   sar       edx, 4
004fb588 8bc2                     mov       eax, edx
004fb58a c1e81f                   shr       eax, 0x1f
004fb58d 03c2                     add       eax, edx
004fb58f 398610210000             cmp       dword ptr [esi + 0x2110], eax
004fb595 0f8372010000             jae       0x4fb70d
004fb59b 8b16                     mov       edx, dword ptr [esi]
004fb59d 8bce                     mov       ecx, esi
004fb59f ff9264030000             call      dword ptr [edx + 0x364]
004fb5a5 8b4828                   mov       ecx, dword ptr [eax + 0x28]
004fb5a8 83c024                   add       eax, 0x24
004fb5ab 85c9                     test      ecx, ecx
004fb5ad 7504                     jne       0x4fb5b3
004fb5af 33c0                     xor       eax, eax
004fb5b1 eb08                     jmp       0x4fb5bb
004fb5b3 8b4008                   mov       eax, dword ptr [eax + 8]
004fb5b6 2bc1                     sub       eax, ecx
004fb5b8 c1f802                   sar       eax, 2
004fb5bb 57                       push      edi
004fb5bc 8bbe10210000             mov       edi, dword ptr [esi + 0x2110]
004fb5c2 3bf8                     cmp       edi, eax
004fb5c4 0f8342010000             jae       0x4fb70c
004fb5ca 8b06                     mov       eax, dword ptr [esi]
004fb5cc 8bce                     mov       ecx, esi
004fb5ce ff9064030000             call      dword ptr [eax + 0x364]
004fb5d4 83c024                   add       eax, 0x24
004fb5d7 8b4004                   mov       eax, dword ptr [eax + 4]
004fb5da 833cb800                 cmp       dword ptr [eax + edi*4], 0
004fb5de 0f8428010000             je        0x4fb70c
004fb5e4 8b8e10210000             mov       ecx, dword ptr [esi + 0x2110]
004fb5ea 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004fb5f0 8d0c49                   lea       ecx, [ecx + ecx*2]
004fb5f3 c1e105                   shl       ecx, 5
004fb5f6 03c8                     add       ecx, eax
004fb5f8 e8636af0ff               call      0x402060
004fb5fd 85c0                     test      eax, eax
004fb5ff 0f8407010000             je        0x4fb70c
004fb605 8b8610210000             mov       eax, dword ptr [esi + 0x2110]
004fb60b 8b8e601d0000             mov       ecx, dword ptr [esi + 0x1d60]
004fb611 8d0440                   lea       eax, [eax + eax*2]
004fb614 c1e005                   shl       eax, 5
004fb617 03c1                     add       eax, ecx
004fb619 53                       push      ebx
004fb61a 8d4828                   lea       ecx, [eax + 0x28]
004fb61d e83e6af0ff               call      0x402060
004fb622 8bf8                     mov       edi, eax
004fb624 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004fb62a 33c9                     xor       ecx, ecx
004fb62c 33db                     xor       ebx, ebx
004fb62e 3bc1                     cmp       eax, ecx
004fb630 7417                     je        0x4fb649
004fb632 8b16                     mov       edx, dword ptr [esi]
004fb634 51                       push      ecx
004fb635 50                       push      eax
004fb636 8bce                     mov       ecx, esi
004fb638 ff5208                   call      dword ptr [edx + 8]
004fb63b 3bc7                     cmp       eax, edi
004fb63d 7d08                     jge       0x4fb647
004fb63f 8b9e801b0000             mov       ebx, dword ptr [esi + 0x1b80]
004fb645 eb53                     jmp       0x4fb69a
004fb647 33c9                     xor       ecx, ecx
004fb649 894de8                   mov       dword ptr [ebp - 0x18], ecx
004fb64c 894dec                   mov       dword ptr [ebp - 0x14], ecx
004fb64f 894df0                   mov       dword ptr [ebp - 0x10], ecx
004fb652 57                       push      edi
004fb653 8d45e4                   lea       eax, [ebp - 0x1c]
004fb656 50                       push      eax
004fb657 51                       push      ecx
004fb658 894dfc                   mov       dword ptr [ebp - 4], ecx
004fb65b 6a11                     push      0x11
004fb65d 8bce                     mov       ecx, esi
004fb65f e89cf7ffff               call      0x4fae00
004fb664 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
004fb667 85c0                     test      eax, eax
004fb669 7420                     je        0x4fb68b
004fb66b 8b7dec                   mov       edi, dword ptr [ebp - 0x14]
004fb66e 2bf8                     sub       edi, eax
004fb670 c1ff02                   sar       edi, 2
004fb673 85ff                     test      edi, edi
004fb675 7614                     jbe       0x4fb68b
004fb677 6a00                     push      0
004fb679 e8722a3b00               call      0x8ae0f0
004fb67e 33d2                     xor       edx, edx
004fb680 83c404                   add       esp, 4
004fb683 f7f7                     div       edi
004fb685 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
004fb688 8b1c91                   mov       ebx, dword ptr [ecx + edx*4]
004fb68b 8d4de4                   lea       ecx, [ebp - 0x1c]
004fb68e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004fb695 e8b6961400               call      0x644d50
004fb69a 33ff                     xor       edi, edi
004fb69c 3bdf                     cmp       ebx, edi
004fb69e 746b                     je        0x4fb70b
004fb6a0 8b13                     mov       edx, dword ptr [ebx]
004fb6a2 8bcb                     mov       ecx, ebx
004fb6a4 ff9294000000             call      dword ptr [edx + 0x94]
004fb6aa 8bd8                     mov       ebx, eax
004fb6ac 8b06                     mov       eax, dword ptr [esi]
004fb6ae 8bce                     mov       ecx, esi
004fb6b0 ff9094000000             call      dword ptr [eax + 0x94]
004fb6b6 3bc3                     cmp       eax, ebx
004fb6b8 8bce                     mov       ecx, esi
004fb6ba 7d0c                     jge       0x4fb6c8
004fb6bc 8b16                     mov       edx, dword ptr [esi]
004fb6be 6a01                     push      1
004fb6c0 ff92b8000000             call      dword ptr [edx + 0xb8]
004fb6c6 eb09                     jmp       0x4fb6d1
004fb6c8 8b06                     mov       eax, dword ptr [esi]
004fb6ca 57                       push      edi
004fb6cb ff90b8000000             call      dword ptr [eax + 0xb8]
004fb6d1 897de8                   mov       dword ptr [ebp - 0x18], edi
004fb6d4 897dec                   mov       dword ptr [ebp - 0x14], edi
004fb6d7 897df0                   mov       dword ptr [ebp - 0x10], edi
004fb6da 8d8610210000             lea       eax, [esi + 0x2110]
004fb6e0 50                       push      eax
004fb6e1 8d4de4                   lea       ecx, [ebp - 0x1c]
004fb6e4 c745fc01000000           mov       dword ptr [ebp - 4], 1
004fb6eb e830baf0ff               call      0x407120
004fb6f0 8b16                     mov       edx, dword ptr [esi]
004fb6f2 57                       push      edi
004fb6f3 57                       push      edi
004fb6f4 57                       push      edi
004fb6f5 8d45e4                   lea       eax, [ebp - 0x1c]
004fb6f8 50                       push      eax
004fb6f9 6a08                     push      8
004fb6fb 8bce                     mov       ecx, esi
004fb6fd ff928c020000             call      dword ptr [edx + 0x28c]
004fb703 8d4de4                   lea       ecx, [ebp - 0x1c]
004fb706 e845961400               call      0x644d50
004fb70b 5b                       pop       ebx
004fb70c 5f                       pop       edi
004fb70d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004fb710 5e                       pop       esi
004fb711 64890d00000000           mov       dword ptr fs:[0], ecx
004fb718 8be5                     mov       esp, ebp
004fb71a 5d                       pop       ebp
004fb71b c20400                   ret       4
004fb71e cc                       int3      
004fb71f cc                       int3      
004fb720 55                       push      ebp
004fb721 8bec                     mov       ebp, esp
004fb723 83ec30                   sub       esp, 0x30
004fb726 56                       push      esi
004fb727 57                       push      edi
004fb728 8bf1                     mov       esi, ecx
004fb72a 33ff                     xor       edi, edi
004fb72c 8d642400                 lea       esp, [esp]
004fb730 8b86781a0000             mov       eax, dword ptr [esi + 0x1a78]
004fb736 85c0                     test      eax, eax
004fb738 7431                     je        0x4fb76b
004fb73a 8b8e7c1a0000             mov       ecx, dword ptr [esi + 0x1a7c]
004fb740 2bc8                     sub       ecx, eax
004fb742 b8398ee338               mov       eax, 0x38e38e39
004fb747 f7e9                     imul      ecx
004fb749 c1fa03                   sar       edx, 3
004fb74c 8bc2                     mov       eax, edx
004fb74e c1e81f                   shr       eax, 0x1f
004fb751 03c2                     add       eax, edx
004fb753 3bf8                     cmp       edi, eax
004fb755 7314                     jae       0x4fb76b
004fb757 8b86381a0000             mov       eax, dword ptr [esi + 0x1a38]
004fb75d 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004fb760 8d04b8                   lea       eax, [eax + edi*4]
004fb763 e808422500               call      0x74f970
004fb768 47                       inc       edi
004fb769 ebc5                     jmp       0x4fb730
004fb76b 33ff                     xor       edi, edi
004fb76d 8d4900                   lea       ecx, [ecx]
004fb770 8b86881a0000             mov       eax, dword ptr [esi + 0x1a88]
004fb776 85c0                     test      eax, eax
004fb778 7430                     je        0x4fb7aa
004fb77a 8b8e8c1a0000             mov       ecx, dword ptr [esi + 0x1a8c]
004fb780 2bc8                     sub       ecx, eax
004fb782 b8abaaaa2a               mov       eax, 0x2aaaaaab
004fb787 f7e9                     imul      ecx
004fb789 c1fa02                   sar       edx, 2
004fb78c 8bc2                     mov       eax, edx
004fb78e c1e81f                   shr       eax, 0x1f
004fb791 03c2                     add       eax, edx
004fb793 3bf8                     cmp       edi, eax
004fb795 7313                     jae       0x4fb7aa
004fb797 8b8e481a0000             mov       ecx, dword ptr [esi + 0x1a48]
004fb79d 8d04b9                   lea       eax, [ecx + edi*4]
004fb7a0 8b08                     mov       ecx, dword ptr [eax]
004fb7a2 e8e93f2500               call      0x74f790
004fb7a7 47                       inc       edi
004fb7a8 ebc6                     jmp       0x4fb770
004fb7aa 8b86781a0000             mov       eax, dword ptr [esi + 0x1a78]
004fb7b0 85c0                     test      eax, eax
004fb7b2 0f848b020000             je        0x4fba43
004fb7b8 8b8e7c1a0000             mov       ecx, dword ptr [esi + 0x1a7c]
004fb7be 2bc8                     sub       ecx, eax
004fb7c0 b8398ee338               mov       eax, 0x38e38e39
004fb7c5 f7e9                     imul      ecx
004fb7c7 c1fa03                   sar       edx, 3
004fb7ca 8bc2                     mov       eax, edx
004fb7cc c1e81f                   shr       eax, 0x1f
004fb7cf 03c2                     add       eax, edx
004fb7d1 8945f0                   mov       dword ptr [ebp - 0x10], eax
004fb7d4 0f8469020000             je        0x4fba43
004fb7da 8b8e18240000             mov       ecx, dword ptr [esi + 0x2418]
004fb7e0 85c9                     test      ecx, ecx
004fb7e2 8dbe14240000             lea       edi, [esi + 0x2414]
004fb7e8 0f8455020000             je        0x4fba43
004fb7ee 8b4708                   mov       eax, dword ptr [edi + 8]
004fb7f1 2bc1                     sub       eax, ecx
004fb7f3 c1f802                   sar       eax, 2
004fb7f6 85c0                     test      eax, eax
004fb7f8 0f8445020000             je        0x4fba43
004fb7fe 85c9                     test      ecx, ecx
004fb800 740c                     je        0x4fb80e
004fb802 8b4708                   mov       eax, dword ptr [edi + 8]
004fb805 2bc1                     sub       eax, ecx
004fb807 c1f802                   sar       eax, 2
004fb80a 85c0                     test      eax, eax
004fb80c 7707                     ja        0x4fb815
004fb80e 8bcf                     mov       ecx, edi
004fb810 e98b82feff               jmp       0x4e3aa0
004fb815 833900                   cmp       dword ptr [ecx], 0
004fb818 744d                     je        0x4fb867
004fb81a 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb81d 85c9                     test      ecx, ecx
004fb81f 740c                     je        0x4fb82d
004fb821 8b4708                   mov       eax, dword ptr [edi + 8]
004fb824 2bc1                     sub       eax, ecx
004fb826 c1f802                   sar       eax, 2
004fb829 85c0                     test      eax, eax
004fb82b 7707                     ja        0x4fb834
004fb82d 8bcf                     mov       ecx, edi
004fb82f e9                       .byte     0xe9
