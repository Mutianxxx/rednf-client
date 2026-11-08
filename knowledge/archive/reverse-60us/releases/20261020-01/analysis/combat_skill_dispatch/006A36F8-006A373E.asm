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