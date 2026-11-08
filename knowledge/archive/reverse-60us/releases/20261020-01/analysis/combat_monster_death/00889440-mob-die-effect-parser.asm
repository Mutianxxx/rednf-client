00889440 682050e200               push      0xe25020
00889445 56                       push      esi
00889446 e885b3b7ff               call      0x4047d0
0088944b 83c408                   add       esp, 8
0088944e 84c0                     test      al, al
00889450 742f                     je        0x889481
00889452 57                       push      edi
00889453 e87863faff               call      0x82f7d0
00889458 8b7508                   mov       esi, dword ptr [ebp + 8]
0088945b 57                       push      edi
0088945c 8986b4070000             mov       dword ptr [esi + 0x7b4], eax
00889462 e86963faff               call      0x82f7d0
00889467 57                       push      edi
00889468 8986b8070000             mov       dword ptr [esi + 0x7b8], eax
0088946e e85d63faff               call      0x82f7d0
00889473 83c40c                   add       esp, 0xc
00889476 8986bc070000             mov       dword ptr [esi + 0x7bc], eax
0088947c e92a1e0000               jmp       0x88b2ab
