00a45c72 8d8540ffffff             lea        eax, [ebp - 0xc0]
00a45c78 682c71e400               push       0xe4712c
00a45c7d 50                       push       eax
00a45c7e e84deb9bff               call       0x4047d0
00a45c83 83c408                   add        esp, 8
00a45c86 84c0                     test       al, al
00a45c88 740f                     je         0xa45c99
00a45c8a c78560ffffff11000000     mov        dword ptr [ebp - 0xa0], 0x11
00a45c94 e9af100000               jmp        0xa46d48
