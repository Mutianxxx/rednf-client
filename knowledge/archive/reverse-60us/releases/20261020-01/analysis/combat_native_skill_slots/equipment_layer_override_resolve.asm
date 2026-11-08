004acd30  55                       push       ebp
004acd31  8bec                     mov        ebp, esp
004acd33  83ec10                   sub        esp, 0x10
004acd36  53                       push       ebx
004acd37  56                       push       esi
004acd38  57                       push       edi
004acd39  894df4                   mov        dword ptr [ebp - 0xc], ecx
004acd3c  8d81ec140000             lea        eax, [ecx + 0x14ec]
004acd42  be13000000               mov        esi, 0x13
004acd47  8b10                     mov        edx, dword ptr [eax]
004acd49  33ff                     xor        edi, edi
004acd4b  3bd7                     cmp        edx, edi
004acd4d  7418                     je         0x4acd67
004acd4f  c6828c07000001           mov        byte ptr [edx + 0x78c], 1
004acd56  8b10                     mov        edx, dword ptr [eax]
004acd58  c6828d07000000           mov        byte ptr [edx + 0x78d], 0
004acd5f  8b10                     mov        edx, dword ptr [eax]
004acd61  89baa0070000             mov        dword ptr [edx + 0x7a0], edi
004acd67  83c004                   add        eax, 4
004acd6a  4e                       dec        esi
004acd6b  75da                     jne        0x4acd47
004acd6d  8d81ec140000             lea        eax, [ecx + 0x14ec]
004acd73  897df8                   mov        dword ptr [ebp - 8], edi
004acd76  8945fc                   mov        dword ptr [ebp - 4], eax
004acd79  8da42400000000           lea        esp, [esp]
004acd80  8b45fc                   mov        eax, dword ptr [ebp - 4]
004acd83  8b00                     mov        eax, dword ptr [eax]
004acd85  83cfff                   or         edi, 0xffffffff
004acd88  83ceff                   or         esi, 0xffffffff
004acd8b  85c0                     test       eax, eax
004acd8d  8945f0                   mov        dword ptr [ebp - 0x10], eax
004acd90  7402                     je         0x4acd94
004acd92  33ff                     xor        edi, edi
004acd94  33d2                     xor        edx, edx
004acd96  8d99ec140000             lea        ebx, [ecx + 0x14ec]
004acd9c  8d642400                 lea        esp, [esp]
004acda0  8b03                     mov        eax, dword ptr [ebx]
004acda2  85c0                     test       eax, eax
004acda4  741c                     je         0x4acdc2
004acda6  8b4df8                   mov        ecx, dword ptr [ebp - 8]
004acda9  3b8890070000             cmp        ecx, dword ptr [eax + 0x790]
004acdaf  750e                     jne        0x4acdbf
004acdb1  8b8094070000             mov        eax, dword ptr [eax + 0x794]
004acdb7  3bf8                     cmp        edi, eax
004acdb9  7d04                     jge        0x4acdbf
004acdbb  8bf8                     mov        edi, eax
004acdbd  8bf2                     mov        esi, edx
004acdbf  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004acdc2  42                       inc        edx
004acdc3  83c304                   add        ebx, 4
004acdc6  83fa13                   cmp        edx, 0x13
004acdc9  7cd5                     jl         0x4acda0
004acdcb  85f6                     test       esi, esi
004acdcd  7c3f                     jl         0x4ace0e
004acdcf  8b84b1ec140000           mov        eax, dword ptr [ecx + esi*4 + 0x14ec]
004acdd6  85c0                     test       eax, eax
004acdd8  7434                     je         0x4ace0e
004acdda  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004acddd  85c0                     test       eax, eax
004acddf  741f                     je         0x4ace00
004acde1  c6808c07000000           mov        byte ptr [eax + 0x78c], 0
004acde8  8b94b1ec140000           mov        edx, dword ptr [ecx + esi*4 + 0x14ec]
004acdef  8b45fc                   mov        eax, dword ptr [ebp - 4]
004acdf2  8b00                     mov        eax, dword ptr [eax]
004acdf4  81c27c070000             add        edx, 0x77c
004acdfa  8990a0070000             mov        dword ptr [eax + 0x7a0], edx
004ace00  8b94b1ec140000           mov        edx, dword ptr [ecx + esi*4 + 0x14ec]
004ace07  c6828d07000001           mov        byte ptr [edx + 0x78d], 1
004ace0e  8b45f8                   mov        eax, dword ptr [ebp - 8]
004ace11  8b75fc                   mov        esi, dword ptr [ebp - 4]
004ace14  40                       inc        eax
004ace15  83c604                   add        esi, 4
004ace18  83f813                   cmp        eax, 0x13
004ace1b  8945f8                   mov        dword ptr [ebp - 8], eax
004ace1e  8975fc                   mov        dword ptr [ebp - 4], esi
004ace21  0f8c59ffffff             jl         0x4acd80
004ace27  5f                       pop        edi
004ace28  5e                       pop        esi
004ace29  5b                       pop        ebx
004ace2a  8be5                     mov        esp, ebp
004ace2c  5d                       pop        ebp
004ace2d  c3                       ret        
