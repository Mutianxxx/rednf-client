005f1f54  b0a7                     mov        al, 0xa7
005f1f56  5e                       pop        esi
005f1f57  00ea                     add        dl, ch
005f1f59  a7                       cmpsd      dword ptr [esi], dword ptr es:[edi]
005f1f5a  5e                       pop        esi
005f1f5b  0024a8                   add        byte ptr [eax + ebp*4], ah
005f1f5e  5e                       pop        esi
005f1f5f  005ea8                   add        byte ptr [esi - 0x58], bl
005f1f62  5e                       pop        esi
005f1f63  0098a85e00d4             add        byte ptr [eax - 0x2bffa158], bl
005f1f69  a85e                     test       al, 0x5e
005f1f6b  000e                     add        byte ptr [esi], cl
005f1f6d  a95e0048a9               test       eax, 0xa948005e
005f1f72  5e                       pop        esi
005f1f73  0082a95e00bc             add        byte ptr [edx - 0x43ffa157], al
005f1f79  a9                       .byte      0xa9
005f1f7a  5e                       pop        esi
005f1f7b  00                       .byte      0x00