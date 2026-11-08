0054ff60  55                       push       ebp
0054ff61  8bec                     mov        ebp, esp
0054ff63  56                       push       esi
0054ff64  8bf1                     mov        esi, ecx
0054ff66  8b8e30020000             mov        ecx, dword ptr [esi + 0x230]
0054ff6c  85c9                     test       ecx, ecx
0054ff6e  57                       push       edi
0054ff6f  7412                     je         0x54ff83
0054ff71  8b8634020000             mov        eax, dword ptr [esi + 0x234]
0054ff77  8b7d08                   mov        edi, dword ptr [ebp + 8]
0054ff7a  2bc1                     sub        eax, ecx
0054ff7c  c1f803                   sar        eax, 3
0054ff7f  3bf8                     cmp        edi, eax
0054ff81  7208                     jb         0x54ff8b
0054ff83  5f                       pop        edi
0054ff84  33c0                     xor        eax, eax
0054ff86  5e                       pop        esi
0054ff87  5d                       pop        ebp
0054ff88  c20800                   ret        8
0054ff8b  8b8630020000             mov        eax, dword ptr [esi + 0x230]
0054ff91  53                       push       ebx
0054ff92  8d0cf8                   lea        ecx, [eax + edi*8]
0054ff95  e8c620ebff               call       0x402060
0054ff9a  8d4e08                   lea        ecx, [esi + 8]
0054ff9d  8bd8                     mov        ebx, eax
0054ff9f  e8bc20ebff               call       0x402060
0054ffa4  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0054ffa7  50                       push       eax
0054ffa8  6a00                     push       0
0054ffaa  57                       push       edi
0054ffab  53                       push       ebx
0054ffac  51                       push       ecx
0054ffad  8bce                     mov        ecx, esi
0054ffaf  e88cfcffff               call       0x54fc40
0054ffb4  5b                       pop        ebx
0054ffb5  5f                       pop        edi
0054ffb6  5e                       pop        esi
0054ffb7  5d                       pop        ebp
0054ffb8  c20800                   ret        8
