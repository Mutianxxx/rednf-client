; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 008b2950..008b29ec (end exclusive); file offset 004b2950
; This is an instruction excerpt, not a recovered original source file.
008b2950  55                       push       ebp
008b2951  8bec                     mov        ebp, esp
008b2953  8b4104                   mov        eax, dword ptr [ecx + 4]
008b2956  85c0                     test       eax, eax
008b2958  7509                     jne        0x8b2963
008b295a  83c118                   add        ecx, 0x18
008b295d  5d                       pop        ebp
008b295e  e9ed902d00               jmp        0xb8ba50
008b2963  b001                     mov        al, 1
008b2965  5d                       pop        ebp
008b2966  c21000                   ret        0x10
008b2969  cc                       int3       
008b296a  cc                       int3       
008b296b  cc                       int3       
008b296c  cc                       int3       
008b296d  cc                       int3       
008b296e  cc                       int3       
008b296f  cc                       int3       
008b2970  56                       push       esi
008b2971  8bf1                     mov        esi, ecx
008b2973  8b4604                   mov        eax, dword ptr [esi + 4]
008b2976  85c0                     test       eax, eax
008b2978  750d                     jne        0x8b2987
008b297a  8d4e18                   lea        ecx, [esi + 0x18]
008b297d  e81e8e2d00               call       0xb8b7a0
008b2982  894608                   mov        dword ptr [esi + 8], eax
008b2985  5e                       pop        esi
008b2986  c3                       ret        
008b2987  83f801                   cmp        eax, 1
008b298a  755b                     jne        0x8b29e7
008b298c  57                       push       edi
008b298d  8dbe74280000             lea        edi, [esi + 0x2874]
008b2993  8bcf                     mov        ecx, edi
008b2995  e806090000               call       0x8b32a0
008b299a  85c0                     test       eax, eax
008b299c  894608                   mov        dword ptr [esi + 8], eax
008b299f  7445                     je         0x8b29e6
008b29a1  83f801                   cmp        eax, 1
008b29a4  7440                     je         0x8b29e6
008b29a6  83f802                   cmp        eax, 2
008b29a9  742f                     je         0x8b29da
008b29ab  83f803                   cmp        eax, 3
008b29ae  742a                     je         0x8b29da
008b29b0  83f809                   cmp        eax, 9
008b29b3  7425                     je         0x8b29da
008b29b5  83f804                   cmp        eax, 4
008b29b8  8bcf                     mov        ecx, edi
008b29ba  6a00                     push       0
008b29bc  750e                     jne        0x8b29cc
008b29be  e85d090000               call       0x8b3320
008b29c3  d95e10                   fstp       dword ptr [esi + 0x10]
008b29c6  8b4608                   mov        eax, dword ptr [esi + 8]
008b29c9  5f                       pop        edi
008b29ca  5e                       pop        esi
008b29cb  c3                       ret        
008b29cc  e81f0a0000               call       0x8b33f0
008b29d1  894614                   mov        dword ptr [esi + 0x14], eax
008b29d4  8b4608                   mov        eax, dword ptr [esi + 8]
008b29d7  5f                       pop        edi
008b29d8  5e                       pop        esi
008b29d9  c3                       ret        
008b29da  6a00                     push       0
008b29dc  8bcf                     mov        ecx, edi
008b29de  e8fd080000               call       0x8b32e0
008b29e3  89460c                   mov        dword ptr [esi + 0xc], eax
008b29e6  5f                       pop        edi
008b29e7  8b4608                   mov        eax, dword ptr [esi + 8]
008b29ea  5e                       pop        esi
008b29eb  c3                       ret        
