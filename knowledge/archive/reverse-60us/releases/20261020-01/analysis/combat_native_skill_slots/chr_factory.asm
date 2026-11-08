00a61910  68180c0000               push       0xc18
00a61915  e803c01800               call       0xbed91d
00a6191a  83c404                   add        esp, 4
00a6191d  8945f0                   mov        dword ptr [ebp - 0x10], eax
00a61920  85c0                     test       eax, eax
00a61922  c745fc00000000           mov        dword ptr [ebp - 4], 0
00a61929  740b                     je         0xa61936
00a6192b  8bc8                     mov        ecx, eax
00a6192d  e89e200000               call       0xa639d0
00a61932  8bf0                     mov        esi, eax
00a61934  eb02                     jmp        0xa61938
00a61936  33f6                     xor        esi, esi
00a61938  8b4508                   mov        eax, dword ptr [ebp + 8]
00a6193b  50                       push       eax
00a6193c  56                       push       esi
00a6193d  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00a61944  e88799e2ff               call       0x88b2d0
00a61949  83c408                   add        esp, 8
00a6194c  84c0                     test       al, al
00a6194e  0f855b060000             jne        0xa61faf
00a61954  85f6                     test       esi, esi
00a61956  0f847a060000             je         0xa61fd6
00a6195c  8bce                     mov        ecx, esi
00a6195e  e82d240000               call       0xa63d90
