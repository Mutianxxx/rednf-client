00437ad0 55                       push      ebp
00437ad1 8bec                     mov       ebp, esp
00437ad3 6aff                     push      -1
00437ad5 688607c500               push      0xc50786
00437ada 64a100000000             mov       eax, dword ptr fs:[0]
00437ae0 50                       push      eax
00437ae1 64892500000000           mov       dword ptr fs:[0], esp
00437ae8 51                       push      ecx
00437ae9 53                       push      ebx
00437aea 56                       push      esi
00437aeb 8bf1                     mov       esi, ecx
00437aed 33db                     xor       ebx, ebx
00437aef 57                       push      edi
00437af0 8d7e24                   lea       edi, [esi + 0x24]
00437af3 8975f0                   mov       dword ptr [ebp - 0x10], esi
00437af6 895f04                   mov       dword ptr [edi + 4], ebx
00437af9 895f08                   mov       dword ptr [edi + 8], ebx
00437afc 895f0c                   mov       dword ptr [edi + 0xc], ebx
00437aff 8d4e38                   lea       ecx, [esi + 0x38]
00437b02 895dfc                   mov       dword ptr [ebp - 4], ebx
00437b05 e846ffffff               call      0x437a50
00437b0a b001                     mov       al, 1
00437b0c 8bcf                     mov       ecx, edi
00437b0e 8845fc                   mov       byte ptr [ebp - 4], al
00437b11 891e                     mov       dword ptr [esi], ebx
00437b13 895e04                   mov       dword ptr [esi + 4], ebx
00437b16 895e08                   mov       dword ptr [esi + 8], ebx
00437b19 895e0c                   mov       dword ptr [esi + 0xc], ebx
00437b1c 895e10                   mov       dword ptr [esi + 0x10], ebx
00437b1f 895e14                   mov       dword ptr [esi + 0x14], ebx
00437b22 895e18                   mov       dword ptr [esi + 0x18], ebx
00437b25 88461c                   mov       byte ptr [esi + 0x1c], al
00437b28 885e1d                   mov       byte ptr [esi + 0x1d], bl
00437b2b 895e20                   mov       dword ptr [esi + 0x20], ebx
00437b2e e8fdbafcff               call      0x403630
00437b33 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00437b36 885e34                   mov       byte ptr [esi + 0x34], bl
00437b39 5f                       pop       edi
00437b3a 8bc6                     mov       eax, esi
00437b3c 5e                       pop       esi
00437b3d 5b                       pop       ebx
00437b3e 64890d00000000           mov       dword ptr fs:[0], ecx
00437b45 8be5                     mov       esp, ebp
00437b47 5d                       pop       ebp
00437b48 c3                       ret       
