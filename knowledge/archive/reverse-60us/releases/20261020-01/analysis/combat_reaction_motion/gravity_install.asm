004ba0c0 55                       push       ebp
004ba0c1 8bec                     mov        ebp, esp
004ba0c3 8b4508                   mov        eax, dword ptr [ebp + 8]
004ba0c6 83f801                   cmp        eax, 1
004ba0c9 56                       push       esi
004ba0ca 8bf1                     mov        esi, ecx
004ba0cc 898638160000             mov        dword ptr [esi + 0x1638], eax
004ba0d2 7508                     jne        0x4ba0dc
004ba0d4 50                       push       eax
004ba0d5 e8c6feffff               call       0x4b9fa0
004ba0da eb13                     jmp        0x4ba0ef
004ba0dc 83f802                   cmp        eax, 2
004ba0df 750b                     jne        0x4ba0ec
004ba0e1 6a00                     push       0
004ba0e3 8bce                     mov        ecx, esi
004ba0e5 e8b6feffff               call       0x4b9fa0
004ba0ea eb03                     jmp        0x4ba0ef
004ba0ec 8b450c                   mov        eax, dword ptr [ebp + 0xc]
004ba0ef 8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004ba0f5 50                       push       eax
004ba0f6 6a02                     push       2
004ba0f8 e8d37c0500               call       0x511dd0
004ba0fd 8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004ba103 6aff                     push       -1
004ba105 6a02                     push       2
004ba107 e8b46f0500               call       0x5110c0
004ba10c 5e                       pop        esi
004ba10d 5d                       pop        ebp
004ba10e c20800                   ret        8
