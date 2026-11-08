0049c090 8b01                     mov       eax, dword ptr [ecx]
0049c092 ff9060010000             call      dword ptr [eax + 0x160]
0049c098 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
0049c09e 3bc1                     cmp       eax, ecx
0049c0a0 750a                     jne       0x49c0ac
0049c0a2 85c9                     test      ecx, ecx
0049c0a4 7406                     je        0x49c0ac
0049c0a6 b801000000               mov       eax, 1
0049c0ab c3                       ret       
0049c0ac 33c0                     xor       eax, eax
0049c0ae c3                       ret       
0049c0af cc                       int3      
0049c0b0 55                       push      ebp
0049c0b1 8bec                     mov       ebp, esp
0049c0b3 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c0b6 d9448104                 fld       dword ptr [ecx + eax*4 + 4]
0049c0ba 5d                       pop       ebp
0049c0bb c20400                   ret       4
0049c0be cc                       int3      
0049c0bf cc                       int3      
0049c0c0 55                       push      ebp
0049c0c1 8bec                     mov       ebp, esp
0049c0c3 d9450c                   fld       dword ptr [ebp + 0xc]
0049c0c6 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c0c9 d95c8104                 fstp      dword ptr [ecx + eax*4 + 4]
0049c0cd 5d                       pop       ebp
0049c0ce c20800                   ret       8
0049c0d1 cc                       int3      
0049c0d2 cc                       int3      
0049c0d3 cc                       int3      
0049c0d4 cc                       int3      
0049c0d5 cc                       int3      
0049c0d6 cc                       int3      
0049c0d7 cc                       int3      
0049c0d8 cc                       int3      
0049c0d9 cc                       int3      
0049c0da cc                       int3      
0049c0db cc                       int3      
0049c0dc cc                       int3      
0049c0dd cc                       int3      
0049c0de cc                       int3      
0049c0df cc                       int3      
0049c0e0 55                       push      ebp
0049c0e1 8bec                     mov       ebp, esp
0049c0e3 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c0e6 d9448110                 fld       dword ptr [ecx + eax*4 + 0x10]
0049c0ea 5d                       pop       ebp
0049c0eb c20400                   ret       4
0049c0ee cc                       int3      
0049c0ef cc                       int3      
0049c0f0 55                       push      ebp
0049c0f1 8bec                     mov       ebp, esp
0049c0f3 d9450c                   fld       dword ptr [ebp + 0xc]
0049c0f6 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c0f9 d95c8110                 fstp      dword ptr [ecx + eax*4 + 0x10]
0049c0fd 5d                       pop       ebp
0049c0fe c20800                   ret       8
0049c101 cc                       int3      
0049c102 cc                       int3      
0049c103 cc                       int3      
0049c104 cc                       int3      
0049c105 cc                       int3      
0049c106 cc                       int3      
0049c107 cc                       int3      
0049c108 cc                       int3      
0049c109 cc                       int3      
0049c10a cc                       int3      
0049c10b cc                       int3      
0049c10c cc                       int3      
0049c10d cc                       int3      
0049c10e cc                       int3      
0049c10f cc                       int3      
0049c110 55                       push      ebp
0049c111 8bec                     mov       ebp, esp
0049c113 6aff                     push      -1
0049c115 681b6ac500               push      0xc56a1b
0049c11a 64a100000000             mov       eax, dword ptr fs:[0]
0049c120 50                       push      eax
0049c121 64892500000000           mov       dword ptr fs:[0], esp
0049c128 51                       push      ecx
0049c129 56                       push      esi
0049c12a 8bf1                     mov       esi, ecx
0049c12c 8975f0                   mov       dword ptr [ebp - 0x10], esi
0049c12f c745fc00000000           mov       dword ptr [ebp - 4], 0
0049c136 e8a5b70800               call      0x5278e0
0049c13b 8d4e04                   lea       ecx, [esi + 4]
0049c13e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049c145 e8e680f6ff               call      0x404230
0049c14a 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049c14d 5e                       pop       esi
0049c14e 64890d00000000           mov       dword ptr fs:[0], ecx
0049c155 8be5                     mov       esp, ebp
0049c157 5d                       pop       ebp
0049c158 c3                       ret       
0049c159 cc                       int3      
0049c15a cc                       int3      
0049c15b cc                       int3      
0049c15c cc                       int3      
0049c15d cc                       int3      
0049c15e cc                       int3      
0049c15f cc                       int3      
0049c160 55                       push      ebp
0049c161 8bec                     mov       ebp, esp
0049c163 6aff                     push      -1
0049c165 683e6ac500               push      0xc56a3e
0049c16a 64a100000000             mov       eax, dword ptr fs:[0]
0049c170 50                       push      eax
0049c171 64892500000000           mov       dword ptr fs:[0], esp
0049c178 51                       push      ecx
0049c179 56                       push      esi
0049c17a 8bf1                     mov       esi, ecx
0049c17c 8975f0                   mov       dword ptr [ebp - 0x10], esi
0049c17f c745fc00000000           mov       dword ptr [ebp - 4], 0
0049c186 e895610700               call      0x512320
0049c18b 8d8ea0000000             lea       ecx, [esi + 0xa0]
0049c191 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049c198 e89380f6ff               call      0x404230
0049c19d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049c1a0 5e                       pop       esi
0049c1a1 64890d00000000           mov       dword ptr fs:[0], ecx
0049c1a8 8be5                     mov       esp, ebp
0049c1aa 5d                       pop       ebp
0049c1ab c3                       ret       
0049c1ac cc                       int3      
0049c1ad cc                       int3      
0049c1ae cc                       int3      
0049c1af cc                       int3      
0049c1b0 81c168180000             add       ecx, 0x1868
0049c1b6 e8a55ef6ff               call      0x402060
0049c1bb f7d8                     neg       eax
0049c1bd 1bc0                     sbb       eax, eax
0049c1bf f7d8                     neg       eax
0049c1c1 c3                       ret       
0049c1c2 cc                       int3      
0049c1c3 cc                       int3      
0049c1c4 cc                       int3      
0049c1c5 cc                       int3      
0049c1c6 cc                       int3      
0049c1c7 cc                       int3      
0049c1c8 cc                       int3      
0049c1c9 cc                       int3      
0049c1ca cc                       int3      
0049c1cb cc                       int3      
0049c1cc cc                       int3      
0049c1cd cc                       int3      
0049c1ce cc                       int3      
0049c1cf cc                       int3      
0049c1d0 55                       push      ebp
0049c1d1 8bec                     mov       ebp, esp
0049c1d3 51                       push      ecx
0049c1d4 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c1d7 56                       push      esi
0049c1d8 8bf1                     mov       esi, ecx
0049c1da 394604                   cmp       dword ptr [esi + 4], eax
0049c1dd 8975fc                   mov       dword ptr [ebp - 4], esi
0049c1e0 0f83ab000000             jae       0x49c291
0049c1e6 53                       push      ebx
0049c1e7 57                       push      edi
0049c1e8 8d3c8500000000           lea       edi, [eax*4]
0049c1ef 57                       push      edi
0049c1f0 e8c3597600               call      0xc01bb8
0049c1f5 8bd8                     mov       ebx, eax
0049c1f7 83c404                   add       esp, 4
0049c1fa 85db                     test      ebx, ebx
0049c1fc 0f8484000000             je        0x49c286
0049c202 8bcf                     mov       ecx, edi
0049c204 8bd1                     mov       edx, ecx
0049c206 c1e902                   shr       ecx, 2
0049c209 33c0                     xor       eax, eax
0049c20b 8bfb                     mov       edi, ebx
0049c20d f3ab                     rep stosd dword ptr es:[edi], eax
0049c20f 8bca                     mov       ecx, edx
0049c211 83e103                   and       ecx, 3
0049c214 f3aa                     rep stosb byte ptr es:[edi], al
0049c216 8b4604                   mov       eax, dword ptr [esi + 4]
0049c219 8b4e08                   mov       ecx, dword ptr [esi + 8]
0049c21c c1e002                   shl       eax, 2
0049c21f c1f802                   sar       eax, 2
0049c222 8d3c8500000000           lea       edi, [eax*4]
0049c229 57                       push      edi
0049c22a 51                       push      ecx
0049c22b 53                       push      ebx
0049c22c e85f387600               call      0xbffa90
0049c231 8bf0                     mov       esi, eax
0049c233 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c236 c1e002                   shl       eax, 2
0049c239 03f7                     add       esi, edi
0049c23b 8d3c18                   lea       edi, [eax + ebx]
0049c23e 83c40c                   add       esp, 0xc
0049c241 3bf7                     cmp       esi, edi
0049c243 741a                     je        0x49c25f
0049c245 6800340000               push      0x3400
0049c24a e869597600               call      0xc01bb8
0049c24f 83c404                   add       esp, 4
0049c252 85c0                     test      eax, eax
0049c254 8906                     mov       dword ptr [esi], eax
0049c256 742e                     je        0x49c286
0049c258 83c604                   add       esi, 4
0049c25b 3bf7                     cmp       esi, edi
0049c25d 75e6                     jne       0x49c245
0049c25f 8b75fc                   mov       esi, dword ptr [ebp - 4]
0049c262 8b4608                   mov       eax, dword ptr [esi + 8]
0049c265 85c0                     test      eax, eax
0049c267 7409                     je        0x49c272
0049c269 50                       push      eax
0049c26a e89a3e7600               call      0xc00109
0049c26f 83c404                   add       esp, 4
0049c272 8b4508                   mov       eax, dword ptr [ebp + 8]
0049c275 5f                       pop       edi
0049c276 895e08                   mov       dword ptr [esi + 8], ebx
0049c279 894604                   mov       dword ptr [esi + 4], eax
0049c27c 5b                       pop       ebx
0049c27d b001                     mov       al, 1
0049c27f 5e                       pop       esi
