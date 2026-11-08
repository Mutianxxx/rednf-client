00884720  55                       push       ebp
00884721  8bec                     mov        ebp, esp
00884723  6aff                     push       -1
00884725  68b919c800               push       0xc819b9
0088472a  64a100000000             mov        eax, dword ptr fs:[0]
00884730  50                       push       eax
00884731  64892500000000           mov        dword ptr fs:[0], esp
00884738  81ec94000000             sub        esp, 0x94
0088473e  53                       push       ebx
0088473f  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
00884742  53                       push       ebx
00884743  68d0dd0b01               push       0x10bddd0
00884748  e843b0faff               call       0x82f790
0088474d  83c408                   add        esp, 8
00884750  84c0                     test       al, al
00884752  750f                     jne        0x884763
00884754  5b                       pop        ebx
00884755  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00884758  64890d00000000           mov        dword ptr fs:[0], ecx
0088475f  8be5                     mov        esp, ebp
00884761  5d                       pop        ebp
00884762  c3                       ret        
00884763  56                       push       esi
00884764  8b7508                   mov        esi, dword ptr [ebp + 8]
00884767  57                       push       edi
00884768  8bce                     mov        ecx, esi
0088476a  e8a1ce0000               call       0x891610
0088476f  8d8ee0000000             lea        ecx, [esi + 0xe0]
00884775  e836ce0000               call       0x8915b0
0088477a  53                       push       ebx
0088477b  68d0dd0b01               push       0x10bddd0
00884780  8d86a4000000             lea        eax, [esi + 0xa4]
00884786  68f8b8ca00               push       0xcab8f8
0088478b  50                       push       eax
0088478c  e87faffaff               call       0x82f710