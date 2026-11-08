00472a60 55                       push      ebp
00472a61 8bec                     mov       ebp, esp
00472a63 6aff                     push      -1
00472a65 68834ac500               push      0xc54a83
00472a6a 64a100000000             mov       eax, dword ptr fs:[0]
00472a70 50                       push      eax
00472a71 64892500000000           mov       dword ptr fs:[0], esp
00472a78 51                       push      ecx
00472a79 53                       push      ebx
00472a7a 56                       push      esi
00472a7b 8bf1                     mov       esi, ecx
00472a7d 33db                     xor       ebx, ebx
00472a7f 57                       push      edi
00472a80 8975f0                   mov       dword ptr [ebp - 0x10], esi
00472a83 895e08                   mov       dword ptr [esi + 8], ebx
00472a86 895e0c                   mov       dword ptr [esi + 0xc], ebx
00472a89 895e10                   mov       dword ptr [esi + 0x10], ebx
00472a8c 895dfc                   mov       dword ptr [ebp - 4], ebx
00472a8f 895e38                   mov       dword ptr [esi + 0x38], ebx
00472a92 895e3c                   mov       dword ptr [esi + 0x3c], ebx
00472a95 895e40                   mov       dword ptr [esi + 0x40], ebx
00472a98 895e44                   mov       dword ptr [esi + 0x44], ebx
00472a9b 8d4e48                   lea       ecx, [esi + 0x48]
00472a9e c645fc01                 mov       byte ptr [ebp - 4], 1
00472aa2 e8b928f9ff               call      0x405360
00472aa7 899e98000000             mov       dword ptr [esi + 0x98], ebx
00472aad 899e9c000000             mov       dword ptr [esi + 0x9c], ebx
00472ab3 899ea0000000             mov       dword ptr [esi + 0xa0], ebx
00472ab9 8d8ea8000000             lea       ecx, [esi + 0xa8]
00472abf c645fc03                 mov       byte ptr [ebp - 4], 3
00472ac3 e868b9ffff               call      0x46e430
00472ac8 8dbe7c010000             lea       edi, [esi + 0x17c]
00472ace 8bcf                     mov       ecx, edi
00472ad0 c645fc04                 mov       byte ptr [ebp - 4], 4
00472ad4 e807cbfcff               call      0x43f5e0
00472ad9 894704                   mov       dword ptr [edi + 4], eax
00472adc 895f08                   mov       dword ptr [edi + 8], ebx
00472adf b807000000               mov       eax, 7
00472ae4 8986b8010000             mov       dword ptr [esi + 0x1b8], eax
00472aea 899eb4010000             mov       dword ptr [esi + 0x1b4], ebx
00472af0 66899ea4010000           mov       word ptr [esi + 0x1a4], bx
00472af7 899ec0010000             mov       dword ptr [esi + 0x1c0], ebx
00472afd 899ec4010000             mov       dword ptr [esi + 0x1c4], ebx
00472b03 899ec8010000             mov       dword ptr [esi + 0x1c8], ebx
00472b09 8dbecc010000             lea       edi, [esi + 0x1cc]
00472b0f 8bcf                     mov       ecx, edi
00472b11 8845fc                   mov       byte ptr [ebp - 4], al
00472b14 e877870b00               call      0x52b290
00472b19 894704                   mov       dword ptr [edi + 4], eax
00472b1c c6402d01                 mov       byte ptr [eax + 0x2d], 1
00472b20 8b4704                   mov       eax, dword ptr [edi + 4]
00472b23 894004                   mov       dword ptr [eax + 4], eax
00472b26 8b4704                   mov       eax, dword ptr [edi + 4]
00472b29 8900                     mov       dword ptr [eax], eax
00472b2b 8b4704                   mov       eax, dword ptr [edi + 4]
00472b2e 894008                   mov       dword ptr [eax + 8], eax
00472b31 895f08                   mov       dword ptr [edi + 8], ebx
00472b34 899edc010000             mov       dword ptr [esi + 0x1dc], ebx
00472b3a 899ee0010000             mov       dword ptr [esi + 0x1e0], ebx
00472b40 899ee4010000             mov       dword ptr [esi + 0x1e4], ebx
00472b46 8bce                     mov       ecx, esi
00472b48 c645fc09                 mov       byte ptr [ebp - 4], 9
00472b4c 885e18                   mov       byte ptr [esi + 0x18], bl
00472b4f e80c505b00               call      0xa27b60
00472b54 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00472b57 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00472b5a 8b5508                   mov       edx, dword ptr [ebp + 8]
00472b5d 53                       push      ebx
00472b5e 53                       push      ebx
00472b5f 53                       push      ebx
00472b60 53                       push      ebx
00472b61 50                       push      eax
00472b62 51                       push      ecx
00472b63 52                       push      edx
00472b64 8bce                     mov       ecx, esi
00472b66 e8656f5b00               call      0xa29ad0
00472b6b 5f                       pop       edi
00472b6c 8bc6                     mov       eax, esi
00472b6e 5e                       pop       esi
00472b6f 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00472b72 5b                       pop       ebx
00472b73 64890d00000000           mov       dword ptr fs:[0], ecx
00472b7a 8be5                     mov       esp, ebp
00472b7c 5d                       pop       ebp
00472b7d c20c00                   ret       0xc
00472b80 55                       push      ebp
00472b81 8bec                     mov       ebp, esp
00472b83 6aff                     push      -1
00472b85 68834ac500               push      0xc54a83
00472b8a 64a100000000             mov       eax, dword ptr fs:[0]
00472b90 50                       push      eax
00472b91 64892500000000           mov       dword ptr fs:[0], esp
00472b98 51                       push      ecx
00472b99 53                       push      ebx
00472b9a 56                       push      esi
00472b9b 8bf1                     mov       esi, ecx
00472b9d 33db                     xor       ebx, ebx
00472b9f 57                       push      edi
00472ba0 8975f0                   mov       dword ptr [ebp - 0x10], esi
00472ba3 895e08                   mov       dword ptr [esi + 8], ebx
00472ba6 895e0c                   mov       dword ptr [esi + 0xc], ebx
00472ba9 895e10                   mov       dword ptr [esi + 0x10], ebx
00472bac 895dfc                   mov       dword ptr [ebp - 4], ebx
00472baf 89                       .byte     0x89
