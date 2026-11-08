005f74c0 55                       push      ebp
005f74c1 8bec                     mov       ebp, esp
005f74c3 6aff                     push      -1
005f74c5 68c776c600               push      0xc676c7
005f74ca 64a100000000             mov       eax, dword ptr fs:[0]
005f74d0 50                       push      eax
005f74d1 64892500000000           mov       dword ptr fs:[0], esp
005f74d8 83ec10                   sub       esp, 0x10
005f74db 56                       push      esi
005f74dc 8bf1                     mov       esi, ecx
005f74de 8b8e00090000             mov       ecx, dword ptr [esi + 0x900]
005f74e4 85c9                     test      ecx, ecx
005f74e6 0f8404020000             je        0x5f76f0
005f74ec 8b8604090000             mov       eax, dword ptr [esi + 0x904]
005f74f2 2bc1                     sub       eax, ecx
005f74f4 c1f803                   sar       eax, 3
005f74f7 85c0                     test      eax, eax
005f74f9 0f84f1010000             je        0x5f76f0
005f74ff 8b8600010000             mov       eax, dword ptr [esi + 0x100]
005f7505 85c0                     test      eax, eax
005f7507 0f94c1                   sete      cl
005f750a 84c9                     test      cl, cl
005f750c 7422                     je        0x5f7530
005f750e 68ec010000               push      0x1ec
005f7513 68b016d500               push      0xd516b0
005f7518 ff15bc2eff00             call      dword ptr [0xff2ebc]
005f751e 83c408                   add       esp, 8
005f7521 5e                       pop       esi
005f7522 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f7525 64890d00000000           mov       dword ptr fs:[0], ecx
005f752c 8be5                     mov       esp, ebp
005f752e 5d                       pop       ebp
005f752f c3                       ret       
005f7530 8b8014010000             mov       eax, dword ptr [eax + 0x114]
005f7536 85c0                     test      eax, eax
005f7538 0f94c1                   sete      cl
005f753b 84c9                     test      cl, cl
005f753d 7422                     je        0x5f7561
005f753f 68ed010000               push      0x1ed
005f7544 68b016d500               push      0xd516b0
005f7549 ff15bc2eff00             call      dword ptr [0xff2ebc]
005f754f 83c408                   add       esp, 8
005f7552 5e                       pop       esi
005f7553 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f7556 64890d00000000           mov       dword ptr fs:[0], ecx
005f755d 8be5                     mov       esp, ebp
005f755f 5d                       pop       ebp
005f7560 c3                       ret       
005f7561 57                       push      edi
005f7562 8bb8b4000000             mov       edi, dword ptr [eax + 0xb4]
005f7568 85ff                     test      edi, edi
005f756a 0f94c1                   sete      cl
005f756d 84c9                     test      cl, cl
005f756f 7423                     je        0x5f7594
005f7571 68ee010000               push      0x1ee
005f7576 68b016d500               push      0xd516b0
005f757b ff15bc2eff00             call      dword ptr [0xff2ebc]
005f7581 83c408                   add       esp, 8
005f7584 5f                       pop       edi
005f7585 5e                       pop       esi
005f7586 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f7589 64890d00000000           mov       dword ptr fs:[0], ecx
005f7590 8be5                     mov       esp, ebp
005f7592 5d                       pop       ebp
005f7593 c3                       ret       
005f7594 8b8e00090000             mov       ecx, dword ptr [esi + 0x900]
005f759a 85c9                     test      ecx, ecx
005f759c 53                       push      ebx
005f759d 7504                     jne       0x5f75a3
005f759f 33db                     xor       ebx, ebx
005f75a1 eb0b                     jmp       0x5f75ae
005f75a3 8b9e04090000             mov       ebx, dword ptr [esi + 0x904]
005f75a9 2bd9                     sub       ebx, ecx
005f75ab c1fb03                   sar       ebx, 3
005f75ae 8b80b4000000             mov       eax, dword ptr [eax + 0xb4]
005f75b4 8bb8e8020000             mov       edi, dword ptr [eax + 0x2e8]
005f75ba 8b06                     mov       eax, dword ptr [esi]
005f75bc 8bce                     mov       ecx, esi
005f75be ff5040                   call      dword ptr [eax + 0x40]
005f75c1 03c3                     add       eax, ebx
005f75c3 03c7                     add       eax, edi
005f75c5 33d2                     xor       edx, edx
005f75c7 8945e8                   mov       dword ptr [ebp - 0x18], eax
005f75ca b968010000               mov       ecx, 0x168
005f75cf f7f1                     div       ecx
005f75d1 8b9e00090000             mov       ebx, dword ptr [esi + 0x900]
005f75d7 3b9e04090000             cmp       ebx, dword ptr [esi + 0x904]
005f75dd 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f75e0 8955f0                   mov       dword ptr [ebp - 0x10], edx
005f75e3 0f84de000000             je        0x5f76c7
005f75e9 8da42400000000           lea       esp, [esp]
005f75f0 6808090000               push      0x908
005f75f5 e856c6e0ff               call      0x403c50
005f75fa 83c404                   add       esp, 4
005f75fd 8945e4                   mov       dword ptr [ebp - 0x1c], eax
005f7600 33ff                     xor       edi, edi
005f7602 3bc7                     cmp       eax, edi
005f7604 897dfc                   mov       dword ptr [ebp - 4], edi
005f7607 7417                     je        0x5f7620
005f7609 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
005f760c 6a64                     push      0x64
005f760e 52                       push      edx
005f760f 8b5304                   mov       edx, dword ptr [ebx + 4]
005f7612 8d4de8                   lea       ecx, [ebp - 0x18]
005f7615 51                       push      ecx
005f7616 52                       push      edx
005f7617 8bc8                     mov       ecx, eax
005f7619 e8b221e4ff               call      0x4397d0
005f761e 8bf8                     mov       edi, eax
005f7620 8b06                     mov       eax, dword ptr [esi]
005f7622 8b1f                     mov       ebx, dword ptr [edi]
005f7624 8bce                     mov       ecx, esi
005f7626 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f762d ff90e4000000             call      dword ptr [eax + 0xe4]
005f7633 8945e4                   mov       dword ptr [ebp - 0x1c], eax
005f7636 db45e4                   fild      dword ptr [ebp - 0x1c]
005f7639 d80ddcb9cc00             fmul      dword ptr [0xccb9dc]
005f763f e8009f6000               call      0xc01544
005f7644 8b16                     mov       edx, dword ptr [esi]
005f7646 50                       push      eax
005f7647 8bce                     mov       ecx, esi
005f7649 ff9298000000             call      dword ptr [edx + 0x98]
005f764f 50                       push      eax
005f7650 8b06                     mov       eax, dword ptr [esi]
005f7652 8bce                     mov       ecx, esi
005f7654 ff9094000000             call      dword ptr [eax + 0x94]
005f765a 50                       push      eax
005f765b 8bcf                     mov       ecx, edi
005f765d ff9388000000             call      dword ptr [ebx + 0x88]
005f7663 8b5dec                   mov       ebx, dword ptr [ebp - 0x14]
005f7666 8b0b                     mov       ecx, dword ptr [ebx]
005f7668 6a00                     push      0
005f766a 6a00                     push      0
005f766c 6a00                     push      0
005f766e 57                       push      edi
005f766f 51                       push      ecx
005f7670 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f7676 6821010000               push      0x121
005f767b 56                       push      esi
005f767c e8ef66f1ff               call      0x50dd70
005f7681 8b8600090000             mov       eax, dword ptr [esi + 0x900]
005f7687 85c0                     test      eax, eax
005f7689 7504                     jne       0x5f768f
005f768b 33c9                     xor       ecx, ecx
005f768d eb0b                     jmp       0x5f769a
005f768f 8b8e04090000             mov       ecx, dword ptr [esi + 0x904]
005f7695 2bc8                     sub       ecx, eax
005f7697 c1f903                   sar       ecx, 3
005f769a 33d2                     xor       edx, edx
005f769c b868010000               mov       eax, 0x168
005f76a1 f7f1                     div       ecx
005f76a3 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
005f76a6 57                       push      edi
005f76a7 03c8                     add       ecx, eax
005f76a9 894df0                   mov       dword ptr [ebp - 0x10], ecx
005f76ac 8bce                     mov       ecx, esi
005f76ae e87d5eefff               call      0x4ed530
005f76b3 8b8604090000             mov       eax, dword ptr [esi + 0x904]
005f76b9 83c308                   add       ebx, 8
005f76bc 3bd8                     cmp       ebx, eax
005f76be 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f76c1 0f8529ffffff             jne       0x5f75f0
005f76c7 8b8600090000             mov       eax, dword ptr [esi + 0x900]
005f76cd 33ff                     xor       edi, edi
005f76cf 3bc7                     cmp       eax, edi
005f76d1 5b                       pop       ebx
005f76d2 7409                     je        0x5f76dd
005f76d4 50                       push      eax
005f76d5 e803896000               call      0xbfffdd
005f76da 83c404                   add       esp, 4
005f76dd 89be00090000             mov       dword ptr [esi + 0x900], edi
005f76e3 89be04090000             mov       dword ptr [esi + 0x904], edi
005f76e9 89be08090000             mov       dword ptr [esi + 0x908], edi
005f76ef 5f                       pop       edi
005f76f0 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f76f3 5e                       pop       esi
005f76f4 64890d00000000           mov       dword ptr fs:[0], ecx
005f76fb 8be5                     mov       esp, ebp
005f76fd 5d                       pop       ebp
005f76fe c3                       ret       
005f76ff cc                       int3      
