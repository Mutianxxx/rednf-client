00a27f60 55                       push      ebp
00a27f61 8bec                     mov       ebp, esp
00a27f63 51                       push      ecx
00a27f64 56                       push      esi
00a27f65 8bf1                     mov       esi, ecx
00a27f67 8b8698010000             mov       eax, dword ptr [esi + 0x198]
00a27f6d 85c0                     test      eax, eax
00a27f6f 57                       push      edi
00a27f70 0f84a3000000             je        0xa28019
00a27f76 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a27f7c 85c0                     test      eax, eax
00a27f7e 0f8495000000             je        0xa28019
00a27f84 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
00a27f8a 2bc8                     sub       ecx, eax
00a27f8c b843082184               mov       eax, 0x84210843
00a27f91 f7e9                     imul      ecx
00a27f93 03d1                     add       edx, ecx
00a27f95 c1fa06                   sar       edx, 6
00a27f98 8bc2                     mov       eax, edx
00a27f9a c1e81f                   shr       eax, 0x1f
00a27f9d 03c2                     add       eax, edx
00a27f9f 8945fc                   mov       dword ptr [ebp - 4], eax
00a27fa2 7475                     je        0xa28019
00a27fa4 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a27faa 8b08                     mov       ecx, dword ptr [eax]
00a27fac 85c9                     test      ecx, ecx
00a27fae 7469                     je        0xa28019
00a27fb0 e87b5c0e00               call      0xb0dc30
00a27fb5 85c0                     test      eax, eax
00a27fb7 7560                     jne       0xa28019
00a27fb9 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a27fbf 8b08                     mov       ecx, dword ptr [eax]
00a27fc1 8b11                     mov       edx, dword ptr [ecx]
00a27fc3 ff9290000000             call      dword ptr [edx + 0x90]
00a27fc9 84c0                     test      al, al
00a27fcb 754c                     jne       0xa28019
00a27fcd 53                       push      ebx
00a27fce 33ff                     xor       edi, edi
00a27fd0 33db                     xor       ebx, ebx
00a27fd2 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a27fd8 85c0                     test      eax, eax
00a27fda 743c                     je        0xa28018
00a27fdc 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
00a27fe2 2bc8                     sub       ecx, eax
00a27fe4 b843082184               mov       eax, 0x84210843
00a27fe9 f7e9                     imul      ecx
00a27feb 03d1                     add       edx, ecx
00a27fed c1fa06                   sar       edx, 6
00a27ff0 8bc2                     mov       eax, edx
00a27ff2 c1e81f                   shr       eax, 0x1f
00a27ff5 03c2                     add       eax, edx
00a27ff7 3bf8                     cmp       edi, eax
00a27ff9 731d                     jae       0xa28018
00a27ffb 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a28001 8b8e98010000             mov       ecx, dword ptr [esi + 0x198]
00a28007 03c3                     add       eax, ebx
00a28009 8b4004                   mov       eax, dword ptr [eax + 4]
00a2800c 50                       push      eax
00a2800d e86edd0c00               call      0xaf5d80
00a28012 47                       inc       edi
00a28013 83c37c                   add       ebx, 0x7c
00a28016 ebba                     jmp       0xa27fd2
00a28018 5b                       pop       ebx
00a28019 8b8e88010000             mov       ecx, dword ptr [esi + 0x188]
00a2801f 85c9                     test      ecx, ecx
00a28021 7407                     je        0xa2802a
00a28023 e8180ea7ff               call      0x498e40
00a28028 eb06                     jmp       0xa28030
00a2802a 8a8639010000             mov       al, byte ptr [esi + 0x139]
00a28030 84c0                     test      al, al
00a28032 750b                     jne       0xa2803f
00a28034 8bce                     mov       ecx, esi
00a28036 e855bcffff               call      0xa23c90
00a2803b 84c0                     test      al, al
00a2803d 7509                     jne       0xa28048
00a2803f 83be24010000ff           cmp       dword ptr [esi + 0x124], -1
00a28046 750e                     jne       0xa28056
00a28048 8bce                     mov       ecx, esi
00a2804a e871fdffff               call      0xa27dc0
00a2804f 8bce                     mov       ecx, esi
00a28051 e8fac8ffff               call      0xa24950
00a28056 8b8680010000             mov       eax, dword ptr [esi + 0x180]
00a2805c 8b38                     mov       edi, dword ptr [eax]
00a2805e 3bf8                     cmp       edi, eax
00a28060 7416                     je        0xa28078
00a28062 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
00a28065 85c9                     test      ecx, ecx
00a28067 7405                     je        0xa2806e
00a28069 e8f2feffff               call      0xa27f60
00a2806e 8b3f                     mov       edi, dword ptr [edi]
00a28070 3bbe80010000             cmp       edi, dword ptr [esi + 0x180]
00a28076 75ea                     jne       0xa28062
00a28078 5f                       pop       edi
00a28079 5e                       pop       esi
00a2807a 8be5                     mov       esp, ebp
00a2807c 5d                       pop       ebp
00a2807d c3                       ret       
00a2807e cc                       int3      
00a2807f cc                       int3      
00a28080 55                       push      ebp
00a28081 8bec                     mov       ebp, esp
00a28083 8b4508                   mov       eax, dword ptr [ebp + 8]
00a28086 56                       push      esi
00a28087 8bf1                     mov       esi, ecx
00a28089 50                       push      eax
00a2808a 8d8e94000000             lea       ecx, [esi + 0x94]
00a28090 e86b3b0000               call      0xa2bc00
00a28095 8bce                     mov       ecx, esi
00a28097 e8c4f2ffff               call      0xa27360
00a2809c 5e                       pop       esi
00a2809d 5d                       pop       ebp
00a2809e c20400                   ret       4
00a280a1 cc                       int3      
00a280a2 cc                       int3      
00a280a3 cc                       int3      
00a280a4 cc                       int3      
00a280a5 cc                       int3      
00a280a6 cc                       int3      
00a280a7 cc                       int3      
00a280a8 cc                       int3      
00a280a9 cc                       int3      
00a280aa cc                       int3      
00a280ab cc                       int3      
00a280ac cc                       int3      
00a280ad cc                       int3      
00a280ae cc                       int3      
00a280af cc                       int3      
00a280b0 55                       push      ebp
00a280b1 8bec                     mov       ebp, esp
00a280b3 56                       push      esi
00a280b4 57                       push      edi
00a280b5 8bf1                     mov       esi, ecx
00a280b7 6a01                     push      1
00a280b9 8d8e94000000             lea       ecx, [esi + 0x94]
00a280bf e83c3b0000               call      0xa2bc00
00a280c4 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a280ca 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a280cd 8908                     mov       dword ptr [eax], ecx
00a280cf 8b4114                   mov       eax, dword ptr [ecx + 0x14]
00a280d2 8bbe98000000             mov       edi, dword ptr [esi + 0x98]
00a280d8 99                       cdq       
00a280d9 2bc2                     sub       eax, edx
00a280db d1f8                     sar       eax, 1
00a280dd f7d8                     neg       eax
00a280df 894708                   mov       dword ptr [edi + 8], eax
00a280e2 8b4118                   mov       eax, dword ptr [ecx + 0x18]
00a280e5 8bbe98000000             mov       edi, dword ptr [esi + 0x98]
00a280eb 99                       cdq       
00a280ec 2bc2                     sub       eax, edx
00a280ee d1f8                     sar       eax, 1
00a280f0 f7d8                     neg       eax
00a280f2 8bce                     mov       ecx, esi
00a280f4 89470c                   mov       dword ptr [edi + 0xc], eax
00a280f7 e864f2ffff               call      0xa27360
00a280fc 5f                       pop       edi
00a280fd 5e                       pop       esi
00a280fe 5d                       pop       ebp
00a280ff c20400                   ret       4
00a28102 cc                       int3      
00a28103 cc                       int3      
00a28104 cc                       int3      
00a28105 cc                       int3      
00a28106 cc                       int3      
00a28107 cc                       int3      
00a28108 cc                       int3      
00a28109 cc                       int3      
00a2810a cc                       int3      
00a2810b cc                       int3      
00a2810c cc                       int3      
00a2810d cc                       int3      
00a2810e cc                       int3      
00a2810f cc                       int3      
00a28110 55                       push      ebp
00a28111 8bec                     mov       ebp, esp
00a28113 51                       push      ecx
00a28114 8a4508                   mov       al, byte ptr [ebp + 8]
00a28117 53                       push      ebx
00a28118 56                       push      esi
00a28119 8bf1                     mov       esi, ecx
00a2811b 8a9e39010000             mov       bl, byte ptr [esi + 0x139]
00a28121 3ac3                     cmp       al, bl
00a28123 7460                     je        0xa28185
00a28125 84c0                     test      al, al
00a28127 7416                     je        0xa2813f
00a28129 e832feffff               call      0xa27f60
00a2812e 8a4d08                   mov       cl, byte ptr [ebp + 8]
00a28131 888e39010000             mov       byte ptr [esi + 0x139], cl
00a28137 5e                       pop       esi
00a28138 5b                       pop       ebx
00a28139 8be5                     mov       esp, ebp
00a2813b 5d                       pop       ebp
00a2813c c20400                   ret       4
00a2813f 8b8e88010000             mov       ecx, dword ptr [esi + 0x188]
00a28145 85c9                     test      ecx, ecx
00a28147 57                       push      edi
00a28148 7409                     je        0xa28153
00a2814a e8b128aaff               call      0x4caa00
00a2814f 8bf8                     mov       edi, eax
00a28151 eb06                     jmp       0xa28159
00a28153 8bbe8c000000             mov       edi, dword ptr [esi + 0x8c]
00a28159 8bce                     mov       ecx, esi
00a2815b 885dfc                   mov       byte ptr [ebp - 4], bl
00a2815e e8fdf1ffff               call      0xa27360
00a28163 8bce                     mov       ecx, esi
00a28165 89be88000000             mov       dword ptr [esi + 0x88], edi
00a2816b e820bbffff               call      0xa23c90
00a28170 8b45fc                   mov       eax, dword ptr [ebp - 4]
00a28173 50                       push      eax
00a28174 8bce                     mov       ecx, esi
00a28176 e895ffffff               call      0xa28110
00a2817b 8a4d08                   mov       cl, byte ptr [ebp + 8]
00a2817e 5f                       pop       edi
00a2817f 888e39010000             mov       byte ptr [esi + 0x139], cl
00a28185 5e                       pop       esi
00a28186 5b                       pop       ebx
00a28187 8be5                     mov       esp, ebp
00a28189 5d                       pop       ebp
00a2818a c20400                   ret       4
00a2818d cc                       int3      
00a2818e cc                       int3      
00a2818f cc                       int3      
00a28190 55                       push      ebp
00a28191 8bec                     mov       ebp, esp
00a28193 53                       push      ebx
00a28194 8bd9                     mov       ebx, ecx
00a28196 8b8380010000             mov       eax, dword ptr [ebx + 0x180]
00a2819c 56                       push      esi
00a2819d 8b30                     mov       esi, dword ptr [eax]
00a2819f 3bf0                     cmp       esi, eax
00a281a1 7474                     je        0xa28217
00a281a3 57                       push      edi
00a281a4 8b4608                   mov       eax, dword ptr [esi + 8]
00a281a7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a281aa 3bc1                     cmp       eax, ecx
00a281ac 755c                     jne       0xa2820a
00a281ae 8b460c                   mov       eax, dword ptr [esi + 0xc]
00a281b1 c7808801000000000000     mov       dword ptr [eax + 0x188], 0
00a281bb 8b7e0c                   mov       edi, dword ptr [esi + 0xc]
00a281be 85ff                     test      edi, edi
00a281c0 7410                     je        0xa281d2
00a281c2 8bcf                     mov       ecx, edi
00a281c4 e807089eff               call      0x4089d0
00a281c9 57                       push      edi
00a281ca e8819d9dff               call      0x401f50
00a281cf 83c404                   add       esp, 4
00a281d2 c7460c00000000           mov       dword ptr [esi + 0xc], 0
00a281d9 3bb380010000             cmp       esi, dword ptr [ebx + 0x180]
00a281df 8b3e                     mov       edi, dword ptr [esi]
00a281e1 7423                     je        0xa28206
00a281e3 8b4604                   mov       eax, dword ptr [esi + 4]
00a281e6 8938                     mov       dword ptr [eax], edi
00a281e8 8b0e                     mov       ecx, dword ptr [esi]
00a281ea 8b5604                   mov       edx, dword ptr [esi + 4]
00a281ed 56                       push      esi
00a281ee 895104                   mov       dword ptr [ecx + 4], edx
00a281f1 e8e77d1d00               call      0xbfffdd
00a281f6 8b8384010000             mov       eax, dword ptr [ebx + 0x184]
00a281fc 83c404                   add       esp, 4
00a281ff 48                       dec       eax
00a28200 898384010000             mov       dword ptr [ebx + 0x184], eax
00a28206 8bf7                     mov       esi, edi
00a28208 eb04                     jmp       0xa2820e
00a2820a 7f0a                     jg        0xa28216
00a2820c 8b36                     mov       esi, dword ptr [esi]
00a2820e 3bb380010000             cmp       esi, dword ptr [ebx + 0x180]
00a28214 758e                     jne       0xa281a4
00a28216 5f                       pop       edi
00a28217 5e                       pop       esi
00a28218 5b                       pop       ebx
00a28219 5d                       pop       ebp
00a2821a c20400                   ret       4
00a2821d cc                       int3      
00a2821e cc                       int3      
00a2821f cc                       int3      
00a28220 55                       push      ebp
00a28221 8bec                     mov       ebp, esp
00a28223 53                       push      ebx
00a28224 8bd9                     mov       ebx, ecx
00a28226 8b8380010000             mov       eax, dword ptr [ebx + 0x180]
00a2822c 56                       push      esi
00a2822d 8b30                     mov       esi, dword ptr [eax]
00a2822f 3bf0                     cmp       esi, eax
00a28231 746e                     je        0xa282a1
00a28233 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a28236 394e0c                   cmp       dword ptr [esi + 0xc], ecx
00a28239 740c                     je        0xa28247
00a2823b 8b36                     mov       esi, dword ptr [esi]
00a2823d 3bf0                     cmp       esi, eax
00a2823f 75f5                     jne       0xa28236
00a28241 5e                       pop       esi
00a28242 5b                       pop       ebx
00a28243 5d                       pop       ebp
00a28244 c20400                   ret       4
00a28247 8b460c                   mov       eax, dword ptr [esi + 0xc]
00a2824a 57                       push      edi
00a2824b c7808801000000000000     mov       dword ptr [eax + 0x188], 0
00a28255 8b7e0c                   mov       edi, dword ptr [esi + 0xc]
00a28258 85ff                     test      edi, edi
00a2825a 7410                     je        0xa2826c
00a2825c 8bcf                     mov       ecx, edi
00a2825e e86d079eff               call      0x4089d0
00a28263 57                       push      edi
00a28264 e8e79c9dff               call      0x401f50
00a28269 83c404                   add       esp, 4
00a2826c c7460c00000000           mov       dword ptr [esi + 0xc], 0
00a28273 3bb380010000             cmp       esi, dword ptr [ebx + 0x180]
00a28279 5f                       pop       edi
00a2827a 7425                     je        0xa282a1
00a2827c 8b4604                   mov       eax, dword ptr [esi + 4]
00a2827f 8b0e                     mov       ecx, dword ptr [esi]
00a28281 8908                     mov       dword ptr [eax], ecx
00a28283 8b16                     mov       edx, dword ptr [esi]
00a28285 8b4604                   mov       eax, dword ptr [esi + 4]
00a28288 56                       push      esi
00a28289 894204                   mov       dword ptr [edx + 4], eax
00a2828c e84c7d1d00               call      0xbfffdd
00a28291 8b8384010000             mov       eax, dword ptr [ebx + 0x184]
00a28297 83c404                   add       esp, 4
00a2829a 48                       dec       eax
00a2829b 898384010000             mov       dword ptr [ebx + 0x184], eax
00a282a1 5e                       pop       esi
00a282a2 5b                       pop       ebx
00a282a3 5d                       pop       ebp
00a282a4 c20400                   ret       4
00a282a7 cc                       int3      
00a282a8 cc                       int3      
00a282a9 cc                       int3      
00a282aa cc                       int3      
00a282ab cc                       int3      
00a282ac cc                       int3      
00a282ad cc                       int3      
00a282ae cc                       int3      
00a282af cc                       int3      
00a282b0 56                       push      esi
00a282b1 57                       push      edi
00a282b2 8bf9                     mov       edi, ecx
00a282b4 8b8780010000             mov       eax, dword ptr [edi + 0x180]
00a282ba 8b30                     mov       esi, dword ptr [eax]
00a282bc 3bf0                     cmp       esi, eax
00a282be 743b                     je        0xa282fb
00a282c0 53                       push      ebx
00a282c1 8b460c                   mov       eax, dword ptr [esi + 0xc]
00a282c4 85c0                     test      eax, eax
00a282c6 7428                     je        0xa282f0
00a282c8 c7                       .byte     0xc7
00a282c9 80880100000000           or        byte ptr [eax + 1], 0
