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
