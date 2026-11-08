00ac8d00  6a04                     push       4
00ac8d02  50                       push       eax
00ac8d03  c7450800000000           mov        dword ptr [ebp + 8], 0
00ac8d0a  e827971300               call       0xc02436
00ac8d0f  8b7d08                   mov        edi, dword ptr [ebp + 8]
00ac8d12  69ff08010000             imul       edi, edi, 0x108
00ac8d18  6a00                     push       0
00ac8d1a  6a00                     push       0
00ac8d1c  56                       push       esi
00ac8d1d  83c714                   add        edi, 0x14
00ac8d20  e88f991300               call       0xc026b4
00ac8d25  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
00ac8d2b  51                       push       ecx
00ac8d2c  e87f5edeff               call       0x8aebb0
00ac8d31  b879787878               mov        eax, 0x78787879
00ac8d36  f7ef                     imul       edi
00ac8d38  c1fa03                   sar        edx, 3
00ac8d3b  8bda                     mov        ebx, edx
00ac8d3d  c1eb1f                   shr        ebx, 0x1f
00ac8d40  03da                     add        ebx, edx
00ac8d42  83c42c                   add        esp, 0x2c
00ac8d45  85db                     test       ebx, ebx
00ac8d47  c745fc00000000           mov        dword ptr [ebp - 4], 0
00ac8d4e  7e36                     jle        0xac8d86
00ac8d50  56                       push       esi
00ac8d51  6a01                     push       1
00ac8d53  8d55e8                   lea        edx, [ebp - 0x18]
00ac8d56  6a11                     push       0x11
00ac8d58  52                       push       edx
00ac8d59  e8d8961300               call       0xc02436
00ac8d5e  83c410                   add        esp, 0x10
00ac8d61  83f801                   cmp        eax, 1
00ac8d64  757d                     jne        0xac8de3
00ac8d66  6a11                     push       0x11
00ac8d68  8d45e8                   lea        eax, [ebp - 0x18]
00ac8d6b  50                       push       eax
00ac8d6c  8d8d40ffffff             lea        ecx, [ebp - 0xc0]
00ac8d72  51                       push       ecx
00ac8d73  e86899deff               call       0x8b26e0
00ac8d78  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac8d7b  83c40c                   add        esp, 0xc
00ac8d7e  40                       inc        eax
00ac8d7f  3bc3                     cmp        eax, ebx
00ac8d81  8945fc                   mov        dword ptr [ebp - 4], eax
00ac8d84  7cca                     jl         0xac8d50
00ac8d86  8d55a8                   lea        edx, [ebp - 0x58]
00ac8d89  52                       push       edx
00ac8d8a  8d8540ffffff             lea        eax, [ebp - 0xc0]
00ac8d90  50                       push       eax
00ac8d91  e81a9adeff               call       0x8b27b0
00ac8d96  6a00                     push       0
00ac8d98  57                       push       edi
00ac8d99  56                       push       esi
00ac8d9a  e815991300               call       0xc026b4
00ac8d9f  56                       push       esi
00ac8da0  6a01                     push       1
00ac8da2  8d4dc8                   lea        ecx, [ebp - 0x38]
00ac8da5  6a20                     push       0x20
00ac8da7  51                       push       ecx
00ac8da8  e889961300               call       0xc02436
00ac8dad  83c424                   add        esp, 0x24
00ac8db0  83f801                   cmp        eax, 1
00ac8db3  56                       push       esi
00ac8db4  752e                     jne        0xac8de4
00ac8db6  e8c18e1300               call       0xc01c7c
00ac8dbb  83c404                   add        esp, 4
00ac8dbe  33c9                     xor        ecx, ecx
00ac8dc0  33c0                     xor        eax, eax
00ac8dc2  8b5405c8                 mov        edx, dword ptr [ebp + eax - 0x38]
00ac8dc6  8b7405a8                 mov        esi, dword ptr [ebp + eax - 0x58]
00ac8dca  83c004                   add        eax, 4
00ac8dcd  3bd6                     cmp        edx, esi
00ac8dcf  751b                     jne        0xac8dec
00ac8dd1  41                       inc        ecx
00ac8dd2  83f908                   cmp        ecx, 8
00ac8dd5  7ceb                     jl         0xac8dc2
00ac8dd7  5f                       pop        edi
00ac8dd8  5b                       pop        ebx
00ac8dd9  b801000000               mov        eax, 1
00ac8dde  5e                       pop        esi
00ac8ddf  8be5                     mov        esp, ebp
00ac8de1  5d                       pop        ebp
00ac8de2  c3                       ret        
00ac8de3  56                       push       esi
00ac8de4  e8938e1300               call       0xc01c7c
00ac8de9  83c404                   add        esp, 4
00ac8dec  5f                       pop        edi
00ac8ded  5b                       pop        ebx
00ac8dee  33c0                     xor        eax, eax
00ac8df0  5e                       pop        esi
00ac8df1  8be5                     mov        esp, ebp
00ac8df3  5d                       pop        ebp
00ac8df4  c3                       ret        
00ac8df5  cc                       int3       
00ac8df6  cc                       int3       
00ac8df7  cc                       int3       
00ac8df8  cc                       int3       
00ac8df9  cc                       int3       
00ac8dfa  cc                       int3       
00ac8dfb  cc                       int3       
00ac8dfc  cc                       int3       
00ac8dfd  cc                       int3       
00ac8dfe  cc                       int3       
00ac8dff  cc                       int3       
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
00ac8f13  8b410c                   mov        eax, dword ptr [ecx + 0xc]
00ac8f16  85c0                     test       eax, eax
00ac8f18  7406                     je         0xac8f20
00ac8f1a  33c0                     xor        eax, eax
00ac8f1c  5d                       pop        ebp
00ac8f1d  c20400                   ret        4
00ac8f20  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac8f23  50                       push       eax
00ac8f24  e8538d1300               call       0xc01c7c
00ac8f29  83c404                   add        esp, 4
00ac8f2c  5d                       pop        ebp
00ac8f2d  c20400                   ret        4
00ac8f30  55                       push       ebp
00ac8f31  8bec                     mov        ebp, esp
00ac8f33  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac8f36  83e800                   sub        eax, 0
00ac8f39  7417                     je         0xac8f52
00ac8f3b  48                       dec        eax
00ac8f3c  7526                     jne        0xac8f64
00ac8f3e  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac8f41  50                       push       eax
00ac8f42  6a01                     push       1
00ac8f44  e877150000               call       0xaca4c0
00ac8f49  8bc8                     mov        ecx, eax
00ac8f4b  e8a0bcfcff               call       0xa94bf0
00ac8f50  5d                       pop        ebp
00ac8f51  c3                       ret        
00ac8f52  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00ac8f55  51                       push       ecx
00ac8f56  6a00                     push       0
00ac8f58  e863150000               call       0xaca4c0
00ac8f5d  8bc8                     mov        ecx, eax
00ac8f5f  e88cbcfcff               call       0xa94bf0
00ac8f64  5d                       pop        ebp
00ac8f65  c3                       ret        
00ac8f66  cc                       int3       
00ac8f67  cc                       int3       
00ac8f68  cc                       int3       
00ac8f69  cc                       int3       
00ac8f6a  cc                       int3       
00ac8f6b  cc                       int3       
00ac8f6c  cc                       int3       
00ac8f6d  cc                       int3       
00ac8f6e  cc                       int3       
00ac8f6f  cc                       int3       
00ac8f70  55                       push       ebp
00ac8f71  8bec                     mov        ebp, esp
00ac8f73  56                       push       esi
00ac8f74  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac8f77  85f6                     test       esi, esi
00ac8f79  743b                     je         0xac8fb6
00ac8f7b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac8f7e  c1e004                   shl        eax, 4
00ac8f81  8b886cab0d01             mov        ecx, dword ptr [eax + 0x10dab6c]
00ac8f87  85c9                     test       ecx, ecx
00ac8f89  7442                     je         0xac8fcd
00ac8f8b  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00ac8f8e  85c9                     test       ecx, ecx
00ac8f90  7433                     je         0xac8fc5
00ac8f92  8b11                     mov        edx, dword ptr [ecx]
00ac8f94  85d2                     test       edx, edx
00ac8f96  7423                     je         0xac8fbb
00ac8f98  83fa02                   cmp        edx, 2
00ac8f9b  7519                     jne        0xac8fb6
00ac8f9d  56                       push       esi
00ac8f9e  8d8860ab0d01             lea        ecx, [eax + 0x10dab60]
00ac8fa4  e867ffffff               call       0xac8f10
00ac8fa9  f7d8                     neg        eax
00ac8fab  1ac0                     sbb        al, al
00ac8fad  fec0                     inc        al
00ac8faf  0fb6c0                   movzx      eax, al
00ac8fb2  85c0                     test       eax, eax
00ac8fb4  7502                     jne        0xac8fb8
00ac8fb6  33c0                     xor        eax, eax
00ac8fb8  5e                       pop        esi
00ac8fb9  5d                       pop        ebp
00ac8fba  c3                       ret        
00ac8fbb  85c9                     test       ecx, ecx
00ac8fbd  7406                     je         0xac8fc5
00ac8fbf  c70102000000             mov        dword ptr [ecx], 2
00ac8fc5  b801000000               mov        eax, 1
00ac8fca  5e                       pop        esi
00ac8fcb  5d                       pop        ebp
00ac8fcc  c3                       ret        
00ac8fcd  56                       push       esi
00ac8fce  e8a98c1300               call       0xc01c7c
00ac8fd3  83c404                   add        esp, 4
00ac8fd6  f7d8                     neg        eax
00ac8fd8  1ac0                     sbb        al, al
00ac8fda  fec0                     inc        al
00ac8fdc  0fb6c0                   movzx      eax, al
00ac8fdf  85c0                     test       eax, eax
00ac8fe1  74d3                     je         0xac8fb6
00ac8fe3  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00ac8fe6  85c9                     test       ecx, ecx
00ac8fe8  74ce                     je         0xac8fb8
00ac8fea  c70101000000             mov        dword ptr [ecx], 1
00ac8ff0  5e                       pop        esi
00ac8ff1  5d                       pop        ebp
00ac8ff2  c3                       ret        
00ac8ff3  cc                       int3       
00ac8ff4  cc                       int3       
00ac8ff5  cc                       int3       
00ac8ff6  cc                       int3       
00ac8ff7  cc                       int3       
00ac8ff8  cc                       int3       
00ac8ff9  cc                       int3       
00ac8ffa  cc                       int3       
00ac8ffb  cc                       int3       
00ac8ffc  cc                       int3       
00ac8ffd  cc                       int3       
00ac8ffe  cc                       int3       
00ac8fff  cc                       int3       
00ac9000  8b4108                   mov        eax, dword ptr [ecx + 8]
00ac9003  69c008010000             imul       eax, eax, 0x108
00ac9009  83c014                   add        eax, 0x14
00ac900c  c3                       ret        
00ac900d  cc                       int3       
00ac900e  cc                       int3       
00ac900f  cc                       int3       
00ac9010  55                       push       ebp
00ac9011  8bec                     mov        ebp, esp
00ac9013  8b5508                   mov        edx, dword ptr [ebp + 8]
00ac9016  85d2                     test       edx, edx
00ac9018  7506                     jne        0xac9020
00ac901a  33c0                     xor        eax, eax
00ac901c  5d                       pop        ebp
00ac901d  c20400                   ret        4
00ac9020  8b4104                   mov        eax, dword ptr [ecx + 4]
00ac9023  56                       push       esi
00ac9024  8b30                     mov        esi, dword ptr [eax]
00ac9026  3bf0                     cmp        esi, eax
00ac9028  7411                     je         0xac903b
00ac902a  8d9b00000000             lea        ebx, [ebx]
00ac9030  395608                   cmp        dword ptr [esi + 8], edx
00ac9033  7419                     je         0xac904e
00ac9035  8b36                     mov        esi, dword ptr [esi]
00ac9037  3bf0                     cmp        esi, eax
00ac9039  75f5                     jne        0xac9030
00ac903b  52                       push       edx
00ac903c  e83b8c1300               call       0xc01c7c
00ac9041  83c404                   add        esp, 4
00ac9044  b801000000               mov        eax, 1
00ac9049  5e                       pop        esi
00ac904a  5d                       pop        ebp
00ac904b  c20400                   ret        4
00ac904e  52                       push       edx
00ac904f  e8288c1300               call       0xc01c7c
00ac9054  83c404                   add        esp, 4
00ac9057  c7460800000000           mov        dword ptr [esi + 8], 0
00ac905e  b801000000               mov        eax, 1
00ac9063  5e                       pop        esi
00ac9064  5d                       pop        ebp
00ac9065  c20400                   ret        4
00ac9068  cc                       int3       
00ac9069  cc                       int3       
00ac906a  cc                       int3       
00ac906b  cc                       int3       
00ac906c  cc                       int3       
00ac906d  cc                       int3       
00ac906e  cc                       int3       
00ac906f  cc                       int3       
00ac9070  56                       push       esi
00ac9071  57                       push       edi
00ac9072  8bf9                     mov        edi, ecx
00ac9074  8b4704                   mov        eax, dword ptr [edi + 4]
00ac9077  8b30                     mov        esi, dword ptr [eax]
00ac9079  3bf0                     cmp        esi, eax
00ac907b  7421                     je         0xac909e
00ac907d  8d4900                   lea        ecx, [ecx]
00ac9080  8b4608                   mov        eax, dword ptr [esi + 8]
00ac9083  85c0                     test       eax, eax
00ac9085  7410                     je         0xac9097
00ac9087  50                       push       eax
00ac9088  e8ef8b1300               call       0xc01c7c
00ac908d  83c404                   add        esp, 4
00ac9090  c7460800000000           mov        dword ptr [esi + 8], 0
00ac9097  8b36                     mov        esi, dword ptr [esi]
00ac9099  3b7704                   cmp        esi, dword ptr [edi + 4]
00ac909c  75e2                     jne        0xac9080
00ac909e  5f                       pop        edi
00ac909f  5e                       pop        esi
00ac90a0  c3                       ret        
00ac90a1  cc                       int3       
00ac90a2  cc                       int3       
00ac90a3  cc                       int3       
00ac90a4  cc                       int3       
00ac90a5  cc                       int3       
00ac90a6  cc                       int3       
00ac90a7  cc                       int3       
00ac90a8  cc                       int3       
00ac90a9  cc                       int3       
00ac90aa  cc                       int3       
00ac90ab  cc                       int3       
00ac90ac  cc                       int3       
00ac90ad  cc                       int3       
00ac90ae  cc                       int3       
00ac90af  cc                       int3       
00ac90b0  55                       push       ebp
00ac90b1  8bec                     mov        ebp, esp
00ac90b3  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00ac90b6  85c9                     test       ecx, ecx
00ac90b8  7504                     jne        0xac90be
00ac90ba  33c0                     xor        eax, eax
00ac90bc  5d                       pop        ebp
00ac90bd  c3                       ret        
00ac90be  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac90c1  c1e004                   shl        eax, 4
00ac90c4  8b906cab0d01             mov        edx, dword ptr [eax + 0x10dab6c]
00ac90ca  85d2                     test       edx, edx
00ac90cc  56                       push       esi
00ac90cd  7444                     je         0xac9113
00ac90cf  8b7510                   mov        esi, dword ptr [ebp + 0x10]
00ac90d2  85f6                     test       esi, esi
00ac90d4  7420                     je         0xac90f6
00ac90d6  8b16                     mov        edx, dword ptr [esi]
00ac90d8  85d2                     test       edx, edx
00ac90da  741a                     je         0xac90f6
00ac90dc  83fa02                   cmp        edx, 2
00ac90df  7510                     jne        0xac90f1
00ac90e1  51                       push       ecx
00ac90e2  8d8860ab0d01             lea        ecx, [eax + 0x10dab60]
00ac90e8  e823ffffff               call       0xac9010
00ac90ed  85c0                     test       eax, eax
00ac90ef  7502                     jne        0xac90f3
00ac90f1  33c0                     xor        eax, eax
00ac90f3  5e                       pop        esi
00ac90f4  5d                       pop        ebp
00ac90f5  c3                       ret        
00ac90f6  51                       push       ecx
00ac90f7  8d8860ab0d01             lea        ecx, [eax + 0x10dab60]
00ac90fd  e80effffff               call       0xac9010
00ac9102  85c0                     test       eax, eax
00ac9104  74eb                     je         0xac90f1
00ac9106  85f6                     test       esi, esi
00ac9108  74e9                     je         0xac90f3
00ac910a  c70602000000             mov        dword ptr [esi], 2
00ac9110  5e                       pop        esi
00ac9111  5d                       pop        ebp
00ac9112  c3                       ret        
00ac9113  51                       push       ecx
00ac9114  e8638b1300               call       0xc01c7c
00ac9119  83c404                   add        esp, 4
00ac911c  f7d8                     neg        eax
00ac911e  1ac0                     sbb        al, al
00ac9120  fec0                     inc        al
00ac9122  0fb6c0                   movzx      eax, al
00ac9125  85c0                     test       eax, eax
00ac9127  74c8                     je         0xac90f1
00ac9129  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00ac912c  85c9                     test       ecx, ecx
00ac912e  74c3                     je         0xac90f3
00ac9130  c70101000000             mov        dword ptr [ecx], 1
00ac9136  5e                       pop        esi
00ac9137  5d                       pop        ebp
00ac9138  c3                       ret        
00ac9139  cc                       int3       
00ac913a  cc                       int3       
00ac913b  cc                       int3       
00ac913c  cc                       int3       
00ac913d  cc                       int3       
00ac913e  cc                       int3       
00ac913f  cc                       int3       
00ac9140  55                       push       ebp
00ac9141  8bec                     mov        ebp, esp
00ac9143  6aff                     push       -1
00ac9145  689833c900               push       0xc93398
00ac914a  64a100000000             mov        eax, dword ptr fs:[0]
00ac9150  50                       push       eax
00ac9151  64892500000000           mov        dword ptr fs:[0], esp
00ac9158  81ec1c080000             sub        esp, 0x81c
00ac915e  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9161  53                       push       ebx
00ac9162  56                       push       esi
00ac9163  57                       push       edi
00ac9164  50                       push       eax
00ac9165  8bf1                     mov        esi, ecx
00ac9167  6800040000               push       0x400
00ac916c  8d8dd8f7ffff             lea        ecx, [ebp - 0x828]
00ac9172  51                       push       ecx
00ac9173  e8188093ff               call       0x401190
00ac9178  8d95d8f7ffff             lea        edx, [ebp - 0x828]
00ac917e  52                       push       edx
00ac917f  e84c110400               call       0xb0a2d0
00ac9184  8d85d8f7ffff             lea        eax, [ebp - 0x828]
00ac918a  33ff                     xor        edi, edi
00ac918c  50                       push       eax
00ac918d  c745f007000000           mov        dword ptr [ebp - 0x10], 7
00ac9194  897dec                   mov        dword ptr [ebp - 0x14], edi
00ac9197  66897ddc                 mov        word ptr [ebp - 0x24], di
00ac919b  e82d6c1300               call       0xbffdcd
00ac91a0  83c408                   add        esp, 8
00ac91a3  50                       push       eax
00ac91a4  8d8dd8f7ffff             lea        ecx, [ebp - 0x828]
00ac91aa  51                       push       ecx
00ac91ab  8d4dd8                   lea        ecx, [ebp - 0x28]
00ac91ae  e8cd9c93ff               call       0x402e80
00ac91b3  8d55d8                   lea        edx, [ebp - 0x28]
00ac91b6  52                       push       edx
00ac91b7  8d4508                   lea        eax, [ebp + 8]
00ac91ba  50                       push       eax
00ac91bb  8bce                     mov        ecx, esi
00ac91bd  897dfc                   mov        dword ptr [ebp - 4], edi
00ac91c0  e87b160000               call       0xaca840
00ac91c5  8b18                     mov        ebx, dword ptr [eax]
00ac91c7  837df008                 cmp        dword ptr [ebp - 0x10], 8
00ac91cb  720c                     jb         0xac91d9
00ac91cd  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
00ac91d0  51                       push       ecx
00ac91d1  e8076e1300               call       0xbfffdd
00ac91d6  83c404                   add        esp, 4
00ac91d9  3b5e04                   cmp        ebx, dword ptr [esi + 4]
00ac91dc  c745f007000000           mov        dword ptr [ebp - 0x10], 7
00ac91e3  897dec                   mov        dword ptr [ebp - 0x14], edi
00ac91e6  66897ddc                 mov        word ptr [ebp - 0x24], di
00ac91ea  7416                     je         0xac9202
00ac91ec  8b4328                   mov        eax, dword ptr [ebx + 0x28]
00ac91ef  5f                       pop        edi
00ac91f0  5e                       pop        esi
00ac91f1  5b                       pop        ebx
00ac91f2  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac91f5  64890d00000000           mov        dword ptr fs:[0], ecx
00ac91fc  8be5                     mov        esp, ebp
00ac91fe  5d                       pop        ebp
00ac91ff  c20400                   ret        4
00ac9202  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac9205  5f                       pop        edi
00ac9206  5e                       pop        esi
00ac9207  83c8ff                   or         eax, 0xffffffff
00ac920a  5b                       pop        ebx
00ac920b  64890d00000000           mov        dword ptr fs:[0], ecx
00ac9212  8be5                     mov        esp, ebp
00ac9214  5d                       pop        ebp
00ac9215  c20400                   ret        4
00ac9218  cc                       int3       
00ac9219  cc                       int3       
00ac921a  cc                       int3       
00ac921b  cc                       int3       
00ac921c  cc                       int3       
00ac921d  cc                       int3       
00ac921e  cc                       int3       
00ac921f  cc                       int3       
00ac9220  55                       push       ebp
00ac9221  8bec                     mov        ebp, esp
00ac9223  6aff                     push       -1
00ac9225  68aa33c900               push       0xc933aa
00ac922a  64a100000000             mov        eax, dword ptr fs:[0]
00ac9230  50                       push       eax
00ac9231  64892500000000           mov        dword ptr fs:[0], esp
00ac9238  81ec1c080000             sub        esp, 0x81c
00ac923e  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9241  56                       push       esi
00ac9242  57                       push       edi
00ac9243  50                       push       eax
00ac9244  8bf1                     mov        esi, ecx
00ac9246  6800040000               push       0x400
00ac924b  8d8dd8f7ffff             lea        ecx, [ebp - 0x828]
00ac9251  51                       push       ecx
00ac9252  e8397f93ff               call       0x401190
00ac9257  8d95d8f7ffff             lea        edx, [ebp - 0x828]
00ac925d  52                       push       edx
00ac925e  e86d100400               call       0xb0a2d0
00ac9263  8d85d8f7ffff             lea        eax, [ebp - 0x828]
00ac9269  33ff                     xor        edi, edi
00ac926b  50                       push       eax
00ac926c  c745f007000000           mov        dword ptr [ebp - 0x10], 7
00ac9273  897dec                   mov        dword ptr [ebp - 0x14], edi
00ac9276  66897ddc                 mov        word ptr [ebp - 0x24], di
00ac927a  e84e6b1300               call       0xbffdcd
00ac927f  83c408                   add        esp, 8
00ac9282  50                       push       eax
00ac9283  8d8dd8f7ffff             lea        ecx, [ebp - 0x828]
00ac9289  51                       push       ecx
00ac928a  8d4dd8                   lea        ecx, [ebp - 0x28]
00ac928d  e8ee9b93ff               call       0x402e80
00ac9292  8d55d8                   lea        edx, [ebp - 0x28]
00ac9295  52                       push       edx
00ac9296  8d4508                   lea        eax, [ebp + 8]
00ac9299  50                       push       eax
00ac929a  8bce                     mov        ecx, esi
00ac929c  897dfc                   mov        dword ptr [ebp - 4], edi
00ac929f  e89c150000               call       0xaca840
00ac92a4  8b38                     mov        edi, dword ptr [eax]
00ac92a6  837df008                 cmp        dword ptr [ebp - 0x10], 8
00ac92aa  720c                     jb         0xac92b8
00ac92ac  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
00ac92af  51                       push       ecx
00ac92b0  e8286d1300               call       0xbfffdd
00ac92b5  83c404                   add        esp, 4
00ac92b8  3b7e04                   cmp        edi, dword ptr [esi + 4]
00ac92bb  7415                     je         0xac92d2
00ac92bd  8d4728                   lea        eax, [edi + 0x28]
00ac92c0  5f                       pop        edi
00ac92c1  5e                       pop        esi
00ac92c2  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac92c5  64890d00000000           mov        dword ptr fs:[0], ecx
00ac92cc  8be5                     mov        esp, ebp
00ac92ce  5d                       pop        ebp
00ac92cf  c20400                   ret        4
00ac92d2  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00ac92d5  5f                       pop        edi
00ac92d6  33c0                     xor        eax, eax
00ac92d8  5e                       pop        esi
00ac92d9  64890d00000000           mov        dword ptr fs:[0], ecx
00ac92e0  8be5                     mov        esp, ebp
00ac92e2  5d                       pop        ebp
00ac92e3  c20400                   ret        4
00ac92e6  cc                       int3       
00ac92e7  cc                       int3       
00ac92e8  cc                       int3       
00ac92e9  cc                       int3       
00ac92ea  cc                       int3       
00ac92eb  cc                       int3       
00ac92ec  cc                       int3       
00ac92ed  cc                       int3       
00ac92ee  cc                       int3       
00ac92ef  cc                       int3       
00ac92f0  55                       push       ebp
00ac92f1  8bec                     mov        ebp, esp
00ac92f3  83ec08                   sub        esp, 8
00ac92f6  53                       push       ebx
00ac92f7  8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
00ac92fa  56                       push       esi
00ac92fb  57                       push       edi
00ac92fc  8bf1                     mov        esi, ecx
00ac92fe  53                       push       ebx
00ac92ff  8975fc                   mov        dword ptr [ebp - 4], esi
00ac9302  c745f800000000           mov        dword ptr [ebp - 8], 0
00ac9309  e8bf6a1300               call       0xbffdcd
00ac930e  83c404                   add        esp, 4
00ac9311  48                       dec        eax
00ac9312  7810                     js         0xac9324
00ac9314  66833c435c               cmp        word ptr [ebx + eax*2], 0x5c
00ac9319  7506                     jne        0xac9321
00ac931b  66c704432f00             mov        word ptr [ebx + eax*2], 0x2f
00ac9321  48                       dec        eax
00ac9322  79f0                     jns        0xac9314
00ac9324  53                       push       ebx
00ac9325  e8a60f0400               call       0xb0a2d0
00ac932a  8b4604                   mov        eax, dword ptr [esi + 4]
00ac932d  8b30                     mov        esi, dword ptr [eax]
00ac932f  83c404                   add        esp, 4
00ac9332  3bf0                     cmp        esi, eax
00ac9334  7419                     je         0xac934f
00ac9336  53                       push       ebx
00ac9337  8d4e28                   lea        ecx, [esi + 0x28]
00ac933a  e8e1feffff               call       0xac9220
00ac933f  8bf8                     mov        edi, eax
00ac9341  85ff                     test       edi, edi
00ac9343  7542                     jne        0xac9387
00ac9345  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac9348  8b36                     mov        esi, dword ptr [esi]
00ac934a  3b7004                   cmp        esi, dword ptr [eax + 4]
00ac934d  75e7                     jne        0xac9336
00ac934f  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9352  33c0                     xor        eax, eax
00ac9354  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac935b  894614                   mov        dword ptr [esi + 0x14], eax
00ac935e  68e0baca00               push       0xcabae0
00ac9363  66894604                 mov        word ptr [esi + 4], ax
00ac9367  e8616a1300               call       0xbffdcd
00ac936c  83c404                   add        esp, 4
00ac936f  50                       push       eax
00ac9370  68e0baca00               push       0xcabae0
00ac9375  8bce                     mov        ecx, esi
00ac9377  e8049b93ff               call       0x402e80
00ac937c  5f                       pop        edi
00ac937d  8bc6                     mov        eax, esi
00ac937f  5e                       pop        esi
00ac9380  5b                       pop        ebx
00ac9381  8be5                     mov        esp, ebp
00ac9383  5d                       pop        ebp
00ac9384  c20c00                   ret        0xc
00ac9387  8b4608                   mov        eax, dword ptr [esi + 8]
00ac938a  85c0                     test       eax, eax
00ac938c  8b0f                     mov        ecx, dword ptr [edi]
00ac938e  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac9391  8d5e08                   lea        ebx, [esi + 8]
00ac9394  890a                     mov        dword ptr [edx], ecx
00ac9396  743a                     je         0xac93d2
00ac9398  8b0f                     mov        ecx, dword ptr [edi]
00ac939a  6a00                     push       0
00ac939c  51                       push       ecx
00ac939d  50                       push       eax
00ac939e  e811931300               call       0xc026b4
00ac93a3  83c40c                   add        esp, 0xc
00ac93a6  33c9                     xor        ecx, ecx
00ac93a8  8d460c                   lea        eax, [esi + 0xc]
00ac93ab  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac93ae  6aff                     push       -1
00ac93b0  894e14                   mov        dword ptr [esi + 0x14], ecx
00ac93b3  51                       push       ecx
00ac93b4  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac93bb  66894e04                 mov        word ptr [esi + 4], cx
00ac93bf  50                       push       eax
00ac93c0  8bce                     mov        ecx, esi
00ac93c2  e8999993ff               call       0x402d60
00ac93c7  5f                       pop        edi
00ac93c8  8bc6                     mov        eax, esi
00ac93ca  5e                       pop        esi
00ac93cb  5b                       pop        ebx
00ac93cc  8be5                     mov        esp, ebp
00ac93ce  5d                       pop        ebp
00ac93cf  c20c00                   ret        0xc
00ac93d2  85db                     test       ebx, ebx
00ac93d4  0f8475ffffff             je         0xac934f
00ac93da  8b4b1c                   mov        ecx, dword ptr [ebx + 0x1c]
00ac93dd  83f908                   cmp        ecx, 8
00ac93e0  8d4304                   lea        eax, [ebx + 4]
00ac93e3  894510                   mov        dword ptr [ebp + 0x10], eax
00ac93e6  7205                     jb         0xac93ed
00ac93e8  8b4004                   mov        eax, dword ptr [eax + 4]
00ac93eb  eb03                     jmp        0xac93f0
00ac93ed  83c004                   add        eax, 4
00ac93f0  68a036e100               push       0xe136a0
00ac93f5  50                       push       eax
00ac93f6  e82e891300               call       0xc01d29
00ac93fb  8bf0                     mov        esi, eax
00ac93fd  83c408                   add        esp, 8
00ac9400  85f6                     test       esi, esi
00ac9402  0f8447ffffff             je         0xac934f
00ac9408  8b17                     mov        edx, dword ptr [edi]
00ac940a  6a00                     push       0
00ac940c  52                       push       edx
00ac940d  56                       push       esi
00ac940e  e8a1921300               call       0xc026b4
00ac9413  8933                     mov        dword ptr [ebx], esi
00ac9415  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9418  83c40c                   add        esp, 0xc
00ac941b  33c0                     xor        eax, eax
00ac941d  6aff                     push       -1
00ac941f  894614                   mov        dword ptr [esi + 0x14], eax
00ac9422  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9429  50                       push       eax
00ac942a  66894604                 mov        word ptr [esi + 4], ax
00ac942e  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00ac9431  50                       push       eax
00ac9432  8bce                     mov        ecx, esi
00ac9434  e8279993ff               call       0x402d60
00ac9439  5f                       pop        edi
00ac943a  8bc6                     mov        eax, esi
00ac943c  5e                       pop        esi
00ac943d  5b                       pop        ebx
00ac943e  8be5                     mov        esp, ebp
00ac9440  5d                       pop        ebp
00ac9441  c20c00                   ret        0xc
00ac9444  cc                       int3       
00ac9445  cc                       int3       
00ac9446  cc                       int3       
00ac9447  cc                       int3       
00ac9448  cc                       int3       
00ac9449  cc                       int3       
00ac944a  cc                       int3       
00ac944b  cc                       int3       
00ac944c  cc                       int3       
00ac944d  cc                       int3       
00ac944e  cc                       int3       
00ac944f  cc                       int3       
00ac9450  55                       push       ebp
00ac9451  8bec                     mov        ebp, esp
00ac9453  83ec08                   sub        esp, 8
00ac9456  53                       push       ebx
00ac9457  8b5d14                   mov        ebx, dword ptr [ebp + 0x14]
00ac945a  56                       push       esi
00ac945b  57                       push       edi
00ac945c  8bf1                     mov        esi, ecx
00ac945e  53                       push       ebx
00ac945f  8975fc                   mov        dword ptr [ebp - 4], esi
00ac9462  c745f800000000           mov        dword ptr [ebp - 8], 0
00ac9469  e85f691300               call       0xbffdcd
00ac946e  83c404                   add        esp, 4
00ac9471  48                       dec        eax
00ac9472  7810                     js         0xac9484
00ac9474  66833c435c               cmp        word ptr [ebx + eax*2], 0x5c
00ac9479  7506                     jne        0xac9481
00ac947b  66c704432f00             mov        word ptr [ebx + eax*2], 0x2f
00ac9481  48                       dec        eax
00ac9482  79f0                     jns        0xac9474
00ac9484  53                       push       ebx
00ac9485  e8460e0400               call       0xb0a2d0
00ac948a  8b4604                   mov        eax, dword ptr [esi + 4]
00ac948d  8b30                     mov        esi, dword ptr [eax]
00ac948f  83c404                   add        esp, 4
00ac9492  3bf0                     cmp        esi, eax
00ac9494  7419                     je         0xac94af
00ac9496  53                       push       ebx
00ac9497  8d4e28                   lea        ecx, [esi + 0x28]
00ac949a  e881fdffff               call       0xac9220
00ac949f  8bf8                     mov        edi, eax
00ac94a1  85ff                     test       edi, edi
00ac94a3  7542                     jne        0xac94e7
00ac94a5  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac94a8  8b36                     mov        esi, dword ptr [esi]
00ac94aa  3b7004                   cmp        esi, dword ptr [eax + 4]
00ac94ad  75e7                     jne        0xac9496
00ac94af  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac94b2  33c0                     xor        eax, eax
00ac94b4  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac94bb  894614                   mov        dword ptr [esi + 0x14], eax
00ac94be  68e0baca00               push       0xcabae0
00ac94c3  66894604                 mov        word ptr [esi + 4], ax
00ac94c7  e801691300               call       0xbffdcd
00ac94cc  83c404                   add        esp, 4
00ac94cf  50                       push       eax
00ac94d0  68e0baca00               push       0xcabae0
00ac94d5  8bce                     mov        ecx, esi
00ac94d7  e8a49993ff               call       0x402e80
00ac94dc  5f                       pop        edi
00ac94dd  8bc6                     mov        eax, esi
00ac94df  5e                       pop        esi
00ac94e0  5b                       pop        ebx
00ac94e1  8be5                     mov        esp, ebp
00ac94e3  5d                       pop        ebp
00ac94e4  c21000                   ret        0x10
00ac94e7  8b0f                     mov        ecx, dword ptr [edi]
00ac94e9  8b4608                   mov        eax, dword ptr [esi + 8]
00ac94ec  85c0                     test       eax, eax
00ac94ee  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac94f1  8d5e08                   lea        ebx, [esi + 8]
00ac94f4  890a                     mov        dword ptr [edx], ecx
00ac94f6  8b4f04                   mov        ecx, dword ptr [edi + 4]
00ac94f9  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00ac94fc  890a                     mov        dword ptr [edx], ecx
00ac94fe  743a                     je         0xac953a