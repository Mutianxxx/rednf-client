005f3180 56                       push      esi
005f3181 8bf1                     mov       esi, ecx
005f3183 e888beeaff               call      0x49f010
005f3188 8a8670080000             mov       al, byte ptr [esi + 0x870]
005f318e 84c0                     test      al, al
005f3190 740c                     je        0x5f319e
005f3192 8b06                     mov       eax, dword ptr [esi]
005f3194 6a00                     push      0
005f3196 8bce                     mov       ecx, esi
005f3198 ff90d8020000             call      dword ptr [eax + 0x2d8]
005f319e 5e                       pop       esi
005f319f c3                       ret       
005f31a0 55                       push      ebp
005f31a1 8bec                     mov       ebp, esp
005f31a3 56                       push      esi
005f31a4 8b7508                   mov       esi, dword ptr [ebp + 8]
005f31a7 57                       push      edi
005f31a8 8bf9                     mov       edi, ecx
005f31aa 3bf7                     cmp       esi, edi
005f31ac 0f84a8000000             je        0x5f325a
005f31b2 8b07                     mov       eax, dword ptr [edi]
005f31b4 56                       push      esi
005f31b5 ff9048020000             call      dword ptr [eax + 0x248]
005f31bb 84c0                     test      al, al
005f31bd 0f8497000000             je        0x5f325a
005f31c3 8b16                     mov       edx, dword ptr [esi]
005f31c5 8bce                     mov       ecx, esi
005f31c7 ff929c000000             call      dword ptr [edx + 0x9c]
005f31cd 3b8788010000             cmp       eax, dword ptr [edi + 0x188]
005f31d3 0f8f81000000             jg        0x5f325a
005f31d9 8b06                     mov       eax, dword ptr [esi]
005f31db 8bce                     mov       ecx, esi
005f31dd ff5048                   call      dword ptr [eax + 0x48]
005f31e0 8b08                     mov       ecx, dword ptr [eax]
005f31e2 85c9                     test      ecx, ecx
005f31e4 7503                     jne       0x5f31e9
005f31e6 8d4808                   lea       ecx, [eax + 8]
005f31e9 8b11                     mov       edx, dword ptr [ecx]
005f31eb 6a00                     push      0
005f31ed ff5208                   call      dword ptr [edx + 8]
005f31f0 d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
005f31f6 dfe0                     fnstsw    ax
005f31f8 f6c441                   test      ah, 0x41
005f31fb 750b                     jne       0x5f3208
005f31fd 5f                       pop       edi
005f31fe b801000000               mov       eax, 1
005f3203 5e                       pop       esi
005f3204 5d                       pop       ebp
005f3205 c20400                   ret       4
005f3208 8b06                     mov       eax, dword ptr [esi]
005f320a 8bce                     mov       ecx, esi
005f320c ff5048                   call      dword ptr [eax + 0x48]
005f320f 8b08                     mov       ecx, dword ptr [eax]
005f3211 85c9                     test      ecx, ecx
005f3213 7503                     jne       0x5f3218
005f3215 8d4808                   lea       ecx, [eax + 8]
005f3218 8b11                     mov       edx, dword ptr [ecx]
005f321a 6a00                     push      0
005f321c ff5208                   call      dword ptr [edx + 8]
005f321f d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
005f3225 dfe0                     fnstsw    ax
005f3227 f6c405                   test      ah, 5
005f322a 7a08                     jp        0x5f3234
005f322c 5f                       pop       edi
005f322d 33c0                     xor       eax, eax
005f322f 5e                       pop       esi
005f3230 5d                       pop       ebp
005f3231 c20400                   ret       4
005f3234 8b06                     mov       eax, dword ptr [esi]
005f3236 8bce                     mov       ecx, esi
005f3238 ff5048                   call      dword ptr [eax + 0x48]
005f323b 8b08                     mov       ecx, dword ptr [eax]
005f323d 85c9                     test      ecx, ecx
005f323f 7503                     jne       0x5f3244
005f3241 8d4808                   lea       ecx, [eax + 8]
005f3244 8b11                     mov       edx, dword ptr [ecx]
005f3246 6a01                     push      1
005f3248 ff5208                   call      dword ptr [edx + 8]
005f324b d905a4d7e900             fld       dword ptr [0xe9d7a4]
005f3251 dae9                     fucompp   
005f3253 dfe0                     fnstsw    ax
005f3255 f6c444                   test      ah, 0x44
005f3258 7a0b                     jp        0x5f3265
005f325a 5f                       pop       edi
005f325b b804000000               mov       eax, 4
005f3260 5e                       pop       esi
005f3261 5d                       pop       ebp
005f3262 c20400                   ret       4
005f3265 8b06                     mov       eax, dword ptr [esi]
005f3267 8bce                     mov       ecx, esi
005f3269 ff90c0000000             call      dword ptr [eax + 0xc0]
005f326f 5f                       pop       edi
005f3270 5e                       pop       esi
005f3271 5d                       pop       ebp
005f3272 c20400                   ret       4
005f3275 cc                       int3      
005f3276 cc                       int3      
005f3277 cc                       int3      
005f3278 cc                       int3      
005f3279 cc                       int3      
005f327a cc                       int3      
005f327b cc                       int3      
005f327c cc                       int3      
005f327d cc                       int3      
005f327e cc                       int3      
005f327f cc                       int3      
005f3280 56                       push      esi
005f3281 57                       push      edi
005f3282 8bf9                     mov       edi, ecx
005f3284 8b8f7c080000             mov       ecx, dword ptr [edi + 0x87c]
005f328a 85c9                     test      ecx, ecx
005f328c 7406                     je        0x5f3294
005f328e 8b01                     mov       eax, dword ptr [ecx]
005f3290 6a01                     push      1
005f3292 ff10                     call      dword ptr [eax]
005f3294 8bb794080000             mov       esi, dword ptr [edi + 0x894]
005f329a 3bb798080000             cmp       esi, dword ptr [edi + 0x898]
005f32a0 c7877c08000000000000     mov       dword ptr [edi + 0x87c], 0
005f32aa 7426                     je        0x5f32d2
005f32ac 8d642400                 lea       esp, [esp]
005f32b0 8b4e04                   mov       ecx, dword ptr [esi + 4]
005f32b3 85c9                     test      ecx, ecx
005f32b5 7407                     je        0x5f32be
005f32b7 8b11                     mov       edx, dword ptr [ecx]
005f32b9 6a01                     push      1
005f32bb ff5208                   call      dword ptr [edx + 8]
005f32be c7460400000000           mov       dword ptr [esi + 4], 0
005f32c5 8b8798080000             mov       eax, dword ptr [edi + 0x898]
005f32cb 83c608                   add       esi, 8
005f32ce 3bf0                     cmp       esi, eax
005f32d0 75de                     jne       0x5f32b0
005f32d2 5f                       pop       edi
005f32d3 5e                       pop       esi
005f32d4 c3                       ret       
005f32d5 cc                       int3      
005f32d6 cc                       int3      
005f32d7 cc                       int3      
005f32d8 cc                       int3      
005f32d9 cc                       int3      
005f32da cc                       int3      
005f32db cc                       int3      
005f32dc cc                       int3      
005f32dd cc                       int3      
005f32de cc                       int3      
005f32df cc                       int3      
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
