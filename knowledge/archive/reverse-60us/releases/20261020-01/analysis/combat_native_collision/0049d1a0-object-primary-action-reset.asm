0049d1a0 55                       push      ebp
0049d1a1 8bec                     mov       ebp, esp
0049d1a3 53                       push      ebx
0049d1a4 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
0049d1a7 56                       push      esi
0049d1a8 57                       push      edi
0049d1a9 8b7d08                   mov       edi, dword ptr [ebp + 8]
0049d1ac 85ff                     test      edi, edi
0049d1ae 8bf1                     mov       esi, ecx
0049d1b0 751a                     jne       0x49d1cc
0049d1b2 8b8e4c010000             mov       ecx, dword ptr [esi + 0x14c]
0049d1b8 85c9                     test      ecx, ecx
0049d1ba 7441                     je        0x49d1fd
0049d1bc 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0049d1bf 50                       push      eax
0049d1c0 e81b125900               call      0xa2e3e0
0049d1c5 5f                       pop       edi
0049d1c6 5e                       pop       esi
0049d1c7 5b                       pop       ebx
0049d1c8 5d                       pop       ebp
0049d1c9 c20c00                   ret       0xc
0049d1cc 83ff0a                   cmp       edi, 0xa
0049d1cf 752c                     jne       0x49d1fd
0049d1d1 8b16                     mov       edx, dword ptr [esi]
0049d1d3 53                       push      ebx
0049d1d4 8bce                     mov       ecx, esi
0049d1d6 ff9250030000             call      dword ptr [edx + 0x350]
0049d1dc 85c0                     test      eax, eax
0049d1de 741d                     je        0x49d1fd
0049d1e0 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0049d1e3 8b16                     mov       edx, dword ptr [esi]
0049d1e5 50                       push      eax
0049d1e6 53                       push      ebx
0049d1e7 8bce                     mov       ecx, esi
0049d1e9 ff9250030000             call      dword ptr [edx + 0x350]
0049d1ef 8bc8                     mov       ecx, eax
0049d1f1 e8ea115900               call      0xa2e3e0
0049d1f6 5f                       pop       edi
0049d1f7 5e                       pop       esi
0049d1f8 5b                       pop       ebx
0049d1f9 5d                       pop       ebp
0049d1fa c20c00                   ret       0xc
0049d1fd 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0049d200 50                       push      eax
0049d201 53                       push      ebx
0049d202 57                       push      edi
0049d203 8bce                     mov       ecx, esi
0049d205 e896cdffff               call      0x499fa0
0049d20a 5f                       pop       edi
0049d20b 5e                       pop       esi
0049d20c 5b                       pop       ebx
0049d20d 5d                       pop       ebp
0049d20e c20c00                   ret       0xc
0049d211 cc                       int3      
0049d212 cc                       int3      
0049d213 cc                       int3      
0049d214 cc                       int3      
0049d215 cc                       int3      
0049d216 cc                       int3      
0049d217 cc                       int3      
0049d218 cc                       int3      
0049d219 cc                       int3      
0049d21a cc                       int3      
0049d21b cc                       int3      
0049d21c cc                       int3      
0049d21d cc                       int3      
0049d21e cc                       int3      
0049d21f cc                       int3      
0049d220 56                       push      esi
0049d221 8bf1                     mov       esi, ecx
0049d223 8a8685010000             mov       al, byte ptr [esi + 0x185]
0049d229 84c0                     test      al, al
0049d22b 741e                     je        0x49d24b
0049d22d 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049d233 e878fd5800               call      0xa2cfb0
0049d238 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
0049d23e 84c9                     test      cl, cl
0049d240 7409                     je        0x49d24b
0049d242 8b06                     mov       eax, dword ptr [esi]
0049d244 6a00                     push      0
0049d246 8bce                     mov       ecx, esi
0049d248 ff5060                   call      dword ptr [eax + 0x60]
0049d24b 8bce                     mov       ecx, esi
0049d24d 5e                       pop       esi
0049d24e e92decffff               jmp       0x49be80
0049d253 cc                       int3      
0049d254 cc                       int3      
0049d255 cc                       int3      
0049d256 cc                       int3      
0049d257 cc                       int3      
0049d258 cc                       int3      
0049d259 cc                       int3      
0049d25a cc                       int3      
0049d25b cc                       int3      
0049d25c cc                       int3      
0049d25d cc                       int3      
0049d25e cc                       int3      
0049d25f cc                       int3      
