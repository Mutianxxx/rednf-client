00a32a90 55                       push      ebp
00a32a91 8bec                     mov       ebp, esp
00a32a93 6aff                     push      -1
00a32a95 68b9e9c800               push      0xc8e9b9
00a32a9a 64a100000000             mov       eax, dword ptr fs:[0]
00a32aa0 50                       push      eax
00a32aa1 64892500000000           mov       dword ptr fs:[0], esp
00a32aa8 81ec90000000             sub       esp, 0x90
00a32aae 53                       push      ebx
00a32aaf 8b5d08                   mov       ebx, dword ptr [ebp + 8]
00a32ab2 56                       push      esi
00a32ab3 57                       push      edi
00a32ab4 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
00a32ab7 57                       push      edi
00a32ab8 53                       push      ebx
00a32ab9 8bf1                     mov       esi, ecx
00a32abb e8d0ccdfff               call      0x82f790
00a32ac0 83c408                   add       esp, 8
00a32ac3 84c0                     test      al, al
00a32ac5 7454                     je        0xa32b1b
00a32ac7 8d8d64ffffff             lea       ecx, [ebp - 0x9c]
00a32acd e8ce7dadff               call      0x50a8a0
00a32ad2 57                       push      edi
00a32ad3 53                       push      ebx
00a32ad4 8d4604                   lea       eax, [esi + 4]
00a32ad7 68f8b8ca00               push      0xcab8f8
00a32adc 50                       push      eax
00a32add c745fc00000000           mov       dword ptr [ebp - 4], 0
00a32ae4 e8a7dadfff               call      0x830590
00a32ae9 57                       push      edi
00a32aea 8d8d64ffffff             lea       ecx, [ebp - 0x9c]
00a32af0 53                       push      ebx
00a32af1 51                       push      ecx
00a32af2 e8e9c50000               call      0xa3f0e0
00a32af7 8b5510                   mov       edx, dword ptr [ebp + 0x10]
00a32afa 83c41c                   add       esp, 0x1c
00a32afd 52                       push      edx
00a32afe 8d8564ffffff             lea       eax, [ebp - 0x9c]
00a32b04 50                       push      eax
00a32b05 8bce                     mov       ecx, esi
00a32b07 e8a4f6ffff               call      0xa321b0
00a32b0c 84c0                     test      al, al
00a32b0e 8d8d64ffffff             lea       ecx, [ebp - 0x9c]
00a32b14 751a                     jne       0xa32b30
00a32b16 e8157eadff               call      0x50a930
00a32b1b 5f                       pop       edi
00a32b1c 5e                       pop       esi
00a32b1d 32c0                     xor       al, al
00a32b1f 5b                       pop       ebx
00a32b20 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a32b23 64890d00000000           mov       dword ptr fs:[0], ecx
00a32b2a 8be5                     mov       esp, ebp
00a32b2c 5d                       pop       ebp
00a32b2d c20c00                   ret       0xc
00a32b30 e8fb7dadff               call      0x50a930
00a32b35 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a32b38 5f                       pop       edi
00a32b39 5e                       pop       esi
00a32b3a b001                     mov       al, 1
00a32b3c 5b                       pop       ebx
00a32b3d 64890d00000000           mov       dword ptr fs:[0], ecx
00a32b44 8be5                     mov       esp, ebp
00a32b46 5d                       pop       ebp
00a32b47 c20c00                   ret       0xc
00a32b4a cc                       int3      
00a32b4b cc                       int3      
00a32b4c cc                       int3      
00a32b4d cc                       int3      
00a32b4e cc                       int3      
00a32b4f cc                       int3      
