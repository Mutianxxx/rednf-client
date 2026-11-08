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
