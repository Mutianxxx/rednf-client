004fa1d0 55                       push      ebp
004fa1d1 8bec                     mov       ebp, esp
004fa1d3 6aff                     push      -1
004fa1d5 68709cc500               push      0xc59c70
004fa1da 64a100000000             mov       eax, dword ptr fs:[0]
004fa1e0 50                       push      eax
004fa1e1 64892500000000           mov       dword ptr fs:[0], esp
004fa1e8 83ec60                   sub       esp, 0x60
004fa1eb 53                       push      ebx
004fa1ec 56                       push      esi
004fa1ed 57                       push      edi
004fa1ee 8bf1                     mov       esi, ecx
004fa1f0 e96a08ec00               jmp       0x13baa5f
004fa1f5 7ce3                     jl        0x4fa1da
004fa1f7 5e                       pop       esi
004fa1f8 1f                       pop       ds
004fa1f9 e453                     in        al, 0x53
004fa1fb 2e395600                 cmp       dword ptr cs:[esi], edx
004fa1ff f8                       clc       
004fa200 e253                     loop      0x4fa255
004fa202 98                       cwde      
004fa203 d7                       xlatb     
004fa204 99                       cdq       
004fa205 9a56e378bdb3ba           lcall     0xbab3, 0xbd78e356
004fa20c 5b                       pop       ebx
004fa20d 6bccf4                   imul      ecx, esp, -0xc
004fa210 94                       xchg      esp, eax
004fa211 91                       xchg      ecx, eax
004fa212 8e92f8e44ad2             mov       ss, word ptr [edx - 0x2db51b08]
004fa218 03bd1c2a8a86             add       edi, dword ptr [ebp - 0x7975d5e4]
004fa21e e801000084               call      0x844fa224
004fa223 c00f85                   ror       byte ptr [edi], 0x85
004fa226 1306                     adc       eax, dword ptr [esi]
004fa228 0000                     add       byte ptr [eax], al
004fa22a 8b06                     mov       eax, dword ptr [esi]
004fa22c ff90a0050000             call      dword ptr [eax + 0x5a0]
004fa232 84c0                     test      al, al
004fa234 0f849e000000             je        0x4fa2d8
004fa23a 8b16                     mov       edx, dword ptr [esi]
004fa23c 8bce                     mov       ecx, esi
004fa23e ff92a0030000             call      dword ptr [edx + 0x3a0]
004fa244 85c0                     test      eax, eax
004fa246 8b06                     mov       eax, dword ptr [esi]
004fa248 8bce                     mov       ecx, esi
004fa24a 7440                     je        0x4fa28c
004fa24c ff90a0030000             call      dword ptr [eax + 0x3a0]
004fa252 398648010000             cmp       dword ptr [esi + 0x148], eax
004fa258 747e                     je        0x4fa2d8
004fa25a 8d8e04170000             lea       ecx, [esi + 0x1704]
004fa260 e8fb7df0ff               call      0x402060
004fa265 8b16                     mov       edx, dword ptr [esi]
004fa267 50                       push      eax
004fa268 8bce                     mov       ecx, esi
004fa26a ff92a0030000             call      dword ptr [edx + 0x3a0]
004fa270 8bc8                     mov       ecx, eax
004fa272 e839635300               call      0xa305b0
004fa277 8b3e                     mov       edi, dword ptr [esi]
004fa279 8bce                     mov       ecx, esi
004fa27b ff97a0030000             call      dword ptr [edi + 0x3a0]
004fa281 50                       push      eax
004fa282 8bce                     mov       ecx, esi
004fa284 ff9700010000             call      dword ptr [edi + 0x100]
004fa28a eb4c                     jmp       0x4fa2d8
004fa28c ff9078030000             call      dword ptr [eax + 0x378]
004fa292 85c0                     test      eax, eax
004fa294 7442                     je        0x4fa2d8
004fa296 8b16                     mov       edx, dword ptr [esi]
004fa298 8bce                     mov       ecx, esi
004fa29a ff9278030000             call      dword ptr [edx + 0x378]
004fa2a0 398604010000             cmp       dword ptr [esi + 0x104], eax
004fa2a6 7430                     je        0x4fa2d8
004fa2a8 8d8e04170000             lea       ecx, [esi + 0x1704]
004fa2ae e8ad7df0ff               call      0x402060
004fa2b3 50                       push      eax
004fa2b4 8b06                     mov       eax, dword ptr [esi]
004fa2b6 8bce                     mov       ecx, esi
004fa2b8 ff9078030000             call      dword ptr [eax + 0x378]
004fa2be 8bc8                     mov       ecx, eax
004fa2c0 e8abd55200               call      0xa27870
004fa2c5 8b3e                     mov       edi, dword ptr [esi]
004fa2c7 8bce                     mov       ecx, esi
004fa2c9 ff9778030000             call      dword ptr [edi + 0x378]
004fa2cf 50                       push      eax
004fa2d0 8bce                     mov       ecx, esi
004fa2d2 ff97f0000000             call      dword ptr [edi + 0xf0]
004fa2d8 8b16                     mov       edx, dword ptr [esi]
004fa2da 8bce                     mov       ecx, esi
004fa2dc ff92d0050000             call      dword ptr [edx + 0x5d0]
004fa2e2 b90ce6ff00               mov       ecx, 0xffe60c
004fa2e7 e8747df0ff               call      0x402060
004fa2ec 85c0                     test      eax, eax
004fa2ee 0f8509050000             jne       0x4fa7fd
004fa2f4 8a86a8240000             mov       al, byte ptr [esi + 0x24a8]
004fa2fa 84c0                     test      al, al
004fa2fc 0f84fb040000             je        0x4fa7fd
004fa302 8b06                     mov       eax, dword ptr [esi]
004fa304 8bce                     mov       ecx, esi
004fa306 ff90b0050000             call      dword ptr [eax + 0x5b0]
004fa30c 8b4818                   mov       ecx, dword ptr [eax + 0x18]
004fa30f 85c9                     test      ecx, ecx
004fa311 741b                     je        0x4fa32e
004fa313 8b16                     mov       edx, dword ptr [esi]
004fa315 8bce                     mov       ecx, esi
004fa317 ff92b0050000             call      dword ptr [edx + 0x5b0]
004fa31d 8b4018                   mov       eax, dword ptr [eax + 0x18]
004fa320 8b10                     mov       edx, dword ptr [eax]
004fa322 8bc8                     mov       ecx, eax
004fa324 ff92a8020000             call      dword ptr [edx + 0x2a8]
004fa32a 8bf8                     mov       edi, eax
004fa32c eb02                     jmp       0x4fa330
004fa32e 33ff                     xor       edi, edi
004fa330 8b06                     mov       eax, dword ptr [esi]
004fa332 8bce                     mov       ecx, esi
004fa334 ff9094000000             call      dword ptr [eax + 0x94]
004fa33a 8b16                     mov       edx, dword ptr [esi]
004fa33c 8bce                     mov       ecx, esi
004fa33e 8945d8                   mov       dword ptr [ebp - 0x28], eax
004fa341 ff9298000000             call      dword ptr [edx + 0x98]
004fa347 8bce                     mov       ecx, esi
004fa349 8945d4                   mov       dword ptr [ebp - 0x2c], eax
004fa34c e83f1dfaff               call      0x49c090
004fa351 84c0                     test      al, al
004fa353 0f84e4040000             je        0x4fa83d
004fa359 8b06                     mov       eax, dword ptr [esi]
004fa35b 8bce                     mov       ecx, esi
004fa35d bbffff0000               mov       ebx, 0xffff
004fa362 ff90b0050000             call      dword ptr [eax + 0x5b0]
004fa368 8b4818                   mov       ecx, dword ptr [eax + 0x18]
004fa36b 85c9                     test      ecx, ecx
004fa36d 740d                     je        0x4fa37c
004fa36f 85ff                     test      edi, edi
004fa371 7409                     je        0x4fa37c
004fa373 8b17                     mov       edx, dword ptr [edi]
004fa375 8bcf                     mov       ecx, edi
004fa377 ff5240                   call      dword ptr [edx + 0x40]
004fa37a 8bd8                     mov       ebx, eax
004fa37c 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa382 6a2a                     push      0x2a
004fa384 e8673f5600               call      0xa5e2f0
004fa389 8b06                     mov       eax, dword ptr [esi]
004fa38b 8b3d80420d01             mov       edi, dword ptr [0x10d4280]
004fa391 8bce                     mov       ecx, esi
004fa393 ff5040                   call      dword ptr [eax + 0x40]
004fa396 6a02                     push      2
004fa398 8d4de8                   lea       ecx, [ebp - 0x18]
004fa39b 51                       push      ecx
004fa39c 8bcf                     mov       ecx, edi
004fa39e 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fa3a1 e82a405600               call      0xa5e3d0
004fa3a6 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3ac 6a02                     push      2
004fa3ae 8d55e8                   lea       edx, [ebp - 0x18]
004fa3b1 52                       push      edx
004fa3b2 895de8                   mov       dword ptr [ebp - 0x18], ebx
004fa3b5 e816405600               call      0xa5e3d0
004fa3ba 8b86cc220000             mov       eax, dword ptr [esi + 0x22cc]
004fa3c0 6a04                     push      4
004fa3c2 8d4de8                   lea       ecx, [ebp - 0x18]
004fa3c5 51                       push      ecx
004fa3c6 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3cc 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fa3cf e8fc3f5600               call      0xa5e3d0
004fa3d4 8b96d0220000             mov       edx, dword ptr [esi + 0x22d0]
004fa3da 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa3e0 6a04                     push      4
004fa3e2 8d45e8                   lea       eax, [ebp - 0x18]
004fa3e5 50                       push      eax
004fa3e6 8955e8                   mov       dword ptr [ebp - 0x18], edx
004fa3e9 e8e23f5600               call      0xa5e3d0
004fa3ee 8bce                     mov       ecx, esi
004fa3f0 e87b5ffbff               call      0x4b0370
004fa3f5 8b16                     mov       edx, dword ptr [esi]
004fa3f7 8bce                     mov       ecx, esi
004fa3f9 8bf8                     mov       edi, eax
004fa3fb ff92b8050000             call      dword ptr [edx + 0x5b8]
004fa401 8d4864                   lea       ecx, [eax + 0x64]
004fa404 e8577cf0ff               call      0x402060
004fa409 8d8e541d0000             lea       ecx, [esi + 0x1d54]
004fa40f 8bd8                     mov       ebx, eax
004fa411 e84a7cf0ff               call      0x402060
004fa416 85c0                     test      eax, eax
004fa418 745c                     je        0x4fa476
004fa41a e9d047ec00               jmp       0x13bebef
004fa41f 7dca                     jge       0x4fa3eb
004fa421 8f07                     pop       dword ptr [edi]
004fa423 d9c3                     fld       st(3)
004fa425 98                       cwde      
004fa426 28fb                     sub       bl, bh
004fa428 e30f                     jecxz     0x4fa439
004fa42a c9                       leave     
004fa42b 3cd5                     cmp       al, 0xd5
004fa42d fa                       cli       
004fa42e 45                       inc       ebp
004fa42f 1e                       push      ds
004fa430 52                       push      edx
004fa431 c1ceda                   ror       esi, 0xda
004fa434 7c14                     jl        0x4fa44a
004fa436 af                       scasd     eax, dword ptr es:[edi]
004fa437 75a4                     jne       0x4fa3dd
004fa439 dea8c3d917ea             fisubr    word ptr [eax - 0x15e8263d]
004fa43f 85975750b076             test      dword ptr [edi + 0x76b05057], edx
004fa445 7535                     jne       0x4fa47c
004fa447 8922                     mov       dword ptr [edx], esp
004fa449 44                       inc       esp
004fa44a f6a70864a859             mul       byte ptr [edi + 0x59a86408]
004fa450 0c09                     or        al, 9
004fa452 59                       pop       ecx
004fa453 b396                     mov       bl, 0x96
004fa455 718b                     jno       0x4fa3e2
004fa457 6e                       outsb     dx, byte ptr [esi]
004fa458 d994e476716bb2           fst       dword ptr [esp - 0x4d948e8a]
004fa45f 2646                     inc       esi
004fa461 cd47                     int       0x47
004fa463 4c                       dec       esp
004fa464 46                       inc       esi
004fa465 1bce                     sbb       ecx, esi
004fa467 0c94                     or        al, 0x94
004fa469 c9                       leave     
004fa46a 9b                       wait      
004fa46b b96ad80122               mov       ecx, 0x2201d86a
004fa470 4c                       dec       esp
004fa471 53                       push      ebx
004fa472 16                       push      ss
004fa473 8316f3                   adc       dword ptr [esi], -0xd
004fa476 e97e7eec00               jmp       0x13c22f9
004fa47b 64                       .byte     0x64
004fa47c dc                       .byte     0xdc
004fa47d d5a8                     aad       0xa8
004fa47f 001a                     add       byte ptr [edx], bl
004fa481 e81733c627               call      0x2815d79d
004fa486 2bb33e79df5f             sub       esi, dword ptr [ebx + 0x5fdf793e]
004fa48c d7                       xlatb     
004fa48d 96                       xchg      esi, eax
004fa48e 4d                       dec       ebp
004fa48f 667613                   jbe       0x4fa4a5
004fa492 cb                       retf      
004fa493 79a2                     jns       0x4fa437
004fa495 23995ef55eb9             and       ebx, dword ptr [ecx - 0x46a10aa2]
004fa49b d7                       xlatb     
004fa49c 00b32fed6267             add       byte ptr [ebx + 0x6762ed2f], dh
004fa4a2 2cf2                     sub       al, 0xf2
004fa4a4 99                       cdq       
004fa4a5 2f                       das       
004fa4a6 f305d58b0d80             add       eax, 0x800d8bd5
004fa4ac 42                       inc       edx
004fa4ad 0d016a048d               or        eax, 0x8d046a01
004fa4b2 55                       push      ebp
004fa4b3 e852897de8               call      0xe8cd2e0a
004fa4b8 e8133f5600               call      0xa5e3d0
004fa4bd 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa4c3 6a04                     push      4
004fa4c5 8d45e8                   lea       eax, [ebp - 0x18]
004fa4c8 50                       push      eax
004fa4c9 895de8                   mov       dword ptr [ebp - 0x18], ebx
004fa4cc e8ff3e5600               call      0xa5e3d0
004fa4d1 e951d6ec00               jmp       0x13c7b27
004fa4d6 f294                     xchg      esp, eax
004fa4d8 c7                       .byte     0xc7
004fa4d9 db17                     fist      dword ptr [edi]
004fa4db 0c0f                     or        al, 0xf
004fa4dd f8                       clc       
004fa4de 7b6d                     jnp       0x4fa54d
004fa4e0 45                       inc       ebp
004fa4e1 7723                     ja        0x4fa506
004fa4e3 d05bc9                   rcr       byte ptr [ebx - 0x37], 1
004fa4e6 30670a                   xor       byte ptr [edi + 0xa], ah
004fa4e9 dbc8                     fcmovne   st(0), st(0)
004fa4eb 025a89                   add       bl, byte ptr [edx - 0x77]
004fa4ee 39ef                     cmp       edi, ebp
004fa4f0 d99ba90c79ad             fstp      dword ptr [ebx - 0x5286f357]
004fa4f6 a4                       movsb     byte ptr es:[edi], byte ptr [esi]
004fa4f7 d6                       salc      
004fa4f8 d472                     aam       0x72
004fa4fa c22118                   ret       0x1821
004fa4fd 344e                     xor       al, 0x4e
004fa4ff e0b6                     loopne    0x4fa4b7
004fa501 4c                       dec       esp
004fa502 07                       pop       es
004fa503 0c9f                     or        al, 0x9f
004fa505 d308                     ror       dword ptr [eax], cl
004fa507 a078d03a6c               mov       al, byte ptr [0x6c3ad078]
004fa50c 3f                       aas       
004fa50d 16                       push      ss
004fa50e d7                       xlatb     
004fa50f 97                       xchg      edi, eax
004fa510 b92ec7c50b               mov       ecx, 0xbc5c72e
004fa515 ad                       lodsd     eax, dword ptr [esi]
004fa516 6e                       outsb     dx, byte ptr [esi]
004fa517 cb                       retf      
004fa518 ca0db9                   retf      0xb90d
004fa51b e405                     in        al, 5
004fa51d f0                       .byte     0xf0
004fa51e 3c63                     cmp       al, 0x63
004fa520 68f71d6a84               push      0x846a1df7
004fa525 91                       xchg      ecx, eax
004fa526 deb3ad465a55             fidiv     word ptr [ebx + 0x555a46ad]
004fa52c f5                       cmc       
004fa52d 235a80                   and       ebx, dword ptr [edx - 0x80]
004fa530 2f                       das       
004fa531 f0                       .byte     0xf0
004fa532 a6                       cmpsb     byte ptr [esi], byte ptr es:[edi]
004fa533 da                       .byte     0xda
004fa534 e42c                     in        al, 0x2c
004fa536 d9ea                     fldl2e    
004fa538 37                       aaa       
004fa539 f9                       stc       
004fa53a 27                       daa       
004fa53b 64e9785362dd             jmp       0xddb1f8b9
004fa541 51                       push      ecx
004fa542 8c5356                   mov       word ptr [ebx + 0x56], ss
004fa545 6a0f                     push      0xf
004fa547 767a                     jbe       0x4fa5c3
004fa549 a90d169541               test      eax, 0x4195160d
004fa54e 1e                       push      ds
004fa54f 3653                     push      ebx
004fa551 208b4f99a283             and       byte ptr [ebx - 0x7c5d66b1], cl
004fa557 0293e51ba797             add       dl, byte ptr [ebx - 0x6858e41b]
004fa55d 49                       dec       ecx
004fa55e db01                     fild      dword ptr [ecx]
004fa560 c3                       ret       
004fa561 00ef                     add       bh, ch
004fa563 8693e9cda097             xchg      byte ptr [ebx - 0x685f3217], dl
004fa569 c83eea76                 enter     -0x15c2, 0x76
004fa56d 2f                       das       
004fa56e 96                       xchg      esi, eax
004fa56f d5ea                     aad       0xea
004fa571 5b                       pop       ebx
004fa572 3b9e9e8bbdd4             cmp       ebx, dword ptr [esi - 0x2b427462]
004fa578 1321                     adc       esp, dword ptr [ecx]
004fa57a 7fea                     jg        0x4fa566
004fa57c 3debece829               cmp       eax, 0x29e8eceb
004fa581 52                       push      edx
004fa582 b2a7                     mov       dl, 0xa7
004fa584 847c1ecb                 test      byte ptr [esi + ebx - 0x35], bh
004fa588 1a4135                   sbb       al, byte ptr [ecx + 0x35]
004fa58b bdae327d9c               mov       ebp, 0x9c7d32ae
004fa590 153ead63eb               adc       eax, 0xeb63ad3e
004fa595 dab7360ac4c8             fidiv     dword ptr [edi - 0x373bf5ca]
004fa59b 25a8308ce0               and       eax, 0xe08c30a8
004fa5a0 0425                     add       al, 0x25
004fa5a2 ac                       lodsb     al, byte ptr [esi]
004fa5a3 7ba1                     jnp       0x4fa546
004fa5a5 a18f745e6a               mov       eax, dword ptr [0x6a5e748f]
004fa5aa c7c169819392             mov       ecx, 0x92938169
004fa5b0 cb                       retf      
004fa5b1 be5add9980               mov       esi, 0x8099dd5a
004fa5b6 34f6                     xor       al, 0xf6
004fa5b8 d7                       xlatb     
004fa5b9 7745                     ja        0x4fa600
004fa5bb 0940dd                   or        dword ptr [eax - 0x23], eax
004fa5be 77ab                     ja        0x4fa56b
004fa5c0 7186                     jno       0x4fa548
004fa5c2 3d6f2cba7e               cmp       eax, 0x7eba2c6f
004fa5c7 dcf7                     fdivr     st(7), st(0)
004fa5c9 01c7                     add       edi, eax
004fa5cb 7e47                     jle       0x4fa614
004fa5cd 27                       daa       
004fa5ce 52                       push      edx
004fa5cf f0                       .byte     0xf0
004fa5d0 a3952c38a5               mov       dword ptr [0xa5382c95], eax
004fa5d5 0a11                     or        dl, byte ptr [ecx]
004fa5d7 7a8a                     jp        0x4fa563
004fa5d9 8fc7                     pop       edi
004fa5db 6c                       insb      byte ptr es:[edi], dx
004fa5dc 3a40e4                   cmp       al, byte ptr [eax - 0x1c]
004fa5df 52                       push      edx
004fa5e0 7f95                     jg        0x4fa577
004fa5e2 e0b7                     loopne    0x4fa59b
004fa5e4 3cf8                     cmp       al, 0xf8
004fa5e6 9e                       sahf      
004fa5e7 3db7f3ad86               cmp       eax, 0x86adf3b7
004fa5ec 61                       popal     
004fa5ed 5d                       pop       ebp
004fa5ee 9d                       popfd     
004fa5ef d95963                   fstp      dword ptr [ecx + 0x63]
004fa5f2 f7ae24eed2ff             imul      dword ptr [esi - 0x2d11dc]
004fa5f8 22aa0b781562             and       ch, byte ptr [edx + 0x6215780b]
004fa5fe bf9abcbcfe               mov       edi, 0xfebcbc9a
004fa603 3c71                     cmp       al, 0x71
004fa605 716c                     jno       0x4fa673
004fa607 3c5f                     cmp       al, 0x5f
004fa609 6ace                     push      -0x32
004fa60b 6d                       insd      dword ptr es:[edi], dx
004fa60c 1a13                     sbb       dl, byte ptr [ebx]
004fa60e ef                       out       dx, eax
004fa60f 13924b69bbd5             adc       edx, dword ptr [edx - 0x2a4496b5]
004fa615 bd0e709d0e               mov       ebp, 0xe9d700e
004fa61a 1026                     adc       byte ptr [esi], ah
004fa61c b4df                     mov       ah, 0xdf
004fa61e 20a7821d8765             and       byte ptr [edi + 0x65871d82], ah
004fa624 16                       push      ss
004fa625 fd                       std       
004fa626 aa                       stosb     byte ptr es:[edi], al
004fa627 dc63c8                   fsub      qword ptr [ebx - 0x38]
004fa62a 9a5ff8abb0db5e           lcall     0x5edb, 0xb0abf85f
004fa631 07                       pop       es
004fa632 7e87                     jle       0x4fa5bb
004fa634 0c1f                     or        al, 0x1f
004fa636 82e514                   and       ch, 0x14
004fa639 96                       xchg      esi, eax
004fa63a 5c                       pop       esp
004fa63b fd                       std       
004fa63c 28a68266bdc1             sub       byte ptr [esi - 0x3e42997e], ah
004fa642 87d9                     xchg      ecx, ebx
004fa644 43                       inc       ebx
004fa645 ab                       stosd     dword ptr es:[edi], eax
004fa646 dda047e9a952             frstor    dword ptr [eax + 0x52a9e947]
004fa64c 32795b                   xor       bh, byte ptr [ecx + 0x5b]
004fa64f a05583df79               mov       al, byte ptr [0x79df8355]
004fa654 0e                       push      cs
004fa655 f4                       hlt       
004fa656 1e                       push      ds
004fa657 f3caa544                 retf      0x44a5
004fa65b e326                     jecxz     0x4fa683
004fa65d 55                       push      ebp
004fa65e a9f6329505               test      eax, 0x59532f6
004fa663 07                       pop       es
004fa664 6f                       outsd     dx, dword ptr [esi]
004fa665 36f2ab                   repne stosd dword ptr es:[edi], eax
004fa668 62                       .byte     0x62
004fa669 c5b89698c526             lds       edi, ptr [eax + 0x26c59896]
004fa66f 17                       pop       ss
004fa670 b1a3                     mov       cl, 0xa3
004fa672 a4                       movsb     byte ptr es:[edi], byte ptr [esi]
004fa673 fc                       cld       
004fa674 69f6f26bc557             imul      esi, esi, 0x57c56bf2
004fa67a ee                       out       dx, al
004fa67b e390                     jecxz     0x4fa60d
004fa67d 54                       push      esp
004fa67e 4a                       dec       edx
004fa67f a2d6caaae3               mov       byte ptr [0xe3aacad6], al
004fa684 6c                       insb      byte ptr es:[edi], dx
004fa685 362144afe5               and       dword ptr ss:[edi + ebp*4 - 0x1b], eax
004fa68a bfa70bc718               mov       edi, 0x18c70ba7
004fa68f ea801fd6ad4bb2           ljmp      0xb24b:0xadd61f80
004fa696 46                       inc       esi
004fa697 91                       xchg      ecx, eax
004fa698 a8fc                     test      al, 0xfc
004fa69a 0d4b526c17               or        eax, 0x176c524b
004fa69f a7                       cmpsd     dword ptr [esi], dword ptr es:[edi]
004fa6a0 13ea                     adc       ebp, edx
004fa6a2 8929                     mov       dword ptr [ecx], ebp
004fa6a4 e1e8                     loope     0x4fa68e
004fa6a6 c4b6b87115b1             les       esi, ptr [esi - 0x4eea8e48]
004fa6ac d18ad436f950             ror       dword ptr [edx + 0x50f936d4], 1
004fa6b2 8260cb74                 and       byte ptr [eax - 0x35], 0x74
004fa6b6 4a                       dec       edx
004fa6b7 42                       inc       edx
004fa6b8 bb74facefd               mov       ebx, 0xfdcefa74
004fa6bd 52                       push      edx
004fa6be 3ecc                     int3      
004fa6c0 59                       pop       ecx
004fa6c1 18bcbaee88843f           sbb       byte ptr [edx + edi*4 + 0x3f8488ee], bh
004fa6c8 3e17                     pop       ss
004fa6ca 39fd                     cmp       ebp, edi
004fa6cc 23620d                   and       esp, dword ptr [edx + 0xd]
004fa6cf 61                       popal     
004fa6d0 1a1f                     sbb       bl, byte ptr [edi]
004fa6d2 807a939d                 cmp       byte ptr [edx - 0x6d], 0x9d
004fa6d6 7f36                     jg        0x4fa70e
004fa6d8 c2bd05                   ret       0x5bd
004fa6db 8b55d8                   mov       edx, dword ptr [ebp - 0x28]
004fa6de 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa6e4 6a02                     push      2
004fa6e6 8d45d8                   lea       eax, [ebp - 0x28]
004fa6e9 50                       push      eax
004fa6ea 8955d8                   mov       dword ptr [ebp - 0x28], edx
004fa6ed e8de3c5600               call      0xa5e3d0
004fa6f2 8b4dd4                   mov       ecx, dword ptr [ebp - 0x2c]
004fa6f5 6a02                     push      2
004fa6f7 8d55d4                   lea       edx, [ebp - 0x2c]
004fa6fa 894dd4                   mov       dword ptr [ebp - 0x2c], ecx
004fa6fd 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa703 52                       push      edx
004fa704 e8c73c5600               call      0xa5e3d0
004fa709 8a86511d0000             mov       al, byte ptr [esi + 0x1d51]
004fa70f 6a01                     push      1
004fa711 8d4df0                   lea       ecx, [ebp - 0x10]
004fa714 51                       push      ecx
004fa715 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa71b 8845f0                   mov       byte ptr [ebp - 0x10], al
004fa71e e8ad3c5600               call      0xa5e3d0
004fa723 8b0d80420d01             mov       ecx, dword ptr [0x10d4280]
004fa729 6a01                     push      1
004fa72b 8d55f0                   lea       edx, [ebp - 0x10]
004fa72e 52                       push      edx
004fa72f c645f000                 mov       byte ptr [ebp - 0x10], 0
004fa733 e8983c5600               call      0xa5e3d0
004fa738 e99216ed00               jmp       0x13cbdcf
004fa73d d213                     rcl       byte ptr [ebx], cl
004fa73f 67                       .byte     0x67
