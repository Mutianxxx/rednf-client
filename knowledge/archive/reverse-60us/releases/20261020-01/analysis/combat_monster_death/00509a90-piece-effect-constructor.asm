00509a90 55                       push      ebp
00509a91 8bec                     mov       ebp, esp
00509a93 6aff                     push      -1
00509a95 6838a3c500               push      0xc5a338
00509a9a 64a100000000             mov       eax, dword ptr fs:[0]
00509aa0 50                       push      eax
00509aa1 64892500000000           mov       dword ptr fs:[0], esp
00509aa8 51                       push      ecx
00509aa9 56                       push      esi
00509aaa 8bf1                     mov       esi, ecx
00509aac 8975f0                   mov       dword ptr [ebp - 0x10], esi
00509aaf e84cdfefff               call      0x407a00
00509ab4 8bce                     mov       ecx, esi
00509ab6 c745fc00000000           mov       dword ptr [ebp - 4], 0
00509abd c7065c5bcd00             mov       dword ptr [esi], 0xcd5b5c
00509ac3 e818343100               call      0x81cee0
00509ac8 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
00509acb 8b4d18                   mov       ecx, dword ptr [ebp + 0x18]
00509ace 8b5514                   mov       edx, dword ptr [ebp + 0x14]
00509ad1 50                       push      eax
00509ad2 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00509ad5 51                       push      ecx
00509ad6 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00509ad9 52                       push      edx
00509ada 8b5508                   mov       edx, dword ptr [ebp + 8]
00509add 50                       push      eax
00509ade 51                       push      ecx
00509adf 52                       push      edx
00509ae0 8bce                     mov       ecx, esi
00509ae2 e8b9343100               call      0x81cfa0
00509ae7 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00509aea 8bc6                     mov       eax, esi
00509aec 5e                       pop       esi
00509aed 64890d00000000           mov       dword ptr fs:[0], ecx
00509af4 8be5                     mov       esp, ebp
00509af6 5d                       pop       ebp
00509af7 c21800                   ret       0x18
