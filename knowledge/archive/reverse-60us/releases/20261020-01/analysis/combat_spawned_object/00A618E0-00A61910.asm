00a618e0  55                       push       ebp
00a618e1  8bec                     mov        ebp, esp
00a618e3  6aff                     push       -1
00a618e5  68c110c900               push       0xc910c1
00a618ea  64a100000000             mov        eax, dword ptr fs:[0]
00a618f0  50                       push       eax
00a618f1  64892500000000           mov        dword ptr fs:[0], esp
00a618f8  51                       push       ecx
00a618f9  8b8120020000             mov        eax, dword ptr [ecx + 0x220]
00a618ff  83f814                   cmp        eax, 0x14
00a61902  56                       push       esi
00a61903  0f87cd060000             ja         0xa61fd6
00a61909  ff2485ec1fa600           jmp        dword ptr [eax*4 + 0xa61fec]