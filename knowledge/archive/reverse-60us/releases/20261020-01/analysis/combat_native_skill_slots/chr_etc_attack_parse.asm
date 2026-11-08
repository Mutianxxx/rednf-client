0088c238  8d55c4                   lea        edx, [ebp - 0x3c]
0088c23b  68ec33e200               push       0xe233ec
0088c240  52                       push       edx
0088c241  e88a85b7ff               call       0x4047d0
0088c246  83c408                   add        esp, 8
0088c249  84c0                     test       al, al
0088c24b  7443                     je         0x88c290
0088c24d  8dbee40b0000             lea        edi, [esi + 0xbe4]
0088c253  8bcf                     mov        ecx, edi
0088c255  e8d673b7ff               call       0x403630
0088c25a  8d45ec                   lea        eax, [ebp - 0x14]
0088c25d  50                       push       eax
0088c25e  e87d42faff               call       0x8304e0
0088c263  83c404                   add        esp, 4
0088c266  84c0                     test       al, al
0088c268  0f8437040000             je         0x88c6a5
0088c26e  8bff                     mov        edi, edi
0088c270  8d4dec                   lea        ecx, [ebp - 0x14]
0088c273  51                       push       ecx
0088c274  8bcf                     mov        ecx, edi
0088c276  e86579b7ff               call       0x403be0
0088c27b  8d55ec                   lea        edx, [ebp - 0x14]
0088c27e  52                       push       edx
0088c27f  e85c42faff               call       0x8304e0
0088c284  83c404                   add        esp, 4
0088c287  84c0                     test       al, al
0088c289  75e5                     jne        0x88c270
0088c28b  e915040000               jmp        0x88c6a5
