0082f710  55                       push       ebp
0082f711  8bec                     mov        ebp, esp
0082f713  81ec00040000             sub        esp, 0x400
0082f719  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0082f71c  8d4510                   lea        eax, [ebp + 0x10]
0082f71f  50                       push       eax
0082f720  51                       push       ecx
0082f721  8d9500fcffff             lea        edx, [ebp - 0x400]
0082f727  6800020000               push       0x200
0082f72c  52                       push       edx
0082f72d  e8b0083d00               call       0xbfffe2
0082f732  8d8500fcffff             lea        eax, [ebp - 0x400]
0082f738  50                       push       eax
0082f739  e88f063d00               call       0xbffdcd
0082f73e  83c414                   add        esp, 0x14
0082f741  48                       dec        eax
0082f742  7823                     js         0x82f767
0082f744  eb0a                     jmp        0x82f750
0082f746  8da42400000000           lea        esp, [esp]
0082f74d  8d4900                   lea        ecx, [ecx]
0082f750  668b8c4500fcffff         mov        cx, word ptr [ebp + eax*2 - 0x400]
0082f758  6683f95c                 cmp        cx, 0x5c
0082f75c  7409                     je         0x82f767
0082f75e  6683f92f                 cmp        cx, 0x2f
0082f762  7403                     je         0x82f767
0082f764  48                       dec        eax
0082f765  79e9                     jns        0x82f750
0082f767  8d8d00fcffff             lea        ecx, [ebp - 0x400]
0082f76d  51                       push       ecx
0082f76e  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0082f771  66c7844502fcffff0000     mov        word ptr [ebp + eax*2 - 0x3fe], 0
0082f77b  e820412200               call       0xa538a0
0082f780  8be5                     mov        esp, ebp
0082f782  5d                       pop        ebp
0082f783  c3                       ret        