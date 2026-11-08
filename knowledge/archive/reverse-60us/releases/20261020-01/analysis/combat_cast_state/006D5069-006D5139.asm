006d5069  8d9e5c150000             lea        ebx, [esi + 0x155c]
006d506f  8bcb                     mov        ecx, ebx
006d5071  e8eacfd2ff               call       0x402060
006d5076  83f814                   cmp        eax, 0x14
006d5079  750a                     jne        0x6d5085
006d507b  8a86b02c0000             mov        al, byte ptr [esi + 0x2cb0]
006d5081  84c0                     test       al, al
006d5083  7520                     jne        0x6d50a5
006d5085  8bcb                     mov        ecx, ebx
006d5087  e8d4cfd2ff               call       0x402060
006d508c  83f81a                   cmp        eax, 0x1a
006d508f  0f8586000000             jne        0x6d511b
006d5095  8d8e802b0000             lea        ecx, [esi + 0x2b80]
006d509b  e8c0cfd2ff               call       0x402060
006d50a0  83f80e                   cmp        eax, 0xe
006d50a3  7576                     jne        0x6d511b
006d50a5  8b8e002f0000             mov        ecx, dword ptr [esi + 0x2f00]
006d50ab  33ff                     xor        edi, edi
006d50ad  3bcf                     cmp        ecx, edi
006d50af  7452                     je         0x6d5103
006d50b1  e8da6fdcff               call       0x49c090
006d50b6  84c0                     test       al, al
006d50b8  7449                     je         0x6d5103
006d50ba  8b8e002f0000             mov        ecx, dword ptr [esi + 0x2f00]
006d50c0  8b11                     mov        edx, dword ptr [ecx]
006d50c2  ff9230020000             call       dword ptr [edx + 0x230]
006d50c8  83f809                   cmp        eax, 9
006d50cb  7436                     je         0x6d5103
006d50cd  8b8e002f0000             mov        ecx, dword ptr [esi + 0x2f00]
006d50d3  8b01                     mov        eax, dword ptr [ecx]
006d50d5  ff9030020000             call       dword ptr [eax + 0x230]
006d50db  83f805                   cmp        eax, 5
006d50de  7423                     je         0x6d5103
006d50e0  8b8e002f0000             mov        ecx, dword ptr [esi + 0x2f00]
006d50e6  8b11                     mov        edx, dword ptr [ecx]
006d50e8  57                       push       edi
006d50e9  57                       push       edi
006d50ea  6a03                     push       3
006d50ec  57                       push       edi
006d50ed  6a09                     push       9
006d50ef  ff928c020000             call       dword ptr [edx + 0x28c]
006d50f5  8b8e002f0000             mov        ecx, dword ptr [esi + 0x2f00]
006d50fb  8b01                     mov        eax, dword ptr [ecx]
006d50fd  ff9090020000             call       dword ptr [eax + 0x290]
006d5103  8b16                     mov        edx, dword ptr [esi]
006d5105  57                       push       edi
006d5106  8bce                     mov        ecx, esi
006d5108  ff92d0020000             call       dword ptr [edx + 0x2d0]
006d510e  8b06                     mov        eax, dword ptr [esi]
006d5110  57                       push       edi
006d5111  8bce                     mov        ecx, esi
006d5113  ff90d8020000             call       dword ptr [eax + 0x2d8]
006d5119  eb02                     jmp        0x6d511d
006d511b  33ff                     xor        edi, edi
006d511d  8bce                     mov        ecx, esi
006d511f  e86c6fdcff               call       0x49c090
006d5124  84c0                     test       al, al
006d5126  0f844b5b0000             je         0x6dac77
006d512c  83beb001000002           cmp        dword ptr [esi + 0x1b0], 2
006d5133  0f843e5b0000             je         0x6dac77