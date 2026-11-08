008896d9 e200                     loop      0x8896db
008896db 56                       push      esi
008896dc e8efb0b7ff               call      0x4047d0
008896e1 83c408                   add       esp, 8
008896e4 84c0                     test      al, al
008896e6 7417                     je        0x8896ff
008896e8 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008896eb 81c104070000             add       ecx, 0x704
008896f1 51                       push      ecx
008896f2 e8e96dfaff               call      0x8304e0
008896f7 83c404                   add       esp, 4
008896fa e9ac1b0000               jmp       0x88b2ab
008896ff 68c44fe200               push      0xe24fc4
00889704 56                       push      esi
00889705 e8c6b0b7ff               call      0x4047d0
0088970a 83c408                   add       esp, 8
0088970d 84c0                     test      al, al
0088970f 7417                     je        0x889728
00889711 8b5508                   mov       edx, dword ptr [ebp + 8]
00889714 81c208070000             add       edx, 0x708
0088971a 52                       push      edx
0088971b e8c06dfaff               call      0x8304e0
00889720 83c404                   add       esp, 4
00889723 e9831b0000               jmp       0x88b2ab
00889728 68a84fe200               push      0xe24fa8
0088972d 56                       push      esi
0088972e e89db0b7ff               call      0x4047d0
00889733 83c408                   add       esp, 8
00889736 84c0                     test      al, al
00889738 7416                     je        0x889750
0088973a 8b4508                   mov       eax, dword ptr [ebp + 8]
0088973d 050c070000               add       eax, 0x70c
00889742 50                       push      eax
00889743 e8986dfaff               call      0x8304e0
00889748 83c404                   add       esp, 4
0088974b e95b1b0000               jmp       0x88b2ab
00889750 68844fe200               push      0xe24f84
00889755 56                       push      esi
00889756 e875b0b7ff               call      0x4047d0
0088975b 83c408                   add       esp, 8
0088975e 84c0                     test      al, al
00889760 7417                     je        0x889779
00889762 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00889765 81c110070000             add       ecx, 0x710
0088976b 51                       push      ecx
0088976c e86f6dfaff               call      0x8304e0
00889771 83c404                   add       esp, 4
00889774 e9321b0000               jmp       0x88b2ab
00889779 68604fe200               push      0xe24f60
0088977e 56                       push      esi
0088977f e84cb0b7ff               call      0x4047d0
00889784 83c408                   add       esp, 8
00889787 84c0                     test      al, al
00889789 7417                     je        0x8897a2
0088978b 8b5508                   mov       edx, dword ptr [ebp + 8]
0088978e 81c214070000             add       edx, 0x714
00889794 52                       push      edx
00889795 e8466dfaff               call      0x8304e0
0088979a 83c404                   add       esp, 4
0088979d e9091b0000               jmp       0x88b2ab
008897a2 68444fe200               push      0xe24f44
008897a7 56                       push      esi
008897a8 e823b0b7ff               call      0x4047d0
008897ad 83c408                   add       esp, 8
008897b0 84c0                     test      al, al
008897b2 7416                     je        0x8897ca
008897b4 8b4508                   mov       eax, dword ptr [ebp + 8]
008897b7 0518070000               add       eax, 0x718
008897bc 50                       push      eax
008897bd e81e6dfaff               call      0x8304e0
008897c2 83c404                   add       esp, 4
008897c5 e9e11a0000               jmp       0x88b2ab
008897ca 68204fe200               push      0xe24f20
008897cf 56                       push      esi
008897d0 e8fbafb7ff               call      0x4047d0
008897d5 83c408                   add       esp, 8
008897d8 84c0                     test      al, al
008897da 7417                     je        0x8897f3
008897dc 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008897df 81c11c070000             add       ecx, 0x71c
008897e5 51                       push      ecx
008897e6 e8f56cfaff               call      0x8304e0
008897eb 83c404                   add       esp, 4
008897ee e9b81a0000               jmp       0x88b2ab
008897f3 68044fe200               push      0xe24f04
008897f8 56                       push      esi
008897f9 e8d2afb7ff               call      0x4047d0
008897fe 83c408                   add       esp, 8
00889801 84c0                     test      al, al
00889803 7417                     je        0x88981c
00889805 8b5508                   mov       edx, dword ptr [ebp + 8]
00889808 81c220070000             add       edx, 0x720
0088980e 52                       push      edx
0088980f e8cc6cfaff               call      0x8304e0
00889814 83c404                   add       esp, 4
00889817 e9                       .byte     0xe9
00889818 8f                       .byte     0x8f
00889819 1a00                     sbb       al, byte ptr [eax]
