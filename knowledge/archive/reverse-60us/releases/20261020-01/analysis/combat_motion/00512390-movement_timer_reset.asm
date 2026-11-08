00512390  53                       push       ebx
00512391  56                       push       esi
00512392  8bf1                     mov        esi, ecx
00512394  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
00512397  33db                     xor        ebx, ebx
00512399  3bcb                     cmp        ecx, ebx
0051239b  7406                     je         0x5123a3
0051239d  8b01                     mov        eax, dword ptr [ecx]
0051239f  53                       push       ebx
005123a0  ff5004                   call       dword ptr [eax + 4]
005123a3  57                       push       edi
005123a4  8dbea0000000             lea        edi, [esi + 0xa0]
005123aa  8bcf                     mov        ecx, edi
005123ac  e83f2befff               call       0x404ef0
005123b1  53                       push       ebx
005123b2  53                       push       ebx
005123b3  8bcf                     mov        ecx, edi
005123b5  e8a64b5f00               call       0xb06f60
005123ba  8b86fc000000             mov        eax, dword ptr [esi + 0xfc]
005123c0  83f8ff                   cmp        eax, -1
005123c3  899ee4000000             mov        dword ptr [esi + 0xe4], ebx
005123c9  5f                       pop        edi
005123ca  7505                     jne        0x5123d1
005123cc  a17cbef500               mov        eax, dword ptr [0xf5be7c]
005123d1  f7d8                     neg        eax
005123d3  8986e8000000             mov        dword ptr [esi + 0xe8], eax
005123d9  899eec000000             mov        dword ptr [esi + 0xec], ebx
005123df  899ef0000000             mov        dword ptr [esi + 0xf0], ebx
005123e5  899ef4000000             mov        dword ptr [esi + 0xf4], ebx
005123eb  889ef8000000             mov        byte ptr [esi + 0xf8], bl
005123f1  8bce                     mov        ecx, esi
005123f3  5e                       pop        esi
005123f4  5b                       pop        ebx
005123f5  e9d6d8ffff               jmp        0x50fcd0
005123fa  cc                       int3       
005123fb  cc                       int3       
005123fc  cc                       int3       
005123fd  cc                       int3       
005123fe  cc                       int3       
005123ff  cc                       int3       
