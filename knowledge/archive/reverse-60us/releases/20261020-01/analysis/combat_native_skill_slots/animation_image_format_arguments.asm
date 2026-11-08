00a28f64  8d4db4                   lea        ecx, [ebp - 0x4c]
00a28f67  51                       push       ecx
00a28f68  e8a377e0ff               call       0x830710
00a28f6d  53                       push       ebx
00a28f6e  e85d68e0ff               call       0x82f7d0
00a28f73  8945d0                   mov        dword ptr [ebp - 0x30], eax
00a28f76  8a4510                   mov        al, byte ptr [ebp + 0x10]
00a28f79  83c408                   add        esp, 8
00a28f7c  3ac3                     cmp        al, bl
00a28f7e  743a                     je         0xa28fba
00a28f80  8b7d14                   mov        edi, dword ptr [ebp + 0x14]
00a28f83  3bfb                     cmp        edi, ebx
00a28f85  7433                     je         0xa28fba
00a28f87  8d55d0                   lea        edx, [ebp - 0x30]
00a28f8a  52                       push       edx
00a28f8b  8d45b4                   lea        eax, [ebp - 0x4c]
00a28f8e  50                       push       eax
00a28f8f  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
00a28f95  e846170000               call       0xa2a6e0
00a28f9a  50                       push       eax
00a28f9b  8bcf                     mov        ecx, edi
00a28f9d  c645fc19                 mov        byte ptr [ebp - 4], 0x19
00a28fa1  e85a29e5ff               call       0x87b900
00a28fa6  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
00a28fac  c645fc03                 mov        byte ptr [ebp - 4], 3
00a28fb0  e8bb501600               call       0xb8e070
00a28fb5  e9d0feffff               jmp        0xa28e8a
00a28fba  3bf3                     cmp        esi, ebx
00a28fbc  0f84c8feffff             je         0xa28e8a
00a28fc2  8d4db4                   lea        ecx, [ebp - 0x4c]
00a28fc5  68e0baca00               push       0xcabae0
00a28fca  51                       push       ecx
00a28fcb  e8a0a9a0ff               call       0x433970
00a28fd0  83c408                   add        esp, 8
00a28fd3  84c0                     test       al, al
00a28fd5  0f84affeffff             je         0xa28e8a
00a28fdb  c745f007000000           mov        dword ptr [ebp - 0x10], 7
00a28fe2  895dec                   mov        dword ptr [ebp - 0x14], ebx
00a28fe5  66895ddc                 mov        word ptr [ebp - 0x24], bx
00a28fe9  385d10                   cmp        byte ptr [ebp + 0x10], bl
00a28fec  c645fc1a                 mov        byte ptr [ebp - 4], 0x1a
00a28ff0  7425                     je         0xa29017
00a28ff2  8b551c                   mov        edx, dword ptr [ebp + 0x1c]
00a28ff5  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a28ff8  52                       push       edx
00a28ff9  50                       push       eax
00a28ffa  8d4db4                   lea        ecx, [ebp - 0x4c]
00a28ffd  e8aea4a0ff               call       0x4334b0
00a29002  50                       push       eax
00a29003  53                       push       ebx
00a29004  e8979a0200               call       0xa52aa0
00a29009  83c410                   add        esp, 0x10
00a2900c  50                       push       eax
00a2900d  8d4dd8                   lea        ecx, [ebp - 0x28]
00a29010  e82b5b9eff               call       0x40eb40
00a29015  eb0c                     jmp        0xa29023
