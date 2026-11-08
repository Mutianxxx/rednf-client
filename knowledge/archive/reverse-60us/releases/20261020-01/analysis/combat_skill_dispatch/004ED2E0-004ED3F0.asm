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
004ed3ed  e8                       .byte      0xe8
004ed3ee  9e                       sahf       
004ed3ef  24                       .byte      0x24