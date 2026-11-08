00447ff0  55                       push       ebp
00447ff1  8bec                     mov        ebp, esp
00447ff3  6aff                     push       -1
00447ff5  68ce1ec500               push       0xc51ece
00447ffa  64a100000000             mov        eax, dword ptr fs:[0]
00448000  50                       push       eax
00448001  64892500000000           mov        dword ptr fs:[0], esp
00448008  51                       push       ecx
00448009  8a0dd4400001             mov        cl, byte ptr [0x10040d4]
0044800f  b801000000               mov        eax, 1
00448014  84c8                     test       al, cl
00448016  7536                     jne        0x44804e
00448018  0905d4400001             or         dword ptr [0x10040d4], eax
0044801e  8d45f0                   lea        eax, [ebp - 0x10]
00448021  50                       push       eax
00448022  b9cc400001               mov        ecx, 0x10040cc
00448027  c745fc00000000           mov        dword ptr [ebp - 4], 0
0044802e  c745f00000003f           mov        dword ptr [ebp - 0x10], 0x3f000000
00448035  e8d64f0000               call       0x44d010
0044803a  68a087ca00               push       0xca87a0
0044803f  e8fd897b00               call       0xc00a41
00448044  83c404                   add        esp, 4
00448047  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0044804e  d94508                   fld        dword ptr [ebp + 8]
00448051  b9cc400001               mov        ecx, 0x10040cc
00448056  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
0044805c  dfe0                     fnstsw     ax
0044805e  f6c401                   test       ah, 1
00448061  751b                     jne        0x44807e
00448063  e848b3feff               call       0x4333b0
00448068  d84508                   fadd       dword ptr [ebp + 8]
0044806b  e8d4947b00               call       0xc01544
00448070  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00448073  64890d00000000           mov        dword ptr fs:[0], ecx
0044807a  8be5                     mov        esp, ebp
0044807c  5d                       pop        ebp
0044807d  c3                       ret        
0044807e  e82db3feff               call       0x4333b0
00448083  d86d08                   fsubr      dword ptr [ebp + 8]
00448086  e8b9947b00               call       0xc01544
0044808b  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0044808e  64890d00000000           mov        dword ptr fs:[0], ecx
00448095  8be5                     mov        esp, ebp
00448097  5d                       pop        ebp
00448098  c3                       ret        