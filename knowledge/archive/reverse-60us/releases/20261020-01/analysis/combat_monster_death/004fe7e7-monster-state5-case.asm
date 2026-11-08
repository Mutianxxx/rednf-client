004fe7e7 8b8610250000             mov       eax, dword ptr [esi + 0x2510]
004fe7ed 85c0                     test      eax, eax
004fe7ef 7408                     je        0x4fe7f9
004fe7f1 50                       push      eax
004fe7f2 8bce                     mov       ecx, esi
004fe7f4 e8c774ffff               call      0x4f5cc0
004fe7f9 8b8e18240000             mov       ecx, dword ptr [esi + 0x2418]
004fe7ff 85c9                     test      ecx, ecx
004fe801 746e                     je        0x4fe871
004fe803 8b861c240000             mov       eax, dword ptr [esi + 0x241c]
004fe809 2bc1                     sub       eax, ecx
004fe80b c1f802                   sar       eax, 2
004fe80e 85c0                     test      eax, eax
004fe810 745f                     je        0x4fe871
004fe812 8b16                     mov       edx, dword ptr [esi]
004fe814 8bc1                     mov       eax, ecx
004fe816 8b00                     mov       eax, dword ptr [eax]
004fe818 50                       push      eax
004fe819 8bce                     mov       ecx, esi
004fe81b ff92fc000000             call      dword ptr [edx + 0xfc]
004fe821 8b8618240000             mov       eax, dword ptr [esi + 0x2418]
004fe827 8b4004                   mov       eax, dword ptr [eax + 4]
004fe82a 8b16                     mov       edx, dword ptr [esi]
004fe82c 50                       push      eax
004fe82d 8bce                     mov       ecx, esi
004fe82f ff92fc000000             call      dword ptr [edx + 0xfc]
004fe835 8b8618240000             mov       eax, dword ptr [esi + 0x2418]
004fe83b 8b4008                   mov       eax, dword ptr [eax + 8]
004fe83e 8b16                     mov       edx, dword ptr [esi]
004fe840 50                       push      eax
004fe841 8bce                     mov       ecx, esi
004fe843 ff92fc000000             call      dword ptr [edx + 0xfc]
004fe849 8b8618240000             mov       eax, dword ptr [esi + 0x2418]
004fe84f 8b400c                   mov       eax, dword ptr [eax + 0xc]
004fe852 8b16                     mov       edx, dword ptr [esi]
004fe854 50                       push      eax
004fe855 8bce                     mov       ecx, esi
004fe857 ff92fc000000             call      dword ptr [edx + 0xfc]
004fe85d 8b8618240000             mov       eax, dword ptr [esi + 0x2418]
004fe863 8b4010                   mov       eax, dword ptr [eax + 0x10]
004fe866 8b16                     mov       edx, dword ptr [esi]
004fe868 50                       push      eax
004fe869 8bce                     mov       ecx, esi
004fe86b ff92fc000000             call      dword ptr [edx + 0xfc]
004fe871 8b8ea0220000             mov       ecx, dword ptr [esi + 0x22a0]
004fe877 85c9                     test      ecx, ecx
004fe879 7470                     je        0x4fe8eb
004fe87b 8b86a4220000             mov       eax, dword ptr [esi + 0x22a4]
004fe881 2bc1                     sub       eax, ecx
004fe883 c1f804                   sar       eax, 4
004fe886 85c0                     test      eax, eax
004fe888 7461                     je        0x4fe8eb
004fe88a c745f000000000           mov       dword ptr [ebp - 0x10], 0
004fe891 8b8ea0220000             mov       ecx, dword ptr [esi + 0x22a0]
004fe897 85c9                     test      ecx, ecx
004fe899 744d                     je        0x4fe8e8
004fe89b 8b86a4220000             mov       eax, dword ptr [esi + 0x22a4]
004fe8a1 2bc1                     sub       eax, ecx
004fe8a3 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004fe8a6 c1f804                   sar       eax, 4
004fe8a9 3bc8                     cmp       ecx, eax
004fe8ab 733b                     jae       0x4fe8e8
004fe8ad 8bd9                     mov       ebx, ecx
004fe8af 33ff                     xor       edi, edi
004fe8b1 c1e304                   shl       ebx, 4
004fe8b4 8b8ea0220000             mov       ecx, dword ptr [esi + 0x22a0]
004fe8ba 8b541904                 mov       edx, dword ptr [ecx + ebx + 4]
004fe8be 03cb                     add       ecx, ebx
004fe8c0 85d2                     test      edx, edx
004fe8c2 741f                     je        0x4fe8e3
004fe8c4 8b4108                   mov       eax, dword ptr [ecx + 8]
004fe8c7 2bc2                     sub       eax, edx
004fe8c9 c1f802                   sar       eax, 2
004fe8cc 3bf8                     cmp       edi, eax
004fe8ce 7313                     jae       0x4fe8e3
004fe8d0 8d04ba                   lea       eax, [edx + edi*4]
004fe8d3 8b00                     mov       eax, dword ptr [eax]
004fe8d5 8b16                     mov       edx, dword ptr [esi]
004fe8d7 50                       push      eax
004fe8d8 8bce                     mov       ecx, esi
004fe8da ff92fc000000             call      dword ptr [edx + 0xfc]
004fe8e0 47                       inc       edi
004fe8e1 ebd1                     jmp       0x4fe8b4
004fe8e3 ff45f0                   inc       dword ptr [ebp - 0x10]
004fe8e6 eba9                     jmp       0x4fe891
004fe8e8 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004fe8eb 6a00                     push      0
004fe8ed e8fef73a00               call      0x8ae0f0
004fe8f2 99                       cdq       
004fe8f3 b964000000               mov       ecx, 0x64
004fe8f8 f7f9                     idiv      ecx
004fe8fa 83c404                   add       esp, 4
004fe8fd 83fa0f                   cmp       edx, 0xf
004fe900 7d0e                     jge       0x4fe910
004fe902 8b16                     mov       edx, dword ptr [esi]
004fe904 6aff                     push      -1
004fe906 6a16                     push      0x16
004fe908 8bce                     mov       ecx, esi
004fe90a ff9244050000             call      dword ptr [edx + 0x544]
004fe910 8b4704                   mov       eax, dword ptr [edi + 4]
004fe913 8b38                     mov       edi, dword ptr [eax]
004fe915 a148280001               mov       eax, dword ptr [0x1002848]
004fe91a 8b80a8190000             mov       eax, dword ptr [eax + 0x19a8]
004fe920 83f802                   cmp       eax, 2
004fe923 897dec                   mov       dword ptr [ebp - 0x14], edi
004fe926 750c                     jne       0x4fe934
004fe928 c786181e000064000000     mov       dword ptr [esi + 0x1e18], 0x64
004fe932 eb4a                     jmp       0x4fe97e
004fe934 8b16                     mov       edx, dword ptr [esi]
004fe936 8bce                     mov       ecx, esi
004fe938 ff9238020000             call      dword ptr [edx + 0x238]
004fe93e 8bd8                     mov       ebx, eax
004fe940 8b06                     mov       eax, dword ptr [esi]
004fe942 8bce                     mov       ecx, esi
004fe944 ff5040                   call      dword ptr [eax + 0x40]
004fe947 0fafd8                   imul      ebx, eax
004fe94a 8d4de4                   lea       ecx, [ebp - 0x1c]
004fe94d 51                       push      ecx
004fe94e 895de4                   mov       dword ptr [ebp - 0x1c], ebx
004fe951 e89af73a00               call      0x8ae0f0
004fe956 99                       cdq       
004fe957 b965000000               mov       ecx, 0x65
004fe95c f7f9                     idiv      ecx
004fe95e 6a64                     push      0x64
004fe960 52                       push      edx
004fe961 6800007a43               push      0x437a0000
004fe966 680000c842               push      0x42c80000
004fe96b e840b06000               call      0xb099b0
004fe970 83c414                   add       esp, 0x14
004fe973 e8cc2b7000               call      0xc01544
004fe978 8986181e0000             mov       dword ptr [esi + 0x1e18], eax
004fe97e 85ff                     test      edi, edi
004fe980 750f                     jne       0x4fe991
004fe982 8b16                     mov       edx, dword ptr [esi]
004fe984 8bce                     mov       ecx, esi
004fe986 ff9254060000             call      dword ptr [edx + 0x654]
004fe98c e9fd010000               jmp       0x4feb8e
004fe991 a148280001               mov       eax, dword ptr [0x1002848]
004fe996 83b8a819000002           cmp       dword ptr [eax + 0x19a8], 2
004fe99d 0f85a1000000             jne       0x4fea44
004fe9a3 8b86a01b0000             mov       eax, dword ptr [esi + 0x1ba0]
004fe9a9 85c0                     test      eax, eax
004fe9ab 0f8f93000000             jg        0x4fea44
004fe9b1 6a00                     push      0
004fe9b3 6a00                     push      0
004fe9b5 8d8eb8240000             lea       ecx, [esi + 0x24b8]
004fe9bb e8a0856000               call      0xb06f60
004fe9c0 8b86a01b0000             mov       eax, dword ptr [esi + 0x1ba0]
004fe9c6 85c0                     test      eax, eax
004fe9c8 0f8549010000             jne       0x4feb17
004fe9ce 8b86841b0000             mov       eax, dword ptr [esi + 0x1b84]
004fe9d4 85c0                     test      eax, eax
004fe9d6 7507                     jne       0x4fe9df
004fe9d8 bb04000000               mov       ebx, 4
004fe9dd eb0d                     jmp       0x4fe9ec
004fe9df 8b16                     mov       edx, dword ptr [esi]
004fe9e1 50                       push      eax
004fe9e2 8bce                     mov       ecx, esi
004fe9e4 ff921c030000             call      dword ptr [edx + 0x31c]
004fe9ea 8bd8                     mov       ebx, eax
004fe9ec 6828020000               push      0x228
004fe9f1 e85a52f0ff               call      0x403c50
004fe9f6 8bf8                     mov       edi, eax
004fe9f8 83c404                   add       esp, 4
004fe9fb 897de0                   mov       dword ptr [ebp - 0x20], edi
004fe9fe 85ff                     test      edi, edi
004fea00 c745fc02000000           mov       dword ptr [ebp - 4], 2
004fea07 0f84b1000000             je        0x4feabe
004fea0d 8b86181e0000             mov       eax, dword ptr [esi + 0x1e18]
004fea13 8b8ea41b0000             mov       ecx, dword ptr [esi + 0x1ba4]
004fea19 8b16                     mov       edx, dword ptr [esi]
004fea1b 53                       push      ebx
004fea1c 6a04                     push      4
004fea1e 50                       push      eax
004fea1f 51                       push      ecx
004fea20 6a03                     push      3
004fea22 8bce                     mov       ecx, esi
004fea24 ff9244030000             call      dword ptr [edx + 0x344]
004fea2a 8bc8                     mov       ecx, eax
004fea2c e88ff3fbff               call      0x4bddc0
004fea31 50                       push      eax
004fea32 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
004fea35 50                       push      eax
004fea36 8bcf                     mov       ecx, edi
004fea38 e853b00000               call      0x509a90
004fea3d 8bf8                     mov       edi, eax
004fea3f e97c000000               jmp       0x4feac0
004fea44 8b9ea81b0000             mov       ebx, dword ptr [esi + 0x1ba8]
004fea4a 6828020000               push      0x228
004fea4f f7d3                     not       ebx
004fea51 e8fa51f0ff               call      0x403c50
004fea56 83c404                   add       esp, 4
004fea59 8945e0                   mov       dword ptr [ebp - 0x20], eax
004fea5c 85c0                     test      eax, eax
004fea5e c745fc01000000           mov       dword ptr [ebp - 4], 1
004fea65 7457                     je        0x4feabe
004fea67 8b16                     mov       edx, dword ptr [esi]
004fea69 6a03                     push      3
004fea6b 8bce                     mov       ecx, esi
004fea6d ff9244030000             call      dword ptr [edx + 0x344]
004fea73 8bf8                     mov       edi, eax
004fea75 8d8f48020000             lea       ecx, [edi + 0x248]
004fea7b e8e035f0ff               call      0x402060
004fea80 8945f0                   mov       dword ptr [ebp - 0x10], eax
004fea83 db45f0                   fild      dword ptr [ebp - 0x10]
004fea86 8d8f50020000             lea       ecx, [edi + 0x250]
004fea8c d95df0                   fstp      dword ptr [ebp - 0x10]
004fea8f e81c49f3ff               call      0x4333b0
004fea94 d84df0                   fmul      dword ptr [ebp - 0x10]
004fea97 e8a82a7000               call      0xc01544
004fea9c 8b8e181e0000             mov       ecx, dword ptr [esi + 0x1e18]
004feaa2 8b96a41b0000             mov       edx, dword ptr [esi + 0x1ba4]
004feaa8 6a04                     push      4
004feaaa 53                       push      ebx
004feaab 51                       push      ecx
004feaac 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004feaaf 52                       push      edx
004feab0 50                       push      eax
004feab1 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
004feab4 50                       push      eax
004feab5 e8d6af0000               call      0x509a90
004feaba 8bf8                     mov       edi, eax
004feabc eb02                     jmp       0x4feac0
004feabe 33ff                     xor       edi, edi
004feac0 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004feac6 6a00                     push      0
004feac8 6a00                     push      0
004feaca 56                       push      esi
004feacb 57                       push      edi
004feacc 6a00                     push      0
004feace 6a02                     push      2
004fead0 56                       push      esi
004fead1 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004fead8 e893f20000               call      0x50dd70
004feadd 8b16                     mov       edx, dword ptr [esi]
004feadf 8b1f                     mov       ebx, dword ptr [edi]
004feae1 8bce                     mov       ecx, esi
004feae3 ff929c000000             call      dword ptr [edx + 0x9c]
004feae9 8bc8                     mov       ecx, eax
004feaeb 8b8688010000             mov       eax, dword ptr [esi + 0x188]
004feaf1 99                       cdq       
004feaf2 2bc2                     sub       eax, edx
004feaf4 8b16                     mov       edx, dword ptr [esi]
004feaf6 d1f8                     sar       eax, 1
004feaf8 03c8                     add       ecx, eax
004feafa 51                       push      ecx
004feafb 8bce                     mov       ecx, esi
004feafd ff9298000000             call      dword ptr [edx + 0x98]
004feb03 50                       push      eax
004feb04 8b06                     mov       eax, dword ptr [esi]
004feb06 8bce                     mov       ecx, esi
004feb08 ff9094000000             call      dword ptr [eax + 0x94]
004feb0e 8bcf                     mov       ecx, edi
004feb10 50                       push      eax
004feb11 ff9388000000             call      dword ptr [ebx + 0x88]
004feb17 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004feb1d 8b81a8190000             mov       eax, dword ptr [ecx + 0x19a8]
004feb23 bb02000000               mov       ebx, 2
004feb28 3bc3                     cmp       eax, ebx
004feb2a 741e                     je        0x4feb4a
004feb2c 8b16                     mov       edx, dword ptr [esi]
004feb2e 8bce                     mov       ecx, esi
004feb30 ff92a0050000             call      dword ptr [edx + 0x5a0]
004feb36 84c0                     test      al, al
004feb38 7510                     jne       0x4feb4a
004feb3a 8b06                     mov       eax, dword ptr [esi]
004feb3c 6aff                     push      -1
004feb3e 6a05                     push      5
004feb40 6a01                     push      1
004feb42 8bce                     mov       ecx, esi
004feb44 ff9034010000             call      dword ptr [eax + 0x134]
004feb4a 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004feb50 8bb9a8190000             mov       edi, dword ptr [ecx + 0x19a8]
004feb56 8b16                     mov       edx, dword ptr [esi]
004feb58 8bce                     mov       ecx, esi
004feb5a ff92a0050000             call      dword ptr [edx + 0x5a0]
004feb60 84c0                     test      al, al
004feb62 752a                     jne       0x4feb8e
004feb64 a148280001               mov       eax, dword ptr [0x1002848]
004feb69 3998a8190000             cmp       dword ptr [eax + 0x19a8], ebx
004feb6f 751d                     jne       0x4feb8e
004feb71 8b16                     mov       edx, dword ptr [esi]
004feb73 33c0                     xor       eax, eax
004feb75 3bfb                     cmp       edi, ebx
004feb77 0f95c0                   setne     al
004feb7a 8bce                     mov       ecx, esi
004feb7c 48                       dec       eax
004feb7d 25010000ff               and       eax, 0xff000001
004feb82 48                       dec       eax
004feb83 50                       push      eax
004feb84 6a05                     push      5
004feb86 6a01                     push      1
004feb88 ff9234010000             call      dword ptr [edx + 0x134]
