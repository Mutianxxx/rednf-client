005270f0  55                       push       ebp
005270f1  8bec                     mov        ebp, esp
005270f3  8b8148040000             mov        eax, dword ptr [ecx + 0x448]
005270f9  8b914c040000             mov        edx, dword ptr [ecx + 0x44c]
005270ff  81c144040000             add        ecx, 0x444
00527105  2bd0                     sub        edx, eax
00527107  b895204f09               mov        eax, 0x94f2095
0052710c  f7ea                     imul       edx
0052710e  8b4508                   mov        eax, dword ptr [ebp + 8]
00527111  56                       push       esi
00527112  c1fa04                   sar        edx, 4
00527115  8bf2                     mov        esi, edx
00527117  c1ee1f                   shr        esi, 0x1f
0052711a  03f2                     add        esi, edx
0052711c  3bc6                     cmp        eax, esi
0052711e  5e                       pop        esi
0052711f  730a                     jae        0x52712b
00527121  50                       push       eax
00527122  e869ffffff               call       0x527090
00527127  5d                       pop        ebp
00527128  c20400                   ret        4
0052712b  33c0                     xor        eax, eax
0052712d  5d                       pop        ebp
0052712e  c20400                   ret        4
