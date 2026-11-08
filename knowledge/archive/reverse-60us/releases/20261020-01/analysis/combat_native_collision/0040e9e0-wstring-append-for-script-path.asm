0040e9e0 55                       push      ebp
0040e9e1 8bec                     mov       ebp, esp
0040e9e3 53                       push      ebx
0040e9e4 8bd9                     mov       ebx, ecx
0040e9e6 8b5318                   mov       edx, dword ptr [ebx + 0x18]
0040e9e9 83fa08                   cmp       edx, 8
0040e9ec 56                       push      esi
0040e9ed 57                       push      edi
0040e9ee 7205                     jb        0x40e9f5
0040e9f0 8b4304                   mov       eax, dword ptr [ebx + 4]
0040e9f3 eb03                     jmp       0x40e9f8
0040e9f5 8d4304                   lea       eax, [ebx + 4]
0040e9f8 8b7508                   mov       esi, dword ptr [ebp + 8]
0040e9fb 3bf0                     cmp       esi, eax
0040e9fd 7237                     jb        0x40ea36
0040e9ff 83fa08                   cmp       edx, 8
0040ea02 8d4304                   lea       eax, [ebx + 4]
0040ea05 7204                     jb        0x40ea0b
0040ea07 8b08                     mov       ecx, dword ptr [eax]
0040ea09 eb02                     jmp       0x40ea0d
0040ea0b 8bc8                     mov       ecx, eax
0040ea0d 8b7b14                   mov       edi, dword ptr [ebx + 0x14]
0040ea10 8d0c79                   lea       ecx, [ecx + edi*2]
0040ea13 3bce                     cmp       ecx, esi
0040ea15 761f                     jbe       0x40ea36
0040ea17 83fa08                   cmp       edx, 8
0040ea1a 7202                     jb        0x40ea1e
0040ea1c 8b00                     mov       eax, dword ptr [eax]
0040ea1e 8b550c                   mov       edx, dword ptr [ebp + 0xc]
0040ea21 2bf0                     sub       esi, eax
0040ea23 52                       push      edx
0040ea24 d1fe                     sar       esi, 1
0040ea26 56                       push      esi
0040ea27 53                       push      ebx
0040ea28 8bcb                     mov       ecx, ebx
0040ea2a e891feffff               call      0x40e8c0
0040ea2f 5f                       pop       edi
0040ea30 5e                       pop       esi
0040ea31 5b                       pop       ebx
0040ea32 5d                       pop       ebp
0040ea33 c20800                   ret       8
0040ea36 8b5314                   mov       edx, dword ptr [ebx + 0x14]
0040ea39 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
0040ea3c 83c8ff                   or        eax, 0xffffffff
0040ea3f 2bc2                     sub       eax, edx
0040ea41 3bc7                     cmp       eax, edi
0040ea43 7707                     ja        0x40ea4c
0040ea45 8bcb                     mov       ecx, ebx
0040ea47 e835ef7d00               call      0xbed981
0040ea4c 85ff                     test      edi, edi
0040ea4e 0f86a9000000             jbe       0x40eafd
0040ea54 8b7b14                   mov       edi, dword ptr [ebx + 0x14]
0040ea57 037d0c                   add       edi, dword ptr [ebp + 0xc]
0040ea5a 81fffeffff7f             cmp       edi, 0x7ffffffe
0040ea60 897d08                   mov       dword ptr [ebp + 8], edi
0040ea63 7607                     jbe       0x40ea6c
0040ea65 8bcb                     mov       ecx, ebx
0040ea67 e815ef7d00               call      0xbed981
0040ea6c 8b4318                   mov       eax, dword ptr [ebx + 0x18]
0040ea6f 3bc7                     cmp       eax, edi
0040ea71 731b                     jae       0x40ea8e
0040ea73 8b4b14                   mov       ecx, dword ptr [ebx + 0x14]
0040ea76 51                       push      ecx
0040ea77 57                       push      edi
0040ea78 8bcb                     mov       ecx, ebx
0040ea7a e8b137ffff               call      0x402230
0040ea7f 85ff                     test      edi, edi
0040ea81 767a                     jbe       0x40eafd
0040ea83 837b1808                 cmp       dword ptr [ebx + 0x18], 8
0040ea87 7231                     jb        0x40eaba
0040ea89 8b4304                   mov       eax, dword ptr [ebx + 4]
0040ea8c eb2f                     jmp       0x40eabd
0040ea8e 85ff                     test      edi, edi
0040ea90 75ef                     jne       0x40ea81
0040ea92 83f808                   cmp       eax, 8
0040ea95 897b14                   mov       dword ptr [ebx + 0x14], edi
0040ea98 720f                     jb        0x40eaa9
0040ea9a 8b4304                   mov       eax, dword ptr [ebx + 4]
0040ea9d 668938                   mov       word ptr [eax], di
0040eaa0 5f                       pop       edi
0040eaa1 5e                       pop       esi
0040eaa2 8bc3                     mov       eax, ebx
0040eaa4 5b                       pop       ebx
0040eaa5 5d                       pop       ebp
0040eaa6 c20800                   ret       8
0040eaa9 8d4304                   lea       eax, [ebx + 4]
0040eaac 5f                       pop       edi
0040eaad 66c7000000               mov       word ptr [eax], 0
0040eab2 5e                       pop       esi
0040eab3 8bc3                     mov       eax, ebx
0040eab5 5b                       pop       ebx
0040eab6 5d                       pop       ebp
0040eab7 c20800                   ret       8
0040eaba 8d4304                   lea       eax, [ebx + 4]
0040eabd 8b5314                   mov       edx, dword ptr [ebx + 0x14]
0040eac0 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0040eac3 03c9                     add       ecx, ecx
0040eac5 8d3c50                   lea       edi, [eax + edx*2]
0040eac8 8bc1                     mov       eax, ecx
0040eaca c1e902                   shr       ecx, 2
0040eacd f3a5                     rep movsd dword ptr es:[edi], dword ptr [esi]
0040eacf 8bc8                     mov       ecx, eax
0040ead1 83e103                   and       ecx, 3
0040ead4 f3a4                     rep movsb byte ptr es:[edi], byte ptr [esi]
0040ead6 837b1808                 cmp       dword ptr [ebx + 0x18], 8
0040eada 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0040eadd 894b14                   mov       dword ptr [ebx + 0x14], ecx
0040eae0 7212                     jb        0x40eaf4
0040eae2 8b4304                   mov       eax, dword ptr [ebx + 4]
0040eae5 5f                       pop       edi
0040eae6 66c704480000             mov       word ptr [eax + ecx*2], 0
0040eaec 5e                       pop       esi
0040eaed 8bc3                     mov       eax, ebx
0040eaef 5b                       pop       ebx
0040eaf0 5d                       pop       ebp
0040eaf1 c20800                   ret       8
0040eaf4 8d4304                   lea       eax, [ebx + 4]
0040eaf7 66c704480000             mov       word ptr [eax + ecx*2], 0
0040eafd 5f                       pop       edi
0040eafe 5e                       pop       esi
0040eaff 8bc3                     mov       eax, ebx
0040eb01 5b                       pop       ebx
0040eb02 5d                       pop       ebp
0040eb03 c20800                   ret       8
0040eb06 cc                       int3      
0040eb07 cc                       int3      
0040eb08 cc                       int3      
0040eb09 cc                       int3      
0040eb0a cc                       int3      
0040eb0b cc                       int3      
0040eb0c cc                       int3      
0040eb0d cc                       int3      
0040eb0e cc                       int3      
0040eb0f cc                       int3      
0040eb10 55                       push      ebp
0040eb11 8bec                     mov       ebp, esp
0040eb13 56                       push      esi
0040eb14 33c0                     xor       eax, eax
0040eb16 8bf1                     mov       esi, ecx
0040eb18 6aff                     push      -1
0040eb1a 894614                   mov       dword ptr [esi + 0x14], eax
0040eb1d c7461807000000           mov       dword ptr [esi + 0x18], 7
0040eb24 50                       push      eax
0040eb25 66894604                 mov       word ptr [esi + 4], ax
0040eb29 8b4508                   mov       eax, dword ptr [ebp + 8]
0040eb2c 50                       push      eax
0040eb2d e8                       .byte     0xe8
0040eb2e 2e42                     inc       edx
