00ca1c00  55                       push       ebp
00ca1c01  8bec                     mov        ebp, esp
00ca1c03  51                       push       ecx
00ca1c04  8d45fc                   lea        eax, [ebp - 4]
00ca1c07  50                       push       eax
00ca1c08  b904340001               mov        ecx, 0x1003404
00ca1c0d  c745fc0000c842           mov        dword ptr [ebp - 4], 0x42c80000
00ca1c14  e8f7b37aff               call       0x44d010
00ca1c19  683087ca00               push       0xca8730
00ca1c1e  e81eeef5ff               call       0xc00a41
00ca1c23  83c404                   add        esp, 4
00ca1c26  8be5                     mov        esp, ebp
00ca1c28  5d                       pop        ebp
00ca1c29  c3                       ret        
