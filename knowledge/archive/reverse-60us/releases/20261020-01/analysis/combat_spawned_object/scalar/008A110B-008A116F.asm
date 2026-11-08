008a110b  8d55c8                   lea        edx, [ebp - 0x38]
008a110e  686096e200               push       0xe29660
008a1113  52                       push       edx
008a1114  e8b736b6ff               call       0x4047d0
008a1119  83c408                   add        esp, 8
008a111c  84c0                     test       al, al
008a111e  741d                     je         0x8a113d
008a1120  53                       push       ebx
008a1121  e8aae6f8ff               call       0x82f7d0
008a1126  8945e8                   mov        dword ptr [ebp - 0x18], eax
008a1129  83c404                   add        esp, 4
008a112c  8d45e8                   lea        eax, [ebp - 0x18]
008a112f  50                       push       eax
008a1130  8d4f30                   lea        ecx, [edi + 0x30]
008a1133  e82834b6ff               call       0x404560
008a1138  e9ab110000               jmp        0x8a22e8
008a113d  8d4dc8                   lea        ecx, [ebp - 0x38]
008a1140  683096e200               push       0xe29630
008a1145  51                       push       ecx
008a1146  e88536b6ff               call       0x4047d0
008a114b  83c408                   add        esp, 8
008a114e  84c0                     test       al, al
008a1150  741d                     je         0x8a116f
008a1152  53                       push       ebx
008a1153  e878e6f8ff               call       0x82f7d0
008a1158  83c404                   add        esp, 4
008a115b  8d55e8                   lea        edx, [ebp - 0x18]
008a115e  52                       push       edx
008a115f  8d4f38                   lea        ecx, [edi + 0x38]
008a1162  8945e8                   mov        dword ptr [ebp - 0x18], eax
008a1165  e8f633b6ff               call       0x404560
008a116a  e979110000               jmp        0x8a22e8