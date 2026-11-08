00acb4d0  8bf1                     mov        esi, ecx
00acb4d2  6aff                     push       -1
00acb4d4  8d4e04                   lea        ecx, [esi + 4]
00acb4d7  8906                     mov        dword ptr [esi], eax
00acb4d9  6a00                     push       0
00acb4db  8d5704                   lea        edx, [edi + 4]
00acb4de  c7411807000000           mov        dword ptr [ecx + 0x18], 7
00acb4e5  c7411400000000           mov        dword ptr [ecx + 0x14], 0
00acb4ec  52                       push       edx
00acb4ed  8975f0                   mov        dword ptr [ebp - 0x10], esi
00acb4f0  66c741040000             mov        word ptr [ecx + 4], 0
00acb4f6  e8657893ff               call       0x402d60
00acb4fb  83c720                   add        edi, 0x20
00acb4fe  57                       push       edi
00acb4ff  8d4e20                   lea        ecx, [esi + 0x20]
00acb502  c745fc00000000           mov        dword ptr [ebp - 4], 0
00acb509  e882feffff               call       0xacb390
00acb50e  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00acb511  5f                       pop        edi
00acb512  8bc6                     mov        eax, esi
00acb514  5e                       pop        esi
00acb515  64890d00000000           mov        dword ptr fs:[0], ecx
00acb51c  8be5                     mov        esp, ebp
00acb51e  5d                       pop        ebp
00acb51f  c20400                   ret        4
00acb522  cc                       int3       
00acb523  cc                       int3       
00acb524  cc                       int3       
00acb525  cc                       int3       
00acb526  cc                       int3       
00acb527  cc                       int3       
00acb528  cc                       int3       
00acb529  cc                       int3       
00acb52a  cc                       int3       
00acb52b  cc                       int3       
00acb52c  cc                       int3       
00acb52d  cc                       int3       
00acb52e  cc                       int3       
00acb52f  cc                       int3       
00acb530  83c108                   add        ecx, 8
00acb533  e9e8feffff               jmp        0xacb420
00acb538  cc                       int3       
00acb539  cc                       int3       
00acb53a  cc                       int3       
00acb53b  cc                       int3       
00acb53c  cc                       int3       
00acb53d  cc                       int3       
00acb53e  cc                       int3       
00acb53f  cc                       int3       
00acb540  55                       push       ebp
00acb541  8bec                     mov        ebp, esp
00acb543  6aff                     push       -1
00acb545  681135c900               push       0xc93511
00acb54a  64a100000000             mov        eax, dword ptr fs:[0]
00acb550  50                       push       eax
00acb551  64892500000000           mov        dword ptr fs:[0], esp
00acb558  83ec0c                   sub        esp, 0xc
00acb55b  53                       push       ebx
00acb55c  56                       push       esi
00acb55d  57                       push       edi
00acb55e  8965f0                   mov        dword ptr [ebp - 0x10], esp
00acb561  6a34                     push       0x34
00acb563  e8b5231200               call       0xbed91d
00acb568  8bf0                     mov        esi, eax
00acb56a  83c404                   add        esp, 4
00acb56d  8975ec                   mov        dword ptr [ebp - 0x14], esi
00acb570  c745fc00000000           mov        dword ptr [ebp - 4], 0
00acb577  8975e8                   mov        dword ptr [ebp - 0x18], esi
00acb57a  85f6                     test       esi, esi
00acb57c  c645fc01                 mov        byte ptr [ebp - 4], 1
00acb580  7417                     je         0xacb599
00acb582  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00acb585  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00acb588  8b4508                   mov        eax, dword ptr [ebp + 8]
00acb58b  894e04                   mov        dword ptr [esi + 4], ecx
00acb58e  52                       push       edx
00acb58f  8d4e08                   lea        ecx, [esi + 8]
00acb592  8906                     mov        dword ptr [esi], eax
00acb594  e817ffffff               call       0xacb4b0
00acb599  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00acb59c  5f                       pop        edi
00acb59d  8bc6                     mov        eax, esi
00acb59f  5e                       pop        esi
00acb5a0  64890d00000000           mov        dword ptr fs:[0], ecx
00acb5a7  5b                       pop        ebx
00acb5a8  8be5                     mov        esp, ebp
00acb5aa  5d                       pop        ebp
00acb5ab  c20c00                   ret        0xc
00acb5ae  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00acb5b1  50                       push       eax
00acb5b2  e8264a1300               call       0xbfffdd
00acb5b7  83c404                   add        esp, 4
00acb5ba  6a00                     push       0
00acb5bc  6a00                     push       0
00acb5be  e8ac4f1300               call       0xc0056f
00acb5c3  cc                       int3       
00acb5c4  cc                       int3       
00acb5c5  cc                       int3       
00acb5c6  cc                       int3       
00acb5c7  cc                       int3       
00acb5c8  cc                       int3       
00acb5c9  cc                       int3       
00acb5ca  cc                       int3       
00acb5cb  cc                       int3       
00acb5cc  cc                       int3       
00acb5cd  cc                       int3       
00acb5ce  cc                       int3       
00acb5cf  cc                       int3       
00acb5d0  56                       push       esi
00acb5d1  57                       push       edi
00acb5d2  8bf9                     mov        edi, ecx
00acb5d4  8b4704                   mov        eax, dword ptr [edi + 4]
00acb5d7  8b30                     mov        esi, dword ptr [eax]
00acb5d9  8900                     mov        dword ptr [eax], eax
00acb5db  8b4704                   mov        eax, dword ptr [edi + 4]
00acb5de  89                       .byte      0x89
00acb5df  40                       inc        eax