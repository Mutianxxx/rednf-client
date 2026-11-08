006d56e5  8bcb                     mov        ecx, ebx
006d56e7  e874c9d2ff               call       0x402060
006d56ec  85c0                     test       eax, eax
006d56ee  741c                     je         0x6d570c
006d56f0  8bcb                     mov        ecx, ebx
006d56f2  e869c9d2ff               call       0x402060
006d56f7  83f80b                   cmp        eax, 0xb
006d56fa  7410                     je         0x6d570c
006d56fc  8bcb                     mov        ecx, ebx
006d56fe  e85dc9d2ff               call       0x402060
006d5703  83f808                   cmp        eax, 8
006d5706  0f8587000000             jne        0x6d5793
006d570c  8b16                     mov        edx, dword ptr [esi]
006d570e  57                       push       edi
006d570f  6a04                     push       4
006d5711  8bce                     mov        ecx, esi
006d5713  ff923c070000             call       dword ptr [edx + 0x73c]
006d5719  8bc8                     mov        ecx, eax
006d571b  e8203ae8ff               call       0x559140
006d5720  83f8ff                   cmp        eax, -1
006d5723  746e                     je         0x6d5793
006d5725  8b06                     mov        eax, dword ptr [esi]
006d5727  6a01                     push       1
006d5729  6a01                     push       1
006d572b  6a01                     push       1
006d572d  6a04                     push       4
006d572f  8bce                     mov        ecx, esi
006d5731  ff9068070000             call       dword ptr [eax + 0x768]
006d5737  84c0                     test       al, al
006d5739  7458                     je         0x6d5793
006d573b  89bd30fcffff             mov        dword ptr [ebp - 0x3d0], edi
006d5741  89bd34fcffff             mov        dword ptr [ebp - 0x3cc], edi
006d5747  89bd38fcffff             mov        dword ptr [ebp - 0x3c8], edi
006d574d  8d4df0                   lea        ecx, [ebp - 0x10]
006d5750  51                       push       ecx
006d5751  8d8d2cfcffff             lea        ecx, [ebp - 0x3d4]
006d5757  c745fc38000000           mov        dword ptr [ebp - 4], 0x38
006d575e  c745f004000000           mov        dword ptr [ebp - 0x10], 4
006d5765  e8b619d3ff               call       0x407120
006d576a  8b16                     mov        edx, dword ptr [esi]
006d576c  57                       push       edi
006d576d  57                       push       edi
006d576e  6a01                     push       1
006d5770  8d852cfcffff             lea        eax, [ebp - 0x3d4]
006d5776  50                       push       eax
006d5777  6a14                     push       0x14
006d5779  8bce                     mov        ecx, esi
006d577b  ff928c020000             call       dword ptr [edx + 0x28c]
006d5781  8d8d2cfcffff             lea        ecx, [ebp - 0x3d4]
006d5787  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
006d578e  e8bdf5f6ff               call       0x644d50