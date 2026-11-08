00499e00 0889018b168b             or        byte ptr [ecx - 0x74e974ff], cl
00499e06 ce                       into      
00499e07 ff9298000000             call      dword ptr [edx + 0x98]
00499e0d 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00499e10 8901                     mov       dword ptr [ecx], eax
00499e12 8b16                     mov       edx, dword ptr [esi]
00499e14 8bce                     mov       ecx, esi
00499e16 ff929c000000             call      dword ptr [edx + 0x9c]
00499e1c 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
00499e1f 8901                     mov       dword ptr [ecx], eax
00499e21 5e                       pop       esi
00499e22 5d                       pop       ebp
00499e23 c20c00                   ret       0xc
00499e26 cc                       int3      
00499e27 cc                       int3      
00499e28 cc                       int3      
00499e29 cc                       int3      
00499e2a cc                       int3      
00499e2b cc                       int3      
00499e2c cc                       int3      
00499e2d cc                       int3      
00499e2e cc                       int3      
00499e2f cc                       int3      
00499e30 55                       push      ebp
00499e31 8bec                     mov       ebp, esp
00499e33 8b450c                   mov       eax, dword ptr [ebp + 0xc]
00499e36 50                       push      eax
00499e37 e894ba6700               call      0xb158d0
00499e3c da4d10                   fimul     dword ptr [ebp + 0x10]
00499e3f 83c404                   add       esp, 4
00499e42 e8fd767600               call      0xc01544
00499e47 8bc8                     mov       ecx, eax
00499e49 8b4514                   mov       eax, dword ptr [ebp + 0x14]
00499e4c 85c0                     test      eax, eax
00499e4e 7507                     jne       0x499e57
00499e50 8b4508                   mov       eax, dword ptr [ebp + 8]
00499e53 2bc1                     sub       eax, ecx
00499e55 5d                       pop       ebp
00499e56 c3                       ret       
00499e57 8b5508                   mov       edx, dword ptr [ebp + 8]
00499e5a 8d0411                   lea       eax, [ecx + edx]
00499e5d 5d                       pop       ebp
00499e5e c3                       ret       
00499e5f cc                       int3      
00499e60 55                       push      ebp
00499e61 8bec                     mov       ebp, esp
00499e63 8b450c                   mov       eax, dword ptr [ebp + 0xc]
00499e66 50                       push      eax
00499e67 e844ba6700               call      0xb158b0
00499e6c da4d10                   fimul     dword ptr [ebp + 0x10]
00499e6f 83c404                   add       esp, 4
00499e72 e8cd767600               call      0xc01544
00499e77 8a4d14                   mov       cl, byte ptr [ebp + 0x14]
00499e7a 84c9                     test      cl, cl
00499e7c 7521                     jne       0x499e9f
00499e7e 8b0ddcf2fa00             mov       ecx, dword ptr [0xfaf2dc]
00499e84 0fafc8                   imul      ecx, eax
00499e87 b81f85eb51               mov       eax, 0x51eb851f
00499e8c f7e9                     imul      ecx
00499e8e 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00499e91 c1fa05                   sar       edx, 5
00499e94 8bc2                     mov       eax, edx
00499e96 c1e81f                   shr       eax, 0x1f
00499e99 03c2                     add       eax, edx
00499e9b 03c1                     add       eax, ecx
00499e9d 5d                       pop       ebp
00499e9e c3                       ret       
00499e9f 8b5508                   mov       edx, dword ptr [ebp + 8]
00499ea2 03c2                     add       eax, edx
00499ea4 5d                       pop       ebp
00499ea5 c3                       ret       
00499ea6 cc                       int3      
00499ea7 cc                       int3      
00499ea8 cc                       int3      
00499ea9 cc                       int3      
00499eaa cc                       int3      
00499eab cc                       int3      
00499eac cc                       int3      
00499ead cc                       int3      
00499eae cc                       int3      
00499eaf cc                       int3      
00499eb0 56                       push      esi
00499eb1 8bf1                     mov       esi, ecx
00499eb3 8b06                     mov       eax, dword ptr [esi]
00499eb5 6a02                     push      2
00499eb7 ff502c                   call      dword ptr [eax + 0x2c]
00499eba 84c0                     test      al, al
00499ebc 7427                     je        0x499ee5
00499ebe 80be8501000001           cmp       byte ptr [esi + 0x185], 1
00499ec5 7417                     je        0x499ede
00499ec7 8b16                     mov       edx, dword ptr [esi]
00499ec9 8bce                     mov       ecx, esi
00499ecb ff5248                   call      dword ptr [edx + 0x48]
00499ece 8b4878                   mov       ecx, dword ptr [eax + 0x78]
00499ed1 85c9                     test      ecx, ecx
00499ed3 7509                     jne       0x499ede
00499ed5 80be8601000001           cmp       byte ptr [esi + 0x186], 1
00499edc 7507                     jne       0x499ee5
00499ede b801000000               mov       eax, 1
00499ee3 5e                       pop       esi
00499ee4 c3                       ret       
00499ee5 33c0                     xor       eax, eax
00499ee7 5e                       pop       esi
00499ee8 c3                       ret       
00499ee9 cc                       int3      
00499eea cc                       int3      
00499eeb cc                       int3      
00499eec cc                       int3      
00499eed cc                       int3      
00499eee cc                       int3      
00499eef cc                       int3      
00499ef0 8bc1                     mov       eax, ecx
00499ef2 8b8848010000             mov       ecx, dword ptr [eax + 0x148]
00499ef8 85c9                     test      ecx, ecx
00499efa 7405                     je        0x499f01
00499efc e9af305900               jmp       0xa2cfb0
00499f01 8b8004010000             mov       eax, dword ptr [eax + 0x104]
00499f07 c3                       ret       
00499f08 cc                       int3      
00499f09 cc                       int3      
00499f0a cc                       int3      
00499f0b cc                       int3      
00499f0c cc                       int3      
00499f0d cc                       int3      
00499f0e cc                       int3      
00499f0f cc                       int3      
