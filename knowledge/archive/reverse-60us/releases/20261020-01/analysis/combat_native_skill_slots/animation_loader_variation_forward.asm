00a29ad0  55                       push       ebp
00a29ad1  8bec                     mov        ebp, esp
00a29ad3  6aff                     push       -1
00a29ad5  68bce4c800               push       0xc8e4bc
00a29ada  64a100000000             mov        eax, dword ptr fs:[0]
00a29ae0  50                       push       eax
00a29ae1  64892500000000           mov        dword ptr fs:[0], esp
00a29ae8  83ec1c                   sub        esp, 0x1c
00a29aeb  8a4514                   mov        al, byte ptr [ebp + 0x14]
00a29aee  84c0                     test       al, al
00a29af0  53                       push       ebx
00a29af1  56                       push       esi
00a29af2  8b7520                   mov        esi, dword ptr [ebp + 0x20]
00a29af5  57                       push       edi
00a29af6  8bd9                     mov        ebx, ecx
00a29af8  740f                     je         0xa29b09
00a29afa  837d1cff                 cmp        dword ptr [ebp + 0x1c], -1
00a29afe  7405                     je         0xa29b05
00a29b00  83feff                   cmp        esi, -1
00a29b03  7504                     jne        0xa29b09
00a29b05  c6451400                 mov        byte ptr [ebp + 0x14], 0
00a29b09  807d1001                 cmp        byte ptr [ebp + 0x10], 1
00a29b0d  8b7d08                   mov        edi, dword ptr [ebp + 8]
00a29b10  0f8527010000             jne        0xa29c3d
00a29b16  68e0baca00               push       0xcabae0
00a29b1b  57                       push       edi
00a29b1c  e8ca721d00               call       0xc00deb
00a29b21  83c408                   add        esp, 8
00a29b24  85c0                     test       eax, eax
00a29b26  56                       push       esi
00a29b27  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00a29b2a  7516                     jne        0xa29b42
00a29b2c  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00a29b2f  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a29b32  50                       push       eax
00a29b33  51                       push       ecx
00a29b34  8b0d38310001             mov        ecx, dword ptr [0x1003138]
00a29b3a  56                       push       esi
00a29b3b  e8d06c0300               call       0xa60810
00a29b40  eb15                     jmp        0xa29b57
00a29b42  8b551c                   mov        edx, dword ptr [ebp + 0x1c]
00a29b45  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00a29b48  8b0d38310001             mov        ecx, dword ptr [0x1003138]
00a29b4e  52                       push       edx
00a29b4f  50                       push       eax
00a29b50  56                       push       esi
00a29b51  57                       push       edi
00a29b52  e8e96d0300               call       0xa60940
00a29b57  85                       .byte      0x85
