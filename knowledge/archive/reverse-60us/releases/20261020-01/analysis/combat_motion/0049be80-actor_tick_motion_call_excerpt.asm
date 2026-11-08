0049be80  55                       push       ebp
0049be81  8bec                     mov        ebp, esp
0049be83  83ec0c                   sub        esp, 0xc
0049be86  56                       push       esi
0049be87  8bf1                     mov        esi, ecx
0049be89  8b86b0010000             mov        eax, dword ptr [esi + 0x1b0]
0049be8f  85c0                     test       eax, eax
0049be91  57                       push       edi
0049be92  742b                     je         0x49bebf
0049be94  83beb4010000ff           cmp        dword ptr [esi + 0x1b4], -1
0049be9b  7422                     je         0x49bebf
0049be9d  8d4e20                   lea        ecx, [esi + 0x20]
0049bea0  e85bb06600               call       0xb06f00
0049bea5  8b8eb8010000             mov        ecx, dword ptr [esi + 0x1b8]
0049beab  038eb4010000             add        ecx, dword ptr [esi + 0x1b4]
0049beb1  3bc1                     cmp        eax, ecx
0049beb3  7c0a                     jl         0x49bebf
0049beb5  8b16                     mov        edx, dword ptr [esi]
0049beb7  8bce                     mov        ecx, esi
0049beb9  ff9220010000             call       dword ptr [edx + 0x120]
0049bebf  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
0049bec5  e836550700               call       0x511400
