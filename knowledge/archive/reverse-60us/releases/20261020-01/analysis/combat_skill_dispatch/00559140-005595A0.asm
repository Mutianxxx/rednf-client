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
00559233  8d9828030000             lea        ebx, [eax + 0x328]
00559239  3315dc012101             xor        edx, dword ptr [0x12101dc]
0055923f  8b4304                   mov        eax, dword ptr [ebx + 4]
00559242  2bd3                     sub        edx, ebx
00559244  3bd0                     cmp        edx, eax
00559246  740e                     je         0x559256
00559248  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0055924e  6a3f                     push       0x3f
00559250  53                       push       ebx
00559251  e85ade5b00               call       0xb170b0
00559256  8b4304                   mov        eax, dword ptr [ebx + 4]
00559259  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0055925f  8b5144                   mov        edx, dword ptr [ecx + 0x44]
00559262  c1e002                   shl        eax, 2
00559265  03d0                     add        edx, eax
00559267  8bda                     mov        ebx, edx
00559269  331ddc012101             xor        ebx, dword ptr [0x12101dc]
0055926f  331a                     xor        ebx, dword ptr [edx]
00559271  8b5148                   mov        edx, dword ptr [ecx + 0x48]
00559274  03c2                     add        eax, edx
00559276  8bd0                     mov        edx, eax
00559278  3315dc012101             xor        edx, dword ptr [0x12101dc]
0055927e  3310                     xor        edx, dword ptr [eax]
00559280  3bda                     cmp        ebx, edx
00559282  7410                     je         0x559294
00559284  8b45fc                   mov        eax, dword ptr [ebp - 4]
00559287  6a40                     push       0x40
00559289  0528030000               add        eax, 0x328
0055928e  50                       push       eax
0055928f  e81cde5b00               call       0xb170b0
00559294  85db                     test       ebx, ebx
00559296  750c                     jne        0x5592a4
00559298  5f                       pop        edi
00559299  5e                       pop        esi
0055929a  83c8ff                   or         eax, 0xffffffff
0055929d  5b                       pop        ebx
0055929e  8be5                     mov        esp, ebp
005592a0  5d                       pop        ebp
005592a1  c20800                   ret        8
005592a4  8b471c                   mov        eax, dword ptr [edi + 0x1c]
005592a7  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
005592aa  50                       push       eax
005592ab  8bcb                     mov        ecx, ebx
005592ad  e80e5effff               call       0x54f0c0
005592b2  83f8ff                   cmp        eax, -1
005592b5  8945fc                   mov        dword ptr [ebp - 4], eax
005592b8  0f84ff000000             je         0x5593bd
005592be  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
005592c1  85c9                     test       ecx, ecx
005592c3  741b                     je         0x5592e0
005592c5  85c0                     test       eax, eax
005592c7  8b83ac030000             mov        eax, dword ptr [ebx + 0x3ac]
005592cd  7503                     jne        0x5592d2
005592cf  83c02c                   add        eax, 0x2c
005592d2  8b571c                   mov        edx, dword ptr [edi + 0x1c]
005592d5  52                       push       edx
005592d6  50                       push       eax
005592d7  51                       push       ecx
005592d8  e8e3fdffff               call       0x5590c0
005592dd  83c40c                   add        esp, 0xc
005592e0  8d8b04030000             lea        ecx, [ebx + 0x304]
005592e6  e8758deaff               call       0x402060
005592eb  85c0                     test       eax, eax
005592ed  7f0f                     jg         0x5592fe
005592ef  8d8b0c030000             lea        ecx, [ebx + 0x30c]
005592f5  e8668deaff               call       0x402060
005592fa  85c0                     test       eax, eax
005592fc  7e41                     jle        0x55933f
005592fe  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00559304  8b5144                   mov        edx, dword ptr [ecx + 0x44]
00559307  8b83dc030000             mov        eax, dword ptr [ebx + 0x3dc]
0055930d  8b35dc012101             mov        esi, dword ptr [0x12101dc]
00559313  8d0482                   lea        eax, [edx + eax*4]
00559316  8bc8                     mov        ecx, eax
00559318  33ce                     xor        ecx, esi
0055931a  83f101                   xor        ecx, 1
0055931d  8908                     mov        dword ptr [eax], ecx
0055931f  a1d8012101               mov        eax, dword ptr [0x12101d8]
00559324  8b93dc030000             mov        edx, dword ptr [ebx + 0x3dc]
0055932a  8b4848                   mov        ecx, dword ptr [eax + 0x48]
0055932d  8b35dc012101             mov        esi, dword ptr [0x12101dc]
00559333  8d0491                   lea        eax, [ecx + edx*4]
00559336  8bd0                     mov        edx, eax
00559338  33d6                     xor        edx, esi
0055933a  83f201                   xor        edx, 1
0055933d  8910                     mov        dword ptr [eax], edx
0055933f  837dfc04                 cmp        dword ptr [ebp - 4], 4
00559343  7543                     jne        0x559388
00559345  8b4718                   mov        eax, dword ptr [edi + 0x18]
00559348  85c0                     test       eax, eax
0055934a  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
00559350  8bd0                     mov        edx, eax
00559352  7502                     jne        0x559356
00559354  8bd1                     mov        edx, ecx
00559356  85d2                     test       edx, edx
00559358  742e                     je         0x559388
0055935a  85c0                     test       eax, eax
0055935c  7402                     je         0x559360
0055935e  8bc8                     mov        ecx, eax
00559360  8b01                     mov        eax, dword ptr [ecx]
00559362  6a00                     push       0
00559364  ff9044060000             call       dword ptr [eax + 0x644]
0055936a  83f804                   cmp        eax, 4
0055936d  7516                     jne        0x559385
0055936f  8b4718                   mov        eax, dword ptr [edi + 0x18]
00559372  85c0                     test       eax, eax
00559374  7505                     jne        0x55937b
00559376  a1d4f10401               mov        eax, dword ptr [0x104f1d4]
0055937b  8b10                     mov        edx, dword ptr [eax]
0055937d  8bc8                     mov        ecx, eax
0055937f  ff92c0000000             call       dword ptr [edx + 0xc0]
00559385  8945fc                   mov        dword ptr [ebp - 4], eax
00559388  8b4508                   mov        eax, dword ptr [ebp + 8]
0055938b  3b4734                   cmp        eax, dword ptr [edi + 0x34]
0055938e  7521                     jne        0x5593b1
00559390  c74734ffffffff           mov        dword ptr [edi + 0x34], 0xffffffff
00559397  8b7f18                   mov        edi, dword ptr [edi + 0x18]
0055939a  85ff                     test       edi, edi
0055939c  8bcf                     mov        ecx, edi
0055939e  7506                     jne        0x5593a6
005593a0  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
005593a6  8b11                     mov        edx, dword ptr [ecx]
005593a8  ff92c0000000             call       dword ptr [edx + 0xc0]
005593ae  8945fc                   mov        dword ptr [ebp - 4], eax
005593b1  8b45fc                   mov        eax, dword ptr [ebp - 4]
005593b4  5f                       pop        edi
005593b5  5e                       pop        esi
005593b6  5b                       pop        ebx
005593b7  8be5                     mov        esp, ebp
005593b9  5d                       pop        ebp
005593ba  c20800                   ret        8
005593bd  83fe06                   cmp        esi, 6
005593c0  0f8d9c000000             jge        0x559462
005593c6  56                       push       esi
005593c7  8d45f0                   lea        eax, [ebp - 0x10]
005593ca  8d5f28                   lea        ebx, [edi + 0x28]
005593cd  50                       push       eax
005593ce  8bcb                     mov        ecx, ebx
005593d0  e8cb030000               call       0x5597a0
005593d5  8b5004                   mov        edx, dword ptr [eax + 4]
005593d8  b901000000               mov        ecx, 1
005593dd  894df8                   mov        dword ptr [ebp - 8], ecx
005593e0  8b08                     mov        ecx, dword ptr [eax]
005593e2  8b45f8                   mov        eax, dword ptr [ebp - 8]
005593e5  d3e0                     shl        eax, cl
005593e7  8502                     test       dword ptr [edx], eax
005593e9  7477                     je         0x559462
005593eb  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
005593ee  85c9                     test       ecx, ecx
005593f0  c745fc04000000           mov        dword ptr [ebp - 4], 4
005593f7  0f8448ffffff             je         0x559345
005593fd  e86e97efff               call       0x452b70
00559402  56                       push       esi
00559403  8d45f0                   lea        eax, [ebp - 0x10]
00559406  50                       push       eax
00559407  8bcb                     mov        ecx, ebx
00559409  e892030000               call       0x5597a0
0055940e  8b08                     mov        ecx, dword ptr [eax]
00559410  8b5004                   mov        edx, dword ptr [eax + 4]
00559413  8b02                     mov        eax, dword ptr [edx]
00559415  bb01000000               mov        ebx, 1
0055941a  d3e3                     shl        ebx, cl
0055941c  85c3                     test       ebx, eax
0055941e  0f8421ffffff             je         0x559345
00559424  8b4f18                   mov        ecx, dword ptr [edi + 0x18]
00559427  85c9                     test       ecx, ecx
00559429  7420                     je         0x55944b
0055942b  8b01                     mov        eax, dword ptr [ecx]
0055942d  ff5034                   call       dword ptr [eax + 0x34]
00559430  84c0                     test       al, al
00559432  7417                     je         0x55944b
00559434  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00559437  c1e604                   shl        esi, 4
0055943a  81c62846f400             add        esi, 0xf44628
00559440  56                       push       esi
00559441  e87a66fdff               call       0x52fac0
00559446  e9fafeffff               jmp        0x559345
0055944b  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0055944e  c1e604                   shl        esi, 4
00559451  81c66845f400             add        esi, 0xf44568
00559457  56                       push       esi
00559458  e86366fdff               call       0x52fac0
0055945d  e9e3feffff               jmp        0x559345
00559462  81fed8000000             cmp        esi, 0xd8
00559468  0f8c1affffff             jl         0x559388
0055946e  81fede000000             cmp        esi, 0xde
00559474  0f8d0effffff             jge        0x559388
0055947a  8d9e28ffffff             lea        ebx, [esi - 0xd8]
00559480  53                       push       ebx
00559481  8d55f0                   lea        edx, [ebp - 0x10]
00559484  8d4f30                   lea        ecx, [edi + 0x30]
00559487  52                       push       edx
00559488  e813030000               call       0x5597a0
0055948d  8b5004                   mov        edx, dword ptr [eax + 4]
00559490  b901000000               mov        ecx, 1
00559495  894df8                   mov        dword ptr [ebp - 8], ecx
00559498  8b08                     mov        ecx, dword ptr [eax]
0055949a  8b45f8                   mov        eax, dword ptr [ebp - 8]
0055949d  d3e0                     shl        eax, cl
0055949f  8502                     test       dword ptr [edx], eax
005594a1  0f84e1feffff             je         0x559388
005594a7  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
005594aa  85c9                     test       ecx, ecx
005594ac  c745fc04000000           mov        dword ptr [ebp - 4], 4
005594b3  0f848cfeffff             je         0x559345
005594b9  e8b296efff               call       0x452b70
005594be  53                       push       ebx
005594bf  8d45f0                   lea        eax, [ebp - 0x10]
005594c2  50                       push       eax
005594c3  8d4f30                   lea        ecx, [edi + 0x30]
005594c6  e8d5020000               call       0x5597a0
005594cb  8b08                     mov        ecx, dword ptr [eax]
005594cd  8b5004                   mov        edx, dword ptr [eax + 4]
005594d0  8b02                     mov        eax, dword ptr [edx]
005594d2  bb01000000               mov        ebx, 1
005594d7  d3e3                     shl        ebx, cl
005594d9  85c3                     test       ebx, eax
005594db  0f8464feffff             je         0x559345
005594e1  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
005594e4  81c628ffffff             add        esi, 0xffffff28
005594ea  c1e604                   shl        esi, 4
005594ed  81c6c845f400             add        esi, 0xf445c8
005594f3  56                       push       esi
005594f4  e8c765fdff               call       0x52fac0
005594f9  e947feffff               jmp        0x559345
005594fe  cc                       int3       
005594ff  cc                       int3       
00559500  55                       push       ebp
00559501  8bec                     mov        ebp, esp
00559503  8b4508                   mov        eax, dword ptr [ebp + 8]
00559506  85c0                     test       eax, eax
00559508  7469                     je         0x559573
0055950a  56                       push       esi
0055950b  7d3b                     jge        0x559548
0055950d  8b11                     mov        edx, dword ptr [ecx]
0055950f  8bf0                     mov        esi, eax
00559511  f7de                     neg        esi
00559513  3bd6                     cmp        edx, esi
00559515  7d31                     jge        0x559548
00559517  03c2                     add        eax, edx
00559519  83caff                   or         edx, 0xffffffff
0055951c  2bd0                     sub        edx, eax
0055951e  c1ea05                   shr        edx, 5
00559521  c1e202                   shl        edx, 2
00559524  befcffffff               mov        esi, 0xfffffffc
00559529  2bf2                     sub        esi, edx
0055952b  8b5104                   mov        edx, dword ptr [ecx + 4]
0055952e  03d6                     add        edx, esi
00559530  251f000080               and        eax, 0x8000001f
00559535  895104                   mov        dword ptr [ecx + 4], edx
00559538  7905                     jns        0x55953f
0055953a  48                       dec        eax
0055953b  83c8e0                   or         eax, 0xffffffe0
0055953e  40                       inc        eax
0055953f  8901                     mov        dword ptr [ecx], eax
00559541  5e                       pop        esi
00559542  8bc1                     mov        eax, ecx
00559544  5d                       pop        ebp
00559545  c20400                   ret        4
00559548  8b11                     mov        edx, dword ptr [ecx]
0055954a  8d3402                   lea        esi, [edx + eax]
0055954d  8bc6                     mov        eax, esi
0055954f  99                       cdq        
00559550  83e21f                   and        edx, 0x1f
00559553  03c2                     add        eax, edx
00559555  8b5104                   mov        edx, dword ptr [ecx + 4]
00559558  c1f805                   sar        eax, 5
0055955b  c1e002                   shl        eax, 2
0055955e  03d0                     add        edx, eax
00559560  81e61f000080             and        esi, 0x8000001f
00559566  895104                   mov        dword ptr [ecx + 4], edx
00559569  7905                     jns        0x559570
0055956b  4e                       dec        esi
0055956c  83cee0                   or         esi, 0xffffffe0
0055956f  46                       inc        esi
00559570  8931                     mov        dword ptr [ecx], esi
00559572  5e                       pop        esi
00559573  8bc1                     mov        eax, ecx
00559575  5d                       pop        ebp
00559576  c20400                   ret        4
00559579  cc                       int3       
0055957a  cc                       int3       
0055957b  cc                       int3       
0055957c  cc                       int3       
0055957d  cc                       int3       
0055957e  cc                       int3       
0055957f  cc                       int3       
00559580  55                       push       ebp
00559581  8bec                     mov        ebp, esp
00559583  56                       push       esi
00559584  8bf1                     mov        esi, ecx
00559586  8b4604                   mov        eax, dword ptr [esi + 4]
00559589  8b4e08                   mov        ecx, dword ptr [esi + 8]
0055958c  2bc8                     sub        ecx, eax
0055958e  b8abaaaa2a               mov        eax, 0x2aaaaaab
00559593  f7e9                     imul       ecx
00559595  c1fa02                   sar        edx, 2
00559598  8bc2                     mov        eax, edx
0055959a  c1e81f                   shr        eax, 0x1f
0055959d  57                       push       edi
0055959e  8b                       .byte      0x8b
0055959f  7d                       .byte      0x7d