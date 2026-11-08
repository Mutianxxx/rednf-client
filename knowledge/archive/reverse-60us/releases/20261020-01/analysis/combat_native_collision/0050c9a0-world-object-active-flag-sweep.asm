0050c9a0 55                       push      ebp
0050c9a1 8bec                     mov       ebp, esp
0050c9a3 51                       push      ecx
0050c9a4 53                       push      ebx
0050c9a5 56                       push      esi
0050c9a6 8bf1                     mov       esi, ecx
0050c9a8 8b4e10                   mov       ecx, dword ptr [esi + 0x10]
0050c9ab 33db                     xor       ebx, ebx
0050c9ad 3bcb                     cmp       ecx, ebx
0050c9af 7505                     jne       0x50c9b6
0050c9b1 895dfc                   mov       dword ptr [ebp - 4], ebx
0050c9b4 eb0b                     jmp       0x50c9c1
0050c9b6 8b4614                   mov       eax, dword ptr [esi + 0x14]
0050c9b9 2bc1                     sub       eax, ecx
0050c9bb c1f802                   sar       eax, 2
0050c9be 8945fc                   mov       dword ptr [ebp - 4], eax
0050c9c1 395dfc                   cmp       dword ptr [ebp - 4], ebx
0050c9c4 7e4d                     jle       0x50ca13
0050c9c6 57                       push      edi
0050c9c7 eb07                     jmp       0x50c9d0
0050c9c9 8da42400000000           lea       esp, [esp]
0050c9d0 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050c9d3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0050c9d6 8d3c9d00000000           lea       edi, [ebx*4]
0050c9dd 03c7                     add       eax, edi
0050c9df 8b00                     mov       eax, dword ptr [eax]
0050c9e1 8b10                     mov       edx, dword ptr [eax]
0050c9e3 51                       push      ecx
0050c9e4 8bc8                     mov       ecx, eax
0050c9e6 ff522c                   call      dword ptr [edx + 0x2c]
0050c9e9 84c0                     test      al, al
0050c9eb 741d                     je        0x50ca0a
0050c9ed 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050c9f0 8b550c                   mov       edx, dword ptr [ebp + 0xc]
0050c9f3 6a00                     push      0
0050c9f5 03c7                     add       eax, edi
0050c9f7 8b00                     mov       eax, dword ptr [eax]
0050c9f9 52                       push      edx
0050c9fa 50                       push      eax
0050c9fb 8bce                     mov       ecx, esi
0050c9fd e8eefcffff               call      0x50c6f0
0050ca02 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050ca05 4b                       dec       ebx
0050ca06 48                       dec       eax
0050ca07 8945fc                   mov       dword ptr [ebp - 4], eax
0050ca0a 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050ca0d 43                       inc       ebx
0050ca0e 3bd8                     cmp       ebx, eax
0050ca10 7cbe                     jl        0x50c9d0
0050ca12 5f                       pop       edi
0050ca13 5e                       pop       esi
0050ca14 5b                       pop       ebx
0050ca15 8be5                     mov       esp, ebp
0050ca17 5d                       pop       ebp
0050ca18 c20800                   ret       8
0050ca1b cc                       int3      
0050ca1c cc                       int3      
0050ca1d cc                       int3      
0050ca1e cc                       int3      
0050ca1f cc                       int3      
0050ca20 55                       push      ebp
0050ca21 8bec                     mov       ebp, esp
0050ca23 56                       push      esi
0050ca24 8b7508                   mov       esi, dword ptr [ebp + 8]
0050ca27 6a00                     push      0
0050ca29 6a00                     push      0
0050ca2b 56                       push      esi
0050ca2c e8bffcffff               call      0x50c6f0
0050ca31 85f6                     test      esi, esi
0050ca33 7408                     je        0x50ca3d
0050ca35 8b06                     mov       eax, dword ptr [esi]
0050ca37 6a01                     push      1
0050ca39 8bce                     mov       ecx, esi
0050ca3b ff10                     call      dword ptr [eax]
0050ca3d 5e                       pop       esi
0050ca3e 5d                       pop       ebp
0050ca3f c20400                   ret       4
0050ca42 cc                       int3      
0050ca43 cc                       int3      
0050ca44 cc                       int3      
0050ca45 cc                       int3      
0050ca46 cc                       int3      
0050ca47 cc                       int3      
0050ca48 cc                       int3      
0050ca49 cc                       int3      
0050ca4a cc                       int3      
0050ca4b cc                       int3      
0050ca4c cc                       int3      
0050ca4d cc                       int3      
0050ca4e cc                       int3      
0050ca4f cc                       int3      
