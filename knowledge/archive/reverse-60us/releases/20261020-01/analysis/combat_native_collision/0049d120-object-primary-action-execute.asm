0049d120 55                       push      ebp
0049d121 8bec                     mov       ebp, esp
0049d123 53                       push      ebx
0049d124 8b5d14                   mov       ebx, dword ptr [ebp + 0x14]
0049d127 56                       push      esi
0049d128 57                       push      edi
0049d129 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
0049d12c 85ff                     test      edi, edi
0049d12e 8bf1                     mov       esi, ecx
0049d130 751e                     jne       0x49d150
0049d132 8b8e4c010000             mov       ecx, dword ptr [esi + 0x14c]
0049d138 85c9                     test      ecx, ecx
0049d13a 7449                     je        0x49d185
0049d13c 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049d13f 8b5508                   mov       edx, dword ptr [ebp + 8]
0049d142 50                       push      eax
0049d143 52                       push      edx
0049d144 e8078f5900               call      0xa36050
0049d149 5f                       pop       edi
0049d14a 5e                       pop       esi
0049d14b 5b                       pop       ebx
0049d14c 5d                       pop       ebp
0049d14d c21000                   ret       0x10
0049d150 83ff0a                   cmp       edi, 0xa
0049d153 7530                     jne       0x49d185
0049d155 8b06                     mov       eax, dword ptr [esi]
0049d157 53                       push      ebx
0049d158 8bce                     mov       ecx, esi
0049d15a ff9050030000             call      dword ptr [eax + 0x350]
0049d160 85c0                     test      eax, eax
0049d162 7421                     je        0x49d185
0049d164 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d167 8b5508                   mov       edx, dword ptr [ebp + 8]
0049d16a 8b06                     mov       eax, dword ptr [esi]
0049d16c 51                       push      ecx
0049d16d 52                       push      edx
0049d16e 53                       push      ebx
0049d16f 8bce                     mov       ecx, esi
0049d171 ff9050030000             call      dword ptr [eax + 0x350]
0049d177 8bc8                     mov       ecx, eax
0049d179 e8d28e5900               call      0xa36050
0049d17e 5f                       pop       edi
0049d17f 5e                       pop       esi
0049d180 5b                       pop       ebx
0049d181 5d                       pop       ebp
0049d182 c21000                   ret       0x10
0049d185 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d188 8b5508                   mov       edx, dword ptr [ebp + 8]
0049d18b 53                       push      ebx
0049d18c 57                       push      edi
0049d18d 51                       push      ecx
0049d18e 52                       push      edx
0049d18f 8bce                     mov       ecx, esi
0049d191 e80acfffff               call      0x49a0a0
0049d196 5f                       pop       edi
0049d197 5e                       pop       esi
0049d198 5b                       pop       ebx
0049d199 5d                       pop       ebp
0049d19a c21000                   ret       0x10
0049d19d cc                       int3      
0049d19e cc                       int3      
0049d19f cc                       int3      
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
