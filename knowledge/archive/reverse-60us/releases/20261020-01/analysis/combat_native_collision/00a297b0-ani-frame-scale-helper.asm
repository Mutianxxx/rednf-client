00a297b0 55                       push      ebp
00a297b1 8bec                     mov       ebp, esp
00a297b3 83ec0c                   sub       esp, 0xc
00a297b6 53                       push      ebx
00a297b7 56                       push      esi
00a297b8 33f6                     xor       esi, esi
00a297ba 57                       push      edi
00a297bb 8bd9                     mov       ebx, ecx
00a297bd 8975f8                   mov       dword ptr [ebp - 8], esi
00a297c0 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a297c6 85c0                     test      eax, eax
00a297c8 8975fc                   mov       dword ptr [ebp - 4], esi
00a297cb 741b                     je        0xa297e8
00a297cd 8b8b9c000000             mov       ecx, dword ptr [ebx + 0x9c]
00a297d3 2bc8                     sub       ecx, eax
00a297d5 b843082184               mov       eax, 0x84210843
00a297da f7e9                     imul      ecx
00a297dc 03d1                     add       edx, ecx
00a297de c1fa06                   sar       edx, 6
00a297e1 8bc2                     mov       eax, edx
00a297e3 c1e81f                   shr       eax, 0x1f
00a297e6 03c2                     add       eax, edx
00a297e8 40                       inc       eax
00a297e9 3bf0                     cmp       esi, eax
00a297eb 0f8346010000             jae       0xa29937
00a297f1 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a297f7 85c0                     test      eax, eax
00a297f9 741b                     je        0xa29816
00a297fb 8b8b9c000000             mov       ecx, dword ptr [ebx + 0x9c]
00a29801 2bc8                     sub       ecx, eax
00a29803 b843082184               mov       eax, 0x84210843
00a29808 f7e9                     imul      ecx
00a2980a 03d1                     add       edx, ecx
00a2980c c1fa06                   sar       edx, 6
00a2980f 8bc2                     mov       eax, edx
00a29811 c1e81f                   shr       eax, 0x1f
00a29814 03c2                     add       eax, edx
00a29816 3bf0                     cmp       esi, eax
00a29818 750d                     jne       0xa29827
00a2981a 83bb24010000ff           cmp       dword ptr [ebx + 0x124], -1
00a29821 0f8401010000             je        0xa29928
00a29827 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a2982d 85c0                     test      eax, eax
00a2982f 741b                     je        0xa2984c
00a29831 8b8b9c000000             mov       ecx, dword ptr [ebx + 0x9c]
00a29837 2bc8                     sub       ecx, eax
00a29839 b843082184               mov       eax, 0x84210843
00a2983e f7e9                     imul      ecx
00a29840 03d1                     add       edx, ecx
00a29842 c1fa06                   sar       edx, 6
00a29845 8bc2                     mov       eax, edx
00a29847 c1e81f                   shr       eax, 0x1f
00a2984a 03c2                     add       eax, edx
00a2984c 3bf0                     cmp       esi, eax
00a2984e 7518                     jne       0xa29868
00a29850 83bb24010000ff           cmp       dword ptr [ebx + 0x124], -1
00a29857 7507                     jne       0xa29860
00a29859 8bcb                     mov       ecx, ebx
00a2985b e800e7ffff               call      0xa27f60
00a29860 8db3a8000000             lea       esi, [ebx + 0xa8]
00a29866 eb36                     jmp       0xa2989e
00a29868 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a2986e 85c0                     test      eax, eax
00a29870 741b                     je        0xa2988d
00a29872 8b8b9c000000             mov       ecx, dword ptr [ebx + 0x9c]
00a29878 2bc8                     sub       ecx, eax
00a2987a b843082184               mov       eax, 0x84210843
00a2987f f7e9                     imul      ecx
00a29881 03d1                     add       edx, ecx
00a29883 c1fa06                   sar       edx, 6
00a29886 8bc2                     mov       eax, edx
00a29888 c1e81f                   shr       eax, 0x1f
00a2988b 03c2                     add       eax, edx
00a2988d 3bf0                     cmp       esi, eax
00a2988f 7d0b                     jge       0xa2989c
00a29891 8bb398000000             mov       esi, dword ptr [ebx + 0x98]
00a29897 0375f8                   add       esi, dword ptr [ebp - 8]
00a2989a eb02                     jmp       0xa2989e
00a2989c 33f6                     xor       esi, esi
00a2989e 8b5610                   mov       edx, dword ptr [esi + 0x10]
00a298a1 8b0dfc3e0d01             mov       ecx, dword ptr [0x10d3efc]
00a298a7 8d4610                   lea       eax, [esi + 0x10]
00a298aa 2bd0                     sub       edx, eax
00a298ac 33d1                     xor       edx, ecx
00a298ae 8955f4                   mov       dword ptr [ebp - 0xc], edx
00a298b1 d945f4                   fld       dword ptr [ebp - 0xc]
00a298b4 d84d08                   fmul      dword ptr [ebp + 8]
00a298b7 d95df4                   fstp      dword ptr [ebp - 0xc]
00a298ba 334df4                   xor       ecx, dword ptr [ebp - 0xc]
00a298bd 03c8                     add       ecx, eax
00a298bf 8908                     mov       dword ptr [eax], ecx
00a298c1 8b5614                   mov       edx, dword ptr [esi + 0x14]
00a298c4 8b0dfc3e0d01             mov       ecx, dword ptr [0x10d3efc]
00a298ca 8d4614                   lea       eax, [esi + 0x14]
00a298cd 2bd0                     sub       edx, eax
00a298cf 33d1                     xor       edx, ecx
00a298d1 8955f4                   mov       dword ptr [ebp - 0xc], edx
00a298d4 d945f4                   fld       dword ptr [ebp - 0xc]
00a298d7 d84d08                   fmul      dword ptr [ebp + 8]
00a298da d95df4                   fstp      dword ptr [ebp - 0xc]
00a298dd 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
00a298e0 33d1                     xor       edx, ecx
00a298e2 03d0                     add       edx, eax
00a298e4 8910                     mov       dword ptr [eax], edx
00a298e6 8b7e3c                   mov       edi, dword ptr [esi + 0x3c]
00a298e9 3b7e40                   cmp       edi, dword ptr [esi + 0x40]
00a298ec 7417                     je        0xa29905
00a298ee 8bff                     mov       edi, edi
00a298f0 8b4508                   mov       eax, dword ptr [ebp + 8]
00a298f3 50                       push      eax
00a298f4 8bcf                     mov       ecx, edi
00a298f6 e8d5aec8ff               call      0x6b47d0
00a298fb 8b4640                   mov       eax, dword ptr [esi + 0x40]
00a298fe 83c730                   add       edi, 0x30
00a29901 3bf8                     cmp       edi, eax
00a29903 75eb                     jne       0xa298f0
00a29905 8b7e4c                   mov       edi, dword ptr [esi + 0x4c]
00a29908 3b7e50                   cmp       edi, dword ptr [esi + 0x50]
00a2990b 7418                     je        0xa29925
00a2990d 8d4900                   lea       ecx, [ecx]
00a29910 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a29913 51                       push      ecx
00a29914 8bcf                     mov       ecx, edi
00a29916 e8b5aec8ff               call      0x6b47d0
00a2991b 8b4650                   mov       eax, dword ptr [esi + 0x50]
00a2991e 83c730                   add       edi, 0x30
00a29921 3bf8                     cmp       edi, eax
00a29923 75eb                     jne       0xa29910
00a29925 8b75fc                   mov       esi, dword ptr [ebp - 4]
00a29928 8b45f8                   mov       eax, dword ptr [ebp - 8]
00a2992b 46                       inc       esi
00a2992c 83c07c                   add       eax, 0x7c
00a2992f 8945f8                   mov       dword ptr [ebp - 8], eax
00a29932 e989feffff               jmp       0xa297c0
00a29937 5f                       pop       edi
00a29938 5e                       pop       esi
00a29939 5b                       pop       ebx
00a2993a 8be5                     mov       esp, ebp
00a2993c 5d                       pop       ebp
00a2993d c20400                   ret       4
