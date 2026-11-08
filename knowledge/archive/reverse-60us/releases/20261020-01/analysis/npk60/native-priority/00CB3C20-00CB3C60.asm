00cb3c20  49                       dec        ecx
00cb3c21  006d00                   add        byte ptr [ebp], ch
00cb3c24  61                       popal      
00cb3c25  006700                   add        byte ptr [edi], ah
00cb3c28  65005000                 add        byte ptr gs:[eax], dl
00cb3c2c  61                       popal      
00cb3c2d  006300                   add        byte ptr [ebx], ah
00cb3c30  6b0073                   imul       eax, dword ptr [eax], 0x73
00cb3c33  0032                     add        byte ptr [edx], dh
00cb3c35  002f                     add        byte ptr [edi], ch
00cb3c37  0000                     add        byte ptr [eax], al
00cb3c39  0000                     add        byte ptr [eax], al
00cb3c3b  0021                     add        byte ptr [ecx], ah
00cb3c3d  004900                   add        byte ptr [ecx], cl
00cb3c40  6d                       insd       dword ptr es:[edi], dx
00cb3c41  006100                   add        byte ptr [ecx], ah
00cb3c44  67006500                 add        byte ptr [di], ah
00cb3c48  50                       push       eax
00cb3c49  006100                   add        byte ptr [ecx], ah
00cb3c4c  6300                     arpl       word ptr [eax], ax
00cb3c4e  6b0073                   imul       eax, dword ptr [eax], 0x73
00cb3c51  0000                     add        byte ptr [eax], al
00cb3c53  005f00                   add        byte ptr [edi], bl
00cb3c56  49                       dec        ecx
00cb3c57  006d00                   add        byte ptr [ebp], ch
00cb3c5a  61                       popal      
00cb3c5b  006700                   add        byte ptr [edi], ah
00cb3c5e  65                       .byte      0x65
00cb3c5f  00                       .byte      0x00