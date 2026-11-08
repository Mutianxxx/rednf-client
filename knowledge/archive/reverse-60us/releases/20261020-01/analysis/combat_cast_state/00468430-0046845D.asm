00468430  55                       push       ebp
00468431  8bec                     mov        ebp, esp
00468433  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00468436  83f8ff                   cmp        eax, -1
00468439  56                       push       esi
0046843a  8bf1                     mov        esi, ecx
0046843c  750b                     jne        0x468449
0046843e  8d8e1c030000             lea        ecx, [esi + 0x31c]
00468444  e8179cf9ff               call       0x402060
00468449  8b8ea4010000             mov        ecx, dword ptr [esi + 0x1a4]
0046844f  48                       dec        eax
00468450  8d0cc1                   lea        ecx, [ecx + eax*8]
00468453  e8089cf9ff               call       0x402060
00468458  5e                       pop        esi
00468459  5d                       pop        ebp
0046845a  c20800                   ret        8