0049f310 55                       push      ebp
0049f311 8bec                     mov       ebp, esp
0049f313 6aff                     push      -1
0049f315 68536bc500               push      0xc56b53
0049f31a 64a100000000             mov       eax, dword ptr fs:[0]
0049f320 50                       push      eax
0049f321 64892500000000           mov       dword ptr fs:[0], esp
0049f328 83ec1c                   sub       esp, 0x1c
0049f32b 56                       push      esi
0049f32c 8bf1                     mov       esi, ecx
0049f32e 8b06                     mov       eax, dword ptr [esi]
0049f330 ff9038020000             call      dword ptr [eax + 0x238]
0049f336 85c0                     test      eax, eax
0049f338 0f8e62010000             jle       0x49f4a0
0049f33e 8a4510                   mov       al, byte ptr [ebp + 0x10]
0049f341 84c0                     test      al, al
0049f343 0f8557010000             jne       0x49f4a0
0049f349 53                       push      ebx
0049f34a 57                       push      edi
0049f34b 8bce                     mov       ecx, esi
0049f34d e83ecdffff               call      0x49c090
0049f352 84c0                     test      al, al
0049f354 0f84e0000000             je        0x49f43a
0049f35a 8b7d08                   mov       edi, dword ptr [ebp + 8]
0049f35d 8b16                     mov       edx, dword ptr [esi]
0049f35f 57                       push      edi
0049f360 8d45ec                   lea       eax, [ebp - 0x14]
0049f363 50                       push      eax
0049f364 8bce                     mov       ecx, esi
0049f366 c645f300                 mov       byte ptr [ebp - 0xd], 0
0049f36a c745ec64000000           mov       dword ptr [ebp - 0x14], 0x64
0049f371 c745e800000000           mov       dword ptr [ebp - 0x18], 0
0049f378 ff9210030000             call      dword ptr [edx + 0x310]
0049f37e 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f381 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
0049f384 8b16                     mov       edx, dword ptr [esi]
0049f386 6a00                     push      0
0049f388 50                       push      eax
0049f389 57                       push      edi
0049f38a 51                       push      ecx
0049f38b 8d45e8                   lea       eax, [ebp - 0x18]
0049f38e 50                       push      eax
0049f38f 8d4df3                   lea       ecx, [ebp - 0xd]
0049f392 51                       push      ecx
0049f393 8bce                     mov       ecx, esi
0049f395 ff92f8020000             call      dword ptr [edx + 0x2f8]
0049f39b 8b16                     mov       edx, dword ptr [esi]
0049f39d 8bce                     mov       ecx, esi
0049f39f 8bd8                     mov       ebx, eax
0049f3a1 ff9234020000             call      dword ptr [edx + 0x234]
0049f3a7 8bf8                     mov       edi, eax
0049f3a9 33c0                     xor       eax, eax
0049f3ab 2bfb                     sub       edi, ebx
0049f3ad 8945dc                   mov       dword ptr [ebp - 0x24], eax
0049f3b0 8945e0                   mov       dword ptr [ebp - 0x20], eax
0049f3b3 8945e4                   mov       dword ptr [ebp - 0x1c], eax
0049f3b6 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f3b9 83c110                   add       ecx, 0x10
0049f3bc 8945fc                   mov       dword ptr [ebp - 4], eax
0049f3bf e8ec3ff9ff               call      0x4333b0
0049f3c4 e87b217600               call      0xc01544
0049f3c9 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f3cc 50                       push      eax
0049f3cd 83c108                   add       ecx, 8
0049f3d0 e8db3ff9ff               call      0x4333b0
0049f3d5 e86a217600               call      0xc01544
0049f3da 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f3dd 50                       push      eax
0049f3de e8cd3ff9ff               call      0x4333b0
0049f3e3 e85c217600               call      0xc01544
0049f3e8 50                       push      eax
0049f3e9 8b4508                   mov       eax, dword ptr [ebp + 8]
0049f3ec 57                       push      edi
0049f3ed 53                       push      ebx
0049f3ee 50                       push      eax
0049f3ef 8d4dd8                   lea       ecx, [ebp - 0x28]
0049f3f2 51                       push      ecx
0049f3f3 8bce                     mov       ecx, esi
0049f3f5 e896fcffff               call      0x49f090
0049f3fa 8b16                     mov       edx, dword ptr [esi]
0049f3fc 33ff                     xor       edi, edi
0049f3fe 57                       push      edi
0049f3ff 57                       push      edi
0049f400 57                       push      edi
0049f401 8d45d8                   lea       eax, [ebp - 0x28]
0049f404 50                       push      eax
0049f405 6a01                     push      1
0049f407 8bce                     mov       ecx, esi
0049f409 ff928c020000             call      dword ptr [edx + 0x28c]
0049f40f 8b16                     mov       edx, dword ptr [esi]
0049f411 8bce                     mov       ecx, esi
0049f413 ff9290020000             call      dword ptr [edx + 0x290]
0049f419 8b45dc                   mov       eax, dword ptr [ebp - 0x24]
0049f41c 83cbff                   or        ebx, 0xffffffff
0049f41f 3bc7                     cmp       eax, edi
0049f421 895dfc                   mov       dword ptr [ebp - 4], ebx
0049f424 7409                     je        0x49f42f
0049f426 50                       push      eax
0049f427 e8b10b7600               call      0xbfffdd
0049f42c 83c404                   add       esp, 4
0049f42f 897ddc                   mov       dword ptr [ebp - 0x24], edi
0049f432 897de0                   mov       dword ptr [ebp - 0x20], edi
0049f435 897de4                   mov       dword ptr [ebp - 0x1c], edi
0049f438 eb05                     jmp       0x49f43f
0049f43a 83cbff                   or        ebx, 0xffffffff
0049f43d 33ff                     xor       edi, edi
0049f43f 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
0049f445 3bcf                     cmp       ecx, edi
0049f447 7455                     je        0x49f49e
0049f449 8b869c050000             mov       eax, dword ptr [esi + 0x59c]
0049f44f 2bc1                     sub       eax, ecx
0049f451 c1f802                   sar       eax, 2
0049f454 3bc7                     cmp       eax, edi
0049f456 7646                     jbe       0x49f49e
0049f458 8bf9                     mov       edi, ecx
0049f45a 8b470c                   mov       eax, dword ptr [edi + 0xc]
0049f45d 83f8fe                   cmp       eax, -2
0049f460 743c                     je        0x49f49e
0049f462 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
0049f468 83c10c                   add       ecx, 0xc
0049f46b 3bc3                     cmp       eax, ebx
0049f46d 741a                     je        0x49f489
0049f46f e87c3c5b00               call      0xa530f0
0049f474 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049f477 8b16                     mov       edx, dword ptr [esi]
0049f479 6a00                     push      0
0049f47b 6a00                     push      0
0049f47d 51                       push      ecx
0049f47e 50                       push      eax
0049f47f 8bce                     mov       ecx, esi
0049f481 ff920c010000             call      dword ptr [edx + 0x10c]
0049f487 eb15                     jmp       0x49f49e
0049f489 8b3e                     mov       edi, dword ptr [esi]
0049f48b 6a00                     push      0
0049f48d 6a00                     push      0
0049f48f 53                       push      ebx
0049f490 e85b3c5b00               call      0xa530f0
0049f495 50                       push      eax
0049f496 8bce                     mov       ecx, esi
0049f498 ff970c010000             call      dword ptr [edi + 0x10c]
0049f49e 5f                       pop       edi
0049f49f 5b                       pop       ebx
0049f4a0 8b5510                   mov       edx, dword ptr [ebp + 0x10]
0049f4a3 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f4a6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f4a9 52                       push      edx
0049f4aa 50                       push      eax
0049f4ab 51                       push      ecx
0049f4ac 8bce                     mov       ecx, esi
0049f4ae e8fdbe0400               call      0x4eb3b0
0049f4b3 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049f4b6 5e                       pop       esi
0049f4b7 64890d00000000           mov       dword ptr fs:[0], ecx
0049f4be 8be5                     mov       esp, ebp
0049f4c0 5d                       pop       ebp
0049f4c1 c20c00                   ret       0xc
0049f4c4 cc                       int3      
0049f4c5 cc                       int3      
0049f4c6 cc                       int3      
0049f4c7 cc                       int3      
0049f4c8 cc                       int3      
0049f4c9 cc                       int3      
0049f4ca cc                       int3      
0049f4cb cc                       int3      
0049f4cc cc                       int3      
0049f4cd cc                       int3      
0049f4ce cc                       int3      
0049f4cf cc                       int3      
0049f4d0 55                       push      ebp
0049f4d1 8bec                     mov       ebp, esp
0049f4d3 6aff                     push      -1
0049f4d5 68db6bc500               push      0xc56bdb
0049f4da 64a100000000             mov       eax, dword ptr fs:[0]
0049f4e0 50                       push      eax
0049f4e1 64892500000000           mov       dword ptr fs:[0], esp
0049f4e8 81ec98030000             sub       esp, 0x398
0049f4ee 53                       push      ebx
0049f4ef 8b5d08                   mov       ebx, dword ptr [ebp + 8]
0049f4f2 56                       push      esi
0049f4f3 57                       push      edi
0049f4f4 53                       push      ebx
0049f4f5 8bf1                     mov       esi, ecx
0049f4f7 8b0de4300001             mov       ecx, dword ptr [0x10030e4]
0049f4fd 6a00                     push      0
0049f4ff e82cd96d00               call      0xb7ce30
0049f504 8bf8                     mov       edi, eax
0049f506 85ff                     test      edi, edi
0049f508 7522                     jne       0x49f52c
0049f50a 53                       push      ebx
0049f50b 6870f0cc00               push      0xccf070
0049f510 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049f516 83c408                   add       esp, 8
0049f519 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049f51c 64890d00000000           mov       dword ptr fs:[0], ecx
0049f523 5f                       pop       edi
0049f524 5e                       pop       esi
0049f525 5b                       pop       ebx
0049f526 8be5                     mov       esp, ebp
0049f528 5d                       pop       ebp
0049f529 c20800                   ret       8
0049f52c 8a8774010000             mov       al, byte ptr [edi + 0x174]
0049f532 84c0                     test      al, al
0049f534 7413                     je        0x49f549
0049f536 8b0d48280001             mov       ecx, dword ptr [0x1002848]
0049f53c e88fb0f9ff               call      0x43a5d0
0049f541 84c0                     test      al, al
0049f543 0f84d6120000             je        0x4a081f
0049f549 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049f54f e89c3b5b00               call      0xa530f0
0049f554 8bd8                     mov       ebx, eax
0049f556 53                       push      ebx
0049f557 e871087600               call      0xbffdcd
0049f55c 83c404                   add       esp, 4
0049f55f 50                       push      eax
0049f560 53                       push      ebx
0049f561 8d8e44020000             lea       ecx, [esi + 0x244]
0049f567 e81439f6ff               call      0x402e80
0049f56c 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f56f 898644050000             mov       dword ptr [esi + 0x544], eax
0049f575 8b0f                     mov       ecx, dword ptr [edi]
0049f577 8d5704                   lea       edx, [edi + 4]
0049f57a 898e04020000             mov       dword ptr [esi + 0x204], ecx
0049f580 8d8e08020000             lea       ecx, [esi + 0x208]
0049f586 52                       push      edx
0049f587 e8043f5b00               call      0xa53490
0049f58c a1d8012101               mov       eax, dword ptr [0x12101d8]
0049f591 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049f594 8b8610020000             mov       eax, dword ptr [esi + 0x210]
0049f59a 8b4f08                   mov       ecx, dword ptr [edi + 8]
0049f59d c1e002                   shl       eax, 2
0049f5a0 8d1c10                   lea       ebx, [eax + edx]
0049f5a3 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5a9 33d9                     xor       ebx, ecx
0049f5ab 891c10                   mov       dword ptr [eax + edx], ebx
0049f5ae 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049f5b4 8b5248                   mov       edx, dword ptr [edx + 0x48]
0049f5b7 8b8610020000             mov       eax, dword ptr [esi + 0x210]
0049f5bd c1e002                   shl       eax, 2
0049f5c0 8d1c10                   lea       ebx, [eax + edx]
0049f5c3 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5c9 33d9                     xor       ebx, ecx
0049f5cb 891c10                   mov       dword ptr [eax + edx], ebx
0049f5ce a1d8012101               mov       eax, dword ptr [0x12101d8]
0049f5d3 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049f5d6 8b8618020000             mov       eax, dword ptr [esi + 0x218]
0049f5dc 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049f5df c1e002                   shl       eax, 2
0049f5e2 8d1c10                   lea       ebx, [eax + edx]
0049f5e5 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5eb 33d9                     xor       ebx, ecx
0049f5ed 891c10                   mov       dword ptr [eax + edx], ebx
0049f5f0 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049f5f6 8b5248                   mov       edx, dword ptr [edx + 0x48]
0049f5f9 8b8618020000             mov       eax, dword ptr [esi + 0x218]
0049f5ff c1e002                   shl       eax, 2
0049f602 8d1c10                   lea       ebx, [eax + edx]
0049f605 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f60b 33d9                     xor       ebx, ecx
0049f60d 891c10                   mov       dword ptr [eax + edx], ebx
0049f610 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049f613 89861c020000             mov       dword ptr [esi + 0x21c], eax
0049f619 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049f61c 898ef4000000             mov       dword ptr [esi + 0xf4], ecx
0049f622 8b5718                   mov       edx, dword ptr [edi + 0x18]
0049f625 89962c050000             mov       dword ptr [esi + 0x52c], edx
0049f62b 8b471c                   mov       eax, dword ptr [edi + 0x1c]
0049f62e 898638050000             mov       dword ptr [esi + 0x538], eax
0049f634 8b4f20                   mov       ecx, dword ptr [edi + 0x20]
0049f637 8d5724                   lea       edx, [edi + 0x24]
0049f63a 898e3c050000             mov       dword ptr [esi + 0x53c], ecx
0049f640 8d8e20020000             lea       ecx, [esi + 0x220]
0049f646 52                       push      edx
0049f647 e8f4820600               call      0x507940
0049f64c 8b06                     mov       eax, dword ptr [esi]
0049f64e 6a01                     push      1
0049f650 6a18                     push      0x18
0049f652 8bce                     mov       ecx, esi
0049f654 ff901c020000             call      dword ptr [eax + 0x21c]
0049f65a 8d5f34                   lea       ebx, [edi + 0x34]
0049f65d 68e0baca00               push      0xcabae0
0049f662 8bcb                     mov       ecx, ebx
0049f664 e8873a5b00               call      0xa530f0
0049f669 50                       push      eax
0049f66a e87c177600               call      0xc00deb
0049f66f 83                       .byte     0x83
