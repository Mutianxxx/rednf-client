00507940 55                       push      ebp
00507941 8bec                     mov       ebp, esp
00507943 56                       push      esi
00507944 57                       push      edi
00507945 8b7d08                   mov       edi, dword ptr [ebp + 8]
00507948 8bf1                     mov       esi, ecx
0050794a 3bf7                     cmp       esi, edi
0050794c 0f8430010000             je        0x507a82
00507952 8b4f04                   mov       ecx, dword ptr [edi + 4]
00507955 53                       push      ebx
00507956 33db                     xor       ebx, ebx
00507958 3bcb                     cmp       ecx, ebx
0050795a 740e                     je        0x50796a
0050795c 8b4708                   mov       eax, dword ptr [edi + 8]
0050795f 8bd0                     mov       edx, eax
00507961 2bd1                     sub       edx, ecx
00507963 c1fa02                   sar       edx, 2
00507966 3bd3                     cmp       edx, ebx
00507968 7522                     jne       0x50798c
0050796a 8b4604                   mov       eax, dword ptr [esi + 4]
0050796d 3bc3                     cmp       eax, ebx
0050796f 7409                     je        0x50797a
00507971 50                       push      eax
00507972 e866866f00               call      0xbfffdd
00507977 83c404                   add       esp, 4
0050797a 895e04                   mov       dword ptr [esi + 4], ebx
0050797d 895e08                   mov       dword ptr [esi + 8], ebx
00507980 895e0c                   mov       dword ptr [esi + 0xc], ebx
00507983 5b                       pop       ebx
00507984 5f                       pop       edi
00507985 8bc6                     mov       eax, esi
00507987 5e                       pop       esi
00507988 5d                       pop       ebp
00507989 c20400                   ret       4
0050798c 8b4e04                   mov       ecx, dword ptr [esi + 4]
0050798f 3bcb                     cmp       ecx, ebx
00507991 7504                     jne       0x507997
00507993 33db                     xor       ebx, ebx
00507995 eb08                     jmp       0x50799f
00507997 8b5e08                   mov       ebx, dword ptr [esi + 8]
0050799a 2bd9                     sub       ebx, ecx
0050799c c1fb02                   sar       ebx, 2
0050799f 3bd3                     cmp       edx, ebx
005079a1 774b                     ja        0x5079ee
005079a3 8b5704                   mov       edx, dword ptr [edi + 4]
005079a6 2bc2                     sub       eax, edx
005079a8 c1f802                   sar       eax, 2
005079ab c1e002                   shl       eax, 2
005079ae 50                       push      eax
005079af 52                       push      edx
005079b0 51                       push      ecx
005079b1 e8da806f00               call      0xbffa90
005079b6 8b4704                   mov       eax, dword ptr [edi + 4]
005079b9 83c40c                   add       esp, 0xc
005079bc 85c0                     test      eax, eax
005079be 7514                     jne       0x5079d4
005079c0 8b4604                   mov       eax, dword ptr [esi + 4]
005079c3 33ff                     xor       edi, edi
005079c5 8d0cb8                   lea       ecx, [eax + edi*4]
005079c8 5b                       pop       ebx
005079c9 5f                       pop       edi
005079ca 894e08                   mov       dword ptr [esi + 8], ecx
005079cd 8bc6                     mov       eax, esi
005079cf 5e                       pop       esi
005079d0 5d                       pop       ebp
005079d1 c20400                   ret       4
005079d4 8b7f08                   mov       edi, dword ptr [edi + 8]
005079d7 2bf8                     sub       edi, eax
005079d9 8b4604                   mov       eax, dword ptr [esi + 4]
005079dc c1ff02                   sar       edi, 2
005079df 8d                       .byte     0x8d
