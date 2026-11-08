004ba620 55                       push      ebp
004ba621 8bec                     mov       ebp, esp
004ba623 51                       push      ecx
004ba624 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004ba627 83f801                   cmp       eax, 1
004ba62a 53                       push      ebx
004ba62b 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004ba62e 56                       push      esi
004ba62f 57                       push      edi
004ba630 894dfc                   mov       dword ptr [ebp - 4], ecx
004ba633 751d                     jne       0x4ba652
004ba635 c70320030000             mov       dword ptr [ebx], 0x320
004ba63b d94518                   fld       dword ptr [ebp + 0x18]
004ba63e d80d5c14cd00             fmul      dword ptr [0xcd145c]
004ba644 e8fb6e7400               call      0xc01544
004ba649 8bf0                     mov       esi, eax
004ba64b 8bfe                     mov       edi, esi
004ba64d e9c4000000               jmp       0x4ba716
004ba652 83f802                   cmp       eax, 2
004ba655 7508                     jne       0x4ba65f
004ba657 c70390010000             mov       dword ptr [ebx], 0x190
004ba65d ebdc                     jmp       0x4ba63b
004ba65f 8a5514                   mov       dl, byte ptr [ebp + 0x14]
004ba662 84d2                     test      dl, dl
004ba664 740a                     je        0x4ba670
004ba666 c70300000000             mov       dword ptr [ebx], 0
004ba66c 33f6                     xor       esi, esi
004ba66e eb1d                     jmp       0x4ba68d
004ba670 83f8ff                   cmp       eax, -1
004ba673 750d                     jne       0x4ba682
004ba675 c70300000000             mov       dword ptr [ebx], 0
004ba67b be1e000000               mov       esi, 0x1e
004ba680 eb0b                     jmp       0x4ba68d
004ba682 c70390010000             mov       dword ptr [ebx], 0x190
004ba688 be96000000               mov       esi, 0x96
004ba68d 8b01                     mov       eax, dword ptr [ecx]
004ba68f 6a03                     push      3
004ba691 ff9044030000             call      dword ptr [eax + 0x344]
004ba697 8bf8                     mov       edi, eax
004ba699 8d8f18020000             lea       ecx, [edi + 0x218]
004ba69f e8bc79f4ff               call      0x402060
004ba6a4 894514                   mov       dword ptr [ebp + 0x14], eax
004ba6a7 db4514                   fild      dword ptr [ebp + 0x14]
004ba6aa 8d8f20020000             lea       ecx, [edi + 0x220]
004ba6b0 d95d14                   fstp      dword ptr [ebp + 0x14]
004ba6b3 e8f88cf7ff               call      0x4333b0
004ba6b8 d84d14                   fmul      dword ptr [ebp + 0x14]
004ba6bb e8846e7400               call      0xc01544
004ba6c0 b9d0070000               mov       ecx, 0x7d0
004ba6c5 2bc8                     sub       ecx, eax
004ba6c7 85c9                     test      ecx, ecx
004ba6c9 7e20                     jle       0x4ba6eb
004ba6cb 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004ba6ce 8b11                     mov       edx, dword ptr [ecx]
004ba6d0 6a03                     push      3
004ba6d2 ff9244030000             call      dword ptr [edx + 0x344]
004ba6d8 8bc8                     mov       ecx, eax
004ba6da e861360000               call      0x4bdd40
004ba6df b9d0070000               mov       ecx, 0x7d0
004ba6e4 2bc8                     sub       ecx, eax
004ba6e6 894d14                   mov       dword ptr [ebp + 0x14], ecx
004ba6e9 eb07                     jmp       0x4ba6f2
004ba6eb c7451400000000           mov       dword ptr [ebp + 0x14], 0
004ba6f2 db4514                   fild      dword ptr [ebp + 0x14]
004ba6f5 d80d4014cd00             fmul      dword ptr [0xcd1440]
004ba6fb e8446e7400               call      0xc01544
004ba700 894514                   mov       dword ptr [ebp + 0x14], eax
004ba703 db4514                   fild      dword ptr [ebp + 0x14]
004ba706 d84d18                   fmul      dword ptr [ebp + 0x18]
004ba709 e8366e7400               call      0xc01544
004ba70e 8bf8                     mov       edi, eax
004ba710 3bf7                     cmp       esi, edi
004ba712 7e02                     jle       0x4ba716
004ba714 8bf7                     mov       esi, edi
004ba716 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004ba719 81c1d8180000             add       ecx, 0x18d8
004ba71f e83c79f4ff               call      0x402060
004ba724 85c0                     test      eax, eax
004ba726 7512                     jne       0x4ba73a
004ba728 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba72b 8903                     mov       dword ptr [ebx], eax
004ba72d 8902                     mov       dword ptr [edx], eax
004ba72f 8bc7                     mov       eax, edi
004ba731 5f                       pop       edi
004ba732 5e                       pop       esi
004ba733 5b                       pop       ebx
004ba734 8be5                     mov       esp, ebp
004ba736 5d                       pop       ebp
004ba737 c21400                   ret       0x14
004ba73a 85f6                     test      esi, esi
004ba73c 7510                     jne       0x4ba74e
004ba73e 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba741 8bc7                     mov       eax, edi
004ba743 5f                       pop       edi
004ba744 8932                     mov       dword ptr [edx], esi
004ba746 5e                       pop       esi
004ba747 5b                       pop       ebx
004ba748 8be5                     mov       esp, ebp
004ba74a 5d                       pop       ebp
004ba74b c21400                   ret       0x14
004ba74e 8b03                     mov       eax, dword ptr [ebx]
004ba750 69c018fcffff             imul      eax, eax, 0xfffffc18
004ba756 99                       cdq       
004ba757 f7fe                     idiv      esi
004ba759 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ba75c 8901                     mov       dword ptr [ecx], eax
004ba75e 8bc7                     mov       eax, edi
004ba760 5f                       pop       edi
004ba761 5e                       pop       esi
004ba762 5b                       pop       ebx
004ba763 8be5                     mov       esp, ebp
004ba765 5d                       pop       ebp
004ba766 c21400                   ret       0x14
004ba769 cc                       int3      
004ba76a cc                       int3      
004ba76b cc                       int3      
004ba76c cc                       int3      
004ba76d cc                       int3      
004ba76e cc                       int3      
004ba76f cc                       int3      
004ba770 56                       push      esi
004ba771 8db15c150000             lea       esi, [ecx + 0x155c]
004ba777 8bce                     mov       ecx, esi
004ba779 e8e278f4ff               call      0x402060
004ba77e 85c0                     test      eax, eax
004ba780 7440                     je        0x4ba7c2
004ba782 8bce                     mov       ecx, esi
004ba784 e8d778f4ff               call      0x402060
004ba789 83f806                   cmp       eax, 6
004ba78c 7434                     je        0x4ba7c2
004ba78e 8bce                     mov       ecx, esi
004ba790 e8cb78f4ff               call      0x402060
004ba795 83f804                   cmp       eax, 4
004ba798 7428                     je        0x4ba7c2
004ba79a 8bce                     mov       ecx, esi
004ba79c e8bf78f4ff               call      0x402060
004ba7a1 83f801                   cmp       eax, 1
004ba7a4 741c                     je        0x4ba7c2
004ba7a6 8bce                     mov       ecx, esi
004ba7a8 e8b378f4ff               call      0x402060
004ba7ad 83f803                   cmp       eax, 3
004ba7b0 7410                     je        0x4ba7c2
004ba7b2 8bce                     mov       ecx, esi
004ba7b4 e8a778f4ff               call      0x402060
004ba7b9 83f809                   cmp       eax, 9
004ba7bc 7404                     je        0x4ba7c2
004ba7be b001                     mov       al, 1
004ba7c0 5e                       pop       esi
004ba7c1 c3                       ret       
004ba7c2 32c0                     xor       al, al
004ba7c4 5e                       pop       esi
004ba7c5 c3                       ret       
004ba7c6 cc                       int3      
004ba7c7 cc                       int3      
004ba7c8 cc                       int3      
004ba7c9 cc                       int3      
004ba7ca cc                       int3      
004ba7cb cc                       int3      
004ba7cc cc                       int3      
004ba7cd cc                       int3      
004ba7ce cc                       int3      
004ba7cf cc                       int3      
004ba7d0 55                       push      ebp
004ba7d1 8bec                     mov       ebp, esp
004ba7d3 83ec38                   sub       esp, 0x38
004ba7d6 53                       push      ebx
004ba7d7 56                       push      esi
004ba7d8 57                       push      edi
004ba7d9 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004ba7dc 8d4f60                   lea       ecx, [edi + 0x60]
004ba7df e81cc76400               call      0xb06f00
004ba7e4 8b7508                   mov       esi, dword ptr [ebp + 8]
004ba7e7 8945f8                   mov       dword ptr [ebp - 8], eax
004ba7ea 8b460c                   mov       eax, dword ptr [esi + 0xc]
004ba7ed 85c0                     test      eax, eax
004ba7ef 0f848c000000             je        0x4ba881
004ba7f5 8b4610                   mov       eax, dword ptr [esi + 0x10]
004ba7f8 8b5608                   mov       edx, dword ptr [esi + 8]
004ba7fb 8bf8                     mov       edi, eax
004ba7fd 8bc8                     mov       ecx, eax
004ba7ff 8bd8                     mov       ebx, eax
004ba801 81e1ff000000             and       ecx, 0xff
004ba807 c1ef08                   shr       edi, 8
004ba80a 8b3cba                   mov       edi, dword ptr [edx + edi*4]
004ba80d 25ff000000               and       eax, 0xff
004ba812 c1eb08                   shr       ebx, 8
004ba815 8b149a                   mov       edx, dword ptr [edx + ebx*4]
004ba818 8d0c89                   lea       ecx, [ecx + ecx*4]
004ba81b 8b4ccf24                 mov       ecx, dword ptr [edi + ecx*8 + 0x24]
004ba81f 8d0480                   lea       eax, [eax + eax*4]
004ba822 8b7cc218                 mov       edi, dword ptr [edx + eax*8 + 0x18]
004ba826 8b45f8                   mov       eax, dword ptr [ebp - 8]
004ba829 03cf                     add       ecx, edi
004ba82b 3bc8                     cmp       ecx, eax
004ba82d 734f                     jae       0x4ba87e
004ba82f 8b460c                   mov       eax, dword ptr [esi + 0xc]
004ba832 85c0                     test      eax, eax
004ba834 7448                     je        0x4ba87e
004ba836 8b4610                   mov       eax, dword ptr [esi + 0x10]
004ba839 40                       inc       eax
004ba83a 3d00010000               cmp       eax, 0x100
004ba83f 894610                   mov       dword ptr [esi + 0x10], eax
004ba842 752b                     jne       0x4ba86f
004ba844 8b5608                   mov       edx, dword ptr [esi + 8]
004ba847 8b3a                     mov       edi, dword ptr [edx]
004ba849 8b5604                   mov       edx, dword ptr [esi + 4]
004ba84c 33c0                     xor       eax, eax
004ba84e 4a                       dec       edx
004ba84f 7411                     je        0x4ba862
004ba851 8b4e08                   mov       ecx, dword ptr [esi + 8]
004ba854 8b5c8104                 mov       ebx, dword ptr [ecx + eax*4 + 4]
004ba858 8d0c81                   lea       ecx, [ecx + eax*4]
004ba85b 40                       inc       eax
004ba85c 3bc2                     cmp       eax, edx
004ba85e 8919                     mov       dword ptr [ecx], ebx
004ba860 72ef                     jb        0x4ba851
004ba862 8b5608                   mov       edx, dword ptr [esi + 8]
004ba865 893c82                   mov       dword ptr [edx + eax*4], edi
004ba868 c7461000000000           mov       dword ptr [esi + 0x10], 0
004ba86f 8b460c                   mov       eax, dword ptr [esi + 0xc]
004ba872 48                       dec       eax
004ba873 85c0                     test      eax, eax
004ba875 89460c                   mov       dword ptr [esi + 0xc], eax
004ba878 0f8577ffffff             jne       0x4ba7f5
004ba87e 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004ba881 8b07                     mov       eax, dword ptr [edi]
004ba883 8bcf                     mov       ecx, edi
004ba885 ff9004010000             call      dword ptr [eax + 0x104]
004ba88b 85c0                     test      eax, eax
004ba88d 8bcf                     mov       ecx, edi
004ba88f 7411                     je        0x4ba8a2
004ba891 8b17                     mov       edx, dword ptr [edi]
004ba893 ff9204010000             call      dword ptr [edx + 0x104]
004ba899 8bc8                     mov       ecx, eax
004ba89b e810275700               call      0xa2cfb0
004ba8a0 eb08                     jmp       0x4ba8aa
004ba8a2 8b07                     mov       eax, dword ptr [edi]
004ba8a4 ff90f4000000             call      dword ptr [eax + 0xf4]
004ba8aa 85c0                     test      eax, eax
004ba8ac 894508                   mov       dword ptr [ebp + 8], eax
004ba8af 0f8448010000             je        0x4ba9fd
004ba8b5 8b4610                   mov       eax, dword ptr [esi + 0x10]
004ba8b8 8945ec                   mov       dword ptr [ebp - 0x14], eax
004ba8bb eb03                     jmp       0x4ba8c0
004ba8bd 8d4900                   lea       ecx, [ecx]
004ba8c0 8b4e10                   mov       ecx, dword ptr [esi + 0x10]
004ba8c3 034e0c                   add       ecx, dword ptr [esi + 0xc]
004ba8c6 3bc1                     cmp       eax, ecx
004ba8c8 0f842f010000             je        0x4ba9fd
004ba8ce 8b4e08                   mov       ecx, dword ptr [esi + 8]
004ba8d1 8bd8                     mov       ebx, eax
004ba8d3 25ff000000               and       eax, 0xff
004ba8d8 8d0480                   lea       eax, [eax + eax*4]
004ba8db c1eb08                   shr       ebx, 8
004ba8de c1e003                   shl       eax, 3
004ba8e1 c1e302                   shl       ebx, 2
004ba8e4 8b140b                   mov       edx, dword ptr [ebx + ecx]
004ba8e7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ba8ea 8945fc                   mov       dword ptr [ebp - 4], eax
004ba8ed 8b44021c                 mov       eax, dword ptr [edx + eax + 0x1c]
004ba8f1 50                       push      eax
004ba8f2 e899a45600               call      0xa24d90
004ba8f7 85c0                     test      eax, eax
004ba8f9 8945f0                   mov       dword ptr [ebp - 0x10], eax
004ba8fc 0f84ef000000             je        0x4ba9f1
004ba902 8b4e08                   mov       ecx, dword ptr [esi + 8]
004ba905 8b140b                   mov       edx, dword ptr [ebx + ecx]
004ba908 8b45fc                   mov       eax, dword ptr [ebp - 4]
004ba90b 8b4c1020                 mov       ecx, dword ptr [eax + edx + 0x20]
004ba90f 03c2                     add       eax, edx
004ba911 8b5024                   mov       edx, dword ptr [eax + 0x24]
004ba914 52                       push      edx
004ba915 894d0c                   mov       dword ptr [ebp + 0xc], ecx
004ba918 8b4df8                   mov       ecx, dword ptr [ebp - 8]
004ba91b 2b4818                   sub       ecx, dword ptr [eax + 0x18]
004ba91e 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ba921 c1ea18                   shr       edx, 0x18
004ba924 51                       push      ecx
004ba925 8955f4                   mov       dword ptr [ebp - 0xc], edx
004ba928 db45f4                   fild      dword ptr [ebp - 0xc]
004ba92b 6a00                     push      0
004ba92d 51                       push      ecx
004ba92e d91c24                   fstp      dword ptr [esp]
004ba931 e87af06400               call      0xb099b0
004ba936 83c410                   add       esp, 0x10
004ba939 e8066c7400               call      0xc01544
004ba93e 8b4e08                   mov       ecx, dword ptr [esi + 8]
004ba941 8b140b                   mov       edx, dword ptr [ebx + ecx]
004ba944 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004ba947 03ca                     add       ecx, edx
004ba949 8b5104                   mov       edx, dword ptr [ecx + 4]
004ba94c 8955c8                   mov       dword ptr [ebp - 0x38], edx
004ba94f 0fb6550e                 movzx     edx, byte ptr [ebp + 0xe]
004ba953 8af0                     mov       dh, al
004ba955 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ba958 c1e808                   shr       eax, 8
004ba95b 0fb6c0                   movzx     eax, al
004ba95e 894df4                   mov       dword ptr [ebp - 0xc], ecx
004ba961 c1e208                   shl       edx, 8
004ba964 0bd0                     or        edx, eax
004ba966 0fb6450c                 movzx     eax, byte ptr [ebp + 0xc]
004ba96a c1e208                   shl       edx, 8
004ba96d 0bd0                     or        edx, eax
004ba96f 8a01                     mov       al, byte ptr [ecx]
004ba971 8955dc                   mov       dword ptr [ebp - 0x24], edx
004ba974 8b5114                   mov       edx, dword ptr [ecx + 0x14]
004ba977 8955d8                   mov       dword ptr [ebp - 0x28], edx
004ba97a 8b17                     mov       edx, dword ptr [edi]
004ba97c 8bcf                     mov       ecx, edi
004ba97e c745e402000000           mov       dword ptr [ebp - 0x1c], 2
004ba985 8845d4                   mov       byte ptr [ebp - 0x2c], al
004ba988 ff5228                   call      dword ptr [edx + 0x28]
004ba98b 8b400c                   mov       eax, dword ptr [eax + 0xc]
004ba98e 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004ba991 8b5108                   mov       edx, dword ptr [ecx + 8]
004ba994 50                       push      eax
004ba995 8b07                     mov       eax, dword ptr [edi]
004ba997 52                       push      edx
004ba998 8bcf                     mov       ecx, edi
004ba99a ff505c                   call      dword ptr [eax + 0x5c]
004ba99d 8bc8                     mov       ecx, eax
004ba99f e85c000500               call      0x50aa00
004ba9a4 8b4e08                   mov       ecx, dword ptr [esi + 8]
004ba9a7 8b140b                   mov       edx, dword ptr [ebx + ecx]
004ba9aa 8945cc                   mov       dword ptr [ebp - 0x34], eax
004ba9ad 8b45fc                   mov       eax, dword ptr [ebp - 4]
