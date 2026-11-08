004ccdb0  55                       push       ebp
004ccdb1  8bec                     mov        ebp, esp
004ccdb3  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004ccdb6  85c9                     test       ecx, ecx
004ccdb8  0f84d5000000             je         0x4cce93
004ccdbe  53                       push       ebx
004ccdbf  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004ccdc2  85db                     test       ebx, ebx
004ccdc4  0f84c8000000             je         0x4cce92
004ccdca  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
004ccdd0  85c0                     test       eax, eax
004ccdd2  56                       push       esi
004ccdd3  57                       push       edi
004ccdd4  7504                     jne        0x4ccdda
004ccdd6  33ff                     xor        edi, edi
004ccdd8  eb1b                     jmp        0x4ccdf5
004ccdda  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
004ccde0  2bf0                     sub        esi, eax
004ccde2  b843082184               mov        eax, 0x84210843
004ccde7  f7ee                     imul       esi
004ccde9  03d6                     add        edx, esi
004ccdeb  c1fa06                   sar        edx, 6
004ccdee  8bfa                     mov        edi, edx
004ccdf0  c1ef1f                   shr        edi, 0x1f
004ccdf3  03fa                     add        edi, edx
004ccdf5  8b8398000000             mov        eax, dword ptr [ebx + 0x98]
004ccdfb  85c0                     test       eax, eax
004ccdfd  741b                     je         0x4cce1a
004ccdff  8bb39c000000             mov        esi, dword ptr [ebx + 0x9c]
004cce05  2bf0                     sub        esi, eax
004cce07  b843082184               mov        eax, 0x84210843
004cce0c  f7ee                     imul       esi
004cce0e  03d6                     add        edx, esi
004cce10  c1fa06                   sar        edx, 6
004cce13  8bc2                     mov        eax, edx
004cce15  c1e81f                   shr        eax, 0x1f
004cce18  03c2                     add        eax, edx
004cce1a  3bf8                     cmp        edi, eax
004cce1c  7d16                     jge        0x4cce34
004cce1e  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
004cce24  85c0                     test       eax, eax
004cce26  7504                     jne        0x4cce2c
004cce28  33ff                     xor        edi, edi
004cce2a  eb31                     jmp        0x4cce5d
004cce2c  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
004cce32  eb14                     jmp        0x4cce48
004cce34  8b8398000000             mov        eax, dword ptr [ebx + 0x98]
004cce3a  85c0                     test       eax, eax
004cce3c  7504                     jne        0x4cce42
004cce3e  33ff                     xor        edi, edi
004cce40  eb1b                     jmp        0x4cce5d
004cce42  8bb39c000000             mov        esi, dword ptr [ebx + 0x9c]
004cce48  2bf0                     sub        esi, eax
004cce4a  b843082184               mov        eax, 0x84210843
004cce4f  f7ee                     imul       esi
004cce51  03d6                     add        edx, esi
004cce53  c1fa06                   sar        edx, 6
004cce56  8bfa                     mov        edi, edx
004cce58  c1ef1f                   shr        edi, 0x1f
004cce5b  03fa                     add        edi, edx
004cce5d  33db                     xor        ebx, ebx
004cce5f  85ff                     test       edi, edi
004cce61  7e2d                     jle        0x4cce90
004cce63  eb03                     jmp        0x4cce68
004cce65  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004cce68  53                       push       ebx
004cce69  e8228e5500               call       0xa25c90
004cce6e  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004cce71  8bf0                     mov        esi, eax
004cce73  53                       push       ebx
004cce74  83c630                   add        esi, 0x30
004cce77  e8148e5500               call       0xa25c90
004cce7c  83c030                   add        eax, 0x30
004cce7f  3bc6                     cmp        eax, esi
004cce81  7408                     je         0x4cce8b
004cce83  8b0e                     mov        ecx, dword ptr [esi]
004cce85  2bce                     sub        ecx, esi
004cce87  03c8                     add        ecx, eax
004cce89  8908                     mov        dword ptr [eax], ecx
004cce8b  43                       inc        ebx
004cce8c  3bdf                     cmp        ebx, edi
004cce8e  7cd5                     jl         0x4cce65
004cce90  5f                       pop        edi
004cce91  5e                       pop        esi
004cce92  5b                       pop        ebx
004cce93  5d                       pop        ebp
004cce94  c3                       ret        
