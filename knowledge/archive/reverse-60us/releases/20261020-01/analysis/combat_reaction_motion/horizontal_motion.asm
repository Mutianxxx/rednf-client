004ba620 55                       push       ebp
004ba621 8bec                     mov        ebp, esp
004ba623 51                       push       ecx
004ba624 8b4510                   mov        eax, dword ptr [ebp + 0x10]
004ba627 83f801                   cmp        eax, 1
004ba62a 53                       push       ebx
004ba62b 8b5d08                   mov        ebx, dword ptr [ebp + 8]
004ba62e 56                       push       esi
004ba62f 57                       push       edi
004ba630 894dfc                   mov        dword ptr [ebp - 4], ecx
004ba633 751d                     jne        0x4ba652
004ba635 c70320030000             mov        dword ptr [ebx], 0x320
004ba63b d94518                   fld        dword ptr [ebp + 0x18]
004ba63e d80d5c14cd00             fmul       dword ptr [0xcd145c]
004ba644 e8fb6e7400               call       0xc01544
004ba649 8bf0                     mov        esi, eax
004ba64b 8bfe                     mov        edi, esi
004ba64d e9c4000000               jmp        0x4ba716
004ba652 83f802                   cmp        eax, 2
004ba655 7508                     jne        0x4ba65f
004ba657 c70390010000             mov        dword ptr [ebx], 0x190
004ba65d ebdc                     jmp        0x4ba63b
004ba65f 8a5514                   mov        dl, byte ptr [ebp + 0x14]
004ba662 84d2                     test       dl, dl
004ba664 740a                     je         0x4ba670
004ba666 c70300000000             mov        dword ptr [ebx], 0
004ba66c 33f6                     xor        esi, esi
004ba66e eb1d                     jmp        0x4ba68d
004ba670 83f8ff                   cmp        eax, -1
004ba673 750d                     jne        0x4ba682
004ba675 c70300000000             mov        dword ptr [ebx], 0
004ba67b be1e000000               mov        esi, 0x1e
004ba680 eb0b                     jmp        0x4ba68d
004ba682 c70390010000             mov        dword ptr [ebx], 0x190
004ba688 be96000000               mov        esi, 0x96
004ba68d 8b01                     mov        eax, dword ptr [ecx]
004ba68f 6a03                     push       3
004ba691 ff9044030000             call       dword ptr [eax + 0x344]
004ba697 8bf8                     mov        edi, eax
004ba699 8d8f18020000             lea        ecx, [edi + 0x218]
004ba69f e8bc79f4ff               call       0x402060
004ba6a4 894514                   mov        dword ptr [ebp + 0x14], eax
004ba6a7 db4514                   fild       dword ptr [ebp + 0x14]
004ba6aa 8d8f20020000             lea        ecx, [edi + 0x220]
004ba6b0 d95d14                   fstp       dword ptr [ebp + 0x14]
004ba6b3 e8f88cf7ff               call       0x4333b0
004ba6b8 d84d14                   fmul       dword ptr [ebp + 0x14]
004ba6bb e8846e7400               call       0xc01544
004ba6c0 b9d0070000               mov        ecx, 0x7d0
004ba6c5 2bc8                     sub        ecx, eax
004ba6c7 85c9                     test       ecx, ecx
004ba6c9 7e20                     jle        0x4ba6eb
004ba6cb 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004ba6ce 8b11                     mov        edx, dword ptr [ecx]
004ba6d0 6a03                     push       3
004ba6d2 ff9244030000             call       dword ptr [edx + 0x344]
004ba6d8 8bc8                     mov        ecx, eax
004ba6da e861360000               call       0x4bdd40
004ba6df b9d0070000               mov        ecx, 0x7d0
004ba6e4 2bc8                     sub        ecx, eax
004ba6e6 894d14                   mov        dword ptr [ebp + 0x14], ecx
004ba6e9 eb07                     jmp        0x4ba6f2
004ba6eb c7451400000000           mov        dword ptr [ebp + 0x14], 0
004ba6f2 db4514                   fild       dword ptr [ebp + 0x14]
004ba6f5 d80d4014cd00             fmul       dword ptr [0xcd1440]
004ba6fb e8446e7400               call       0xc01544
004ba700 894514                   mov        dword ptr [ebp + 0x14], eax
004ba703 db4514                   fild       dword ptr [ebp + 0x14]
004ba706 d84d18                   fmul       dword ptr [ebp + 0x18]
004ba709 e8366e7400               call       0xc01544
004ba70e 8bf8                     mov        edi, eax
004ba710 3bf7                     cmp        esi, edi
004ba712 7e02                     jle        0x4ba716
004ba714 8bf7                     mov        esi, edi
004ba716 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004ba719 81c1d8180000             add        ecx, 0x18d8
004ba71f e83c79f4ff               call       0x402060
004ba724 85c0                     test       eax, eax
004ba726 7512                     jne        0x4ba73a
004ba728 8b550c                   mov        edx, dword ptr [ebp + 0xc]
004ba72b 8903                     mov        dword ptr [ebx], eax
004ba72d 8902                     mov        dword ptr [edx], eax
004ba72f 8bc7                     mov        eax, edi
004ba731 5f                       pop        edi
004ba732 5e                       pop        esi
004ba733 5b                       pop        ebx
004ba734 8be5                     mov        esp, ebp
004ba736 5d                       pop        ebp
004ba737 c21400                   ret        0x14
004ba73a 85f6                     test       esi, esi
004ba73c 7510                     jne        0x4ba74e
004ba73e 8b550c                   mov        edx, dword ptr [ebp + 0xc]
004ba741 8bc7                     mov        eax, edi
004ba743 5f                       pop        edi
004ba744 8932                     mov        dword ptr [edx], esi
004ba746 5e                       pop        esi
004ba747 5b                       pop        ebx
004ba748 8be5                     mov        esp, ebp
004ba74a 5d                       pop        ebp
004ba74b c21400                   ret        0x14
004ba74e 8b03                     mov        eax, dword ptr [ebx]
004ba750 69c018fcffff             imul       eax, eax, 0xfffffc18
004ba756 99                       cdq        
004ba757 f7fe                     idiv       esi
004ba759 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004ba75c 8901                     mov        dword ptr [ecx], eax
004ba75e 8bc7                     mov        eax, edi
004ba760 5f                       pop        edi
004ba761 5e                       pop        esi
004ba762 5b                       pop        ebx
004ba763 8be5                     mov        esp, ebp
004ba765 5d                       pop        ebp
004ba766 c21400                   ret        0x14
