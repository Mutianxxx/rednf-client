005f6260 55                       push      ebp
005f6261 8bec                     mov       ebp, esp
005f6263 51                       push      ecx
005f6264 53                       push      ebx
005f6265 33db                     xor       ebx, ebx
005f6267 56                       push      esi
005f6268 8bf1                     mov       esi, ecx
005f626a c786e400000021040000     mov       dword ptr [esi + 0xe4], 0x421
005f6274 899e7c080000             mov       dword ptr [esi + 0x87c], ebx
005f627a 899e84080000             mov       dword ptr [esi + 0x884], ebx
005f6280 57                       push      edi
005f6281 899ee4080000             mov       dword ptr [esi + 0x8e4], ebx
005f6287 899ee8080000             mov       dword ptr [esi + 0x8e8], ebx
005f628d 899eec080000             mov       dword ptr [esi + 0x8ec], ebx
005f6293 8dbef0080000             lea       edi, [esi + 0x8f0]
005f6299 c745fc03000000           mov       dword ptr [ebp - 4], 3
005f62a0 53                       push      ebx
005f62a1 8bcf                     mov       ecx, edi
005f62a3 e8f8d54500               call      0xa538a0
005f62a8 8b45fc                   mov       eax, dword ptr [ebp - 4]
005f62ab 83c704                   add       edi, 4
005f62ae 48                       dec       eax
005f62af 8945fc                   mov       dword ptr [ebp - 4], eax
005f62b2 75ec                     jne       0x5f62a0
005f62b4 8b86d4080000             mov       eax, dword ptr [esi + 0x8d4]
005f62ba 3bc3                     cmp       eax, ebx
005f62bc 7409                     je        0x5f62c7
005f62be 50                       push      eax
005f62bf e8199d6000               call      0xbfffdd
005f62c4 83c404                   add       esp, 4
005f62c7 899ed4080000             mov       dword ptr [esi + 0x8d4], ebx
005f62cd 899ed8080000             mov       dword ptr [esi + 0x8d8], ebx
005f62d3 899edc080000             mov       dword ptr [esi + 0x8dc], ebx
005f62d9 c786e008000004000000     mov       dword ptr [esi + 0x8e0], 4
005f62e3 889e88080000             mov       byte ptr [esi + 0x888], bl
005f62e9 899e78080000             mov       dword ptr [esi + 0x878], ebx
005f62ef 899e74080000             mov       dword ptr [esi + 0x874], ebx
005f62f5 899e70080000             mov       dword ptr [esi + 0x870], ebx
005f62fb 899e3c090000             mov       dword ptr [esi + 0x93c], ebx
005f6301 889e40090000             mov       byte ptr [esi + 0x940], bl
005f6307 889e89080000             mov       byte ptr [esi + 0x889], bl
005f630d 899e44090000             mov       dword ptr [esi + 0x944], ebx
005f6313 889e41090000             mov       byte ptr [esi + 0x941], bl
005f6319 8b8630090000             mov       eax, dword ptr [esi + 0x930]
005f631f 3bc3                     cmp       eax, ebx
005f6321 7409                     je        0x5f632c
005f6323 50                       push      eax
005f6324 e8b49c6000               call      0xbfffdd
005f6329 83c404                   add       esp, 4
005f632c 899e30090000             mov       dword ptr [esi + 0x930], ebx
005f6332 899e34090000             mov       dword ptr [esi + 0x934], ebx
005f6338 899e38090000             mov       dword ptr [esi + 0x938], ebx
005f633e 889e48090000             mov       byte ptr [esi + 0x948], bl
005f6344 889e49090000             mov       byte ptr [esi + 0x949], bl
005f634a 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
005f6350 8b5144                   mov       edx, dword ptr [ecx + 0x44]
005f6353 8b86f0070000             mov       eax, dword ptr [esi + 0x7f0]
005f6359 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
005f635f 8d0482                   lea       eax, [edx + eax*4]
005f6362 8bc8                     mov       ecx, eax
005f6364 33cb                     xor       ecx, ebx
005f6366 83f103                   xor       ecx, 3
005f6369 8908                     mov       dword ptr [eax], ecx
005f636b 8b96f0070000             mov       edx, dword ptr [esi + 0x7f0]
005f6371 a1d8012101               mov       eax, dword ptr [0x12101d8]
005f6376 8b4848                   mov       ecx, dword ptr [eax + 0x48]
005f6379 8b35dc012101             mov       esi, dword ptr [0x12101dc]
005f637f 8d0491                   lea       eax, [ecx + edx*4]
005f6382 8bd0                     mov       edx, eax
005f6384 33d6                     xor       edx, esi
005f6386 5f                       pop       edi
005f6387 83f203                   xor       edx, 3
005f638a 5e                       pop       esi
005f638b 8910                     mov       dword ptr [eax], edx
005f638d 5b                       pop       ebx
005f638e 8be5                     mov       esp, ebp
005f6390 5d                       pop       ebp
005f6391 c3                       ret       
005f6392 cc                       int3      
005f6393 cc                       int3      
005f6394 cc                       int3      
005f6395 cc                       int3      
005f6396 cc                       int3      
005f6397 cc                       int3      
005f6398 cc                       int3      
005f6399 cc                       int3      
005f639a cc                       int3      
005f639b cc                       int3      
005f639c cc                       int3      
005f639d cc                       int3      
005f639e cc                       int3      
005f639f cc                       int3      
005f63a0 55                       push      ebp
005f63a1 8bec                     mov       ebp, esp
005f63a3 6aff                     push      -1
005f63a5 68de75c600               push      0xc675de
005f63aa 64a100000000             mov       eax, dword ptr fs:[0]
005f63b0 50                       push      eax
005f63b1 64892500000000           mov       dword ptr fs:[0], esp
005f63b8 83ec14                   sub       esp, 0x14
005f63bb 53                       push      ebx
005f63bc 33db                     xor       ebx, ebx
005f63be 56                       push      esi
005f63bf 57                       push      edi
005f63c0 8bf1                     mov       esi, ecx
005f63c2 895de4                   mov       dword ptr [ebp - 0x1c], ebx
005f63c5 895de8                   mov       dword ptr [ebp - 0x18], ebx
005f63c8 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f63cb 8d45e0                   lea       eax, [ebp - 0x20]
005f63ce 50                       push      eax
005f63cf 6a32                     push      0x32
005f63d1 6a32                     push      0x32
005f63d3 895dfc                   mov       dword ptr [ebp - 4], ebx
005f63d6 e8b571efff               call      0x4ed590
005f63db 3bc3                     cmp       eax, ebx
005f63dd 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f63e0 7411                     je        0x5f63f3
005f63e2 8b3e                     mov       edi, dword ptr [esi]
005f63e4 53                       push      ebx
005f63e5 8bce                     mov       ecx, esi
005f63e7 ff577c                   call      dword ptr [edi + 0x7c]
005f63ea 50                       push      eax
005f63eb 8bce                     mov       ecx, esi
005f63ed ff97f0000000             call      dword ptr [edi + 0xf0]
005f63f3 8b16                     mov       edx, dword ptr [esi]
005f63f5 8bce                     mov       ecx, esi
005f63f7 ff92f4000000             call      dword ptr [edx + 0xf4]
005f63fd 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
005f6403 84c9                     test      cl, cl
005f6405 746e                     je        0x5f6475
005f6407 8bce                     mov       ecx, esi
005f6409 e8825ceaff               call      0x49c090
005f640e 84c0                     test      al, al
005f6410 7451                     je        0x5f6463
005f6412 8a864c090000             mov       al, byte ptr [esi + 0x94c]
005f6418 84c0                     test      al, al
005f641a 7547                     jne       0x5f6463
005f641c 53                       push      ebx
005f641d e8ce7c2b00               call      0x8ae0f0
005f6422 99                       cdq       
005f6423 b905000000               mov       ecx, 5
005f6428 f7f9                     idiv      ecx
005f642a 83c404                   add       esp, 4
005f642d 3bd3                     cmp       edx, ebx
005f642f 756f                     jne       0x5f64a0
005f6431 686c19d500               push      0xd5196c
005f6436 8b16                     mov       edx, dword ptr [esi]
005f6438 8bce                     mov       ecx, esi
005f643a ff92c0020000             call      dword ptr [edx + 0x2c0]
005f6440 53                       push      ebx
005f6441 53                       push      ebx
005f6442 8b16                     mov       edx, dword ptr [esi]
005f6444 53                       push      ebx
005f6445 53                       push      ebx
005f6446 53                       push      ebx
005f6447 6a04                     push      4
005f6449 53                       push      ebx
005f644a 53                       push      ebx
005f644b 53                       push      ebx
005f644c 53                       push      ebx
005f644d 50                       push      eax
005f644e 53                       push      ebx
005f644f 6845770000               push      0x7745
005f6454 8bce                     mov       ecx, esi
005f6456 ff92b8020000             call      dword ptr [edx + 0x2b8]
005f645c c6864c09000001           mov       byte ptr [esi + 0x94c], 1
005f6463 8b3e                     mov       edi, dword ptr [esi]
005f6465 6a01                     push      1
005f6467 8bce                     mov       ecx, esi
005f6469 ff577c                   call      dword ptr [edi + 0x7c]
005f646c 50                       push      eax
005f646d 8bce                     mov       ecx, esi
005f646f ff97f0000000             call      dword ptr [edi + 0xf0]
005f6475 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
005f6478 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
005f647b 3bd3                     cmp       edx, ebx
005f647d 0f95c3                   setne     bl
005f6480 85c0                     test      eax, eax
005f6482 7409                     je        0x5f648d
005f6484 50                       push      eax
005f6485 e8539b6000               call      0xbfffdd
005f648a 83c404                   add       esp, 4
005f648d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f6490 5f                       pop       edi
005f6491 5e                       pop       esi
005f6492 8ac3                     mov       al, bl
005f6494 5b                       pop       ebx
005f6495 64890d00000000           mov       dword ptr fs:[0], ecx
005f649c 8be5                     mov       esp, ebp
005f649e 5d                       pop       ebp
005f649f c3                       ret       
005f64a0 83fa01                   cmp       edx, 1
005f64a3 7511                     jne       0x5f64b6
005f64a5 8b06                     mov       eax, dword ptr [esi]
005f64a7 683019d500               push      0xd51930
005f64ac 8bce                     mov       ecx, esi
005f64ae ff90c0020000             call      dword ptr [eax + 0x2c0]
005f64b4 eb8a                     jmp       0x5f6440
005f64b6 83fa02                   cmp       edx, 2
005f64b9 750a                     jne       0x5f64c5
005f64bb 68f818d500               push      0xd518f8
005f64c0 e971ffffff               jmp       0x5f6436
005f64c5 83fa03                   cmp       edx, 3
005f64c8 7514                     jne       0x5f64de
005f64ca 8b06                     mov       eax, dword ptr [esi]
005f64cc 68c018d500               push      0xd518c0
005f64d1 8bce                     mov       ecx, esi
005f64d3 ff90c0020000             call      dword ptr [eax + 0x2c0]
005f64d9 e962ffffff               jmp       0x5f6440
005f64de 83fa04                   cmp       edx, 4
005f64e1 750a                     jne       0x5f64ed
005f64e3 688018d500               push      0xd51880
005f64e8 e949ffffff               jmp       0x5f6436
005f64ed 83fa05                   cmp       edx, 5
005f64f0 7514                     jne       0x5f6506
005f64f2 8b06                     mov       eax, dword ptr [esi]
005f64f4 684418d500               push      0xd51844
005f64f9 8bce                     mov       ecx, esi
005f64fb ff90c0020000             call      dword ptr [eax + 0x2c0]
005f6501 e93affffff               jmp       0x5f6440
005f6506 83fa06                   cmp       edx, 6
005f6509 750a                     jne       0x5f6515
005f650b 681018d500               push      0xd51810
005f6510 e921ffffff               jmp       0x5f6436
005f6515 83fa07                   cmp       edx, 7
005f6518 68e017d500               push      0xd517e0
005f651d 0f8513ffffff             jne       0x5f6436
005f6523 8b06                     mov       eax, dword ptr [esi]
005f6525 8bce                     mov       ecx, esi
005f6527 ff90c0020000             call      dword ptr [eax + 0x2c0]
005f652d e90effffff               jmp       0x5f6440
005f6532 cc                       int3      
005f6533 cc                       int3      
005f6534 cc                       int3      
005f6535 cc                       int3      
005f6536 cc                       int3      
005f6537 cc                       int3      
005f6538 cc                       int3      
005f6539 cc                       int3      
005f653a cc                       int3      
005f653b cc                       int3      
005f653c cc                       int3      
005f653d cc                       int3      
005f653e cc                       int3      
005f653f cc                       int3      
005f6540 55                       push      ebp
005f6541 8bec                     mov       ebp, esp
005f6543 8b4508                   mov       eax, dword ptr [ebp + 8]
005f6546 50                       push      eax
005f6547 e8c4f1ffff               call      0x5f5710
005f654c 84c0                     test      al, al
005f654e 7406                     je        0x5f6556
005f6550 32c0                     xor       al, al
005f6552 5d                       pop       ebp
005f6553 c20400                   ret       4
005f6556 8d5508                   lea       edx, [ebp + 8]
005f6559 52                       push      edx
005f655a 81c1d0080000             add       ecx, 0x8d0
005f6560 e86b16f1ff               call      0x507bd0
005f6565 b001                     mov       al, 1
005f6567 5d                       pop       ebp
005f6568 c20400                   ret       4
005f656b cc                       int3      
005f656c cc                       int3      
005f656d cc                       int3      
005f656e cc                       int3      
005f656f cc                       int3      
005f6570 55                       push      ebp
005f6571 8bec                     mov       ebp, esp
005f6573 83ec08                   sub       esp, 8
005f6576 8b4508                   mov       eax, dword ptr [ebp + 8]
005f6579 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f657c 8945f8                   mov       dword ptr [ebp - 8], eax
005f657f 8d45f8                   lea       eax, [ebp - 8]
005f6582 50                       push      eax
005f6583 81c1fc080000             add       ecx, 0x8fc
005f6589 8955fc                   mov       dword ptr [ebp - 4], edx
005f658c e8efd8ffff               call      0x5f3e80
005f6591 8be5                     mov       esp, ebp
005f6593 5d                       pop       ebp
005f6594 c20800                   ret       8
005f6597 cc                       int3      
005f6598 cc                       int3      
005f6599 cc                       int3      
005f659a cc                       int3      
005f659b cc                       int3      
005f659c cc                       int3      
005f659d cc                       int3      
005f659e cc                       int3      
005f659f cc                       int3      
005f65a0 55                       push      ebp
005f65a1 8bec                     mov       ebp, esp
005f65a3 83ec08                   sub       esp, 8
005f65a6 8b4508                   mov       eax, dword ptr [ebp + 8]
005f65a9 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f65ac 8945f8                   mov       dword ptr [ebp - 8], eax
005f65af 8d45f8                   lea       eax, [ebp - 8]
005f65b2 50                       push      eax
005f65b3 81c10c090000             add       ecx, 0x90c
005f65b9 8955fc                   mov       dword ptr [ebp - 4], edx
005f65bc e8af0be1ff               call      0x407170
005f65c1 8be5                     mov       esp, ebp
005f65c3 5d                       pop       ebp
005f65c4 c20800                   ret       8
005f65c7 cc                       int3      
005f65c8 cc                       int3      
005f65c9 cc                       int3      
005f65ca cc                       int3      
005f65cb cc                       int3      
005f65cc cc                       int3      
005f65cd cc                       int3      
005f65ce cc                       int3      
005f65cf cc                       int3      
005f65d0 55                       push      ebp
005f65d1 8bec                     mov       ebp, esp
005f65d3 83ec0c                   sub       esp, 0xc
005f65d6 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f65d9 8b4508                   mov       eax, dword ptr [ebp + 8]
005f65dc 8955f8                   mov       dword ptr [ebp - 8], edx
005f65df 8945f4                   mov       dword ptr [ebp - 0xc], eax
005f65e2 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f65e5 8d55f4                   lea       edx, [ebp - 0xc]
005f65e8 52                       push      edx
005f65e9 81c11c090000             add       ecx, 0x91c
005f65ef 8945fc                   mov       dword ptr [ebp - 4], eax
005f65f2 e8f9160000               call      0x5f7cf0
005f65f7 8be5                     mov       esp, ebp
005f65f9 5d                       pop       ebp
005f65fa c20c00                   ret       0xc
005f65fd cc                       int3      
005f65fe cc                       int3      
005f65ff cc                       int3      
005f6600 55                       push      ebp
005f6601 8bec                     mov       ebp, esp
005f6603 83ec10                   sub       esp, 0x10
005f6606 8b4508                   mov       eax, dword ptr [ebp + 8]
005f6609 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f660c 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f660f 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f6612 8945f8                   mov       dword ptr [ebp - 8], eax
005f6615 8955f4                   mov       dword ptr [ebp - 0xc], edx
005f6618 8b5514                   mov       edx, dword ptr [ebp + 0x14]
005f661b 8d45f0                   lea       eax, [ebp - 0x10]
005f661e 50                       push      eax
005f661f 81c12c090000             add       ecx, 0x92c
005f6625 8955fc                   mov       dword ptr [ebp - 4], edx
005f6628 e843170000               call      0x5f7d70
005f662d 8be5                     mov       esp, ebp
005f662f 5d                       pop       ebp
005f6630 c21000                   ret       0x10
005f6633 cc                       int3      
005f6634 cc                       int3      
005f6635 cc                       int3      
005f6636 cc                       int3      
005f6637 cc                       int3      
005f6638 cc                       int3      
005f6639 cc                       int3      
005f663a cc                       int3      
005f663b cc                       int3      
005f663c cc                       int3      
005f663d cc                       int3      
005f663e cc                       int3      
005f663f cc                       int3      
005f6640 55                       push      ebp
005f6641 8bec                     mov       ebp, esp
005f6643 6aff                     push      -1
005f6645 68f375c600               push      0xc675f3
005f664a 64a100000000             mov       eax, dword ptr fs:[0]
005f6650 50                       push      eax
005f6651 64892500000000           mov       dword ptr fs:[0], esp
005f6658 83ec08                   sub       esp, 8
005f665b 53                       push      ebx
005f665c 56                       push      esi
005f665d 8bf1                     mov       esi, ecx
005f665f 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f6665 85c9                     test      ecx, ecx
005f6667 0f84f3000000             je        0x5f6760
005f666d 8b8650050000             mov       eax, dword ptr [esi + 0x550]
005f6673 2bc1                     sub       eax, ecx
005f6675 c1f802                   sar       eax, 2
005f6678 83f805                   cmp       eax, 5
005f667b 0f82df000000             jb        0x5f6760
005f6681 8d86e4080000             lea       eax, [esi + 0x8e4]
005f6687 33db                     xor       ebx, ebx
005f6689 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f668c 57                       push      edi
005f668d 8d4900                   lea       ecx, [ecx]
005f6690 8b864c050000             mov       eax, dword ptr [esi + 0x54c]
005f6696 8b0403                   mov       eax, dword ptr [ebx + eax]
005f6699 85c0                     test      eax, eax
005f669b 7462                     je        0x5f66ff
005f669d 8b4804                   mov       ecx, dword ptr [eax + 4]
005f66a0 85c9                     test      ecx, ecx
005f66a2 765b                     jbe       0x5f66ff
005f66a4 68b4010000               push      0x1b4
005f66a9 e8a2d5e0ff               call      0x403c50
005f66ae 83                       .byte     0x83
005f66af c4                       .byte     0xc4
