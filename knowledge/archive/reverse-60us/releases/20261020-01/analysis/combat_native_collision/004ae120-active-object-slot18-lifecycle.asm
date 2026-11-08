004ae120 55                       push      ebp
004ae121 8bec                     mov       ebp, esp
004ae123 83ec18                   sub       esp, 0x18
004ae126 56                       push      esi
004ae127 8bf1                     mov       esi, ecx
004ae129 57                       push      edi
004ae12a 8bbe04010000             mov       edi, dword ptr [esi + 0x104]
004ae130 85ff                     test      edi, edi
004ae132 750e                     jne       0x4ae142
004ae134 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004ae13a 85c0                     test      eax, eax
004ae13c 0f8446050000             je        0x4ae688
004ae142 8b868c190000             mov       eax, dword ptr [esi + 0x198c]
004ae148 85c0                     test      eax, eax
004ae14a 7546                     jne       0x4ae192
004ae14c 83be9019000001           cmp       dword ptr [esi + 0x1990], 1
004ae153 743d                     je        0x4ae192
004ae155 85ff                     test      edi, edi
004ae157 7439                     je        0x4ae192
004ae159 83bf24010000ff           cmp       dword ptr [edi + 0x124], -1
004ae160 7507                     jne       0x4ae169
004ae162 8bcf                     mov       ecx, edi
004ae164 e8f79d5700               call      0xa27f60
004ae169 8b8fdc000000             mov       ecx, dword ptr [edi + 0xdc]
004ae16f 8b15f83e0d01             mov       edx, dword ptr [0x10d3ef8]
004ae175 8d87dc000000             lea       eax, [edi + 0xdc]
004ae17b 2bc8                     sub       ecx, eax
004ae17d 33ca                     xor       ecx, edx
004ae17f 83f901                   cmp       ecx, 1
004ae182 750e                     jne       0x4ae192
004ae184 8d4e60                   lea       ecx, [esi + 0x60]
004ae187 e8748d6500               call      0xb06f00
004ae18c 89868c190000             mov       dword ptr [esi + 0x198c], eax
004ae192 8b16                     mov       edx, dword ptr [esi]
004ae194 8bce                     mov       ecx, esi
004ae196 ff92f4000000             call      dword ptr [edx + 0xf4]
004ae19c 85c0                     test      eax, eax
004ae19e 7436                     je        0x4ae1d6
004ae1a0 8b06                     mov       eax, dword ptr [esi]
004ae1a2 8bce                     mov       ecx, esi
004ae1a4 ff90f4000000             call      dword ptr [eax + 0xf4]
004ae1aa 8bf8                     mov       edi, eax
004ae1ac 83bf24010000ff           cmp       dword ptr [edi + 0x124], -1
004ae1b3 7507                     jne       0x4ae1bc
004ae1b5 8bcf                     mov       ecx, edi
004ae1b7 e8a49d5700               call      0xa27f60
004ae1bc 8b8fdc000000             mov       ecx, dword ptr [edi + 0xdc]
004ae1c2 8d87dc000000             lea       eax, [edi + 0xdc]
004ae1c8 2bc8                     sub       ecx, eax
004ae1ca 330df83e0d01             xor       ecx, dword ptr [0x10d3ef8]
004ae1d0 898e90190000             mov       dword ptr [esi + 0x1990], ecx
004ae1d6 8bce                     mov       ecx, esi
004ae1d8 e8c3f2ffff               call      0x4ad4a0
004ae1dd 84c0                     test      al, al
004ae1df 750e                     jne       0x4ae1ef
004ae1e1 8b868c190000             mov       eax, dword ptr [esi + 0x198c]
004ae1e7 85c0                     test      eax, eax
004ae1e9 0f8692040000             jbe       0x4ae681
004ae1ef 8b16                     mov       edx, dword ptr [esi]
004ae1f1 8bbe00010000             mov       edi, dword ptr [esi + 0x100]
004ae1f7 53                       push      ebx
004ae1f8 8bce                     mov       ecx, esi
004ae1fa ff5228                   call      dword ptr [edx + 0x28]
004ae1fd 8b400c                   mov       eax, dword ptr [eax + 0xc]
004ae200 8b16                     mov       edx, dword ptr [esi]
004ae202 50                       push      eax
004ae203 8bce                     mov       ecx, esi
004ae205 ff9294000000             call      dword ptr [edx + 0x94]
004ae20b 50                       push      eax
004ae20c 8bcf                     mov       ecx, edi
004ae20e e8edc70500               call      0x50aa00
004ae213 8b9e00010000             mov       ebx, dword ptr [esi + 0x100]
004ae219 8945f0                   mov       dword ptr [ebp - 0x10], eax
004ae21c 8b06                     mov       eax, dword ptr [esi]
004ae21e 680000803f               push      0x3f800000
004ae223 8bce                     mov       ecx, esi
004ae225 ff5028                   call      dword ptr [eax + 0x28]
004ae228 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004ae22b 8b16                     mov       edx, dword ptr [esi]
004ae22d 51                       push      ecx
004ae22e 8bce                     mov       ecx, esi
004ae230 ff929c000000             call      dword ptr [edx + 0x9c]
004ae236 50                       push      eax
004ae237 8b06                     mov       eax, dword ptr [esi]
004ae239 8bce                     mov       ecx, esi
004ae23b ff9098000000             call      dword ptr [eax + 0x98]
004ae241 50                       push      eax
004ae242 8bcb                     mov       ecx, ebx
004ae244 e8f7c70500               call      0x50aa40
004ae249 8b16                     mov       edx, dword ptr [esi]
004ae24b 8bce                     mov       ecx, esi
004ae24d 8945f4                   mov       dword ptr [ebp - 0xc], eax
004ae250 ff92c0000000             call      dword ptr [edx + 0xc0]
004ae256 83f801                   cmp       eax, 1
004ae259 0f95c0                   setne     al
004ae25c 8845f8                   mov       byte ptr [ebp - 8], al
004ae25f 8b868c190000             mov       eax, dword ptr [esi + 0x198c]
004ae265 85c0                     test      eax, eax
004ae267 765d                     jbe       0x4ae2c6
004ae269 8d7e60                   lea       edi, [esi + 0x60]
004ae26c 68c8000000               push      0xc8
004ae271 8bcf                     mov       ecx, edi
004ae273 e8888c6500               call      0xb06f00
004ae278 2b868c190000             sub       eax, dword ptr [esi + 0x198c]
004ae27e 50                       push      eax
004ae27f 680000803f               push      0x3f800000
004ae284 680000c03f               push      0x3fc00000
004ae289 e822b76500               call      0xb099b0
004ae28e d95c240c                 fstp      dword ptr [esp + 0xc]
004ae292 83c40c                   add       esp, 0xc
004ae295 8bce                     mov       ecx, esi
004ae297 e8c4700000               call      0x4b5360
004ae29c 8bcf                     mov       ecx, edi
004ae29e e85d8c6500               call      0xb06f00
004ae2a3 2b868c190000             sub       eax, dword ptr [esi + 0x198c]
004ae2a9 3dc8000000               cmp       eax, 0xc8
004ae2ae 7616                     jbe       0x4ae2c6
004ae2b0 68000080bf               push      0xbf800000
004ae2b5 8bce                     mov       ecx, esi
004ae2b7 c7868c19000000000000     mov       dword ptr [esi + 0x198c], 0
004ae2c1 e89a700000               call      0x4b5360
004ae2c6 d98640190000             fld       dword ptr [esi + 0x1940]
004ae2cc d81d581fcc00             fcomp     dword ptr [0xcc1f58]
004ae2d2 dfe0                     fnstsw    ax
004ae2d4 f6c441                   test      ah, 0x41
004ae2d7 0f85be000000             jne       0x4ae39b
004ae2dd 8b16                     mov       edx, dword ptr [esi]
004ae2df 8b                       .byte     0x8b
