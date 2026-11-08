00836c20  55                       push       ebp
00836c21  8bec                     mov        ebp, esp
00836c23  6aff                     push       -1
00836c25  6847dec700               push       0xc7de47
00836c2a  64a100000000             mov        eax, dword ptr fs:[0]
00836c30  50                       push       eax
00836c31  64892500000000           mov        dword ptr fs:[0], esp
00836c38  81ecdc000000             sub        esp, 0xdc
00836c3e  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00836c41  50                       push       eax
00836c42  68e0baca00               push       0xcabae0
00836c47  e8448bffff               call       0x82f790
00836c4c  83c408                   add        esp, 8
00836c4f  84c0                     test       al, al
00836c51  750e                     jne        0x836c61
00836c53  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00836c56  64890d00000000           mov        dword ptr fs:[0], ecx
00836c5d  8be5                     mov        esp, ebp
00836c5f  5d                       pop        ebp
00836c60  c3                       ret        
00836c61  53                       push       ebx
00836c62  56                       push       esi
00836c63  57                       push       edi
00836c64  8b7d08                   mov        edi, dword ptr [ebp + 8]
00836c67  8bcf                     mov        ecx, edi
00836c69  e8c2e7bfff               call       0x435430
00836c6e  33f6                     xor        esi, esi
00836c70  bb07000000               mov        ebx, 7
00836c75  895dd0                   mov        dword ptr [ebp - 0x30], ebx
00836c78  8975cc                   mov        dword ptr [ebp - 0x34], esi
00836c7b  668975bc                 mov        word ptr [ebp - 0x44], si
00836c7f  8975fc                   mov        dword ptr [ebp - 4], esi
00836c82  895dec                   mov        dword ptr [ebp - 0x14], ebx
00836c85  8975e8                   mov        dword ptr [ebp - 0x18], esi
00836c88  668975d8                 mov        word ptr [ebp - 0x28], si
00836c8c  8d4db8                   lea        ecx, [ebp - 0x48]
00836c8f  6a01                     push       1
00836c91  51                       push       ecx
00836c92  c645fc01                 mov        byte ptr [ebp - 4], 1
00836c96  e8459bffff               call       0x8307e0
00836c9b  83c408                   add        esp, 8
00836c9e  84c0                     test       al, al
00836ca0  0f8479110000             je         0x837e1f
00836ca6  8d55b8                   lea        edx, [ebp - 0x48]
00836ca9  52                       push       edx
00836caa  bb02000000               mov        ebx, 2
00836caf  e82c93ffff               call       0x82ffe0
