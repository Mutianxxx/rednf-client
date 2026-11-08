0049fd8e 8d4f6c                   lea       ecx, [edi + 0x6c]
0049fd91 68e0baca00               push      0xcabae0
0049fd96 e855335b00               call      0xa530f0
0049fd9b 50                       push      eax
0049fd9c e84a107600               call      0xc00deb
0049fda1 83c408                   add       esp, 8
0049fda4 85c0                     test      eax, eax
0049fda6 7456                     je        0x49fdfe
0049fda8 68b4010000               push      0x1b4
0049fdad e89e3ef6ff               call      0x403c50
0049fdb2 83c404                   add       esp, 4
0049fdb5 894508                   mov       dword ptr [ebp + 8], eax
0049fdb8 85c0                     test      eax, eax
0049fdba c745fc07000000           mov       dword ptr [ebp - 4], 7
0049fdc1 742c                     je        0x49fdef
0049fdc3 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
0049fdca 7208                     jb        0x49fdd4
0049fdcc 8b9e48020000             mov       ebx, dword ptr [esi + 0x248]
0049fdd2 eb06                     jmp       0x49fdda
0049fdd4 8d9e48020000             lea       ebx, [esi + 0x248]
0049fdda 56                       push      esi
0049fddb 8d4f6c                   lea       ecx, [edi + 0x6c]
0049fdde e80d335b00               call      0xa530f0
0049fde3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049fde6 50                       push      eax
0049fde7 53                       push      ebx
0049fde8 e853360000               call      0x4a3440
0049fded eb02                     jmp       0x49fdf1
0049fdef 33c0                     xor       eax, eax
0049fdf1 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fdf8 898694070000             mov       dword ptr [esi + 0x794], eax
