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