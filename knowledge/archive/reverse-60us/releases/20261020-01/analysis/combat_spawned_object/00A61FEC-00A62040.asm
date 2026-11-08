00a61fec  1019                     adc        byte ptr [ecx], bl
00a61fee  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a61fef  006819                   add        byte ptr [eax + 0x19], ch
00a61ff2  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a61ff3  00c2                     add        dl, al
00a61ff5  19a6001c1aa6             sbb        dword ptr [esi - 0x59e5e400], esp
00a61ffb  00741aa6                 add        byte ptr [edx + ebx - 0x5a], dh
00a61fff  00ce                     add        dh, cl
00a62001  1aa600281ba6             sbb        ah, byte ptr [esi - 0x59e4d800]
00a62007  007d1b                   add        byte ptr [ebp + 0x1b], bh
00a6200a  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a6200b  00d5                     add        ch, dl
00a6200d  1ba6002d1ca6             sbb        esp, dword ptr [esi - 0x59e3d300]
00a62013  00851ca600da             add        byte ptr [ebp - 0x25ff59e4], al
00a62019  1ca6                     sbb        al, 0xa6
00a6201b  0032                     add        byte ptr [edx], dh
00a6201d  1da6008a1d               sbb        eax, 0x1d8a00a6
00a62022  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a62023  00e2                     add        dl, ah
00a62025  1da6003a1e               sbb        eax, 0x1e3a00a6
00a6202a  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a6202b  00921ea600d6             add        byte ptr [edx - 0x29ff59e2], dl
00a62031  1f                       pop        ds
00a62032  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a62033  00d6                     add        dh, dl
00a62035  1f                       pop        ds
00a62036  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a62037  00fb                     add        bl, bh
00a62039  1e                       push       ds
00a6203a  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a6203b  006f1f                   add        byte ptr [edi + 0x1f], ch
00a6203e  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00a6203f  00                       .byte      0x00