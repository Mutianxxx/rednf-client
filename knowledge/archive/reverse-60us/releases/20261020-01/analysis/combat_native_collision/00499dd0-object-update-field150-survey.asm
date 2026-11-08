00499dd0 c681f401000000           mov       byte ptr [ecx + 0x1f4], 0
00499dd7 c3                       ret       
00499dd8 cc                       int3      
00499dd9 cc                       int3      
00499dda cc                       int3      
00499ddb cc                       int3      
00499ddc cc                       int3      
00499ddd cc                       int3      
00499dde cc                       int3      
00499ddf cc                       int3      
00499de0 c681f401000001           mov       byte ptr [ecx + 0x1f4], 1
00499de7 c3                       ret       
00499de8 cc                       int3      
00499de9 cc                       int3      
00499dea cc                       int3      
00499deb cc                       int3      
00499dec cc                       int3      
00499ded cc                       int3      
00499dee cc                       int3      
00499def cc                       int3      
00499df0 55                       push      ebp
00499df1 8bec                     mov       ebp, esp
00499df3 56                       push      esi
00499df4 8bf1                     mov       esi, ecx
00499df6 8b06                     mov       eax, dword ptr [esi]
00499df8 ff9094000000             call      dword ptr [eax + 0x94]
00499dfe 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00499e01 8901                     mov       dword ptr [ecx], eax
00499e03 8b16                     mov       edx, dword ptr [esi]
00499e05 8bce                     mov       ecx, esi
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
00499e8e 8b                       .byte     0x8b
00499e8f 4d                       dec       ebp
