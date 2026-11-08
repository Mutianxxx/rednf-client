004f3200 55                       push      ebp
004f3201 8bec                     mov       ebp, esp
004f3203 51                       push      ecx
004f3204 56                       push      esi
004f3205 57                       push      edi
004f3206 8bf1                     mov       esi, ecx
004f3208 e803bafbff               call      0x4aec10
004f320d 8a8614250000             mov       al, byte ptr [esi + 0x2514]
004f3213 84c0                     test      al, al
004f3215 753b                     jne       0x4f3252
004f3217 83be5c1b000008           cmp       dword ptr [esi + 0x1b5c], 8
004f321e 7208                     jb        0x4f3228
004f3220 8b86481b0000             mov       eax, dword ptr [esi + 0x1b48]
004f3226 eb06                     jmp       0x4f322e
004f3228 8d86481b0000             lea       eax, [esi + 0x1b48]
004f322e 8b3e                     mov       edi, dword ptr [esi]
004f3230 50                       push      eax
004f3231 6a03                     push      3
004f3233 8bce                     mov       ecx, esi
004f3235 ff9744030000             call      dword ptr [edi + 0x344]
004f323b 8bc8                     mov       ecx, eax
004f323d e81eeef0ff               call      0x402060
004f3242 50                       push      eax
004f3243 8bce                     mov       ecx, esi
004f3245 ff97a4050000             call      dword ptr [edi + 0x5a4]
004f324b c6861425000001           mov       byte ptr [esi + 0x2514], 1
004f3252 8b06                     mov       eax, dword ptr [esi]
004f3254 33ff                     xor       edi, edi
004f3256 57                       push      edi
004f3257 8bce                     mov       ecx, esi
004f3259 ff9028030000             call      dword ptr [eax + 0x328]
004f325f 8b16                     mov       edx, dword ptr [esi]
004f3261 8bce                     mov       ecx, esi
004f3263 89be801b0000             mov       dword ptr [esi + 0x1b80], edi
004f3269 89be841b0000             mov       dword ptr [esi + 0x1b84], edi
004f326f ff92c4010000             call      dword ptr [edx + 0x1c4]
004f3275 85c0                     test      eax, eax
004f3277 7c1b                     jl        0x4f3294
004f3279 8b06                     mov       eax, dword ptr [esi]
004f327b 8bce                     mov       ecx, esi
004f327d ff90c4010000             call      dword ptr [eax + 0x1c4]
004f3283 83f80b                   cmp       eax, 0xb
004f3286 7f0c                     jg        0x4f3294
004f3288 c786881b000018fcffff     mov       dword ptr [esi + 0x1b88], 0xfffffc18
004f3292 eb06                     jmp       0x4f329a
004f3294 89be881b0000             mov       dword ptr [esi + 0x1b88], edi
004f329a 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004f32a0 89be8c1b0000             mov       dword ptr [esi + 0x1b8c], edi
004f32a6 89be901b0000             mov       dword ptr [esi + 0x1b90], edi
004f32ac 89be941b0000             mov       dword ptr [esi + 0x1b94], edi
004f32b2 89beb41d0000             mov       dword ptr [esi + 0x1db4], edi
004f32b8 39b914010000             cmp       dword ptr [ecx + 0x114], edi
004f32be 0f844f010000             je        0x4f3413
004f32c4 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f32ca 81c140100000             add       ecx, 0x1040
004f32d0 e88bedf0ff               call      0x402060
004f32d5 83f80a                   cmp       eax, 0xa
004f32d8 741a                     je        0x4f32f4
004f32da 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f32e0 81c140100000             add       ecx, 0x1040
004f32e6 e875edf0ff               call      0x402060
004f32eb 83f803                   cmp       eax, 3
004f32ee 0f851f010000             jne       0x4f3413
004f32f4 8b9600010000             mov       edx, dword ptr [esi + 0x100]
004f32fa 8b8214010000             mov       eax, dword ptr [edx + 0x114]
004f3300 8bb8b8000000             mov       edi, dword ptr [eax + 0xb8]
004f3306 53                       push      ebx
004f3307 8b98bc000000             mov       ebx, dword ptr [eax + 0xbc]
004f330d b9684c0001               mov       ecx, 0x1004c68
004f3312 e849edf0ff               call      0x402060
004f3317 3bc7                     cmp       eax, edi
004f3319 0f85f3000000             jne       0x4f3412
004f331f b9704c0001               mov       ecx, 0x1004c70
004f3324 e837edf0ff               call      0x402060
004f3329 3bc3                     cmp       eax, ebx
004f332b 0f85e1000000             jne       0x4f3412
004f3331 c645ff00                 mov       byte ptr [ebp - 1], 0
004f3335 33db                     xor       ebx, ebx
004f3337 eb07                     jmp       0x4f3340
004f3339 8da42400000000           lea       esp, [esp]
004f3340 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004f3346 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f334c 85d2                     test      edx, edx
004f334e 7504                     jne       0x4f3354
004f3350 33c0                     xor       eax, eax
004f3352 eb0b                     jmp       0x4f335f
004f3354 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f335a 2bc2                     sub       eax, edx
004f335c c1f802                   sar       eax, 2
004f335f 3bd8                     cmp       ebx, eax
004f3361 7d57                     jge       0x4f33ba
004f3363 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f3369 85d2                     test      edx, edx
004f336b 7419                     je        0x4f3386
004f336d 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f3373 2bc2                     sub       eax, edx
004f3375 c1f802                   sar       eax, 2
004f3378 3bd8                     cmp       ebx, eax
004f337a 730a                     jae       0x4f3386
004f337c 8bc2                     mov       eax, edx
004f337e 8b3c98                   mov       edi, dword ptr [eax + ebx*4]
004f3381 8d0498                   lea       eax, [eax + ebx*4]
004f3384 eb02                     jmp       0x4f3388
004f3386 33ff                     xor       edi, edi
004f3388 8b17                     mov       edx, dword ptr [edi]
004f338a 6a11                     push      0x11
004f338c 8bcf                     mov       ecx, edi
004f338e ff522c                   call      dword ptr [edx + 0x2c]
004f3391 84c0                     test      al, al
004f3393 741e                     je        0x4f33b3
004f3395 8b87e4190000             mov       eax, dword ptr [edi + 0x19e4]
004f339b 83f803                   cmp       eax, 3
004f339e 7405                     je        0x4f33a5
004f33a0 83f808                   cmp       eax, 8
004f33a3 750e                     jne       0x4f33b3
004f33a5 8b07                     mov       eax, dword ptr [edi]
004f33a7 8bcf                     mov       ecx, edi
004f33a9 ff90dc030000             call      dword ptr [eax + 0x3dc]
004f33af 84c0                     test      al, al
004f33b1 7403                     je        0x4f33b6
004f33b3 43                       inc       ebx
004f33b4 eb8a                     jmp       0x4f3340
004f33b6 c645ff01                 mov       byte ptr [ebp - 1], 1
004f33ba 8b16                     mov       edx, dword ptr [esi]
004f33bc 8bce                     mov       ecx, esi
004f33be 32db                     xor       bl, bl
004f33c0 ff92c4010000             call      dword ptr [edx + 0x1c4]
004f33c6 85c0                     test      eax, eax
004f33c8 7426                     je        0x4f33f0
004f33ca 8b06                     mov       eax, dword ptr [esi]
004f33cc 8bce                     mov       ecx, esi
004f33ce ff90a8020000             call      dword ptr [eax + 0x2a8]
004f33d4 85c0                     test      eax, eax
004f33d6 741a                     je        0x4f33f2
004f33d8 8b16                     mov       edx, dword ptr [esi]
004f33da 8bce                     mov       ecx, esi
004f33dc ff92a8020000             call      dword ptr [edx + 0x2a8]
004f33e2 8b10                     mov       edx, dword ptr [eax]
004f33e4 8bc8                     mov       ecx, eax
004f33e6 ff92c4010000             call      dword ptr [edx + 0x1c4]
004f33ec 85c0                     test      eax, eax
004f33ee 7502                     jne       0x4f33f2
004f33f0 b301                     mov       bl, 1
004f33f2 8a45ff                   mov       al, byte ptr [ebp - 1]
004f33f5 84c0                     test      al, al
004f33f7 7519                     jne       0x4f3412
004f33f9 84db                     test      bl, bl
004f33fb 7515                     jne       0x4f3412
004f33fd 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
004f3403 8b06                     mov       eax, dword ptr [esi]
004f3405 6a01                     push      1
004f3407 51                       push      ecx
004f3408 6a00                     push      0
004f340a 8bce                     mov       ecx, esi
004f340c ff90ec030000             call      dword ptr [eax + 0x3ec]
004f3412 5b                       pop       ebx
004f3413 8b16                     mov       edx, dword ptr [esi]
004f3415 6a03                     push      3
004f3417 8bce                     mov       ecx, esi
004f3419 ff9244030000             call      dword ptr [edx + 0x344]
004f341f 5f                       pop       edi
004f3420 5e                       pop       esi
004f3421 8be5                     mov       esp, ebp
004f3423 5d                       pop       ebp
004f3424 c3                       ret       
004f3425 cc                       int3      
004f3426 cc                       int3      
004f3427 cc                       int3      
004f3428 cc                       int3      
004f3429 cc                       int3      
004f342a cc                       int3      
004f342b cc                       int3      
004f342c cc                       int3      
004f342d cc                       int3      
004f342e cc                       int3      
004f342f cc                       int3      
004f3430 55                       push      ebp
004f3431 8bec                     mov       ebp, esp
004f3433 56                       push      esi
004f3434 8bf1                     mov       esi, ecx
004f3436 8b8ea0220000             mov       ecx, dword ptr [esi + 0x22a0]
004f343c 85c9                     test      ecx, ecx
004f343e 0f84d9000000             je        0x4f351d
004f3444 8b86a4220000             mov       eax, dword ptr [esi + 0x22a4]
004f344a 2bc1                     sub       eax, ecx
004f344c c1f804                   sar       eax, 4
004f344f 85c0                     test      eax, eax
004f3451 0f84c6000000             je        0x4f351d
004f3457 8b5508                   mov       edx, dword ptr [ebp + 8]
004f345a 53                       push      ebx
004f345b 33db                     xor       ebx, ebx
004f345d 57                       push      edi
004f345e 8bff                     mov       edi, edi
004f3460 85c9                     test      ecx, ecx
004f3462 0f84b3000000             je        0x4f351b
004f3468 8b86a4220000             mov       eax, dword ptr [esi + 0x22a4]
004f346e 2bc1                     sub       eax, ecx
004f3470 c1f804                   sar       eax, 4
004f3473 3bd8                     cmp       ebx, eax
004f3475 0f83a0000000             jae       0x4f351b
004f347b 8b86c0220000             mov       eax, dword ptr [esi + 0x22c0]
004f3481 8b3c98                   mov       edi, dword ptr [eax + ebx*4]
004f3484 3bfa                     cmp       edi, edx
004f3486 8d0498                   lea       eax, [eax + ebx*4]
004f3489 7403                     je        0x4f348e
004f348b 43                       inc       ebx
004f348c ebd2                     jmp       0x4f3460
004f348e 33d2                     xor       edx, edx
004f3490 895508                   mov       dword ptr [ebp + 8], edx
004f3493 c1e304                   shl       ebx, 4
004f3496 eb08                     jmp       0x4f34a0
004f3498 8da42400000000           lea       esp, [esp]
004f349f 90                       nop       
004f34a0 8b8ea0220000             mov       ecx, dword ptr [esi + 0x22a0]
004f34a6 8b7c1904                 mov       edi, dword ptr [ecx + ebx + 4]
004f34aa 85ff                     test      edi, edi
004f34ac 8d0419                   lea       eax, [ecx + ebx]
004f34af 746a                     je        0x4f351b
004f34b1 8b4808                   mov       ecx, dword ptr [eax + 8]
004f34b4 2bcf                     sub       ecx, edi
004f34b6 c1f902                   sar       ecx, 2
004f34b9 3bd1                     cmp       edx, ecx
004f34bb 735e                     jae       0x4f351b
004f34bd 8b4004                   mov       eax, dword ptr [eax + 4]
004f34c0 8d3c9500000000           lea       edi, [edx*4]
004f34c7 8b16                     mov       edx, dword ptr [esi]
004f34c9 03c7                     add       eax, edi
004f34cb 8b00                     mov       eax, dword ptr [eax]
004f34cd 50                       push      eax
004f34ce 8bce                     mov       ecx, esi
004f34d0 ff92fc000000             call      dword ptr [edx + 0xfc]
004f34d6 8b86a0220000             mov       eax, dword ptr [esi + 0x22a0]
004f34dc 8b8eb0220000             mov       ecx, dword ptr [esi + 0x22b0]
004f34e2 8b16                     mov       edx, dword ptr [esi]
004f34e4 6a01                     push      1
004f34e6 6a00                     push      0
004f34e8 6a00                     push      0
004f34ea 6a00                     push      0
004f34ec 6a00                     push      0
004f34ee 03c3                     add       eax, ebx
004f34f0 8b4004                   mov       eax, dword ptr [eax + 4]
004f34f3 03cb                     add       ecx, ebx
004f34f5 8b4904                   mov       ecx, dword ptr [ecx + 4]
004f34f8 6a00                     push      0
004f34fa 6a00                     push      0
004f34fc 03c7                     add       eax, edi
004f34fe 8b00                     mov       eax, dword ptr [eax]
004f3500 03cf                     add       ecx, edi
004f3502 8b09                     mov       ecx, dword ptr [ecx]
004f3504 6a00                     push      0
004f3506 50                       push      eax
004f3507 51                       push      ecx
004f3508 8bce                     mov       ecx, esi
004f350a ff92f8000000             call      dword ptr [edx + 0xf8]
004f3510 8b4508                   mov       eax, dword ptr [ebp + 8]
004f3513 40                       inc       eax
004f3514 894508                   mov       dword ptr [ebp + 8], eax
004f3517 8bd0                     mov       edx, eax
004f3519 eb85                     jmp       0x4f34a0
004f351b 5f                       pop       edi
004f351c 5b                       pop       ebx
004f351d 5e                       pop       esi
004f351e 5d                       pop       ebp
004f351f c20400                   ret       4
004f3522 cc                       int3      
004f3523 cc                       int3      
004f3524 cc                       int3      
004f3525 cc                       int3      
004f3526 cc                       int3      
004f3527 cc                       int3      
004f3528 cc                       int3      
004f3529 cc                       int3      
004f352a cc                       int3      
004f352b cc                       int3      
004f352c cc                       int3      
004f352d cc                       int3      
004f352e cc                       int3      
004f352f cc                       int3      
004f3530 55                       push      ebp
004f3531 8bec                     mov       ebp, esp
004f3533 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004f3536 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004f3539 8b89dc120000             mov       ecx, dword ptr [ecx + 0x12dc]
004f353f 50                       push      eax
004f3540 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004f3543 52                       push      edx
004f3544 8b5508                   mov       edx, dword ptr [ebp + 8]
004f3547 50                       push      eax
004f3548 52                       push      edx
004f3549 e8b21a0100               call      0x505000
004f354e 33c0                     xor       eax, eax
004f3550 5d                       pop       ebp
004f3551 c21000                   ret       0x10
004f3554 cc                       int3      
004f3555 cc                       int3      
004f3556 cc                       int3      
004f3557 cc                       int3      
004f3558 cc                       int3      
004f3559 cc                       int3      
004f355a cc                       int3      
004f355b cc                       int3      
004f355c cc                       int3      
004f355d cc                       int3      
004f355e cc                       int3      
004f355f cc                       int3      
004f3560 55                       push      ebp
004f3561 8bec                     mov       ebp, esp
004f3563 83ec20                   sub       esp, 0x20
004f3566 53                       push      ebx
004f3567 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
004f356a 8b03                     mov       eax, dword ptr [ebx]
004f356c 56                       push      esi
004f356d 8bf1                     mov       esi, ecx
004f356f 57                       push      edi
004f3570 8bcb                     mov       ecx, ebx
004f3572 ff90c4010000             call      dword ptr [eax + 0x1c4]
004f3578 8b16                     mov       edx, dword ptr [esi]
004f357a 8bce                     mov       ecx, esi
004f357c 8bf8                     mov       edi, eax
004f357e ff92c4010000             call      dword ptr [edx + 0x1c4]
004f3584 3bf8                     cmp       edi, eax
004f3586 741f                     je        0x4f35a7
004f3588 8b03                     mov       eax, dword ptr [ebx]
004f358a 6a11                     push      0x11
004f358c 8bcb                     mov       ecx, ebx
004f358e ff502c                   call      dword ptr [eax + 0x2c]
004f3591 84c0                     test      al, al
004f3593 7412                     je        0x4f35a7
004f3595 8b13                     mov       edx, dword ptr [ebx]
004f3597 8bcb                     mov       ecx, ebx
004f3599 ff92f4040000             call      dword ptr [edx + 0x4f4]
004f359f 3c01                     cmp       al, 1
004f35a1 0f84fe010000             je        0x4f37a5
004f35a7 8b8e68120000             mov       ecx, dword ptr [esi + 0x1268]
004f35ad 85c9                     test      ecx, ecx
004f35af 0f84f0010000             je        0x4f37a5
004f35b5 8b866c120000             mov       eax, dword ptr [esi + 0x126c]
004f35bb 8b7d08                   mov       edi, dword ptr [ebp + 8]
004f35be 2bc1                     sub       eax, ecx
004f35c0 c1f802                   sar       eax, 2
004f35c3 3bc7                     cmp       eax, edi
004f35c5 0f86da010000             jbe       0x4f37a5
004f35cb 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f35d1 85c0                     test      eax, eax
004f35d3 0f84cc010000             je        0x4f37a5
004f35d9 8b8e641d0000             mov       ecx, dword ptr [esi + 0x1d64]
004f35df 2bc8                     sub       ecx, eax
004f35e1 b8abaaaa2a               mov       eax, 0x2aaaaaab
004f35e6 f7e9                     imul      ecx
004f35e8 c1fa04                   sar       edx, 4
004f35eb 8bc2                     mov       eax, edx
004f35ed c1e81f                   shr       eax, 0x1f
004f35f0 03c2                     add       eax, edx
004f35f2 3bc7                     cmp       eax, edi
004f35f4 0f86ab010000             jbe       0x4f37a5
004f35fa 8b06                     mov       eax, dword ptr [esi]
004f35fc 53                       push      ebx
004f35fd 8bce                     mov       ecx, esi
004f35ff ff9044040000             call      dword ptr [eax + 0x444]
004f3605 84c0                     test      al, al
004f3607 0f8498010000             je        0x4f37a5
004f360d 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f3613 8d3c7f                   lea       edi, [edi + edi*2]
004f3616 c1e705                   shl       edi, 5
004f3619 03c7                     add       eax, edi
004f361b 8d4820                   lea       ecx, [eax + 0x20]
004f361e e83deaf0ff               call      0x402060
004f3623 8945f8                   mov       dword ptr [ebp - 8], eax
004f3626 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f362c 03c7                     add       eax, edi
004f362e 8d4828                   lea       ecx, [eax + 0x28]
004f3631 e82aeaf0ff               call      0x402060
004f3636 894508                   mov       dword ptr [ebp + 8], eax
004f3639 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f363f 03c7                     add       eax, edi
004f3641 8d4830                   lea       ecx, [eax + 0x30]
004f3644 e817eaf0ff               call      0x402060
004f3649 8945f4                   mov       dword ptr [ebp - 0xc], eax
004f364c 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f3652 03c7                     add       eax, edi
004f3654 8d4838                   lea       ecx, [eax + 0x38]
004f3657 e804eaf0ff               call      0x402060
004f365c 89450c                   mov       dword ptr [ebp + 0xc], eax
004f365f 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f3665 03c7                     add       eax, edi
004f3667 8d4840                   lea       ecx, [eax + 0x40]
004f366a e8f1e9f0ff               call      0x402060
004f366f 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f3672 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f3678 03c7                     add       eax, edi
004f367a 8d4848                   lea       ecx, [eax + 0x48]
004f367d e8dee9f0ff               call      0x402060
004f3682 8945f0                   mov       dword ptr [ebp - 0x10], eax
004f3685 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f368b 03c7                     add       eax, edi
004f368d 8d4850                   lea       ecx, [eax + 0x50]
004f3690 e8cbe9f0ff               call      0x402060
004f3695 8945e0                   mov       dword ptr [ebp - 0x20], eax
004f3698 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f369e 03c7                     add       eax, edi
004f36a0 8d4858                   lea       ecx, [eax + 0x58]
004f36a3 e8b8e9f0ff               call      0x402060
004f36a8 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f36ab 85c9                     test      ecx, ecx
004f36ad 8945e8                   mov       dword ptr [ebp - 0x18], eax
004f36b0 750b                     jne       0x4f36bd
004f36b2 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f36b5 85c9                     test      ecx, ecx
004f36b7 0f84e8000000             je        0x4f37a5
004f36bd 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004f36c0 85c9                     test      ecx, ecx
004f36c2 7508                     jne       0x4f36cc
004f36c4 85c0                     test      eax, eax
004f36c6 0f84d9000000             je        0x4f37a5
004f36cc 8b864c1d0000             mov       eax, dword ptr [esi + 0x1d4c]
004f36d2 8b16                     mov       edx, dword ptr [esi]
004f36d4 33c9                     xor       ecx, ecx
004f36d6 83f8ff                   cmp       eax, -1
004f36d9 0f94c1                   sete      cl
004f36dc 49                       dec       ecx
004f36dd 23c8                     and       ecx, eax
004f36df 8bf9                     mov       edi, ecx
004f36e1 8bce                     mov       ecx, esi
004f36e3 897dfc                   mov       dword ptr [ebp - 4], edi
004f36e6 ff92c0000000             call      dword ptr [edx + 0xc0]
004f36ec 85c0                     test      eax, eax
004f36ee 8b03                     mov       eax, dword ptr [ebx]
004f36f0 8bcb                     mov       ecx, ebx
004f36f2 0f85b8000000             jne       0x4f37b0
004f36f8 ff90fc010000             call      dword ptr [eax + 0x1fc]
004f36fe 99                       cdq       
004f36ff 83e203                   and       edx, 3
004f3702 03c2                     add       eax, edx
004f3704 8b13                     mov       edx, dword ptr [ebx]
004f3706 c1f802                   sar       eax, 2
004f3709 8bcb                     mov       ecx, ebx
004f370b 2bf8                     sub       edi, eax
004f370d ff9294000000             call      dword ptr [edx + 0x94]
004f3713 03f8                     add       edi, eax
004f3715 8b06                     mov       eax, dword ptr [esi]
004f3717 8bce                     mov       ecx, esi
004f3719 ff9094000000             call      dword ptr [eax + 0x94]
004f371f 03450c                   add       eax, dword ptr [ebp + 0xc]
004f3722 3bf8                     cmp       edi, eax
004f3724 7f7f                     jg        0x4f37a5
004f3726 8b13                     mov       edx, dword ptr [ebx]
004f3728 8bcb                     mov       ecx, ebx
004f372a ff92fc010000             call      dword ptr [edx + 0x1fc]
004f3730 99                       cdq       
004f3731 83e203                   and       edx, 3
004f3734 03c2                     add       eax, edx
004f3736 8bf8                     mov       edi, eax
004f3738 8b03                     mov       eax, dword ptr [ebx]
004f373a 8bcb                     mov       ecx, ebx
004f373c c1ff02                   sar       edi, 2
004f373f ff9094000000             call      dword ptr [eax + 0x94]
004f3745 037dfc                   add       edi, dword ptr [ebp - 4]
004f3748 8b16                     mov       edx, dword ptr [esi]
004f374a 03c7                     add       eax, edi
004f374c 8bce                     mov       ecx, esi
004f374e 8bf8                     mov       edi, eax
004f3750 ff9294000000             call      dword ptr [edx + 0x94]
004f3756 8b5508                   mov       edx, dword ptr [ebp + 8]
004f3759 2bc2                     sub       eax, edx
004f375b 3bf8                     cmp       edi, eax
004f375d 7c46                     jl        0x4f37a5
004f375f 8b06                     mov       eax, dword ptr [esi]
004f3761 8bce                     mov       ecx, esi
004f3763 ff9094000000             call      dword ptr [eax + 0x94]
004f3769 8b55f8                   mov       edx, dword ptr [ebp - 8]
004f376c 8bf8                     mov       edi, eax
004f376e 2bfa                     sub       edi, edx
004f3770 8b13                     mov       edx, dword ptr [ebx]
004f3772 8bcb                     mov       ecx, ebx
004f3774 ff9294000000             call      dword ptr [edx + 0x94]
004f377a 3bc7                     cmp       eax, edi
004f377c 0f8ee5000000             jle       0x4f3867
004f3782 8b06                     mov       eax, dword ptr [esi]
004f3784 8bce                     mov       ecx, esi
004f3786 ff9094000000             call      dword ptr [eax + 0x94]
004f378c 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004f378f 8bf8                     mov       edi, eax
004f3791 03fa                     add       edi, edx
004f3793 8b13                     mov       edx, dword ptr [ebx]
004f3795 8bcb                     mov       ecx, ebx
004f3797 ff9294000000             call      dword ptr [edx + 0x94]
004f379d 3bc7                     cmp       eax, edi
004f379f 0f8dc2000000             jge       0x4f3867
004f37a5 5f                       pop       edi
004f37a6 5e                       pop       esi
004f37a7 32c0                     xor       al, al
004f37a9 5b                       pop       ebx
004f37aa 8be5                     mov       esp, ebp
004f37ac 5d                       pop       ebp
004f37ad c20800                   ret       8
004f37b0 ff90fc010000             call      dword ptr [eax + 0x1fc]
004f37b6 99                       cdq       
004f37b7 83e203                   and       edx, 3
004f37ba 03c2                     add       eax, edx
004f37bc 8b13                     mov       edx, dword ptr [ebx]
004f37be c1f802                   sar       eax, 2
004f37c1 2bc7                     sub       eax, edi
004f37c3 8bcb                     mov       ecx, ebx
004f37c5 8945ec                   mov       dword ptr [ebp - 0x14], eax
004f37c8 ff9294000000             call      dword ptr [edx + 0x94]
004f37ce 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
004f37d1 03c8                     add       ecx, eax
004f37d3 8b06                     mov       eax, dword ptr [esi]
004f37d5 894dec                   mov       dword ptr [ebp - 0x14], ecx
004f37d8 8bce                     mov       ecx, esi
004f37da ff9094000000             call      dword ptr [eax + 0x94]
004f37e0 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004f37e3 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
004f37e6 2bc7                     sub       eax, edi
004f37e8 3bc8                     cmp       ecx, eax
004f37ea 7cb9                     jl        0x4f37a5
004f37ec 8b13                     mov       edx, dword ptr [ebx]
004f37ee 8bcb                     mov       ecx, ebx
004f37f0 ff92fc010000             call      dword ptr [edx + 0x1fc]
004f37f6 99                       cdq       
004f37f7 83e203                   and       edx, 3
004f37fa 03c2                     add       eax, edx
004f37fc 8bf8                     mov       edi, eax
004f37fe 8b03                     mov       eax, dword ptr [ebx]
004f3800 8bcb                     mov       ecx, ebx
004f3802 c1ff02                   sar       edi, 2
004f3805 ff9094000000             call      dword ptr [eax + 0x94]
004f380b 8b16                     mov       edx, dword ptr [esi]
004f380d 2bc7                     sub       eax, edi
004f380f 2b45fc                   sub       eax, dword ptr [ebp - 4]
004f3812 8bce                     mov       ecx, esi
004f3814 8bf8                     mov       edi, eax
004f3816 ff9294000000             call      dword ptr [edx + 0x94]
004f381c 8b5508                   mov       edx, dword ptr [ebp + 8]
004f381f 03c2                     add       eax, edx
004f3821 3bf8                     cmp       edi, eax
004f3823 7f80                     jg        0x4f37a5
004f3825 8b06                     mov       eax, dword ptr [esi]
004f3827 8bce                     mov       ecx, esi
004f3829 ff9094000000             call      dword ptr [eax + 0x94]
004f382f 8b55f8                   mov       edx, dword ptr [ebp - 8]
004f3832 8bf8                     mov       edi, eax
004f3834 2bfa                     sub       edi, edx
004f3836 8b13                     mov       edx, dword ptr [ebx]
004f3838 8bcb                     mov       ecx, ebx
004f383a ff9294000000             call      dword ptr [edx + 0x94]
004f3840 3bc7                     cmp       eax, edi
004f3842 7e23                     jle       0x4f3867
004f3844 8b06                     mov       eax, dword ptr [esi]
004f3846 8bce                     mov       ecx, esi
004f3848 ff9094000000             call      dword ptr [eax + 0x94]
004f384e 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004f3851 8bf8                     mov       edi, eax
004f3853 03fa                     add       edi, edx
004f3855 8b13                     mov       edx, dword ptr [ebx]
004f3857 8bcb                     mov       ecx, ebx
004f3859 ff9294000000             call      dword ptr [edx + 0x94]
004f385f 3bc7                     cmp       eax, edi
004f3861 0f8c3effffff             jl        0x4f37a5
004f3867 8b03                     mov       eax, dword ptr [ebx]
004f3869 8bcb                     mov       ecx, ebx
004f386b ff9000020000             call      dword ptr [eax + 0x200]
004f3871 99                       cdq       
004f3872 83e203                   and       edx, 3
004f3875 03c2                     add       eax, edx
004f3877 8b13                     mov       edx, dword ptr [ebx]
004f3879 8bf8                     mov       edi, eax
004f387b 8bcb                     mov       ecx, ebx
004f387d c1ff02                   sar       edi, 2
004f3880 ff9298000000             call      dword ptr [edx + 0x98]
004f3886 03f8                     add       edi, eax
004f3888 8b06                     mov       eax, dword ptr [esi]
004f388a 8bce                     mov       ecx, esi
004f388c ff9098000000             call      dword ptr [eax + 0x98]
004f3892 2b45f0                   sub       eax, dword ptr [ebp - 0x10]
004f3895 3bf8                     cmp       edi, eax
004f3897 0f8c08ffffff             jl        0x4f37a5
004f389d 8b13                     mov       edx, dword ptr [ebx]
004f389f 8bcb                     mov       ecx, ebx
004f38a1 ff9200020000             call      dword ptr [edx + 0x200]
004f38a7 99                       cdq       
004f38a8 83e203                   and       edx, 3
004f38ab 03c2                     add       eax, edx
004f38ad 8bf8                     mov       edi, eax
004f38af 8b03                     mov       eax, dword ptr [ebx]
004f38b1 8bcb                     mov       ecx, ebx
004f38b3 c1ff02                   sar       edi, 2
004f38b6 ff9098000000             call      dword ptr [eax + 0x98]
004f38bc 8b16                     mov       edx, dword ptr [esi]
004f38be 2bc7                     sub       eax, edi
004f38c0 8bce                     mov       ecx, esi
004f38c2 8bf8                     mov       edi, eax
004f38c4 ff9298000000             call      dword ptr [edx + 0x98]
004f38ca 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f38cd 03c2                     add       eax, edx
004f38cf 3bf8                     cmp       edi, eax
004f38d1 0f8fcefeffff             jg        0x4f37a5
004f38d7 8b06                     mov       eax, dword ptr [esi]
004f38d9 8bce                     mov       ecx, esi
004f38db ff9098000000             call      dword ptr [eax + 0x98]
004f38e1 8b55e4                   mov       edx, dword ptr [ebp - 0x1c]
004f38e4 8bf8                     mov       edi, eax
004f38e6 2bfa                     sub       edi, edx
004f38e8 8b13                     mov       edx, dword ptr [ebx]
004f38ea 8bcb                     mov       ecx, ebx
004f38ec ff9298000000             call      dword ptr [edx + 0x98]
004f38f2 3bc7                     cmp       eax, edi
004f38f4 7e23                     jle       0x4f3919
004f38f6 8b06                     mov       eax, dword ptr [esi]
004f38f8 8bce                     mov       ecx, esi
004f38fa ff9098000000             call      dword ptr [eax + 0x98]
004f3900 8b55e0                   mov       edx, dword ptr [ebp - 0x20]
004f3903 8bf0                     mov       esi, eax
004f3905 03f2                     add       esi, edx
004f3907 8b13                     mov       edx, dword ptr [ebx]
004f3909 8bcb                     mov       ecx, ebx
004f390b ff9298000000             call      dword ptr [edx + 0x98]
004f3911 3bc6                     cmp       eax, esi
004f3913 0f8c8cfeffff             jl        0x4f37a5
004f3919 5f                       pop       edi
004f391a 5e                       pop       esi
004f391b b001                     mov       al, 1
004f391d 5b                       pop       ebx
004f391e 8be5                     mov       esp, ebp
004f3920 5d                       pop       ebp
004f3921 c20800                   ret       8
004f3924 cc                       int3      
004f3925 cc                       int3      
004f3926 cc                       int3      
004f3927 cc                       int3      
004f3928 cc                       int3      
004f3929 cc                       int3      
004f392a cc                       int3      
004f392b cc                       int3      
004f392c cc                       int3      
004f392d cc                       int3      
004f392e cc                       int3      
004f392f cc                       int3      
004f3930 55                       push      ebp
004f3931 8bec                     mov       ebp, esp
004f3933 83ec14                   sub       esp, 0x14
004f3936 56                       push      esi
004f3937 8bf1                     mov       esi, ecx
004f3939 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004f393f 8b01                     mov       eax, dword ptr [ecx]
004f3941 8d55fc                   lea       edx, [ebp - 4]
004f3944 52                       push      edx
004f3945 ff5054                   call      dword ptr [eax + 0x54]
004f3948 8b86f0040000             mov       eax, dword ptr [esi + 0x4f0]
004f394e 85c0                     test      eax, eax
004f3950 0f8497000000             je        0x4f39ed
004f3956 8bc8                     mov       ecx, eax
004f3958 8b01                     mov       eax, dword ptr [ecx]
004f395a ff5040                   call      dword ptr [eax + 0x40]
004f395d 0fb74dfc                 movzx     ecx, word ptr [ebp - 4]
004f3961 3bc1                     cmp       eax, ecx
004f3963 0f8584000000             jne       0x4f39ed
004f3969 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004f396f 8b11                     mov       edx, dword ptr [ecx]
004f3971 6a0d                     push      0xd
004f3973 8d45ec                   lea       eax, [ebp - 0x14]
004f3976 50                       push      eax
004f3977 ff5264                   call      dword ptr [edx + 0x64]
004f397a 8a45f8                   mov       al, byte ptr [ebp - 8]
004f397d 84c0                     test      al, al
004f397f 743b                     je        0x4f39bc
004f3981 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
004f3984 83f9ff                   cmp       ecx, -1
004f3987 7419                     je        0x4f39a2
004f3989 8b96381a0000             mov       edx, dword ptr [esi + 0x1a38]
004f398f 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
004f3992 8d0482                   lea       eax, [edx + eax*4]
004f3995 51                       push      ecx
004f3996 8b08                     mov       ecx, dword ptr [eax]
004f3998 e883bf2500               call      0x74f920
004f399d 5e                       pop       esi
004f399e 8be5                     mov       esp, ebp
004f39a0 5d                       pop       ebp
004f39a1 c3                       ret       
004f39a2 8b8e481a0000             mov       ecx, dword ptr [esi + 0x1a48]
004f39a8 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004f39ab 8d0491                   lea       eax, [ecx + edx*4]
004f39ae 8b08                     mov       ecx, dword ptr [eax]
004f39b0 6aff                     push      -1
004f39b2 e869bf2500               call      0x74f920
004f39b7 5e                       pop       esi
004f39b8 8be5                     mov       esp, ebp
004f39ba 5d                       pop       ebp
004f39bb c3                       ret       
004f39bc 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004f39bf 83f80d                   cmp       eax, 0xd
004f39c2 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
004f39c5 50                       push      eax
004f39c6 7d15                     jge       0x4f39dd
004f39c8 8b8e381a0000             mov       ecx, dword ptr [esi + 0x1a38]
004f39ce 8d0c91                   lea       ecx, [ecx + edx*4]
004f39d1 8b09                     mov       ecx, dword ptr [ecx]
004f39d3 e8f8be2500               call      0x74f8d0
004f39d8 5e                       pop       esi
004f39d9 8be5                     mov       esp, ebp
004f39db 5d                       pop       ebp
004f39dc c3                       ret       
004f39dd 8b8e481a0000             mov       ecx, dword ptr [esi + 0x1a48]
004f39e3 8d0c91                   lea       ecx, [ecx + edx*4]
004f39e6 8b09                     mov       ecx, dword ptr [ecx]
004f39e8 e8e3be2500               call      0x74f8d0
004f39ed 5e                       pop       esi
004f39ee 8be5                     mov       esp, ebp
004f39f0 5d                       pop       ebp
004f39f1 c3                       ret       
004f39f2 cc                       int3      
004f39f3 cc                       int3      
004f39f4 cc                       int3      
004f39f5 cc                       int3      
004f39f6 cc                       int3      
004f39f7 cc                       int3      
004f39f8 cc                       int3      
004f39f9 cc                       int3      
004f39fa cc                       int3      
004f39fb cc                       int3      
004f39fc cc                       int3      
004f39fd cc                       int3      
004f39fe cc                       int3      
004f39ff cc                       int3      
