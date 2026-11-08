00a49220 55                       push       ebp
00a49221 8bec                     mov        ebp, esp
00a49223 6aff                     push       -1
00a49225 689af5c800               push       0xc8f59a
00a4922a 64a100000000             mov        eax, dword ptr fs:[0]
00a49230 50                       push       eax
00a49231 64892500000000           mov        dword ptr fs:[0], esp
00a49238 83ec1c                   sub        esp, 0x1c
00a4923b 53                       push       ebx
00a4923c 56                       push       esi
00a4923d 57                       push       edi
00a4923e 8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00a49241 8b472c                   mov        eax, dword ptr [edi + 0x2c]
00a49244 8b5f28                   mov        ebx, dword ptr [edi + 0x28]
00a49247 894df0                   mov        dword ptr [ebp - 0x10], ecx
00a4924a 8d4f24                   lea        ecx, [edi + 0x24]
00a4924d 2bc3                     sub        eax, ebx
00a4924f c1f802                   sar        eax, 2
00a49252 85c0                     test       eax, eax
00a49254 c745ec01000000           mov        dword ptr [ebp - 0x14], 1
00a4925b 760b                     jbe        0xa49268
00a4925d 6a00                     push       0
00a4925f e81c55ffff               call       0xa3e780
00a49264 8b30                     mov        esi, dword ptr [eax]
00a49266 eb03                     jmp        0xa4926b
00a49268 83ceff                   or         esi, 0xffffffff
00a4926b 83cbff                   or         ebx, 0xffffffff
00a4926e 83fe06                   cmp        esi, 6
00a49271 750f                     jne        0xa49282
00a49273 8d4dec                   lea        ecx, [ebp - 0x14]
00a49276 51                       push       ecx
00a49277 8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00a4927a 57                       push       edi
00a4927b e8403ffeff               call       0xa2d1c0
00a49280 8bd8                     mov        ebx, eax
00a49282 8d55ec                   lea        edx, [ebp - 0x14]
00a49285 52                       push       edx
00a49286 57                       push       edi
00a49287 8b7df0                   mov        edi, dword ptr [ebp - 0x10]
00a4928a 8bcf                     mov        ecx, edi
00a4928c e82f3ffeff               call       0xa2d1c0
00a49291 33c9                     xor        ecx, ecx
00a49293 8945e8                   mov        dword ptr [ebp - 0x18], eax
00a49296 894ddc                   mov        dword ptr [ebp - 0x24], ecx
00a49299 894de0                   mov        dword ptr [ebp - 0x20], ecx
00a4929c 894de4                   mov        dword ptr [ebp - 0x1c], ecx
00a4929f 3bf1                     cmp        esi, ecx
00a492a1 894dfc                   mov        dword ptr [ebp - 4], ecx
00a492a4 751c                     jne        0xa492c2
00a492a6 8b577c                   mov        edx, dword ptr [edi + 0x7c]
00a492a9 3bd1                     cmp        edx, ecx
00a492ab 8d477c                   lea        eax, [edi + 0x7c]
00a492ae 0f8414030000             je         0xa495c8
00a492b4 50                       push       eax
00a492b5 8d4dd8                   lea        ecx, [ebp - 0x28]
00a492b8 e83352a4ff               call       0x48e4f0
00a492bd e906030000               jmp        0xa495c8
00a492c2 83fe01                   cmp        esi, 1
00a492c5 0f8547010000             jne        0xa49412
00a492cb 8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a492ce 8b5804                   mov        ebx, dword ptr [eax + 4]
00a492d1 3b5808                   cmp        ebx, dword ptr [eax + 8]
00a492d4 0f84ee020000             je         0xa495c8
00a492da eb04                     jmp        0xa492e0
00a492dc 33c9                     xor        ecx, ecx
00a492de 8bff                     mov        edi, edi
00a492e0 8b33                     mov        esi, dword ptr [ebx]
00a492e2 3bf1                     cmp        esi, ecx
00a492e4 0f8412010000             je         0xa493fc
00a492ea 8b06                     mov        eax, dword ptr [esi]
00a492ec 6811020000               push       0x211
00a492f1 8bce                     mov        ecx, esi
00a492f3 ff502c                   call       dword ptr [eax + 0x2c]
00a492f6 84c0                     test       al, al
00a492f8 8bce                     mov        ecx, esi
00a492fa 0f849e000000             je         0xa4939e
00a49300 8b16                     mov        edx, dword ptr [esi]
00a49302 ff5238                   call       dword ptr [edx + 0x38]
00a49305 84c0                     test       al, al
00a49307 6a00                     push       0
00a49309 7449                     je         0xa49354
00a4930b 68f49df500               push       0xf59df4
00a49310 681009f400               push       0xf40910
00a49315 6a00                     push       0
00a49317 56                       push       esi
00a49318 e8ee791b00               call       0xc00d0b
00a4931d 8bf0                     mov        esi, eax
00a4931f 83c414                   add        esp, 0x14
00a49322 85f6                     test       esi, esi
00a49324 0f84bd000000             je         0xa493e7
00a4932a 8bce                     mov        ecx, esi
00a4932c e85ffccfff               call       0x748f90
00a49331 85c0                     test       eax, eax
00a49333 0f84ae000000             je         0xa493e7
00a49339 8bce                     mov        ecx, esi
00a4933b e850fccfff               call       0x748f90
00a49340 89450c                   mov        dword ptr [ebp + 0xc], eax
00a49343 8d450c                   lea        eax, [ebp + 0xc]
00a49346 50                       push       eax
00a49347 8d4dd8                   lea        ecx, [ebp - 0x28]
00a4934a e8a151a4ff               call       0x48e4f0
00a4934f e9a8000000               jmp        0xa493fc
00a49354 682829f400               push       0xf42928
00a49359 681009f400               push       0xf40910
00a4935e 6a00                     push       0
00a49360 56                       push       esi
00a49361 e8a5791b00               call       0xc00d0b
00a49366 8bf0                     mov        esi, eax
00a49368 83c414                   add        esp, 0x14
00a4936b 85f6                     test       esi, esi
00a4936d 7478                     je         0xa493e7
00a4936f 8b16                     mov        edx, dword ptr [esi]
00a49371 8bce                     mov        ecx, esi
00a49373 ff92b0050000             call       dword ptr [edx + 0x5b0]
00a49379 8b4814                   mov        ecx, dword ptr [eax + 0x14]
00a4937c 85c9                     test       ecx, ecx
00a4937e 7467                     je         0xa493e7
00a49380 8b06                     mov        eax, dword ptr [esi]
00a49382 8bce                     mov        ecx, esi
00a49384 ff90b0050000             call       dword ptr [eax + 0x5b0]
00a4938a 8b4814                   mov        ecx, dword ptr [eax + 0x14]
00a4938d 8d550c                   lea        edx, [ebp + 0xc]
00a49390 894d0c                   mov        dword ptr [ebp + 0xc], ecx
00a49393 52                       push       edx
00a49394 8d4dd8                   lea        ecx, [ebp - 0x28]
00a49397 e85451a4ff               call       0x48e4f0
00a4939c eb5e                     jmp        0xa493fc
00a4939e 8b06                     mov        eax, dword ptr [esi]
00a493a0 ff5034                   call       dword ptr [eax + 0x34]
00a493a3 84c0                     test       al, al
00a493a5 7447                     je         0xa493ee
00a493a7 6a00                     push       0
00a493a9 680829f400               push       0xf42908
00a493ae 681009f400               push       0xf40910
00a493b3 6a00                     push       0
00a493b5 56                       push       esi
00a493b6 e850791b00               call       0xc00d0b
00a493bb 8bf0                     mov        esi, eax
00a493bd 83c414                   add        esp, 0x14
00a493c0 85f6                     test       esi, esi
00a493c2 7423                     je         0xa493e7
00a493c4 8bce                     mov        ecx, esi
00a493c6 e8a54ca7ff               call       0x4be070
00a493cb 85c0                     test       eax, eax
00a493cd 7418                     je         0xa493e7
00a493cf 8bce                     mov        ecx, esi
00a493d1 e89a4ca7ff               call       0x4be070
00a493d6 8d4d0c                   lea        ecx, [ebp + 0xc]
00a493d9 51                       push       ecx
00a493da 8d4dd8                   lea        ecx, [ebp - 0x28]
00a493dd 89450c                   mov        dword ptr [ebp + 0xc], eax
00a493e0 e80b51a4ff               call       0x48e4f0
00a493e5 eb15                     jmp        0xa493fc
00a493e7 684494e400               push       0xe49444
00a493ec eb05                     jmp        0xa493f3
00a493ee 68e093e400               push       0xe493e0
00a493f3 ff15bc2eff00             call       dword ptr [0xff2ebc]
00a493f9 83c404                   add        esp, 4
00a493fc 8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a493ff 8b4208                   mov        eax, dword ptr [edx + 8]
00a49402 83c304                   add        ebx, 4
00a49405 3bd8                     cmp        ebx, eax
00a49407 0f85cffeffff             jne        0xa492dc
00a4940d e9b6010000               jmp        0xa495c8
00a49412 83fe03                   cmp        esi, 3
00a49415 7531                     jne        0xa49448
00a49417 8b9780000000             mov        edx, dword ptr [edi + 0x80]
00a4941d 3bd1                     cmp        edx, ecx
00a4941f 8d8780000000             lea        eax, [edi + 0x80]
00a49425 740e                     je         0xa49435
00a49427 50                       push       eax
00a49428 8d4dd8                   lea        ecx, [ebp - 0x28]
00a4942b e8c050a4ff               call       0x48e4f0
00a49430 e993010000               jmp        0xa495c8
00a49435 689093e400               push       0xe49390
00a4943a ff15bc2eff00             call       dword ptr [0xff2ebc]
00a49440 83c404                   add        esp, 4
00a49443 e980010000               jmp        0xa495c8
00a49448 83fe04                   cmp        esi, 4
00a4944b 7531                     jne        0xa4947e
00a4944d 8b9784000000             mov        edx, dword ptr [edi + 0x84]
00a49453 3bd1                     cmp        edx, ecx
00a49455 8d8784000000             lea        eax, [edi + 0x84]
00a4945b 740e                     je         0xa4946b
00a4945d 50                       push       eax
00a4945e 8d4dd8                   lea        ecx, [ebp - 0x28]
00a49461 e88a50a4ff               call       0x48e4f0
00a49466 e95d010000               jmp        0xa495c8
00a4946b 683893e400               push       0xe49338
00a49470 ff15bc2eff00             call       dword ptr [0xff2ebc]
00a49476 83c404                   add        esp, 4
00a49479 e94a010000               jmp        0xa495c8
00a4947e 83fe02                   cmp        esi, 2
00a49481 0f857b010000             jne        0xa49602
00a49487 8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a4948a 8b5f04                   mov        ebx, dword ptr [edi + 4]
00a4948d 3b5f08                   cmp        ebx, dword ptr [edi + 8]
00a49490 0f842f010000             je         0xa495c5
00a49496 8b33                     mov        esi, dword ptr [ebx]
00a49498 85f6                     test       esi, esi
00a4949a 0f8417010000             je         0xa495b7
00a494a0 8b06                     mov        eax, dword ptr [esi]
00a494a2 6811020000               push       0x211
00a494a7 8bce                     mov        ecx, esi
00a494a9 ff502c                   call       dword ptr [eax + 0x2c]
00a494ac 84c0                     test       al, al
00a494ae 7451                     je         0xa49501
00a494b0 6a00                     push       0
00a494b2 682829f400               push       0xf42928
00a494b7 681009f400               push       0xf40910
00a494bc 6a00                     push       0
00a494be 56                       push       esi
00a494bf e847781b00               call       0xc00d0b
00a494c4 8bf0                     mov        esi, eax
00a494c6 83c414                   add        esp, 0x14
00a494c9 85f6                     test       esi, esi
00a494cb 0f84e6000000             je         0xa495b7
00a494d1 8b16                     mov        edx, dword ptr [esi]
00a494d3 8bce                     mov        ecx, esi
00a494d5 ff9258030000             call       dword ptr [edx + 0x358]
00a494db 85c0                     test       eax, eax
00a494dd 0f84d4000000             je         0xa495b7
00a494e3 8b06                     mov        eax, dword ptr [esi]
00a494e5 8bce                     mov        ecx, esi
00a494e7 ff9058030000             call       dword ptr [eax + 0x358]
00a494ed 8d4d10                   lea        ecx, [ebp + 0x10]
00a494f0 51                       push       ecx
00a494f1 8d4dd8                   lea        ecx, [ebp - 0x28]
00a494f4 894510                   mov        dword ptr [ebp + 0x10], eax
00a494f7 e8f44fa4ff               call       0x48e4f0
00a494fc e9b6000000               jmp        0xa495b7
00a49501 8b16                     mov        edx, dword ptr [esi]
00a49503 8bce                     mov        ecx, esi
00a49505 ff5234                   call       dword ptr [edx + 0x34]
00a49508 84c0                     test       al, al
00a4950a 744a                     je         0xa49556
00a4950c 6a00                     push       0
00a4950e 680829f400               push       0xf42908
00a49513 681009f400               push       0xf40910
00a49518 6a00                     push       0
00a4951a 56                       push       esi
00a4951b e8eb771b00               call       0xc00d0b
00a49520 8bf0                     mov        esi, eax
00a49522 83c414                   add        esp, 0x14
00a49525 85f6                     test       esi, esi
00a49527 0f848a000000             je         0xa495b7
00a4952d 8b06                     mov        eax, dword ptr [esi]
00a4952f 8bce                     mov        ecx, esi
00a49531 ff9058030000             call       dword ptr [eax + 0x358]
00a49537 85c0                     test       eax, eax
00a49539 747c                     je         0xa495b7
00a4953b 8b16                     mov        edx, dword ptr [esi]
00a4953d 8bce                     mov        ecx, esi
00a4953f ff9258030000             call       dword ptr [edx + 0x358]
00a49545 894510                   mov        dword ptr [ebp + 0x10], eax
00a49548 8d4510                   lea        eax, [ebp + 0x10]
00a4954b 50                       push       eax
00a4954c 8d4dd8                   lea        ecx, [ebp - 0x28]
00a4954f e89c4fa4ff               call       0x48e4f0
00a49554 eb61                     jmp        0xa495b7
00a49556 8b16                     mov        edx, dword ptr [esi]
00a49558 6a21                     push       0x21
00a4955a 8bce                     mov        ecx, esi
00a4955c ff522c                   call       dword ptr [edx + 0x2c]
00a4955f 84c0                     test       al, al
00a49561 7446                     je         0xa495a9
00a49563 6a00                     push       0
00a49565 68a028f400               push       0xf428a0
00a4956a 681009f400               push       0xf40910
00a4956f 6a00                     push       0
00a49571 56                       push       esi
00a49572 e894771b00               call       0xc00d0b
00a49577 8bf0                     mov        esi, eax
00a49579 83c414                   add        esp, 0x14
00a4957c 85f6                     test       esi, esi
00a4957e 7437                     je         0xa495b7
00a49580 8b06                     mov        eax, dword ptr [esi]
00a49582 8bce                     mov        ecx, esi
00a49584 ff908c010000             call       dword ptr [eax + 0x18c]
00a4958a 85c0                     test       eax, eax
00a4958c 7429                     je         0xa495b7
00a4958e 8b16                     mov        edx, dword ptr [esi]
00a49590 8bce                     mov        ecx, esi
00a49592 ff928c010000             call       dword ptr [edx + 0x18c]
00a49598 894510                   mov        dword ptr [ebp + 0x10], eax
00a4959b 8d4510                   lea        eax, [ebp + 0x10]
00a4959e 50                       push       eax
00a4959f 8d4dd8                   lea        ecx, [ebp - 0x28]
00a495a2 e8494fa4ff               call       0x48e4f0
00a495a7 eb0e                     jmp        0xa495b7
00a495a9 68e092e400               push       0xe492e0
00a495ae ff15bc2eff00             call       dword ptr [0xff2ebc]
00a495b4 83c404                   add        esp, 4
00a495b7 8b4708                   mov        eax, dword ptr [edi + 8]
00a495ba 83c304                   add        ebx, 4
00a495bd 3bd8                     cmp        ebx, eax
00a495bf 0f85d1feffff             jne        0xa49496
00a495c5 8b7df0                   mov        edi, dword ptr [ebp - 0x10]
00a495c8 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00a495cb 8b55e8                   mov        edx, dword ptr [ebp - 0x18]
00a495ce 50                       push       eax
00a495cf 8b4508                   mov        eax, dword ptr [ebp + 8]
00a495d2 8d4dd8                   lea        ecx, [ebp - 0x28]
00a495d5 51                       push       ecx
00a495d6 52                       push       edx
00a495d7 50                       push       eax
00a495d8 8bcf                     mov        ecx, edi
00a495da e8a1f6ffff               call       0xa48c80
00a495df 8b45dc                   mov        eax, dword ptr [ebp - 0x24]
00a495e2 85c0                     test       eax, eax
00a495e4 7409                     je         0xa495ef
00a495e6 50                       push       eax
00a495e7 e8f1691b00               call       0xbfffdd
00a495ec 83c404                   add        esp, 4
00a495ef 5f                       pop        edi
00a495f0 5e                       pop        esi
00a495f1 5b                       pop        ebx
00a495f2 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a495f5 64890d00000000           mov        dword ptr fs:[0], ecx
00a495fc 8be5                     mov        esp, ebp
00a495fe 5d                       pop        ebp
00a495ff c21000                   ret        0x10
00a49602 83fe06                   cmp        esi, 6
00a49605 7536                     jne        0xa4963d
00a49607 8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a4960a 8b7704                   mov        esi, dword ptr [edi + 4]
00a4960d 3b7708                   cmp        esi, dword ptr [edi + 8]
00a49610 74b3                     je         0xa495c5
00a49612 8b0e                     mov        ecx, dword ptr [esi]
00a49614 85c9                     test       ecx, ecx
00a49616 7419                     je         0xa49631
00a49618 53                       push       ebx
00a49619 e8a21ba5ff               call       0x49b1c0
00a4961e 85c0                     test       eax, eax
00a49620 894510                   mov        dword ptr [ebp + 0x10], eax
00a49623 740c                     je         0xa49631
00a49625 8d4d10                   lea        ecx, [ebp + 0x10]
00a49628 51                       push       ecx
00a49629 8d4dd8                   lea        ecx, [ebp - 0x28]
00a4962c e8bf4ea4ff               call       0x48e4f0
00a49631 8b4708                   mov        eax, dword ptr [edi + 8]
00a49634 83c604                   add        esi, 4
00a49637 3bf0                     cmp        esi, eax
00a49639 75d7                     jne        0xa49612
00a4963b eb88                     jmp        0xa495c5
00a4963d 83fe05                   cmp        esi, 5
00a49640 7586                     jne        0xa495c8
00a49642 8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a49645 8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00a49648 52                       push       edx
00a49649 8b5508                   mov        edx, dword ptr [ebp + 8]
00a4964c 51                       push       ecx
00a4964d 50                       push       eax
00a4964e 52                       push       edx
00a4964f 8bcf                     mov        ecx, edi
00a49651 e82af6ffff               call       0xa48c80
00a49656 8d4dd8                   lea        ecx, [ebp - 0x28]
00a49659 e8f2b6bfff               call       0x644d50
00a4965e 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a49661 5f                       pop        edi
00a49662 5e                       pop        esi
00a49663 5b                       pop        ebx
00a49664 64890d00000000           mov        dword ptr fs:[0], ecx
00a4966b 8be5                     mov        esp, ebp
00a4966d 5d                       pop        ebp
00a4966e c2                       .byte      0xc2
