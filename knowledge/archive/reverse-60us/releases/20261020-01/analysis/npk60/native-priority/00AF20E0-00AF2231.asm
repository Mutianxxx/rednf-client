00af20e0  55                       push       ebp
00af20e1  8bec                     mov        ebp, esp
00af20e3  83ec08                   sub        esp, 8
00af20e6  53                       push       ebx
00af20e7  8bd9                     mov        ebx, ecx
00af20e9  8a432c                   mov        al, byte ptr [ebx + 0x2c]
00af20ec  84c0                     test       al, al
00af20ee  8b4508                   mov        eax, dword ptr [ebp + 8]
00af20f1  8b4818                   mov        ecx, dword ptr [eax + 0x18]
00af20f4  57                       push       edi
00af20f5  742e                     je         0xaf2125
00af20f7  83f908                   cmp        ecx, 8
00af20fa  7205                     jb         0xaf2101
00af20fc  8b4004                   mov        eax, dword ptr [eax + 4]
00af20ff  eb03                     jmp        0xaf2104
00af2101  83c004                   add        eax, 4
00af2104  8d8b8c000000             lea        ecx, [ebx + 0x8c]
00af210a  51                       push       ecx
00af210b  6a00                     push       0
00af210d  50                       push       eax
00af210e  8d55fc                   lea        edx, [ebp - 4]
00af2111  52                       push       edx
00af2112  8d45f8                   lea        eax, [ebp - 8]
00af2115  50                       push       eax
00af2116  e8f57afdff               call       0xac9c10
00af211b  8bf8                     mov        edi, eax
00af211d  83c414                   add        esp, 0x14
00af2120  897d08                   mov        dword ptr [ebp + 8], edi
00af2123  eb20                     jmp        0xaf2145
00af2125  83f908                   cmp        ecx, 8
00af2128  7205                     jb         0xaf212f
00af212a  8b4004                   mov        eax, dword ptr [eax + 4]
00af212d  eb03                     jmp        0xaf2132
00af212f  83c004                   add        eax, 4
00af2132  68a036e100               push       0xe136a0
00af2137  50                       push       eax
00af2138  e8ecfb1000               call       0xc01d29
00af213d  83c408                   add        esp, 8
00af2140  894508                   mov        dword ptr [ebp + 8], eax
00af2143  8bf8                     mov        edi, eax
00af2145  85ff                     test       edi, edi
00af2147  750a                     jne        0xaf2153
00af2149  5f                       pop        edi
00af214a  33c0                     xor        eax, eax
00af214c  5b                       pop        ebx
00af214d  8be5                     mov        esp, ebp
00af214f  5d                       pop        ebp
00af2150  c20400                   ret        4
00af2153  56                       push       esi
00af2154  57                       push       edi
00af2155  6a01                     push       1
00af2157  8d730c                   lea        esi, [ebx + 0xc]
00af215a  6a20                     push       0x20
00af215c  56                       push       esi
00af215d  e8d4021100               call       0xc02436
00af2162  8b4324                   mov        eax, dword ptr [ebx + 0x24]
00af2165  83c410                   add        esp, 0x10
00af2168  83f801                   cmp        eax, 1
00af216b  7562                     jne        0xaf21cf
00af216d  bf983ae400               mov        edi, 0xe43a98
00af2172  b912000000               mov        ecx, 0x12
00af2177  33d2                     xor        edx, edx
00af2179  f3a6                     repe cmpsb byte ptr [esi], byte ptr es:[edi]
00af217b  7422                     je         0xaf219f
00af217d  8a432c                   mov        al, byte ptr [ebx + 0x2c]
00af2180  84c0                     test       al, al
00af2182  0f859e000000             jne        0xaf2226
00af2188  8b4508                   mov        eax, dword ptr [ebp + 8]
00af218b  50                       push       eax
00af218c  e8ebfa1000               call       0xc01c7c
00af2191  83c404                   add        esp, 4
00af2194  5e                       pop        esi
00af2195  5f                       pop        edi
00af2196  33c0                     xor        eax, eax
00af2198  5b                       pop        ebx
00af2199  8be5                     mov        esp, ebp
00af219b  5d                       pop        ebp
00af219c  c20400                   ret        4
00af219f  837b2002                 cmp        dword ptr [ebx + 0x20], 2
00af21a3  730c                     jae        0xaf21b1
00af21a5  8b4508                   mov        eax, dword ptr [ebp + 8]
00af21a8  5e                       pop        esi
00af21a9  5f                       pop        edi
00af21aa  5b                       pop        ebx
00af21ab  8be5                     mov        esp, ebp
00af21ad  5d                       pop        ebp
00af21ae  c20400                   ret        4
00af21b1  8a432c                   mov        al, byte ptr [ebx + 0x2c]
00af21b4  84c0                     test       al, al
00af21b6  756e                     jne        0xaf2226
00af21b8  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00af21bb  51                       push       ecx
00af21bc  e8bbfa1000               call       0xc01c7c
00af21c1  83c404                   add        esp, 4
00af21c4  5e                       pop        esi
00af21c5  5f                       pop        edi
00af21c6  33c0                     xor        eax, eax
00af21c8  5b                       pop        ebx
00af21c9  8be5                     mov        esp, ebp
00af21cb  5d                       pop        ebp
00af21cc  c20400                   ret        4
00af21cf  83f802                   cmp        eax, 2
00af21d2  7542                     jne        0xaf2216
00af21d4  bf80aae600               mov        edi, 0xe6aa80
00af21d9  b910000000               mov        ecx, 0x10
00af21de  33d2                     xor        edx, edx
00af21e0  f3a6                     repe cmpsb byte ptr [esi], byte ptr es:[edi]
00af21e2  7416                     je         0xaf21fa
00af21e4  8b4508                   mov        eax, dword ptr [ebp + 8]
00af21e7  50                       push       eax
00af21e8  8bcb                     mov        ecx, ebx
00af21ea  e8b1f8ffff               call       0xaf1aa0
00af21ef  5e                       pop        esi
00af21f0  5f                       pop        edi
00af21f1  33c0                     xor        eax, eax
00af21f3  5b                       pop        ebx
00af21f4  8be5                     mov        esp, ebp
00af21f6  5d                       pop        ebp
00af21f7  c20400                   ret        4
00af21fa  837b2002                 cmp        dword ptr [ebx + 0x20], 2
00af21fe  72a5                     jb         0xaf21a5
00af2200  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00af2203  51                       push       ecx
00af2204  8bcb                     mov        ecx, ebx
00af2206  e895f8ffff               call       0xaf1aa0
00af220b  5e                       pop        esi
00af220c  5f                       pop        edi
00af220d  33c0                     xor        eax, eax
00af220f  5b                       pop        ebx
00af2210  8be5                     mov        esp, ebp
00af2212  5d                       pop        ebp
00af2213  c20400                   ret        4
00af2216  8a432c                   mov        al, byte ptr [ebx + 0x2c]
00af2219  84c0                     test       al, al
00af221b  7509                     jne        0xaf2226
00af221d  57                       push       edi
00af221e  e859fa1000               call       0xc01c7c
00af2223  83c404                   add        esp, 4
00af2226  5e                       pop        esi
00af2227  5f                       pop        edi
00af2228  33c0                     xor        eax, eax
00af222a  5b                       pop        ebx
00af222b  8be5                     mov        esp, ebp
00af222d  5d                       pop        ebp
00af222e  c20400                   ret        4