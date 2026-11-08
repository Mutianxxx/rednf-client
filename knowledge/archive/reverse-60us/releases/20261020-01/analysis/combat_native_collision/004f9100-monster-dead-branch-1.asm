004f9100 da743a8b                 fidiv     dword ptr [edx + edi - 0x75]
004f9104 42                       inc       edx
004f9105 048b                     add       al, 0x8b
004f9107 49                       dec       ecx
004f9108 44                       inc       esp
004f9109 8b5b04                   mov       ebx, dword ptr [ebx + 4]
004f910c 8d0481                   lea       eax, [ecx + eax*4]
004f910f 8d0c99                   lea       ecx, [ecx + ebx*4]
004f9112 8b18                     mov       ebx, dword ptr [eax]
004f9114 33d9                     xor       ebx, ecx
004f9116 33d8                     xor       ebx, eax
004f9118 8919                     mov       dword ptr [ecx], ebx
004f911a 8b5204                   mov       edx, dword ptr [edx + 4]
004f911d 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f9123 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004f9126 8d0c90                   lea       ecx, [eax + edx*4]
004f9129 8b571c                   mov       edx, dword ptr [edi + 0x1c]
004f912c 8d0490                   lea       eax, [eax + edx*4]
004f912f 8b11                     mov       edx, dword ptr [ecx]
004f9131 33d0                     xor       edx, eax
004f9133 33d1                     xor       edx, ecx
004f9135 8910                     mov       dword ptr [eax], edx
004f9137 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f913d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f9140 83c220                   add       edx, 0x20
004f9143 83c720                   add       edi, 0x20
004f9146 3bfa                     cmp       edi, edx
004f9148 743c                     je        0x4f9186
004f914a 8b4204                   mov       eax, dword ptr [edx + 4]
004f914d 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004f9150 8b5f04                   mov       ebx, dword ptr [edi + 4]
004f9153 8d0481                   lea       eax, [ecx + eax*4]
004f9156 8d0c99                   lea       ecx, [ecx + ebx*4]
004f9159 8bd9                     mov       ebx, ecx
004f915b 33d8                     xor       ebx, eax
004f915d 3318                     xor       ebx, dword ptr [eax]
004f915f 8919                     mov       dword ptr [ecx], ebx
004f9161 8b5204                   mov       edx, dword ptr [edx + 4]
004f9164 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f916a 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004f916d 8d0c90                   lea       ecx, [eax + edx*4]
004f9170 8b5704                   mov       edx, dword ptr [edi + 4]
004f9173 8b39                     mov       edi, dword ptr [ecx]
004f9175 8d0490                   lea       eax, [eax + edx*4]
004f9178 8bd0                     mov       edx, eax
004f917a 33d1                     xor       edx, ecx
004f917c 33d7                     xor       edx, edi
004f917e 8910                     mov       dword ptr [eax], edx
004f9180 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f9186 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f9189 83c228                   add       edx, 0x28
004f918c 8dbe461e0000             lea       edi, [esi + 0x1e46]
004f9192 3bfa                     cmp       edi, edx
004f9194 7434                     je        0x4f91ca
004f9196 8b4204                   mov       eax, dword ptr [edx + 4]
004f9199 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004f919c 8b5f04                   mov       ebx, dword ptr [edi + 4]
004f919f 8d0481                   lea       eax, [ecx + eax*4]
004f91a2 8d0c99                   lea       ecx, [ecx + ebx*4]
004f91a5 8b18                     mov       ebx, dword ptr [eax]
004f91a7 33d9                     xor       ebx, ecx
004f91a9 33d8                     xor       ebx, eax
004f91ab 8919                     mov       dword ptr [ecx], ebx
004f91ad 8b5204                   mov       edx, dword ptr [edx + 4]
004f91b0 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f91b6 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004f91b9 8d0c90                   lea       ecx, [eax + edx*4]
004f91bc 8b5704                   mov       edx, dword ptr [edi + 4]
004f91bf 8d0490                   lea       eax, [eax + edx*4]
004f91c2 8b11                     mov       edx, dword ptr [ecx]
004f91c4 33d0                     xor       edx, eax
004f91c6 33d1                     xor       edx, ecx
004f91c8 8910                     mov       dword ptr [eax], edx
004f91ca 8b06                     mov       eax, dword ptr [esi]
004f91cc 8bce                     mov       ecx, esi
004f91ce ff90dc030000             call      dword ptr [eax + 0x3dc]
004f91d4 84c0                     test      al, al
004f91d6 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004f91d9 752f                     jne       0x4f920a
004f91db 8b13                     mov       edx, dword ptr [ebx]
004f91dd 8bcb                     mov       ecx, ebx
004f91df ff92a4020000             call      dword ptr [edx + 0x2a4]
004f91e5 85c0                     test      eax, eax
004f91e7 750a                     jne       0x4f91f3
004f91e9 8b03                     mov       eax, dword ptr [ebx]
004f91eb 8bcb                     mov       ecx, ebx
004f91ed ff90a0020000             call      dword ptr [eax + 0x2a0]
004f91f3 85c0                     test      eax, eax
004f91f5 8986841b0000             mov       dword ptr [esi + 0x1b84], eax
004f91fb 740d                     je        0x4f920a
004f91fd 8b10                     mov       edx, dword ptr [eax]
004f91ff 8bc8                     mov       ecx, eax
004f9201 ff5240                   call      dword ptr [edx + 0x40]
004f9204 8986ac240000             mov       dword ptr [esi + 0x24ac], eax
004f920a 8a86c11c0000             mov       al, byte ptr [esi + 0x1cc1]
004f9210 84c0                     test      al, al
004f9212 740a                     je        0x4f921e
004f9214 8b06                     mov       eax, dword ptr [esi]
004f9216 8bce                     mov       ecx, esi
004f9218 ff908c060000             call      dword ptr [eax + 0x68c]
004f921e 83be301a00000b           cmp       dword ptr [esi + 0x1a30], 0xb
004f9225 750c                     jne       0x4f9233
004f9227 8b16                     mov       edx, dword ptr [esi]
004f9229 6a04                     push      4
004f922b 8bce                     mov       ecx, esi
004f922d ff92f0050000             call      dword ptr [edx + 0x5f0]
004f9233 8b03                     mov       eax, dword ptr [ebx]
004f9235 8bcb                     mov       ecx, ebx
004f9237 ff90a4020000             call      dword ptr [eax + 0x2a4]
004f923d 85c0                     test      eax, eax
004f923f 0f849c000000             je        0x4f92e1
004f9245 8b13                     mov       edx, dword ptr [ebx]
004f9247 8bcb                     mov       ecx, ebx
004f9249 ff92b8010000             call      dword ptr [edx + 0x1b8]
004f924f 84c0                     test      al, al
004f9251 0f858a000000             jne       0x4f92e1
004f9257 8b06                     mov       eax, dword ptr [esi]
004f9259 53                       push      ebx
004f925a 8bce                     mov       ecx, esi
004f925c ff9018060000             call      dword ptr [eax + 0x618]
004f9262 3c01                     cmp       al, 1
004f9264 7522                     jne       0x4f9288
004f9266 6a00                     push      0
004f9268 e8834e3b00               call      0x8ae0f0
004f926d 99                       cdq       
004f926e b964000000               mov       ecx, 0x64
004f9273 f7f9                     idiv      ecx
004f9275 83c404                   add       esp, 4
004f9278 83fa46                   cmp       edx, 0x46
004f927b 7d0b                     jge       0x4f9288
004f927d 8b16                     mov       edx, dword ptr [esi]
004f927f 53                       push      ebx
