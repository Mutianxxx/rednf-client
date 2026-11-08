0082fc70  55                       push       ebp
0082fc71  8bec                     mov        ebp, esp
0082fc73  56                       push       esi
0082fc74  8b7508                   mov        esi, dword ptr [ebp + 8]
0082fc77  680038e100               push       0xe13800
0082fc7c  56                       push       esi
0082fc7d  e869113d00               call       0xc00deb
0082fc82  83c408                   add        esp, 8
0082fc85  85c0                     test       eax, eax
0082fc87  7503                     jne        0x82fc8c
0082fc89  5e                       pop        esi
0082fc8a  5d                       pop        ebp
0082fc8b  c3                       ret        
0082fc8c  68e037e100               push       0xe137e0
0082fc91  56                       push       esi
0082fc92  e854113d00               call       0xc00deb
0082fc97  83c408                   add        esp, 8
0082fc9a  85c0                     test       eax, eax
0082fc9c  7508                     jne        0x82fca6
0082fc9e  b801000000               mov        eax, 1
0082fca3  5e                       pop        esi
0082fca4  5d                       pop        ebp
0082fca5  c3                       ret        
0082fca6  68c037e100               push       0xe137c0
0082fcab  56                       push       esi
0082fcac  e83a113d00               call       0xc00deb
0082fcb1  83c408                   add        esp, 8
0082fcb4  85c0                     test       eax, eax
0082fcb6  7508                     jne        0x82fcc0
0082fcb8  b802000000               mov        eax, 2
0082fcbd  5e                       pop        esi
0082fcbe  5d                       pop        ebp
0082fcbf  c3                       ret        
0082fcc0  68a037e100               push       0xe137a0
0082fcc5  56                       push       esi
0082fcc6  e820113d00               call       0xc00deb
0082fccb  83c408                   add        esp, 8
0082fcce  f7d8                     neg        eax
0082fcd0  1bc0                     sbb        eax, eax
0082fcd2  f7d8                     neg        eax
0082fcd4  83c003                   add        eax, 3
0082fcd7  5e                       pop        esi
0082fcd8  5d                       pop        ebp
0082fcd9  c3                       ret        
0082fcda  cc                       int3       
0082fcdb  cc                       int3       
0082fcdc  cc                       int3       
0082fcdd  cc                       int3       
0082fcde  cc                       int3       
0082fcdf  cc                       int3       
0082fce0  55                       push       ebp
0082fce1  8bec                     mov        ebp, esp
0082fce3  8b4508                   mov        eax, dword ptr [ebp + 8]
0082fce6  85c0                     test       eax, eax
0082fce8  6a10                     push       0x10
0082fcea  7519                     jne        0x82fd05
0082fcec  680038e100               push       0xe13800
0082fcf1  6820ef0a01               push       0x10aef20
0082fcf6  e8cb0b3d00               call       0xc008c6
0082fcfb  83c40c                   add        esp, 0xc
0082fcfe  b820ef0a01               mov        eax, 0x10aef20
0082fd03  5d                       pop        ebp
0082fd04  c3                       ret        
0082fd05  83f801                   cmp        eax, 1
0082fd08  7519                     jne        0x82fd23
0082fd0a  68e037e100               push       0xe137e0
0082fd0f  6820ef0a01               push       0x10aef20
0082fd14  e8ad0b3d00               call       0xc008c6
0082fd19  83c40c                   add        esp, 0xc
0082fd1c  b820ef0a01               mov        eax, 0x10aef20
0082fd21  5d                       pop        ebp
0082fd22  c3                       ret        
0082fd23  83f802                   cmp        eax, 2
0082fd26  7519                     jne        0x82fd41
0082fd28  68c037e100               push       0xe137c0
0082fd2d  6820ef0a01               push       0x10aef20
0082fd32  e88f0b3d00               call       0xc008c6
0082fd37  83c40c                   add        esp, 0xc
0082fd3a  b820ef0a01               mov        eax, 0x10aef20
0082fd3f  5d                       pop        ebp
0082fd40  c3                       ret        
0082fd41  83f803                   cmp        eax, 3
0082fd44  7519                     jne        0x82fd5f
0082fd46  68a037e100               push       0xe137a0
0082fd4b  6820ef0a01               push       0x10aef20
0082fd50  e8710b3d00               call       0xc008c6
0082fd55  83c40c                   add        esp, 0xc
0082fd58  b820ef0a01               mov        eax, 0x10aef20
0082fd5d  5d                       pop        ebp
0082fd5e  c3                       ret        
0082fd5f  68                       .byte      0x68
