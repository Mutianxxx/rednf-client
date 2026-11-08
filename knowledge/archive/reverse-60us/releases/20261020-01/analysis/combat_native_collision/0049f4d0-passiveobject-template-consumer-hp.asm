0049f4d0 55                       push      ebp
0049f4d1 8bec                     mov       ebp, esp
0049f4d3 6aff                     push      -1
0049f4d5 68db6bc500               push      0xc56bdb
0049f4da 64a100000000             mov       eax, dword ptr fs:[0]
0049f4e0 50                       push      eax
0049f4e1 64892500000000           mov       dword ptr fs:[0], esp
0049f4e8 81ec98030000             sub       esp, 0x398
0049f4ee 53                       push      ebx
0049f4ef 8b5d08                   mov       ebx, dword ptr [ebp + 8]
0049f4f2 56                       push      esi
0049f4f3 57                       push      edi
0049f4f4 53                       push      ebx
0049f4f5 8bf1                     mov       esi, ecx
0049f4f7 8b0de4300001             mov       ecx, dword ptr [0x10030e4]
0049f4fd 6a00                     push      0
0049f4ff e82cd96d00               call      0xb7ce30
0049f504 8bf8                     mov       edi, eax
0049f506 85ff                     test      edi, edi
0049f508 7522                     jne       0x49f52c
0049f50a 53                       push      ebx
0049f50b 6870f0cc00               push      0xccf070
0049f510 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049f516 83c408                   add       esp, 8
0049f519 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049f51c 64890d00000000           mov       dword ptr fs:[0], ecx
0049f523 5f                       pop       edi
0049f524 5e                       pop       esi
0049f525 5b                       pop       ebx
0049f526 8be5                     mov       esp, ebp
0049f528 5d                       pop       ebp
0049f529 c20800                   ret       8
0049f52c 8a8774010000             mov       al, byte ptr [edi + 0x174]
0049f532 84c0                     test      al, al
0049f534 7413                     je        0x49f549
0049f536 8b0d48280001             mov       ecx, dword ptr [0x1002848]
0049f53c e88fb0f9ff               call      0x43a5d0
0049f541 84c0                     test      al, al
0049f543 0f84d6120000             je        0x4a081f
0049f549 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049f54f e89c3b5b00               call      0xa530f0
0049f554 8bd8                     mov       ebx, eax
0049f556 53                       push      ebx
0049f557 e871087600               call      0xbffdcd
0049f55c 83c404                   add       esp, 4
0049f55f 50                       push      eax
0049f560 53                       push      ebx
0049f561 8d8e44020000             lea       ecx, [esi + 0x244]
0049f567 e81439f6ff               call      0x402e80
0049f56c 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f56f 898644050000             mov       dword ptr [esi + 0x544], eax
0049f575 8b0f                     mov       ecx, dword ptr [edi]
0049f577 8d5704                   lea       edx, [edi + 4]
0049f57a 898e04020000             mov       dword ptr [esi + 0x204], ecx
0049f580 8d8e08020000             lea       ecx, [esi + 0x208]
0049f586 52                       push      edx
0049f587 e8043f5b00               call      0xa53490
0049f58c a1d8012101               mov       eax, dword ptr [0x12101d8]
0049f591 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049f594 8b8610020000             mov       eax, dword ptr [esi + 0x210]
0049f59a 8b4f08                   mov       ecx, dword ptr [edi + 8]
0049f59d c1e002                   shl       eax, 2
0049f5a0 8d1c10                   lea       ebx, [eax + edx]
0049f5a3 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5a9 33d9                     xor       ebx, ecx
0049f5ab 891c10                   mov       dword ptr [eax + edx], ebx
0049f5ae 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049f5b4 8b5248                   mov       edx, dword ptr [edx + 0x48]
0049f5b7 8b8610020000             mov       eax, dword ptr [esi + 0x210]
0049f5bd c1e002                   shl       eax, 2
0049f5c0 8d1c10                   lea       ebx, [eax + edx]
0049f5c3 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5c9 33d9                     xor       ebx, ecx
0049f5cb 891c10                   mov       dword ptr [eax + edx], ebx
0049f5ce a1d8012101               mov       eax, dword ptr [0x12101d8]
0049f5d3 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049f5d6 8b8618020000             mov       eax, dword ptr [esi + 0x218]
0049f5dc 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049f5df c1e002                   shl       eax, 2
0049f5e2 8d1c10                   lea       ebx, [eax + edx]
0049f5e5 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f5eb 33d9                     xor       ebx, ecx
0049f5ed 891c10                   mov       dword ptr [eax + edx], ebx
0049f5f0 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049f5f6 8b5248                   mov       edx, dword ptr [edx + 0x48]
0049f5f9 8b8618020000             mov       eax, dword ptr [esi + 0x218]
0049f5ff c1e002                   shl       eax, 2
0049f602 8d1c10                   lea       ebx, [eax + edx]
0049f605 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049f60b 33d9                     xor       ebx, ecx
0049f60d 891c10                   mov       dword ptr [eax + edx], ebx
0049f610 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049f613 89861c020000             mov       dword ptr [esi + 0x21c], eax
0049f619 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049f61c 898ef4000000             mov       dword ptr [esi + 0xf4], ecx
0049f622 8b5718                   mov       edx, dword ptr [edi + 0x18]
0049f625 89962c050000             mov       dword ptr [esi + 0x52c], edx
0049f62b 8b471c                   mov       eax, dword ptr [edi + 0x1c]
0049f62e 898638050000             mov       dword ptr [esi + 0x538], eax
0049f634 8b4f20                   mov       ecx, dword ptr [edi + 0x20]
0049f637 8d5724                   lea       edx, [edi + 0x24]
0049f63a 898e3c050000             mov       dword ptr [esi + 0x53c], ecx
0049f640 8d8e20020000             lea       ecx, [esi + 0x220]
0049f646 52                       push      edx
0049f647 e8f4820600               call      0x507940
0049f64c 8b06                     mov       eax, dword ptr [esi]
0049f64e 6a01                     push      1
0049f650 6a18                     push      0x18
0049f652 8bce                     mov       ecx, esi
0049f654 ff901c020000             call      dword ptr [eax + 0x21c]
0049f65a 8d5f34                   lea       ebx, [edi + 0x34]
0049f65d 68e0baca00               push      0xcabae0
0049f662 8bcb                     mov       ecx, ebx
0049f664 e8873a5b00               call      0xa530f0
0049f669 50                       push      eax
0049f66a e87c177600               call      0xc00deb
0049f66f 83c408                   add       esp, 8
0049f672 85c0                     test      eax, eax
0049f674 7452                     je        0x49f6c8
0049f676 68e8010000               push      0x1e8
0049f67b e8d045f6ff               call      0x403c50
0049f680 83c404                   add       esp, 4
0049f683 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f686 85c0                     test      eax, eax
0049f688 c745fc00000000           mov       dword ptr [ebp - 4], 0
0049f68f 7426                     je        0x49f6b7
0049f691 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049f697 e8543a5b00               call      0xa530f0
0049f69c 6a01                     push      1
0049f69e 8bcb                     mov       ecx, ebx
0049f6a0 894508                   mov       dword ptr [ebp + 8], eax
0049f6a3 e8483a5b00               call      0xa530f0
0049f6a8 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f6ab 50                       push      eax
0049f6ac 51                       push      ecx
0049f6ad 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f6b0 e8ab33fdff               call      0x472a60
0049f6b5 eb02                     jmp       0x49f6b9
0049f6b7 33c0                     xor       eax, eax
0049f6b9 8b16                     mov       edx, dword ptr [esi]
0049f6bb 50                       push      eax
0049f6bc 8bce                     mov       ecx, esi
0049f6be c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049f6c5 ff526c                   call      dword ptr [edx + 0x6c]
0049f6c8 8b473c                   mov       eax, dword ptr [edi + 0x3c]
0049f6cb 8b4f40                   mov       ecx, dword ptr [edi + 0x40]
0049f6ce 3bc1                     cmp       eax, ecx
0049f6d0 894508                   mov       dword ptr [ebp + 8], eax
0049f6d3 0f8417010000             je        0x49f7f0
0049f6d9 8d9e1c010000             lea       ebx, [esi + 0x11c]
0049f6df 90                       nop       
0049f6e0 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f6e3 68e0baca00               push      0xcabae0
0049f6e8 e8033a5b00               call      0xa530f0
0049f6ed 50                       push      eax
0049f6ee e8f8167600               call      0xc00deb
0049f6f3 83c408                   add       esp, 8
0049f6f6 85c0                     test      eax, eax
0049f6f8 0f8492000000             je        0x49f790
0049f6fe 68e8010000               push      0x1e8
0049f703 e84845f6ff               call      0x403c50
0049f708 83c404                   add       esp, 4
0049f70b 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049f70e 85c0                     test      eax, eax
0049f710 c745fc01000000           mov       dword ptr [ebp - 4], 1
0049f717 742a                     je        0x49f743
0049f719 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049f71f e8cc395b00               call      0xa530f0
0049f724 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f727 6a01                     push      1
0049f729 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f72c e8bf395b00               call      0xa530f0
0049f731 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049f734 50                       push      eax
0049f735 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f738 50                       push      eax
0049f739 e82233fdff               call      0x472a60
0049f73e 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f741 eb07                     jmp       0x49f74a
0049f743 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
0049f74a 8b5304                   mov       edx, dword ptr [ebx + 4]
0049f74d 85d2                     test      edx, edx
0049f74f 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f752 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049f759 894df0                   mov       dword ptr [ebp - 0x10], ecx
0049f75c 7504                     jne       0x49f762
0049f75e 33c0                     xor       eax, eax
0049f760 eb08                     jmp       0x49f76a
0049f762 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f765 2bc2                     sub       eax, edx
0049f767 c1f802                   sar       eax, 2
0049f76a 85d2                     test      edx, edx
0049f76c 741c                     je        0x49f78a
0049f76e 8b4b0c                   mov       ecx, dword ptr [ebx + 0xc]
0049f771 2bca                     sub       ecx, edx
0049f773 c1f902                   sar       ecx, 2
0049f776 3bc1                     cmp       eax, ecx
0049f778 7310                     jae       0x49f78a
0049f77a 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f77d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
0049f780 8910                     mov       dword ptr [eax], edx
0049f782 83c004                   add       eax, 4
0049f785 894308                   mov       dword ptr [ebx + 8], eax
0049f788 eb52                     jmp       0x49f7dc
0049f78a 8d4df0                   lea       ecx, [ebp - 0x10]
0049f78d 51                       push      ecx
0049f78e eb3f                     jmp       0x49f7cf
0049f790 8b5304                   mov       edx, dword ptr [ebx + 4]
0049f793 85d2                     test      edx, edx
0049f795 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
0049f79c 7504                     jne       0x49f7a2
0049f79e 33c9                     xor       ecx, ecx
0049f7a0 eb08                     jmp       0x49f7aa
0049f7a2 8b4b08                   mov       ecx, dword ptr [ebx + 8]
0049f7a5 2bca                     sub       ecx, edx
0049f7a7 c1f902                   sar       ecx, 2
0049f7aa 85d2                     test      edx, edx
0049f7ac 741d                     je        0x49f7cb
0049f7ae 8b430c                   mov       eax, dword ptr [ebx + 0xc]
0049f7b1 2bc2                     sub       eax, edx
0049f7b3 c1f802                   sar       eax, 2
0049f7b6 3bc8                     cmp       ecx, eax
0049f7b8 7311                     jae       0x49f7cb
0049f7ba 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f7bd c70000000000             mov       dword ptr [eax], 0
0049f7c3 83c004                   add       eax, 4
0049f7c6 894308                   mov       dword ptr [ebx + 8], eax
0049f7c9 eb11                     jmp       0x49f7dc
0049f7cb 8d550c                   lea       edx, [ebp + 0xc]
0049f7ce 52                       push      edx
0049f7cf 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f7d2 6a01                     push      1
0049f7d4 8bcb                     mov       ecx, ebx
0049f7d6 50                       push      eax
0049f7d7 e88489f6ff               call      0x408160
0049f7dc 8b4508                   mov       eax, dword ptr [ebp + 8]
0049f7df 8b4f40                   mov       ecx, dword ptr [edi + 0x40]
0049f7e2 83c004                   add       eax, 4
0049f7e5 3bc1                     cmp       eax, ecx
0049f7e7 894508                   mov       dword ptr [ebp + 8], eax
0049f7ea 0f85f0feffff             jne       0x49f6e0
0049f7f0 8d4f48                   lea       ecx, [edi + 0x48]
0049f7f3 68e0baca00               push      0xcabae0
0049f7f8 e8f3385b00               call      0xa530f0
0049f7fd 50                       push      eax
0049f7fe e8e8157600               call      0xc00deb
0049f803 83c408                   add       esp, 8
0049f806 85c0                     test      eax, eax
0049f808 7468                     je        0x49f872
0049f80a 68e0020000               push      0x2e0
0049f80f e83c44f6ff               call      0x403c50
0049f814 8bd8                     mov       ebx, eax
0049f816 83c404                   add       esp, 4
0049f819 895d0c                   mov       dword ptr [ebp + 0xc], ebx
0049f81c 85db                     test      ebx, ebx
0049f81e c745fc02000000           mov       dword ptr [ebp - 4], 2
0049f825 7426                     je        0x49f84d
0049f827 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049f82d e8be385b00               call      0xa530f0
0049f832 6a00                     push      0
0049f834 8d4f48                   lea       ecx, [edi + 0x48]
0049f837 894508                   mov       dword ptr [ebp + 8], eax
0049f83a e8b1385b00               call      0xa530f0
0049f83f 50                       push      eax
0049f840 8b4508                   mov       eax, dword ptr [ebp + 8]
0049f843 50                       push      eax
0049f844 8bcb                     mov       ecx, ebx
0049f846 e8b5400000               call      0x4a3900
0049f84b eb02                     jmp       0x49f84f
0049f84d 33c0                     xor       eax, eax
0049f84f 8b16                     mov       edx, dword ptr [esi]
0049f851 50                       push      eax
0049f852 8bce                     mov       ecx, esi
0049f854 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049f85b ff5270                   call      dword ptr [edx + 0x70]
0049f85e 8b864c010000             mov       eax, dword ptr [esi + 0x14c]
0049f864 33c9                     xor       ecx, ecx
0049f866 8988cc020000             mov       dword ptr [eax + 0x2cc], ecx
0049f86c 8988d0020000             mov       dword ptr [eax + 0x2d0], ecx
0049f872 8b4f50                   mov       ecx, dword ptr [edi + 0x50]
0049f875 8b4754                   mov       eax, dword ptr [edi + 0x54]
0049f878 3bc8                     cmp       ecx, eax
0049f87a c7450c00000000           mov       dword ptr [ebp + 0xc], 0
0049f881 894d08                   mov       dword ptr [ebp + 8], ecx
0049f884 0f8438010000             je        0x49f9c2
0049f88a 8d9e58010000             lea       ebx, [esi + 0x158]
0049f890 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f893 68e0baca00               push      0xcabae0
0049f898 e853385b00               call      0xa530f0
0049f89d 50                       push      eax
0049f89e e848157600               call      0xc00deb
0049f8a3 83c408                   add       esp, 8
0049f8a6 85c0                     test      eax, eax
0049f8a8 0f84ad000000             je        0x49f95b
0049f8ae 68e0020000               push      0x2e0
0049f8b3 e89843f6ff               call      0x403c50
0049f8b8 83c404                   add       esp, 4
0049f8bb 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049f8be 85c0                     test      eax, eax
0049f8c0 c745fc03000000           mov       dword ptr [ebp - 4], 3
0049f8c7 7436                     je        0x49f8ff
0049f8c9 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
0049f8d0 720b                     jb        0x49f8dd
0049f8d2 8b8648020000             mov       eax, dword ptr [esi + 0x248]
0049f8d8 8945ec                   mov       dword ptr [ebp - 0x14], eax
0049f8db eb09                     jmp       0x49f8e6
0049f8dd 8d8e48020000             lea       ecx, [esi + 0x248]
0049f8e3 894dec                   mov       dword ptr [ebp - 0x14], ecx
0049f8e6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049f8e9 6a01                     push      1
0049f8eb e800385b00               call      0xa530f0
0049f8f0 8b55ec                   mov       edx, dword ptr [ebp - 0x14]
0049f8f3 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049f8f6 50                       push      eax
0049f8f7 52                       push      edx
0049f8f8 e803400000               call      0x4a3900
0049f8fd eb02                     jmp       0x49f901
0049f8ff 33c0                     xor       eax, eax
0049f901 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f904 c780cc0200000a000000     mov       dword ptr [eax + 0x2cc], 0xa
0049f90e 8988d0020000             mov       dword ptr [eax + 0x2d0], ecx
0049f914 8b4b04                   mov       ecx, dword ptr [ebx + 4]
0049f917 85c9                     test      ecx, ecx
0049f919 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049f920 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049f923 7505                     jne       0x49f92a
0049f925 894dec                   mov       dword ptr [ebp - 0x14], ecx
0049f928 eb0b                     jmp       0x49f935
0049f92a 8b5308                   mov       edx, dword ptr [ebx + 8]
0049f92d 2bd1                     sub       edx, ecx
0049f92f c1fa02                   sar       edx, 2
0049f932 8955ec                   mov       dword ptr [ebp - 0x14], edx
0049f935 85c9                     test      ecx, ecx
0049f937 741c                     je        0x49f955
0049f939 8b530c                   mov       edx, dword ptr [ebx + 0xc]
0049f93c 2bd1                     sub       edx, ecx
0049f93e 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
0049f941 c1fa02                   sar       edx, 2
0049f944 3bca                     cmp       ecx, edx
0049f946 730d                     jae       0x49f955
0049f948 8b4b08                   mov       ecx, dword ptr [ebx + 8]
0049f94b 8901                     mov       dword ptr [ecx], eax
0049f94d 83c104                   add       ecx, 4
0049f950 894b08                   mov       dword ptr [ebx + 8], ecx
0049f953 eb52                     jmp       0x49f9a7
0049f955 8d55f0                   lea       edx, [ebp - 0x10]
0049f958 52                       push      edx
0049f959 eb3f                     jmp       0x49f99a
0049f95b 8b5304                   mov       edx, dword ptr [ebx + 4]
0049f95e 85d2                     test      edx, edx
0049f960 c745f000000000           mov       dword ptr [ebp - 0x10], 0
0049f967 7504                     jne       0x49f96d
0049f969 33c9                     xor       ecx, ecx
0049f96b eb08                     jmp       0x49f975
0049f96d 8b4b08                   mov       ecx, dword ptr [ebx + 8]
0049f970 2bca                     sub       ecx, edx
0049f972 c1f902                   sar       ecx, 2
0049f975 85d2                     test      edx, edx
0049f977 741d                     je        0x49f996
0049f979 8b430c                   mov       eax, dword ptr [ebx + 0xc]
0049f97c 2bc2                     sub       eax, edx
0049f97e c1f802                   sar       eax, 2
0049f981 3bc8                     cmp       ecx, eax
0049f983 7311                     jae       0x49f996
0049f985 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f988 c70000000000             mov       dword ptr [eax], 0
0049f98e 83c004                   add       eax, 4
0049f991 894308                   mov       dword ptr [ebx + 8], eax
0049f994 eb11                     jmp       0x49f9a7
0049f996 8d4df0                   lea       ecx, [ebp - 0x10]
0049f999 51                       push      ecx
0049f99a 8b4308                   mov       eax, dword ptr [ebx + 8]
0049f99d 6a01                     push      1
0049f99f 8bcb                     mov       ecx, ebx
0049f9a1 50                       push      eax
0049f9a2 e8b965f6ff               call      0x405f60
0049f9a7 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049f9aa 8b4f54                   mov       ecx, dword ptr [edi + 0x54]
0049f9ad 40                       inc       eax
0049f9ae 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f9b1 8b4508                   mov       eax, dword ptr [ebp + 8]
0049f9b4 83c004                   add       eax, 4
0049f9b7 3bc1                     cmp       eax, ecx
0049f9b9 894508                   mov       dword ptr [ebp + 8], eax
0049f9bc 0f85cefeffff             jne       0x49f890
0049f9c2 8d5f5c                   lea       ebx, [edi + 0x5c]
0049f9c5 68e0baca00               push      0xcabae0
0049f9ca 8bcb                     mov       ecx, ebx
0049f9cc e81f375b00               call      0xa530f0
0049f9d1 50                       push      eax
0049f9d2 e814147600               call      0xc00deb
0049f9d7 83c408                   add       esp, 8
0049f9da 85c0                     test      eax, eax
0049f9dc 0f8491000000             je        0x49fa73
0049f9e2 68e0020000               push      0x2e0
0049f9e7 e86442f6ff               call      0x403c50
0049f9ec 83c404                   add       esp, 4
0049f9ef 89450c                   mov       dword ptr [ebp + 0xc], eax
0049f9f2 85c0                     test      eax, eax
0049f9f4 c745fc04000000           mov       dword ptr [ebp - 4], 4
0049f9fb 7426                     je        0x49fa23
0049f9fd 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049fa03 e8e8365b00               call      0xa530f0
0049fa08 6a00                     push      0
0049fa0a 8bcb                     mov       ecx, ebx
0049fa0c 894508                   mov       dword ptr [ebp + 8], eax
0049fa0f e8dc365b00               call      0xa530f0
0049fa14 8b5508                   mov       edx, dword ptr [ebp + 8]
0049fa17 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049fa1a 50                       push      eax
0049fa1b 52                       push      edx
0049fa1c e8df3e0000               call      0x4a3900
0049fa21 eb02                     jmp       0x49fa25
0049fa23 33c0                     xor       eax, eax
0049fa25 56                       push      esi
0049fa26 8bc8                     mov       ecx, eax
0049fa28 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fa2f 898650010000             mov       dword ptr [esi + 0x150], eax
0049fa35 e8e6d55800               call      0xa2d020
0049fa3a 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0049fa40 8bcb                     mov       ecx, ebx
0049fa42 c780cc0200000b000000     mov       dword ptr [eax + 0x2cc], 0xb
0049fa4c c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
0049fa56 e895365b00               call      0xa530f0
0049fa5b 8bd8                     mov       ebx, eax
0049fa5d 53                       push      ebx
0049fa5e e86a037600               call      0xbffdcd
0049fa63 83c404                   add       esp, 4
0049fa66 50                       push      eax
0049fa67 53                       push      ebx
0049fa68 8d8ef4070000             lea       ecx, [esi + 0x7f4]
0049fa6e e80d34f6ff               call      0x402e80
0049fa73 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
0049fa79 85c9                     test      ecx, ecx
0049fa7b 741a                     je        0x49fa97
0049fa7d 6a01                     push      1
0049fa7f 6a02                     push      2
0049fa81 6a00                     push      0
0049fa83 e808625800               call      0xa25c90
0049fa88 50                       push      eax
0049fa89 e852485800               call      0xa242e0
0049fa8e 83c40c                   add       esp, 0xc
0049fa91 898688010000             mov       dword ptr [esi + 0x188], eax
0049fa97 8b8e4c010000             mov       ecx, dword ptr [esi + 0x14c]
0049fa9d 85c9                     test      ecx, ecx
0049fa9f 740b                     je        0x49faac
0049faa1 e8cad45800               call      0xa2cf70
0049faa6 898688010000             mov       dword ptr [esi + 0x188], eax
0049faac 8d5f70                   lea       ebx, [edi + 0x70]
0049faaf 68e0baca00               push      0xcabae0
0049fab4 8bcb                     mov       ecx, ebx
0049fab6 e835365b00               call      0xa530f0
0049fabb 50                       push      eax
0049fabc e82a137600               call      0xc00deb
0049fac1 83c408                   add       esp, 8
0049fac4 85c0                     test      eax, eax
0049fac6 7468                     je        0x49fb30
0049fac8 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049face e8                       .byte     0xe8
0049facf 1d                       .byte     0x1d
