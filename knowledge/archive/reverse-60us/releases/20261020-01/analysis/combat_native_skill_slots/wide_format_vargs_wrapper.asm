004011f0  55                       push       ebp
004011f1  8bec                     mov        ebp, esp
004011f3  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004011f6  53                       push       ebx
004011f7  33db                     xor        ebx, ebx
004011f9  85c0                     test       eax, eax
004011fb  750a                     jne        0x401207
004011fd  b857000780               mov        eax, 0x80070057
00401202  5b                       pop        ebx
00401203  5d                       pop        ebp
00401204  c21000                   ret        0x10
00401207  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
0040120a  56                       push       esi
0040120b  57                       push       edi
0040120c  8b7d08                   mov        edi, dword ptr [ebp + 8]
0040120f  8d70ff                   lea        esi, [eax - 1]
00401212  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00401215  50                       push       eax
00401216  51                       push       ecx
00401217  56                       push       esi
00401218  57                       push       edi
00401219  e8c4ed7f00               call       0xbfffe2
0040121e  83c410                   add        esp, 0x10
00401221  85c0                     test       eax, eax
00401223  7c15                     jl         0x40123a
00401225  3bc6                     cmp        eax, esi
00401227  7711                     ja         0x40123a
00401229  8bc3                     mov        eax, ebx
0040122b  7518                     jne        0x401245
0040122d  66c704770000             mov        word ptr [edi + esi*2], 0
00401233  5f                       pop        edi
00401234  5e                       pop        esi
00401235  5b                       pop        ebx
00401236  5d                       pop        ebp
00401237  c21000                   ret        0x10
0040123a  b87a000780               mov        eax, 0x8007007a
0040123f  66c704770000             mov        word ptr [edi + esi*2], 0
00401245  5f                       pop        edi
00401246  5e                       pop        esi
00401247  5b                       pop        ebx
00401248  5d                       pop        ebp
00401249  c2                       .byte      0xc2
