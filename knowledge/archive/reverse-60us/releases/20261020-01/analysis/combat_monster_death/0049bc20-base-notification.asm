0049bc20 55                       push      ebp
0049bc21 8bec                     mov       ebp, esp
0049bc23 51                       push      ecx
0049bc24 56                       push      esi
0049bc25 8bf1                     mov       esi, ecx
0049bc27 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049bc2d 8b8190000000             mov       eax, dword ptr [ecx + 0x90]
0049bc33 57                       push      edi
0049bc34 8b7d08                   mov       edi, dword ptr [ebp + 8]
0049bc37 3bc7                     cmp       eax, edi
0049bc39 7521                     jne       0x49bc5c
0049bc3b 85ff                     test      edi, edi
0049bc3d 741d                     je        0x49bc5c
0049bc3f 6a00                     push      0
0049bc41 e83a520700               call      0x510e80
0049bc46 8b06                     mov       eax, dword ptr [esi]
0049bc48 6a02                     push      2
0049bc4a 8bce                     mov       ecx, esi
0049bc4c ff502c                   call      dword ptr [eax + 0x2c]
0049bc4f 84c0                     test      al, al
0049bc51 7409                     je        0x49bc5c
0049bc53 8b16                     mov       edx, dword ptr [esi]
0049bc55 6a00                     push      0
0049bc57 8bce                     mov       ecx, esi
0049bc59 ff5260                   call      dword ptr [edx + 0x60]
0049bc5c 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0049bc62 85c0                     test      eax, eax
0049bc64 7408                     je        0x49bc6e
0049bc66 8bc8                     mov       ecx, eax
0049bc68 8b01                     mov       eax, dword ptr [ecx]
0049bc6a 57                       push      edi
0049bc6b ff5008                   call      dword ptr [eax + 8]
0049bc6e 8b8654010000             mov       eax, dword ptr [esi + 0x154]
0049bc74 85c0                     test      eax, eax
0049bc76 7408                     je        0x49bc80
0049bc78 8bc8                     mov       ecx, eax
0049bc7a 8b11                     mov       edx, dword ptr [ecx]
0049bc7c 57                       push      edi
0049bc7d ff5208                   call      dword ptr [edx + 8]
0049bc80 8b8e7c010000             mov       ecx, dword ptr [esi + 0x17c]
0049bc86 8b01                     mov       eax, dword ptr [ecx]
0049bc88 3bc1                     cmp       eax, ecx
0049bc8a 894508                   mov       dword ptr [ebp + 8], eax
0049bc8d 7430                     je        0x49bcbf
0049bc8f 90                       nop       
0049bc90 397810                   cmp       dword ptr [eax + 0x10], edi
0049bc93 7517                     jne       0x49bcac
0049bc95 50                       push      eax
0049bc96 8d45fc                   lea       eax, [ebp - 4]
0049bc99 50                       push      eax
0049bc9a 8d8e78010000             lea       ecx, [esi + 0x178]
0049bca0 e8ab9bf6ff               call      0x405850
0049bca5 8b00                     mov       eax, dword ptr [eax]
0049bca7 894508                   mov       dword ptr [ebp + 8], eax
0049bcaa eb0b                     jmp       0x49bcb7
0049bcac 8d4d08                   lea       ecx, [ebp + 8]
0049bcaf e82c12fbff               call      0x44cee0
0049bcb4 8b4508                   mov       eax, dword ptr [ebp + 8]
0049bcb7 3b867c010000             cmp       eax, dword ptr [esi + 0x17c]
0049bcbd 75d1                     jne       0x49bc90
0049bcbf 3bf7                     cmp       esi, edi
0049bcc1 0f85ad000000             jne       0x49bd74
0049bcc7 eb07                     jmp       0x49bcd0
0049bcc9 8da42400000000           lea       esp, [esp]
0049bcd0 8b8e30010000             mov       ecx, dword ptr [esi + 0x130]
0049bcd6 85c9                     test      ecx, ecx
0049bcd8 7446                     je        0x49bd20
0049bcda 8b8634010000             mov       eax, dword ptr [esi + 0x134]
0049bce0 2bc1                     sub       eax, ecx
0049bce2 c1f802                   sar       eax, 2
0049bce5 85c0                     test      eax, eax
0049bce7 7437                     je        0x49bd20
0049bce9 8b8634010000             mov       eax, dword ptr [esi + 0x134]
0049bcef 8b78fc                   mov       edi, dword ptr [eax - 4]
0049bcf2 83e804                   sub       eax, 4
0049bcf5 85c9                     test      ecx, ecx
0049bcf7 741a                     je        0x49bd13
0049bcf9 8b9634010000             mov       edx, dword ptr [esi + 0x134]
0049bcff 8bc2                     mov       eax, edx
0049bd01 2bc1                     sub       eax, ecx
0049bd03 c1f802                   sar       eax, 2
0049bd06 85c0                     test      eax, eax
0049bd08 7409                     je        0x49bd13
0049bd0a 83c2fc                   add       edx, -4
0049bd0d 899634010000             mov       dword ptr [esi + 0x134], edx
0049bd13 8b16                     mov       edx, dword ptr [esi]
0049bd15 57                       push      edi
0049bd16 8bce                     mov       ecx, esi
0049bd18 ff92fc000000             call      dword ptr [edx + 0xfc]
0049bd1e ebb0                     jmp       0x49bcd0
0049bd20 8b8644010000             mov       eax, dword ptr [esi + 0x144]
0049bd26 85c0                     test      eax, eax
0049bd28 744a                     je        0x49bd74
0049bd2a 53                       push      ebx
0049bd2b 8d9e3c010000             lea       ebx, [esi + 0x13c]
0049bd31 8b8640010000             mov       eax, dword ptr [esi + 0x140]
0049bd37 8b08                     mov       ecx, dword ptr [eax]
0049bd39 8b790c                   mov       edi, dword ptr [ecx + 0xc]
0049bd3c 8d5508                   lea       edx, [ebp + 8]
0049bd3f 52                       push      edx
0049bd40 8bcb                     mov       ecx, ebx
0049bd42 897d08                   mov       dword ptr [ebp + 8], edi
0049bd45 e8260d0000               call      0x49ca70
0049bd4a 8b06                     mov       eax, dword ptr [esi]
0049bd4c 57                       push      edi
0049bd4d 8bce                     mov       ecx, esi
0049bd4f ff90fc000000             call      dword ptr [eax + 0xfc]
0049bd55 85ff                     test      edi, edi
0049bd57 7410                     je        0x49bd69
0049bd59 8bcf                     mov       ecx, edi
0049bd5b e870ccf6ff               call      0x4089d0
0049bd60 57                       push      edi
0049bd61 e8ea61f6ff               call      0x401f50
0049bd66 83c404                   add       esp, 4
0049bd69 8b8644010000             mov       eax, dword ptr [esi + 0x144]
0049bd6f 85c0                     test      eax, eax
0049bd71 75be                     jne       0x49bd31
0049bd73 5b                       pop       ebx
0049bd74 5f                       pop       edi
0049bd75 5e                       pop       esi
0049bd76 8be5                     mov       esp, ebp
0049bd78 5d                       pop       ebp
0049bd79 c20400                   ret       4
