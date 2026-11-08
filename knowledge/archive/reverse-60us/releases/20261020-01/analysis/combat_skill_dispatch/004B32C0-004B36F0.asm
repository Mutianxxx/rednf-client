004b32c0  00e8                     add        al, ch
004b32c2  2aae3f0083c4             sub        ch, byte ptr [esi - 0x3b7cffc1]
004b32c8  0425                     add        al, 0x25
004b32ca  0100                     add        dword ptr [eax], eax
004b32cc  008079054883             add        byte ptr [eax - 0x7cb7fa87], al
004b32d2  c8fe4089                 enter      0x40fe, -0x77
004b32d6  45                       inc        ebp
004b32d7  e08b                     loopne     0x4b3264
004b32d9  7de8                     jge        0x4b32c3
004b32db  8d8f88010000             lea        ecx, [edi + 0x188]
004b32e1  e8ca00f8ff               call       0x4333b0
004b32e6  d955e4                   fst        dword ptr [ebp - 0x1c]
004b32e9  dc25f0b8ca00             fsub       qword ptr [0xcab8f0]
004b32ef  d9e1                     fabs       
004b32f1  d945e4                   fld        dword ptr [ebp - 0x1c]
004b32f4  d9e1                     fabs       
004b32f6  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
004b32fc  ded9                     fcompp     
004b32fe  dfe0                     fnstsw     ax
004b3300  f6c401                   test       ah, 1
004b3303  7507                     jne        0x4b330c
004b3305  c745e40000803f           mov        dword ptr [ebp - 0x1c], 0x3f800000
004b330c  395f18                   cmp        dword ptr [edi + 0x18], ebx
004b330f  750c                     jne        0x4b331d
004b3311  d945e4                   fld        dword ptr [ebp - 0x1c]
004b3314  d80ddcb9cc00             fmul       dword ptr [0xccb9dc]
004b331a  d95de4                   fstp       dword ptr [ebp - 0x1c]
004b331d  8b86a0040000             mov        eax, dword ptr [esi + 0x4a0]
004b3323  83f804                   cmp        eax, 4
004b3326  0f8414030000             je         0x4b3640
004b332c  83f805                   cmp        eax, 5
004b332f  0f840b030000             je         0x4b3640
004b3335  33db                     xor        ebx, ebx
004b3337  895dbc                   mov        dword ptr [ebp - 0x44], ebx
004b333a  895dc0                   mov        dword ptr [ebp - 0x40], ebx
004b333d  895dc4                   mov        dword ptr [ebp - 0x3c], ebx
004b3340  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b3343  8b17                     mov        edx, dword ptr [edi]
004b3345  56                       push       esi
004b3346  8bcf                     mov        ecx, edi
004b3348  c745fc06000000           mov        dword ptr [ebp - 4], 6
004b334f  ff921c030000             call       dword ptr [edx + 0x31c]
004b3355  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b3358  8d45c8                   lea        eax, [ebp - 0x38]
004b335b  50                       push       eax
004b335c  8d4db8                   lea        ecx, [ebp - 0x48]
004b335f  e8bc3df5ff               call       0x407120
004b3364  b904340001               mov        ecx, 0x1003404
004b3369  e84200f8ff               call       0x4333b0
004b336e  d84de4                   fmul       dword ptr [ebp - 0x1c]
004b3371  e8cee17400               call       0xc01544
004b3376  8d4dc8                   lea        ecx, [ebp - 0x38]
004b3379  51                       push       ecx
004b337a  8d4db8                   lea        ecx, [ebp - 0x48]
004b337d  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b3380  e89b3df5ff               call       0x407120
004b3385  8d55e0                   lea        edx, [ebp - 0x20]
004b3388  52                       push       edx
004b3389  8d4db8                   lea        ecx, [ebp - 0x48]
004b338c  e88f3df5ff               call       0x407120
004b3391  8b07                     mov        eax, dword ptr [edi]
004b3393  8bcf                     mov        ecx, edi
004b3395  ff909c010000             call       dword ptr [eax + 0x19c]
004b339b  8b8878010000             mov        ecx, dword ptr [eax + 0x178]
004b33a1  8d55c8                   lea        edx, [ebp - 0x38]
004b33a4  894dc8                   mov        dword ptr [ebp - 0x38], ecx
004b33a7  52                       push       edx
004b33a8  8d4db8                   lea        ecx, [ebp - 0x48]
004b33ab  e8703df5ff               call       0x407120
004b33b0  8b7de8                   mov        edi, dword ptr [ebp - 0x18]
004b33b3  81c718010000             add        edi, 0x118
004b33b9  8bcf                     mov        ecx, edi
004b33bb  e8a0ecf4ff               call       0x402060
004b33c0  85c0                     test       eax, eax
004b33c2  7416                     je         0x4b33da
004b33c4  8bcf                     mov        ecx, edi
004b33c6  e895ecf4ff               call       0x402060
004b33cb  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b33ce  8d45c8                   lea        eax, [ebp - 0x38]
004b33d1  50                       push       eax
004b33d2  8d4db8                   lea        ecx, [ebp - 0x48]
004b33d5  e8463df5ff               call       0x407120
004b33da  8b16                     mov        edx, dword ptr [esi]
004b33dc  53                       push       ebx
004b33dd  53                       push       ebx
004b33de  6a03                     push       3
004b33e0  8d45b8                   lea        eax, [ebp - 0x48]
004b33e3  50                       push       eax
004b33e4  6a03                     push       3
004b33e6  8bce                     mov        ecx, esi
004b33e8  ff928c020000             call       dword ptr [edx + 0x28c]
004b33ee  8b45bc                   mov        eax, dword ptr [ebp - 0x44]
004b33f1  3bc3                     cmp        eax, ebx
004b33f3  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b33fa  0f8440020000             je         0x4b3640
004b3400  50                       push       eax
004b3401  e8d7cb7400               call       0xbfffdd
004b3406  83c404                   add        esp, 4
004b3409  e932020000               jmp        0x4b3640
004b340e  83ff04                   cmp        edi, 4
004b3411  0f85c5010000             jne        0x4b35dc
004b3417  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004b341a  81c130010000             add        ecx, 0x130
004b3420  c745d401000000           mov        dword ptr [ebp - 0x2c], 1
004b3427  e834ecf4ff               call       0x402060
004b342c  85c0                     test       eax, eax
004b342e  740e                     je         0x4b343e
004b3430  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
004b3433  85c0                     test       eax, eax
004b3435  7507                     jne        0x4b343e
004b3437  c745d402000000           mov        dword ptr [ebp - 0x2c], 2
004b343e  33c0                     xor        eax, eax
004b3440  8945bc                   mov        dword ptr [ebp - 0x44], eax
004b3443  8945c0                   mov        dword ptr [ebp - 0x40], eax
004b3446  8945c4                   mov        dword ptr [ebp - 0x3c], eax
004b3449  8b13                     mov        edx, dword ptr [ebx]
004b344b  56                       push       esi
004b344c  8bcb                     mov        ecx, ebx
004b344e  c745fc07000000           mov        dword ptr [ebp - 4], 7
004b3455  ff921c030000             call       dword ptr [edx + 0x31c]
004b345b  8b5dc0                   mov        ebx, dword ptr [ebp - 0x40]
004b345e  8bf8                     mov        edi, eax
004b3460  8b45bc                   mov        eax, dword ptr [ebp - 0x44]
004b3463  85c0                     test       eax, eax
004b3465  897dc8                   mov        dword ptr [ebp - 0x38], edi
004b3468  741f                     je         0x4b3489
004b346a  8b55c4                   mov        edx, dword ptr [ebp - 0x3c]
004b346d  8bcb                     mov        ecx, ebx
004b346f  2bc8                     sub        ecx, eax
004b3471  2bd0                     sub        edx, eax
004b3473  c1f902                   sar        ecx, 2
004b3476  c1fa02                   sar        edx, 2
004b3479  3bca                     cmp        ecx, edx
004b347b  730c                     jae        0x4b3489
004b347d  8bd3                     mov        edx, ebx
004b347f  83c204                   add        edx, 4
004b3482  893b                     mov        dword ptr [ebx], edi
004b3484  8955c0                   mov        dword ptr [ebp - 0x40], edx
004b3487  eb12                     jmp        0x4b349b
004b3489  8d45c8                   lea        eax, [ebp - 0x38]
004b348c  50                       push       eax
004b348d  6a01                     push       1
004b348f  53                       push       ebx
004b3490  8d4db8                   lea        ecx, [ebp - 0x48]
004b3493  e8c82af5ff               call       0x405f60
004b3498  8b55c0                   mov        edx, dword ptr [ebp - 0x40]
004b349b  8b5dbc                   mov        ebx, dword ptr [ebp - 0x44]
004b349e  85db                     test       ebx, ebx
004b34a0  7420                     je         0x4b34c2
004b34a2  8b4dc4                   mov        ecx, dword ptr [ebp - 0x3c]
004b34a5  8bc2                     mov        eax, edx
004b34a7  2bc3                     sub        eax, ebx
004b34a9  2bcb                     sub        ecx, ebx
004b34ab  c1f802                   sar        eax, 2
004b34ae  c1f902                   sar        ecx, 2
004b34b1  3bc1                     cmp        eax, ecx
004b34b3  730d                     jae        0x4b34c2
004b34b5  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
004b34b8  890a                     mov        dword ptr [edx], ecx
004b34ba  83c204                   add        edx, 4
004b34bd  8955c0                   mov        dword ptr [ebp - 0x40], edx
004b34c0  eb12                     jmp        0x4b34d4
004b34c2  8d45dc                   lea        eax, [ebp - 0x24]
004b34c5  50                       push       eax
004b34c6  6a01                     push       1
004b34c8  52                       push       edx
004b34c9  8d4db8                   lea        ecx, [ebp - 0x48]
004b34cc  e88f2af5ff               call       0x405f60
004b34d1  8b55c0                   mov        edx, dword ptr [ebp - 0x40]
004b34d4  8b5dbc                   mov        ebx, dword ptr [ebp - 0x44]
004b34d7  85db                     test       ebx, ebx
004b34d9  8b7dd4                   mov        edi, dword ptr [ebp - 0x2c]
004b34dc  897dc8                   mov        dword ptr [ebp - 0x38], edi
004b34df  741d                     je         0x4b34fe
004b34e1  8b4dc4                   mov        ecx, dword ptr [ebp - 0x3c]
004b34e4  8bc2                     mov        eax, edx
004b34e6  2bc3                     sub        eax, ebx
004b34e8  2bcb                     sub        ecx, ebx
004b34ea  c1f802                   sar        eax, 2
004b34ed  c1f902                   sar        ecx, 2
004b34f0  3bc1                     cmp        eax, ecx
004b34f2  730a                     jae        0x4b34fe
004b34f4  893a                     mov        dword ptr [edx], edi
004b34f6  83c204                   add        edx, 4
004b34f9  8955c0                   mov        dword ptr [ebp - 0x40], edx
004b34fc  eb0f                     jmp        0x4b350d
004b34fe  8d4dc8                   lea        ecx, [ebp - 0x38]
004b3501  51                       push       ecx
004b3502  6a01                     push       1
004b3504  52                       push       edx
004b3505  8d4db8                   lea        ecx, [ebp - 0x48]
004b3508  e8532af5ff               call       0x405f60
004b350d  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004b3510  81c1f0000000             add        ecx, 0xf0
004b3516  e845ebf4ff               call       0x402060
004b351b  8b5dbc                   mov        ebx, dword ptr [ebp - 0x44]
004b351e  85db                     test       ebx, ebx
004b3520  8bf8                     mov        edi, eax
004b3522  8b45c0                   mov        eax, dword ptr [ebp - 0x40]
004b3525  897dc8                   mov        dword ptr [ebp - 0x38], edi
004b3528  741d                     je         0x4b3547
004b352a  8b55c4                   mov        edx, dword ptr [ebp - 0x3c]
004b352d  8bc8                     mov        ecx, eax
004b352f  2bcb                     sub        ecx, ebx
004b3531  2bd3                     sub        edx, ebx
004b3533  c1f902                   sar        ecx, 2
004b3536  c1fa02                   sar        edx, 2
004b3539  3bca                     cmp        ecx, edx
004b353b  730a                     jae        0x4b3547
004b353d  8938                     mov        dword ptr [eax], edi
004b353f  83c004                   add        eax, 4
004b3542  8945c0                   mov        dword ptr [ebp - 0x40], eax
004b3545  eb0f                     jmp        0x4b3556
004b3547  8d55c8                   lea        edx, [ebp - 0x38]
004b354a  52                       push       edx
004b354b  6a01                     push       1
004b354d  50                       push       eax
004b354e  8d4db8                   lea        ecx, [ebp - 0x48]
004b3551  e80a2af5ff               call       0x405f60
004b3556  8a45f3                   mov        al, byte ptr [ebp - 0xd]
004b3559  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004b355c  f6d8                     neg        al
004b355e  1bc0                     sbb        eax, eax
004b3560  83e032                   and        eax, 0x32
004b3563  81c1f8000000             add        ecx, 0xf8
004b3569  8bd8                     mov        ebx, eax
004b356b  e8f0eaf4ff               call       0x402060
004b3570  8b7dc0                   mov        edi, dword ptr [ebp - 0x40]
004b3573  03c3                     add        eax, ebx
004b3575  8b5dbc                   mov        ebx, dword ptr [ebp - 0x44]
004b3578  85db                     test       ebx, ebx
004b357a  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b357d  741f                     je         0x4b359e
004b357f  8b55c4                   mov        edx, dword ptr [ebp - 0x3c]
004b3582  8bcf                     mov        ecx, edi
004b3584  2bcb                     sub        ecx, ebx
004b3586  2bd3                     sub        edx, ebx
004b3588  c1f902                   sar        ecx, 2
004b358b  c1fa02                   sar        edx, 2
004b358e  3bca                     cmp        ecx, edx
004b3590  730c                     jae        0x4b359e
004b3592  8bcf                     mov        ecx, edi
004b3594  83c104                   add        ecx, 4
004b3597  8907                     mov        dword ptr [edi], eax
004b3599  894dc0                   mov        dword ptr [ebp - 0x40], ecx
004b359c  eb0f                     jmp        0x4b35ad
004b359e  8d45c8                   lea        eax, [ebp - 0x38]
004b35a1  50                       push       eax
004b35a2  6a01                     push       1
004b35a4  57                       push       edi
004b35a5  8d4db8                   lea        ecx, [ebp - 0x48]
004b35a8  e8b329f5ff               call       0x405f60
004b35ad  8b16                     mov        edx, dword ptr [esi]
004b35af  6a00                     push       0
004b35b1  6a00                     push       0
004b35b3  6a03                     push       3
004b35b5  8d45b8                   lea        eax, [ebp - 0x48]
004b35b8  50                       push       eax
004b35b9  6a04                     push       4
004b35bb  8bce                     mov        ecx, esi
004b35bd  ff928c020000             call       dword ptr [edx + 0x28c]
004b35c3  8b45bc                   mov        eax, dword ptr [ebp - 0x44]
004b35c6  85c0                     test       eax, eax
004b35c8  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b35cf  746f                     je         0x4b3640
004b35d1  50                       push       eax
004b35d2  e806ca7400               call       0xbfffdd
004b35d7  83c404                   add        esp, 4
004b35da  eb64                     jmp        0x4b3640
004b35dc  83ff05                   cmp        edi, 5
004b35df  755f                     jne        0x4b3640
004b35e1  33ff                     xor        edi, edi
004b35e3  897dbc                   mov        dword ptr [ebp - 0x44], edi
004b35e6  897dc0                   mov        dword ptr [ebp - 0x40], edi
004b35e9  897dc4                   mov        dword ptr [ebp - 0x3c], edi
004b35ec  8d4dd0                   lea        ecx, [ebp - 0x30]
004b35ef  51                       push       ecx
004b35f0  8d4db8                   lea        ecx, [ebp - 0x48]
004b35f3  c745fc08000000           mov        dword ptr [ebp - 4], 8
004b35fa  e8213bf5ff               call       0x407120
004b35ff  8b16                     mov        edx, dword ptr [esi]
004b3601  57                       push       edi
004b3602  57                       push       edi
004b3603  6a03                     push       3
004b3605  8d45b8                   lea        eax, [ebp - 0x48]
004b3608  50                       push       eax
004b3609  6a05                     push       5
004b360b  8bce                     mov        ecx, esi
004b360d  ff928c020000             call       dword ptr [edx + 0x28c]
004b3613  8b45bc                   mov        eax, dword ptr [ebp - 0x44]
004b3616  3bc7                     cmp        eax, edi
004b3618  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b361f  741f                     je         0x4b3640
004b3621  50                       push       eax
004b3622  e8b6c97400               call       0xbfffdd
004b3627  83c404                   add        esp, 4
004b362a  eb14                     jmp        0x4b3640
004b362c  c745ecffffffff           mov        dword ptr [ebp - 0x14], 0xffffffff
004b3633  eb0b                     jmp        0x4b3640
004b3635  8b16                     mov        edx, dword ptr [esi]
004b3637  57                       push       edi
004b3638  8bce                     mov        ecx, esi
004b363a  ff9284020000             call       dword ptr [edx + 0x284]
004b3640  33db                     xor        ebx, ebx
004b3642  8dbe94120000             lea        edi, [esi + 0x1294]
004b3648  8b06                     mov        eax, dword ptr [esi]
004b364a  53                       push       ebx
004b364b  8bce                     mov        ecx, esi
004b364d  ff9010040000             call       dword ptr [eax + 0x410]
004b3653  84c0                     test       al, al
004b3655  7413                     je         0x4b366a
004b3657  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b365a  8b0f                     mov        ecx, dword ptr [edi]
004b365c  8b11                     mov        edx, dword ptr [ecx]
004b365e  50                       push       eax
004b365f  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b3662  50                       push       eax
004b3663  8b4508                   mov        eax, dword ptr [ebp + 8]
004b3666  50                       push       eax
004b3667  ff5248                   call       dword ptr [edx + 0x48]
004b366a  43                       inc        ebx
004b366b  83c704                   add        edi, 4
004b366e  83fb12                   cmp        ebx, 0x12
004b3671  7cd5                     jl         0x4b3648
004b3673  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
004b3676  85c0                     test       eax, eax
004b3678  7e34                     jle        0x4b36ae
004b367a  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004b3680  752c                     jne        0x4b36ae
004b3682  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
004b3688  8b8914010000             mov        ecx, dword ptr [ecx + 0x114]
004b368e  50                       push       eax
004b368f  6a03                     push       3
004b3691  e8da870800               call       0x53be70
004b3696  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004b369c  8b7dec                   mov        edi, dword ptr [ebp - 0x14]
004b369f  e88c71f8ff               call       0x43a830
004b36a4  84c0                     test       al, al
004b36a6  7406                     je         0x4b36ae
004b36a8  013dfc4b0001             add        dword ptr [0x1004bfc], edi
004b36ae  8bce                     mov        ecx, esi
004b36b0  e8eb9dffff               call       0x4ad4a0
004b36b5  84c0                     test       al, al
004b36b7  0f8493020000             je         0x4b3950
004b36bd  8b9654190000             mov        edx, dword ptr [esi + 0x1954]
004b36c3  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004b36c9  8b8658190000             mov        eax, dword ptr [esi + 0x1958]
004b36cf  8dbe54190000             lea        edi, [esi + 0x1954]
004b36d5  33d3                     xor        edx, ebx
004b36d7  2bd7                     sub        edx, edi
004b36d9  3bd0                     cmp        edx, eax
004b36db  740e                     je         0x4b36eb
004b36dd  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b36e3  6a3f                     push       0x3f
004b36e5  57                       push       edi
004b36e6  e8c5396600               call       0xb170b0
004b36eb  8b                       .byte      0x8b
004b36ec  15                       .byte      0x15
004b36ed  d801                     fadd       dword ptr [ecx]
004b36ef  21                       .byte      0x21