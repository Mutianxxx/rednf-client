00ac9e30  55                       push       ebp
00ac9e31  8bec                     mov        ebp, esp
00ac9e33  6aff                     push       -1
00ac9e35  681534c900               push       0xc93415
00ac9e3a  64a100000000             mov        eax, dword ptr fs:[0]
00ac9e40  50                       push       eax
00ac9e41  64892500000000           mov        dword ptr fs:[0], esp
00ac9e48  81eca4020000             sub        esp, 0x2a4
00ac9e4e  53                       push       ebx
00ac9e4f  33db                     xor        ebx, ebx
00ac9e51  56                       push       esi
00ac9e52  894de8                   mov        dword ptr [ebp - 0x18], ecx
00ac9e55  c745c807000000           mov        dword ptr [ebp - 0x38], 7
00ac9e5c  895dc4                   mov        dword ptr [ebp - 0x3c], ebx
00ac9e5f  66895db4                 mov        word ptr [ebp - 0x4c], bx
00ac9e63  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9e66  56                       push       esi
00ac9e67  6a01                     push       1
00ac9e69  8d8558ffffff             lea        eax, [ebp - 0xa8]
00ac9e6f  6a10                     push       0x10
00ac9e71  50                       push       eax
00ac9e72  895dfc                   mov        dword ptr [ebp - 4], ebx
00ac9e75  e8bc851300               call       0xc02436
00ac9e7a  6a10                     push       0x10
00ac9e7c  8d8d58ffffff             lea        ecx, [ebp - 0xa8]
00ac9e82  51                       push       ecx
00ac9e83  68987be600               push       0xe67b98
00ac9e88  e8a3981300               call       0xc03730
00ac9e8d  83c41c                   add        esp, 0x1c
00ac9e90  85c0                     test       eax, eax
00ac9e92  7426                     je         0xac9eba
00ac9e94  837dc808                 cmp        dword ptr [ebp - 0x38], 8
00ac9e98  720c                     jb         0xac9ea6
00ac9e9a  8b55b4                   mov        edx, dword ptr [ebp - 0x4c]
00ac9e9d  52                       push       edx
00ac9e9e  e83a611300               call       0xbfffdd
00ac9ea3  83c404                   add        esp, 4
00ac9ea6  5e                       pop        esi
00ac9ea7  33c0                     xor        eax, eax
00ac9ea9  5b                       pop        ebx
00ac9eaa  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac9ead  64890d00000000           mov        dword ptr fs:[0], ecx
00ac9eb4  8be5                     mov        esp, ebp
00ac9eb6  5d                       pop        ebp
00ac9eb7  c20400                   ret        4
00ac9eba  56                       push       esi
00ac9ebb  6a01                     push       1
00ac9ebd  8d45ec                   lea        eax, [ebp - 0x14]
00ac9ec0  6a04                     push       4
00ac9ec2  50                       push       eax
00ac9ec3  e86e851300               call       0xc02436
00ac9ec8  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00ac9ecb  83c410                   add        esp, 0x10
00ac9ece  3bc3                     cmp        eax, ebx
00ac9ed0  895df0                   mov        dword ptr [ebp - 0x10], ebx
00ac9ed3  0f8e4a010000             jle        0xaca023
00ac9ed9  57                       push       edi
00ac9eda  eb04                     jmp        0xac9ee0
00ac9edc  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9edf  90                       nop        
00ac9ee0  56                       push       esi
00ac9ee1  6a01                     push       1
00ac9ee3  8d4da8                   lea        ecx, [ebp - 0x58]
00ac9ee6  6a04                     push       4
00ac9ee8  51                       push       ecx
00ac9ee9  e848851300               call       0xc02436
00ac9eee  56                       push       esi
00ac9eef  6a01                     push       1
00ac9ef1  8d55ac                   lea        edx, [ebp - 0x54]
00ac9ef4  6a04                     push       4
00ac9ef6  52                       push       edx
00ac9ef7  e83a851300               call       0xc02436
00ac9efc  56                       push       esi
00ac9efd  6a01                     push       1
00ac9eff  8d8550fdffff             lea        eax, [ebp - 0x2b0]
00ac9f05  6800010000               push       0x100
00ac9f0a  50                       push       eax
00ac9f0b  e826851300               call       0xc02436
00ac9f10  8b158019ff00             mov        edx, dword ptr [0xff1980]
00ac9f16  83c430                   add        esp, 0x30
00ac9f19  b940000000               mov        ecx, 0x40
00ac9f1e  33c0                     xor        eax, eax
00ac9f20  8dbd50feffff             lea        edi, [ebp - 0x1b0]
00ac9f26  f3ab                     rep stosd  dword ptr es:[edi], eax
00ac9f28  eb06                     jmp        0xac9f30
00ac9f2a  8d9b00000000             lea        ebx, [ebx]
00ac9f30  8a0c42                   mov        cl, byte ptr [edx + eax*2]
00ac9f33  328c0550fdffff           xor        cl, byte ptr [ebp + eax - 0x2b0]
00ac9f3a  888c0550feffff           mov        byte ptr [ebp + eax - 0x1b0], cl
00ac9f41  7408                     je         0xac9f4b
00ac9f43  40                       inc        eax
00ac9f44  3d00010000               cmp        eax, 0x100
00ac9f49  7ce5                     jl         0xac9f30
00ac9f4b  8d8d50feffff             lea        ecx, [ebp - 0x1b0]
00ac9f51  51                       push       ecx
00ac9f52  889d4fffffff             mov        byte ptr [ebp - 0xb1], bl
00ac9f58  e8f38cfcff               call       0xa92c50
00ac9f5d  8bf0                     mov        esi, eax
00ac9f5f  bf07000000               mov        edi, 7
00ac9f64  56                       push       esi
00ac9f65  897de4                   mov        dword ptr [ebp - 0x1c], edi
00ac9f68  895de0                   mov        dword ptr [ebp - 0x20], ebx
00ac9f6b  66895dd0                 mov        word ptr [ebp - 0x30], bx
00ac9f6f  e8595e1300               call       0xbffdcd
00ac9f74  83c408                   add        esp, 8
00ac9f77  50                       push       eax
00ac9f78  56                       push       esi
00ac9f79  8d4dcc                   lea        ecx, [ebp - 0x34]
00ac9f7c  e8ff8e93ff               call       0x402e80
00ac9f81  8d55a8                   lea        edx, [ebp - 0x58]
00ac9f84  52                       push       edx
00ac9f85  8d45cc                   lea        eax, [ebp - 0x34]
00ac9f88  50                       push       eax
00ac9f89  8d8d68ffffff             lea        ecx, [ebp - 0x98]
00ac9f8f  c645fc01                 mov        byte ptr [ebp - 4], 1
00ac9f93  e898090000               call       0xaca930
00ac9f98  50                       push       eax
00ac9f99  8d8d50ffffff             lea        ecx, [ebp - 0xb0]
00ac9f9f  51                       push       ecx
00ac9fa0  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
00ac9fa3  c645fc02                 mov        byte ptr [ebp - 4], 2
00ac9fa7  e8f4100000               call       0xacb0a0
00ac9fac  8b45a4                   mov        eax, dword ptr [ebp - 0x5c]
00ac9faf  be08000000               mov        esi, 8
00ac9fb4  3bc6                     cmp        eax, esi
00ac9fb6  720c                     jb         0xac9fc4
00ac9fb8  8b5590                   mov        edx, dword ptr [ebp - 0x70]
00ac9fbb  52                       push       edx
00ac9fbc  e81c601300               call       0xbfffdd
00ac9fc1  83c404                   add        esp, 4
00ac9fc4  397580                   cmp        dword ptr [ebp - 0x80], esi
00ac9fc7  897da4                   mov        dword ptr [ebp - 0x5c], edi
00ac9fca  895da0                   mov        dword ptr [ebp - 0x60], ebx
00ac9fcd  66895d90                 mov        word ptr [ebp - 0x70], bx
00ac9fd1  720f                     jb         0xac9fe2
00ac9fd3  8b856cffffff             mov        eax, dword ptr [ebp - 0x94]
00ac9fd9  50                       push       eax
00ac9fda  e8fe5f1300               call       0xbfffdd
00ac9fdf  83c404                   add        esp, 4
00ac9fe2  3975e4                   cmp        dword ptr [ebp - 0x1c], esi
00ac9fe5  897d80                   mov        dword ptr [ebp - 0x80], edi
00ac9fe8  899d7cffffff             mov        dword ptr [ebp - 0x84], ebx
00ac9fee  66899d6cffffff           mov        word ptr [ebp - 0x94], bx
00ac9ff5  885dfc                   mov        byte ptr [ebp - 4], bl
00ac9ff8  720c                     jb         0xaca006
00ac9ffa  8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00ac9ffd  51                       push       ecx
00ac9ffe  e8da5f1300               call       0xbfffdd
00aca003  83c404                   add        esp, 4
00aca006  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00aca009  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
00aca00c  40                       inc        eax
00aca00d  3bc1                     cmp        eax, ecx
00aca00f  897de4                   mov        dword ptr [ebp - 0x1c], edi
00aca012  895de0                   mov        dword ptr [ebp - 0x20], ebx
00aca015  66895dd0                 mov        word ptr [ebp - 0x30], bx
00aca019  8945f0                   mov        dword ptr [ebp - 0x10], eax
00aca01c  0f8cbafeffff             jl         0xac9edc
00aca022  5f                       pop        edi
00aca023  837dc808                 cmp        dword ptr [ebp - 0x38], 8
00aca027  720c                     jb         0xaca035
00aca029  8b55b4                   mov        edx, dword ptr [ebp - 0x4c]
00aca02c  52                       push       edx
00aca02d  e8ab5f1300               call       0xbfffdd
00aca032  83c404                   add        esp, 4
00aca035  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00aca038  5e                       pop        esi
00aca039  b801000000               mov        eax, 1
00aca03e  5b                       pop        ebx
00aca03f  64890d00000000           mov        dword ptr fs:[0], ecx
00aca046  8be5                     mov        esp, ebp
00aca048  5d                       pop        ebp
00aca049  c20400                   ret        4