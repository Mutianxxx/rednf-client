005f7700 55                       push      ebp
005f7701 8bec                     mov       ebp, esp
005f7703 8b4514                   mov       eax, dword ptr [ebp + 0x14]
005f7706 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f7709 56                       push      esi
005f770a 57                       push      edi
005f770b 8b7d08                   mov       edi, dword ptr [ebp + 8]
005f770e 8bf1                     mov       esi, ecx
005f7710 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005f7713 50                       push      eax
005f7714 51                       push      ecx
005f7715 52                       push      edx
005f7716 57                       push      edi
005f7717 8bce                     mov       ecx, esi
005f7719 e8b260eaff               call      0x49d7d0
005f771e 8bc7                     mov       eax, edi
005f7720 83e802                   sub       eax, 2
005f7723 7519                     jne       0x5f773e
005f7725 8bce                     mov       ecx, esi
005f7727 e8e4f6ffff               call      0x5f6e10
005f772c 8b06                     mov       eax, dword ptr [esi]
005f772e 6a01                     push      1
005f7730 6a01                     push      1
005f7732 6a00                     push      0
005f7734 6a00                     push      0
005f7736 8bce                     mov       ecx, esi
005f7738 ff902c020000             call      dword ptr [eax + 0x22c]
005f773e 5f                       pop       edi
005f773f 5e                       pop       esi
005f7740 5d                       pop       ebp
005f7741 c21000                   ret       0x10
005f7744 cc                       int3      
005f7745 cc                       int3      
005f7746 cc                       int3      
005f7747 cc                       int3      
005f7748 cc                       int3      
005f7749 cc                       int3      
005f774a cc                       int3      
005f774b cc                       int3      
005f774c cc                       int3      
005f774d cc                       int3      
005f774e cc                       int3      
005f774f cc                       int3      
005f7750 56                       push      esi
005f7751 8bf1                     mov       esi, ecx
005f7753 c6864909000001           mov       byte ptr [esi + 0x949], 1
005f775a e861fdffff               call      0x5f74c0
005f775f 8bce                     mov       ecx, esi
005f7761 e83ae0ffff               call      0x5f57a0
005f7766 8bce                     mov       ecx, esi
005f7768 5e                       pop       esi
005f7769 e962e5ffff               jmp       0x5f5cd0
005f776e cc                       int3      
005f776f cc                       int3      
005f7770 55                       push      ebp
005f7771 8bec                     mov       ebp, esp
005f7773 6aff                     push      -1
005f7775 68e076c600               push      0xc676e0
005f777a 64a100000000             mov       eax, dword ptr fs:[0]
005f7780 50                       push      eax
005f7781 64892500000000           mov       dword ptr fs:[0], esp
005f7788 83ec10                   sub       esp, 0x10
005f778b 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f778e 53                       push      ebx
005f778f 56                       push      esi
005f7790 8bf1                     mov       esi, ecx
005f7792 8b08                     mov       ecx, dword ptr [eax]
005f7794 8b5004                   mov       edx, dword ptr [eax + 4]
005f7797 8b5e04                   mov       ebx, dword ptr [esi + 4]
005f779a 85db                     test      ebx, ebx
005f779c 8b4008                   mov       eax, dword ptr [eax + 8]
005f779f 57                       push      edi
005f77a0 8965f0                   mov       dword ptr [ebp - 0x10], esp
005f77a3 894de4                   mov       dword ptr [ebp - 0x1c], ecx
005f77a6 8955e8                   mov       dword ptr [ebp - 0x18], edx
005f77a9 8945ec                   mov       dword ptr [ebp - 0x14], eax
005f77ac 7504                     jne       0x5f77b2
005f77ae 33c9                     xor       ecx, ecx
005f77b0 eb15                     jmp       0x5f77c7
005f77b2 8b4e0c                   mov       ecx, dword ptr [esi + 0xc]
005f77b5 2bcb                     sub       ecx, ebx
005f77b7 b8abaaaa2a               mov       eax, 0x2aaaaaab
005f77bc f7e9                     imul      ecx
005f77be d1fa                     sar       edx, 1
005f77c0 8bca                     mov       ecx, edx
005f77c2 c1e91f                   shr       ecx, 0x1f
005f77c5 03ca                     add       ecx, edx
005f77c7 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
005f77ca 85ff                     test      edi, edi
005f77cc 0f8438020000             je        0x5f7a0a
005f77d2 85db                     test      ebx, ebx
005f77d4 7504                     jne       0x5f77da
005f77d6 33c0                     xor       eax, eax
005f77d8 eb15                     jmp       0x5f77ef
005f77da 8b5608                   mov       edx, dword ptr [esi + 8]
005f77dd 2bd3                     sub       edx, ebx
005f77df b8abaaaa2a               mov       eax, 0x2aaaaaab
005f77e4 f7ea                     imul      edx
005f77e6 d1fa                     sar       edx, 1
005f77e8 8bc2                     mov       eax, edx
005f77ea c1e81f                   shr       eax, 0x1f
005f77ed 03c2                     add       eax, edx
005f77ef ba55555515               mov       edx, 0x15555555
005f77f4 2bd0                     sub       edx, eax
005f77f6 3bd7                     cmp       edx, edi
005f77f8 7307                     jae       0x5f7801
005f77fa 8bce                     mov       ecx, esi
005f77fc e8df49e9ff               call      0x48c1e0
005f7801 85db                     test      ebx, ebx
005f7803 7504                     jne       0x5f7809
005f7805 33c0                     xor       eax, eax
005f7807 eb15                     jmp       0x5f781e
005f7809 8b5608                   mov       edx, dword ptr [esi + 8]
005f780c 2bd3                     sub       edx, ebx
005f780e b8abaaaa2a               mov       eax, 0x2aaaaaab
005f7813 f7ea                     imul      edx
005f7815 d1fa                     sar       edx, 1
005f7817 8bc2                     mov       eax, edx
005f7819 c1e81f                   shr       eax, 0x1f
005f781c 03c2                     add       eax, edx
005f781e 03c7                     add       eax, edi
005f7820 3bc8                     cmp       ecx, eax
005f7822 0f830e010000             jae       0x5f7936
005f7828 8bc1                     mov       eax, ecx
005f782a d1e8                     shr       eax, 1
005f782c ba55555515               mov       edx, 0x15555555
005f7831 2bd0                     sub       edx, eax
005f7833 3bd1                     cmp       edx, ecx
005f7835 7304                     jae       0x5f783b
005f7837 33c9                     xor       ecx, ecx
005f7839 eb02                     jmp       0x5f783d
005f783b 03c8                     add       ecx, eax
005f783d 85db                     test      ebx, ebx
005f783f 7504                     jne       0x5f7845
005f7841 33c0                     xor       eax, eax
005f7843 eb15                     jmp       0x5f785a
005f7845 8b5608                   mov       edx, dword ptr [esi + 8]
005f7848 2bd3                     sub       edx, ebx
005f784a b8abaaaa2a               mov       eax, 0x2aaaaaab
005f784f f7ea                     imul      edx
005f7851 d1fa                     sar       edx, 1
005f7853 8bc2                     mov       eax, edx
005f7855 c1e81f                   shr       eax, 0x1f
005f7858 03c2                     add       eax, edx
005f785a 03c7                     add       eax, edi
005f785c 3bc8                     cmp       ecx, eax
005f785e 730b                     jae       0x5f786b
005f7860 8bce                     mov       ecx, esi
005f7862 e8e91d1200               call      0x719650
005f7867 8bc8                     mov       ecx, eax
005f7869 03cf                     add       ecx, edi
005f786b 8d1c49                   lea       ebx, [ecx + ecx*2]
005f786e c1e302                   shl       ebx, 2
005f7871 53                       push      ebx
005f7872 e8a6605f00               call      0xbed91d
005f7877 8b5508                   mov       edx, dword ptr [ebp + 8]
005f787a 8b4e04                   mov       ecx, dword ptr [esi + 4]
005f787d 52                       push      edx
005f787e 56                       push      esi
005f787f 50                       push      eax
005f7880 894510                   mov       dword ptr [ebp + 0x10], eax
005f7883 8b4508                   mov       eax, dword ptr [ebp + 8]
005f7886 50                       push      eax
005f7887 51                       push      ecx
005f7888 c745fc00000000           mov       dword ptr [ebp - 4], 0
005f788f e8dcbce3ff               call      0x433570
005f7894 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f7897 83c418                   add       esp, 0x18
005f789a 51                       push      ecx
005f789b 56                       push      esi
005f789c 8d55e4                   lea       edx, [ebp - 0x1c]
005f789f 52                       push      edx
005f78a0 57                       push      edi
005f78a1 50                       push      eax
005f78a2 89450c                   mov       dword ptr [ebp + 0xc], eax
005f78a5 e866102400               call      0x838910
005f78aa 8b5508                   mov       edx, dword ptr [ebp + 8]
005f78ad 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005f78b0 83c414                   add       esp, 0x14
005f78b3 52                       push      edx
005f78b4 8d047f                   lea       eax, [edi + edi*2]
005f78b7 8d0481                   lea       eax, [ecx + eax*4]
005f78ba 8b4e08                   mov       ecx, dword ptr [esi + 8]
005f78bd 56                       push      esi
005f78be 50                       push      eax
005f78bf 8b4508                   mov       eax, dword ptr [ebp + 8]
005f78c2 51                       push      ecx
005f78c3 50                       push      eax
005f78c4 e8a7bce3ff               call      0x433570
005f78c9 8b4604                   mov       eax, dword ptr [esi + 4]
005f78cc 83c414                   add       esp, 0x14
005f78cf 85c0                     test      eax, eax
005f78d1 7415                     je        0x5f78e8
005f78d3 8b4e08                   mov       ecx, dword ptr [esi + 8]
005f78d6 2bc8                     sub       ecx, eax
005f78d8 b8abaaaa2a               mov       eax, 0x2aaaaaab
005f78dd f7e9                     imul      ecx
005f78df d1fa                     sar       edx, 1
005f78e1 8bc2                     mov       eax, edx
005f78e3 c1e81f                   shr       eax, 0x1f
005f78e6 03c2                     add       eax, edx
005f78e8 03f8                     add       edi, eax
005f78ea 8b4604                   mov       eax, dword ptr [esi + 4]
005f78ed 85c0                     test      eax, eax
005f78ef 7409                     je        0x5f78fa
005f78f1 50                       push      eax
005f78f2 e8e6866000               call      0xbfffdd
005f78f7 83c404                   add       esp, 4
005f78fa 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f78fd 8d0c7f                   lea       ecx, [edi + edi*2]
005f7900 03d8                     add       ebx, eax
005f7902 8d1488                   lea       edx, [eax + ecx*4]
005f7905 895e0c                   mov       dword ptr [esi + 0xc], ebx
005f7908 895608                   mov       dword ptr [esi + 8], edx
005f790b 894604                   mov       dword ptr [esi + 4], eax
005f790e 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f7911 64890d00000000           mov       dword ptr fs:[0], ecx
005f7918 5f                       pop       edi
005f7919 5e                       pop       esi
005f791a 5b                       pop       ebx
005f791b 8be5                     mov       esp, ebp
005f791d 5d                       pop       ebp
005f791e c20c00                   ret       0xc
005f7921 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f7924 50                       push      eax
005f7925 e8b3866000               call      0xbfffdd
005f792a 83c404                   add       esp, 4
005f792d 6a00                     push      0
005f792f 6a00                     push      0
005f7931 e8398c6000               call      0xc0056f
005f7936 8b4e08                   mov       ecx, dword ptr [esi + 8]
005f7939 8b5d08                   mov       ebx, dword ptr [ebp + 8]
005f793c 8bd1                     mov       edx, ecx
005f793e 2bd3                     sub       edx, ebx
005f7940 b8abaaaa2a               mov       eax, 0x2aaaaaab
005f7945 f7ea                     imul      edx
005f7947 d1fa                     sar       edx, 1
005f7949 8bc2                     mov       eax, edx
005f794b c1e81f                   shr       eax, 0x1f
005f794e 03c2                     add       eax, edx
005f7950 3bc7                     cmp       eax, edi
005f7952 894d10                   mov       dword ptr [ebp + 0x10], ecx
005f7955 7378                     jae       0x5f79cf
005f7957 8d047f                   lea       eax, [edi + edi*2]
005f795a c1e002                   shl       eax, 2
005f795d 894508                   mov       dword ptr [ebp + 8], eax
005f7960 8b5508                   mov       edx, dword ptr [ebp + 8]
005f7963 52                       push      edx
005f7964 56                       push      esi
005f7965 03c3                     add       eax, ebx
005f7967 50                       push      eax
005f7968 51                       push      ecx
005f7969 53                       push      ebx
005f796a e801bce3ff               call      0x433570
005f796f 8b4e08                   mov       ecx, dword ptr [esi + 8]
005f7972 83c414                   add       esp, 0x14
005f7975 8d45e4                   lea       eax, [ebp - 0x1c]
005f7978 50                       push      eax
005f7979 8bd1                     mov       edx, ecx
005f797b 2bd3                     sub       edx, ebx
005f797d b8abaaaa2a               mov       eax, 0x2aaaaaab
005f7982 f7ea                     imul      edx
005f7984 d1fa                     sar       edx, 1
005f7986 8bc2                     mov       eax, edx
005f7988 c1e81f                   shr       eax, 0x1f
005f798b 03c2                     add       eax, edx
005f798d 2bf8                     sub       edi, eax
005f798f 57                       push      edi
005f7990 51                       push      ecx
005f7991 8bce                     mov       ecx, esi
005f7993 c745fc02000000           mov       dword ptr [ebp - 4], 2
005f799a e8a1c52400               call      0x843f40
005f799f 8b7e08                   mov       edi, dword ptr [esi + 8]
005f79a2 8b4508                   mov       eax, dword ptr [ebp + 8]
005f79a5 03f8                     add       edi, eax
005f79a7 897e08                   mov       dword ptr [esi + 8], edi
005f79aa 8d4de4                   lea       ecx, [ebp - 0x1c]
005f79ad 8bf7                     mov       esi, edi
005f79af 51                       push      ecx
005f79b0 2bf0                     sub       esi, eax
005f79b2 56                       push      esi
005f79b3 53                       push      ebx
005f79b4 e847072800               call      0x878100
005f79b9 83c40c                   add       esp, 0xc
005f79bc 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f79bf 64                       .byte     0x64
