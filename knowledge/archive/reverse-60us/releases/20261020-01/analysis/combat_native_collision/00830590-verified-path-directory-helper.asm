00830590 55                       push      ebp
00830591 8bec                     mov       ebp, esp
00830593 81ec00040000             sub       esp, 0x400
00830599 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0083059c 8d4510                   lea       eax, [ebp + 0x10]
0083059f 50                       push      eax
008305a0 51                       push      ecx
008305a1 8d9500fcffff             lea       edx, [ebp - 0x400]
008305a7 6800020000               push      0x200
008305ac 52                       push      edx
008305ad e830fa3c00               call      0xbfffe2
008305b2 8d8500fcffff             lea       eax, [ebp - 0x400]
008305b8 50                       push      eax
008305b9 e80ff83c00               call      0xbffdcd
008305be 83c414                   add       esp, 0x14
008305c1 48                       dec       eax
008305c2 7823                     js        0x8305e7
008305c4 eb0a                     jmp       0x8305d0
008305c6 8da42400000000           lea       esp, [esp]
008305cd 8d4900                   lea       ecx, [ecx]
008305d0 668b8c4500fcffff         mov       cx, word ptr [ebp + eax*2 - 0x400]
008305d8 6683f95c                 cmp       cx, 0x5c
008305dc 7409                     je        0x8305e7
008305de 6683f92f                 cmp       cx, 0x2f
008305e2 7403                     je        0x8305e7
008305e4 48                       dec       eax
008305e5 79e9                     jns       0x8305d0
008305e7 8d8d00fcffff             lea       ecx, [ebp - 0x400]
008305ed 51                       push      ecx
008305ee 66c7844502fcffff0000     mov       word ptr [ebp + eax*2 - 0x3fe], 0
008305f8 e8d0f73c00               call      0xbffdcd
008305fd 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00830600 83c404                   add       esp, 4
00830603 50                       push      eax
00830604 8d9500fcffff             lea       edx, [ebp - 0x400]
0083060a 52                       push      edx
0083060b e87028bdff               call      0x402e80
00830610 8be5                     mov       esp, ebp
00830612 5d                       pop       ebp
00830613 c3                       ret       
