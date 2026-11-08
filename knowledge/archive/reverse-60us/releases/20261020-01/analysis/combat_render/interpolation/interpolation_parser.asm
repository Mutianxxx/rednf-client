00a29191 53                       push       ebx
00a29192 e83966e0ff               call       0x82f7d0
00a29197 83c404                   add        esp, 4
00a2919a 3bf3                     cmp        esi, ebx
00a2919c 0f84e8fcffff             je         0xa28e8a
00a291a2 3bc3                     cmp        eax, ebx
00a291a4 0f95c1                   setne      cl
00a291a7 884e20                   mov        byte ptr [esi + 0x20], cl
00a291aa e9dbfcffff               jmp        0xa28e8a
