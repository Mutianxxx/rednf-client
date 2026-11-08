005f3300 55                       push      ebp
005f3301 8bec                     mov       ebp, esp
005f3303 56                       push      esi
005f3304 8bf1                     mov       esi, ecx
005f3306 8b8688080000             mov       eax, dword ptr [esi + 0x888]
005f330c 57                       push      edi
005f330d 8b7d08                   mov       edi, dword ptr [ebp + 8]
005f3310 3bf8                     cmp       edi, eax
005f3312 7452                     je        0x5f3366
005f3314 8a8680080000             mov       al, byte ptr [esi + 0x880]
005f331a 84c0                     test      al, al
005f331c 7448                     je        0x5f3366
005f331e 83ff04                   cmp       edi, 4
005f3321 7513                     jne       0x5f3336
005f3323 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
005f3329 8b06                     mov       eax, dword ptr [esi]
005f332b 51                       push      ecx
005f332c 8bce                     mov       ecx, esi
005f332e ff90f0000000             call      dword ptr [eax + 0xf0]
005f3334 eb1f                     jmp       0x5f3355
005f3336 85ff                     test      edi, edi
005f3338 8b16                     mov       edx, dword ptr [esi]
005f333a 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f3340 8bce                     mov       ecx, esi
005f3342 7505                     jne       0x5f3349
005f3344 83c004                   add       eax, 4
005f3347 eb03                     jmp       0x5f334c
005f3349 83c008                   add       eax, 8
005f334c 8b00                     mov       eax, dword ptr [eax]
005f334e 50                       push      eax
005f334f ff92f0000000             call      dword ptr [edx + 0xf0]
005f3355 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
005f335b e800404300               call      0xa27360
005f3360 89be88080000             mov       dword ptr [esi + 0x888], edi
005f3366 5f                       pop       edi
005f3367 5e                       pop       esi
005f3368 5d                       pop       ebp
005f3369 c20400                   ret       4
