00885060 8d4df0                   lea       ecx, [ebp - 0x10]
00885063 e88897b8ff               call      0x40e7f0
00885068 84c0                     test      al, al
0088506a 743a                     je        0x8850a6
0088506c 6a00                     push      0
0088506e e85da7faff               call      0x82f7d0
00885073 83c404                   add       esp, 4
00885076 85c0                     test      eax, eax
00885078 0f8eb0000000             jle       0x88512e
0088507e 8d9ee8000000             lea       ebx, [esi + 0xe8]
00885084 8bf8                     mov       edi, eax
00885086 6a00                     push      0
00885088 e843a7faff               call      0x82f7d0
0088508d 83c404                   add       esp, 4
00885090 8d4dec                   lea       ecx, [ebp - 0x14]
00885093 51                       push      ecx
00885094 8bcb                     mov       ecx, ebx
00885096 8945ec                   mov       dword ptr [ebp - 0x14], eax
00885099 e88220b8ff               call      0x407120
0088509e 4f                       dec       edi
0088509f 75e5                     jne       0x885086
008850a1 e988000000               jmp       0x88512e
008850a6 686031e200               push      0xe23160
008850ab 8d4df0                   lea       ecx, [ebp - 0x10]
008850ae e83d97b8ff               call      0x40e7f0
008850b3 84c0                     test      al, al
008850b5 7435                     je        0x8850ec
008850b7 6a00                     push      0
008850b9 e812a7faff               call      0x82f7d0
008850be 83c404                   add       esp, 4
008850c1 85c0                     test      eax, eax
008850c3 7e69                     jle       0x88512e
008850c5 8d9ef8000000             lea       ebx, [esi + 0xf8]
008850cb 8bf8                     mov       edi, eax
008850cd 8d4900                   lea       ecx, [ecx]
008850d0 8d55e0                   lea       edx, [ebp - 0x20]
008850d3 52                       push      edx
008850d4 e807b4faff               call      0x8304e0
008850d9 83c404                   add       esp, 4
008850dc 8d45e0                   lea       eax, [ebp - 0x20]
008850df 50                       push      eax
008850e0 8bcb                     mov       ecx, ebx
008850e2 e8f9eab7ff               call      0x403be0
008850e7 4f                       dec       edi
008850e8 75e6                     jne       0x8850d0
008850ea eb42                     jmp       0x88512e
008850ec 682431e200               push      0xe23124
008850f1 8d4df0                   lea       ecx, [ebp - 0x10]
008850f4 e8f796b8ff               call      0x40e7f0
008850f9 84c0                     test      al, al
008850fb 7431                     je        0x88512e
008850fd 6a00                     push      0
008850ff e8cca6faff               call      0x82f7d0
00885104 83c404                   add       esp, 4
00885107 85c0                     test      eax, eax
00885109 7e23                     jle       0x88512e
0088510b 8d9e34010000             lea       ebx, [esi + 0x134]
00885111 8bf8                     mov       edi, eax
00885113 6a00                     push      0
00885115 e8b6a6faff               call      0x82f7d0
0088511a 83c404                   add       esp, 4
0088511d 8d4dec                   lea       ecx, [ebp - 0x14]
00885120 51                       push      ecx
00885121 8bcb                     mov       ecx, ebx
00885123 8945ec                   mov       dword ptr [ebp - 0x14], eax
00885126 e8f51fb8ff               call      0x407120
0088512b 4f                       dec       edi
0088512c 75e5                     jne       0x885113
0088512e 8d55f0                   lea       edx, [ebp - 0x10]
00885131 52                       push      edx
