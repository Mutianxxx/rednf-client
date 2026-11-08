0049f240 55                       push      ebp
0049f241 8bec                     mov       ebp, esp
0049f243 6aff                     push      -1
0049f245 68416bc500               push      0xc56b41
0049f24a 64a100000000             mov       eax, dword ptr fs:[0]
0049f250 50                       push      eax
0049f251 64892500000000           mov       dword ptr fs:[0], esp
0049f258 51                       push      ecx
0049f259 56                       push      esi
0049f25a 8bf1                     mov       esi, ecx
0049f25c 6a00                     push      0
0049f25e 6a00                     push      0
0049f260 8d4e20                   lea       ecx, [esi + 0x20]
0049f263 e8f87c6600               call      0xb06f60
0049f268 6a00                     push      0
0049f26a 6a00                     push      0
0049f26c 8d4e60                   lea       ecx, [esi + 0x60]
0049f26f e8ec7c6600               call      0xb06f60
0049f274 6a00                     push      0
0049f276 6a00                     push      0
0049f278 8d8ea0000000             lea       ecx, [esi + 0xa0]
0049f27e e8dd7c6600               call      0xb06f60
0049f283 6844010000               push      0x144
0049f288 e8c349f6ff               call      0x403c50
0049f28d 83c404                   add       esp, 4
0049f290 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049f293 85c0                     test      eax, eax
0049f295 c745fc00000000           mov       dword ptr [ebp - 4], 0
0049f29c 740a                     je        0x49f2a8
0049f29e 56                       push      esi
0049f29f 8bc8                     mov       ecx, eax
0049f2a1 e89ad1ffff               call      0x49c440
0049f2a6 eb02                     jmp       0x49f2aa
0049f2a8 33c0                     xor       eax, eax
0049f2aa 8986f8000000             mov       dword ptr [esi + 0xf8], eax
0049f2b0 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0049f2b3 85c0                     test      eax, eax
0049f2b5 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049f2bc 740a                     je        0x49f2c8
0049f2be 8b16                     mov       edx, dword ptr [esi]
0049f2c0 50                       push      eax
0049f2c1 8bce                     mov       ecx, esi
0049f2c3 ff5270                   call      dword ptr [edx + 0x70]
0049f2c6 eb0b                     jmp       0x49f2d3
0049f2c8 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f2cb 8b06                     mov       eax, dword ptr [esi]
0049f2cd 51                       push      ecx
0049f2ce 8bce                     mov       ecx, esi
0049f2d0 ff506c                   call      dword ptr [eax + 0x6c]
0049f2d3 8a550c                   mov       dl, byte ptr [ebp + 0xc]
0049f2d6 8b06                     mov       eax, dword ptr [esi]
0049f2d8 6a01                     push      1
0049f2da 8bce                     mov       ecx, esi
0049f2dc c786e400000021000000     mov       dword ptr [esi + 0xe4], 0x21
0049f2e6 889685010000             mov       byte ptr [esi + 0x185], dl
0049f2ec ff5054                   call      dword ptr [eax + 0x54]
0049f2ef 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049f2f2 c686e801000000           mov       byte ptr [esi + 0x1e8], 0
0049f2f9 5e                       pop       esi
0049f2fa 64890d00000000           mov       dword ptr fs:[0], ecx
0049f301 8be5                     mov       esp, ebp
0049f303 5d                       pop       ebp
0049f304 c20c00                   ret       0xc
