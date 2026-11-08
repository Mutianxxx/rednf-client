004eb780 55                       push      ebp
004eb781 8bec                     mov       ebp, esp
004eb783 81ecd8010000             sub       esp, 0x1d8
004eb789 53                       push      ebx
004eb78a 56                       push      esi
004eb78b 8b7514                   mov       esi, dword ptr [ebp + 0x14]
004eb78e 8b06                     mov       eax, dword ptr [esi]
004eb790 57                       push      edi
004eb791 8bf9                     mov       edi, ecx
004eb793 8bce                     mov       ecx, esi
004eb795 897df8                   mov       dword ptr [ebp - 8], edi
004eb798 ff909c010000             call      dword ptr [eax + 0x19c]
004eb79e 8bd8                     mov       ebx, eax
004eb7a0 85db                     test      ebx, ebx
004eb7a2 895df4                   mov       dword ptr [ebp - 0xc], ebx
004eb7a5 7412                     je        0x4eb7b9
004eb7a7 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004eb7aa 85c0                     test      eax, eax
004eb7ac 7e0b                     jle       0x4eb7b9
004eb7ae 8bcb                     mov       ecx, ebx
004eb7b0 e8cbbcf7ff               call      0x467480
004eb7b5 84c0                     test      al, al
004eb7b7 750b                     jne       0x4eb7c4
004eb7b9 5f                       pop       edi
004eb7ba 5e                       pop       esi
004eb7bb 33c0                     xor       eax, eax
004eb7bd 5b                       pop       ebx
004eb7be 8be5                     mov       esp, ebp
004eb7c0 5d                       pop       ebp
004eb7c1 c21800                   ret       0x18
004eb7c4 6a00                     push      0
004eb7c6 686c52f500               push      0xf5526c
004eb7cb 687c28f400               push      0xf4287c
004eb7d0 6a00                     push      0
004eb7d2 57                       push      edi
004eb7d3 e833557100               call      0xc00d0b
004eb7d8 83c414                   add       esp, 0x14
004eb7db 8d8d28feffff             lea       ecx, [ebp - 0x1d8]
004eb7e1 894514                   mov       dword ptr [ebp + 0x14], eax
004eb7e4 e867a2f6ff               call      0x455a50
004eb7e9 8b16                     mov       edx, dword ptr [esi]
004eb7eb 8bce                     mov       ecx, esi
004eb7ed ff5230                   call      dword ptr [edx + 0x30]
004eb7f0 8945b9                   mov       dword ptr [ebp - 0x47], eax
004eb7f3 8b06                     mov       eax, dword ptr [esi]
004eb7f5 8bce                     mov       ecx, esi
004eb7f7 ff90b0020000             call      dword ptr [eax + 0x2b0]
004eb7fd 8b17                     mov       edx, dword ptr [edi]
004eb7ff 8bcf                     mov       ecx, edi
004eb801 8945bd                   mov       dword ptr [ebp - 0x43], eax
004eb804 ff5230                   call      dword ptr [edx + 0x30]
004eb807 8945c1                   mov       dword ptr [ebp - 0x3f], eax
004eb80a 8b07                     mov       eax, dword ptr [edi]
004eb80c 8bcf                     mov       ecx, edi
004eb80e ff90b0020000             call      dword ptr [eax + 0x2b0]
004eb814 8b17                     mov       edx, dword ptr [edi]
004eb816 8bcf                     mov       ecx, edi
004eb818 8945c5                   mov       dword ptr [ebp - 0x3b], eax
004eb81b ff5240                   call      dword ptr [edx + 0x40]
004eb81e 56                       push      esi
004eb81f 57                       push      edi
004eb820 8945c9                   mov       dword ptr [ebp - 0x37], eax
004eb823 c645cd00                 mov       byte ptr [ebp - 0x33], 0
004eb827 c645ce00                 mov       byte ptr [ebp - 0x32], 0
004eb82b e8c0d8ffff               call      0x4e90f0
004eb830 56                       push      esi
004eb831 57                       push      edi
004eb832 8845dd                   mov       byte ptr [ebp - 0x23], al
004eb835 e826d9ffff               call      0x4e9160
004eb83a 8845de                   mov       byte ptr [ebp - 0x22], al
004eb83d 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004eb840 8b08                     mov       ecx, dword ptr [eax]
004eb842 83c410                   add       esp, 0x10
004eb845 894dcf                   mov       dword ptr [ebp - 0x31], ecx
004eb848 53                       push      ebx
004eb849 8bcf                     mov       ecx, edi
004eb84b c645d301                 mov       byte ptr [ebp - 0x2d], 1
004eb84f e8bcd2ffff               call      0x4e8b10
004eb854 84c0                     test      al, al
004eb856 8845df                   mov       byte ptr [ebp - 0x21], al
004eb859 0f84bf000000             je        0x4eb91e
004eb85f 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004eb862 85c0                     test      eax, eax
004eb864 0f84b4000000             je        0x4eb91e
004eb86a 8d8b28010000             lea       ecx, [ebx + 0x128]
004eb870 e83b7bf4ff               call      0x4333b0
004eb875 d80dac10cc00             fmul      dword ptr [0xcc10ac]
004eb87b 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004eb87e 8b11                     mov       edx, dword ptr [ecx]
004eb880 d95dfc                   fstp      dword ptr [ebp - 4]
004eb883 ff9234020000             call      dword ptr [edx + 0x234]
004eb889 8945f0                   mov       dword ptr [ebp - 0x10], eax
004eb88c db45f0                   fild      dword ptr [ebp - 0x10]
004eb88f d84dfc                   fmul      dword ptr [ebp - 4]
004eb892 e8ad5c7100               call      0xc01544
004eb897 6a00                     push      0
004eb899 682829f400               push      0xf42928
004eb89e 686c52f500               push      0xf5526c
004eb8a3 8945e0                   mov       dword ptr [ebp - 0x20], eax
004eb8a6 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004eb8a9 6a00                     push      0
004eb8ab 50                       push      eax
004eb8ac e85a547100               call      0xc00d0b
004eb8b1 83c414                   add       esp, 0x14
004eb8b4 85c0                     test      eax, eax
004eb8b6 7466                     je        0x4eb91e
004eb8b8 8b88e4190000             mov       ecx, dword ptr [eax + 0x19e4]
004eb8be 83f901                   cmp       ecx, 1
004eb8c1 7516                     jne       0x4eb8d9
004eb8c3 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004eb8c6 b856555555               mov       eax, 0x55555556
004eb8cb f7e9                     imul      ecx
004eb8cd 8bca                     mov       ecx, edx
004eb8cf c1e91f                   shr       ecx, 0x1f
004eb8d2 03ca                     add       ecx, edx
004eb8d4 894de0                   mov       dword ptr [ebp - 0x20], ecx
004eb8d7 eb45                     jmp       0x4eb91e
004eb8d9 83f902                   cmp       ecx, 2
004eb8dc 7507                     jne       0x4eb8e5
004eb8de b856555555               mov       eax, 0x55555556
004eb8e3 eb2a                     jmp       0x4eb90f
004eb8e5 83f903                   cmp       ecx, 3
004eb8e8 7516                     jne       0x4eb900
004eb8ea 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004eb8ed b8abaaaa2a               mov       eax, 0x2aaaaaab
004eb8f2 f7e9                     imul      ecx
004eb8f4 8bca                     mov       ecx, edx
004eb8f6 c1e91f                   shr       ecx, 0x1f
004eb8f9 03ca                     add       ecx, edx
004eb8fb 894de0                   mov       dword ptr [ebp - 0x20], ecx
004eb8fe eb1e                     jmp       0x4eb91e
004eb900 8a881c1e0000             mov       cl, byte ptr [eax + 0x1e1c]
004eb906 84c9                     test      cl, cl
004eb908 7414                     je        0x4eb91e
004eb90a b8abaaaa2a               mov       eax, 0x2aaaaaab
004eb90f 8b4de0                   mov       ecx, dword ptr [ebp - 0x20]
004eb912 f7e9                     imul      ecx
004eb914 8bc2                     mov       eax, edx
004eb916 c1e81f                   shr       eax, 0x1f
004eb919 03c2                     add       eax, edx
004eb91b 8945e0                   mov       dword ptr [ebp - 0x20], eax
004eb91e 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004eb921 85c0                     test      eax, eax
004eb923 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004eb926 894dd4                   mov       dword ptr [ebp - 0x2c], ecx
004eb929 7407                     je        0x4eb932
004eb92b 8b10                     mov       edx, dword ptr [eax]
004eb92d 8955d8                   mov       dword ptr [ebp - 0x28], edx
004eb930 eb0d                     jmp       0x4eb93f
004eb932 6a00                     push      0
004eb934 e8b7273c00               call      0x8ae0f0
004eb939 83c404                   add       esp, 4
004eb93c 8945d8                   mov       dword ptr [ebp - 0x28], eax
004eb93f 8bbf00010000             mov       edi, dword ptr [edi + 0x100]
004eb945 85ff                     test      edi, edi
004eb947 7417                     je        0x4eb960
004eb949 8b8714010000             mov       eax, dword ptr [edi + 0x114]
004eb94f 85c0                     test      eax, eax
004eb951 740d                     je        0x4eb960
004eb953 8b4050                   mov       eax, dword ptr [eax + 0x50]
004eb956 85c0                     test      eax, eax
004eb958 7406                     je        0x4eb960
004eb95a 8a4064                   mov       al, byte ptr [eax + 0x64]
004eb95d 8845dc                   mov       byte ptr [ebp - 0x24], al
004eb960 8b16                     mov       edx, dword ptr [esi]
004eb962 8bce                     mov       ecx, esi
004eb964 ff928c010000             call      dword ptr [edx + 0x18c]
004eb96a 85c0                     test      eax, eax
004eb96c 0f95c0                   setne     al
004eb96f 8bcb                     mov       ecx, ebx
004eb971 8845b5                   mov       byte ptr [ebp - 0x4b], al
004eb974 e8377af4ff               call      0x4333b0
004eb979 d99d28feffff             fstp      dword ptr [ebp - 0x1d8]
004eb97f 8d4b1c                   lea       ecx, [ebx + 0x1c]
004eb982 e8d966f1ff               call      0x402060
004eb987 88852cfeffff             mov       byte ptr [ebp - 0x1d4], al
004eb98d 8a4b18                   mov       cl, byte ptr [ebx + 0x18]
004eb990 888d2dfeffff             mov       byte ptr [ebp - 0x1d3], cl
004eb996 8d4b10                   lea       ecx, [ebx + 0x10]
004eb999 e8c266f1ff               call      0x402060
004eb99e 894510                   mov       dword ptr [ebp + 0x10], eax
004eb9a1 db4510                   fild      dword ptr [ebp + 0x10]
004eb9a4 d99d2efeffff             fstp      dword ptr [ebp - 0x1d2]
004eb9aa 8b4b40                   mov       ecx, dword ptr [ebx + 0x40]
004eb9ad 8b01                     mov       eax, dword ptr [ecx]
004eb9af 3bc1                     cmp       eax, ecx
004eb9b1 894510                   mov       dword ptr [ebp + 0x10], eax
004eb9b4 7420                     je        0x4eb9d6
004eb9b6 8b400c                   mov       eax, dword ptr [eax + 0xc]
004eb9b9 83f804                   cmp       eax, 4
004eb9bc 7408                     je        0x4eb9c6
004eb9be c6840532feffff01         mov       byte ptr [ebp + eax - 0x1ce], 1
004eb9c6 8d4d10                   lea       ecx, [ebp + 0x10]
004eb9c9 e8f278f4ff               call      0x4332c0
004eb9ce 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004eb9d1 3b4340                   cmp       eax, dword ptr [ebx + 0x40]
004eb9d4 75e0                     jne       0x4eb9b6
004eb9d6 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004eb9d9 85c0                     test      eax, eax
004eb9db 7471                     je        0x4eba4e
004eb9dd c7451000000000           mov       dword ptr [ebp + 0x10], 0
004eb9e4 bf88000000               mov       edi, 0x88
004eb9e9 8da42400000000           lea       esp, [esp]
004eb9f0 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004eb9f3 8a841532feffff           mov       al, byte ptr [ebp + edx - 0x1ce]
004eb9fa 84c0                     test      al, al
004eb9fc 743e                     je        0x4eba3c
004eb9fe 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004eba01 8b01                     mov       eax, dword ptr [ecx]
004eba03 6a03                     push      3
004eba05 ff9044030000             call      dword ptr [eax + 0x344]
004eba0b 8d4c07e0                 lea       ecx, [edi + eax - 0x20]
004eba0f 8945fc                   mov       dword ptr [ebp - 4], eax
004eba12 e84966f1ff               call      0x402060
004eba17 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004eba1a 89451c                   mov       dword ptr [ebp + 0x1c], eax
004eba1d db451c                   fild      dword ptr [ebp + 0x1c]
004eba20 03cf                     add       ecx, edi
004eba22 d95d1c                   fstp      dword ptr [ebp + 0x1c]
004eba25 e88679f4ff               call      0x4333b0
004eba2a d84d1c                   fmul      dword ptr [ebp + 0x1c]
004eba2d e8125b7100               call      0xc01544
004eba32 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004eba35 8984959ffeffff           mov       dword ptr [ebp + edx*4 - 0x161], eax
004eba3c 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004eba3f 42                       inc       edx
004eba40 83c708                   add       edi, 8
004eba43 81ffa8000000             cmp       edi, 0xa8
004eba49 895510                   mov       dword ptr [ebp + 0x10], edx
004eba4c 7ca2                     jl        0x4eb9f0
004eba4e 8d8b38010000             lea       ecx, [ebx + 0x138]
004eba54 e80766f1ff               call      0x402060
004eba59 8d4b08                   lea       ecx, [ebx + 8]
004eba5c 888536feffff             mov       byte ptr [ebp - 0x1ca], al
004eba62 e8f965f1ff               call      0x402060
004eba67 894510                   mov       dword ptr [ebp + 0x10], eax
004eba6a db4510                   fild      dword ptr [ebp + 0x10]
004eba6d 8d8b00010000             lea       ecx, [ebx + 0x100]
004eba73 d99d37feffff             fstp      dword ptr [ebp - 0x1c9]
004eba79 e83279f4ff               call      0x4333b0
004eba7e 8d8ba4010000             lea       ecx, [ebx + 0x1a4]
004eba84 d99d3bfeffff             fstp      dword ptr [ebp - 0x1c5]
004eba8a e82179f4ff               call      0x4333b0
004eba8f d99d3ffeffff             fstp      dword ptr [ebp - 0x1c1]
004eba95 8d8bac010000             lea       ecx, [ebx + 0x1ac]
004eba9b e81079f4ff               call      0x4333b0
004ebaa0 d99d43feffff             fstp      dword ptr [ebp - 0x1bd]
004ebaa6 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebaac c7451000000000           mov       dword ptr [ebp + 0x10], 0
004ebab3 81c340010000             add       ebx, 0x140
004ebab9 8da42400000000           lea       esp, [esp]
004ebac0 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004ebac6 8b03                     mov       eax, dword ptr [ebx]
004ebac8 33c2                     xor       eax, edx
004ebaca 8b5304                   mov       edx, dword ptr [ebx + 4]
004ebacd 2bc3                     sub       eax, ebx
004ebacf 3bc2                     cmp       eax, edx
004ebad1 740e                     je        0x4ebae1
004ebad3 6a3f                     push      0x3f
004ebad5 53                       push      ebx
004ebad6 e8d5b56200               call      0xb170b0
004ebadb 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebae1 8b4304                   mov       eax, dword ptr [ebx + 4]
004ebae4 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ebae7 c1e002                   shl       eax, 2
004ebaea 03d0                     add       edx, eax
004ebaec 8bfa                     mov       edi, edx
004ebaee 333ddc012101             xor       edi, dword ptr [0x12101dc]
004ebaf4 333a                     xor       edi, dword ptr [edx]
004ebaf6 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004ebaf9 03c2                     add       eax, edx
004ebafb 8b10                     mov       edx, dword ptr [eax]
004ebafd 33d0                     xor       edx, eax
004ebaff 3315dc012101             xor       edx, dword ptr [0x12101dc]
004ebb05 3bfa                     cmp       edi, edx
004ebb07 740e                     je        0x4ebb17
004ebb09 6a40                     push      0x40
004ebb0b 53                       push      ebx
004ebb0c e89fb56200               call      0xb170b0
004ebb11 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebb17 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004ebb1a 89bc8547feffff           mov       dword ptr [ebp + eax*4 - 0x1b9], edi
004ebb21 40                       inc       eax
004ebb22 83c308                   add       ebx, 8
004ebb25 83f803                   cmp       eax, 3
004ebb28 894510                   mov       dword ptr [ebp + 0x10], eax
004ebb2b 7c93                     jl        0x4ebac0
004ebb2d 8b06                     mov       eax, dword ptr [esi]
004ebb2f 8bce                     mov       ecx, esi
004ebb31 ff90bc010000             call      dword ptr [eax + 0x1bc]
004ebb37 84c0                     test      al, al
004ebb39 0f84f7000000             je        0x4ebc36
004ebb3f 8b16                     mov       edx, dword ptr [esi]
004ebb41 8bce                     mov       ecx, esi
004ebb43 c645b601                 mov       byte ptr [ebp - 0x4a], 1
004ebb47 ff92ac020000             call      dword ptr [edx + 0x2ac]
004ebb4d 85c0                     test      eax, eax
004ebb4f 0f84e1000000             je        0x4ebc36
004ebb55 8b06                     mov       eax, dword ptr [esi]
004ebb57 8bce                     mov       ecx, esi
004ebb59 ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebb5f 8b10                     mov       edx, dword ptr [eax]
004ebb61 8bc8                     mov       ecx, eax
004ebb63 ff92d0010000             call      dword ptr [edx + 0x1d0]
004ebb69 8b16                     mov       edx, dword ptr [esi]
004ebb6b 8845b8                   mov       byte ptr [ebp - 0x48], al
004ebb6e 0fbe852dfeffff           movsx     eax, byte ptr [ebp - 0x1d3]
004ebb75 50                       push      eax
004ebb76 8bce                     mov       ecx, esi
004ebb78 ff92ac020000             call      dword ptr [edx + 0x2ac]
004ebb7e 8bc8                     mov       ecx, eax
004ebb80 e86b640300               call      0x521ff0
004ebb85 8b06                     mov       eax, dword ptr [esi]
004ebb87 d99d83feffff             fstp      dword ptr [ebp - 0x17d]
004ebb8d 8bce                     mov       ecx, esi
004ebb8f ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebb95 8b10                     mov       edx, dword ptr [eax]
004ebb97 8bc8                     mov       ecx, eax
004ebb99 ff928c010000             call      dword ptr [edx + 0x18c]
004ebb9f 85c0                     test      eax, eax
004ebba1 7446                     je        0x4ebbe9
004ebba3 8b06                     mov       eax, dword ptr [esi]
004ebba5 8bce                     mov       ecx, esi
004ebba7 ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebbad 8b10                     mov       edx, dword ptr [eax]
004ebbaf 8bc8                     mov       ecx, eax
004ebbb1 ff928c010000             call      dword ptr [edx + 0x18c]
004ebbb7 8b10                     mov       edx, dword ptr [eax]
004ebbb9 8bc8                     mov       ecx, eax
004ebbbb ff92d0010000             call      dword ptr [edx + 0x1d0]
004ebbc1 8845b7                   mov       byte ptr [ebp - 0x49], al
004ebbc4 8b06                     mov       eax, dword ptr [esi]
004ebbc6 8bce                     mov       ecx, esi
004ebbc8 ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebbce 8b10                     mov       edx, dword ptr [eax]
004ebbd0 6a00                     push      0
004ebbd2 8bc8                     mov       ecx, eax
004ebbd4 ff928c010000             call      dword ptr [edx + 0x18c]
004ebbda 50                       push      eax
004ebbdb e830d0f5ff               call      0x448c10
004ebbe0 d99d53feffff             fstp      dword ptr [ebp - 0x1ad]
004ebbe6 83c408                   add       esp, 8
004ebbe9 8b06                     mov       eax, dword ptr [esi]
004ebbeb 8bce                     mov       ecx, esi
004ebbed ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebbf3 8b880c070000             mov       ecx, dword ptr [eax + 0x70c]
004ebbf9 85c9                     test      ecx, ecx
004ebbfb 7439                     je        0x4ebc36
004ebbfd 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004ebc00 8b4118                   mov       eax, dword ptr [ecx + 0x18]
004ebc03 83f801                   cmp       eax, 1
004ebc06 750e                     jne       0x4ebc16
004ebc08 8b16                     mov       edx, dword ptr [esi]
004ebc0a 8bce                     mov       ecx, esi
004ebc0c ff92ac020000             call      dword ptr [edx + 0x2ac]
004ebc12 6a02                     push      2
004ebc14 eb10                     jmp       0x4ebc26
004ebc16 85c0                     test      eax, eax
004ebc18 751c                     jne       0x4ebc36
004ebc1a 8b06                     mov       eax, dword ptr [esi]
004ebc1c 8bce                     mov       ecx, esi
004ebc1e ff90ac020000             call      dword ptr [eax + 0x2ac]
004ebc24 6a01                     push      1
004ebc26 8b800c070000             mov       eax, dword ptr [eax + 0x70c]
004ebc2c 8bc8                     mov       ecx, eax
004ebc2e e84d96f6ff               call      0x455280
004ebc33 dd5daa                   fstp      qword ptr [ebp - 0x56]
004ebc36 8b16                     mov       edx, dword ptr [esi]
004ebc38 8bce                     mov       ecx, esi
004ebc3a ff92d8010000             call      dword ptr [edx + 0x1d8]
004ebc40 894510                   mov       dword ptr [ebp + 0x10], eax
004ebc43 db4510                   fild      dword ptr [ebp + 0x10]
004ebc46 8b06                     mov       eax, dword ptr [esi]
004ebc48 8bce                     mov       ecx, esi
004ebc4a d99d57feffff             fstp      dword ptr [ebp - 0x1a9]
004ebc50 ff90e8010000             call      dword ptr [eax + 0x1e8]
004ebc56 8b16                     mov       edx, dword ptr [esi]
004ebc58 894510                   mov       dword ptr [ebp + 0x10], eax
004ebc5b db4510                   fild      dword ptr [ebp + 0x10]
004ebc5e 8bce                     mov       ecx, esi
004ebc60 d99d5bfeffff             fstp      dword ptr [ebp - 0x1a5]
004ebc66 ff92dc010000             call      dword ptr [edx + 0x1dc]
004ebc6c 894510                   mov       dword ptr [ebp + 0x10], eax
004ebc6f db4510                   fild      dword ptr [ebp + 0x10]
004ebc72 8b06                     mov       eax, dword ptr [esi]
004ebc74 8bce                     mov       ecx, esi
004ebc76 d99d5ffeffff             fstp      dword ptr [ebp - 0x1a1]
004ebc7c ff90ec010000             call      dword ptr [eax + 0x1ec]
004ebc82 8b16                     mov       edx, dword ptr [esi]
004ebc84 894510                   mov       dword ptr [ebp + 0x10], eax
004ebc87 db4510                   fild      dword ptr [ebp + 0x10]
004ebc8a 8bce                     mov       ecx, esi
004ebc8c d99d63feffff             fstp      dword ptr [ebp - 0x19d]
004ebc92 ff92d4010000             call      dword ptr [edx + 0x1d4]
004ebc98 894510                   mov       dword ptr [ebp + 0x10], eax
004ebc9b db4510                   fild      dword ptr [ebp + 0x10]
004ebc9e 8b06                     mov       eax, dword ptr [esi]
004ebca0 8bce                     mov       ecx, esi
004ebca2 d99d67feffff             fstp      dword ptr [ebp - 0x199]
004ebca8 ff90e4010000             call      dword ptr [eax + 0x1e4]
004ebcae 8b16                     mov       edx, dword ptr [esi]
004ebcb0 894510                   mov       dword ptr [ebp + 0x10], eax
004ebcb3 db4510                   fild      dword ptr [ebp + 0x10]
004ebcb6 8bce                     mov       ecx, esi
004ebcb8 d99d6bfeffff             fstp      dword ptr [ebp - 0x195]
004ebcbe ff92f8010000             call      dword ptr [edx + 0x1f8]
004ebcc4 8b8618050000             mov       eax, dword ptr [esi + 0x518]
004ebcca d99d6ffeffff             fstp      dword ptr [ebp - 0x191]
004ebcd0 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004ebcd6 8b8e1c050000             mov       ecx, dword ptr [esi + 0x51c]
004ebcdc 8d9e18050000             lea       ebx, [esi + 0x518]
004ebce2 33c7                     xor       eax, edi
004ebce4 2bc3                     sub       eax, ebx
004ebce6 3bc1                     cmp       eax, ecx
004ebce8 740e                     je        0x4ebcf8
004ebcea 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebcf0 6a3f                     push      0x3f
004ebcf2 53                       push      ebx
004ebcf3 e8b8b36200               call      0xb170b0
004ebcf8 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebcfe 8b4304                   mov       eax, dword ptr [ebx + 4]
004ebd01 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ebd04 c1e002                   shl       eax, 2
004ebd07 8b3c02                   mov       edi, dword ptr [edx + eax]
004ebd0a 03d0                     add       edx, eax
004ebd0c 33fa                     xor       edi, edx
004ebd0e 333ddc012101             xor       edi, dword ptr [0x12101dc]
004ebd14 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004ebd17 03c2                     add       eax, edx
004ebd19 8bd0                     mov       edx, eax
004ebd1b 3315dc012101             xor       edx, dword ptr [0x12101dc]
004ebd21 3310                     xor       edx, dword ptr [eax]
004ebd23 3bfa                     cmp       edi, edx
004ebd25 7408                     je        0x4ebd2f
004ebd27 6a40                     push      0x40
004ebd29 53                       push      ebx
004ebd2a e881b36200               call      0xb170b0
004ebd2f d905581fcc00             fld       dword ptr [0xcc1f58]
004ebd35 897d10                   mov       dword ptr [ebp + 0x10], edi
004ebd38 d86510                   fsub      dword ptr [ebp + 0x10]
004ebd3b d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004ebd41 dfe0                     fnstsw    ax
004ebd43 f6c405                   test      ah, 5
004ebd46 7a0c                     jp        0x4ebd54
004ebd48 c78587feffff00000000     mov       dword ptr [ebp - 0x179], 0
004ebd52 eb13                     jmp       0x4ebd67
004ebd54 8bcb                     mov       ecx, ebx
004ebd56 e85576f4ff               call      0x4333b0
004ebd5b d82d581fcc00             fsubr     dword ptr [0xcc1f58]
004ebd61 d99d87feffff             fstp      dword ptr [ebp - 0x179]
004ebd67 8b06                     mov       eax, dword ptr [esi]
004ebd69 8bce                     mov       ecx, esi
004ebd6b ff90e0010000             call      dword ptr [eax + 0x1e0]
004ebd71 8b16                     mov       edx, dword ptr [esi]
004ebd73 8bce                     mov       ecx, esi
004ebd75 89858bfeffff             mov       dword ptr [ebp - 0x175], eax
004ebd7b ff92f0010000             call      dword ptr [edx + 0x1f0]
004ebd81 89858ffeffff             mov       dword ptr [ebp - 0x171], eax
004ebd87 8b06                     mov       eax, dword ptr [esi]
004ebd89 8bce                     mov       ecx, esi
004ebd8b ff90a8020000             call      dword ptr [eax + 0x2a8]
004ebd91 85c0                     test      eax, eax
004ebd93 741c                     je        0x4ebdb1
004ebd95 8b16                     mov       edx, dword ptr [esi]
004ebd97 8bce                     mov       ecx, esi
004ebd99 ff92a8020000             call      dword ptr [edx + 0x2a8]
004ebd9f 8b10                     mov       edx, dword ptr [eax]
004ebda1 8bc8                     mov       ecx, eax
004ebda3 ff92f8050000             call      dword ptr [edx + 0x5f8]
004ebda9 d99d93feffff             fstp      dword ptr [ebp - 0x16d]
004ebdaf eb0a                     jmp       0x4ebdbb
004ebdb1 c78593feffff00000000     mov       dword ptr [ebp - 0x16d], 0
004ebdbb 8b06                     mov       eax, dword ptr [esi]
004ebdbd 8bce                     mov       ecx, esi
004ebdbf ff90a4020000             call      dword ptr [eax + 0x2a4]
004ebdc5 85c0                     test      eax, eax
004ebdc7 7421                     je        0x4ebdea
004ebdc9 8b16                     mov       edx, dword ptr [esi]
004ebdcb 8bce                     mov       ecx, esi
004ebdcd ff92a4020000             call      dword ptr [edx + 0x2a4]
004ebdd3 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004ebdd6 8b10                     mov       edx, dword ptr [eax]
004ebdd8 51                       push      ecx
004ebdd9 56                       push      esi
004ebdda 8bc8                     mov       ecx, eax
004ebddc ff9200050000             call      dword ptr [edx + 0x500]
004ebde2 d99d97feffff             fstp      dword ptr [ebp - 0x169]
004ebde8 eb0a                     jmp       0x4ebdf4
004ebdea c78597feffff00000000     mov       dword ptr [ebp - 0x169], 0
004ebdf4 8b16                     mov       edx, dword ptr [esi]
004ebdf6 8bce                     mov       ecx, esi
004ebdf8 ff92a4020000             call      dword ptr [edx + 0x2a4]
004ebdfe 85c0                     test      eax, eax
004ebe00 7429                     je        0x4ebe2b
004ebe02 8b06                     mov       eax, dword ptr [esi]
004ebe04 8bce                     mov       ecx, esi
004ebe06 ff90a4020000             call      dword ptr [eax + 0x2a4]
004ebe0c 8b10                     mov       edx, dword ptr [eax]
004ebe0e 6a03                     push      3
004ebe10 8bc8                     mov       ecx, eax
004ebe12 ff9244030000             call      dword ptr [edx + 0x344]
004ebe18 8d8828030000             lea       ecx, [eax + 0x328]
004ebe1e e88d75f4ff               call      0x4333b0
004ebe23 d99d9bfeffff             fstp      dword ptr [ebp - 0x165]
004ebe29 eb0a                     jmp       0x4ebe35
004ebe2b c7859bfeffff00000000     mov       dword ptr [ebp - 0x165], 0
004ebe35 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004ebe38 85c0                     test      eax, eax
004ebe3a 0f8457060000             je        0x4ec497
004ebe40 8bf8                     mov       edi, eax
004ebe42 8b07                     mov       eax, dword ptr [edi]
004ebe44 6a03                     push      3
004ebe46 8bcf                     mov       ecx, edi
004ebe48 ff9044030000             call      dword ptr [eax + 0x344]
004ebe4e 8bc8                     mov       ecx, eax
004ebe50 e82b98fcff               call      0x4b5680
004ebe55 8985b3feffff             mov       dword ptr [ebp - 0x14d], eax
004ebe5b 8b17                     mov       edx, dword ptr [edi]
004ebe5d 6a03                     push      3
004ebe5f 8bcf                     mov       ecx, edi
004ebe61 ff9244030000             call      dword ptr [edx + 0x344]
004ebe67 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ebe6d 8bd8                     mov       ebx, eax
004ebe6f 8b8310030000             mov       eax, dword ptr [ebx + 0x310]
004ebe75 81c310030000             add       ebx, 0x310
004ebe7b 33c1                     xor       eax, ecx
004ebe7d 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004ebe80 2bc3                     sub       eax, ebx
004ebe82 3bc1                     cmp       eax, ecx
004ebe84 895d10                   mov       dword ptr [ebp + 0x10], ebx
004ebe87 740e                     je        0x4ebe97
004ebe89 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebe8f 6a3f                     push      0x3f
004ebe91 53                       push      ebx
004ebe92 e819b26200               call      0xb170b0
004ebe97 8b4304                   mov       eax, dword ptr [ebx + 4]
004ebe9a 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebea0 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ebea3 c1e002                   shl       eax, 2
004ebea6 03d0                     add       edx, eax
004ebea8 8bda                     mov       ebx, edx
004ebeaa 331ddc012101             xor       ebx, dword ptr [0x12101dc]
004ebeb0 331a                     xor       ebx, dword ptr [edx]
004ebeb2 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004ebeb5 03c2                     add       eax, edx
004ebeb7 8b10                     mov       edx, dword ptr [eax]
004ebeb9 33d0                     xor       edx, eax
004ebebb 3315dc012101             xor       edx, dword ptr [0x12101dc]
004ebec1 3bda                     cmp       ebx, edx
004ebec3 740b                     je        0x4ebed0
004ebec5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004ebec8 6a40                     push      0x40
004ebeca 50                       push      eax
004ebecb e8e0b16200               call      0xb170b0
004ebed0 899db7feffff             mov       dword ptr [ebp - 0x149], ebx
004ebed6 8b17                     mov       edx, dword ptr [edi]
004ebed8 6a03                     push      3
004ebeda 8bcf                     mov       ecx, edi
004ebedc ff9244030000             call      dword ptr [edx + 0x344]
004ebee2 8bc8                     mov       ecx, eax
004ebee4 81c1a8020000             add       ecx, 0x2a8
004ebeea e8c174f4ff               call      0x4333b0
004ebeef d99dbbfeffff             fstp      dword ptr [ebp - 0x145]
004ebef5 8b07                     mov       eax, dword ptr [edi]
004ebef7 6a03                     push      3
004ebef9 8bcf                     mov       ecx, edi
004ebefb ff9044030000             call      dword ptr [eax + 0x344]
004ebf01 8bc8                     mov       ecx, eax
004ebf03 e85898fcff               call      0x4b5760
004ebf08 8985bffeffff             mov       dword ptr [ebp - 0x141], eax
004ebf0e 8b17                     mov       edx, dword ptr [edi]
004ebf10 6a03                     push      3
004ebf12 8bcf                     mov       ecx, edi
004ebf14 ff9244030000             call      dword ptr [edx + 0x344]
004ebf1a 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ebf20 8bd8                     mov       ebx, eax
004ebf22 8b8320030000             mov       eax, dword ptr [ebx + 0x320]
004ebf28 81c320030000             add       ebx, 0x320
004ebf2e 33c1                     xor       eax, ecx
004ebf30 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004ebf33 2bc3                     sub       eax, ebx
004ebf35 3bc1                     cmp       eax, ecx
004ebf37 740e                     je        0x4ebf47
004ebf39 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebf3f 6a3f                     push      0x3f
004ebf41 53                       push      ebx
004ebf42 e869b16200               call      0xb170b0
004ebf47 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebf4d 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ebf50 8b4304                   mov       eax, dword ptr [ebx + 4]
004ebf53 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ebf59 c1e002                   shl       eax, 2
004ebf5c 03d0                     add       edx, eax
004ebf5e 895510                   mov       dword ptr [ebp + 0x10], edx
004ebf61 33d1                     xor       edx, ecx
004ebf63 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ebf66 3311                     xor       edx, dword ptr [ecx]
004ebf68 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebf6e 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
004ebf71 03c1                     add       eax, ecx
004ebf73 8b08                     mov       ecx, dword ptr [eax]
004ebf75 33c8                     xor       ecx, eax
004ebf77 330ddc012101             xor       ecx, dword ptr [0x12101dc]
004ebf7d 3bd1                     cmp       edx, ecx
004ebf7f 895510                   mov       dword ptr [ebp + 0x10], edx
004ebf82 740e                     je        0x4ebf92
004ebf84 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebf8a 6a40                     push      0x40
004ebf8c 53                       push      ebx
004ebf8d e81eb16200               call      0xb170b0
004ebf92 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004ebf95 8995c3feffff             mov       dword ptr [ebp - 0x13d], edx
004ebf9b 8b07                     mov       eax, dword ptr [edi]
004ebf9d 6a03                     push      3
004ebf9f 8bcf                     mov       ecx, edi
004ebfa1 ff9044030000             call      dword ptr [eax + 0x344]
004ebfa7 8bc8                     mov       ecx, eax
004ebfa9 81c1c0020000             add       ecx, 0x2c0
004ebfaf e8fc73f4ff               call      0x4333b0
004ebfb4 d99dc7feffff             fstp      dword ptr [ebp - 0x139]
004ebfba 8b17                     mov       edx, dword ptr [edi]
004ebfbc 6a03                     push      3
004ebfbe 8bcf                     mov       ecx, edi
004ebfc0 ff9244030000             call      dword ptr [edx + 0x344]
004ebfc6 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ebfcc 8d5838                   lea       ebx, [eax + 0x38]
004ebfcf 89451c                   mov       dword ptr [ebp + 0x1c], eax
004ebfd2 8b03                     mov       eax, dword ptr [ebx]
004ebfd4 33c1                     xor       eax, ecx
004ebfd6 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004ebfd9 2bc3                     sub       eax, ebx
004ebfdb 3bc1                     cmp       eax, ecx
004ebfdd 740e                     je        0x4ebfed
004ebfdf 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebfe5 6a3f                     push      0x3f
004ebfe7 53                       push      ebx
004ebfe8 e8c3b06200               call      0xb170b0
004ebfed 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ebff3 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ebff6 8b4304                   mov       eax, dword ptr [ebx + 4]
004ebff9 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ebfff c1e002                   shl       eax, 2
004ec002 03d0                     add       edx, eax
004ec004 895510                   mov       dword ptr [ebp + 0x10], edx
004ec007 33d1                     xor       edx, ecx
004ec009 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ec00c 3311                     xor       edx, dword ptr [ecx]
004ec00e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec014 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
004ec017 03c1                     add       eax, ecx
004ec019 8b08                     mov       ecx, dword ptr [eax]
004ec01b 33c8                     xor       ecx, eax
004ec01d 330ddc012101             xor       ecx, dword ptr [0x12101dc]
004ec023 3bd1                     cmp       edx, ecx
004ec025 895510                   mov       dword ptr [ebp + 0x10], edx
004ec028 740e                     je        0x4ec038
004ec02a 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec030 6a40                     push      0x40
004ec032 53                       push      ebx
004ec033 e878b06200               call      0xb170b0
004ec038 8b4d1c                   mov       ecx, dword ptr [ebp + 0x1c]
004ec03b 83c140                   add       ecx, 0x40
004ec03e 894d1c                   mov       dword ptr [ebp + 0x1c], ecx
004ec041 e86a73f4ff               call      0x4333b0
004ec046 da4d10                   fimul     dword ptr [ebp + 0x10]
004ec049 e8f6547100               call      0xc01544
004ec04e 3d24faffff               cmp       eax, 0xfffffa24
004ec053 7d09                     jge       0x4ec05e
004ec055 c7451024faffff           mov       dword ptr [ebp + 0x10], 0xfffffa24
004ec05c eb23                     jmp       0x4ec081
004ec05e 8bcb                     mov       ecx, ebx
004ec060 e8fb5ff1ff               call      0x402060
004ec065 8b4d1c                   mov       ecx, dword ptr [ebp + 0x1c]
004ec068 894510                   mov       dword ptr [ebp + 0x10], eax
004ec06b db4510                   fild      dword ptr [ebp + 0x10]
004ec06e d95d10                   fstp      dword ptr [ebp + 0x10]
004ec071 e83a73f4ff               call      0x4333b0
004ec076 d84d10                   fmul      dword ptr [ebp + 0x10]
004ec079 e8c6547100               call      0xc01544
004ec07e 894510                   mov       dword ptr [ebp + 0x10], eax
004ec081 db4510                   fild      dword ptr [ebp + 0x10]
004ec084 6a03                     push      3
004ec086 8bcf                     mov       ecx, edi
004ec088 d99dcbfeffff             fstp      dword ptr [ebp - 0x135]
004ec08e 8b17                     mov       edx, dword ptr [edi]
004ec090 ff9244030000             call      dword ptr [edx + 0x344]
004ec096 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec09c 8d5858                   lea       ebx, [eax + 0x58]
004ec09f 89451c                   mov       dword ptr [ebp + 0x1c], eax
004ec0a2 8b03                     mov       eax, dword ptr [ebx]
004ec0a4 33c1                     xor       eax, ecx
004ec0a6 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004ec0a9 2bc3                     sub       eax, ebx
004ec0ab 3bc1                     cmp       eax, ecx
004ec0ad 740e                     je        0x4ec0bd
004ec0af 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec0b5 6a3f                     push      0x3f
004ec0b7 53                       push      ebx
004ec0b8 e8f3af6200               call      0xb170b0
004ec0bd 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec0c3 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ec0c6 8b4304                   mov       eax, dword ptr [ebx + 4]
004ec0c9 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec0cf c1e002                   shl       eax, 2
004ec0d2 03d0                     add       edx, eax
004ec0d4 895510                   mov       dword ptr [ebp + 0x10], edx
004ec0d7 33d1                     xor       edx, ecx
004ec0d9 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ec0dc 3311                     xor       edx, dword ptr [ecx]
004ec0de 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec0e4 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
004ec0e7 03c1                     add       eax, ecx
004ec0e9 8b08                     mov       ecx, dword ptr [eax]
004ec0eb 33c8                     xor       ecx, eax
004ec0ed 330ddc012101             xor       ecx, dword ptr [0x12101dc]
004ec0f3 3bd1                     cmp       edx, ecx
004ec0f5 895510                   mov       dword ptr [ebp + 0x10], edx
004ec0f8 740e                     je        0x4ec108
004ec0fa 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec100 6a40                     push      0x40
004ec102 53                       push      ebx
004ec103 e8a8af6200               call      0xb170b0
004ec108 8b4d1c                   mov       ecx, dword ptr [ebp + 0x1c]
004ec10b 83c160                   add       ecx, 0x60
004ec10e 894d1c                   mov       dword ptr [ebp + 0x1c], ecx
004ec111 e89a72f4ff               call      0x4333b0
004ec116 da4d10                   fimul     dword ptr [ebp + 0x10]
004ec119 e826547100               call      0xc01544
004ec11e 3d24faffff               cmp       eax, 0xfffffa24
004ec123 7d09                     jge       0x4ec12e
004ec125 c7451024faffff           mov       dword ptr [ebp + 0x10], 0xfffffa24
004ec12c eb23                     jmp       0x4ec151
004ec12e 8bcb                     mov       ecx, ebx
004ec130 e82b5ff1ff               call      0x402060
004ec135 8b4d1c                   mov       ecx, dword ptr [ebp + 0x1c]
004ec138 894510                   mov       dword ptr [ebp + 0x10], eax
004ec13b db4510                   fild      dword ptr [ebp + 0x10]
004ec13e d95d10                   fstp      dword ptr [ebp + 0x10]
004ec141 e86a72f4ff               call      0x4333b0
004ec146 d84d10                   fmul      dword ptr [ebp + 0x10]
004ec149 e8f6537100               call      0xc01544
004ec14e 894510                   mov       dword ptr [ebp + 0x10], eax
004ec151 db4510                   fild      dword ptr [ebp + 0x10]
004ec154 8d9f10050000             lea       ebx, [edi + 0x510]
004ec15a 8bcb                     mov       ecx, ebx
004ec15c d99dcffeffff             fstp      dword ptr [ebp - 0x131]
004ec162 e84972f4ff               call      0x4333b0
004ec167 d82d581fcc00             fsubr     dword ptr [0xcc1f58]
004ec16d d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004ec173 dfe0                     fnstsw    ax
004ec175 f6c405                   test      ah, 5
004ec178 7a0c                     jp        0x4ec186
004ec17a c785d3feffff00000000     mov       dword ptr [ebp - 0x12d], 0
004ec184 eb13                     jmp       0x4ec199
004ec186 8bcb                     mov       ecx, ebx
004ec188 e82372f4ff               call      0x4333b0
004ec18d d82d581fcc00             fsubr     dword ptr [0xcc1f58]
004ec193 d99dd3feffff             fstp      dword ptr [ebp - 0x12d]
004ec199 8b17                     mov       edx, dword ptr [edi]
004ec19b 6a03                     push      3
004ec19d 8bcf                     mov       ecx, edi
004ec19f ff9244030000             call      dword ptr [edx + 0x344]
004ec1a5 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec1ab 8bd8                     mov       ebx, eax
004ec1ad 8b83a0020000             mov       eax, dword ptr [ebx + 0x2a0]
004ec1b3 8b93a4020000             mov       edx, dword ptr [ebx + 0x2a4]
004ec1b9 81c3a0020000             add       ebx, 0x2a0
004ec1bf 33c1                     xor       eax, ecx
004ec1c1 2bc3                     sub       eax, ebx
004ec1c3 3bc2                     cmp       eax, edx
004ec1c5 895d10                   mov       dword ptr [ebp + 0x10], ebx
004ec1c8 7414                     je        0x4ec1de
004ec1ca 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec1d0 6a3f                     push      0x3f
004ec1d2 53                       push      ebx
004ec1d3 e8d8ae6200               call      0xb170b0
004ec1d8 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec1de 8b4304                   mov       eax, dword ptr [ebx + 4]
004ec1e1 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004ec1e7 8b5244                   mov       edx, dword ptr [edx + 0x44]
004ec1ea c1e002                   shl       eax, 2
004ec1ed 8b1c02                   mov       ebx, dword ptr [edx + eax]
004ec1f0 03d0                     add       edx, eax
004ec1f2 33da                     xor       ebx, edx
004ec1f4 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004ec1fa 8b5248                   mov       edx, dword ptr [edx + 0x48]
004ec1fd 03c2                     add       eax, edx
004ec1ff 8b10                     mov       edx, dword ptr [eax]
004ec201 33d0                     xor       edx, eax
004ec203 33d9                     xor       ebx, ecx
004ec205 33d1                     xor       edx, ecx
004ec207 3bda                     cmp       ebx, edx
004ec209 7411                     je        0x4ec21c
004ec20b 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004ec20e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec214 6a40                     push      0x40
004ec216 50                       push      eax
004ec217 e894ae6200               call      0xb170b0
004ec21c 899dd7feffff             mov       dword ptr [ebp - 0x129], ebx
004ec222 8b17                     mov       edx, dword ptr [edi]
004ec224 6a03                     push      3
004ec226 8bcf                     mov       ecx, edi
004ec228 ff9244030000             call      dword ptr [edx + 0x344]
004ec22e 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec234 8bd8                     mov       ebx, eax
004ec236 8b83b8020000             mov       eax, dword ptr [ebx + 0x2b8]
004ec23c 81c3b8020000             add       ebx, 0x2b8
004ec242 33c1                     xor       eax, ecx
004ec244 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004ec247 2bc3                     sub       eax, ebx
004ec249 3bc1                     cmp       eax, ecx
004ec24b 740e                     je        0x4ec25b
004ec24d 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec253 6a3f                     push      0x3f
004ec255 53                       push      ebx
004ec256 e855ae6200               call      0xb170b0
004ec25b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec261 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004ec264 8b4304                   mov       eax, dword ptr [ebx + 4]
004ec267 c1e002                   shl       eax, 2
004ec26a 8d0c02                   lea       ecx, [edx + eax]
004ec26d 8b11                     mov       edx, dword ptr [ecx]
004ec26f 33d1                     xor       edx, ecx
004ec271 3315dc012101             xor       edx, dword ptr [0x12101dc]
004ec277 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec27d 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
004ec280 03c1                     add       eax, ecx
004ec282 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004ec288 894510                   mov       dword ptr [ebp + 0x10], eax
004ec28b 33c1                     xor       eax, ecx
004ec28d 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ec290 3301                     xor       eax, dword ptr [ecx]
004ec292 89551c                   mov       dword ptr [ebp + 0x1c], edx
004ec295 3bd0                     cmp       edx, eax
004ec297 740e                     je        0x4ec2a7
004ec299 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004ec29f 6a40                     push      0x40
004ec2a1 53                       push      ebx
004ec2a2 e809ae6200               call      0xb170b0
004ec2a7 8b551c                   mov       edx, dword ptr [ebp + 0x1c]
004ec2aa 8995dbfeffff             mov       dword ptr [ebp - 0x125], edx
004ec2b0 8b07                     mov       eax, dword ptr [edi]
004ec2b2 6a03                     push      3
004ec2b4 8bcf                     mov       ecx, edi
004ec2b6 ff9044030000             call      dword ptr [eax + 0x344]
004ec2bc 8bc8                     mov       ecx, eax
004ec2be 81c1f8020000             add       ecx, 0x2f8
004ec2c4 e8e770f4ff               call      0x4333b0
004ec2c9 d99de7feffff             fstp      dword ptr [ebp - 0x119]
004ec2cf 8b8f28020000             mov       ecx, dword ptr [edi + 0x228]
004ec2d5 8b8724020000             mov       eax, dword ptr [edi + 0x224]
004ec2db 3bc1                     cmp       eax, ecx
004ec2dd 740f                     je        0x4ec2ee
004ec2df 90                       nop       
004ec2e0 833812                   cmp       dword ptr [eax], 0x12
004ec2e3 7407                     je        0x4ec2ec
004ec2e5 83c004                   add       eax, 4
004ec2e8 3bc1                     cmp       eax, ecx
004ec2ea 75f4                     jne       0x4ec2e0
004ec2ec 3bc1                     cmp       eax, ecx
004ec2ee 0f95c1                   setne     cl
004ec2f1 888debfeffff             mov       byte ptr [ebp - 0x115], cl
004ec2f7 8b8f28020000             mov       ecx, dword ptr [edi + 0x228]
004ec2fd 8b8724020000             mov       eax, dword ptr [edi + 0x224]
004ec303 3bc1                     cmp       eax, ecx
004ec305 740e                     je        0x4ec315
004ec307 833813                   cmp       dword ptr [eax], 0x13
004ec30a 7407                     je        0x4ec313
004ec30c 83c004                   add       eax, 4
004ec30f 3bc1                     cmp       eax, ecx
004ec311 75f4                     jne       0x4ec307
004ec313 3bc1                     cmp       eax, ecx
004ec315 0f95c2                   setne     dl
004ec318 8bcf                     mov       ecx, edi
004ec31a 8895ecfeffff             mov       byte ptr [ebp - 0x114], dl
004ec320 e8fbeeffff               call      0x4eb220
004ec325 f7d8                     neg       eax
004ec327 1ac0                     sbb       al, al
004ec329 fec0                     inc       al
004ec32b 8885edfeffff             mov       byte ptr [ebp - 0x113], al
004ec331 8b07                     mov       eax, dword ptr [edi]
004ec333 6a09                     push      9
004ec335 ff9028040000             call      dword ptr [eax + 0x428]
004ec33b 85c0                     test      eax, eax
004ec33d 0f84b2000000             je        0x4ec3f5
004ec343 8b17                     mov       edx, dword ptr [edi]
004ec345 6a09                     push      9
004ec347 8bcf                     mov       ecx, edi
004ec349 ff9228040000             call      dword ptr [edx + 0x428]
004ec34f 8bf8                     mov       edi, eax
004ec351 85ff                     test      edi, edi
004ec353 0f849c000000             je        0x4ec3f5
004ec359 6a00                     push      0
004ec35b e8901d3c00               call      0x8ae0f0
004ec360 99                       cdq       
004ec361 b964000000               mov       ecx, 0x64
004ec366 f7f9                     idiv      ecx
004ec368 83c404                   add       esp, 4
004ec36b 8bcf                     mov       ecx, edi
004ec36d 895510                   mov       dword ptr [ebp + 0x10], edx
004ec370 db4510                   fild      dword ptr [ebp + 0x10]
004ec373 8b17                     mov       edx, dword ptr [edi]
004ec375 d95d10                   fstp      dword ptr [ebp + 0x10]
004ec378 ff92e4000000             call      dword ptr [edx + 0xe4]
004ec37e 8bc8                     mov       ecx, eax
