00731f0c  83fb14                   cmp        ebx, 0x14
00731f0f  8b4704                   mov        eax, dword ptr [edi + 4]
00731f12  8b00                     mov        eax, dword ptr [eax]
00731f14  8986ec2e0000             mov        dword ptr [esi + 0x2eec], eax
00731f1a  742c                     je         0x731f48
00731f1c  8b16                     mov        edx, dword ptr [esi]
00731f1e  6a06                     push       6
00731f20  8bce                     mov        ecx, esi
00731f22  ff924c060000             call       dword ptr [edx + 0x64c]
00731f28  85c0                     test       eax, eax
00731f2a  7e1c                     jle        0x731f48
00731f2c  8b06                     mov        eax, dword ptr [esi]
00731f2e  56                       push       esi
00731f2f  6a01                     push       1
00731f31  6a06                     push       6
00731f33  8bce                     mov        ecx, esi
00731f35  ff907c060000             call       dword ptr [eax + 0x67c]
00731f3b  8bc8                     mov        ecx, eax
00731f3d  e81ee0e1ff               call       0x54ff60
00731f42  8986f02e0000             mov        dword ptr [esi + 0x2ef0], eax
00731f48  8b86ec2e0000             mov        eax, dword ptr [esi + 0x2eec]
00731f4e  85c0                     test       eax, eax
00731f50  8bce                     mov        ecx, esi
00731f52  7513                     jne        0x731f67
00731f54  8b16                     mov        edx, dword ptr [esi]
00731f56  50                       push       eax
00731f57  50                       push       eax
00731f58  6a12                     push       0x12
00731f5a  6824f9d700               push       0xd7f924
00731f5f  ff920c010000             call       dword ptr [edx + 0x10c]
00731f65  eb40                     jmp        0x731fa7
00731f67  83f801                   cmp        eax, 1
00731f6a  7515                     jne        0x731f81
00731f6c  8b06                     mov        eax, dword ptr [esi]
00731f6e  6a00                     push       0
00731f70  6a00                     push       0
00731f72  6a13                     push       0x13
00731f74  6808f9d700               push       0xd7f908
00731f79  ff900c010000             call       dword ptr [eax + 0x10c]
00731f7f  eb26                     jmp        0x731fa7
00731f81  8b16                     mov        edx, dword ptr [esi]
00731f83  6a13                     push       0x13
00731f85  ff9210010000             call       dword ptr [edx + 0x110]
00731f8b  8b06                     mov        eax, dword ptr [esi]
00731f8d  6a00                     push       0
00731f8f  6a00                     push       0
00731f91  6a12                     push       0x12
00731f93  6824f9d700               push       0xd7f924
00731f98  8bce                     mov        ecx, esi
00731f9a  ff900c010000             call       dword ptr [eax + 0x10c]
00731fa0  c6860c2f000000           mov        byte ptr [esi + 0x2f0c], 0
00731fa7  8b1e                     mov        ebx, dword ptr [esi]
00731fa9  6a01                     push       1
00731fab  8bce                     mov        ecx, esi
00731fad  ff938c030000             call       dword ptr [ebx + 0x38c]
00731fb3  50                       push       eax
00731fb4  8bce                     mov        ecx, esi
00731fb6  ff93f0000000             call       dword ptr [ebx + 0xf0]
00731fbc  8b1e                     mov        ebx, dword ptr [esi]
00731fbe  6a00                     push       0
00731fc0  8bce                     mov        ecx, esi
00731fc2  e82951dfff               call       0x5270f0
00731fc7  50                       push       eax
00731fc8  8bce                     mov        ecx, esi
00731fca  ff9398010000             call       dword ptr [ebx + 0x198]
