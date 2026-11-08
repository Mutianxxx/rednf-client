006a49ee  6a01                     push       1
006a49f0  6a01                     push       1
006a49f2  6a01                     push       1
006a49f4  6a0d                     push       0xd
006a49f6  8bcb                     mov        ecx, ebx
006a49f8  ff9068070000             call       dword ptr [eax + 0x768]
006a49fe  84c0                     test       al, al
006a4a00  0f84e6000000             je         0x6a4aec
006a4a06  8b13                     mov        edx, dword ptr [ebx]
006a4a08  6a0d                     push       0xd
006a4a0a  8bcb                     mov        ecx, ebx
006a4a0c  ff927c060000             call       dword ptr [edx + 0x67c]
006a4a12  8bf0                     mov        esi, eax
006a4a14  897dac                   mov        dword ptr [ebp - 0x54], edi
006a4a17  897db0                   mov        dword ptr [ebp - 0x50], edi
006a4a1a  897db4                   mov        dword ptr [ebp - 0x4c], edi
006a4a1d  8d45f0                   lea        eax, [ebp - 0x10]
006a4a20  50                       push       eax
006a4a21  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a24  c745fc38000000           mov        dword ptr [ebp - 4], 0x38
006a4a2b  897df0                   mov        dword ptr [ebp - 0x10], edi
006a4a2e  e8ed26d6ff               call       0x407120
006a4a33  8d4df0                   lea        ecx, [ebp - 0x10]
006a4a36  51                       push       ecx
006a4a37  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a3a  897df0                   mov        dword ptr [ebp - 0x10], edi
006a4a3d  e8de26d6ff               call       0x407120
006a4a42  8d55f0                   lea        edx, [ebp - 0x10]
006a4a45  52                       push       edx
006a4a46  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a49  c745f00d000000           mov        dword ptr [ebp - 0x10], 0xd
006a4a50  e8cb26d6ff               call       0x407120
006a4a55  53                       push       ebx
006a4a56  57                       push       edi
006a4a57  8bce                     mov        ecx, esi
006a4a59  e802b5eaff               call       0x54ff60
006a4a5e  8945f0                   mov        dword ptr [ebp - 0x10], eax
006a4a61  8d45f0                   lea        eax, [ebp - 0x10]
006a4a64  50                       push       eax
006a4a65  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a68  e8b326d6ff               call       0x407120
006a4a6d  53                       push       ebx
006a4a6e  6a01                     push       1
006a4a70  8bce                     mov        ecx, esi
006a4a72  e8e9b4eaff               call       0x54ff60
006a4a77  8d4df0                   lea        ecx, [ebp - 0x10]
006a4a7a  51                       push       ecx
006a4a7b  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a7e  8945f0                   mov        dword ptr [ebp - 0x10], eax
006a4a81  e89a26d6ff               call       0x407120
006a4a86  8d55f0                   lea        edx, [ebp - 0x10]
006a4a89  52                       push       edx
006a4a8a  8d4da8                   lea        ecx, [ebp - 0x58]
006a4a8d  897df0                   mov        dword ptr [ebp - 0x10], edi
006a4a90  e88b26d6ff               call       0x407120
006a4a95  8d45f0                   lea        eax, [ebp - 0x10]
006a4a98  be02000000               mov        esi, 2
006a4a9d  50                       push       eax
006a4a9e  8d4da8                   lea        ecx, [ebp - 0x58]
006a4aa1  8975f0                   mov        dword ptr [ebp - 0x10], esi
006a4aa4  e87726d6ff               call       0x407120
006a4aa9  8d4df0                   lea        ecx, [ebp - 0x10]
006a4aac  51                       push       ecx
006a4aad  8d4da8                   lea        ecx, [ebp - 0x58]
006a4ab0  8975f0                   mov        dword ptr [ebp - 0x10], esi
006a4ab3  e86826d6ff               call       0x407120
006a4ab8  8b13                     mov        edx, dword ptr [ebx]
006a4aba  57                       push       edi
006a4abb  57                       push       edi
006a4abc  6a01                     push       1
006a4abe  8d45a8                   lea        eax, [ebp - 0x58]
006a4ac1  50                       push       eax
006a4ac2  6a0a                     push       0xa
006a4ac4  8bcb                     mov        ecx, ebx
006a4ac6  ff928c020000             call       dword ptr [edx + 0x28c]