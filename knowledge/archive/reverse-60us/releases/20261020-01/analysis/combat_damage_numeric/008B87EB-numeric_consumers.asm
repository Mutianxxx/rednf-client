008b87eb 8b8699010000             mov        eax, dword ptr [esi + 0x199]
008b87f1 d84508                   fadd       dword ptr [ebp + 8]
008b87f4 8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
008b87f7 83e011                   and        eax, 0x11
008b87fa 83c410                   add        esp, 0x10
008b87fd d95d08                   fstp       dword ptr [ebp + 8]
008b8800 3c11                     cmp        al, 0x11
008b8802 0f85b7000000             jne        0x8b88bf
008b8808 807e0502                 cmp        byte ptr [esi + 5], 2
008b880c 0f84ad000000             je         0x8b88bf
008b8812 8a460e                   mov        al, byte ptr [esi + 0xe]
008b8815 84c0                     test       al, al
008b8817 0f85a2000000             jne        0x8b88bf
008b881d 57                       push       edi
008b881e 56                       push       esi
008b881f 8d4dfc                   lea        ecx, [ebp - 4]
008b8822 51                       push       ecx
008b8823 8d5510                   lea        edx, [ebp + 0x10]
008b8826 52                       push       edx
008b8827 c7451000000000           mov        dword ptr [ebp + 0x10], 0
008b882e c745fc00000000           mov        dword ptr [ebp - 4], 0
008b8835 e856f4ffff               call       0x8b7c90
008b883a d905581fcc00             fld        dword ptr [0xcc1f58]
008b8840 d86510                   fsub       dword ptr [ebp + 0x10]
008b8843 8a4605                   mov        al, byte ptr [esi + 5]
008b8846 d945fc                   fld        dword ptr [ebp - 4]
008b8849 83c410                   add        esp, 0x10
008b884c 84c0                     test       al, al
008b884e d84e5f                   fmul       dword ptr [esi + 0x5f]
008b8851 dee9                     fsubp      st(1)
008b8853 d84d08                   fmul       dword ptr [ebp + 8]
008b8856 d95d08                   fstp       dword ptr [ebp + 8]
008b8859 752a                     jne        0x8b8885
008b885b 8b86a3000000             mov        eax, dword ptr [esi + 0xa3]
008b8861 894510                   mov        dword ptr [ebp + 0x10], eax
008b8864 80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b886b 7411                     je         0x8b887e
008b886d 6a04                     push       4
008b886f 57                       push       edi
008b8870 e89b03b9ff               call       0x448c10
008b8875 d84d10                   fmul       dword ptr [ebp + 0x10]
008b8878 83c408                   add        esp, 8
008b887b d95d10                   fstp       dword ptr [ebp + 0x10]
008b887e b9a8fe0b01               mov        ecx, 0x10bfea8
008b8883 eb2c                     jmp        0x8b88b1
008b8885 3c01                     cmp        al, 1
008b8887 7536                     jne        0x8b88bf
008b8889 80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b8890 8b8ea7000000             mov        ecx, dword ptr [esi + 0xa7]
008b8896 894d10                   mov        dword ptr [ebp + 0x10], ecx
008b8899 7411                     je         0x8b88ac
008b889b 6a06                     push       6
008b889d 57                       push       edi
008b889e e86d03b9ff               call       0x448c10
008b88a3 d84d10                   fmul       dword ptr [ebp + 0x10]
008b88a6 83c408                   add        esp, 8
008b88a9 d95d10                   fstp       dword ptr [ebp + 0x10]
008b88ac b9b8fe0b01               mov        ecx, 0x10bfeb8
008b88b1 e8faaab7ff               call       0x4333b0
008b88b6 d87d10                   fdivr      dword ptr [ebp + 0x10]
008b88b9 d86d08                   fsubr      dword ptr [ebp + 8]
008b88bc d95d08                   fstp       dword ptr [ebp + 8]
008b88bf 8a4605                   mov        al, byte ptr [esi + 5]
008b88c2 84c0                     test       al, al
008b88c4 7527                     jne        0x8b88ed
008b88c6 80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b88cd 8b563f                   mov        edx, dword ptr [esi + 0x3f]
008b88d0 895510                   mov        dword ptr [ebp + 0x10], edx
008b88d3 7411                     je         0x8b88e6
008b88d5 6a03                     push       3
008b88d7 53                       push       ebx
008b88d8 e83303b9ff               call       0x448c10
008b88dd d84d10                   fmul       dword ptr [ebp + 0x10]
008b88e0 83c408                   add        esp, 8
008b88e3 d95d10                   fstp       dword ptr [ebp + 0x10]
008b88e6 b9e0fe0b01               mov        ecx, 0x10bfee0
008b88eb eb3f                     jmp        0x8b892c
008b88ed 3c01                     cmp        al, 1
008b88ef 7549                     jne        0x8b893a
008b88f1 8b4643                   mov        eax, dword ptr [esi + 0x43]
008b88f4 894510                   mov        dword ptr [ebp + 0x10], eax
008b88f7 80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b88fe 7411                     je         0x8b8911
008b8900 6a05                     push       5
008b8902 53                       push       ebx
008b8903 e80803b9ff               call       0x448c10
008b8908 d84d10                   fmul       dword ptr [ebp + 0x10]
008b890b 83c408                   add        esp, 8
008b890e d95d10                   fstp       dword ptr [ebp + 0x10]
008b8911 8a86c1010000             mov        al, byte ptr [esi + 0x1c1]
008b8917 84c0                     test       al, al
008b8919 740c                     je         0x8b8927
008b891b 81bec2010000b2b30000     cmp        dword ptr [esi + 0x1c2], 0xb3b2
008b8925 7413                     je         0x8b893a
008b8927 b980fe0b01               mov        ecx, 0x10bfe80
008b892c e87faab7ff               call       0x4333b0
008b8931 d87d10                   fdivr      dword ptr [ebp + 0x10]
008b8934 d84508                   fadd       dword ptr [ebp + 8]
008b8937 d95d08                   fstp       dword ptr [ebp + 8]
008b893a 8a4605                   mov        al, byte ptr [esi + 5]
008b893d 84c0                     test       al, al
008b893f 0f8580000000             jne        0x8b89c5
008b8945 8a4604                   mov        al, byte ptr [esi + 4]
008b8948 d9460f                   fld        dword ptr [esi + 0xf]
008b894b 84c0                     test       al, al
008b894d 740b                     je         0x8b895a
008b894f db4663                   fild       dword ptr [esi + 0x63]
008b8952 d88eab000000             fmul       dword ptr [esi + 0xab]
008b8958 dec1                     faddp      st(1)
008b895a d94606                   fld        dword ptr [esi + 6]
008b895d 6a07                     push       7
008b895f d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8965 53                       push       ebx
008b8966 d805581fcc00             fadd       dword ptr [0xcc1f58]
008b896c d8c9                     fmul       st(1)
008b896e d94637                   fld        dword ptr [esi + 0x37]
008b8971 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8977 d805581fcc00             fadd       dword ptr [0xcc1f58]
008b897d dec9                     fmulp      st(1)
008b897f d95d10                   fstp       dword ptr [ebp + 0x10]
008b8982 ddd8                     fstp       st(0)
008b8984 e88702b9ff               call       0x448c10
008b8989 d84d10                   fmul       dword ptr [ebp + 0x10]
008b898c 8b8e99010000             mov        ecx, dword ptr [esi + 0x199]
008b8992 83e111                   and        ecx, 0x11
008b8995 83c408                   add        esp, 8
008b8998 80f911                   cmp        cl, 0x11
008b899b d84508                   fadd       dword ptr [ebp + 8]
008b899e d95d08                   fstp       dword ptr [ebp + 8]
008b89a1 0f85b0000000             jne        0x8b8a57
008b89a7 8a460e                   mov        al, byte ptr [esi + 0xe]
008b89aa 84c0                     test       al, al
008b89ac 0f85a5000000             jne        0x8b8a57
008b89b2 db86af000000             fild       dword ptr [esi + 0xaf]
008b89b8 6a08                     push       8
008b89ba d84e5f                   fmul       dword ptr [esi + 0x5f]
008b89bd da86b7000000             fiadd      dword ptr [esi + 0xb7]
008b89c3 eb7d                     jmp        0x8b8a42
008b89c5 3c01                     cmp        al, 1
008b89c7 0f8595000000             jne        0x8b8a62
008b89cd 8a4604                   mov        al, byte ptr [esi + 4]
008b89d0 d9460f                   fld        dword ptr [esi + 0xf]
008b89d3 84c0                     test       al, al
008b89d5 740b                     je         0x8b89e2
008b89d7 db4667                   fild       dword ptr [esi + 0x67]
008b89da d88eab000000             fmul       dword ptr [esi + 0xab]
008b89e0 dec1                     faddp      st(1)
008b89e2 d94606                   fld        dword ptr [esi + 6]
008b89e5 6a09                     push       9
008b89e7 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b89ed 53                       push       ebx
008b89ee d805581fcc00             fadd       dword ptr [0xcc1f58]
008b89f4 d8c9                     fmul       st(1)
008b89f6 d9463b                   fld        dword ptr [esi + 0x3b]
008b89f9 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b89ff d805581fcc00             fadd       dword ptr [0xcc1f58]
008b8a05 dec9                     fmulp      st(1)
008b8a07 d95d10                   fstp       dword ptr [ebp + 0x10]
008b8a0a ddd8                     fstp       st(0)
008b8a0c e8ff01b9ff               call       0x448c10
008b8a11 d84d10                   fmul       dword ptr [ebp + 0x10]
008b8a14 8b8699010000             mov        eax, dword ptr [esi + 0x199]
008b8a1a 83e011                   and        eax, 0x11
008b8a1d 83c408                   add        esp, 8
008b8a20 3c11                     cmp        al, 0x11
008b8a22 d84508                   fadd       dword ptr [ebp + 8]
008b8a25 d95d08                   fstp       dword ptr [ebp + 8]
008b8a28 752d                     jne        0x8b8a57
008b8a2a 8a460e                   mov        al, byte ptr [esi + 0xe]
008b8a2d 84c0                     test       al, al
008b8a2f 7526                     jne        0x8b8a57
008b8a31 db86b3000000             fild       dword ptr [esi + 0xb3]
008b8a37 6a0a                     push       0xa
008b8a39 d84e5f                   fmul       dword ptr [esi + 0x5f]
008b8a3c da86bb000000             fiadd      dword ptr [esi + 0xbb]
008b8a42 57                       push       edi
008b8a43 d95d10                   fstp       dword ptr [ebp + 0x10]
008b8a46 e8c501b9ff               call       0x448c10
008b8a4b d84d10                   fmul       dword ptr [ebp + 0x10]
008b8a4e 83c408                   add        esp, 8
008b8a51 d86d08                   fsubr      dword ptr [ebp + 8]
008b8a54 d95d08                   fstp       dword ptr [ebp + 8]
008b8a57 8b17                     mov        edx, dword ptr [edi]
008b8a59 8bcf                     mov        ecx, edi
008b8a5b 53                       push       ebx
008b8a5c ff9220030000             call       dword ptr [edx + 0x320]
008b8a62 d94508                   fld        dword ptr [ebp + 8]
008b8a65 d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
008b8a6b dfe0                     fnstsw     ax
008b8a6d f6c405                   test       ah, 5
008b8a70 7a07                     jp         0x8b8a79
008b8a72 c7450800000000           mov        dword ptr [ebp + 8], 0
008b8a79 8d45f8                   lea        eax, [ebp - 8]
008b8a7c 50                       push       eax
008b8a7d 8d4d08                   lea        ecx, [ebp + 8]
008b8a80 51                       push       ecx
008b8a81 56                       push       esi
008b8a82 e829f0ffff               call       0x8b7ab0
008b8a87 d94508                   fld        dword ptr [ebp + 8]
008b8a8a 8ad8                     mov        bl, al
008b8a8c 8a86a6010000             mov        al, byte ptr [esi + 0x1a6]
008b8a92 83c40c                   add        esp, 0xc
008b8a95 84c0                     test       al, al
008b8a97 889ea5010000             mov        byte ptr [esi + 0x1a5], bl
008b8a9d 7416                     je         0x8b8ab5
008b8a9f d80d9051df00             fmul       dword ptr [0xdf5190]
008b8aa5 d94508                   fld        dword ptr [ebp + 8]
008b8aa8 d8e9                     fsubr      st(1)
008b8aaa e8958a3400               call       0xc01544
008b8aaf 8986a7010000             mov        dword ptr [esi + 0x1a7], eax
008b8ab5 d84e1b                   fmul       dword ptr [esi + 0x1b]
008b8ab8 8a86c3000000             mov        al, byte ptr [esi + 0xc3]
008b8abe 84c0                     test       al, al
008b8ac0 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8ac6 da8eac010000             fimul      dword ptr [esi + 0x1ac]
008b8acc d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8ad2 d95508                   fst        dword ptr [ebp + 8]
008b8ad5 740c                     je         0x8b8ae3
008b8ad7 d84e1f                   fmul       dword ptr [esi + 0x1f]
008b8ada d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8ae0 d95508                   fst        dword ptr [ebp + 8]
008b8ae3 8a86c4000000             mov        al, byte ptr [esi + 0xc4]
008b8ae9 84c0                     test       al, al
008b8aeb 740c                     je         0x8b8af9
008b8aed d84e23                   fmul       dword ptr [esi + 0x23]
008b8af0 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8af6 d95508                   fst        dword ptr [ebp + 8]
008b8af9 8a86c5000000             mov        al, byte ptr [esi + 0xc5]
008b8aff 84c0                     test       al, al
008b8b01 740c                     je         0x8b8b0f
008b8b03 d84e27                   fmul       dword ptr [esi + 0x27]
008b8b06 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b8b0c d95508                   fst        dword ptr [ebp + 8]
008b8b0f 8b9695010000             mov        edx, dword ptr [esi + 0x195]
008b8b15 8bc2                     mov        eax, edx
008b8b17 2511010000               and        eax, 0x111
008b8b1c 3d11010000               cmp        eax, 0x111
008b8b21 7506                     jne        0x8b8b29
008b8b23 d84e6b                   fmul       dword ptr [esi + 0x6b]
008b8b26 d95508                   fst        dword ptr [ebp + 8]
008b8b29 d815581fcc00             fcom       dword ptr [0xcc1f58]
008b8b2f dfe0                     fnstsw     ax
008b8b31 f6c405                   test       ah, 5
008b8b34 7a0b                     jp         0x8b8b41
008b8b36 ddd8                     fstp       st(0)
008b8b38 d905581fcc00             fld        dword ptr [0xcc1f58]
008b8b3e d95508                   fst        dword ptr [ebp + 8]