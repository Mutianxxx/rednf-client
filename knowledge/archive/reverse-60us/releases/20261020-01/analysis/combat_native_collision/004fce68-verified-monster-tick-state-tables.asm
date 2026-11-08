004fce68 b4c8                     mov       ah, 0xc8
004fce6a 4f                       dec       edi
004fce6b 002a                     add       byte ptr [edx], ch
004fce6d cb                       retf      
004fce6e 4f                       dec       edi
004fce6f 0059c9                   add       byte ptr [ecx - 0x37], bl
004fce72 4f                       dec       edi
004fce73 0007                     add       byte ptr [edi], al
004fce75 c9                       leave     
004fce76 4f                       dec       edi
004fce77 0055ca                   add       byte ptr [ebp - 0x36], dl
004fce7a 4f                       dec       edi
004fce7b 0077ca                   add       byte ptr [edi - 0x36], dh
004fce7e 4f                       dec       edi
004fce7f 006ccd4f                 add       byte ptr [ebp + ecx*8 + 0x4f], ch
004fce83 0000                     add       byte ptr [eax], al
004fce85 06                       push      es
004fce86 06                       push      es
004fce87 06                       push      es
004fce88 06                       push      es
004fce89 0106                     add       dword ptr [esi], eax
004fce8b 06                       push      es
004fce8c 0206                     add       al, byte ptr [esi]
004fce8e 030406                   add       eax, dword ptr [esi + eax]
004fce91 05                       .byte     0x05
