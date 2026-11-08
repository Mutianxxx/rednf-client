006a36c0  37                       aaa        
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
006a373e  8bce                     mov        ecx, esi
006a3740  e81be9d5ff               call       0x402060
006a3745  83f82f                   cmp        eax, 0x2f
006a3748  751f                     jne        0x6a3769
006a374a  8b8304010000             mov        eax, dword ptr [ebx + 0x104]
006a3750  8a883a010000             mov        cl, byte ptr [eax + 0x13a]
006a3756  84c9                     test       cl, cl
006a3758  740f                     je         0x6a3769
006a375a  8b13                     mov        edx, dword ptr [ebx]
006a375c  57                       push       edi
006a375d  57                       push       edi
006a375e  57                       push       edi
006a375f  57                       push       edi
006a3760  57                       push       edi
006a3761  8bcb                     mov        ecx, ebx
006a3763  ff928c020000             call       dword ptr [edx + 0x28c]
006a3769  8bce                     mov        ecx, esi
006a376b  e8f0e8d5ff               call       0x402060
006a3770  85c0                     test       eax, eax
006a3772  740c                     je         0x6a3780
006a3774  8bce                     mov        ecx, esi
006a3776  e8e5e8d5ff               call       0x402060
006a377b  83f80b                   cmp        eax, 0xb
006a377e  7540                     jne        0x6a37c0
006a3780  8b03                     mov        eax, dword ptr [ebx]
006a3782  57                       push       edi
006a3783  6a02                     push       2
006a3785  8bcb                     mov        ecx, ebx
006a3787  ff903c070000             call       dword ptr [eax + 0x73c]
006a378d  8bc8                     mov        ecx, eax
006a378f  e8                       .byte      0xe8