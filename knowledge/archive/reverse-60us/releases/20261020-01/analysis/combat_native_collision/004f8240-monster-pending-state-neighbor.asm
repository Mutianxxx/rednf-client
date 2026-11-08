004f8240 55                       push      ebp
004f8241 8bec                     mov       ebp, esp
004f8243 6aff                     push      -1
004f8245 68f69bc500               push      0xc59bf6
004f824a 64a100000000             mov       eax, dword ptr fs:[0]
004f8250 50                       push      eax
004f8251 64892500000000           mov       dword ptr fs:[0], esp
004f8258 83ec34                   sub       esp, 0x34
004f825b 56                       push      esi
004f825c 8bf1                     mov       esi, ecx
004f825e 8b8618220000             mov       eax, dword ptr [esi + 0x2218]
004f8264 57                       push      edi
004f8265 33ff                     xor       edi, edi
004f8267 3bc7                     cmp       eax, edi
004f8269 0f8437050000             je        0x4f87a6
004f826f 8b8e1c220000             mov       ecx, dword ptr [esi + 0x221c]
004f8275 2bc8                     sub       ecx, eax
004f8277 b889888888               mov       eax, 0x88888889
004f827c f7e9                     imul      ecx
004f827e 03d1                     add       edx, ecx
004f8280 c1fa06                   sar       edx, 6
004f8283 8bc2                     mov       eax, edx
004f8285 c1e81f                   shr       eax, 0x1f
004f8288 03c2                     add       eax, edx
004f828a 8945d0                   mov       dword ptr [ebp - 0x30], eax
004f828d 0f8413050000             je        0x4f87a6
004f8293 83bea0040000ff           cmp       dword ptr [esi + 0x4a0], -1
004f829a 0f8506050000             jne       0x4f87a6
004f82a0 8a8648220000             mov       al, byte ptr [esi + 0x2248]
004f82a6 84c0                     test      al, al
004f82a8 53                       push      ebx
004f82a9 0f858d000000             jne       0x4f833c
004f82af 8b16                     mov       edx, dword ptr [esi]
004f82b1 8bce                     mov       ecx, esi
004f82b3 ff92b0050000             call      dword ptr [edx + 0x5b0]
004f82b9 397814                   cmp       dword ptr [eax + 0x14], edi
004f82bc 747e                     je        0x4f833c
004f82be 8b06                     mov       eax, dword ptr [esi]
004f82c0 8bce                     mov       ecx, esi
004f82c2 ff90b0050000             call      dword ptr [eax + 0x5b0]
004f82c8 8b4014                   mov       eax, dword ptr [eax + 0x14]
004f82cb 8b10                     mov       edx, dword ptr [eax]
004f82cd 8bc8                     mov       ecx, eax
004f82cf ff9294000000             call      dword ptr [edx + 0x94]
004f82d5 8bd8                     mov       ebx, eax
004f82d7 8b06                     mov       eax, dword ptr [esi]
004f82d9 8bce                     mov       ecx, esi
004f82db ff9094000000             call      dword ptr [eax + 0x94]
004f82e1 8b16                     mov       edx, dword ptr [esi]
004f82e3 2bc3                     sub       eax, ebx
004f82e5 8bce                     mov       ecx, esi
004f82e7 89864c220000             mov       dword ptr [esi + 0x224c], eax
004f82ed ff92b0050000             call      dword ptr [edx + 0x5b0]
004f82f3 8b5814                   mov       ebx, dword ptr [eax + 0x14]
004f82f6 8b06                     mov       eax, dword ptr [esi]
004f82f8 8bce                     mov       ecx, esi
004f82fa ff9098000000             call      dword ptr [eax + 0x98]
004f8300 8b13                     mov       edx, dword ptr [ebx]
004f8302 8bcb                     mov       ecx, ebx
004f8304 8945e0                   mov       dword ptr [ebp - 0x20], eax
004f8307 ff9298000000             call      dword ptr [edx + 0x98]
004f830d 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004f8310 2bc8                     sub       ecx, eax
004f8312 8b06                     mov       eax, dword ptr [esi]
004f8314 898e50220000             mov       dword ptr [esi + 0x2250], ecx
004f831a 8bce                     mov       ecx, esi
004f831c ff90b0050000             call      dword ptr [eax + 0x5b0]
004f8322 8b4014                   mov       eax, dword ptr [eax + 0x14]
004f8325 8b10                     mov       edx, dword ptr [eax]
004f8327 8bc8                     mov       ecx, eax
004f8329 ff929c000000             call      dword ptr [edx + 0x9c]
004f832f 898654220000             mov       dword ptr [esi + 0x2254], eax
004f8335 c6864822000001           mov       byte ptr [esi + 0x2248], 1
004f833c 897de4                   mov       dword ptr [ebp - 0x1c], edi
004f833f 897de8                   mov       dword ptr [ebp - 0x18], edi
004f8342 8b9e18220000             mov       ebx, dword ptr [esi + 0x2218]
004f8348 85db                     test      ebx, ebx
004f834a 0f8455040000             je        0x4f87a5
004f8350 8b8e1c220000             mov       ecx, dword ptr [esi + 0x221c]
004f8356 2bcb                     sub       ecx, ebx
004f8358 b889888888               mov       eax, 0x88888889
004f835d f7e9                     imul      ecx
004f835f 03d1                     add       edx, ecx
004f8361 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
004f8364 c1fa06                   sar       edx, 6
004f8367 8bc2                     mov       eax, edx
004f8369 c1e81f                   shr       eax, 0x1f
004f836c 03c2                     add       eax, edx
004f836e 3bc8                     cmp       ecx, eax
004f8370 0f832f040000             jae       0x4f87a5
004f8376 8d8e28180000             lea       ecx, [esi + 0x1828]
004f837c e8df9cf0ff               call      0x402060
004f8381 3b441f54                 cmp       eax, dword ptr [edi + ebx + 0x54]
004f8385 0f8502040000             jne       0x4f878d
004f838b 8b55e4                   mov       edx, dword ptr [ebp - 0x1c]
004f838e 8b8e2c220000             mov       ecx, dword ptr [esi + 0x222c]
004f8394 33c0                     xor       eax, eax
004f8396 8bc2                     mov       eax, edx
004f8398 8bd0                     mov       edx, eax
004f839a c1ea05                   shr       edx, 5
004f839d 8d1491                   lea       edx, [ecx + edx*4]
004f83a0 83e01f                   and       eax, 0x1f
004f83a3 b901000000               mov       ecx, 1
004f83a8 894de0                   mov       dword ptr [ebp - 0x20], ecx
004f83ab 8bc8                     mov       ecx, eax
004f83ad 8b45e0                   mov       eax, dword ptr [ebp - 0x20]
004f83b0 d3e0                     shl       eax, cl
004f83b2 8b0a                     mov       ecx, dword ptr [edx]
004f83b4 33db                     xor       ebx, ebx
004f83b6 85c1                     test      ecx, eax
004f83b8 0f85cf030000             jne       0x4f878d
004f83be 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f83c4 8b8824010000             mov       ecx, dword ptr [eax + 0x124]
004f83ca 8b8618220000             mov       eax, dword ptr [esi + 0x2218]
004f83d0 3b4c0718                 cmp       ecx, dword ptr [edi + eax + 0x18]
004f83d4 0f8eb3030000             jle       0x4f878d
004f83da 395c0710                 cmp       dword ptr [edi + eax + 0x10], ebx
004f83de 0f84a9030000             je        0x4f878d
004f83e4 395c0758                 cmp       dword ptr [edi + eax + 0x58], ebx
004f83e8 0f849f030000             je        0x4f878d
004f83ee 8bce                     mov       ecx, esi
004f83f0 e89b3cfaff               call      0x49c090
004f83f5 84c0                     test      al, al
004f83f7 0f8439030000             je        0x4f8736
004f83fd 8b8618220000             mov       eax, dword ptr [esi + 0x2218]
004f8403 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f8406 3b4c0760                 cmp       ecx, dword ptr [edi + eax + 0x60]
004f840a 7d07                     jge       0x4f8413
004f840c 8bd1                     mov       edx, ecx
004f840e 8955ec                   mov       dword ptr [ebp - 0x14], edx
004f8411 eb07                     jmp       0x4f841a
004f8413 8b540760                 mov       edx, dword ptr [edi + eax + 0x60]
004f8417 8955ec                   mov       dword ptr [ebp - 0x14], edx
004f841a 3bcb                     cmp       ecx, ebx
004f841c 7509                     jne       0x4f8427
004f841e 8b4c0760                 mov       ecx, dword ptr [edi + eax + 0x60]
004f8422 894dec                   mov       dword ptr [ebp - 0x14], ecx
004f8425 8bd1                     mov       edx, ecx
004f8427 395c0764                 cmp       dword ptr [edi + eax + 0x64], ebx
004f842b 0f8566010000             jne       0x4f8597
004f8431 33c9                     xor       ecx, ecx
004f8433 3bd3                     cmp       edx, ebx
004f8435 894df0                   mov       dword ptr [ebp - 0x10], ecx
004f8438 0f8e7b020000             jle       0x4f86b9
004f843e eb03                     jmp       0x4f8443
004f8440 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004f8443 8b9e18220000             mov       ebx, dword ptr [esi + 0x2218]
004f8449 8b541f6c                 mov       edx, dword ptr [edi + ebx + 0x6c]
004f844d 85d2                     test      edx, edx
004f844f 0f84d3000000             je        0x4f8528
004f8455 8b441f70                 mov       eax, dword ptr [edi + ebx + 0x70]
004f8459 2bc2                     sub       eax, edx
004f845b c1f802                   sar       eax, 2
004f845e 85c0                     test      eax, eax
004f8460 0f86c2000000             jbe       0x4f8528
004f8466 6a00                     push      0
004f8468 6a00                     push      0
004f846a 8bc2                     mov       eax, edx
004f846c 833c8800                 cmp       dword ptr [eax + ecx*4], 0
004f8470 6a00                     push      0
004f8472 6a00                     push      0
004f8474 6a00                     push      0
004f8476 7548                     jne       0x4f84c0
004f8478 8b863c220000             mov       eax, dword ptr [esi + 0x223c]
004f847e 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f8481 8b440204                 mov       eax, dword ptr [edx + eax + 4]
004f8485 8945e0                   mov       dword ptr [ebp - 0x20], eax
004f8488 8b441f40                 mov       eax, dword ptr [edi + ebx + 0x40]
004f848c 8b0488                   mov       eax, dword ptr [eax + ecx*4]
004f848f 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004f8492 6a04                     push      4
004f8494 50                       push      eax
004f8495 8b441f30                 mov       eax, dword ptr [edi + ebx + 0x30]
004f8499 8b0488                   mov       eax, dword ptr [eax + ecx*4]
004f849c 50                       push      eax
004f849d 8b441f20                 mov       eax, dword ptr [edi + ebx + 0x20]
004f84a1 8b0488                   mov       eax, dword ptr [eax + ecx*4]
004f84a4 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004f84a7 50                       push      eax
004f84a8 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004f84ab 8b0c81                   mov       ecx, dword ptr [ecx + eax*4]
004f84ae 8b441f14                 mov       eax, dword ptr [edi + ebx + 0x14]
004f84b2 6a00                     push      0
004f84b4 51                       push      ecx
004f84b5 8b4c1f10                 mov       ecx, dword ptr [edi + ebx + 0x10]
004f84b9 50                       push      eax
004f84ba 51                       push      ecx
004f84bb e9b6000000               jmp       0x4f8576
004f84c0 8b541f40                 mov       edx, dword ptr [edi + ebx + 0x40]
004f84c4 8b441f30                 mov       eax, dword ptr [edi + ebx + 0x30]
004f84c8 8b4c1f20                 mov       ecx, dword ptr [edi + ebx + 0x20]
004f84cc 8945dc                   mov       dword ptr [ebp - 0x24], eax
004f84cf 8b863c220000             mov       eax, dword ptr [esi + 0x223c]
004f84d5 8955e0                   mov       dword ptr [ebp - 0x20], edx
004f84d8 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f84db 8b440204                 mov       eax, dword ptr [edx + eax + 4]
004f84df 8945d4                   mov       dword ptr [ebp - 0x2c], eax
004f84e2 8b06                     mov       eax, dword ptr [esi]
004f84e4 894dd8                   mov       dword ptr [ebp - 0x28], ecx
004f84e7 8bce                     mov       ecx, esi
004f84e9 8945d0                   mov       dword ptr [ebp - 0x30], eax
004f84ec ff90c0000000             call      dword ptr [eax + 0xc0]
004f84f2 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004f84f5 f7d8                     neg       eax
004f84f7 1bc0                     sbb       eax, eax
004f84f9 40                       inc       eax
004f84fa 50                       push      eax
004f84fb 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004f84fe 8b1481                   mov       edx, dword ptr [ecx + eax*4]
004f8501 8b4ddc                   mov       ecx, dword ptr [ebp - 0x24]
004f8504 52                       push      edx
004f8505 8b1481                   mov       edx, dword ptr [ecx + eax*4]
004f8508 8b4dd8                   mov       ecx, dword ptr [ebp - 0x28]
004f850b 52                       push      edx
004f850c 8b1481                   mov       edx, dword ptr [ecx + eax*4]
004f850f 8b4dd4                   mov       ecx, dword ptr [ebp - 0x2c]
004f8512 52                       push      edx
004f8513 8b1481                   mov       edx, dword ptr [ecx + eax*4]
004f8516 8b441f14                 mov       eax, dword ptr [edi + ebx + 0x14]
004f851a 8b4c1f10                 mov       ecx, dword ptr [edi + ebx + 0x10]
004f851e 6a00                     push      0
004f8520 52                       push      edx
004f8521 8b55d0                   mov       edx, dword ptr [ebp - 0x30]
004f8524 50                       push      eax
004f8525 51                       push      ecx
004f8526 eb50                     jmp       0x4f8578
004f8528 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f852b 6a00                     push      0
004f852d 8d048d00000000           lea       eax, [ecx*4]
004f8534 8b8e3c220000             mov       ecx, dword ptr [esi + 0x223c]
004f853a 8b4c0a04                 mov       ecx, dword ptr [edx + ecx + 4]
004f853e 6a00                     push      0
004f8540 6a00                     push      0
004f8542 6a00                     push      0
004f8544 894dd0                   mov       dword ptr [ebp - 0x30], ecx
004f8547 8b4c1f40                 mov       ecx, dword ptr [edi + ebx + 0x40]
004f854b 8b0c08                   mov       ecx, dword ptr [eax + ecx]
004f854e 6a00                     push      0
004f8550 6a04                     push      4
004f8552 51                       push      ecx
004f8553 8b4c1f30                 mov       ecx, dword ptr [edi + ebx + 0x30]
004f8557 8b0c08                   mov       ecx, dword ptr [eax + ecx]
004f855a 51                       push      ecx
004f855b 8b4c1f20                 mov       ecx, dword ptr [edi + ebx + 0x20]
004f855f 8b0c08                   mov       ecx, dword ptr [eax + ecx]
004f8562 51                       push      ecx
004f8563 8b4dd0                   mov       ecx, dword ptr [ebp - 0x30]
004f8566 8b0408                   mov       eax, dword ptr [eax + ecx]
004f8569 8b4c1f14                 mov       ecx, dword ptr [edi + ebx + 0x14]
004f856d 6a00                     push      0
004f856f 50                       push      eax
004f8570 8b441f10                 mov       eax, dword ptr [edi + ebx + 0x10]
004f8574 51                       push      ecx
004f8575 50                       push      eax
004f8576 8b16                     mov       edx, dword ptr [esi]
004f8578 8bce                     mov       ecx, esi
004f857a ff92b8020000             call      dword ptr [edx + 0x2b8]
004f8580 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004f8583 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
004f8586 40                       inc       eax
004f8587 3bc1                     cmp       eax, ecx
004f8589 8945f0                   mov       dword ptr [ebp - 0x10], eax
004f858c 0f8caefeffff             jl        0x4f8440
004f8592 e922010000               jmp       0x4f86b9
004f8597 837c076401               cmp       dword ptr [edi + eax + 0x64], 1
004f859c 0f85a6000000             jne       0x4f8648
004f85a2 85d2                     test      edx, edx
004f85a4 895de0                   mov       dword ptr [ebp - 0x20], ebx
004f85a7 0f8e0c010000             jle       0x4f86b9
004f85ad 8d4900                   lea       ecx, [ecx]
004f85b0 8b16                     mov       edx, dword ptr [esi]
004f85b2 8bce                     mov       ecx, esi
004f85b4 ff92b0050000             call      dword ptr [edx + 0x5b0]
004f85ba 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004f85bd 85c9                     test      ecx, ecx
004f85bf 7476                     je        0x4f8637
004f85c1 8b06                     mov       eax, dword ptr [esi]
004f85c3 8bce                     mov       ecx, esi
004f85c5 ff90c0000000             call      dword ptr [eax + 0xc0]
004f85cb 85c0                     test      eax, eax
004f85cd 750b                     jne       0x4f85da
004f85cf 8b8e4c220000             mov       ecx, dword ptr [esi + 0x224c]
004f85d5 894df0                   mov       dword ptr [ebp - 0x10], ecx
004f85d8 eb0b                     jmp       0x4f85e5
004f85da 8b864c220000             mov       eax, dword ptr [esi + 0x224c]
004f85e0 f7d8                     neg       eax
004f85e2 8945f0                   mov       dword ptr [ebp - 0x10], eax
004f85e5 8b9e54220000             mov       ebx, dword ptr [esi + 0x2254]
004f85eb 8b863c220000             mov       eax, dword ptr [esi + 0x223c]
004f85f1 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f85f4 8b4c0204                 mov       ecx, dword ptr [edx + eax + 4]
004f85f8 6a00                     push      0
004f85fa 8b8618220000             mov       eax, dword ptr [esi + 0x2218]
004f8600 6a00                     push      0
004f8602 6a00                     push      0
004f8604 6a00                     push      0
004f8606 8b16                     mov       edx, dword ptr [esi]
004f8608 6a00                     push      0
004f860a 6a04                     push      4
004f860c f7db                     neg       ebx
004f860e 53                       push      ebx
004f860f 8b9e50220000             mov       ebx, dword ptr [esi + 0x2250]
004f8615 f7db                     neg       ebx
004f8617 53                       push      ebx
004f8618 8b5df0                   mov       ebx, dword ptr [ebp - 0x10]
004f861b 53                       push      ebx
004f861c 8b5de0                   mov       ebx, dword ptr [ebp - 0x20]
004f861f 8b0c99                   mov       ecx, dword ptr [ecx + ebx*4]
004f8622 6a00                     push      0
004f8624 51                       push      ecx
004f8625 8b4c0714                 mov       ecx, dword ptr [edi + eax + 0x14]
004f8629 8b440710                 mov       eax, dword ptr [edi + eax + 0x10]
004f862d 51                       push      ecx
004f862e 50                       push      eax
004f862f 8bce                     mov       ecx, esi
004f8631 ff92b8020000             call      dword ptr [edx + 0x2b8]
004f8637 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
004f863a 43                       inc       ebx
004f863b 3bd8                     cmp       ebx, eax
004f863d 895de0                   mov       dword ptr [ebp - 0x20], ebx
