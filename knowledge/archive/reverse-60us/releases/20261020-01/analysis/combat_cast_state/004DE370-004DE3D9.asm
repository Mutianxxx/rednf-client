004de370  55                       push       ebp
004de371  8bec                     mov        ebp, esp
004de373  6aff                     push       -1
004de375  68be87c500               push       0xc587be
004de37a  64a100000000             mov        eax, dword ptr fs:[0]
004de380  50                       push       eax
004de381  64892500000000           mov        dword ptr fs:[0], esp
004de388  83ec30                   sub        esp, 0x30
004de38b  53                       push       ebx
004de38c  56                       push       esi
004de38d  8bf1                     mov        esi, ecx
004de38f  57                       push       edi
004de390  8d8e5c150000             lea        ecx, [esi + 0x155c]
004de396  e8c53cf2ff               call       0x402060
004de39b  8945f0                   mov        dword ptr [ebp - 0x10], eax
004de39e  83c0f6                   add        eax, -0xa
004de3a1  83f805                   cmp        eax, 5
004de3a4  0f87ff000000             ja         0x4de4a9
004de3aa  ff248598f24d00           jmp        dword ptr [eax*4 + 0x4df298]
004de3b1  8d8e20240000             lea        ecx, [esi + 0x2420]
004de3b7  e8a43cf2ff               call       0x402060
004de3bc  85c0                     test       eax, eax
004de3be  0f85e5000000             jne        0x4de4a9
004de3c4  8b06                     mov        eax, dword ptr [esi]
004de3c6  8bce                     mov        ecx, esi
004de3c8  ff9058050000             call       dword ptr [eax + 0x558]
004de3ce  e9d6000000               jmp        0x4de4a9
004de3d3  8b16                     mov        edx, dword ptr [esi]
004de3d5  6a10                     push       0x10
004de3d7  8bce                     mov        ecx, esi