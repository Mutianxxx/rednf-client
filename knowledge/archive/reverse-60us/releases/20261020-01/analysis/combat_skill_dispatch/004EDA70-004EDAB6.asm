004eda70  55                       push       ebp
004eda71  8bec                     mov        ebp, esp
004eda73  51                       push       ecx
004eda74  53                       push       ebx
004eda75  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004eda78  8b4304                   mov        eax, dword ptr [ebx + 4]
004eda7b  85c0                     test       eax, eax
004eda7d  56                       push       esi
004eda7e  57                       push       edi
004eda7f  894dfc                   mov        dword ptr [ebp - 4], ecx
004eda82  7504                     jne        0x4eda88
004eda84  33ff                     xor        edi, edi
004eda86  eb08                     jmp        0x4eda90
004eda88  8b7b08                   mov        edi, dword ptr [ebx + 8]
004eda8b  2bf8                     sub        edi, eax
004eda8d  c1ff02                   sar        edi, 2
004eda90  33f6                     xor        esi, esi
004eda92  85ff                     test       edi, edi
004eda94  7e17                     jle        0x4edaad
004eda96  8b4304                   mov        eax, dword ptr [ebx + 4]
004eda99  8b0cb0                   mov        ecx, dword ptr [eax + esi*4]
004eda9c  8d04b0                   lea        eax, [eax + esi*4]
004eda9f  51                       push       ecx
004edaa0  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004edaa3  e838f8ffff               call       0x4ed2e0
004edaa8  46                       inc        esi
004edaa9  3bf7                     cmp        esi, edi
004edaab  7ce9                     jl         0x4eda96
004edaad  5f                       pop        edi
004edaae  5e                       pop        esi
004edaaf  5b                       pop        ebx
004edab0  8be5                     mov        esp, ebp
004edab2  5d                       pop        ebp
004edab3  c20400                   ret        4