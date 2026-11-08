0049dc70 56                       push      esi
0049dc71 8bf1                     mov       esi, ecx
0049dc73 e888ff0400               call      0x4edc00
0049dc78 8bce                     mov       ecx, esi
0049dc7a e8e1fcffff               call      0x49d960
0049dc7f 8a86d8070000             mov       al, byte ptr [esi + 0x7d8]
0049dc85 84c0                     test      al, al
0049dc87 752f                     jne       0x49dcb8
0049dc89 83bed407000008           cmp       dword ptr [esi + 0x7d4], 8
0049dc90 7208                     jb        0x49dc9a
0049dc92 8b86c0070000             mov       eax, dword ptr [esi + 0x7c0]
0049dc98 eb06                     jmp       0x49dca0
0049dc9a 8d86c0070000             lea       eax, [esi + 0x7c0]
0049dca0 8b16                     mov       edx, dword ptr [esi]
0049dca2 6a00                     push      0
0049dca4 6a00                     push      0
0049dca6 6aff                     push      -1
0049dca8 50                       push      eax
0049dca9 8bce                     mov       ecx, esi
0049dcab ff920c010000             call      dword ptr [edx + 0x10c]
0049dcb1 c686d807000001           mov       byte ptr [esi + 0x7d8], 1
0049dcb8 8bce                     mov       ecx, esi
0049dcba e8d1e3ffff               call      0x49c090
0049dcbf 84c0                     test      al, al
0049dcc1 7422                     je        0x49dce5
0049dcc3 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
0049dcc9 8b4878                   mov       ecx, dword ptr [eax + 0x78]
0049dccc 85c9                     test      ecx, ecx
0049dcce 7415                     je        0x49dce5
0049dcd0 8b11                     mov       edx, dword ptr [ecx]
0049dcd2 ff5234                   call      dword ptr [edx + 0x34]
0049dcd5 84c0                     test      al, al
0049dcd7 750c                     jne       0x49dce5
0049dcd9 8b06                     mov       eax, dword ptr [esi]
0049dcdb 6a00                     push      0
0049dcdd 8bce                     mov       ecx, esi
0049dcdf ff9064010000             call      dword ptr [eax + 0x164]
0049dce5 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049dceb 85c9                     test      ecx, ecx
0049dced 741a                     je        0x49dd09
0049dcef 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049dcf5 2bc1                     sub       eax, ecx
0049dcf7 c1f805                   sar       eax, 5
0049dcfa 85c0                     test      eax, eax
0049dcfc 740b                     je        0x49dd09
0049dcfe 8b16                     mov       edx, dword ptr [esi]
0049dd00 8bce                     mov       ecx, esi
0049dd02 5e                       pop       esi
0049dd03 ffa264030000             jmp       dword ptr [edx + 0x364]
0049dd09 5e                       pop       esi
0049dd0a c3                       ret       
0049dd0b cc                       int3      
0049dd0c cc                       int3      
0049dd0d cc                       int3      
0049dd0e cc                       int3      
0049dd0f cc                       int3      
0049dd10 55                       push      ebp
0049dd11 8bec                     mov       ebp, esp
0049dd13 56                       push      esi
0049dd14 8b7508                   mov       esi, dword ptr [ebp + 8]
0049dd17 85f6                     test      esi, esi
0049dd19 57                       push      edi
0049dd1a 8bf9                     mov       edi, ecx
0049dd1c 89b730050000             mov       dword ptr [edi + 0x530], esi
0049dd22 0f847e010000             je        0x49dea6
0049dd28 8b06                     mov       eax, dword ptr [esi]
0049dd2a 53                       push      ebx
0049dd2b 8bce                     mov       ecx, esi
0049dd2d ff90c4010000             call      dword ptr [eax + 0x1c4]
0049dd33 898798040000             mov       dword ptr [edi + 0x498], eax
0049dd39 8b16                     mov       edx, dword ptr [esi]
0049dd3b 8bce                     mov       ecx, esi
0049dd3d ff92a8020000             call      dword ptr [edx + 0x2a8]
0049dd43 898734050000             mov       dword ptr [edi + 0x534], eax
0049dd49 8b06                     mov       eax, dword ptr [esi]
0049dd4b 8bce                     mov       ecx, esi
0049dd4d ff90d0010000             call      dword ptr [eax + 0x1d0]
0049dd53 898798070000             mov       dword ptr [edi + 0x798], eax
0049dd59 8b16                     mov       edx, dword ptr [esi]
0049dd5b 8bce                     mov       ecx, esi
0049dd5d ff92d4010000             call      dword ptr [edx + 0x1d4]
0049dd63 89879c070000             mov       dword ptr [edi + 0x79c], eax
0049dd69 8b06                     mov       eax, dword ptr [esi]
0049dd6b 8bce                     mov       ecx, esi
0049dd6d ff90d8010000             call      dword ptr [eax + 0x1d8]
0049dd73 8987a0070000             mov       dword ptr [edi + 0x7a0], eax
0049dd79 8b16                     mov       edx, dword ptr [esi]
0049dd7b 8bce                     mov       ecx, esi
0049dd7d ff92dc010000             call      dword ptr [edx + 0x1dc]
0049dd83 8987a4070000             mov       dword ptr [edi + 0x7a4], eax
0049dd89 8b06                     mov       eax, dword ptr [esi]
0049dd8b 8bce                     mov       ecx, esi
0049dd8d ff90e0010000             call      dword ptr [eax + 0x1e0]
0049dd93 8987a8070000             mov       dword ptr [edi + 0x7a8], eax
0049dd99 8b16                     mov       edx, dword ptr [esi]
0049dd9b 8bce                     mov       ecx, esi
0049dd9d ff92e4010000             call      dword ptr [edx + 0x1e4]
0049dda3 8987ac070000             mov       dword ptr [edi + 0x7ac], eax
0049dda9 8b06                     mov       eax, dword ptr [esi]
0049ddab 8bce                     mov       ecx, esi
0049ddad ff90e8010000             call      dword ptr [eax + 0x1e8]
0049ddb3 8987b0070000             mov       dword ptr [edi + 0x7b0], eax
0049ddb9 8b16                     mov       edx, dword ptr [esi]
0049ddbb 8bce                     mov       ecx, esi
0049ddbd ff92ec010000             call      dword ptr [edx + 0x1ec]
0049ddc3 8987b4070000             mov       dword ptr [edi + 0x7b4], eax
0049ddc9 8b06                     mov       eax, dword ptr [esi]
0049ddcb 8bce                     mov       ecx, esi
0049ddcd ff90f0010000             call      dword ptr [eax + 0x1f0]
0049ddd3 6a00                     push      0
0049ddd5 682829f400               push      0xf42928
0049ddda 687c28f400               push      0xf4287c
0049dddf 6a00                     push      0
0049dde1 56                       push      esi
0049dde2 8987b8070000             mov       dword ptr [edi + 0x7b8], eax
0049dde8 e81e2f7600               call      0xc00d0b
0049dded 83c414                   add       esp, 0x14
0049ddf0 85c0                     test      eax, eax
0049ddf2 747c                     je        0x49de70
0049ddf4 8d9f24060000             lea       ebx, [edi + 0x624]
0049ddfa 8db74c060000             lea       esi, [edi + 0x64c]
0049de00 c7450803000000           mov       dword ptr [ebp + 8], 3
0049de07 833b12                   cmp       dword ptr [ebx], 0x12
0049de0a 7447                     je        0x49de53
0049de0c 8d8e04020000             lea       ecx, [esi + 0x204]
0049de12 e84942f6ff               call      0x402060
0049de17 8b8f98070000             mov       ecx, dword ptr [edi + 0x798]
0049de1d 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049de23 8b5244                   mov       edx, dword ptr [edx + 0x44]
0049de26 03c1                     add       eax, ecx
0049de28 8b0e                     mov       ecx, dword ptr [esi]
0049de2a 8d0c8a                   lea       ecx, [edx + ecx*4]
0049de2d 8bd1                     mov       edx, ecx
0049de2f 3315dc012101             xor       edx, dword ptr [0x12101dc]
0049de35 33d0                     xor       edx, eax
0049de37 8911                     mov       dword ptr [ecx], edx
0049de39 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049de3f 8b5248                   mov       edx, dword ptr [edx + 0x48]
0049de42 8b0e                     mov       ecx, dword ptr [esi]
0049de44 8d0c8a                   lea       ecx, [edx + ecx*4]
0049de47 8bd1                     mov       edx, ecx
0049de49 3315dc012101             xor       edx, dword ptr [0x12101dc]
0049de4f 33d0                     xor       edx, eax
0049de51 8911                     mov       dword ptr [ecx], edx
0049de53 8b4508                   mov       eax, dword ptr [ebp + 8]
0049de56 83c304                   add       ebx, 4
0049de59 83c608                   add       esi, 8
0049de5c 48                       dec       eax
0049de5d 894508                   mov       dword ptr [ebp + 8], eax
0049de60 75a5                     jne       0x49de07
0049de62 5b                       pop       ebx
0049de63 8bcf                     mov       ecx, edi
0049de65 e806ad0400               call      0x4e8b70
0049de6a 5f                       pop       edi
0049de6b 5e                       pop       esi
0049de6c 5d                       pop       ebp
0049de6d c20400                   ret       4
0049de70 8d9f48060000             lea       ebx, [edi + 0x648]
0049de76 8db724060000             lea       esi, [edi + 0x624]
0049de7c c7450803000000           mov       dword ptr [ebp + 8], 3
0049de83 833e12                   cmp       dword ptr [esi], 0x12
0049de86 740e                     je        0x49de96
0049de88 8d8308020000             lea       eax, [ebx + 0x208]
0049de8e 50                       push      eax
0049de8f 8bcb                     mov       ecx, ebx
0049de91 e81a67f6ff               call      0x4045b0
0049de96 8b4508                   mov       eax, dword ptr [ebp + 8]
0049de99 83c604                   add       esi, 4
0049de9c 83c308                   add       ebx, 8
0049de9f 48                       dec       eax
0049dea0 894508                   mov       dword ptr [ebp + 8], eax
0049dea3 75de                     jne       0x49de83
0049dea5 5b                       pop       ebx
0049dea6 8bcf                     mov       ecx, edi
0049dea8 e8c3ac0400               call      0x4e8b70
0049dead 5f                       pop       edi
0049deae 5e                       pop       esi
0049deaf 5d                       pop       ebp
0049deb0 c20400                   ret       4
0049deb3 cc                       int3      
0049deb4 cc                       int3      
0049deb5 cc                       int3      
0049deb6 cc                       int3      
0049deb7 cc                       int3      
0049deb8 cc                       int3      
0049deb9 cc                       int3      
0049deba cc                       int3      
0049debb cc                       int3      
0049debc cc                       int3      
0049debd cc                       int3      
0049debe cc                       int3      
0049debf cc                       int3      
0049dec0 55                       push      ebp
0049dec1 8bec                     mov       ebp, esp
0049dec3 56                       push      esi
0049dec4 8bf1                     mov       esi, ecx
0049dec6 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
0049decc 85c0                     test      eax, eax
0049dece 7515                     jne       0x49dee5
0049ded0 6824eccc00               push      0xccec24
0049ded5 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049dedb 83c404                   add       esp, 4
0049dede 33c0                     xor       eax, eax
0049dee0 5e                       pop       esi
0049dee1 5d                       pop       ebp
0049dee2 c20400                   ret       4
0049dee5 8b4508                   mov       eax, dword ptr [ebp + 8]
0049dee8 85c0                     test      eax, eax
0049deea 7524                     jne       0x49df10
0049deec 8b06                     mov       eax, dword ptr [esi]
0049deee 8bce                     mov       ecx, esi
0049def0 ff908c010000             call      dword ptr [eax + 0x18c]
0049def6 85c0                     test      eax, eax
0049def8 740f                     je        0x49df09
0049defa 8b16                     mov       edx, dword ptr [esi]
0049defc 8bce                     mov       ecx, esi
0049defe ff928c010000             call      dword ptr [edx + 0x18c]
0049df04 5e                       pop       esi
0049df05 5d                       pop       ebp
0049df06 c20400                   ret       4
0049df09 8bc6                     mov       eax, esi
0049df0b 5e                       pop       esi
0049df0c 5d                       pop       ebp
0049df0d c20400                   ret       4
0049df10 83f801                   cmp       eax, 1
0049df13 75c9                     jne       0x49dede
0049df15 8b06                     mov       eax, dword ptr [esi]
0049df17 8bce                     mov       ecx, esi
0049df19 ff505c                   call      dword ptr [eax + 0x5c]
0049df1c 85c0                     test      eax, eax
0049df1e 74be                     je        0x49dede
0049df20 8b16                     mov       edx, dword ptr [esi]
0049df22 8bce                     mov       ecx, esi
0049df24 ff928c010000             call      dword ptr [edx + 0x18c]
0049df2a 85c0                     test      eax, eax
0049df2c 7454                     je        0x49df82
0049df2e 8b06                     mov       eax, dword ptr [esi]
0049df30 8bce                     mov       ecx, esi
0049df32 ff908c010000             call      dword ptr [eax + 0x18c]
0049df38 8b10                     mov       edx, dword ptr [eax]
0049df3a 8bc8                     mov       ecx, eax
0049df3c ff5234                   call      dword ptr [edx + 0x34]
0049df3f 84c0                     test      al, al
0049df41 8bce                     mov       ecx, esi
0049df43 7414                     je        0x49df59
0049df45 8b06                     mov       eax, dword ptr [esi]
0049df47 ff908c010000             call      dword ptr [eax + 0x18c]
0049df4d 8bc8                     mov       ecx, eax
0049df4f e81c010200               call      0x4be070
0049df54 5e                       pop       esi
0049df55 5d                       pop       ebp
0049df56 c20400                   ret       4
0049df59 8b16                     mov       edx, dword ptr [esi]
0049df5b ff928c010000             call      dword ptr [edx + 0x18c]
0049df61 8b10                     mov       edx, dword ptr [eax]
0049df63 8bc8                     mov       ecx, eax
0049df65 ff5238                   call      dword ptr [edx + 0x38]
0049df68 84c0                     test      al, al
0049df6a 7416                     je        0x49df82
0049df6c 8b06                     mov       eax, dword ptr [esi]
0049df6e 8bce                     mov       ecx, esi
0049df70 ff908c010000             call      dword ptr [eax + 0x18c]
0049df76 8bc8                     mov       ecx, eax
0049df78 e813b02a00               call      0x748f90
0049df7d 5e                       pop       esi
0049df7e 5d                       pop       ebp
0049df7f c20400                   ret       4
0049df82 53                       push      ebx
0049df83 57                       push      edi
0049df84 33db                     xor       ebx, ebx
0049df86 33ff                     xor       edi, edi
0049df88 897d08                   mov       dword ptr [ebp + 8], edi
0049df8b eb03                     jmp       0x49df90
0049df8d 8d4900                   lea       ecx, [ecx]
0049df90 8b16                     mov       edx, dword ptr [esi]
0049df92 8bce                     mov       ecx, esi
0049df94 ff525c                   call      dword ptr [edx + 0x5c]
0049df97 8b4810                   mov       ecx, dword ptr [eax + 0x10]
0049df9a 83c00c                   add       eax, 0xc
0049df9d 85c9                     test      ecx, ecx
0049df9f 7504                     jne       0x49dfa5
0049dfa1 33c0                     xor       eax, eax
0049dfa3 eb08                     jmp       0x49dfad
0049dfa5 8b4008                   mov       eax, dword ptr [eax + 8]
0049dfa8 2bc1                     sub       eax, ecx
0049dfaa c1f802                   sar       eax, 2
0049dfad 3bf8                     cmp       edi, eax
0049dfaf 0f8d94000000             jge       0x49e049
0049dfb5 8b06                     mov       eax, dword ptr [esi]
0049dfb7 8bce                     mov       ecx, esi
0049dfb9 ff505c                   call      dword ptr [eax + 0x5c]
0049dfbc 8b5010                   mov       edx, dword ptr [eax + 0x10]
0049dfbf 85d2                     test      edx, edx
0049dfc1 7415                     je        0x49dfd8
0049dfc3 8b4814                   mov       ecx, dword ptr [eax + 0x14]
0049dfc6 2bca                     sub       ecx, edx
0049dfc8 c1f902                   sar       ecx, 2
0049dfcb 3bf9                     cmp       edi, ecx
0049dfcd 7309                     jae       0x49dfd8
0049dfcf 8bca                     mov       ecx, edx
0049dfd1 8d04b9                   lea       eax, [ecx + edi*4]
0049dfd4 8b38                     mov       edi, dword ptr [eax]
0049dfd6 eb02                     jmp       0x49dfda
0049dfd8 33ff                     xor       edi, edi
0049dfda 8b17                     mov       edx, dword ptr [edi]
0049dfdc 6a01                     push      1
0049dfde 8bcf                     mov       ecx, edi
0049dfe0 ff522c                   call      dword ptr [edx + 0x2c]
0049dfe3 84c0                     test      al, al
0049dfe5 7419                     je        0x49e000
0049dfe7 6a00                     push      0
0049dfe9 687c28f400               push      0xf4287c
0049dfee 681009f400               push      0xf40910
0049dff3 6a00                     push      0
0049dff5 57                       push      edi
0049dff6 e8102d7600               call      0xc00d0b
0049dffb 83c414                   add       esp, 0x14
0049dffe 8bd8                     mov       ebx, eax
0049e000 85db                     test      ebx, ebx
0049e002 742e                     je        0x49e032
0049e004 8b03                     mov       eax, dword ptr [ebx]
0049e006 8bcb                     mov       ecx, ebx
0049e008 ff90c4010000             call      dword ptr [eax + 0x1c4]
0049e00e 3dc8000000               cmp       eax, 0xc8
0049e013 7c11                     jl        0x49e026
0049e015 8b13                     mov       edx, dword ptr [ebx]
0049e017 8bcb                     mov       ecx, ebx
0049e019 ff92c4010000             call      dword ptr [edx + 0x1c4]
0049e01f 3dcd000000               cmp       eax, 0xcd
0049e024 7e0c                     jle       0x49e032
0049e026 53                       push      ebx
0049e027 8bce                     mov       ecx, esi
0049e029 e8a2ab0400               call      0x4e8bd0
0049e02e 84c0                     test      al, al
0049e030 750e                     jne       0x49e040
0049e032 8b4508                   mov       eax, dword ptr [ebp + 8]
0049e035 40                       inc       eax
0049e036 894508                   mov       dword ptr [ebp + 8], eax
0049e039 8bf8                     mov       edi, eax
0049e03b e950ffffff               jmp       0x49df90
0049e040 5f                       pop       edi
0049e041 8bc3                     mov       eax, ebx
0049e043 5b                       pop       ebx
0049e044 5e                       pop       esi
0049e045 5d                       pop       ebp
0049e046 c20400                   ret       4
0049e049 5f                       pop       edi
0049e04a 5b                       pop       ebx
0049e04b 33c0                     xor       eax, eax
0049e04d 5e                       pop       esi
0049e04e 5d                       pop       ebp
0049e04f c20400                   ret       4
0049e052 cc                       int3      
0049e053 cc                       int3      
0049e054 cc                       int3      
0049e055 cc                       int3      
0049e056 cc                       int3      
0049e057 cc                       int3      
0049e058 cc                       int3      
0049e059 cc                       int3      
0049e05a cc                       int3      
0049e05b cc                       int3      
0049e05c cc                       int3      
0049e05d cc                       int3      
0049e05e cc                       int3      
0049e05f cc                       int3      
0049e060 56                       push      esi
0049e061 8bf1                     mov       esi, ecx
0049e063 8b8e94070000             mov       ecx, dword ptr [esi + 0x794]
0049e069 57                       push      edi
0049e06a 33ff                     xor       edi, edi
0049e06c 3bcf                     cmp       ecx, edi
0049e06e 7406                     je        0x49e076
0049e070 8b01                     mov       eax, dword ptr [ecx]
0049e072 6a01                     push      1
0049e074 ff10                     call      dword ptr [eax]
0049e076 8b8e14080000             mov       ecx, dword ptr [esi + 0x814]
0049e07c 51                       push      ecx
0049e07d 89be94070000             mov       dword ptr [esi + 0x794], edi
0049e083 e8fe317600               call      0xc01286
0049e088 89be14080000             mov       dword ptr [esi + 0x814], edi
0049e08e 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049e094 83c404                   add       esp, 4
0049e097 3bcf                     cmp       ecx, edi
0049e099 7455                     je        0x49e0f0
0049e09b 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049e0a1 2bc1                     sub       eax, ecx
0049e0a3 c1f805                   sar       eax, 5
0049e0a6 3bc7                     cmp       eax, edi
0049e0a8 7446                     je        0x49e0f0
0049e0aa 53                       push      ebx
0049e0ab 33db                     xor       ebx, ebx
0049e0ad 8d4900                   lea       ecx, [ecx]
0049e0b0 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049e0b6 85c9                     test      ecx, ecx
0049e0b8 7435                     je        0x49e0ef
0049e0ba 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049e0c0 2bc1                     sub       eax, ecx
0049e0c2 c1f805                   sar       eax, 5
0049e0c5 3bd8                     cmp       ebx, eax
0049e0c7 7326                     jae       0x49e0ef
0049e0c9 8bc1                     mov       eax, ecx
0049e0cb 03c7                     add       eax, edi
0049e0cd 8b00                     mov       eax, dword ptr [eax]
0049e0cf 85c0                     test      eax, eax
0049e0d1 7408                     je        0x49e0db
0049e0d3 8b10                     mov       edx, dword ptr [eax]
0049e0d5 6a01                     push      1
0049e0d7 8bc8                     mov       ecx, eax
0049e0d9 ff12                     call      dword ptr [edx]
0049e0db 8b8620080000             mov       eax, dword ptr [esi + 0x820]
0049e0e1 03c7                     add       eax, edi
0049e0e3 43                       inc       ebx
0049e0e4 c70000000000             mov       dword ptr [eax], 0
0049e0ea 83c720                   add       edi, 0x20
0049e0ed ebc1                     jmp       0x49e0b0
0049e0ef 5b                       pop       ebx
0049e0f0 5f                       pop       edi
0049e0f1 5e                       pop       esi
0049e0f2 c3                       ret       
0049e0f3 cc                       int3      
0049e0f4 cc                       int3      
0049e0f5 cc                       int3      
0049e0f6 cc                       int3      
0049e0f7 cc                       int3      
0049e0f8 cc                       int3      
0049e0f9 cc                       int3      
0049e0fa cc                       int3      
0049e0fb cc                       int3      
0049e0fc cc                       int3      
0049e0fd cc                       int3      
0049e0fe cc                       int3      
0049e0ff cc                       int3      
0049e100 55                       push      ebp
0049e101 8bec                     mov       ebp, esp
0049e103 6aff                     push      -1
0049e105 68086bc500               push      0xc56b08
0049e10a 64a100000000             mov       eax, dword ptr fs:[0]
0049e110 50                       push      eax
0049e111 64892500000000           mov       dword ptr fs:[0], esp
0049e118 83ec48                   sub       esp, 0x48
0049e11b 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049e11e 53                       push      ebx
0049e11f 57                       push      edi
0049e120 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
0049e123 8bd9                     mov       ebx, ecx
0049e125 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049e128 57                       push      edi
0049e129 50                       push      eax
0049e12a 51                       push      ecx
0049e12b 8bcb                     mov       ecx, ebx
0049e12d 895ddc                   mov       dword ptr [ebp - 0x24], ebx
0049e130 e8fba80400               call      0x4e8a30
0049e135 8a8340050000             mov       al, byte ptr [ebx + 0x540]
0049e13b 84c0                     test      al, al
0049e13d 0f84d5030000             je        0x49e518
0049e143 8bcb                     mov       ecx, ebx
0049e145 e846dfffff               call      0x49c090
0049e14a 84c0                     test      al, al
0049e14c 0f84c6030000             je        0x49e518
0049e152 8b8304010000             mov       eax, dword ptr [ebx + 0x104]
0049e158 56                       push      esi
0049e159 33f6                     xor       esi, esi
0049e15b 3bc6                     cmp       eax, esi
0049e15d 0f84a8030000             je        0x49e50b
0049e163 8b13                     mov       edx, dword ptr [ebx]
0049e165 8bcb                     mov       ecx, ebx
0049e167 ff92d4020000             call      dword ptr [edx + 0x2d4]
0049e16d 84c0                     test      al, al
0049e16f 0f                       .byte     0x0f
