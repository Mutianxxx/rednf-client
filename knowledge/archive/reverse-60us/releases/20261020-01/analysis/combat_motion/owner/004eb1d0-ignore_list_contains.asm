004eb1d0  55                       push       ebp
004eb1d1  8bec                     mov        ebp, esp
004eb1d3  53                       push       ebx
004eb1d4  56                       push       esi
004eb1d5  8bb1d4040000             mov        esi, dword ptr [ecx + 0x4d4]
004eb1db  57                       push       edi
004eb1dc  8b7d08                   mov        edi, dword ptr [ebp + 8]
004eb1df  33d2                     xor        edx, edx
004eb1e1  85f6                     test       esi, esi
004eb1e3  742b                     je         0x4eb210
004eb1e5  8b81d8040000             mov        eax, dword ptr [ecx + 0x4d8]
004eb1eb  2bc6                     sub        eax, esi
004eb1ed  c1f802                   sar        eax, 2
004eb1f0  3bd0                     cmp        edx, eax
004eb1f2  731c                     jae        0x4eb210
004eb1f4  8b81d4040000             mov        eax, dword ptr [ecx + 0x4d4]
004eb1fa  8b1c90                   mov        ebx, dword ptr [eax + edx*4]
004eb1fd  3bdf                     cmp        ebx, edi
004eb1ff  8d0490                   lea        eax, [eax + edx*4]
004eb202  7403                     je         0x4eb207
004eb204  42                       inc        edx
004eb205  ebda                     jmp        0x4eb1e1
004eb207  5f                       pop        edi
004eb208  5e                       pop        esi
004eb209  b001                     mov        al, 1
004eb20b  5b                       pop        ebx
004eb20c  5d                       pop        ebp
004eb20d  c20400                   ret        4
004eb210  5f                       pop        edi
004eb211  5e                       pop        esi
004eb212  32c0                     xor        al, al
004eb214  5b                       pop        ebx
004eb215  5d                       pop        ebp
004eb216  c20400                   ret        4
