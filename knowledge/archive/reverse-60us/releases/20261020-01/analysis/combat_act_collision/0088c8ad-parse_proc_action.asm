0088c8ad 68842ae200               push       0xe22a84
0088c8b2 e816353700               call       0xbffdcd
0088c8b7 8b55e8                   mov        edx, dword ptr [ebp - 0x18]
0088c8ba 83c404                   add        esp, 4
0088c8bd 50                       push       eax
0088c8be 68842ae200               push       0xe22a84
0088c8c3 52                       push       edx
0088c8c4 57                       push       edi
0088c8c5 8d4dd4                   lea        ecx, [ebp - 0x2c]
0088c8c8 e82377b7ff               call       0x403ff0
0088c8cd 85c0                     test       eax, eax
0088c8cf 750f                     jne        0x88c8e0
0088c8d1 8d864c070000             lea        eax, [esi + 0x74c]
0088c8d7 50                       push       eax
0088c8d8 e8033cfaff               call       0x8304e0
0088c8dd 83c404                   add        esp, 4
