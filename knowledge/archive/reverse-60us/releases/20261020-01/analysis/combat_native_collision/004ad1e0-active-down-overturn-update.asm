004ad1e0 55                       push      ebp
004ad1e1 8bec                     mov       ebp, esp
004ad1e3 83ec08                   sub       esp, 8
004ad1e6 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004ad1e9 8b01                     mov       eax, dword ptr [ecx]
004ad1eb 56                       push      esi
004ad1ec 8b7510                   mov       esi, dword ptr [ebp + 0x10]
004ad1ef 52                       push      edx
004ad1f0 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004ad1f3 56                       push      esi
004ad1f4 52                       push      edx
004ad1f5 8d55fc                   lea       edx, [ebp - 4]
004ad1f8 52                       push      edx
004ad1f9 8d55f8                   lea       edx, [ebp - 8]
004ad1fc 52                       push      edx
004ad1fd c745f800000000           mov       dword ptr [ebp - 8], 0
004ad204 c745fc00000000           mov       dword ptr [ebp - 4], 0
004ad20b ff90d4030000             call      dword ptr [eax + 0x3d4]
004ad211 85f6                     test      esi, esi
004ad213 c7451400000000           mov       dword ptr [ebp + 0x14], 0
004ad21a 7507                     jne       0x4ad223
004ad21c b9b0fe0b01               mov       ecx, 0x10bfeb0
004ad221 eb0a                     jmp       0x4ad22d
004ad223 83fe01                   cmp       esi, 1
004ad226 750d                     jne       0x4ad235
004ad228 b9d0fe0b01               mov       ecx, 0x10bfed0
004ad22d e87e61f8ff               call      0x4333b0
004ad232 d95d14                   fstp      dword ptr [ebp + 0x14]
004ad235 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ad23b 6aff                     push      -1
004ad23d e8aed9f8ff               call      0x43abf0
004ad242 d94514                   fld       dword ptr [ebp + 0x14]
004ad245 84c0                     test      al, al
004ad247 5e                       pop       esi
004ad248 7402                     je        0x4ad24c
004ad24a dcc0                     fadd      st(0), st(0)
004ad24c d945fc                   fld       dword ptr [ebp - 4]
004ad24f d845f8                   fadd      dword ptr [ebp - 8]
004ad252 d8153009cd00             fcom      dword ptr [0xcd0930]
004ad258 dfe0                     fnstsw    ax
004ad25a f6c405                   test      ah, 5
004ad25d 7b08                     jnp       0x4ad267
004ad25f ddd8                     fstp      st(0)
004ad261 d9053009cd00             fld       dword ptr [0xcd0930]
004ad267 db450c                   fild      dword ptr [ebp + 0xc]
004ad26a 51                       push      ecx
004ad26b d8c9                     fmul      st(1)
004ad26d d8ca                     fmul      st(2)
004ad26f d905581fcc00             fld       dword ptr [0xcc1f58]
004ad275 d8e2                     fsub      st(2)
004ad277 def9                     fdivp     st(1)
004ad279 d91c24                   fstp      dword ptr [esp]
004ad27c ddd8                     fstp      st(0)
004ad27e ddd8                     fstp      st(0)
004ad280 e86badf9ff               call      0x447ff0
004ad285 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ad288 83c404                   add       esp, 4
004ad28b 8901                     mov       dword ptr [ecx], eax
004ad28d 8be5                     mov       esp, ebp
004ad28f 5d                       pop       ebp
004ad290 c21000                   ret       0x10
004ad293 cc                       int3      
004ad294 cc                       int3      
004ad295 cc                       int3      
004ad296 cc                       int3      
004ad297 cc                       int3      
004ad298 cc                       int3      
004ad299 cc                       int3      
004ad29a cc                       int3      
004ad29b cc                       int3      
004ad29c cc                       int3      
004ad29d cc                       int3      
004ad29e cc                       int3      
004ad29f cc                       int3      
004ad2a0 56                       push      esi
004ad2a1 8bf1                     mov       esi, ecx
004ad2a3 8d8e5c150000             lea       ecx, [esi + 0x155c]
004ad2a9 e8b24df5ff               call      0x402060
004ad2ae 83f809                   cmp       eax, 9
004ad2b1 0f85c9000000             jne       0x4ad380
004ad2b7 8b86b0160000             mov       eax, dword ptr [esi + 0x16b0]
004ad2bd 85c0                     test      eax, eax
004ad2bf 57                       push      edi
004ad2c0 8bce                     mov       ecx, esi
004ad2c2 750d                     jne       0x4ad2d1
004ad2c4 8b06                     mov       eax, dword ptr [esi]
004ad2c6 ff9094000000             call      dword ptr [eax + 0x94]
004ad2cc 8bf8                     mov       edi, eax
004ad2ce 4f                       dec       edi
004ad2cf eb0b                     jmp       0x4ad2dc
004ad2d1 8b16                     mov       edx, dword ptr [esi]
004ad2d3 ff9294000000             call      dword ptr [edx + 0x94]
004ad2d9 8bf8                     mov       edi, eax
004ad2db 47                       inc       edi
004ad2dc 8b86b0160000             mov       eax, dword ptr [esi + 0x16b0]
004ad2e2 53                       push      ebx
004ad2e3 50                       push      eax
004ad2e4 e877a6f9ff               call      0x447960
004ad2e9 8b1e                     mov       ebx, dword ptr [esi]
004ad2eb 83c404                   add       esp, 4
004ad2ee 6a00                     push      0
004ad2f0 8bce                     mov       ecx, esi
004ad2f2 8986b0160000             mov       dword ptr [esi + 0x16b0], eax
004ad2f8 ff9398000000             call      dword ptr [ebx + 0x98]
004ad2fe 50                       push      eax
004ad2ff 57                       push      edi
004ad300 8bce                     mov       ecx, esi
004ad302 ff93ac000000             call      dword ptr [ebx + 0xac]
004ad308 84c0                     test      al, al
004ad30a 7539                     jne       0x4ad345
004ad30c 8b86b0160000             mov       eax, dword ptr [esi + 0x16b0]
004ad312 85c0                     test      eax, eax
004ad314 8bce                     mov       ecx, esi
004ad316 750d                     jne       0x4ad325
004ad318 8b16                     mov       edx, dword ptr [esi]
004ad31a ff9294000000             call      dword ptr [edx + 0x94]
004ad320 8bf8                     mov       edi, eax
004ad322 4f                       dec       edi
004ad323 eb0b                     jmp       0x4ad330
004ad325 8b06                     mov       eax, dword ptr [esi]
004ad327 ff9094000000             call      dword ptr [eax + 0x94]
004ad32d 8bf8                     mov       edi, eax
004ad32f 47                       inc       edi
004ad330 8b8eb0160000             mov       ecx, dword ptr [esi + 0x16b0]
004ad336 51                       push      ecx
004ad337 e824a6f9ff               call      0x447960
004ad33c 83c404                   add       esp, 4
004ad33f 8986b0160000             mov       dword ptr [esi + 0x16b0], eax
004ad345 8b1e                     mov       ebx, dword ptr [esi]
004ad347 6a00                     push      0
004ad349 8bce                     mov       ecx, esi
004ad34b ff9398000000             call      dword ptr [ebx + 0x98]
004ad351 50                       push      eax
004ad352 57                       push      edi
004ad353 8bce                     mov       ecx, esi
004ad355 ff93ac000000             call      dword ptr [ebx + 0xac]
004ad35b 84c0                     test      al, al
004ad35d 741f                     je        0x4ad37e
004ad35f 8b1e                     mov       ebx, dword ptr [esi]
004ad361 8bce                     mov       ecx, esi
004ad363 ff939c000000             call      dword ptr [ebx + 0x9c]
004ad369 8b16                     mov       edx, dword ptr [esi]
004ad36b 50                       push      eax
004ad36c 8bce                     mov       ecx, esi
004ad36e ff9298000000             call      dword ptr [edx + 0x98]
004ad374 50                       push      eax
004ad375 57                       push      edi
004ad376 8bce                     mov       ecx, esi
004ad378 ff9388000000             call      dword ptr [ebx + 0x88]
004ad37e 5b                       pop       ebx
004ad37f 5f                       pop       edi
004ad380 5e                       pop       esi
004ad381 c3                       ret       
004ad382 cc                       int3      
004ad383 cc                       int3      
004ad384 cc                       int3      
004ad385 cc                       int3      
004ad386 cc                       int3      
004ad387 cc                       int3      
004ad388 cc                       int3      
004ad389 cc                       int3      
004ad38a cc                       int3      
004ad38b cc                       int3      
004ad38c cc                       int3      
004ad38d cc                       int3      
004ad38e cc                       int3      
004ad38f cc                       int3      
004ad390 56                       push      esi
004ad391 8bf1                     mov       esi, ecx
004ad393 8d8e5c150000             lea       ecx, [esi + 0x155c]
004ad399 e8c24cf5ff               call      0x402060
004ad39e 83f809                   cmp       eax, 9
004ad3a1 756f                     jne       0x4ad412
004ad3a3 53                       push      ebx
004ad3a4 57                       push      edi
004ad3a5 33db                     xor       ebx, ebx
004ad3a7 bf01000000               mov       edi, 1
004ad3ac 8d642400                 lea       esp, [esp]
004ad3b0 8b06                     mov       eax, dword ptr [esi]
004ad3b2 53                       push      ebx
004ad3b3 8bce                     mov       ecx, esi
004ad3b5 ff9074030000             call      dword ptr [eax + 0x374]
004ad3bb 398604010000             cmp       dword ptr [esi + 0x104], eax
004ad3c1 750f                     jne       0x4ad3d2
004ad3c3 8b16                     mov       edx, dword ptr [esi]
004ad3c5 57                       push      edi
004ad3c6 8bce                     mov       ecx, esi
004ad3c8 ff9274030000             call      dword ptr [edx + 0x374]
004ad3ce 85c0                     test      eax, eax
004ad3d0 750b                     jne       0x4ad3dd
004ad3d2 43                       inc       ebx
004ad3d3 4f                       dec       edi
004ad3d4 83ffff                   cmp       edi, -1
004ad3d7 7fd7                     jg        0x4ad3b0
004ad3d9 5f                       pop       edi
004ad3da 5b                       pop       ebx
004ad3db 5e                       pop       esi
004ad3dc c3                       ret       
004ad3dd 8b3e                     mov       edi, dword ptr [esi]
004ad3df b801000000               mov       eax, 1
004ad3e4 2bc3                     sub       eax, ebx
004ad3e6 50                       push      eax
004ad3e7 8bce                     mov       ecx, esi
004ad3e9 ff9774030000             call      dword ptr [edi + 0x374]
004ad3ef 50                       push      eax
004ad3f0 8bce                     mov       ecx, esi
004ad3f2 ff97f0000000             call      dword ptr [edi + 0xf0]
004ad3f8 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004ad3fe e85d9f5700               call      0xa27360
004ad403 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004ad409 6a01                     push      1
004ad40b e800ad5700               call      0xa28110
004ad410 5f                       pop       edi
004ad411 5b                       pop       ebx
004ad412 5e                       pop       esi
004ad413 c3                       ret       
004ad414 cc                       int3      
004ad415 cc                       int3      
004ad416 cc                       int3      
004ad417 cc                       int3      
004ad418 cc                       int3      
004ad419 cc                       int3      
004ad41a cc                       int3      
004ad41b cc                       int3      
004ad41c cc                       int3      
004ad41d cc                       int3      
004ad41e cc                       int3      
004ad41f cc                       int3      
004ad420 56                       push      esi
004ad421 8bf1                     mov       esi, ecx
004ad423 8b06                     mov       eax, dword ptr [esi]
004ad425 ff905c050000             call      dword ptr [eax + 0x55c]
004ad42b 84c0                     test      al, al
004ad42d 7504                     jne       0x4ad433
004ad42f 33c0                     xor       eax, eax
004ad431 5e                       pop       esi
004ad432 c3                       ret       
004ad433 8a867c180000             mov       al, byte ptr [esi + 0x187c]
004ad439 84c0                     test      al, al
004ad43b 741e                     je        0x4ad45b
004ad43d 8d8e20160000             lea       ecx, [esi + 0x1620]
004ad443 e8184cf5ff               call      0x402060
004ad448 8bc8                     mov       ecx, eax
004ad44a 8b8678180000             mov       eax, dword ptr [esi + 0x1878]
004ad450 69c0e8030000             imul      eax, eax, 0x3e8
004ad456 99                       cdq       
004ad457 f7f9                     idiv      ecx
004ad459 5e                       pop       esi
004ad45a c3                       ret       
004ad45b 8b8678180000             mov       eax, dword ptr [esi + 0x1878]
004ad461 5e                       pop       esi
004ad462 c3                       ret       
004ad463 cc                       int3      
004ad464 cc                       int3      
004ad465 cc                       int3      
004ad466 cc                       int3      
004ad467 cc                       int3      
004ad468 cc                       int3      
004ad469 cc                       int3      
004ad46a cc                       int3      
004ad46b cc                       int3      
004ad46c cc                       int3      
004ad46d cc                       int3      
004ad46e cc                       int3      
004ad46f cc                       int3      
004ad470 56                       push      esi
004ad471 8bf1                     mov       esi, ecx
004ad473 8b06                     mov       eax, dword ptr [esi]
004ad475 6a05                     push      5
004ad477 ff9010040000             call      dword ptr [eax + 0x410]
004ad47d 84c0                     test      al, al
004ad47f 7404                     je        0x4ad485
004ad481 33c0                     xor       eax, eax
004ad483 5e                       pop       esi
004ad484 c3                       ret       
004ad485 8d8ee0180000             lea       ecx, [esi + 0x18e0]
004ad48b 5e                       pop       esi
004ad48c e9cf4bf5ff               jmp       0x402060
004ad491 cc                       int3      
004ad492 cc                       int3      
004ad493 cc                       int3      
004ad494 cc                       int3      
004ad495 cc                       int3      
004ad496 cc                       int3      
004ad497 cc                       int3      
004ad498 cc                       int3      
004ad499 cc                       int3      
004ad49a cc                       int3      
004ad49b cc                       int3      
004ad49c cc                       int3      
004ad49d cc                       int3      
004ad49e cc                       int3      
004ad49f cc                       int3      
004ad4a0 56                       push      esi
004ad4a1 8bf1                     mov       esi, ecx
004ad4a3 8b06                     mov       eax, dword ptr [esi]
004ad4a5 57                       push      edi
004ad4a6 ff90f4000000             call      dword ptr [eax + 0xf4]
004ad4ac 85c0                     test      eax, eax
004ad4ae 0f8486010000             je        0x4ad63a
004ad4b4 8a863c190000             mov       al, byte ptr [esi + 0x193c]
004ad4ba 84c0                     test      al, al
004ad4bc 0f8478010000             je        0x4ad63a
004ad4c2 8a86d8010000             mov       al, byte ptr [esi + 0x1d8]
004ad4c8 84c0                     test      al, al
004ad4ca 0f856a010000             jne       0x4ad63a
004ad4d0 8b16                     mov       edx, dword ptr [esi]
004ad4d2 8bce                     mov       ecx, esi
004ad4d4 ff92dc030000             call      dword ptr [edx + 0x3dc]
004ad4da 84c0                     test      al, al
004ad4dc 0f8558010000             jne       0x4ad63a
004ad4e2 8b06                     mov       eax, dword ptr [esi]
004ad4e4 8bce                     mov       ecx, esi
004ad4e6 ff90f4000000             call      dword ptr [eax + 0xf4]
004ad4ec 8bf8                     mov       edi, eax
004ad4ee 83bf24010000ff           cmp       dword ptr [edi + 0x124], -1
004ad4f5 7507                     jne       0x4ad4fe
004ad4f7 8bcf                     mov       ecx, edi
004ad4f9 e862aa5700               call      0xa27f60
004ad4fe 8b8fdc000000             mov       ecx, dword ptr [edi + 0xdc]
004ad504 8b15f83e0d01             mov       edx, dword ptr [0x10d3ef8]
004ad50a 8d87dc000000             lea       eax, [edi + 0xdc]
004ad510 2bc8                     sub       ecx, eax
004ad512 33ca                     xor       ecx, edx
004ad514 83f901                   cmp       ecx, 1
004ad517 7428                     je        0x4ad541
004ad519 8d8ebc040000             lea       ecx, [esi + 0x4bc]
004ad51f e83c4bf5ff               call      0x402060
004ad524 83f801                   cmp       eax, 1
004ad527 0f850d010000             jne       0x4ad63a
004ad52d 8d8ec4040000             lea       ecx, [esi + 0x4c4]
004ad533 e8284bf5ff               call      0x402060
004ad538 83f801                   cmp       eax, 1
004ad53b 0f85f9000000             jne       0x4ad63a
004ad541 8b16                     mov       edx, dword ptr [esi]
004ad543 8bce                     mov       ecx, esi
004ad545 ff92f4000000             call      dword ptr [edx + 0xf4]
004ad54b 85c0                     test      eax, eax
004ad54d 746c                     je        0x4ad5bb
004ad54f 8b06                     mov       eax, dword ptr [esi]
004ad551 6a00                     push      0
004ad553 8bce                     mov       ecx, esi
004ad555 ff9074030000             call      dword ptr [eax + 0x374]
004ad55b 8b16                     mov       edx, dword ptr [esi]
004ad55d 8bce                     mov       ecx, esi
004ad55f 8bf8                     mov       edi, eax
004ad561 ff92f4000000             call      dword ptr [edx + 0xf4]
004ad567 3bc7                     cmp       eax, edi
004ad569 7450                     je        0x4ad5bb
004ad56b 8b06                     mov       eax, dword ptr [esi]
004ad56d 6a01                     push      1
004ad56f 8bce                     mov       ecx, esi
004ad571 ff9074030000             call      dword ptr [eax + 0x374]
004ad577 8b16                     mov       edx, dword ptr [esi]
004ad579 8bce                     mov       ecx, esi
004ad57b 8bf8                     mov       edi, eax
004ad57d ff92f4000000             call      dword ptr [edx + 0xf4]
004ad583 3bc7                     cmp       eax, edi
004ad585 7434                     je        0x4ad5bb
004ad587 8b06                     mov       eax, dword ptr [esi]
004ad589 8bce                     mov       ecx, esi
004ad58b ff9078030000             call      dword ptr [eax + 0x378]
004ad591 8b16                     mov       edx, dword ptr [esi]
004ad593 8bce                     mov       ecx, esi
004ad595 8bf8                     mov       edi, eax
004ad597 ff92f4000000             call      dword ptr [edx + 0xf4]
004ad59d 3bc7                     cmp       eax, edi
004ad59f 741a                     je        0x4ad5bb
004ad5a1 8b06                     mov       eax, dword ptr [esi]
004ad5a3 8bce                     mov       ecx, esi
004ad5a5 ff907c030000             call      dword ptr [eax + 0x37c]
004ad5ab 8b16                     mov       edx, dword ptr [esi]
004ad5ad 8bce                     mov       ecx, esi
004ad5af 8bf8                     mov       edi, eax
004ad5b1 ff92f4000000             call      dword ptr [edx + 0xf4]
004ad5b7 3bc7                     cmp       eax, edi
004ad5b9 757a                     jne       0x4ad635
004ad5bb 8b06                     mov       eax, dword ptr [esi]
004ad5bd 8bce                     mov       ecx, esi
004ad5bf ff9004010000             call      dword ptr [eax + 0x104]
004ad5c5 85c0                     test      eax, eax
004ad5c7 7471                     je        0x4ad63a
004ad5c9 8b16                     mov       edx, dword ptr [esi]
004ad5cb 6a00                     push      0
004ad5cd 8bce                     mov       ecx, esi
004ad5cf ff929c030000             call      dword ptr [edx + 0x39c]
004ad5d5 8bf8                     mov       edi, eax
004ad5d7 8b06                     mov       eax, dword ptr [esi]
004ad5d9 8bce                     mov       ecx, esi
004ad5db ff9004010000             call      dword ptr [eax + 0x104]
004ad5e1 3bc7                     cmp       eax, edi
004ad5e3 7455                     je        0x4ad63a
004ad5e5 8b16                     mov       edx, dword ptr [esi]
004ad5e7 6a01                     push      1
004ad5e9 8bce                     mov       ecx, esi
004ad5eb ff929c030000             call      dword ptr [edx + 0x39c]
004ad5f1 8bf8                     mov       edi, eax
004ad5f3 8b06                     mov       eax, dword ptr [esi]
004ad5f5 8bce                     mov       ecx, esi
004ad5f7 ff9004010000             call      dword ptr [eax + 0x104]
004ad5fd 3bc7                     cmp       eax, edi
004ad5ff 7439                     je        0x4ad63a
004ad601 8b16                     mov       edx, dword ptr [esi]
004ad603 8bce                     mov       ecx, esi
004ad605 ff92a0030000             call      dword ptr [edx + 0x3a0]
004ad60b 8bf8                     mov       edi, eax
004ad60d 8b06                     mov       eax, dword ptr [esi]
004ad60f 8bce                     mov       ecx, esi
004ad611 ff9004010000             call      dword ptr [eax + 0x104]
004ad617 3bc7                     cmp       eax, edi
004ad619 741f                     je        0x4ad63a
004ad61b 8b16                     mov       edx, dword ptr [esi]
004ad61d 8bce                     mov       ecx, esi
004ad61f ff92a4030000             call      dword ptr [edx + 0x3a4]
004ad625 8bf8                     mov       edi, eax
004ad627 8b06                     mov       eax, dword ptr [esi]
004ad629 8bce                     mov       ecx, esi
004ad62b ff9004010000             call      dword ptr [eax + 0x104]
004ad631 3bc7                     cmp       eax, edi
004ad633 7405                     je        0x4ad63a
004ad635 5f                       pop       edi
004ad636 b001                     mov       al, 1
004ad638 5e                       pop       esi
004ad639 c3                       ret       
004ad63a 5f                       pop       edi
004ad63b 32c0                     xor       al, al
004ad63d 5e                       pop       esi
004ad63e c3                       ret       
004ad63f cc                       int3      
004ad640 55                       push      ebp
004ad641 8bec                     mov       ebp, esp
004ad643 51                       push      ecx
004ad644 56                       push      esi
004ad645 57                       push      edi
004ad646 c745fc00000000           mov       dword ptr [ebp - 4], 0
004ad64d 8db1ec140000             lea       esi, [ecx + 0x14ec]
004ad653 bf17000000               mov       edi, 0x17
004ad658 8b06                     mov       eax, dword ptr [esi]
004ad65a 85c0                     test      eax, eax
004ad65c 741d                     je        0x4ad67b
004ad65e 8bc8                     mov       ecx, eax
004ad660 8b01                     mov       eax, dword ptr [ecx]
004ad662 ff90e4000000             call      dword ptr [eax + 0xe4]
004ad668 8bc8                     mov       ecx, eax
004ad66a 81c120020000             add       ecx, 0x220
004ad670 e83b5df8ff               call      0x4333b0
004ad675 d845fc                   fadd      dword ptr [ebp - 4]
004ad678 d95dfc                   fstp      dword ptr [ebp - 4]
004ad67b 83c604                   add       esi, 4
004ad67e 4f                       dec       edi
004ad67f 75d7                     jne       0x4ad658
004ad681 d945fc                   fld       dword ptr [ebp - 4]
004ad684 5f                       pop       edi
004ad685 5e                       pop       esi
004ad686 8be5                     mov       esp, ebp
004ad688 5d                       pop       ebp
004ad689 c3                       ret       
004ad68a cc                       int3      
004ad68b cc                       int3      
004ad68c cc                       int3      
004ad68d cc                       int3      
004ad68e cc                       int3      
004ad68f cc                       int3      
004ad690 56                       push      esi
004ad691 8bf1                     mov       esi, ecx
004ad693 8b06                     mov       eax, dword ptr [esi]
004ad695 6a00                     push      0
004ad697 ff9074030000             call      dword ptr [eax + 0x374]
004ad69d 85c0                     test      eax, eax
004ad69f 740e                     je        0x4ad6af
004ad6a1 8b16                     mov       edx, dword ptr [esi]
004ad6a3 8bce                     mov       ecx, esi
004ad6a5 ff9278030000             call      dword ptr [edx + 0x378]
004ad6ab 85c0                     test      eax, eax
004ad6ad 751e                     jne       0x4ad6cd
004ad6af 8b06                     mov       eax, dword ptr [esi]
004ad6b1 6a00                     push      0
004ad6b3 8bce                     mov       ecx, esi
004ad6b5 ff909c030000             call      dword ptr [eax + 0x39c]
004ad6bb 85c0                     test      eax, eax
004ad6bd 7551                     jne       0x4ad710
004ad6bf 8b16                     mov       edx, dword ptr [esi]
004ad6c1 8bce                     mov       ecx, esi
004ad6c3 ff92a0030000             call      dword ptr [edx + 0x3a0]
004ad6c9 85c0                     test      eax, eax
004ad6cb 7443                     je        0x4ad710
004ad6cd 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ad6d3 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ad6d6 8b86a8160000             mov       eax, dword ptr [esi + 0x16a8]
004ad6dc 8d0482                   lea       eax, [edx + eax*4]
004ad6df 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004ad6e5 8bc8                     mov       ecx, eax
004ad6e7 33ca                     xor       ecx, edx
004ad6e9 83f101                   xor       ecx, 1
004ad6ec 8908                     mov       dword ptr [eax], ecx
004ad6ee 8b96a8160000             mov       edx, dword ptr [esi + 0x16a8]
004ad6f4 a1d8012101               mov       eax, dword ptr [0x12101d8]
004ad6f9 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004ad6fc 8b35dc012101             mov       esi, dword ptr [0x12101dc]
004ad702 8d0491                   lea       eax, [ecx + edx*4]
004ad705 8bd0                     mov       edx, eax
004ad707 33d6                     xor       edx, esi
004ad709 83f201                   xor       edx, 1
004ad70c 8910                     mov       dword ptr [eax], edx
004ad70e 5e                       pop       esi
004ad70f c3                       ret       
004ad710 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ad716 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ad719 8b86a8160000             mov       eax, dword ptr [esi + 0x16a8]
004ad71f 8d0482                   lea       eax, [edx + eax*4]
004ad722 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004ad728 8bc8                     mov       ecx, eax
004ad72a 33ca                     xor       ecx, edx
004ad72c 8908                     mov       dword ptr [eax], ecx
004ad72e a1d8012101               mov       eax, dword ptr [0x12101d8]
004ad733 8b96a8160000             mov       edx, dword ptr [esi + 0x16a8]
004ad739 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004ad73c 8d0491                   lea       eax, [ecx + edx*4]
004ad73f 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ad745 8bd0                     mov       edx, eax
004ad747 33d1                     xor       edx, ecx
004ad749 8910                     mov       dword ptr [eax], edx
004ad74b 5e                       pop       esi
004ad74c c3                       ret       
004ad74d cc                       int3      
004ad74e cc                       int3      
004ad74f cc                       int3      
004ad750 55                       push      ebp
004ad751 8bec                     mov       ebp, esp
004ad753 83ec08                   sub       esp, 8
004ad756 53                       push      ebx
004ad757 56                       push      esi
004ad758 8bf1                     mov       esi, ecx
004ad75a 57                       push      edi
004ad75b 8d8ea0000000             lea       ecx, [esi + 0xa0]
004ad761 8dbeac150000             lea       edi, [esi + 0x15ac]
004ad767 e894976500               call      0xb06f00
004ad76c 8bcf                     mov       ecx, edi
004ad76e 8bd8                     mov       ebx, eax
004ad770 e8eb48f5ff               call      0x402060
004ad775 2bd8                     sub       ebx, eax
004ad777 8d8ea0000000             lea       ecx, [esi + 0xa0]
004ad77d 895df8                   mov       dword ptr [ebp - 8], ebx
004ad780 e87b976500               call      0xb06f00
004ad785 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004ad78b 8b5244                   mov       edx, dword ptr [edx + 0x44]
004ad78e 8b4f04                   mov       ecx, dword ptr [edi + 4]
004ad791 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004ad797 8d0c8a                   lea       ecx, [edx + ecx*4]
004ad79a 8bd1                     mov       edx, ecx
004ad79c 33d3                     xor       edx, ebx
004ad79e 33d0                     xor       edx, eax
004ad7a0 8911                     mov       dword ptr [ecx], edx
004ad7a2 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004ad7a8 8b5248                   mov       edx, dword ptr [edx + 0x48]
004ad7ab 8b4f04                   mov       ecx, dword ptr [edi + 4]
004ad7ae 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004ad7b4 8d0c8a                   lea       ecx, [edx + ecx*4]
004ad7b7 8bd1                     mov       edx, ecx
004ad7b9 33d3                     xor       edx, ebx
004ad7bb 33d0                     xor       edx, eax
004ad7bd 8911                     mov       dword ptr [ecx], edx
004ad7bf 8b06                     mov       eax, dword ptr [esi]
004ad7c1 6a03                     push      3
004ad7c3 8bce                     mov       ecx, esi
004ad7c5 ff9044030000             call      dword ptr [eax + 0x344]
004ad7cb db45f8                   fild      dword ptr [ebp - 8]
004ad7ce 8bf8                     mov       edi, eax
004ad7d0 8d8fc8010000             lea       ecx, [edi + 0x1c8]
004ad7d6 d95df8                   fstp      dword ptr [ebp - 8]
004ad7d9 e88248f5ff               call      0x402060
004ad7de 8945fc                   mov       dword ptr [ebp - 4], eax
004ad7e1 db45fc                   fild      dword ptr [ebp - 4]
004ad7e4 8d8fd0010000             lea       ecx, [edi + 0x1d0]
004ad7ea d95dfc                   fstp      dword ptr [ebp - 4]
004ad7ed e8be5bf8ff               call      0x4333b0
004ad7f2 d84dfc                   fmul      dword ptr [ebp - 4]
004ad7f5 e84a3d7500               call      0xc01544
004ad7fa 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ad800 8945fc                   mov       dword ptr [ebp - 4], eax
004ad803 db45fc                   fild      dword ptr [ebp - 4]
004ad806 81c140100000             add       ecx, 0x1040
004ad80c d84df8                   fmul      dword ptr [ebp - 8]
004ad80f d80d1009cd00             fmul      dword ptr [0xcd0910]
004ad815 d80df811cc00             fmul      dword ptr [0xcc11f8]
004ad81b d95dfc                   fstp      dword ptr [ebp - 4]
004ad81e e83d48f5ff               call      0x402060
004ad823 83f804                   cmp       eax, 4
004ad826 7411                     je        0x4ad839
004ad828 6a02                     push      2
004ad82a 56                       push      esi
004ad82b e8e0b3f9ff               call      0x448c10
004ad830 d84dfc                   fmul      dword ptr [ebp - 4]
004ad833 83c408                   add       esp, 8
004ad836 d95dfc                   fstp      dword ptr [ebp - 4]
004ad839 8d4dfc                   lea       ecx, [ebp - 4]
004ad83c 8dbebc150000             lea       edi, [esi + 0x15bc]
004ad842 51                       push      ecx
004ad843 8bcf                     mov       ecx, edi
004ad845 e8c690fbff               call      0x466910
004ad84a 8bcf                     mov       ecx, edi
004ad84c e85f5bf8ff               call      0x4333b0
004ad851 d9e1                     fabs      
004ad853 dc1da0b5cc00             fcomp     qword ptr [0xccb5a0]
004ad859 dfe0                     fnstsw    ax
004ad85b f6c401                   test      ah, 1
004ad85e 7541                     jne       0x4ad8a1
004ad860 8bcf                     mov       ecx, edi
004ad862 e8495bf8ff               call      0x4333b0
004ad867 e8d83c7500               call      0xc01544
004ad86c 8b1e                     mov       ebx, dword ptr [esi]
004ad86e 6a00                     push      0
004ad870 6a00                     push      0
004ad872 8bce                     mov       ecx, esi
004ad874 8945fc                   mov       dword ptr [ebp - 4], eax
004ad877 ff9360030000             call      dword ptr [ebx + 0x360]
004ad87d 8bc8                     mov       ecx, eax
004ad87f e8dc47f5ff               call      0x402060
004ad884 0345fc                   add       eax, dword ptr [ebp - 4]
004ad887 50                       push      eax
004ad888 8bce                     mov       ecx, esi
004ad88a ff93e8030000             call      dword ptr [ebx + 0x3e8]
004ad890 db45fc                   fild      dword ptr [ebp - 4]
004ad893 8d55fc                   lea       edx, [ebp - 4]
004ad896 52                       push      edx
004ad897 8bcf                     mov       ecx, edi
004ad899 d95dfc                   fstp      dword ptr [ebp - 4]
004ad89c e8ff7a0000               call      0x4b53a0
004ad8a1 8b06                     mov       eax, dword ptr [esi]
004ad8a3 6a03                     push      3
004ad8a5 8bce                     mov       ecx, esi
004ad8a7 ff9044030000             call      dword ptr [eax + 0x344]
004ad8ad 8bf8                     mov       edi, eax
004ad8af 8d8fd8010000             lea       ecx, [edi + 0x1d8]
004ad8b5 e8a647f5ff               call      0x402060
004ad8ba 8945fc                   mov       dword ptr [ebp - 4], eax
004ad8bd db45fc                   fild      dword ptr [ebp - 4]
004ad8c0 8d8fe0010000             lea       ecx, [edi + 0x1e0]
004ad8c6 d95dfc                   fstp      dword ptr [ebp - 4]
004ad8c9 e8e25af8ff               call      0x4333b0
004ad8ce d84dfc                   fmul      dword ptr [ebp - 4]
004ad8d1 e86e3c7500               call      0xc01544
004ad8d6 8945fc                   mov       dword ptr [ebp - 4], eax
004ad8d9 db45fc                   fild      dword ptr [ebp - 4]
004ad8dc 8d4df8                   lea       ecx, [ebp - 8]
004ad8df 8dbeb4150000             lea       edi, [esi + 0x15b4]
004ad8e5 d84df8                   fmul      dword ptr [ebp - 8]
004ad8e8 51                       push      ecx
004ad8e9 8bcf                     mov       ecx, edi
004ad8eb d80d0c09cd00             fmul      dword ptr [0xcd090c]
004ad8f1 d80df811cc00             fmul      dword ptr [0xcc11f8]
004ad8f7 d95df8                   fstp      dword ptr [ebp - 8]
004ad8fa e81190fbff               call      0x466910
004ad8ff 8bcf                     mov       ecx, edi
004ad901 e8aa5af8ff               call      0x4333b0
004ad906 d9e1                     fabs      
004ad908 dc1da0b5cc00             fcomp     qword ptr [0xccb5a0]
004ad90e dfe0                     fnstsw    ax
004ad910 f6c401                   test      ah, 1
004ad913 7542                     jne       0x4ad957
004ad915 8bcf                     mov       ecx, edi
004ad917 e8945af8ff               call      0x4333b0
004ad91c e8                       .byte     0xe8
004ad91d 23                       .byte     0x23
004ad91e 3c75                     cmp       al, 0x75
