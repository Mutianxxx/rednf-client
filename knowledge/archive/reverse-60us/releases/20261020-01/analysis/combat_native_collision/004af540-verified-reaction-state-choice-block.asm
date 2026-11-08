004af540 55                       push      ebp
004af541 8bec                     mov       ebp, esp
004af543 83ec10                   sub       esp, 0x10
004af546 53                       push      ebx
004af547 56                       push      esi
004af548 8bf1                     mov       esi, ecx
004af54a 8b06                     mov       eax, dword ptr [esi]
004af54c 6811020000               push      0x211
004af551 c745f800000000           mov       dword ptr [ebp - 8], 0
004af558 ff502c                   call      dword ptr [eax + 0x2c]
004af55b 84c0                     test      al, al
004af55d 741a                     je        0x4af579
004af55f 6a00                     push      0
004af561 682829f400               push      0xf42928
004af566 686c52f500               push      0xf5526c
004af56b 6a00                     push      0
004af56d 56                       push      esi
004af56e e898177500               call      0xc00d0b
004af573 83c414                   add       esp, 0x14
004af576 8945f8                   mov       dword ptr [ebp - 8], eax
004af579 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004af57c 8b11                     mov       edx, dword ptr [ecx]
004af57e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004af585 ff929c010000             call      dword ptr [edx + 0x19c]
004af58b 8b98ec000000             mov       ebx, dword ptr [eax + 0xec]
004af591 83fb03                   cmp       ebx, 3
004af594 8945f4                   mov       dword ptr [ebp - 0xc], eax
004af597 7532                     jne       0x4af5cb
004af599 8b8e28020000             mov       ecx, dword ptr [esi + 0x228]
004af59f 8b8624020000             mov       eax, dword ptr [esi + 0x224]
004af5a5 3bc1                     cmp       eax, ecx
004af5a7 741b                     je        0x4af5c4
004af5a9 8da42400000000           lea       esp, [esp]
004af5b0 833812                   cmp       dword ptr [eax], 0x12
004af5b3 7407                     je        0x4af5bc
004af5b5 83c004                   add       eax, 4
004af5b8 3bc1                     cmp       eax, ecx
004af5ba 75f4                     jne       0x4af5b0
004af5bc 3bc1                     cmp       eax, ecx
004af5be 0f85b3020000             jne       0x4af877
004af5c4 bb01000000               mov       ebx, 1
004af5c9 eb08                     jmp       0x4af5d3
004af5cb 85db                     test      ebx, ebx
004af5cd 0f84a4020000             je        0x4af877
004af5d3 57                       push      edi
004af5d4 8d8ebc040000             lea       ecx, [esi + 0x4bc]
004af5da e8812af5ff               call      0x402060
004af5df 85c0                     test      eax, eax
004af5e1 740d                     je        0x4af5f0
004af5e3 8d8ec4040000             lea       ecx, [esi + 0x4c4]
004af5e9 e8722af5ff               call      0x402060
004af5ee eb07                     jmp       0x4af5f7
004af5f0 8bce                     mov       ecx, esi
004af5f2 e8e9a9feff               call      0x499fe0
004af5f7 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004af5fa 51                       push      ecx
004af5fb 8d55f0                   lea       edx, [ebp - 0x10]
004af5fe 8bf8                     mov       edi, eax
004af600 8b06                     mov       eax, dword ptr [esi]
004af602 52                       push      edx
004af603 8bce                     mov       ecx, esi
004af605 c745f064000000           mov       dword ptr [ebp - 0x10], 0x64
004af60c ff9010030000             call      dword ptr [eax + 0x310]
004af612 83ff02                   cmp       edi, 2
004af615 740f                     je        0x4af626
004af617 83f801                   cmp       eax, 1
004af61a 7405                     je        0x4af621
004af61c 83f802                   cmp       eax, 2
004af61f 7505                     jne       0x4af626
004af621 bf01000000               mov       edi, 1
004af626 8b06                     mov       eax, dword ptr [esi]
004af628 8bce                     mov       ecx, esi
004af62a ff90dc030000             call      dword ptr [eax + 0x3dc]
004af630 84c0                     test      al, al
004af632 0f84ba000000             je        0x4af6f2
004af638 8b16                     mov       edx, dword ptr [esi]
004af63a 6811020000               push      0x211
004af63f 8bce                     mov       ecx, esi
004af641 c6450c00                 mov       byte ptr [ebp + 0xc], 0
004af645 ff522c                   call      dword ptr [edx + 0x2c]
004af648 84c0                     test      al, al
004af64a 740d                     je        0x4af659
004af64c 8b06                     mov       eax, dword ptr [esi]
004af64e 8bce                     mov       ecx, esi
004af650 ff90f0040000             call      dword ptr [eax + 0x4f0]
004af656 88450c                   mov       byte ptr [ebp + 0xc], al
004af659 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004af65c 8b3e                     mov       edi, dword ptr [esi]
004af65e 51                       push      ecx
004af65f 8bce                     mov       ecx, esi
004af661 ff9730020000             call      dword ptr [edi + 0x230]
004af667 50                       push      eax
004af668 8bce                     mov       ecx, esi
004af66a ff97e4030000             call      dword ptr [edi + 0x3e4]
004af670 83f805                   cmp       eax, 5
004af673 8945fc                   mov       dword ptr [ebp - 4], eax
004af676 0f85fa010000             jne       0x4af876
004af67c 8b7df4                   mov       edi, dword ptr [ebp - 0xc]
004af67f 8d8ff0000000             lea       ecx, [edi + 0xf0]
004af685 e8d629f5ff               call      0x402060
004af68a 3d96000000               cmp       eax, 0x96
004af68f 7d3d                     jge       0x4af6ce
004af691 8d8f18010000             lea       ecx, [edi + 0x118]
004af697 e8c429f5ff               call      0x402060
004af69c 83f801                   cmp       eax, 1
004af69f 742d                     je        0x4af6ce
004af6a1 8d8ff8000000             lea       ecx, [edi + 0xf8]
004af6a7 e8b429f5ff               call      0x402060
004af6ac 33d2                     xor       edx, edx
004af6ae 3d90010000               cmp       eax, 0x190
004af6b3 8b4508                   mov       eax, dword ptr [ebp + 8]
004af6b6 0f9cc2                   setl      dl
004af6b9 5f                       pop       edi
004af6ba 5e                       pop       esi
004af6bb 5b                       pop       ebx
004af6bc 4a                       dec       edx
004af6bd 83e203                   and       edx, 3
