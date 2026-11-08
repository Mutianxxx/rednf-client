0049b7b0  55                       push       ebp
0049b7b1  8bec                     mov        ebp, esp
0049b7b3  83ec1c                   sub        esp, 0x1c
0049b7b6  53                       push       ebx
0049b7b7  56                       push       esi
0049b7b8  8b750c                   mov        esi, dword ptr [ebp + 0xc]
0049b7bb  85f6                     test       esi, esi
0049b7bd  8bd9                     mov        ebx, ecx
0049b7bf  0f8412010000             je         0x49b8d7
0049b7c5  8b83e0000000             mov        eax, dword ptr [ebx + 0xe0]
0049b7cb  50                       push       eax
0049b7cc  8d4e48                   lea        ecx, [esi + 0x48]
0049b7cf  e80cb96600               call       0xb070e0
0049b7d4  8b4514                   mov        eax, dword ptr [ebp + 0x14]
0049b7d7  8b5510                   mov        edx, dword ptr [ebp + 0x10]
0049b7da  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0049b7dd  8945f0                   mov        dword ptr [ebp - 0x10], eax
0049b7e0  8a451c                   mov        al, byte ptr [ebp + 0x1c]
0049b7e3  8845f5                   mov        byte ptr [ebp - 0xb], al
0049b7e6  8a452c                   mov        al, byte ptr [ebp + 0x2c]
0049b7e9  8955ec                   mov        dword ptr [ebp - 0x14], edx
0049b7ec  8a5518                   mov        dl, byte ptr [ebp + 0x18]
0049b7ef  8845f7                   mov        byte ptr [ebp - 9], al
0049b7f2  8b830c010000             mov        eax, dword ptr [ebx + 0x10c]
0049b7f8  8975e8                   mov        dword ptr [ebp - 0x18], esi
0049b7fb  8b30                     mov        esi, dword ptr [eax]
0049b7fd  3bf0                     cmp        esi, eax
0049b7ff  8855f4                   mov        byte ptr [ebp - 0xc], dl
0049b802  8a5528                   mov        dl, byte ptr [ebp + 0x28]
0049b805  894de4                   mov        dword ptr [ebp - 0x1c], ecx
0049b808  8855f6                   mov        byte ptr [ebp - 0xa], dl
0049b80b  7412                     je         0x49b81f
0049b80d  8d4900                   lea        ecx, [ecx]
0049b810  394e08                   cmp        dword ptr [esi + 8], ecx
0049b813  7f0a                     jg         0x49b81f
0049b815  8b36                     mov        esi, dword ptr [esi]
0049b817  3bb30c010000             cmp        esi, dword ptr [ebx + 0x10c]
0049b81d  75f1                     jne        0x49b810
0049b81f  8b4604                   mov        eax, dword ptr [esi + 4]
0049b822  57                       push       edi
0049b823  8d55e4                   lea        edx, [ebp - 0x1c]
0049b826  52                       push       edx
0049b827  50                       push       eax
0049b828  8d8b08010000             lea        ecx, [ebx + 0x108]
0049b82e  56                       push       esi
0049b82f  e80c745900               call       0xa32c40
0049b834  6a01                     push       1
0049b836  8d8b08010000             lea        ecx, [ebx + 0x108]
0049b83c  8bf8                     mov        edi, eax
0049b83e  e81d100000               call       0x49c860
0049b843  897e04                   mov        dword ptr [esi + 4], edi
0049b846  8b4f04                   mov        ecx, dword ptr [edi + 4]
0049b849  8939                     mov        dword ptr [ecx], edi
0049b84b  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
0049b84e  8bcf                     mov        ecx, edi
0049b850  e80bbb5800               call       0xa27360
0049b855  8bcf                     mov        ecx, edi
0049b857  e804c75800               call       0xa27f60
0049b85c  8a4520                   mov        al, byte ptr [ebp + 0x20]
0049b85f  84c0                     test       al, al
0049b861  7459                     je         0x49b8bc
0049b863  8bb330010000             mov        esi, dword ptr [ebx + 0x130]
0049b869  85f6                     test       esi, esi
0049b86b  8d8b2c010000             lea        ecx, [ebx + 0x12c]
0049b871  7504                     jne        0x49b877
0049b873  33d2                     xor        edx, edx
0049b875  eb08                     jmp        0x49b87f
0049b877  8b5108                   mov        edx, dword ptr [ecx + 8]
0049b87a  2bd6                     sub        edx, esi
0049b87c  c1fa02                   sar        edx, 2
0049b87f  85f6                     test       esi, esi
0049b881  7419                     je         0x49b89c
0049b883  8b410c                   mov        eax, dword ptr [ecx + 0xc]
0049b886  2bc6                     sub        eax, esi
0049b888  c1f802                   sar        eax, 2
0049b88b  3bd0                     cmp        edx, eax
0049b88d  730d                     jae        0x49b89c
0049b88f  8b4108                   mov        eax, dword ptr [ecx + 8]
0049b892  8938                     mov        dword ptr [eax], edi
0049b894  83c004                   add        eax, 4
0049b897  894108                   mov        dword ptr [ecx + 8], eax
0049b89a  eb0f                     jmp        0x49b8ab
0049b89c  8b4108                   mov        eax, dword ptr [ecx + 8]
0049b89f  8d550c                   lea        edx, [ebp + 0xc]
0049b8a2  52                       push       edx
0049b8a3  6a01                     push       1
0049b8a5  50                       push       eax
0049b8a6  e8b5c8f6ff               call       0x408160
0049b8ab  8a8385010000             mov        al, byte ptr [ebx + 0x185]
0049b8b1  84c0                     test       al, al
0049b8b3  7407                     je         0x49b8bc
0049b8b5  c6838601000001           mov        byte ptr [ebx + 0x186], 1
0049b8bc  8a4524                   mov        al, byte ptr [ebp + 0x24]
0049b8bf  84c0                     test       al, al
0049b8c1  5f                       pop        edi
0049b8c2  7413                     je         0x49b8d7
0049b8c4  8d450c                   lea        eax, [ebp + 0xc]
0049b8c7  50                       push       eax
0049b8c8  8d4df8                   lea        ecx, [ebp - 8]
0049b8cb  51                       push       ecx
0049b8cc  8d8b3c010000             lea        ecx, [ebx + 0x13c]
0049b8d2  e8d9100000               call       0x49c9b0
0049b8d7  5e                       pop        esi
0049b8d8  5b                       pop        ebx
0049b8d9  8be5                     mov        esp, ebp
0049b8db  5d                       pop        ebp
0049b8dc  c22800                   ret        0x28
0049b8df  cc                       int3       
