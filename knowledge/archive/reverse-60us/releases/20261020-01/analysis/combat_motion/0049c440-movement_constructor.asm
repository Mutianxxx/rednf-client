0049c440  55                       push       ebp
0049c441  8bec                     mov        ebp, esp
0049c443  6aff                     push       -1
0049c445  683e6ac500               push       0xc56a3e
0049c44a  64a100000000             mov        eax, dword ptr fs:[0]
0049c450  50                       push       eax
0049c451  64892500000000           mov        dword ptr fs:[0], esp
0049c458  51                       push       ecx
0049c459  56                       push       esi
0049c45a  57                       push       edi
0049c45b  8bf1                     mov        esi, ecx
0049c45d  8975f0                   mov        dword ptr [ebp - 0x10], esi
0049c460  83c8ff                   or         eax, 0xffffffff
0049c463  ba78e9cc00               mov        edx, 0xcce978
0049c468  895608                   mov        dword ptr [esi + 8], edx
0049c46b  894630                   mov        dword ptr [esi + 0x30], eax
0049c46e  894634                   mov        dword ptr [esi + 0x34], eax
0049c471  894638                   mov        dword ptr [esi + 0x38], eax
0049c474  33ff                     xor        edi, edi
0049c476  897e0c                   mov        dword ptr [esi + 0xc], edi
0049c479  897e18                   mov        dword ptr [esi + 0x18], edi
0049c47c  897e24                   mov        dword ptr [esi + 0x24], edi
0049c47f  897e10                   mov        dword ptr [esi + 0x10], edi
0049c482  897e1c                   mov        dword ptr [esi + 0x1c], edi
0049c485  897e28                   mov        dword ptr [esi + 0x28], edi
0049c488  897e14                   mov        dword ptr [esi + 0x14], edi
0049c48b  897e20                   mov        dword ptr [esi + 0x20], edi
0049c48e  897e2c                   mov        dword ptr [esi + 0x2c], edi
0049c491  b101                     mov        cl, 1
0049c493  884e3c                   mov        byte ptr [esi + 0x3c], cl
0049c496  89563d                   mov        dword ptr [esi + 0x3d], edx
0049c499  897e41                   mov        dword ptr [esi + 0x41], edi
0049c49c  897e4d                   mov        dword ptr [esi + 0x4d], edi
0049c49f  897e59                   mov        dword ptr [esi + 0x59], edi
0049c4a2  894665                   mov        dword ptr [esi + 0x65], eax
0049c4a5  897e45                   mov        dword ptr [esi + 0x45], edi
0049c4a8  897e51                   mov        dword ptr [esi + 0x51], edi
0049c4ab  897e5d                   mov        dword ptr [esi + 0x5d], edi
0049c4ae  894669                   mov        dword ptr [esi + 0x69], eax
0049c4b1  897e49                   mov        dword ptr [esi + 0x49], edi
0049c4b4  897e55                   mov        dword ptr [esi + 0x55], edi
0049c4b7  897e61                   mov        dword ptr [esi + 0x61], edi
0049c4ba  89466d                   mov        dword ptr [esi + 0x6d], eax
0049c4bd  884e71                   mov        byte ptr [esi + 0x71], cl
0049c4c0  8d8ea0000000             lea        ecx, [esi + 0xa0]
0049c4c6  e8958ef6ff               call       0x405360
0049c4cb  8bce                     mov        ecx, esi
0049c4cd  897dfc                   mov        dword ptr [ebp - 4], edi
0049c4d0  e88b4c0700               call       0x511160
0049c4d5  8b4508                   mov        eax, dword ptr [ebp + 8]
0049c4d8  50                       push       eax
0049c4d9  8bce                     mov        ecx, esi
0049c4db  e8205f0700               call       0x512400
0049c4e0  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0049c4e3  5f                       pop        edi
0049c4e4  8bc6                     mov        eax, esi
0049c4e6  5e                       pop        esi
0049c4e7  64890d00000000           mov        dword ptr fs:[0], ecx
0049c4ee  8be5                     mov        esp, ebp
0049c4f0  5d                       pop        ebp
0049c4f1  c20400                   ret        4
