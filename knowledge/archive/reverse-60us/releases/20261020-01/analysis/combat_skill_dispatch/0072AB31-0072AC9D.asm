0072ab31  8bce                     mov        ecx, esi
0072ab33  e85815d7ff               call       0x49c090
0072ab38  84c0                     test       al, al
0072ab3a  0f842f570000             je         0x73026f
0072ab40  83beb001000002           cmp        dword ptr [esi + 0x1b0], 2
0072ab47  0f8422570000             je         0x73026f
0072ab4d  8dbe5c150000             lea        edi, [esi + 0x155c]
0072ab53  8bcf                     mov        ecx, edi
0072ab55  e80675cdff               call       0x402060
0072ab5a  85c0                     test       eax, eax
0072ab5c  741c                     je         0x72ab7a
0072ab5e  8bcf                     mov        ecx, edi
0072ab60  e8fb74cdff               call       0x402060
0072ab65  83f80b                   cmp        eax, 0xb
0072ab68  7410                     je         0x72ab7a
0072ab6a  8bcf                     mov        ecx, edi
0072ab6c  e8ef74cdff               call       0x402060
0072ab71  83f808                   cmp        eax, 8
0072ab74  0f85d1000000             jne        0x72ac4b
0072ab7a  8b06                     mov        eax, dword ptr [esi]
0072ab7c  8d96e4250000             lea        edx, [esi + 0x25e4]
0072ab82  52                       push       edx
0072ab83  6a01                     push       1
0072ab85  8bce                     mov        ecx, esi
0072ab87  ff903c070000             call       dword ptr [eax + 0x73c]
0072ab8d  8bc8                     mov        ecx, eax
0072ab8f  e8ace5e2ff               call       0x559140
0072ab94  83f8ff                   cmp        eax, -1
0072ab97  0f84ae000000             je         0x72ac4b
0072ab9d  8b16                     mov        edx, dword ptr [esi]
0072ab9f  6a01                     push       1
0072aba1  6a01                     push       1
0072aba3  6a01                     push       1
0072aba5  6a01                     push       1
0072aba7  8bce                     mov        ecx, esi
0072aba9  ff9268070000             call       dword ptr [edx + 0x768]
0072abaf  84c0                     test       al, al
0072abb1  0f8494000000             je         0x72ac4b
0072abb7  899dd8fcffff             mov        dword ptr [ebp - 0x328], ebx
0072abbd  899ddcfcffff             mov        dword ptr [ebp - 0x324], ebx
0072abc3  899de0fcffff             mov        dword ptr [ebp - 0x320], ebx
0072abc9  8d45ec                   lea        eax, [ebp - 0x14]
0072abcc  50                       push       eax
0072abcd  8d8dd4fcffff             lea        ecx, [ebp - 0x32c]
0072abd3  c745fc1c000000           mov        dword ptr [ebp - 4], 0x1c
0072abda  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072abdd  e83ec5cdff               call       0x407120
0072abe2  8d4dec                   lea        ecx, [ebp - 0x14]
0072abe5  51                       push       ecx
0072abe6  8d8dd4fcffff             lea        ecx, [ebp - 0x32c]
0072abec  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072abef  e82cc5cdff               call       0x407120
0072abf4  8d55ec                   lea        edx, [ebp - 0x14]
0072abf7  52                       push       edx
0072abf8  8d8dd4fcffff             lea        ecx, [ebp - 0x32c]
0072abfe  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072ac01  e81ac5cdff               call       0x407120
0072ac06  8b06                     mov        eax, dword ptr [esi]
0072ac08  8bce                     mov        ecx, esi
0072ac0a  ff90c0000000             call       dword ptr [eax + 0xc0]
0072ac10  8d4dec                   lea        ecx, [ebp - 0x14]
0072ac13  51                       push       ecx
0072ac14  8d8dd4fcffff             lea        ecx, [ebp - 0x32c]
0072ac1a  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072ac1d  e8fec4cdff               call       0x407120
0072ac22  8b16                     mov        edx, dword ptr [esi]
0072ac24  53                       push       ebx
0072ac25  53                       push       ebx
0072ac26  6a01                     push       1
0072ac28  8d85d4fcffff             lea        eax, [ebp - 0x32c]
0072ac2e  50                       push       eax
0072ac2f  6a13                     push       0x13
0072ac31  8bce                     mov        ecx, esi
0072ac33  ff928c020000             call       dword ptr [edx + 0x28c]
0072ac39  8d8dd4fcffff             lea        ecx, [ebp - 0x32c]
0072ac3f  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0072ac46  e805a1f1ff               call       0x644d50
0072ac4b  8bcf                     mov        ecx, edi
0072ac4d  e80e74cdff               call       0x402060
0072ac52  83f813                   cmp        eax, 0x13
0072ac55  7546                     jne        0x72ac9d
0072ac57  399ec02e0000             cmp        dword ptr [esi + 0x2ec0], ebx
0072ac5d  753e                     jne        0x72ac9d
0072ac5f  8d8e64150000             lea        ecx, [esi + 0x1564]
0072ac65  e896c23d00               call       0xb06f00
0072ac6a  3b86c42e0000             cmp        eax, dword ptr [esi + 0x2ec4]
0072ac70  7c2b                     jl         0x72ac9d
0072ac72  8b16                     mov        edx, dword ptr [esi]
0072ac74  8bce                     mov        ecx, esi
0072ac76  ff9238070000             call       dword ptr [edx + 0x738]
0072ac7c  8b10                     mov        edx, dword ptr [eax]
0072ac7e  8d8ee4250000             lea        ecx, [esi + 0x25e4]
0072ac84  51                       push       ecx
0072ac85  8bc8                     mov        ecx, eax
0072ac87  ff5238                   call       dword ptr [edx + 0x38]
0072ac8a  84c0                     test       al, al
0072ac8c  750f                     jne        0x72ac9d
0072ac8e  8b16                     mov        edx, dword ptr [esi]
0072ac90  53                       push       ebx
0072ac91  53                       push       ebx
0072ac92  53                       push       ebx
0072ac93  53                       push       ebx
0072ac94  53                       push       ebx
0072ac95  8bce                     mov        ecx, esi
0072ac97  ff928c020000             call       dword ptr [edx + 0x28c]