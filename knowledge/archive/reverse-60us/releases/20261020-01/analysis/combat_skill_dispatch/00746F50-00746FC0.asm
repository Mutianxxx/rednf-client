00746f50  55                       push       ebp
00746f51  8bec                     mov        ebp, esp
00746f53  6aff                     push       -1
00746f55  68923bc700               push       0xc73b92
00746f5a  64a100000000             mov        eax, dword ptr fs:[0]
00746f60  50                       push       eax
00746f61  64892500000000           mov        dword ptr fs:[0], esp
00746f68  51                       push       ecx
00746f69  8b4508                   mov        eax, dword ptr [ebp + 8]
00746f6c  53                       push       ebx
00746f6d  56                       push       esi
00746f6e  57                       push       edi
00746f6f  50                       push       eax
00746f70  8bf1                     mov        esi, ecx
00746f72  6a01                     push       1
00746f74  8975f0                   mov        dword ptr [ebp - 0x10], esi
00746f77  e8f4f6ffff               call       0x746670
00746f7c  8d9ef02a0000             lea        ebx, [esi + 0x2af0]
00746f82  33ff                     xor        edi, edi
00746f84  8bcb                     mov        ecx, ebx
00746f86  897dfc                   mov        dword ptr [ebp - 4], edi
00746f89  c7067417d800             mov        dword ptr [esi], 0xd81774
00746f8f  e88caf3000               call       0xa51f20
00746f94  8bcb                     mov        ecx, ebx
00746f96  e885b03000               call       0xa52020
00746f9b  68906f8d00               push       0x8d6f90
00746fa0  68d05e8d00               push       0x8d5ed0
00746fa5  6a04                     push       4
00746fa7  6a14                     push       0x14
00746fa9  8d8e282b0000             lea        ecx, [esi + 0x2b28]
00746faf  51                       push       ecx
00746fb0  c645fc01                 mov        byte ptr [ebp - 4], 1
00746fb4  e8ab984b00               call       0xc00864
00746fb9  68f03e4000               push       0x403ef0
00746fbe  68                       .byte      0x68
00746fbf  d0                       .byte      0xd0