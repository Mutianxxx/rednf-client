00511110  55                       push       ebp
00511111  8bec                     mov        ebp, esp
00511113  56                       push       esi
00511114  8bf1                     mov        esi, ecx
00511116  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511119  85c9                     test       ecx, ecx
0051111b  7439                     je         0x511156
0051111d  e86eaff8ff               call       0x49c090
00511122  84c0                     test       al, al
00511124  7430                     je         0x511156
00511126  8b06                     mov        eax, dword ptr [esi]
00511128  85c0                     test       eax, eax
0051112a  8bc8                     mov        ecx, eax
0051112c  7503                     jne        0x511131
0051112e  8d4e08                   lea        ecx, [esi + 8]
00511131  0fbe5134                 movsx      edx, byte ptr [ecx + 0x34]
00511135  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00511138  3bd1                     cmp        edx, ecx
0051113a  741a                     je         0x511156
0051113c  85c9                     test       ecx, ecx
0051113e  7405                     je         0x511145
00511140  83f901                   cmp        ecx, 1
00511143  750a                     jne        0x51114f
00511145  85c0                     test       eax, eax
00511147  7503                     jne        0x51114c
00511149  8d4608                   lea        eax, [esi + 8]
0051114c  884834                   mov        byte ptr [eax + 0x34], cl
0051114f  c686f800000001           mov        byte ptr [esi + 0xf8], 1
00511156  5e                       pop        esi
00511157  5d                       pop        ebp
00511158  c20400                   ret        4
