0040a9c0 1ddc012101               sbb       eax, 0x12101dc
0040a9c5 83f314                   xor       ebx, 0x14
0040a9c8 891c08                   mov       dword ptr [eax + ecx], ebx
0040a9cb 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0040a9d1 8b8640010000             mov       eax, dword ptr [esi + 0x140]
0040a9d7 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
0040a9da c1e002                   shl       eax, 2
0040a9dd 8d1c08                   lea       ebx, [eax + ecx]
0040a9e0 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0040a9e6 83f314                   xor       ebx, 0x14
0040a9e9 85ff                     test      edi, edi
0040a9eb 891c08                   mov       dword ptr [eax + ecx], ebx
0040a9ee 756e                     jne       0x40aa5e
0040a9f0 6a01                     push      1
0040a9f2 57                       push      edi
0040a9f3 52                       push      edx
0040a9f4 8b55b8                   mov       edx, dword ptr [ebp - 0x48]
0040a9f7 52                       push      edx
0040a9f8 e8339f0c00               call      0x4d4930
0040a9fd 50                       push      eax
0040a9fe 68dcbeca00               push      0xcabedc
0040aa03 57                       push      edi
0040aa04 e897806400               call      0xa52aa0
0040aa09 83c41c                   add       esp, 0x1c
0040aa0c 50                       push      eax
0040aa0d 8bce                     mov       ecx, esi
0040aa0f e88c8e6400               call      0xa538a0
0040aa14 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0040aa1a 8b4a44                   mov       ecx, dword ptr [edx + 0x44]
0040aa1d 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0040aa23 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
0040aa29 c1e002                   shl       eax, 2
0040aa2c 8d1408                   lea       edx, [eax + ecx]
0040aa2f 33d3                     xor       edx, ebx
0040aa31 81f28e130000             xor       edx, 0x138e
0040aa37 891408                   mov       dword ptr [eax + ecx], edx
0040aa3a a1d8012101               mov       eax, dword ptr [0x12101d8]
0040aa3f 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0040aa42 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0040aa48 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
0040aa4e c1e002                   shl       eax, 2
0040aa51 8d1408                   lea       edx, [eax + ecx]
0040aa54 33d3                     xor       edx, ebx
0040aa56 81f28e130000             xor       edx, 0x138e
0040aa5c eb68                     jmp       0x40aac6
0040aa5e 8b4db8                   mov       ecx, dword ptr [ebp - 0x48]
0040aa61 8d4701                   lea       eax, [edi + 1]
0040aa64 50                       push      eax
0040aa65 6a01                     push      1
0040aa67 6a00                     push      0
0040aa69 52                       push      edx
0040aa6a 51                       push      ecx
0040aa6b e8c09e0c00               call      0x4d4930
0040aa70 83c410                   add       esp, 0x10
0040aa73 50                       push      eax
0040aa74 68ccbeca00               push      0xcabecc
0040aa79 6a00                     push      0
0040aa7b e820806400               call      0xa52aa0
0040aa80 83c410                   add       esp, 0x10
0040aa83 50                       push      eax
0040aa84 8bce                     mov       ecx, esi
0040aa86 e8158e6400               call      0xa538a0
0040aa8b a1d8012101               mov       eax, dword ptr [0x12101d8]
0040aa90 8b4844                   mov       ecx, dword ptr [eax + 0x44]
0040aa93 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0040aa99 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
0040aa9f c1e002                   shl       eax, 2
0040aaa2 8d1408                   lea       edx, [eax + ecx]
0040aaa5 33d3                     xor       edx, ebx
0040aaa7 891408                   mov       dword ptr [eax + ecx], edx
0040aaaa a1d8012101               mov       eax, dword ptr [0x12101d8]
0040aaaf 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0040aab2 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0040aab8 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
0040aabe c1e002                   shl       eax, 2
0040aac1 8d1408                   lea       edx, [eax + ecx]
0040aac4 33d3                     xor       edx, ebx
0040aac6 891408                   mov       dword ptr [eax + ecx], edx
0040aac9 c745d000000000           mov       dword ptr [ebp - 0x30], 0
0040aad0 8b45cc                   mov       eax, dword ptr [ebp - 0x34]
0040aad3 8b8c051cfeffff           mov       ecx, dword ptr [ebp + eax - 0x1e4]
0040aada 85c9                     test      ecx, ecx
0040aadc 8b5de4                   mov       ebx, dword ptr [ebp - 0x1c]
0040aadf 0f8482000000             je        0x40ab67
0040aae5 8b840520feffff           mov       eax, dword ptr [ebp + eax - 0x1e0]
0040aaec 2bc1                     sub       eax, ecx
0040aaee 8b4dd0                   mov       ecx, dword ptr [ebp - 0x30]
0040aaf1 c1f802                   sar       eax, 2
0040aaf4 3bc8                     cmp       ecx, eax
0040aaf6 736f                     jae       0x40ab67
0040aaf8 8b45cc                   mov       eax, dword ptr [ebp - 0x34]
0040aafb 8b                       .byte     0x8b
0040aafc 84                       .byte     0x84
0040aafd 05                       .byte     0x05
0040aafe 1cfe                     sbb       al, 0xfe
