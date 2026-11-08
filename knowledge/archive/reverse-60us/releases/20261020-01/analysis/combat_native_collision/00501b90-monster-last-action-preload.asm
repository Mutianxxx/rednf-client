00501b90 c1f902                   sar       ecx, 2
00501b93 85d2                     test      edx, edx
00501b95 741c                     je        0x501bb3
00501b97 8b460c                   mov       eax, dword ptr [esi + 0xc]
00501b9a 2bc2                     sub       eax, edx
00501b9c c1f802                   sar       eax, 2
00501b9f 3bc8                     cmp       ecx, eax
00501ba1 7310                     jae       0x501bb3
00501ba3 8b4608                   mov       eax, dword ptr [esi + 8]
00501ba6 8938                     mov       dword ptr [eax], edi
00501ba8 83c004                   add       eax, 4
00501bab 894608                   mov       dword ptr [esi + 8], eax
00501bae 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
00501bb1 eb62                     jmp       0x501c15
00501bb3 8b4608                   mov       eax, dword ptr [esi + 8]
00501bb6 8d55cc                   lea       edx, [ebp - 0x34]
00501bb9 52                       push      edx
00501bba 6a01                     push      1
00501bbc 50                       push      eax
00501bbd 8bce                     mov       ecx, esi
00501bbf e89c43f0ff               call      0x405f60
00501bc4 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
00501bc7 eb4c                     jmp       0x501c15
00501bc9 c745b000000000           mov       dword ptr [ebp - 0x50], 0
00501bd0 8b5604                   mov       edx, dword ptr [esi + 4]
00501bd3 85d2                     test      edx, edx
00501bd5 7504                     jne       0x501bdb
00501bd7 33c9                     xor       ecx, ecx
00501bd9 eb08                     jmp       0x501be3
00501bdb 8b4e08                   mov       ecx, dword ptr [esi + 8]
00501bde 2bca                     sub       ecx, edx
00501be0 c1f902                   sar       ecx, 2
00501be3 85d2                     test      edx, edx
00501be5 741d                     je        0x501c04
00501be7 8b460c                   mov       eax, dword ptr [esi + 0xc]
00501bea 2bc2                     sub       eax, edx
00501bec c1f802                   sar       eax, 2
00501bef 3bc8                     cmp       ecx, eax
00501bf1 7311                     jae       0x501c04
00501bf3 8b4608                   mov       eax, dword ptr [esi + 8]
00501bf6 c70000000000             mov       dword ptr [eax], 0
00501bfc 83c004                   add       eax, 4
00501bff 894608                   mov       dword ptr [esi + 8], eax
00501c02 eb11                     jmp       0x501c15
00501c04 8b4608                   mov       eax, dword ptr [esi + 8]
00501c07 8d4db0                   lea       ecx, [ebp - 0x50]
00501c0a 51                       push      ecx
00501c0b 6a01                     push      1
00501c0d 50                       push      eax
00501c0e 8bce                     mov       ecx, esi
00501c10 e84b43f0ff               call      0x405f60
00501c15 ff45e4                   inc       dword ptr [ebp - 0x1c]
00501c18 8b5508                   mov       edx, dword ptr [ebp + 8]
00501c1b 83c704                   add       edi, 4
00501c1e 897df0                   mov       dword ptr [ebp - 0x10], edi
00501c21 3bba40070000             cmp       edi, dword ptr [edx + 0x740]
00501c27 0f85b4feffff             jne       0x501ae1
00501c2d 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501c30 68e0baca00               push      0xcabae0
00501c35 81c148070000             add       ecx, 0x748
00501c3b e8b0145500               call      0xa530f0
00501c40 50                       push      eax
00501c41 e8a5f16f00               call      0xc00deb
00501c46 83c408                   add       esp, 8
00501c49 85c0                     test      eax, eax
00501c4b 0f8482000000             je        0x501cd3
00501c51 68e0020000               push      0x2e0
00501c56 e8f51ff0ff               call      0x403c50
00501c5b 8bf8                     mov       edi, eax
00501c5d 83c404                   add       esp, 4
00501c60 897de8                   mov       dword ptr [ebp - 0x18], edi
00501c63 85ff                     test      edi, edi
00501c65 c745fc16000000           mov       dword ptr [ebp - 4], 0x16
00501c6c 7432                     je        0x501ca0
00501c6e 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
00501c75 7208                     jb        0x501c7f
00501c77 8bb348020000             mov       esi, dword ptr [ebx + 0x248]
00501c7d eb06                     jmp       0x501c85
00501c7f 8db348020000             lea       esi, [ebx + 0x248]
00501c85 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501c88 6a00                     push      0
00501c8a 81c148070000             add       ecx, 0x748
00501c90 e85b145500               call      0xa530f0
00501c95 50                       push      eax
00501c96 56                       push      esi
00501c97 8bcf                     mov       ecx, edi
00501c99 e8621cfaff               call      0x4a3900
00501c9e eb02                     jmp       0x501ca2
00501ca0 33c0                     xor       eax, eax
00501ca2 85c0                     test      eax, eax
00501ca4 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00501cab 898350010000             mov       dword ptr [ebx + 0x150], eax
00501cb1 7420                     je        0x501cd3
00501cb3 c780cc0200000b000000     mov       dword ptr [eax + 0x2cc], 0xb
00501cbd c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
00501cc7 8b8b50010000             mov       ecx, dword ptr [ebx + 0x150]
00501ccd 53                       push      ebx
00501cce e84db35200               call      0xa2d020
00501cd3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501cd6 68e0baca00               push      0xcabae0
00501cdb 81c14c070000             add       ecx, 0x74c
00501ce1 e80a145500               call      0xa530f0
00501ce6 50                       push      eax
00501ce7 e8fff06f00               call      0xc00deb
00501cec 83c408                   add       esp, 8
00501cef 85c0                     test      eax, eax
00501cf1 0f8482000000             je        0x501d79
00501cf7 68e0020000               push      0x2e0
00501cfc e84f1ff0ff               call      0x403c50
00501d01 8bf8                     mov       edi, eax
00501d03 83c404                   add       esp, 4
00501d06 897de8                   mov       dword ptr [ebp - 0x18], edi
00501d09 85ff                     test      edi, edi
00501d0b c745fc17000000           mov       dword ptr [ebp - 4], 0x17
00501d12 7432                     je        0x501d46
00501d14 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
00501d1b 7208                     jb        0x501d25
00501d1d 8bb348020000             mov       esi, dword ptr [ebx + 0x248]
00501d23 eb06                     jmp       0x501d2b
00501d25 8db348020000             lea       esi, [ebx + 0x248]
00501d2b 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501d2e 6a00                     push      0
00501d30 81c14c070000             add       ecx, 0x74c
00501d36 e8b5135500               call      0xa530f0
00501d3b 50                       push      eax
00501d3c 56                       push      esi
00501d3d 8bcf                     mov       ecx, edi
00501d3f e8bc1bfaff               call      0x4a3900
00501d44 eb02                     jmp       0x501d48
00501d46 33c0                     xor       eax, eax
00501d48 85c0                     test      eax, eax
00501d4a c7                       .byte     0xc7
00501d4b 45                       inc       ebp
00501d4c fc                       cld       
00501d4d ff                       .byte     0xff
00501d4e ff                       .byte     0xff
00501d4f ff                       .byte     0xff
