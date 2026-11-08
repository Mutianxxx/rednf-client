004db594  8bbbe80b0000             mov        edi, dword ptr [ebx + 0xbe8]
004db59a  3bbbec0b0000             cmp        edi, dword ptr [ebx + 0xbec]
004db5a0  0f84ce000000             je         0x4db674
004db5a6  eb08                     jmp        0x4db5b0
004db5a8  8da42400000000           lea        esp, [esp]
004db5af  90                       nop        
004db5b0  68e0baca00               push       0xcabae0
004db5b5  8bcf                     mov        ecx, edi
004db5b7  e8347b5700               call       0xa530f0
004db5bc  50                       push       eax
004db5bd  e829587200               call       0xc00deb
004db5c2  83c408                   add        esp, 8
004db5c5  85c0                     test       eax, eax
004db5c7  746a                     je         0x4db633
004db5c9  8d8b040c0000             lea        ecx, [ebx + 0xc04]
004db5cf  e81c7b5700               call       0xa530f0
004db5d4  8bcf                     mov        ecx, edi
004db5d6  89450c                   mov        dword ptr [ebp + 0xc], eax
004db5d9  e8127b5700               call       0xa530f0
004db5de  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004db5e1  8b15f8300001             mov        edx, dword ptr [0x10030f8]
004db5e7  50                       push       eax
004db5e8  51                       push       ecx
004db5e9  68f8b8ca00               push       0xcab8f8
004db5ee  52                       push       edx
004db5ef  e83c1c6a00               call       0xb7d230
004db5f4  83c410                   add        esp, 0x10
004db5f7  85c0                     test       eax, eax
004db5f9  740e                     je         0x4db609
004db5fb  50                       push       eax
004db5fc  8d8e44040000             lea        ecx, [esi + 0x444]
004db602  e82980fcff               call       0x4a3630
004db607  eb5a                     jmp        0x4db663
004db609  8d8b040c0000             lea        ecx, [ebx + 0xc04]
004db60f  e8dc7a5700               call       0xa530f0
004db614  8bcf                     mov        ecx, edi
004db616  89450c                   mov        dword ptr [ebp + 0xc], eax
004db619  e8d27a5700               call       0xa530f0
004db61e  50                       push       eax
004db61f  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004db622  50                       push       eax
004db623  68983ecd00               push       0xcd3e98
004db628  ff15bc2eff00             call       dword ptr [0xff2ebc]
004db62e  83c40c                   add        esp, 0xc
004db631  eb30                     jmp        0x4db663
004db633  8d8d70fcffff             lea        ecx, [ebp - 0x390]
004db639  e8f2c6f5ff               call       0x437d30
004db63e  50                       push       eax
004db63f  8d8e44040000             lea        ecx, [esi + 0x444]
004db645  c745fc12000000           mov        dword ptr [ebp - 4], 0x12
004db64c  e8df7ffcff               call       0x4a3630
004db651  8d8d70fcffff             lea        ecx, [ebp - 0x390]
004db657  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004db65e  e8fdc0f5ff               call       0x437760
004db663  8b83ec0b0000             mov        eax, dword ptr [ebx + 0xbec]
004db669  83c704                   add        edi, 4
004db66c  3bf8                     cmp        edi, eax
004db66e  0f853cffffff             jne        0x4db5b0
