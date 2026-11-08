006a367c  8bcb                     mov        ecx, ebx
006a367e  e80d8adfff               call       0x49c090
006a3683  84c0                     test       al, al
006a3685  0f844a3b0000             je         0x6a71d5
006a368b  83bbb001000002           cmp        dword ptr [ebx + 0x1b0], 2
006a3692  0f843d3b0000             je         0x6a71d5
006a3698  8db35c150000             lea        esi, [ebx + 0x155c]
006a369e  8bce                     mov        ecx, esi
006a36a0  e8bbe9d5ff               call       0x402060
006a36a5  85c0                     test       eax, eax
006a36a7  744f                     je         0x6a36f8
006a36a9  8bce                     mov        ecx, esi
006a36ab  e8b0e9d5ff               call       0x402060
006a36b0  83f80b                   cmp        eax, 0xb
006a36b3  7443                     je         0x6a36f8
006a36b5  8bce                     mov        ecx, esi
006a36b7  e8a4e9d5ff               call       0x402060
006a36bc  83f813                   cmp        eax, 0x13
006a36bf  7437                     je         0x6a36f8
006a36c1  8bce                     mov        ecx, esi
006a36c3  e898e9d5ff               call       0x402060
006a36c8  83f808                   cmp        eax, 8
006a36cb  742b                     je         0x6a36f8
006a36cd  8bce                     mov        ecx, esi
006a36cf  e88ce9d5ff               call       0x402060
006a36d4  83f80c                   cmp        eax, 0xc
006a36d7  741f                     je         0x6a36f8
006a36d9  8bce                     mov        ecx, esi
006a36db  e880e9d5ff               call       0x402060
006a36e0  83f837                   cmp        eax, 0x37
006a36e3  7413                     je         0x6a36f8
006a36e5  8bce                     mov        ecx, esi
006a36e7  e874e9d5ff               call       0x402060
006a36ec  50                       push       eax
006a36ed  8bcb                     mov        ecx, ebx
006a36ef  e8dc250100               call       0x6b5cd0
006a36f4  84c0                     test       al, al
006a36f6  7444                     je         0x6a373c
006a36f8  8b13                     mov        edx, dword ptr [ebx]
006a36fa  33ff                     xor        edi, edi
006a36fc  57                       push       edi
006a36fd  6a01                     push       1
006a36ff  8bcb                     mov        ecx, ebx
006a3701  ff923c070000             call       dword ptr [edx + 0x73c]
006a3707  8bc8                     mov        ecx, eax
006a3709  e8325aebff               call       0x559140
006a370e  83f8ff                   cmp        eax, -1
006a3711  742b                     je         0x6a373e
006a3713  8b03                     mov        eax, dword ptr [ebx]
006a3715  6a01                     push       1
006a3717  6a01                     push       1
006a3719  6a01                     push       1
006a371b  6a01                     push       1
006a371d  8bcb                     mov        ecx, ebx
006a371f  ff9068070000             call       dword ptr [eax + 0x768]
006a3725  84c0                     test       al, al
006a3727  7415                     je         0x6a373e
006a3729  8b13                     mov        edx, dword ptr [ebx]
006a372b  57                       push       edi
006a372c  57                       push       edi
006a372d  6a01                     push       1
006a372f  57                       push       edi
006a3730  6a2f                     push       0x2f
006a3732  8bcb                     mov        ecx, ebx
006a3734  ff928c020000             call       dword ptr [edx + 0x28c]
006a373a  eb02                     jmp        0x6a373e
006a373c  33ff                     xor        edi, edi