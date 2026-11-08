004f2950 55                       push      ebp
004f2951 8bec                     mov       ebp, esp
004f2953 83ec08                   sub       esp, 8
004f2956 56                       push      esi
004f2957 8bf1                     mov       esi, ecx
004f2959 83be301a000007           cmp       dword ptr [esi + 0x1a30], 7
004f2960 7507                     jne       0x4f2969
004f2962 32c0                     xor       al, al
004f2964 5e                       pop       esi
004f2965 8be5                     mov       esp, ebp
004f2967 5d                       pop       ebp
004f2968 c3                       ret       
004f2969 57                       push      edi
004f296a 6a00                     push      0
004f296c e87fb73b00               call      0x8ae0f0
004f2971 99                       cdq       
004f2972 b964000000               mov       ecx, 0x64
004f2977 f7f9                     idiv      ecx
004f2979 83c404                   add       esp, 4
004f297c 83fa32                   cmp       edx, 0x32
004f297f 0f8dae000000             jge       0x4f2a33
004f2985 8bbe801b0000             mov       edi, dword ptr [esi + 0x1b80]
004f298b 85ff                     test      edi, edi
004f298d 0f84a0000000             je        0x4f2a33
004f2993 6a0c                     push      0xc
004f2995 8bce                     mov       ecx, esi
004f2997 e86456f7ff               call      0x468000
004f299c 84c0                     test      al, al
004f299e 0f858f000000             jne       0x4f2a33
004f29a4 8b17                     mov       edx, dword ptr [edi]
004f29a6 8bcf                     mov       ecx, edi
004f29a8 ff9294000000             call      dword ptr [edx + 0x94]
004f29ae 8bf8                     mov       edi, eax
004f29b0 8b06                     mov       eax, dword ptr [esi]
004f29b2 8bce                     mov       ecx, esi
004f29b4 ff9094000000             call      dword ptr [eax + 0x94]
004f29ba 3bc7                     cmp       eax, edi
004f29bc 8d8ea81c0000             lea       ecx, [esi + 0x1ca8]
004f29c2 7d29                     jge       0x4f29ed
004f29c4 e897f6f0ff               call      0x402060
004f29c9 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f29cf 8b11                     mov       edx, dword ptr [ecx]
004f29d1 8945f8                   mov       dword ptr [ebp - 8], eax
004f29d4 ff9294000000             call      dword ptr [edx + 0x94]
004f29da 8945fc                   mov       dword ptr [ebp - 4], eax
004f29dd db45fc                   fild      dword ptr [ebp - 4]
004f29e0 db45f8                   fild      dword ptr [ebp - 8]
004f29e3 d80dd04bcd00             fmul      dword ptr [0xcd4bd0]
004f29e9 dec1                     faddp     st(1)
004f29eb eb27                     jmp       0x4f2a14
004f29ed e86ef6f0ff               call      0x402060
004f29f2 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f29f8 8945fc                   mov       dword ptr [ebp - 4], eax
004f29fb 8b01                     mov       eax, dword ptr [ecx]
004f29fd ff9094000000             call      dword ptr [eax + 0x94]
004f2a03 8945f8                   mov       dword ptr [ebp - 8], eax
004f2a06 db45f8                   fild      dword ptr [ebp - 8]
004f2a09 db45fc                   fild      dword ptr [ebp - 4]
004f2a0c d80dd04bcd00             fmul      dword ptr [0xcd4bd0]
004f2a12 dee9                     fsubp     st(1)
004f2a14 e82beb7000               call      0xc01544
004f2a19 8b16                     mov       edx, dword ptr [esi]
004f2a1b 6a0b                     push      0xb
004f2a1d 8bce                     mov       ecx, esi
004f2a1f 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004f2a25 ff92f0050000             call      dword ptr [edx + 0x5f0]
004f2a2b 5f                       pop       edi
004f2a2c b001                     mov       al, 1
004f2a2e 5e                       pop       esi
004f2a2f 8be5                     mov       esp, ebp
004f2a31 5d                       pop       ebp
004f2a32 c3                       ret       
004f2a33 5f                       pop       edi
004f2a34 32c0                     xor       al, al
004f2a36 5e                       pop       esi
004f2a37 8be5                     mov       esp, ebp
004f2a39 5d                       pop       ebp
004f2a3a c3                       ret       
004f2a3b cc                       int3      
004f2a3c cc                       int3      
004f2a3d cc                       int3      
004f2a3e cc                       int3      
004f2a3f cc                       int3      
004f2a40 56                       push      esi
004f2a41 8bf1                     mov       esi, ecx
004f2a43 8b06                     mov       eax, dword ptr [esi]
004f2a45 ff5038                   call      dword ptr [eax + 0x38]
004f2a48 84c0                     test      al, al
004f2a4a 7430                     je        0x4f2a7c
004f2a4c 57                       push      edi
004f2a4d 68e0baca00               push      0xcabae0
004f2a52 8dbef01a0000             lea       edi, [esi + 0x1af0]
004f2a58 e870d37000               call      0xbffdcd
004f2a5d 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
004f2a60 83c404                   add       esp, 4
004f2a63 50                       push      eax
004f2a64 68e0baca00               push      0xcabae0
004f2a69 51                       push      ecx
004f2a6a 6a00                     push      0
004f2a6c 8bcf                     mov       ecx, edi
004f2a6e e87d15f1ff               call      0x403ff0
004f2a73 85c0                     test      eax, eax
004f2a75 5f                       pop       edi
004f2a76 7404                     je        0x4f2a7c
004f2a78 32c0                     xor       al, al
004f2a7a 5e                       pop       esi
004f2a7b c3                       ret       
004f2a7c 8b86e4190000             mov       eax, dword ptr [esi + 0x19e4]
004f2a82 83f803                   cmp       eax, 3
004f2a85 7405                     je        0x4f2a8c
004f2a87 83f808                   cmp       eax, 8
004f2a8a 7559                     jne       0x4f2ae5
004f2a8c 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f2a92 81c140100000             add       ecx, 0x1040
004f2a98 e8c3f5f0ff               call      0x402060
004f2a9d 83f803                   cmp       eax, 3
