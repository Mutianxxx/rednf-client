005f3500 55                       push      ebp
005f3501 8bec                     mov       ebp, esp
005f3503 6aff                     push      -1
005f3505 680a75c600               push      0xc6750a
005f350a 64a100000000             mov       eax, dword ptr fs:[0]
005f3510 50                       push      eax
005f3511 64892500000000           mov       dword ptr fs:[0], esp
005f3518 83ec34                   sub       esp, 0x34
005f351b 53                       push      ebx
005f351c 56                       push      esi
005f351d 57                       push      edi
005f351e 8bf1                     mov       esi, ecx
005f3520 e84ba7eaff               call      0x49dc70
005f3525 8a8680080000             mov       al, byte ptr [esi + 0x880]
005f352b 84c0                     test      al, al
005f352d 0f84b7000000             je        0x5f35ea
005f3533 8b8684080000             mov       eax, dword ptr [esi + 0x884]
005f3539 33db                     xor       ebx, ebx
005f353b 3bc3                     cmp       eax, ebx
005f353d 741b                     je        0x5f355a
005f353f 50                       push      eax
005f3540 8bce                     mov       ecx, esi
005f3542 e859fcffff               call      0x5f31a0
005f3547 83f804                   cmp       eax, 4
005f354a 7506                     jne       0x5f3552
005f354c 899e84080000             mov       dword ptr [esi + 0x884], ebx
005f3552 50                       push      eax
005f3553 8bce                     mov       ecx, esi
005f3555 e8a6fdffff               call      0x5f3300
005f355a 399e84080000             cmp       dword ptr [esi + 0x884], ebx
005f3560 0f8584000000             jne       0x5f35ea
005f3566 8b8600010000             mov       eax, dword ptr [esi + 0x100]
005f356c 8b8890000000             mov       ecx, dword ptr [eax + 0x90]
005f3572 058c000000               add       eax, 0x8c
005f3577 3bcb                     cmp       ecx, ebx
005f3579 7505                     jne       0x5f3580
005f357b 895df0                   mov       dword ptr [ebp - 0x10], ebx
005f357e eb0b                     jmp       0x5f358b
005f3580 8b4008                   mov       eax, dword ptr [eax + 8]
005f3583 2bc1                     sub       eax, ecx
005f3585 c1f802                   sar       eax, 2
005f3588 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f358b 395df0                   cmp       dword ptr [ebp - 0x10], ebx
005f358e 7e5a                     jle       0x5f35ea
005f3590 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f3596 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
005f359c 85d2                     test      edx, edx
005f359e 7416                     je        0x5f35b6
005f35a0 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
005f35a6 2bc2                     sub       eax, edx
005f35a8 c1f802                   sar       eax, 2
005f35ab 3bd8                     cmp       ebx, eax
005f35ad 7307                     jae       0x5f35b6
005f35af 8bca                     mov       ecx, edx
005f35b1 8b3c99                   mov       edi, dword ptr [ecx + ebx*4]
005f35b4 eb02                     jmp       0x5f35b8
005f35b6 33ff                     xor       edi, edi
005f35b8 8b07                     mov       eax, dword ptr [edi]
005f35ba 6a11                     push      0x11
005f35bc 8bcf                     mov       ecx, edi
005f35be ff502c                   call      dword ptr [eax + 0x2c]
005f35c1 84c0                     test      al, al
005f35c3 740d                     je        0x5f35d2
005f35c5 57                       push      edi
005f35c6 8bce                     mov       ecx, esi
005f35c8 e8d3fbffff               call      0x5f31a0
005f35cd 83f804                   cmp       eax, 4
005f35d0 750a                     jne       0x5f35dc
005f35d2 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
005f35d5 43                       inc       ebx
005f35d6 3bd8                     cmp       ebx, eax
005f35d8 7cb6                     jl        0x5f3590
005f35da eb0e                     jmp       0x5f35ea
005f35dc 50                       push      eax
005f35dd 8bce                     mov       ecx, esi
005f35df 89be84080000             mov       dword ptr [esi + 0x884], edi
005f35e5 e816fdffff               call      0x5f3300
005f35ea 8a8670080000             mov       al, byte ptr [esi + 0x870]
005f35f0 84c0                     test      al, al
005f35f2 0f8402010000             je        0x5f36fa
005f35f8 8b16                     mov       edx, dword ptr [esi]
005f35fa 6a01                     push      1
005f35fc 8bce                     mov       ecx, esi
005f35fe ff92d8020000             call      dword ptr [edx + 0x2d8]
005f3604 8b8600010000             mov       eax, dword ptr [esi + 0x100]
005f360a 8b8890000000             mov       ecx, dword ptr [eax + 0x90]
005f3610 058c000000               add       eax, 0x8c
005f3615 33db                     xor       ebx, ebx
005f3617 3bcb                     cmp       ecx, ebx
005f3619 7505                     jne       0x5f3620
005f361b 895df0                   mov       dword ptr [ebp - 0x10], ebx
005f361e eb0b                     jmp       0x5f362b
005f3620 8b4008                   mov       eax, dword ptr [eax + 8]
005f3623 2bc1                     sub       eax, ecx
005f3625 c1f802                   sar       eax, 2
005f3628 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f362b 395df0                   cmp       dword ptr [ebp - 0x10], ebx
005f362e 0f8eba000000             jle       0x5f36ee
005f3634 eb0a                     jmp       0x5f3640
005f3636 8da42400000000           lea       esp, [esp]
005f363d 8d4900                   lea       ecx, [ecx]
005f3640 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f3646 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
005f364c 85d2                     test      edx, edx
005f364e 7416                     je        0x5f3666
005f3650 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
005f3656 2bc2                     sub       eax, edx
005f3658 c1f802                   sar       eax, 2
005f365b 3bd8                     cmp       ebx, eax
005f365d 7307                     jae       0x5f3666
005f365f 8bca                     mov       ecx, edx
005f3661 8b3c99                   mov       edi, dword ptr [ecx + ebx*4]
005f3664 eb02                     jmp       0x5f3668
005f3666 33ff                     xor       edi, edi
005f3668 8a868c080000             mov       al, byte ptr [esi + 0x88c]
005f366e 84c0                     test      al, al
005f3670 7414                     je        0x5f3686
005f3672 8b07                     mov       eax, dword ptr [edi]
005f3674 8bcf                     mov       ecx, edi
005f3676 ff909c010000             call      dword ptr [eax + 0x19c]
005f367c 8a887c010000             mov       cl, byte ptr [eax + 0x17c]
005f3682 84c9                     test      cl, cl
005f3684 745c                     je        0x5f36e2
005f3686 8b17                     mov       edx, dword ptr [edi]
005f3688 56                       push      esi
005f3689 8bcf                     mov       ecx, edi
005f368b ff92a8010000             call      dword ptr [edx + 0x1a8]
005f3691 84c0                     test      al, al
005f3693 754d                     jne       0x5f36e2
005f3695 8d4dc0                   lea       ecx, [ebp - 0x40]
005f3698 e8133ce7ff               call      0x4672b0
005f369d 8b07                     mov       eax, dword ptr [edi]
005f369f 8d4dc0                   lea       ecx, [ebp - 0x40]
005f36a2 51                       push      ecx
005f36a3 56                       push      esi
005f36a4 8bcf                     mov       ecx, edi
005f36a6 c745fc00000000           mov       dword ptr [ebp - 4], 0
005f36ad ff9040020000             call      dword ptr [eax + 0x240]
005f36b3 84c0                     test      al, al
005f36b5 741c                     je        0x5f36d3
005f36b7 8b17                     mov       edx, dword ptr [edi]
005f36b9 56                       push      esi
005f36ba 8bcf                     mov       ecx, edi
005f36bc ff92a4010000             call      dword ptr [edx + 0x1a4]
005f36c2 8b06                     mov       eax, dword ptr [esi]
005f36c4 6a00                     push      0
005f36c6 8d4dc0                   lea       ecx, [ebp - 0x40]
005f36c9 51                       push      ecx
005f36ca 57                       push      edi
005f36cb 8bce                     mov       ecx, esi
005f36cd ff9060020000             call      dword ptr [eax + 0x260]
005f36d3 8d4dc0                   lea       ecx, [ebp - 0x40]
005f36d6 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f36dd e81e0ce1ff               call      0x404300
005f36e2 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
005f36e5 43                       inc       ebx
005f36e6 3bd8                     cmp       ebx, eax
005f36e8 0f8c52ffffff             jl        0x5f3640
005f36ee 8b16                     mov       edx, dword ptr [esi]
005f36f0 6a00                     push      0
005f36f2 8bce                     mov       ecx, esi
005f36f4 ff92d8020000             call      dword ptr [edx + 0x2d8]
005f36fa 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f36fd 5f                       pop       edi
005f36fe 5e                       pop       esi
005f36ff 5b                       pop       ebx
005f3700 64890d00000000           mov       dword ptr fs:[0], ecx
005f3707 8be5                     mov       esp, ebp
005f3709 5d                       pop       ebp
005f370a c3                       ret       
005f370b cc                       int3      
005f370c cc                       int3      
005f370d cc                       int3      
005f370e cc                       int3      
005f370f cc                       int3      
005f3710 55                       push      ebp
005f3711 8bec                     mov       ebp, esp
005f3713 83ec08                   sub       esp, 8
005f3716 8b4508                   mov       eax, dword ptr [ebp + 8]
005f3719 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f371c 8945f8                   mov       dword ptr [ebp - 8], eax
005f371f 8d45f8                   lea       eax, [ebp - 8]
005f3722 50                       push      eax
005f3723 81c190080000             add       ecx, 0x890
005f3729 8955fc                   mov       dword ptr [ebp - 4], edx
005f372c e84f070000               call      0x5f3e80
005f3731 8be5                     mov       esp, ebp
005f3733 5d                       pop       ebp
005f3734 c20800                   ret       8
005f3737 cc                       int3      
005f3738 cc                       int3      
005f3739 cc                       int3      
005f373a cc                       int3      
005f373b cc                       int3      
005f373c cc                       int3      
005f373d cc                       int3      
005f373e cc                       int3      
005f373f cc                       int3      
005f3740 55                       push      ebp
005f3741 8bec                     mov       ebp, esp
005f3743 83ec08                   sub       esp, 8
005f3746 8b4508                   mov       eax, dword ptr [ebp + 8]
005f3749 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f374c 8945f8                   mov       dword ptr [ebp - 8], eax
005f374f 8d45f8                   lea       eax, [ebp - 8]
005f3752 50                       push      eax
005f3753 81c1a0080000             add       ecx, 0x8a0
005f3759 8955fc                   mov       dword ptr [ebp - 4], edx
005f375c e80f3ae1ff               call      0x407170
005f3761 8be5                     mov       esp, ebp
005f3763 5d                       pop       ebp
005f3764 c20800                   ret       8
005f3767 cc                       int3      
005f3768 cc                       int3      
005f3769 cc                       int3      
005f376a cc                       int3      
005f376b cc                       int3      
005f376c cc                       int3      
