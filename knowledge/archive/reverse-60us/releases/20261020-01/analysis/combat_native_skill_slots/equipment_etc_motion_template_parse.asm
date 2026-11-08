008679d5  8d4dac                   lea        ecx, [ebp - 0x54]
008679d8  688ce8e100               push       0xe1e88c
008679dd  51                       push       ecx
008679de  e8edcdb9ff               call       0x4047d0
008679e3  83c408                   add        esp, 8
008679e6  84c0                     test       al, al
008679e8  0f8497010000             je         0x867b85
008679ee  8a45f3                   mov        al, byte ptr [ebp - 0xd]
008679f1  84c0                     test       al, al
008679f3  0f84c6000000             je         0x867abf
008679f9  8bb5ccfeffff             mov        esi, dword ptr [ebp - 0x134]
008679ff  3bf3                     cmp        esi, ebx
00867a01  742c                     je         0x867a2f
00867a03  8b9dd0feffff             mov        ebx, dword ptr [ebp - 0x130]
00867a09  3bf3                     cmp        esi, ebx
00867a0b  7417                     je         0x867a24
00867a0d  8d4900                   lea        ecx, [ecx]
00867a10  8bce                     mov        ecx, esi
00867a12  e839ba1e00               call       0xa53450
00867a17  83c604                   add        esi, 4
00867a1a  3bf3                     cmp        esi, ebx
00867a1c  75f2                     jne        0x867a10
00867a1e  8bb5ccfeffff             mov        esi, dword ptr [ebp - 0x134]
00867a24  56                       push       esi
00867a25  e8b3853900               call       0xbfffdd
00867a2a  83c404                   add        esp, 4
00867a2d  33db                     xor        ebx, ebx
00867a2f  8d55cc                   lea        edx, [ebp - 0x34]
00867a32  52                       push       edx
00867a33  899dccfeffff             mov        dword ptr [ebp - 0x134], ebx
00867a39  899dd0feffff             mov        dword ptr [ebp - 0x130], ebx
00867a3f  899dd4feffff             mov        dword ptr [ebp - 0x12c], ebx
00867a45  e8c68cfcff               call       0x830710
00867a4a  83c404                   add        esp, 4
00867a4d  84c0                     test       al, al
00867a4f  0f8463070000             je         0x8681b8
00867a55  be08000000               mov        esi, 8
00867a5a  8d9b00000000             lea        ebx, [ebx]
00867a60  3975a0                   cmp        dword ptr [ebp - 0x60], esi
00867a63  8b4d8c                   mov        ecx, dword ptr [ebp - 0x74]
00867a66  7303                     jae        0x867a6b
00867a68  8d4d8c                   lea        ecx, [ebp - 0x74]
00867a6b  3975e4                   cmp        dword ptr [ebp - 0x1c], esi
00867a6e  8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00867a71  7303                     jae        0x867a76
00867a73  8d45d0                   lea        eax, [ebp - 0x30]
00867a76  51                       push       ecx
00867a77  50                       push       eax
00867a78  8d853cfaffff             lea        eax, [ebp - 0x5c4]
00867a7e  6800020000               push       0x200
00867a83  50                       push       eax
00867a84  e8f6a73900               call       0xc0227f
00867a89  83c410                   add        esp, 0x10
00867a8c  8d8d3cfaffff             lea        ecx, [ebp - 0x5c4]
00867a92  51                       push       ecx
00867a93  8d4dec                   lea        ecx, [ebp - 0x14]
00867a96  e805be1e00               call       0xa538a0
00867a9b  8d55ec                   lea        edx, [ebp - 0x14]
00867a9e  52                       push       edx
00867a9f  8d8dc8feffff             lea        ecx, [ebp - 0x138]
00867aa5  e836c1b9ff               call       0x403be0
00867aaa  8d45cc                   lea        eax, [ebp - 0x34]
00867aad  50                       push       eax
00867aae  e85d8cfcff               call       0x830710
00867ab3  83c404                   add        esp, 4
00867ab6  84c0                     test       al, al
00867ab8  75a6                     jne        0x867a60
00867aba  e9f9060000               jmp        0x8681b8
00867abf  8bb54cffffff             mov        esi, dword ptr [ebp - 0xb4]
00867ac5  3bf3                     cmp        esi, ebx
00867ac7  7429                     je         0x867af2
00867ac9  8b9d50ffffff             mov        ebx, dword ptr [ebp - 0xb0]
00867acf  3bf3                     cmp        esi, ebx
00867ad1  7414                     je         0x867ae7
00867ad3  8bce                     mov        ecx, esi
00867ad5  e876b91e00               call       0xa53450
00867ada  83c604                   add        esi, 4
00867add  3bf3                     cmp        esi, ebx
00867adf  75f2                     jne        0x867ad3
00867ae1  8bb54cffffff             mov        esi, dword ptr [ebp - 0xb4]
00867ae7  56                       push       esi
00867ae8  e8f0843900               call       0xbfffdd
00867aed  83c404                   add        esp, 4
00867af0  33db                     xor        ebx, ebx
00867af2  8d4dcc                   lea        ecx, [ebp - 0x34]
00867af5  51                       push       ecx
00867af6  899d4cffffff             mov        dword ptr [ebp - 0xb4], ebx
00867afc  899d50ffffff             mov        dword ptr [ebp - 0xb0], ebx
00867b02  899d54ffffff             mov        dword ptr [ebp - 0xac], ebx
00867b08  e8038cfcff               call       0x830710
00867b0d  83c404                   add        esp, 4
00867b10  84c0                     test       al, al
00867b12  0f84a0060000             je         0x8681b8
00867b18  be08000000               mov        esi, 8
00867b1d  8d4900                   lea        ecx, [ecx]
00867b20  397584                   cmp        dword ptr [ebp - 0x7c], esi
00867b23  8b8d70ffffff             mov        ecx, dword ptr [ebp - 0x90]
00867b29  7306                     jae        0x867b31
00867b2b  8d8d70ffffff             lea        ecx, [ebp - 0x90]
00867b31  3975e4                   cmp        dword ptr [ebp - 0x1c], esi
00867b34  8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00867b37  7303                     jae        0x867b3c
00867b39  8d45d0                   lea        eax, [ebp - 0x30]
00867b3c  51                       push       ecx
00867b3d  50                       push       eax
00867b3e  8d953cfaffff             lea        edx, [ebp - 0x5c4]
00867b44  6800020000               push       0x200
00867b49  52                       push       edx
00867b4a  e830a73900               call       0xc0227f
00867b4f  83c410                   add        esp, 0x10
00867b52  8d853cfaffff             lea        eax, [ebp - 0x5c4]
00867b58  50                       push       eax
00867b59  8d4dec                   lea        ecx, [ebp - 0x14]
00867b5c  e83fbd1e00               call       0xa538a0
00867b61  8d4dec                   lea        ecx, [ebp - 0x14]
00867b64  51                       push       ecx
00867b65  8d8d48ffffff             lea        ecx, [ebp - 0xb8]
00867b6b  e870c0b9ff               call       0x403be0
00867b70  8d55cc                   lea        edx, [ebp - 0x34]
00867b73  52                       push       edx
00867b74  e8978bfcff               call       0x830710
00867b79  83c404                   add        esp, 4
00867b7c  84c0                     test       al, al
00867b7e  75a0                     jne        0x867b20
00867b80  e933060000               jmp        0x8681b8
