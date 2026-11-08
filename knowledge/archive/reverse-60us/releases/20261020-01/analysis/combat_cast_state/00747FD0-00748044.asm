00747fd0  55                       push       ebp
00747fd1  8bec                     mov        ebp, esp
00747fd3  56                       push       esi
00747fd4  8bf1                     mov        esi, ecx
00747fd6  e84567f9ff               call       0x6de720
00747fdb  84c0                     test       al, al
00747fdd  740b                     je         0x747fea
00747fdf  8b86e82d0000             mov        eax, dword ptr [esi + 0x2de8]
00747fe5  5e                       pop        esi
00747fe6  5d                       pop        ebp
00747fe7  c20400                   ret        4
00747fea  8b4508                   mov        eax, dword ptr [ebp + 8]
00747fed  83f804                   cmp        eax, 4
00747ff0  7d0c                     jge        0x747ffe
00747ff2  8b8486e01b0000           mov        eax, dword ptr [esi + eax*4 + 0x1be0]
00747ff9  5e                       pop        esi
00747ffa  5d                       pop        ebp
00747ffb  c20400                   ret        4
00747ffe  33c0                     xor        eax, eax
00748000  5e                       pop        esi
00748001  5d                       pop        ebp
00748002  c20400                   ret        4
00748005  cc                       int3       
00748006  cc                       int3       
00748007  cc                       int3       
00748008  cc                       int3       
00748009  cc                       int3       
0074800a  cc                       int3       
0074800b  cc                       int3       
0074800c  cc                       int3       
0074800d  cc                       int3       
0074800e  cc                       int3       
0074800f  cc                       int3       
00748010  55                       push       ebp
00748011  8bec                     mov        ebp, esp
00748013  56                       push       esi
00748014  8bf1                     mov        esi, ecx
00748016  e80567f9ff               call       0x6de720
0074801b  84c0                     test       al, al
0074801d  740b                     je         0x74802a
0074801f  8b86e82d0000             mov        eax, dword ptr [esi + 0x2de8]
00748025  5e                       pop        esi
00748026  5d                       pop        ebp
00748027  c20400                   ret        4
0074802a  8b4508                   mov        eax, dword ptr [ebp + 8]
0074802d  83f804                   cmp        eax, 4
00748030  7d0c                     jge        0x74803e
00748032  8b8486f01b0000           mov        eax, dword ptr [esi + eax*4 + 0x1bf0]
00748039  5e                       pop        esi
0074803a  5d                       pop        ebp
0074803b  c20400                   ret        4
0074803e  33c0                     xor        eax, eax
00748040  5e                       pop        esi
00748041  5d                       pop        ebp
00748042  c2                       .byte      0xc2
00748043  04                       .byte      0x04