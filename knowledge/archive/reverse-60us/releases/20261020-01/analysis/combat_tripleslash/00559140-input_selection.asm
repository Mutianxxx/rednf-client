00559140  55                       push       ebp
00559141  8bec                     mov        ebp, esp
00559143  83ec10                   sub        esp, 0x10
00559146  53                       push       ebx
00559147  56                       push       esi
00559148  57                       push       edi
00559149  8bf9                     mov        edi, ecx
0055914b  8b07                     mov        eax, dword ptr [edi]
0055914d  33f6                     xor        esi, esi
0055914f  85c0                     test       eax, eax
00559151  0f8e41010000             jle        0x559298
00559157  8b1d28f04001             mov        ebx, dword ptr [0x140f028]
0055915d  8d4900                   lea        ecx, [ecx]
00559160  8b470c                   mov        eax, dword ptr [edi + 0xc]
00559163  2b4708                   sub        eax, dword ptr [edi + 8]
00559166  c1f802                   sar        eax, 2
00559169  3bf0                     cmp        esi, eax
0055916b  7222                     jb         0x55918f
0055916d  50                       push       eax
0055916e  56                       push       esi
0055916f  6840cfcd00               push       0xcdcf40
00559174  68a0b3cb00               push       0xcbb3a0
00559179  ff15bc2eff00             call       dword ptr [0xff2ebc]
0055917f  83c410                   add        esp, 0x10
00559182  6a00                     push       0
00559184  6a00                     push       0
00559186  6a00                     push       0
00559188  688c0000c0               push       0xc000008c
0055918d  ffd3                     call       ebx
0055918f  8b4708                   mov        eax, dword ptr [edi + 8]
00559192  833cb000                 cmp        dword ptr [eax + esi*4], 0
00559196  7442                     je         0x5591da
00559198  8b470c                   mov        eax, dword ptr [edi + 0xc]
0055919b  2b4708                   sub        eax, dword ptr [edi + 8]
0055919e  c1f802                   sar        eax, 2
005591a1  3bf0                     cmp        esi, eax
005591a3  7222                     jb         0x5591c7
005591a5  50                       push       eax
005591a6  56                       push       esi
005591a7  6840cfcd00               push       0xcdcf40
005591ac  68a0b3cb00               push       0xcbb3a0
005591b1  ff15bc2eff00             call       dword ptr [0xff2ebc]
005591b7  83c410                   add        esp, 0x10
005591ba  6a00                     push       0
005591bc  6a00                     push       0
005591be  6a00                     push       0
005591c0  688c0000c0               push       0xc000008c
005591c5  ffd3                     call       ebx
005591c7  8b4708                   mov        eax, dword ptr [edi + 8]
005591ca  8b0cb0                   mov        ecx, dword ptr [eax + esi*4]
005591cd  83c108                   add        ecx, 8
005591d0  e88b8eeaff               call       0x402060
005591d5  3b4508                   cmp        eax, dword ptr [ebp + 8]
005591d8  7417                     je         0x5591f1
005591da  8b07                     mov        eax, dword ptr [edi]
005591dc  46                       inc        esi
005591dd  3bf0                     cmp        esi, eax
005591df  0f8c7bffffff             jl         0x559160
005591e5  5f                       pop        edi
005591e6  5e                       pop        esi
005591e7  83c8ff                   or         eax, 0xffffffff
005591ea  5b                       pop        ebx
005591eb  8be5                     mov        esp, ebp
005591ed  5d                       pop        ebp
005591ee  c20800                   ret        8
005591f1  8b470c                   mov        eax, dword ptr [edi + 0xc]
005591f4  2b4708                   sub        eax, dword ptr [edi + 8]
005591f7  c1f802                   sar        eax, 2
005591fa  3bf0                     cmp        esi, eax
005591fc  7222                     jb         0x559220
005591fe  50                       push       eax
005591ff  56                       push       esi
00559200  6840cfcd00               push       0xcdcf40
00559205  68a0b3cb00               push       0xcbb3a0
0055920a  ff15bc2eff00             call       dword ptr [0xff2ebc]
00559210  83c410                   add        esp, 0x10
00559213  6a00                     push       0
00559215  6a00                     push       0
00559217  6a00                     push       0
00559219  688c0000c0               push       0xc000008c
0055921e  ffd3                     call       ebx
00559220  8b4f08                   mov        ecx, dword ptr [edi + 8]
00559223  8b04b1                   mov        eax, dword ptr [ecx + esi*4]
00559226  85c0                     test       eax, eax
00559228  8945fc                   mov        dword ptr [ebp - 4], eax
0055922b  746b                     je         0x559298
0055922d  8b9028030000             mov        edx, dword ptr [eax + 0x328]
