004aeb90  55                       push       ebp
004aeb91  8bec                     mov        ebp, esp
004aeb93  56                       push       esi
004aeb94  8b7508                   mov        esi, dword ptr [ebp + 8]
004aeb97  85f6                     test       esi, esi
004aeb99  7469                     je         0x4aec04
004aeb9b  8b4138                   mov        eax, dword ptr [ecx + 0x38]
004aeb9e  85c0                     test       eax, eax
004aeba0  7504                     jne        0x4aeba6
004aeba2  33d2                     xor        edx, edx
004aeba4  eb08                     jmp        0x4aebae
004aeba6  8b513c                   mov        edx, dword ptr [ecx + 0x3c]
004aeba9  2bd0                     sub        edx, eax
004aebab  c1fa02                   sar        edx, 2
004aebae  57                       push       edi
004aebaf  8b7e38                   mov        edi, dword ptr [esi + 0x38]
004aebb2  85ff                     test       edi, edi
004aebb4  741c                     je         0x4aebd2
004aebb6  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004aebb9  2bc7                     sub        eax, edi
004aebbb  c1f802                   sar        eax, 2
004aebbe  3bd0                     cmp        edx, eax
004aebc0  7310                     jae        0x4aebd2
004aebc2  8b5138                   mov        edx, dword ptr [ecx + 0x38]
004aebc5  85d2                     test       edx, edx
004aebc7  7504                     jne        0x4aebcd
004aebc9  33c0                     xor        eax, eax
004aebcb  eb18                     jmp        0x4aebe5
004aebcd  8b413c                   mov        eax, dword ptr [ecx + 0x3c]
004aebd0  eb0e                     jmp        0x4aebe0
004aebd2  8b5638                   mov        edx, dword ptr [esi + 0x38]
004aebd5  85d2                     test       edx, edx
004aebd7  7504                     jne        0x4aebdd
004aebd9  33c0                     xor        eax, eax
004aebdb  eb08                     jmp        0x4aebe5
004aebdd  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004aebe0  2bc2                     sub        eax, edx
004aebe2  c1f802                   sar        eax, 2
004aebe5  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004aebe8  3bd0                     cmp        edx, eax
004aebea  5f                       pop        edi
004aebeb  7d17                     jge        0x4aec04
004aebed  8b4638                   mov        eax, dword ptr [esi + 0x38]
004aebf0  8b4938                   mov        ecx, dword ptr [ecx + 0x38]
004aebf3  c1e202                   shl        edx, 2
004aebf6  03c2                     add        eax, edx
004aebf8  8b00                     mov        eax, dword ptr [eax]
004aebfa  03ca                     add        ecx, edx
004aebfc  8b09                     mov        ecx, dword ptr [ecx]
004aebfe  50                       push       eax
004aebff  e8fc885700               call       0xa27500
004aec04  5e                       pop        esi
004aec05  5d                       pop        ebp
004aec06  c2                       .byte      0xc2
