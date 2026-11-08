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