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
007469f3  8d8e2c2b0000             lea        ecx, [esi + 0x2b2c]
007469f9  c645fc01                 mov        byte ptr [ebp - 4], 1
007469fd  e8dedacbff               call       0x4044e0
00746a02  8d550b                   lea        edx, [ebp + 0xb]
00746a05  52                       push       edx
00746a06  8d450b                   lea        eax, [ebp + 0xb]
00746a09  8d8e6c2b0000             lea        ecx, [esi + 0x2b6c]
00746a0f  50                       push       eax
00746a10  c645fc02                 mov        byte ptr [ebp - 4], 2
00746a14  e827d7ffff               call       0x744140
00746a19  8d8eb02b0000             lea        ecx, [esi + 0x2bb0]
00746a1f  c645fc03                 mov        byte ptr [ebp - 4], 3
00746a23  e8b8dacbff               call       0x4044e0
00746a28  8d550b                   lea        edx, [ebp + 0xb]
00746a2b  52                       push       edx
00746a2c  8d450b                   lea        eax, [ebp + 0xb]
00746a2f  8d                       .byte      0x8d