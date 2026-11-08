004b2e86  8b16                     mov        edx, dword ptr [esi]
004b2e88  53                       push       ebx
004b2e89  8d45e0                   lea        eax, [ebp - 0x20]
004b2e8c  50                       push       eax
004b2e8d  8bce                     mov        ecx, esi
004b2e8f  c645d800                 mov        byte ptr [ebp - 0x28], 0
004b2e93  c745e064000000           mov        dword ptr [ebp - 0x20], 0x64
004b2e9a  c745e400000000           mov        dword ptr [ebp - 0x1c], 0
004b2ea1  ff9210030000             call       dword ptr [edx + 0x310]
004b2ea7  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004b2eaa  8b16                     mov        edx, dword ptr [esi]
004b2eac  6a00                     push       0
004b2eae  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b2eb1  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b2eb4  50                       push       eax
004b2eb5  53                       push       ebx
004b2eb6  51                       push       ecx
004b2eb7  8d45e4                   lea        eax, [ebp - 0x1c]
004b2eba  50                       push       eax
004b2ebb  8d4dd8                   lea        ecx, [ebp - 0x28]
004b2ebe  51                       push       ecx
004b2ebf  8bce                     mov        ecx, esi
004b2ec1  ff92f8020000             call       dword ptr [edx + 0x2f8]
004b2ec7  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
004b2eca  52                       push       edx
004b2ecb  8bce                     mov        ecx, esi
004b2ecd  8945ec                   mov        dword ptr [ebp - 0x14], eax
004b2ed0  e83b5c0300               call       0x4e8b10
004b2ed5  84c0                     test       al, al
004b2ed7  0f8457010000             je         0x4b3034
004b2edd  8b06                     mov        eax, dword ptr [esi]
004b2edf  8bce                     mov        ecx, esi
004b2ee1  ff90e4000000             call       dword ptr [eax + 0xe4]
004b2ee7  68e8010000               push       0x1e8
004b2eec  8bf8                     mov        edi, eax
004b2eee  e85d0df5ff               call       0x403c50
004b2ef3  83c404                   add        esp, 4
004b2ef6  8945cc                   mov        dword ptr [ebp - 0x34], eax
004b2ef9  85c0                     test       eax, eax
004b2efb  c745fc02000000           mov        dword ptr [ebp - 4], 2
004b2f02  7410                     je         0x4b2f14
004b2f04  6a01                     push       1
004b2f06  68280dcd00               push       0xcd0d28
004b2f0b  8bc8                     mov        ecx, eax
004b2f0d  e8be07feff               call       0x4936d0
004b2f12  eb02                     jmp        0x4b2f16
004b2f14  33c0                     xor        eax, eax
004b2f16  8b16                     mov        edx, dword ptr [esi]
004b2f18  6a01                     push       1
004b2f1a  6a00                     push       0
004b2f1c  6a01                     push       1
004b2f1e  6a01                     push       1
004b2f20  6a00                     push       0
004b2f22  6a01                     push       1
004b2f24  f7df                     neg        edi
004b2f26  57                       push       edi
004b2f27  6a00                     push       0
004b2f29  50                       push       eax
004b2f2a  6a64                     push       0x64
004b2f2c  8bce                     mov        ecx, esi
004b2f2e  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b2f35  ff92f8000000             call       dword ptr [edx + 0xf8]
004b2f3b  68e8010000               push       0x1e8
004b2f40  e80b0df5ff               call       0x403c50
004b2f45  83c404                   add        esp, 4
004b2f48  8945cc                   mov        dword ptr [ebp - 0x34], eax
004b2f4b  85c0                     test       eax, eax
004b2f4d  c745fc03000000           mov        dword ptr [ebp - 4], 3
004b2f54  7410                     je         0x4b2f66
004b2f56  6a01                     push       1
004b2f58  68c80ccd00               push       0xcd0cc8
004b2f5d  8bc8                     mov        ecx, eax
004b2f5f  e86c07feff               call       0x4936d0
004b2f64  eb02                     jmp        0x4b2f68
004b2f66  33c0                     xor        eax, eax
004b2f68  8b16                     mov        edx, dword ptr [esi]
004b2f6a  6a01                     push       1
004b2f6c  6a00                     push       0
004b2f6e  6a01                     push       1
004b2f70  6a01                     push       1
004b2f72  6a00                     push       0
004b2f74  6a01                     push       1
004b2f76  57                       push       edi
004b2f77  6a00                     push       0
004b2f79  50                       push       eax
004b2f7a  6a63                     push       0x63
004b2f7c  8bce                     mov        ecx, esi
004b2f7e  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b2f85  ff92f8000000             call       dword ptr [edx + 0xf8]
004b2f8b  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
004b2f8e  81c128010000             add        ecx, 0x128
004b2f94  e81704f8ff               call       0x4333b0
004b2f99  d80d1009cd00             fmul       dword ptr [0xcd0910]
004b2f9f  8b06                     mov        eax, dword ptr [esi]
004b2fa1  8bce                     mov        ecx, esi
004b2fa3  d95dcc                   fstp       dword ptr [ebp - 0x34]
004b2fa6  ff9034020000             call       dword ptr [eax + 0x234]
004b2fac  8945d4                   mov        dword ptr [ebp - 0x2c], eax
004b2faf  db45d4                   fild       dword ptr [ebp - 0x2c]
004b2fb2  d84dcc                   fmul       dword ptr [ebp - 0x34]
004b2fb5  e88ae57400               call       0xc01544
004b2fba  6a00                     push       0
004b2fbc  682829f400               push       0xf42928
004b2fc1  686c52f500               push       0xf5526c
004b2fc6  6a00                     push       0
004b2fc8  56                       push       esi
004b2fc9  8bf8                     mov        edi, eax
004b2fcb  e83bdd7400               call       0xc00d0b
004b2fd0  83c414                   add        esp, 0x14
004b2fd3  85c0                     test       eax, eax
004b2fd5  745a                     je         0x4b3031
004b2fd7  8b88e4190000             mov        ecx, dword ptr [eax + 0x19e4]
004b2fdd  83f901                   cmp        ecx, 1
004b2fe0  7512                     jne        0x4b2ff4
004b2fe2  b856555555               mov        eax, 0x55555556
004b2fe7  f7ef                     imul       edi
004b2fe9  8bca                     mov        ecx, edx
004b2feb  c1e91f                   shr        ecx, 0x1f
004b2fee  03ca                     add        ecx, edx
004b2ff0  8bf9                     mov        edi, ecx
004b2ff2  eb3d                     jmp        0x4b3031
004b2ff4  83f902                   cmp        ecx, 2
004b2ff7  7507                     jne        0x4b3000
004b2ff9  b856555555               mov        eax, 0x55555556
004b2ffe  eb26                     jmp        0x4b3026
004b3000  83f903                   cmp        ecx, 3
004b3003  7512                     jne        0x4b3017
004b3005  b8abaaaa2a               mov        eax, 0x2aaaaaab
004b300a  f7ef                     imul       edi
004b300c  8bca                     mov        ecx, edx
004b300e  c1e91f                   shr        ecx, 0x1f
004b3011  03ca                     add        ecx, edx
004b3013  8bf9                     mov        edi, ecx
004b3015  eb1a                     jmp        0x4b3031
004b3017  8a881c1e0000             mov        cl, byte ptr [eax + 0x1e1c]
004b301d  84c9                     test       cl, cl
004b301f  7410                     je         0x4b3031
004b3021  b8abaaaa2a               mov        eax, 0x2aaaaaab
004b3026  f7ef                     imul       edi
004b3028  8bc2                     mov        eax, edx
004b302a  c1e81f                   shr        eax, 0x1f
004b302d  03c2                     add        eax, edx
004b302f  8bf8                     mov        edi, eax
004b3031  017dec                   add        dword ptr [ebp - 0x14], edi
004b3034  8b8edc120000             mov        ecx, dword ptr [esi + 0x12dc]
004b303a  85c9                     test       ecx, ecx
004b303c  740a                     je         0x4b3048
004b303e  53                       push       ebx
004b303f  8d55ec                   lea        edx, [ebp - 0x14]
004b3042  52                       push       edx
004b3043  e8483c0000               call       0x4b6c90
004b3048  8b06                     mov        eax, dword ptr [esi]
004b304a  8bce                     mov        ecx, esi
004b304c  ff9034020000             call       dword ptr [eax + 0x234]
004b3052  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b3055  3bc8                     cmp        ecx, eax
004b3057  7d05                     jge        0x4b305e
004b3059  894dd4                   mov        dword ptr [ebp - 0x2c], ecx
004b305c  eb0d                     jmp        0x4b306b
004b305e  8b16                     mov        edx, dword ptr [esi]
004b3060  8bce                     mov        ecx, esi
004b3062  ff9234020000             call       dword ptr [edx + 0x234]
004b3068  8945d4                   mov        dword ptr [ebp - 0x2c], eax
004b306b  8b03                     mov        eax, dword ptr [ebx]
004b306d  8bcb                     mov        ecx, ebx
004b306f  ff909c010000             call       dword ptr [eax + 0x19c]
004b3075  83b87801000002           cmp        dword ptr [eax + 0x178], 2
004b307c  755d                     jne        0x4b30db
004b307e  6800010000               push       0x100
004b3083  e8c80bf5ff               call       0x403c50
004b3088  83c404                   add        esp, 4
004b308b  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b308e  85c0                     test       eax, eax
004b3090  c745fc04000000           mov        dword ptr [ebp - 4], 4
004b3097  7421                     je         0x4b30ba
004b3099  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b309c  6a01                     push       1
004b309e  f7d9                     neg        ecx
004b30a0  6a00                     push       0
004b30a2  894dcc                   mov        dword ptr [ebp - 0x34], ecx
004b30a5  db45cc                   fild       dword ptr [ebp - 0x34]
004b30a8  68e8030000               push       0x3e8
004b30ad  51                       push       ecx
004b30ae  8bc8                     mov        ecx, eax
004b30b0  d91c24                   fstp       dword ptr [esp]
004b30b3  e8f86afbff               call       0x469bb0
004b30b8  eb02                     jmp        0x4b30bc
004b30ba  33c0                     xor        eax, eax
004b30bc  8b10                     mov        edx, dword ptr [eax]
004b30be  6a00                     push       0
004b30c0  6aff                     push       -1
004b30c2  6a00                     push       0
004b30c4  6a00                     push       0
004b30c6  6a00                     push       0
004b30c8  53                       push       ebx
004b30c9  56                       push       esi
004b30ca  8bc8                     mov        ecx, eax
004b30cc  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b30d3  ff5248                   call       dword ptr [edx + 0x48]
004b30d6  e9ff000000               jmp        0x4b31da
004b30db  8b03                     mov        eax, dword ptr [ebx]
004b30dd  8bcb                     mov        ecx, ebx
004b30df  ff909c010000             call       dword ptr [eax + 0x19c]
004b30e5  83b87801000004           cmp        dword ptr [eax + 0x178], 4
004b30ec  7531                     jne        0x4b311f
004b30ee  68a4000000               push       0xa4
004b30f3  e8580bf5ff               call       0x403c50
004b30f8  83c404                   add        esp, 4
004b30fb  8945c8                   mov        dword ptr [ebp - 0x38], eax
004b30fe  85c0                     test       eax, eax
004b3100  c745fc05000000           mov        dword ptr [ebp - 4], 5
004b3107  74b1                     je         0x4b30ba
004b3109  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b310c  6a01                     push       1
004b310e  f7d9                     neg        ecx
004b3110  68e8030000               push       0x3e8
004b3115  51                       push       ecx
004b3116  8bc8                     mov        ecx, eax
004b3118  e8936cfbff               call       0x469db0
004b311d  eb9d                     jmp        0x4b30bc
004b311f  8b3e                     mov        edi, dword ptr [esi]
004b3121  53                       push       ebx
004b3122  6a00                     push       0
004b3124  8d8e30120000             lea        ecx, [esi + 0x1230]
004b312a  e831eff4ff               call       0x402060
004b312f  2b45ec                   sub        eax, dword ptr [ebp - 0x14]
004b3132  50                       push       eax
004b3133  8bce                     mov        ecx, esi
004b3135  ff97e8030000             call       dword ptr [edi + 0x3e8]
004b313b  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b3140  8b4844                   mov        ecx, dword ptr [eax + 0x44]
004b3143  8b86c8150000             mov        eax, dword ptr [esi + 0x15c8]
004b3149  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b314f  c1e002                   shl        eax, 2
004b3152  8d1408                   lea        edx, [eax + ecx]
004b3155  f7d2                     not        edx
004b3157  33d7                     xor        edx, edi
004b3159  891408                   mov        dword ptr [eax + ecx], edx
004b315c  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b3161  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004b3164  8b86c8150000             mov        eax, dword ptr [esi + 0x15c8]
004b316a  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b3170  c1e002                   shl        eax, 2
004b3173  8d1408                   lea        edx, [eax + ecx]
004b3176  f7d2                     not        edx
004b3178  33d7                     xor        edx, edi
004b317a  891408                   mov        dword ptr [eax + ecx], edx
004b317d  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
004b3180  85c0                     test       eax, eax
004b3182  752f                     jne        0x4b31b3
004b3184  8b7de8                   mov        edi, dword ptr [ebp - 0x18]
004b3187  8d4f1c                   lea        ecx, [edi + 0x1c]
004b318a  e8d1eef4ff               call       0x402060
004b318f  85c0                     test       eax, eax
004b3191  7520                     jne        0x4b31b3
004b3193  8bcf                     mov        ecx, edi
004b3195  e81602f8ff               call       0x4333b0
004b319a  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
004b31a0  dfe0                     fnstsw     ax
004b31a2  f6c441                   test       ah, 0x41
004b31a5  740c                     je         0x4b31b3
004b31a7  8d4f08                   lea        ecx, [edi + 8]
004b31aa  e8b1eef4ff               call       0x402060
004b31af  85c0                     test       eax, eax
004b31b1  7e27                     jle        0x4b31da
004b31b3  8b45c8                   mov        eax, dword ptr [ebp - 0x38]
004b31b6  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004b31b9  8b55d8                   mov        edx, dword ptr [ebp - 0x28]
004b31bc  50                       push       eax
004b31bd  8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
004b31c0  51                       push       ecx
004b31c1  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b31c4  52                       push       edx
004b31c5  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004b31c8  50                       push       eax
004b31c9  51                       push       ecx
004b31ca  52                       push       edx
004b31cb  56                       push       esi
004b31cc  53                       push       ebx
004b31cd  e82e9effff               call       0x4ad000
004b31d2  83c420                   add        esp, 0x20
004b31d5  eb03                     jmp        0x4b31da
004b31d7  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004b31da  33c0                     xor        eax, eax
004b31dc  53                       push       ebx
004b31dd  8d4ddc                   lea        ecx, [ebp - 0x24]
004b31e0  51                       push       ecx
004b31e1  8d55d0                   lea        edx, [ebp - 0x30]
004b31e4  8945d0                   mov        dword ptr [ebp - 0x30], eax
004b31e7  8945dc                   mov        dword ptr [ebp - 0x24], eax
004b31ea  8b06                     mov        eax, dword ptr [esi]
004b31ec  52                       push       edx
004b31ed  8bce                     mov        ecx, esi
004b31ef  ff90e0030000             call       dword ptr [eax + 0x3e0]
004b31f5  8bf8                     mov        edi, eax
004b31f7  83ffff                   cmp        edi, -1
004b31fa  744a                     je         0x4b3246
004b31fc  8a869c040000             mov        al, byte ptr [esi + 0x49c]
004b3202  84c0                     test       al, al
004b3204  7440                     je         0x4b3246
004b3206  8b03                     mov        eax, dword ptr [ebx]
004b3208  8bcb                     mov        ecx, ebx
004b320a  ff909c010000             call       dword ptr [eax + 0x19c]
004b3210  83b87801000002           cmp        dword ptr [eax + 0x178], 2
004b3217  7523                     jne        0x4b323c
004b3219  6a00                     push       0
004b321b  e8d0ae3f00               call       0x8ae0f0
004b3220  99                       cdq        
004b3221  b964000000               mov        ecx, 0x64
004b3226  f7f9                     idiv       ecx
004b3228  83c404                   add        esp, 4
004b322b  83fa14                   cmp        edx, 0x14
004b322e  7d0c                     jge        0x4b323c
004b3230  8b16                     mov        edx, dword ptr [esi]
004b3232  8bce                     mov        ecx, esi
004b3234  ff92dc040000             call       dword ptr [edx + 0x4dc]
004b323a  eb0a                     jmp        0x4b3246
004b323c  8b06                     mov        eax, dword ptr [esi]
004b323e  8bce                     mov        ecx, esi
004b3240  ff90dc040000             call       dword ptr [eax + 0x4dc]
004b3246  83ff03                   cmp        edi, 3
004b3249  0f85bf010000             jne        0x4b340e
004b324f  8b16                     mov        edx, dword ptr [esi]
004b3251  bb01000000               mov        ebx, 1
004b3256  53                       push       ebx
004b3257  8bce                     mov        ecx, esi
004b3259  ff9274030000             call       dword ptr [edx + 0x374]
004b325f  85c0                     test       eax, eax
004b3261  7518                     jne        0x4b327b
004b3263  8b06                     mov        eax, dword ptr [esi]
004b3265  53                       push       ebx
004b3266  8bce                     mov        ecx, esi
004b3268  ff909c030000             call       dword ptr [eax + 0x39c]
004b326e  85c0                     test       eax, eax
004b3270  7409                     je         0x4b327b
004b3272  c745e000000000           mov        dword ptr [ebp - 0x20], 0
004b3279  eb5d                     jmp        0x4b32d8
004b327b  8b16                     mov        edx, dword ptr [esi]
004b327d  6a00                     push       0
004b327f  8bce                     mov        ecx, esi
004b3281  ff9274030000             call       dword ptr [edx + 0x374]
004b3287  85c0                     test       eax, eax
004b3289  7515                     jne        0x4b32a0
004b328b  8b06                     mov        eax, dword ptr [esi]
004b328d  6a00                     push       0
004b328f  8bce                     mov        ecx, esi
004b3291  ff909c030000             call       dword ptr [eax + 0x39c]
004b3297  85c0                     test       eax, eax
004b3299  7405                     je         0x4b32a0
004b329b  895de0                   mov        dword ptr [ebp - 0x20], ebx
004b329e  eb38                     jmp        0x4b32d8
004b32a0  8d8e5c150000             lea        ecx, [esi + 0x155c]
004b32a6  e8b5edf4ff               call       0x402060
004b32ab  83f803                   cmp        eax, 3
004b32ae  750f                     jne        0x4b32bf
004b32b0  8b86bc160000             mov        eax, dword ptr [esi + 0x16bc]
004b32b6  8bcb                     mov        ecx, ebx
004b32b8  2bc8                     sub        ecx, eax
004b32ba  894de0                   mov        dword ptr [ebp - 0x20], ecx
004b32bd  eb19                     jmp        0x4b32d8
004b32bf  6a00                     push       0
004b32c1  e82aae3f00               call       0x8ae0f0
004b32c6  83c404                   add        esp, 4
004b32c9  2501000080               and        eax, 0x80000001
004b32ce  7905                     jns        0x4b32d5
004b32d0  48                       dec        eax
004b32d1  83c8fe                   or         eax, 0xfffffffe
004b32d4  40                       inc        eax
004b32d5  8945e0                   mov        dword ptr [ebp - 0x20], eax
004b32d8  8b7de8                   mov        edi, dword ptr [ebp - 0x18]
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
004b334f  ff                       .byte      0xff
004b3350  92                       xchg       edx, eax
004b3351  1c03                     sbb        al, 3
004b3353  00                       .byte      0x00