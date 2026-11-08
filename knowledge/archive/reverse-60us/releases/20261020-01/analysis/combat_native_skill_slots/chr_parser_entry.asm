0088b2d0  55                       push       ebp
0088b2d1  8bec                     mov        ebp, esp
0088b2d3  6aff                     push       -1
0088b2d5  68af1bc800               push       0xc81baf
0088b2da  64a100000000             mov        eax, dword ptr fs:[0]
0088b2e0  50                       push       eax
0088b2e1  64892500000000           mov        dword ptr fs:[0], esp
0088b2e8  81eca8000000             sub        esp, 0xa8
0088b2ee  57                       push       edi
0088b2ef  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
0088b2f2  57                       push       edi
0088b2f3  6840d80b01               push       0x10bd840
0088b2f8  e89344faff               call       0x82f790
0088b2fd  83c408                   add        esp, 8
0088b300  84c0                     test       al, al
0088b302  750f                     jne        0x88b313
0088b304  5f                       pop        edi
0088b305  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0088b308  64890d00000000           mov        dword ptr fs:[0], ecx
0088b30f  8be5                     mov        esp, ebp
0088b311  5d                       pop        ebp
0088b312  c3                       ret        
0088b313  53                       push       ebx
0088b314  56                       push       esi
0088b315  8b7508                   mov        esi, dword ptr [ebp + 8]
0088b318  8bce                     mov        ecx, esi
0088b31a  e821ac0000               call       0x895f40
0088b31f  57                       push       edi
0088b320  6840d80b01               push       0x10bd840
0088b325  8d86040c0000             lea        eax, [esi + 0xc04]
0088b32b  68f8b8ca00               push       0xcab8f8
0088b330  50                       push       eax
0088b331  e8da43faff               call       0x82f710
0088b336  33ff                     xor        edi, edi
0088b338  83c410                   add        esp, 0x10
0088b33b  c745dc07000000           mov        dword ptr [ebp - 0x24], 7
0088b342  897dd8                   mov        dword ptr [ebp - 0x28], edi
0088b345  66897dc8                 mov        word ptr [ebp - 0x38], di
0088b349  68e0baca00               push       0xcabae0
0088b34e  8d4dec                   lea        ecx, [ebp - 0x14]
0088b351  897dfc                   mov        dword ptr [ebp - 4], edi
0088b354  897dec                   mov        dword ptr [ebp - 0x14], edi
0088b357  e844851c00               call       0xa538a0
0088b35c  8d8620020000             lea        eax, [esi + 0x220]
0088b362  8945e0                   mov        dword ptr [ebp - 0x20], eax
0088b365  8d4dc4                   lea        ecx, [ebp - 0x3c]
0088b368  8d8680020000             lea        eax, [esi + 0x280]
0088b36e  6a01                     push       1
0088b370  8d5e20                   lea        ebx, [esi + 0x20]
0088b373  51                       push       ecx
0088b374  c645fc01                 mov        byte ptr [ebp - 4], 1
0088b378  c645f300                 mov        byte ptr [ebp - 0xd], 0
0088b37c  895dbc                   mov        dword ptr [ebp - 0x44], ebx
0088b37f  8945c0                   mov        dword ptr [ebp - 0x40], eax
0088b382  897db8                   mov        dword ptr [ebp - 0x48], edi
0088b385  897db4                   mov        dword ptr [ebp - 0x4c], edi
0088b388  e85354faff               call       0x8307e0
0088b38d  83c408                   add        esp, 8
0088b390  84c0                     test       al, al
0088b392  0f8423130000             je         0x88c6bb
