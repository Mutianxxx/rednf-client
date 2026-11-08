00a46a31 8d9540ffffff             lea        edx, [ebp - 0xc0]
00a46a37 68406ce400               push       0xe46c40
00a46a3c 52                       push       edx
00a46a3d e88edd9bff               call       0x4047d0
00a46a42 83c408                   add        esp, 8
00a46a45 84c0                     test       al, al
00a46a47 7427                     je         0xa46a70
00a46a49 c78560ffffff2f000000     mov        dword ptr [ebp - 0xa0], 0x2f
00a46a53 57                       push       edi
00a46a54 e8778ddeff               call       0x82f7d0
00a46a59 8945f0                   mov        dword ptr [ebp - 0x10], eax
00a46a5c 83c404                   add        esp, 4
00a46a5f 8d45f0                   lea        eax, [ebp - 0x10]
00a46a62 50                       push       eax
00a46a63 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46a66 e8c5060000               call       0xa47130
00a46a6b e9d8020000               jmp        0xa46d48
