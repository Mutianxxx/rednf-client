008898b0 3807                     cmp       byte ptr [edi], al
008898b2 0000                     add       byte ptr [eax], al
008898b4 8bce                     mov       ecx, esi
008898b6 e8759db7ff               call      0x403630
008898bb 8d55ec                   lea       edx, [ebp - 0x14]
008898be 52                       push      edx
008898bf e81c6cfaff               call      0x8304e0
008898c4 83c404                   add       esp, 4
008898c7 84c0                     test      al, al
008898c9 0f84dc190000             je        0x88b2ab
008898cf 90                       nop       
008898d0 8d45ec                   lea       eax, [ebp - 0x14]
008898d3 50                       push      eax
008898d4 8bce                     mov       ecx, esi
008898d6 e805a3b7ff               call      0x403be0
008898db 8d4dec                   lea       ecx, [ebp - 0x14]
008898de 51                       push      ecx
008898df e8fc6bfaff               call      0x8304e0
008898e4 83c404                   add       esp, 4
008898e7 84c0                     test      al, al
008898e9 75e5                     jne       0x8898d0
008898eb e9bb190000               jmp       0x88b2ab
008898f0 68e434e200               push      0xe234e4
008898f5 56                       push      esi
008898f6 e8d5aeb7ff               call      0x4047d0
008898fb 83c408                   add       esp, 8
008898fe 84c0                     test      al, al
00889900 7417                     je        0x889919
00889902 8b5508                   mov       edx, dword ptr [ebp + 8]
00889905 81c248070000             add       edx, 0x748
0088990b 52                       push      edx
0088990c e8cf6bfaff               call      0x8304e0
00889911 83c404                   add       esp, 4
00889914 e992190000               jmp       0x88b2ab
00889919 687c4ee200               push      0xe24e7c
0088991e 56                       push      esi
0088991f e8acaeb7ff               call      0x4047d0
00889924 83c408                   add       esp, 8
00889927 84c0                     test      al, al
00889929 7416                     je        0x889941
0088992b 8b4508                   mov       eax, dword ptr [ebp + 8]
0088992e 0568070000               add       eax, 0x768
00889933 50                       push      eax
00889934 e8a76bfaff               call      0x8304e0
00889939 83c404                   add       esp, 4
0088993c e96a190000               jmp       0x88b2ab
00889941 685cf1e100               push      0xe1f15c
00889946 56                       push      esi
00889947 e884aeb7ff               call      0x4047d0
0088994c 83c408                   add       esp, 8
0088994f 84c0                     test      al, al
00889951 7444                     je        0x889997
00889953 8b7508                   mov       esi, dword ptr [ebp + 8]
00889956 81c66c070000             add       esi, 0x76c
0088995c 8bce                     mov       ecx, esi
0088995e e8cd9cb7ff               call      0x403630
00889963 8d4dec                   lea       ecx, [ebp - 0x14]
00889966 51                       push      ecx
00889967 e8746bfaff               call      0x8304e0
0088996c 83c404                   add       esp, 4
0088996f 84c0                     test      al, al
00889971 0f8434190000             je        0x88b2ab
00889977 8d55ec                   lea       edx, [ebp - 0x14]
0088997a 52                       push      edx
0088997b 8bce                     mov       ecx, esi
0088997d e85ea2b7ff               call      0x403be0
00889982 8d45ec                   lea       eax, [ebp - 0x14]
00889985 50                       push      eax
00889986 e8556bfaff               call      0x8304e0
0088998b 83c404                   add       esp, 4
0088998e 84c0                     test      al, al
00889990 75e5                     jne       0x889977
00889992 e914190000               jmp       0x88b2ab
00889997 68ec33e200               push      0xe233ec
0088999c 56                       push      esi
0088999d e8                       .byte     0xe8
0088999e 2eae                     scasb     al, byte ptr es:[edi]
