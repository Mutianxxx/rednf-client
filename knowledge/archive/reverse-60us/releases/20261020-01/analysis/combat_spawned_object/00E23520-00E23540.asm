00e23520  5b                       pop        ebx
00e23521  006200                   add        byte ptr [edx], ah
00e23524  61                       popal      
00e23525  007300                   add        byte ptr [ebx], dh
00e23528  690063002000             imul       eax, dword ptr [eax], 0x200063
00e2352e  6d                       insd       dword ptr es:[edi], dx
00e2352f  006f00                   add        byte ptr [edi], ch
00e23532  7400                     je         0xe23534
00e23534  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e2353a  5d                       pop        ebp
00e2353b  0000                     add        byte ptr [eax], al
00e2353d  0000                     add        byte ptr [eax], al
00e2353f  00                       .byte      0x00