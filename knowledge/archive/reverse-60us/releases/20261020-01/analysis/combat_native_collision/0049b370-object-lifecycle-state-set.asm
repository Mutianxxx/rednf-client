0049b370 55                       push      ebp
0049b371 8bec                     mov       ebp, esp
0049b373 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049b376 53                       push      ebx
0049b377 8b5d08                   mov       ebx, dword ptr [ebp + 8]
0049b37a 85db                     test      ebx, ebx
0049b37c 56                       push      esi
0049b37d 57                       push      edi
0049b37e 8bf1                     mov       esi, ecx
0049b380 7406                     je        0x49b388
0049b382 85c0                     test      eax, eax
0049b384 7502                     jne       0x49b388
0049b386 33db                     xor       ebx, ebx
0049b388 85db                     test      ebx, ebx
0049b38a 8bbeb0010000             mov       edi, dword ptr [esi + 0x1b0]
0049b390 897d08                   mov       dword ptr [ebp + 8], edi
0049b393 899eb0010000             mov       dword ptr [esi + 0x1b0], ebx
0049b399 7417                     je        0x49b3b2
0049b39b 8d4e20                   lea       ecx, [esi + 0x20]
0049b39e 8986b4010000             mov       dword ptr [esi + 0x1b4], eax
0049b3a4 e857bb6600               call      0xb06f00
0049b3a9 2b4510                   sub       eax, dword ptr [ebp + 0x10]
0049b3ac 8986b8010000             mov       dword ptr [esi + 0x1b8], eax
0049b3b2 3bfb                     cmp       edi, ebx
0049b3b4 0f84bc020000             je        0x49b676
0049b3ba 83ff01                   cmp       edi, 1
0049b3bd 0f8dfb000000             jge       0x49b4be
0049b3c3 83fb01                   cmp       ebx, 1
0049b3c6 0f8cdd010000             jl        0x49b5a9
0049b3cc 8bbe04010000             mov       edi, dword ptr [esi + 0x104]
0049b3d2 85ff                     test      edi, edi
0049b3d4 c686bc01000000           mov       byte ptr [esi + 0x1bc], 0
0049b3db 7426                     je        0x49b403
0049b3dd 8b8f88010000             mov       ecx, dword ptr [edi + 0x188]
0049b3e3 85c9                     test      ecx, ecx
0049b3e5 7407                     je        0x49b3ee
0049b3e7 e854daffff               call      0x498e40
0049b3ec eb06                     jmp       0x49b3f4
0049b3ee 8a8739010000             mov       al, byte ptr [edi + 0x139]
0049b3f4 6a01                     push      1
0049b3f6 8bcf                     mov       ecx, edi
0049b3f8 8886bc010000             mov       byte ptr [esi + 0x1bc], al
0049b3fe e80dcd5800               call      0xa28110
0049b403 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049b409 85c9                     test      ecx, ecx
0049b40b 742e                     je        0x49b43b
0049b40d e89e1b5900               call      0xa2cfb0
0049b412 85c0                     test      eax, eax
0049b414 7425                     je        0x49b43b
0049b416 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049b41c e88f1b5900               call      0xa2cfb0
0049b421 8bc8                     mov       ecx, eax
0049b423 e818daffff               call      0x498e40
0049b428 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049b42e 6a01                     push      1
0049b430 8886bc010000             mov       byte ptr [esi + 0x1bc], al
0049b436 e8f5215900               call      0xa2d630
0049b43b 8b06                     mov       eax, dword ptr [esi]
0049b43d 6a11                     push      0x11
0049b43f 8bce                     mov       ecx, esi
0049b441 ff502c                   call      dword ptr [eax + 0x2c]
0049b444 84c0                     test      al, al
0049b446 8bce                     mov       ecx, esi
0049b448 740a                     je        0x49b454
0049b44a 8b16                     mov       edx, dword ptr [esi]
0049b44c ff9254040000             call      dword ptr [edx + 0x454]
0049b452 eb25                     jmp       0x49b479
0049b454 8b06                     mov       eax, dword ptr [esi]
0049b456 6a41                     push      0x41
0049b458 ff502c                   call      dword ptr [eax + 0x2c]
0049b45b 84c0                     test      al, al
0049b45d 8bce                     mov       ecx, esi
0049b45f 7510                     jne       0x49b471
0049b461 8b06                     mov       eax, dword ptr [esi]
0049b463 6881000000               push      0x81
0049b468 ff502c                   call      dword ptr [eax + 0x2c]
0049b46b 84c0                     test      al, al
0049b46d 7411                     je        0x49b480
0049b46f 8bce                     mov       ecx, esi
0049b471 8b16                     mov       edx, dword ptr [esi]
0049b473 ff9244030000             call      dword ptr [edx + 0x344]
0049b479 8bc8                     mov       ecx, eax
0049b47b e860bb6600               call      0xb06fe0
0049b480 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049b486 6a01                     push      1
0049b488 e8a3590700               call      0x510e30
0049b48d 8d4e60                   lea       ecx, [esi + 0x60]
0049b490 e84bbb6600               call      0xb06fe0
0049b495 8b860c010000             mov       eax, dword ptr [esi + 0x10c]
0049b49b 8b38                     mov       edi, dword ptr [eax]
0049b49d 3bf8                     cmp       edi, eax
0049b49f 0f8404010000             je        0x49b5a9
0049b4a5 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049b4a8 6a01                     push      1
0049b4aa e861cc5800               call      0xa28110
0049b4af 8b3f                     mov       edi, dword ptr [edi]
0049b4b1 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049b4b7 75ec                     jne       0x49b4a5
0049b4b9 e9eb000000               jmp       0x49b5a9
0049b4be 83fb01                   cmp       ebx, 1
0049b4c1 0f8de2000000             jge       0x49b5a9
0049b4c7 8a86bc010000             mov       al, byte ptr [esi + 0x1bc]
0049b4cd 84c0                     test      al, al
0049b4cf 752c                     jne       0x49b4fd
0049b4d1 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049b4d7 85c9                     test      ecx, ecx
0049b4d9 7407                     je        0x49b4e2
0049b4db 6a00                     push      0
0049b4dd e82ecc5800               call      0xa28110
0049b4e2 8a86bc010000             mov       al, byte ptr [esi + 0x1bc]
0049b4e8 84c0                     test      al, al
0049b4ea 7511                     jne       0x49b4fd
0049b4ec 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049b4f2 85c9                     test      ecx, ecx
0049b4f4 7407                     je        0x49b4fd
0049b4f6 6a00                     push      0
0049b4f8 e833215900               call      0xa2d630
0049b4fd 8b06                     mov       eax, dword ptr [esi]
0049b4ff 6a11                     push      0x11
0049b501 8bce                     mov       ecx, esi
0049b503 ff502c                   call      dword ptr [eax + 0x2c]
0049b506 84c0                     test      al, al
0049b508 8bce                     mov       ecx, esi
0049b50a 740a                     je        0x49b516
0049b50c 8b16                     mov       edx, dword ptr [esi]
0049b50e ff9254040000             call      dword ptr [edx + 0x454]
0049b514 eb25                     jmp       0x49b53b
0049b516 8b06                     mov       eax, dword ptr [esi]
0049b518 6a41                     push      0x41
0049b51a ff502c                   call      dword ptr [eax + 0x2c]
0049b51d 84c0                     test      al, al
0049b51f 8bce                     mov       ecx, esi
0049b521 7510                     jne       0x49b533
0049b523 8b06                     mov       eax, dword ptr [esi]
0049b525 6881000000               push      0x81
0049b52a ff502c                   call      dword ptr [eax + 0x2c]
0049b52d 84c0                     test      al, al
0049b52f 7411                     je        0x49b542
0049b531 8bce                     mov       ecx, esi
0049b533 8b16                     mov       edx, dword ptr [esi]
0049b535 ff9244030000             call      dword ptr [edx + 0x344]
0049b53b 8bc8                     mov       ecx, eax
0049b53d e83ebb6600               call      0xb07080
0049b542 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049b548 6a00                     push      0
0049b54a e8e1580700               call      0x510e30
0049b54f 8d4e60                   lea       ecx, [esi + 0x60]
0049b552 e829bb6600               call      0xb07080
0049b557 8b06                     mov       eax, dword ptr [esi]
0049b559 6a01                     push      1
0049b55b 8bce                     mov       ecx, esi
0049b55d ff502c                   call      dword ptr [eax + 0x2c]
0049b560 84c0                     test      al, al
0049b562 7425                     je        0x49b589
0049b564 68a4eacc00               push      0xcceaa4
0049b569 b944070001               mov       ecx, 0x1000744
0049b56e e8cd35f7ff               call      0x40eb40
0049b573 8d8e08020000             lea       ecx, [esi + 0x208]
0049b579 e8727b5b00               call      0xa530f0
0049b57e 50                       push      eax
0049b57f b944070001               mov       ecx, 0x1000744
0049b584 e8e735f7ff               call      0x40eb70
0049b589 8b860c010000             mov       eax, dword ptr [esi + 0x10c]
0049b58f 8b38                     mov       edi, dword ptr [eax]
0049b591 3bf8                     cmp       edi, eax
0049b593 7414                     je        0x49b5a9
0049b595 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049b598 6a00                     push      0
0049b59a e871cb5800               call      0xa28110
0049b59f 8b3f                     mov       edi, dword ptr [edi]
0049b5a1 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049b5a7 75ec                     jne       0x49b595
0049b5a9 837d0802                 cmp       dword ptr [ebp + 8], 2
0049b5ad 7d6c                     jge       0x49b61b
0049b5af 83fb02                   cmp       ebx, 2
0049b5b2 0f8cbe000000             jl        0x49b676
0049b5b8 8b16                     mov       edx, dword ptr [esi]
0049b5ba 6a11                     push      0x11
0049b5bc 8bce                     mov       ecx, esi
0049b5be ff522c                   call      dword ptr [edx + 0x2c]
0049b5c1 84c0                     test      al, al
0049b5c3 7444                     je        0x49b609
0049b5c5 8b06                     mov       eax, dword ptr [esi]
0049b5c7 6a01                     push      1
0049b5c9 8bce                     mov       ecx, esi
0049b5cb ff90c4030000             call      dword ptr [eax + 0x3c4]
0049b5d1 8bc8                     mov       ecx, eax
0049b5d3 e8880d0000               call      0x49c360
0049b5d8 33ff                     xor       edi, edi
0049b5da 8d9b00000000             lea       ebx, [ebx]
0049b5e0 8b16                     mov       edx, dword ptr [esi]
0049b5e2 57                       push      edi
0049b5e3 8bce                     mov       ecx, esi
0049b5e5 ff9210040000             call      dword ptr [edx + 0x410]
0049b5eb 84c0                     test      al, al
0049b5ed 7414                     je        0x49b603
0049b5ef 8b06                     mov       eax, dword ptr [esi]
0049b5f1 57                       push      edi
0049b5f2 8bce                     mov       ecx, esi
0049b5f4 ff900c040000             call      dword ptr [eax + 0x40c]
0049b5fa 8b10                     mov       edx, dword ptr [eax]
0049b5fc 6a01                     push      1
0049b5fe 8bc8                     mov       ecx, eax
