0049d7d0 55                       push      ebp
0049d7d1 8bec                     mov       ebp, esp
0049d7d3 83ec10                   sub       esp, 0x10
0049d7d6 53                       push      ebx
0049d7d7 56                       push      esi
0049d7d8 57                       push      edi
0049d7d9 8b7d08                   mov       edi, dword ptr [ebp + 8]
0049d7dc 8bc7                     mov       eax, edi
0049d7de 83e800                   sub       eax, 0
0049d7e1 8bf1                     mov       esi, ecx
0049d7e3 0f84c1000000             je        0x49d8aa
0049d7e9 48                       dec       eax
0049d7ea 0f85df000000             jne       0x49d8cf
0049d7f0 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049d7f3 8b4004                   mov       eax, dword ptr [eax + 4]
0049d7f6 8b4808                   mov       ecx, dword ptr [eax + 8]
0049d7f9 8b500c                   mov       edx, dword ptr [eax + 0xc]
0049d7fc 8b18                     mov       ebx, dword ptr [eax]
0049d7fe 8b7804                   mov       edi, dword ptr [eax + 4]
0049d801 894d0c                   mov       dword ptr [ebp + 0xc], ecx
0049d804 8b4810                   mov       ecx, dword ptr [eax + 0x10]
0049d807 8955f0                   mov       dword ptr [ebp - 0x10], edx
0049d80a 8b5014                   mov       edx, dword ptr [eax + 0x14]
0049d80d 8b4018                   mov       eax, dword ptr [eax + 0x18]
0049d810 894d08                   mov       dword ptr [ebp + 8], ecx
0049d813 8955f4                   mov       dword ptr [ebp - 0xc], edx
0049d816 8b16                     mov       edx, dword ptr [esi]
0049d818 8bce                     mov       ecx, esi
0049d81a 8945f8                   mov       dword ptr [ebp - 8], eax
0049d81d ff923c030000             call      dword ptr [edx + 0x33c]
0049d823 8b00                     mov       eax, dword ptr [eax]
0049d825 8b16                     mov       edx, dword ptr [esi]
0049d827 8bce                     mov       ecx, esi
0049d829 8945fc                   mov       dword ptr [ebp - 4], eax
0049d82c ff923c030000             call      dword ptr [edx + 0x33c]
0049d832 8938                     mov       dword ptr [eax], edi
0049d834 8b45fc                   mov       eax, dword ptr [ebp - 4]
0049d837 3bc7                     cmp       eax, edi
0049d839 7e16                     jle       0x49d851
0049d83b 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
0049d841 8b9658040000             mov       edx, dword ptr [esi + 0x458]
0049d847 33c0                     xor       eax, eax
0049d849 3bca                     cmp       ecx, edx
0049d84b 0f94c0                   sete      al
0049d84e 50                       push      eax
0049d84f eb04                     jmp       0x49d855
0049d851 7d20                     jge       0x49d873
0049d853 6a04                     push      4
0049d855 8b5508                   mov       edx, dword ptr [ebp + 8]
0049d858 8b06                     mov       eax, dword ptr [esi]
0049d85a 53                       push      ebx
0049d85b 8bce                     mov       ecx, esi
0049d85d 52                       push      edx
0049d85e ff9098000000             call      dword ptr [eax + 0x98]
0049d864 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d867 40                       inc       eax
0049d868 50                       push      eax
0049d869 51                       push      ecx
0049d86a 56                       push      esi
0049d86b e810b1ffff               call      0x498980
0049d870 83c418                   add       esp, 0x18
0049d873 8b55f8                   mov       edx, dword ptr [ebp - 8]
0049d876 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049d879 52                       push      edx
0049d87a 8b16                     mov       edx, dword ptr [esi]
0049d87c 50                       push      eax
0049d87d 8bce                     mov       ecx, esi
0049d87f ff525c                   call      dword ptr [edx + 0x5c]
0049d882 8bc8                     mov       ecx, eax
0049d884 e897df0600               call      0x50b820
0049d889 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049d88c 8b16                     mov       edx, dword ptr [esi]
0049d88e 51                       push      ecx
0049d88f 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049d892 51                       push      ecx
0049d893 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d896 51                       push      ecx
0049d897 53                       push      ebx
0049d898 50                       push      eax
0049d899 8bce                     mov       ecx, esi
0049d89b ff9248030000             call      dword ptr [edx + 0x348]
0049d8a1 5f                       pop       edi
0049d8a2 5e                       pop       esi
0049d8a3 5b                       pop       ebx
0049d8a4 8be5                     mov       esp, ebp
0049d8a6 5d                       pop       ebp
0049d8a7 c21000                   ret       0x10
0049d8aa 8b864c010000             mov       eax, dword ptr [esi + 0x14c]
0049d8b0 85c0                     test      eax, eax
0049d8b2 741b                     je        0x49d8cf
0049d8b4 8b16                     mov       edx, dword ptr [esi]
0049d8b6 8bce                     mov       ecx, esi
0049d8b8 8bd8                     mov       ebx, eax
0049d8ba ff9204010000             call      dword ptr [edx + 0x104]
0049d8c0 3bc3                     cmp       eax, ebx
0049d8c2 740b                     je        0x49d8cf
0049d8c4 8b06                     mov       eax, dword ptr [esi]
0049d8c6 53                       push      ebx
0049d8c7 8bce                     mov       ecx, esi
0049d8c9 ff9000010000             call      dword ptr [eax + 0x100]
0049d8cf 8b16                     mov       edx, dword ptr [esi]
0049d8d1 8bce                     mov       ecx, esi
0049d8d3 ff924c030000             call      dword ptr [edx + 0x34c]
0049d8d9 3bf8                     cmp       edi, eax
0049d8db 7c65                     jl        0x49d942
0049d8dd 8b1e                     mov       ebx, dword ptr [esi]
0049d8df 8bce                     mov       ecx, esi
0049d8e1 ff934c030000             call      dword ptr [ebx + 0x34c]
0049d8e7 8bcf                     mov       ecx, edi
0049d8e9 2bc8                     sub       ecx, eax
0049d8eb 51                       push      ecx
0049d8ec 8bce                     mov       ecx, esi
0049d8ee ff9350030000             call      dword ptr [ebx + 0x350]
0049d8f4 85c0                     test      eax, eax
0049d8f6 742f                     je        0x49d927
0049d8f8 8b1e                     mov       ebx, dword ptr [esi]
0049d8fa 8bce                     mov       ecx, esi
0049d8fc ff934c030000             call      dword ptr [ebx + 0x34c]
0049d902 8bd7                     mov       edx, edi
0049d904 2bd0                     sub       edx, eax
0049d906 52                       push      edx
0049d907 8bce                     mov       ecx, esi
0049d909 ff9350030000             call      dword ptr [ebx + 0x350]
0049d90f 50                       push      eax
0049d910 8bce                     mov       ecx, esi
0049d912 ff9300010000             call      dword ptr [ebx + 0x100]
0049d918 89bee8070000             mov       dword ptr [esi + 0x7e8], edi
0049d91e 5f                       pop       edi
0049d91f 5e                       pop       esi
0049d920 5b                       pop       ebx
0049d921 8be5                     mov       esp, ebp
0049d923 5d                       pop       ebp
0049d924 c21000                   ret       0x10
0049d927 57                       push      edi
0049d928 8d8e08020000             lea       ecx, [esi + 0x208]
0049d92e e8bd575b00               call      0xa530f0
0049d933 50                       push      eax
0049d934 68e8ebcc00               push      0xccebe8
0049d939 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049d93f 83c40c                   add       esp, 0xc
0049d942 89bee8070000             mov       dword ptr [esi + 0x7e8], edi
0049d948 5f                       pop       edi
0049d949 5e                       pop       esi
0049d94a 5b                       pop       ebx
0049d94b 8be5                     mov       esp, ebp
0049d94d 5d                       pop       ebp
0049d94e c21000                   ret       0x10
0049d951 cc                       int3      
0049d952 cc                       int3      
0049d953 cc                       int3      
0049d954 cc                       int3      
0049d955 cc                       int3      
0049d956 cc                       int3      
0049d957 cc                       int3      
0049d958 cc                       int3      
0049d959 cc                       int3      
0049d95a cc                       int3      
0049d95b cc                       int3      
0049d95c cc                       int3      
0049d95d cc                       int3      
0049d95e cc                       int3      
0049d95f cc                       int3      
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
0049dc6c cc                       int3      
0049dc6d cc                       int3      
0049dc6e cc                       int3      
0049dc6f cc                       int3      
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
0049e0cf 85                       .byte     0x85
