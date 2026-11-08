005f3b00 55                       push      ebp
005f3b01 8bec                     mov       ebp, esp
005f3b03 6aff                     push      -1
005f3b05 684675c600               push      0xc67546
005f3b0a 64a100000000             mov       eax, dword ptr fs:[0]
005f3b10 50                       push      eax
005f3b11 64892500000000           mov       dword ptr fs:[0], esp
005f3b18 83ec10                   sub       esp, 0x10
005f3b1b 53                       push      ebx
005f3b1c 8b5d08                   mov       ebx, dword ptr [ebp + 8]
005f3b1f 56                       push      esi
005f3b20 57                       push      edi
005f3b21 53                       push      ebx
005f3b22 8bf1                     mov       esi, ecx
005f3b24 e817cdeaff               call      0x4a0840
005f3b29 33ff                     xor       edi, edi
005f3b2b 3bde                     cmp       ebx, esi
005f3b2d 0f85d2000000             jne       0x5f3c05
005f3b33 8b8674080000             mov       eax, dword ptr [esi + 0x874]
005f3b39 3b8678080000             cmp       eax, dword ptr [esi + 0x878]
005f3b3f 0f8db9000000             jge       0x5f3bfe
005f3b45 8b967c080000             mov       edx, dword ptr [esi + 0x87c]
005f3b4b 3bd7                     cmp       edx, edi
005f3b4d 0f8498000000             je        0x5f3beb
005f3b53 8b8e34020000             mov       ecx, dword ptr [esi + 0x234]
005f3b59 3bcf                     cmp       ecx, edi
005f3b5b 7415                     je        0x5f3b72
005f3b5d 8b8638020000             mov       eax, dword ptr [esi + 0x238]
005f3b63 2bc1                     sub       eax, ecx
005f3b65 c1f802                   sar       eax, 2
005f3b68 3bc7                     cmp       eax, edi
005f3b6a 7606                     jbe       0x5f3b72
005f3b6c 8bc1                     mov       eax, ecx
005f3b6e 8b00                     mov       eax, dword ptr [eax]
005f3b70 eb02                     jmp       0x5f3b74
005f3b72 33c0                     xor       eax, eax
005f3b74 8b1a                     mov       ebx, dword ptr [edx]
005f3b76 8b16                     mov       edx, dword ptr [esi]
005f3b78 50                       push      eax
005f3b79 8bce                     mov       ecx, esi
005f3b7b ff9298000000             call      dword ptr [edx + 0x98]
005f3b81 50                       push      eax
005f3b82 8b06                     mov       eax, dword ptr [esi]
005f3b84 8bce                     mov       ecx, esi
005f3b86 ff9094000000             call      dword ptr [eax + 0x94]
005f3b8c 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f3b92 50                       push      eax
005f3b93 ff5328                   call      dword ptr [ebx + 0x28]
005f3b96 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f3b9c 8b11                     mov       edx, dword ptr [ecx]
005f3b9e 57                       push      edi
005f3b9f ff520c                   call      dword ptr [edx + 0xc]
005f3ba2 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f3ba8 8b01                     mov       eax, dword ptr [ecx]
005f3baa 8d55e4                   lea       edx, [ebp - 0x1c]
005f3bad 52                       push      edx
005f3bae ff505c                   call      dword ptr [eax + 0x5c]
005f3bb1 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f3bb7 57                       push      edi
005f3bb8 8d45e4                   lea       eax, [ebp - 0x1c]
005f3bbb 50                       push      eax
005f3bbc 57                       push      edi
005f3bbd 6a02                     push      2
005f3bbf 56                       push      esi
005f3bc0 897dfc                   mov       dword ptr [ebp - 4], edi
005f3bc3 e898a4f1ff               call      0x50e060
005f3bc8 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
005f3bcb 3bc7                     cmp       eax, edi
005f3bcd c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f3bd4 7409                     je        0x5f3bdf
005f3bd6 50                       push      eax
005f3bd7 e801c46000               call      0xbfffdd
005f3bdc 83c404                   add       esp, 4
005f3bdf 8b5d08                   mov       ebx, dword ptr [ebp + 8]
005f3be2 897de8                   mov       dword ptr [ebp - 0x18], edi
005f3be5 897dec                   mov       dword ptr [ebp - 0x14], edi
005f3be8 897df0                   mov       dword ptr [ebp - 0x10], edi
005f3beb 8bce                     mov       ecx, esi
005f3bed e87ef7ffff               call      0x5f3370
005f3bf2 8b8e78080000             mov       ecx, dword ptr [esi + 0x878]
005f3bf8 898e74080000             mov       dword ptr [esi + 0x874], ecx
005f3bfe 8bce                     mov       ecx, esi
005f3c00 e83bfdffff               call      0x5f3940
005f3c05 399e84080000             cmp       dword ptr [esi + 0x884], ebx
005f3c0b 7506                     jne       0x5f3c13
005f3c0d 89be84080000             mov       dword ptr [esi + 0x884], edi
005f3c13 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f3c16 5f                       pop       edi
005f3c17 5e                       pop       esi
005f3c18 5b                       pop       ebx
005f3c19 64890d00000000           mov       dword ptr fs:[0], ecx
005f3c20 8be5                     mov       esp, ebp
005f3c22 5d                       pop       ebp
005f3c23 c20400                   ret       4
005f3c26 cc                       int3      
005f3c27 cc                       int3      
005f3c28 cc                       int3      
005f3c29 cc                       int3      
005f3c2a cc                       int3      
005f3c2b cc                       int3      
005f3c2c cc                       int3      
005f3c2d cc                       int3      
005f3c2e cc                       int3      
005f3c2f cc                       int3      
005f3c30 55                       push      ebp
005f3c31 8bec                     mov       ebp, esp
005f3c33 6aff                     push      -1
005f3c35 685075c600               push      0xc67550
005f3c3a 64a100000000             mov       eax, dword ptr fs:[0]
005f3c40 50                       push      eax
005f3c41 64892500000000           mov       dword ptr fs:[0], esp
005f3c48 83ec10                   sub       esp, 0x10
005f3c4b 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f3c4e 8b5004                   mov       edx, dword ptr [eax + 4]
005f3c51 53                       push      ebx
005f3c52 56                       push      esi
005f3c53 8bf1                     mov       esi, ecx
005f3c55 8b08                     mov       ecx, dword ptr [eax]
005f3c57 894de4                   mov       dword ptr [ebp - 0x1c], ecx
005f3c5a 8b4e04                   mov       ecx, dword ptr [esi + 4]
005f3c5d 85c9                     test      ecx, ecx
005f3c5f 57                       push      edi
005f3c60 8965f0                   mov       dword ptr [ebp - 0x10], esp
005f3c63 8955e8                   mov       dword ptr [ebp - 0x18], edx
005f3c66 7504                     jne       0x5f3c6c
005f3c68 33c0                     xor       eax, eax
005f3c6a eb08                     jmp       0x5f3c74
005f3c6c 8b460c                   mov       eax, dword ptr [esi + 0xc]
005f3c6f 2bc1                     sub       eax, ecx
005f3c71 c1f803                   sar       eax, 3
005f3c74 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
005f3c77 85db                     test      ebx, ebx
005f3c79 0f84e1010000             je        0x5f3e60
005f3c7f 85                       .byte     0x85
