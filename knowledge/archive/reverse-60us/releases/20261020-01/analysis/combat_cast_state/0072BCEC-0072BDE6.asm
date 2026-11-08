0072bcec  6a01                     push       1
0072bcee  6a01                     push       1
0072bcf0  6a01                     push       1
0072bcf2  6a2f                     push       0x2f
0072bcf4  8bce                     mov        ecx, esi
0072bcf6  ff9068070000             call       dword ptr [eax + 0x768]
0072bcfc  84c0                     test       al, al
0072bcfe  0f84f4000000             je         0x72bdf8
0072bd04  895d80                   mov        dword ptr [ebp - 0x80], ebx
0072bd07  895d84                   mov        dword ptr [ebp - 0x7c], ebx
0072bd0a  895d88                   mov        dword ptr [ebp - 0x78], ebx
0072bd0d  8d4dec                   lea        ecx, [ebp - 0x14]
0072bd10  51                       push       ecx
0072bd11  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd17  c745fc28000000           mov        dword ptr [ebp - 4], 0x28
0072bd1e  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072bd21  e8fab3cdff               call       0x407120
0072bd26  8d55ec                   lea        edx, [ebp - 0x14]
0072bd29  52                       push       edx
0072bd2a  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd30  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072bd33  e8e8b3cdff               call       0x407120
0072bd38  8d45ec                   lea        eax, [ebp - 0x14]
0072bd3b  50                       push       eax
0072bd3c  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd42  c745ec2f000000           mov        dword ptr [ebp - 0x14], 0x2f
0072bd49  e8d2b3cdff               call       0x407120
0072bd4e  8b16                     mov        edx, dword ptr [esi]
0072bd50  6a2f                     push       0x2f
0072bd52  8bce                     mov        ecx, esi
0072bd54  ff924c060000             call       dword ptr [edx + 0x64c]
0072bd5a  50                       push       eax
0072bd5b  56                       push       esi
0072bd5c  8bcf                     mov        ecx, edi
0072bd5e  e8cdc6d3ff               call       0x468430
0072bd63  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072bd66  8d45ec                   lea        eax, [ebp - 0x14]
0072bd69  50                       push       eax
0072bd6a  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd70  e8abb3cdff               call       0x407120
0072bd75  56                       push       esi
0072bd76  53                       push       ebx
0072bd77  8bcf                     mov        ecx, edi
0072bd79  e8e241e2ff               call       0x54ff60
0072bd7e  8d4dec                   lea        ecx, [ebp - 0x14]
0072bd81  51                       push       ecx
0072bd82  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd88  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072bd8b  e890b3cdff               call       0x407120
0072bd90  8d55ec                   lea        edx, [ebp - 0x14]
0072bd93  52                       push       edx
0072bd94  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bd9a  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072bda1  e87ab3cdff               call       0x407120
0072bda6  8d45ec                   lea        eax, [ebp - 0x14]
0072bda9  bf04000000               mov        edi, 4
0072bdae  50                       push       eax
0072bdaf  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bdb5  897dec                   mov        dword ptr [ebp - 0x14], edi
0072bdb8  e863b3cdff               call       0x407120
0072bdbd  8d4dec                   lea        ecx, [ebp - 0x14]
0072bdc0  51                       push       ecx
0072bdc1  8d8d7cffffff             lea        ecx, [ebp - 0x84]
0072bdc7  897dec                   mov        dword ptr [ebp - 0x14], edi
0072bdca  e851b3cdff               call       0x407120
0072bdcf  8b16                     mov        edx, dword ptr [esi]
0072bdd1  53                       push       ebx
0072bdd2  53                       push       ebx
0072bdd3  6a01                     push       1
0072bdd5  8d857cffffff             lea        eax, [ebp - 0x84]
0072bddb  50                       push       eax
0072bddc  6a0a                     push       0xa
0072bdde  8bce                     mov        ecx, esi
0072bde0  ff928c020000             call       dword ptr [edx + 0x28c]