0044ab90  684cb2cc00               push       0xccb24c
0044ab95  e8cd5a7b00               call       0xc00667
0044ab9a  85c0                     test       eax, eax
0044ab9c  0f95c0                   setne      al
0044ab9f  68d81a0000               push       0x1ad8
0044aba4  a29c44f400               mov        byte ptr [0xf4449c], al
0044aba9  e86f2d7a00               call       0xbed91d
0044abae  83c40c                   add        esp, 0xc
0044abb1  8945f0                   mov        dword ptr [ebp - 0x10], eax
0044abb4  3bc6                     cmp        eax, esi
0044abb6  8975fc                   mov        dword ptr [ebp - 4], esi
0044abb9  7407                     je         0x44abc2
0044abbb  8bc8                     mov        ecx, eax
0044abbd  e84e3a7400               call       0xb8e610
0044abc2  53                       push       ebx
0044abc3  56                       push       esi
0044abc4  6834b2cc00               push       0xccb234
0044abc9  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0044abd0  e8925a7b00               call       0xc00667
0044abd5  56                       push       esi
0044abd6  681cb2cc00               push       0xccb21c
0044abdb  e8875a7b00               call       0xc00667
0044abe0  bb01000000               mov        ebx, 1
0044abe5  53                       push       ebx
0044abe6  6804b2cc00               push       0xccb204
0044abeb  e890f76700               call       0xaca380
0044abf0  a1cca02301               mov        eax, dword ptr [0x123a0cc]
0044abf5  8b3d58f04001             mov        edi, dword ptr [0x140f058]
0044abfb  8898a01a0000             mov        byte ptr [eax + 0x1aa0], bl
0044ac01  c7809c1a000060ab0d01     mov        dword ptr [eax + 0x1a9c], 0x10dab60
0044ac0b  a09c44f400               mov        al, byte ptr [0xf4449c]
0044ac10  83c418                   add        esp, 0x18
0044ac13  84c0                     test       al, al
0044ac15  7450                     je         0x44ac67
0044ac17  8b0d1ca90d01             mov        ecx, dword ptr [0x10da91c]
0044ac1d  8b4110                   mov        eax, dword ptr [ecx + 0x10]
0044ac20  8b0dcca02301             mov        ecx, dword ptr [0x123a0cc]
0044ac26  50                       push       eax
0044ac27  e864247400               call       0xb8d090
0044ac2c  84c0                     test       al, al
0044ac2e  7414                     je         0x44ac44
0044ac30  8b0dcca02301             mov        ecx, dword ptr [0x123a0cc]
0044ac36  68f0b1cc00               push       0xccb1f0
0044ac3b  e890447400               call       0xb8f0d0
0044ac40  84c0                     test       al, al
0044ac42  7523                     jne        0x44ac67
0044ac44  68b4b1cc00               push       0xccb1b4
0044ac49  ff15bc2eff00             call       dword ptr [0xff2ebc]
0044ac4f  83c404                   add        esp, 4
0044ac52  56                       push       esi
0044ac53  689cb1cc00               push       0xccb19c
0044ac58  6830b1cc00               push       0xccb130
0044ac5d  56                       push       esi
0044ac5e  ffd7                     call       edi