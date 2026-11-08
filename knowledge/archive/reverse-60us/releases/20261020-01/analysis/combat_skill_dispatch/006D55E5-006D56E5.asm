006d55e5  8bcb                     mov        ecx, ebx
006d55e7  e874cad2ff               call       0x402060
006d55ec  85c0                     test       eax, eax
006d55ee  7434                     je         0x6d5624
006d55f0  8bcb                     mov        ecx, ebx
006d55f2  e869cad2ff               call       0x402060
006d55f7  83f80b                   cmp        eax, 0xb
006d55fa  7428                     je         0x6d5624
006d55fc  8bcb                     mov        ecx, ebx
006d55fe  e85dcad2ff               call       0x402060
006d5603  83f80c                   cmp        eax, 0xc
006d5606  741c                     je         0x6d5624
006d5608  8bcb                     mov        ecx, ebx
006d560a  e851cad2ff               call       0x402060
006d560f  83f804                   cmp        eax, 4
006d5612  7410                     je         0x6d5624
006d5614  8bcb                     mov        ecx, ebx
006d5616  e845cad2ff               call       0x402060
006d561b  83f808                   cmp        eax, 8
006d561e  0f85c1000000             jne        0x6d56e5
006d5624  8b16                     mov        edx, dword ptr [esi]
006d5626  57                       push       edi
006d5627  6a03                     push       3
006d5629  8bce                     mov        ecx, esi
006d562b  ff923c070000             call       dword ptr [edx + 0x73c]
006d5631  8bc8                     mov        ecx, eax
006d5633  e8083be8ff               call       0x559140
006d5638  83f8ff                   cmp        eax, -1
006d563b  753a                     jne        0x6d5677
006d563d  8bcb                     mov        ecx, ebx
006d563f  e81ccad2ff               call       0x402060
006d5644  83f80c                   cmp        eax, 0xc
006d5647  7410                     je         0x6d5659
006d5649  8bcb                     mov        ecx, ebx
006d564b  e810cad2ff               call       0x402060
006d5650  83f804                   cmp        eax, 4
006d5653  0f858c000000             jne        0x6d56e5
006d5659  8b06                     mov        eax, dword ptr [esi]
006d565b  8bce                     mov        ecx, esi
006d565d  ff9038070000             call       dword ptr [eax + 0x738]
006d5663  8b10                     mov        edx, dword ptr [eax]
006d5665  6a01                     push       1
006d5667  8d8e301a0000             lea        ecx, [esi + 0x1a30]
006d566d  51                       push       ecx
006d566e  8bc8                     mov        ecx, eax
006d5670  ff5248                   call       dword ptr [edx + 0x48]
006d5673  84c0                     test       al, al
006d5675  746e                     je         0x6d56e5
006d5677  8b16                     mov        edx, dword ptr [esi]
006d5679  6a01                     push       1
006d567b  6a01                     push       1
006d567d  6a01                     push       1
006d567f  6a03                     push       3
006d5681  8bce                     mov        ecx, esi
006d5683  ff9268070000             call       dword ptr [edx + 0x768]
006d5689  84c0                     test       al, al
006d568b  7458                     je         0x6d56e5
006d568d  89bdd0fbffff             mov        dword ptr [ebp - 0x430], edi
006d5693  89bdd4fbffff             mov        dword ptr [ebp - 0x42c], edi
006d5699  89bdd8fbffff             mov        dword ptr [ebp - 0x428], edi
006d569f  8d45f0                   lea        eax, [ebp - 0x10]
006d56a2  50                       push       eax
006d56a3  8d8dccfbffff             lea        ecx, [ebp - 0x434]
006d56a9  c745fc37000000           mov        dword ptr [ebp - 4], 0x37
006d56b0  c745f003000000           mov        dword ptr [ebp - 0x10], 3
006d56b7  e8641ad3ff               call       0x407120
006d56bc  8b16                     mov        edx, dword ptr [esi]
006d56be  57                       push       edi
006d56bf  57                       push       edi
006d56c0  6a01                     push       1
006d56c2  8d85ccfbffff             lea        eax, [ebp - 0x434]
006d56c8  50                       push       eax
006d56c9  6a13                     push       0x13
006d56cb  8bce                     mov        ecx, esi
006d56cd  ff928c020000             call       dword ptr [edx + 0x28c]
006d56d3  8d8dccfbffff             lea        ecx, [ebp - 0x434]
006d56d9  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
006d56e0  e86bf6f6ff               call       0x644d50