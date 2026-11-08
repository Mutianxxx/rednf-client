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
004fb82f e96c82feff               jmp       0x4e3aa0
004fb834 8b09                     mov       ecx, dword ptr [ecx]
004fb836 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fb83c 84c0                     test      al, al
004fb83e 7427                     je        0x4fb867
004fb840 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb843 85c9                     test      ecx, ecx
004fb845 740c                     je        0x4fb853
004fb847 8b4708                   mov       eax, dword ptr [edi + 8]
004fb84a 2bc1                     sub       eax, ecx
004fb84c c1f802                   sar       eax, 2
004fb84f 85c0                     test      eax, eax
004fb851 7707                     ja        0x4fb85a
004fb853 8bcf                     mov       ecx, edi
004fb855 e94682feff               jmp       0x4e3aa0
004fb85a 8b01                     mov       eax, dword ptr [ecx]
004fb85c 8b16                     mov       edx, dword ptr [esi]
004fb85e 50                       push      eax
004fb85f 8bce                     mov       ecx, esi
004fb861 ff92fc000000             call      dword ptr [edx + 0xfc]
004fb867 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb86a 85c9                     test      ecx, ecx
004fb86c 740d                     je        0x4fb87b
004fb86e 8b4708                   mov       eax, dword ptr [edi + 8]
004fb871 2bc1                     sub       eax, ecx
004fb873 c1f802                   sar       eax, 2
004fb876 83f801                   cmp       eax, 1
004fb879 7707                     ja        0x4fb882
004fb87b 8bcf                     mov       ecx, edi
004fb87d e91e82feff               jmp       0x4e3aa0
004fb882 8b4104                   mov       eax, dword ptr [ecx + 4]
004fb885 85c0                     test      eax, eax
004fb887 0f84c8000000             je        0x4fb955
004fb88d 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb890 85c9                     test      ecx, ecx
004fb892 740d                     je        0x4fb8a1
004fb894 8b4708                   mov       eax, dword ptr [edi + 8]
004fb897 2bc1                     sub       eax, ecx
004fb899 c1f802                   sar       eax, 2
004fb89c 83f802                   cmp       eax, 2
004fb89f 7707                     ja        0x4fb8a8
004fb8a1 8bcf                     mov       ecx, edi
004fb8a3 e9f881feff               jmp       0x4e3aa0
004fb8a8 8b4108                   mov       eax, dword ptr [ecx + 8]
004fb8ab 85c0                     test      eax, eax
004fb8ad 0f84a2000000             je        0x4fb955
004fb8b3 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb8b6 85c9                     test      ecx, ecx
004fb8b8 740d                     je        0x4fb8c7
004fb8ba 8b4708                   mov       eax, dword ptr [edi + 8]
004fb8bd 2bc1                     sub       eax, ecx
004fb8bf c1f802                   sar       eax, 2
004fb8c2 83f801                   cmp       eax, 1
004fb8c5 7707                     ja        0x4fb8ce
004fb8c7 8bcf                     mov       ecx, edi
004fb8c9 e9d281feff               jmp       0x4e3aa0
004fb8ce 8b4904                   mov       ecx, dword ptr [ecx + 4]
004fb8d1 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fb8d7 84c0                     test      al, al
004fb8d9 747a                     je        0x4fb955
004fb8db 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb8de 85c9                     test      ecx, ecx
004fb8e0 740d                     je        0x4fb8ef
004fb8e2 8b4708                   mov       eax, dword ptr [edi + 8]
004fb8e5 2bc1                     sub       eax, ecx
004fb8e7 c1f802                   sar       eax, 2
004fb8ea 83f802                   cmp       eax, 2
004fb8ed 7707                     ja        0x4fb8f6
004fb8ef 8bcf                     mov       ecx, edi
004fb8f1 e9aa81feff               jmp       0x4e3aa0
004fb8f6 8b5108                   mov       edx, dword ptr [ecx + 8]
004fb8f9 8a823a010000             mov       al, byte ptr [edx + 0x13a]
004fb8ff 84c0                     test      al, al
004fb901 7452                     je        0x4fb955
004fb903 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb906 85c9                     test      ecx, ecx
004fb908 740d                     je        0x4fb917
004fb90a 8b4708                   mov       eax, dword ptr [edi + 8]
004fb90d 2bc1                     sub       eax, ecx
004fb90f c1f802                   sar       eax, 2
004fb912 83f801                   cmp       eax, 1
004fb915 7707                     ja        0x4fb91e
004fb917 8bcf                     mov       ecx, edi
004fb919 e98281feff               jmp       0x4e3aa0
004fb91e 8b4904                   mov       ecx, dword ptr [ecx + 4]
004fb921 8b06                     mov       eax, dword ptr [esi]
004fb923 51                       push      ecx
004fb924 8bce                     mov       ecx, esi
004fb926 ff90fc000000             call      dword ptr [eax + 0xfc]
004fb92c 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb92f 85c9                     test      ecx, ecx
004fb931 740d                     je        0x4fb940
004fb933 8b4708                   mov       eax, dword ptr [edi + 8]
004fb936 2bc1                     sub       eax, ecx
004fb938 c1f802                   sar       eax, 2
004fb93b 83f802                   cmp       eax, 2
004fb93e 7707                     ja        0x4fb947
004fb940 8bcf                     mov       ecx, edi
004fb942 e95981feff               jmp       0x4e3aa0
004fb947 8b4108                   mov       eax, dword ptr [ecx + 8]
004fb94a 8b16                     mov       edx, dword ptr [esi]
004fb94c 50                       push      eax
004fb94d 8bce                     mov       ecx, esi
004fb94f ff92fc000000             call      dword ptr [edx + 0xfc]
004fb955 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb958 85c9                     test      ecx, ecx
004fb95a 740d                     je        0x4fb969
004fb95c 8b4708                   mov       eax, dword ptr [edi + 8]
004fb95f 2bc1                     sub       eax, ecx
004fb961 c1f802                   sar       eax, 2
004fb964 83f803                   cmp       eax, 3
004fb967 7707                     ja        0x4fb970
004fb969 8bcf                     mov       ecx, edi
004fb96b e93081feff               jmp       0x4e3aa0
004fb970 8b410c                   mov       eax, dword ptr [ecx + 0xc]
004fb973 85c0                     test      eax, eax
004fb975 0f84c8000000             je        0x4fba43
004fb97b 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb97e 85c9                     test      ecx, ecx
004fb980 740d                     je        0x4fb98f
004fb982 8b4708                   mov       eax, dword ptr [edi + 8]
004fb985 2bc1                     sub       eax, ecx
004fb987 c1f802                   sar       eax, 2
004fb98a 83f804                   cmp       eax, 4
004fb98d 7707                     ja        0x4fb996
004fb98f 8bcf                     mov       ecx, edi
004fb991 e90a81feff               jmp       0x4e3aa0
004fb996 8b4110                   mov       eax, dword ptr [ecx + 0x10]
004fb999 85c0                     test      eax, eax
004fb99b 0f84a2000000             je        0x4fba43
004fb9a1 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb9a4 85c9                     test      ecx, ecx
004fb9a6 740d                     je        0x4fb9b5
004fb9a8 8b4708                   mov       eax, dword ptr [edi + 8]
004fb9ab 2bc1                     sub       eax, ecx
004fb9ad c1f802                   sar       eax, 2
004fb9b0 83f803                   cmp       eax, 3
004fb9b3 7707                     ja        0x4fb9bc
004fb9b5 8bcf                     mov       ecx, edi
004fb9b7 e9e480feff               jmp       0x4e3aa0
004fb9bc 8b490c                   mov       ecx, dword ptr [ecx + 0xc]
004fb9bf 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fb9c5 84c0                     test      al, al
004fb9c7 747a                     je        0x4fba43
004fb9c9 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb9cc 85c9                     test      ecx, ecx
004fb9ce 740d                     je        0x4fb9dd
004fb9d0 8b4708                   mov       eax, dword ptr [edi + 8]
004fb9d3 2bc1                     sub       eax, ecx
004fb9d5 c1f802                   sar       eax, 2
004fb9d8 83f804                   cmp       eax, 4
004fb9db 7707                     ja        0x4fb9e4
004fb9dd 8bcf                     mov       ecx, edi
004fb9df e9bc80feff               jmp       0x4e3aa0
004fb9e4 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004fb9e7 8a823a010000             mov       al, byte ptr [edx + 0x13a]
004fb9ed 84c0                     test      al, al
004fb9ef 7452                     je        0x4fba43
004fb9f1 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fb9f4 85c9                     test      ecx, ecx
004fb9f6 740d                     je        0x4fba05
004fb9f8 8b4708                   mov       eax, dword ptr [edi + 8]
004fb9fb 2bc1                     sub       eax, ecx
004fb9fd c1f802                   sar       eax, 2
004fba00 83f803                   cmp       eax, 3
004fba03 7707                     ja        0x4fba0c
004fba05 8bcf                     mov       ecx, edi
004fba07 e99480feff               jmp       0x4e3aa0
004fba0c 8b490c                   mov       ecx, dword ptr [ecx + 0xc]
004fba0f 8b06                     mov       eax, dword ptr [esi]
004fba11 51                       push      ecx
004fba12 8bce                     mov       ecx, esi
004fba14 ff90fc000000             call      dword ptr [eax + 0xfc]
004fba1a 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fba1d 85c9                     test      ecx, ecx
004fba1f 740d                     je        0x4fba2e
004fba21 8b4708                   mov       eax, dword ptr [edi + 8]
004fba24 2bc1                     sub       eax, ecx
004fba26 c1f802                   sar       eax, 2
004fba29 83f804                   cmp       eax, 4
004fba2c 7707                     ja        0x4fba35
004fba2e 8bcf                     mov       ecx, edi
004fba30 e96b80feff               jmp       0x4e3aa0
004fba35 8b4110                   mov       eax, dword ptr [ecx + 0x10]
004fba38 8b16                     mov       edx, dword ptr [esi]
004fba3a 50                       push      eax
004fba3b 8bce                     mov       ecx, esi
004fba3d ff92fc000000             call      dword ptr [edx + 0xfc]
004fba43 8b86a41a0000             mov       eax, dword ptr [esi + 0x1aa4]
004fba49 85c0                     test      eax, eax
004fba4b 0f8469020000             je        0x4fbcba
004fba51 8b8e18240000             mov       ecx, dword ptr [esi + 0x2418]
004fba57 85c9                     test      ecx, ecx
004fba59 8dbe14240000             lea       edi, [esi + 0x2414]
004fba5f 0f8455020000             je        0x4fbcba
004fba65 8b4708                   mov       eax, dword ptr [edi + 8]
004fba68 2bc1                     sub       eax, ecx
004fba6a c1f802                   sar       eax, 2
004fba6d 85c0                     test      eax, eax
004fba6f 0f8445020000             je        0x4fbcba
004fba75 85c9                     test      ecx, ecx
004fba77 740c                     je        0x4fba85
004fba79 8b4708                   mov       eax, dword ptr [edi + 8]
004fba7c 2bc1                     sub       eax, ecx
004fba7e c1f802                   sar       eax, 2
004fba81 85c0                     test      eax, eax
004fba83 7707                     ja        0x4fba8c
004fba85 8bcf                     mov       ecx, edi
004fba87 e91480feff               jmp       0x4e3aa0
004fba8c 833900                   cmp       dword ptr [ecx], 0
004fba8f 744d                     je        0x4fbade
004fba91 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fba94 85c9                     test      ecx, ecx
004fba96 740c                     je        0x4fbaa4
004fba98 8b4708                   mov       eax, dword ptr [edi + 8]
004fba9b 2bc1                     sub       eax, ecx
004fba9d c1f802                   sar       eax, 2
004fbaa0 85c0                     test      eax, eax
004fbaa2 7707                     ja        0x4fbaab
004fbaa4 8bcf                     mov       ecx, edi
004fbaa6 e9f57ffeff               jmp       0x4e3aa0
004fbaab 8b09                     mov       ecx, dword ptr [ecx]
004fbaad 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fbab3 84c0                     test      al, al
004fbab5 7427                     je        0x4fbade
004fbab7 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbaba 85c9                     test      ecx, ecx
004fbabc 740c                     je        0x4fbaca
004fbabe 8b4708                   mov       eax, dword ptr [edi + 8]
004fbac1 2bc1                     sub       eax, ecx
004fbac3 c1f802                   sar       eax, 2
004fbac6 85c0                     test      eax, eax
004fbac8 7707                     ja        0x4fbad1
004fbaca 8bcf                     mov       ecx, edi
004fbacc e9cf7ffeff               jmp       0x4e3aa0
004fbad1 8b01                     mov       eax, dword ptr [ecx]
004fbad3 8b16                     mov       edx, dword ptr [esi]
004fbad5 50                       push      eax
004fbad6 8bce                     mov       ecx, esi
004fbad8 ff92fc000000             call      dword ptr [edx + 0xfc]
004fbade 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbae1 85c9                     test      ecx, ecx
004fbae3 740d                     je        0x4fbaf2
004fbae5 8b4708                   mov       eax, dword ptr [edi + 8]
004fbae8 2bc1                     sub       eax, ecx
004fbaea c1f802                   sar       eax, 2
004fbaed 83f801                   cmp       eax, 1
004fbaf0 7707                     ja        0x4fbaf9
004fbaf2 8bcf                     mov       ecx, edi
004fbaf4 e9a77ffeff               jmp       0x4e3aa0
004fbaf9 8b4104                   mov       eax, dword ptr [ecx + 4]
004fbafc 85c0                     test      eax, eax
004fbafe 0f84c8000000             je        0x4fbbcc
004fbb04 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbb07 85c9                     test      ecx, ecx
004fbb09 740d                     je        0x4fbb18
004fbb0b 8b4708                   mov       eax, dword ptr [edi + 8]
004fbb0e 2bc1                     sub       eax, ecx
004fbb10 c1f802                   sar       eax, 2
004fbb13 83f802                   cmp       eax, 2
004fbb16 7707                     ja        0x4fbb1f
004fbb18 8bcf                     mov       ecx, edi
004fbb1a e9817ffeff               jmp       0x4e3aa0
004fbb1f 8b4108                   mov       eax, dword ptr [ecx + 8]
004fbb22 85c0                     test      eax, eax
004fbb24 0f84a2000000             je        0x4fbbcc
004fbb2a 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbb2d 85c9                     test      ecx, ecx
004fbb2f 740d                     je        0x4fbb3e
004fbb31 8b4708                   mov       eax, dword ptr [edi + 8]
004fbb34 2bc1                     sub       eax, ecx
004fbb36 c1f802                   sar       eax, 2
004fbb39 83f801                   cmp       eax, 1
004fbb3c 7707                     ja        0x4fbb45
004fbb3e 8bcf                     mov       ecx, edi
004fbb40 e95b7ffeff               jmp       0x4e3aa0
004fbb45 8b4904                   mov       ecx, dword ptr [ecx + 4]
004fbb48 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fbb4e 84c0                     test      al, al
004fbb50 747a                     je        0x4fbbcc
004fbb52 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbb55 85c9                     test      ecx, ecx
004fbb57 740d                     je        0x4fbb66
004fbb59 8b4708                   mov       eax, dword ptr [edi + 8]
004fbb5c 2bc1                     sub       eax, ecx
004fbb5e c1f802                   sar       eax, 2
004fbb61 83f802                   cmp       eax, 2
004fbb64 7707                     ja        0x4fbb6d
004fbb66 8bcf                     mov       ecx, edi
004fbb68 e9337ffeff               jmp       0x4e3aa0
004fbb6d 8b5108                   mov       edx, dword ptr [ecx + 8]
004fbb70 8a823a010000             mov       al, byte ptr [edx + 0x13a]
004fbb76 84c0                     test      al, al
004fbb78 7452                     je        0x4fbbcc
004fbb7a 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbb7d 85c9                     test      ecx, ecx
004fbb7f 740d                     je        0x4fbb8e
004fbb81 8b4708                   mov       eax, dword ptr [edi + 8]
004fbb84 2bc1                     sub       eax, ecx
004fbb86 c1f802                   sar       eax, 2
004fbb89 83f801                   cmp       eax, 1
004fbb8c 7707                     ja        0x4fbb95
004fbb8e 8bcf                     mov       ecx, edi
004fbb90 e90b7ffeff               jmp       0x4e3aa0
004fbb95 8b4904                   mov       ecx, dword ptr [ecx + 4]
004fbb98 8b06                     mov       eax, dword ptr [esi]
004fbb9a 51                       push      ecx
004fbb9b 8bce                     mov       ecx, esi
004fbb9d ff90fc000000             call      dword ptr [eax + 0xfc]
004fbba3 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbba6 85c9                     test      ecx, ecx
004fbba8 740d                     je        0x4fbbb7
004fbbaa 8b4708                   mov       eax, dword ptr [edi + 8]
004fbbad 2bc1                     sub       eax, ecx
004fbbaf c1f802                   sar       eax, 2
004fbbb2 83f802                   cmp       eax, 2
004fbbb5 7707                     ja        0x4fbbbe
004fbbb7 8bcf                     mov       ecx, edi
004fbbb9 e9e27efeff               jmp       0x4e3aa0
004fbbbe 8b4108                   mov       eax, dword ptr [ecx + 8]
004fbbc1 8b16                     mov       edx, dword ptr [esi]
004fbbc3 50                       push      eax
004fbbc4 8bce                     mov       ecx, esi
004fbbc6 ff92fc000000             call      dword ptr [edx + 0xfc]
004fbbcc 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbbcf 85c9                     test      ecx, ecx
004fbbd1 740d                     je        0x4fbbe0
004fbbd3 8b4708                   mov       eax, dword ptr [edi + 8]
004fbbd6 2bc1                     sub       eax, ecx
004fbbd8 c1f802                   sar       eax, 2
004fbbdb 83f803                   cmp       eax, 3
004fbbde 7707                     ja        0x4fbbe7
004fbbe0 8bcf                     mov       ecx, edi
004fbbe2 e9b97efeff               jmp       0x4e3aa0
004fbbe7 8b410c                   mov       eax, dword ptr [ecx + 0xc]
004fbbea 85c0                     test      eax, eax
004fbbec 0f84c8000000             je        0x4fbcba
004fbbf2 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbbf5 85c9                     test      ecx, ecx
004fbbf7 740d                     je        0x4fbc06
004fbbf9 8b4708                   mov       eax, dword ptr [edi + 8]
004fbbfc 2bc1                     sub       eax, ecx
004fbbfe c1f802                   sar       eax, 2
004fbc01 83f804                   cmp       eax, 4
004fbc04 7707                     ja        0x4fbc0d
004fbc06 8bcf                     mov       ecx, edi
004fbc08 e9937efeff               jmp       0x4e3aa0
004fbc0d 8b4110                   mov       eax, dword ptr [ecx + 0x10]
004fbc10 85c0                     test      eax, eax
004fbc12 0f84a2000000             je        0x4fbcba
004fbc18 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbc1b 85c9                     test      ecx, ecx
004fbc1d 740d                     je        0x4fbc2c
004fbc1f 8b4708                   mov       eax, dword ptr [edi + 8]
004fbc22 2bc1                     sub       eax, ecx
004fbc24 c1f802                   sar       eax, 2
004fbc27 83f803                   cmp       eax, 3
004fbc2a 7707                     ja        0x4fbc33
004fbc2c 8bcf                     mov       ecx, edi
004fbc2e e96d7efeff               jmp       0x4e3aa0
004fbc33 8b490c                   mov       ecx, dword ptr [ecx + 0xc]
004fbc36 8a813a010000             mov       al, byte ptr [ecx + 0x13a]
004fbc3c 84c0                     test      al, al
004fbc3e 747a                     je        0x4fbcba
004fbc40 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbc43 85c9                     test      ecx, ecx
004fbc45 740d                     je        0x4fbc54
004fbc47 8b4708                   mov       eax, dword ptr [edi + 8]
004fbc4a 2bc1                     sub       eax, ecx
004fbc4c c1f802                   sar       eax, 2
004fbc4f 83f804                   cmp       eax, 4
004fbc52 7707                     ja        0x4fbc5b
004fbc54 8bcf                     mov       ecx, edi
004fbc56 e9457efeff               jmp       0x4e3aa0
004fbc5b 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004fbc5e 8a823a010000             mov       al, byte ptr [edx + 0x13a]
004fbc64 84c0                     test      al, al
004fbc66 7452                     je        0x4fbcba
004fbc68 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbc6b 85c9                     test      ecx, ecx
004fbc6d 740d                     je        0x4fbc7c
004fbc6f 8b4708                   mov       eax, dword ptr [edi + 8]
004fbc72 2bc1                     sub       eax, ecx
004fbc74 c1f802                   sar       eax, 2
004fbc77 83f803                   cmp       eax, 3
004fbc7a 7707                     ja        0x4fbc83
004fbc7c 8bcf                     mov       ecx, edi
004fbc7e e91d7efeff               jmp       0x4e3aa0
004fbc83 8b490c                   mov       ecx, dword ptr [ecx + 0xc]
004fbc86 8b06                     mov       eax, dword ptr [esi]
004fbc88 51                       push      ecx
004fbc89 8bce                     mov       ecx, esi
004fbc8b ff90fc000000             call      dword ptr [eax + 0xfc]
004fbc91 8b4f04                   mov       ecx, dword ptr [edi + 4]
004fbc94 85c9                     test      ecx, ecx
004fbc96 740d                     je        0x4fbca5
004fbc98 8b4708                   mov       eax, dword ptr [edi + 8]
004fbc9b 2bc1                     sub       eax, ecx
004fbc9d c1f802                   sar       eax, 2
004fbca0 83f804                   cmp       eax, 4
004fbca3 7707                     ja        0x4fbcac
004fbca5 8bcf                     mov       ecx, edi
004fbca7 e9f47dfeff               jmp       0x4e3aa0
004fbcac 8b4110                   mov       eax, dword ptr [ecx + 0x10]
004fbcaf 8b16                     mov       edx, dword ptr [esi]
004fbcb1 50                       push      eax
004fbcb2 8bce                     mov       ecx, esi
004fbcb4 ff92fc000000             call      dword ptr [edx + 0xfc]
004fbcba 33ff                     xor       edi, edi
004fbcbc 53                       push      ebx
004fbcbd 33db                     xor       ebx, ebx
004fbcbf 897df4                   mov       dword ptr [ebp - 0xc], edi
004fbcc2 8b8eec230000             mov       ecx, dword ptr [esi + 0x23ec]
004fbcc8 85c9                     test      ecx, ecx
004fbcca 0f8431010000             je        0x4fbe01
