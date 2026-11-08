00498ff0  55                       push       ebp
00498ff1  8bec                     mov        ebp, esp
00498ff3  8b4508                   mov        eax, dword ptr [ebp + 8]
00498ff6  8b89e4000000             mov        ecx, dword ptr [ecx + 0xe4]
00498ffc  23c8                     and        ecx, eax
00498ffe  3bc8                     cmp        ecx, eax
00499000  0f94c0                   sete       al
00499003  5d                       pop        ebp
00499004  c20400                   ret        4
