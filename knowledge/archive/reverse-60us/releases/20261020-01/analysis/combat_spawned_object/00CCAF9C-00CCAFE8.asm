00ccaf9c  50                       push       eax
00ccaf9d  006100                   add        byte ptr [ecx], ah
00ccafa0  7300                     jae        0xccafa2
00ccafa2  7300                     jae        0xccafa4
00ccafa4  690076006500             imul       eax, dword ptr [eax], 0x650076
00ccafaa  4f                       dec        edi
00ccafab  006200                   add        byte ptr [edx], ah
00ccafae  6a00                     push       0
00ccafb0  65006300                 add        byte ptr gs:[ebx], ah
00ccafb4  7400                     je         0xccafb6
00ccafb6  2f                       das        
00ccafb7  0000                     add        byte ptr [eax], al
00ccafb9  0000                     add        byte ptr [eax], al
00ccafbb  005000                   add        byte ptr [eax], dl
00ccafbe  61                       popal      
00ccafbf  007300                   add        byte ptr [ebx], dh
00ccafc2  7300                     jae        0xccafc4
00ccafc4  690076006500             imul       eax, dword ptr [eax], 0x650076
00ccafca  4f                       dec        edi
00ccafcb  006200                   add        byte ptr [edx], ah
00ccafce  6a00                     push       0
00ccafd0  65006300                 add        byte ptr gs:[ebx], ah
00ccafd4  7400                     je         0xccafd6
00ccafd6  2e007500                 add        byte ptr cs:[ebp], dh
00ccafda  7300                     jae        0xccafdc
00ccafdc  61                       popal      
00ccafdd  002e                     add        byte ptr [esi], ch
00ccafdf  006c0073                 add        byte ptr [eax + eax + 0x73], ch
00ccafe3  00740000                 add        byte ptr [eax + eax], dh
00ccafe7  00                       .byte      0x00