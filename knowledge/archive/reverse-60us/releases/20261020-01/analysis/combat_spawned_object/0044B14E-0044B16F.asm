0044b14e  6a00                     push       0
0044b150  68e0baca00               push       0xcabae0
0044b155  6a02                     push       2
0044b157  8bc8                     mov        ecx, eax
0044b159  e872636100               call       0xa614d0
0044b15e  eb02                     jmp        0x44b162
0044b160  33c0                     xor        eax, eax
0044b162  6824020000               push       0x224
0044b167  885dfc                   mov        byte ptr [ebp - 4], bl
0044b16a  a3e4300001               mov        dword ptr [0x10030e4], eax