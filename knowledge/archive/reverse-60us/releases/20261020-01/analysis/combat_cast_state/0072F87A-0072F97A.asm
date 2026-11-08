0072f87a  6a01                     push       1
0072f87c  6a01                     push       1
0072f87e  6a01                     push       1
0072f880  6a55                     push       0x55
0072f882  8bce                     mov        ecx, esi
0072f884  ff9068070000             call       dword ptr [eax + 0x768]
0072f88a  84c0                     test       al, al
0072f88c  0f84fa000000             je         0x72f98c
0072f892  8b16                     mov        edx, dword ptr [esi]
0072f894  6a55                     push       0x55
0072f896  8bce                     mov        ecx, esi
0072f898  ff927c060000             call       dword ptr [edx + 0x67c]
0072f89e  53                       push       ebx
0072f89f  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f8a5  8bf8                     mov        edi, eax
0072f8a7  e864d6d5ff               call       0x48cf10
0072f8ac  8d45ec                   lea        eax, [ebp - 0x14]
0072f8af  50                       push       eax
0072f8b0  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f8b6  c745fc5b000000           mov        dword ptr [ebp - 4], 0x5b
0072f8bd  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072f8c0  e85b78cdff               call       0x407120
0072f8c5  8d4dec                   lea        ecx, [ebp - 0x14]
0072f8c8  51                       push       ecx
0072f8c9  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f8cf  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072f8d2  e84978cdff               call       0x407120
0072f8d7  8d55ec                   lea        edx, [ebp - 0x14]
0072f8da  52                       push       edx
0072f8db  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f8e1  c745ec55000000           mov        dword ptr [ebp - 0x14], 0x55
0072f8e8  e83378cdff               call       0x407120
0072f8ed  56                       push       esi
0072f8ee  53                       push       ebx
0072f8ef  8bcf                     mov        ecx, edi
0072f8f1  e86a06e2ff               call       0x54ff60
0072f8f6  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072f8f9  8d45ec                   lea        eax, [ebp - 0x14]
0072f8fc  50                       push       eax
0072f8fd  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f903  e81878cdff               call       0x407120
0072f908  56                       push       esi
0072f909  6a01                     push       1
0072f90b  8bcf                     mov        ecx, edi
0072f90d  e84e06e2ff               call       0x54ff60
0072f912  8d4dec                   lea        ecx, [ebp - 0x14]
0072f915  51                       push       ecx
0072f916  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f91c  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072f91f  e8fc77cdff               call       0x407120
0072f924  8d55ec                   lea        edx, [ebp - 0x14]
0072f927  52                       push       edx
0072f928  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f92e  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072f935  e8e677cdff               call       0x407120
0072f93a  8d45ec                   lea        eax, [ebp - 0x14]
0072f93d  bf03000000               mov        edi, 3
0072f942  50                       push       eax
0072f943  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f949  897dec                   mov        dword ptr [ebp - 0x14], edi
0072f94c  e8cf77cdff               call       0x407120
0072f951  8d4dec                   lea        ecx, [ebp - 0x14]
0072f954  51                       push       ecx
0072f955  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
0072f95b  897dec                   mov        dword ptr [ebp - 0x14], edi
0072f95e  e8bd77cdff               call       0x407120
0072f963  8b16                     mov        edx, dword ptr [esi]
0072f965  53                       push       ebx
0072f966  53                       push       ebx
0072f967  6a01                     push       1
0072f969  8d85c4feffff             lea        eax, [ebp - 0x13c]
0072f96f  50                       push       eax
0072f970  6a0a                     push       0xa
0072f972  8bce                     mov        ecx, esi
0072f974  ff928c020000             call       dword ptr [edx + 0x28c]