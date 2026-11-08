00a619c2  6878010000               push       0x178
00a619c7  e851bf1800               call       0xbed91d
00a619cc  83c404                   add        esp, 4
00a619cf  8945f0                   mov        dword ptr [ebp - 0x10], eax
00a619d2  85c0                     test       eax, eax
00a619d4  c745fc02000000           mov        dword ptr [ebp - 4], 2
00a619db  740b                     je         0xa619e8
00a619dd  8bc8                     mov        ecx, eax
00a619df  e82c26e3ff               call       0x894010
00a619e4  8bf0                     mov        esi, eax
00a619e6  eb02                     jmp        0xa619ea
00a619e8  33f6                     xor        esi, esi
00a619ea  8b5508                   mov        edx, dword ptr [ebp + 8]
00a619ed  6a00                     push       0
00a619ef  52                       push       edx
00a619f0  56                       push       esi
00a619f1  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00a619f8  e8232de2ff               call       0x884720
00a619fd  83c40c                   add        esp, 0xc
00a61a00  84c0                     test       al, al
00a61a02  0f85a7050000             jne        0xa61faf
00a61a08  85f6                     test       esi, esi
00a61a0a  0f84c6050000             je         0xa61fd6
00a61a10  8bce                     mov        ecx, esi
00a61a12  e8d9ffe2ff               call       0x8919f0
00a61a17  e9b1050000               jmp        0xa61fcd