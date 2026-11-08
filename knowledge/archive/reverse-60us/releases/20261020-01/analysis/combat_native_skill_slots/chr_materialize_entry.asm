004da140  55                       push       ebp
004da141  8bec                     mov        ebp, esp
004da143  6aff                     push       -1
004da145  680087c500               push       0xc58700
004da14a  64a100000000             mov        eax, dword ptr fs:[0]
004da150  50                       push       eax
004da151  64892500000000           mov        dword ptr fs:[0], esp
004da158  81ec84030000             sub        esp, 0x384
004da15e  53                       push       ebx
004da15f  56                       push       esi
004da160  57                       push       edi
004da161  8b7d08                   mov        edi, dword ptr [ebp + 8]
004da164  57                       push       edi
004da165  8bf1                     mov        esi, ecx
004da167  8b0ddc300001             mov        ecx, dword ptr [0x10030dc]
004da16d  6a00                     push       0
004da16f  e8bc2c6a00               call       0xb7ce30
004da174  8bd8                     mov        ebx, eax
004da176  85db                     test       ebx, ebx
004da178  895d08                   mov        dword ptr [ebp + 8], ebx
004da17b  7522                     jne        0x4da19f
004da17d  57                       push       edi
004da17e  68e03ecd00               push       0xcd3ee0
004da183  ff15bc2eff00             call       dword ptr [0xff2ebc]
004da189  83c408                   add        esp, 8
004da18c  5f                       pop        edi
004da18d  5e                       pop        esi
004da18e  5b                       pop        ebx
004da18f  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004da192  64890d00000000           mov        dword ptr fs:[0], ecx
004da199  8be5                     mov        esp, ebp
004da19b  5d                       pop        ebp
004da19c  c20800                   ret        8
004da19f  8d8b040c0000             lea        ecx, [ebx + 0xc04]
004da1a5  e8468f5700               call       0xa530f0
004da1aa  8bf8                     mov        edi, eax
004da1ac  57                       push       edi
004da1ad  e81b5c7200               call       0xbffdcd
004da1b2  83c404                   add        esp, 4
004da1b5  50                       push       eax
004da1b6  57                       push       edi
004da1b7  8d8e44020000             lea        ecx, [esi + 0x244]
004da1bd  e8be8cf2ff               call       0x402e80
