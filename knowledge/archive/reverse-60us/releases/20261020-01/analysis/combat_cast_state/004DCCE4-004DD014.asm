004dcce4  8dbe20240000             lea        edi, [esi + 0x2420]
004dccea  8bcf                     mov        ecx, edi
004dccec  e86f53f2ff               call       0x402060
004dccf1  85c0                     test       eax, eax
004dccf3  0f85f6000000             jne        0x4dcdef
004dccf9  8bce                     mov        ecx, esi
004dccfb  e890f3fbff               call       0x49c090
004dcd00  84c0                     test       al, al
004dcd02  0f8427070000             je         0x4dd42f
004dcd08  8dbe34240000             lea        edi, [esi + 0x2434]
004dcd0e  8bcf                     mov        ecx, edi
004dcd10  e84b53f2ff               call       0x402060
004dcd15  83f8ff                   cmp        eax, -1
004dcd18  0f8411070000             je         0x4dd42f
004dcd1e  8d8e64150000             lea        ecx, [esi + 0x1564]
004dcd24  e8d7a16200               call       0xb06f00
004dcd29  8bcf                     mov        ecx, edi
004dcd2b  8bd8                     mov        ebx, eax
004dcd2d  e82e53f2ff               call       0x402060
004dcd32  3bd8                     cmp        ebx, eax
004dcd34  0f8cf5060000             jl         0x4dd42f
004dcd3a  8d8e50240000             lea        ecx, [esi + 0x2450]
004dcd40  e81b53f2ff               call       0x402060
004dcd45  83f8ff                   cmp        eax, -1
004dcd48  7513                     jne        0x4dcd5d
004dcd4a  8b06                     mov        eax, dword ptr [esi]
004dcd4c  6a00                     push       0
004dcd4e  6a01                     push       1
004dcd50  8bce                     mov        ecx, esi
004dcd52  ff9084070000             call       dword ptr [eax + 0x784]
004dcd58  e9d2060000               jmp        0x4dd42f
004dcd5d  33ff                     xor        edi, edi
004dcd5f  897de4                   mov        dword ptr [ebp - 0x1c], edi
004dcd62  897de8                   mov        dword ptr [ebp - 0x18], edi
004dcd65  897dec                   mov        dword ptr [ebp - 0x14], edi
004dcd68  8d4de0                   lea        ecx, [ebp - 0x20]
004dcd6b  51                       push       ecx
004dcd6c  8d8e2c240000             lea        ecx, [esi + 0x242c]
004dcd72  c745fc05000000           mov        dword ptr [ebp - 4], 5
004dcd79  e8e252f2ff               call       0x402060
004dcd7e  50                       push       eax
004dcd7f  8bce                     mov        ecx, esi
004dcd81  e82a91ffff               call       0x4d5eb0
004dcd86  8d4de0                   lea        ecx, [ebp - 0x20]
004dcd89  e8d2570000               call       0x4e2560
004dcd8e  84c0                     test       al, al
004dcd90  7405                     je         0x4dcd97
004dcd92  57                       push       edi
004dcd93  6a01                     push       1
004dcd95  eb3a                     jmp        0x4dcdd1
004dcd97  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004dcd9a  3bcf                     cmp        ecx, edi
004dcd9c  7430                     je         0x4dcdce
004dcd9e  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004dcda1  2bc1                     sub        eax, ecx
004dcda3  c1f802                   sar        eax, 2
004dcda6  83f801                   cmp        eax, 1
004dcda9  7523                     jne        0x4dcdce
004dcdab  8b09                     mov        ecx, dword ptr [ecx]
004dcdad  8b06                     mov        eax, dword ptr [esi]
004dcdaf  51                       push       ecx
004dcdb0  6a01                     push       1
004dcdb2  8bce                     mov        ecx, esi
004dcdb4  ff9084070000             call       dword ptr [eax + 0x784]
004dcdba  8d4de0                   lea        ecx, [ebp - 0x20]
004dcdbd  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004dcdc4  e8877f1600               call       0x644d50
004dcdc9  e961060000               jmp        0x4dd42f
004dcdce  57                       push       edi
004dcdcf  6a02                     push       2
004dcdd1  8b16                     mov        edx, dword ptr [esi]
004dcdd3  8bce                     mov        ecx, esi
004dcdd5  ff9284070000             call       dword ptr [edx + 0x784]
004dcddb  8d4de0                   lea        ecx, [ebp - 0x20]
004dcdde  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004dcde5  e8667f1600               call       0x644d50
004dcdea  e940060000               jmp        0x4dd42f
004dcdef  8bcf                     mov        ecx, edi
004dcdf1  e86a52f2ff               call       0x402060
004dcdf6  83f801                   cmp        eax, 1
004dcdf9  0f8515020000             jne        0x4dd014
004dcdff  8a866c240000             mov        al, byte ptr [esi + 0x246c]
004dce05  84c0                     test       al, al
004dce07  0f855f010000             jne        0x4dcf6c
004dce0d  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004dce13  85c9                     test       ecx, ecx
004dce15  0f8451010000             je         0x4dcf6c
004dce1b  8b8628240000             mov        eax, dword ptr [esi + 0x2428]
004dce21  83f802                   cmp        eax, 2
004dce24  741b                     je         0x4dce41
004dce26  83f801                   cmp        eax, 1
004dce29  0f853d010000             jne        0x4dcf6c
004dce2f  8b8924010000             mov        ecx, dword ptr [ecx + 0x124]
004dce35  3b8e78240000             cmp        ecx, dword ptr [esi + 0x2478]
004dce3b  0f8c2b010000             jl         0x4dcf6c
004dce41  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004dce47  741e                     je         0x4dce67
004dce49  8bce                     mov        ecx, esi
004dce4b  e840f2fbff               call       0x49c090
004dce50  84c0                     test       al, al
004dce52  0f84a2000000             je         0x4dcefa
004dce58  8b06                     mov        eax, dword ptr [esi]
004dce5a  8bce                     mov        ecx, esi
004dce5c  ff5034                   call       dword ptr [eax + 0x34]
004dce5f  84c0                     test       al, al
004dce61  0f8493000000             je         0x4dcefa
004dce67  8b8644270000             mov        eax, dword ptr [esi + 0x2744]
004dce6d  85c0                     test       eax, eax
004dce6f  0f8485000000             je         0x4dcefa
004dce75  8d8e2c240000             lea        ecx, [esi + 0x242c]
004dce7b  e8e051f2ff               call       0x402060
004dce80  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004dce86  50                       push       eax
004dce87  e89407faff               call       0x47d620
004dce8c  8bf8                     mov        edi, eax
004dce8e  83ffff                   cmp        edi, -1
004dce91  7451                     je         0x4dcee4
004dce93  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004dce99  57                       push       edi
004dce9a  e81176f2ff               call       0x4044b0
004dce9f  8b10                     mov        edx, dword ptr [eax]
004dcea1  8bc8                     mov        ecx, eax
004dcea3  ff5230                   call       dword ptr [edx + 0x30]
004dcea6  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004dceac  8bd8                     mov        ebx, eax
004dceae  e8ed2cf3ff               call       0x40fba0
004dceb3  3bd8                     cmp        ebx, eax
004dceb5  762d                     jbe        0x4dcee4
004dceb7  8b8698240000             mov        eax, dword ptr [esi + 0x2498]
004dcebd  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004dcec3  50                       push       eax
004dcec4  57                       push       edi
004dcec5  e84631faff               call       0x480010
004dceca  84c0                     test       al, al
004dcecc  752c                     jne        0x4dcefa
004dcece  8b16                     mov        edx, dword ptr [esi]
004dced0  6a00                     push       0
004dced2  6a00                     push       0
004dced4  6a00                     push       0
004dced6  6a00                     push       0
004dced8  6a00                     push       0
004dceda  8bce                     mov        ecx, esi
004dcedc  ff928c020000             call       dword ptr [edx + 0x28c]
004dcee2  eb2b                     jmp        0x4dcf0f
004dcee4  8b06                     mov        eax, dword ptr [esi]
004dcee6  6a00                     push       0
004dcee8  6a00                     push       0
004dceea  6a00                     push       0
004dceec  6a00                     push       0
004dceee  6a00                     push       0
004dcef0  8bce                     mov        ecx, esi
004dcef2  ff908c020000             call       dword ptr [eax + 0x28c]
004dcef8  eb15                     jmp        0x4dcf0f
004dcefa  8bce                     mov        ecx, esi
004dcefc  e88ff1fbff               call       0x49c090
004dcf01  84c0                     test       al, al
004dcf03  740a                     je         0x4dcf0f
004dcf05  8b16                     mov        edx, dword ptr [esi]
004dcf07  8bce                     mov        ecx, esi
004dcf09  ff9218070000             call       dword ptr [edx + 0x718]
004dcf0f  8d8e2c240000             lea        ecx, [esi + 0x242c]
004dcf15  e84651f2ff               call       0x402060
004dcf1a  8b0dec300001             mov        ecx, dword ptr [0x10030ec]
004dcf20  50                       push       eax
004dcf21  e8fa455800               call       0xa61520
004dcf26  8bf8                     mov        edi, eax
004dcf28  85ff                     test       edi, edi
004dcf2a  742f                     je         0x4dcf5b
004dcf2c  8d8fc0000000             lea        ecx, [edi + 0xc0]
004dcf32  e85998f8ff               call       0x466790
004dcf37  83f801                   cmp        eax, 1
004dcf3a  761f                     jbe        0x4dcf5b
004dcf3c  8bbfc4000000             mov        edi, dword ptr [edi + 0xc4]
004dcf42  6a00                     push       0
004dcf44  6a00                     push       0
004dcf46  8d4f04                   lea        ecx, [edi + 4]
004dcf49  8b3e                     mov        edi, dword ptr [esi]
004dcf4b  6aff                     push       -1
004dcf4d  e89e615700               call       0xa530f0
004dcf52  50                       push       eax
004dcf53  8bce                     mov        ecx, esi
004dcf55  ff970c010000             call       dword ptr [edi + 0x10c]
004dcf5b  8b06                     mov        eax, dword ptr [esi]
004dcf5d  8bce                     mov        ecx, esi
004dcf5f  ff9070060000             call       dword ptr [eax + 0x670]
004dcf65  c6866c24000001           mov        byte ptr [esi + 0x246c], 1
004dcf6c  8b8628240000             mov        eax, dword ptr [esi + 0x2428]
004dcf72  83f802                   cmp        eax, 2
004dcf75  744a                     je         0x4dcfc1
004dcf77  83f801                   cmp        eax, 1
004dcf7a  7445                     je         0x4dcfc1
004dcf7c  8dbe3c240000             lea        edi, [esi + 0x243c]
004dcf82  8bcf                     mov        ecx, edi
004dcf84  e8d750f2ff               call       0x402060
004dcf89  83f8ff                   cmp        eax, -1
004dcf8c  0f849d040000             je         0x4dd42f
004dcf92  8d8e64150000             lea        ecx, [esi + 0x1564]
004dcf98  e8639f6200               call       0xb06f00
004dcf9d  8bcf                     mov        ecx, edi
004dcf9f  8bd8                     mov        ebx, eax
004dcfa1  e8ba50f2ff               call       0x402060
004dcfa6  3bd8                     cmp        ebx, eax
004dcfa8  0f8c81040000             jl         0x4dd42f
004dcfae  8b16                     mov        edx, dword ptr [esi]
004dcfb0  6a00                     push       0
004dcfb2  6aff                     push       -1
004dcfb4  8bce                     mov        ecx, esi
004dcfb6  ff9284070000             call       dword ptr [edx + 0x784]
004dcfbc  e96e040000               jmp        0x4dd42f
004dcfc1  8a866c240000             mov        al, byte ptr [esi + 0x246c]
004dcfc7  84c0                     test       al, al
004dcfc9  0f8460040000             je         0x4dd42f
004dcfcf  8dbe3c240000             lea        edi, [esi + 0x243c]
004dcfd5  8bcf                     mov        ecx, edi
004dcfd7  e88450f2ff               call       0x402060
004dcfdc  83f8ff                   cmp        eax, -1
004dcfdf  0f844a040000             je         0x4dd42f
004dcfe5  8d8e64150000             lea        ecx, [esi + 0x1564]
004dcfeb  e8109f6200               call       0xb06f00
004dcff0  8bcf                     mov        ecx, edi
004dcff2  8bd8                     mov        ebx, eax
004dcff4  e86750f2ff               call       0x402060
004dcff9  3bd8                     cmp        ebx, eax
004dcffb  0f8c2e040000             jl         0x4dd42f
004dd001  8b06                     mov        eax, dword ptr [esi]
004dd003  6a00                     push       0
004dd005  6aff                     push       -1
004dd007  8bce                     mov        ecx, esi
004dd009  ff9084070000             call       dword ptr [eax + 0x784]
004dd00f  e91b040000               jmp        0x4dd42f