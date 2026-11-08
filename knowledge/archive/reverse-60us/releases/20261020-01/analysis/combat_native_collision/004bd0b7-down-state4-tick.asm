004bd0b7 8b16                     mov       edx, dword ptr [esi]
004bd0b9 8bce                     mov       ecx, esi
004bd0bb 8dbe14170000             lea       edi, [esi + 0x1714]
004bd0c1 ff929c000000             call      dword ptr [edx + 0x9c]
004bd0c7 8bcf                     mov       ecx, edi
004bd0c9 8bd8                     mov       ebx, eax
004bd0cb e8904ff4ff               call      0x402060
004bd0d0 3bd8                     cmp       ebx, eax
004bd0d2 7e18                     jle       0x4bd0ec
004bd0d4 8b06                     mov       eax, dword ptr [esi]
004bd0d6 8bce                     mov       ecx, esi
004bd0d8 ff909c000000             call      dword ptr [eax + 0x9c]
004bd0de 8d4dec                   lea       ecx, [ebp - 0x14]
004bd0e1 51                       push      ecx
004bd0e2 8bcf                     mov       ecx, edi
004bd0e4 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd0e7 e87474f4ff               call      0x404560
004bd0ec 8dbe20170000             lea       edi, [esi + 0x1720]
004bd0f2 8bcf                     mov       ecx, edi
004bd0f4 e8674ff4ff               call      0x402060
004bd0f9 85c0                     test      eax, eax
004bd0fb 0f85d2020000             jne       0x4bd3d3
004bd101 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd107 8b08                     mov       ecx, dword ptr [eax]
004bd109 85c9                     test      ecx, ecx
004bd10b 7503                     jne       0x4bd110
004bd10d 8d4808                   lea       ecx, [eax + 8]
004bd110 8b11                     mov       edx, dword ptr [ecx]
004bd112 6a02                     push      2
004bd114 ff5208                   call      dword ptr [edx + 8]
004bd117 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004bd11d 85c0                     test      eax, eax
004bd11f 747a                     je        0x4bd19b
004bd121 dc1d60b2cc00             fcomp     qword ptr [0xccb260]
004bd127 8b9824010000             mov       ebx, dword ptr [eax + 0x124]
004bd12d dfe0                     fnstsw    ax
004bd12f f6c441                   test      ah, 0x41
004bd132 7469                     je        0x4bd19d
004bd134 8dbee4160000             lea       edi, [esi + 0x16e4]
004bd13a 8bcf                     mov       ecx, edi
004bd13c e81f4ff4ff               call      0x402060
004bd141 3bd8                     cmp       ebx, eax
004bd143 7558                     jne       0x4bd19d
004bd145 8d8eec160000             lea       ecx, [esi + 0x16ec]
004bd14b e8104ff4ff               call      0x402060
004bd150 8bcf                     mov       ecx, edi
004bd152 8bd8                     mov       ebx, eax
004bd154 e8074ff4ff               call      0x402060
004bd159 3bc3                     cmp       eax, ebx
004bd15b 7440                     je        0x4bd19d
004bd15d 8b06                     mov       eax, dword ptr [esi]
004bd15f 8bce                     mov       ecx, esi
004bd161 ff9004010000             call      dword ptr [eax + 0x104]
004bd167 85c0                     test      eax, eax
004bd169 8bcf                     mov       ecx, edi
004bd16b 741a                     je        0x4bd187
004bd16d e8ee4ef4ff               call      0x402060
004bd172 8b16                     mov       edx, dword ptr [esi]
004bd174 40                       inc       eax
004bd175 50                       push      eax
004bd176 8bce                     mov       ecx, esi
004bd178 ff9204010000             call      dword ptr [edx + 0x104]
004bd17e 8bc8                     mov       ecx, eax
004bd180 e82b345700               call      0xa305b0
004bd185 eb16                     jmp       0x4bd19d
004bd187 e8d44ef4ff               call      0x402060
004bd18c 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004bd192 40                       inc       eax
004bd193 50                       push      eax
004bd194 e8c7d1ffff               call      0x4ba360
004bd199 eb02                     jmp       0x4bd19d
004bd19b ddd8                     fstp      st(0)
004bd19d 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd1a3 83b8ec00000004           cmp       dword ptr [eax + 0xec], 4
004bd1aa 7570                     jne       0x4bd21c
004bd1ac 8b861c170000             mov       eax, dword ptr [esi + 0x171c]
004bd1b2 83cbff                   or        ebx, 0xffffffff
004bd1b5 3bc3                     cmp       eax, ebx
004bd1b7 7463                     je        0x4bd21c
004bd1b9 8b16                     mov       edx, dword ptr [esi]
004bd1bb 8bce                     mov       ecx, esi
004bd1bd ff9294000000             call      dword ptr [edx + 0x94]
004bd1c3 39861c170000             cmp       dword ptr [esi + 0x171c], eax
004bd1c9 7451                     je        0x4bd21c
004bd1cb 8dbe0c170000             lea       edi, [esi + 0x170c]
004bd1d1 8bcf                     mov       ecx, edi
004bd1d3 e8884ef4ff               call      0x402060
004bd1d8 8bc8                     mov       ecx, eax
004bd1da b899999999               mov       eax, 0x99999999
004bd1df f7e9                     imul      ecx
004bd1e1 d1fa                     sar       edx, 1
004bd1e3 8bc2                     mov       eax, edx
004bd1e5 c1e81f                   shr       eax, 0x1f
004bd1e8 8d4dec                   lea       ecx, [ebp - 0x14]
004bd1eb 03c2                     add       eax, edx
004bd1ed 51                       push      ecx
004bd1ee 8bcf                     mov       ecx, edi
004bd1f0 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd1f3 e86873f4ff               call      0x404560
004bd1f8 8bcf                     mov       ecx, edi
004bd1fa e8614ef4ff               call      0x402060
004bd1ff 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd202 db45ec                   fild      dword ptr [ebp - 0x14]
004bd205 51                       push      ecx
004bd206 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004bd20c d91c24                   fstp      dword ptr [esp]
004bd20f 6a00                     push      0
004bd211 e82a3e0500               call      0x511040
004bd216 899e1c170000             mov       dword ptr [esi + 0x171c], ebx
004bd21c 8bce                     mov       ecx, esi
004bd21e e86deefdff               call      0x49c090
004bd223 84c0                     test      al, al
004bd225 0f84d5070000             je        0x4bda00
004bd22b 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd231 8b08                     mov       ecx, dword ptr [eax]
004bd233 85c9                     test      ecx, ecx
004bd235 7503                     jne       0x4bd23a
004bd237 8d4808                   lea       ecx, [eax + 8]
004bd23a 8b11                     mov       edx, dword ptr [ecx]
004bd23c 6a02                     push      2
004bd23e ff5208                   call      dword ptr [edx + 8]
004bd241 d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004bd247 dfe0                     fnstsw    ax
004bd249 f6c405                   test      ah, 5
004bd24c 0f8aae070000             jp        0x4bda00
004bd252 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd258 83b8f400000004           cmp       dword ptr [eax + 0xf4], 4
004bd25f 0f859b070000             jne       0x4bda00
004bd265 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
004bd26b 85c0                     test      eax, eax
004bd26d 0f858d070000             jne       0x4bda00
004bd273 8b866c160000             mov       eax, dword ptr [esi + 0x166c]
004bd279 83cbff                   or        ebx, 0xffffffff
004bd27c 3bc3                     cmp       eax, ebx
004bd27e 742d                     je        0x4bd2ad
004bd280 8d8ea0000000             lea       ecx, [esi + 0xa0]
004bd286 e8759c6400               call      0xb06f00
004bd28b 3b866c160000             cmp       eax, dword ptr [esi + 0x166c]
004bd291 7c1a                     jl        0x4bd2ad
004bd293 8b16                     mov       edx, dword ptr [esi]
004bd295 8bce                     mov       ecx, esi
004bd297 ff92dc030000             call      dword ptr [edx + 0x3dc]
004bd29d 84c0                     test      al, al
004bd29f 750c                     jne       0x4bd2ad
004bd2a1 8bce                     mov       ecx, esi
004bd2a3 e8d8d0ffff               call      0x4ba380
004bd2a8 e953070000               jmp       0x4bda00
004bd2ad 8b8e28170000             mov       ecx, dword ptr [esi + 0x1728]
004bd2b3 33ff                     xor       edi, edi
004bd2b5 b802000000               mov       eax, 2
004bd2ba 3bc8                     cmp       ecx, eax
004bd2bc 897de8                   mov       dword ptr [ebp - 0x18], edi
004bd2bf 897de4                   mov       dword ptr [ebp - 0x1c], edi
004bd2c2 897de0                   mov       dword ptr [ebp - 0x20], edi
004bd2c5 0f8590000000             jne       0x4bd35b
004bd2cb 8945fc                   mov       dword ptr [ebp - 4], eax
004bd2ce 8d45ec                   lea       eax, [ebp - 0x14]
004bd2d1 50                       push      eax
004bd2d2 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd2d5 c745ec04000000           mov       dword ptr [ebp - 0x14], 4
004bd2dc e83f9ef4ff               call      0x407120
004bd2e1 8d4dec                   lea       ecx, [ebp - 0x14]
004bd2e4 51                       push      ecx
004bd2e5 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd2e8 897dec                   mov       dword ptr [ebp - 0x14], edi
004bd2eb e8309ef4ff               call      0x407120
004bd2f0 8d55ec                   lea       edx, [ebp - 0x14]
004bd2f3 52                       push      edx
004bd2f4 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd2f7 c745ec01000000           mov       dword ptr [ebp - 0x14], 1
004bd2fe e81d9ef4ff               call      0x407120
004bd303 8d8e38170000             lea       ecx, [esi + 0x1738]
004bd309 e8524df4ff               call      0x402060
004bd30e 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd311 8d45ec                   lea       eax, [ebp - 0x14]
004bd314 50                       push      eax
004bd315 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd318 e8039ef4ff               call      0x407120
004bd31d 8d8e30170000             lea       ecx, [esi + 0x1730]
004bd323 e8384df4ff               call      0x402060
004bd328 8d4dec                   lea       ecx, [ebp - 0x14]
004bd32b 51                       push      ecx
004bd32c 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd32f 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd332 e8e99df4ff               call      0x407120
004bd337 8b16                     mov       edx, dword ptr [esi]
004bd339 57                       push      edi
004bd33a 57                       push      edi
004bd33b 6a03                     push      3
004bd33d 8d45dc                   lea       eax, [ebp - 0x24]
004bd340 50                       push      eax
004bd341 6a04                     push      4
004bd343 8bce                     mov       ecx, esi
004bd345 ff928c020000             call      dword ptr [edx + 0x28c]
004bd34b 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd34e 895dfc                   mov       dword ptr [ebp - 4], ebx
004bd351 e8fa791800               call      0x644d50
004bd356 e9a5060000               jmp       0x4bda00
004bd35b 8d4dec                   lea       ecx, [ebp - 0x14]
004bd35e 51                       push      ecx
004bd35f 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd362 c745fc03000000           mov       dword ptr [ebp - 4], 3
004bd369 c745ec04000000           mov       dword ptr [ebp - 0x14], 4
004bd370 e8ab9df4ff               call      0x407120
004bd375 8d55ec                   lea       edx, [ebp - 0x14]
004bd378 52                       push      edx
004bd379 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd37c c745ec01000000           mov       dword ptr [ebp - 0x14], 1
004bd383 e8989df4ff               call      0x407120
004bd388 8d45ec                   lea       eax, [ebp - 0x14]
004bd38b 50                       push      eax
004bd38c 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd38f 897dec                   mov       dword ptr [ebp - 0x14], edi
004bd392 e8899df4ff               call      0x407120
004bd397 8d8e0c170000             lea       ecx, [esi + 0x170c]
004bd39d e8be4cf4ff               call      0x402060
004bd3a2 8d4dec                   lea       ecx, [ebp - 0x14]
004bd3a5 51                       push      ecx
004bd3a6 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd3a9 8945ec                   mov       dword ptr [ebp - 0x14], eax
004bd3ac e86f9df4ff               call      0x407120
004bd3b1 8d8e14170000             lea       ecx, [esi + 0x1714]
004bd3b7 e8a44cf4ff               call      0x402060
004bd3bc 8bc8                     mov       ecx, eax
004bd3be b867666666               mov       eax, 0x66666667
004bd3c3 f7e9                     imul      ecx
004bd3c5 d1fa                     sar       edx, 1
004bd3c7 8bc2                     mov       eax, edx
004bd3c9 c1e81f                   shr       eax, 0x1f
004bd3cc 03c2                     add       eax, edx
004bd3ce e955ffffff               jmp       0x4bd328
004bd3d3 8bcf                     mov       ecx, edi
004bd3d5 e8864cf4ff               call      0x402060
004bd3da 83f801                   cmp       eax, 1
004bd3dd 0f8599010000             jne       0x4bd57c
004bd3e3 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd3e9 8b08                     mov       ecx, dword ptr [eax]
004bd3eb 85c9                     test      ecx, ecx
004bd3ed 7503                     jne       0x4bd3f2
004bd3ef 8d4808                   lea       ecx, [eax + 8]
004bd3f2 8b11                     mov       edx, dword ptr [ecx]
004bd3f4 6a02                     push      2
004bd3f6 ff5208                   call      dword ptr [edx + 8]
004bd3f9 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004bd3ff 85c0                     test      eax, eax
004bd401 747a                     je        0x4bd47d
004bd403 dc1d60b2cc00             fcomp     qword ptr [0xccb260]
004bd409 8b9824010000             mov       ebx, dword ptr [eax + 0x124]
004bd40f dfe0                     fnstsw    ax
004bd411 f6c441                   test      ah, 0x41
004bd414 7469                     je        0x4bd47f
004bd416 8dbef4160000             lea       edi, [esi + 0x16f4]
004bd41c 8bcf                     mov       ecx, edi
004bd41e e83d4cf4ff               call      0x402060
004bd423 3bd8                     cmp       ebx, eax
004bd425 7558                     jne       0x4bd47f
004bd427 8d8efc160000             lea       ecx, [esi + 0x16fc]
004bd42d e82e4cf4ff               call      0x402060
004bd432 8bcf                     mov       ecx, edi
004bd434 8bd8                     mov       ebx, eax
004bd436 e8254cf4ff               call      0x402060
004bd43b 3bc3                     cmp       eax, ebx
004bd43d 7440                     je        0x4bd47f
004bd43f 8b06                     mov       eax, dword ptr [esi]
004bd441 8bce                     mov       ecx, esi
004bd443 ff9004010000             call      dword ptr [eax + 0x104]
004bd449 85c0                     test      eax, eax
004bd44b 8bcf                     mov       ecx, edi
004bd44d 741a                     je        0x4bd469
004bd44f e80c4cf4ff               call      0x402060
004bd454 8b16                     mov       edx, dword ptr [esi]
004bd456 40                       inc       eax
004bd457 50                       push      eax
004bd458 8bce                     mov       ecx, esi
004bd45a ff9204010000             call      dword ptr [edx + 0x104]
004bd460 8bc8                     mov       ecx, eax
004bd462 e849315700               call      0xa305b0
004bd467 eb16                     jmp       0x4bd47f
004bd469 e8f24bf4ff               call      0x402060
004bd46e 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004bd474 40                       inc       eax
004bd475 50                       push      eax
004bd476 e8e5ceffff               call      0x4ba360
004bd47b eb02                     jmp       0x4bd47f
004bd47d ddd8                     fstp      st(0)
004bd47f 8bce                     mov       ecx, esi
004bd481 e80aecfdff               call      0x49c090
004bd486 84c0                     test      al, al
004bd488 0f8472050000             je        0x4bda00
004bd48e 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004bd494 8b08                     mov       ecx, dword ptr [eax]
004bd496 85c9                     test      ecx, ecx
004bd498 7503                     jne       0x4bd49d
004bd49a 8d4808                   lea       ecx, [eax + 8]
004bd49d 8b01                     mov       eax, dword ptr [ecx]
004bd49f 6a02                     push      2
004bd4a1 ff5008                   call      dword ptr [eax + 8]
004bd4a4 d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004bd4aa dfe0                     fnstsw    ax
004bd4ac f6c405                   test      ah, 5
004bd4af 0f8a4b050000             jp        0x4bda00
004bd4b5 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004bd4bb 83b9f400000004           cmp       dword ptr [ecx + 0xf4], 4
004bd4c2 0f8538050000             jne       0x4bda00
004bd4c8 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
004bd4ce 85c0                     test      eax, eax
004bd4d0 0f852a050000             jne       0x4bda00
004bd4d6 83be6c160000ff           cmp       dword ptr [esi + 0x166c], -1
004bd4dd 742d                     je        0x4bd50c
004bd4df 8d8ea0000000             lea       ecx, [esi + 0xa0]
004bd4e5 e8169a6400               call      0xb06f00
004bd4ea 3b866c160000             cmp       eax, dword ptr [esi + 0x166c]
004bd4f0 7c1a                     jl        0x4bd50c
004bd4f2 8b16                     mov       edx, dword ptr [esi]
004bd4f4 8bce                     mov       ecx, esi
004bd4f6 ff92dc030000             call      dword ptr [edx + 0x3dc]
004bd4fc 84c0                     test      al, al
004bd4fe 750c                     jne       0x4bd50c
004bd500 8bce                     mov       ecx, esi
004bd502 e879ceffff               call      0x4ba380
004bd507 e9f4040000               jmp       0x4bda00
004bd50c 33ff                     xor       edi, edi
004bd50e 897de0                   mov       dword ptr [ebp - 0x20], edi
004bd511 897de4                   mov       dword ptr [ebp - 0x1c], edi
004bd514 897de8                   mov       dword ptr [ebp - 0x18], edi
004bd517 8d45ec                   lea       eax, [ebp - 0x14]
004bd51a bb04000000               mov       ebx, 4
004bd51f 50                       push      eax
004bd520 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd523 895dfc                   mov       dword ptr [ebp - 4], ebx
004bd526 895dec                   mov       dword ptr [ebp - 0x14], ebx
004bd529 e8f29bf4ff               call      0x407120
004bd52e 8d4dec                   lea       ecx, [ebp - 0x14]
004bd531 51                       push      ecx
004bd532 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd535 c745ec02000000           mov       dword ptr [ebp - 0x14], 2
004bd53c e8df9bf4ff               call      0x407120
004bd541 8d55ec                   lea       edx, [ebp - 0x14]
004bd544 52                       push      edx
004bd545 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd548 897dec                   mov       dword ptr [ebp - 0x14], edi
004bd54b e8d09bf4ff               call      0x407120
004bd550 8d45ec                   lea       eax, [ebp - 0x14]
004bd553 50                       push      eax
004bd554 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd557 897dec                   mov       dword ptr [ebp - 0x14], edi
004bd55a e8c19bf4ff               call      0x407120
004bd55f 8d4dec                   lea       ecx, [ebp - 0x14]
004bd562 51                       push      ecx
004bd563 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd566 897dec                   mov       dword ptr [ebp - 0x14], edi
004bd569 e8b29bf4ff               call      0x407120
004bd56e 57                       push      edi
004bd56f 57                       push      edi
004bd570 6a03                     push      3
004bd572 8d45dc                   lea       eax, [ebp - 0x24]
004bd575 50                       push      eax
004bd576 53                       push      ebx
004bd577 e97b030000               jmp       0x4bd8f7
004bd57c 8bcf                     mov       ecx, edi
004bd57e e8dd4af4ff               call      0x402060
004bd583 83f802                   cmp       eax, 2
004bd586 0f8574040000             jne       0x4bda00
004bd58c 8bce                     mov       ecx, esi
004bd58e e8fdeafdff               call      0x49c090
004bd593 84c0                     test      al, al
004bd595 0f8465040000             je        0x4bda00
004bd59b 8b16                     mov       edx, dword ptr [esi]
004bd59d 8bce                     mov       ecx, esi
004bd59f ff92dc030000             call      dword ptr [edx + 0x3dc]
004bd5a5 84c0                     test      al, al
004bd5a7 744e                     je        0x4bd5f7
004bd5a9 8b86a0040000             mov       eax, dword ptr [esi + 0x4a0]
004bd5af 83f805                   cmp       eax, 5
004bd5b2 7443                     je        0x4bd5f7
004bd5b4 83f804                   cmp       eax, 4
004bd5b7 743e                     je        0x4bd5f7
004bd5b9 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
004bd5bf 33ff                     xor       edi, edi
004bd5c1 3bc7                     cmp       eax, edi
004bd5c3 7532                     jne       0x4bd5f7
004bd5c5 897de0                   mov       dword ptr [ebp - 0x20], edi
004bd5c8 897de4                   mov       dword ptr [ebp - 0x1c], edi
004bd5cb 897de8                   mov       dword ptr [ebp - 0x18], edi
004bd5ce 8d45ec                   lea       eax, [ebp - 0x14]
004bd5d1 50                       push      eax
004bd5d2 8d4ddc                   lea       ecx, [ebp - 0x24]
004bd5d5 c745fc05000000           mov       dword ptr [ebp - 4], 5
004bd5dc c745ec01000000           mov       dword ptr [ebp - 0x14], 1
004bd5e3 e8389bf4ff               call      0x407120
004bd5e8 57                       push      edi
004bd5e9 57                       push      edi
004bd5ea 6a03                     push      3
004bd5ec 8d45dc                   lea       eax, [ebp - 0x24]
004bd5ef 50                       push      eax
004bd5f0 6a05                     push      5
004bd5f2 e900030000               jmp       0x4bd8f7
004bd5f7 8b16                     mov       edx, dword ptr [esi]
004bd5f9 8bce                     mov       ecx, esi
004bd5fb ff92f4000000             call      dword ptr [edx + 0xf4]
004bd601 85c0                     test      eax, eax
004bd603 7414                     je        0x4bd619
004bd605 8b06                     mov       eax, dword ptr [esi]
004bd607 8bce                     mov       ecx, esi
004bd609 ff90f4000000             call      dword ptr [eax + 0xf4]
004bd60f 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
004bd615 84c9                     test      cl, cl
004bd617 7524                     jne       0x4bd63d
004bd619 83be6c160000ff           cmp       dword ptr [esi + 0x166c], -1
004bd620 0f84da030000             je        0x4bda00
004bd626 8d8ea0000000             lea       ecx, [esi + 0xa0]
004bd62c e8cf986400               call      0xb06f00
004bd631 3b866c160000             cmp       eax, dword ptr [esi + 0x166c]
004bd637 0f8cc3030000             jl        0x4bda00
004bd63d 8bce                     mov       ecx, esi
004bd63f e83ccdffff               call      0x4ba380
004bd644 e9b7030000               jmp       0x4bda00
