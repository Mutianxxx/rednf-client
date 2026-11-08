004ac020  55                       push       ebp
004ac021  8bec                     mov        ebp, esp
004ac023  8b4508                   mov        eax, dword ptr [ebp + 8]
004ac026  8b948194120000           mov        edx, dword ptr [ecx + eax*4 + 0x1294]
004ac02d  85d2                     test       edx, edx
004ac02f  7414                     je         0x4ac045
004ac031  8bca                     mov        ecx, edx
004ac033  8b01                     mov        eax, dword ptr [ecx]
004ac035  ff5008                   call       dword ptr [eax + 8]
004ac038  84c0                     test       al, al
004ac03a  7409                     je         0x4ac045
004ac03c  b801000000               mov        eax, 1
004ac041  5d                       pop        ebp
004ac042  c20400                   ret        4
004ac045  33c0                     xor        eax, eax
004ac047  5d                       pop        ebp
004ac048  c20400                   ret        4
