004a3820 55                       push      ebp
004a3821 8bec                     mov       ebp, esp
004a3823 6aff                     push      -1
004a3825 68486ec500               push      0xc56e48
004a382a 64a100000000             mov       eax, dword ptr fs:[0]
004a3830 50                       push      eax
004a3831 64892500000000           mov       dword ptr fs:[0], esp
004a3838 51                       push      ecx
004a3839 56                       push      esi
004a383a 8bf1                     mov       esi, ecx
004a383c 8975f0                   mov       dword ptr [ebp - 0x10], esi
004a383f e82c57f9ff               call      0x438f70
004a3844 8b4508                   mov       eax, dword ptr [ebp + 8]
004a3847 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a384a 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004a384d 50                       push      eax
004a384e 51                       push      ecx
004a384f 52                       push      edx
004a3850 8bce                     mov       ecx, esi
004a3852 c745fc00000000           mov       dword ptr [ebp - 4], 0
004a3859 c7065ceccc00             mov       dword ptr [esi], 0xccec5c
004a385f e8dcb9ffff               call      0x49f240
004a3864 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a3867 8bc6                     mov       eax, esi
004a3869 5e                       pop       esi
004a386a 64890d00000000           mov       dword ptr fs:[0], ecx
004a3871 8be5                     mov       esp, ebp
004a3873 5d                       pop       ebp
004a3874 c20c00                   ret       0xc
004a3877 cc                       int3      
004a3878 cc                       int3      
004a3879 cc                       int3      
004a387a cc                       int3      
004a387b cc                       int3      
004a387c cc                       int3      
004a387d cc                       int3      
004a387e cc                       int3      
004a387f cc                       int3      
004a3880 55                       push      ebp
004a3881 8bec                     mov       ebp, esp
004a3883 56                       push      esi
004a3884 8b7508                   mov       esi, dword ptr [ebp + 8]
004a3887 57                       push      edi
004a3888 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004a388b 3bf7                     cmp       esi, edi
004a388d 740f                     je        0x4a389e
004a388f 90                       nop       
004a3890 8bce                     mov       ecx, esi
004a3892 e879feffff               call      0x4a3710
004a3897 83c61c                   add       esi, 0x1c
004a389a 3bf7                     cmp       esi, edi
004a389c 75f2                     jne       0x4a3890
004a389e 5f                       pop       edi
004a389f 5e                       pop       esi
004a38a0 5d                       pop       ebp
004a38a1 c20800                   ret       8
004a38a4 cc                       int3      
004a38a5 cc                       int3      
004a38a6 cc                       int3      
004a38a7 cc                       int3      
004a38a8 cc                       int3      
004a38a9 cc                       int3      
004a38aa cc                       int3      
004a38ab cc                       int3      
004a38ac cc                       int3      
004a38ad cc                       int3      
004a38ae cc                       int3      
004a38af cc                       int3      
004a38b0 53                       push      ebx
004a38b1 8bd9                     mov       ebx, ecx
004a38b3 56                       push      esi
004a38b4 8b7304                   mov       esi, dword ptr [ebx + 4]
004a38b7 33c0                     xor       eax, eax
004a38b9 3bf0                     cmp       esi, eax
004a38bb 7425                     je        0x4a38e2
004a38bd 57                       push      edi
004a38be 8b7b08                   mov       edi, dword ptr [ebx + 8]
004a38c1 3bf7                     cmp       esi, edi
004a38c3 740e                     je        0x4a38d3
004a38c5 8bce                     mov       ecx, esi
004a38c7 e844feffff               call      0x4a3710
004a38cc 83c61c                   add       esi, 0x1c
004a38cf 3bf7                     cmp       esi, edi
004a38d1 75f2                     jne       0x4a38c5
004a38d3 8b4304                   mov       eax, dword ptr [ebx + 4]
004a38d6 50                       push      eax
004a38d7 e801c77500               call      0xbfffdd
004a38dc 83c404                   add       esp, 4
004a38df 33c0                     xor       eax, eax
004a38e1 5f                       pop       edi
004a38e2 5e                       pop       esi
004a38e3 894304                   mov       dword ptr [ebx + 4], eax
004a38e6 894308                   mov       dword ptr [ebx + 8], eax
004a38e9 89430c                   mov       dword ptr [ebx + 0xc], eax
004a38ec 5b                       pop       ebx
004a38ed c3                       ret       
004a38ee cc                       int3      
004a38ef cc                       int3      
004a38f0 e9bbffffff               jmp       0x4a38b0
004a38f5 cc                       int3      
004a38f6 cc                       int3      
004a38f7 cc                       int3      
004a38f8 cc                       int3      
004a38f9 cc                       int3      
004a38fa cc                       int3      
004a38fb cc                       int3      
004a38fc cc                       int3      
004a38fd cc                       int3      
004a38fe cc                       int3      
004a38ff cc                       int3      
