0050cb59 03c7                     add       eax, edi
0050cb5b 8b00                     mov       eax, dword ptr [eax]
0050cb5d 8b10                     mov       edx, dword ptr [eax]
0050cb5f 6a12                     push      0x12
0050cb61 8bc8                     mov       ecx, eax
0050cb63 ff522c                   call      dword ptr [edx + 0x2c]
0050cb66 84c0                     test      al, al
0050cb68 757e                     jne       0x50cbe8
0050cb6a 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb6d 03c7                     add       eax, edi
0050cb6f 8b00                     mov       eax, dword ptr [eax]
0050cb71 8b10                     mov       edx, dword ptr [eax]
0050cb73 6a41                     push      0x41
0050cb75 8bc8                     mov       ecx, eax
0050cb77 ff522c                   call      dword ptr [edx + 0x2c]
0050cb7a 84c0                     test      al, al
0050cb7c 756a                     jne       0x50cbe8
0050cb7e 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb81 03c7                     add       eax, edi
0050cb83 8b00                     mov       eax, dword ptr [eax]
0050cb85 8b10                     mov       edx, dword ptr [eax]
0050cb87 6881000000               push      0x81
0050cb8c 8bc8                     mov       ecx, eax
0050cb8e ff522c                   call      dword ptr [edx + 0x2c]
0050cb91 84c0                     test      al, al
0050cb93 7553                     jne       0x50cbe8
0050cb95 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cb98 03c7                     add       eax, edi
0050cb9a 8b00                     mov       eax, dword ptr [eax]
0050cb9c 8b10                     mov       edx, dword ptr [eax]
0050cb9e 6882000000               push      0x82
0050cba3 8bc8                     mov       ecx, eax
0050cba5 ff522c                   call      dword ptr [edx + 0x2c]
0050cba8 84c0                     test      al, al
0050cbaa 753c                     jne       0x50cbe8
0050cbac 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbaf 03c7                     add       eax, edi
0050cbb1 8b00                     mov       eax, dword ptr [eax]
0050cbb3 8b10                     mov       edx, dword ptr [eax]
0050cbb5 6811020000               push      0x211
0050cbba 8bc8                     mov       ecx, eax
0050cbbc ff522c                   call      dword ptr [edx + 0x2c]
0050cbbf 6a00                     push      0
0050cbc1 84c0                     test      al, al
0050cbc3 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbc6 8bce                     mov       ecx, esi
0050cbc8 6a00                     push      0
0050cbca 0f855fffffff             jne       0x50cb2f
0050cbd0 03c7                     add       eax, edi
0050cbd2 8b38                     mov       edi, dword ptr [eax]
0050cbd4 57                       push      edi
0050cbd5 e816fbffff               call      0x50c6f0
0050cbda 85ff                     test      edi, edi
0050cbdc 741d                     je        0x50cbfb
0050cbde 8b17                     mov       edx, dword ptr [edi]
0050cbe0 6a01                     push      1
0050cbe2 8bcf                     mov       ecx, edi
0050cbe4 ff12                     call      dword ptr [edx]
0050cbe6 eb13                     jmp       0x50cbfb
0050cbe8 8b4610                   mov       eax, dword ptr [esi + 0x10]
0050cbeb 6a00                     push      0
0050cbed 03c7                     add       eax, edi
0050cbef 8b00                     mov       eax, dword ptr [eax]
0050cbf1 6a00                     push      0
0050cbf3 50                       push      eax
0050cbf4 8bce                     mov       ecx, esi
0050cbf6 e8f5faffff               call      0x50c6f0
0050cbfb 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050cbfe 4b                       dec       ebx
0050cbff 48                       dec       eax
0050cc00 8945fc                   mov       dword ptr [ebp - 4], eax
0050cc03 8b45fc                   mov       eax, dword ptr [ebp - 4]
0050cc06 43                       inc       ebx
0050cc07 3bd8                     cmp       ebx, eax
0050cc09 0f8cd1feffff             jl        0x50cae0
0050cc0f 5f                       pop       edi
0050cc10 5e                       pop       esi
0050cc11 5b                       pop       ebx
0050cc12 8be5                     mov       esp, ebp
0050cc14 5d                       pop       ebp
0050cc15 c3                       ret       
0050cc16 cc                       int3      
0050cc17 cc                       int3      
0050cc18 cc                       int3      
0050cc19 cc                       int3      
0050cc1a cc                       int3      
0050cc1b cc                       int3      
0050cc1c cc                       int3      
0050cc1d cc                       int3      
0050cc1e cc                       int3      
0050cc1f cc                       int3      
