00882a50  55                       push       ebp
00882a51  8bec                     mov        ebp, esp
00882a53  8b4508                   mov        eax, dword ptr [ebp + 8]
00882a56  6800010000               push       0x100
00882a5b  50                       push       eax
00882a5c  68d0dd0b01               push       0x10bddd0
00882a61  e860de3700               call       0xc008c6
00882a66  68d0dd0b01               push       0x10bddd0
00882a6b  e85dd33700               call       0xbffdcd
00882a70  83c410                   add        esp, 0x10
00882a73  66833c45cedd0b015c       cmp        word ptr [eax*2 + 0x10bddce], 0x5c
00882a7c  742f                     je         0x882aad
00882a7e  68d0dd0b01               push       0x10bddd0
00882a83  e845d33700               call       0xbffdcd
00882a88  83c404                   add        esp, 4
00882a8b  66833c45cedd0b012f       cmp        word ptr [eax*2 + 0x10bddce], 0x2f
00882a94  7417                     je         0x882aad
00882a96  6800010000               push       0x100
00882a9b  6804b9ca00               push       0xcab904
00882aa0  68d0dd0b01               push       0x10bddd0
00882aa5  e898f73700               call       0xc02242
00882aaa  83c40c                   add        esp, 0xc
00882aad  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00882ab0  51                       push       ecx
00882ab1  68d0dd0b01               push       0x10bddd0
00882ab6  68e8e30b01               push       0x10be3e8
00882abb  e810f0faff               call       0x831ad0
00882ac0  83c40c                   add        esp, 0xc
00882ac3  84c0                     test       al, al
00882ac5  0f95c0                   setne      al
00882ac8  5d                       pop        ebp
00882ac9  c3                       ret        