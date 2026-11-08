004fcb2a 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004fcb30 85c0                     test      eax, eax
004fcb32 0f840d020000             je        0x4fcd45
004fcb38 8b16                     mov       edx, dword ptr [esi]
004fcb3a 8bce                     mov       ecx, esi
004fcb3c ff92a0050000             call      dword ptr [edx + 0x5a0]
004fcb42 84c0                     test      al, al
004fcb44 0f8578010000             jne       0x4fccc2
004fcb4a a148280001               mov       eax, dword ptr [0x1002848]
004fcb4f 83b8a819000002           cmp       dword ptr [eax + 0x19a8], 2
004fcb56 0f85f3000000             jne       0x4fcc4f
004fcb5c 8d8eb8240000             lea       ecx, [esi + 0x24b8]
004fcb62 e899a36000               call      0xb06f00
004fcb67 83f819                   cmp       eax, 0x19
004fcb6a 0f8ed5010000             jle       0x4fcd45
004fcb70 8dbe64150000             lea       edi, [esi + 0x1564]
004fcb76 8bcf                     mov       ecx, edi
004fcb78 e883a36000               call      0xb06f00
004fcb7d 3b86181e0000             cmp       eax, dword ptr [esi + 0x1e18]
004fcb83 0f8fbc010000             jg        0x4fcd45
004fcb89 6a64                     push      0x64
004fcb8b 8bcf                     mov       ecx, edi
004fcb8d e86ea36000               call      0xb06f00
004fcb92 8b96181e0000             mov       edx, dword ptr [esi + 0x1e18]
004fcb98 b964000000               mov       ecx, 0x64
004fcb9d 2bca                     sub       ecx, edx
004fcb9f 03c1                     add       eax, ecx
004fcba1 50                       push      eax
004fcba2 686666863f               push      0x3f866666
004fcba7 680000803f               push      0x3f800000
004fcbac e8ffcd6000               call      0xb099b0
004fcbb1 d955f4                   fst       dword ptr [ebp - 0xc]
004fcbb4 d88ef8240000             fmul      dword ptr [esi + 0x24f8]
004fcbba 83c410                   add       esp, 0x10
004fcbbd d996f8240000             fst       dword ptr [esi + 0x24f8]
004fcbc3 d81d2809cd00             fcomp     dword ptr [0xcd0928]
004fcbc9 dfe0                     fnstsw    ax
004fcbcb f6c441                   test      ah, 0x41
004fcbce 7a35                     jp        0x4fcc05
004fcbd0 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004fcbd3 8b06                     mov       eax, dword ptr [esi]
004fcbd5 52                       push      edx
004fcbd6 8bce                     mov       ecx, esi
004fcbd8 ff90f4000000             call      dword ptr [eax + 0xf4]
004fcbde 8bc8                     mov       ecx, eax
004fcbe0 e8cbcb5200               call      0xa297b0
004fcbe5 8dbeec140000             lea       edi, [esi + 0x14ec]
004fcbeb bb17000000               mov       ebx, 0x17
004fcbf0 8b0f                     mov       ecx, dword ptr [edi]
004fcbf2 85c9                     test      ecx, ecx
004fcbf4 7409                     je        0x4fcbff
004fcbf6 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004fcbf9 52                       push      edx
004fcbfa e8f1abf5ff               call      0x4577f0
004fcbff 83c704                   add       edi, 4
004fcc02 4b                       dec       ebx
004fcc03 75eb                     jne       0x4fcbf0
004fcc05 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004fcc0b 6a00                     push      0
004fcc0d 6a00                     push      0
004fcc0f e82c440100               call      0x511040
004fcc14 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004fcc1a 6a00                     push      0
004fcc1c 6a01                     push      1
004fcc1e e81d440100               call      0x511040
004fcc23 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004fcc29 6a00                     push      0
004fcc2b 6a02                     push      2
004fcc2d e80e440100               call      0x511040
004fcc32 8dbeb8240000             lea       edi, [esi + 0x24b8]
004fcc38 8bcf                     mov       ecx, edi
004fcc3a e8b182f0ff               call      0x404ef0
004fcc3f 6a00                     push      0
004fcc41 6a00                     push      0
004fcc43 8bcf                     mov       ecx, edi
004fcc45 e816a36000               call      0xb06f60
004fcc4a e9f6000000               jmp       0x4fcd45
004fcc4f 8d8e64150000             lea       ecx, [esi + 0x1564]
004fcc55 e8a6a26000               call      0xb06f00
004fcc5a 8bbe181e0000             mov       edi, dword ptr [esi + 0x1e18]
004fcc60 b964000000               mov       ecx, 0x64
004fcc65 2bcf                     sub       ecx, edi
004fcc67 6a64                     push      0x64
004fcc69 03c1                     add       eax, ecx
004fcc6b 50                       push      eax
004fcc6c 6a00                     push      0
004fcc6e 6800007f43               push      0x437f0000
004fcc73 e838cd6000               call      0xb099b0
004fcc78 83c410                   add       esp, 0x10
004fcc7b e8c4487000               call      0xc01544
004fcc80 0fb6c0                   movzx     eax, al
004fcc83 c1e018                   shl       eax, 0x18
004fcc86 0dffffff00               or        eax, 0xffffff
004fcc8b 25000000ff               and       eax, 0xff000000
004fcc90 3d000000ff               cmp       eax, 0xff000000
004fcc95 750d                     jne       0x4fcca4
004fcc97 50                       push      eax
004fcc98 8bce                     mov       ecx, esi
004fcc9a e8c1c1f9ff               call      0x498e60
004fcc9f e9a1000000               jmp       0x4fcd45
004fcca4 8b96c0010000             mov       edx, dword ptr [esi + 0x1c0]
004fccaa 81e2ffffff00             and       edx, 0xffffff
004fccb0 0bd0                     or        edx, eax
004fccb2 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
004fccb8 0d000000ff               or        eax, 0xff000000
004fccbd e977000000               jmp       0x4fcd39
004fccc2 8d8e64150000             lea       ecx, [esi + 0x1564]
004fccc8 e833a26000               call      0xb06f00
004fcccd 8bbe181e0000             mov       edi, dword ptr [esi + 0x1e18]
004fccd3 b964000000               mov       ecx, 0x64
004fccd8 2bcf                     sub       ecx, edi
004fccda 6a64                     push      0x64
004fccdc 03c1                     add       eax, ecx
004fccde 50                       push      eax
004fccdf 680000c842               push      0x42c80000
004fcce4 6800007f43               push      0x437f0000
004fcce9 e8c2cc6000               call      0xb099b0
004fccee 83c410                   add       esp, 0x10
004fccf1 e84e487000               call      0xc01544
004fccf6 0fb6c8                   movzx     ecx, al
004fccf9 8bc1                     mov       eax, ecx
004fccfb 0d00ffffff               or        eax, 0xffffff00
004fcd00 c1e008                   shl       eax, 8
004fcd03 0bc1                     or        eax, ecx
004fcd05 c1e008                   shl       eax, 8
004fcd08 0bc1                     or        eax, ecx
004fcd0a 25ffffff00               and       eax, 0xffffff
004fcd0f 3dffffff00               cmp       eax, 0xffffff
004fcd14 750a                     jne       0x4fcd20
004fcd16 50                       push      eax
004fcd17 8bce                     mov       ecx, esi
004fcd19 e842c1f9ff               call      0x498e60
004fcd1e eb25                     jmp       0x4fcd45
004fcd20 8b96c0010000             mov       edx, dword ptr [esi + 0x1c0]
004fcd26 81e2000000ff             and       edx, 0xff000000
004fcd2c 0bd0                     or        edx, eax
004fcd2e 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
004fcd34 0dffffff00               or        eax, 0xffffff
004fcd39 8996c0010000             mov       dword ptr [esi + 0x1c0], edx
004fcd3f 8986c4010000             mov       dword ptr [esi + 0x1c4], eax
004fcd45 8d8e64150000             lea       ecx, [esi + 0x1564]
004fcd4b e8b0a16000               call      0xb06f00
004fcd50 3b86181e0000             cmp       eax, dword ptr [esi + 0x1e18]
004fcd56 7c14                     jl        0x4fcd6c
004fcd58 8a86e8010000             mov       al, byte ptr [esi + 0x1e8]
004fcd5e 84c0                     test      al, al
004fcd60 750a                     jne       0x4fcd6c
004fcd62 8b06                     mov       eax, dword ptr [esi]
004fcd64 8bce                     mov       ecx, esi
004fcd66 ff9054060000             call      dword ptr [eax + 0x654]
