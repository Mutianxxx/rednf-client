004ac440 55                       push      ebp
004ac441 8bec                     mov       ebp, esp
004ac443 56                       push      esi
004ac444 8bf1                     mov       esi, ecx
004ac446 8b06                     mov       eax, dword ptr [esi]
004ac448 ff90dc030000             call      dword ptr [eax + 0x3dc]
004ac44e 84c0                     test      al, al
004ac450 750a                     jne       0x4ac45c
004ac452 b804000000               mov       eax, 4
004ac457 5e                       pop       esi
004ac458 5d                       pop       ebp
004ac459 c20800                   ret       8
004ac45c 57                       push      edi
004ac45d 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ac460 83ff05                   cmp       edi, 5
004ac463 7475                     je        0x4ac4da
004ac465 83bea004000005           cmp       dword ptr [esi + 0x4a0], 5
004ac46c 746c                     je        0x4ac4da
004ac46e 8b16                     mov       edx, dword ptr [esi]
004ac470 6811010000               push      0x111
004ac475 8bce                     mov       ecx, esi
004ac477 ff522c                   call      dword ptr [edx + 0x2c]
004ac47a 84c0                     test      al, al
004ac47c 740b                     je        0x4ac489
004ac47e 5f                       pop       edi
004ac47f b804000000               mov       eax, 4
004ac484 5e                       pop       esi
004ac485 5d                       pop       ebp
004ac486 c20800                   ret       8
004ac489 8b06                     mov       eax, dword ptr [esi]
004ac48b 6811020000               push      0x211
004ac490 8bce                     mov       ecx, esi
004ac492 ff502c                   call      dword ptr [eax + 0x2c]
004ac495 84c0                     test      al, al
004ac497 74e5                     je        0x4ac47e
004ac499 8a450c                   mov       al, byte ptr [ebp + 0xc]
004ac49c 84c0                     test      al, al
004ac49e 7505                     jne       0x4ac4a5
004ac4a0 83ff09                   cmp       edi, 9
004ac4a3 750e                     jne       0x4ac4b3
004ac4a5 8b16                     mov       edx, dword ptr [esi]
004ac4a7 8bce                     mov       ecx, esi
004ac4a9 ff92a0050000             call      dword ptr [edx + 0x5a0]
004ac4af 84c0                     test      al, al
004ac4b1 741c                     je        0x4ac4cf
004ac4b3 8b06                     mov       eax, dword ptr [esi]
004ac4b5 8bce                     mov       ecx, esi
004ac4b7 ff9078030000             call      dword ptr [eax + 0x378]
004ac4bd 85c0                     test      eax, eax
004ac4bf 75bd                     jne       0x4ac47e
004ac4c1 8b16                     mov       edx, dword ptr [esi]
004ac4c3 8bce                     mov       ecx, esi
004ac4c5 ff92a0030000             call      dword ptr [edx + 0x3a0]
004ac4cb 85c0                     test      eax, eax
004ac4cd 75af                     jne       0x4ac47e
004ac4cf 5f                       pop       edi
004ac4d0 b805000000               mov       eax, 5
004ac4d5 5e                       pop       esi
004ac4d6 5d                       pop       ebp
004ac4d7 c20800                   ret       8
004ac4da 5f                       pop       edi
004ac4db 83c8ff                   or        eax, 0xffffffff
004ac4de 5e                       pop       esi
004ac4df 5d                       pop       ebp
004ac4e0 c20800                   ret       8
