004af8d0  55                       push       ebp
004af8d1  8bec                     mov        ebp, esp
004af8d3  56                       push       esi
004af8d4  8b7508                   mov        esi, dword ptr [ebp + 8]
004af8d7  85f6                     test       esi, esi
004af8d9  7448                     je         0x4af923
004af8db  8b8698000000             mov        eax, dword ptr [esi + 0x98]
004af8e1  85c0                     test       eax, eax
004af8e3  743e                     je         0x4af923
004af8e5  8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
004af8eb  2bc8                     sub        ecx, eax
004af8ed  b843082184               mov        eax, 0x84210843
004af8f2  f7e9                     imul       ecx
004af8f4  03d1                     add        edx, ecx
004af8f6  c1fa06                   sar        edx, 6
004af8f9  8bc2                     mov        eax, edx
004af8fb  c1e81f                   shr        eax, 0x1f
004af8fe  03c2                     add        eax, edx
004af900  83f801                   cmp        eax, 1
004af903  751e                     jne        0x4af923
004af905  8bb698000000             mov        esi, dword ptr [esi + 0x98]
004af90b  8b4e08                   mov        ecx, dword ptr [esi + 8]
004af90e  b8ffff0000               mov        eax, 0xffff
004af913  3bc8                     cmp        ecx, eax
004af915  750c                     jne        0x4af923
004af917  39460c                   cmp        dword ptr [esi + 0xc], eax
004af91a  7507                     jne        0x4af923
004af91c  b001                     mov        al, 1
004af91e  5e                       pop        esi
004af91f  5d                       pop        ebp
004af920  c20400                   ret        4
004af923  32c0                     xor        al, al
004af925  5e                       pop        esi
004af926  5d                       pop        ebp
004af927  c20400                   ret        4
