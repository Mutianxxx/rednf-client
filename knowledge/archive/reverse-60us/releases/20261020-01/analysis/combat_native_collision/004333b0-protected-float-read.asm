004333b0 55                       push      ebp
004333b1 8bec                     mov       ebp, esp
004333b3 51                       push      ecx
004333b4 53                       push      ebx
004333b5 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004333bb 56                       push      esi
004333bc 57                       push      edi
004333bd 8bf9                     mov       edi, ecx
004333bf 8b07                     mov       eax, dword ptr [edi]
004333c1 8b4f04                   mov       ecx, dword ptr [edi + 4]
004333c4 33c3                     xor       eax, ebx
004333c6 2bc7                     sub       eax, edi
004333c8 3bc1                     cmp       eax, ecx
004333ca 7414                     je        0x4333e0
004333cc 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004333d2 6a3f                     push      0x3f
004333d4 57                       push      edi
004333d5 e8d63c6e00               call      0xb170b0
004333da 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004333e0 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004333e6 8b4704                   mov       eax, dword ptr [edi + 4]
004333e9 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004333ec c1e002                   shl       eax, 2
004333ef 8b3402                   mov       esi, dword ptr [edx + eax]
004333f2 03d0                     add       edx, eax
004333f4 33f2                     xor       esi, edx
004333f6 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004333f9 03c2                     add       eax, edx
004333fb 8b10                     mov       edx, dword ptr [eax]
004333fd 33d0                     xor       edx, eax
004333ff 33f3                     xor       esi, ebx
00433401 33d3                     xor       edx, ebx
00433403 3bf2                     cmp       esi, edx
00433405 7408                     je        0x43340f
00433407 6a40                     push      0x40
00433409 57                       push      edi
0043340a e8a13c6e00               call      0xb170b0
0043340f 5f                       pop       edi
00433410 8975fc                   mov       dword ptr [ebp - 4], esi
00433413 d945fc                   fld       dword ptr [ebp - 4]
00433416 5e                       pop       esi
00433417 5b                       pop       ebx
00433418 8be5                     mov       esp, ebp
0043341a 5d                       pop       ebp
0043341b c3                       ret       
0043341c cc                       int3      
0043341d cc                       int3      
0043341e cc                       int3      
0043341f cc                       int3      
00433420 81c1f8030000             add       ecx, 0x3f8
00433426 e985ffffff               jmp       0x4333b0
0043342b cc                       int3      
0043342c cc                       int3      
0043342d cc                       int3      
0043342e cc                       int3      
0043342f cc                       int3      
00433430 81c108040000             add       ecx, 0x408
00433436 e975ffffff               jmp       0x4333b0
0043343b cc                       int3      
0043343c cc                       int3      
0043343d cc                       int3      
0043343e cc                       int3      
0043343f cc                       int3      
