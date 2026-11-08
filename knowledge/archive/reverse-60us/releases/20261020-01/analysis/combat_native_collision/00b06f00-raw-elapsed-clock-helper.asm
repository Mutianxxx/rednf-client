00b06f00 56                       push      esi
00b06f01 8bf1                     mov       esi, ecx
00b06f03 8d4e10                   lea       ecx, [esi + 0x10]
00b06f06 e855b18fff               call      0x402060
00b06f0b 85c0                     test      eax, eax
00b06f0d 7442                     je        0xb06f51
00b06f0f 8d4e18                   lea       ecx, [esi + 0x18]
00b06f12 e849b18fff               call      0x402060
00b06f17 85c0                     test      eax, eax
00b06f19 7436                     je        0xb06f51
00b06f1b 8d4e20                   lea       ecx, [esi + 0x20]
00b06f1e e83db18fff               call      0x402060
00b06f23 85c0                     test      eax, eax
00b06f25 7409                     je        0xb06f30
00b06f27 8d4e30                   lea       ecx, [esi + 0x30]
00b06f2a 5e                       pop       esi
00b06f2b e930b18fff               jmp       0x402060
00b06f30 57                       push      edi
00b06f31 8d4e08                   lea       ecx, [esi + 8]
00b06f34 e827b18fff               call      0x402060
00b06f39 50                       push      eax
00b06f3a e841bb0000               call      0xb12a80
00b06f3f 83c404                   add       esp, 4
00b06f42 8d4e28                   lea       ecx, [esi + 0x28]
00b06f45 8bf8                     mov       edi, eax
00b06f47 e814b18fff               call      0x402060
00b06f4c 03c7                     add       eax, edi
00b06f4e 5f                       pop       edi
00b06f4f 5e                       pop       esi
00b06f50 c3                       ret       
00b06f51 33c0                     xor       eax, eax
00b06f53 5e                       pop       esi
00b06f54 c3                       ret       
00b06f55 cc                       int3      
00b06f56 cc                       int3      
00b06f57 cc                       int3      
00b06f58 cc                       int3      
00b06f59 cc                       int3      
00b06f5a cc                       int3      
00b06f5b cc                       int3      
00b06f5c cc                       int3      
00b06f5d cc                       int3      
00b06f5e cc                       int3      
00b06f5f cc                       int3      
00b06f60 55                       push      ebp
00b06f61 8bec                     mov       ebp, esp
00b06f63 51                       push      ecx
00b06f64 56                       push      esi
00b06f65 8bf1                     mov       esi, ecx
00b06f67 8d4e10                   lea       ecx, [esi + 0x10]
00b06f6a e8f1b08fff               call      0x402060
00b06f6f 85c0                     test      eax, eax
00b06f71 745a                     je        0xb06fcd
00b06f73 57                       push      edi
00b06f74 8d7e18                   lea       edi, [esi + 0x18]
00b06f77 8bcf                     mov       ecx, edi
00b06f79 e8e2b08fff               call      0x402060
00b06f7e 85c0                     test      eax, eax
00b06f80 754a                     jne       0xb06fcc
00b06f82 8d45fc                   lea       eax, [ebp - 4]
00b06f85 50                       push      eax
00b06f86 8bcf                     mov       ecx, edi
00b06f88 c745fc01000000           mov       dword ptr [ebp - 4], 1
00b06f8f e8ccd58fff               call      0x404560
00b06f94 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
00b06f97 57                       push      edi
00b06f98 8bce                     mov       ecx, esi
00b06f9a e8c19190ff               call      0x410160
00b06f9f 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00b06fa2 8d550c                   lea       edx, [ebp + 0xc]
00b06fa5 894d0c                   mov       dword ptr [ebp + 0xc], ecx
00b06fa8 52                       push      edx
00b06fa9 8d4e38                   lea       ecx, [esi + 0x38]
00b06fac e8afd58fff               call      0x404560
00b06fb1 8d4e20                   lea       ecx, [esi + 0x20]
00b06fb4 e8a7b08fff               call      0x402060
00b06fb9 85c0                     test      eax, eax
00b06fbb 740f                     je        0xb06fcc
00b06fbd 8d450c                   lea       eax, [ebp + 0xc]
00b06fc0 50                       push      eax
00b06fc1 8d4e30                   lea       ecx, [esi + 0x30]
00b06fc4 897d0c                   mov       dword ptr [ebp + 0xc], edi
00b06fc7 e894d58fff               call      0x404560
00b06fcc 5f                       pop       edi
00b06fcd 5e                       pop       esi
00b06fce 8be5                     mov       esp, ebp
00b06fd0 5d                       pop       ebp
00b06fd1 c20800                   ret       8
00b06fd4 cc                       int3      
00b06fd5 cc                       int3      
00b06fd6 cc                       int3      
00b06fd7 cc                       int3      
00b06fd8 cc                       int3      
00b06fd9 cc                       int3      
00b06fda cc                       int3      
00b06fdb cc                       int3      
00b06fdc cc                       int3      
00b06fdd cc                       int3      
00b06fde cc                       int3      
00b06fdf cc                       int3      
00b06fe0 56                       push      esi
00b06fe1 8bf1                     mov       esi, ecx
00b06fe3 57                       push      edi
00b06fe4 8d7e20                   lea       edi, [esi + 0x20]
00b06fe7 8bcf                     mov       ecx, edi
00b06fe9 e872b08fff               call      0x402060
00b06fee 85c0                     test      eax, eax
00b06ff0 757e                     jne       0xb07070
00b06ff2 53                       push      ebx
00b06ff3 8bce                     mov       ecx, esi
00b06ff5 e806ffffff               call      0xb06f00
00b06ffa 8b4e34                   mov       ecx, dword ptr [esi + 0x34]
00b06ffd 8b15d8012101             mov       edx, dword ptr [0x12101d8]
00b07003 8b5244                   mov       edx, dword ptr [edx + 0x44]
00b07006 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
00b0700c 8d0c8a                   lea       ecx, [edx + ecx*4]
00b0700f 8bd1                     mov       edx, ecx
00b07011 33d3                     xor       edx, ebx
00b07013 33d0                     xor       edx, eax
00b07015 8911                     mov       dword ptr [ecx], edx
00b07017 8b4e34                   mov       ecx, dword ptr [esi + 0x34]
00b0701a 8b15d8012101             mov       edx, dword ptr [0x12101d8]
00b07020 8b5248                   mov       edx, dword ptr [edx + 0x48]
00b07023 8b35dc012101             mov       esi, dword ptr [0x12101dc]
00b07029 8d0c8a                   lea       ecx, [edx + ecx*4]
00b0702c 8bd1                     mov       edx, ecx
00b0702e 33d6                     xor       edx, esi
