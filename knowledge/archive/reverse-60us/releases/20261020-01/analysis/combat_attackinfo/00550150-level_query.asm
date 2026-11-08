00550150  55                       push       ebp
00550151  8bec                     mov        ebp, esp
00550153  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00550156  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00550159  53                       push       ebx
0055015a  56                       push       esi
0055015b  57                       push       edi
0055015c  8b7d14                   mov        edi, dword ptr [ebp + 0x14]
0055015f  6a00                     push       0
00550161  6a00                     push       0
00550163  50                       push       eax
00550164  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00550167  8bf1                     mov        esi, ecx
00550169  8b4d18                   mov        ecx, dword ptr [ebp + 0x18]
0055016c  51                       push       ecx
0055016d  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00550170  57                       push       edi
00550171  52                       push       edx
00550172  50                       push       eax
00550173  51                       push       ecx
00550174  8bce                     mov        ecx, esi
00550176  e805ffffff               call       0x550080
0055017b  8b0d48280001             mov        ecx, dword ptr [0x1002848]
00550181  6aff                     push       -1
00550183  8bd8                     mov        ebx, eax
00550185  e866aaeeff               call       0x43abf0
0055018a  84c0                     test       al, al
0055018c  7513                     jne        0x5501a1
0055018e  8b0d48280001             mov        ecx, dword ptr [0x1002848]
00550194  e877a1eeff               call       0x43a310
00550199  84c0                     test       al, al
0055019b  0f84bb010000             je         0x55035c
005501a1  8d4e20                   lea        ecx, [esi + 0x20]
005501a4  e8b71eebff               call       0x402060
005501a9  83f801                   cmp        eax, 1
005501ac  0f8eaa010000             jle        0x55035c
005501b2  8d4e40                   lea        ecx, [esi + 0x40]
005501b5  e8a61eebff               call       0x402060
005501ba  85c0                     test       eax, eax
005501bc  0f849a010000             je         0x55035c
005501c2  83ffff                   cmp        edi, -1
005501c5  0f8491010000             je         0x55035c
005501cb  8d4e38                   lea        ecx, [esi + 0x38]
005501ce  e88d1eebff               call       0x402060
005501d3  8d4e40                   lea        ecx, [esi + 0x40]
005501d6  2bf8                     sub        edi, eax
005501d8  e8831eebff               call       0x402060
005501dd  8bc8                     mov        ecx, eax
005501df  8bc7                     mov        eax, edi
005501e1  99                       cdq        
005501e2  f7f9                     idiv       ecx
005501e4  8d9e78010000             lea        ebx, [esi + 0x178]
005501ea  8bcb                     mov        ecx, ebx
005501ec  8bf8                     mov        edi, eax
005501ee  47                       inc        edi
005501ef  e86c1eebff               call       0x402060
005501f4  3bf8                     cmp        edi, eax
005501f6  7c09                     jl         0x550201
005501f8  8bcb                     mov        ecx, ebx
005501fa  e8611eebff               call       0x402060
005501ff  8bf8                     mov        edi, eax
00550201  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00550204  6a00                     push       0
00550206  6a00                     push       0
00550208  6a0c                     push       0xc
0055020a  6aff                     push       -1
0055020c  6aff                     push       -1
0055020e  52                       push       edx
0055020f  8bcb                     mov        ecx, ebx
00550211  e84a1eebff               call       0x402060
00550216  50                       push       eax
00550217  8b4508                   mov        eax, dword ptr [ebp + 8]
0055021a  50                       push       eax
0055021b  8bce                     mov        ecx, esi
0055021d  e85efeffff               call       0x550080
00550222  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00550225  894510                   mov        dword ptr [ebp + 0x10], eax
00550228  db4510                   fild       dword ptr [ebp + 0x10]
0055022b  2bfa                     sub        edi, edx
0055022d  8bcb                     mov        ecx, ebx
0055022f  897d10                   mov        dword ptr [ebp + 0x10], edi
00550232  d95d14                   fstp       dword ptr [ebp + 0x14]
00550235  e8261eebff               call       0x402060
0055023a  83f801                   cmp        eax, 1
0055023d  6a00                     push       0
0055023f  6a00                     push       0
00550241  6a0c                     push       0xc
00550243  6aff                     push       -1
00550245  6aff                     push       -1
00550247  6a00                     push       0
00550249  7533                     jne        0x55027e
0055024b  8b7d08                   mov        edi, dword ptr [ebp + 8]
0055024e  6a02                     push       2
00550250  57                       push       edi
00550251  8bce                     mov        ecx, esi
00550253  e828feffff               call       0x550080
00550258  6a00                     push       0
0055025a  6a00                     push       0
0055025c  6a0c                     push       0xc
0055025e  6aff                     push       -1
00550260  6aff                     push       -1
00550262  6a00                     push       0
00550264  6a01                     push       1
00550266  57                       push       edi
00550267  8bce                     mov        ecx, esi
00550269  894508                   mov        dword ptr [ebp + 8], eax
0055026c  e80ffeffff               call       0x550080
00550271  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00550274  2bc8                     sub        ecx, eax
00550276  894d08                   mov        dword ptr [ebp + 8], ecx
00550279  db4508                   fild       dword ptr [ebp + 8]
0055027c  eb4a                     jmp        0x5502c8
0055027e  8bcb                     mov        ecx, ebx
00550280  e8db1debff               call       0x402060
00550285  8b7d08                   mov        edi, dword ptr [ebp + 8]
00550288  50                       push       eax
00550289  57                       push       edi
0055028a  8bce                     mov        ecx, esi
0055028c  e8effdffff               call       0x550080
00550291  6a00                     push       0
00550293  6a00                     push       0
00550295  6a0c                     push       0xc
00550297  6aff                     push       -1
00550299  6aff                     push       -1
0055029b  6a00                     push       0
0055029d  6a01                     push       1
0055029f  57                       push       edi
005502a0  8bce                     mov        ecx, esi
005502a2  894508                   mov        dword ptr [ebp + 8], eax
005502a5  e8d6fdffff               call       0x550080
005502aa  8b4d08                   mov        ecx, dword ptr [ebp + 8]
005502ad  2bc8                     sub        ecx, eax
005502af  894d08                   mov        dword ptr [ebp + 8], ecx
005502b2  8bcb                     mov        ecx, ebx
005502b4  e8a71debff               call       0x402060
005502b9  8bc8                     mov        ecx, eax
005502bb  8b4508                   mov        eax, dword ptr [ebp + 8]
005502be  99                       cdq        
005502bf  49                       dec        ecx
005502c0  f7f9                     idiv       ecx
005502c2  894508                   mov        dword ptr [ebp + 8], eax
005502c5  db4508                   fild       dword ptr [ebp + 8]
005502c8  db4510                   fild       dword ptr [ebp + 0x10]
005502cb  51                       push       ecx
005502cc  d8c9                     fmul       st(1)
005502ce  d86d14                   fsubr      dword ptr [ebp + 0x14]
005502d1  d91c24                   fstp       dword ptr [esp]
005502d4  ddd8                     fstp       st(0)
005502d6  e8157defff               call       0x447ff0
005502db  8b7d1c                   mov        edi, dword ptr [ebp + 0x1c]
005502de  894508                   mov        dword ptr [ebp + 8], eax
005502e1  db4508                   fild       dword ptr [ebp + 8]
005502e4  83c404                   add        esp, 4
005502e7  83ff0c                   cmp        edi, 0xc
005502ea  d95d08                   fstp       dword ptr [ebp + 8]
005502ed  7437                     je         0x550326
005502ef  8bcb                     mov        ecx, ebx
005502f1  e86a1debff               call       0x402060
005502f6  50                       push       eax
005502f7  8bce                     mov        ecx, esi
005502f9  e8a2380000               call       0x553ba0
005502fe  8b7518                   mov        esi, dword ptr [ebp + 0x18]
00550301  3bf0                     cmp        esi, eax
00550303  7d21                     jge        0x550326
00550305  6a00                     push       0
00550307  57                       push       edi
00550308  50                       push       eax
00550309  e8427eefff               call       0x448150
0055030e  d84d08                   fmul       dword ptr [ebp + 8]
00550311  6a00                     push       0
00550313  57                       push       edi
00550314  56                       push       esi
00550315  d95d08                   fstp       dword ptr [ebp + 8]
00550318  e8337eefff               call       0x448150
0055031d  d87d08                   fdivr      dword ptr [ebp + 8]
00550320  83c418                   add        esp, 0x18
00550323  d95d08                   fstp       dword ptr [ebp + 8]
00550326  8b0d48280001             mov        ecx, dword ptr [0x1002848]
0055032c  e8df9feeff               call       0x43a310
00550331  84c0                     test       al, al
00550333  7408                     je         0x55033d
00550335  d90558e9f500             fld        dword ptr [0xf5e958]
0055033b  eb06                     jmp        0x550343
0055033d  d90554e9f500             fld        dword ptr [0xf5e954]
00550343  d84d08                   fmul       dword ptr [ebp + 8]
00550346  d95d08                   fstp       dword ptr [ebp + 8]
00550349  8b5508                   mov        edx, dword ptr [ebp + 8]
0055034c  52                       push       edx
0055034d  e89e7cefff               call       0x447ff0
00550352  83c404                   add        esp, 4
00550355  5f                       pop        edi
00550356  5e                       pop        esi
00550357  5b                       pop        ebx
00550358  5d                       pop        ebp
00550359  c21800                   ret        0x18
0055035c  5f                       pop        edi
0055035d  5e                       pop        esi
0055035e  8bc3                     mov        eax, ebx
00550360  5b                       pop        ebx
00550361  5d                       pop        ebp
00550362  c21800                   ret        0x18
