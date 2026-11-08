004fae00 55                       push      ebp
004fae01 8bec                     mov       ebp, esp
004fae03 83ec0c                   sub       esp, 0xc
004fae06 53                       push      ebx
004fae07 56                       push      esi
004fae08 57                       push      edi
004fae09 8bd9                     mov       ebx, ecx
004fae0b 33ff                     xor       edi, edi
004fae0d 895df4                   mov       dword ptr [ebp - 0xc], ebx
004fae10 897dfc                   mov       dword ptr [ebp - 4], edi
004fae13 8b8b00010000             mov       ecx, dword ptr [ebx + 0x100]
004fae19 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004fae1c 85d2                     test      edx, edx
004fae1e 7504                     jne       0x4fae24
004fae20 33c0                     xor       eax, eax
004fae22 eb08                     jmp       0x4fae2c
004fae24 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004fae27 2bc2                     sub       eax, edx
004fae29 c1f802                   sar       eax, 2
004fae2c 3bf8                     cmp       edi, eax
004fae2e 0f8d23010000             jge       0x4faf57
004fae34 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004fae37 85d2                     test      edx, edx
004fae39 7416                     je        0x4fae51
004fae3b 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004fae3e 2bc2                     sub       eax, edx
004fae40 c1f802                   sar       eax, 2
004fae43 3bf8                     cmp       edi, eax
004fae45 730a                     jae       0x4fae51
004fae47 8bc2                     mov       eax, edx
004fae49 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004fae4c 8d04b8                   lea       eax, [eax + edi*4]
004fae4f eb02                     jmp       0x4fae53
004fae51 33c9                     xor       ecx, ecx
004fae53 8b4508                   mov       eax, dword ptr [ebp + 8]
004fae56 8b11                     mov       edx, dword ptr [ecx]
004fae58 50                       push      eax
004fae59 ff522c                   call      dword ptr [edx + 0x2c]
004fae5c 84c0                     test      al, al
004fae5e 0f84ed000000             je        0x4faf51
004fae64 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
004fae6a 8b5010                   mov       edx, dword ptr [eax + 0x10]
004fae6d 85d2                     test      edx, edx
004fae6f 7415                     je        0x4fae86
004fae71 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004fae74 2bca                     sub       ecx, edx
004fae76 c1f902                   sar       ecx, 2
004fae79 3bf9                     cmp       edi, ecx
004fae7b 7309                     jae       0x4fae86
004fae7d 8bca                     mov       ecx, edx
004fae7f 8d0cb9                   lea       ecx, [ecx + edi*4]
004fae82 8b09                     mov       ecx, dword ptr [ecx]
004fae84 eb02                     jmp       0x4fae88
004fae86 33c9                     xor       ecx, ecx
004fae88 3bcb                     cmp       ecx, ebx
004fae8a 0f84c1000000             je        0x4faf51
004fae90 8b5010                   mov       edx, dword ptr [eax + 0x10]
004fae93 85d2                     test      edx, edx
004fae95 7414                     je        0x4faeab
004fae97 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004fae9a 2bca                     sub       ecx, edx
004fae9c c1f902                   sar       ecx, 2
004fae9f 3bf9                     cmp       edi, ecx
004faea1 7308                     jae       0x4faeab
004faea3 8b34ba                   mov       esi, dword ptr [edx + edi*4]
004faea6 8d04ba                   lea       eax, [edx + edi*4]
004faea9 eb02                     jmp       0x4faead
004faeab 33f6                     xor       esi, esi
004faead 8a450c                   mov       al, byte ptr [ebp + 0xc]
004faeb0 3c01                     cmp       al, 1
004faeb2 8975f8                   mov       dword ptr [ebp - 8], esi
004faeb5 751f                     jne       0x4faed6
004faeb7 8b03                     mov       eax, dword ptr [ebx]
004faeb9 8bcb                     mov       ecx, ebx
004faebb ff90c4010000             call      dword ptr [eax + 0x1c4]
004faec1 8b16                     mov       edx, dword ptr [esi]
004faec3 8bce                     mov       ecx, esi
004faec5 8bd8                     mov       ebx, eax
004faec7 ff92c4010000             call      dword ptr [edx + 0x1c4]
004faecd 3bc3                     cmp       eax, ebx
004faecf 8b5df4                   mov       ebx, dword ptr [ebp - 0xc]
004faed2 757d                     jne       0x4faf51
004faed4 eb10                     jmp       0x4faee6
004faed6 84c0                     test      al, al
004faed8 750c                     jne       0x4faee6
004faeda 56                       push      esi
004faedb 8bcb                     mov       ecx, ebx
004faedd e8eedcfeff               call      0x4e8bd0
004faee2 84c0                     test      al, al
004faee4 746b                     je        0x4faf51
004faee6 8bce                     mov       ecx, esi
004faee8 e813d9feff               call      0x4e8800
004faeed 84c0                     test      al, al
004faeef 7560                     jne       0x4faf51
004faef1 837d14ff                 cmp       dword ptr [ebp + 0x14], -1
004faef5 8bcb                     mov       ecx, ebx
004faef7 750f                     jne       0x4faf08
004faef9 8b03                     mov       eax, dword ptr [ebx]
004faefb 56                       push      esi
004faefc ff9044040000             call      dword ptr [eax + 0x444]
004faf02 84c0                     test      al, al
004faf04 744b                     je        0x4faf51
004faf06 eb0d                     jmp       0x4faf15
004faf08 8b13                     mov       edx, dword ptr [ebx]
004faf0a 6a00                     push      0
004faf0c 56                       push      esi
004faf0d ff5208                   call      dword ptr [edx + 8]
004faf10 3b4514                   cmp       eax, dword ptr [ebp + 0x14]
004faf13 7f3c                     jg        0x4faf51
004faf15 8b06                     mov       eax, dword ptr [esi]
004faf17 6a11                     push      0x11
004faf19 8bce                     mov       ecx, esi
004faf1b ff502c                   call      dword ptr [eax + 0x2c]
004faf1e 84c0                     test      al, al
004faf20 741c                     je        0x4faf3e
004faf22 8b16                     mov       edx, dword ptr [esi]
004faf24 8bce                     mov       ecx, esi
004faf26 ff92f4040000             call      dword ptr [edx + 0x4f4]
004faf2c 3c01                     cmp       al, 1
004faf2e 7421                     je        0x4faf51
004faf30 8b06                     mov       eax, dword ptr [esi]
004faf32 8bce                     mov       ecx, esi
004faf34 ff90dc030000             call      dword ptr [eax + 0x3dc]
004faf3a 84c0                     test      al, al
004faf3c 7513                     jne       0x4faf51
004faf3e ff45fc                   inc       dword ptr [ebp - 4]
004faf41 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004faf44 85c9                     test      ecx, ecx
004faf46 7409                     je        0x4faf51
004faf48 8d55f8                   lea       edx, [ebp - 8]
004faf4b 52                       push      edx
004faf4c e87fcc0000               call      0x507bd0
004faf51 47                       inc       edi
004faf52 e9bcfeffff               jmp       0x4fae13
004faf57 8b45fc                   mov       eax, dword ptr [ebp - 4]
004faf5a 5f                       pop       edi
004faf5b 5e                       pop       esi
004faf5c 5b                       pop       ebx
004faf5d 8be5                     mov       esp, ebp
004faf5f 5d                       pop       ebp
004faf60 c21000                   ret       0x10
004faf63 cc                       int3      
004faf64 cc                       int3      
004faf65 cc                       int3      
004faf66 cc                       int3      
004faf67 cc                       int3      
004faf68 cc                       int3      
004faf69 cc                       int3      
004faf6a cc                       int3      
004faf6b cc                       int3      
004faf6c cc                       int3      
004faf6d cc                       int3      
004faf6e cc                       int3      
004faf6f cc                       int3      
004faf70 55                       push      ebp
004faf71 8bec                     mov       ebp, esp
004faf73 83ec24                   sub       esp, 0x24
004faf76 56                       push      esi
004faf77 8bf1                     mov       esi, ecx
004faf79 8b8e28020000             mov       ecx, dword ptr [esi + 0x228]
004faf7f 8b8624020000             mov       eax, dword ptr [esi + 0x224]
004faf85 3bc1                     cmp       eax, ecx
004faf87 7420                     je        0x4fafa9
004faf89 8da42400000000           lea       esp, [esp]
004faf90 833819                   cmp       dword ptr [eax], 0x19
004faf93 7407                     je        0x4faf9c
004faf95 83c004                   add       eax, 4
004faf98 3bc1                     cmp       eax, ecx
004faf9a 75f4                     jne       0x4faf90
004faf9c 3bc1                     cmp       eax, ecx
004faf9e 7409                     je        0x4fafa9
004fafa0 32c0                     xor       al, al
004fafa2 5e                       pop       esi
004fafa3 8be5                     mov       esp, ebp
004fafa5 5d                       pop       ebp
004fafa6 c20400                   ret       4
004fafa9 57                       push      edi
004fafaa 8b7d08                   mov       edi, dword ptr [ebp + 8]
004fafad 85ff                     test      edi, edi
004fafaf 0f8431030000             je        0x4fb2e6
004fafb5 8b07                     mov       eax, dword ptr [edi]
004fafb7 8bcf                     mov       ecx, edi
004fafb9 ff90a4020000             call      dword ptr [eax + 0x2a4]
004fafbf 85c0                     test      eax, eax
004fafc1 0f841f030000             je        0x4fb2e6
004fafc7 8bce                     mov       ecx, esi
004fafc9 e8c210faff               call      0x49c090
004fafce 84c0                     test      al, al
004fafd0 0f8410030000             je        0x4fb2e6
004fafd6 8b86301a0000             mov       eax, dword ptr [esi + 0x1a30]
004fafdc 83f80c                   cmp       eax, 0xc
004fafdf 53                       push      ebx
004fafe0 0f84e0000000             je        0x4fb0c6
004fafe6 83f807                   cmp       eax, 7
004fafe9 0f84d7000000             je        0x4fb0c6
004fafef 8b17                     mov       edx, dword ptr [edi]
004faff1 8b1e                     mov       ebx, dword ptr [esi]
004faff3 6a00                     push      0
004faff5 8bcf                     mov       ecx, edi
004faff7 ff92a4020000             call      dword ptr [edx + 0x2a4]
004faffd 50                       push      eax
004faffe 8bce                     mov       ecx, esi
004fb000 ff5308                   call      dword ptr [ebx + 8]
004fb003 3d96000000               cmp       eax, 0x96
004fb008 0f8cb8000000             jl        0x4fb0c6
004fb00e 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004fb014 33db                     xor       ebx, ebx
004fb016 3bc3                     cmp       eax, ebx
004fb018 0f84b3000000             je        0x4fb0d1
004fb01e 33c0                     xor       eax, eax
004fb020 8945e0                   mov       dword ptr [ebp - 0x20], eax
004fb023 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004fb026 8945e8                   mov       dword ptr [ebp - 0x18], eax
004fb029 8945ec                   mov       dword ptr [ebp - 0x14], eax
004fb02c 8945f0                   mov       dword ptr [ebp - 0x10], eax
004fb02f 399ee41c0000             cmp       dword ptr [esi + 0x1ce4], ebx
004fb035 895df8                   mov       dword ptr [ebp - 8], ebx
004fb038 895df4                   mov       dword ptr [ebp - 0xc], ebx
004fb03b 895ddc                   mov       dword ptr [ebp - 0x24], ebx
004fb03e 740f                     je        0x4fb04f
