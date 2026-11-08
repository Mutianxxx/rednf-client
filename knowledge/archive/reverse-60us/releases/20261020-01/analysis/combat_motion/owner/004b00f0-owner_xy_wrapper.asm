004b00f0  55                       push       ebp
004b00f1  8bec                     mov        ebp, esp
004b00f3  53                       push       ebx
004b00f4  56                       push       esi
004b00f5  8bf1                     mov        esi, ecx
004b00f7  33db                     xor        ebx, ebx
004b00f9  85f6                     test       esi, esi
004b00fb  0f84c3000000             je         0x4b01c4
004b0101  8b06                     mov        eax, dword ptr [esi]
004b0103  ff5064                   call       dword ptr [eax + 0x64]
004b0106  84c0                     test       al, al
004b0108  0f84b6000000             je         0x4b01c4
004b010e  8b16                     mov        edx, dword ptr [esi]
004b0110  8bce                     mov        ecx, esi
004b0112  ff92c4030000             call       dword ptr [edx + 0x3c4]
004b0118  85c0                     test       eax, eax
004b011a  0f84a4000000             je         0x4b01c4
004b0120  57                       push       edi
004b0121  33ff                     xor        edi, edi
004b0123  8b06                     mov        eax, dword ptr [esi]
004b0125  8bce                     mov        ecx, esi
004b0127  ff90c4030000             call       dword ptr [eax + 0x3c4]
004b012d  8b4804                   mov        ecx, dword ptr [eax + 4]
004b0130  85c9                     test       ecx, ecx
004b0132  7504                     jne        0x4b0138
004b0134  33c0                     xor        eax, eax
004b0136  eb08                     jmp        0x4b0140
004b0138  8b4008                   mov        eax, dword ptr [eax + 8]
004b013b  2bc1                     sub        eax, ecx
004b013d  c1f802                   sar        eax, 2
004b0140  3bf8                     cmp        edi, eax
004b0142  0f8d7b000000             jge        0x4b01c3
004b0148  8b16                     mov        edx, dword ptr [esi]
004b014a  8bce                     mov        ecx, esi
004b014c  ff92c4030000             call       dword ptr [edx + 0x3c4]
004b0152  8b4804                   mov        ecx, dword ptr [eax + 4]
004b0155  85c9                     test       ecx, ecx
004b0157  7411                     je         0x4b016a
004b0159  8b4008                   mov        eax, dword ptr [eax + 8]
004b015c  2bc1                     sub        eax, ecx
004b015e  c1f802                   sar        eax, 2
004b0161  3bf8                     cmp        edi, eax
004b0163  7305                     jae        0x4b016a
004b0165  8b0cb9                   mov        ecx, dword ptr [ecx + edi*4]
004b0168  eb02                     jmp        0x4b016c
004b016a  33c9                     xor        ecx, ecx
004b016c  397104                   cmp        dword ptr [ecx + 4], esi
004b016f  754c                     jne        0x4b01bd
004b0171  8b06                     mov        eax, dword ptr [esi]
004b0173  8bce                     mov        ecx, esi
004b0175  ff90c4030000             call       dword ptr [eax + 0x3c4]
004b017b  8b4804                   mov        ecx, dword ptr [eax + 4]
004b017e  85c9                     test       ecx, ecx
004b0180  7411                     je         0x4b0193
004b0182  8b4008                   mov        eax, dword ptr [eax + 8]
004b0185  2bc1                     sub        eax, ecx
004b0187  c1f802                   sar        eax, 2
004b018a  3bf8                     cmp        edi, eax
004b018c  7305                     jae        0x4b0193
004b018e  8b0cb9                   mov        ecx, dword ptr [ecx + edi*4]
004b0191  eb02                     jmp        0x4b0195
004b0193  33c9                     xor        ecx, ecx
004b0195  6a00                     push       0
004b0197  683c96f500               push       0xf5963c
004b019c  68f451f500               push       0xf551f4
004b01a1  6a00                     push       0
004b01a3  51                       push       ecx
004b01a4  e8620b7500               call       0xc00d0b
004b01a9  8bd8                     mov        ebx, eax
004b01ab  83c414                   add        esp, 0x14
004b01ae  85db                     test       ebx, ebx
004b01b0  740b                     je         0x4b01bd
004b01b2  8b13                     mov        edx, dword ptr [ebx]
004b01b4  8bcb                     mov        ecx, ebx
004b01b6  ff5260                   call       dword ptr [edx + 0x60]
004b01b9  84c0                     test       al, al
004b01bb  7506                     jne        0x4b01c3
004b01bd  47                       inc        edi
004b01be  e960ffffff               jmp        0x4b0123
004b01c3  5f                       pop        edi
004b01c4  8b06                     mov        eax, dword ptr [esi]
004b01c6  6a10                     push       0x10
004b01c8  8bce                     mov        ecx, esi
004b01ca  ff9010040000             call       dword ptr [eax + 0x410]
004b01d0  84c0                     test       al, al
004b01d2  741a                     je         0x4b01ee
004b01d4  85db                     test       ebx, ebx
004b01d6  7516                     jne        0x4b01ee
004b01d8  8b16                     mov        edx, dword ptr [esi]
004b01da  8bce                     mov        ecx, esi
004b01dc  ff9230020000             call       dword ptr [edx + 0x230]
004b01e2  83f805                   cmp        eax, 5
004b01e5  5e                       pop        esi
004b01e6  0f94c0                   sete       al
004b01e9  5b                       pop        ebx
004b01ea  5d                       pop        ebp
004b01eb  c20c00                   ret        0xc
004b01ee  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b01f1  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b01f4  8b5508                   mov        edx, dword ptr [ebp + 8]
004b01f7  50                       push       eax
004b01f8  51                       push       ecx
004b01f9  52                       push       edx
004b01fa  8bce                     mov        ecx, esi
004b01fc  e8cf7b0300               call       0x4e7dd0
004b0201  5e                       pop        esi
004b0202  5b                       pop        ebx
004b0203  5d                       pop        ebp
004b0204  c20c00                   ret        0xc
