00438990 56                       push      esi
00438991 8bf1                     mov       esi, ecx
00438993 8d8e18040000             lea       ecx, [esi + 0x418]
00438999 e812000000               call      0x4389b0
0043899e 8d8e70040000             lea       ecx, [esi + 0x470]
004389a4 5e                       pop       esi
004389a5 e906000000               jmp       0x4389b0
004389aa cc                       int3      
004389ab cc                       int3      
004389ac cc                       int3      
004389ad cc                       int3      
004389ae cc                       int3      
004389af cc                       int3      
004389b0 55                       push      ebp
004389b1 8bec                     mov       ebp, esp
004389b3 51                       push      ecx
004389b4 56                       push      esi
004389b5 8bf1                     mov       esi, ecx
004389b7 8d4e04                   lea       ecx, [esi + 4]
004389ba e871833100               call      0x750d30
004389bf 8b4608                   mov       eax, dword ptr [esi + 8]
004389c2 8d4dfc                   lea       ecx, [ebp - 4]
004389c5 51                       push      ecx
004389c6 6a09                     push      9
004389c8 8d4e10                   lea       ecx, [esi + 0x10]
004389cb 8945fc                   mov       dword ptr [ebp - 4], eax
004389ce e81d000000               call      0x4389f0
004389d3 b801000000               mov       eax, 1
004389d8 894620                   mov       dword ptr [esi + 0x20], eax
004389db 894624                   mov       dword ptr [esi + 0x24], eax
004389de 5e                       pop       esi
004389df 8be5                     mov       esp, ebp
004389e1 5d                       pop       ebp
004389e2 c3                       ret       
004389e3 cc                       int3      
004389e4 cc                       int3      
004389e5 cc                       int3      
004389e6 cc                       int3      
004389e7 cc                       int3      
004389e8 cc                       int3      
004389e9 cc                       int3      
004389ea cc                       int3      
004389eb cc                       int3      
004389ec cc                       int3      
004389ed cc                       int3      
004389ee cc                       int3      
004389ef cc                       int3      
004389f0 55                       push      ebp
004389f1 8bec                     mov       ebp, esp
004389f3 51                       push      ecx
004389f4 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004389f7 56                       push      esi
004389f8 8bf1                     mov       esi, ecx
004389fa 8b08                     mov       ecx, dword ptr [eax]
004389fc 8b4608                   mov       eax, dword ptr [esi + 8]
004389ff 894d0c                   mov       dword ptr [ebp + 0xc], ecx
00438a02 8b4e04                   mov       ecx, dword ptr [esi + 4]
00438a05 50                       push      eax
00438a06 51                       push      ecx
00438a07 8d55fc                   lea       edx, [ebp - 4]
00438a0a 52                       push      edx
00438a0b 8bce                     mov       ecx, esi
00438a0d e8                       .byte     0xe8
00438a0e 4e                       dec       esi
00438a0f e5                       .byte     0xe5
