005f3770 55                       push      ebp
005f3771 8bec                     mov       ebp, esp
005f3773 6aff                     push      -1
005f3775 681f75c600               push      0xc6751f
005f377a 64a100000000             mov       eax, dword ptr fs:[0]
005f3780 50                       push      eax
005f3781 64892500000000           mov       dword ptr fs:[0], esp
005f3788 51                       push      ecx
005f3789 53                       push      ebx
005f378a 56                       push      esi
005f378b 8bf1                     mov       esi, ecx
005f378d 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f3793 85c9                     test      ecx, ecx
005f3795 57                       push      edi
005f3796 0f8493000000             je        0x5f382f
005f379c 8b8650050000             mov       eax, dword ptr [esi + 0x550]
005f37a2 2bc1                     sub       eax, ecx
005f37a4 c1f802                   sar       eax, 2
005f37a7 85c0                     test      eax, eax
005f37a9 0f8680000000             jbe       0x5f382f
005f37af 68e0baca00               push      0xcabae0
005f37b4 e837f94500               call      0xa530f0
005f37b9 50                       push      eax
005f37ba e82cd66000               call      0xc00deb
005f37bf 83c408                   add       esp, 8
005f37c2 85c0                     test      eax, eax
005f37c4 7469                     je        0x5f382f
005f37c6 68b4010000               push      0x1b4
005f37cb e88004e1ff               call      0x403c50
005f37d0 8bd8                     mov       ebx, eax
005f37d2 83c404                   add       esp, 4
005f37d5 895df0                   mov       dword ptr [ebp - 0x10], ebx
005f37d8 85db                     test      ebx, ebx
005f37da c745fc00000000           mov       dword ptr [ebp - 4], 0
005f37e1 743d                     je        0x5f3820
005f37e3 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
005f37ea 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f37f0 7217                     jb        0x5f3809
005f37f2 8bbe48020000             mov       edi, dword ptr [esi + 0x248]
005f37f8 56                       push      esi
005f37f9 e8f2f84500               call      0xa530f0
005f37fe 50                       push      eax
005f37ff 57                       push      edi
005f3800 8bcb                     mov       ecx, ebx
005f3802 e839fceaff               call      0x4a3440
005f3807 eb19                     jmp       0x5f3822
005f3809 56                       push      esi
005f380a 8dbe48020000             lea       edi, [esi + 0x248]
005f3810 e8dbf84500               call      0xa530f0
005f3815 50                       push      eax
005f3816 57                       push      edi
005f3817 8bcb                     mov       ecx, ebx
005f3819 e822fceaff               call      0x4a3440
005f381e eb02                     jmp       0x5f3822
005f3820 33c0                     xor       eax, eax
005f3822 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f3829 89867c080000             mov       dword ptr [esi + 0x87c], eax
005f382f 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
005f3835 85c9                     test      ecx, ecx
005f3837 bb01000000               mov       ebx, 1
005f383c 7426                     je        0x5f3864
005f383e 8b8624010000             mov       eax, dword ptr [esi + 0x124]
005f3844 2bc1                     sub       eax, ecx
005f3846 c1f802                   sar       eax, 2
005f3849 83f802                   cmp       eax, 2
005f384c 7616                     jbe       0x5f3864
005f384e 8bc1                     mov       eax, ecx
005f3850 8b4804                   mov       ecx, dword ptr [eax + 4]
005f3853 85c9                     test      ecx, ecx
005f3855 740d                     je        0x5f3864
005f3857 8b4808                   mov       ecx, dword ptr [eax + 8]
005f385a 85c9                     test      ecx, ecx
005f385c 7406                     je        0x5f3864
005f385e 889e80080000             mov       byte ptr [esi + 0x880], bl
005f3864 6a00                     push      0
005f3866 e885a82b00               call      0x8ae0f0
005f386b 99                       cdq       
005f386c b9e8030000               mov       ecx, 0x3e8
005f3871 f7f9                     idiv      ecx
005f3873 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
005f3879 83c404                   add       esp, 4
005f387c 52                       push      edx
005f387d e8be4a4300               call      0xa28340
005f3882 8b862c050000             mov       eax, dword ptr [esi + 0x52c]
005f3888 85c0                     test      eax, eax
005f388a 7506                     jne       0x5f3892
005f388c 889e70080000             mov       byte ptr [esi + 0x870], bl
005f3892 8b8e34020000             mov       ecx, dword ptr [esi + 0x234]
005f3898 85c9                     test      ecx, ecx
005f389a 7421                     je        0x5f38bd
005f389c 8b8638020000             mov       eax, dword ptr [esi + 0x238]
005f38a2 2bc1                     sub       eax, ecx
005f38a4 c1f802                   sar       eax, 2
005f38a7 3bc3                     cmp       eax, ebx
005f38a9 7612                     jbe       0x5f38bd
005f38ab 8bc1                     mov       eax, ecx
005f38ad 8b4804                   mov       ecx, dword ptr [eax + 4]
005f38b0 83c004                   add       eax, 4
005f38b3 3bcb                     cmp       ecx, ebx
005f38b5 7506                     jne       0x5f38bd
005f38b7 889e8c080000             mov       byte ptr [esi + 0x88c], bl
005f38bd 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
005f38c3 85c9                     test      ecx, ecx
005f38c5 7422                     je        0x5f38e9
005f38c7 8b8624010000             mov       eax, dword ptr [esi + 0x124]
005f38cd 2bc1                     sub       eax, ecx
005f38cf c1f802                   sar       eax, 2
005f38d2 85c0                     test      eax, eax
005f38d4 7613                     jbe       0x5f38e9
005f38d6 8bc1                     mov       eax, ecx
005f38d8 833800                   cmp       dword ptr [eax], 0
005f38db 740c                     je        0x5f38e9
005f38dd c7867808000002000000     mov       dword ptr [esi + 0x878], 2
005f38e7 eb06                     jmp       0x5f38ef
005f38e9 899e78080000             mov       dword ptr [esi + 0x878], ebx
005f38ef 8b16                     mov       edx, dword ptr [esi]
005f38f1 8bce                     mov       ecx, esi
005f38f3 ff9204020000             call      dword ptr [edx + 0x204]
005f38f9 85c0                     test      eax, eax
005f38fb 7e29                     jle       0x5f3926
005f38fd 8b3e                     mov       edi, dword ptr [esi]
005f38ff 8bce                     mov       ecx, esi
005f3901 ff9704020000             call      dword ptr [edi + 0x204]
005f3907 50                       push      eax
005f3908 8b06                     mov       eax, dword ptr [esi]
005f390a 8bce                     mov       ecx, esi
005f390c ff9098000000             call      dword ptr [eax + 0x98]
005f3912 8b16                     mov       edx, dword ptr [esi]
005f3914 50                       push      eax
005f3915 8bce                     mov       ecx, esi
005f3917 ff9294000000             call      dword ptr [edx + 0x94]
005f391d 50                       push      eax
005f391e 8bce                     mov       ecx, esi
005f3920 ff9788000000             call      dword ptr [edi + 0x88]
005f3926 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f3929 5f                       pop       edi
005f392a 5e                       pop       esi
005f392b 5b                       pop       ebx
005f392c 64890d00000000           mov       dword ptr fs:[0], ecx
005f3933 8be5                     mov       esp, ebp
005f3935 5d                       pop       ebp
005f3936 c3                       ret       
005f3937 cc                       int3      
005f3938 cc                       int3      
005f3939 cc                       int3      
005f393a cc                       int3      
005f393b cc                       int3      
005f393c cc                       int3      
005f393d cc                       int3      
005f393e cc                       int3      
005f393f cc                       int3      
005f3940 55                       push      ebp
005f3941 8bec                     mov       ebp, esp
005f3943 6aff                     push      -1
005f3945 683475c600               push      0xc67534
005f394a 64a100000000             mov       eax, dword ptr fs:[0]
005f3950 50                       push      eax
005f3951 64892500000000           mov       dword ptr fs:[0], esp
005f3958 83ec10                   sub       esp, 0x10
005f395b 53                       push      ebx
005f395c 56                       push      esi
005f395d 8bf1                     mov       esi, ecx
005f395f 8b8e94080000             mov       ecx, dword ptr [esi + 0x894]
005f3965 33db                     xor       ebx, ebx
005f3967 3bcb                     cmp       ecx, ebx
005f3969 57                       push      edi
005f396a 0f8419010000             je        0x5f3a89
005f3970 8b8698080000             mov       eax, dword ptr [esi + 0x898]
005f3976 2bc1                     sub       eax, ecx
005f3978 c1f803                   sar       eax, 3
005f397b 3bc3                     cmp       eax, ebx
005f397d 0f8406010000             je        0x5f3a89
005f3983 8b06                     mov       eax, dword ptr [esi]
005f3985 8bce                     mov       ecx, esi
005f3987 ff5040                   call      dword ptr [eax + 0x40]
005f398a 33d2                     xor       edx, edx
005f398c 8945e8                   mov       dword ptr [ebp - 0x18], eax
005f398f b968010000               mov       ecx, 0x168
005f3994 f7f1                     div       ecx
005f3996 8bbe94080000             mov       edi, dword ptr [esi + 0x894]
005f399c 3bbe98080000             cmp       edi, dword ptr [esi + 0x898]
005f39a2 897dec                   mov       dword ptr [ebp - 0x14], edi
005f39a5 8955f0                   mov       dword ptr [ebp - 0x10], edx
005f39a8 0f84b6000000             je        0x5f3a64
005f39ae 8bff                     mov       edi, edi
005f39b0 6808090000               push      0x908
005f39b5 e89602e1ff               call      0x403c50
005f39ba 83c404                   add       esp, 4
005f39bd 8945e4                   mov       dword ptr [ebp - 0x1c], eax
005f39c0 3bc3                     cmp       eax, ebx
005f39c2 895dfc                   mov       dword ptr [ebp - 4], ebx
005f39c5 7419                     je        0x5f39e0
005f39c7 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
005f39ca 6a64                     push      0x64
005f39cc 52                       push      edx
005f39cd 8b5704                   mov       edx, dword ptr [edi + 4]
005f39d0 8d4de8                   lea       ecx, [ebp - 0x18]
005f39d3 51                       push      ecx
005f39d4 52                       push      edx
005f39d5 8bc8                     mov       ecx, eax
005f39d7 e8f45de4ff               call      0x4397d0
005f39dc 8bf8                     mov       edi, eax
005f39de eb02                     jmp       0x5f39e2
005f39e0 33ff                     xor       edi, edi
005f39e2 8b06                     mov       eax, dword ptr [esi]
005f39e4 8b1f                     mov       ebx, dword ptr [edi]
005f39e6 6a3c                     push      0x3c
005f39e8 8bce                     mov       ecx, esi
005f39ea c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f39f1 ff9098000000             call      dword ptr [eax + 0x98]
005f39f7 8b16                     mov       edx, dword ptr [esi]
005f39f9 50                       push      eax
005f39fa 8bce                     mov       ecx, esi
005f39fc ff9294000000             call      dword ptr [edx + 0x94]
005f3a02 50                       push      eax
005f3a03 8bcf                     mov       ecx, edi
005f3a05 ff9388000000             call      dword ptr [ebx + 0x88]
005f3a0b 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f3a11 33db                     xor       ebx, ebx
005f3a13 53                       push      ebx
005f3a14 53                       push      ebx
005f3a15 53                       push      ebx
005f3a16 57                       push      edi
005f3a17 8b7dec                   mov       edi, dword ptr [ebp - 0x14]
005f3a1a 8b07                     mov       eax, dword ptr [edi]
005f3a1c 50                       push      eax
005f3a1d 6821010000               push      0x121
005f3a22 56                       push      esi
005f3a23 e848a3f1ff               call      0x50dd70
005f3a28 8b8694080000             mov       eax, dword ptr [esi + 0x894]
005f3a2e 3bc3                     cmp       eax, ebx
005f3a30 7504                     jne       0x5f3a36
005f3a32 33c9                     xor       ecx, ecx
005f3a34 eb0b                     jmp       0x5f3a41
005f3a36 8b8e98080000             mov       ecx, dword ptr [esi + 0x898]
005f3a3c 2bc8                     sub       ecx, eax
005f3a3e c1f903                   sar       ecx, 3
005f3a41 33d2                     xor       edx, edx
005f3a43 b868010000               mov       eax, 0x168
005f3a48 f7f1                     div       ecx
005f3a4a 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
005f3a4d 83c708                   add       edi, 8
005f3a50 897dec                   mov       dword ptr [ebp - 0x14], edi
005f3a53 03d0                     add       edx, eax
005f3a55 3bbe98080000             cmp       edi, dword ptr [esi + 0x898]
005f3a5b 8955f0                   mov       dword ptr [ebp - 0x10], edx
005f3a5e 0f854cffffff             jne       0x5f39b0
005f3a64 8b8694080000             mov       eax, dword ptr [esi + 0x894]
005f3a6a 3bc3                     cmp       eax, ebx
005f3a6c 7409                     je        0x5f3a77
005f3a6e 50                       push      eax
005f3a6f e869c56000               call      0xbfffdd
005f3a74 83c404                   add       esp, 4
005f3a77 899e94080000             mov       dword ptr [esi + 0x894], ebx
005f3a7d 899e98080000             mov       dword ptr [esi + 0x898], ebx
005f3a83 899e9c080000             mov       dword ptr [esi + 0x89c], ebx
005f3a89 8b8ea4080000             mov       ecx, dword ptr [esi + 0x8a4]
005f3a8f 3bcb                     cmp       ecx, ebx
005f3a91 7459                     je        0x5f3aec
005f3a93 8b86a8080000             mov       eax, dword ptr [esi + 0x8a8]
005f3a99 2bc1                     sub       eax, ecx
005f3a9b c1f803                   sar       eax, 3
005f3a9e 3bc3                     cmp       eax, ebx
005f3aa0 764a                     jbe       0x5f3aec
005f3aa2 8bce                     mov       ecx, esi
005f3aa4 e8e785eaff               call      0x49c090
005f3aa9 84c0                     test      al, al
005f3aab 743f                     je        0x5f3aec
005f3aad 33ff                     xor       edi, edi
005f3aaf 90                       nop       
005f3ab0 8b8ea4080000             mov       ecx, dword ptr [esi + 0x8a4]
005f3ab6 3bcb                     cmp       ecx, ebx
005f3ab8 7432                     je        0x5f3aec
005f3aba 8b86a8080000             mov       eax, dword ptr [esi + 0x8a8]
005f3ac0 2bc1                     sub       eax, ecx
005f3ac2 c1f803                   sar       eax, 3
005f3ac5 3bf8                     cmp       edi, eax
005f3ac7 7323                     jae       0x5f3aec
005f3ac9 53                       push      ebx
005f3aca 53                       push      ebx
005f3acb 8b16                     mov       edx, dword ptr [esi]
005f3acd 53                       push      ebx
005f3ace 53                       push      ebx
005f3acf 53                       push      ebx
005f3ad0 6a04                     push      4
005f3ad2 53                       push      ebx
005f3ad3 53                       push      ebx
005f3ad4 53                       push      ebx
005f3ad5 8d04f9                   lea       eax, [ecx + edi*8]
005f3ad8 8b4804                   mov       ecx, dword ptr [eax + 4]
005f3adb 8b00                     mov       eax, dword ptr [eax]
005f3add 53                       push      ebx
005f3ade 53                       push      ebx
005f3adf 51                       push      ecx
005f3ae0 50                       push      eax
005f3ae1 8bce                     mov       ecx, esi
005f3ae3 ff92b8020000             call      dword ptr [edx + 0x2b8]
005f3ae9 47                       inc       edi
005f3aea ebc4                     jmp       0x5f3ab0
005f3aec 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f3aef 5f                       pop       edi
005f3af0 5e                       pop       esi
005f3af1 5b                       pop       ebx
005f3af2 64890d00000000           mov       dword ptr fs:[0], ecx
005f3af9 8be5                     mov       esp, ebp
005f3afb 5d                       pop       ebp
005f3afc c3                       ret       
005f3afd cc                       int3      
005f3afe cc                       int3      
005f3aff cc                       int3      
