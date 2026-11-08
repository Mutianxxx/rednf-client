004f9440 3bc7                     cmp       eax, edi
004f9442 7d7d                     jge       0x4f94c1
004f9444 8b8640240000             mov       eax, dword ptr [esi + 0x2440]
004f944a 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004f9450 8b8e44240000             mov       ecx, dword ptr [esi + 0x2444]
004f9456 8dbe40240000             lea       edi, [esi + 0x2440]
004f945c 33c2                     xor       eax, edx
004f945e 2bc7                     sub       eax, edi
004f9460 3bc1                     cmp       eax, ecx
004f9462 7414                     je        0x4f9478
004f9464 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f946a 6a3f                     push      0x3f
004f946c 57                       push      edi
004f946d e83edc6100               call      0xb170b0
004f9472 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004f9478 8b4704                   mov       eax, dword ptr [edi + 4]
004f947b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f9481 8b7944                   mov       edi, dword ptr [ecx + 0x44]
004f9484 c1e002                   shl       eax, 2
004f9487 8d1c07                   lea       ebx, [edi + eax]
004f948a 8b3b                     mov       edi, dword ptr [ebx]
004f948c 33fb                     xor       edi, ebx
004f948e 8b5948                   mov       ebx, dword ptr [ecx + 0x48]
004f9491 03c3                     add       eax, ebx
004f9493 8b18                     mov       ebx, dword ptr [eax]
004f9495 33d8                     xor       ebx, eax
004f9497 33fa                     xor       edi, edx
004f9499 33da                     xor       ebx, edx
004f949b 3bfb                     cmp       edi, ebx
004f949d 741a                     je        0x4f94b9
004f949f 6a40                     push      0x40
004f94a1 8d8640240000             lea       eax, [esi + 0x2440]
004f94a7 50                       push      eax
004f94a8 e803dc6100               call      0xb170b0
004f94ad 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004f94b3 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f94b9 85ff                     test      edi, edi
004f94bb 0f8501020000             jne       0x4f96c2
004f94c1 8b8e18240000             mov       ecx, dword ptr [esi + 0x2418]
004f94c7 85c9                     test      ecx, ecx
004f94c9 0f84e5050000             je        0x4f9ab4
004f94cf 8b861c240000             mov       eax, dword ptr [esi + 0x241c]
004f94d5 2bc1                     sub       eax, ecx
004f94d7 c1f802                   sar       eax, 2
004f94da 85c0                     test      eax, eax
004f94dc 0f84d2050000             je        0x4f9ab4
004f94e2 8bc1                     mov       eax, ecx
004f94e4 833800                   cmp       dword ptr [eax], 0
004f94e7 0f84c7050000             je        0x4f9ab4
004f94ed 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f94f3 85c0                     test      eax, eax
004f94f5 750e                     jne       0x4f9505
004f94f7 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004f94fd 85c0                     test      eax, eax
004f94ff 0f84af050000             je        0x4f9ab4
004f9505 8b16                     mov       edx, dword ptr [esi]
004f9507 8bce                     mov       ecx, esi
004f9509 ff92dc030000             call      dword ptr [edx + 0x3dc]
004f950f 84c0                     test      al, al
004f9511 0f859d050000             jne       0x4f9ab4
004f9517 8b06                     mov       eax, dword ptr [esi]
004f9519 8bce                     mov       ecx, esi
004f951b ff9078030000             call      dword ptr [eax + 0x378]
004f9521 398604010000             cmp       dword ptr [esi + 0x104], eax
004f9527 7516                     jne       0x4f953f
004f9529 8b16                     mov       edx, dword ptr [esi]
004f952b 8bce                     mov       ecx, esi
004f952d ff92a0030000             call      dword ptr [edx + 0x3a0]
004f9533 398648010000             cmp       dword ptr [esi + 0x148], eax
004f9539 0f8475050000             je        0x4f9ab4
004f953f 8b06                     mov       eax, dword ptr [esi]
004f9541 8bce                     mov       ecx, esi
004f9543 ff907c030000             call      dword ptr [eax + 0x37c]
004f9549 398604010000             cmp       dword ptr [esi + 0x104], eax
004f954f 7516                     jne       0x4f9567
004f9551 8b16                     mov       edx, dword ptr [esi]
004f9553 8bce                     mov       ecx, esi
004f9555 ff92a4030000             call      dword ptr [edx + 0x3a4]
004f955b 398648010000             cmp       dword ptr [esi + 0x148], eax
004f9561 0f844d050000             je        0x4f9ab4
004f9567 6a0e                     push      0xe
004f9569 8bce                     mov       ecx, esi
004f956b e800f4feff               call      0x4e8970
