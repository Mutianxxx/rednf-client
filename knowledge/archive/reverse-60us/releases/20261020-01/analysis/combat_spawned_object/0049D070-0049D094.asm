0049d070  55                       push       ebp
0049d071  8bec                     mov        ebp, esp
0049d073  8b4508                   mov        eax, dword ptr [ebp + 8]
0049d076  56                       push       esi
0049d077  50                       push       eax
0049d078  8bf1                     mov        esi, ecx
0049d07a  e8d1e1ffff               call       0x49b250
0049d07f  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
0049d085  85c9                     test       ecx, ecx
0049d087  7406                     je         0x49d08f
0049d089  56                       push       esi
0049d08a  e8a10a0700               call       0x50db30
0049d08f  5e                       pop        esi
0049d090  5d                       pop        ebp
0049d091  c20400                   ret        4