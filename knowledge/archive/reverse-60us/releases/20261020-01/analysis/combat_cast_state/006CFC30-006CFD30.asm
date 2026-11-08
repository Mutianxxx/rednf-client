006cfc30  55                       push       ebp
006cfc31  8bec                     mov        ebp, esp
006cfc33  6aff                     push       -1
006cfc35  6868e6c600               push       0xc6e668
006cfc3a  64a100000000             mov        eax, dword ptr fs:[0]
006cfc40  50                       push       eax
006cfc41  64892500000000           mov        dword ptr fs:[0], esp
006cfc48  81ec10050000             sub        esp, 0x510
006cfc4e  53                       push       ebx
006cfc4f  56                       push       esi
006cfc50  57                       push       edi
006cfc51  8bf1                     mov        esi, ecx
006cfc53  e878fddeff               call       0x4bf9d0
006cfc58  8d9e80180000             lea        ebx, [esi + 0x1880]
006cfc5e  8bcb                     mov        ecx, ebx
006cfc60  e8fb23d3ff               call       0x402060
006cfc65  85c0                     test       eax, eax
006cfc67  0f84af000000             je         0x6cfd1c
006cfc6d  8a86882c0000             mov        al, byte ptr [esi + 0x2c88]
006cfc73  84c0                     test       al, al
006cfc75  0f85a1000000             jne        0x6cfd1c
006cfc7b  8b86842c0000             mov        eax, dword ptr [esi + 0x2c84]
006cfc81  85c0                     test       eax, eax
006cfc83  754a                     jne        0x6cfccf
006cfc85  68f4070000               push       0x7f4
006cfc8a  e8c13fd3ff               call       0x403c50
006cfc8f  83c404                   add        esp, 4
006cfc92  8945f0                   mov        dword ptr [ebp - 0x10], eax
006cfc95  85c0                     test       eax, eax
006cfc97  c745fc00000000           mov        dword ptr [ebp - 4], 0
006cfc9e  7420                     je         0x6cfcc0
006cfca0  8a8e681b0000             mov        cl, byte ptr [esi + 0x1b68]
006cfca6  84c9                     test       cl, cl
006cfca8  ba48f1d600               mov        edx, 0xd6f148
006cfcad  7505                     jne        0x6cfcb4
006cfcaf  baf8f0d600               mov        edx, 0xd6f0f8
006cfcb4  6a00                     push       0
006cfcb6  52                       push       edx
006cfcb7  8bc8                     mov        ecx, eax
006cfcb9  e8c279e1ff               call       0x4e7680
006cfcbe  eb02                     jmp        0x6cfcc2
006cfcc0  33c0                     xor        eax, eax
006cfcc2  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
006cfcc9  8986842c0000             mov        dword ptr [esi + 0x2c84], eax
006cfccf  8b8e842c0000             mov        ecx, dword ptr [esi + 0x2c84]
006cfcd5  8b06                     mov        eax, dword ptr [esi]
006cfcd7  51                       push       ecx
006cfcd8  8bce                     mov        ecx, esi
006cfcda  ff9024040000             call       dword ptr [eax + 0x424]
006cfce0  8b86842c0000             mov        eax, dword ptr [esi + 0x2c84]
006cfce6  8b16                     mov        edx, dword ptr [esi]
006cfce8  50                       push       eax
006cfce9  8bce                     mov        ecx, esi
006cfceb  ff920c060000             call       dword ptr [edx + 0x60c]
006cfcf1  8b86842c0000             mov        eax, dword ptr [esi + 0x2c84]
006cfcf7  8b16                     mov        edx, dword ptr [esi]
006cfcf9  50                       push       eax
006cfcfa  8bce                     mov        ecx, esi
006cfcfc  ff921c040000             call       dword ptr [edx + 0x41c]
006cfd02  8b86842c0000             mov        eax, dword ptr [esi + 0x2c84]
006cfd08  8b16                     mov        edx, dword ptr [esi]
006cfd0a  50                       push       eax
006cfd0b  8bce                     mov        ecx, esi
006cfd0d  ff9208060000             call       dword ptr [edx + 0x608]
006cfd13  c686882c000001           mov        byte ptr [esi + 0x2c88], 1
006cfd1a  eb48                     jmp        0x6cfd64
006cfd1c  8b86842c0000             mov        eax, dword ptr [esi + 0x2c84]
006cfd22  85c0                     test       eax, eax
006cfd24  743e                     je         0x6cfd64
006cfd26  8bcb                     mov        ecx, ebx
006cfd28  e83323d3ff               call       0x402060
006cfd2d  85c0                     test       eax, eax
006cfd2f  75                       .byte      0x75