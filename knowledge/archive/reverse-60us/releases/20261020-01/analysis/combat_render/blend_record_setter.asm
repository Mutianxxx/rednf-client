00b084b0 55                       push       ebp
00b084b1 8bec                     mov        ebp, esp
00b084b3 668b4508                 mov        ax, word ptr [ebp + 8]
00b084b7 66898148030500           mov        word ptr [ecx + 0x50348], ax
00b084be b801000000               mov        eax, 1
00b084c3 5d                       pop        ebp
00b084c4 c20400                   ret        4