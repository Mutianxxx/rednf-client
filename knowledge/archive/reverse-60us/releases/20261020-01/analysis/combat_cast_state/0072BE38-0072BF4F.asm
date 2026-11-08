0072be38  6a01                     push       1
0072be3a  6a01                     push       1
0072be3c  6a01                     push       1
0072be3e  6a12                     push       0x12
0072be40  8bce                     mov        ecx, esi
0072be42  ff9068070000             call       dword ptr [eax + 0x768]
0072be48  84c0                     test       al, al
0072be4a  0f8411010000             je         0x72bf61
0072be50  899d70ffffff             mov        dword ptr [ebp - 0x90], ebx
0072be56  899d74ffffff             mov        dword ptr [ebp - 0x8c], ebx
0072be5c  899d78ffffff             mov        dword ptr [ebp - 0x88], ebx
0072be62  8d4dec                   lea        ecx, [ebp - 0x14]
0072be65  51                       push       ecx
0072be66  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072be6c  c745fc29000000           mov        dword ptr [ebp - 4], 0x29
0072be73  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072be76  e8a5b2cdff               call       0x407120
0072be7b  8d55ec                   lea        edx, [ebp - 0x14]
0072be7e  52                       push       edx
0072be7f  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072be85  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072be88  e893b2cdff               call       0x407120
0072be8d  8d45ec                   lea        eax, [ebp - 0x14]
0072be90  50                       push       eax
0072be91  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072be97  c745ec12000000           mov        dword ptr [ebp - 0x14], 0x12
0072be9e  e87db2cdff               call       0x407120
0072bea3  8b16                     mov        edx, dword ptr [esi]
0072bea5  6a12                     push       0x12
0072bea7  8bce                     mov        ecx, esi
0072bea9  ff924c060000             call       dword ptr [edx + 0x64c]
0072beaf  50                       push       eax
0072beb0  8b06                     mov        eax, dword ptr [esi]
0072beb2  56                       push       esi
0072beb3  6a12                     push       0x12
0072beb5  8bce                     mov        ecx, esi
0072beb7  ff907c060000             call       dword ptr [eax + 0x67c]
0072bebd  8bc8                     mov        ecx, eax
0072bebf  e86cc5d3ff               call       0x468430
0072bec4  8d4dec                   lea        ecx, [ebp - 0x14]
0072bec7  51                       push       ecx
0072bec8  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072bece  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072bed1  e84ab2cdff               call       0x407120
0072bed6  8b16                     mov        edx, dword ptr [esi]
0072bed8  56                       push       esi
0072bed9  53                       push       ebx
0072beda  6a12                     push       0x12
0072bedc  8bce                     mov        ecx, esi
0072bede  ff927c060000             call       dword ptr [edx + 0x67c]
0072bee4  8bc8                     mov        ecx, eax
0072bee6  e87540e2ff               call       0x54ff60
0072beeb  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072beee  8d45ec                   lea        eax, [ebp - 0x14]
0072bef1  50                       push       eax
0072bef2  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072bef8  e823b2cdff               call       0x407120
0072befd  8d4dec                   lea        ecx, [ebp - 0x14]
0072bf00  51                       push       ecx
0072bf01  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072bf07  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072bf0a  e811b2cdff               call       0x407120
0072bf0f  8d55ec                   lea        edx, [ebp - 0x14]
0072bf12  bf04000000               mov        edi, 4
0072bf17  52                       push       edx
0072bf18  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072bf1e  897dec                   mov        dword ptr [ebp - 0x14], edi
0072bf21  e8fab1cdff               call       0x407120
0072bf26  8d45ec                   lea        eax, [ebp - 0x14]
0072bf29  50                       push       eax
0072bf2a  8d8d6cffffff             lea        ecx, [ebp - 0x94]
0072bf30  897dec                   mov        dword ptr [ebp - 0x14], edi
0072bf33  e8e8b1cdff               call       0x407120
0072bf38  8b16                     mov        edx, dword ptr [esi]
0072bf3a  53                       push       ebx
0072bf3b  53                       push       ebx
0072bf3c  6a01                     push       1
0072bf3e  8d856cffffff             lea        eax, [ebp - 0x94]
0072bf44  50                       push       eax
0072bf45  6a0a                     push       0xa
0072bf47  8bce                     mov        ecx, esi
0072bf49  ff928c020000             call       dword ptr [edx + 0x28c]