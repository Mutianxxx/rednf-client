004daaf0  8d8ef01b0000             lea        ecx, [esi + 0x1bf0]
004daaf6  894de8                   mov        dword ptr [ebp - 0x18], ecx
004daaf9  8d8b780b0000             lea        ecx, [ebx + 0xb78]
004daaff  894d0c                   mov        dword ptr [ebp + 0xc], ecx
004dab02  c745e404000000           mov        dword ptr [ebp - 0x1c], 4
004dab09  8da42400000000           lea        esp, [esp]
004dab10  83c1f0                   add        ecx, -0x10
004dab13  68e0baca00               push       0xcabae0
004dab18  e8d3855700               call       0xa530f0
004dab1d  50                       push       eax
004dab1e  e8c8627200               call       0xc00deb
004dab23  83c408                   add        esp, 8
004dab26  85c0                     test       eax, eax
004dab28  0f84c8000000             je         0x4dabf6
004dab2e  68e8010000               push       0x1e8
004dab33  e81891f2ff               call       0x403c50
004dab38  83c404                   add        esp, 4
004dab3b  8945e0                   mov        dword ptr [ebp - 0x20], eax
004dab3e  85c0                     test       eax, eax
004dab40  c745fc09000000           mov        dword ptr [ebp - 4], 9
004dab47  0f8497000000             je         0x4dabe4
004dab4d  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004dab50  81c1040c0000             add        ecx, 0xc04
004dab56  e895855700               call       0xa530f0
004dab5b  8b968c260000             mov        edx, dword ptr [esi + 0x268c]
004dab61  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004dab67  8d9e8c260000             lea        ebx, [esi + 0x268c]
004dab6d  33d7                     xor        edx, edi
004dab6f  8945f0                   mov        dword ptr [ebp - 0x10], eax
004dab72  8b4304                   mov        eax, dword ptr [ebx + 4]
004dab75  2bd3                     sub        edx, ebx
004dab77  3bd0                     cmp        edx, eax
004dab79  740e                     je         0x4dab89
004dab7b  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004dab81  6a3f                     push       0x3f
004dab83  53                       push       ebx
004dab84  e827c56300               call       0xb170b0
004dab89  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004dab8f  8b4a44                   mov        ecx, dword ptr [edx + 0x44]
004dab92  8b4304                   mov        eax, dword ptr [ebx + 4]
004dab95  c1e002                   shl        eax, 2
004dab98  8d3c08                   lea        edi, [eax + ecx]
004dab9b  333c08                   xor        edi, dword ptr [eax + ecx]
004dab9e  333ddc012101             xor        edi, dword ptr [0x12101dc]
004daba4  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
004daba7  8d1408                   lea        edx, [eax + ecx]
004dabaa  331408                   xor        edx, dword ptr [eax + ecx]
004dabad  3315dc012101             xor        edx, dword ptr [0x12101dc]
004dabb3  3bfa                     cmp        edi, edx
004dabb5  740e                     je         0x4dabc5
004dabb7  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004dabbd  6a40                     push       0x40
004dabbf  53                       push       ebx
004dabc0  e8ebc46300               call       0xb170b0
004dabc5  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004dabc8  6a01                     push       1
004dabca  83c1f0                   add        ecx, -0x10
004dabcd  e81e855700               call       0xa530f0
004dabd2  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004dabd5  50                       push       eax
004dabd6  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004dabd9  50                       push       eax
004dabda  6a00                     push       0
004dabdc  57                       push       edi
004dabdd  e89e7ff9ff               call       0x472b80
004dabe2  eb02                     jmp        0x4dabe6
004dabe4  33c0                     xor        eax, eax
004dabe6  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004dabe9  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004dabec  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004dabf3  8941f0                   mov        dword ptr [ecx - 0x10], eax
004dabf6  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004dabf9  68e0baca00               push       0xcabae0
004dabfe  e8ed845700               call       0xa530f0
004dac03  50                       push       eax
004dac04  e8e2617200               call       0xc00deb
004dac09  83c408                   add        esp, 8
004dac0c  85c0                     test       eax, eax
004dac0e  0f84c4000000             je         0x4dacd8
004dac14  68e8010000               push       0x1e8
004dac19  e83290f2ff               call       0x403c50
004dac1e  83c404                   add        esp, 4
004dac21  8945e0                   mov        dword ptr [ebp - 0x20], eax
004dac24  85c0                     test       eax, eax
004dac26  c745fc0a000000           mov        dword ptr [ebp - 4], 0xa
004dac2d  0f8494000000             je         0x4dacc7
004dac33  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004dac36  81c1040c0000             add        ecx, 0xc04
004dac3c  e8af845700               call       0xa530f0
004dac41  8b968c260000             mov        edx, dword ptr [esi + 0x268c]
004dac47  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004dac4d  8d9e8c260000             lea        ebx, [esi + 0x268c]
004dac53  33d7                     xor        edx, edi
004dac55  8945f0                   mov        dword ptr [ebp - 0x10], eax
004dac58  8b4304                   mov        eax, dword ptr [ebx + 4]
004dac5b  2bd3                     sub        edx, ebx
004dac5d  3bd0                     cmp        edx, eax
004dac5f  740e                     je         0x4dac6f
004dac61  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004dac67  6a3f                     push       0x3f
004dac69  53                       push       ebx
004dac6a  e841c46300               call       0xb170b0
004dac6f  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004dac75  8b4a44                   mov        ecx, dword ptr [edx + 0x44]
004dac78  8b4304                   mov        eax, dword ptr [ebx + 4]
004dac7b  c1e002                   shl        eax, 2
004dac7e  8d3c08                   lea        edi, [eax + ecx]
004dac81  333c08                   xor        edi, dword ptr [eax + ecx]
004dac84  333ddc012101             xor        edi, dword ptr [0x12101dc]
004dac8a  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
004dac8d  8d1408                   lea        edx, [eax + ecx]
004dac90  331408                   xor        edx, dword ptr [eax + ecx]
004dac93  3315dc012101             xor        edx, dword ptr [0x12101dc]
004dac99  3bfa                     cmp        edi, edx
004dac9b  740e                     je         0x4dacab
004dac9d  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004daca3  6a40                     push       0x40
004daca5  53                       push       ebx
004daca6  e805c46300               call       0xb170b0
004dacab  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004dacae  6a01                     push       1
004dacb0  e83b845700               call       0xa530f0
004dacb5  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004dacb8  50                       push       eax
004dacb9  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004dacbc  50                       push       eax
004dacbd  6a00                     push       0
004dacbf  57                       push       edi
004dacc0  e8bb7ef9ff               call       0x472b80
004dacc5  eb02                     jmp        0x4dacc9
004dacc7  33c0                     xor        eax, eax
004dacc9  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004daccc  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004daccf  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004dacd6  8901                     mov        dword ptr [ecx], eax
004dacd8  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004dacdb  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
004dacde  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
004dace1  83c104                   add        ecx, 4
004dace4  83c204                   add        edx, 4
004dace7  48                       dec        eax
004dace8  894d0c                   mov        dword ptr [ebp + 0xc], ecx
004daceb  8955e8                   mov        dword ptr [ebp - 0x18], edx
004dacee  8945e4                   mov        dword ptr [ebp - 0x1c], eax
004dacf1  0f8519feffff             jne        0x4dab10
004dacf7  8d                       .byte      0x8d
004dacf8  8b                       .byte      0x8b
004dacf9  880b                     mov        byte ptr [ebx], cl