004d8c00  55                       push       ebp
004d8c01  8bec                     mov        ebp, esp
004d8c03  6aff                     push       -1
004d8c05  68e485c500               push       0xc585e4
004d8c0a  64a100000000             mov        eax, dword ptr fs:[0]
004d8c10  50                       push       eax
004d8c11  64892500000000           mov        dword ptr fs:[0], esp
004d8c18  83ec20                   sub        esp, 0x20
004d8c1b  56                       push       esi
004d8c1c  8bf1                     mov        esi, ecx
004d8c1e  8b06                     mov        eax, dword ptr [esi]
004d8c20  ff505c                   call       dword ptr [eax + 0x5c]
004d8c23  85c0                     test       eax, eax
004d8c25  0f8430010000             je         0x4d8d5b
004d8c2b  8b16                     mov        edx, dword ptr [esi]
004d8c2d  8d45ec                   lea        eax, [ebp - 0x14]
004d8c30  50                       push       eax
004d8c31  8d4de8                   lea        ecx, [ebp - 0x18]
004d8c34  51                       push       ecx
004d8c35  8d45f0                   lea        eax, [ebp - 0x10]
004d8c38  50                       push       eax
004d8c39  8bce                     mov        ecx, esi
004d8c3b  ff9298070000             call       dword ptr [edx + 0x798]
004d8c41  84c0                     test       al, al
004d8c43  0f8412010000             je         0x4d8d5b
004d8c49  8b869c270000             mov        eax, dword ptr [esi + 0x279c]
004d8c4f  85c0                     test       eax, eax
004d8c51  7567                     jne        0x4d8cba
004d8c53  68b4010000               push       0x1b4
004d8c58  e8f3aff2ff               call       0x403c50
004d8c5d  83c404                   add        esp, 4
004d8c60  8945e4                   mov        dword ptr [ebp - 0x1c], eax
004d8c63  85c0                     test       eax, eax
004d8c65  c745fc00000000           mov        dword ptr [ebp - 4], 0
004d8c6c  7435                     je         0x4d8ca3
004d8c6e  83be9827000008           cmp        dword ptr [esi + 0x2798], 8
004d8c75  7216                     jb         0x4d8c8d
004d8c77  8b9684270000             mov        edx, dword ptr [esi + 0x2784]
004d8c7d  56                       push       esi
004d8c7e  52                       push       edx
004d8c7f  68b03acd00               push       0xcd3ab0
004d8c84  8bc8                     mov        ecx, eax
004d8c86  e8b5a7fcff               call       0x4a3440
004d8c8b  eb18                     jmp        0x4d8ca5
004d8c8d  56                       push       esi
004d8c8e  8d9684270000             lea        edx, [esi + 0x2784]
004d8c94  52                       push       edx
004d8c95  68b03acd00               push       0xcd3ab0
004d8c9a  8bc8                     mov        ecx, eax
004d8c9c  e89fa7fcff               call       0x4a3440
004d8ca1  eb02                     jmp        0x4d8ca5
004d8ca3  33c0                     xor        eax, eax
004d8ca5  85c0                     test       eax, eax
004d8ca7  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004d8cae  89869c270000             mov        dword ptr [esi + 0x279c], eax
004d8cb4  0f84a1000000             je         0x4d8d5b
004d8cba  8b16                     mov        edx, dword ptr [esi]
004d8cbc  8bce                     mov        ecx, esi
004d8cbe  ff92c0000000             call       dword ptr [edx + 0xc0]
004d8cc4  85c0                     test       eax, eax
004d8cc6  7508                     jne        0x4d8cd0
004d8cc8  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004d8ccb  f7d8                     neg        eax
004d8ccd  8945f0                   mov        dword ptr [ebp - 0x10], eax
004d8cd0  8b8e9c270000             mov        ecx, dword ptr [esi + 0x279c]
004d8cd6  8b16                     mov        edx, dword ptr [esi]
004d8cd8  57                       push       edi
004d8cd9  8b39                     mov        edi, dword ptr [ecx]
004d8cdb  8bce                     mov        ecx, esi
004d8cdd  ff929c000000             call       dword ptr [edx + 0x9c]
004d8ce3  0345ec                   add        eax, dword ptr [ebp - 0x14]
004d8ce6  50                       push       eax
004d8ce7  8b06                     mov        eax, dword ptr [esi]
004d8ce9  8bce                     mov        ecx, esi
004d8ceb  ff9098000000             call       dword ptr [eax + 0x98]
004d8cf1  0345e8                   add        eax, dword ptr [ebp - 0x18]
004d8cf4  8b16                     mov        edx, dword ptr [esi]
004d8cf6  50                       push       eax
004d8cf7  8bce                     mov        ecx, esi
004d8cf9  ff9294000000             call       dword ptr [edx + 0x94]
004d8cff  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
004d8d02  8b8e9c270000             mov        ecx, dword ptr [esi + 0x279c]
004d8d08  03c2                     add        eax, edx
004d8d0a  50                       push       eax
004d8d0b  ff5728                   call       dword ptr [edi + 0x28]
004d8d0e  8b8e9c270000             mov        ecx, dword ptr [esi + 0x279c]
004d8d14  8b01                     mov        eax, dword ptr [ecx]
004d8d16  6a00                     push       0
004d8d18  ff500c                   call       dword ptr [eax + 0xc]
004d8d1b  8b8e9c270000             mov        ecx, dword ptr [esi + 0x279c]
004d8d21  8b11                     mov        edx, dword ptr [ecx]
004d8d23  8d45d4                   lea        eax, [ebp - 0x2c]
004d8d26  50                       push       eax
004d8d27  ff525c                   call       dword ptr [edx + 0x5c]
004d8d2a  8b16                     mov        edx, dword ptr [esi]
004d8d2c  6a00                     push       0
004d8d2e  8d4dd4                   lea        ecx, [ebp - 0x2c]
004d8d31  51                       push       ecx
004d8d32  6a00                     push       0
004d8d34  6a02                     push       2
004d8d36  56                       push       esi
004d8d37  8bce                     mov        ecx, esi
004d8d39  c745fc01000000           mov        dword ptr [ebp - 4], 1
004d8d40  ff525c                   call       dword ptr [edx + 0x5c]
004d8d43  8bc8                     mov        ecx, eax
004d8d45  e816530300               call       0x50e060
004d8d4a  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
004d8d4d  85c0                     test       eax, eax
004d8d4f  5f                       pop        edi
004d8d50  7409                     je         0x4d8d5b
004d8d52  50                       push       eax
004d8d53  e885727200               call       0xbfffdd
004d8d58  83c404                   add        esp, 4
004d8d5b  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d8d5e  5e                       pop        esi
004d8d5f  64890d00000000           mov        dword ptr fs:[0], ecx
004d8d66  8be5                     mov        esp, ebp
004d8d68  5d                       pop        ebp
004d8d69  c3                       ret        
004d8d6a  cc                       int3       
004d8d6b  cc                       int3       
004d8d6c  cc                       int3       
004d8d6d  cc                       int3       
004d8d6e  cc                       int3       
004d8d6f  cc                       int3       
004d8d70  55                       push       ebp
004d8d71  8bec                     mov        ebp, esp
004d8d73  53                       push       ebx
004d8d74  56                       push       esi
004d8d75  8bf1                     mov        esi, ecx
004d8d77  8b06                     mov        eax, dword ptr [esi]
004d8d79  57                       push       edi
004d8d7a  ff5010                   call       dword ptr [eax + 0x10]
004d8d7d  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004d8d80  84db                     test       bl, bl
004d8d82  7518                     jne        0x4d8d9c
004d8d84  8bce                     mov        ecx, esi
004d8d86  e865acffff               call       0x4d39f0
004d8d8b  8d8e08010000             lea        ecx, [esi + 0x108]
004d8d91  889eae230000             mov        byte ptr [esi + 0x23ae], bl
004d8d97  e8947f2700               call       0x750d30
004d8d9c  8b16                     mov        edx, dword ptr [esi]
004d8d9e  8bce                     mov        ecx, esi
004d8da0  ff9214040000             call       dword ptr [edx + 0x414]
004d8da6  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d8dac  83cfff                   or         edi, 0xffffffff
004d8daf  57                       push       edi
004d8db0  e83b1ef6ff               call       0x43abf0
004d8db5  84c0                     test       al, al
004d8db7  7440                     je         0x4d8df9
004d8db9  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d8dbf  81c140100000             add        ecx, 0x1040
004d8dc5  e89692f2ff               call       0x402060
004d8dca  83f804                   cmp        eax, 4
004d8dcd  752a                     jne        0x4d8df9
004d8dcf  a148280001               mov        eax, dword ptr [0x1002848]
004d8dd4  8b8858100000             mov        ecx, dword ptr [eax + 0x1058]
004d8dda  83792803                 cmp        dword ptr [ecx + 0x28], 3
004d8dde  7519                     jne        0x4d8df9
004d8de0  a188f10401               mov        eax, dword ptr [0x104f188]
004d8de5  85c0                     test       eax, eax
004d8de7  7410                     je         0x4d8df9
004d8de9  8b8088000000             mov        eax, dword ptr [eax + 0x88]
004d8def  83f804                   cmp        eax, 4
004d8df2  7410                     je         0x4d8e04
004d8df4  83f803                   cmp        eax, 3
004d8df7  740b                     je         0x4d8e04
004d8df9  8b16                     mov        edx, dword ptr [esi]
004d8dfb  53                       push       ebx
004d8dfc  8bce                     mov        ecx, esi
004d8dfe  ff92a8050000             call       dword ptr [edx + 0x5a8]
004d8e04  8b06                     mov        eax, dword ptr [esi]
004d8e06  8bce                     mov        ecx, esi
004d8e08  ff9058060000             call       dword ptr [eax + 0x658]
004d8e0e  8b16                     mov        edx, dword ptr [esi]
004d8e10  6a00                     push       0
004d8e12  8bce                     mov        ecx, esi
004d8e14  ff9248030000             call       dword ptr [edx + 0x348]
004d8e1a  8b06                     mov        eax, dword ptr [esi]
004d8e1c  8bce                     mov        ecx, esi
004d8e1e  ff90dc030000             call       dword ptr [eax + 0x3dc]
004d8e24  84c0                     test       al, al
004d8e26  750c                     jne        0x4d8e34
004d8e28  89be98260000             mov        dword ptr [esi + 0x2698], edi
004d8e2e  89be94260000             mov        dword ptr [esi + 0x2694], edi
004d8e34  84db                     test       bl, bl
004d8e36  754c                     jne        0x4d8e84
004d8e38  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004d8e3e  750e                     jne        0x4d8e4e
004d8e40  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004d8e43  51                       push       ecx
004d8e44  e8b731faff               call       0x47c000
004d8e49  83c404                   add        esp, 4
004d8e4c  eb1d                     jmp        0x4d8e6b
004d8e4e  8bce                     mov        ecx, esi
004d8e50  e83b32fcff               call       0x49c090
004d8e55  84c0                     test       al, al
004d8e57  7419                     je         0x4d8e72
004d8e59  8b16                     mov        edx, dword ptr [esi]
004d8e5b  8bce                     mov        ecx, esi
004d8e5d  ff5234                   call       dword ptr [edx + 0x34]
004d8e60  84c0                     test       al, al
004d8e62  7407                     je         0x4d8e6b
004d8e64  8bce                     mov        ecx, esi
004d8e66  e865a2feff               call       0x4c30d0
004d8e6b  8bce                     mov        ecx, esi
004d8e6d  e85e98ffff               call       0x4d26d0
004d8e72  8a4510                   mov        al, byte ptr [ebp + 0x10]
004d8e75  84c0                     test       al, al
004d8e77  740b                     je         0x4d8e84
004d8e79  8d8e40210000             lea        ecx, [esi + 0x2140]
004d8e7f  e86cd7f6ff               call       0x4465f0
004d8e84  84db                     test       bl, bl
004d8e86  c6861c24000000           mov        byte ptr [esi + 0x241c], 0
004d8e8d  0f85fb000000             jne        0x4d8f8e
004d8e93  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d8e99  57                       push       edi
004d8e9a  e8511df6ff               call       0x43abf0
004d8e9f  84c0                     test       al, al
004d8ea1  7470                     je         0x4d8f13
004d8ea3  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d8ea9  81c140100000             add        ecx, 0x1040
004d8eaf  e8ac91f2ff               call       0x402060
004d8eb4  83f809                   cmp        eax, 9
004d8eb7  745a                     je         0x4d8f13
004d8eb9  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d8ebf  81c140100000             add        ecx, 0x1040
004d8ec5  e89691f2ff               call       0x402060
004d8eca  83f804                   cmp        eax, 4
004d8ecd  7516                     jne        0x4d8ee5
004d8ecf  a188f10401               mov        eax, dword ptr [0x104f188]
004d8ed4  85c0                     test       eax, eax
004d8ed6  740d                     je         0x4d8ee5
004d8ed8  83b88800000002           cmp        dword ptr [eax + 0x88], 2
004d8edf  0f849d000000             je         0x4d8f82
004d8ee5  8b3e                     mov        edi, dword ptr [esi]
004d8ee7  6a01                     push       1
004d8ee9  6a00                     push       0
004d8eeb  8bce                     mov        ecx, esi
004d8eed  ff9738020000             call       dword ptr [edi + 0x238]
004d8ef3  50                       push       eax
004d8ef4  8bce                     mov        ecx, esi
004d8ef6  ff97ec030000             call       dword ptr [edi + 0x3ec]
004d8efc  8b3e                     mov        edi, dword ptr [esi]
004d8efe  6a01                     push       1
004d8f00  8bce                     mov        ecx, esi
004d8f02  ff97fc030000             call       dword ptr [edi + 0x3fc]
004d8f08  50                       push       eax
004d8f09  8bce                     mov        ecx, esi
004d8f0b  ff97f4030000             call       dword ptr [edi + 0x3f4]
004d8f11  eb6f                     jmp        0x4d8f82
004d8f13  8b1e                     mov        ebx, dword ptr [esi]
004d8f15  6a01                     push       1
004d8f17  6a00                     push       0
004d8f19  8bce                     mov        ecx, esi
004d8f1b  ff93d4050000             call       dword ptr [ebx + 0x5d4]
004d8f21  8bf8                     mov        edi, eax
004d8f23  8b06                     mov        eax, dword ptr [esi]
004d8f25  8bce                     mov        ecx, esi
004d8f27  ff9038020000             call       dword ptr [eax + 0x238]
004d8f2d  0faff8                   imul       edi, eax
004d8f30  b81f85eb51               mov        eax, 0x51eb851f
004d8f35  f7ef                     imul       edi
004d8f37  c1fa05                   sar        edx, 5
004d8f3a  8bca                     mov        ecx, edx
004d8f3c  c1e91f                   shr        ecx, 0x1f
004d8f3f  03ca                     add        ecx, edx
004d8f41  51                       push       ecx
004d8f42  8bce                     mov        ecx, esi
004d8f44  ff93ec030000             call       dword ptr [ebx + 0x3ec]
004d8f4a  8b1e                     mov        ebx, dword ptr [esi]
004d8f4c  6a01                     push       1
004d8f4e  8bce                     mov        ecx, esi
004d8f50  ff93d4050000             call       dword ptr [ebx + 0x5d4]
004d8f56  8b16                     mov        edx, dword ptr [esi]
004d8f58  8bce                     mov        ecx, esi
004d8f5a  8bf8                     mov        edi, eax
004d8f5c  ff92fc030000             call       dword ptr [edx + 0x3fc]
004d8f62  0faff8                   imul       edi, eax
004d8f65  b81f85eb51               mov        eax, 0x51eb851f
004d8f6a  f7ef                     imul       edi
004d8f6c  c1fa05                   sar        edx, 5
004d8f6f  8bc2                     mov        eax, edx
004d8f71  c1e81f                   shr        eax, 0x1f
004d8f74  03c2                     add        eax, edx
004d8f76  50                       push       eax
004d8f77  8bce                     mov        ecx, esi
004d8f79  ff93f4030000             call       dword ptr [ebx + 0x3f4]
004d8f7f  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004d8f82  8b16                     mov        edx, dword ptr [esi]
004d8f84  6a00                     push       0
004d8f86  8bce                     mov        ecx, esi
004d8f88  ff92d8030000             call       dword ptr [edx + 0x3d8]
004d8f8e  8b06                     mov        eax, dword ptr [esi]
004d8f90  6a01                     push       1
004d8f92  8bce                     mov        ecx, esi
004d8f94  ff90d0020000             call       dword ptr [eax + 0x2d0]
004d8f9a  8b16                     mov        edx, dword ptr [esi]
004d8f9c  6a01                     push       1
004d8f9e  8bce                     mov        ecx, esi
004d8fa0  ff92d8020000             call       dword ptr [edx + 0x2d8]
004d8fa6  8b06                     mov        eax, dword ptr [esi]
004d8fa8  6a01                     push       1
004d8faa  8bce                     mov        ecx, esi
004d8fac  ff9088020000             call       dword ptr [eax + 0x288]
004d8fb2  84db                     test       bl, bl
004d8fb4  7547                     jne        0x4d8ffd
004d8fb6  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004d8fbc  8b4244                   mov        eax, dword ptr [edx + 0x44]
004d8fbf  8b8e6c180000             mov        ecx, dword ptr [esi + 0x186c]
004d8fc5  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004d8fcb  8d0488                   lea        eax, [eax + ecx*4]
004d8fce  8bc8                     mov        ecx, eax
004d8fd0  33ca                     xor        ecx, edx
004d8fd2  8908                     mov        dword ptr [eax], ecx
004d8fd4  a1d8012101               mov        eax, dword ptr [0x12101d8]
004d8fd9  8b966c180000             mov        edx, dword ptr [esi + 0x186c]
004d8fdf  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004d8fe2  8d0491                   lea        eax, [ecx + edx*4]
004d8fe5  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004d8feb  8bd0                     mov        edx, eax
004d8fed  33d1                     xor        edx, ecx
004d8fef  68000000ff               push       0xff000000
004d8ff4  8bce                     mov        ecx, esi
004d8ff6  8910                     mov        dword ptr [eax], edx
004d8ff8  e863fefbff               call       0x498e60
004d8ffd  8b06                     mov        eax, dword ptr [esi]
004d8fff  6a00                     push       0
004d9001  6a00                     push       0
004d9003  8bce                     mov        ecx, esi
004d9005  ff90e0020000             call       dword ptr [eax + 0x2e0]
004d900b  8b16                     mov        edx, dword ptr [esi]
004d900d  8bce                     mov        ecx, esi
004d900f  ff5234                   call       dword ptr [edx + 0x34]
004d9012  84c0                     test       al, al
004d9014  7411                     je         0x4d9027
004d9016  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004d901c  85c9                     test       ecx, ecx
004d901e  7407                     je         0x4d9027
004d9020  6a00                     push       0
004d9022  e859a30500               call       0x533380
004d9027  8d8e50250000             lea        ecx, [esi + 0x2550]
004d902d  e82ea90000               call       0x4e3960
004d9032  5f                       pop        edi
004d9033  5e                       pop        esi
004d9034  5b                       pop        ebx
004d9035  5d                       pop        ebp
004d9036  c20c00                   ret        0xc
004d9039  cc                       int3       
004d903a  cc                       int3       
004d903b  cc                       int3       
004d903c  cc                       int3       
004d903d  cc                       int3       
004d903e  cc                       int3       
004d903f  cc                       int3       
004d9040  55                       push       ebp
004d9041  8bec                     mov        ebp, esp
004d9043  6aff                     push       -1
004d9045  680f86c500               push       0xc5860f
004d904a  64a100000000             mov        eax, dword ptr fs:[0]
004d9050  50                       push       eax
004d9051  64892500000000           mov        dword ptr fs:[0], esp
004d9058  81ec30040000             sub        esp, 0x430
004d905e  56                       push       esi
004d905f  8bf1                     mov        esi, ecx
004d9061  c745e800000000           mov        dword ptr [ebp - 0x18], 0
004d9068  e82330fcff               call       0x49c090
004d906d  84c0                     test       al, al
004d906f  0f84f8060000             je         0x4d976d
004d9075  83beb001000002           cmp        dword ptr [esi + 0x1b0], 2
004d907c  0f84eb060000             je         0x4d976d
004d9082  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004d9085  8b06                     mov        eax, dword ptr [esi]
004d9087  53                       push       ebx
004d9088  51                       push       ecx
004d9089  8bce                     mov        ecx, esi
004d908b  ff907c060000             call       dword ptr [eax + 0x67c]
004d9091  8bd8                     mov        ebx, eax
004d9093  85db                     test       ebx, ebx
004d9095  895dec                   mov        dword ptr [ebp - 0x14], ebx
004d9098  7514                     jne        0x4d90ae
004d909a  5b                       pop        ebx
004d909b  32c0                     xor        al, al
004d909d  5e                       pop        esi
004d909e  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d90a1  64890d00000000           mov        dword ptr fs:[0], ecx
004d90a8  8be5                     mov        esp, ebp
004d90aa  5d                       pop        ebp
004d90ab  c21000                   ret        0x10
004d90ae  8d8b1c030000             lea        ecx, [ebx + 0x31c]
004d90b4  e8a78ff2ff               call       0x402060
004d90b9  85c0                     test       eax, eax
004d90bb  8945c4                   mov        dword ptr [ebp - 0x3c], eax
004d90be  c645f301                 mov        byte ptr [ebp - 0xd], 1
004d90c2  74d6                     je         0x4d909a
004d90c4  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d90ca  e80115f6ff               call       0x43a5d0
004d90cf  84c0                     test       al, al
004d90d1  740b                     je         0x4d90de
004d90d3  8bcb                     mov        ecx, ebx
004d90d5  e8d6990000               call       0x4e2ab0
004d90da  84c0                     test       al, al
004d90dc  75bc                     jne        0x4d909a
004d90de  8b16                     mov        edx, dword ptr [esi]
004d90e0  8bce                     mov        ecx, esi
004d90e2  ff5234                   call       dword ptr [edx + 0x34]
004d90e5  84c0                     test       al, al
004d90e7  7404                     je         0x4d90ed
004d90e9  c6450c00                 mov        byte ptr [ebp + 0xc], 0
004d90ed  57                       push       edi
004d90ee  6aff                     push       -1
004d90f0  56                       push       esi
004d90f1  8bcb                     mov        ecx, ebx
004d90f3  e8c89b0000               call       0x4e2cc0
004d90f8  8bf8                     mov        edi, eax
004d90fa  8b06                     mov        eax, dword ptr [esi]
004d90fc  8bce                     mov        ecx, esi
004d90fe  89                       .byte      0x89
004d90ff  7d                       .byte      0x7d