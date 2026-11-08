00e67b98  4e                       dec        esi
00e67b99  656f                     outsd      dx, dword ptr gs:[esi]
00e67b9b  706c                     jo         0xe67c09
00e67b9d  6550                     push       eax
00e67b9f  61                       popal      
00e67ba0  636b5f                   arpl       word ptr [ebx + 0x5f], bp
00e67ba3  42                       inc        edx
00e67ba4  696c6c0066006900         imul       ebp, dword ptr [esp + ebp*2], 0x690066
00e67bac  6c                       insb       byte ptr es:[edi], dx
00e67bad  006500                   add        byte ptr [ebp], ah
00e67bb0  2000                     and        byte ptr [eax], al
00e67bb2  64006f00                 add        byte ptr fs:[edi], ch
00e67bb6  65007300                 add        byte ptr gs:[ebx], dh
00e67bba  6e                       outsb      dx, byte ptr [esi]
00e67bbb  0027                     add        byte ptr [edi], ah
00e67bbd  00740020                 add        byte ptr [eax + eax + 0x20], dh
00e67bc1  006500                   add        byte ptr [ebp], ah
00e67bc4  7800                     js         0xe67bc6
00e67bc6  690073007400             imul       eax, dword ptr [eax], 0x740073
00e67bcc  2000                     and        byte ptr [eax], al
00e67bce  2d00200025               sub        eax, 0x25002000
00e67bd3  007300                   add        byte ptr [ebx], dh
00e67bd6  0000                     add        byte ptr [eax], al
00e67bd8  66006900                 add        byte ptr [ecx], ch
00e67bdc  6c                       insb       byte ptr es:[edi], dx
00e67bdd  006500                   add        byte ptr [ebp], ah
00e67be0  2000                     and        byte ptr [eax], al
00e67be2  6e                       outsb      dx, byte ptr [esi]
00e67be3  006100                   add        byte ptr [ecx], ah
00e67be6  6d                       insd       dword ptr es:[edi], dx
00e67be7  006500                   add        byte ptr [ebp], ah
00e67bea  3a00                     cmp        al, byte ptr [eax]
00e67bec  2000                     and        byte ptr [eax], al
00e67bee  2500730000               and        eax, 0x7300
00e67bf3  007200                   add        byte ptr [edx], dh
00e67bf6  65006100                 add        byte ptr gs:[ecx], ah
00e67bfa  64006900                 add        byte ptr fs:[ecx], ch
00e67bfe  6e                       outsb      dx, byte ptr [esi]
00e67bff  006700                   add        byte ptr [edi], ah
00e67c02  2000                     and        byte ptr [eax], al
00e67c04  66006900                 add        byte ptr [ecx], ch
00e67c08  6c                       insb       byte ptr es:[edi], dx
00e67c09  006500                   add        byte ptr [ebp], ah
00e67c0c  2000                     and        byte ptr [eax], al
00e67c0e  6800650061               push       0x61006500
00e67c13  00640065                 add        byte ptr [eax + eax + 0x65], ah
00e67c17  007200                   add        byte ptr [edx], dh
00e67c1a  2000                     and        byte ptr [eax], al
00e67c1c  7700                     ja         0xe67c1e
00e67c1e  61                       popal      
00e67c1f  007300                   add        byte ptr [ebx], dh
00e67c22  2000                     and        byte ptr [eax], al
00e67c24  66006100                 add        byte ptr [ecx], ah
00e67c28  69006c006500             imul       eax, dword ptr [eax], 0x65006c
00e67c2e  640000                   add        byte ptr fs:[eax], al
00e67c31  0000                     add        byte ptr [eax], al
00e67c33  002500730020             add        byte ptr [0x20007300], ah
00e67c39  006600                   add        byte ptr [esi], ah
00e67c3c  69006c006500             imul       eax, dword ptr [eax], 0x65006c
00e67c42  2000                     and        byte ptr [eax], al
00e67c44  7700                     ja         0xe67c46
00e67c46  61                       popal      
00e67c47  007300                   add        byte ptr [ebx], dh
00e67c4a  2000                     and        byte ptr [eax], al
00e67c4c  64006500                 add        byte ptr fs:[ebp], ah
00e67c50  6c                       insb       byte ptr es:[edi], dx
00e67c51  006500                   add        byte ptr [ebp], ah
00e67c54  7400                     je         0xe67c56
00e67c56  6500640020               add        byte ptr gs:[eax + eax + 0x20], ah
00e67c5b  006200                   add        byte ptr [edx], ah
00e67c5e  7900                     jns        0xe67c60
00e67c60  2000                     and        byte ptr [eax], al
00e67c62  7200                     jb         0xe67c64
00e67c64  690068007700             imul       eax, dword ptr [eax], 0x770068
00e67c6a  61                       popal      
00e67c6b  006e00                   add        byte ptr [esi], ch
00e67c6e  0000                     add        byte ptr [eax], al
00e67c70  4e                       dec        esi
00e67c71  005000                   add        byte ptr [eax], dl
00e67c74  4b                       dec        ebx
00e67c75  0020                     add        byte ptr [eax], ah
00e67c77  004600                   add        byte ptr [esi], al
00e67c7a  69006c006500             imul       eax, dword ptr [eax], 0x65006c
00e67c80  2000                     and        byte ptr [eax], al
00e67c82  43                       inc        ebx
00e67c83  006800                   add        byte ptr [eax], ch
00e67c86  65006300                 add        byte ptr gs:[ebx], ah
00e67c8a  6b0073                   imul       eax, dword ptr [eax], 0x73
00e67c8d  007500                   add        byte ptr [ebp], dh
00e67c90  6d                       insd       dword ptr es:[edi], dx
00e67c91  0020                     add        byte ptr [eax], ah
00e67c93  006900                   add        byte ptr [ecx], ch
00e67c96  7300                     jae        0xe67c98
00e67c98  2000                     and        byte ptr [eax], al
00e67c9a  69006e006300             imul       eax, dword ptr [eax], 0x63006e
00e67ca0  6f                       outsd      dx, dword ptr [esi]
00e67ca1  007200                   add        byte ptr [edx], dh
00e67ca4  7200                     jb         0xe67ca6
00e67ca6  65006300                 add        byte ptr gs:[ebx], ah
00e67caa  7400                     je         0xe67cac
00e67cac  0000                     add        byte ptr [eax], al
00e67cae  0000                     add        byte ptr [eax], al
00e67cb0  2a00                     sub        al, byte ptr [eax]
00e67cb2  2e006e00                 add        byte ptr cs:[esi], ch
00e67cb6  7000                     jo         0xe67cb8
00e67cb8  6b0000                   imul       eax, dword ptr [eax], 0
00e67cbb  00                       .byte      0x00
00e67cbc  25                       .byte      0x25
00e67cbd  006600                   add        byte ptr [esi], ah