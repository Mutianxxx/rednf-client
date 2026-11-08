0050155b 8db748070000             lea       esi, [edi + 0x748]
00501561 68e0baca00               push      0xcabae0
00501566 8bce                     mov       ecx, esi
00501568 e8831b5500               call      0xa530f0
0050156d 50                       push      eax
0050156e e878f86f00               call      0xc00deb
00501573 83c408                   add       esp, 8
00501576 85c0                     test      eax, eax
00501578 741f                     je        0x501599
0050157a 8bce                     mov       ecx, esi
0050157c e86f1b5500               call      0xa530f0
00501581 8bf0                     mov       esi, eax
00501583 56                       push      esi
00501584 e844e86f00               call      0xbffdcd
00501589 83c404                   add       esp, 4
0050158c 50                       push      eax
0050158d 56                       push      esi
0050158e 8d8bf01a0000             lea       ecx, [ebx + 0x1af0]
00501594 e8e718f0ff               call      0x402e80
