00467480  56                       push       esi
00467481  8bf1                     mov        esi, ecx
00467483  8d4e1c                   lea        ecx, [esi + 0x1c]
00467486  e8d5abf9ff               call       0x402060
0046748b  85c0                     test       eax, eax
0046748d  7524                     jne        0x4674b3
0046748f  8bce                     mov        ecx, esi
00467491  e81abffcff               call       0x4333b0
00467496  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
0046749c  dfe0                     fnstsw     ax
0046749e  f6c441                   test       ah, 0x41
004674a1  7410                     je         0x4674b3
004674a3  8d4e08                   lea        ecx, [esi + 8]
004674a6  e8b5abf9ff               call       0x402060
004674ab  85c0                     test       eax, eax
004674ad  7f04                     jg         0x4674b3
004674af  33c0                     xor        eax, eax
004674b1  5e                       pop        esi
004674b2  c3                       ret        
004674b3  b801000000               mov        eax, 1
004674b8  5e                       pop        esi
004674b9  c3                       ret        