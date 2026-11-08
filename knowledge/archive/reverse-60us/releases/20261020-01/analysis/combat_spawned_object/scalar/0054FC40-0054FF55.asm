0054fc40  55                       push       ebp
0054fc41  8bec                     mov        ebp, esp
0054fc43  83ec14                   sub        esp, 0x14
0054fc46  56                       push       esi
0054fc47  8b7508                   mov        esi, dword ptr [ebp + 8]
0054fc4a  85f6                     test       esi, esi
0054fc4c  0f84f9020000             je         0x54ff4b
0054fc52  53                       push       ebx
0054fc53  33db                     xor        ebx, ebx
0054fc55  57                       push       edi
0054fc56  895df0                   mov        dword ptr [ebp - 0x10], ebx
0054fc59  8da42400000000           lea        esp, [esp]
0054fc60  8b06                     mov        eax, dword ptr [esi]
0054fc62  53                       push       ebx
0054fc63  8bce                     mov        ecx, esi
0054fc65  ff9028040000             call       dword ptr [eax + 0x428]
0054fc6b  8bf8                     mov        edi, eax
0054fc6d  85ff                     test       edi, edi
0054fc6f  897df4                   mov        dword ptr [ebp - 0xc], edi
0054fc72  0f84c4020000             je         0x54ff3c
0054fc78  8b17                     mov        edx, dword ptr [edi]
0054fc7a  8bcf                     mov        ecx, edi
0054fc7c  ff92e4000000             call       dword ptr [edx + 0xe4]
0054fc82  8bd8                     mov        ebx, eax
0054fc84  33c0                     xor        eax, eax
0054fc86  8945f8                   mov        dword ptr [ebp - 8], eax
0054fc89  8945fc                   mov        dword ptr [ebp - 4], eax
0054fc8c  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fc92  85c0                     test       eax, eax
0054fc94  0f8464010000             je         0x54fdfe
0054fc9a  8b8ba4020000             mov        ecx, dword ptr [ebx + 0x2a4]
0054fca0  2bc8                     sub        ecx, eax
0054fca2  b867666666               mov        eax, 0x66666667
0054fca7  f7e9                     imul       ecx
0054fca9  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0054fcac  c1fa04                   sar        edx, 4
0054fcaf  8bc2                     mov        eax, edx
0054fcb1  c1e81f                   shr        eax, 0x1f
0054fcb4  03c2                     add        eax, edx
0054fcb6  3bc8                     cmp        ecx, eax
0054fcb8  0f8340010000             jae        0x54fdfe
0054fcbe  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fcc4  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
0054fcc7  8b5514                   mov        edx, dword ptr [ebp + 0x14]
0054fcca  8d3c01                   lea        edi, [ecx + eax]
0054fccd  395720                   cmp        dword ptr [edi + 0x20], edx
0054fcd0  0f8513010000             jne        0x54fde9
0054fcd6  8b4704                   mov        eax, dword ptr [edi + 4]
0054fcd9  8b35dc012101             mov        esi, dword ptr [0x12101dc]
0054fcdf  8b4f08                   mov        ecx, dword ptr [edi + 8]
0054fce2  83c704                   add        edi, 4
0054fce5  33c6                     xor        eax, esi
0054fce7  2bc7                     sub        eax, edi
0054fce9  3bc1                     cmp        eax, ecx
0054fceb  740e                     je         0x54fcfb
0054fced  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0054fcf3  6a3f                     push       0x3f
0054fcf5  57                       push       edi
0054fcf6  e8b5735c00               call       0xb170b0
0054fcfb  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0054fd01  8b4704                   mov        eax, dword ptr [edi + 4]
0054fd04  8b5144                   mov        edx, dword ptr [ecx + 0x44]
0054fd07  c1e002                   shl        eax, 2
0054fd0a  8d0c02                   lea        ecx, [edx + eax]
0054fd0d  8b15dc012101             mov        edx, dword ptr [0x12101dc]
0054fd13  8bf1                     mov        esi, ecx
0054fd15  33f2                     xor        esi, edx
0054fd17  8b11                     mov        edx, dword ptr [ecx]
0054fd19  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0054fd1f  33f2                     xor        esi, edx
0054fd21  8b5148                   mov        edx, dword ptr [ecx + 0x48]
0054fd24  03c2                     add        eax, edx
0054fd26  8bd0                     mov        edx, eax
0054fd28  3315dc012101             xor        edx, dword ptr [0x12101dc]
0054fd2e  3310                     xor        edx, dword ptr [eax]
0054fd30  3bf2                     cmp        esi, edx
0054fd32  7408                     je         0x54fd3c
0054fd34  6a40                     push       0x40
0054fd36  57                       push       edi
0054fd37  e874735c00               call       0xb170b0
0054fd3c  3b7518                   cmp        esi, dword ptr [ebp + 0x18]
0054fd3f  0f85a4000000             jne        0x54fde9
0054fd45  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fd4b  8b75fc                   mov        esi, dword ptr [ebp - 4]
0054fd4e  03c6                     add        eax, esi
0054fd50  8b4024                   mov        eax, dword ptr [eax + 0x24]
0054fd53  85c0                     test       eax, eax
0054fd55  7416                     je         0x54fd6d
0054fd57  83f802                   cmp        eax, 2
0054fd5a  7511                     jne        0x54fd6d
0054fd5c  8b0d48280001             mov        ecx, dword ptr [0x1002848]
0054fd62  6aff                     push       -1
0054fd64  e887aeeeff               call       0x43abf0
0054fd69  84c0                     test       al, al
0054fd6b  747c                     je         0x54fde9
0054fd6d  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fd73  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
0054fd76  03f0                     add        esi, eax
0054fd78  394e0c                   cmp        dword ptr [esi + 0xc], ecx
0054fd7b  756c                     jne        0x54fde9
0054fd7d  833e06                   cmp        dword ptr [esi], 6
0054fd80  7411                     je         0x54fd93
0054fd82  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0054fd85  8b11                     mov        edx, dword ptr [ecx]
0054fd87  ff92b0050000             call       dword ptr [edx + 0x5b0]
0054fd8d  8b0e                     mov        ecx, dword ptr [esi]
0054fd8f  3b08                     cmp        ecx, dword ptr [eax]
0054fd91  7556                     jne        0x54fde9
0054fd93  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fd99  8b75fc                   mov        esi, dword ptr [ebp - 4]
0054fd9c  03c6                     add        eax, esi
0054fd9e  8d4810                   lea        ecx, [eax + 0x10]
0054fda1  e8ba22ebff               call       0x402060
0054fda6  85c0                     test       eax, eax
0054fda8  8b83a0020000             mov        eax, dword ptr [ebx + 0x2a0]
0054fdae  742c                     je         0x54fddc
0054fdb0  db450c                   fild       dword ptr [ebp + 0xc]
0054fdb3  03c6                     add        eax, esi
0054fdb5  8d4818                   lea        ecx, [eax + 0x18]
0054fdb8  d95d0c                   fstp       dword ptr [ebp + 0xc]
0054fdbb  e8a022ebff               call       0x402060
0054fdc0  8945ec                   mov        dword ptr [ebp - 0x14], eax
0054fdc3  db45ec                   fild       dword ptr [ebp - 0x14]
0054fdc6  d80dac10cc00             fmul       dword ptr [0xcc10ac]
0054fdcc  d84d0c                   fmul       dword ptr [ebp + 0xc]
0054fdcf  d8450c                   fadd       dword ptr [ebp + 0xc]
0054fdd2  e86d176b00               call       0xc01544
0054fdd7  89450c                   mov        dword ptr [ebp + 0xc], eax
0054fdda  eb0d                     jmp        0x54fde9
0054fddc  03c6                     add        eax, esi
0054fdde  8d4818                   lea        ecx, [eax + 0x18]
0054fde1  e87a22ebff               call       0x402060
0054fde6  01450c                   add        dword ptr [ebp + 0xc], eax
0054fde9  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0054fdec  8b45fc                   mov        eax, dword ptr [ebp - 4]
0054fdef  8b7df4                   mov        edi, dword ptr [ebp - 0xc]
0054fdf2  41                       inc        ecx
0054fdf3  894df8                   mov        dword ptr [ebp - 8], ecx
0054fdf6  83c028                   add        eax, 0x28
0054fdf9  e98bfeffff               jmp        0x54fc89
0054fdfe  8b17                     mov        edx, dword ptr [edi]
0054fe00  8bcf                     mov        ecx, edi
0054fe02  ff921c010000             call       dword ptr [edx + 0x11c]
0054fe08  8bf0                     mov        esi, eax
0054fe0a  85f6                     test       esi, esi
0054fe0c  0f8424010000             je         0x54ff36
0054fe12  33db                     xor        ebx, ebx
0054fe14  895df8                   mov        dword ptr [ebp - 8], ebx
0054fe17  eb07                     jmp        0x54fe20
0054fe19  8da42400000000           lea        esp, [esp]
0054fe20  8b86a0020000             mov        eax, dword ptr [esi + 0x2a0]
0054fe26  85c0                     test       eax, eax
0054fe28  0f8408010000             je         0x54ff36
0054fe2e  8b8ea4020000             mov        ecx, dword ptr [esi + 0x2a4]
0054fe34  2bc8                     sub        ecx, eax
0054fe36  b867666666               mov        eax, 0x66666667
0054fe3b  f7e9                     imul       ecx
0054fe3d  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0054fe40  c1fa04                   sar        edx, 4
0054fe43  8bc2                     mov        eax, edx
0054fe45  c1e81f                   shr        eax, 0x1f
0054fe48  03c2                     add        eax, edx
0054fe4a  3bc8                     cmp        ecx, eax
0054fe4c  0f83e4000000             jae        0x54ff36
0054fe52  8b7df4                   mov        edi, dword ptr [ebp - 0xc]
0054fe55  8b07                     mov        eax, dword ptr [edi]
0054fe57  8bcf                     mov        ecx, edi
0054fe59  ff902c010000             call       dword ptr [eax + 0x12c]
0054fe5f  84c0                     test       al, al
0054fe61  0f84c4000000             je         0x54ff2b
0054fe67  8b17                     mov        edx, dword ptr [edi]
0054fe69  8bcf                     mov        ecx, edi
0054fe6b  ff9218010000             call       dword ptr [edx + 0x118]
0054fe71  84c0                     test       al, al
0054fe73  0f84b2000000             je         0x54ff2b
0054fe79  8b86a0020000             mov        eax, dword ptr [esi + 0x2a0]
0054fe7f  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
0054fe82  8b541820                 mov        edx, dword ptr [eax + ebx + 0x20]
0054fe86  03c3                     add        eax, ebx
0054fe88  3bd1                     cmp        edx, ecx
0054fe8a  0f859b000000             jne        0x54ff2b
0054fe90  8d4804                   lea        ecx, [eax + 4]
0054fe93  e8c821ebff               call       0x402060
0054fe98  3b4518                   cmp        eax, dword ptr [ebp + 0x18]
0054fe9b  0f858a000000             jne        0x54ff2b
0054fea1  8b96a0020000             mov        edx, dword ptr [esi + 0x2a0]
0054fea7  8b4510                   mov        eax, dword ptr [ebp + 0x10]
0054feaa  8b4c130c                 mov        ecx, dword ptr [ebx + edx + 0xc]
0054feae  3bc8                     cmp        ecx, eax
0054feb0  8d3c13                   lea        edi, [ebx + edx]
0054feb3  7576                     jne        0x54ff2b
0054feb5  833f06                   cmp        dword ptr [edi], 6
0054feb8  7411                     je         0x54fecb
0054feba  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0054febd  8b11                     mov        edx, dword ptr [ecx]
0054febf  ff92b0050000             call       dword ptr [edx + 0x5b0]
0054fec5  8b0f                     mov        ecx, dword ptr [edi]
0054fec7  3b08                     cmp        ecx, dword ptr [eax]
0054fec9  7560                     jne        0x54ff2b
0054fecb  8b86a0020000             mov        eax, dword ptr [esi + 0x2a0]
0054fed1  03c3                     add        eax, ebx
0054fed3  8d4810                   lea        ecx, [eax + 0x10]
0054fed6  e88521ebff               call       0x402060
0054fedb  85c0                     test       eax, eax
0054fedd  8b86a0020000             mov        eax, dword ptr [esi + 0x2a0]
0054fee3  7439                     je         0x54ff1e
0054fee5  db450c                   fild       dword ptr [ebp + 0xc]
0054fee8  03c3                     add        eax, ebx
0054feea  8d4818                   lea        ecx, [eax + 0x18]
0054feed  d95d0c                   fstp       dword ptr [ebp + 0xc]
0054fef0  e86b21ebff               call       0x402060
0054fef5  8945ec                   mov        dword ptr [ebp - 0x14], eax
0054fef8  db45ec                   fild       dword ptr [ebp - 0x14]
0054fefb  d80dac10cc00             fmul       dword ptr [0xcc10ac]
0054ff01  d84d0c                   fmul       dword ptr [ebp + 0xc]
0054ff04  d8450c                   fadd       dword ptr [ebp + 0xc]
0054ff07  e838166b00               call       0xc01544
0054ff0c  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0054ff0f  41                       inc        ecx
0054ff10  89450c                   mov        dword ptr [ebp + 0xc], eax
0054ff13  894df8                   mov        dword ptr [ebp - 8], ecx
0054ff16  83c328                   add        ebx, 0x28
0054ff19  e902ffffff               jmp        0x54fe20
0054ff1e  03c3                     add        eax, ebx
0054ff20  8d4818                   lea        ecx, [eax + 0x18]
0054ff23  e83821ebff               call       0x402060
0054ff28  01450c                   add        dword ptr [ebp + 0xc], eax
0054ff2b  ff45f8                   inc        dword ptr [ebp - 8]
0054ff2e  83c328                   add        ebx, 0x28
0054ff31  e9eafeffff               jmp        0x54fe20
0054ff36  8b5df0                   mov        ebx, dword ptr [ebp - 0x10]
0054ff39  8b7508                   mov        esi, dword ptr [ebp + 8]
0054ff3c  43                       inc        ebx
0054ff3d  83fb17                   cmp        ebx, 0x17
0054ff40  895df0                   mov        dword ptr [ebp - 0x10], ebx
0054ff43  0f8c17fdffff             jl         0x54fc60
0054ff49  5f                       pop        edi
0054ff4a  5b                       pop        ebx
0054ff4b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
0054ff4e  5e                       pop        esi
0054ff4f  8be5                     mov        esp, ebp
0054ff51  5d                       pop        ebp
0054ff52  c21400                   ret        0x14