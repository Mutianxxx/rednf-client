005f57a0 56                       push      esi
005f57a1 8bf1                     mov       esi, ecx
005f57a3 8b8e10090000             mov       ecx, dword ptr [esi + 0x910]
005f57a9 85c9                     test      ecx, ecx
005f57ab 0f84ff000000             je        0x5f58b0
005f57b1 8b8614090000             mov       eax, dword ptr [esi + 0x914]
005f57b7 2bc1                     sub       eax, ecx
005f57b9 c1f803                   sar       eax, 3
005f57bc 85c0                     test      eax, eax
005f57be 0f86ec000000             jbe       0x5f58b0
005f57c4 8bce                     mov       ecx, esi
005f57c6 e8c568eaff               call      0x49c090
005f57cb 84c0                     test      al, al
005f57cd 0f84dd000000             je        0x5f58b0
005f57d3 8a8689080000             mov       al, byte ptr [esi + 0x889]
005f57d9 84c0                     test      al, al
005f57db 0f85cf000000             jne       0x5f58b0
005f57e1 53                       push      ebx
005f57e2 33db                     xor       ebx, ebx
005f57e4 57                       push      edi
005f57e5 eb09                     jmp       0x5f57f0
005f57e7 8da42400000000           lea       esp, [esp]
005f57ee 8bff                     mov       edi, edi
005f57f0 8b8e10090000             mov       ecx, dword ptr [esi + 0x910]
005f57f6 85c9                     test      ecx, ecx
005f57f8 0f84b0000000             je        0x5f58ae
005f57fe 8b8614090000             mov       eax, dword ptr [esi + 0x914]
005f5804 2bc1                     sub       eax, ecx
005f5806 c1f803                   sar       eax, 3
005f5809 3bd8                     cmp       ebx, eax
005f580b 0f839d000000             jae       0x5f58ae
005f5811 8bc1                     mov       eax, ecx
005f5813 8b0cd8                   mov       ecx, dword ptr [eax + ebx*8]
005f5816 81f9d0070000             cmp       ecx, 0x7d0
005f581c 8d04d8                   lea       eax, [eax + ebx*8]
005f581f 7c32                     jl        0x5f5853
005f5821 81f9340a0000             cmp       ecx, 0xa34
005f5827 7f2a                     jg        0x5f5853
005f5829 8b4804                   mov       ecx, dword ptr [eax + 4]
005f582c 6a00                     push      0
005f582e 8b00                     mov       eax, dword ptr [eax]
005f5830 6a00                     push      0
005f5832 8b16                     mov       edx, dword ptr [esi]
005f5834 6a00                     push      0
005f5836 6a00                     push      0
005f5838 6a00                     push      0
005f583a 6a04                     push      4
005f583c 6a00                     push      0
005f583e 6a00                     push      0
005f5840 6a00                     push      0
005f5842 6a00                     push      0
005f5844 6a00                     push      0
005f5846 51                       push      ecx
005f5847 50                       push      eax
005f5848 8bce                     mov       ecx, esi
005f584a ff92b8020000             call      dword ptr [edx + 0x2b8]
005f5850 43                       inc       ebx
005f5851 eb9d                     jmp       0x5f57f0
005f5853 8a8689080000             mov       al, byte ptr [esi + 0x889]
005f5859 84c0                     test      al, al
005f585b 754b                     jne       0x5f58a8
005f585d 8d7e60                   lea       edi, [esi + 0x60]
005f5860 8bcf                     mov       ecx, edi
005f5862 e889f6e0ff               call      0x404ef0
005f5867 8b8e44090000             mov       ecx, dword ptr [esi + 0x944]
005f586d 6a00                     push      0
005f586f 51                       push      ecx
005f5870 8bcf                     mov       ecx, edi
005f5872 e8e9165100               call      0xb06f60
005f5877 8b16                     mov       edx, dword ptr [esi]
005f5879 6a00                     push      0
005f587b 6a00                     push      0
005f587d 6a00                     push      0
005f587f 6a00                     push      0
005f5881 6a02                     push      2
005f5883 8bce                     mov       ecx, esi
005f5885 ff928c020000             call      dword ptr [edx + 0x28c]
005f588b 8b06                     mov       eax, dword ptr [esi]
005f588d 8bce                     mov       ecx, esi
005f588f ff9090020000             call      dword ptr [eax + 0x290]
005f5895 8b16                     mov       edx, dword ptr [esi]
005f5897 6a00                     push      0
005f5899 8bce                     mov       ecx, esi
005f589b ff92d8020000             call      dword ptr [edx + 0x2d8]
005f58a1 c6868908000001           mov       byte ptr [esi + 0x889], 1
005f58a8 43                       inc       ebx
005f58a9 e942ffffff               jmp       0x5f57f0
005f58ae 5f                       pop       edi
005f58af 5b                       pop       ebx
005f58b0 5e                       pop       esi
005f58b1 c3                       ret       
005f58b2 cc                       int3      
005f58b3 cc                       int3      
005f58b4 cc                       int3      
005f58b5 cc                       int3      
005f58b6 cc                       int3      
005f58b7 cc                       int3      
005f58b8 cc                       int3      
005f58b9 cc                       int3      
005f58ba cc                       int3      
005f58bb cc                       int3      
005f58bc cc                       int3      
005f58bd cc                       int3      
005f58be cc                       int3      
005f58bf cc                       int3      
005f58c0 56                       push      esi
005f58c1 6a01                     push      1
005f58c3 6a00                     push      0
005f58c5 6a00                     push      0
005f58c7 6a00                     push      0
005f58c9 6a00                     push      0
005f58cb 8bf1                     mov       esi, ecx
005f58cd 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f58d3 8b16                     mov       edx, dword ptr [esi]
005f58d5 6a00                     push      0
005f58d7 6a00                     push      0
005f58d9 83c008                   add       eax, 8
005f58dc 8b00                     mov       eax, dword ptr [eax]
005f58de 6a00                     push      0
005f58e0 50                       push      eax
005f58e1 6aff                     push      -1
005f58e3 ff92f8000000             call      dword ptr [edx + 0xf8]
005f58e9 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f58ef 8b16                     mov       edx, dword ptr [esi]
005f58f1 6a01                     push      1
005f58f3 6a00                     push      0
005f58f5 6a00                     push      0
005f58f7 6a00                     push      0
005f58f9 6a00                     push      0
005f58fb 6a00                     push      0
005f58fd 6a00                     push      0
005f58ff 83                       .byte     0x83
