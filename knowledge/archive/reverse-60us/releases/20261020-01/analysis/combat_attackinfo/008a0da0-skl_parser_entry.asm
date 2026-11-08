008a0da0  55                       push       ebp
008a0da1  8bec                     mov        ebp, esp
008a0da3  6aff                     push       -1
008a0da5  68db24c800               push       0xc824db
008a0daa  64a100000000             mov        eax, dword ptr fs:[0]
008a0db0  50                       push       eax
008a0db1  64892500000000           mov        dword ptr fs:[0], esp
008a0db8  81ec80010000             sub        esp, 0x180
008a0dbe  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008a0dc1  50                       push       eax
008a0dc2  6878ee0b01               push       0x10bee78
008a0dc7  e8c4e9f8ff               call       0x82f790
008a0dcc  83c408                   add        esp, 8
008a0dcf  84c0                     test       al, al
008a0dd1  750e                     jne        0x8a0de1
008a0dd3  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a0dd6  64890d00000000           mov        dword ptr fs:[0], ecx
008a0ddd  8be5                     mov        esp, ebp
008a0ddf  5d                       pop        ebp
008a0de0  c3                       ret        
008a0de1  53                       push       ebx
008a0de2  56                       push       esi
008a0de3  57                       push       edi
008a0de4  8b7d08                   mov        edi, dword ptr [ebp + 8]
008a0de7  8bcf                     mov        ecx, edi
008a0de9  e8823fcbff               call       0x554d70
008a0dee  33c0                     xor        eax, eax
008a0df0  b907000000               mov        ecx, 7
008a0df5  894de0                   mov        dword ptr [ebp - 0x20], ecx
008a0df8  8945dc                   mov        dword ptr [ebp - 0x24], eax
008a0dfb  668945cc                 mov        word ptr [ebp - 0x34], ax
008a0dff  8945fc                   mov        dword ptr [ebp - 4], eax
008a0e02  894da0                   mov        dword ptr [ebp - 0x60], ecx
008a0e05  89459c                   mov        dword ptr [ebp - 0x64], eax
008a0e08  6689458c                 mov        word ptr [ebp - 0x74], ax
008a0e0c  8d4dc8                   lea        ecx, [ebp - 0x38]
008a0e0f  6a01                     push       1
008a0e11  51                       push       ecx
008a0e12  c645fc01                 mov        byte ptr [ebp - 4], 1
008a0e16  8845f3                   mov        byte ptr [ebp - 0xd], al
008a0e19  e8c2f9f8ff               call       0x8307e0
008a0e1e  83c408                   add        esp, 8
008a0e21  84c0                     test       al, al
008a0e23  0f84d5140000             je         0x8a22fe
008a0e29  8da42400000000           lea        esp, [esp]
008a0e30  8d55c8                   lea        edx, [ebp - 0x38]
008a0e33  52                       push       edx
008a0e34  e8a7f1f8ff               call       0x82ffe0
008a0e39  8b4514                   mov        eax, dword ptr [ebp + 0x14]
008a0e3c  50                       push       eax
008a0e3d  8d4dc8                   lea        ecx, [ebp - 0x38]
008a0e40  51                       push       ecx
008a0e41  57                       push       edi
008a0e42  e839f5ffff               call       0x8a0380
008a0e47  83c410                   add        esp, 0x10
008a0e4a  84c0                     test       al, al
008a0e4c  0f                       .byte      0x0f
008a0e4d  84                       .byte      0x84
