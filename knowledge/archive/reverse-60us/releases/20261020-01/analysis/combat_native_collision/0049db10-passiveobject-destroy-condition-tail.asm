0049db10 0000                     add       byte ptr [eax], al
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
0049dc6c cc                       int3      
0049dc6d cc                       int3      
0049dc6e cc                       int3      
0049dc6f cc                       int3      
