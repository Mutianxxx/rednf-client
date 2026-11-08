004fcea0 55                       push      ebp
004fcea1 8bec                     mov       ebp, esp
004fcea3 83ec2c                   sub       esp, 0x2c
004fcea6 57                       push      edi
004fcea7 8bf9                     mov       edi, ecx
004fcea9 8b8f28020000             mov       ecx, dword ptr [edi + 0x228]
004fceaf 8b8724020000             mov       eax, dword ptr [edi + 0x224]
004fceb5 3bc1                     cmp       eax, ecx
004fceb7 741b                     je        0x4fced4
004fceb9 8da42400000000           lea       esp, [esp]
004fcec0 833819                   cmp       dword ptr [eax], 0x19
004fcec3 7407                     je        0x4fcecc
004fcec5 83c004                   add       eax, 4
004fcec8 3bc1                     cmp       eax, ecx
004fceca 75f4                     jne       0x4fcec0
004fcecc 3bc1                     cmp       eax, ecx
004fcece 0f8521020000             jne       0x4fd0f5
004fced4 8bcf                     mov       ecx, edi
004fced6 e8b5f1f9ff               call      0x49c090
004fcedb 84c0                     test      al, al
004fcedd 0f8412020000             je        0x4fd0f5
004fcee3 8d8fb81c0000             lea       ecx, [edi + 0x1cb8]
004fcee9 e87251f0ff               call      0x402060
004fceee 85c0                     test      eax, eax
004fcef0 0f84ff010000             je        0x4fd0f5
004fcef6 8b87301a0000             mov       eax, dword ptr [edi + 0x1a30]
004fcefc 53                       push      ebx
004fcefd 33db                     xor       ebx, ebx
004fceff 83f809                   cmp       eax, 9
004fcf02 56                       push      esi
004fcf03 8bb7801b0000             mov       esi, dword ptr [edi + 0x1b80]
004fcf09 8975ec                   mov       dword ptr [ebp - 0x14], esi
004fcf0c 895df8                   mov       dword ptr [ebp - 8], ebx
004fcf0f 899f801b0000             mov       dword ptr [edi + 0x1b80], ebx
004fcf15 895df0                   mov       dword ptr [ebp - 0x10], ebx
004fcf18 740a                     je        0x4fcf24
004fcf1a 83f80a                   cmp       eax, 0xa
004fcf1d 7405                     je        0x4fcf24
004fcf1f 83f80b                   cmp       eax, 0xb
004fcf22 7517                     jne       0x4fcf3b
004fcf24 3bf3                     cmp       esi, ebx
004fcf26 7413                     je        0x4fcf3b
004fcf28 8b07                     mov       eax, dword ptr [edi]
004fcf2a 56                       push      esi
004fcf2b 8bcf                     mov       ecx, edi
004fcf2d ff9044040000             call      dword ptr [eax + 0x444]
004fcf33 3c01                     cmp       al, 1
004fcf35 0f84ad010000             je        0x4fd0e8
004fcf3b 33c0                     xor       eax, eax
004fcf3d 8945d8                   mov       dword ptr [ebp - 0x28], eax
004fcf40 8945dc                   mov       dword ptr [ebp - 0x24], eax
004fcf43 8945e0                   mov       dword ptr [ebp - 0x20], eax
004fcf46 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004fcf49 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fcf4c 399fe41c0000             cmp       dword ptr [edi + 0x1ce4], ebx
004fcf52 895dd4                   mov       dword ptr [ebp - 0x2c], ebx
004fcf55 740f                     je        0x4fcf66
004fcf57 8d4dd8                   lea       ecx, [ebp - 0x28]
004fcf5a 51                       push      ecx
004fcf5b 8d55d4                   lea       edx, [ebp - 0x2c]
004fcf5e 52                       push      edx
004fcf5f 8bcf                     mov       ecx, edi
004fcf61 e89a83ffff               call      0x4f5300
004fcf66 399fe81c0000             cmp       dword ptr [edi + 0x1ce8], ebx
004fcf6c 740f                     je        0x4fcf7d
004fcf6e 8d45e0                   lea       eax, [ebp - 0x20]
004fcf71 50                       push      eax
004fcf72 8d4ddc                   lea       ecx, [ebp - 0x24]
004fcf75 51                       push      ecx
004fcf76 8bcf                     mov       ecx, edi
004fcf78 e85385ffff               call      0x4f54d0
004fcf7d 399fec1c0000             cmp       dword ptr [edi + 0x1cec], ebx
004fcf83 740f                     je        0x4fcf94
004fcf85 8d55e8                   lea       edx, [ebp - 0x18]
004fcf88 52                       push      edx
004fcf89 8d45e4                   lea       eax, [ebp - 0x1c]
004fcf8c 50                       push      eax
004fcf8d 8bcf                     mov       ecx, edi
004fcf8f e8bcdbffff               call      0x4fab50
004fcf94 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004fcf9a 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004fcfa0 85d2                     test      edx, edx
004fcfa2 895dfc                   mov       dword ptr [ebp - 4], ebx
004fcfa5 7504                     jne       0x4fcfab
004fcfa7 33c0                     xor       eax, eax
004fcfa9 eb0b                     jmp       0x4fcfb6
004fcfab 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004fcfb1 2bc2                     sub       eax, edx
004fcfb3 c1f802                   sar       eax, 2
004fcfb6 3bd8                     cmp       ebx, eax
004fcfb8 0f8d07010000             jge       0x4fd0c5
004fcfbe 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004fcfc4 85d2                     test      edx, edx
004fcfc6 7418                     je        0x4fcfe0
004fcfc8 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004fcfce 2bc2                     sub       eax, edx
004fcfd0 c1f802                   sar       eax, 2
004fcfd3 3bd8                     cmp       ebx, eax
004fcfd5 7309                     jae       0x4fcfe0
004fcfd7 8bca                     mov       ecx, edx
004fcfd9 8d0499                   lea       eax, [ecx + ebx*4]
004fcfdc 8b08                     mov       ecx, dword ptr [eax]
004fcfde eb02                     jmp       0x4fcfe2
004fcfe0 33c9                     xor       ecx, ecx
004fcfe2 8b11                     mov       edx, dword ptr [ecx]
004fcfe4 6a11                     push      0x11
004fcfe6 ff522c                   call      dword ptr [edx + 0x2c]
004fcfe9 84c0                     test      al, al
004fcfeb 0f84cb000000             je        0x4fd0bc
004fcff1 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004fcff7 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004fcffd 85d2                     test      edx, edx
004fcfff 7419                     je        0x4fd01a
004fd001 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004fd007 2bc2                     sub       eax, edx
004fd009 c1f802                   sar       eax, 2
004fd00c 3bd8                     cmp       ebx, eax
004fd00e 730a                     jae       0x4fd01a
004fd010 8bc2                     mov       eax, edx
004fd012 8b3498                   mov       esi, dword ptr [eax + ebx*4]
004fd015 8d0498                   lea       eax, [eax + ebx*4]
004fd018 eb02                     jmp       0x4fd01c
004fd01a 33f6                     xor       esi, esi
004fd01c 56                       push      esi
004fd01d 8bcf                     mov       ecx, edi
004fd01f e8acbbfeff               call      0x4e8bd0
004fd024 84c0                     test      al, al
004fd026 0f8490000000             je        0x4fd0bc
004fd02c 8bce                     mov       ecx, esi
004fd02e e8cdb7feff               call      0x4e8800
004fd033 84c0                     test      al, al
004fd035 0f8581000000             jne       0x4fd0bc
004fd03b 8b17                     mov       edx, dword ptr [edi]
004fd03d 56                       push      esi
004fd03e 8bcf                     mov       ecx, edi
004fd040 ff9244040000             call      dword ptr [edx + 0x444]
004fd046 84c0                     test      al, al
004fd048 7472                     je        0x4fd0bc
004fd04a 8b06                     mov       eax, dword ptr [esi]
004fd04c 6811020000               push      0x211
004fd051 8bce                     mov       ecx, esi
004fd053 ff502c                   call      dword ptr [eax + 0x2c]
004fd056 84c0                     test      al, al
004fd058 7425                     je        0x4fd07f
004fd05a 6a00                     push      0
004fd05c 682829f400               push      0xf42928
004fd061 686c52f500               push      0xf5526c
004fd066 6a00                     push      0
004fd068 56                       push      esi
004fd069 e89d3c7000               call      0xc00d0b
004fd06e 83c414                   add       esp, 0x14
004fd071 85c0                     test      eax, eax
004fd073 740a                     je        0x4fd07f
004fd075 8a88501d0000             mov       cl, byte ptr [eax + 0x1d50]
004fd07b 84c9                     test      cl, cl
004fd07d 753d                     jne       0x4fd0bc
004fd07f 8d4dd4                   lea       ecx, [ebp - 0x2c]
004fd082 51                       push      ecx
004fd083 56                       push      esi
004fd084 8d55f4                   lea       edx, [ebp - 0xc]
004fd087 52                       push      edx
004fd088 8bcf                     mov       ecx, edi
004fd08a c745f400000000           mov       dword ptr [ebp - 0xc], 0
004fd091 e8ba3cffff               call      0x4f0d50
004fd096 8b5df4                   mov       ebx, dword ptr [ebp - 0xc]
004fd099 3b5df0                   cmp       ebx, dword ptr [ebp - 0x10]
004fd09c 7f07                     jg        0x4fd0a5
004fd09e 8b45f8                   mov       eax, dword ptr [ebp - 8]
004fd0a1 85c0                     test      eax, eax
004fd0a3 7514                     jne       0x4fd0b9
004fd0a5 8b06                     mov       eax, dword ptr [esi]
004fd0a7 8bce                     mov       ecx, esi
004fd0a9 ff90dc030000             call      dword ptr [eax + 0x3dc]
004fd0af 84c0                     test      al, al
004fd0b1 7506                     jne       0x4fd0b9
004fd0b3 8975f8                   mov       dword ptr [ebp - 8], esi
004fd0b6 895df0                   mov       dword ptr [ebp - 0x10], ebx
004fd0b9 8b5dfc                   mov       ebx, dword ptr [ebp - 4]
004fd0bc 8b75ec                   mov       esi, dword ptr [ebp - 0x14]
004fd0bf 43                       inc       ebx
004fd0c0 e9cffeffff               jmp       0x4fcf94
004fd0c5 8b45f8                   mov       eax, dword ptr [ebp - 8]
004fd0c8 3bf0                     cmp       esi, eax
004fd0ca 741c                     je        0x4fd0e8
004fd0cc 8b17                     mov       edx, dword ptr [edi]
004fd0ce 50                       push      eax
004fd0cf 8bcf                     mov       ecx, edi
004fd0d1 ff922c060000             call      dword ptr [edx + 0x62c]
004fd0d7 8b07                     mov       eax, dword ptr [edi]
004fd0d9 8bcf                     mov       ecx, edi
004fd0db ff909c060000             call      dword ptr [eax + 0x69c]
004fd0e1 5e                       pop       esi
004fd0e2 5b                       pop       ebx
004fd0e3 5f                       pop       edi
004fd0e4 8be5                     mov       esp, ebp
004fd0e6 5d                       pop       ebp
004fd0e7 c3                       ret       
004fd0e8 8b17                     mov       edx, dword ptr [edi]
004fd0ea 8bcf                     mov       ecx, edi
004fd0ec 56                       push      esi
004fd0ed ff922c060000             call      dword ptr [edx + 0x62c]
004fd0f3 5e                       pop       esi
004fd0f4 5b                       pop       ebx
004fd0f5 5f                       pop       edi
004fd0f6 8be5                     mov       esp, ebp
004fd0f8 5d                       pop       ebp
004fd0f9 c3                       ret       
004fd0fa cc                       int3      
004fd0fb cc                       int3      
004fd0fc cc                       int3      
004fd0fd cc                       int3      
004fd0fe cc                       int3      
004fd0ff cc                       int3      
004fd100 55                       push      ebp
004fd101 8bec                     mov       ebp, esp
004fd103 56                       push      esi
004fd104 8bf1                     mov       esi, ecx
004fd106 8b06                     mov       eax, dword ptr [esi]
004fd108 57                       push      edi
004fd109 ff9038020000             call      dword ptr [eax + 0x238]
004fd10f 99                       cdq       
004fd110 2bc2                     sub       eax, edx
004fd112 8b16                     mov       edx, dword ptr [esi]
004fd114 8bf8                     mov       edi, eax
004fd116 8bce                     mov       ecx, esi
004fd118 d1ff                     sar       edi, 1
004fd11a ff9234020000             call      dword ptr [edx + 0x234]
004fd120 8b5508                   mov       edx, dword ptr [ebp + 8]
004fd123 33c9                     xor       ecx, ecx
004fd125 3bc7                     cmp       eax, edi
004fd127 0f9ec1                   setle     cl
004fd12a 6aff                     push      -1
004fd12c 6a00                     push      0
004fd12e 6a01                     push      1
004fd130 6811020000               push      0x211
004fd135 49                       dec       ecx
004fd136 83e102                   and       ecx, 2
004fd139 890a                     mov       dword ptr [edx], ecx
004fd13b 8bce                     mov       ecx, esi
004fd13d e8bedcffff               call      0x4fae00
004fd142 8bf0                     mov       esi, eax
004fd144 85f6                     test      esi, esi
004fd146 750b                     jne       0x4fd153
004fd148 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004fd14b 5f                       pop       edi
004fd14c 8930                     mov       dword ptr [eax], esi
004fd14e 5e                       pop       esi
004fd14f 5d                       pop       ebp
004fd150 c20800                   ret       8
004fd153 8b0d4c310001             mov       ecx, dword ptr [0x100314c]
004fd159 6a00                     push      0
004fd15b e880020600               call      0x55d3e0
004fd160 3bf0                     cmp       esi, eax
004fd162 7e0f                     jle       0x4fd173
004fd164 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004fd167 5f                       pop       edi
004fd168 c70102000000             mov       dword ptr [ecx], 2
004fd16e 5e                       pop       esi
004fd16f 5d                       pop       ebp
004fd170 c20800                   ret       8
004fd173 8b0d4c310001             mov       ecx, dword ptr [0x100314c]
004fd179 6a00                     push      0
004fd17b e860020600               call      0x55d3e0
004fd180 33d2                     xor       edx, edx
004fd182 3bf0                     cmp       esi, eax
004fd184 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004fd187 0f94c2                   sete      dl
004fd18a 5f                       pop       edi
004fd18b 5e                       pop       esi
004fd18c 8910                     mov       dword ptr [eax], edx
004fd18e 5d                       pop       ebp
004fd18f c20800                   ret       8
004fd192 cc                       int3      
004fd193 cc                       int3      
004fd194 cc                       int3      
004fd195 cc                       int3      
004fd196 cc                       int3      
004fd197 cc                       int3      
004fd198 cc                       int3      
004fd199 cc                       int3      
004fd19a cc                       int3      
004fd19b cc                       int3      
004fd19c cc                       int3      
004fd19d cc                       int3      
004fd19e cc                       int3      
004fd19f cc                       int3      
004fd1a0 55                       push      ebp
004fd1a1 8bec                     mov       ebp, esp
004fd1a3 6aff                     push      -1
004fd1a5 68c09cc500               push      0xc59cc0
004fd1aa 64a100000000             mov       eax, dword ptr fs:[0]
004fd1b0 50                       push      eax
004fd1b1 64892500000000           mov       dword ptr fs:[0], esp
004fd1b8 83ec54                   sub       esp, 0x54
004fd1bb 53                       push      ebx
004fd1bc 8bd9                     mov       ebx, ecx
004fd1be 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004fd1c4 56                       push      esi
004fd1c5 33f6                     xor       esi, esi
004fd1c7 3bc6                     cmp       eax, esi
004fd1c9 0f8487030000             je        0x4fd556
004fd1cf 57                       push      edi
004fd1d0 8d45f3                   lea       eax, [ebp - 0xd]
004fd1d3 50                       push      eax
004fd1d4 8d4df3                   lea       ecx, [ebp - 0xd]
004fd1d7 51                       push      ecx
004fd1d8 8d4da0                   lea       ecx, [ebp - 0x60]
004fd1db 8975dc                   mov       dword ptr [ebp - 0x24], esi
004fd1de 8975ec                   mov       dword ptr [ebp - 0x14], esi
004fd1e1 e82ac20000               call      0x509410
004fd1e6 8975fc                   mov       dword ptr [ebp - 4], esi
004fd1e9 33ff                     xor       edi, edi
004fd1eb eb03                     jmp       0x4fd1f0
004fd1ed 8d4900                   lea       ecx, [ecx]
004fd1f0 8b8b00010000             mov       ecx, dword ptr [ebx + 0x100]
004fd1f6 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004fd1fc 3bd6                     cmp       edx, esi
004fd1fe 7504                     jne       0x4fd204
004fd200 33c0                     xor       eax, eax
004fd202 eb0b                     jmp       0x4fd20f
004fd204 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004fd20a 2bc2                     sub       eax, edx
004fd20c c1f802                   sar       eax, 2
004fd20f 3bf8                     cmp       edi, eax
004fd211 0f8d8a000000             jge       0x4fd2a1
004fd217 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004fd21d 3bd6                     cmp       edx, esi
004fd21f 74                       .byte     0x74
