0072b919  6a01                     push       1
0072b91b  6a01                     push       1
0072b91d  6a01                     push       1
0072b91f  6a4a                     push       0x4a
0072b921  ff9068070000             call       dword ptr [eax + 0x768]
0072b927  84c0                     test       al, al
0072b929  0f845f010000             je         0x72ba8e
0072b92f  899d30ffffff             mov        dword ptr [ebp - 0xd0], ebx
0072b935  899d34ffffff             mov        dword ptr [ebp - 0xcc], ebx
0072b93b  899d38ffffff             mov        dword ptr [ebp - 0xc8], ebx
0072b941  8d4dec                   lea        ecx, [ebp - 0x14]
0072b944  51                       push       ecx
0072b945  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b94b  c745fc27000000           mov        dword ptr [ebp - 4], 0x27
0072b952  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b955  e8c6b7cdff               call       0x407120
0072b95a  8d55ec                   lea        edx, [ebp - 0x14]
0072b95d  52                       push       edx
0072b95e  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b964  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b967  e8b4b7cdff               call       0x407120
0072b96c  8d45ec                   lea        eax, [ebp - 0x14]
0072b96f  50                       push       eax
0072b970  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b976  c745ec4a000000           mov        dword ptr [ebp - 0x14], 0x4a
0072b97d  e89eb7cdff               call       0x407120
0072b982  8b16                     mov        edx, dword ptr [esi]
0072b984  6a4a                     push       0x4a
0072b986  8bce                     mov        ecx, esi
0072b988  ff924c060000             call       dword ptr [edx + 0x64c]
0072b98e  50                       push       eax
0072b98f  8b06                     mov        eax, dword ptr [esi]
0072b991  56                       push       esi
0072b992  6a4a                     push       0x4a
0072b994  8bce                     mov        ecx, esi
0072b996  ff907c060000             call       dword ptr [eax + 0x67c]
0072b99c  8bc8                     mov        ecx, eax
0072b99e  e88dcad3ff               call       0x468430
0072b9a3  8d4dec                   lea        ecx, [ebp - 0x14]
0072b9a6  51                       push       ecx
0072b9a7  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b9ad  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b9b0  e86bb7cdff               call       0x407120
0072b9b5  8b16                     mov        edx, dword ptr [esi]
0072b9b7  56                       push       esi
0072b9b8  53                       push       ebx
0072b9b9  6a4a                     push       0x4a
0072b9bb  8bce                     mov        ecx, esi
0072b9bd  ff927c060000             call       dword ptr [edx + 0x67c]
0072b9c3  8bc8                     mov        ecx, eax
0072b9c5  e89645e2ff               call       0x54ff60
0072b9ca  6a06                     push       6
0072b9cc  8bf8                     mov        edi, eax
0072b9ce  8b06                     mov        eax, dword ptr [esi]
0072b9d0  6a38                     push       0x38
0072b9d2  8bce                     mov        ecx, esi
0072b9d4  ff908c030000             call       dword ptr [eax + 0x38c]
0072b9da  8bc8                     mov        ecx, eax
0072b9dc  e8ff922f00               call       0xa24ce0
0072b9e1  8d4dec                   lea        ecx, [ebp - 0x14]
0072b9e4  2bf8                     sub        edi, eax
0072b9e6  51                       push       ecx
0072b9e7  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b9ed  897dec                   mov        dword ptr [ebp - 0x14], edi
0072b9f0  e82bb7cdff               call       0x407120
0072b9f5  8d55ec                   lea        edx, [ebp - 0x14]
0072b9f8  52                       push       edx
0072b9f9  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072b9ff  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072ba06  e815b7cdff               call       0x407120
0072ba0b  8d45ec                   lea        eax, [ebp - 0x14]
0072ba0e  50                       push       eax
0072ba0f  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072ba15  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072ba1c  e8ffb6cdff               call       0x407120
0072ba21  8d4dec                   lea        ecx, [ebp - 0x14]
0072ba24  51                       push       ecx
0072ba25  8d8d2cffffff             lea        ecx, [ebp - 0xd4]
0072ba2b  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072ba2e  e8edb6cdff               call       0x407120
0072ba33  8b16                     mov        edx, dword ptr [esi]
0072ba35  53                       push       ebx
0072ba36  53                       push       ebx
0072ba37  6a01                     push       1
0072ba39  8d852cffffff             lea        eax, [ebp - 0xd4]
0072ba3f  50                       push       eax
0072ba40  6a0a                     push       0xa
0072ba42  8bce                     mov        ecx, esi
0072ba44  ff928c020000             call       dword ptr [edx + 0x28c]