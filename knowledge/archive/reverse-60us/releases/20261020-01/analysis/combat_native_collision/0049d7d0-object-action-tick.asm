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
0049dbcf 0f                       .byte     0x0f
