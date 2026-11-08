006d7b80  6a01                     push       1
006d7b82  6a01                     push       1
006d7b84  6a01                     push       1
006d7b86  6a46                     push       0x46
006d7b88  8bce                     mov        ecx, esi
006d7b8a  ff9268070000             call       dword ptr [edx + 0x768]
006d7b90  84c0                     test       al, al
006d7b92  0f841a010000             je         0x6d7cb2
006d7b98  8b06                     mov        eax, dword ptr [esi]
006d7b9a  6a46                     push       0x46
006d7b9c  8bce                     mov        ecx, esi
006d7b9e  ff907c060000             call       dword ptr [eax + 0x67c]
006d7ba4  8bd8                     mov        ebx, eax
006d7ba6  89bd38ffffff             mov        dword ptr [ebp - 0xc8], edi
006d7bac  89bd3cffffff             mov        dword ptr [ebp - 0xc4], edi
006d7bb2  89bd40ffffff             mov        dword ptr [ebp - 0xc0], edi
006d7bb8  8d4df0                   lea        ecx, [ebp - 0x10]
006d7bbb  51                       push       ecx
006d7bbc  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7bc2  c745fc55000000           mov        dword ptr [ebp - 4], 0x55
006d7bc9  897df0                   mov        dword ptr [ebp - 0x10], edi
006d7bcc  e84ff5d2ff               call       0x407120
006d7bd1  8d55f0                   lea        edx, [ebp - 0x10]
006d7bd4  52                       push       edx
006d7bd5  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7bdb  897df0                   mov        dword ptr [ebp - 0x10], edi
006d7bde  e83df5d2ff               call       0x407120
006d7be3  8d45f0                   lea        eax, [ebp - 0x10]
006d7be6  50                       push       eax
006d7be7  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7bed  c745f046000000           mov        dword ptr [ebp - 0x10], 0x46
006d7bf4  e827f5d2ff               call       0x407120
006d7bf9  56                       push       esi
006d7bfa  57                       push       edi
006d7bfb  8bcb                     mov        ecx, ebx
006d7bfd  e85e83e7ff               call       0x54ff60
006d7c02  8d4df0                   lea        ecx, [ebp - 0x10]
006d7c05  51                       push       ecx
006d7c06  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c0c  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d7c0f  e80cf5d2ff               call       0x407120
006d7c14  56                       push       esi
006d7c15  6a01                     push       1
006d7c17  8bcb                     mov        ecx, ebx
006d7c19  e84283e7ff               call       0x54ff60
006d7c1e  8d55f0                   lea        edx, [ebp - 0x10]
006d7c21  52                       push       edx
006d7c22  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c28  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d7c2b  e8f0f4d2ff               call       0x407120
006d7c30  8d45f0                   lea        eax, [ebp - 0x10]
006d7c33  50                       push       eax
006d7c34  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c3a  c745f001000000           mov        dword ptr [ebp - 0x10], 1
006d7c41  e8daf4d2ff               call       0x407120
006d7c46  8d4df0                   lea        ecx, [ebp - 0x10]
006d7c49  51                       push       ecx
006d7c4a  bb03000000               mov        ebx, 3
006d7c4f  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c55  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d7c58  e8c3f4d2ff               call       0x407120
006d7c5d  8d55f0                   lea        edx, [ebp - 0x10]
006d7c60  52                       push       edx
006d7c61  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c67  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d7c6a  e8b1f4d2ff               call       0x407120
006d7c6f  8b06                     mov        eax, dword ptr [esi]
006d7c71  57                       push       edi
006d7c72  57                       push       edi
006d7c73  6a01                     push       1
006d7c75  8d8d34ffffff             lea        ecx, [ebp - 0xcc]
006d7c7b  51                       push       ecx
006d7c7c  6a0a                     push       0xa
006d7c7e  8bce                     mov        ecx, esi
006d7c80  ff908c020000             call       dword ptr [eax + 0x28c]