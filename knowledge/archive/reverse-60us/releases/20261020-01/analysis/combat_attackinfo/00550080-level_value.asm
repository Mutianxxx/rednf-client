00550080  55                       push       ebp
00550081  8bec                     mov        ebp, esp
00550083  53                       push       ebx
00550084  56                       push       esi
00550085  8bf1                     mov        esi, ecx
00550087  8b8e40020000             mov        ecx, dword ptr [esi + 0x240]
0055008d  85c9                     test       ecx, ecx
0055008f  7412                     je         0x5500a3
00550091  8b8644020000             mov        eax, dword ptr [esi + 0x244]
00550097  8b5d08                   mov        ebx, dword ptr [ebp + 8]
0055009a  2bc1                     sub        eax, ecx
0055009c  c1f804                   sar        eax, 4
0055009f  3bd8                     cmp        ebx, eax
005500a1  7208                     jb         0x5500ab
005500a3  5e                       pop        esi
005500a4  33c0                     xor        eax, eax
005500a6  5b                       pop        ebx
005500a7  5d                       pop        ebp
005500a8  c22000                   ret        0x20
005500ab  8b8e40020000             mov        ecx, dword ptr [esi + 0x240]
005500b1  8bc3                     mov        eax, ebx
005500b3  c1e004                   shl        eax, 4
005500b6  8b540804                 mov        edx, dword ptr [eax + ecx + 4]
005500ba  03c1                     add        eax, ecx
005500bc  85d2                     test       edx, edx
005500be  7504                     jne        0x5500c4
005500c0  33c9                     xor        ecx, ecx
005500c2  eb08                     jmp        0x5500cc
005500c4  8b4808                   mov        ecx, dword ptr [eax + 8]
005500c7  2bca                     sub        ecx, edx
005500c9  c1f903                   sar        ecx, 3
005500cc  8b550c                   mov        edx, dword ptr [ebp + 0xc]
005500cf  57                       push       edi
005500d0  8d7aff                   lea        edi, [edx - 1]
005500d3  3bf9                     cmp        edi, ecx
005500d5  7209                     jb         0x5500e0
005500d7  5f                       pop        edi
005500d8  5e                       pop        esi
005500d9  33c0                     xor        eax, eax
005500db  5b                       pop        ebx
005500dc  5d                       pop        ebp
005500dd  c22000                   ret        0x20
005500e0  8b4004                   mov        eax, dword ptr [eax + 4]
005500e3  8d4cd0f8                 lea        ecx, [eax + edx*8 - 8]
005500e7  e8741febff               call       0x402060
005500ec  8d4e08                   lea        ecx, [esi + 8]
005500ef  8bf8                     mov        edi, eax
005500f1  e86a1febff               call       0x402060
005500f6  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
005500f9  50                       push       eax
005500fa  6a01                     push       1
005500fc  53                       push       ebx
005500fd  57                       push       edi
005500fe  51                       push       ecx
005500ff  8bce                     mov        ecx, esi
00550101  e83afbffff               call       0x54fc40
00550106  8b751c                   mov        esi, dword ptr [ebp + 0x1c]
00550109  83fe0c                   cmp        esi, 0xc
0055010c  894508                   mov        dword ptr [ebp + 8], eax
0055010f  7431                     je         0x550142
00550111  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00550114  8b7d18                   mov        edi, dword ptr [ebp + 0x18]
00550117  3bcf                     cmp        ecx, edi
00550119  7427                     je         0x550142
0055011b  8b5520                   mov        edx, dword ptr [ebp + 0x20]
0055011e  52                       push       edx
0055011f  56                       push       esi
00550120  51                       push       ecx
00550121  e82a80efff               call       0x448150
00550126  da4d08                   fimul      dword ptr [ebp + 8]
00550129  8b4524                   mov        eax, dword ptr [ebp + 0x24]
0055012c  50                       push       eax
0055012d  56                       push       esi
0055012e  57                       push       edi
0055012f  d95d08                   fstp       dword ptr [ebp + 8]
00550132  e81980efff               call       0x448150
00550137  d87d08                   fdivr      dword ptr [ebp + 8]
0055013a  83c418                   add        esp, 0x18
0055013d  e802146b00               call       0xc01544
00550142  5f                       pop        edi
00550143  5e                       pop        esi
00550144  5b                       pop        ebx
00550145  5d                       pop        ebp
00550146  c22000                   ret        0x20
