004e81d0  55                       push       ebp
004e81d1  8bec                     mov        ebp, esp
004e81d3  53                       push       ebx
004e81d4  56                       push       esi
004e81d5  57                       push       edi
004e81d6  8b7d08                   mov        edi, dword ptr [ebp + 8]
004e81d9  8b07                     mov        eax, dword ptr [edi]
004e81db  8bf1                     mov        esi, ecx
004e81dd  8bcf                     mov        ecx, edi
004e81df  ff900c020000             call       dword ptr [eax + 0x20c]
004e81e5  8b16                     mov        edx, dword ptr [esi]
004e81e7  8bce                     mov        ecx, esi
004e81e9  8bd8                     mov        ebx, eax
004e81eb  ff9210020000             call       dword ptr [edx + 0x210]
004e81f1  3bc3                     cmp        eax, ebx
004e81f3  7d09                     jge        0x4e81fe
004e81f5  5f                       pop        edi
004e81f6  5e                       pop        esi
004e81f7  32c0                     xor        al, al
004e81f9  5b                       pop        ebx
004e81fa  5d                       pop        ebp
004e81fb  c20400                   ret        4
004e81fe  8b07                     mov        eax, dword ptr [edi]
004e8200  8bcf                     mov        ecx, edi
004e8202  ff9010020000             call       dword ptr [eax + 0x210]
004e8208  8b16                     mov        edx, dword ptr [esi]
004e820a  8bce                     mov        ecx, esi
004e820c  8bd8                     mov        ebx, eax
004e820e  ff920c020000             call       dword ptr [edx + 0x20c]
004e8214  3bd8                     cmp        ebx, eax
004e8216  7cdd                     jl         0x4e81f5
004e8218  8b07                     mov        eax, dword ptr [edi]
004e821a  8bcf                     mov        ecx, edi
004e821c  ff9014020000             call       dword ptr [eax + 0x214]
004e8222  8b16                     mov        edx, dword ptr [esi]
004e8224  8bce                     mov        ecx, esi
004e8226  8bd8                     mov        ebx, eax
004e8228  ff9218020000             call       dword ptr [edx + 0x218]
004e822e  3bc3                     cmp        eax, ebx
004e8230  7cc3                     jl         0x4e81f5
004e8232  8b07                     mov        eax, dword ptr [edi]
004e8234  8bcf                     mov        ecx, edi
004e8236  ff9018020000             call       dword ptr [eax + 0x218]
004e823c  8b16                     mov        edx, dword ptr [esi]
004e823e  8bce                     mov        ecx, esi
004e8240  8bf8                     mov        edi, eax
004e8242  ff9214020000             call       dword ptr [edx + 0x214]
004e8248  3bf8                     cmp        edi, eax
004e824a  5f                       pop        edi
004e824b  5e                       pop        esi
004e824c  0f9dc0                   setge      al
004e824f  5b                       pop        ebx
004e8250  5d                       pop        ebp
004e8251  c20400                   ret        4
