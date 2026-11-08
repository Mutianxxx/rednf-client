0088505b 689831e200               push      0xe23198
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
