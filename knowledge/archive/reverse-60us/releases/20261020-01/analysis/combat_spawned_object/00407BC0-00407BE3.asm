00407bc0  55                       push       ebp
00407bc1  8bec                     mov        ebp, esp
00407bc3  8b9104010000             mov        edx, dword ptr [ecx + 0x104]
00407bc9  85d2                     test       edx, edx
00407bcb  8b4508                   mov        eax, dword ptr [ebp + 8]
00407bce  898118010000             mov        dword ptr [ecx + 0x118], eax
00407bd4  7509                     jne        0x407bdf
00407bd6  8b11                     mov        edx, dword ptr [ecx]
00407bd8  50                       push       eax
00407bd9  ff92f0000000             call       dword ptr [edx + 0xf0]
00407bdf  5d                       pop        ebp
00407be0  c20400                   ret        4