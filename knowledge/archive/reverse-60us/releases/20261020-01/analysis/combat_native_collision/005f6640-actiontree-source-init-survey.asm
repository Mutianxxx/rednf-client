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
005f67ea cc                       int3      
005f67eb cc                       int3      
005f67ec cc                       int3      
005f67ed cc                       int3      
005f67ee cc                       int3      
005f67ef cc                       int3      
005f67f0 55                       push      ebp
005f67f1 8bec                     mov       ebp, esp
005f67f3 83ec0c                   sub       esp, 0xc
005f67f6 53                       push      ebx
005f67f7 56                       push      esi
005f67f8 8bf1                     mov       esi, ecx
005f67fa 8b8ed4080000             mov       ecx, dword ptr [esi + 0x8d4]
005f6800 85c9                     test      ecx, ecx
005f6802 8d9ed0080000             lea       ebx, [esi + 0x8d0]
005f6808 57                       push      edi
005f6809 0f847f000000             je        0x5f688e
005f680f 8b4308                   mov       eax, dword ptr [ebx + 8]
005f6812 2bc1                     sub       eax, ecx
005f6814 c1f802                   sar       eax, 2
005f6817 85c0                     test      eax, eax
005f6819 7673                     jbe       0x5f688e
005f681b 33ff                     xor       edi, edi
005f681d 8d4900                   lea       ecx, [ecx]
005f6820 8b4b04                   mov       ecx, dword ptr [ebx + 4]
005f6823 85c9                     test      ecx, ecx
005f6825 7467                     je        0x5f688e
005f6827 8b4308                   mov       eax, dword ptr [ebx + 8]
005f682a 2bc1                     sub       eax, ecx
005f682c c1f802                   sar       eax, 2
005f682f 3bf8                     cmp       edi, eax
005f6831 735b                     jae       0x5f688e
005f6833 8b86d4080000             mov       eax, dword ptr [esi + 0x8d4]
005f6839 8b04b8                   mov       eax, dword ptr [eax + edi*4]
005f683c 3bc6                     cmp       eax, esi
005f683e 740f                     je        0x5f684f
005f6840 8b16                     mov       edx, dword ptr [esi]
005f6842 50                       push      eax
005f6843 8bce                     mov       ecx, esi
005f6845 ff9248020000             call      dword ptr [edx + 0x248]
005f684b 84c0                     test      al, al
005f684d 7528                     jne       0x5f6877
005f684f 8b8ed4080000             mov       ecx, dword ptr [esi + 0x8d4]
005f6855 8b14b9                   mov       edx, dword ptr [ecx + edi*4]
005f6858 8b06                     mov       eax, dword ptr [esi]
005f685a 52                       push      edx
005f685b 8bce                     mov       ecx, esi
005f685d ff9074030000             call      dword ptr [eax + 0x374]
005f6863 8b86d4080000             mov       eax, dword ptr [esi + 0x8d4]
005f6869 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
005f686c 51                       push      ecx
005f686d 8bce                     mov       ecx, esi
005f686f e8acf3ffff               call      0x5f5c20
005f6874 47                       inc       edi
005f6875 eba9                     jmp       0x5f6820
005f6877 8b86d4080000             mov       eax, dword ptr [esi + 0x8d4]
005f687d 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
005f6880 8b16                     mov       edx, dword ptr [esi]
005f6882 51                       push      ecx
005f6883 8bce                     mov       ecx, esi
005f6885 ff9270030000             call      dword ptr [edx + 0x370]
005f688b 47                       inc       edi
005f688c eb92                     jmp       0x5f6820
005f688e 8b8600010000             mov       eax, dword ptr [esi + 0x100]
005f6894 8b8890000000             mov       ecx, dword ptr [eax + 0x90]
005f689a 058c000000               add       eax, 0x8c
005f689f 85c9                     test      ecx, ecx
005f68a1 7505                     jne       0x5f68a8
005f68a3 894df8                   mov       dword ptr [ebp - 8], ecx
005f68a6 eb0b                     jmp       0x5f68b3
005f68a8 8b4008                   mov       eax, dword ptr [eax + 8]
005f68ab 2bc1                     sub       eax, ecx
005f68ad c1f802                   sar       eax, 2
005f68b0 8945f8                   mov       dword ptr [ebp - 8], eax
005f68b3 8b45f8                   mov       eax, dword ptr [ebp - 8]
005f68b6 33ff                     xor       edi, edi
005f68b8 85c0                     test      eax, eax
005f68ba 897dfc                   mov       dword ptr [ebp - 4], edi
005f68bd 0f8ec2000000             jle       0x5f6985
005f68c3 eb0b                     jmp       0x5f68d0
005f68c5 8b7dfc                   mov       edi, dword ptr [ebp - 4]
005f68c8 eb06                     jmp       0x5f68d0
005f68ca 8d9b00000000             lea       ebx, [ebx]
005f68d0 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f68d6 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
005f68dc 85d2                     test      edx, edx
005f68de 7414                     je        0x5f68f4
005f68e0 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
005f68e6 2bc2                     sub       eax, edx
005f68e8 c1f802                   sar       eax, 2
005f68eb 3bf8                     cmp       edi, eax
005f68ed 7305                     jae       0x5f68f4
005f68ef 8b3cba                   mov       edi, dword ptr [edx + edi*4]
005f68f2 eb02                     jmp       0x5f68f6
005f68f4 33ff                     xor       edi, edi
005f68f6 8b06                     mov       eax, dword ptr [esi]
005f68f8 57                       push      edi
005f68f9 8bce                     mov       ecx, esi
005f68fb ff909c030000             call      dword ptr [eax + 0x39c]
005f6901 84c0                     test      al, al
005f6903 746e                     je        0x5f6973
005f6905 3bfe                     cmp       edi, esi
005f6907 746a                     je        0x5f6973
005f6909 8b16                     mov       edx, dword ptr [esi]
005f690b 57                       push      edi
005f690c 8bce                     mov       ecx, esi
005f690e ff9248020000             call      dword ptr [edx + 0x248]
005f6914 84c0                     test      al, al
005f6916 745b                     je        0x5f6973
005f6918 57                       push      edi
005f6919 8bce                     mov       ecx, esi
005f691b 897df4                   mov       dword ptr [ebp - 0xc], edi
005f691e e8ededffff               call      0x5f5710
005f6923 84c0                     test      al, al
005f6925 754c                     jne       0x5f6973
005f6927 8b5304                   mov       edx, dword ptr [ebx + 4]
005f692a 85d2                     test      edx, edx
005f692c 7504                     jne       0x5f6932
005f692e 33c9                     xor       ecx, ecx
005f6930 eb08                     jmp       0x5f693a
005f6932 8b4b08                   mov       ecx, dword ptr [ebx + 8]
005f6935 2bca                     sub       ecx, edx
005f6937 c1f902                   sar       ecx, 2
005f693a 85d2                     test      edx, edx
005f693c 7419                     je        0x5f6957
005f693e 8b430c                   mov       eax, dword ptr [ebx + 0xc]
005f6941 2bc2                     sub       eax, edx
005f6943 c1f802                   sar       eax, 2
005f6946 3bc8                     cmp       ecx, eax
005f6948 730d                     jae       0x5f6957
005f694a 8b4308                   mov       eax, dword ptr [ebx + 8]
005f694d 8938                     mov       dword ptr [eax], edi
005f694f 83c004                   add       eax, 4
005f6952 894308                   mov       dword ptr [ebx + 8], eax
005f6955 eb11                     jmp       0x5f6968
005f6957 8b4308                   mov       eax, dword ptr [ebx + 8]
005f695a 8d4df4                   lea       ecx, [ebp - 0xc]
005f695d 51                       push      ecx
005f695e 6a01                     push      1
005f6960 50                       push      eax
005f6961 8bcb                     mov       ecx, ebx
005f6963 e808eef0ff               call      0x505770
005f6968 8b16                     mov       edx, dword ptr [esi]
005f696a 57                       push      edi
005f696b 8bce                     mov       ecx, esi
005f696d ff926c030000             call      dword ptr [edx + 0x36c]
005f6973 8b45fc                   mov       eax, dword ptr [ebp - 4]
005f6976 8b4df8                   mov       ecx, dword ptr [ebp - 8]
005f6979 40                       inc       eax
005f697a 3bc1                     cmp       eax, ecx
005f697c 8945fc                   mov       dword ptr [ebp - 4], eax
005f697f 0f8c40ffffff             jl        0x5f68c5
005f6985 5f                       pop       edi
005f6986 5e                       pop       esi
005f6987 5b                       pop       ebx
005f6988 8be5                     mov       esp, ebp
005f698a 5d                       pop       ebp
005f698b c3                       ret       
005f698c cc                       int3      
005f698d cc                       int3      
005f698e cc                       int3      
005f698f cc                       int3      
005f6990 55                       push      ebp
005f6991 8bec                     mov       ebp, esp
005f6993 6aff                     push      -1
005f6995 680876c600               push      0xc67608
005f699a 64a100000000             mov       eax, dword ptr fs:[0]
005f69a0 50                       push      eax
005f69a1 64892500000000           mov       dword ptr fs:[0], esp
005f69a8 51                       push      ecx
005f69a9 56                       push      esi
005f69aa 68b4010000               push      0x1b4
005f69af 8bf1                     mov       esi, ecx
005f69b1 e89ad2e0ff               call      0x403c50
005f69b6 83c404                   add       esp, 4
005f69b9 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f69bc 85c0                     test      eax, eax
005f69be c745fc00000000           mov       dword ptr [ebp - 4], 0
005f69c5 740f                     je        0x5f69d6
005f69c7 56                       push      esi
005f69c8 68a019d500               push      0xd519a0
005f69cd 8bc8                     mov       ecx, eax
005f69cf e84cc9e5ff               call      0x453320
005f69d4 eb02                     jmp       0x5f69d8
005f69d6 33c0                     xor       eax, eax
005f69d8 89864c090000             mov       dword ptr [esi + 0x94c], eax
005f69de 8b10                     mov       edx, dword ptr [eax]
005f69e0 56                       push      esi
005f69e1 8bc8                     mov       ecx, eax
005f69e3 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f69ea ff5270                   call      dword ptr [edx + 0x70]
005f69ed 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f69f3 8b01                     mov       eax, dword ptr [ecx]
005f69f5 6a00                     push      0
005f69f7 ff500c                   call      dword ptr [eax + 0xc]
005f69fa 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f69fd 5e                       pop       esi
005f69fe 64890d00000000           mov       dword ptr fs:[0], ecx
005f6a05 8be5                     mov       esp, ebp
005f6a07 5d                       pop       ebp
005f6a08 c3                       ret       
005f6a09 cc                       int3      
005f6a0a cc                       int3      
005f6a0b cc                       int3      
005f6a0c cc                       int3      
005f6a0d cc                       int3      
005f6a0e cc                       int3      
005f6a0f cc                       int3      
005f6a10 55                       push      ebp
005f6a11 8bec                     mov       ebp, esp
005f6a13 6aff                     push      -1
005f6a15 684976c600               push      0xc67649
005f6a1a 64a100000000             mov       eax, dword ptr fs:[0]
005f6a20 50                       push      eax
005f6a21 64892500000000           mov       dword ptr fs:[0], esp
005f6a28 51                       push      ecx
005f6a29 56                       push      esi
005f6a2a 8bf1                     mov       esi, ecx
005f6a2c 68b4010000               push      0x1b4
005f6a31 c7865009000005000000     mov       dword ptr [esi + 0x950], 5
005f6a3b e810d2e0ff               call      0x403c50
005f6a40 83c404                   add       esp, 4
005f6a43 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6a46 85c0                     test      eax, eax
005f6a48 c745fc00000000           mov       dword ptr [ebp - 4], 0
005f6a4f 7410                     je        0x5f6a61
005f6a51 6a00                     push      0
005f6a53 68e01bd500               push      0xd51be0
005f6a58 8bc8                     mov       ecx, eax
005f6a5a e8c1c8e5ff               call      0x453320
005f6a5f eb02                     jmp       0x5f6a63
005f6a61 33c0                     xor       eax, eax
005f6a63 57                       push      edi
005f6a64 83cfff                   or        edi, 0xffffffff
005f6a67 68b4010000               push      0x1b4
005f6a6c 897dfc                   mov       dword ptr [ebp - 4], edi
005f6a6f 898658090000             mov       dword ptr [esi + 0x958], eax
005f6a75 e8d6d1e0ff               call      0x403c50
005f6a7a 83c404                   add       esp, 4
005f6a7d 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6a80 85c0                     test      eax, eax
005f6a82 c745fc01000000           mov       dword ptr [ebp - 4], 1
005f6a89 7410                     je        0x5f6a9b
005f6a8b 6a00                     push      0
005f6a8d 68681bd500               push      0xd51b68
005f6a92 8bc8                     mov       ecx, eax
005f6a94 e887c8e5ff               call      0x453320
005f6a99 eb02                     jmp       0x5f6a9d
005f6a9b 33c0                     xor       eax, eax
005f6a9d 68b4010000               push      0x1b4
005f6aa2 897dfc                   mov       dword ptr [ebp - 4], edi
005f6aa5 89865c090000             mov       dword ptr [esi + 0x95c], eax
005f6aab e8a0d1e0ff               call      0x403c50
005f6ab0 83c404                   add       esp, 4
005f6ab3 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6ab6 85c0                     test      eax, eax
005f6ab8 c745fc02000000           mov       dword ptr [ebp - 4], 2
005f6abf 7410                     je        0x5f6ad1
005f6ac1 6a00                     push      0
005f6ac3 68f01ad500               push      0xd51af0
005f6ac8 8bc8                     mov       ecx, eax
005f6aca e851c8e5ff               call      0x453320
005f6acf eb02                     jmp       0x5f6ad3
005f6ad1 33c0                     xor       eax, eax
005f6ad3 68b4010000               push      0x1b4
005f6ad8 897dfc                   mov       dword ptr [ebp - 4], edi
005f6adb 898660090000             mov       dword ptr [esi + 0x960], eax
005f6ae1 e86ad1e0ff               call      0x403c50
005f6ae6 83c404                   add       esp, 4
005f6ae9 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6aec 85c0                     test      eax, eax
005f6aee c745fc03000000           mov       dword ptr [ebp - 4], 3
005f6af5 7410                     je        0x5f6b07
005f6af7 6a00                     push      0
005f6af9 68781ad500               push      0xd51a78
005f6afe 8bc8                     mov       ecx, eax
005f6b00 e81bc8e5ff               call      0x453320
005f6b05 eb02                     jmp       0x5f6b09
005f6b07 33c0                     xor       eax, eax
005f6b09 68b4010000               push      0x1b4
005f6b0e 897dfc                   mov       dword ptr [ebp - 4], edi
005f6b11 898664090000             mov       dword ptr [esi + 0x964], eax
005f6b17 e834d1e0ff               call      0x403c50
005f6b1c 83c404                   add       esp, 4
005f6b1f 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6b22 85c0                     test      eax, eax
005f6b24 c745fc04000000           mov       dword ptr [ebp - 4], 4
005f6b2b 5f                       pop       edi
005f6b2c 7410                     je        0x5f6b3e
005f6b2e 6a00                     push      0
005f6b30 68001ad500               push      0xd51a00
005f6b35 8bc8                     mov       ecx, eax
005f6b37 e8e4c7e5ff               call      0x453320
005f6b3c eb02                     jmp       0x5f6b40
005f6b3e 33c0                     xor       eax, eax
005f6b40 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f6b43 898668090000             mov       dword ptr [esi + 0x968], eax
005f6b49 5e                       pop       esi
005f6b4a 64890d00000000           mov       dword ptr fs:[0], ecx
005f6b51 8be5                     mov       esp, ebp
005f6b53 5d                       pop       ebp
005f6b54 c3                       ret       
005f6b55 cc                       int3      
005f6b56 cc                       int3      
005f6b57 cc                       int3      
005f6b58 cc                       int3      
005f6b59 cc                       int3      
005f6b5a cc                       int3      
005f6b5b cc                       int3      
005f6b5c cc                       int3      
005f6b5d cc                       int3      
005f6b5e cc                       int3      
005f6b5f cc                       int3      
