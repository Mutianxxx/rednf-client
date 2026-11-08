00cf08a0  57                       push       edi
00cf08a1  004100                   add        byte ptr [ecx], al
00cf08a4  56                       push       esi
00cf08a5  004500                   add        byte ptr [ebp], al
00cf08a8  5f                       pop        edi
00cf08a9  004300                   add        byte ptr [ebx], al
00cf08ac  41                       inc        ecx
00cf08ad  004e00                   add        byte ptr [esi], cl
00cf08b0  43                       inc        ebx
00cf08b1  004c0045                 add        byte ptr [eax + eax + 0x45], cl
00cf08b5  0000                     add        byte ptr [eax], al
00cf08b7  00                       .byte      0x00