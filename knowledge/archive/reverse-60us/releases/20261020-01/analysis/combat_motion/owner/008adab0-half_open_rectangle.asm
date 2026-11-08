008adab0  55                       push       ebp
008adab1  8bec                     mov        ebp, esp
008adab3  8b4510                   mov        eax, dword ptr [ebp + 0x10]
008adab6  8b08                     mov        ecx, dword ptr [eax]
008adab8  8b5508                   mov        edx, dword ptr [ebp + 8]
008adabb  3bd1                     cmp        edx, ecx
008adabd  7d04                     jge        0x8adac3
008adabf  32c0                     xor        al, al
008adac1  5d                       pop        ebp
008adac2  c3                       ret        
008adac3  56                       push       esi
008adac4  8b7008                   mov        esi, dword ptr [eax + 8]
008adac7  03f1                     add        esi, ecx
008adac9  3bd6                     cmp        edx, esi
008adacb  5e                       pop        esi
008adacc  7df1                     jge        0x8adabf
008adace  8b4804                   mov        ecx, dword ptr [eax + 4]
008adad1  8b550c                   mov        edx, dword ptr [ebp + 0xc]
008adad4  3bd1                     cmp        edx, ecx
008adad6  7ce7                     jl         0x8adabf
008adad8  8b400c                   mov        eax, dword ptr [eax + 0xc]
008adadb  03c1                     add        eax, ecx
008adadd  3bd0                     cmp        edx, eax
008adadf  0f9cc0                   setl       al
008adae2  5d                       pop        ebp
008adae3  c3                       ret        
