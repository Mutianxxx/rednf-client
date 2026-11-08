0088c136  8d55c4                   lea        edx, [ebp - 0x3c]
0088c139  688ce8e100               push       0xe1e88c
0088c13e  52                       push       edx
0088c13f  e88c86b7ff               call       0x4047d0
0088c144  83c408                   add        esp, 8
0088c147  84c0                     test       al, al
0088c149  7445                     je         0x88c190
0088c14b  8dbebc0b0000             lea        edi, [esi + 0xbbc]
0088c151  8bcf                     mov        ecx, edi
0088c153  e8d874b7ff               call       0x403630
0088c158  8d45ec                   lea        eax, [ebp - 0x14]
0088c15b  50                       push       eax
0088c15c  e87f43faff               call       0x8304e0
0088c161  83c404                   add        esp, 4
0088c164  84c0                     test       al, al
0088c166  0f8439050000             je         0x88c6a5
0088c16c  8d642400                 lea        esp, [esp]
0088c170  8d4dec                   lea        ecx, [ebp - 0x14]
0088c173  51                       push       ecx
0088c174  8bcf                     mov        ecx, edi
0088c176  e8657ab7ff               call       0x403be0
0088c17b  8d55ec                   lea        edx, [ebp - 0x14]
0088c17e  52                       push       edx
0088c17f  e85c43faff               call       0x8304e0
0088c184  83c404                   add        esp, 4
0088c187  84c0                     test       al, al
0088c189  75e5                     jne        0x88c170
0088c18b  e915050000               jmp        0x88c6a5
