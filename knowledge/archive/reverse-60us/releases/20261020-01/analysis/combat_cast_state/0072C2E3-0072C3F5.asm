0072c2e3  6a01                     push       1
0072c2e5  6a01                     push       1
0072c2e7  6a01                     push       1
0072c2e9  6a22                     push       0x22
0072c2eb  8bce                     mov        ecx, esi
0072c2ed  ff9068070000             call       dword ptr [eax + 0x768]
0072c2f3  84c0                     test       al, al
0072c2f5  0f840c010000             je         0x72c407
0072c2fb  8b16                     mov        edx, dword ptr [esi]
0072c2fd  6a22                     push       0x22
0072c2ff  8bce                     mov        ecx, esi
0072c301  ff927c060000             call       dword ptr [edx + 0x67c]
0072c307  8bf8                     mov        edi, eax
0072c309  899d00ffffff             mov        dword ptr [ebp - 0x100], ebx
0072c30f  899d04ffffff             mov        dword ptr [ebp - 0xfc], ebx
0072c315  899d08ffffff             mov        dword ptr [ebp - 0xf8], ebx
0072c31b  8d45ec                   lea        eax, [ebp - 0x14]
0072c31e  50                       push       eax
0072c31f  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c325  c745fc2c000000           mov        dword ptr [ebp - 4], 0x2c
0072c32c  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072c32f  e8ecadcdff               call       0x407120
0072c334  8d4dec                   lea        ecx, [ebp - 0x14]
0072c337  51                       push       ecx
0072c338  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c33e  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072c341  e8daadcdff               call       0x407120
0072c346  8d55ec                   lea        edx, [ebp - 0x14]
0072c349  52                       push       edx
0072c34a  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c350  c745ec22000000           mov        dword ptr [ebp - 0x14], 0x22
0072c357  e8c4adcdff               call       0x407120
0072c35c  8b06                     mov        eax, dword ptr [esi]
0072c35e  6a22                     push       0x22
0072c360  8bce                     mov        ecx, esi
0072c362  ff904c060000             call       dword ptr [eax + 0x64c]
0072c368  50                       push       eax
0072c369  56                       push       esi
0072c36a  8bcf                     mov        ecx, edi
0072c36c  e8bfc0d3ff               call       0x468430
0072c371  8d4dec                   lea        ecx, [ebp - 0x14]
0072c374  51                       push       ecx
0072c375  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c37b  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c37e  e89dadcdff               call       0x407120
0072c383  56                       push       esi
0072c384  6a01                     push       1
0072c386  8bcf                     mov        ecx, edi
0072c388  e8d33be2ff               call       0x54ff60
0072c38d  8d55ec                   lea        edx, [ebp - 0x14]
0072c390  52                       push       edx
0072c391  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c397  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c39a  e881adcdff               call       0x407120
0072c39f  8d45ec                   lea        eax, [ebp - 0x14]
0072c3a2  50                       push       eax
0072c3a3  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c3a9  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072c3b0  e86badcdff               call       0x407120
0072c3b5  8d4dec                   lea        ecx, [ebp - 0x14]
0072c3b8  51                       push       ecx
0072c3b9  bf04000000               mov        edi, 4
0072c3be  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c3c4  897dec                   mov        dword ptr [ebp - 0x14], edi
0072c3c7  e854adcdff               call       0x407120
0072c3cc  8d55ec                   lea        edx, [ebp - 0x14]
0072c3cf  52                       push       edx
0072c3d0  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c3d6  897dec                   mov        dword ptr [ebp - 0x14], edi
0072c3d9  e842adcdff               call       0x407120
0072c3de  8b06                     mov        eax, dword ptr [esi]
0072c3e0  53                       push       ebx
0072c3e1  53                       push       ebx
0072c3e2  6a01                     push       1
0072c3e4  8d8dfcfeffff             lea        ecx, [ebp - 0x104]
0072c3ea  51                       push       ecx
0072c3eb  6a0a                     push       0xa
0072c3ed  8bce                     mov        ecx, esi
0072c3ef  ff908c020000             call       dword ptr [eax + 0x28c]