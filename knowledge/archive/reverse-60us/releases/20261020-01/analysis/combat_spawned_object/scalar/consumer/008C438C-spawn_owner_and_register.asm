008c438c  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
008c438f  0fb755d0                 movzx      edx, word ptr [ebp - 0x30]
008c4393  51                       push       ecx
008c4394  52                       push       edx
008c4395  e86641d2ff               call       0x5e8500
008c439a  8bf8                     mov        edi, eax
008c439c  83c408                   add        esp, 8
008c439f  3bfb                     cmp        edi, ebx
008c43a1  897dbc                   mov        dword ptr [ebp - 0x44], edi
008c43a4  0f8433020000             je         0x8c45dd
008c43aa  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
008c43ad  8b07                     mov        eax, dword ptr [edi]
008c43af  51                       push       ecx
008c43b0  8bcf                     mov        ecx, edi
008c43b2  ff9044030000             call       dword ptr [eax + 0x344]
008c43b8  0fb755d8                 movzx      edx, word ptr [ebp - 0x28]
008c43bc  0fb745e0                 movzx      eax, word ptr [ebp - 0x20]
008c43c0  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
008c43c3  53                       push       ebx
008c43c4  53                       push       ebx
008c43c5  53                       push       ebx
008c43c6  57                       push       edi
008c43c7  52                       push       edx
008c43c8  50                       push       eax
008c43c9  53                       push       ebx
008c43ca  e8a199c4ff               call       0x50dd70