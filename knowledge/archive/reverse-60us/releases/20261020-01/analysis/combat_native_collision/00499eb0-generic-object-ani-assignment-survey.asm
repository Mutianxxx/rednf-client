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
00499f10 55                       push      ebp
00499f11 8bec                     mov       ebp, esp
00499f13 56                       push      esi
00499f14 8bf1                     mov       esi, ecx
00499f16 57                       push      edi
00499f17 8bbe48010000             mov       edi, dword ptr [esi + 0x148]
00499f1d 85ff                     test      edi, edi
00499f1f 7408                     je        0x499f29
00499f21 8b07                     mov       eax, dword ptr [edi]
00499f23 56                       push      esi
00499f24 8bcf                     mov       ecx, edi
00499f26 ff5014                   call      dword ptr [eax + 0x14]
00499f29 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00499f2c 85c9                     test      ecx, ecx
00499f2e 740d                     je        0x499f3d
00499f30 e85b385900               call      0xa2d790
00499f35 898648010000             mov       dword ptr [esi + 0x148], eax
00499f3b eb0a                     jmp       0x499f47
00499f3d c7864801000000000000     mov       dword ptr [esi + 0x148], 0
00499f47 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f4d 85c9                     test      ecx, ecx
00499f4f 7427                     je        0x499f78
00499f51 c7860401000000000000     mov       dword ptr [esi + 0x104], 0
00499f5b e8807a5900               call      0xa319e0
00499f60 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f66 56                       push      esi
00499f67 e8b4305900               call      0xa2d020
00499f6c 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f72 8b11                     mov       edx, dword ptr [ecx]
00499f74 56                       push      esi
00499f75 ff5210                   call      dword ptr [edx + 0x10]
00499f78 85ff                     test      edi, edi
00499f7a 7419                     je        0x499f95
00499f7c 8a87ae000000             mov       al, byte ptr [edi + 0xae]
00499f82 84c0                     test      al, al
00499f84 740f                     je        0x499f95
00499f86 8bcf                     mov       ecx, edi
00499f88 e803385900               call      0xa2d790
00499f8d 8b07                     mov       eax, dword ptr [edi]
00499f8f 6a01                     push      1
00499f91 8bcf                     mov       ecx, edi
00499f93 ff10                     call      dword ptr [eax]
00499f95 5f                       pop       edi
00499f96 5e                       pop       esi
00499f97 5d                       pop       ebp
00499f98 c20400                   ret       4
00499f9b cc                       int3      
00499f9c cc                       int3      
00499f9d cc                       int3      
00499f9e cc                       int3      
00499f9f cc                       int3      
00499fa0 55                       push      ebp
00499fa1 8bec                     mov       ebp, esp
00499fa3 8bc1                     mov       eax, ecx
00499fa5 837d080d                 cmp       dword ptr [ebp + 8], 0xd
00499fa9 7517                     jne       0x499fc2
00499fab 8b                       .byte     0x8b
00499fac 88540100                 mov       byte ptr [ecx + eax], dl
