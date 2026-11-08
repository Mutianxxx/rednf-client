00e1f15c  5b                       pop        ebx
00e1f15d  006100                   add        byte ptr [ecx], ah
00e1f160  7400                     je         0xe1f162
00e1f162  7400                     je         0xe1f164
00e1f164  61                       popal      
00e1f165  006300                   add        byte ptr [ebx], ah
00e1f168  6b0020                   imul       eax, dword ptr [eax], 0x20
00e1f16b  006900                   add        byte ptr [ecx], ch
00e1f16e  6e                       outsb      dx, byte ptr [esi]
00e1f16f  006600                   add        byte ptr [esi], ah
00e1f172  6f                       outsd      dx, dword ptr [esi]
00e1f173  005d00                   add        byte ptr [ebp], bl
00e1f176  0000                     add        byte ptr [eax], al