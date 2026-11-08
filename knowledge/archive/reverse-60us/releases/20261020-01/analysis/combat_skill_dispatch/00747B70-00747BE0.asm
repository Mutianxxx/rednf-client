00747b70  55                       push       ebp
00747b71  8bec                     mov        ebp, esp
00747b73  6aff                     push       -1
00747b75  681040c700               push       0xc74010
00747b7a  64a100000000             mov        eax, dword ptr fs:[0]
00747b80  50                       push       eax
00747b81  64892500000000           mov        dword ptr fs:[0], esp
00747b88  51                       push       ecx
00747b89  8b4508                   mov        eax, dword ptr [ebp + 8]
00747b8c  53                       push       ebx
00747b8d  56                       push       esi
00747b8e  57                       push       edi
00747b8f  50                       push       eax
00747b90  8bf1                     mov        esi, ecx
00747b92  6a03                     push       3
00747b94  8975f0                   mov        dword ptr [ebp - 0x10], esi
00747b97  e8d4eaffff               call       0x746670
00747b9c  8d9e102b0000             lea        ebx, [esi + 0x2b10]
00747ba2  33ff                     xor        edi, edi
00747ba4  8bcb                     mov        ecx, ebx
00747ba6  897dfc                   mov        dword ptr [ebp - 4], edi
00747ba9  c7063427d800             mov        dword ptr [esi], 0xd82734
00747baf  e86ca33000               call       0xa51f20
00747bb4  8bcb                     mov        ecx, ebx
00747bb6  e865a43000               call       0xa52020
00747bbb  89beec2c0000             mov        dword ptr [esi + 0x2cec], edi
00747bc1  89bef02c0000             mov        dword ptr [esi + 0x2cf0], edi
00747bc7  89bef42c0000             mov        dword ptr [esi + 0x2cf4], edi
00747bcd  68504d6400               push       0x644d50
00747bd2  6880c96d00               push       0x6dc980
00747bd7  6a02                     push       2
00747bd9  6a10                     push       0x10
00747bdb  8d                       .byte      0x8d
00747bdc  8e                       .byte      0x8e
00747bdd  2c2d                     sub        al, 0x2d
00747bdf  00                       .byte      0x00