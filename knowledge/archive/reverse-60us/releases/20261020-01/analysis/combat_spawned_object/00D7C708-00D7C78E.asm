00d7c708  45                       inc        ebp
00d7c709  006600                   add        byte ptr [esi], ah
00d7c70c  66006500                 add        byte ptr [ebp], ah
00d7c710  6300                     arpl       word ptr [eax], ax
00d7c712  7400                     je         0xd7c714
00d7c714  2f                       das        
00d7c715  004100                   add        byte ptr [ecx], al
00d7c718  6e                       outsb      dx, byte ptr [esi]
00d7c719  006900                   add        byte ptr [ecx], ch
00d7c71c  6d                       insd       dword ptr es:[edi], dx
00d7c71d  006100                   add        byte ptr [ecx], ah
00d7c720  7400                     je         0xd7c722
00d7c722  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00d7c728  2f                       das        
00d7c729  005200                   add        byte ptr [edx], dl
00d7c72c  65006c0065               add        byte ptr gs:[eax + eax + 0x65], ch
00d7c731  006100                   add        byte ptr [ecx], ah
00d7c734  7300                     jae        0xd7c736
00d7c736  65005700                 add        byte ptr gs:[edi], dl
00d7c73a  61                       popal      
00d7c73b  007600                   add        byte ptr [esi], dh
00d7c73e  650032                   add        byte ptr gs:[edx], dh
00d7c741  002e                     add        byte ptr [esi], ch
00d7c743  006100                   add        byte ptr [ecx], ah
00d7c746  6e                       outsb      dx, byte ptr [esi]
00d7c747  006900                   add        byte ptr [ecx], ch
00d7c74a  0000                     add        byte ptr [eax], al
00d7c74c  0000                     add        byte ptr [eax], al
00d7c74e  0000                     add        byte ptr [eax], al
00d7c750  45                       inc        ebp
00d7c751  006600                   add        byte ptr [esi], ah
00d7c754  66006500                 add        byte ptr [ebp], ah
00d7c758  6300                     arpl       word ptr [eax], ax
00d7c75a  7400                     je         0xd7c75c
00d7c75c  2f                       das        
00d7c75d  004100                   add        byte ptr [ecx], al
00d7c760  6e                       outsb      dx, byte ptr [esi]
00d7c761  006900                   add        byte ptr [ecx], ch
00d7c764  6d                       insd       dword ptr es:[edi], dx
00d7c765  006100                   add        byte ptr [ecx], ah
00d7c768  7400                     je         0xd7c76a
00d7c76a  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00d7c770  2f                       das        
00d7c771  005200                   add        byte ptr [edx], dl
00d7c774  65006c0065               add        byte ptr gs:[eax + eax + 0x65], ch
00d7c779  006100                   add        byte ptr [ecx], ah
00d7c77c  7300                     jae        0xd7c77e
00d7c77e  65005700                 add        byte ptr gs:[edi], dl
00d7c782  61                       popal      
00d7c783  007600                   add        byte ptr [esi], dh
00d7c786  650031                   add        byte ptr gs:[ecx], dh
00d7c789  002e                     add        byte ptr [esi], ch
00d7c78b  006100                   add        byte ptr [ecx], ah