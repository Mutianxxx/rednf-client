004cc270  8b81a0260000             mov        eax, dword ptr [ecx + 0x26a0]
004cc276  85c0                     test       eax, eax
004cc278  7526                     jne        0x4cc2a0
004cc27a  390dd4f10401             cmp        dword ptr [0x104f1d4], ecx
004cc280  b8c824cd00               mov        eax, 0xcd24c8
004cc285  7405                     je         0x4cc28c
004cc287  b8bc24cd00               mov        eax, 0xcd24bc
004cc28c  50                       push       eax
004cc28d  68d824cd00               push       0xcd24d8
004cc292  ff15bc2eff00             call       dword ptr [0xff2ebc]
004cc298  83c408                   add        esp, 8
004cc29b  b89c330001               mov        eax, 0x100339c
004cc2a0  c3                       ret        
004cc2a1  cc                       int3       
004cc2a2  cc                       int3       
004cc2a3  cc                       int3       
004cc2a4  cc                       int3       
004cc2a5  cc                       int3       
004cc2a6  cc                       int3       
004cc2a7  cc                       int3       
004cc2a8  cc                       int3       
004cc2a9  cc                       int3       
004cc2aa  cc                       int3       
004cc2ab  cc                       int3       
004cc2ac  cc                       int3       
004cc2ad  cc                       int3       
004cc2ae  cc                       int3       
004cc2af  cc                       int3       
004cc2b0  55                       push       ebp
004cc2b1  8bec                     mov        ebp, esp
004cc2b3  8b4508                   mov        eax, dword ptr [ebp + 8]
004cc2b6  85c0                     test       eax, eax
004cc2b8  56                       push       esi
004cc2b9  57                       push       edi
004cc2ba  8bf9                     mov        edi, ecx
004cc2bc  be3c530001               mov        esi, 0x100533c
004cc2c1  7405                     je         0x4cc2c8
004cc2c3  be4c530001               mov        esi, 0x100534c
004cc2c8  8b07                     mov        eax, dword ptr [edi]
004cc2ca  8bcf                     mov        ecx, edi
004cc2cc  ff9038070000             call       dword ptr [eax + 0x738]
004cc2d2  8b10                     mov        edx, dword ptr [eax]
004cc2d4  56                       push       esi
004cc2d5  8bc8                     mov        ecx, eax
004cc2d7  ff5228                   call       dword ptr [edx + 0x28]
004cc2da  83f802                   cmp        eax, 2
004cc2dd  be04000000               mov        esi, 4
004cc2e2  7504                     jne        0x4cc2e8
004cc2e4  33f6                     xor        esi, esi
004cc2e6  eb21                     jmp        0x4cc309
004cc2e8  83f803                   cmp        eax, 3
004cc2eb  7507                     jne        0x4cc2f4
004cc2ed  be01000000               mov        esi, 1
004cc2f2  eb15                     jmp        0x4cc309
004cc2f4  85c0                     test       eax, eax
004cc2f6  7507                     jne        0x4cc2ff
004cc2f8  be02000000               mov        esi, 2
004cc2fd  eb0a                     jmp        0x4cc309
004cc2ff  83f801                   cmp        eax, 1
004cc302  7505                     jne        0x4cc309
004cc304  be03000000               mov        esi, 3
004cc309  8b07                     mov        eax, dword ptr [edi]
004cc30b  6a0f                     push       0xf
004cc30d  8bcf                     mov        ecx, edi
004cc30f  ff9010040000             call       dword ptr [eax + 0x410]
004cc315  84c0                     test       al, al
004cc317  740f                     je         0x4cc328
004cc319  56                       push       esi
004cc31a  e841b6f7ff               call       0x447960
004cc31f  83c404                   add        esp, 4
004cc322  5f                       pop        edi
004cc323  5e                       pop        esi
004cc324  5d                       pop        ebp
004cc325  c20400                   ret        4
004cc328  5f                       pop        edi
004cc329  8bc6                     mov        eax, esi
004cc32b  5e                       pop        esi
004cc32c  5d                       pop        ebp
004cc32d  c20400                   ret        4