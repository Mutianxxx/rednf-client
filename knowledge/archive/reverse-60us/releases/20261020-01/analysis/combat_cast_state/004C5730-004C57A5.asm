004c5730  55                       push       ebp
004c5731  8bec                     mov        ebp, esp
004c5733  64a100000000             mov        eax, dword ptr fs:[0]
004c5739  6aff                     push       -1
004c573b  689b7bc500               push       0xc57b9b
004c5740  50                       push       eax
004c5741  64892500000000           mov        dword ptr fs:[0], esp
004c5748  53                       push       ebx
004c5749  56                       push       esi
004c574a  8bf1                     mov        esi, ecx
004c574c  8b06                     mov        eax, dword ptr [esi]
004c574e  57                       push       edi
004c574f  ff9030020000             call       dword ptr [eax + 0x230]
004c5755  8b16                     mov        edx, dword ptr [esi]
004c5757  8bce                     mov        ecx, esi
004c5759  8bd8                     mov        ebx, eax
004c575b  ff5234                   call       dword ptr [edx + 0x34]
004c575e  84c0                     test       al, al
004c5760  8b7d08                   mov        edi, dword ptr [ebp + 8]
004c5763  7427                     je         0x4c578c
004c5765  83fb10                   cmp        ebx, 0x10
004c5768  7509                     jne        0x4c5773
004c576a  83ff11                   cmp        edi, 0x11
004c576d  0f850d030000             jne        0x4c5a80
004c5773  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004c5776  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
004c5779  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004c577c  53                       push       ebx
004c577d  50                       push       eax
004c577e  51                       push       ecx
004c577f  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004c5785  52                       push       edx
004c5786  57                       push       edi
004c5787  e8a4e00600               call       0x533830
004c578c  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004c578f  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
004c5792  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004c5795  50                       push       eax
004c5796  51                       push       ecx
004c5797  52                       push       edx
004c5798  57                       push       edi
004c5799  8bce                     mov        ecx, esi
004c579b  e8d08b0100               call       0x4de370
004c57a0  8b06                     mov        eax, dword ptr [esi]
004c57a2  8bce                     mov        ecx, esi
004c57a4  ff                       .byte      0xff