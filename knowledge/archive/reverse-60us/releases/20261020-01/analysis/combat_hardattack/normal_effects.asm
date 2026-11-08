007326f0 85c0                     test       eax, eax
007326f2 7409                     je         0x7326fd
007326f4 83f802                   cmp        eax, 2
007326f7 0f85ee000000             jne        0x7327eb
007326fd 8b86fc2e0000             mov        eax, dword ptr [esi + 0x2efc]
00732703 85c0                     test       eax, eax
00732705 8d9efc2e0000             lea        ebx, [esi + 0x2efc]
0073270b 0f8580000000             jne        0x732791
00732711 68e8010000               push       0x1e8
00732716 e83515cdff               call       0x403c50
0073271b 8bf8                     mov        edi, eax
0073271d 83c404                   add        esp, 4
00732720 897dec                   mov        dword ptr [ebp - 0x14], edi
00732723 85ff                     test       edi, edi
00732725 c645fc0a                 mov        byte ptr [ebp - 4], 0xa
00732729 741c                     je         0x732747
0073272b 6a01                     push       1
0073272d 68c0f6d700               push       0xd7f6c0
00732732 8d8e44020000             lea        ecx, [esi + 0x244]
00732738 e8730dd0ff               call       0x4334b0
0073273d 50                       push       eax
0073273e 8bcf                     mov        ecx, edi
00732740 e81b03d4ff               call       0x472a60
00732745 eb02                     jmp        0x732749
00732747 33c0                     xor        eax, eax
00732749 68e8010000               push       0x1e8
0073274e c645fc00                 mov        byte ptr [ebp - 4], 0
00732752 8903                     mov        dword ptr [ebx], eax
00732754 e8f714cdff               call       0x403c50
00732759 8bf8                     mov        edi, eax
0073275b 83c404                   add        esp, 4
0073275e 897dec                   mov        dword ptr [ebp - 0x14], edi
00732761 85ff                     test       edi, edi
00732763 c645fc0b                 mov        byte ptr [ebp - 4], 0xb
00732767 741c                     je         0x732785
00732769 6a01                     push       1
0073276b 6878f6d700               push       0xd7f678
00732770 8d8e44020000             lea        ecx, [esi + 0x244]
00732776 e8350dd0ff               call       0x4334b0
0073277b 50                       push       eax
0073277c 8bcf                     mov        ecx, edi
0073277e e8dd02d4ff               call       0x472a60
00732783 eb02                     jmp        0x732787
00732785 33c0                     xor        eax, eax
00732787 c645fc00                 mov        byte ptr [ebp - 4], 0
0073278b 8986002f0000             mov        dword ptr [esi + 0x2f00], eax
00732791 8b06                     mov        eax, dword ptr [esi]
00732793 56                       push       esi
00732794 6a00                     push       0
00732796 6a05                     push       5
00732798 8bce                     mov        ecx, esi
0073279a ff907c060000             call       dword ptr [eax + 0x67c]
007327a0 8bc8                     mov        ecx, eax
007327a2 e8b9d7e1ff               call       0x54ff60
007327a7 8945f0                   mov        dword ptr [ebp - 0x10], eax
007327aa db45f0                   fild       dword ptr [ebp - 0x10]
007327ad 33ff                     xor        edi, edi
007327af d80dac10cc00             fmul       dword ptr [0xcc10ac]
007327b5 d95df0                   fstp       dword ptr [ebp - 0x10]
007327b8 8b45f0                   mov        eax, dword ptr [ebp - 0x10]
007327bb 8b0b                     mov        ecx, dword ptr [ebx]
007327bd 50                       push       eax
007327be 50                       push       eax
007327bf e83c312f00               call       0xa25900
007327c4 8b03                     mov        eax, dword ptr [ebx]
007327c6 8b16                     mov        edx, dword ptr [esi]
007327c8 6a01                     push       1
007327ca 6a00                     push       0
007327cc 6a00                     push       0
007327ce 6a00                     push       0
007327d0 6a00                     push       0
007327d2 6a00                     push       0
007327d4 6a00                     push       0
007327d6 6a28                     push       0x28
007327d8 50                       push       eax
007327d9 47                       inc        edi
007327da 57                       push       edi
007327db 8bce                     mov        ecx, esi
007327dd ff92f8000000             call       dword ptr [edx + 0xf8]
007327e3 83c304                   add        ebx, 4
007327e6 83ff02                   cmp        edi, 2
007327e9 7ccd                     jl         0x7327b8