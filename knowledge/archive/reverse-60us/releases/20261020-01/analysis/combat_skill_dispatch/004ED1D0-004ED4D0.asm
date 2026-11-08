004ed1d0  55                       push       ebp
004ed1d1  8bec                     mov        ebp, esp
004ed1d3  56                       push       esi
004ed1d4  8bf1                     mov        esi, ecx
004ed1d6  8a869c040000             mov        al, byte ptr [esi + 0x49c]
004ed1dc  84c0                     test       al, al
004ed1de  0f84ee000000             je         0x4ed2d2
004ed1e4  e8a7eefaff               call       0x49c090
004ed1e9  84c0                     test       al, al
004ed1eb  750b                     jne        0x4ed1f8
004ed1ed  8a4514                   mov        al, byte ptr [ebp + 0x14]
004ed1f0  84c0                     test       al, al
004ed1f2  0f84da000000             je         0x4ed2d2
004ed1f8  8b06                     mov        eax, dword ptr [esi]
004ed1fa  57                       push       edi
004ed1fb  6881000000               push       0x81
004ed200  8bce                     mov        ecx, esi
004ed202  ff502c                   call       dword ptr [eax + 0x2c]
004ed205  84c0                     test       al, al
004ed207  7461                     je         0x4ed26a
004ed209  8b4518                   mov        eax, dword ptr [ebp + 0x18]
004ed20c  85c0                     test       eax, eax
004ed20e  745a                     je         0x4ed26a
004ed210  53                       push       ebx
004ed211  b960070001               mov        ecx, 0x1000760
004ed216  e8055bf1ff               call       0x402d20
004ed21b  8b16                     mov        edx, dword ptr [esi]
004ed21d  8bce                     mov        ecx, esi
004ed21f  ff9230020000             call       dword ptr [edx + 0x230]
004ed225  8d8e08020000             lea        ecx, [esi + 0x208]
004ed22b  8bf8                     mov        edi, eax
004ed22d  e8be5e5600               call       0xa530f0
004ed232  8b16                     mov        edx, dword ptr [esi]
004ed234  8bd8                     mov        ebx, eax
004ed236  8b4508                   mov        eax, dword ptr [ebp + 8]
004ed239  50                       push       eax
004ed23a  57                       push       edi
004ed23b  8bce                     mov        ecx, esi
004ed23d  ff5240                   call       dword ptr [edx + 0x40]
004ed240  50                       push       eax
004ed241  8b4518                   mov        eax, dword ptr [ebp + 0x18]
004ed244  53                       push       ebx
004ed245  50                       push       eax
004ed246  68404fcd00               push       0xcd4f40
004ed24b  6a00                     push       0
004ed24d  e84e585600               call       0xa52aa0
004ed252  8bf8                     mov        edi, eax
004ed254  57                       push       edi
004ed255  e8732b7100               call       0xbffdcd
004ed25a  83c420                   add        esp, 0x20
004ed25d  50                       push       eax
004ed25e  57                       push       edi
004ed25f  b960070001               mov        ecx, 0x1000760
004ed264  e8175cf1ff               call       0x402e80
004ed269  5b                       pop        ebx
004ed26a  8b16                     mov        edx, dword ptr [esi]
004ed26c  6811020000               push       0x211
004ed271  8bce                     mov        ecx, esi
004ed273  ff522c                   call       dword ptr [edx + 0x2c]
004ed276  84c0                     test       al, al
004ed278  7409                     je         0x4ed283
004ed27a  83bea004000005           cmp        dword ptr [esi + 0x4a0], 5
004ed281  744e                     je         0x4ed2d1
004ed283  83bea0040000ff           cmp        dword ptr [esi + 0x4a0], -1
004ed28a  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
004ed28d  7408                     je         0x4ed297
004ed28f  39beb4040000             cmp        dword ptr [esi + 0x4b4], edi
004ed295  7f3a                     jg         0x4ed2d1
004ed297  8b4508                   mov        eax, dword ptr [ebp + 8]
004ed29a  8986a0040000             mov        dword ptr [esi + 0x4a0], eax
004ed2a0  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004ed2a3  85c0                     test       eax, eax
004ed2a5  c6869d04000000           mov        byte ptr [esi + 0x49d], 0
004ed2ac  8d8ea4040000             lea        ecx, [esi + 0x4a4]
004ed2b2  7412                     je         0x4ed2c6
004ed2b4  50                       push       eax
004ed2b5  e886a60100               call       0x507940
004ed2ba  89beb4040000             mov        dword ptr [esi + 0x4b4], edi
004ed2c0  5f                       pop        edi
004ed2c1  5e                       pop        esi
004ed2c2  5d                       pop        ebp
004ed2c3  c21400                   ret        0x14
004ed2c6  e8857a1500               call       0x644d50
004ed2cb  89beb4040000             mov        dword ptr [esi + 0x4b4], edi
004ed2d1  5f                       pop        edi
004ed2d2  5e                       pop        esi
004ed2d3  5d                       pop        ebp
004ed2d4  c21400                   ret        0x14
004ed2d7  cc                       int3       
004ed2d8  cc                       int3       
004ed2d9  cc                       int3       
004ed2da  cc                       int3       
004ed2db  cc                       int3       
004ed2dc  cc                       int3       
004ed2dd  cc                       int3       
004ed2de  cc                       int3       
004ed2df  cc                       int3       
004ed2e0  55                       push       ebp
004ed2e1  8bec                     mov        ebp, esp
004ed2e3  51                       push       ecx
004ed2e4  8b4508                   mov        eax, dword ptr [ebp + 8]
004ed2e7  3d80000000               cmp        eax, 0x80
004ed2ec  56                       push       esi
004ed2ed  8bf1                     mov        esi, ecx
004ed2ef  734b                     jae        0x4ed33c
004ed2f1  8b5604                   mov        edx, dword ptr [esi + 4]
004ed2f4  85d2                     test       edx, edx
004ed2f6  57                       push       edi
004ed2f7  88450b                   mov        byte ptr [ebp + 0xb], al
004ed2fa  7504                     jne        0x4ed300
004ed2fc  33ff                     xor        edi, edi
004ed2fe  eb05                     jmp        0x4ed305
004ed300  8b7e08                   mov        edi, dword ptr [esi + 8]
004ed303  2bfa                     sub        edi, edx
004ed305  85d2                     test       edx, edx
004ed307  741a                     je         0x4ed323
004ed309  8b4e0c                   mov        ecx, dword ptr [esi + 0xc]
004ed30c  2bca                     sub        ecx, edx
004ed30e  3bf9                     cmp        edi, ecx
004ed310  7311                     jae        0x4ed323
004ed312  8b4e08                   mov        ecx, dword ptr [esi + 8]
004ed315  8801                     mov        byte ptr [ecx], al
004ed317  41                       inc        ecx
004ed318  5f                       pop        edi
004ed319  894e08                   mov        dword ptr [esi + 8], ecx
004ed31c  5e                       pop        esi
004ed31d  8be5                     mov        esp, ebp
004ed31f  5d                       pop        ebp
004ed320  c20400                   ret        4
004ed323  8b4608                   mov        eax, dword ptr [esi + 8]
004ed326  8d4d0b                   lea        ecx, [ebp + 0xb]
004ed329  51                       push       ecx
004ed32a  6a01                     push       1
004ed32c  50                       push       eax
004ed32d  8bce                     mov        ecx, esi
004ed32f  e8ec1bf3ff               call       0x41ef20
004ed334  5f                       pop        edi
004ed335  5e                       pop        esi
004ed336  8be5                     mov        esp, ebp
004ed338  5d                       pop        ebp
004ed339  c20400                   ret        4
004ed33c  3d00400000               cmp        eax, 0x4000
004ed341  732d                     jae        0x4ed370
004ed343  8ad0                     mov        dl, al
004ed345  c1e807                   shr        eax, 7
004ed348  0c80                     or         al, 0x80
004ed34a  88450b                   mov        byte ptr [ebp + 0xb], al
004ed34d  8d450b                   lea        eax, [ebp + 0xb]
004ed350  80e27f                   and        dl, 0x7f
004ed353  50                       push       eax
004ed354  8bce                     mov        ecx, esi
004ed356  8855ff                   mov        byte ptr [ebp - 1], dl
004ed359  e83225f3ff               call       0x41f890
004ed35e  8d4dff                   lea        ecx, [ebp - 1]
004ed361  51                       push       ecx
004ed362  8bce                     mov        ecx, esi
004ed364  e82725f3ff               call       0x41f890
004ed369  5e                       pop        esi
004ed36a  8be5                     mov        esp, ebp
004ed36c  5d                       pop        ebp
004ed36d  c20400                   ret        4
004ed370  3d00002000               cmp        eax, 0x200000
004ed375  7343                     jae        0x4ed3ba
004ed377  8ad0                     mov        dl, al
004ed379  8bc8                     mov        ecx, eax
004ed37b  80e27f                   and        dl, 0x7f
004ed37e  c1e907                   shr        ecx, 7
004ed381  80c980                   or         cl, 0x80
004ed384  8855fe                   mov        byte ptr [ebp - 2], dl
004ed387  c1e80e                   shr        eax, 0xe
004ed38a  8d550b                   lea        edx, [ebp + 0xb]
004ed38d  884dff                   mov        byte ptr [ebp - 1], cl
004ed390  0c80                     or         al, 0x80
004ed392  52                       push       edx
004ed393  8bce                     mov        ecx, esi
004ed395  88450b                   mov        byte ptr [ebp + 0xb], al
004ed398  e8f324f3ff               call       0x41f890
004ed39d  8d45ff                   lea        eax, [ebp - 1]
004ed3a0  50                       push       eax
004ed3a1  8bce                     mov        ecx, esi
004ed3a3  e8e824f3ff               call       0x41f890
004ed3a8  8d4dfe                   lea        ecx, [ebp - 2]
004ed3ab  51                       push       ecx
004ed3ac  8bce                     mov        ecx, esi
004ed3ae  e8dd24f3ff               call       0x41f890
004ed3b3  5e                       pop        esi
004ed3b4  8be5                     mov        esp, ebp
004ed3b6  5d                       pop        ebp
004ed3b7  c20400                   ret        4
004ed3ba  3d00000010               cmp        eax, 0x10000000
004ed3bf  7359                     jae        0x4ed41a
004ed3c1  8ad0                     mov        dl, al
004ed3c3  80e27f                   and        dl, 0x7f
004ed3c6  8855fd                   mov        byte ptr [ebp - 3], dl
004ed3c9  8bc8                     mov        ecx, eax
004ed3cb  8bd0                     mov        edx, eax
004ed3cd  c1e815                   shr        eax, 0x15
004ed3d0  c1e907                   shr        ecx, 7
004ed3d3  0c80                     or         al, 0x80
004ed3d5  80c980                   or         cl, 0x80
004ed3d8  c1ea0e                   shr        edx, 0xe
004ed3db  88450b                   mov        byte ptr [ebp + 0xb], al
004ed3de  8d450b                   lea        eax, [ebp + 0xb]
004ed3e1  884dff                   mov        byte ptr [ebp - 1], cl
004ed3e4  80ca80                   or         dl, 0x80
004ed3e7  50                       push       eax
004ed3e8  8bce                     mov        ecx, esi
004ed3ea  8855fe                   mov        byte ptr [ebp - 2], dl
004ed3ed  e89e24f3ff               call       0x41f890
004ed3f2  8d4dfe                   lea        ecx, [ebp - 2]
004ed3f5  51                       push       ecx
004ed3f6  8bce                     mov        ecx, esi
004ed3f8  e89324f3ff               call       0x41f890
004ed3fd  8d55ff                   lea        edx, [ebp - 1]
004ed400  52                       push       edx
004ed401  8bce                     mov        ecx, esi
004ed403  e88824f3ff               call       0x41f890
004ed408  8d45fd                   lea        eax, [ebp - 3]
004ed40b  50                       push       eax
004ed40c  8bce                     mov        ecx, esi
004ed40e  e87d24f3ff               call       0x41f890
004ed413  5e                       pop        esi
004ed414  8be5                     mov        esp, ebp
004ed416  5d                       pop        ebp
004ed417  c20400                   ret        4
004ed41a  8bd0                     mov        edx, eax
004ed41c  8ac8                     mov        cl, al
004ed41e  c1ea07                   shr        edx, 7
004ed421  80e17f                   and        cl, 0x7f
004ed424  80ca80                   or         dl, 0x80
004ed427  884dfc                   mov        byte ptr [ebp - 4], cl
004ed42a  8bc8                     mov        ecx, eax
004ed42c  8855ff                   mov        byte ptr [ebp - 1], dl
004ed42f  8bd0                     mov        edx, eax
004ed431  c1e81c                   shr        eax, 0x1c
004ed434  240f                     and        al, 0xf
004ed436  c1e90e                   shr        ecx, 0xe
004ed439  0c80                     or         al, 0x80
004ed43b  80c980                   or         cl, 0x80
004ed43e  c1ea15                   shr        edx, 0x15
004ed441  88450b                   mov        byte ptr [ebp + 0xb], al
004ed444  8d450b                   lea        eax, [ebp + 0xb]
004ed447  884dfe                   mov        byte ptr [ebp - 2], cl
004ed44a  80ca80                   or         dl, 0x80
004ed44d  50                       push       eax
004ed44e  8bce                     mov        ecx, esi
004ed450  8855fd                   mov        byte ptr [ebp - 3], dl
004ed453  e83824f3ff               call       0x41f890
004ed458  8d4dfd                   lea        ecx, [ebp - 3]
004ed45b  51                       push       ecx
004ed45c  8bce                     mov        ecx, esi
004ed45e  e82d24f3ff               call       0x41f890
004ed463  8d55fe                   lea        edx, [ebp - 2]
004ed466  52                       push       edx
004ed467  8bce                     mov        ecx, esi
004ed469  e82224f3ff               call       0x41f890
004ed46e  8d45ff                   lea        eax, [ebp - 1]
004ed471  50                       push       eax
004ed472  8bce                     mov        ecx, esi
004ed474  e81724f3ff               call       0x41f890
004ed479  8d4dfc                   lea        ecx, [ebp - 4]
004ed47c  51                       push       ecx
004ed47d  8bce                     mov        ecx, esi
004ed47f  e80c24f3ff               call       0x41f890
004ed484  5e                       pop        esi
004ed485  8be5                     mov        esp, ebp
004ed487  5d                       pop        ebp
004ed488  c20400                   ret        4
004ed48b  cc                       int3       
004ed48c  cc                       int3       
004ed48d  cc                       int3       
004ed48e  cc                       int3       
004ed48f  cc                       int3       
004ed490  55                       push       ebp
004ed491  8bec                     mov        ebp, esp
004ed493  83ec08                   sub        esp, 8
004ed496  8b4104                   mov        eax, dword ptr [ecx + 4]
004ed499  53                       push       ebx
004ed49a  57                       push       edi
004ed49b  33db                     xor        ebx, ebx
004ed49d  33ff                     xor        edi, edi
004ed49f  3bc3                     cmp        eax, ebx
004ed4a1  894df8                   mov        dword ptr [ebp - 8], ecx
004ed4a4  7505                     jne        0x4ed4ab
004ed4a6  895dfc                   mov        dword ptr [ebp - 4], ebx
004ed4a9  eb08                     jmp        0x4ed4b3
004ed4ab  8b5108                   mov        edx, dword ptr [ecx + 8]
004ed4ae  2bd0                     sub        edx, eax
004ed4b0  8955fc                   mov        dword ptr [ebp - 4], edx
004ed4b3  395dfc                   cmp        dword ptr [ebp - 4], ebx
004ed4b6  7e70                     jle        0x4ed528
004ed4b8  56                       push       esi
004ed4b9  8b7508                   mov        esi, dword ptr [ebp + 8]
004ed4bc  8d642400                 lea        esp, [esp]
004ed4c0  8b4104                   mov        eax, dword ptr [ecx + 4]
004ed4c3  8a0403                   mov        al, byte ptr [ebx + eax]
004ed4c6  33d2                     xor        edx, edx
004ed4c8  8ad0                     mov        dl, al
004ed4ca  c1e707                   shl        edi, 7
004ed4cd  83e27f                   and        edx, 0x7f