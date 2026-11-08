0049c090  8b01                     mov        eax, dword ptr [ecx]
0049c092  ff9060010000             call       dword ptr [eax + 0x160]
0049c098  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
0049c09e  3bc1                     cmp        eax, ecx
0049c0a0  750a                     jne        0x49c0ac
0049c0a2  85c9                     test       ecx, ecx
0049c0a4  7406                     je         0x49c0ac
0049c0a6  b801000000               mov        eax, 1
0049c0ab  c3                       ret        
0049c0ac  33c0                     xor        eax, eax
0049c0ae  c3                       ret        