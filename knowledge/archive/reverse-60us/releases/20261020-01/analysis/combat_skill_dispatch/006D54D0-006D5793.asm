006d54d0  52                       push       edx
006d54d1  48                       dec        eax
006d54d2  84c0                     test       al, al
006d54d4  7410                     je         0x6d54e6
006d54d6  8bce                     mov        ecx, esi
006d54d8  8b16                     mov        edx, dword ptr [esi]
006d54da  57                       push       edi
006d54db  57                       push       edi
006d54dc  57                       push       edi
006d54dd  57                       push       edi
006d54de  6a07                     push       7
006d54e0  ff928c020000             call       dword ptr [edx + 0x28c]
006d54e6  8d8e5c150000             lea        ecx, [esi + 0x155c]
006d54ec  e86fcbd2ff               call       0x402060
006d54f1  83f80c                   cmp        eax, 0xc
006d54f4  7541                     jne        0x6d5537
006d54f6  8b86242c0000             mov        eax, dword ptr [esi + 0x2c24]
006d54fc  83cbff                   or         ebx, 0xffffffff
006d54ff  3bc3                     cmp        eax, ebx
006d5501  7434                     je         0x6d5537
006d5503  8d8e64150000             lea        ecx, [esi + 0x1564]
006d5509  e8f2194300               call       0xb06f00
006d550e  3b86242c0000             cmp        eax, dword ptr [esi + 0x2c24]
006d5514  7e21                     jle        0x6d5537
006d5516  8b06                     mov        eax, dword ptr [esi]
006d5518  57                       push       edi
006d5519  6a03                     push       3
006d551b  8bce                     mov        ecx, esi
006d551d  ff907c060000             call       dword ptr [eax + 0x67c]
006d5523  8bc8                     mov        ecx, eax
006d5525  e8469de7ff               call       0x54f270
006d552a  c686581a000000           mov        byte ptr [esi + 0x1a58], 0
006d5531  899e242c0000             mov        dword ptr [esi + 0x2c24], ebx
006d5537  8d9e5c150000             lea        ebx, [esi + 0x155c]
006d553d  8bcb                     mov        ecx, ebx
006d553f  e81ccbd2ff               call       0x402060
006d5544  83f804                   cmp        eax, 4
006d5547  0f8598000000             jne        0x6d55e5
006d554d  8d8e20170000             lea        ecx, [esi + 0x1720]
006d5553  e808cbd2ff               call       0x402060
006d5558  83f802                   cmp        eax, 2
006d555b  0f8584000000             jne        0x6d55e5
006d5561  8b16                     mov        edx, dword ptr [esi]
006d5563  8bce                     mov        ecx, esi
006d5565  ff9290050000             call       dword ptr [edx + 0x590]
006d556b  84c0                     test       al, al
006d556d  7444                     je         0x6d55b3
006d556f  83be8c2c0000ff           cmp        dword ptr [esi + 0x2c8c], -1
006d5576  746d                     je         0x6d55e5
006d5578  8d8e64150000             lea        ecx, [esi + 0x1564]
006d557e  e87d194300               call       0xb06f00
006d5583  3b868c2c0000             cmp        eax, dword ptr [esi + 0x2c8c]
006d5589  7c5a                     jl         0x6d55e5
006d558b  8b06                     mov        eax, dword ptr [esi]
006d558d  6a01                     push       1
006d558f  6a03                     push       3
006d5591  8bce                     mov        ecx, esi
006d5593  ff907c060000             call       dword ptr [eax + 0x67c]
006d5599  8bc8                     mov        ecx, eax
006d559b  e8d09ce7ff               call       0x54f270
006d55a0  c686581a000001           mov        byte ptr [esi + 0x1a58], 1
006d55a7  c7868c2c0000ffffffff     mov        dword ptr [esi + 0x2c8c], 0xffffffff
006d55b1  eb32                     jmp        0x6d55e5
006d55b3  8b16                     mov        edx, dword ptr [esi]
006d55b5  6a03                     push       3
006d55b7  8bce                     mov        ecx, esi
006d55b9  ff927c060000             call       dword ptr [edx + 0x67c]
006d55bf  8bc8                     mov        ecx, eax
006d55c1  e80ae6e7ff               call       0x553bd0
006d55c6  84c0                     test       al, al
006d55c8  741b                     je         0x6d55e5
006d55ca  8b06                     mov        eax, dword ptr [esi]
006d55cc  57                       push       edi
006d55cd  6a03                     push       3
006d55cf  8bce                     mov        ecx, esi
006d55d1  ff907c060000             call       dword ptr [eax + 0x67c]
006d55d7  8bc8                     mov        ecx, eax
006d55d9  e8929ce7ff               call       0x54f270
006d55de  c686581a000000           mov        byte ptr [esi + 0x1a58], 0
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