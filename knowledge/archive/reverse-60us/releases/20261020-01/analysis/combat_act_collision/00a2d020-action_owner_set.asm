00a2d020 55                       push       ebp
00a2d021 8bec                     mov        ebp, esp
00a2d023 8b4508                   mov        eax, dword ptr [ebp + 8]
00a2d026 89417c                   mov        dword ptr [ecx + 0x7c], eax
00a2d029 5d                       pop        ebp
00a2d02a c20400                   ret        4
