005f32e0 8b8120010000             mov       eax, dword ptr [ecx + 0x120]
005f32e6 8b00                     mov       eax, dword ptr [eax]
005f32e8 8b11                     mov       edx, dword ptr [ecx]
005f32ea 50                       push      eax
005f32eb ff92f0000000             call      dword ptr [edx + 0xf0]
005f32f1 c3                       ret       
005f32f2 cc                       int3      
005f32f3 cc                       int3      
005f32f4 cc                       int3      
005f32f5 cc                       int3      
005f32f6 cc                       int3      
005f32f7 cc                       int3      
005f32f8 cc                       int3      
005f32f9 cc                       int3      
005f32fa cc                       int3      
005f32fb cc                       int3      
005f32fc cc                       int3      
005f32fd cc                       int3      
005f32fe cc                       int3      
005f32ff cc                       int3      
005f3300 55                       push      ebp
005f3301 8bec                     mov       ebp, esp
005f3303 56                       push      esi
005f3304 8bf1                     mov       esi, ecx
005f3306 8b8688080000             mov       eax, dword ptr [esi + 0x888]
005f330c 57                       push      edi
005f330d 8b7d08                   mov       edi, dword ptr [ebp + 8]
005f3310 3bf8                     cmp       edi, eax
005f3312 7452                     je        0x5f3366
005f3314 8a8680080000             mov       al, byte ptr [esi + 0x880]
005f331a 84c0                     test      al, al
005f331c 7448                     je        0x5f3366
005f331e 83ff04                   cmp       edi, 4
005f3321 7513                     jne       0x5f3336
005f3323 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
005f3329 8b06                     mov       eax, dword ptr [esi]
005f332b 51                       push      ecx
005f332c 8bce                     mov       ecx, esi
005f332e ff90f0000000             call      dword ptr [eax + 0xf0]
005f3334 eb1f                     jmp       0x5f3355
005f3336 85ff                     test      edi, edi
005f3338 8b16                     mov       edx, dword ptr [esi]
005f333a 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f3340 8bce                     mov       ecx, esi
005f3342 7505                     jne       0x5f3349
005f3344 83c004                   add       eax, 4
005f3347 eb03                     jmp       0x5f334c
005f3349 83c008                   add       eax, 8
005f334c 8b00                     mov       eax, dword ptr [eax]
005f334e 50                       push      eax
005f334f ff92f0000000             call      dword ptr [edx + 0xf0]
005f3355 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
005f335b e800404300               call      0xa27360
005f3360 89be88080000             mov       dword ptr [esi + 0x888], edi
005f3366 5f                       pop       edi
005f3367 5e                       pop       esi
005f3368 5d                       pop       ebp
005f3369 c20400                   ret       4
005f336c cc                       int3      
005f336d cc                       int3      
005f336e cc                       int3      
005f336f cc                       int3      
005f3370 53                       push      ebx
005f3371 56                       push      esi
005f3372 57                       push      edi
005f3373 8bf1                     mov       esi, ecx
005f3375 bf01000000               mov       edi, 1
005f337a 8d9b00000000             lea       ebx, [ebx]
005f3380 8b8e4c050000             mov       ecx, dword ptr [esi + 0x54c]
005f3386 85c9                     test      ecx, ecx
005f3388 742a                     je        0x5f33b4
005f338a 8b8650050000             mov       eax, dword ptr [esi + 0x550]
005f3390 2bc1                     sub       eax, ecx
005f3392 c1f802                   sar       eax, 2
005f3395 3bc7                     cmp       eax, edi
005f3397 761b                     jbe       0x5f33b4
005f3399 8b1e                     mov       ebx, dword ptr [esi]
005f339b 6a00                     push      0
005f339d 8bc1                     mov       eax, ecx
005f339f 6a00                     push      0
005f33a1 8d0cb8                   lea       ecx, [eax + edi*4]
005f33a4 6aff                     push      -1
005f33a6 e845fd4500               call      0xa530f0
005f33ab 50                       push      eax
005f33ac 8bce                     mov       ecx, esi
005f33ae ff930c010000             call      dword ptr [ebx + 0x10c]
005f33b4 47                       inc       edi
005f33b5 83ff03                   cmp       edi, 3
005f33b8 7cc6                     jl        0x5f3380
005f33ba 5f                       pop       edi
005f33bb 5e                       pop       esi
005f33bc 5b                       pop       ebx
005f33bd c3                       ret       
005f33be cc                       int3      
005f33bf cc                       int3      
