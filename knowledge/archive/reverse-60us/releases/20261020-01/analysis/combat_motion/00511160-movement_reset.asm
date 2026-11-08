00511160  55                       push       ebp
00511161  8bec                     mov        ebp, esp
00511163  6aff                     push       -1
00511165  685ba5c500               push       0xc5a55b
0051116a  64a100000000             mov        eax, dword ptr fs:[0]
00511170  50                       push       eax
00511171  64892500000000           mov        dword ptr fs:[0], esp
00511178  51                       push       ecx
00511179  a1c05a0101               mov        eax, dword ptr [0x1015ac0]
0051117e  53                       push       ebx
0051117f  56                       push       esi
00511180  57                       push       edi
00511181  33db                     xor        ebx, ebx
00511183  83cfff                   or         edi, 0xffffffff
00511186  3bc3                     cmp        eax, ebx
00511188  8bf1                     mov        esi, ecx
0051118a  751e                     jne        0x5111aa
0051118c  6a24                     push       0x24
0051118e  e88ac76d00               call       0xbed91d
00511193  83c404                   add        esp, 4
00511196  8945f0                   mov        dword ptr [ebp - 0x10], eax
00511199  3bc3                     cmp        eax, ebx
0051119b  895dfc                   mov        dword ptr [ebp - 4], ebx
0051119e  7407                     je         0x5111a7
005111a0  8bc8                     mov        ecx, eax
005111a2  e8d9190000               call       0x512b80
005111a7  897dfc                   mov        dword ptr [ebp - 4], edi
005111aa  8b0dc05a0101             mov        ecx, dword ptr [0x1015ac0]
005111b0  56                       push       esi
005111b1  e81a1a0000               call       0x512bd0
005111b6  895e74                   mov        dword ptr [esi + 0x74], ebx
005111b9  895e78                   mov        dword ptr [esi + 0x78], ebx
005111bc  899e80000000             mov        dword ptr [esi + 0x80], ebx
005111c2  889e84000000             mov        byte ptr [esi + 0x84], bl
005111c8  b901000000               mov        ecx, 1
005111cd  884e7c                   mov        byte ptr [esi + 0x7c], cl
005111d0  33c0                     xor        eax, eax
005111d2  66898685000000           mov        word ptr [esi + 0x85], ax
005111d9  888687000000             mov        byte ptr [esi + 0x87], al
005111df  899e88000000             mov        dword ptr [esi + 0x88], ebx
005111e5  899e90000000             mov        dword ptr [esi + 0x90], ebx
005111eb  899e94000000             mov        dword ptr [esi + 0x94], ebx
005111f1  899e98000000             mov        dword ptr [esi + 0x98], ebx
005111f7  899e9c000000             mov        dword ptr [esi + 0x9c], ebx
005111fd  889ee0000000             mov        byte ptr [esi + 0xe0], bl
00511203  899ee4000000             mov        dword ptr [esi + 0xe4], ebx
00511209  899ee8000000             mov        dword ptr [esi + 0xe8], ebx
0051120f  899eec000000             mov        dword ptr [esi + 0xec], ebx
00511215  899ef0000000             mov        dword ptr [esi + 0xf0], ebx
0051121b  899ef4000000             mov        dword ptr [esi + 0xf4], ebx
00511221  895e04                   mov        dword ptr [esi + 4], ebx
00511224  889ef8000000             mov        byte ptr [esi + 0xf8], bl
0051122a  899efc000000             mov        dword ptr [esi + 0xfc], ebx
00511230  889e8c000000             mov        byte ptr [esi + 0x8c], bl
00511236  891e                     mov        dword ptr [esi], ebx
00511238  895e0c                   mov        dword ptr [esi + 0xc], ebx
0051123b  895e18                   mov        dword ptr [esi + 0x18], ebx
0051123e  895e24                   mov        dword ptr [esi + 0x24], ebx
00511241  897e30                   mov        dword ptr [esi + 0x30], edi
00511244  895e10                   mov        dword ptr [esi + 0x10], ebx
00511247  895e1c                   mov        dword ptr [esi + 0x1c], ebx
0051124a  895e28                   mov        dword ptr [esi + 0x28], ebx
0051124d  897e34                   mov        dword ptr [esi + 0x34], edi
00511250  895e14                   mov        dword ptr [esi + 0x14], ebx
00511253  895e20                   mov        dword ptr [esi + 0x20], ebx
00511256  895e2c                   mov        dword ptr [esi + 0x2c], ebx
00511259  897e38                   mov        dword ptr [esi + 0x38], edi
0051125c  884e3c                   mov        byte ptr [esi + 0x3c], cl
0051125f  8b4604                   mov        eax, dword ptr [esi + 4]
00511262  3bc3                     cmp        eax, ebx
00511264  7503                     jne        0x511269
00511266  8d463d                   lea        eax, [esi + 0x3d]
00511269  895804                   mov        dword ptr [eax + 4], ebx
0051126c  895810                   mov        dword ptr [eax + 0x10], ebx
0051126f  89581c                   mov        dword ptr [eax + 0x1c], ebx
00511272  897828                   mov        dword ptr [eax + 0x28], edi
00511275  895808                   mov        dword ptr [eax + 8], ebx
00511278  895814                   mov        dword ptr [eax + 0x14], ebx
0051127b  895820                   mov        dword ptr [eax + 0x20], ebx
0051127e  89782c                   mov        dword ptr [eax + 0x2c], edi
00511281  89580c                   mov        dword ptr [eax + 0xc], ebx
00511284  895818                   mov        dword ptr [eax + 0x18], ebx
00511287  89                       .byte      0x89
00511288  58                       pop        eax
