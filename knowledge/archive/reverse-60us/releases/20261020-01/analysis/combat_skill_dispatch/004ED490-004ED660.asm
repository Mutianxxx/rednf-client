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
004ed4d0  03fa                     add        edi, edx
004ed4d2  84c0                     test       al, al
004ed4d4  7849                     js         0x4ed51f
004ed4d6  8b5604                   mov        edx, dword ptr [esi + 4]
004ed4d9  85d2                     test       edx, edx
004ed4db  897d08                   mov        dword ptr [ebp + 8], edi
004ed4de  7504                     jne        0x4ed4e4
004ed4e0  33c9                     xor        ecx, ecx
004ed4e2  eb08                     jmp        0x4ed4ec
004ed4e4  8b4e08                   mov        ecx, dword ptr [esi + 8]
004ed4e7  2bca                     sub        ecx, edx
004ed4e9  c1f902                   sar        ecx, 2
004ed4ec  85d2                     test       edx, edx
004ed4ee  7419                     je         0x4ed509
004ed4f0  8b460c                   mov        eax, dword ptr [esi + 0xc]
004ed4f3  2bc2                     sub        eax, edx
004ed4f5  c1f802                   sar        eax, 2
004ed4f8  3bc8                     cmp        ecx, eax
004ed4fa  730d                     jae        0x4ed509
004ed4fc  8b4608                   mov        eax, dword ptr [esi + 8]
004ed4ff  8938                     mov        dword ptr [eax], edi
004ed501  83c004                   add        eax, 4
004ed504  894608                   mov        dword ptr [esi + 8], eax
004ed507  eb11                     jmp        0x4ed51a
004ed509  8b4608                   mov        eax, dword ptr [esi + 8]
004ed50c  8d4d08                   lea        ecx, [ebp + 8]
004ed50f  51                       push       ecx
004ed510  6a01                     push       1
004ed512  50                       push       eax
004ed513  8bce                     mov        ecx, esi
004ed515  e8468af1ff               call       0x405f60
004ed51a  8b4df8                   mov        ecx, dword ptr [ebp - 8]
004ed51d  33ff                     xor        edi, edi
004ed51f  8b45fc                   mov        eax, dword ptr [ebp - 4]
004ed522  43                       inc        ebx
004ed523  3bd8                     cmp        ebx, eax
004ed525  7c99                     jl         0x4ed4c0
004ed527  5e                       pop        esi
004ed528  5f                       pop        edi
004ed529  5b                       pop        ebx
004ed52a  8be5                     mov        esp, ebp
004ed52c  5d                       pop        ebp
004ed52d  c20400                   ret        4
004ed530  55                       push       ebp
004ed531  8bec                     mov        ebp, esp
004ed533  81c1d0040000             add        ecx, 0x4d0
004ed539  56                       push       esi
004ed53a  8b7104                   mov        esi, dword ptr [ecx + 4]
004ed53d  85f6                     test       esi, esi
004ed53f  7504                     jne        0x4ed545
004ed541  33d2                     xor        edx, edx
004ed543  eb08                     jmp        0x4ed54d
004ed545  8b5108                   mov        edx, dword ptr [ecx + 8]
004ed548  2bd6                     sub        edx, esi
004ed54a  c1fa02                   sar        edx, 2
004ed54d  85f6                     test       esi, esi
004ed54f  741f                     je         0x4ed570
004ed551  8b410c                   mov        eax, dword ptr [ecx + 0xc]
004ed554  2bc6                     sub        eax, esi
004ed556  c1f802                   sar        eax, 2
004ed559  3bd0                     cmp        edx, eax
004ed55b  7313                     jae        0x4ed570
004ed55d  8b4108                   mov        eax, dword ptr [ecx + 8]
004ed560  8b5508                   mov        edx, dword ptr [ebp + 8]
004ed563  8910                     mov        dword ptr [eax], edx
004ed565  83c004                   add        eax, 4
004ed568  894108                   mov        dword ptr [ecx + 8], eax
004ed56b  5e                       pop        esi
004ed56c  5d                       pop        ebp
004ed56d  c20400                   ret        4
004ed570  8b4108                   mov        eax, dword ptr [ecx + 8]
004ed573  8d5508                   lea        edx, [ebp + 8]
004ed576  52                       push       edx
004ed577  6a01                     push       1
004ed579  50                       push       eax
004ed57a  e8f1810100               call       0x505770
004ed57f  5e                       pop        esi
004ed580  5d                       pop        ebp
004ed581  c20400                   ret        4
004ed584  cc                       int3       
004ed585  cc                       int3       
004ed586  cc                       int3       
004ed587  cc                       int3       
004ed588  cc                       int3       
004ed589  cc                       int3       
004ed58a  cc                       int3       
004ed58b  cc                       int3       
004ed58c  cc                       int3       
004ed58d  cc                       int3       
004ed58e  cc                       int3       
004ed58f  cc                       int3       
004ed590  55                       push       ebp
004ed591  8bec                     mov        ebp, esp
004ed593  83ec08                   sub        esp, 8
004ed596  53                       push       ebx
004ed597  56                       push       esi
004ed598  57                       push       edi
004ed599  8bd9                     mov        ebx, ecx
004ed59b  33ff                     xor        edi, edi
004ed59d  8b8b00010000             mov        ecx, dword ptr [ebx + 0x100]
004ed5a3  8b9190000000             mov        edx, dword ptr [ecx + 0x90]
004ed5a9  85d2                     test       edx, edx
004ed5ab  897dfc                   mov        dword ptr [ebp - 4], edi
004ed5ae  7504                     jne        0x4ed5b4
004ed5b0  33c0                     xor        eax, eax
004ed5b2  eb0b                     jmp        0x4ed5bf
004ed5b4  8b8194000000             mov        eax, dword ptr [ecx + 0x94]
004ed5ba  2bc2                     sub        eax, edx
004ed5bc  c1f802                   sar        eax, 2
004ed5bf  3bf8                     cmp        edi, eax
004ed5c1  0f8d0a010000             jge        0x4ed6d1
004ed5c7  8b9190000000             mov        edx, dword ptr [ecx + 0x90]
004ed5cd  85d2                     test       edx, edx
004ed5cf  7419                     je         0x4ed5ea
004ed5d1  8b8194000000             mov        eax, dword ptr [ecx + 0x94]
004ed5d7  2bc2                     sub        eax, edx
004ed5d9  c1f802                   sar        eax, 2
004ed5dc  3bf8                     cmp        edi, eax
004ed5de  730a                     jae        0x4ed5ea
004ed5e0  8bc2                     mov        eax, edx
004ed5e2  8b0cb8                   mov        ecx, dword ptr [eax + edi*4]
004ed5e5  8d04b8                   lea        eax, [eax + edi*4]
004ed5e8  eb02                     jmp        0x4ed5ec
004ed5ea  33c9                     xor        ecx, ecx
004ed5ec  8b11                     mov        edx, dword ptr [ecx]
004ed5ee  6a11                     push       0x11
004ed5f0  ff522c                   call       dword ptr [edx + 0x2c]
004ed5f3  84c0                     test       al, al
004ed5f5  0f84c5000000             je         0x4ed6c0
004ed5fb  8b8b00010000             mov        ecx, dword ptr [ebx + 0x100]
004ed601  8b9190000000             mov        edx, dword ptr [ecx + 0x90]
004ed607  85d2                     test       edx, edx
004ed609  7419                     je         0x4ed624
004ed60b  8b8194000000             mov        eax, dword ptr [ecx + 0x94]
004ed611  2bc2                     sub        eax, edx
004ed613  c1f802                   sar        eax, 2
004ed616  3bf8                     cmp        edi, eax
004ed618  730a                     jae        0x4ed624
004ed61a  8bc2                     mov        eax, edx
004ed61c  8b34b8                   mov        esi, dword ptr [eax + edi*4]
004ed61f  8d04b8                   lea        eax, [eax + edi*4]
004ed622  eb02                     jmp        0x4ed626
004ed624  33f6                     xor        esi, esi
004ed626  56                       push       esi
004ed627  8bcb                     mov        ecx, ebx
004ed629  8975f8                   mov        dword ptr [ebp - 8], esi
004ed62c  e89fb5ffff               call       0x4e8bd0
004ed631  84c0                     test       al, al
004ed633  0f8487000000             je         0x4ed6c0
004ed639  bfc8000000               mov        edi, 0xc8
004ed63e  8bff                     mov        edi, edi
004ed640  8b16                     mov        edx, dword ptr [esi]
004ed642  8bce                     mov        ecx, esi
004ed644  ff92c4010000             call       dword ptr [edx + 0x1c4]
004ed64a  3bf8                     cmp        edi, eax
004ed64c  746f                     je         0x4ed6bd
004ed64e  47                       inc        edi
004ed64f  81ffcd000000             cmp        edi, 0xcd
004ed655  7ce9                     jl         0x4ed640
004ed657  8b06                     mov        eax, dword ptr [esi]
004ed659  8bce                     mov        ecx, esi
004ed65b  ff                       .byte      0xff
004ed65c  90                       nop        
004ed65d  f4                       hlt        
004ed65e  0400                     add        al, 0