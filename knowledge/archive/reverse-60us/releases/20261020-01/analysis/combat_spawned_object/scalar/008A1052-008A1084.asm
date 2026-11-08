008a1052  8d4dc8                   lea        ecx, [ebp - 0x38]
008a1055  68a496e200               push       0xe296a4
008a105a  51                       push       ecx
008a105b  e87037b6ff               call       0x4047d0
008a1060  83c408                   add        esp, 8
008a1063  84c0                     test       al, al
008a1065  741d                     je         0x8a1084
008a1067  53                       push       ebx
008a1068  e863e7f8ff               call       0x82f7d0
008a106d  83c404                   add        esp, 4
008a1070  8d55e8                   lea        edx, [ebp - 0x18]
008a1073  52                       push       edx
008a1074  8d4f18                   lea        ecx, [edi + 0x18]
008a1077  8945e8                   mov        dword ptr [ebp - 0x18], eax
008a107a  e8e134b6ff               call       0x404560
008a107f  e964120000               jmp        0x8a22e8