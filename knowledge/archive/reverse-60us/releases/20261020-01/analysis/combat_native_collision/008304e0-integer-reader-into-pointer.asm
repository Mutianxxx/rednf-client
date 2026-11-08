008304e0 55                       push      ebp
008304e1 8bec                     mov       ebp, esp
008304e3 53                       push      ebx
008304e4 56                       push      esi
008304e5 6a09                     push      9
008304e7 e8c49a2d00               call      0xb09fb0
008304ec 83c404                   add       esp, 4
008304ef b928120501               mov       ecx, 0x1051228
008304f4 32db                     xor       bl, bl
008304f6 e875240800               call      0x8b2970
008304fb 83e807                   sub       eax, 7
008304fe 7453                     je        0x830553
00830500 83e802                   sub       eax, 2
00830503 756c                     jne       0x830571
00830505 b928120501               mov       ecx, 0x1051228
0083050a e821260800               call      0x8b2b30
0083050f b928120501               mov       ecx, 0x1051228
00830514 8bf0                     mov       esi, eax
00830516 e855240800               call      0x8b2970
0083051b 83f80a                   cmp       eax, 0xa
0083051e 7551                     jne       0x830571
00830520 b928120501               mov       ecx, 0x1051228
00830525 e876260800               call      0x8b2ba0
0083052a 85c0                     test      eax, eax
0083052c 7507                     jne       0x830535
0083052e b87039e100               mov       eax, 0xe13970
00830533 eb31                     jmp       0x830566
00830535 8b0d94110501             mov       ecx, dword ptr [0x1051194]
0083053b 6bf63c                   imul      esi, esi, 0x3c
0083053e 50                       push      eax
0083053f 03f1                     add       esi, ecx
00830541 e80a272600               call      0xa92c50
00830546 83c404                   add       esp, 4
00830549 50                       push      eax
0083054a 8bce                     mov       ecx, esi
0083054c e85f620700               call      0x8a67b0
00830551 eb13                     jmp       0x830566
00830553 b928120501               mov       ecx, 0x1051228
00830558 e893250800               call      0x8b2af0
0083055d 50                       push      eax
0083055e e8ed262600               call      0xa92c50
00830563 83c404                   add       esp, 4
00830566 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00830569 50                       push      eax
0083056a e831332200               call      0xa538a0
0083056f b3                       .byte     0xb3
