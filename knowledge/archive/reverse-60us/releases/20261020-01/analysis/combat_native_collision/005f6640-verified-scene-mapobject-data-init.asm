005f6640 55                       push      ebp
005f6641 8bec                     mov       ebp, esp
005f6643 6aff                     push      -1
005f6645 68f375c600               push      0xc675f3
005f664a 64a100000000             mov       eax, dword ptr fs:[0]
005f6650 50                       push      eax
005f6651 64892500000000           mov       dword ptr fs:[0], esp
005f6658 83ec08                   sub       esp, 8
005f665b 53                       push      ebx
005f665c 56                       push      esi
005f665d 8bf1                     mov       esi, ecx
005f665f 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f6665 85c9                     test      ecx, ecx
005f6667 0f84f3000000             je        0x5f6760
005f666d 8b8650050000             mov       eax, dword ptr [esi + 0x550]
005f6673 2bc1                     sub       eax, ecx
005f6675 c1f802                   sar       eax, 2
005f6678 83f805                   cmp       eax, 5
005f667b 0f82df000000             jb        0x5f6760
005f6681 8d86e4080000             lea       eax, [esi + 0x8e4]
005f6687 33db                     xor       ebx, ebx
005f6689 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f668c 57                       push      edi
005f668d 8d4900                   lea       ecx, [ecx]
005f6690 8b864c050000             mov       eax, dword ptr [esi + 0x54c]
005f6696 8b0403                   mov       eax, dword ptr [ebx + eax]
005f6699 85c0                     test      eax, eax
005f669b 7462                     je        0x5f66ff
005f669d 8b4804                   mov       ecx, dword ptr [eax + 4]
005f66a0 85c9                     test      ecx, ecx
005f66a2 765b                     jbe       0x5f66ff
005f66a4 68b4010000               push      0x1b4
005f66a9 e8a2d5e0ff               call      0x403c50
005f66ae 83c404                   add       esp, 4
005f66b1 8945ec                   mov       dword ptr [ebp - 0x14], eax
005f66b4 85c0                     test      eax, eax
005f66b6 c745fc00000000           mov       dword ptr [ebp - 4], 0
005f66bd 7432                     je        0x5f66f1
005f66bf 8b864c050000             mov       eax, dword ptr [esi + 0x54c]
005f66c5 8d0c03                   lea       ecx, [ebx + eax]
005f66c8 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
005f66cf 7208                     jb        0x5f66d9
005f66d1 8bbe48020000             mov       edi, dword ptr [esi + 0x248]
005f66d7 eb06                     jmp       0x5f66df
005f66d9 8dbe48020000             lea       edi, [esi + 0x248]
005f66df 56                       push      esi
005f66e0 e80bca4500               call      0xa530f0
005f66e5 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
005f66e8 50                       push      eax
005f66e9 57                       push      edi
005f66ea e851cdeaff               call      0x4a3440
005f66ef eb02                     jmp       0x5f66f3
005f66f1 33c0                     xor       eax, eax
005f66f3 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
005f66f6 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f66fd 8901                     mov       dword ptr [ecx], eax
005f66ff 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
005f6702 83c304                   add       ebx, 4
005f6705 83c104                   add       ecx, 4
005f6708 83fb0c                   cmp       ebx, 0xc
005f670b 894df0                   mov       dword ptr [ebp - 0x10], ecx
005f670e 7c80                     jl        0x5f6690
005f6710 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f6716 85c9                     test      ecx, ecx
005f6718 7445                     je        0x5f675f
005f671a 8b8650050000             mov       eax, dword ptr [esi + 0x550]
005f6720 2bc1                     sub       eax, ecx
005f6722 c1f802                   sar       eax, 2
005f6725 83f802                   cmp       eax, 2
005f6728 7235                     jb        0x5f675f
005f672a bf0c000000               mov       edi, 0xc
005f672f 8d9ef0080000             lea       ebx, [esi + 0x8f0]
005f6735 8b964c050000             mov       edx, dword ptr [esi + 0x54c]
005f673b 8b0417                   mov       eax, dword ptr [edi + edx]
005f673e 85c0                     test      eax, eax
005f6740 8d0c17                   lea       ecx, [edi + edx]
005f6743 740f                     je        0x5f6754
005f6745 8b5004                   mov       edx, dword ptr [eax + 4]
005f6748 85d2                     test      edx, edx
005f674a 7608                     jbe       0x5f6754
005f674c 51                       push      ecx
005f674d 8bcb                     mov       ecx, ebx
005f674f e83ccd4500               call      0xa53490
005f6754 83c704                   add       edi, 4
005f6757 83c304                   add       ebx, 4
005f675a 83ff18                   cmp       edi, 0x18
005f675d 7cd6                     jl        0x5f6735
005f675f 5f                       pop       edi
005f6760 8b8e34020000             mov       ecx, dword ptr [esi + 0x234]
005f6766 85c9                     test      ecx, ecx
005f6768 7470                     je        0x5f67da
005f676a 8b8638020000             mov       eax, dword ptr [esi + 0x238]
005f6770 2bc1                     sub       eax, ecx
005f6772 c1f802                   sar       eax, 2
005f6775 83f806                   cmp       eax, 6
005f6778 7260                     jb        0x5f67da
005f677a 8bc1                     mov       eax, ecx
005f677c 8b08                     mov       ecx, dword ptr [eax]
005f677e 898e80080000             mov       dword ptr [esi + 0x880], ecx
005f6784 8b5004                   mov       edx, dword ptr [eax + 4]
005f6787 899684080000             mov       dword ptr [esi + 0x884], edx
005f678d 8b5808                   mov       ebx, dword ptr [eax + 8]
005f6790 85db                     test      ebx, ebx
005f6792 0f95c1                   setne     cl
005f6795 888e88080000             mov       byte ptr [esi + 0x888], cl
005f679b 8b500c                   mov       edx, dword ptr [eax + 0xc]
005f679e 899670080000             mov       dword ptr [esi + 0x870], edx
005f67a4 8b4810                   mov       ecx, dword ptr [eax + 0x10]
005f67a7 898e74080000             mov       dword ptr [esi + 0x874], ecx
005f67ad 8b5014                   mov       edx, dword ptr [eax + 0x14]
005f67b0 899678080000             mov       dword ptr [esi + 0x878], edx
005f67b6 8b4018                   mov       eax, dword ptr [eax + 0x18]
005f67b9 8b16                     mov       edx, dword ptr [esi]
005f67bb 50                       push      eax
005f67bc 8bce                     mov       ecx, esi
005f67be ff925c030000             call      dword ptr [edx + 0x35c]
005f67c4 8b8634020000             mov       eax, dword ptr [esi + 0x234]
005f67ca 8b16                     mov       edx, dword ptr [esi]
005f67cc 83c018                   add       eax, 0x18
005f67cf 8b00                     mov       eax, dword ptr [eax]
005f67d1 50                       push      eax
005f67d2 8bce                     mov       ecx, esi
005f67d4 ff9260030000             call      dword ptr [edx + 0x360]
005f67da 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f67dd 5e                       pop       esi
005f67de 5b                       pop       ebx
005f67df 64890d00000000           mov       dword ptr fs:[0], ecx
005f67e6 8be5                     mov       esp, ebp
005f67e8 5d                       pop       ebp
005f67e9 c3                       ret       
