0088948d c408                     les       ecx, ptr [eax]
0088948f 84c0                     test      al, al
00889491 7423                     je        0x8894b6
00889493 8b7508                   mov       esi, dword ptr [ebp + 8]
00889496 8d86b8060000             lea       eax, [esi + 0x6b8]
0088949c 50                       push      eax
0088949d e83e70faff               call      0x8304e0
008894a2 57                       push      edi
008894a3 e82863faff               call      0x82f7d0
008894a8 83c408                   add       esp, 8
008894ab 8986bc060000             mov       dword ptr [esi + 0x6bc], eax
008894b1 e9f51d0000               jmp       0x88b2ab
008894b6 68c8ebe100               push      0xe1ebc8
008894bb 56                       push      esi
008894bc e80fb3b7ff               call      0x4047d0
008894c1 83c408                   add       esp, 8
008894c4 84c0                     test      al, al
008894c6 7417                     je        0x8894df
008894c8 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008894cb 81c1c0060000             add       ecx, 0x6c0
008894d1 51                       push      ecx
008894d2 e80970faff               call      0x8304e0
008894d7 83c404                   add       esp, 4
008894da e9cc1d0000               jmp       0x88b2ab
008894df 68acebe100               push      0xe1ebac
008894e4 56                       push      esi
008894e5 e8e6b2b7ff               call      0x4047d0
008894ea 83c408                   add       esp, 8
008894ed 84c0                     test      al, al
008894ef 7417                     je        0x889508
008894f1 8b5508                   mov       edx, dword ptr [ebp + 8]
008894f4 81c2c4060000             add       edx, 0x6c4
008894fa 52                       push      edx
008894fb e8e06ffaff               call      0x8304e0
00889500 83c404                   add       esp, 4
00889503 e9a31d0000               jmp       0x88b2ab
00889508 6890ebe100               push      0xe1eb90
0088950d 56                       push      esi
0088950e e8bdb2b7ff               call      0x4047d0
00889513 83c408                   add       esp, 8
00889516 84c0                     test      al, al
00889518 7416                     je        0x889530
0088951a 8b4508                   mov       eax, dword ptr [ebp + 8]
0088951d 05c8060000               add       eax, 0x6c8
00889522 50                       push      eax
00889523 e8b86ffaff               call      0x8304e0
00889528 83c404                   add       esp, 4
0088952b e97b1d0000               jmp       0x88b2ab
00889530 686cebe100               push      0xe1eb6c
00889535 56                       push      esi
00889536 e895b2b7ff               call      0x4047d0
0088953b 83c408                   add       esp, 8
0088953e 84c0                     test      al, al
00889540 7417                     je        0x889559
00889542 8b4d08                   mov       ecx, dword ptr [ebp + 8]
