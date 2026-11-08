006f0c00  06                       push       es
006f0c01  53                       push       ebx
006f0c02  53                       push       ebx
006f0c03  53                       push       ebx
006f0c04  53                       push       ebx
006f0c05  53                       push       ebx
006f0c06  8bce                     mov        ecx, esi
006f0c08  ff908c020000             call       dword ptr [eax + 0x28c]
006f0c0e  8d8e5c150000             lea        ecx, [esi + 0x155c]
006f0c14  e84714d1ff               call       0x402060
006f0c19  85c0                     test       eax, eax
006f0c1b  7424                     je         0x6f0c41
006f0c1d  8d8e5c150000             lea        ecx, [esi + 0x155c]
006f0c23  e83814d1ff               call       0x402060
006f0c28  83f80b                   cmp        eax, 0xb
006f0c2b  7414                     je         0x6f0c41
006f0c2d  8d8e5c150000             lea        ecx, [esi + 0x155c]
006f0c33  e82814d1ff               call       0x402060
006f0c38  83f808                   cmp        eax, 8
006f0c3b  0f8582000000             jne        0x6f0cc3
006f0c41  8b16                     mov        edx, dword ptr [esi]
006f0c43  53                       push       ebx
006f0c44  6a04                     push       4
006f0c46  8bce                     mov        ecx, esi
006f0c48  ff923c070000             call       dword ptr [edx + 0x73c]
006f0c4e  8bc8                     mov        ecx, eax
006f0c50  e8eb84e6ff               call       0x559140
006f0c55  3bc7                     cmp        eax, edi
006f0c57  746a                     je         0x6f0cc3
006f0c59  8b06                     mov        eax, dword ptr [esi]
006f0c5b  6a01                     push       1
006f0c5d  6a01                     push       1
006f0c5f  6a01                     push       1
006f0c61  6a04                     push       4
006f0c63  8bce                     mov        ecx, esi
006f0c65  ff9068070000             call       dword ptr [eax + 0x768]
006f0c6b  84c0                     test       al, al
006f0c6d  7454                     je         0x6f0cc3
006f0c6f  899d28fcffff             mov        dword ptr [ebp - 0x3d8], ebx
006f0c75  899d2cfcffff             mov        dword ptr [ebp - 0x3d4], ebx
006f0c7b  899d30fcffff             mov        dword ptr [ebp - 0x3d0], ebx
006f0c81  8d4df0                   lea        ecx, [ebp - 0x10]
006f0c84  51                       push       ecx
006f0c85  8d8d24fcffff             lea        ecx, [ebp - 0x3dc]
006f0c8b  c745fc3b000000           mov        dword ptr [ebp - 4], 0x3b
006f0c92  c745f004000000           mov        dword ptr [ebp - 0x10], 4
006f0c99  e88264d1ff               call       0x407120
006f0c9e  8b16                     mov        edx, dword ptr [esi]
006f0ca0  53                       push       ebx
006f0ca1  53                       push       ebx
006f0ca2  6a01                     push       1
006f0ca4  8d8524fcffff             lea        eax, [ebp - 0x3dc]
006f0caa  50                       push       eax
006f0cab  6a16                     push       0x16
006f0cad  8bce                     mov        ecx, esi
006f0caf  ff928c020000             call       dword ptr [edx + 0x28c]
006f0cb5  8d8d24fcffff             lea        ecx, [ebp - 0x3dc]
006f0cbb  897dfc                   mov        dword ptr [ebp - 4], edi
006f0cbe  e88d40f5ff               call       0x644d50