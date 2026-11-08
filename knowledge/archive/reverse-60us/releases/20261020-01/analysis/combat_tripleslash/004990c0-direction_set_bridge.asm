004990c0  55                       push       ebp
004990c1  8bec                     mov        ebp, esp
004990c3  8b81b0010000             mov        eax, dword ptr [ecx + 0x1b0]
004990c9  85c0                     test       eax, eax
004990cb  750c                     jne        0x4990d9
004990cd  8b89f8000000             mov        ecx, dword ptr [ecx + 0xf8]
004990d3  5d                       pop        ebp
004990d4  e937800700               jmp        0x511110
004990d9  5d                       pop        ebp
004990da  c20400                   ret        4
