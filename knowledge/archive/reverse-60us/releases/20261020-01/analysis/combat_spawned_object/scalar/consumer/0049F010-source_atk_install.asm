0049f010  56                       push       esi
0049f011  8bf1                     mov        esi, ecx
0049f013  e828e10400               call       0x4ed140
0049f018  8b06                     mov        eax, dword ptr [esi]
0049f01a  8d8edc050000             lea        ecx, [esi + 0x5dc]
0049f020  51                       push       ecx
0049f021  8bce                     mov        ecx, esi
0049f023  ff9098010000             call       dword ptr [eax + 0x198]
0049f029  8b8648010000             mov        eax, dword ptr [esi + 0x148]
0049f02f  85c0                     test       eax, eax
0049f031  744a                     je         0x49f07d
0049f033  57                       push       edi
0049f034  8db8b0000000             lea        edi, [eax + 0xb0]
0049f03a  8d4f1c                   lea        ecx, [edi + 0x1c]
0049f03d  e81e30f6ff               call       0x402060
0049f042  85c0                     test       eax, eax
0049f044  7520                     jne        0x49f066
0049f046  8bcf                     mov        ecx, edi
0049f048  e86343f9ff               call       0x4333b0
0049f04d  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
0049f053  dfe0                     fnstsw     ax
0049f055  f6c441                   test       ah, 0x41
0049f058  740c                     je         0x49f066
0049f05a  8d4f08                   lea        ecx, [edi + 8]
0049f05d  e8fe2ff6ff               call       0x402060
0049f062  85c0                     test       eax, eax
0049f064  7e16                     jle        0x49f07c
0049f066  8b8648010000             mov        eax, dword ptr [esi + 0x148]
0049f06c  8b16                     mov        edx, dword ptr [esi]
0049f06e  05b0000000               add        eax, 0xb0
0049f073  50                       push       eax
0049f074  8bce                     mov        ecx, esi
0049f076  ff9298010000             call       dword ptr [edx + 0x198]
0049f07c  5f                       pop        edi
0049f07d  8bce                     mov        ecx, esi
0049f07f  5e                       pop        esi
0049f080  e94bfcffff               jmp        0x49ecd0