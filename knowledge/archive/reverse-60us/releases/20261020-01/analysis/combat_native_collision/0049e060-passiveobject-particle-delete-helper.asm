0049e060 56                       push      esi
0049e061 8bf1                     mov       esi, ecx
0049e063 8b8e94070000             mov       ecx, dword ptr [esi + 0x794]
0049e069 57                       push      edi
0049e06a 33ff                     xor       edi, edi
0049e06c 3bcf                     cmp       ecx, edi
0049e06e 7406                     je        0x49e076
0049e070 8b01                     mov       eax, dword ptr [ecx]
0049e072 6a01                     push      1
0049e074 ff10                     call      dword ptr [eax]
0049e076 8b8e14080000             mov       ecx, dword ptr [esi + 0x814]
0049e07c 51                       push      ecx
0049e07d 89be94070000             mov       dword ptr [esi + 0x794], edi
0049e083 e8fe317600               call      0xc01286
0049e088 89be14080000             mov       dword ptr [esi + 0x814], edi
0049e08e 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049e094 83c404                   add       esp, 4
0049e097 3bcf                     cmp       ecx, edi
0049e099 7455                     je        0x49e0f0
0049e09b 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049e0a1 2bc1                     sub       eax, ecx
0049e0a3 c1f805                   sar       eax, 5
0049e0a6 3bc7                     cmp       eax, edi
0049e0a8 7446                     je        0x49e0f0
0049e0aa 53                       push      ebx
0049e0ab 33db                     xor       ebx, ebx
0049e0ad 8d4900                   lea       ecx, [ecx]
0049e0b0 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049e0b6 85c9                     test      ecx, ecx
0049e0b8 7435                     je        0x49e0ef
0049e0ba 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049e0c0 2bc1                     sub       eax, ecx
0049e0c2 c1f805                   sar       eax, 5
0049e0c5 3bd8                     cmp       ebx, eax
0049e0c7 7326                     jae       0x49e0ef
0049e0c9 8bc1                     mov       eax, ecx
0049e0cb 03c7                     add       eax, edi
0049e0cd 8b00                     mov       eax, dword ptr [eax]
0049e0cf 85c0                     test      eax, eax
0049e0d1 7408                     je        0x49e0db
0049e0d3 8b10                     mov       edx, dword ptr [eax]
0049e0d5 6a01                     push      1
0049e0d7 8bc8                     mov       ecx, eax
0049e0d9 ff12                     call      dword ptr [edx]
0049e0db 8b8620080000             mov       eax, dword ptr [esi + 0x820]
0049e0e1 03c7                     add       eax, edi
0049e0e3 43                       inc       ebx
0049e0e4 c70000000000             mov       dword ptr [eax], 0
0049e0ea 83c720                   add       edi, 0x20
0049e0ed ebc1                     jmp       0x49e0b0
0049e0ef 5b                       pop       ebx
0049e0f0 5f                       pop       edi
0049e0f1 5e                       pop       esi
0049e0f2 c3                       ret       
0049e0f3 cc                       int3      
0049e0f4 cc                       int3      
0049e0f5 cc                       int3      
0049e0f6 cc                       int3      
0049e0f7 cc                       int3      
0049e0f8 cc                       int3      
0049e0f9 cc                       int3      
0049e0fa cc                       int3      
0049e0fb cc                       int3      
0049e0fc cc                       int3      
0049e0fd cc                       int3      
0049e0fe cc                       int3      
0049e0ff cc                       int3      
