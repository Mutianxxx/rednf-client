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
