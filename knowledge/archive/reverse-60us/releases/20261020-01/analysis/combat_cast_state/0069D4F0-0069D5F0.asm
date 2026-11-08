0069d4f0  55                       push       ebp
0069d4f1  8bec                     mov        ebp, esp
0069d4f3  6aff                     push       -1
0069d4f5  6826d1c600               push       0xc6d126
0069d4fa  64a100000000             mov        eax, dword ptr fs:[0]
0069d500  50                       push       eax
0069d501  64892500000000           mov        dword ptr fs:[0], esp
0069d508  81ec80060000             sub        esp, 0x680
0069d50e  53                       push       ebx
0069d50f  56                       push       esi
0069d510  57                       push       edi
0069d511  8bd9                     mov        ebx, ecx
0069d513  e8b824e2ff               call       0x4bf9d0
0069d518  8bcb                     mov        ecx, ebx
0069d51a  e8b1e9ffff               call       0x69bed0
0069d51f  8bcb                     mov        ecx, ebx
0069d521  e86a7cffff               call       0x695190
0069d526  8a83712d0000             mov        al, byte ptr [ebx + 0x2d71]
0069d52c  84c0                     test       al, al
0069d52e  743c                     je         0x69d56c
0069d530  8b8ba02d0000             mov        ecx, dword ptr [ebx + 0x2da0]
0069d536  85c9                     test       ecx, ecx
0069d538  7409                     je         0x69d543
0069d53a  8b01                     mov        eax, dword ptr [ecx]
0069d53c  ff5060                   call       dword ptr [eax + 0x60]
0069d53f  84c0                     test       al, al
0069d541  7529                     jne        0x69d56c
0069d543  c683712d000000           mov        byte ptr [ebx + 0x2d71], 0
0069d54a  8b83742d0000             mov        eax, dword ptr [ebx + 0x2d74]
0069d550  8b13                     mov        edx, dword ptr [ebx]
0069d552  50                       push       eax
0069d553  8bcb                     mov        ecx, ebx
0069d555  ff920c060000             call       dword ptr [edx + 0x60c]
0069d55b  8b83742d0000             mov        eax, dword ptr [ebx + 0x2d74]
0069d561  8b13                     mov        edx, dword ptr [ebx]
0069d563  50                       push       eax
0069d564  8bcb                     mov        ecx, ebx
0069d566  ff9224040000             call       dword ptr [edx + 0x424]
0069d56c  8a83702d0000             mov        al, byte ptr [ebx + 0x2d70]
0069d572  84c0                     test       al, al
0069d574  743c                     je         0x69d5b2
0069d576  8b8b942d0000             mov        ecx, dword ptr [ebx + 0x2d94]
0069d57c  85c9                     test       ecx, ecx
0069d57e  7409                     je         0x69d589
0069d580  8b11                     mov        edx, dword ptr [ecx]
0069d582  ff5260                   call       dword ptr [edx + 0x60]
0069d585  84c0                     test       al, al
0069d587  7529                     jne        0x69d5b2
0069d589  c683702d000000           mov        byte ptr [ebx + 0x2d70], 0
0069d590  8b8b682d0000             mov        ecx, dword ptr [ebx + 0x2d68]
0069d596  8b03                     mov        eax, dword ptr [ebx]
0069d598  51                       push       ecx
0069d599  8bcb                     mov        ecx, ebx
0069d59b  ff900c060000             call       dword ptr [eax + 0x60c]
0069d5a1  8b83682d0000             mov        eax, dword ptr [ebx + 0x2d68]
0069d5a7  8b13                     mov        edx, dword ptr [ebx]
0069d5a9  50                       push       eax
0069d5aa  8bcb                     mov        ecx, ebx
0069d5ac  ff9224040000             call       dword ptr [edx + 0x424]
0069d5b2  8a83342e0000             mov        al, byte ptr [ebx + 0x2e34]
0069d5b8  33ff                     xor        edi, edi
0069d5ba  84c0                     test       al, al
0069d5bc  7444                     je         0x69d602
0069d5be  8b8b302e0000             mov        ecx, dword ptr [ebx + 0x2e30]
0069d5c4  3bcf                     cmp        ecx, edi
0069d5c6  7409                     je         0x69d5d1
0069d5c8  8b11                     mov        edx, dword ptr [ecx]
0069d5ca  ff5260                   call       dword ptr [edx + 0x60]
0069d5cd  84c0                     test       al, al
0069d5cf  7531                     jne        0x69d602
0069d5d1  8db35c150000             lea        esi, [ebx + 0x155c]
0069d5d7  8bce                     mov        ecx, esi
0069d5d9  e8824ad6ff               call       0x402060
0069d5de  83f808                   cmp        eax, 8
0069d5e1  741f                     je         0x69d602
0069d5e3  8bce                     mov        ecx, esi
0069d5e5  e8764ad6ff               call       0x402060
0069d5ea  83f807                   cmp        eax, 7
0069d5ed  7413                     je         0x69d602
0069d5ef  8b                       .byte      0x8b