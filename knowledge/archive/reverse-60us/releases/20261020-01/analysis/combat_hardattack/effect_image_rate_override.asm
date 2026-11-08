00a25900 55                       push       ebp
00a25901 8bec                     mov        ebp, esp
00a25903 53                       push       ebx
00a25904 56                       push       esi
00a25905 8bf1                     mov        esi, ecx
00a25907 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2590d 85c0                     test       eax, eax
00a2590f 57                       push       edi
00a25910 741b                     je         0xa2592d
00a25912 8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a25918 2bc8                     sub        ecx, eax
00a2591a b843082184               mov        eax, 0x84210843
00a2591f f7e9                     imul       ecx
00a25921 03d1                     add        edx, ecx
00a25923 c1fa06                   sar        edx, 6
00a25926 8bc2                     mov        eax, edx
00a25928 c1e81f                   shr        eax, 0x1f
00a2592b 03c2                     add        eax, edx
00a2592d 85c0                     test       eax, eax
00a2592f 8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
00a25932 7e46                     jle        0xa2597a
00a25934 33c9                     xor        ecx, ecx
00a25936 8bd0                     mov        edx, eax
00a25938 eb06                     jmp        0xa25940
00a2593a 8d9b00000000             lea        ebx, [ebx]
00a25940 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a25946 8b3dfc3e0d01             mov        edi, dword ptr [0x10d3efc]
00a2594c 8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a2594f 03c1                     add        eax, ecx
00a25951 83c010                   add        eax, 0x10
00a25954 33fb                     xor        edi, ebx
00a25956 8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
00a25959 03f8                     add        edi, eax
00a2595b 8938                     mov        dword ptr [eax], edi
00a2595d 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a25963 8b3dfc3e0d01             mov        edi, dword ptr [0x10d3efc]
00a25969 03c1                     add        eax, ecx
00a2596b 83c014                   add        eax, 0x14
00a2596e 33fb                     xor        edi, ebx
00a25970 03f8                     add        edi, eax
00a25972 83c17c                   add        ecx, 0x7c
00a25975 4a                       dec        edx
00a25976 8938                     mov        dword ptr [eax], edi
00a25978 75c6                     jne        0xa25940
00a2597a 83be24010000ff           cmp        dword ptr [esi + 0x124], -1
00a25981 7427                     je         0xa259aa
00a25983 8b0dfc3e0d01             mov        ecx, dword ptr [0x10d3efc]
00a25989 8b7d08                   mov        edi, dword ptr [ebp + 8]
00a2598c 8d86b8000000             lea        eax, [esi + 0xb8]
00a25992 33cf                     xor        ecx, edi
00a25994 03c8                     add        ecx, eax
00a25996 8908                     mov        dword ptr [eax], ecx
00a25998 8b15fc3e0d01             mov        edx, dword ptr [0x10d3efc]
00a2599e 8d86bc000000             lea        eax, [esi + 0xbc]
00a259a4 33d3                     xor        edx, ebx
00a259a6 03d0                     add        edx, eax
00a259a8 8910                     mov        dword ptr [eax], edx
00a259aa 8b8680010000             mov        eax, dword ptr [esi + 0x180]
00a259b0 8b38                     mov        edi, dword ptr [eax]
00a259b2 3bf8                     cmp        edi, eax
00a259b4 741b                     je         0xa259d1
00a259b6 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00a259b9 85c9                     test       ecx, ecx
00a259bb 740a                     je         0xa259c7
00a259bd 8b4508                   mov        eax, dword ptr [ebp + 8]
00a259c0 53                       push       ebx
00a259c1 50                       push       eax
00a259c2 e839ffffff               call       0xa25900
00a259c7 8b3f                     mov        edi, dword ptr [edi]
00a259c9 3bbe80010000             cmp        edi, dword ptr [esi + 0x180]
00a259cf 75e5                     jne        0xa259b6
00a259d1 5f                       pop        edi
00a259d2 5e                       pop        esi
00a259d3 5b                       pop        ebx
00a259d4 5d                       pop        ebp
00a259d5 c20800                   ret        8