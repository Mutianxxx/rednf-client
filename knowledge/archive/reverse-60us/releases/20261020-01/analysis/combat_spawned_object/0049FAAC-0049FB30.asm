0049faac  8d5f70                   lea        ebx, [edi + 0x70]
0049faaf  68e0baca00               push       0xcabae0
0049fab4  8bcb                     mov        ecx, ebx
0049fab6  e835365b00               call       0xa530f0
0049fabb  50                       push       eax
0049fabc  e82a137600               call       0xc00deb
0049fac1  83c408                   add        esp, 8
0049fac4  85c0                     test       eax, eax
0049fac6  7468                     je         0x49fb30
0049fac8  8d8fa4000000             lea        ecx, [edi + 0xa4]
0049face  e81d365b00               call       0xa530f0
0049fad3  8bcb                     mov        ecx, ebx
0049fad5  894508                   mov        dword ptr [ebp + 8], eax
0049fad8  e813365b00               call       0xa530f0
0049fadd  8b0df8300001             mov        ecx, dword ptr [0x10030f8]
0049fae3  50                       push       eax
0049fae4  8b4508                   mov        eax, dword ptr [ebp + 8]
0049fae7  50                       push       eax
0049fae8  68f8b8ca00               push       0xcab8f8
0049faed  51                       push       ecx
0049faee  e83dd76d00               call       0xb7d230
0049faf3  83c410                   add        esp, 0x10
0049faf6  85c0                     test       eax, eax
0049faf8  740e                     je         0x49fb08
0049fafa  50                       push       eax
0049fafb  8d8edc050000             lea        ecx, [esi + 0x5dc]
0049fb01  e8da2c0000               call       0x4a27e0
0049fb06  eb28                     jmp        0x49fb30
0049fb08  8d8fa4000000             lea        ecx, [edi + 0xa4]
0049fb0e  e8dd355b00               call       0xa530f0
0049fb13  8bcb                     mov        ecx, ebx
0049fb15  894508                   mov        dword ptr [ebp + 8], eax
0049fb18  e8d3355b00               call       0xa530f0
0049fb1d  8b5508                   mov        edx, dword ptr [ebp + 8]
0049fb20  50                       push       eax
0049fb21  52                       push       edx
0049fb22  6828f0cc00               push       0xccf028
0049fb27  ff15bc2eff00             call       dword ptr [0xff2ebc]
0049fb2d  83c40c                   add        esp, 0xc