0049be80 55                       push      ebp
0049be81 8bec                     mov       ebp, esp
0049be83 83ec0c                   sub       esp, 0xc
0049be86 56                       push      esi
0049be87 8bf1                     mov       esi, ecx
0049be89 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
0049be8f 85c0                     test      eax, eax
0049be91 57                       push      edi
0049be92 742b                     je        0x49bebf
0049be94 83beb4010000ff           cmp       dword ptr [esi + 0x1b4], -1
0049be9b 7422                     je        0x49bebf
0049be9d 8d4e20                   lea       ecx, [esi + 0x20]
0049bea0 e85bb06600               call      0xb06f00
0049bea5 8b8eb8010000             mov       ecx, dword ptr [esi + 0x1b8]
0049beab 038eb4010000             add       ecx, dword ptr [esi + 0x1b4]
0049beb1 3bc1                     cmp       eax, ecx
0049beb3 7c0a                     jl        0x49bebf
0049beb5 8b16                     mov       edx, dword ptr [esi]
0049beb7 8bce                     mov       ecx, esi
0049beb9 ff9220010000             call      dword ptr [edx + 0x120]
0049bebf 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049bec5 e836550700               call      0x511400
0049beca 8b06                     mov       eax, dword ptr [esi]
0049becc 8bce                     mov       ecx, esi
0049bece ff909c000000             call      dword ptr [eax + 0x9c]
0049bed4 8b16                     mov       edx, dword ptr [esi]
0049bed6 8945fc                   mov       dword ptr [ebp - 4], eax
0049bed9 db45fc                   fild      dword ptr [ebp - 4]
0049bedc 8bce                     mov       ecx, esi
0049bede d95df4                   fstp      dword ptr [ebp - 0xc]
0049bee1 ff9298000000             call      dword ptr [edx + 0x98]
0049bee7 8945fc                   mov       dword ptr [ebp - 4], eax
0049beea db45fc                   fild      dword ptr [ebp - 4]
0049beed 8b06                     mov       eax, dword ptr [esi]
0049beef 8bce                     mov       ecx, esi
0049bef1 d95df8                   fstp      dword ptr [ebp - 8]
0049bef4 ff9094000000             call      dword ptr [eax + 0x94]
0049befa 8b4df8                   mov       ecx, dword ptr [ebp - 8]
0049befd 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
0049bf00 8945fc                   mov       dword ptr [ebp - 4], eax
0049bf03 db45fc                   fild      dword ptr [ebp - 4]
0049bf06 898e9c010000             mov       dword ptr [esi + 0x19c], ecx
0049bf0c 8996a0010000             mov       dword ptr [esi + 0x1a0], edx
0049bf12 6a02                     push      2
0049bf14 d99e98010000             fstp      dword ptr [esi + 0x198]
0049bf1a 8b06                     mov       eax, dword ptr [esi]
0049bf1c 8bce                     mov       ecx, esi
0049bf1e ff502c                   call      dword ptr [eax + 0x2c]
0049bf21 84c0                     test      al, al
0049bf23 0f849c000000             je        0x49bfc5
0049bf29 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049bf2f 8b4978                   mov       ecx, dword ptr [ecx + 0x78]
0049bf32 85c9                     test      ecx, ecx
0049bf34 7412                     je        0x49bf48
0049bf36 8b11                     mov       edx, dword ptr [ecx]
0049bf38 ff5234                   call      dword ptr [edx + 0x34]
0049bf3b 84c0                     test      al, al
0049bf3d 7509                     jne       0x49bf48
0049bf3f 8b06                     mov       eax, dword ptr [esi]
0049bf41 6a00                     push      0
0049bf43 8bce                     mov       ecx, esi
0049bf45 ff5060                   call      dword ptr [eax + 0x60]
0049bf48 80be8501000001           cmp       byte ptr [esi + 0x185], 1
0049bf4f 753b                     jne       0x49bf8c
0049bf51 8b16                     mov       edx, dword ptr [esi]
0049bf53 8bce                     mov       ecx, esi
0049bf55 ff92f4000000             call      dword ptr [edx + 0xf4]
0049bf5b 85c0                     test      eax, eax
0049bf5d 742d                     je        0x49bf8c
0049bf5f 8b06                     mov       eax, dword ptr [esi]
0049bf61 8bce                     mov       ecx, esi
0049bf63 ff90f4000000             call      dword ptr [eax + 0xf4]
0049bf69 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
0049bf6f 84c9                     test      cl, cl
0049bf71 7419                     je        0x49bf8c
0049bf73 8b8e30010000             mov       ecx, dword ptr [esi + 0x130]
0049bf79 85c9                     test      ecx, ecx
0049bf7b 743f                     je        0x49bfbc
0049bf7d 8b8634010000             mov       eax, dword ptr [esi + 0x134]
0049bf83 2bc1                     sub       eax, ecx
0049bf85 c1f802                   sar       eax, 2
0049bf88 85c0                     test      eax, eax
0049bf8a 7430                     je        0x49bfbc
0049bf8c 8b06                     mov       eax, dword ptr [esi]
0049bf8e 8bce                     mov       ecx, esi
0049bf90 ff9004010000             call      dword ptr [eax + 0x104]
0049bf96 85c0                     test      eax, eax
0049bf98 752b                     jne       0x49bfc5
0049bf9a 80be8601000001           cmp       byte ptr [esi + 0x186], 1
0049bfa1 7522                     jne       0x49bfc5
0049bfa3 8b8e30010000             mov       ecx, dword ptr [esi + 0x130]
0049bfa9 85c9                     test      ecx, ecx
0049bfab 740f                     je        0x49bfbc
0049bfad 8b8634010000             mov       eax, dword ptr [esi + 0x134]
0049bfb3 2bc1                     sub       eax, ecx
0049bfb5 c1f802                   sar       eax, 2
0049bfb8 85c0                     test      eax, eax
0049bfba 7509                     jne       0x49bfc5
0049bfbc 8b16                     mov       edx, dword ptr [esi]
0049bfbe 8bce                     mov       ecx, esi
0049bfc0 6a00                     push      0
0049bfc2 ff5260                   call      dword ptr [edx + 0x60]
0049bfc5 8b06                     mov       eax, dword ptr [esi]
0049bfc7 8bce                     mov       ecx, esi
0049bfc9 ff90f4000000             call      dword ptr [eax + 0xf4]
0049bfcf 85c0                     test      eax, eax
0049bfd1 7412                     je        0x49bfe5
0049bfd3 8b16                     mov       edx, dword ptr [esi]
0049bfd5 56                       push      esi
0049bfd6 8bce                     mov       ecx, esi
0049bfd8 ff92f4000000             call      dword ptr [edx + 0xf4]
0049bfde 8bc8                     mov       ecx, eax
0049bfe0 e8eb9e5800               call      0xa25ed0
0049bfe5 8b860c010000             mov       eax, dword ptr [esi + 0x10c]
0049bfeb 8b38                     mov       edi, dword ptr [eax]
0049bfed 3bf8                     cmp       edi, eax
0049bfef 7413                     je        0x49c004
0049bff1 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049bff4 56                       push      esi
0049bff5 e8d69e5800               call      0xa25ed0
0049bffa 8b3f                     mov       edi, dword ptr [edi]
0049bffc 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049c002 75ed                     jne       0x49bff1
0049c004 8b06                     mov       eax, dword ptr [esi]
0049c006 8bce                     mov       ecx, esi
0049c008 ff9004010000             call      dword ptr [eax + 0x104]
0049c00e 85c0                     test      eax, eax
0049c010 7411                     je        0x49c023
0049c012 8b16                     mov       edx, dword ptr [esi]
0049c014 8bce                     mov       ecx, esi
0049c016 ff9204010000             call      dword ptr [edx + 0x104]
0049c01c 8bc8                     mov       ecx, eax
0049c01e e81d525900               call      0xa31240
0049c023 8b06                     mov       eax, dword ptr [esi]
0049c025 8bce                     mov       ecx, esi
0049c027 ff9008010000             call      dword ptr [eax + 0x108]
0049c02d 85c0                     test      eax, eax
0049c02f 7411                     je        0x49c042
0049c031 8b16                     mov       edx, dword ptr [esi]
0049c033 8bce                     mov       ecx, esi
0049c035 ff9208010000             call      dword ptr [edx + 0x108]
0049c03b 8bc8                     mov       ecx, eax
0049c03d e8fe515900               call      0xa31240
0049c042 8b06                     mov       eax, dword ptr [esi]
0049c044 8bce                     mov       ecx, esi
0049c046 ff9088010000             call      dword ptr [eax + 0x188]
0049c04c 8b8e8c010000             mov       ecx, dword ptr [esi + 0x18c]
0049c052 85c9                     test      ecx, ecx
0049c054 7405                     je        0x49c05b
0049c056 e815be0800               call      0x527e70
0049c05b 8b8e90010000             mov       ecx, dword ptr [esi + 0x190]
0049c061 85c9                     test      ecx, ecx
0049c063 7405                     je        0x49c06a
0049c065 e8e6b60800               call      0x527750
0049c06a 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049c070 8a81f8000000             mov       al, byte ptr [ecx + 0xf8]
0049c076 84c0                     test      al, al
0049c078 7409                     je        0x49c083
0049c07a 6a00                     push      0
0049c07c 6a00                     push      0
0049c07e e8ed5a0700               call      0x511b70
0049c083 8bce                     mov       ecx, esi
0049c085 e8f6fcffff               call      0x49bd80
0049c08a 5f                       pop       edi
0049c08b 5e                       pop       esi
0049c08c 8be5                     mov       esp, ebp
0049c08e 5d                       pop       ebp
0049c08f c3                       ret       
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
