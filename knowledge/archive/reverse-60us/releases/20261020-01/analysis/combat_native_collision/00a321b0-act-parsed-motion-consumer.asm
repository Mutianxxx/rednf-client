00a321b0 55                       push      ebp
00a321b1 8bec                     mov       ebp, esp
00a321b3 6aff                     push      -1
00a321b5 68a4e9c800               push      0xc8e9a4
00a321ba 64a100000000             mov       eax, dword ptr fs:[0]
00a321c0 50                       push      eax
00a321c1 64892500000000           mov       dword ptr fs:[0], esp
00a321c8 83ec38                   sub       esp, 0x38
00a321cb 53                       push      ebx
00a321cc 8b5d08                   mov       ebx, dword ptr [ebp + 8]
00a321cf 85db                     test      ebx, ebx
00a321d1 57                       push      edi
00a321d2 8bf9                     mov       edi, ecx
00a321d4 897df0                   mov       dword ptr [ebp - 0x10], edi
00a321d7 7522                     jne       0xa321fb
00a321d9 683455e400               push      0xe45534
00a321de ff15bc2eff00             call      dword ptr [0xff2ebc]
00a321e4 83c404                   add       esp, 4
00a321e7 5f                       pop       edi
00a321e8 32c0                     xor       al, al
00a321ea 5b                       pop       ebx
00a321eb 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a321ee 64890d00000000           mov       dword ptr fs:[0], ecx
00a321f5 8be5                     mov       esp, ebp
00a321f7 5d                       pop       ebp
00a321f8 c20800                   ret       8
00a321fb 56                       push      esi
00a321fc 68e8010000               push      0x1e8
00a32201 e84a1a9dff               call      0x403c50
00a32206 83c404                   add       esp, 4
00a32209 8945e8                   mov       dword ptr [ebp - 0x18], eax
00a3220c 85c0                     test      eax, eax
00a3220e c745fc00000000           mov       dword ptr [ebp - 4], 0
00a32215 be08000000               mov       esi, 8
00a3221a 7423                     je        0xa3223f
00a3221c 39731c                   cmp       dword ptr [ebx + 0x1c], esi
00a3221f 720f                     jb        0xa32230
00a32221 8b4b08                   mov       ecx, dword ptr [ebx + 8]
00a32224 6a01                     push      1
00a32226 51                       push      ecx
00a32227 8bc8                     mov       ecx, eax
00a32229 e8a214a6ff               call      0x4936d0
00a3222e eb11                     jmp       0xa32241
00a32230 8d4b08                   lea       ecx, [ebx + 8]
00a32233 6a01                     push      1
00a32235 51                       push      ecx
00a32236 8bc8                     mov       ecx, eax
00a32238 e89314a6ff               call      0x4936d0
00a3223d eb02                     jmp       0xa32241
00a3223f 33c0                     xor       eax, eax
00a32241 85c0                     test      eax, eax
00a32243 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00a3224a 894720                   mov       dword ptr [edi + 0x20], eax
00a3224d 7408                     je        0xa32257
00a3224f 89b89c010000             mov       dword ptr [eax + 0x19c], edi
00a32255 eb1c                     jmp       0xa32273
00a32257 39731c                   cmp       dword ptr [ebx + 0x1c], esi
00a3225a 7205                     jb        0xa32261
00a3225c 8b4308                   mov       eax, dword ptr [ebx + 8]
00a3225f eb03                     jmp       0xa32264
00a32261 8d4308                   lea       eax, [ebx + 8]
00a32264 50                       push      eax
00a32265 681455e400               push      0xe45514
00a3226a ff15bc2eff00             call      dword ptr [0xff2ebc]
00a32270 83c408                   add       esp, 8
00a32273 8b4728                   mov       eax, dword ptr [edi + 0x28]
00a32276 83c724                   add       edi, 0x24
00a32279 85c0                     test      eax, eax
00a3227b 7409                     je        0xa32286
00a3227d 50                       push      eax
00a3227e e85add1c00               call      0xbfffdd
00a32283 83c404                   add       esp, 4
00a32286 33c0                     xor       eax, eax
00a32288 894704                   mov       dword ptr [edi + 4], eax
00a3228b 894708                   mov       dword ptr [edi + 8], eax
00a3228e 89470c                   mov       dword ptr [edi + 0xc], eax
00a32291 8b7328                   mov       esi, dword ptr [ebx + 0x28]
00a32294 8b4324                   mov       eax, dword ptr [ebx + 0x24]
00a32297 8bce                     mov       ecx, esi
00a32299 2bc8                     sub       ecx, eax
00a3229b b8e9a28b2e               mov       eax, 0x2e8ba2e9
00a322a0 f7e9                     imul      ecx
00a322a2 c1fa03                   sar       edx, 3
00a322a5 8bc2                     mov       eax, edx
00a322a7 c1e81f                   shr       eax, 0x1f
00a322aa 68c0cfa200               push      0xa2cfc0
00a322af 03c2                     add       eax, edx
00a322b1 50                       push      eax
00a322b2 8b4324                   mov       eax, dword ptr [ebx + 0x24]
00a322b5 56                       push      esi
00a322b6 50                       push      eax
00a322b7 e844270000               call      0xa34a00
00a322bc 8b7324                   mov       esi, dword ptr [ebx + 0x24]
00a322bf 8b4328                   mov       eax, dword ptr [ebx + 0x28]
00a322c2 83c410                   add       esp, 0x10
00a322c5 3bf0                     cmp       esi, eax
00a322c7 747f                     je        0xa32348
00a322c9 c645e400                 mov       byte ptr [ebp - 0x1c], 0
00a322cd 8d4900                   lea       ecx, [ecx]
00a322d0 8b4e20                   mov       ecx, dword ptr [esi + 0x20]
00a322d3 8b561c                   mov       edx, dword ptr [esi + 0x1c]
00a322d6 8b4624                   mov       eax, dword ptr [esi + 0x24]
00a322d9 894dd8                   mov       dword ptr [ebp - 0x28], ecx
00a322dc 8b4e28                   mov       ecx, dword ptr [esi + 0x28]
00a322df 68e8010000               push      0x1e8
00a322e4 8955d4                   mov       dword ptr [ebp - 0x2c], edx
00a322e7 8945dc                   mov       dword ptr [ebp - 0x24], eax
00a322ea 894de0                   mov       dword ptr [ebp - 0x20], ecx
00a322ed e85e199dff               call      0x403c50
00a322f2 83c404                   add       esp, 4
00a322f5 8945e8                   mov       dword ptr [ebp - 0x18], eax
00a322f8 85c0                     test      eax, eax
00a322fa c745fc01000000           mov       dword ptr [ebp - 4], 1
00a32301 7424                     je        0xa32327
00a32303 837e1808                 cmp       dword ptr [esi + 0x18], 8
00a32307 720f                     jb        0xa32318
00a32309 8b4e04                   mov       ecx, dword ptr [esi + 4]
00a3230c 6a01                     push      1
00a3230e 51                       push      ecx
00a3230f 8bc8                     mov       ecx, eax
00a32311 e8ba13a6ff               call      0x4936d0
00a32316 eb11                     jmp       0xa32329
00a32318 8d4e04                   lea       ecx, [esi + 4]
00a3231b 6a01                     push      1
00a3231d 51                       push      ecx
00a3231e 8bc8                     mov       ecx, eax
00a32320 e8ab13a6ff               call      0x4936d0
00a32325 eb02                     jmp       0xa32329
00a32327 33c0                     xor       eax, eax
00a32329 8d55d0                   lea       edx, [ebp - 0x30]
00a3232c 52                       push      edx
00a3232d 8bcf                     mov       ecx, edi
00a3232f c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00a32336 8945d0                   mov       dword ptr [ebp - 0x30], eax
00a32339 e8f21c0000               call      0xa34030
00a3233e 8b4328                   mov       eax, dword ptr [ebx + 0x28]
00a32341 83c62c                   add       esi, 0x2c
00a32344 3bf0                     cmp       esi, eax
00a32346 7588                     jne       0xa322d0
00a32348 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
00a3234b 8b7754                   mov       esi, dword ptr [edi + 0x54]
00a3234e 83c750                   add       edi, 0x50
00a32351 33c9                     xor       ecx, ecx
00a32353 3bf1                     cmp       esi, ecx
00a32355 746f                     je        0xa323c6
00a32357 8b4708                   mov       eax, dword ptr [edi + 8]
00a3235a 3bf0                     cmp       esi, eax
00a3235c 8945ec                   mov       dword ptr [ebp - 0x14], eax
00a3235f 7459                     je        0xa323ba
00a32361 83c61c                   add       esi, 0x1c
00a32364 8b06                     mov       eax, dword ptr [esi]
00a32366 3bc1                     cmp       eax, ecx
00a32368 740b                     je        0xa32375
00a3236a 50                       push      eax
00a3236b e86ddc1c00               call      0xbfffdd
00a32370 83c404                   add       esp, 4
00a32373 33c9                     xor       ecx, ecx
00a32375 890e                     mov       dword ptr [esi], ecx
00a32377 894e04                   mov       dword ptr [esi + 4], ecx
00a3237a 894e08                   mov       dword ptr [esi + 8], ecx
00a3237d 8b46e8                   mov       eax, dword ptr [esi - 0x18]
00a32380 3bc1                     cmp       eax, ecx
00a32382 7420                     je        0xa323a4
00a32384 8b550c                   mov       edx, dword ptr [ebp + 0xc]
00a32387 8b4eec                   mov       ecx, dword ptr [esi - 0x14]
00a3238a 52                       push      edx
00a3238b 8d56e4                   lea       edx, [esi - 0x1c]
00a3238e 52                       push      edx
00a3238f 51                       push      ecx
00a32390 50                       push      eax
00a32391 e85a28a1ff               call      0x444bf0
00a32396 8b46e8                   mov       eax, dword ptr [esi - 0x18]
00a32399 50                       push      eax
00a3239a e83edc1c00               call      0xbfffdd
00a3239f 83c414                   add       esp, 0x14
00a323a2 33c9                     xor       ecx, ecx
00a323a4 8b55ec                   mov       edx, dword ptr [ebp - 0x14]
00a323a7 894ee8                   mov       dword ptr [esi - 0x18], ecx
00a323aa 894eec                   mov       dword ptr [esi - 0x14], ecx
00a323ad 894ef0                   mov       dword ptr [esi - 0x10], ecx
00a323b0 83c62c                   add       esi, 0x2c
00a323b3 8d46e4                   lea       eax, [esi - 0x1c]
00a323b6 3bc2                     cmp       eax, edx
00a323b8 75aa                     jne       0xa32364
00a323ba 8b4704                   mov       eax, dword ptr [edi + 4]
00a323bd 50                       push      eax
00a323be e81adc1c00               call      0xbfffdd
00a323c3 83c404                   add       esp, 4
00a323c6 33c0                     xor       eax, eax
00a323c8 894704                   mov       dword ptr [edi + 4], eax
00a323cb 894708                   mov       dword ptr [edi + 8], eax
00a323ce 89470c                   mov       dword ptr [edi + 0xc], eax
00a323d1 8b7348                   mov       esi, dword ptr [ebx + 0x48]
00a323d4 8b4344                   mov       eax, dword ptr [ebx + 0x44]
00a323d7 8bce                     mov       ecx, esi
00a323d9 2bc8                     sub       ecx, eax
00a323db b8398ee338               mov       eax, 0x38e38e39
00a323e0 f7e9                     imul      ecx
00a323e2 8b4344                   mov       eax, dword ptr [ebx + 0x44]
00a323e5 c1fa03                   sar       edx, 3
00a323e8 8bca                     mov       ecx, edx
00a323ea c1e91f                   shr       ecx, 0x1f
00a323ed 6800d0a200               push      0xa2d000
00a323f2 03ca                     add       ecx, edx
00a323f4 51                       push      ecx
00a323f5 56                       push      esi
00a323f6 50                       push      eax
00a323f7 e844270000               call      0xa34b40
00a323fc 8b7334                   mov       esi, dword ptr [ebx + 0x34]
00a323ff 8b5b38                   mov       ebx, dword ptr [ebx + 0x38]
00a32402 83c410                   add       esp, 0x10
00a32405 3bf3                     cmp       esi, ebx
00a32407 0f8472010000             je        0xa3257f
00a3240d 8d4900                   lea       ecx, [ecx]
00a32410 8b4704                   mov       eax, dword ptr [edi + 4]
00a32413 33db                     xor       ebx, ebx
00a32415 3bc3                     cmp       eax, ebx
00a32417 7504                     jne       0xa3241d
00a32419 33c0                     xor       eax, eax
00a3241b eb16                     jmp       0xa32433
00a3241d 8b4f08                   mov       ecx, dword ptr [edi + 8]
00a32420 2bc8                     sub       ecx, eax
00a32422 b8e9a28b2e               mov       eax, 0x2e8ba2e9
00a32427 f7e9                     imul      ecx
00a32429 c1fa03                   sar       edx, 3
00a3242c 8bc2                     mov       eax, edx
00a3242e c1e81f                   shr       eax, 0x1f
00a32431 03c2                     add       eax, edx
00a32433 8b4e1c                   mov       ecx, dword ptr [esi + 0x1c]
00a32436 3bc1                     cmp       eax, ecx
00a32438 774d                     ja        0xa32487
00a3243a 895dc0                   mov       dword ptr [ebp - 0x40], ebx
00a3243d 895dc4                   mov       dword ptr [ebp - 0x3c], ebx
00a32440 895dc8                   mov       dword ptr [ebp - 0x38], ebx
00a32443 895dd8                   mov       dword ptr [ebp - 0x28], ebx
00a32446 895ddc                   mov       dword ptr [ebp - 0x24], ebx
00a32449 895de0                   mov       dword ptr [ebp - 0x20], ebx
00a3244c c745ccffffffff           mov       dword ptr [ebp - 0x34], 0xffffffff
00a32453 c645d000                 mov       byte ptr [ebp - 0x30], 0
00a32457 895de4                   mov       dword ptr [ebp - 0x1c], ebx
00a3245a 8d55bc                   lea       edx, [ebp - 0x44]
00a3245d 52                       push      edx
00a3245e 8bcf                     mov       ecx, edi
00a32460 c745fc03000000           mov       dword ptr [ebp - 4], 3
00a32467 e814370000               call      0xa35b80
00a3246c c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00a32473 895dd8                   mov       dword ptr [ebp - 0x28], ebx
00a32476 895ddc                   mov       dword ptr [ebp - 0x24], ebx
00a32479 895de0                   mov       dword ptr [ebp - 0x20], ebx
00a3247c 895dc0                   mov       dword ptr [ebp - 0x40], ebx
00a3247f 895dc4                   mov       dword ptr [ebp - 0x3c], ebx
00a32482 895dc8                   mov       dword ptr [ebp - 0x38], ebx
00a32485 eb89                     jmp       0xa32410
00a32487 8b5f04                   mov       ebx, dword ptr [edi + 4]
00a3248a 85db                     test      ebx, ebx
00a3248c 0f84dc010000             je        0xa3266e
00a32492 8b5708                   mov       edx, dword ptr [edi + 8]
00a32495 2bd3                     sub       edx, ebx
00a32497 b8e9a28b2e               mov       eax, 0x2e8ba2e9
00a3249c f7ea                     imul      edx
00a3249e c1fa03                   sar       edx, 3
00a324a1 8bc2                     mov       eax, edx
00a324a3 c1e81f                   shr       eax, 0x1f
00a324a6 03c2                     add       eax, edx
00a324a8 3bc1                     cmp       eax, ecx
00a324aa 0f86be010000             jbe       0xa3266e
00a324b0 6bc92c                   imul      ecx, ecx, 0x2c
00a324b3 03cb                     add       ecx, ebx
00a324b5 56                       push      esi
00a324b6 e8e574a9ff               call      0x4c99a0
00a324bb 8b5f04                   mov       ebx, dword ptr [edi + 4]
00a324be 85db                     test      ebx, ebx
00a324c0 8b4e1c                   mov       ecx, dword ptr [esi + 0x1c]
00a324c3 0f84a5010000             je        0xa3266e
00a324c9 8b5708                   mov       edx, dword ptr [edi + 8]
00a324cc 2bd3                     sub       edx, ebx
00a324ce b8e9a28b2e               mov       eax, 0x2e8ba2e9
00a324d3 f7ea                     imul      edx
00a324d5 c1fa03                   sar       edx, 3
00a324d8 8bc2                     mov       eax, edx
00a324da c1e81f                   shr       eax, 0x1f
00a324dd 03c2                     add       eax, edx
00a324df 3bc1                     cmp       eax, ecx
00a324e1 0f8687010000             jbe       0xa3266e
00a324e7 6bc92c                   imul      ecx, ecx, 0x2c
00a324ea 03cb                     add       ecx, ebx
00a324ec 8b511c                   mov       edx, dword ptr [ecx + 0x1c]
00a324ef 83c118                   add       ecx, 0x18
00a324f2 85d2                     test      edx, edx
00a324f4 7504                     jne       0xa324fa
00a324f6 33db                     xor       ebx, ebx
00a324f8 eb08                     jmp       0xa32502
00a324fa 8b5908                   mov       ebx, dword ptr [ecx + 8]
00a324fd 2bda                     sub       ebx, edx
00a324ff c1fb02                   sar       ebx, 2
00a32502 85d2                     test      edx, edx
00a32504 741c                     je        0xa32522
00a32506 8b410c                   mov       eax, dword ptr [ecx + 0xc]
00a32509 2bc2                     sub       eax, edx
00a3250b c1f802                   sar       eax, 2
00a3250e 3bd8                     cmp       ebx, eax
00a32510 7310                     jae       0xa32522
00a32512 8b4108                   mov       eax, dword ptr [ecx + 8]
00a32515 8b5620                   mov       edx, dword ptr [esi + 0x20]
00a32518 8910                     mov       dword ptr [eax], edx
00a3251a 83c004                   add       eax, 4
00a3251d 894108                   mov       dword ptr [ecx + 8], eax
00a32520 eb0f                     jmp       0xa32531
00a32522 8b4108                   mov       eax, dword ptr [ecx + 8]
00a32525 8d5620                   lea       edx, [esi + 0x20]
00a32528 52                       push      edx
00a32529 6a01                     push      1
00a3252b 50                       push      eax
00a3252c e82f3a9dff               call      0x405f60
00a32531 8b5f04                   mov       ebx, dword ptr [edi + 4]
00a32534 85db                     test      ebx, ebx
00a32536 8b4e1c                   mov       ecx, dword ptr [esi + 0x1c]
00a32539 0f842f010000             je        0xa3266e
00a3253f 8b5708                   mov       edx, dword ptr [edi + 8]
00a32542 2bd3                     sub       edx, ebx
00a32544 b8e9a28b2e               mov       eax, 0x2e8ba2e9
00a32549 f7ea                     imul      edx
00a3254b c1fa03                   sar       edx, 3
00a3254e 8bc2                     mov       eax, edx
00a32550 c1e81f                   shr       eax, 0x1f
00a32553 03c2                     add       eax, edx
00a32555 3bc1                     cmp       eax, ecx
00a32557 0f8611010000             jbe       0xa3266e
00a3255d 8b4620                   mov       eax, dword ptr [esi + 0x20]
00a32560 6bc92c                   imul      ecx, ecx, 0x2c
00a32563 8b541928                 mov       edx, dword ptr [ecx + ebx + 0x28]
00a32567 03cb                     add       ecx, ebx
00a32569 03d0                     add       edx, eax
00a3256b 895128                   mov       dword ptr [ecx + 0x28], edx
00a3256e 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a32571 8b4138                   mov       eax, dword ptr [ecx + 0x38]
00a32574 83c624                   add       esi, 0x24
00a32577 3bf0                     cmp       esi, eax
00a32579 0f8591feffff             jne       0xa32410
00a3257f 8b75f0                   mov       esi, dword ptr [ebp - 0x10]
00a32582 8b7e64                   mov       edi, dword ptr [esi + 0x64]
00a32585 83c660                   add       esi, 0x60
00a32588 33db                     xor       ebx, ebx
00a3258a 3bfb                     cmp       edi, ebx
00a3258c 0f8481000000             je        0xa32613
00a32592 8b4608                   mov       eax, dword ptr [esi + 8]
00a32595 3bf8                     cmp       edi, eax
00a32597 8945e8                   mov       dword ptr [ebp - 0x18], eax
00a3259a 746b                     je        0xa32607
00a3259c 83c714                   add       edi, 0x14
00a3259f 90                       nop       
00a325a0 8b07                     mov       eax, dword ptr [edi]
00a325a2 3bc3                     cmp       eax, ebx
00a325a4 7409                     je        0xa325af
00a325a6 50                       push      eax
00a325a7 e831da1c00               call      0xbfffdd
00a325ac 83c404                   add       esp, 4
00a325af 891f                     mov       dword ptr [edi], ebx
00a325b1 895f04                   mov       dword ptr [edi + 4], ebx
00a325b4 895f08                   mov       dword ptr [edi + 8], ebx
00a325b7 8b47f0                   mov       eax, dword ptr [edi - 0x10]
00a325ba 3bc3                     cmp       eax, ebx
00a325bc 7433                     je        0xa325f1
00a325be 8b4ff4                   mov       ecx, dword ptr [edi - 0xc]
00a325c1 8bd8                     mov       ebx, eax
00a325c3 3bd9                     cmp       ebx, ecx
00a325c5 894dec                   mov       dword ptr [ebp - 0x14], ecx
00a325c8 7419                     je        0xa325e3
00a325ca 8d9b00000000             lea       ebx, [ebx]
00a325d0 6a00                     push      0
00a325d2 8bcb                     mov       ecx, ebx
00a325d4 e8e7d0a0ff               call      0x43f6c0
00a325d9 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
00a325dc 83c31c                   add       ebx, 0x1c
00a325df 3bd8                     cmp       ebx, eax
00a325e1 75ed                     jne       0xa325d0
00a325e3 8b47f0                   mov       eax, dword ptr [edi - 0x10]
00a325e6 50                       push      eax
00a325e7 e8f1d91c00               call      0xbfffdd
00a325ec 83c404                   add       esp, 4
00a325ef 33db                     xor       ebx, ebx
00a325f1 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
00a325f4 895ff0                   mov       dword ptr [edi - 0x10], ebx
00a325f7 895ff4                   mov       dword ptr [edi - 0xc], ebx
00a325fa 895ff8                   mov       dword ptr [edi - 8], ebx
00a325fd 83c728                   add       edi, 0x28
00a32600 8d57ec                   lea       edx, [edi - 0x14]
00a32603 3bd0                     cmp       edx, eax
00a32605 7599                     jne       0xa325a0
00a32607 8b4604                   mov       eax, dword ptr [esi + 4]
00a3260a 50                       push      eax
00a3260b e8cdd91c00               call      0xbfffdd
00a32610 83c404                   add       esp, 4
00a32613 8b4508                   mov       eax, dword ptr [ebp + 8]
00a32616 895e04                   mov       dword ptr [esi + 4], ebx
00a32619 895e08                   mov       dword ptr [esi + 8], ebx
00a3261c 895e0c                   mov       dword ptr [esi + 0xc], ebx
00a3261f 8b7848                   mov       edi, dword ptr [eax + 0x48]
00a32622 8b4044                   mov       eax, dword ptr [eax + 0x44]
00a32625 8bcf                     mov       ecx, edi
00a32627 2bc8                     sub       ecx, eax
00a32629 b8398ee338               mov       eax, 0x38e38e39
00a3262e f7e9                     imul      ecx
00a32630 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a32633 c1fa03                   sar       edx, 3
00a32636 8bc2                     mov       eax, edx
00a32638 c1e81f                   shr       eax, 0x1f
00a3263b 6800d0a200               push      0xa2d000
00a32640 03c2                     add       eax, edx
00a32642 50                       push      eax
00a32643 8b4144                   mov       eax, dword ptr [ecx + 0x44]
00a32646 57                       push      edi
00a32647 50                       push      eax
00a32648 e8f3240000               call      0xa34b40
00a3264d 8b5508                   mov       edx, dword ptr [ebp + 8]
00a32650 8b7a44                   mov       edi, dword ptr [edx + 0x44]
00a32653 8bc2                     mov       eax, edx
00a32655 8b4848                   mov       ecx, dword ptr [eax + 0x48]
00a32658 83c410                   add       esp, 0x10
00a3265b 3bf9                     cmp       edi, ecx
00a3265d 0f847c010000             je        0xa327df
00a32663 8b4604                   mov       eax, dword ptr [esi + 4]
00a32666 3bc3                     cmp       eax, ebx
00a32668 750b                     jne       0xa32675
00a3266a 33c0                     xor       eax, eax
00a3266c eb1d                     jmp       0xa3268b
00a3266e 8bcf                     mov       ecx, edi
00a32670 e8db060000               call      0xa32d50
00a32675 8b4e08                   mov       ecx, dword ptr [esi + 8]
00a32678 2bc8                     sub       ecx, eax
00a3267a b867666666               mov       eax, 0x66666667
00a3267f f7e9                     imul      ecx
00a32681 c1fa04                   sar       edx, 4
00a32684 8bc2                     mov       eax, edx
00a32686 c1e81f                   shr       eax, 0x1f
00a32689 03c2                     add       eax, edx
00a3268b 8b5f1c                   mov       ebx, dword ptr [edi + 0x1c]
00a3268e 3bc3                     cmp       eax, ebx
00a32690 7747                     ja        0xa326d9
00a32692 33db                     xor       ebx, ebx
00a32694 895dc4                   mov       dword ptr [ebp - 0x3c], ebx
00a32697 895dc8                   mov       dword ptr [ebp - 0x38], ebx
00a3269a 895dcc                   mov       dword ptr [ebp - 0x34], ebx
00a3269d 895dd4                   mov       dword ptr [ebp - 0x2c], ebx
00a326a0 895dd8                   mov       dword ptr [ebp - 0x28], ebx
00a326a3 895ddc                   mov       dword ptr [ebp - 0x24], ebx
00a326a6 885de0                   mov       byte ptr [ebp - 0x20], bl
00a326a9 895de4                   mov       dword ptr [ebp - 0x1c], ebx
00a326ac 8d4dc0                   lea       ecx, [ebp - 0x40]
00a326af 51                       push      ecx
00a326b0 8bce                     mov       ecx, esi
00a326b2 c745fc05000000           mov       dword ptr [ebp - 4], 5
00a326b9 e852350000               call      0xa35c10
00a326be c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00a326c5 895dd4                   mov       dword ptr [ebp - 0x2c], ebx
00a326c8 895dd8                   mov       dword ptr [ebp - 0x28], ebx
00a326cb 895ddc                   mov       dword ptr [ebp - 0x24], ebx
00a326ce 895dc4                   mov       dword ptr [ebp - 0x3c], ebx
00a326d1 895dc8                   mov       dword ptr [ebp - 0x38], ebx
00a326d4 895dcc                   mov       dword ptr [ebp - 0x34], ebx
00a326d7 eb8a                     jmp       0xa32663
00a326d9 8b4604                   mov       eax, dword ptr [esi + 4]
00a326dc 85c0                     test      eax, eax
00a326de 0f84f4000000             je        0xa327d8
00a326e4 8b4e08                   mov       ecx, dword ptr [esi + 8]
00a326e7 8bd0                     mov       edx, eax
00a326e9 2bca                     sub       ecx, edx
00a326eb b867666666               mov       eax, 0x66666667
00a326f0 f7e9                     imul      ecx
00a326f2 c1fa04                   sar       edx, 4
00a326f5 8bc2                     mov       eax, edx
00a326f7 c1e81f                   shr       eax, 0x1f
00a326fa 03c2                     add       eax, edx
00a326fc 3bc3                     cmp       eax, ebx
00a326fe 0f86d4000000             jbe       0xa327d8
00a32704 8b4604                   mov       eax, dword ptr [esi + 4]
00a32707 8d149b                   lea       edx, [ebx + ebx*4]
00a3270a 57                       push      edi
00a3270b 8d0cd0                   lea       ecx, [eax + edx*8]
00a3270e e88d72a9ff               call      0x4c99a0
00a32713 8b4e04                   mov       ecx, dword ptr [esi + 4]
00a32716 85c9                     test      ecx, ecx
00a32718 8b5f1c                   mov       ebx, dword ptr [edi + 0x1c]
00a3271b 0f84b7000000             je        0xa327d8
00a32721 8b5608                   mov       edx, dword ptr [esi + 8]
00a32724 2bd1                     sub       edx, ecx
00a32726 b867666666               mov       eax, 0x66666667
00a3272b f7ea                     imul      edx
00a3272d c1fa04                   sar       edx, 4
00a32730 8bc2                     mov       eax, edx
00a32732 c1e81f                   shr       eax, 0x1f
00a32735 03c2                     add       eax, edx
00a32737 3bc3                     cmp       eax, ebx
00a32739 0f8699000000             jbe       0xa327d8
00a3273f 8d049b                   lea       eax, [ebx + ebx*4]
00a32742 8b54c114                 mov       edx, dword ptr [ecx + eax*8 + 0x14]
00a32746 85d2                     test      edx, edx
00a32748 8d4cc110                 lea       ecx, [ecx + eax*8 + 0x10]
00a3274c 7504                     jne       0xa32752
00a3274e 33db                     xor       ebx, ebx
00a32750 eb08                     jmp       0xa3275a
00a32752 8b5908                   mov       ebx, dword ptr [ecx + 8]
00a32755 2bda                     sub       ebx, edx
00a32757 c1fb02                   sar       ebx, 2
00a3275a 85d2                     test      edx, edx
00a3275c 741c                     je        0xa3277a
00a3275e 8b410c                   mov       eax, dword ptr [ecx + 0xc]
00a32761 2bc2                     sub       eax, edx
00a32763 c1f802                   sar       eax, 2
00a32766 3bd8                     cmp       ebx, eax
00a32768 7310                     jae       0xa3277a
00a3276a 8b4108                   mov       eax, dword ptr [ecx + 8]
00a3276d 8b5720                   mov       edx, dword ptr [edi + 0x20]
00a32770 8910                     mov       dword ptr [eax], edx
00a32772 83c004                   add       eax, 4
00a32775 894108                   mov       dword ptr [ecx + 8], eax
00a32778 eb0f                     jmp       0xa32789
00a3277a 8b4108                   mov       eax, dword ptr [ecx + 8]
00a3277d 8d5720                   lea       edx, [edi + 0x20]
00a32780 52                       push      edx
00a32781 6a01                     push      1
00a32783 50                       push      eax
00a32784 e8d7379dff               call      0x405f60
00a32789 8b4604                   mov       eax, dword ptr [esi + 4]
00a3278c 85c0                     test      eax, eax
00a3278e 8b5f1c                   mov       ebx, dword ptr [edi + 0x1c]
00a32791 7445                     je        0xa327d8
00a32793 8b4e08                   mov       ecx, dword ptr [esi + 8]
00a32796 8bd0                     mov       edx, eax
00a32798 2bca                     sub       ecx, edx
00a3279a b867666666               mov       eax, 0x66666667
00a3279f f7e9                     imul      ecx
00a327a1 c1fa04                   sar       edx, 4
00a327a4 8bc2                     mov       eax, edx
00a327a6 c1e81f                   shr       eax, 0x1f
00a327a9 03c2                     add       eax, edx
00a327ab 3bc3                     cmp       eax, ebx
00a327ad 7629                     jbe       0xa327d8
00a327af 8b                       .byte     0x8b
