0072ac9d  8bcf                     mov        ecx, edi
0072ac9f  e8bc73cdff               call       0x402060
0072aca4  85c0                     test       eax, eax
0072aca6  741c                     je         0x72acc4
0072aca8  8bcf                     mov        ecx, edi
0072acaa  e8b173cdff               call       0x402060
0072acaf  83f80b                   cmp        eax, 0xb
0072acb2  7410                     je         0x72acc4
0072acb4  8bcf                     mov        ecx, edi
0072acb6  e8a573cdff               call       0x402060
0072acbb  83f808                   cmp        eax, 8
0072acbe  0f85b2000000             jne        0x72ad76
0072acc4  8b16                     mov        edx, dword ptr [esi]
0072acc6  8d86e4250000             lea        eax, [esi + 0x25e4]
0072accc  50                       push       eax
0072accd  6a05                     push       5
0072accf  8bce                     mov        ecx, esi
0072acd1  ff923c070000             call       dword ptr [edx + 0x73c]
0072acd7  8bc8                     mov        ecx, eax
0072acd9  e862e4e2ff               call       0x559140
0072acde  83f8ff                   cmp        eax, -1
0072ace1  0f848f000000             je         0x72ad76
0072ace7  8b06                     mov        eax, dword ptr [esi]
0072ace9  6a01                     push       1
0072aceb  6a01                     push       1
0072aced  6a01                     push       1
0072acef  6a05                     push       5
0072acf1  8bce                     mov        ecx, esi
0072acf3  ff9068070000             call       dword ptr [eax + 0x768]
0072acf9  84c0                     test       al, al
0072acfb  7479                     je         0x72ad76
0072acfd  899d88fcffff             mov        dword ptr [ebp - 0x378], ebx
0072ad03  899d8cfcffff             mov        dword ptr [ebp - 0x374], ebx
0072ad09  899d90fcffff             mov        dword ptr [ebp - 0x370], ebx
0072ad0f  8b16                     mov        edx, dword ptr [esi]
0072ad11  6a06                     push       6
0072ad13  8bce                     mov        ecx, esi
0072ad15  c745fc1d000000           mov        dword ptr [ebp - 4], 0x1d
0072ad1c  ff924c060000             call       dword ptr [edx + 0x64c]
0072ad22  33c9                     xor        ecx, ecx
0072ad24  85c0                     test       eax, eax
0072ad26  0f9fc1                   setg       cl
0072ad29  8d55ec                   lea        edx, [ebp - 0x14]
0072ad2c  52                       push       edx
0072ad2d  894dec                   mov        dword ptr [ebp - 0x14], ecx
0072ad30  8d8d84fcffff             lea        ecx, [ebp - 0x37c]
0072ad36  e8e5c3cdff               call       0x407120
0072ad3b  8d45ec                   lea        eax, [ebp - 0x14]
0072ad3e  50                       push       eax
0072ad3f  8d8d84fcffff             lea        ecx, [ebp - 0x37c]
0072ad45  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072ad48  e8d3c3cdff               call       0x407120
0072ad4d  8b16                     mov        edx, dword ptr [esi]
0072ad4f  53                       push       ebx
0072ad50  53                       push       ebx
0072ad51  6a01                     push       1
0072ad53  8d8584fcffff             lea        eax, [ebp - 0x37c]
0072ad59  50                       push       eax
0072ad5a  6a14                     push       0x14
0072ad5c  8bce                     mov        ecx, esi
0072ad5e  ff928c020000             call       dword ptr [edx + 0x28c]
0072ad64  8d8d84fcffff             lea        ecx, [ebp - 0x37c]
0072ad6a  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0072ad71  e8da9ff1ff               call       0x644d50