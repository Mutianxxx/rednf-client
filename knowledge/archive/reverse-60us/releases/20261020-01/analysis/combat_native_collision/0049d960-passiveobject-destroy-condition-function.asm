0049d960 56                       push      esi
0049d961 8bf1                     mov       esi, ecx
0049d963 ff155cf04001             call      dword ptr [0x140f05c]
0049d969 8986c4050000             mov       dword ptr [esi + 0x5c4], eax
0049d96f 8b865c050000             mov       eax, dword ptr [esi + 0x55c]
0049d975 83f8ff                   cmp       eax, -1
0049d978 0f84eb020000             je        0x49dc69
0049d97e 85c0                     test      eax, eax
0049d980 57                       push      edi
0049d981 751e                     jne       0x49d9a1
0049d983 8b06                     mov       eax, dword ptr [esi]
0049d985 8bce                     mov       ecx, esi
0049d987 ff90f4000000             call      dword ptr [eax + 0xf4]
0049d98d 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
0049d993 84c9                     test      cl, cl
0049d995 740a                     je        0x49d9a1
0049d997 8a86a4050000             mov       al, byte ptr [esi + 0x5a4]
0049d99d 84c0                     test      al, al
0049d99f 7477                     je        0x49da18
0049d9a1 83be5c05000001           cmp       dword ptr [esi + 0x55c], 1
0049d9a8 7518                     jne       0x49d9c2
0049d9aa 8b16                     mov       edx, dword ptr [esi]
0049d9ac 8bce                     mov       ecx, esi
0049d9ae ff929c000000             call      dword ptr [edx + 0x9c]
0049d9b4 85c0                     test      eax, eax
0049d9b6 750a                     jne       0x49d9c2
0049d9b8 8a86a4050000             mov       al, byte ptr [esi + 0x5a4]
0049d9be 84c0                     test      al, al
0049d9c0 7456                     je        0x49da18
0049d9c2 8b865c050000             mov       eax, dword ptr [esi + 0x55c]
0049d9c8 83f802                   cmp       eax, 2
0049d9cb 7522                     jne       0x49d9ef
0049d9cd 8b8ec4050000             mov       ecx, dword ptr [esi + 0x5c4]
0049d9d3 8bbec0050000             mov       edi, dword ptr [esi + 0x5c0]
0049d9d9 8b96bc050000             mov       edx, dword ptr [esi + 0x5bc]
0049d9df 2bcf                     sub       ecx, edi
0049d9e1 3bca                     cmp       ecx, edx
0049d9e3 7e0a                     jle       0x49d9ef
0049d9e5 8a8ea4050000             mov       cl, byte ptr [esi + 0x5a4]
0049d9eb 84c9                     test      cl, cl
0049d9ed 7429                     je        0x49da18
0049d9ef 83f803                   cmp       eax, 3
0049d9f2 0f8535010000             jne       0x49db2d
0049d9f8 8b16                     mov       edx, dword ptr [esi]
0049d9fa 8bce                     mov       ecx, esi
0049d9fc ff929c000000             call      dword ptr [edx + 0x9c]
0049da02 85c0                     test      eax, eax
0049da04 0f8523010000             jne       0x49db2d
0049da0a 8a86a4050000             mov       al, byte ptr [esi + 0x5a4]
0049da10 84c0                     test      al, al
0049da12 0f8515010000             jne       0x49db2d
0049da18 53                       push      ebx
0049da19 8bce                     mov       ecx, esi
0049da1b e870e6ffff               call      0x49c090
0049da20 84c0                     test      al, al
0049da22 0f8499000000             je        0x49dac1
0049da28 8a86a4050000             mov       al, byte ptr [esi + 0x5a4]
0049da2e 84c0                     test      al, al
0049da30 0f858b000000             jne       0x49dac1
0049da36 83be6005000001           cmp       dword ptr [esi + 0x560], 1
0049da3d 756d                     jne       0x49daac
0049da3f 33ff                     xor       edi, edi
0049da41 8b8e68050000             mov       ecx, dword ptr [esi + 0x568]
0049da47 85c9                     test      ecx, ecx
0049da49 746f                     je        0x49daba
0049da4b 8b866c050000             mov       eax, dword ptr [esi + 0x56c]
0049da51 2bc1                     sub       eax, ecx
0049da53 c1f802                   sar       eax, 2
0049da56 3bf8                     cmp       edi, eax
0049da58 7360                     jae       0x49daba
0049da5a 8b16                     mov       edx, dword ptr [esi]
0049da5c 6a00                     push      0
0049da5e 6a00                     push      0
0049da60 6a00                     push      0
0049da62 8bc1                     mov       eax, ecx
0049da64 6a00                     push      0
0049da66 6a00                     push      0
0049da68 8bce                     mov       ecx, esi
0049da6a 8d1cb8                   lea       ebx, [eax + edi*4]
0049da6d ff92c0000000             call      dword ptr [edx + 0xc0]
0049da73 50                       push      eax
0049da74 8b06                     mov       eax, dword ptr [esi]
0049da76 8bce                     mov       ecx, esi
0049da78 ff909c000000             call      dword ptr [eax + 0x9c]
0049da7e 8b16                     mov       edx, dword ptr [esi]
0049da80 50                       push      eax
0049da81 8bce                     mov       ecx, esi
0049da83 ff9298000000             call      dword ptr [edx + 0x98]
0049da89 50                       push      eax
0049da8a 8b06                     mov       eax, dword ptr [esi]
0049da8c 8bce                     mov       ecx, esi
0049da8e ff9094000000             call      dword ptr [eax + 0x94]
0049da94 8b0b                     mov       ecx, dword ptr [ebx]
0049da96 8b9630050000             mov       edx, dword ptr [esi + 0x530]
0049da9c 50                       push      eax
0049da9d 6a00                     push      0
0049da9f 51                       push      ecx
0049daa0 52                       push      edx
0049daa1 e8fac30400               call      0x4e9ea0
0049daa6 83c430                   add       esp, 0x30
0049daa9 47                       inc       edi
0049daaa eb95                     jmp       0x49da41
0049daac 84c0                     test      al, al
0049daae 7511                     jne       0x49dac1
0049dab0 8b8660050000             mov       eax, dword ptr [esi + 0x560]
0049dab6 85c0                     test      eax, eax
0049dab8 7507                     jne       0x49dac1
0049daba c686a405000001           mov       byte ptr [esi + 0x5a4], 1
0049dac1 8b8698050000             mov       eax, dword ptr [esi + 0x598]
0049dac7 85c0                     test      eax, eax
0049dac9 7504                     jne       0x49dacf
0049dacb 33db                     xor       ebx, ebx
0049dacd eb0b                     jmp       0x49dada
0049dacf 8b9e9c050000             mov       ebx, dword ptr [esi + 0x59c]
0049dad5 2bd8                     sub       ebx, eax
0049dad7 c1fb02                   sar       ebx, 2
0049dada 33ff                     xor       edi, edi
0049dadc 85db                     test      ebx, ebx
0049dade 7e37                     jle       0x49db17
0049dae0 8b8698050000             mov       eax, dword ptr [esi + 0x598]
0049dae6 8d0cbd00000000           lea       ecx, [edi*4]
0049daed 8b1408                   mov       edx, dword ptr [eax + ecx]
0049daf0 03c1                     add       eax, ecx
0049daf2 85d2                     test      edx, edx
0049daf4 7c1c                     jl        0x49db12
0049daf6 8b8698050000             mov       eax, dword ptr [esi + 0x598]
0049dafc 03c1                     add       eax, ecx
0049dafe 8b08                     mov       ecx, dword ptr [eax]
0049db00 83f9ff                   cmp       ecx, -1
0049db03 740d                     je        0x49db12
0049db05 8b16                     mov       edx, dword ptr [esi]
0049db07 8bc1                     mov       eax, ecx
0049db09 50                       push      eax
0049db0a 8bce                     mov       ecx, esi
0049db0c ff9210010000             call      dword ptr [edx + 0x110]
0049db12 47                       inc       edi
0049db13 3bfb                     cmp       edi, ebx
0049db15 7cc9                     jl        0x49dae0
0049db17 83be5c05000003           cmp       dword ptr [esi + 0x55c], 3
0049db1e 5b                       pop       ebx
0049db1f 740c                     je        0x49db2d
0049db21 8b16                     mov       edx, dword ptr [esi]
0049db23 6a00                     push      0
0049db25 8bce                     mov       ecx, esi
0049db27 ff9264010000             call      dword ptr [edx + 0x164]
0049db2d 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
0049db33 833800                   cmp       dword ptr [eax], 0
0049db36 7568                     jne       0x49dba0
0049db38 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
0049db3e 85c9                     test      ecx, ecx
0049db40 745e                     je        0x49dba0
0049db42 8b869c050000             mov       eax, dword ptr [esi + 0x59c]
0049db48 2bc1                     sub       eax, ecx
0049db4a c1f802                   sar       eax, 2
0049db4d 85c0                     test      eax, eax
0049db4f 764f                     jbe       0x49dba0
0049db51 8bf9                     mov       edi, ecx
0049db53 8b07                     mov       eax, dword ptr [edi]
0049db55 83f8fe                   cmp       eax, -2
0049db58 7446                     je        0x49dba0
0049db5a 83f8ff                   cmp       eax, -1
0049db5d 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
0049db63 7419                     je        0x49db7e
0049db65 e886555b00               call      0xa530f0
0049db6a 8b0f                     mov       ecx, dword ptr [edi]
0049db6c 8b16                     mov       edx, dword ptr [esi]
0049db6e 6a00                     push      0
0049db70 6a00                     push      0
0049db72 51                       push      ecx
0049db73 50                       push      eax
0049db74 8bce                     mov       ecx, esi
0049db76 ff920c010000             call      dword ptr [edx + 0x10c]
0049db7c eb16                     jmp       0x49db94
0049db7e 8b3e                     mov       edi, dword ptr [esi]
0049db80 6a00                     push      0
0049db82 6a00                     push      0
0049db84 6aff                     push      -1
0049db86 e865555b00               call      0xa530f0
0049db8b 50                       push      eax
0049db8c 8bce                     mov       ecx, esi
0049db8e ff970c010000             call      dword ptr [edi + 0x10c]
0049db94 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
0049db9a c70001000000             mov       dword ptr [eax], 1
0049dba0 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
0049dba6 8b4804                   mov       ecx, dword ptr [eax + 4]
0049dba9 83c004                   add       eax, 4
0049dbac 85c9                     test      ecx, ecx
0049dbae 0f85b4000000             jne       0x49dc68
0049dbb4 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
0049dbba 85c9                     test      ecx, ecx
0049dbbc 0f84a6000000             je        0x49dc68
0049dbc2 8b869c050000             mov       eax, dword ptr [esi + 0x59c]
0049dbc8 2bc1                     sub       eax, ecx
0049dbca c1f802                   sar       eax, 2
0049dbcd 85c0                     test      eax, eax
0049dbcf 0f8693000000             jbe       0x49dc68
0049dbd5 8bc1                     mov       eax, ecx
0049dbd7 8b4804                   mov       ecx, dword ptr [eax + 4]
0049dbda 83c004                   add       eax, 4
0049dbdd 83f9fe                   cmp       ecx, -2
0049dbe0 0f8482000000             je        0x49dc68
0049dbe6 8b16                     mov       edx, dword ptr [esi]
0049dbe8 8bce                     mov       ecx, esi
0049dbea ff92f4000000             call      dword ptr [edx + 0xf4]
0049dbf0 8b8024010000             mov       eax, dword ptr [eax + 0x124]
0049dbf6 3b86b8050000             cmp       eax, dword ptr [esi + 0x5b8]
0049dbfc 7e6a                     jle       0x49dc68
0049dbfe 8bbe98050000             mov       edi, dword ptr [esi + 0x598]
0049dc04 8b4f04                   mov       ecx, dword ptr [edi + 4]
0049dc07 83c8ff                   or        eax, 0xffffffff
0049dc0a 3bc8                     cmp       ecx, eax
0049dc0c 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
0049dc12 742d                     je        0x49dc41
0049dc14 83c104                   add       ecx, 4
0049dc17 e8d4545b00               call      0xa530f0
0049dc1c 8b4f04                   mov       ecx, dword ptr [edi + 4]
0049dc1f 8b16                     mov       edx, dword ptr [esi]
0049dc21 6a00                     push      0
0049dc23 6a00                     push      0
0049dc25 51                       push      ecx
0049dc26 50                       push      eax
0049dc27 8bce                     mov       ecx, esi
0049dc29 ff920c010000             call      dword ptr [edx + 0x10c]
0049dc2f 8bb6ac050000             mov       esi, dword ptr [esi + 0x5ac]
0049dc35 83c604                   add       esi, 4
0049dc38 5f                       pop       edi
0049dc39 c70601000000             mov       dword ptr [esi], 1
0049dc3f 5e                       pop       esi
0049dc40 c3                       ret       
0049dc41 8b3e                     mov       edi, dword ptr [esi]
0049dc43 6a00                     push      0
0049dc45 6a00                     push      0
0049dc47 83c104                   add       ecx, 4
0049dc4a 50                       push      eax
0049dc4b e8a0545b00               call      0xa530f0
0049dc50 50                       push      eax
0049dc51 8bce                     mov       ecx, esi
0049dc53 ff970c010000             call      dword ptr [edi + 0x10c]
0049dc59 8bb6ac050000             mov       esi, dword ptr [esi + 0x5ac]
0049dc5f 83c604                   add       esi, 4
0049dc62 c70601000000             mov       dword ptr [esi], 1
0049dc68 5f                       pop       edi
0049dc69 5e                       pop       esi
0049dc6a c3                       ret       
0049dc6b cc                       int3      
