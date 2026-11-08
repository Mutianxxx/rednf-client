004eabf0 55                       push      ebp
004eabf1 8bec                     mov       ebp, esp
004eabf3 83ec10                   sub       esp, 0x10
004eabf6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004eabf9 85c9                     test      ecx, ecx
004eabfb 0f84f5030000             je        0x4eaff6
004eac01 57                       push      edi
004eac02 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004eac05 85ff                     test      edi, edi
004eac07 0f84e8030000             je        0x4eaff5
004eac0d 8b01                     mov       eax, dword ptr [ecx]
004eac0f 56                       push      esi
004eac10 ff90c8010000             call      dword ptr [eax + 0x1c8]
004eac16 8b17                     mov       edx, dword ptr [edi]
004eac18 8bcf                     mov       ecx, edi
004eac1a 8bf0                     mov       esi, eax
004eac1c ff92c8010000             call      dword ptr [edx + 0x1c8]
004eac22 8bf8                     mov       edi, eax
004eac24 8a4514                   mov       al, byte ptr [ebp + 0x14]
004eac27 84c0                     test      al, al
004eac29 7413                     je        0x4eac3e
004eac2b 8b07                     mov       eax, dword ptr [edi]
004eac2d 56                       push      esi
004eac2e 8bcf                     mov       ecx, edi
004eac30 ff90ec020000             call      dword ptr [eax + 0x2ec]
004eac36 84c0                     test      al, al
004eac38 0f84b6030000             je        0x4eaff4
004eac3e 8a4518                   mov       al, byte ptr [ebp + 0x18]
004eac41 84c0                     test      al, al
004eac43 53                       push      ebx
004eac44 c6450b00                 mov       byte ptr [ebp + 0xb], 0
004eac48 0f8431020000             je        0x4eae7f
004eac4e 8b17                     mov       edx, dword ptr [edi]
004eac50 6a11                     push      0x11
004eac52 8bcf                     mov       ecx, edi
004eac54 ff522c                   call      dword ptr [edx + 0x2c]
004eac57 84c0                     test      al, al
004eac59 0f8420020000             je        0x4eae7f
004eac5f 8b06                     mov       eax, dword ptr [esi]
004eac61 8bce                     mov       ecx, esi
004eac63 ff909c010000             call      dword ptr [eax + 0x19c]
004eac69 8bd8                     mov       ebx, eax
004eac6b 8d8b08010000             lea       ecx, [ebx + 0x108]
004eac71 e83a87f4ff               call      0x4333b0
004eac76 d80578b5cc00             fadd      dword ptr [0xccb578]
004eac7c a088590001               mov       al, byte ptr [0x1005988]
004eac81 84c0                     test      al, al
004eac83 d95dfc                   fstp      dword ptr [ebp - 4]
004eac86 7423                     je        0x4eacab
004eac88 d945fc                   fld       dword ptr [ebp - 4]
004eac8b 83ec08                   sub       esp, 8
004eac8e 8d8e08020000             lea       ecx, [esi + 0x208]
004eac94 dd1c24                   fstp      qword ptr [esp]
004eac97 e854845600               call      0xa530f0
004eac9c 50                       push      eax
004eac9d 686c4ecd00               push      0xcd4e6c
004eaca2 ff15bc2eff00             call      dword ptr [0xff2ebc]
004eaca8 83c410                   add       esp, 0x10
004eacab 8d8b10010000             lea       ecx, [ebx + 0x110]
004eacb1 e8aa73f1ff               call      0x402060
004eacb6 85c0                     test      eax, eax
004eacb8 742a                     je        0x4eace4
004eacba 8b16                     mov       edx, dword ptr [esi]
004eacbc 8bce                     mov       ecx, esi
004eacbe ff92ac010000             call      dword ptr [edx + 0x1ac]
004eacc4 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004eacc7 83f901                   cmp       ecx, 1
004eacca 7e18                     jle       0x4eace4
004eaccc 8d4101                   lea       eax, [ecx + 1]
004eaccf 0fafc1                   imul      eax, ecx
004eacd2 99                       cdq       
004eacd3 2bc2                     sub       eax, edx
004eacd5 d1f8                     sar       eax, 1
004eacd7 48                       dec       eax
004eacd8 8945f4                   mov       dword ptr [ebp - 0xc], eax
004eacdb db45f4                   fild      dword ptr [ebp - 0xc]
004eacde d845fc                   fadd      dword ptr [ebp - 4]
004eace1 d95dfc                   fstp      dword ptr [ebp - 4]
004eace4 8b07                     mov       eax, dword ptr [edi]
004eace6 8bcf                     mov       ecx, edi
004eace8 ff90fc020000             call      dword ptr [eax + 0x2fc]
004eacee 83f832                   cmp       eax, 0x32
004eacf1 7d26                     jge       0x4ead19
004eacf3 8b16                     mov       edx, dword ptr [esi]
004eacf5 8bce                     mov       ecx, esi
004eacf7 ff92a4020000             call      dword ptr [edx + 0x2a4]
004eacfd 8bd8                     mov       ebx, eax
004eacff 8b07                     mov       eax, dword ptr [edi]
004ead01 8bcf                     mov       ecx, edi
004ead03 ff9000030000             call      dword ptr [eax + 0x300]
004ead09 3bc3                     cmp       eax, ebx
004ead0b 740c                     je        0x4ead19
004ead0d d945fc                   fld       dword ptr [ebp - 4]
004ead10 d82570e9cc00             fsub      dword ptr [0xcce970]
004ead16 d95dfc                   fstp      dword ptr [ebp - 4]
004ead19 56                       push      esi
004ead1a 57                       push      edi
004ead1b e8d0e3ffff               call      0x4e90f0
004ead20 83c408                   add       esp, 8
004ead23 84c0                     test      al, al
004ead25 740c                     je        0x4ead33
004ead27 d945fc                   fld       dword ptr [ebp - 4]
004ead2a d82570e9cc00             fsub      dword ptr [0xcce970]
004ead30 d95dfc                   fstp      dword ptr [ebp - 4]
004ead33 8b16                     mov       edx, dword ptr [esi]
004ead35 8bce                     mov       ecx, esi
004ead37 c745f400000000           mov       dword ptr [ebp - 0xc], 0
004ead3e ff92bc010000             call      dword ptr [edx + 0x1bc]
004ead44 84c0                     test      al, al
004ead46 8b06                     mov       eax, dword ptr [esi]
004ead48 8bce                     mov       ecx, esi
004ead4a 741d                     je        0x4ead69
004ead4c ff90ac020000             call      dword ptr [eax + 0x2ac]
004ead52 85c0                     test      eax, eax
004ead54 7443                     je        0x4ead99
004ead56 8b16                     mov       edx, dword ptr [esi]
004ead58 8bce                     mov       ecx, esi
004ead5a ff92ac020000             call      dword ptr [edx + 0x2ac]
004ead60 8bc8                     mov       ecx, eax
004ead62 e879720300               call      0x521fe0
004ead67 eb2d                     jmp       0x4ead96
004ead69 ff90a4020000             call      dword ptr [eax + 0x2a4]
004ead6f 85c0                     test      eax, eax
004ead71 7426                     je        0x4ead99
004ead73 8b16                     mov       edx, dword ptr [esi]
004ead75 8bce                     mov       ecx, esi
004ead77 ff92a4020000             call      dword ptr [edx + 0x2a4]
004ead7d 8b10                     mov       edx, dword ptr [eax]
004ead7f 6a03                     push      3
004ead81 8bc8                     mov       ecx, eax
004ead83 ff9244030000             call      dword ptr [edx + 0x344]
004ead89 8bc8                     mov       ecx, eax
004ead8b 81c1e8020000             add       ecx, 0x2e8
004ead91 e81a86f4ff               call      0x4333b0
004ead96 d95df4                   fstp      dword ptr [ebp - 0xc]
004ead99 8b07                     mov       eax, dword ptr [edi]
004ead9b 56                       push      esi
004ead9c 8bcf                     mov       ecx, edi
004ead9e ff90c8030000             call      dword ptr [eax + 0x3c8]
004eada4 d845f4                   fadd      dword ptr [ebp - 0xc]
004eada7 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004eadad 6aff                     push      -1
004eadaf d95df4                   fstp      dword ptr [ebp - 0xc]
004eadb2 e839fef4ff               call      0x43abf0
004eadb7 84c0                     test      al, al
004eadb9 750f                     jne       0x4eadca
004eadbb 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004eadc1 e84af5f4ff               call      0x43a310
004eadc6 84c0                     test      al, al
004eadc8 742d                     je        0x4eadf7
004eadca 8bcf                     mov       ecx, edi
004eadcc e8bf370000               call      0x4ee590
004eadd1 83f8ff                   cmp       eax, -1
004eadd4 7421                     je        0x4eadf7
004eadd6 3d10270000               cmp       eax, 0x2710
004eaddb 7d1a                     jge       0x4eadf7
004eaddd 6810270000               push      0x2710
004eade2 50                       push      eax
004eade3 680000803f               push      0x3f800000
004eade8 6a00                     push      0
004eadea e8c1eb6100               call      0xb099b0
004eadef d84df4                   fmul      dword ptr [ebp - 0xc]
004eadf2 83c410                   add       esp, 0x10
004eadf5 eb03                     jmp       0x4eadfa
004eadf7 d945f4                   fld       dword ptr [ebp - 0xc]
004eadfa d845fc                   fadd      dword ptr [ebp - 4]
004eadfd a088590001               mov       al, byte ptr [0x1005988]
004eae02 84c0                     test      al, al
004eae04 d95dfc                   fstp      dword ptr [ebp - 4]
004eae07 7431                     je        0x4eae3a
004eae09 8d8e08020000             lea       ecx, [esi + 0x208]
004eae0f e8dc825600               call      0xa530f0
004eae14 d945fc                   fld       dword ptr [ebp - 4]
004eae17 83ec08                   sub       esp, 8
004eae1a 8d8f08020000             lea       ecx, [edi + 0x208]
004eae20 dd1c24                   fstp      qword ptr [esp]
004eae23 8bd8                     mov       ebx, eax
004eae25 e8c6825600               call      0xa530f0
004eae2a 50                       push      eax
004eae2b 53                       push      ebx
004eae2c 68304ecd00               push      0xcd4e30
004eae31 ff15bc2eff00             call      dword ptr [0xff2ebc]
004eae37 83c414                   add       esp, 0x14
004eae3a d945fc                   fld       dword ptr [ebp - 4]
004eae3d d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004eae43 dfe0                     fnstsw    ax
004eae45 f6c441                   test      ah, 0x41
004eae48 7535                     jne       0x4eae7f
004eae4a 6a00                     push      0
004eae4c e89f323c00               call      0x8ae0f0
004eae51 99                       cdq       
004eae52 b910270000               mov       ecx, 0x2710
004eae57 f7f9                     idiv      ecx
004eae59 83c404                   add       esp, 4
004eae5c 8955f4                   mov       dword ptr [ebp - 0xc], edx
004eae5f db45f4                   fild      dword ptr [ebp - 0xc]
004eae62 d945fc                   fld       dword ptr [ebp - 4]
004eae65 d80dd8b9cc00             fmul      dword ptr [0xccb9d8]
004eae6b ded9                     fcompp    
004eae6d dfe0                     fnstsw    ax
004eae6f f6c441                   test      ah, 0x41
004eae72 750b                     jne       0x4eae7f
004eae74 8bcf                     mov       ecx, edi
004eae76 e8a5370000               call      0x4ee620
004eae7b c6450b01                 mov       byte ptr [ebp + 0xb], 1
004eae7f 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eae85 8b11                     mov       edx, dword ptr [ecx]
004eae87 6a02                     push      2
004eae89 6a13                     push      0x13
004eae8b ff5208                   call      dword ptr [edx + 8]
004eae8e a164310001               mov       eax, dword ptr [0x1003164]
004eae93 8b16                     mov       edx, dword ptr [esi]
004eae95 8b18                     mov       ebx, dword ptr [eax]
004eae97 8bce                     mov       ecx, esi
004eae99 ff523c                   call      dword ptr [edx + 0x3c]
004eae9c 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaea2 50                       push      eax
004eaea3 ff5324                   call      dword ptr [ebx + 0x24]
004eaea6 a164310001               mov       eax, dword ptr [0x1003164]
004eaeab 8b16                     mov       edx, dword ptr [esi]
004eaead 8b18                     mov       ebx, dword ptr [eax]
004eaeaf 8bce                     mov       ecx, esi
004eaeb1 ff5240                   call      dword ptr [edx + 0x40]
004eaeb4 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaeba 50                       push      eax
004eaebb ff5324                   call      dword ptr [ebx + 0x24]
004eaebe a164310001               mov       eax, dword ptr [0x1003164]
004eaec3 8b17                     mov       edx, dword ptr [edi]
004eaec5 8b30                     mov       esi, dword ptr [eax]
004eaec7 8bcf                     mov       ecx, edi
004eaec9 ff523c                   call      dword ptr [edx + 0x3c]
004eaecc 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaed2 50                       push      eax
004eaed3 ff5624                   call      dword ptr [esi + 0x24]
004eaed6 a164310001               mov       eax, dword ptr [0x1003164]
004eaedb 8b17                     mov       edx, dword ptr [edi]
004eaedd 8b30                     mov       esi, dword ptr [eax]
004eaedf 8bcf                     mov       ecx, edi
004eaee1 ff5240                   call      dword ptr [edx + 0x40]
004eaee4 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaeea 50                       push      eax
004eaeeb ff5624                   call      dword ptr [esi + 0x24]
004eaeee 8b7510                   mov       esi, dword ptr [ebp + 0x10]
004eaef1 8bce                     mov       ecx, esi
004eaef3 e8b884f4ff               call      0x4333b0
004eaef8 d95df0                   fstp      dword ptr [ebp - 0x10]
004eaefb 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaf01 8b01                     mov       eax, dword ptr [ecx]
004eaf03 6a04                     push      4
004eaf05 8d55f0                   lea       edx, [ebp - 0x10]
004eaf08 52                       push      edx
004eaf09 ff5034                   call      dword ptr [eax + 0x34]
004eaf0c 8d4e08                   lea       ecx, [esi + 8]
004eaf0f e89c84f4ff               call      0x4333b0
004eaf14 e82b667100               call      0xc01544
004eaf19 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaf1f 6a02                     push      2
004eaf21 8d55f8                   lea       edx, [ebp - 8]
004eaf24 52                       push      edx
004eaf25 8945f8                   mov       dword ptr [ebp - 8], eax
004eaf28 8b01                     mov       eax, dword ptr [ecx]
004eaf2a ff5034                   call      dword ptr [eax + 0x34]
004eaf2d 8d4e10                   lea       ecx, [esi + 0x10]
004eaf30 e87b84f4ff               call      0x4333b0
004eaf35 e80a667100               call      0xc01544
004eaf3a 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaf40 6a02                     push      2
004eaf42 8d55f8                   lea       edx, [ebp - 8]
004eaf45 52                       push      edx
004eaf46 8945f8                   mov       dword ptr [ebp - 8], eax
004eaf49 8b01                     mov       eax, dword ptr [ecx]
004eaf4b ff5034                   call      dword ptr [eax + 0x34]
004eaf4e 8d4e18                   lea       ecx, [esi + 0x18]
004eaf51 e85a84f4ff               call      0x4333b0
004eaf56 e8e9657100               call      0xc01544
004eaf5b 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaf61 6a02                     push      2
004eaf63 8d55f8                   lea       edx, [ebp - 8]
004eaf66 52                       push      edx
004eaf67 8945f8                   mov       dword ptr [ebp - 8], eax
004eaf6a 8b01                     mov       eax, dword ptr [ecx]
004eaf6c ff5034                   call      dword ptr [eax + 0x34]
004eaf6f 8d4e20                   lea       ecx, [esi + 0x20]
004eaf72 e83984f4ff               call      0x4333b0
004eaf77 e8c8657100               call      0xc01544
004eaf7c 8945f8                   mov       dword ptr [ebp - 8], eax
004eaf7f 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eaf85 8b01                     mov       eax, dword ptr [ecx]
004eaf87 6a02                     push      2
004eaf89 8d55f8                   lea       edx, [ebp - 8]
004eaf8c 52                       push      edx
004eaf8d ff5034                   call      dword ptr [eax + 0x34]
004eaf90 8d4e28                   lea       ecx, [esi + 0x28]
004eaf93 e81884f4ff               call      0x4333b0
004eaf98 e8a7657100               call      0xc01544
004eaf9d 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eafa3 6a02                     push      2
004eafa5 8d55f8                   lea       edx, [ebp - 8]
004eafa8 52                       push      edx
004eafa9 8945f8                   mov       dword ptr [ebp - 8], eax
004eafac 8b01                     mov       eax, dword ptr [ecx]
004eafae ff5034                   call      dword ptr [eax + 0x34]
004eafb1 8a550b                   mov       dl, byte ptr [ebp + 0xb]
004eafb4 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eafba 8b01                     mov       eax, dword ptr [ecx]
004eafbc 84d2                     test      dl, dl
004eafbe 0f95c2                   setne     dl
004eafc1 52                       push      edx
004eafc2 ff5020                   call      dword ptr [eax + 0x20]
004eafc5 a164310001               mov       eax, dword ptr [0x1003164]
004eafca 8b30                     mov       esi, dword ptr [eax]
004eafcc 6a00                     push      0
004eafce e81d313c00               call      0x8ae0f0
004eafd3 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004eafd9 83c404                   add       esp, 4
004eafdc 50                       push      eax
004eafdd ff5624                   call      dword ptr [esi + 0x24]
004eafe0 8b0d90070c01             mov       ecx, dword ptr [0x10c0790]
004eafe6 8b11                     mov       edx, dword ptr [ecx]
004eafe8 6a03                     push      3
004eafea 6a00                     push      0
004eafec 6aff                     push      -1
004eafee 6a01                     push      1
004eaff0 ff5244                   call      dword ptr [edx + 0x44]
004eaff3 5b                       pop       ebx
004eaff4 5e                       pop       esi
004eaff5 5f                       pop       edi
004eaff6 8be5                     mov       esp, ebp
004eaff8 5d                       pop       ebp
004eaff9 c3                       ret       
004eaffa cc                       int3      
004eaffb cc                       int3      
004eaffc cc                       int3      
004eaffd cc                       int3      
004eaffe cc                       int3      
004eafff cc                       int3      
004eb000 55                       push      ebp
004eb001 8bec                     mov       ebp, esp
004eb003 6aff                     push      -1
004eb005 68b298c500               push      0xc598b2
004eb00a 64a100000000             mov       eax, dword ptr fs:[0]
004eb010 50                       push      eax
004eb011 64892500000000           mov       dword ptr fs:[0], esp
004eb018 83ec38                   sub       esp, 0x38
004eb01b 56                       push      esi
004eb01c 57                       push      edi
004eb01d 8b7d08                   mov       edi, dword ptr [ebp + 8]
004eb020 8b07                     mov       eax, dword ptr [edi]
004eb022 8bf1                     mov       esi, ecx
004eb024 8bcf                     mov       ecx, edi
004eb026 ff90a4020000             call      dword ptr [eax + 0x2a4]
004eb02c 85c0                     test      eax, eax
004eb02e 0f848a010000             je        0x4eb1be
004eb034 8b10                     mov       edx, dword ptr [eax]
004eb036 6a09                     push      9
004eb038 8bc8                     mov       ecx, eax
004eb03a ff9228040000             call      dword ptr [edx + 0x428]
004eb040 85c0                     test      eax, eax
004eb042 0f8476010000             je        0x4eb1be
004eb048 6a00                     push      0
004eb04a 686c52f500               push      0xf5526c
004eb04f 687c28f400               push      0xf4287c
004eb054 6a00                     push      0
004eb056 57                       push      edi
004eb057 e8af5c7100               call      0xc00d0b
004eb05c 83c414                   add       esp, 0x14
004eb05f 85c0                     test      eax, eax
004eb061 8945ec                   mov       dword ptr [ebp - 0x14], eax
004eb064 0f8454010000             je        0x4eb1be
004eb06a 8b10                     mov       edx, dword ptr [eax]
004eb06c 6a09                     push      9
004eb06e 8bc8                     mov       ecx, eax
004eb070 ff9228040000             call      dword ptr [edx + 0x428]
004eb076 8bf8                     mov       edi, eax
004eb078 85ff                     test      edi, edi
004eb07a 0f843e010000             je        0x4eb1be
004eb080 8b07                     mov       eax, dword ptr [edi]
004eb082 8bcf                     mov       ecx, edi
004eb084 ff90e4000000             call      dword ptr [eax + 0xe4]
004eb08a 8b8874020000             mov       ecx, dword ptr [eax + 0x274]
004eb090 85c9                     test      ecx, ecx
004eb092 0f8526010000             jne       0x4eb1be
004eb098 6a00                     push      0
004eb09a e851303c00               call      0x8ae0f0
004eb09f 99                       cdq       
004eb0a0 b964000000               mov       ecx, 0x64
004eb0a5 f7f9                     idiv      ecx
004eb0a7 83c404                   add       esp, 4
004eb0aa 8bcf                     mov       ecx, edi
004eb0ac 8955f0                   mov       dword ptr [ebp - 0x10], edx
004eb0af db45f0                   fild      dword ptr [ebp - 0x10]
004eb0b2 8b17                     mov       edx, dword ptr [edi]
004eb0b4 d95df0                   fstp      dword ptr [ebp - 0x10]
004eb0b7 ff92e4000000             call      dword ptr [edx + 0xe4]
004eb0bd 8bc8                     mov       ecx, eax
004eb0bf 81c178020000             add       ecx, 0x278
004eb0c5 e8e682f4ff               call      0x4333b0
004eb0ca d85df0                   fcomp     dword ptr [ebp - 0x10]
004eb0cd dfe0                     fnstsw    ax
004eb0cf f6c441                   test      ah, 0x41
004eb0d2 0f85e6000000             jne       0x4eb1be
004eb0d8 53                       push      ebx
004eb0d9 8d4dbc                   lea       ecx, [ebp - 0x44]
004eb0dc e8cfc1f7ff               call      0x4672b0
004eb0e1 8b06                     mov       eax, dword ptr [esi]
004eb0e3 8bce                     mov       ecx, esi
004eb0e5 c745fc00000000           mov       dword ptr [ebp - 4], 0
004eb0ec ff9094000000             call      dword ptr [eax + 0x94]
004eb0f2 8945f0                   mov       dword ptr [ebp - 0x10], eax
004eb0f5 db45f0                   fild      dword ptr [ebp - 0x10]
004eb0f8 8d4df0                   lea       ecx, [ebp - 0x10]
004eb0fb 51                       push      ecx
004eb0fc 8d4dbc                   lea       ecx, [ebp - 0x44]
004eb0ff d95df0                   fstp      dword ptr [ebp - 0x10]
004eb102 e85994f1ff               call      0x404560
004eb107 8b16                     mov       edx, dword ptr [esi]
004eb109 8bce                     mov       ecx, esi
004eb10b ff9298000000             call      dword ptr [edx + 0x98]
004eb111 8945f0                   mov       dword ptr [ebp - 0x10], eax
004eb114 db45f0                   fild      dword ptr [ebp - 0x10]
004eb117 8d45f0                   lea       eax, [ebp - 0x10]
004eb11a 50                       push      eax
004eb11b 8d4dc4                   lea       ecx, [ebp - 0x3c]
004eb11e d95df0                   fstp      dword ptr [ebp - 0x10]
004eb121 e83a94f1ff               call      0x404560
004eb126 8b16                     mov       edx, dword ptr [esi]
004eb128 8bce                     mov       ecx, esi
004eb12a ff92e4000000             call      dword ptr [edx + 0xe4]
004eb130 99                       cdq       
004eb131 2bc2                     sub       eax, edx
004eb133 8bd8                     mov       ebx, eax
004eb135 8b06                     mov       eax, dword ptr [esi]
004eb137 8bce                     mov       ecx, esi
004eb139 d1fb                     sar       ebx, 1
004eb13b ff909c000000             call      dword ptr [eax + 0x9c]
004eb141 03d8                     add       ebx, eax
004eb143 895df0                   mov       dword ptr [ebp - 0x10], ebx
004eb146 db45f0                   fild      dword ptr [ebp - 0x10]
004eb149 8d4df0                   lea       ecx, [ebp - 0x10]
004eb14c 51                       push      ecx
004eb14d 8d4dcc                   lea       ecx, [ebp - 0x34]
004eb150 d95df0                   fstp      dword ptr [ebp - 0x10]
004eb153 e80894f1ff               call      0x404560
004eb158 6a00                     push      0
004eb15a 8d55bc                   lea       edx, [ebp - 0x44]
004eb15d 52                       push      edx
004eb15e 8d                       .byte     0x8d
004eb15f 45                       inc       ebp
