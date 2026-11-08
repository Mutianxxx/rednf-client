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
0050cb34 e8                       .byte     0xe8
0050cb35 b7fb                     mov       bh, 0xfb
0050cb37 ff                       .byte     0xff
