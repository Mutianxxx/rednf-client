004b9d80  55                       push       ebp
004b9d81  8bec                     mov        ebp, esp
004b9d83  56                       push       esi
004b9d84  57                       push       edi
004b9d85  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b9d88  83ff01                   cmp        edi, 1
004b9d8b  8bf1                     mov        esi, ecx
004b9d8d  0f8fa4000000             jg         0x4b9e37
004b9d93  85ff                     test       edi, edi
004b9d95  0f8c9c000000             jl         0x4b9e37
004b9d9b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b9d9e  53                       push       ebx
004b9d9f  8d4d08                   lea        ecx, [ebp + 8]
004b9da2  51                       push       ecx
004b9da3  8d8cfed4150000           lea        ecx, [esi + edi*8 + 0x15d4]
004b9daa  894508                   mov        dword ptr [ebp + 8], eax
004b9dad  e8aea7f4ff               call       0x404560
004b9db2  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004b9db5  8d4508                   lea        eax, [ebp + 8]
004b9db8  50                       push       eax
004b9db9  8d8cfee4150000           lea        ecx, [esi + edi*8 + 0x15e4]
004b9dc0  895508                   mov        dword ptr [ebp + 8], edx
004b9dc3  e898a7f4ff               call       0x404560
004b9dc8  8a4d14                   mov        cl, byte ptr [ebp + 0x14]
004b9dcb  8b5d18                   mov        ebx, dword ptr [ebp + 0x18]
004b9dce  8d5514                   lea        edx, [ebp + 0x14]
004b9dd1  888c3706160000           mov        byte ptr [edi + esi + 0x1606], cl
004b9dd8  52                       push       edx
004b9dd9  8d8cfef4150000           lea        ecx, [esi + edi*8 + 0x15f4]
004b9de0  895d14                   mov        dword ptr [ebp + 0x14], ebx
004b9de3  e878a7f4ff               call       0x404560
004b9de8  8a451c                   mov        al, byte ptr [ebp + 0x1c]
004b9deb  85db                     test       ebx, ebx
004b9ded  88843704160000           mov        byte ptr [edi + esi + 0x1604], al
004b9df4  5b                       pop        ebx
004b9df5  7408                     je         0x4b9dff
004b9df7  c684370616000000         mov        byte ptr [edi + esi + 0x1606], 0
004b9dff  8b8e08160000             mov        ecx, dword ptr [esi + 0x1608]
004b9e05  b804000000               mov        eax, 4
004b9e0a  3bc8                     cmp        ecx, eax
004b9e0c  c6451401                 mov        byte ptr [ebp + 0x14], 1
004b9e10  7408                     je         0x4b9e1a
004b9e12  39860c160000             cmp        dword ptr [esi + 0x160c], eax
004b9e18  7504                     jne        0x4b9e1e
004b9e1a  c6451400                 mov        byte ptr [ebp + 0x14], 0
004b9e1e  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004b9e21  8b8cbe08160000           mov        ecx, dword ptr [esi + edi*4 + 0x1608]
004b9e28  8b16                     mov        edx, dword ptr [esi]
004b9e2a  6a00                     push       0
004b9e2c  50                       push       eax
004b9e2d  51                       push       ecx
004b9e2e  57                       push       edi
004b9e2f  8bce                     mov        ecx, esi
004b9e31  ff9298040000             call       dword ptr [edx + 0x498]
004b9e37  5f                       pop        edi
004b9e38  5e                       pop        esi
004b9e39  5d                       pop        ebp
004b9e3a  c21800                   ret        0x18
004b9e3d  cc                       int3       
004b9e3e  cc                       int3       
004b9e3f  cc                       int3       
004b9e40  55                       push       ebp
004b9e41  8bec                     mov        ebp, esp
004b9e43  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b9e49  8b5244                   mov        edx, dword ptr [edx + 0x44]
004b9e4c  8b811c160000             mov        eax, dword ptr [ecx + 0x161c]
004b9e52  56                       push       esi
004b9e53  8d0482                   lea        eax, [edx + eax*4]
004b9e56  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004b9e5c  8bf0                     mov        esi, eax
004b9e5e  33f2                     xor        esi, edx
004b9e60  8b5508                   mov        edx, dword ptr [ebp + 8]
004b9e63  33f2                     xor        esi, edx
004b9e65  8930                     mov        dword ptr [eax], esi
004b9e67  8b35d8012101             mov        esi, dword ptr [0x12101d8]
004b9e6d  8b7648                   mov        esi, dword ptr [esi + 0x48]
004b9e70  8b811c160000             mov        eax, dword ptr [ecx + 0x161c]
004b9e76  8d0486                   lea        eax, [esi + eax*4]
004b9e79  57                       push       edi
004b9e7a  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b9e80  8bf0                     mov        esi, eax
004b9e82  33f7                     xor        esi, edi
004b9e84  33f2                     xor        esi, edx
004b9e86  8930                     mov        dword ptr [eax], esi
004b9e88  8b810c160000             mov        eax, dword ptr [ecx + 0x160c]
004b9e8e  8b11                     mov        edx, dword ptr [ecx]
004b9e90  6a00                     push       0
004b9e92  50                       push       eax
004b9e93  8b8108160000             mov        eax, dword ptr [ecx + 0x1608]
004b9e99  50                       push       eax
004b9e9a  ff929c040000             call       dword ptr [edx + 0x49c]
004b9ea0  5f                       pop        edi
004b9ea1  5e                       pop        esi
004b9ea2  5d                       pop        ebp
004b9ea3  c20400                   ret        4
004b9ea6  cc                       int3       
004b9ea7  cc                       int3       
004b9ea8  cc                       int3       
004b9ea9  cc                       int3       
004b9eaa  cc                       int3       
004b9eab  cc                       int3       
004b9eac  cc                       int3       
004b9ead  cc                       int3       
004b9eae  cc                       int3       
004b9eaf  cc                       int3       
004b9eb0  55                       push       ebp
004b9eb1  8bec                     mov        ebp, esp
004b9eb3  53                       push       ebx
004b9eb4  56                       push       esi
004b9eb5  8bf1                     mov        esi, ecx
004b9eb7  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b9ebd  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004b9ec0  8b8624160000             mov        eax, dword ptr [esi + 0x1624]
004b9ec6  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004b9ecc  8d0482                   lea        eax, [edx + eax*4]
004b9ecf  8d9e20160000             lea        ebx, [esi + 0x1620]
004b9ed5  8bd0                     mov        edx, eax
004b9ed7  33d1                     xor        edx, ecx
004b9ed9  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b9edc  33d1                     xor        edx, ecx
004b9ede  8910                     mov        dword ptr [eax], edx
004b9ee0  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b9ee6  8b5248                   mov        edx, dword ptr [edx + 0x48]
004b9ee9  8b4304                   mov        eax, dword ptr [ebx + 4]
004b9eec  8d0482                   lea        eax, [edx + eax*4]
004b9eef  57                       push       edi
004b9ef0  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b9ef6  8bd0                     mov        edx, eax
004b9ef8  33d7                     xor        edx, edi
004b9efa  33d1                     xor        edx, ecx
004b9efc  8910                     mov        dword ptr [eax], edx
004b9efe  8b                       .byte      0x8b
004b9eff  860401                   xchg       byte ptr [ecx + eax], al
004b9f02  00                       .byte      0x00
