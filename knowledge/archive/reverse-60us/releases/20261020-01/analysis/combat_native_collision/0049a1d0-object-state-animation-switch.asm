0049a1d0 55                       push      ebp
0049a1d1 8bec                     mov       ebp, esp
0049a1d3 83ec20                   sub       esp, 0x20
0049a1d6 56                       push      esi
0049a1d7 8bf1                     mov       esi, ecx
0049a1d9 8b8600010000             mov       eax, dword ptr [esi + 0x100]
0049a1df 85c0                     test      eax, eax
0049a1e1 0f8488040000             je        0x49a66f
0049a1e7 8b8ec4010000             mov       ecx, dword ptr [esi + 0x1c4]
0049a1ed 8b86c0010000             mov       eax, dword ptr [esi + 0x1c0]
0049a1f3 894dec                   mov       dword ptr [ebp - 0x14], ecx
0049a1f6 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a1fc 85c9                     test      ecx, ecx
0049a1fe 53                       push      ebx
0049a1ff 8a9ec3010000             mov       bl, byte ptr [esi + 0x1c3]
0049a205 8945e8                   mov       dword ptr [ebp - 0x18], eax
0049a208 885dff                   mov       byte ptr [ebp - 1], bl
0049a20b 0f849b000000             je        0x49a2ac
0049a211 e84add5800               call      0xa27f60
0049a216 8b96f8000000             mov       edx, dword ptr [esi + 0xf8]
0049a21c 8b4a78                   mov       ecx, dword ptr [edx + 0x78]
0049a21f 85c9                     test      ecx, ecx
0049a221 7462                     je        0x49a285
0049a223 8b01                     mov       eax, dword ptr [ecx]
0049a225 ff5040                   call      dword ptr [eax + 0x40]
0049a228 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
0049a22e dfe0                     fnstsw    ax
0049a230 f6c405                   test      ah, 5
0049a233 7a50                     jp        0x49a285
0049a235 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049a23b 8b4978                   mov       ecx, dword ptr [ecx + 0x78]
0049a23e 8b11                     mov       edx, dword ptr [ecx]
0049a240 ff5240                   call      dword ptr [edx + 0x40]
0049a243 0fb6c3                   movzx     eax, bl
0049a246 8945e4                   mov       dword ptr [ebp - 0x1c], eax
0049a249 da4de4                   fimul     dword ptr [ebp - 0x1c]
0049a24c d80dac10cc00             fmul      dword ptr [0xcc10ac]
0049a252 e8ed727600               call      0xc01544
0049a257 8b96c0010000             mov       edx, dword ptr [esi + 0x1c0]
0049a25d 0fb6c8                   movzx     ecx, al
0049a260 81e2ffffff00             and       edx, 0xffffff
0049a266 c1e118                   shl       ecx, 0x18
0049a269 0bca                     or        ecx, edx
0049a26b 8b55ec                   mov       edx, dword ptr [ebp - 0x14]
0049a26e 81ca000000ff             or        edx, 0xff000000
0049a274 84c0                     test      al, al
0049a276 8845ff                   mov       byte ptr [ebp - 1], al
0049a279 894de8                   mov       dword ptr [ebp - 0x18], ecx
0049a27c 8955ec                   mov       dword ptr [ebp - 0x14], edx
0049a27f 0f84e9030000             je        0x49a66e
0049a285 8b06                     mov       eax, dword ptr [esi]
0049a287 8bce                     mov       ecx, esi
0049a289 ff9038010000             call      dword ptr [eax + 0x138]
0049a28f 84c0                     test      al, al
0049a291 7419                     je        0x49a2ac
0049a293 8b8ed0010000             mov       ecx, dword ptr [esi + 0x1d0]
0049a299 8b96cc010000             mov       edx, dword ptr [esi + 0x1cc]
0049a29f 51                       push      ecx
0049a2a0 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a2a6 52                       push      edx
0049a2a7 e884b55800               call      0xa25830
0049a2ac 8b06                     mov       eax, dword ptr [esi]
0049a2ae 57                       push      edi
0049a2af 8bbe00010000             mov       edi, dword ptr [esi + 0x100]
0049a2b5 8bce                     mov       ecx, esi
0049a2b7 ff5028                   call      dword ptr [eax + 0x28]
0049a2ba 8b480c                   mov       ecx, dword ptr [eax + 0xc]
0049a2bd 8b16                     mov       edx, dword ptr [esi]
0049a2bf 51                       push      ecx
0049a2c0 8bce                     mov       ecx, esi
0049a2c2 ff9294000000             call      dword ptr [edx + 0x94]
0049a2c8 50                       push      eax
0049a2c9 8bcf                     mov       ecx, edi
0049a2cb e830070700               call      0x50aa00
0049a2d0 8bbe00010000             mov       edi, dword ptr [esi + 0x100]
0049a2d6 8bd8                     mov       ebx, eax
0049a2d8 8b06                     mov       eax, dword ptr [esi]
0049a2da 680000803f               push      0x3f800000
0049a2df 8bce                     mov       ecx, esi
0049a2e1 895df0                   mov       dword ptr [ebp - 0x10], ebx
0049a2e4 ff5028                   call      dword ptr [eax + 0x28]
0049a2e7 8b480c                   mov       ecx, dword ptr [eax + 0xc]
0049a2ea 8b16                     mov       edx, dword ptr [esi]
0049a2ec 51                       push      ecx
0049a2ed 8bce                     mov       ecx, esi
0049a2ef ff929c000000             call      dword ptr [edx + 0x9c]
0049a2f5 50                       push      eax
0049a2f6 8b06                     mov       eax, dword ptr [esi]
0049a2f8 8bce                     mov       ecx, esi
0049a2fa ff9098000000             call      dword ptr [eax + 0x98]
0049a300 50                       push      eax
0049a301 8bcf                     mov       ecx, edi
0049a303 e838070700               call      0x50aa40
0049a308 8b16                     mov       edx, dword ptr [esi]
0049a30a 8bce                     mov       ecx, esi
0049a30c 8945f4                   mov       dword ptr [ebp - 0xc], eax
0049a30f ff92c0000000             call      dword ptr [edx + 0xc0]
0049a315 8bbe04010000             mov       edi, dword ptr [esi + 0x104]
0049a31b 83f801                   cmp       eax, 1
0049a31e 0f9545fa                 setne     byte ptr [ebp - 6]
0049a322 85ff                     test      edi, edi
0049a324 741e                     je        0x49a344
0049a326 83bf24010000ff           cmp       dword ptr [edi + 0x124], -1
0049a32d 7507                     jne       0x49a336
0049a32f 8bcf                     mov       ecx, edi
0049a331 e82adc5800               call      0xa27f60
0049a336 8b87cc000000             mov       eax, dword ptr [edi + 0xcc]
0049a33c 85c0                     test      eax, eax
0049a33e 7404                     je        0x49a344
0049a340 c645fa01                 mov       byte ptr [ebp - 6], 1
0049a344 8b4dfa                   mov       ecx, dword ptr [ebp - 6]
0049a347 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
0049a34a 8b06                     mov       eax, dword ptr [esi]
0049a34c 51                       push      ecx
0049a34d 52                       push      edx
0049a34e 53                       push      ebx
0049a34f 6a00                     push      0
0049a351 8bce                     mov       ecx, esi
0049a353 ff9080010000             call      dword ptr [eax + 0x180]
0049a359 8b860c010000             mov       eax, dword ptr [esi + 0x10c]
0049a35f 8b38                     mov       edi, dword ptr [eax]
0049a361 3bf8                     cmp       edi, eax
0049a363 7476                     je        0x49a3db
0049a365 8b4708                   mov       eax, dword ptr [edi + 8]
0049a368 85c0                     test      eax, eax
0049a36a 7d6f                     jge       0x49a3db
0049a36c 8a4719                   mov       al, byte ptr [edi + 0x19]
0049a36f 84c0                     test      al, al
0049a371 755e                     jne       0x49a3d1
0049a373 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a376 e8e5db5800               call      0xa27f60
0049a37b 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
0049a37e 85c0                     test      eax, eax
0049a380 7413                     je        0x49a395
0049a382 807f1a01                 cmp       byte ptr [edi + 0x1a], 1
0049a386 750d                     jne       0x49a395
0049a388 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
0049a38b 51                       push      ecx
0049a38c 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a38f 50                       push      eax
0049a390 e83bb45800               call      0xa257d0
0049a395 8a45fa                   mov       al, byte ptr [ebp - 6]
0049a398 84c0                     test      al, al
0049a39a 7409                     je        0x49a3a5
0049a39c 8b4f10                   mov       ecx, dword ptr [edi + 0x10]
0049a39f 8bc3                     mov       eax, ebx
0049a3a1 2bc1                     sub       eax, ecx
0049a3a3 eb05                     jmp       0x49a3aa
0049a3a5 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049a3a8 03c3                     add       eax, ebx
0049a3aa 8a5718                   mov       dl, byte ptr [edi + 0x18]
0049a3ad 8b4dfa                   mov       ecx, dword ptr [ebp - 6]
0049a3b0 84d2                     test      dl, dl
0049a3b2 0f95c2                   setne     dl
0049a3b5 feca                     dec       dl
0049a3b7 23d1                     and       edx, ecx
0049a3b9 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049a3bc 52                       push      edx
0049a3bd 034df4                   add       ecx, dword ptr [ebp - 0xc]
0049a3c0 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049a3c6 51                       push      ecx
0049a3c7 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a3ca 50                       push      eax
0049a3cb 52                       push      edx
0049a3cc e8bfc55800               call      0xa26990
0049a3d1 8b3f                     mov       edi, dword ptr [edi]
0049a3d3 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049a3d9 758a                     jne       0x49a365
0049a3db 8b06                     mov       eax, dword ptr [esi]
0049a3dd 8bce                     mov       ecx, esi
0049a3df ff90f4000000             call      dword ptr [eax + 0xf4]
0049a3e5 85c0                     test      eax, eax
0049a3e7 0f84ca010000             je        0x49a5b7
0049a3ed 8a86d8010000             mov       al, byte ptr [esi + 0x1d8]
0049a3f3 84c0                     test      al, al
0049a3f5 0f8467010000             je        0x49a562
0049a3fb 8a86e0010000             mov       al, byte ptr [esi + 0x1e0]
0049a401 84c0                     test      al, al
0049a403 0f84be000000             je        0x49a4c7
0049a409 6a00                     push      0
0049a40b e8e03c4100               call      0x8ae0f0
0049a410 99                       cdq       
0049a411 b903000000               mov       ecx, 3
0049a416 f7f9                     idiv      ecx
0049a418 83c404                   add       esp, 4
0049a41b 6a00                     push      0
0049a41d 4a                       dec       edx
0049a41e 8955e4                   mov       dword ptr [ebp - 0x1c], edx
0049a421 751d                     jne       0x49a440
0049a423 e8c83c4100               call      0x8ae0f0
0049a428 83c404                   add       esp, 4
0049a42b 2501000080               and       eax, 0x80000001
0049a430 7905                     jns       0x49a437
0049a432 48                       dec       eax
0049a433 83c8fe                   or        eax, 0xfffffffe
0049a436 40                       inc       eax
0049a437 f7d8                     neg       eax
0049a439 1bc0                     sbb       eax, eax
0049a43b 83e002                   and       eax, 2
0049a43e eb12                     jmp       0x49a452
0049a440 e8ab3c4100               call      0x8ae0f0
0049a445 99                       cdq       
0049a446 b903000000               mov       ecx, 3
0049a44b 83c404                   add       esp, 4
0049a44e f7f9                     idiv      ecx
0049a450 8bc2                     mov       eax, edx
0049a452 8b8ee4010000             mov       ecx, dword ptr [esi + 0x1e4]
0049a458 0fb655ff                 movzx     edx, byte ptr [ebp - 1]
0049a45c 48                       dec       eax
0049a45d 8bd9                     mov       ebx, ecx
0049a45f 0fafc8                   imul      ecx, eax
0049a462 0faf5de4                 imul      ebx, dword ptr [ebp - 0x1c]
0049a466 8955e4                   mov       dword ptr [ebp - 0x1c], edx
0049a469 6a00                     push      0
0049a46b 894de0                   mov       dword ptr [ebp - 0x20], ecx
0049a46e db45e4                   fild      dword ptr [ebp - 0x1c]
0049a471 6a00                     push      0
0049a473 d80da0eacc00             fmul      dword ptr [0xcceaa0]
0049a479 e8c6707600               call      0xc01544
0049a47e 8b8edc010000             mov       ecx, dword ptr [esi + 0x1dc]
0049a484 8b55fa                   mov       edx, dword ptr [ebp - 6]
0049a487 0fb6c0                   movzx     eax, al
0049a48a c1e018                   shl       eax, 0x18
0049a48d 0dffffff00               or        eax, 0xffffff
0049a492 50                       push      eax
0049a493 8b45e0                   mov       eax, dword ptr [ebp - 0x20]
0049a496 51                       push      ecx
0049a497 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049a49a 6a01                     push      1
0049a49c 6a00                     push      0
0049a49e 52                       push      edx
0049a49f 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
0049a4a2 03c1                     add       eax, ecx
0049a4a4 50                       push      eax
0049a4a5 a12ca90d01               mov       eax, dword ptr [0x10da92c]
0049a4aa 03da                     add       ebx, edx
0049a4ac 8b16                     mov       edx, dword ptr [esi]
0049a4ae 53                       push      ebx
0049a4af 50                       push      eax
0049a4b0 8bce                     mov       ecx, esi
0049a4b2 ff92f4000000             call      dword ptr [edx + 0xf4]
0049a4b8 8bc8                     mov       ecx, eax
0049a4ba e861bd5800               call      0xa26220
0049a4bf 8b5df0                   mov       ebx, dword ptr [ebp - 0x10]
0049a4c2 e99b000000               jmp       0x49a562
0049a4c7 0fb686df010000           movzx     eax, byte ptr [esi + 0x1df]
0049a4ce 0fb64dff                 movzx     ecx, byte ptr [ebp - 1]
0049a4d2 8945e0                   mov       dword ptr [ebp - 0x20], eax
0049a4d5 db45e0                   fild      dword ptr [ebp - 0x20]
0049a4d8 894de0                   mov       dword ptr [ebp - 0x20], ecx
0049a4db da4de0                   fimul     dword ptr [ebp - 0x20]
0049a4de d80d9ceacc00             fmul      dword ptr [0xccea9c]
0049a4e4 e85b707600               call      0xc01544
0049a4e9 8845fe                   mov       byte ptr [ebp - 2], al
0049a4ec 33c0                     xor       eax, eax
0049a4ee 8945e4                   mov       dword ptr [ebp - 0x1c], eax
0049a4f1 83f804                   cmp       eax, 4
0049a4f4 7463                     je        0x49a559
0049a4f6 99                       cdq       
0049a4f7 b903000000               mov       ecx, 3
0049a4fc f7f9                     idiv      ecx
0049a4fe 8b9ee4010000             mov       ebx, dword ptr [esi + 0x1e4]
0049a504 6a00                     push      0
0049a506 6a00                     push      0
0049a508 8d4aff                   lea       ecx, [edx - 1]
0049a50b 0fb655fe                 movzx     edx, byte ptr [ebp - 2]
0049a50f 0fafcb                   imul      ecx, ebx
0049a512 c1e218                   shl       edx, 0x18
0049a515 81caffffff00             or        edx, 0xffffff
0049a51b 52                       push      edx
0049a51c 8b96dc010000             mov       edx, dword ptr [esi + 0x1dc]
0049a522 52                       push      edx
0049a523 8b55fa                   mov       edx, dword ptr [ebp - 6]
0049a526 6a01                     push      1
0049a528 48                       dec       eax
0049a529 6a00                     push      0
0049a52b 0fafc3                   imul      eax, ebx
0049a52e 52                       push      edx
0049a52f 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
0049a532 03ca                     add       ecx, edx
0049a534 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049a53a 51                       push      ecx
0049a53b 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049a53e 03c1                     add       eax, ecx
0049a540 50                       push      eax
0049a541 8b06                     mov       eax, dword ptr [esi]
0049a543 52                       push      edx
0049a544 8bce                     mov       ecx, esi
0049a546 ff90f4000000             call      dword ptr [eax + 0xf4]
0049a54c 8bc8                     mov       ecx, eax
0049a54e e8cdbc5800               call      0xa26220
0049a553 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
0049a556 8b5df0                   mov       ebx, dword ptr [ebp - 0x10]
0049a559 40                       inc       eax
0049a55a 83f809                   cmp       eax, 9
0049a55d 8945e4                   mov       dword ptr [ebp - 0x1c], eax
0049a560 7c8f                     jl        0x49a4f1
0049a562 8a45ff                   mov       al, byte ptr [ebp - 1]
0049a565 84c0                     test      al, al
0049a567 744e                     je        0x49a5b7
0049a569 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049a56f 85c9                     test      ecx, ecx
0049a571 8b55fa                   mov       edx, dword ptr [ebp - 6]
0049a574 8b86f0010000             mov       eax, dword ptr [esi + 0x1f0]
0049a57a 52                       push      edx
0049a57b 7414                     je        0x49a591
0049a57d 0345f4                   add       eax, dword ptr [ebp - 0xc]
0049a580 8b96ec010000             mov       edx, dword ptr [esi + 0x1ec]
0049a586 50                       push      eax
0049a587 03d3                     add       edx, ebx
0049a589 52                       push      edx
0049a58a e8712d5900               call      0xa2d300
0049a58f eb26                     jmp       0x49a5b7
0049a591 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
0049a594 8b8eec010000             mov       ecx, dword ptr [esi + 0x1ec]
0049a59a 03c2                     add       eax, edx
0049a59c 8b16                     mov       edx, dword ptr [esi]
0049a59e 50                       push      eax
0049a59f a12ca90d01               mov       eax, dword ptr [0x10da92c]
0049a5a4 03cb                     add       ecx, ebx
0049a5a6 51                       push      ecx
0049a5a7 50                       push      eax
0049a5a8 8bce                     mov       ecx, esi
0049a5aa ff92f4000000             call      dword ptr [edx + 0xf4]
0049a5b0 8bc8                     mov       ecx, eax
0049a5b2 e8d9c35800               call      0xa26990
0049a5b7 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049a5bd 7470                     je        0x49a62f
0049a5bf 90                       nop       
0049a5c0 8a4719                   mov       al, byte ptr [edi + 0x19]
0049a5c3 84c0                     test      al, al
0049a5c5 755e                     jne       0x49a625
0049a5c7 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a5ca e891d95800               call      0xa27f60
0049a5cf 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
0049a5d2 85c0                     test      eax, eax
0049a5d4 7413                     je        0x49a5e9
0049a5d6 807f1a01                 cmp       byte ptr [edi + 0x1a], 1
0049a5da 750d                     jne       0x49a5e9
0049a5dc 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
0049a5df 51                       push      ecx
0049a5e0 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a5e3 50                       push      eax
0049a5e4 e8e7b15800               call      0xa257d0
0049a5e9 8a45fa                   mov       al, byte ptr [ebp - 6]
0049a5ec 84c0                     test      al, al
0049a5ee 7409                     je        0x49a5f9
0049a5f0 8b4f10                   mov       ecx, dword ptr [edi + 0x10]
0049a5f3 8bc3                     mov       eax, ebx
0049a5f5 2bc1                     sub       eax, ecx
0049a5f7 eb05                     jmp       0x49a5fe
0049a5f9 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049a5fc 03c3                     add       eax, ebx
0049a5fe 8a5718                   mov       dl, byte ptr [edi + 0x18]
0049a601 8b4dfa                   mov       ecx, dword ptr [ebp - 6]
0049a604 84d2                     test      dl, dl
0049a606 0f95c2                   setne     dl
0049a609 feca                     dec       dl
0049a60b 23d1                     and       edx, ecx
0049a60d 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049a610 52                       push      edx
0049a611 034df4                   add       ecx, dword ptr [ebp - 0xc]
0049a614 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049a61a 51                       push      ecx
0049a61b 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a61e 50                       push      eax
0049a61f 52                       push      edx
0049a620 e86bc35800               call      0xa26990
0049a625 8b3f                     mov       edi, dword ptr [edi]
0049a627 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049a62d 7591                     jne       0x49a5c0
0049a62f 8b4dfa                   mov       ecx, dword ptr [ebp - 6]
0049a632 8b7df4                   mov       edi, dword ptr [ebp - 0xc]
0049a635 8b06                     mov       eax, dword ptr [esi]
0049a637 51                       push      ecx
0049a638 57                       push      edi
0049a639 53                       push      ebx
0049a63a 6a01                     push      1
0049a63c 8bce                     mov       ecx, esi
0049a63e ff9080010000             call      dword ptr [eax + 0x180]
0049a644 8b8e8c010000             mov       ecx, dword ptr [esi + 0x18c]
0049a64a 85c9                     test      ecx, ecx
0049a64c 740c                     je        0x49a65a
0049a64e 68ff000000               push      0xff
0049a653 57                       push      edi
0049a654 53                       push      ebx
0049a655 e8c6d60800               call      0x527d20
0049a65a 8bb690010000             mov       esi, dword ptr [esi + 0x190]
0049a660 85f6                     test      esi, esi
0049a662 7409                     je        0x49a66d
0049a664 57                       push      edi
0049a665 53                       push      ebx
0049a666 8bce                     mov       ecx, esi
0049a668 e8d3cd0800               call      0x527440
0049a66d 5f                       pop       edi
0049a66e 5b                       pop       ebx
0049a66f 5e                       pop       esi
0049a670 8be5                     mov       esp, ebp
0049a672 5d                       pop       ebp
0049a673 c3                       ret       
0049a674 cc                       int3      
0049a675 cc                       int3      
0049a676 cc                       int3      
0049a677 cc                       int3      
0049a678 cc                       int3      
0049a679 cc                       int3      
0049a67a cc                       int3      
0049a67b cc                       int3      
0049a67c cc                       int3      
0049a67d cc                       int3      
0049a67e cc                       int3      
0049a67f cc                       int3      
