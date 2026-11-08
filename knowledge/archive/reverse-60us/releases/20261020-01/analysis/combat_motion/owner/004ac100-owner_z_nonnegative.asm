004ac100  55                       push       ebp
004ac101  8bec                     mov        ebp, esp
004ac103  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004ac106  33c0                     xor        eax, eax
004ac108  85c9                     test       ecx, ecx
004ac10a  0f9dc0                   setge      al
004ac10d  5d                       pop        ebp
004ac10e  c20400                   ret        4
