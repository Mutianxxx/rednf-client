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