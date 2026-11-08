007488e0  55                       push       ebp
007488e1  8bec                     mov        ebp, esp
007488e3  6aff                     push       -1
007488e5  68d040c700               push       0xc740d0
007488ea  64a100000000             mov        eax, dword ptr fs:[0]
007488f0  50                       push       eax
007488f1  64892500000000           mov        dword ptr fs:[0], esp
007488f8  51                       push       ecx
007488f9  8b4508                   mov        eax, dword ptr [ebp + 8]
007488fc  53                       push       ebx
007488fd  56                       push       esi
007488fe  57                       push       edi
007488ff  50                       push       eax
00748900  8bf1                     mov        esi, ecx
00748902  6a04                     push       4
00748904  8975f0                   mov        dword ptr [ebp - 0x10], esi
00748907  e864ddffff               call       0x746670
0074890c  33db                     xor        ebx, ebx
0074890e  8d8eac2a0000             lea        ecx, [esi + 0x2aac]
00748914  895dfc                   mov        dword ptr [ebp - 4], ebx
00748917  c706642fd800             mov        dword ptr [esi], 0xd82f64
0074891d  e8bebbcbff               call       0x4044e0
00748922  8dbef82a0000             lea        edi, [esi + 0x2af8]
00748928  8bcf                     mov        ecx, edi
0074892a  c645fc01                 mov        byte ptr [ebp - 4], 1
0074892e  e8ed953000               call       0xa51f20
00748933  8bcf                     mov        ecx, edi
00748935  e8e6963000               call       0xa52020
0074893a  8d8e182b0000             lea        ecx, [esi + 0x2b18]
00748940  c645fc02                 mov        byte ptr [ebp - 4], 2
00748944  e897bbcbff               call       0x4044e0
00748949  8d8e302b0000             lea        ecx, [esi + 0x2b30]
0074894f  c6                       .byte      0xc6