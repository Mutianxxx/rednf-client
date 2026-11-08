005015d7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005015da 8dbbec120000             lea       edi, [ebx + 0x12ec]
005015e0 81c110070000             add       ecx, 0x710
005015e6 c745f000000000           mov       dword ptr [ebp - 0x10], 0
005015ed 897dec                   mov       dword ptr [ebp - 0x14], edi
005015f0 894de4                   mov       dword ptr [ebp - 0x1c], ecx
005015f3 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
005015f6 68e0baca00               push      0xcabae0
005015fb e8f01a5500               call      0xa530f0
00501600 50                       push      eax
00501601 e8e5f76f00               call      0xc00deb
00501606 83c408                   add       esp, 8
00501609 85c0                     test      eax, eax
0050160b 0f8480000000             je        0x501691
00501611 68e0020000               push      0x2e0
00501616 e83526f0ff               call      0x403c50
0050161b 8bf0                     mov       esi, eax
0050161d 83c404                   add       esp, 4
00501620 8975e8                   mov       dword ptr [ebp - 0x18], esi
00501623 85f6                     test      esi, esi
00501625 c745fc0f000000           mov       dword ptr [ebp - 4], 0xf
0050162c 742f                     je        0x50165d
0050162e 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
00501635 7208                     jb        0x50163f
00501637 8bbb48020000             mov       edi, dword ptr [ebx + 0x248]
0050163d eb06                     jmp       0x501645
0050163f 8dbb48020000             lea       edi, [ebx + 0x248]
00501645 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
00501648 6a00                     push      0
0050164a e8a11a5500               call      0xa530f0
0050164f 50                       push      eax
00501650 57                       push      edi
00501651 8bce                     mov       ecx, esi
00501653 e8a822faff               call      0x4a3900
00501658 8b7dec                   mov       edi, dword ptr [ebp - 0x14]
0050165b eb02                     jmp       0x50165f
0050165d 33c0                     xor       eax, eax
0050165f 85c0                     test      eax, eax
00501661 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00501668 8907                     mov       dword ptr [edi], eax
0050166a 7425                     je        0x501691
0050166c 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
0050166f 33d2                     xor       edx, edx
00501671 85f6                     test      esi, esi
00501673 0f95c2                   setne     dl
00501676 53                       push      ebx
00501677 83c203                   add       edx, 3
0050167a 8990cc020000             mov       dword ptr [eax + 0x2cc], edx
00501680 c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
0050168a 8b0f                     mov       ecx, dword ptr [edi]
0050168c e88fb95200               call      0xa2d020
00501691 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
00501694 8b75e4                   mov       esi, dword ptr [ebp - 0x1c]
00501697 40                       inc       eax
00501698 83c604                   add       esi, 4
0050169b 83c704                   add       edi, 4
0050169e 83f802                   cmp       eax, 2
005016a1 8945f0                   mov       dword ptr [ebp - 0x10], eax
005016a4 8975e4                   mov       dword ptr [ebp - 0x1c], esi
005016a7 897dec                   mov       dword ptr [ebp - 0x14], edi
005016aa 0f8c43ffffff             jl        0x5015f3
005016b0 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005016b3 81c118070000             add       ecx, 0x718
005016b9 68e0baca00               push      0xcabae0
005016be e82d1a5500               call      0xa530f0
005016c3 50                       push      eax
005016c4 e822f76f00               call      0xc00deb
005016c9 83c408                   add       esp, 8
005016cc 85c0                     test      eax, eax
005016ce 0f8482000000             je        0x501756
005016d4 68e0020000               push      0x2e0
005016d9 e87225f0ff               call      0x403c50
005016de 8bf0                     mov       esi, eax
005016e0 83c404                   add       esp, 4
005016e3 8975e8                   mov       dword ptr [ebp - 0x18], esi
005016e6 85f6                     test      esi, esi
005016e8 c745fc10000000           mov       dword ptr [ebp - 4], 0x10
005016ef 7432                     je        0x501723
005016f1 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
005016f8 7208                     jb        0x501702
005016fa 8bbb48020000             mov       edi, dword ptr [ebx + 0x248]
00501700 eb06                     jmp       0x501708
00501702 8dbb48020000             lea       edi, [ebx + 0x248]
00501708 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0050170b 6a00                     push      0
0050170d 81c118070000             add       ecx, 0x718
00501713 e8d8195500               call      0xa530f0
00501718 50                       push      eax
00501719 57                       push      edi
0050171a 8bce                     mov       ecx, esi
0050171c e8df21faff               call      0x4a3900
00501721 eb02                     jmp       0x501725
00501723 33c0                     xor       eax, eax
00501725 85c0                     test      eax, eax
00501727 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0050172e 8983f4120000             mov       dword ptr [ebx + 0x12f4], eax
00501734 7420                     je        0x501756
00501736 c780cc02000005000000     mov       dword ptr [eax + 0x2cc], 5
00501740 c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
0050174a 8b8bf4120000             mov       ecx, dword ptr [ebx + 0x12f4]
00501750 53                       push      ebx
00501751 e8cab85200               call      0xa2d020
00501756 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501759 81c11c070000             add       ecx, 0x71c
0050175f 68e0baca00               push      0xcabae0
00501764 e887195500               call      0xa530f0
00501769 50                       push      eax
0050176a e87cf66f00               call      0xc00deb
0050176f 83c408                   add       esp, 8
00501772 85c0                     test      eax, eax
00501774 0f8482000000             je        0x5017fc
0050177a 68e0020000               push      0x2e0
0050177f e8cc24f0ff               call      0x403c50
00501784 8bf0                     mov       esi, eax
00501786 83c404                   add       esp, 4
00501789 8975e8                   mov       dword ptr [ebp - 0x18], esi
0050178c 85f6                     test      esi, esi
0050178e c745fc11000000           mov       dword ptr [ebp - 4], 0x11
00501795 7432                     je        0x5017c9
00501797 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
0050179e 7208                     jb        0x5017a8
005017a0 8bbb48020000             mov       edi, dword ptr [ebx + 0x248]
005017a6 eb06                     jmp       0x5017ae
005017a8 8dbb48020000             lea       edi, [ebx + 0x248]
005017ae 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005017b1 6a00                     push      0
005017b3 81c11c070000             add       ecx, 0x71c
005017b9 e832195500               call      0xa530f0
005017be 50                       push      eax
005017bf 57                       push      edi
005017c0 8bce                     mov       ecx, esi
005017c2 e83921faff               call      0x4a3900
005017c7 eb02                     jmp       0x5017cb
005017c9 33c0                     xor       eax, eax
005017cb 85c0                     test      eax, eax
005017cd c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005017d4 8983f8120000             mov       dword ptr [ebx + 0x12f8], eax
005017da 7420                     je        0x5017fc
005017dc c780cc02000006000000     mov       dword ptr [eax + 0x2cc], 6
005017e6 c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
005017f0 8b8bf8120000             mov       ecx, dword ptr [ebx + 0x12f8]
005017f6 53                       push      ebx
005017f7 e824b85200               call      0xa2d020
