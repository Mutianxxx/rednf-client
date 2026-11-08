00501cd3 8b4d08                   mov        ecx, dword ptr [ebp + 8]
00501cd6 68e0baca00               push       0xcabae0
00501cdb 81c14c070000             add        ecx, 0x74c
00501ce1 e80a145500               call       0xa530f0
00501ce6 50                       push       eax
00501ce7 e8fff06f00               call       0xc00deb
00501cec 83c408                   add        esp, 8
00501cef 85c0                     test       eax, eax
00501cf1 0f8482000000             je         0x501d79
00501cf7 68e0020000               push       0x2e0
00501cfc e84f1ff0ff               call       0x403c50
00501d01 8bf8                     mov        edi, eax
00501d03 83c404                   add        esp, 4
00501d06 897de8                   mov        dword ptr [ebp - 0x18], edi
00501d09 85ff                     test       edi, edi
00501d0b c745fc17000000           mov        dword ptr [ebp - 4], 0x17
00501d12 7432                     je         0x501d46
00501d14 83bb5c02000008           cmp        dword ptr [ebx + 0x25c], 8
00501d1b 7208                     jb         0x501d25
00501d1d 8bb348020000             mov        esi, dword ptr [ebx + 0x248]
00501d23 eb06                     jmp        0x501d2b
00501d25 8db348020000             lea        esi, [ebx + 0x248]
00501d2b 8b4d08                   mov        ecx, dword ptr [ebp + 8]
00501d2e 6a00                     push       0
00501d30 81c14c070000             add        ecx, 0x74c
00501d36 e8b5135500               call       0xa530f0
00501d3b 50                       push       eax
00501d3c 56                       push       esi
00501d3d 8bcf                     mov        ecx, edi
00501d3f e8bc1bfaff               call       0x4a3900
00501d44 eb02                     jmp        0x501d48
00501d46 33c0                     xor        eax, eax
00501d48 85c0                     test       eax, eax
00501d4a c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00501d51 898354010000             mov        dword ptr [ebx + 0x154], eax
00501d57 7420                     je         0x501d79
00501d59 c780cc0200000d000000     mov        dword ptr [eax + 0x2cc], 0xd
00501d63 c780d002000000000000     mov        dword ptr [eax + 0x2d0], 0
00501d6d 8b8b54010000             mov        ecx, dword ptr [ebx + 0x154]
00501d73 53                       push       ebx
00501d74 e8a7b25200               call       0xa2d020
