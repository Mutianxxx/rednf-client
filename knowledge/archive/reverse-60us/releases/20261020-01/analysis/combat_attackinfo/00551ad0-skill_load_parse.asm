00551ad0  55                       push       ebp
00551ad1  8bec                     mov        ebp, esp
00551ad3  6aff                     push       -1
00551ad5  687cd2c500               push       0xc5d27c
00551ada  64a100000000             mov        eax, dword ptr fs:[0]
00551ae0  50                       push       eax
00551ae1  64892500000000           mov        dword ptr fs:[0], esp
00551ae8  81ec64030000             sub        esp, 0x364
00551aee  53                       push       ebx
00551aef  56                       push       esi
00551af0  8bd9                     mov        ebx, ecx
00551af2  57                       push       edi
00551af3  8d8d90fcffff             lea        ecx, [ebp - 0x370]
00551af9  895df0                   mov        dword ptr [ebp - 0x10], ebx
00551afc  e86f460000               call       0x556170
00551b01  83bbd403000006           cmp        dword ptr [ebx + 0x3d4], 6
00551b08  8d7308                   lea        esi, [ebx + 8]
00551b0b  8bce                     mov        ecx, esi
00551b0d  c745fc00000000           mov        dword ptr [ebp - 4], 0
00551b14  0f9445ef                 sete       byte ptr [ebp - 0x11]
00551b18  e82341f9ff               call       0x4e5c40
00551b1d  8b7d08                   mov        edi, dword ptr [ebp + 8]
00551b20  57                       push       edi
00551b21  e8a7e26a00               call       0xbffdcd
00551b26  83c404                   add        esp, 4
00551b29  50                       push       eax
00551b2a  57                       push       edi
00551b2b  8d8bb8030000             lea        ecx, [ebx + 0x3b8]
00551b31  e84a13ebff               call       0x402e80
00551b36  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00551b39  8983d4030000             mov        dword ptr [ebx + 0x3d4], eax
00551b3f  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00551b42  83f80c                   cmp        eax, 0xc
00551b45  751b                     jne        0x551b62
00551b47  a148280001               mov        eax, dword ptr [0x1002848]
00551b4c  85c0                     test       eax, eax
00551b4e  740d                     je         0x551b5d
00551b50  8d8840100000             lea        ecx, [eax + 0x1040]
00551b56  e80505ebff               call       0x402060
00551b5b  eb05                     jmp        0x551b62
00551b5d  b803000000               mov        eax, 3
00551b62  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00551b65  50                       push       eax
00551b66  51                       push       ecx
00551b67  8d9590fcffff             lea        edx, [ebp - 0x370]
00551b6d  57                       push       edi
00551b6e  52                       push       edx
00551b6f  e82cf23400               call       0x8a0da0
00551b74  83c410                   add        esp, 0x10
00551b77  84c0                     test       al, al
00551b79  7514                     jne        0x551b8f
00551b7b  57                       push       edi
00551b7c  68d8cdcd00               push       0xcdcdd8
00551b81  ff15bc2eff00             call       dword ptr [0xff2ebc]
00551b87  83c408                   add        esp, 8
00551b8a  e93e1a0000               jmp        0x5535cd
00551b8f  8d8590fcffff             lea        eax, [ebp - 0x370]
00551b95  50                       push       eax
00551b96  8bce                     mov        ecx, esi
00551b98  e8132aebff               call       0x4045b0
