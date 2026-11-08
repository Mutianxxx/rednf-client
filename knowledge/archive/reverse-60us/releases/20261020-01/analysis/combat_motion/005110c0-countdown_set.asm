005110c0  55                       push       ebp
005110c1  8bec                     mov        ebp, esp
005110c3  56                       push       esi
005110c4  8bf1                     mov        esi, ecx
005110c6  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
005110c9  85c9                     test       ecx, ecx
005110cb  7438                     je         0x511105
005110cd  e8beaff8ff               call       0x49c090
005110d2  84c0                     test       al, al
005110d4  742f                     je         0x511105
005110d6  8b06                     mov        eax, dword ptr [esi]
005110d8  85c0                     test       eax, eax
005110da  8bc8                     mov        ecx, eax
005110dc  7503                     jne        0x5110e1
005110de  8d4e08                   lea        ecx, [esi + 8]
005110e1  8b5508                   mov        edx, dword ptr [ebp + 8]
005110e4  53                       push       ebx
005110e5  8b5c9128                 mov        ebx, dword ptr [ecx + edx*4 + 0x28]
005110e9  57                       push       edi
005110ea  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
005110ed  3bdf                     cmp        ebx, edi
005110ef  7412                     je         0x511103
005110f1  85c0                     test       eax, eax
005110f3  7503                     jne        0x5110f8
005110f5  8d4608                   lea        eax, [esi + 8]
005110f8  897c9028                 mov        dword ptr [eax + edx*4 + 0x28], edi
005110fc  c686f800000001           mov        byte ptr [esi + 0xf8], 1
00511103  5f                       pop        edi
00511104  5b                       pop        ebx
00511105  5e                       pop        esi
00511106  5d                       pop        ebp
00511107  c20800                   ret        8
