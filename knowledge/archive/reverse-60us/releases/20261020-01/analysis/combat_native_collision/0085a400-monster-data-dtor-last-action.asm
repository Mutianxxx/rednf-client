0085a400 45                       inc       ebp
0085a401 fc                       cld       
0085a402 1be8                     sbb       ebp, eax
0085a404 d8a0baff8d8e             fsub      dword ptr [eax - 0x71720046]
0085a40a bc060000c6               mov       esp, 0xc6000006
0085a40f 45                       inc       ebp
0085a410 fc                       cld       
0085a411 1c89                     sbb       al, 0x89
0085a413 3968e0                   cmp       dword ptr [eax - 0x20], ebp
0085a416 baca00e882               mov       edx, 0x82e800ca
0085a41b 94                       xchg      esp, eax
0085a41c 1f                       pop       ds
0085a41d 008d8ec40600             add       byte ptr [ebp + 0x6c48e], cl
0085a423 00c6                     add       dh, al
0085a425 45                       inc       ebp
0085a426 fc                       cld       
0085a427 1de89377ff               sbb       eax, 0xff7793e8
0085a42c ff89be240700             dec       dword ptr [ecx + 0x724be]
0085a432 0089be280700             add       byte ptr [ecx + 0x728be], cl
0085a438 0089be2c0700             add       byte ptr [ecx + 0x72cbe], cl
0085a43e 0089be340700             add       byte ptr [ecx + 0x734be], cl
0085a444 0089be380700             add       byte ptr [ecx + 0x738be], cl
0085a44a 0089be3c0700             add       byte ptr [ecx + 0x73cbe], cl
0085a450 008d8e400700             add       byte ptr [ebp + 0x7408e], cl
0085a456 00c6                     add       dh, al
0085a458 45                       inc       ebp
0085a459 fc                       cld       
0085a45a 20e8                     and       al, ch
0085a45c 80a0baff8d8e48           and       byte ptr [eax - 0x71720046], 0x48
0085a463 07                       pop       es
0085a464 0000                     add       byte ptr [eax], al
0085a466 c645fc21                 mov       byte ptr [ebp - 4], 0x21
0085a46a e871a0baff               call      0x4044e0
0085a46f 8d8e5c070000             lea       ecx, [esi + 0x75c]
0085a475 c645fc22                 mov       byte ptr [ebp - 4], 0x22
0085a479 e862a0baff               call      0x4044e0
0085a47e 89be6c070000             mov       dword ptr [esi + 0x76c], edi
0085a484 89be70070000             mov       dword ptr [esi + 0x770], edi
0085a48a 89be74070000             mov       dword ptr [esi + 0x774], edi
0085a490 8bce                     mov       ecx, esi
0085a492 c645fc24                 mov       byte ptr [ebp - 4], 0x24
0085a496 e8d5f3ffff               call      0x859870
0085a49b 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0085a49e 5f                       pop       edi
0085a49f 8b                       .byte     0x8b
