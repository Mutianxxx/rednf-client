00e1e968  5b                       pop        ebx
00e1e969  00740068                 add        byte ptr [eax + eax + 0x68], dh
00e1e96d  007200                   add        byte ptr [edx], dh
00e1e970  6f                       outsd      dx, dword ptr [esi]
00e1e971  007700                   add        byte ptr [edi], dh
00e1e974  2000                     and        byte ptr [eax], al
00e1e976  6d                       insd       dword ptr es:[edi], dx
00e1e977  006f00                   add        byte ptr [edi], ch
00e1e97a  7400                     je         0xe1e97c
00e1e97c  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1e982  2000                     and        byte ptr [eax], al
00e1e984  3400                     xor        al, 0
00e1e986  2d0032005d               sub        eax, 0x5d003200
00e1e98b  0000                     add        byte ptr [eax], al
00e1e98d  0000                     add        byte ptr [eax], al
00e1e98f  005b00                   add        byte ptr [ebx], bl
00e1e992  7400                     je         0xe1e994
00e1e994  680072006f               push       0x6f007200
00e1e999  007700                   add        byte ptr [edi], dh
00e1e99c  2000                     and        byte ptr [eax], al
00e1e99e  6d                       insd       dword ptr es:[edi], dx
00e1e99f  006f00                   add        byte ptr [edi], ch
00e1e9a2  7400                     je         0xe1e9a4
00e1e9a4  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1e9aa  2000                     and        byte ptr [eax], al
00e1e9ac  3400                     xor        al, 0
00e1e9ae  2d0031005d               sub        eax, 0x5d003100
00e1e9b3  0000                     add        byte ptr [eax], al
00e1e9b5  0000                     add        byte ptr [eax], al
00e1e9b7  005b00                   add        byte ptr [ebx], bl
00e1e9ba  7400                     je         0xe1e9bc
00e1e9bc  680072006f               push       0x6f007200
00e1e9c1  007700                   add        byte ptr [edi], dh
00e1e9c4  2000                     and        byte ptr [eax], al
00e1e9c6  6d                       insd       dword ptr es:[edi], dx
00e1e9c7  006f00                   add        byte ptr [edi], ch
00e1e9ca  7400                     je         0xe1e9cc
00e1e9cc  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1e9d2  2000                     and        byte ptr [eax], al
00e1e9d4  3300                     xor        eax, dword ptr [eax]
00e1e9d6  2d0032005d               sub        eax, 0x5d003200
00e1e9db  0000                     add        byte ptr [eax], al
00e1e9dd  0000                     add        byte ptr [eax], al
00e1e9df  005b00                   add        byte ptr [ebx], bl
00e1e9e2  7400                     je         0xe1e9e4
00e1e9e4  680072006f               push       0x6f007200
00e1e9e9  007700                   add        byte ptr [edi], dh
00e1e9ec  2000                     and        byte ptr [eax], al
00e1e9ee  6d                       insd       dword ptr es:[edi], dx
00e1e9ef  006f00                   add        byte ptr [edi], ch
00e1e9f2  7400                     je         0xe1e9f4
00e1e9f4  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1e9fa  2000                     and        byte ptr [eax], al
00e1e9fc  3300                     xor        eax, dword ptr [eax]
00e1e9fe  2d0031005d               sub        eax, 0x5d003100
00e1ea03  0000                     add        byte ptr [eax], al
00e1ea05  0000                     add        byte ptr [eax], al
00e1ea07  005b00                   add        byte ptr [ebx], bl
00e1ea0a  7400                     je         0xe1ea0c
00e1ea0c  680072006f               push       0x6f007200
00e1ea11  007700                   add        byte ptr [edi], dh
00e1ea14  2000                     and        byte ptr [eax], al
00e1ea16  6d                       insd       dword ptr es:[edi], dx
00e1ea17  006f00                   add        byte ptr [edi], ch
00e1ea1a  7400                     je         0xe1ea1c
00e1ea1c  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1ea22  2000                     and        byte ptr [eax], al
00e1ea24  3200                     xor        al, byte ptr [eax]
00e1ea26  2d0032005d               sub        eax, 0x5d003200
00e1ea2b  0000                     add        byte ptr [eax], al
00e1ea2d  0000                     add        byte ptr [eax], al
00e1ea2f  005b00                   add        byte ptr [ebx], bl
00e1ea32  7400                     je         0xe1ea34
00e1ea34  680072006f               push       0x6f007200
00e1ea39  007700                   add        byte ptr [edi], dh
00e1ea3c  2000                     and        byte ptr [eax], al
00e1ea3e  6d                       insd       dword ptr es:[edi], dx
00e1ea3f  006f00                   add        byte ptr [edi], ch
00e1ea42  7400                     je         0xe1ea44
00e1ea44  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1ea4a  2000                     and        byte ptr [eax], al
00e1ea4c  3200                     xor        al, byte ptr [eax]
00e1ea4e  2d0031005d               sub        eax, 0x5d003100
00e1ea53  0000                     add        byte ptr [eax], al
00e1ea55  0000                     add        byte ptr [eax], al
00e1ea57  005b00                   add        byte ptr [ebx], bl
00e1ea5a  7400                     je         0xe1ea5c
00e1ea5c  680072006f               push       0x6f007200
00e1ea61  007700                   add        byte ptr [edi], dh
00e1ea64  2000                     and        byte ptr [eax], al
00e1ea66  6d                       insd       dword ptr es:[edi], dx
00e1ea67  006f00                   add        byte ptr [edi], ch
00e1ea6a  7400                     je         0xe1ea6c
00e1ea6c  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1ea72  2000                     and        byte ptr [eax], al
00e1ea74  3100                     xor        dword ptr [eax], eax
00e1ea76  2d0032005d               sub        eax, 0x5d003200
00e1ea7b  0000                     add        byte ptr [eax], al
00e1ea7d  0000                     add        byte ptr [eax], al
00e1ea7f  005b00                   add        byte ptr [ebx], bl
00e1ea82  7400                     je         0xe1ea84
00e1ea84  680072006f               push       0x6f007200
00e1ea89  007700                   add        byte ptr [edi], dh
00e1ea8c  2000                     and        byte ptr [eax], al
00e1ea8e  6d                       insd       dword ptr es:[edi], dx
00e1ea8f  006f00                   add        byte ptr [edi], ch
00e1ea92  7400                     je         0xe1ea94
00e1ea94  69006f006e00             imul       eax, dword ptr [eax], 0x6e006f
00e1ea9a  2000                     and        byte ptr [eax], al
00e1ea9c  3100                     xor        dword ptr [eax], eax
00e1ea9e  2d0031005d               sub        eax, 0x5d003100
00e1eaa3  0000                     add        byte ptr [eax], al
00e1eaa5  00                       .byte      0x00