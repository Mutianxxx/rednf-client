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