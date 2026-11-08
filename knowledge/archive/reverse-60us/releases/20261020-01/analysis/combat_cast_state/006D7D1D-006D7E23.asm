006d7d1d  6a01                     push       1
006d7d1f  6a01                     push       1
006d7d21  6a01                     push       1
006d7d23  6a36                     push       0x36
006d7d25  8bce                     mov        ecx, esi
006d7d27  ff9068070000             call       dword ptr [eax + 0x768]
006d7d2d  84c0                     test       al, al
006d7d2f  0f841a010000             je         0x6d7e4f
006d7d35  8b16                     mov        edx, dword ptr [esi]
006d7d37  6a36                     push       0x36
006d7d39  8bce                     mov        ecx, esi
006d7d3b  ff927c060000             call       dword ptr [edx + 0x67c]
006d7d41  8bd8                     mov        ebx, eax
006d7d43  89bda8feffff             mov        dword ptr [ebp - 0x158], edi
006d7d49  89bdacfeffff             mov        dword ptr [ebp - 0x154], edi
006d7d4f  89bdb0feffff             mov        dword ptr [ebp - 0x150], edi
006d7d55  8d45f0                   lea        eax, [ebp - 0x10]
006d7d58  50                       push       eax
006d7d59  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7d5f  c745fc56000000           mov        dword ptr [ebp - 4], 0x56
006d7d66  897df0                   mov        dword ptr [ebp - 0x10], edi
006d7d69  e8b2f3d2ff               call       0x407120
006d7d6e  8d4df0                   lea        ecx, [ebp - 0x10]
006d7d71  51                       push       ecx
006d7d72  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7d78  897df0                   mov        dword ptr [ebp - 0x10], edi
006d7d7b  e8a0f3d2ff               call       0x407120
006d7d80  8d55f0                   lea        edx, [ebp - 0x10]
006d7d83  52                       push       edx
006d7d84  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7d8a  c745f036000000           mov        dword ptr [ebp - 0x10], 0x36
006d7d91  e88af3d2ff               call       0x407120
006d7d96  56                       push       esi
006d7d97  57                       push       edi
006d7d98  8bcb                     mov        ecx, ebx
006d7d9a  e8c181e7ff               call       0x54ff60
006d7d9f  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d7da2  8d45f0                   lea        eax, [ebp - 0x10]
006d7da5  50                       push       eax
006d7da6  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7dac  e86ff3d2ff               call       0x407120
006d7db1  56                       push       esi
006d7db2  6a01                     push       1
006d7db4  8bcb                     mov        ecx, ebx
006d7db6  e8a581e7ff               call       0x54ff60
006d7dbb  8d4df0                   lea        ecx, [ebp - 0x10]
006d7dbe  51                       push       ecx
006d7dbf  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7dc5  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d7dc8  e853f3d2ff               call       0x407120
006d7dcd  8d55f0                   lea        edx, [ebp - 0x10]
006d7dd0  52                       push       edx
006d7dd1  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7dd7  c745f001000000           mov        dword ptr [ebp - 0x10], 1
006d7dde  e83df3d2ff               call       0x407120
006d7de3  8d45f0                   lea        eax, [ebp - 0x10]
006d7de6  bb03000000               mov        ebx, 3
006d7deb  50                       push       eax
006d7dec  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7df2  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d7df5  e826f3d2ff               call       0x407120
006d7dfa  8d4df0                   lea        ecx, [ebp - 0x10]
006d7dfd  51                       push       ecx
006d7dfe  8d8da4feffff             lea        ecx, [ebp - 0x15c]
006d7e04  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d7e07  e814f3d2ff               call       0x407120
006d7e0c  8b16                     mov        edx, dword ptr [esi]
006d7e0e  57                       push       edi
006d7e0f  57                       push       edi
006d7e10  6a01                     push       1
006d7e12  8d85a4feffff             lea        eax, [ebp - 0x15c]
006d7e18  50                       push       eax
006d7e19  6a0a                     push       0xa
006d7e1b  8bce                     mov        ecx, esi
006d7e1d  ff928c020000             call       dword ptr [edx + 0x28c]