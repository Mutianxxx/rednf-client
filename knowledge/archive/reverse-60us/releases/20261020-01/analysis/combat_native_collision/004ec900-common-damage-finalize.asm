004ec900 40                       inc       eax
004ec901 50                       push      eax
004ec902 e8a9a76200               call      0xb170b0
004ec907 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ec90d 6aff                     push      -1
004ec90f 885db2                   mov       byte ptr [ebp - 0x4e], bl
004ec912 e8d9e2f4ff               call      0x43abf0
004ec917 8b16                     mov       edx, dword ptr [esi]
004ec919 8bce                     mov       ecx, esi
004ec91b 8845e4                   mov       byte ptr [ebp - 0x1c], al
004ec91e ff92d0010000             call      dword ptr [edx + 0x1d0]
004ec924 6a00                     push      0
004ec926 688c52f500               push      0xf5528c
004ec92b 686c52f500               push      0xf5526c
004ec930 8845b3                   mov       byte ptr [ebp - 0x4d], al
004ec933 8b06                     mov       eax, dword ptr [esi]
004ec935 6a00                     push      0
004ec937 8bce                     mov       ecx, esi
004ec939 ff90a4020000             call      dword ptr [eax + 0x2a4]
004ec93f 50                       push      eax
004ec940 e8c6437100               call      0xc00d0b
004ec945 8bf8                     mov       edi, eax
004ec947 83c414                   add       esp, 0x14
004ec94a 85ff                     test      edi, edi
004ec94c 7428                     je        0x4ec976
004ec94e 8b17                     mov       edx, dword ptr [edi]
004ec950 6a09                     push      9
004ec952 8bcf                     mov       ecx, edi
004ec954 ff9228040000             call      dword ptr [edx + 0x428]
004ec95a 85c0                     test      eax, eax
004ec95c 741c                     je        0x4ec97a
004ec95e 8b07                     mov       eax, dword ptr [edi]
004ec960 6a09                     push      9
004ec962 8bcf                     mov       ecx, edi
004ec964 ff9028040000             call      dword ptr [eax + 0x428]
004ec96a 8bc8                     mov       ecx, eax
004ec96c e87f9bf6ff               call      0x4564f0
004ec971 8845b4                   mov       byte ptr [ebp - 0x4c], al
004ec974 eb04                     jmp       0x4ec97a
004ec976 c645b401                 mov       byte ptr [ebp - 0x4c], 1
004ec97a 8b7df8                   mov       edi, dword ptr [ebp - 8]
004ec97d 8b17                     mov       edx, dword ptr [edi]
004ec97f 8bcf                     mov       ecx, edi
004ec981 ff92fc020000             call      dword ptr [edx + 0x2fc]
004ec987 83f832                   cmp       eax, 0x32
004ec98a 7d2a                     jge       0x4ec9b6
004ec98c 8b06                     mov       eax, dword ptr [esi]
004ec98e 8bce                     mov       ecx, esi
004ec990 ff90a4020000             call      dword ptr [eax + 0x2a4]
004ec996 3b8758040000             cmp       eax, dword ptr [edi + 0x458]
004ec99c 7418                     je        0x4ec9b6
004ec99e 8a45d3                   mov       al, byte ptr [ebp - 0x2d]
004ec9a1 fec0                     inc       al
004ec9a3 3c04                     cmp       al, 4
004ec9a5 c645ce01                 mov       byte ptr [ebp - 0x32], 1
004ec9a9 7d05                     jge       0x4ec9b0
004ec9ab 8845d3                   mov       byte ptr [ebp - 0x2d], al
004ec9ae eb11                     jmp       0x4ec9c1
004ec9b0 c645d304                 mov       byte ptr [ebp - 0x2d], 4
004ec9b4 eb0b                     jmp       0x4ec9c1
004ec9b6 c745cf00000000           mov       dword ptr [ebp - 0x31], 0
004ec9bd c645d301                 mov       byte ptr [ebp - 0x2d], 1
004ec9c1 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004ec9c4 85c9                     test      ecx, ecx
004ec9c6 740d                     je        0x4ec9d5
004ec9c8 8b11                     mov       edx, dword ptr [ecx]
004ec9ca 6a06                     push      6
004ec9cc ff9210040000             call      dword ptr [edx + 0x410]
004ec9d2 8845e9                   mov       byte ptr [ebp - 0x17], al
004ec9d5 8b06                     mov       eax, dword ptr [esi]
004ec9d7 6a21                     push      0x21
004ec9d9 8bce                     mov       ecx, esi
004ec9db ff502c                   call      dword ptr [eax + 0x2c]
004ec9de 84c0                     test      al, al
004ec9e0 7409                     je        0x4ec9eb
004ec9e2 8b8e04020000             mov       ecx, dword ptr [esi + 0x204]
004ec9e8 894dea                   mov       dword ptr [ebp - 0x16], ecx
004ec9eb 56                       push      esi
004ec9ec 8d9528feffff             lea       edx, [ebp - 0x1d8]
004ec9f2 57                       push      edi
004ec9f3 52                       push      edx
004ec9f4 e857bc3c00               call      0x8b8650
004ec9f9 8a4dcd                   mov       cl, byte ptr [ebp - 0x33]
004ec9fc 8b5508                   mov       edx, dword ptr [ebp + 8]
004ec9ff 83c40c                   add       esp, 0xc
004eca02 84c9                     test      cl, cl
004eca04 0f95c1                   setne     cl
004eca07 880a                     mov       byte ptr [edx], cl
004eca09 8b4dcf                   mov       ecx, dword ptr [ebp - 0x31]
004eca0c 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004eca0f 5f                       pop       edi
004eca10 5e                       pop       esi
004eca11 890a                     mov       dword ptr [edx], ecx
004eca13 5b                       pop       ebx
004eca14 8be5                     mov       esp, ebp
004eca16 5d                       pop       ebp
004eca17 c21800                   ret       0x18
004eca1a cc                       int3      
004eca1b cc                       int3      
004eca1c cc                       int3      
004eca1d cc                       int3      
004eca1e cc                       int3      
004eca1f cc                       int3      
004eca20 55                       push      ebp
004eca21 8bec                     mov       ebp, esp
004eca23 53                       push      ebx
004eca24 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004eca27 56                       push      esi
004eca28 57                       push      edi
004eca29 8bf1                     mov       esi, ecx
004eca2b 33ff                     xor       edi, edi
004eca2d 8d4900                   lea       ecx, [ecx]
004eca30 8b8ed4040000             mov       ecx, dword ptr [esi + 0x4d4]
004eca36 85c9                     test      ecx, ecx
004eca38 7449                     je        0x4eca83
004eca3a 8b86d8040000             mov       eax, dword ptr [esi + 0x4d8]
004eca40 2bc1                     sub       eax, ecx
004eca42 c1f802                   sar       eax, 2
004eca45 3bf8                     cmp       edi, eax
004eca47 733a                     jae       0x4eca83
004eca49 8bc1                     mov       eax, ecx
004eca4b 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004eca4e 3bcb                     cmp       ecx, ebx
004eca50 8d04b8                   lea       eax, [eax + edi*4]
004eca53 752b                     jne       0x4eca80
004eca55 8b96d8040000             mov       edx, dword ptr [esi + 0x4d8]
004eca5b 8d4804                   lea       ecx, [eax + 4]
004eca5e 2bd1                     sub       edx, ecx
004eca60 c1fa02                   sar       edx, 2
004eca63 c1e202                   shl       edx, 2
004eca66 52                       push      edx
004eca67 51                       push      ecx
004eca68 50                       push      eax
004eca69 e822307100               call      0xbffa90
004eca6e 8b86d8040000             mov       eax, dword ptr [esi + 0x4d8]
004eca74 83c40c                   add       esp, 0xc
004eca77 83c0fc                   add       eax, -4
004eca7a 8986d8040000             mov       dword ptr [esi + 0x4d8], eax
004eca80 47                       inc       edi
004eca81 ebad                     jmp       0x4eca30
004eca83 5f                       pop       edi
004eca84 5e                       pop       esi
004eca85 5b                       pop       ebx
004eca86 5d                       pop       ebp
004eca87 c20400                   ret       4
004eca8a cc                       int3      
004eca8b cc                       int3      
004eca8c cc                       int3      
004eca8d cc                       int3      
004eca8e cc                       int3      
004eca8f cc                       int3      
004eca90 55                       push      ebp
004eca91 8bec                     mov       ebp, esp
004eca93 56                       push      esi
004eca94 8bf1                     mov       esi, ecx
004eca96 8b8e28020000             mov       ecx, dword ptr [esi + 0x228]
004eca9c 8b8624020000             mov       eax, dword ptr [esi + 0x224]
004ecaa2 3bc1                     cmp       eax, ecx
004ecaa4 57                       push      edi
004ecaa5 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ecaa8 744b                     je        0x4ecaf5
004ecaaa 8d9b00000000             lea       ebx, [ebx]
004ecab0 3938                     cmp       dword ptr [eax], edi
004ecab2 7407                     je        0x4ecabb
004ecab4 83c004                   add       eax, 4
004ecab7 3bc1                     cmp       eax, ecx
004ecab9 75f5                     jne       0x4ecab0
004ecabb 3bc1                     cmp       eax, ecx
004ecabd 7436                     je        0x4ecaf5
004ecabf 8b9628020000             mov       edx, dword ptr [esi + 0x228]
004ecac5 8d4804                   lea       ecx, [eax + 4]
004ecac8 2bd1                     sub       edx, ecx
004ecaca c1fa02                   sar       edx, 2
004ecacd c1e202                   shl       edx, 2
004ecad0 52                       push      edx
004ecad1 51                       push      ecx
004ecad2 50                       push      eax
004ecad3 e8b82f7100               call      0xbffa90
004ecad8 8b9628020000             mov       edx, dword ptr [esi + 0x228]
004ecade 83c2fc                   add       edx, -4
004ecae1 83c40c                   add       esp, 0xc
004ecae4 899628020000             mov       dword ptr [esi + 0x228], edx
004ecaea 8b06                     mov       eax, dword ptr [esi]
004ecaec 57                       push      edi
004ecaed 8bce                     mov       ecx, esi
004ecaef ff9028020000             call      dword ptr [eax + 0x228]
004ecaf5 5f                       pop       edi
004ecaf6 5e                       pop       esi
004ecaf7 5d                       pop       ebp
004ecaf8 c20400                   ret       4
004ecafb cc                       int3      
004ecafc cc                       int3      
004ecafd cc                       int3      
004ecafe cc                       int3      
004ecaff cc                       int3      
004ecb00 55                       push      ebp
004ecb01 8bec                     mov       ebp, esp
004ecb03 83ec14                   sub       esp, 0x14
004ecb06 57                       push      edi
004ecb07 8bf9                     mov       edi, ecx
004ecb09 8b8700010000             mov       eax, dword ptr [edi + 0x100]
004ecb0f 85c0                     test      eax, eax
004ecb11 0f842d030000             je        0x4ece44
004ecb17 8d8fbc040000             lea       ecx, [edi + 0x4bc]
004ecb1d e83e55f1ff               call      0x402060
004ecb22 85c0                     test      eax, eax
004ecb24 740d                     je        0x4ecb33
004ecb26 8d8fc4040000             lea       ecx, [edi + 0x4c4]
004ecb2c e82f55f1ff               call      0x402060
004ecb31 eb07                     jmp       0x4ecb3a
004ecb33 8bcf                     mov       ecx, edi
004ecb35 e8a6d4faff               call      0x499fe0
004ecb3a 85c0                     test      eax, eax
004ecb3c 7409                     je        0x4ecb47
004ecb3e 83f801                   cmp       eax, 1
004ecb41 0f85fd020000             jne       0x4ece44
004ecb47 53                       push      ebx
004ecb48 56                       push      esi
004ecb49 8b7508                   mov       esi, dword ptr [ebp + 8]
004ecb4c 8b06                     mov       eax, dword ptr [esi]
004ecb4e 8bce                     mov       ecx, esi
004ecb50 ff909c010000             call      dword ptr [eax + 0x19c]
004ecb56 8bd8                     mov       ebx, eax
004ecb58 85db                     test      ebx, ebx
004ecb5a 895df8                   mov       dword ptr [ebp - 8], ebx
004ecb5d 740f                     je        0x4ecb6e
004ecb5f 8bcb                     mov       ecx, ebx
004ecb61 e81aa9f7ff               call      0x467480
004ecb66 84c0                     test      al, al
004ecb68 0f84d4020000             je        0x4ece42
004ecb6e c645ff00                 mov       byte ptr [ebp - 1], 0
004ecb72 8b8378010000             mov       eax, dword ptr [ebx + 0x178]
004ecb78 83f801                   cmp       eax, 1
004ecb7b c745f4e0baca00           mov       dword ptr [ebp - 0xc], 0xcabae0
004ecb82 c7450800000000           mov       dword ptr [ebp + 8], 0
004ecb89 751e                     jne       0x4ecba9
004ecb8b 8b16                     mov       edx, dword ptr [esi]
004ecb8d 8bce                     mov       ecx, esi
004ecb8f c7450800000100           mov       dword ptr [ebp + 8], 0x10000
004ecb96 ff92c0000000             call      dword ptr [edx + 0xc0]
004ecb9c 85c0                     test      eax, eax
004ecb9e 7547                     jne       0x4ecbe7
004ecba0 c7450802000100           mov       dword ptr [ebp + 8], 0x10002
004ecba7 eb3e                     jmp       0x4ecbe7
004ecba9 85c0                     test      eax, eax
004ecbab 7509                     jne       0x4ecbb6
004ecbad c7450800800000           mov       dword ptr [ebp + 8], 0x8000
004ecbb4 eb1d                     jmp       0x4ecbd3
004ecbb6 83f803                   cmp       eax, 3
004ecbb9 7518                     jne       0x4ecbd3
004ecbbb 8b06                     mov       eax, dword ptr [esi]
004ecbbd 8d4dff                   lea       ecx, [ebp - 1]
004ecbc0 51                       push      ecx
004ecbc1 8bce                     mov       ecx, esi
004ecbc3 c7450800000200           mov       dword ptr [ebp + 8], 0x20000
004ecbca ff9014030000             call      dword ptr [eax + 0x314]
004ecbd0 8945f4                   mov       dword ptr [ebp - 0xc], eax
004ecbd3 8b16                     mov       edx, dword ptr [esi]
004ecbd5 57                       push      edi
004ecbd6 8bce                     mov       ecx, esi
004ecbd8 ff921c030000             call      dword ptr [edx + 0x31c]
004ecbde 83f801                   cmp       eax, 1
004ecbe1 7504                     jne       0x4ecbe7
004ecbe3 834d0802                 or        dword ptr [ebp + 8], 2
004ecbe7 56                       push      esi
004ecbe8 57                       push      edi
004ecbe9 e872c5ffff               call      0x4e9160
004ecbee 83c408                   add       esp, 8
004ecbf1 3c01                     cmp       al, 1
004ecbf3 7570                     jne       0x4ecc65
004ecbf5 8b06                     mov       eax, dword ptr [esi]
004ecbf7 8bce                     mov       ecx, esi
004ecbf9 ff90ac010000             call      dword ptr [eax + 0x1ac]
004ecbff 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004ecc02 85c9                     test      ecx, ecx
004ecc04 765f                     jbe       0x4ecc65
004ecc06 8b17                     mov       edx, dword ptr [edi]
004ecc08 8bcf                     mov       ecx, edi
004ecc0a ff92c8010000             call      dword ptr [edx + 0x1c8]
004ecc10 8945f0                   mov       dword ptr [ebp - 0x10], eax
004ecc13 8b06                     mov       eax, dword ptr [esi]
004ecc15 8bce                     mov       ecx, esi
004ecc17 ff90ac010000             call      dword ptr [eax + 0x1ac]
004ecc1d 8b4808                   mov       ecx, dword ptr [eax + 8]
004ecc20 8b19                     mov       ebx, dword ptr [ecx]
004ecc22 8b16                     mov       edx, dword ptr [esi]
004ecc24 8bce                     mov       ecx, esi
004ecc26 ff92ac010000             call      dword ptr [edx + 0x1ac]
004ecc2c 8d4df0                   lea       ecx, [ebp - 0x10]
004ecc2f 51                       push      ecx
