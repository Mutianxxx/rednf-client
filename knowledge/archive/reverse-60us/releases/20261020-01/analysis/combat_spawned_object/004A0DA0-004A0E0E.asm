004a0da0  55                       push       ebp
004a0da1  8bec                     mov        ebp, esp
004a0da3  51                       push       ecx
004a0da4  56                       push       esi
004a0da5  57                       push       edi
004a0da6  8b7d08                   mov        edi, dword ptr [ebp + 8]
004a0da9  8bf1                     mov        esi, ecx
004a0dab  8d4508                   lea        eax, [ebp + 8]
004a0dae  50                       push       eax
004a0daf  8d4dfc                   lea        ecx, [ebp - 4]
004a0db2  51                       push       ecx
004a0db3  b9e8e30b01               mov        ecx, 0x10be3e8
004a0db8  89be68080000             mov        dword ptr [esi + 0x868], edi
004a0dbe  897d08                   mov        dword ptr [ebp + 8], edi
004a0dc1  e84a35f9ff               call       0x434310
004a0dc6  8b45fc                   mov        eax, dword ptr [ebp - 4]
004a0dc9  3b05ece30b01             cmp        eax, dword ptr [0x10be3ec]
004a0dcf  7426                     je         0x4a0df7
004a0dd1  83782808                 cmp        dword ptr [eax + 0x28], 8
004a0dd5  7205                     jb         0x4a0ddc
004a0dd7  8b4014                   mov        eax, dword ptr [eax + 0x14]
004a0dda  eb03                     jmp        0x4a0ddf
004a0ddc  83c014                   add        eax, 0x14
004a0ddf  85c0                     test       eax, eax
004a0de1  7414                     je         0x4a0df7
004a0de3  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004a0de6  52                       push       edx
004a0de7  50                       push       eax
004a0de8  8bce                     mov        ecx, esi
004a0dea  e8e1e6ffff               call       0x49f4d0
004a0def  5f                       pop        edi
004a0df0  5e                       pop        esi
004a0df1  8be5                     mov        esp, ebp
004a0df3  5d                       pop        ebp
004a0df4  c20800                   ret        8
004a0df7  57                       push       edi
004a0df8  6848f1cc00               push       0xccf148
004a0dfd  ff15bc2eff00             call       dword ptr [0xff2ebc]
004a0e03  83c408                   add        esp, 8
004a0e06  5f                       pop        edi
004a0e07  5e                       pop        esi
004a0e08  8be5                     mov        esp, ebp
004a0e0a  5d                       pop        ebp
004a0e0b  c20800                   ret        8