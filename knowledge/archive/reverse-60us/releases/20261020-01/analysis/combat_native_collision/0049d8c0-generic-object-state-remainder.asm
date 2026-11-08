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
