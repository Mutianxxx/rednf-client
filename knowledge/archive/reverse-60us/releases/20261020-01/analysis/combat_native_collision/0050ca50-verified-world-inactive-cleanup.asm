0050ca50 55                       push      ebp
0050ca51 8bec                     mov       ebp, esp
0050ca53 51                       push      ecx
0050ca54 53                       push      ebx
0050ca55 56                       push      esi
0050ca56 8bf1                     mov       esi, ecx
0050ca58 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050ca5b 33db                     xor       ebx, ebx
0050ca5d 3bc3                     cmp       eax, ebx
0050ca5f 57                       push      edi
0050ca60 7505                     jne       0x50ca67
0050ca62 895dfc                   mov       dword ptr [ebp - 4], ebx
0050ca65 eb0b                     jmp       0x50ca72
0050ca67 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0050ca6a 2bc8                     sub       ecx, eax
0050ca6c c1f902                   sar       ecx, 2
0050ca6f 894dfc                   mov       dword ptr [ebp - 4], ecx
0050ca72 8bbea0000000             mov       edi, dword ptr [esi + 0xa0]
0050ca78 3bbea4000000             cmp       edi, dword ptr [esi + 0xa4]
0050ca7e 7428                     je        0x50caa8
0050ca80 8b07                     mov       eax, dword ptr [edi]
0050ca82 6a01                     push      1
0050ca84 53                       push      ebx
0050ca85 50                       push      eax
0050ca86 8bce                     mov       ecx, esi
0050ca88 e863fcffff               call      0x50c6f0
0050ca8d 8b0f                     mov       ecx, dword ptr [edi]
0050ca8f 3bcb                     cmp       ecx, ebx
0050ca91 7406                     je        0x50ca99
0050ca93 8b11                     mov       edx, dword ptr [ecx]
0050ca95 6a01                     push      1
0050ca97 ff12                     call      dword ptr [edx]
0050ca99 891f                     mov       dword ptr [edi], ebx
0050ca9b 8b86a4000000             mov       eax, dword ptr [esi + 0xa4]
0050caa1 83c704                   add       edi, 4
0050caa4 3bf8                     cmp       edi, eax
0050caa6 75d8                     jne       0x50ca80
0050caa8 8b86a0000000             mov       eax, dword ptr [esi + 0xa0]
0050caae 3bc3                     cmp       eax, ebx
0050cab0 7409                     je        0x50cabb
0050cab2 50                       push      eax
0050cab3 e825356f00               call      0xbfffdd
0050cab8 83c404                   add       esp, 4
0050cabb 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050cabe 85c0                     test      eax, eax
0050cac0 899ea0000000             mov       dword ptr [esi + 0xa0], ebx
0050cac6 899ea4000000             mov       dword ptr [esi + 0xa4], ebx
0050cacc 899ea8000000             mov       dword ptr [esi + 0xa8], ebx
0050cad2 0f8e37010000             jle       0x50cc0f
0050cad8 eb06                     jmp       0x50cae0
0050cada 8d9b00000000             lea       ebx, [ebx]
0050cae0 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cae3 8d3c9d00000000           lea       edi, [ebx*4]
0050caea 03c7                     add       eax, edi
0050caec 8b00                     mov       eax, dword ptr [eax]
0050caee 8b10                     mov       edx, dword ptr [eax]
0050caf0 8bc8                     mov       ecx, eax
0050caf2 ff5264                   call      dword ptr [edx + 0x64]
0050caf5 84c0                     test      al, al
0050caf7 0f8506010000             jne       0x50cc03
0050cafd 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb00 03c7                     add       eax, edi
0050cb02 8b00                     mov       eax, dword ptr [eax]
0050cb04 8b10                     mov       edx, dword ptr [eax]
0050cb06 6811010000               push      0x111
0050cb0b 8bc8                     mov       ecx, eax
0050cb0d ff522c                   call      dword ptr [edx + 0x2c]
0050cb10 84c0                     test      al, al
0050cb12 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb15 7442                     je        0x50cb59
0050cb17 03c7                     add       eax, edi
0050cb19 8b00                     mov       eax, dword ptr [eax]
0050cb1b 8b10                     mov       edx, dword ptr [eax]
0050cb1d 8bc8                     mov       ecx, eax
0050cb1f ff5234                   call      dword ptr [edx + 0x34]
0050cb22 6a00                     push      0
0050cb24 84c0                     test      al, al
0050cb26 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb29 6a00                     push      0
0050cb2b 7421                     je        0x50cb4e
0050cb2d 8bce                     mov       ecx, esi
0050cb2f 03c7                     add       eax, edi
0050cb31 8b38                     mov       edi, dword ptr [eax]
0050cb33 57                       push      edi
0050cb34 e8b7fbffff               call      0x50c6f0
0050cb39 85ff                     test      edi, edi
0050cb3b 0f84ba000000             je        0x50cbfb
0050cb41 8b07                     mov       eax, dword ptr [edi]
0050cb43 6a01                     push      1
0050cb45 8bcf                     mov       ecx, edi
0050cb47 ff10                     call      dword ptr [eax]
0050cb49 e9ad000000               jmp       0x50cbfb
0050cb4e 8b0c38                   mov       ecx, dword ptr [eax + edi]
0050cb51 03c7                     add       eax, edi
0050cb53 51                       push      ecx
0050cb54 e99b000000               jmp       0x50cbf4
0050cb59 03c7                     add       eax, edi
0050cb5b 8b00                     mov       eax, dword ptr [eax]
0050cb5d 8b10                     mov       edx, dword ptr [eax]
0050cb5f 6a12                     push      0x12
0050cb61 8bc8                     mov       ecx, eax
0050cb63 ff522c                   call      dword ptr [edx + 0x2c]
0050cb66 84c0                     test      al, al
0050cb68 757e                     jne       0x50cbe8
0050cb6a 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb6d 03c7                     add       eax, edi
0050cb6f 8b00                     mov       eax, dword ptr [eax]
0050cb71 8b10                     mov       edx, dword ptr [eax]
0050cb73 6a41                     push      0x41
0050cb75 8bc8                     mov       ecx, eax
0050cb77 ff522c                   call      dword ptr [edx + 0x2c]
0050cb7a 84c0                     test      al, al
0050cb7c 756a                     jne       0x50cbe8
0050cb7e 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb81 03c7                     add       eax, edi
0050cb83 8b00                     mov       eax, dword ptr [eax]
0050cb85 8b10                     mov       edx, dword ptr [eax]
0050cb87 6881000000               push      0x81
0050cb8c 8bc8                     mov       ecx, eax
0050cb8e ff522c                   call      dword ptr [edx + 0x2c]
0050cb91 84c0                     test      al, al
0050cb93 7553                     jne       0x50cbe8
0050cb95 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb98 03c7                     add       eax, edi
0050cb9a 8b00                     mov       eax, dword ptr [eax]
0050cb9c 8b10                     mov       edx, dword ptr [eax]
0050cb9e 6882000000               push      0x82
0050cba3 8bc8                     mov       ecx, eax
0050cba5 ff522c                   call      dword ptr [edx + 0x2c]
0050cba8 84c0                     test      al, al
0050cbaa 753c                     jne       0x50cbe8
0050cbac 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbaf 03c7                     add       eax, edi
0050cbb1 8b00                     mov       eax, dword ptr [eax]
0050cbb3 8b10                     mov       edx, dword ptr [eax]
0050cbb5 6811020000               push      0x211
0050cbba 8bc8                     mov       ecx, eax
0050cbbc ff522c                   call      dword ptr [edx + 0x2c]
0050cbbf 6a00                     push      0
0050cbc1 84c0                     test      al, al
0050cbc3 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbc6 8bce                     mov       ecx, esi
0050cbc8 6a00                     push      0
0050cbca 0f855fffffff             jne       0x50cb2f
0050cbd0 03c7                     add       eax, edi
0050cbd2 8b38                     mov       edi, dword ptr [eax]
0050cbd4 57                       push      edi
0050cbd5 e816fbffff               call      0x50c6f0
0050cbda 85ff                     test      edi, edi
0050cbdc 741d                     je        0x50cbfb
0050cbde 8b17                     mov       edx, dword ptr [edi]
0050cbe0 6a01                     push      1
0050cbe2 8bcf                     mov       ecx, edi
0050cbe4 ff12                     call      dword ptr [edx]
0050cbe6 eb13                     jmp       0x50cbfb
0050cbe8 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbeb 6a00                     push      0
0050cbed 03c7                     add       eax, edi
0050cbef 8b00                     mov       eax, dword ptr [eax]
0050cbf1 6a00                     push      0
0050cbf3 50                       push      eax
0050cbf4 8bce                     mov       ecx, esi
0050cbf6 e8f5faffff               call      0x50c6f0
0050cbfb 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050cbfe 4b                       dec       ebx
0050cbff 48                       dec       eax
0050cc00 8945fc                   mov       dword ptr [ebp - 4], eax
0050cc03 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050cc06 43                       inc       ebx
0050cc07 3bd8                     cmp       ebx, eax
0050cc09 0f8cd1feffff             jl        0x50cae0
0050cc0f 5f                       pop       edi
0050cc10 5e                       pop       esi
0050cc11 5b                       pop       ebx
0050cc12 8be5                     mov       esp, ebp
0050cc14 5d                       pop       ebp
0050cc15 c3                       ret       
