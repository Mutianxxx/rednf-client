00746c30  55                       push       ebp
00746c31  8bec                     mov        ebp, esp
00746c33  8b4508                   mov        eax, dword ptr [ebp + 8]
00746c36  56                       push       esi
00746c37  50                       push       eax
00746c38  8bf1                     mov        esi, ecx
00746c3a  e8418ad8ff               call       0x4cf680
00746c3f  c6865f2b000000           mov        byte ptr [esi + 0x2b5f], 0
00746c46  5e                       pop        esi
00746c47  5d                       pop        ebp
00746c48  c20400                   ret        4
