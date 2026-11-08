0050c710 8bcb                     mov       ecx, ebx
0050c712 ff502c                   call      dword ptr [eax + 0x2c]
0050c715 84c0                     test      al, al
0050c717 7421                     je        0x50c73a
0050c719 57                       push      edi
0050c71a 57                       push      edi
0050c71b 8bcb                     mov       ecx, ebx
0050c71d e82e7ef9ff               call      0x4a4550
0050c722 50                       push      eax
0050c723 8bce                     mov       ecx, esi
0050c725 e8c6ffffff               call      0x50c6f0
0050c72a 8b8b04070000             mov       ecx, dword ptr [ebx + 0x704]
0050c730 57                       push      edi
0050c731 57                       push      edi
0050c732 51                       push      ecx
0050c733 8bce                     mov       ecx, esi
0050c735 e8b6ffffff               call      0x50c6f0
0050c73a 8b13                     mov       edx, dword ptr [ebx]
0050c73c 6a21                     push      0x21
0050c73e 8bcb                     mov       ecx, ebx
0050c740 ff522c                   call      dword ptr [edx + 0x2c]
0050c743 84c0                     test      al, al
0050c745 7419                     je        0x50c760
0050c747 8b8614010000             mov       eax, dword ptr [esi + 0x114]
0050c74d 3bc7                     cmp       eax, edi
0050c74f 740f                     je        0x50c760
0050c751 8b4850                   mov       ecx, dword ptr [eax + 0x50]
0050c754 3bcf                     cmp       ecx, edi
0050c756 7408                     je        0x50c760
0050c758 6a01                     push      1
0050c75a 53                       push      ebx
0050c75b e80099f7ff               call      0x486060
0050c760 8b03                     mov       eax, dword ptr [ebx]
0050c762 53                       push      ebx
0050c763 8bcb                     mov       ecx, ebx
0050c765 ff905c010000             call      dword ptr [eax + 0x15c]
0050c76b 8b4e10                   mov       ecx, dword ptr [esi + 0x10]
0050c76e 3bcf                     cmp       ecx, edi
0050c770 7505                     jne       0x50c777
0050c772 897d08                   mov       dword ptr [ebp + 8], edi
0050c775 eb0b                     jmp       0x50c782
0050c777 8b4614                   mov       eax, dword ptr [esi + 0x14]
0050c77a 2bc1                     sub       eax, ecx
0050c77c c1f802                   sar       eax, 2
0050c77f 894508                   mov       dword ptr [ebp + 8], eax
0050c782 8b5508                   mov       edx, dword ptr [ebp + 8]
0050c785 85d2                     test      edx, edx
0050c787 7e56                     jle       0x50c7df
0050c789 8da42400000000           lea       esp, [esp]
0050c790 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0050c793 85c0                     test      eax, eax
0050c795 7428                     je        0x50c7bf
0050c797 8b4808                   mov       ecx, dword ptr [eax + 8]
0050c79a 8b4004                   mov       eax, dword ptr [eax + 4]
0050c79d 3bc1                     cmp       eax, ecx
0050c79f 8b5610                   mov       edx, dword ptr [esi + 0x10]
0050c7a2 8d14ba                   lea       edx, [edx + edi*4]
0050c7a5 7418                     je        0x50c7bf
0050c7a7 8b12                     mov       edx, dword ptr [edx]
0050c7a9 8da42400000000           lea       esp, [esp]
0050c7b0 3910                     cmp       dword ptr [eax], edx
0050c7b2 7407                     je        0x50c7bb
0050c7b4 83c004                   add       eax, 4
0050c7b7 3bc1                     cmp       eax, ecx
0050c7b9 75f5                     jne       0x50c7b0
0050c7bb 3bc1                     cmp       eax, ecx
0050c7bd 7518                     jne       0x50c7d7
0050c7bf 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050c7c2 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
0050c7c5 3bd9                     cmp       ebx, ecx
0050c7c7 8d04b8                   lea       eax, [eax + edi*4]
0050c7ca 740b                     je        0x50c7d7
0050c7cc 8bc1                     mov       eax, ecx
0050c7ce 8b10                     mov       edx, dword ptr [eax]
0050c7d0 53                       push      ebx
0050c7d1 ff925c010000             call      dword ptr [edx + 0x15c]
0050c7d7 8b5508                   mov       edx, dword ptr [ebp + 8]
0050c7da 47                       inc       edi
0050c7db 3bfa                     cmp       edi, edx
0050c7dd 7cb1                     jl        0x50c790
0050c7df 807d1001                 cmp       byte ptr [ebp + 0x10], 1
0050c7e3 0f84a8010000             je        0x50c991
0050c7e9 33ff                     xor       edi, edi
0050c7eb 85d2                     test      edx, edx
0050c7ed 7e38                     jle       0x50c827
0050c7ef 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050c7f2 8bc8                     mov       ecx, eax
0050c7f4 3919                     cmp       dword ptr [ecx], ebx
0050c7f6 740a                     je        0x50c802
0050c7f8 47                       inc       edi
0050c7f9 83c104                   add       ecx, 4
0050c7fc 3bfa                     cmp       edi, edx
0050c7fe 7cf4                     jl        0x50c7f4
0050c800 eb25                     jmp       0x50c827
0050c802 8b5614                   mov       edx, dword ptr [esi + 0x14]
0050c805 8d04b8                   lea       eax, [eax + edi*4]
0050c808 8d4804                   lea       ecx, [eax + 4]
0050c80b 2bd1                     sub       edx, ecx
0050c80d c1fa02                   sar       edx, 2
