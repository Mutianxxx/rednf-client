004f58c0 55                       push      ebp
004f58c1 8bec                     mov       ebp, esp
004f58c3 6aff                     push      -1
004f58c5 68b89bc500               push      0xc59bb8
004f58ca 64a100000000             mov       eax, dword ptr fs:[0]
004f58d0 50                       push      eax
004f58d1 64892500000000           mov       dword ptr fs:[0], esp
004f58d8 83ec08                   sub       esp, 8
004f58db 53                       push      ebx
004f58dc 8bd9                     mov       ebx, ecx
004f58de 8b03                     mov       eax, dword ptr [ebx]
004f58e0 57                       push      edi
004f58e1 ff9060030000             call      dword ptr [eax + 0x360]
004f58e7 8bc8                     mov       ecx, eax
004f58e9 e872c7f0ff               call      0x402060
004f58ee 8b7d08                   mov       edi, dword ptr [ebp + 8]
004f58f1 3bc7                     cmp       eax, edi
004f58f3 0f84b0020000             je        0x4f5ba9
004f58f9 8b13                     mov       edx, dword ptr [ebx]
004f58fb 56                       push      esi
004f58fc 8bcb                     mov       ecx, ebx
004f58fe ff9260030000             call      dword ptr [edx + 0x360]
004f5904 8bc8                     mov       ecx, eax
004f5906 e855c7f0ff               call      0x402060
004f590b 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004f590e 2bc7                     sub       eax, edi
004f5910 85c0                     test      eax, eax
004f5912 7e24                     jle       0x4f5938
004f5914 85f6                     test      esi, esi
004f5916 7420                     je        0x4f5938
004f5918 8b06                     mov       eax, dword ptr [esi]
004f591a 8bce                     mov       ecx, esi
004f591c ff90a4020000             call      dword ptr [eax + 0x2a4]
004f5922 85c0                     test      eax, eax
004f5924 7412                     je        0x4f5938
004f5926 8b16                     mov       edx, dword ptr [esi]
004f5928 8bce                     mov       ecx, esi
004f592a ff92a4020000             call      dword ptr [edx + 0x2a4]
004f5930 50                       push      eax
004f5931 8bcb                     mov       ecx, ebx
004f5933 e878aaffff               call      0x4f03b0
004f5938 85ff                     test      edi, edi
004f593a 0f8f95000000             jg        0x4f59d5
004f5940 8d83501e0000             lea       eax, [ebx + 0x1e50]
004f5946 6813000200               push      0x20013
004f594b 50                       push      eax
004f594c e81f843b00               call      0x8add70
004f5951 83c408                   add       esp, 8
004f5954 84c0                     test      al, al
004f5956 747d                     je        0x4f59d5
004f5958 8b13                     mov       edx, dword ptr [ebx]
004f595a 8bcb                     mov       ecx, ebx
004f595c ff525c                   call      dword ptr [edx + 0x5c]
004f595f 8d4804                   lea       ecx, [eax + 4]
004f5962 e8f9c6f0ff               call      0x402060
004f5967 83f801                   cmp       eax, 1
004f596a 7469                     je        0x4f59d5
004f596c 8b03                     mov       eax, dword ptr [ebx]
004f596e 8bcb                     mov       ecx, ebx
004f5970 ff9038020000             call      dword ptr [eax + 0x238]
004f5976 8bcb                     mov       ecx, ebx
004f5978 8bf8                     mov       edi, eax
004f597a e81167faff               call      0x49c090
004f597f 84c0                     test      al, al
004f5981 7427                     je        0x4f59aa
004f5983 6a00                     push      0
004f5985 6a00                     push      0
004f5987 8b13                     mov       edx, dword ptr [ebx]
004f5989 6a00                     push      0
004f598b 6a00                     push      0
004f598d 6a00                     push      0
004f598f 6a04                     push      4
004f5991 6a00                     push      0
004f5993 6a00                     push      0
004f5995 6a00                     push      0
004f5997 6a00                     push      0
004f5999 6a00                     push      0
004f599b 6a03                     push      3
004f599d 6881bb0000               push      0xbb81
004f59a2 8bcb                     mov       ecx, ebx
004f59a4 ff92b8020000             call      dword ptr [edx + 0x2b8]
004f59aa 6813000200               push      0x20013
004f59af 8bcb                     mov       ecx, ebx
004f59b1 e88afeffff               call      0x4f5840
004f59b6 6a00                     push      0
004f59b8 6a00                     push      0
004f59ba 6a08                     push      8
004f59bc 8bcb                     mov       ecx, ebx
004f59be e8ad535700               call      0xa6ad70
004f59c3 68d0070000               push      0x7d0
004f59c8 6a00                     push      0
004f59ca 6a00                     push      0
004f59cc 6a09                     push      9
004f59ce 8bcb                     mov       ecx, ebx
004f59d0 e84b535700               call      0xa6ad20
004f59d5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004f59d8 50                       push      eax
004f59d9 56                       push      esi
004f59da 57                       push      edi
004f59db 8bcb                     mov       ecx, ebx
004f59dd e81ef4fbff               call      0x4b4e00
004f59e2 b90ce6ff00               mov       ecx, 0xffe60c
004f59e7 e874c6f0ff               call      0x402060
004f59ec 85c0                     test      eax, eax
004f59ee 0f85b4010000             jne       0x4f5ba8
004f59f4 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004f59fa 85c0                     test      eax, eax
004f59fc 0f84a6010000             je        0x4f5ba8
004f5a02 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
004f5a08 85c9                     test      ecx, ecx
004f5a0a 0f8498010000             je        0x4f5ba8
004f5a10 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f5a16 81c140100000             add       ecx, 0x1040
004f5a1c e83fc6f0ff               call      0x402060
004f5a21 83f803                   cmp       eax, 3
004f5a24 0f857e010000             jne       0x4f5ba8
004f5a2a 85ff                     test      edi, edi
004f5a2c 8b8b00010000             mov       ecx, dword ptr [ebx + 0x100]
004f5a32 8b8114010000             mov       eax, dword ptr [ecx + 0x114]
004f5a38 8bb0b4000000             mov       esi, dword ptr [eax + 0xb4]
004f5a3e 0f8f64010000             jg        0x4f5ba8
004f5a44 85f6                     test      esi, esi
004f5a46 0f845c010000             je        0x4f5ba8
004f5a4c b9604c0001               mov       ecx, 0x1004c60
004f5a51 e80ac6f0ff               call      0x402060
004f5a56 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5a59 c1e004                   shl       eax, 4
004f5a5c 03c1                     add       eax, ecx
004f5a5e 8bc8                     mov       ecx, eax
004f5a60 e80bed1b00               call      0x6b4770
004f5a65 84c0                     test      al, al
004f5a67 0f853b010000             jne       0x4f5ba8
004f5a6d 8d5508                   lea       edx, [ebp + 8]
004f5a70 33ff                     xor       edi, edi
004f5a72 52                       push      edx
004f5a73 8d4dec                   lea       ecx, [ebp - 0x14]
004f5a76 897d08                   mov       dword ptr [ebp + 8], edi
004f5a79 e8d2c6f0ff               call      0x402150
004f5a7e b9604c0001               mov       ecx, 0x1004c60
004f5a83 897dfc                   mov       dword ptr [ebp - 4], edi
004f5a86 c6450b00                 mov       byte ptr [ebp + 0xb], 0
004f5a8a 897d0c                   mov       dword ptr [ebp + 0xc], edi
004f5a8d e8cec5f0ff               call      0x402060
004f5a92 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5a95 c1e004                   shl       eax, 4
004f5a98 03c1                     add       eax, ecx
004f5a9a 8bc8                     mov       ecx, eax
004f5a9c e8af3b2200               call      0x719650
004f5aa1 85c0                     test      eax, eax
004f5aa3 0f86d4000000             jbe       0x4f5b7d
004f5aa9 8da42400000000           lea       esp, [esp]
004f5ab0 b9604c0001               mov       ecx, 0x1004c60
004f5ab5 e8a6c5f0ff               call      0x402060
004f5aba 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5abd c1e004                   shl       eax, 4
004f5ac0 03c1                     add       eax, ecx
004f5ac2 8b4004                   mov       eax, dword ptr [eax + 4]
004f5ac5 833c0702                 cmp       dword ptr [edi + eax], 2
004f5ac9 7562                     jne       0x4f5b2d
004f5acb b9604c0001               mov       ecx, 0x1004c60
004f5ad0 e88bc5f0ff               call      0x402060
004f5ad5 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5ad8 c1e004                   shl       eax, 4
004f5adb 03c1                     add       eax, ecx
004f5add 8b4004                   mov       eax, dword ptr [eax + 4]
004f5ae0 8b8b04020000             mov       ecx, dword ptr [ebx + 0x204]
004f5ae6 394c0704                 cmp       dword ptr [edi + eax + 4], ecx
004f5aea 7541                     jne       0x4f5b2d
004f5aec b9604c0001               mov       ecx, 0x1004c60
004f5af1 e86ac5f0ff               call      0x402060
004f5af6 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5af9 c1e004                   shl       eax, 4
004f5afc 03c1                     add       eax, ecx
004f5afe 8b4004                   mov       eax, dword ptr [eax + 4]
004f5b01 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004f5b05 85c9                     test      ecx, ecx
004f5b07 7424                     je        0x4f5b2d
004f5b09 b9604c0001               mov       ecx, 0x1004c60
004f5b0e e84dc5f0ff               call      0x402060
004f5b13 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5b16 c1e004                   shl       eax, 4
004f5b19 03c1                     add       eax, ecx
004f5b1b 8b4004                   mov       eax, dword ptr [eax + 4]
004f5b1e 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
004f5b22 8d440708                 lea       eax, [edi + eax + 8]
004f5b26 49                       dec       ecx
004f5b27 8908                     mov       dword ptr [eax], ecx
004f5b29 c6450b01                 mov       byte ptr [ebp + 0xb], 1
004f5b2d b9604c0001               mov       ecx, 0x1004c60
004f5b32 e829c5f0ff               call      0x402060
004f5b37 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5b3a c1e004                   shl       eax, 4
004f5b3d 03c1                     add       eax, ecx
004f5b3f 8b4004                   mov       eax, dword ptr [eax + 4]
004f5b42 8b440708                 mov       eax, dword ptr [edi + eax + 8]
004f5b46 8d4d10                   lea       ecx, [ebp + 0x10]
004f5b49 51                       push      ecx
004f5b4a 8d4dec                   lea       ecx, [ebp - 0x14]
004f5b4d 894510                   mov       dword ptr [ebp + 0x10], eax
004f5b50 e8bba0f1ff               call      0x40fc10
004f5b55 ff450c                   inc       dword ptr [ebp + 0xc]
004f5b58 b9604c0001               mov       ecx, 0x1004c60
004f5b5d 83c70c                   add       edi, 0xc
004f5b60 e8fbc4f0ff               call      0x402060
004f5b65 8b4e04                   mov       ecx, dword ptr [esi + 4]
004f5b68 c1e004                   shl       eax, 4
004f5b6b 03c1                     add       eax, ecx
004f5b6d 8bc8                     mov       ecx, eax
004f5b6f e8dc3a2200               call      0x719650
004f5b74 39450c                   cmp       dword ptr [ebp + 0xc], eax
004f5b77 0f8233ffffff             jb        0x4f5ab0
004f5b7d 8d4dec                   lea       ecx, [ebp - 0x14]
004f5b80 e8dbc4f0ff               call      0x402060
004f5b85 85c0                     test      eax, eax
004f5b87 7510                     jne       0x4f5b99
004f5b89 8a450b                   mov       al, byte ptr [ebp + 0xb]
004f5b8c 84c0                     test      al, al
004f5b8e 7409                     je        0x4f5b99
004f5b90 6a01                     push      1
004f5b92 8bcb                     mov       ecx, ebx
004f5b94 e897b7faff               call      0x4a1330
004f5b99 8d4dec                   lea       ecx, [ebp - 0x14]
004f5b9c c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004f5ba3 e868c4f0ff               call      0x402010
004f5ba8 5e                       pop       esi
004f5ba9 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004f5bac 5f                       pop       edi
004f5bad 5b                       pop       ebx
004f5bae 64890d00000000           mov       dword ptr fs:[0], ecx
004f5bb5 8be5                     mov       esp, ebp
004f5bb7 5d                       pop       ebp
004f5bb8 c20c00                   ret       0xc
004f5bbb cc                       int3      
004f5bbc cc                       int3      
004f5bbd cc                       int3      
004f5bbe cc                       int3      
004f5bbf cc                       int3      
004f5bc0 55                       push      ebp
004f5bc1 8bec                     mov       ebp, esp
004f5bc3 53                       push      ebx
004f5bc4 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004f5bc7 56                       push      esi
004f5bc8 57                       push      edi
004f5bc9 53                       push      ebx
004f5bca 8bf1                     mov       esi, ecx
004f5bcc e8bf64fbff               call      0x4ac090
004f5bd1 33ff                     xor       edi, edi
004f5bd3 8b8608230000             mov       eax, dword ptr [esi + 0x2308]
004f5bd9 85c0                     test      eax, eax
004f5bdb 7432                     je        0x4f5c0f
004f5bdd 8b8e0c230000             mov       ecx, dword ptr [esi + 0x230c]
004f5be3 2bc8                     sub       ecx, eax
004f5be5 b8398ee338               mov       eax, 0x38e38e39
004f5bea f7e9                     imul      ecx
004f5bec c1fa03                   sar       edx, 3
004f5bef 8bc2                     mov       eax, edx
004f5bf1 c1e81f                   shr       eax, 0x1f
004f5bf4 03c2                     add       eax, edx
004f5bf6 3bf8                     cmp       edi, eax
004f5bf8 7315                     jae       0x4f5c0f
004f5bfa 8b8648230000             mov       eax, dword ptr [esi + 0x2348]
004f5c00 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004f5c03 8d04b8                   lea       eax, [eax + edi*4]
004f5c06 53                       push      ebx
004f5c07 e8847e2500               call      0x74da90
004f5c0c 47                       inc       edi
004f5c0d ebc4                     jmp       0x4f5bd3
004f5c0f 5f                       pop       edi
004f5c10 5e                       pop       esi
004f5c11 5b                       pop       ebx
004f5c12 5d                       pop       ebp
004f5c13 c20400                   ret       4
004f5c16 cc                       int3      
004f5c17 cc                       int3      
004f5c18 cc                       int3      
004f5c19 cc                       int3      
004f5c1a cc                       int3      
004f5c1b cc                       int3      
004f5c1c cc                       int3      
004f5c1d cc                       int3      
004f5c1e cc                       int3      
004f5c1f cc                       int3      
004f5c20 55                       push      ebp
004f5c21 8bec                     mov       ebp, esp
004f5c23 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004f5c26 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004f5c29 56                       push      esi
004f5c2a 57                       push      edi
004f5c2b 50                       push      eax
004f5c2c 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004f5c2f 8bf1                     mov       esi, ecx
004f5c31 8b4d18                   mov       ecx, dword ptr [ebp + 0x18]
004f5c34 51                       push      ecx
004f5c35 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f5c38 52                       push      edx
004f5c39 8b5508                   mov       edx, dword ptr [ebp + 8]
004f5c3c 50                       push      eax
004f5c3d 51                       push      ecx
004f5c3e 52                       push      edx
004f5c3f 8bce                     mov       ecx, esi
004f5c41 e83a5bffff               call      0x4eb780
004f5c46 8bf8                     mov       edi, eax
004f5c48 8a8608050000             mov       al, byte ptr [esi + 0x508]
004f5c4e 84c0                     test      al, al
004f5c50 745c                     je        0x4f5cae
004f5c52 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f5c58 84c0                     test      al, al
004f5c5a 7452                     je        0x4f5cae
004f5c5c 6a0d                     push      0xd
004f5c5e 8bce                     mov       ecx, esi
004f5c60 e80b2dffff               call      0x4e8970
004f5c65 84c0                     test      al, al
004f5c67 7417                     je        0x4f5c80
004f5c69 8b8e481a0000             mov       ecx, dword ptr [esi + 0x1a48]
004f5c6f 8b8604050000             mov       eax, dword ptr [esi + 0x504]
004f5c75 8d0481                   lea       eax, [ecx + eax*4]
004f5c78 8b08                     mov       ecx, dword ptr [eax]
004f5c7a 8b11                     mov       edx, dword ptr [ecx]
004f5c7c 57                       push      edi
004f5c7d ff5210                   call      dword ptr [edx + 0x10]
004f5c80 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f5c86 84c0                     test      al, al
004f5c88 7424                     je        0x4f5cae
004f5c8a 6a00                     push      0
004f5c8c 8bce                     mov       ecx, esi
004f5c8e e8dd2cffff               call      0x4e8970
004f5c93 84c0                     test      al, al
004f5c95 7417                     je        0x4f5cae
004f5c97 8b8e381a0000             mov       ecx, dword ptr [esi + 0x1a38]
004f5c9d 8b8604050000             mov       eax, dword ptr [esi + 0x504]
004f5ca3 8d0481                   lea       eax, [ecx + eax*4]
004f5ca6 8b08                     mov       ecx, dword ptr [eax]
004f5ca8 8b11                     mov       edx, dword ptr [ecx]
004f5caa 57                       push      edi
004f5cab ff5210                   call      dword ptr [edx + 0x10]
004f5cae 8bc7                     mov       eax, edi
004f5cb0 5f                       pop       edi
004f5cb1 5e                       pop       esi
004f5cb2 5d                       pop       ebp
004f5cb3 c21800                   ret       0x18
004f5cb6 cc                       int3      
004f5cb7 cc                       int3      
004f5cb8 cc                       int3      
004f5cb9 cc                       int3      
004f5cba cc                       int3      
004f5cbb cc                       int3      
004f5cbc cc                       int3      
004f5cbd cc                       int3      
004f5cbe cc                       int3      
004f5cbf cc                       int3      
004f5cc0 55                       push      ebp
004f5cc1 8bec                     mov       ebp, esp
004f5cc3 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f5cc9 53                       push      ebx
004f5cca e86146f4ff               call      0x43a330
004f5ccf 8bd8                     mov       ebx, eax
004f5cd1 85db                     test      ebx, ebx
004f5cd3 7513                     jne       0x4f5ce8
004f5cd5 68b05acd00               push      0xcd5ab0
004f5cda ff15bc2eff00             call      dword ptr [0xff2ebc]
004f5ce0 83c404                   add       esp, 4
004f5ce3 5b                       pop       ebx
004f5ce4 5d                       pop       ebp
004f5ce5 c20400                   ret       4
004f5ce8 8b83b0000000             mov       eax, dword ptr [ebx + 0xb0]
004f5cee 85c0                     test      eax, eax
004f5cf0 7513                     jne       0x4f5d05
004f5cf2 68205acd00               push      0xcd5a20
004f5cf7 ff15bc2eff00             call      dword ptr [0xff2ebc]
004f5cfd 83c404                   add       esp, 4
004f5d00 5b                       pop       ebx
004f5d01 5d                       pop       ebp
004f5d02 c20400                   ret       4
004f5d05 57                       push      edi
004f5d06 33ff                     xor       edi, edi
004f5d08 56                       push      esi
004f5d09 8da42400000000           lea       esp, [esp]
004f5d10 8b8bb0000000             mov       ecx, dword ptr [ebx + 0xb0]
004f5d16 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f5d19 85d2                     test      edx, edx
004f5d1b 7504                     jne       0x4f5d21
004f5d1d 33c0                     xor       eax, eax
004f5d1f eb08                     jmp       0x4f5d29
004f5d21 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f5d24 2bc2                     sub       eax, edx
004f5d26 c1f802                   sar       eax, 2
004f5d29 3bf8                     cmp       edi, eax
004f5d2b 7d68                     jge       0x4f5d95
004f5d2d 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f5d30 85d2                     test      edx, edx
004f5d32 7416                     je        0x4f5d4a
004f5d34 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f5d37 2bc2                     sub       eax, edx
004f5d39 c1f802                   sar       eax, 2
004f5d3c 3bf8                     cmp       edi, eax
004f5d3e 730a                     jae       0x4f5d4a
004f5d40 8bc2                     mov       eax, edx
004f5d42 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004f5d45 8d04b8                   lea       eax, [eax + edi*4]
004f5d48 eb02                     jmp       0x4f5d4c
004f5d4a 33c9                     xor       ecx, ecx
004f5d4c 8b11                     mov       edx, dword ptr [ecx]
004f5d4e 6881000000               push      0x81
004f5d53 ff522c                   call      dword ptr [edx + 0x2c]
004f5d56 84c0                     test      al, al
004f5d58 7431                     je        0x4f5d8b
004f5d5a 8b8bb0000000             mov       ecx, dword ptr [ebx + 0xb0]
004f5d60 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f5d63 85d2                     test      edx, edx
004f5d65 7424                     je        0x4f5d8b
004f5d67 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f5d6a 2bc2                     sub       eax, edx
004f5d6c c1f802                   sar       eax, 2
004f5d6f 3bf8                     cmp       edi, eax
004f5d71 7318                     jae       0x4f5d8b
004f5d73 8bc2                     mov       eax, edx
004f5d75 8b34b8                   mov       esi, dword ptr [eax + edi*4]
004f5d78 85f6                     test      esi, esi
004f5d7a 8d04b8                   lea       eax, [eax + edi*4]
004f5d7d 740c                     je        0x4f5d8b
004f5d7f 8b16                     mov       edx, dword ptr [esi]
004f5d81 8bce                     mov       ecx, esi
004f5d83 ff5240                   call      dword ptr [edx + 0x40]
004f5d86 3b4508                   cmp       eax, dword ptr [ebp + 8]
004f5d89 7403                     je        0x4f5d8e
004f5d8b 47                       inc       edi
004f5d8c eb82                     jmp       0x4f5d10
004f5d8e c6861008000001           mov       byte ptr [esi + 0x810], 1
004f5d95 5e                       pop       esi
004f5d96 5f                       pop       edi
004f5d97 5b                       pop       ebx
004f5d98 5d                       pop       ebp
004f5d99 c20400                   ret       4
004f5d9c cc                       int3      
004f5d9d cc                       int3      
004f5d9e cc                       int3      
004f5d9f cc                       int3      
004f5da0 55                       push      ebp
004f5da1 8bec                     mov       ebp, esp
004f5da3 83ec08                   sub       esp, 8
004f5da6 53                       push      ebx
004f5da7 56                       push      esi
004f5da8 57                       push      edi
004f5da9 33ff                     xor       edi, edi
004f5dab 8bf1                     mov       esi, ecx
004f5dad 33db                     xor       ebx, ebx
004f5daf 8b866c220000             mov       eax, dword ptr [esi + 0x226c]
004f5db5 85c0                     test      eax, eax
004f5db7 895dfc                   mov       dword ptr [ebp - 4], ebx
004f5dba 0f8475030000             je        0x4f6135
004f5dc0 8b8e70220000             mov       ecx, dword ptr [esi + 0x2270]
004f5dc6 2bc8                     sub       ecx, eax
004f5dc8 b8e9a28b2e               mov       eax, 0x2e8ba2e9
004f5dcd f7e9                     imul      ecx
004f5dcf c1fa03                   sar       edx, 3
004f5dd2 8bc2                     mov       eax, edx
004f5dd4 c1e81f                   shr       eax, 0x1f
004f5dd7 03c2                     add       eax, edx
004f5dd9 3bf8                     cmp       edi, eax
004f5ddb 0f8354030000             jae       0x4f6135
004f5de1 8b866c220000             mov       eax, dword ptr [esi + 0x226c]
004f5de7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f5dea 8b1418                   mov       edx, dword ptr [eax + ebx]
004f5ded 03c3                     add       eax, ebx
004f5def 3bca                     cmp       ecx, edx
004f5df1 0f8532030000             jne       0x4f6129
004f5df7 8bce                     mov       ecx, esi
004f5df9 e89262faff               call      0x49c090
004f5dfe 84c0                     test      al, al
004f5e00 0f845d010000             je        0x4f5f63
004f5e06 8b966c220000             mov       edx, dword ptr [esi + 0x226c]
004f5e0c 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f5e12 8b8824010000             mov       ecx, dword ptr [eax + 0x124]
004f5e18 8b441a1c                 mov       eax, dword ptr [edx + ebx + 0x1c]
004f5e1c 03d3                     add       edx, ebx
004f5e1e 3bc8                     cmp       ecx, eax
004f5e20 0f8ce4000000             jl        0x4f5f0a
004f5e26 8b8e80220000             mov       ecx, dword ptr [esi + 0x2280]
004f5e2c 33c0                     xor       eax, eax
004f5e2e 8bc7                     mov       eax, edi
004f5e30 8bd8                     mov       ebx, eax
004f5e32 c1eb05                   shr       ebx, 5
004f5e35 8d1c99                   lea       ebx, [ecx + ebx*4]
004f5e38 83e01f                   and       eax, 0x1f
004f5e3b b901000000               mov       ecx, 1
004f5e40 894df8                   mov       dword ptr [ebp - 8], ecx
004f5e43 8bc8                     mov       ecx, eax
004f5e45 8b45f8                   mov       eax, dword ptr [ebp - 8]
004f5e48 d3e0                     shl       eax, cl
004f5e4a 8503                     test      dword ptr [ebx], eax
004f5e4c 0f85b8000000             jne       0x4f5f0a
004f5e52 8b4214                   mov       eax, dword ptr [edx + 0x14]
004f5e55 85c0                     test      eax, eax
004f5e57 7543                     jne       0x4f5e9c
004f5e59 8b4228                   mov       eax, dword ptr [edx + 0x28]
004f5e5c db4208                   fild      dword ptr [edx + 8]
004f5e5f 8b4a24                   mov       ecx, dword ptr [edx + 0x24]
004f5e62 50                       push      eax
004f5e63 8b4210                   mov       eax, dword ptr [edx + 0x10]
004f5e66 51                       push      ecx
004f5e67 50                       push      eax
004f5e68 51                       push      ecx
004f5e69 8bce                     mov       ecx, esi
004f5e6b d91c24                   fstp      dword ptr [esp]
004f5e6e e84d92ffff               call      0x4ef0c0
004f5e73 8945f8                   mov       dword ptr [ebp - 8], eax
004f5e76 db45f8                   fild      dword ptr [ebp - 8]
004f5e79 d815d8b9cc00             fcom      dword ptr [0xccb9d8]
004f5e7f dfe0                     fnstsw    ax
004f5e81 f6c405                   test      ah, 5
004f5e84 7a08                     jp        0x4f5e8e
004f5e86 ddd8                     fstp      st(0)
004f5e88 d905d8b9cc00             fld       dword ptr [0xccb9d8]
004f5e8e d80dd04bcd00             fmul      dword ptr [0xcd4bd0]
004f5e94 e8abb67000               call      0xc01544
004f5e99 50                       push      eax
004f5e9a eb63                     jmp       0x4f5eff
004f5e9c 837a1401                 cmp       dword ptr [edx + 0x14], 1
004f5ea0 752e                     jne       0x4f5ed0
004f5ea2 8b4a28                   mov       ecx, dword ptr [edx + 0x28]
004f5ea5 db4208                   fild      dword ptr [edx + 8]
004f5ea8 8b4224                   mov       eax, dword ptr [edx + 0x24]
004f5eab 51                       push      ecx
004f5eac 8b4a10                   mov       ecx, dword ptr [edx + 0x10]
004f5eaf 50                       push      eax
004f5eb0 51                       push      ecx
004f5eb1 e88eb67000               call      0xc01544
004f5eb6 50                       push      eax
004f5eb7 8bce                     mov       ecx, esi
004f5eb9 e87290ffff               call      0x4eef30
004f5ebe 8b866c220000             mov       eax, dword ptr [esi + 0x226c]
004f5ec4 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004f5ec7 8b540804                 mov       edx, dword ptr [eax + ecx + 4]
004f5ecb 03c1                     add       eax, ecx
004f5ecd 52                       push      edx
004f5ece eb2f                     jmp       0x4f5eff
004f5ed0 837a1402                 cmp       dword ptr [edx + 0x14], 2
004f5ed4 7534                     jne       0x4f5f0a
004f5ed6 8b4228                   mov       eax, dword ptr [edx + 0x28]
004f5ed9 db4208                   fild      dword ptr [edx + 8]
004f5edc 8b4a24                   mov       ecx, dword ptr [edx + 0x24]
004f5edf 50                       push      eax
