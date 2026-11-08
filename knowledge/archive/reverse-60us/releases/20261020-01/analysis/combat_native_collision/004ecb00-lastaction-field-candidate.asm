004ecb00 55                       push      ebp
004ecb01 8bec                     mov       ebp, esp
004ecb03 83ec14                   sub       esp, 0x14
004ecb06 57                       push      edi
004ecb07 8bf9                     mov       edi, ecx
004ecb09 8b8700010000             mov       eax, dword ptr [edi + 0x100]
004ecb0f 85c0                     test      eax, eax
004ecb11 0f842d030000             je        0x4ece44
004ecb17 8d8fbc040000             lea       ecx, [edi + 0x4bc]
004ecb1d e83e55f1ff               call      0x402060
004ecb22 85c0                     test      eax, eax
004ecb24 740d                     je        0x4ecb33
004ecb26 8d8fc4040000             lea       ecx, [edi + 0x4c4]
004ecb2c e82f55f1ff               call      0x402060
004ecb31 eb07                     jmp       0x4ecb3a
004ecb33 8bcf                     mov       ecx, edi
004ecb35 e8a6d4faff               call      0x499fe0
004ecb3a 85c0                     test      eax, eax
004ecb3c 7409                     je        0x4ecb47
004ecb3e 83f801                   cmp       eax, 1
004ecb41 0f85fd020000             jne       0x4ece44
004ecb47 53                       push      ebx
004ecb48 56                       push      esi
004ecb49 8b7508                   mov       esi, dword ptr [ebp + 8]
004ecb4c 8b06                     mov       eax, dword ptr [esi]
004ecb4e 8bce                     mov       ecx, esi
004ecb50 ff909c010000             call      dword ptr [eax + 0x19c]
004ecb56 8bd8                     mov       ebx, eax
004ecb58 85db                     test      ebx, ebx
004ecb5a 895df8                   mov       dword ptr [ebp - 8], ebx
004ecb5d 740f                     je        0x4ecb6e
004ecb5f 8bcb                     mov       ecx, ebx
004ecb61 e81aa9f7ff               call      0x467480
004ecb66 84c0                     test      al, al
004ecb68 0f84d4020000             je        0x4ece42
004ecb6e c645ff00                 mov       byte ptr [ebp - 1], 0
004ecb72 8b8378010000             mov       eax, dword ptr [ebx + 0x178]
004ecb78 83f801                   cmp       eax, 1
004ecb7b c745f4e0baca00           mov       dword ptr [ebp - 0xc], 0xcabae0
004ecb82 c7450800000000           mov       dword ptr [ebp + 8], 0
004ecb89 751e                     jne       0x4ecba9
004ecb8b 8b16                     mov       edx, dword ptr [esi]
004ecb8d 8bce                     mov       ecx, esi
004ecb8f c7450800000100           mov       dword ptr [ebp + 8], 0x10000
004ecb96 ff92c0000000             call      dword ptr [edx + 0xc0]
004ecb9c 85c0                     test      eax, eax
004ecb9e 7547                     jne       0x4ecbe7
004ecba0 c7450802000100           mov       dword ptr [ebp + 8], 0x10002
004ecba7 eb3e                     jmp       0x4ecbe7
004ecba9 85c0                     test      eax, eax
004ecbab 7509                     jne       0x4ecbb6
004ecbad c7450800800000           mov       dword ptr [ebp + 8], 0x8000
004ecbb4 eb1d                     jmp       0x4ecbd3
004ecbb6 83f803                   cmp       eax, 3
004ecbb9 7518                     jne       0x4ecbd3
004ecbbb 8b06                     mov       eax, dword ptr [esi]
004ecbbd 8d4dff                   lea       ecx, [ebp - 1]
004ecbc0 51                       push      ecx
004ecbc1 8bce                     mov       ecx, esi
004ecbc3 c7450800000200           mov       dword ptr [ebp + 8], 0x20000
004ecbca ff9014030000             call      dword ptr [eax + 0x314]
004ecbd0 8945f4                   mov       dword ptr [ebp - 0xc], eax
004ecbd3 8b16                     mov       edx, dword ptr [esi]
004ecbd5 57                       push      edi
004ecbd6 8bce                     mov       ecx, esi
004ecbd8 ff921c030000             call      dword ptr [edx + 0x31c]
004ecbde 83f801                   cmp       eax, 1
004ecbe1 7504                     jne       0x4ecbe7
004ecbe3 834d0802                 or        dword ptr [ebp + 8], 2
004ecbe7 56                       push      esi
004ecbe8 57                       push      edi
004ecbe9 e872c5ffff               call      0x4e9160
004ecbee 83c408                   add       esp, 8
004ecbf1 3c01                     cmp       al, 1
004ecbf3 7570                     jne       0x4ecc65
004ecbf5 8b06                     mov       eax, dword ptr [esi]
004ecbf7 8bce                     mov       ecx, esi
004ecbf9 ff90ac010000             call      dword ptr [eax + 0x1ac]
004ecbff 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004ecc02 85c9                     test      ecx, ecx
004ecc04 765f                     jbe       0x4ecc65
004ecc06 8b17                     mov       edx, dword ptr [edi]
004ecc08 8bcf                     mov       ecx, edi
004ecc0a ff92c8010000             call      dword ptr [edx + 0x1c8]
004ecc10 8945f0                   mov       dword ptr [ebp - 0x10], eax
004ecc13 8b06                     mov       eax, dword ptr [esi]
004ecc15 8bce                     mov       ecx, esi
004ecc17 ff90ac010000             call      dword ptr [eax + 0x1ac]
004ecc1d 8b4808                   mov       ecx, dword ptr [eax + 8]
004ecc20 8b19                     mov       ebx, dword ptr [ecx]
004ecc22 8b16                     mov       edx, dword ptr [esi]
004ecc24 8bce                     mov       ecx, esi
004ecc26 ff92ac010000             call      dword ptr [edx + 0x1ac]
004ecc2c 8d4df0                   lea       ecx, [ebp - 0x10]
004ecc2f 51                       push      ecx
004ecc30 8d55ec                   lea       edx, [ebp - 0x14]
004ecc33 52                       push      edx
004ecc34 8bc8                     mov       ecx, eax
004ecc36 e8a5805700               call      0xa64ce0
004ecc3b 395dec                   cmp       dword ptr [ebp - 0x14], ebx
004ecc3e 7522                     jne       0x4ecc62
004ecc40 8bcf                     mov       ecx, edi
004ecc42 e889bcffff               call      0x4e88d0
004ecc47 84c0                     test      al, al
004ecc49 7417                     je        0x4ecc62
004ecc4b 8b4508                   mov       eax, dword ptr [ebp + 8]
004ecc4e 83c808                   or        eax, 8
004ecc51 8d4f60                   lea       ecx, [edi + 0x60]
004ecc54 894508                   mov       dword ptr [ebp + 8], eax
004ecc57 e8a4a26100               call      0xb06f00
004ecc5c 89870c050000             mov       dword ptr [edi + 0x50c], eax
004ecc62 8b5df8                   mov       ebx, dword ptr [ebp - 8]
004ecc65 8b8374010000             mov       eax, dword ptr [ebx + 0x174]
004ecc6b 85c0                     test      eax, eax
004ecc6d 750e                     jne       0x4ecc7d
004ecc6f 8b7508                   mov       esi, dword ptr [ebp + 8]
004ecc72 81ce00000002             or        esi, 0x2000000
004ecc78 897508                   mov       dword ptr [ebp + 8], esi
004ecc7b eb22                     jmp       0x4ecc9f
004ecc7d 83f801                   cmp       eax, 1
004ecc80 750a                     jne       0x4ecc8c
004ecc82 8b4508                   mov       eax, dword ptr [ebp + 8]
004ecc85 0d00000008               or        eax, 0x8000000
004ecc8a eb0d                     jmp       0x4ecc99
004ecc8c 83f802                   cmp       eax, 2
004ecc8f 750b                     jne       0x4ecc9c
004ecc91 8b4508                   mov       eax, dword ptr [ebp + 8]
004ecc94 0d00000004               or        eax, 0x4000000
004ecc99 894508                   mov       dword ptr [ebp + 8], eax
004ecc9c 8b7508                   mov       esi, dword ptr [ebp + 8]
004ecc9f 8a837c010000             mov       al, byte ptr [ebx + 0x17c]
004ecca5 84c0                     test      al, al
004ecca7 7433                     je        0x4eccdc
004ecca9 8b07                     mov       eax, dword ptr [edi]
004eccab 6a11                     push      0x11
004eccad 8bcf                     mov       ecx, edi
004eccaf ff502c                   call      dword ptr [eax + 0x2c]
004eccb2 84c0                     test      al, al
004eccb4 7426                     je        0x4eccdc
004eccb6 8b17                     mov       edx, dword ptr [edi]
004eccb8 6811020000               push      0x211
004eccbd 8bcf                     mov       ecx, edi
004eccbf ff522c                   call      dword ptr [edx + 0x2c]
004eccc2 3c01                     cmp       al, 1
004eccc4 7510                     jne       0x4eccd6
004eccc6 8b07                     mov       eax, dword ptr [edi]
004eccc8 8bcf                     mov       ecx, edi
004eccca ff90b0050000             call      dword ptr [eax + 0x5b0]
004eccd0 f6403c02                 test      byte ptr [eax + 0x3c], 2
004eccd4 7506                     jne       0x4eccdc
004eccd6 83ce04                   or        esi, 4
004eccd9 897508                   mov       dword ptr [ebp + 8], esi
004eccdc 8d8b40010000             lea       ecx, [ebx + 0x140]
004ecce2 e8c966f4ff               call      0x4333b0
004ecce7 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
004ecced dfe0                     fnstsw    ax
004eccef f6c441                   test      ah, 0x41
004eccf2 7516                     jne       0x4ecd0a
004eccf4 6a12                     push      0x12
004eccf6 8bcf                     mov       ecx, edi
004eccf8 e803b3f7ff               call      0x468000
004eccfd 3c01                     cmp       al, 1
004eccff 7509                     jne       0x4ecd0a
004ecd01 81ce00001000             or        esi, 0x100000
004ecd07 897508                   mov       dword ptr [ebp + 8], esi
004ecd0a 8d8b48010000             lea       ecx, [ebx + 0x148]
004ecd10 e89b66f4ff               call      0x4333b0
004ecd15 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
004ecd1b dfe0                     fnstsw    ax
004ecd1d f6c441                   test      ah, 0x41
004ecd20 7516                     jne       0x4ecd38
004ecd22 6a13                     push      0x13
004ecd24 8bcf                     mov       ecx, edi
004ecd26 e8d5b2f7ff               call      0x468000
004ecd2b 3c01                     cmp       al, 1
004ecd2d 7509                     jne       0x4ecd38
004ecd2f 81ce00002000             or        esi, 0x200000
004ecd35 897508                   mov       dword ptr [ebp + 8], esi
004ecd38 8d8b50010000             lea       ecx, [ebx + 0x150]
004ecd3e e86d66f4ff               call      0x4333b0
004ecd43 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
004ecd49 dfe0                     fnstsw    ax
004ecd4b f6c441                   test      ah, 0x41
004ecd4e 7514                     jne       0x4ecd64
004ecd50 8bcf                     mov       ecx, edi
004ecd52 e8c9e4ffff               call      0x4eb220
004ecd57 85c0                     test      eax, eax
004ecd59 7509                     jne       0x4ecd64
004ecd5b 81ce00004000             or        esi, 0x400000
004ecd61 897508                   mov       dword ptr [ebp + 8], esi
004ecd64 8b4344                   mov       eax, dword ptr [ebx + 0x44]
004ecd67 85c0                     test      eax, eax
004ecd69 770e                     ja        0x4ecd79
004ecd6b 837b1801                 cmp       dword ptr [ebx + 0x18], 1
004ecd6f 7508                     jne       0x4ecd79
004ecd71 81ce00020000             or        esi, 0x200
004ecd77 eb49                     jmp       0x4ecdc2
004ecd79 8b5b40                   mov       ebx, dword ptr [ebx + 0x40]
004ecd7c 8b03                     mov       eax, dword ptr [ebx]
004ecd7e 3bc3                     cmp       eax, ebx
004ecd80 8945f8                   mov       dword ptr [ebp - 8], eax
004ecd83 7440                     je        0x4ecdc5
004ecd85 8b400c                   mov       eax, dword ptr [eax + 0xc]
004ecd88 85c0                     test      eax, eax
004ecd8a 7505                     jne       0x4ecd91
004ecd8c 83ce20                   or        esi, 0x20
004ecd8f eb22                     jmp       0x4ecdb3
004ecd91 83f801                   cmp       eax, 1
004ecd94 7505                     jne       0x4ecd9b
004ecd96 83ce40                   or        esi, 0x40
004ecd99 eb18                     jmp       0x4ecdb3
004ecd9b 83f802                   cmp       eax, 2
004ecd9e 7508                     jne       0x4ecda8
004ecda0 81ce80000000             or        esi, 0x80
004ecda6 eb0b                     jmp       0x4ecdb3
004ecda8 83f803                   cmp       eax, 3
004ecdab 7506                     jne       0x4ecdb3
004ecdad 81ce00010000             or        esi, 0x100
004ecdb3 8d4df8                   lea       ecx, [ebp - 8]
004ecdb6 e80565f4ff               call      0x4332c0
004ecdbb 8b45f8                   mov       eax, dword ptr [ebp - 8]
004ecdbe 3bc3                     cmp       eax, ebx
004ecdc0 75c3                     jne       0x4ecd85
004ecdc2 897508                   mov       dword ptr [ebp + 8], esi
004ecdc5 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004ecdc8 8d                       .byte     0x8d
004ecdc9 4e                       dec       esi
