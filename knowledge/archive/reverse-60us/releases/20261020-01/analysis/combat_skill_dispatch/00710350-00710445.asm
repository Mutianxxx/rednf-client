00710350  006a10                   add        byte ptr [edx + 0x10], ch
00710353  68e6c89bff               push       0xff9bc8e6
00710358  680f0e0000               push       0xe0f
0071035d  e8de0e3400               call       0xa51240
00710362  83c404                   add        esp, 4
00710365  50                       push       eax
00710366  8bcf                     mov        ecx, edi
00710368  e8a3c32a00               call       0x9bc710
0071036d  8dbe5c150000             lea        edi, [esi + 0x155c]
00710373  8bcf                     mov        ecx, edi
00710375  e8e61ccfff               call       0x402060
0071037a  85c0                     test       eax, eax
0071037c  7418                     je         0x710396
0071037e  8bcf                     mov        ecx, edi
00710380  e8db1ccfff               call       0x402060
00710385  83f80b                   cmp        eax, 0xb
00710388  740c                     je         0x710396
0071038a  8bcf                     mov        ecx, edi
0071038c  e8cf1ccfff               call       0x402060
00710391  83f808                   cmp        eax, 8
00710394  754a                     jne        0x7103e0
00710396  8b06                     mov        eax, dword ptr [esi]
00710398  8d96e4250000             lea        edx, [esi + 0x25e4]
0071039e  52                       push       edx
0071039f  6a01                     push       1
007103a1  8bce                     mov        ecx, esi
007103a3  ff903c070000             call       dword ptr [eax + 0x73c]
007103a9  8bc8                     mov        ecx, eax
007103ab  e8908de4ff               call       0x559140
007103b0  83f8ff                   cmp        eax, -1
007103b3  742b                     je         0x7103e0
007103b5  8b16                     mov        edx, dword ptr [esi]
007103b7  6a01                     push       1
007103b9  6a01                     push       1
007103bb  6a01                     push       1
007103bd  6a01                     push       1
007103bf  8bce                     mov        ecx, esi
007103c1  ff9268070000             call       dword ptr [edx + 0x768]
007103c7  84c0                     test       al, al
007103c9  7415                     je         0x7103e0
007103cb  8b06                     mov        eax, dword ptr [esi]
007103cd  33db                     xor        ebx, ebx
007103cf  53                       push       ebx
007103d0  53                       push       ebx
007103d1  6a01                     push       1
007103d3  53                       push       ebx
007103d4  6a14                     push       0x14
007103d6  8bce                     mov        ecx, esi
007103d8  ff908c020000             call       dword ptr [eax + 0x28c]
007103de  eb02                     jmp        0x7103e2
007103e0  33db                     xor        ebx, ebx
007103e2  8bcf                     mov        ecx, edi
007103e4  e8771ccfff               call       0x402060
007103e9  85c0                     test       eax, eax
007103eb  7418                     je         0x710405
007103ed  8bcf                     mov        ecx, edi
007103ef  e86c1ccfff               call       0x402060
007103f4  83f80b                   cmp        eax, 0xb
007103f7  740c                     je         0x710405
007103f9  8bcf                     mov        ecx, edi
007103fb  e8601ccfff               call       0x402060
00710400  83f808                   cmp        eax, 8
00710403  7540                     jne        0x710445
00710405  8b16                     mov        edx, dword ptr [esi]
00710407  53                       push       ebx
00710408  6a0b                     push       0xb
0071040a  8bce                     mov        ecx, esi
0071040c  ff923c070000             call       dword ptr [edx + 0x73c]
00710412  8bc8                     mov        ecx, eax
00710414  e8278de4ff               call       0x559140
00710419  83f8ff                   cmp        eax, -1
0071041c  7427                     je         0x710445
0071041e  8b06                     mov        eax, dword ptr [esi]
00710420  6a01                     push       1
00710422  6a01                     push       1
00710424  6a01                     push       1
00710426  6a0b                     push       0xb
00710428  8bce                     mov        ecx, esi
0071042a  ff9068070000             call       dword ptr [eax + 0x768]
00710430  84c0                     test       al, al
00710432  7411                     je         0x710445
00710434  8b16                     mov        edx, dword ptr [esi]
00710436  53                       push       ebx
00710437  53                       push       ebx
00710438  6a01                     push       1
0071043a  53                       push       ebx
0071043b  6a1a                     push       0x1a
0071043d  8bce                     mov        ecx, esi
0071043f  ff928c020000             call       dword ptr [edx + 0x28c]