00ac8e00  55                       push       ebp
00ac8e01  8bec                     mov        ebp, esp
00ac8e03  81ecc0000000             sub        esp, 0xc0
00ac8e09  53                       push       ebx
00ac8e0a  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00ac8e0d  85db                     test       ebx, ebx
00ac8e0f  7507                     jne        0xac8e18
00ac8e11  33c0                     xor        eax, eax
00ac8e13  5b                       pop        ebx
00ac8e14  8be5                     mov        esp, ebp
00ac8e16  5d                       pop        ebp
00ac8e17  c3                       ret        
00ac8e18  56                       push       esi
00ac8e19  57                       push       edi
00ac8e1a  6a00                     push       0
00ac8e1c  6a10                     push       0x10
00ac8e1e  53                       push       ebx
00ac8e1f  e890981300               call       0xc026b4
00ac8e24  53                       push       ebx
00ac8e25  6a01                     push       1
00ac8e27  8d45fc                   lea        eax, [ebp - 4]
00ac8e2a  6a04                     push       4
00ac8e2c  50                       push       eax
00ac8e2d  e804961300               call       0xc02436
00ac8e32  8b75fc                   mov        esi, dword ptr [ebp - 4]
00ac8e35  69f608010000             imul       esi, esi, 0x108
00ac8e3b  6a00                     push       0
00ac8e3d  6a00                     push       0
00ac8e3f  53                       push       ebx
00ac8e40  83c614                   add        esi, 0x14
00ac8e43  e86c981300               call       0xc026b4
00ac8e48  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
00ac8e4e  51                       push       ecx
00ac8e4f  e85c5ddeff               call       0x8aebb0
00ac8e54  b879787878               mov        eax, 0x78787879
00ac8e59  f7ee                     imul       esi
00ac8e5b  c1fa03                   sar        edx, 3
00ac8e5e  8bfa                     mov        edi, edx
00ac8e60  c1ef1f                   shr        edi, 0x1f
00ac8e63  03fa                     add        edi, edx
00ac8e65  83c42c                   add        esp, 0x2c
00ac8e68  85ff                     test       edi, edi
00ac8e6a  c7450800000000           mov        dword ptr [ebp + 8], 0
00ac8e71  7e36                     jle        0xac8ea9
00ac8e73  53                       push       ebx
00ac8e74  6a01                     push       1
00ac8e76  8d55e8                   lea        edx, [ebp - 0x18]
00ac8e79  6a11                     push       0x11
00ac8e7b  52                       push       edx
00ac8e7c  e8b5951300               call       0xc02436
00ac8e81  83c410                   add        esp, 0x10
00ac8e84  83f801                   cmp        eax, 1
00ac8e87  7578                     jne        0xac8f01
00ac8e89  6a11                     push       0x11
00ac8e8b  8d45e8                   lea        eax, [ebp - 0x18]
00ac8e8e  50                       push       eax
00ac8e8f  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
00ac8e95  51                       push       ecx
00ac8e96  e84598deff               call       0x8b26e0
00ac8e9b  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac8e9e  83c40c                   add        esp, 0xc
00ac8ea1  40                       inc        eax
00ac8ea2  3bc7                     cmp        eax, edi
00ac8ea4  894508                   mov        dword ptr [ebp + 8], eax
00ac8ea7  7cca                     jl         0xac8e73
00ac8ea9  8d55a8                   lea        edx, [ebp - 0x58]
00ac8eac  52                       push       edx
00ac8ead  8d8540ffffff             lea        eax, [ebp - 0xc0]
00ac8eb3  50                       push       eax
00ac8eb4  e8f798deff               call       0x8b27b0
00ac8eb9  6a00                     push       0
00ac8ebb  56                       push       esi
00ac8ebc  53                       push       ebx
00ac8ebd  e8f2971300               call       0xc026b4
00ac8ec2  53                       push       ebx
00ac8ec3  6a01                     push       1
00ac8ec5  8d4dc8                   lea        ecx, [ebp - 0x38]
00ac8ec8  6a20                     push       0x20
00ac8eca  51                       push       ecx
00ac8ecb  e866951300               call       0xc02436
00ac8ed0  83c424                   add        esp, 0x24
00ac8ed3  83f801                   cmp        eax, 1
00ac8ed6  7529                     jne        0xac8f01
00ac8ed8  33c9                     xor        ecx, ecx
00ac8eda  33c0                     xor        eax, eax
00ac8edc  8d642400                 lea        esp, [esp]
00ac8ee0  8b5405c8                 mov        edx, dword ptr [ebp + eax - 0x38]
00ac8ee4  8b7405a8                 mov        esi, dword ptr [ebp + eax - 0x58]
00ac8ee8  83c004                   add        eax, 4
00ac8eeb  3bd6                     cmp        edx, esi
00ac8eed  7512                     jne        0xac8f01
00ac8eef  41                       inc        ecx
00ac8ef0  83f908                   cmp        ecx, 8
00ac8ef3  7ceb                     jl         0xac8ee0
00ac8ef5  5f                       pop        edi
00ac8ef6  5e                       pop        esi
00ac8ef7  b801000000               mov        eax, 1
00ac8efc  5b                       pop        ebx
00ac8efd  8be5                     mov        esp, ebp
00ac8eff  5d                       pop        ebp
00ac8f00  c3                       ret        
00ac8f01  5f                       pop        edi
00ac8f02  5e                       pop        esi
00ac8f03  33c0                     xor        eax, eax
00ac8f05  5b                       pop        ebx
00ac8f06  8be5                     mov        esp, ebp
00ac8f08  5d                       pop        ebp
00ac8f09  c3                       ret        
00ac8f0a  cc                       int3       
00ac8f0b  cc                       int3       
00ac8f0c  cc                       int3       
00ac8f0d  cc                       int3       
00ac8f0e  cc                       int3       
00ac8f0f  cc                       int3       
00ac8f10  55                       push       ebp
00ac8f11  8bec                     mov        ebp, esp
00ac8f13  8b                       .byte      0x8b