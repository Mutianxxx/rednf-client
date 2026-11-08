007469b0  55                       push       ebp
007469b1  8bec                     mov        ebp, esp
007469b3  6aff                     push       -1
007469b5  683e3ac700               push       0xc73a3e
007469ba  64a100000000             mov        eax, dword ptr fs:[0]
007469c0  50                       push       eax
007469c1  64892500000000           mov        dword ptr fs:[0], esp
007469c8  51                       push       ecx
007469c9  8b4508                   mov        eax, dword ptr [ebp + 8]
007469cc  56                       push       esi
007469cd  57                       push       edi
007469ce  50                       push       eax
007469cf  8bf1                     mov        esi, ecx
007469d1  6a00                     push       0
007469d3  8975f0                   mov        dword ptr [ebp - 0x10], esi
007469d6  e895fcffff               call       0x746670
007469db  8d8ea82a0000             lea        ecx, [esi + 0x2aa8]
007469e1  c745fc00000000           mov        dword ptr [ebp - 4], 0
007469e8  c706940fd800             mov        dword ptr [esi], 0xd80f94
007469ee  e8eddacbff               call       0x4044e0
