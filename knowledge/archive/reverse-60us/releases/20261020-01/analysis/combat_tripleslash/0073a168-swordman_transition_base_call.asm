0073a168  8b4514                   mov        eax, dword ptr [ebp + 0x14]
0073a16b  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
0073a16e  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
0073a171  8b5d08                   mov        ebx, dword ptr [ebp + 8]
0073a174  50                       push       eax
0073a175  51                       push       ecx
0073a176  57                       push       edi
0073a177  53                       push       ebx
0073a178  8bce                     mov        ecx, esi
0073a17a  e8b1b5d8ff               call       0x4c5730
0073a17f  8d43fa                   lea        eax, [ebx - 6]
0073a182  83f808                   cmp        eax, 8
0073a185  0f8792320000             ja         0x73d41d
0073a18b  ff                       .byte      0xff
0073a18c  24                       .byte      0x24
