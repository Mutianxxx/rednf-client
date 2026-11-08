006a3c95  8b03                     mov        eax, dword ptr [ebx]
006a3c97  57                       push       edi
006a3c98  6a05                     push       5
006a3c9a  8bcb                     mov        ecx, ebx
006a3c9c  ff903c070000             call       dword ptr [eax + 0x73c]
006a3ca2  8bc8                     mov        ecx, eax
006a3ca4  e89754ebff               call       0x559140
006a3ca9  83f8ff                   cmp        eax, -1
006a3cac  7427                     je         0x6a3cd5
006a3cae  8b13                     mov        edx, dword ptr [ebx]
006a3cb0  6a01                     push       1
006a3cb2  6a01                     push       1
006a3cb4  6a01                     push       1
006a3cb6  6a05                     push       5
006a3cb8  8bcb                     mov        ecx, ebx
006a3cba  ff9268070000             call       dword ptr [edx + 0x768]
006a3cc0  84c0                     test       al, al
006a3cc2  7411                     je         0x6a3cd5
006a3cc4  8b03                     mov        eax, dword ptr [ebx]
006a3cc6  57                       push       edi
006a3cc7  57                       push       edi
006a3cc8  6a01                     push       1
006a3cca  57                       push       edi
006a3ccb  6a1e                     push       0x1e
006a3ccd  8bcb                     mov        ecx, ebx
006a3ccf  ff908c020000             call       dword ptr [eax + 0x28c]