00527090  55                       push       ebp
00527091  8bec                     mov        ebp, esp
00527093  56                       push       esi
00527094  8bf1                     mov        esi, ecx
00527096  8b4604                   mov        eax, dword ptr [esi + 4]
00527099  8b4e08                   mov        ecx, dword ptr [esi + 8]
0052709c  2bc8                     sub        ecx, eax
0052709e  b895204f09               mov        eax, 0x94f2095
005270a3  f7e9                     imul       ecx
005270a5  c1fa04                   sar        edx, 4
005270a8  8bc2                     mov        eax, edx
005270aa  c1e81f                   shr        eax, 0x1f
005270ad  57                       push       edi
005270ae  8b7d08                   mov        edi, dword ptr [ebp + 8]
005270b1  03c2                     add        eax, edx
005270b3  3bf8                     cmp        edi, eax
005270b5  7226                     jb         0x5270dd
005270b7  50                       push       eax
005270b8  57                       push       edi
005270b9  688887cd00               push       0xcd8788
005270be  68a0b3cb00               push       0xcbb3a0
005270c3  ff15bc2eff00             call       dword ptr [0xff2ebc]
005270c9  83c410                   add        esp, 0x10
005270cc  6a00                     push       0
005270ce  6a00                     push       0
005270d0  6a00                     push       0
005270d2  688c0000c0               push       0xc000008c
005270d7  ff1528f04001             call       dword ptr [0x140f028]
005270dd  8b4e04                   mov        ecx, dword ptr [esi + 4]
005270e0  8bc7                     mov        eax, edi
005270e2  69c0b8010000             imul       eax, eax, 0x1b8
005270e8  5f                       pop        edi
005270e9  03c1                     add        eax, ecx
005270eb  5e                       pop        esi
005270ec  5d                       pop        ebp
005270ed  c20400                   ret        4
