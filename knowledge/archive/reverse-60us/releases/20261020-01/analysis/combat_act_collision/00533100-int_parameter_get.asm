00533100 55                       push       ebp
00533101 8bec                     mov        ebp, esp
00533103 8b4128                   mov        eax, dword ptr [ecx + 0x28]
00533106 8b512c                   mov        edx, dword ptr [ecx + 0x2c]
00533109 83c124                   add        ecx, 0x24
0053310c 2bd0                     sub        edx, eax
0053310e 8b4508                   mov        eax, dword ptr [ebp + 8]
00533111 c1fa02                   sar        edx, 2
00533114 3bd0                     cmp        edx, eax
00533116 760c                     jbe        0x533124
00533118 50                       push       eax
00533119 e862b65000               call       0xa3e780
0053311e 8b00                     mov        eax, dword ptr [eax]
00533120 5d                       pop        ebp
00533121 c20400                   ret        4
00533124 83c8ff                   or         eax, 0xffffffff
00533127 5d                       pop        ebp
00533128 c20400                   ret        4
