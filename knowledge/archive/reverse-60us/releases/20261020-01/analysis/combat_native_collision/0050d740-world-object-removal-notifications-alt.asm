0050d740 c1e102                   shl       ecx, 2
0050d743 51                       push      ecx
0050d744 50                       push      eax
0050d745 57                       push      edi
0050d746 e845236f00               call      0xbffa90
0050d74b 8b4614                   mov       eax, dword ptr [esi + 0x14]
0050d74e 83c40c                   add       esp, 0xc
0050d751 83c0fc                   add       eax, -4
0050d754 894614                   mov       dword ptr [esi + 0x14], eax
0050d757 3b7e14                   cmp       edi, dword ptr [esi + 0x14]
0050d75a 0f8532ffffff             jne       0x50d692
0050d760 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
0050d763 3bc3                     cmp       eax, ebx
0050d765 8bf8                     mov       edi, eax
0050d767 741b                     je        0x50d784
0050d769 8da42400000000           lea       esp, [esp]
0050d770 8b0f                     mov       ecx, dword ptr [edi]
0050d772 8b11                     mov       edx, dword ptr [ecx]
0050d774 ff9270010000             call      dword ptr [edx + 0x170]
0050d77a 83c704                   add       edi, 4
0050d77d 3bfb                     cmp       edi, ebx
0050d77f 75ef                     jne       0x50d770
0050d781 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
0050d784 8b4e10                   mov       ecx, dword ptr [esi + 0x10]
0050d787 3b4e14                   cmp       ecx, dword ptr [esi + 0x14]
0050d78a 894df0                   mov       dword ptr [ebp - 0x10], ecx
0050d78d 7449                     je        0x50d7d8
0050d78f 90                       nop       
0050d790 3bc3                     cmp       eax, ebx
0050d792 8bf8                     mov       edi, eax
0050d794 7417                     je        0x50d7ad
0050d796 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
0050d799 8b0f                     mov       ecx, dword ptr [edi]
0050d79b 8b12                     mov       edx, dword ptr [edx]
0050d79d 8b01                     mov       eax, dword ptr [ecx]
0050d79f 52                       push      edx
0050d7a0 ff905c010000             call      dword ptr [eax + 0x15c]
0050d7a6 83c704                   add       edi, 4
0050d7a9 3bfb                     cmp       edi, ebx
0050d7ab 75e9                     jne       0x50d796
0050d7ad 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
0050d7b0 8b08                     mov       ecx, dword ptr [eax]
0050d7b2 8b11                     mov       edx, dword ptr [ecx]
0050d7b4 6a00                     push      0
0050d7b6 ff5258                   call      dword ptr [edx + 0x58]
0050d7b9 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
0050d7bc 8b0f                     mov       ecx, dword ptr [edi]
0050d7be 85c9                     test      ecx, ecx
0050d7c0 7406                     je        0x50d7c8
0050d7c2 8b01                     mov       eax, dword ptr [ecx]
0050d7c4 6a01                     push      1
0050d7c6 ff10                     call      dword ptr [eax]
0050d7c8 8b4614                   mov       eax, dword ptr [esi + 0x14]
0050d7cb 83c704                   add       edi, 4
0050d7ce 3bf8                     cmp       edi, eax
0050d7d0 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
0050d7d3 897df0                   mov       dword ptr [ebp - 0x10], edi
0050d7d6 75b8                     jne       0x50d790
0050d7d8 8b8ea0000000             mov       ecx, dword ptr [esi + 0xa0]
0050d7de 3b8ea4000000             cmp       ecx, dword ptr [esi + 0xa4]
0050d7e4 894df0                   mov       dword ptr [ebp - 0x10], ecx
0050d7e7 744f                     je        0x50d838
0050d7e9 eb05                     jmp       0x50d7f0
0050d7eb 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
0050d7ee 8bff                     mov       edi, edi
0050d7f0 3bc3                     cmp       eax, ebx
0050d7f2 8bf8                     mov       edi, eax
0050d7f4 7417                     je        0x50d80d
0050d7f6 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
0050d7f9 8b0f                     mov       ecx, dword ptr [edi]
0050d7fb 8b00                     mov       eax, dword ptr [eax]
0050d7fd 8b11                     mov       edx, dword ptr [ecx]
0050d7ff 50                       push      eax
0050d800 ff925c010000             call      dword ptr [edx + 0x15c]
0050d806 83c704                   add       edi, 4
0050d809 3bfb                     cmp       edi, ebx
0050d80b 75e9                     jne       0x50d7f6
0050d80d 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0050d810 8b09                     mov       ecx, dword ptr [ecx]
0050d812 8b11                     mov       edx, dword ptr [ecx]
0050d814 6a00                     push      0
0050d816 ff5258                   call      dword ptr [edx + 0x58]
0050d819 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
0050d81c 8b0f                     mov       ecx, dword ptr [edi]
0050d81e 85c9                     test      ecx, ecx
0050d820 7406                     je        0x50d828
0050d822 8b01                     mov       eax, dword ptr [ecx]
0050d824 6a01                     push      1
0050d826 ff10                     call      dword ptr [eax]
0050d828 8b86a4000000             mov       eax, dword ptr [esi + 0xa4]
0050d82e 83                       .byte     0x83
0050d82f c7                       .byte     0xc7
