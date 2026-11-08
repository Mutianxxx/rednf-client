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
004af6c0 83c202                   add       edx, 2
004af6c3 8910                     mov       dword ptr [eax], edx
004af6c5 8b45fc                   mov       eax, dword ptr [ebp - 4]
004af6c8 8be5                     mov       esp, ebp
004af6ca 5d                       pop       ebp
004af6cb c20c00                   ret       0xc
004af6ce 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004af6d1 8b11                     mov       edx, dword ptr [ecx]
004af6d3 56                       push      esi
004af6d4 ff921c030000             call      dword ptr [edx + 0x31c]
004af6da 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004af6dd f7d8                     neg       eax
004af6df 1bc0                     sbb       eax, eax
004af6e1 5f                       pop       edi
004af6e2 83c004                   add       eax, 4
004af6e5 5e                       pop       esi
004af6e6 8901                     mov       dword ptr [ecx], eax
004af6e8 8b45fc                   mov       eax, dword ptr [ebp - 4]
004af6eb 5b                       pop       ebx
004af6ec 8be5                     mov       esp, ebp
004af6ee 5d                       pop       ebp
004af6ef c20c00                   ret       0xc
004af6f2 85ff                     test      edi, edi
004af6f4 0f8480000000             je        0x4af77a
004af6fa 8a8608050000             mov       al, byte ptr [esi + 0x508]
004af700 84c0                     test      al, al
004af702 7420                     je        0x4af724
004af704 6a0e                     push      0xe
004af706 8bce                     mov       ecx, esi
004af708 e863920300               call      0x4e8970
004af70d 84c0                     test      al, al
004af70f 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004af712 7413                     je        0x4af727
004af714 8b17                     mov       edx, dword ptr [edi]
004af716 8bcf                     mov       ecx, edi
004af718 ff92b8010000             call      dword ptr [edx + 0x1b8]
004af71e 84c0                     test      al, al
004af720 7558                     jne       0x4af77a
004af722 eb03                     jmp       0x4af727
004af724 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004af727 8a8608050000             mov       al, byte ptr [esi + 0x508]
004af72d 84c0                     test      al, al
004af72f 741b                     je        0x4af74c
004af731 6a01                     push      1
004af733 8bce                     mov       ecx, esi
004af735 e836920300               call      0x4e8970
004af73a 84c0                     test      al, al
004af73c 740e                     je        0x4af74c
004af73e 8b07                     mov       eax, dword ptr [edi]
004af740 8bcf                     mov       ecx, edi
004af742 ff90b8010000             call      dword ptr [eax + 0x1b8]
004af748 84c0                     test      al, al
004af74a 752e                     jne       0x4af77a
004af74c 8b45f8                   mov       eax, dword ptr [ebp - 8]
004af74f 85c0                     test      eax, eax
004af751 0f841f010000             je        0x4af876
004af757 8b88a41a0000             mov       ecx, dword ptr [eax + 0x1aa4]
004af75d 8a413c                   mov       al, byte ptr [ecx + 0x3c]
004af760 84c0                     test      al, al
004af762 0f840e010000             je        0x4af876
004af768 8b17                     mov       edx, dword ptr [edi]
004af76a 8bcf                     mov       ecx, edi
004af76c ff92b8010000             call      dword ptr [edx + 0x1b8]
004af772 84c0                     test      al, al
004af774 0f84fc000000             je        0x4af876
004af77a 8b06                     mov       eax, dword ptr [esi]
004af77c 6a01                     push      1
004af77e 8bce                     mov       ecx, esi
004af780 ff9010040000             call      dword ptr [eax + 0x410]
004af786 84c0                     test      al, al
004af788 0f859a000000             jne       0x4af828
004af78e 8b16                     mov       edx, dword ptr [esi]
004af790 6a07                     push      7
004af792 8bce                     mov       ecx, esi
004af794 ff9210040000             call      dword ptr [edx + 0x410]
004af79a 84c0                     test      al, al
004af79c 0f8586000000             jne       0x4af828
004af7a2 83fb01                   cmp       ebx, 1
004af7a5 752e                     jne       0x4af7d5
004af7a7 8b06                     mov       eax, dword ptr [esi]
004af7a9 8bce                     mov       ecx, esi
004af7ab ff9004020000             call      dword ptr [eax + 0x204]
004af7b1 85c0                     test      eax, eax
004af7b3 7f0e                     jg        0x4af7c3
004af7b5 8b16                     mov       edx, dword ptr [esi]
004af7b7 8bce                     mov       ecx, esi
004af7b9 ff929c000000             call      dword ptr [edx + 0x9c]
004af7bf 85c0                     test      eax, eax
004af7c1 7f1b                     jg        0x4af7de
004af7c3 8d8e5c150000             lea       ecx, [esi + 0x155c]
004af7c9 e89228f5ff               call      0x402060
004af7ce 83f804                   cmp       eax, 4
004af7d1 752e                     jne       0x4af801
004af7d3 eb09                     jmp       0x4af7de
004af7d5 83fb02                   cmp       ebx, 2
004af7d8 0f8598000000             jne       0x4af876
004af7de 8b06                     mov       eax, dword ptr [esi]
004af7e0 8bce                     mov       ecx, esi
004af7e2 c745fc04000000           mov       dword ptr [ebp - 4], 4
004af7e9 ff9078030000             call      dword ptr [eax + 0x378]
004af7ef 85c0                     test      eax, eax
004af7f1 7548                     jne       0x4af83b
004af7f3 8b16                     mov       edx, dword ptr [esi]
004af7f5 8bce                     mov       ecx, esi
004af7f7 ff92a0030000             call      dword ptr [edx + 0x3a0]
004af7fd 85c0                     test      eax, eax
004af7ff 753a                     jne       0x4af83b
004af801 8b06                     mov       eax, dword ptr [esi]
004af803 6a00                     push      0
004af805 8bce                     mov       ecx, esi
004af807 c745fc03000000           mov       dword ptr [ebp - 4], 3
004af80e ff9074030000             call      dword ptr [eax + 0x374]
004af814 85c0                     test      eax, eax
004af816 755e                     jne       0x4af876
004af818 8b16                     mov       edx, dword ptr [esi]
004af81a 6a01                     push      1
004af81c 8bce                     mov       ecx, esi
004af81e ff9274030000             call      dword ptr [edx + 0x374]
004af824 85c0                     test      eax, eax
004af826 754e                     jne       0x4af876
004af828 5f                       pop       edi
004af829 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004af830 8b45fc                   mov       eax, dword ptr [ebp - 4]
004af833 5e                       pop       esi
004af834 5b                       pop       ebx
004af835 8be5                     mov       esp, ebp
004af837 5d                       pop       ebp
004af838 c20c00                   ret       0xc
004af83b 8d8e5c150000             lea       ecx, [esi + 0x155c]
004af841 e81a28f5ff               call      0x402060
004af846 83f804                   cmp       eax, 4
004af849 752b                     jne       0x4af876
004af84b 8d8e20170000             lea       ecx, [esi + 0x1720]
004af851 e80a28f5ff               call      0x402060
004af856 83f801                   cmp       eax, 1
004af859 7c1b                     jl        0x4af876
004af85b 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004af85e 81c130010000             add       ecx, 0x130
004af864 e8f727f5ff               call      0x402060
004af869 85c0                     test      eax, eax
004af86b 7509                     jne       0x4af876
004af86d 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004af870 c70001000000             mov       dword ptr [eax], 1
004af876 5f                       pop       edi
004af877 8b45fc                   mov       eax, dword ptr [ebp - 4]
004af87a 5e                       pop       esi
004af87b 5b                       pop       ebx
004af87c 8be5                     mov       esp, ebp
004af87e 5d                       pop       ebp
004af87f c20c00                   ret       0xc
004af882 cc                       int3      
004af883 cc                       int3      
004af884 cc                       int3      
004af885 cc                       int3      
004af886 cc                       int3      
004af887 cc                       int3      
004af888 cc                       int3      
004af889 cc                       int3      
004af88a cc                       int3      
004af88b cc                       int3      
004af88c cc                       int3      
004af88d cc                       int3      
004af88e cc                       int3      
004af88f cc                       int3      
004af890 55                       push      ebp
004af891 8bec                     mov       ebp, esp
004af893 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004af896 85c0                     test      eax, eax
004af898 7424                     je        0x4af8be
004af89a 8b514c                   mov       edx, dword ptr [ecx + 0x4c]
004af89d 2bd0                     sub       edx, eax
004af89f 8b4508                   mov       eax, dword ptr [ebp + 8]
004af8a2 c1fa06                   sar       edx, 6
004af8a5 3bc2                     cmp       eax, edx
004af8a7 7315                     jae       0x4af8be
004af8a9 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004af8ac c1e006                   shl       eax, 6
004af8af 8b4c1038                 mov       ecx, dword ptr [eax + edx + 0x38]
004af8b3 03c2                     add       eax, edx
004af8b5 85c9                     test      ecx, ecx
004af8b7 0f97c0                   seta      al
004af8ba 5d                       pop       ebp
004af8bb c20400                   ret       4
004af8be 32c0                     xor       al, al
004af8c0 5d                       pop       ebp
004af8c1 c20400                   ret       4
004af8c4 cc                       int3      
004af8c5 cc                       int3      
004af8c6 cc                       int3      
004af8c7 cc                       int3      
004af8c8 cc                       int3      
004af8c9 cc                       int3      
004af8ca cc                       int3      
004af8cb cc                       int3      
004af8cc cc                       int3      
004af8cd cc                       int3      
004af8ce cc                       int3      
004af8cf cc                       int3      
004af8d0 55                       push      ebp
004af8d1 8bec                     mov       ebp, esp
004af8d3 56                       push      esi
004af8d4 8b7508                   mov       esi, dword ptr [ebp + 8]
004af8d7 85f6                     test      esi, esi
004af8d9 7448                     je        0x4af923
004af8db 8b8698000000             mov       eax, dword ptr [esi + 0x98]
004af8e1 85c0                     test      eax, eax
004af8e3 743e                     je        0x4af923
004af8e5 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
004af8eb 2bc8                     sub       ecx, eax
004af8ed b843082184               mov       eax, 0x84210843
004af8f2 f7e9                     imul      ecx
004af8f4 03d1                     add       edx, ecx
004af8f6 c1fa06                   sar       edx, 6
004af8f9 8bc2                     mov       eax, edx
004af8fb c1e81f                   shr       eax, 0x1f
004af8fe 03c2                     add       eax, edx
004af900 83f801                   cmp       eax, 1
004af903 751e                     jne       0x4af923
004af905 8bb698000000             mov       esi, dword ptr [esi + 0x98]
004af90b 8b4e08                   mov       ecx, dword ptr [esi + 8]
004af90e b8ffff0000               mov       eax, 0xffff
004af913 3bc8                     cmp       ecx, eax
004af915 750c                     jne       0x4af923
004af917 39460c                   cmp       dword ptr [esi + 0xc], eax
004af91a 7507                     jne       0x4af923
004af91c b001                     mov       al, 1
004af91e 5e                       pop       esi
004af91f 5d                       pop       ebp
004af920 c20400                   ret       4
004af923 32c0                     xor       al, al
004af925 5e                       pop       esi
004af926 5d                       pop       ebp
004af927 c20400                   ret       4
004af92a cc                       int3      
004af92b cc                       int3      
004af92c cc                       int3      
004af92d cc                       int3      
004af92e cc                       int3      
004af92f cc                       int3      
004af930 55                       push      ebp
004af931 8bec                     mov       ebp, esp
004af933 51                       push      ecx
004af934 53                       push      ebx
004af935 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
004af938 56                       push      esi
004af939 8bf1                     mov       esi, ecx
004af93b 57                       push      edi
004af93c 8dbeec140000             lea       edi, [esi + 0x14ec]
004af942 c745fc17000000           mov       dword ptr [ebp - 4], 0x17
004af949 8da42400000000           lea       esp, [esp]
004af950 8b07                     mov       eax, dword ptr [edi]
004af952 85c0                     test      eax, eax
004af954 7434                     je        0x4af98a
004af956 8d9660020000             lea       edx, [esi + 0x260]
004af95c 52                       push      edx
004af95d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004af960 6a01                     push      1
004af962 53                       push      ebx
004af963 52                       push      edx
004af964 8b5508                   mov       edx, dword ptr [ebp + 8]
004af967 8bc8                     mov       ecx, eax
004af969 8b01                     mov       eax, dword ptr [ecx]
004af96b 52                       push      edx
004af96c ff90b8000000             call      dword ptr [eax + 0xb8]
004af972 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004af975 8b0f                     mov       ecx, dword ptr [edi]
004af977 8b01                     mov       eax, dword ptr [ecx]
004af979 6a00                     push      0
004af97b 52                       push      edx
004af97c 8b5508                   mov       edx, dword ptr [ebp + 8]
004af97f 56                       push      esi
004af980 53                       push      ebx
004af981 52                       push      edx
004af982 6a00                     push      0
004af984 ff9098010000             call      dword ptr [eax + 0x198]
004af98a 8b45fc                   mov       eax, dword ptr [ebp - 4]
004af98d 83c704                   add       edi, 4
004af990 48                       dec       eax
004af991 8945fc                   mov       dword ptr [ebp - 4], eax
004af994 75ba                     jne       0x4af950
004af996 c7451000000000           mov       dword ptr [ebp + 0x10], 0
004af99d 8dbe94120000             lea       edi, [esi + 0x1294]
004af9a3 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004af9a6 8b06                     mov       eax, dword ptr [esi]
004af9a8 51                       push      ecx
004af9a9 8bce                     mov       ecx, esi
004af9ab ff9010040000             call      dword ptr [eax + 0x410]
004af9b1 84c0                     test      al, al
004af9b3 7410                     je        0x4af9c5
004af9b5 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004af9b8 8b0f                     mov       ecx, dword ptr [edi]
004af9ba 8b11                     mov       edx, dword ptr [ecx]
004af9bc 53                       push      ebx
004af9bd 50                       push      eax
004af9be 8b4508                   mov       eax, dword ptr [ebp + 8]
004af9c1 50                       push      eax
004af9c2 ff5244                   call      dword ptr [edx + 0x44]
004af9c5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004af9c8 40                       inc       eax
004af9c9 83c704                   add       edi, 4
004af9cc 83f812                   cmp       eax, 0x12
004af9cf 894510                   mov       dword ptr [ebp + 0x10], eax
004af9d2 7ccf                     jl        0x4af9a3
004af9d4 8bce                     mov       ecx, esi
004af9d6 e865faffff               call      0x4af440
004af9db 84db                     test      bl, bl
004af9dd 740e                     je        0x4af9ed
004af9df 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004af9e2 8b16                     mov       edx, dword ptr [esi]
004af9e4 50                       push      eax
004af9e5 8bce                     mov       ecx, esi
004af9e7 ff9280020000             call      dword ptr [edx + 0x280]
004af9ed 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004af9f0 8b5508                   mov       edx, dword ptr [ebp + 8]
004af9f3 53                       push      ebx
004af9f4 51                       push      ecx
004af9f5 52                       push      edx
004af9f6 8bce                     mov       ecx, esi
004af9f8 e893920300               call      0x4e8c90
004af9fd 5f                       pop       edi
004af9fe 5e                       pop       esi
004af9ff 5b                       pop       ebx
004afa00 8be5                     mov       esp, ebp
004afa02 5d                       pop       ebp
004afa03 c20c00                   ret       0xc
004afa06 cc                       int3      
004afa07 cc                       int3      
004afa08 cc                       int3      
004afa09 cc                       int3      
004afa0a cc                       int3      
004afa0b cc                       int3      
004afa0c cc                       int3      
004afa0d cc                       int3      
004afa0e cc                       int3      
004afa0f cc                       int3      
004afa10 55                       push      ebp
004afa11 8bec                     mov       ebp, esp
004afa13 8b4508                   mov       eax, dword ptr [ebp + 8]
004afa16 53                       push      ebx
004afa17 56                       push      esi
004afa18 57                       push      edi
004afa19 50                       push      eax
004afa1a 8bf9                     mov       edi, ecx
004afa1c e8afe20300               call      0x4edcd0
004afa21 8db7ec140000             lea       esi, [edi + 0x14ec]
004afa27 bb17000000               mov       ebx, 0x17
004afa2c 8d642400                 lea       esp, [esp]
004afa30 8b06                     mov       eax, dword ptr [esi]
004afa32 85c0                     test      eax, eax
004afa34 7411                     je        0x4afa47
004afa36 8bc8                     mov       ecx, eax
004afa38 8b11                     mov       edx, dword ptr [ecx]
004afa3a 8d8760020000             lea       eax, [edi + 0x260]
004afa40 50                       push      eax
004afa41 ff92ac000000             call      dword ptr [edx + 0xac]
004afa47 83c604                   add       esi, 4
004afa4a 4b                       dec       ebx
004afa4b 75e3                     jne       0x4afa30
004afa4d 8b8fdc120000             mov       ecx, dword ptr [edi + 0x12dc]
004afa53 85c9                     test      ecx, ecx
004afa55 740c                     je        0x4afa63
004afa57 81c760020000             add       edi, 0x260
004afa5d 57                       push      edi
004afa5e e84d700000               call      0x4b6ab0
004afa63 5f                       pop       edi
004afa64 5e                       pop       esi
004afa65 5b                       pop       ebx
004afa66 5d                       pop       ebp
004afa67 c20400                   ret       4
004afa6a cc                       int3      
004afa6b cc                       int3      
004afa6c cc                       int3      
004afa6d cc                       int3      
004afa6e cc                       int3      
004afa6f cc                       int3      
004afa70 55                       push      ebp
004afa71 8bec                     mov       ebp, esp
004afa73 8b4508                   mov       eax, dword ptr [ebp + 8]
004afa76 85c0                     test      eax, eax
004afa78 53                       push      ebx
004afa79 56                       push      esi
004afa7a 57                       push      edi
004afa7b 8bf1                     mov       esi, ecx
004afa7d 0f857f000000             jne       0x4afb02
004afa83 8b06                     mov       eax, dword ptr [esi]
004afa85 8d9e70080000             lea       ebx, [esi + 0x870]
004afa8b 53                       push      ebx
004afa8c ff9050030000             call      dword ptr [eax + 0x350]
004afa92 8dbeec140000             lea       edi, [esi + 0x14ec]
004afa98 c7450817000000           mov       dword ptr [ebp + 8], 0x17
004afa9f 90                       nop       
004afaa0 8b07                     mov       eax, dword ptr [edi]
004afaa2 85c0                     test      eax, eax
004afaa4 740b                     je        0x4afab1
004afaa6 8bc8                     mov       ecx, eax
004afaa8 8b11                     mov       edx, dword ptr [ecx]
004afaaa 53                       push      ebx
004afaab ff92b0000000             call      dword ptr [edx + 0xb0]
004afab1 8b4508                   mov       eax, dword ptr [ebp + 8]
004afab4 83c704                   add       edi, 4
004afab7 48                       dec       eax
004afab8 894508                   mov       dword ptr [ebp + 8], eax
004afabb 75e3                     jne       0x4afaa0
004afabd 33ff                     xor       edi, edi
004afabf 90                       nop       
004afac0 8b8e24020000             mov       ecx, dword ptr [esi + 0x224]
004afac6 85c9                     test      ecx, ecx
004afac8 7425                     je        0x4afaef
004afaca 8b8628020000             mov       eax, dword ptr [esi + 0x228]
004afad0 2bc1                     sub       eax, ecx
004afad2 c1f802                   sar       eax, 2
004afad5 3bf8                     cmp       edi, eax
004afad7 7316                     jae       0x4afaef
004afad9 8b16                     mov       edx, dword ptr [esi]
004afadb 8bc1                     mov       eax, ecx
004afadd 8d04b8                   lea       eax, [eax + edi*4]
004afae0 8b00                     mov       eax, dword ptr [eax]
004afae2 53                       push      ebx
004afae3 50                       push      eax
004afae4 8bce                     mov       ecx, esi
004afae6 ff9250040000             call      dword ptr [edx + 0x450]
004afaec 47                       inc       edi
004afaed ebd1                     jmp       0x4afac0
004afaef 8b16                     mov       edx, dword ptr [esi]
004afaf1 6a01                     push      1
004afaf3 8bce                     mov       ecx, esi
004afaf5 ff9248030000             call      dword ptr [edx + 0x348]
004afafb 5f                       pop       edi
004afafc 5e                       pop       esi
004afafd 5b                       pop       ebx
004afafe 5d                       pop       ebp
004afaff c20400                   ret       4
004afb02 83f801                   cmp       eax, 1
004afb05 7559                     jne       0x4afb60
004afb07 8d8670080000             lea       eax, [esi + 0x870]
004afb0d 8d9eb00b0000             lea       ebx, [esi + 0xbb0]
004afb13 50                       push      eax
004afb14 8bcb                     mov       ecx, ebx
004afb16 e865600000               call      0x4b5b80
004afb1b 8dbe94120000             lea       edi, [esi + 0x1294]
004afb21 c7450812000000           mov       dword ptr [ebp + 8], 0x12
004afb28 8b07                     mov       eax, dword ptr [edi]
004afb2a 85c0                     test      eax, eax
004afb2c 7413                     je        0x4afb41
004afb2e 8bc8                     mov       ecx, eax
004afb30 8b11                     mov       edx, dword ptr [ecx]
004afb32 ff5208                   call      dword ptr [edx + 8]
004afb35 84c0                     test      al, al
004afb37 7408                     je        0x4afb41
004afb39 8b0f                     mov       ecx, dword ptr [edi]
004afb3b 8b01                     mov       eax, dword ptr [ecx]
004afb3d 53                       push      ebx
004afb3e ff5034                   call      dword ptr [eax + 0x34]
004afb41 8b4508                   mov       eax, dword ptr [ebp + 8]
004afb44 83c704                   add       edi, 4
004afb47 48                       dec       eax
004afb48 894508                   mov       dword ptr [ebp + 8], eax
004afb4b 75db                     jne       0x4afb28
004afb4d 8b16                     mov       edx, dword ptr [esi]
004afb4f 6a02                     push      2
004afb51 8bce                     mov       ecx, esi
004afb53 ff9248030000             call      dword ptr [edx + 0x348]
004afb59 5f                       pop       edi
004afb5a 5e                       pop       esi
004afb5b 5b                       pop       ebx
004afb5c 5d                       pop       ebp
004afb5d c20400                   ret       4
004afb60 83f802                   cmp       eax, 2
004afb63 0f85d0000000             jne       0x4afc39
004afb69 8d86b00b0000             lea       eax, [esi + 0xbb0]
004afb6f 8dbef00e0000             lea       edi, [esi + 0xef0]
004afb75 50                       push      eax
004afb76 8bcf                     mov       ecx, edi
004afb78 e803600000               call      0x4b5b80
004afb7d 8b8edc120000             mov       ecx, dword ptr [esi + 0x12dc]
004afb83 85c9                     test      ecx, ecx
004afb85 7406                     je        0x4afb8d
004afb87 57                       push      edi
004afb88 e8a36f0000               call      0x4b6b30
004afb8d 8b                       .byte     0x8b
004afb8e 0d                       .byte     0x0d
004afb8f 48                       dec       eax
