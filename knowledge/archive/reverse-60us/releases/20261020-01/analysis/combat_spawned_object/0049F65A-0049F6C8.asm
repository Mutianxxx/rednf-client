0049f65a  8d5f34                   lea        ebx, [edi + 0x34]
0049f65d  68e0baca00               push       0xcabae0
0049f662  8bcb                     mov        ecx, ebx
0049f664  e8873a5b00               call       0xa530f0
0049f669  50                       push       eax
0049f66a  e87c177600               call       0xc00deb
0049f66f  83c408                   add        esp, 8
0049f672  85c0                     test       eax, eax
0049f674  7452                     je         0x49f6c8
0049f676  68e8010000               push       0x1e8
0049f67b  e8d045f6ff               call       0x403c50
0049f680  83c404                   add        esp, 4
0049f683  89450c                   mov        dword ptr [ebp + 0xc], eax
0049f686  85c0                     test       eax, eax
0049f688  c745fc00000000           mov        dword ptr [ebp - 4], 0
0049f68f  7426                     je         0x49f6b7
0049f691  8d8fa4000000             lea        ecx, [edi + 0xa4]
0049f697  e8543a5b00               call       0xa530f0
0049f69c  6a01                     push       1
0049f69e  8bcb                     mov        ecx, ebx
0049f6a0  894508                   mov        dword ptr [ebp + 8], eax
0049f6a3  e8483a5b00               call       0xa530f0
0049f6a8  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0049f6ab  50                       push       eax
0049f6ac  51                       push       ecx
0049f6ad  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0049f6b0  e8ab33fdff               call       0x472a60
0049f6b5  eb02                     jmp        0x49f6b9
0049f6b7  33c0                     xor        eax, eax
0049f6b9  8b16                     mov        edx, dword ptr [esi]
0049f6bb  50                       push       eax
0049f6bc  8bce                     mov        ecx, esi
0049f6be  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0049f6c5  ff526c                   call       dword ptr [edx + 0x6c]