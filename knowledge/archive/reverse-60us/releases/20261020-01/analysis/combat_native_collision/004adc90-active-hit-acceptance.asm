004adc90 55                       push      ebp
004adc91 8bec                     mov       ebp, esp
004adc93 56                       push      esi
004adc94 8bf1                     mov       esi, ecx
004adc96 8d8e68180000             lea       ecx, [esi + 0x1868]
004adc9c e8bf43f5ff               call      0x402060
004adca1 85c0                     test      eax, eax
004adca3 8b4508                   mov       eax, dword ptr [ebp + 8]
004adca6 7410                     je        0x4adcb8
004adca8 c70000000000             mov       dword ptr [eax], 0
004adcae b803000000               mov       eax, 3
004adcb3 5e                       pop       esi
004adcb4 5d                       pop       ebp
004adcb5 c20800                   ret       8
004adcb8 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004adcbb 51                       push      ecx
004adcbc c70064000000             mov       dword ptr [eax], 0x64
004adcc2 8b8edc120000             mov       ecx, dword ptr [esi + 0x12dc]
004adcc8 50                       push      eax
004adcc9 e8027d0b00               call      0x5659d0
004adcce 33d2                     xor       edx, edx
004adcd0 85c0                     test      eax, eax
004adcd2 0f9cc2                   setl      dl
004adcd5 5e                       pop       esi
004adcd6 4a                       dec       edx
004adcd7 23c2                     and       eax, edx
004adcd9 5d                       pop       ebp
004adcda c20800                   ret       8
004adcdd cc                       int3      
004adcde cc                       int3      
004adcdf cc                       int3      
004adce0 55                       push      ebp
004adce1 8bec                     mov       ebp, esp
004adce3 56                       push      esi
004adce4 8bf1                     mov       esi, ecx
004adce6 8d8ea4160000             lea       ecx, [esi + 0x16a4]
004adcec e86f43f5ff               call      0x402060
004adcf1 85c0                     test      eax, eax
004adcf3 0f84c5000000             je        0x4addbe
004adcf9 8d8ebc040000             lea       ecx, [esi + 0x4bc]
004adcff e85c43f5ff               call      0x402060
004add04 85c0                     test      eax, eax
004add06 740d                     je        0x4add15
004add08 8d8ec4040000             lea       ecx, [esi + 0x4c4]
004add0e e84d43f5ff               call      0x402060
004add13 eb07                     jmp       0x4add1c
004add15 8bce                     mov       ecx, esi
004add17 e8c4c2feff               call      0x499fe0
004add1c 85c0                     test      eax, eax
004add1e 7409                     je        0x4add29
004add20 83f801                   cmp       eax, 1
004add23 0f8595000000             jne       0x4addbe
004add29 8b4508                   mov       eax, dword ptr [ebp + 8]
004add2c 85c0                     test      eax, eax
004add2e 7422                     je        0x4add52
004add30 8b16                     mov       edx, dword ptr [esi]
004add32 50                       push      eax
004add33 8d4508                   lea       eax, [ebp + 8]
004add36 50                       push      eax
004add37 8bce                     mov       ecx, esi
004add39 c7450864000000           mov       dword ptr [ebp + 8], 0x64
004add40 ff9210030000             call      dword ptr [edx + 0x310]
004add46 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004add49 85c9                     test      ecx, ecx
004add4b 7471                     je        0x4addbe
004add4d 83f803                   cmp       eax, 3
004add50 746c                     je        0x4addbe
004add52 8b16                     mov       edx, dword ptr [esi]
004add54 6a00                     push      0
004add56 8bce                     mov       ecx, esi
004add58 ff9274030000             call      dword ptr [edx + 0x374]
004add5e 85c0                     test      eax, eax
004add60 740e                     je        0x4add70
004add62 8b06                     mov       eax, dword ptr [esi]
004add64 8bce                     mov       ecx, esi
004add66 ff9078030000             call      dword ptr [eax + 0x378]
004add6c 85c0                     test      eax, eax
004add6e 751e                     jne       0x4add8e
004add70 8b16                     mov       edx, dword ptr [esi]
004add72 6a00                     push      0
004add74 8bce                     mov       ecx, esi
004add76 ff929c030000             call      dword ptr [edx + 0x39c]
004add7c 85c0                     test      eax, eax
004add7e 753e                     jne       0x4addbe
004add80 8b06                     mov       eax, dword ptr [esi]
004add82 8bce                     mov       ecx, esi
004add84 ff90a0030000             call      dword ptr [eax + 0x3a0]
004add8a 85c0                     test      eax, eax
004add8c 7430                     je        0x4addbe
004add8e 8b16                     mov       edx, dword ptr [esi]
004add90 6a01                     push      1
004add92 8bce                     mov       ecx, esi
004add94 ff9210040000             call      dword ptr [edx + 0x410]
004add9a 84c0                     test      al, al
004add9c 7520                     jne       0x4addbe
004add9e 8b06                     mov       eax, dword ptr [esi]
004adda0 6a07                     push      7
004adda2 8bce                     mov       ecx, esi
004adda4 ff9010040000             call      dword ptr [eax + 0x410]
004addaa 84c0                     test      al, al
004addac 7510                     jne       0x4addbe
004addae 8a869c040000             mov       al, byte ptr [esi + 0x49c]
004addb4 84c0                     test      al, al
004addb6 0f95c0                   setne     al
004addb9 5e                       pop       esi
004addba 5d                       pop       ebp
004addbb c20400                   ret       4
004addbe 32c0                     xor       al, al
004addc0 5e                       pop       esi
004addc1 5d                       pop       ebp
004addc2 c20400                   ret       4
004addc5 cc                       int3      
004addc6 cc                       int3      
004addc7 cc                       int3      
004addc8 cc                       int3      
004addc9 cc                       int3      
004addca cc                       int3      
004addcb cc                       int3      
004addcc cc                       int3      
004addcd cc                       int3      
004addce cc                       int3      
004addcf cc                       int3      
004addd0 55                       push      ebp
004addd1 8bec                     mov       ebp, esp
004addd3 51                       push      ecx
004addd4 56                       push      esi
004addd5 57                       push      edi
004addd6 8b7d08                   mov       edi, dword ptr [ebp + 8]
004addd9 85ff                     test      edi, edi
004adddb 8bf1                     mov       esi, ecx
004adddd 0f8405010000             je        0x4adee8
004adde3 8b8610150000             mov       eax, dword ptr [esi + 0x1510]
004adde9 85c0                     test      eax, eax
004addeb 0f84f7000000             je        0x4adee8
004addf1 53                       push      ebx
004addf2 8bd8                     mov       ebx, eax
004addf4 8b06                     mov       eax, dword ptr [esi]
004addf6 57                       push      edi
004addf7 ff9044030000             call      dword ptr [eax + 0x344]
004addfd 8bc8                     mov       ecx, eax
004addff 81c100020000             add       ecx, 0x200
004ade05 e8a655f8ff               call      0x4333b0
004ade0a d95dfc                   fstp      dword ptr [ebp - 4]
004ade0d 8b13                     mov       edx, dword ptr [ebx]
004ade0f 8bcb                     mov       ecx, ebx
004ade11 ff92e4000000             call      dword ptr [edx + 0xe4]
004ade17 8bc8                     mov       ecx, eax
004ade19 81c1c0010000             add       ecx, 0x1c0
004ade1f e83c42f5ff               call      0x402060
004ade24 894508                   mov       dword ptr [ebp + 8], eax
004ade27 db4508                   fild      dword ptr [ebp + 8]
004ade2a 8b06                     mov       eax, dword ptr [esi]
004ade2c 57                       push      edi
004ade2d 8bce                     mov       ecx, esi
004ade2f d80df811cc00             fmul      dword ptr [0xcc11f8]
004ade35 d86dfc                   fsubr     dword ptr [ebp - 4]
004ade38 d95dfc                   fstp      dword ptr [ebp - 4]
004ade3b ff9044030000             call      dword ptr [eax + 0x344]
004ade41 8bc8                     mov       ecx, eax
004ade43 81c1f8010000             add       ecx, 0x1f8
004ade49 e81242f5ff               call      0x402060
004ade4e 894508                   mov       dword ptr [ebp + 8], eax
004ade51 db4508                   fild      dword ptr [ebp + 8]
004ade54 d84dfc                   fmul      dword ptr [ebp - 4]
004ade57 e8e8367500               call      0xc01544
004ade5c 83f801                   cmp       eax, 1
004ade5f 7e79                     jle       0x4adeda
004ade61 8b16                     mov       edx, dword ptr [esi]
004ade63 8b9e10150000             mov       ebx, dword ptr [esi + 0x1510]
004ade69 57                       push      edi
004ade6a 8bce                     mov       ecx, esi
004ade6c ff9244030000             call      dword ptr [edx + 0x344]
004ade72 8bc8                     mov       ecx, eax
004ade74 81c100020000             add       ecx, 0x200
004ade7a e83155f8ff               call      0x4333b0
004ade7f d95dfc                   fstp      dword ptr [ebp - 4]
004ade82 8b03                     mov       eax, dword ptr [ebx]
004ade84 8bcb                     mov       ecx, ebx
004ade86 ff90e4000000             call      dword ptr [eax + 0xe4]
004ade8c 8bc8                     mov       ecx, eax
004ade8e 81c1c0010000             add       ecx, 0x1c0
004ade94 e8c741f5ff               call      0x402060
004ade99 8b16                     mov       edx, dword ptr [esi]
004ade9b 894508                   mov       dword ptr [ebp + 8], eax
004ade9e db4508                   fild      dword ptr [ebp + 8]
004adea1 57                       push      edi
004adea2 8bce                     mov       ecx, esi
004adea4 d80df811cc00             fmul      dword ptr [0xcc11f8]
004adeaa d86dfc                   fsubr     dword ptr [ebp - 4]
004adead d95dfc                   fstp      dword ptr [ebp - 4]
004adeb0 ff9244030000             call      dword ptr [edx + 0x344]
004adeb6 8bc8                     mov       ecx, eax
004adeb8 81c1f8010000             add       ecx, 0x1f8
004adebe e8                       .byte     0xe8
004adebf 9d                       popfd     
