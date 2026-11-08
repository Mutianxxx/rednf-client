008b8650 55                       push      ebp
008b8651 8bec                     mov       ebp, esp
008b8653 83ec0c                   sub       esp, 0xc
008b8656 53                       push      ebx
008b8657 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
008b865a 56                       push      esi
008b865b 8b7508                   mov       esi, dword ptr [ebp + 8]
008b865e 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
008b8664 57                       push      edi
008b8665 53                       push      ebx
008b8666 56                       push      esi
008b8667 8945f8                   mov       dword ptr [ebp - 8], eax
008b866a e881ffffff               call      0x8b85f0
008b866f d95d08                   fstp      dword ptr [ebp + 8]
008b8672 8a86b4010000             mov       al, byte ptr [esi + 0x1b4]
008b8678 83c408                   add       esp, 8
008b867b 3c04                     cmp       al, 4
008b867d 741d                     je        0x8b869c
008b867f 0fbec8                   movsx     ecx, al
008b8682 51                       push      ecx
008b8683 56                       push      esi
008b8684 e8e7f2ffff               call      0x8b7970
008b8689 83c408                   add       esp, 8
008b868c 84c0                     test      al, al
008b868e 740c                     je        0x8b869c
008b8690 d94508                   fld       dword ptr [ebp + 8]
008b8693 d80d60f3e200             fmul      dword ptr [0xe2f360]
008b8699 d95d08                   fstp      dword ptr [ebp + 8]
008b869c 8b9699010000             mov       edx, dword ptr [esi + 0x199]
008b86a2 83e211                   and       edx, 0x11
008b86a5 80fa11                   cmp       dl, 0x11
008b86a8 7576                     jne       0x8b8720
008b86aa 8a460a                   mov       al, byte ptr [esi + 0xa]
008b86ad 84c0                     test      al, al
008b86af 7515                     jne       0x8b86c6
008b86b1 8a460b                   mov       al, byte ptr [esi + 0xb]
008b86b4 84c0                     test      al, al
008b86b6 750e                     jne       0x8b86c6
008b86b8 8a460c                   mov       al, byte ptr [esi + 0xc]
008b86bb 84c0                     test      al, al
008b86bd 7507                     jne       0x8b86c6
008b86bf 8a460d                   mov       al, byte ptr [esi + 0xd]
008b86c2 84c0                     test      al, al
008b86c4 745a                     je        0x8b8720
008b86c6 c745fc000080bf           mov       dword ptr [ebp - 4], 0xbf800000
008b86cd 33ff                     xor       edi, edi
008b86cf 8d5e77                   lea       ebx, [esi + 0x77]
008b86d2 8a443e0a                 mov       al, byte ptr [esi + edi + 0xa]
008b86d6 84c0                     test      al, al
008b86d8 7434                     je        0x8b870e
008b86da 8b03                     mov       eax, dword ptr [ebx]
008b86dc b9f0fe0b01               mov       ecx, 0x10bfef0
008b86e1 8945f4                   mov       dword ptr [ebp - 0xc], eax
008b86e4 e8c7acb7ff               call      0x4333b0
008b86e9 db45f4                   fild      dword ptr [ebp - 0xc]
008b86ec d88e87000000             fmul      dword ptr [esi + 0x87]
008b86f2 dee9                     fsubp     st(1)
008b86f4 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b86fa d84d08                   fmul      dword ptr [ebp + 8]
008b86fd d855fc                   fcom      dword ptr [ebp - 4]
008b8700 dfe0                     fnstsw    ax
008b8702 f6c441                   test      ah, 0x41
008b8705 7505                     jne       0x8b870c
008b8707 d95dfc                   fstp      dword ptr [ebp - 4]
008b870a eb02                     jmp       0x8b870e
008b870c ddd8                     fstp      st(0)
008b870e 47                       inc       edi
008b870f 83c304                   add       ebx, 4
008b8712 83ff04                   cmp       edi, 4
008b8715 7cbb                     jl        0x8b86d2
008b8717 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
008b871a 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
008b871d 894d08                   mov       dword ptr [ebp + 8], ecx
008b8720 8a4605                   mov       al, byte ptr [esi + 5]
008b8723 84c0                     test      al, al
008b8725 c7451000000000           mov       dword ptr [ebp + 0x10], 0
008b872c 7534                     jne       0x8b8762
008b872e b9a0fe0b01               mov       ecx, 0x10bfea0
008b8733 e878acb7ff               call      0x4333b0
008b8738 d95d10                   fstp      dword ptr [ebp + 0x10]
008b873b 8a4604                   mov       al, byte ptr [esi + 4]
008b873e 84c0                     test      al, al
008b8740 0f95c2                   setne     dl
008b8743 52                       push      edx
008b8744 56                       push      esi
008b8745 e8a6f4ffff               call      0x8b7bf0
008b874a 83c408                   add       esp, 8
008b874d b998fe0b01               mov       ecx, 0x10bfe98
008b8752 8945f4                   mov       dword ptr [ebp - 0xc], eax
008b8755 e856acb7ff               call      0x4333b0
008b875a da4df4                   fimul     dword ptr [ebp - 0xc]
008b875d d84510                   fadd      dword ptr [ebp + 0x10]
008b8760 eb45                     jmp       0x8b87a7
008b8762 3c01                     cmp       al, 1
008b8764 7534                     jne       0x8b879a
008b8766 b9c0fe0b01               mov       ecx, 0x10bfec0
008b876b e840acb7ff               call      0x4333b0
008b8770 d95d10                   fstp      dword ptr [ebp + 0x10]
008b8773 8a4604                   mov       al, byte ptr [esi + 4]
008b8776 84c0                     test      al, al
008b8778 0f95c0                   setne     al
008b877b 50                       push      eax
008b877c 56                       push      esi
008b877d e86ef4ffff               call      0x8b7bf0
008b8782 83c408                   add       esp, 8
008b8785 b9e8fe0b01               mov       ecx, 0x10bfee8
008b878a 8945f4                   mov       dword ptr [ebp - 0xc], eax
008b878d e81eacb7ff               call      0x4333b0
008b8792 da4df4                   fimul     dword ptr [ebp - 0xc]
008b8795 d84510                   fadd      dword ptr [ebp + 0x10]
008b8798 eb0d                     jmp       0x8b87a7
008b879a 3c02                     cmp       al, 2
008b879c 750c                     jne       0x8b87aa
008b879e d94508                   fld       dword ptr [ebp + 8]
008b87a1 d80d5cf3e200             fmul      dword ptr [0xe2f35c]
008b87a7 d95d10                   fstp      dword ptr [ebp + 0x10]
008b87aa b98c590001               mov       ecx, 0x100598c
008b87af e8ac98b4ff               call      0x402060
008b87b4 85c0                     test      eax, eax
008b87b6 7407                     je        0x8b87bf
008b87b8 c7451000000000           mov       dword ptr [ebp + 0x10], 0
008b87bf 8d4df8                   lea       ecx, [ebp - 8]
008b87c2 68e7030000               push      0x3e7
008b87c7 51                       push      ecx
008b87c8 e89359ffff               call      0x8ae160
008b87cd d94510                   fld       dword ptr [ebp + 0x10]
008b87d0 99                       cdq       
008b87d1 d9e0                     fchs      
008b87d3 b9e8030000               mov       ecx, 0x3e8
008b87d8 f7f9                     idiv      ecx
008b87da 83c404                   add       esp, 4
008b87dd 52                       push      edx
008b87de 8b5510                   mov       edx, dword ptr [ebp + 0x10]
008b87e1 52                       push      edx
008b87e2 51                       push      ecx
008b87e3 d91c24                   fstp      dword ptr [esp]
008b87e6 e8c554ffff               call      0x8adcb0
008b87eb 8b8699010000             mov       eax, dword ptr [esi + 0x199]
008b87f1 d84508                   fadd      dword ptr [ebp + 8]
008b87f4 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
008b87f7 83e011                   and       eax, 0x11
008b87fa 83c410                   add       esp, 0x10
008b87fd d95d08                   fstp      dword ptr [ebp + 8]
008b8800 3c11                     cmp       al, 0x11
008b8802 0f85b7000000             jne       0x8b88bf
008b8808 807e0502                 cmp       byte ptr [esi + 5], 2
008b880c 0f84ad000000             je        0x8b88bf
008b8812 8a460e                   mov       al, byte ptr [esi + 0xe]
008b8815 84c0                     test      al, al
008b8817 0f85a2000000             jne       0x8b88bf
008b881d 57                       push      edi
008b881e 56                       push      esi
008b881f 8d4dfc                   lea       ecx, [ebp - 4]
008b8822 51                       push      ecx
008b8823 8d5510                   lea       edx, [ebp + 0x10]
008b8826 52                       push      edx
008b8827 c7451000000000           mov       dword ptr [ebp + 0x10], 0
008b882e c745fc00000000           mov       dword ptr [ebp - 4], 0
008b8835 e856f4ffff               call      0x8b7c90
008b883a d905581fcc00             fld       dword ptr [0xcc1f58]
008b8840 d86510                   fsub      dword ptr [ebp + 0x10]
008b8843 8a4605                   mov       al, byte ptr [esi + 5]
008b8846 d945fc                   fld       dword ptr [ebp - 4]
008b8849 83c410                   add       esp, 0x10
008b884c 84c0                     test      al, al
008b884e d84e5f                   fmul      dword ptr [esi + 0x5f]
008b8851 dee9                     fsubp     st(1)
008b8853 d84d08                   fmul      dword ptr [ebp + 8]
008b8856 d95d08                   fstp      dword ptr [ebp + 8]
008b8859 752a                     jne       0x8b8885
008b885b 8b86a3000000             mov       eax, dword ptr [esi + 0xa3]
008b8861 894510                   mov       dword ptr [ebp + 0x10], eax
008b8864 80be8a01000004           cmp       byte ptr [esi + 0x18a], 4
008b886b 7411                     je        0x8b887e
008b886d 6a04                     push      4
008b886f 57                       push      edi
008b8870 e89b03b9ff               call      0x448c10
008b8875 d84d10                   fmul      dword ptr [ebp + 0x10]
008b8878 83c408                   add       esp, 8
008b887b d95d10                   fstp      dword ptr [ebp + 0x10]
008b887e b9a8fe0b01               mov       ecx, 0x10bfea8
008b8883 eb2c                     jmp       0x8b88b1
008b8885 3c01                     cmp       al, 1
008b8887 7536                     jne       0x8b88bf
008b8889 80be8a01000004           cmp       byte ptr [esi + 0x18a], 4
008b8890 8b8ea7000000             mov       ecx, dword ptr [esi + 0xa7]
008b8896 894d10                   mov       dword ptr [ebp + 0x10], ecx
008b8899 7411                     je        0x8b88ac
008b889b 6a06                     push      6
008b889d 57                       push      edi
008b889e e86d03b9ff               call      0x448c10
008b88a3 d84d10                   fmul      dword ptr [ebp + 0x10]
008b88a6 83c408                   add       esp, 8
008b88a9 d95d10                   fstp      dword ptr [ebp + 0x10]
008b88ac b9b8fe0b01               mov       ecx, 0x10bfeb8
008b88b1 e8faaab7ff               call      0x4333b0
008b88b6 d87d10                   fdivr     dword ptr [ebp + 0x10]
008b88b9 d86d08                   fsubr     dword ptr [ebp + 8]
008b88bc d95d08                   fstp      dword ptr [ebp + 8]
008b88bf 8a4605                   mov       al, byte ptr [esi + 5]
008b88c2 84c0                     test      al, al
008b88c4 7527                     jne       0x8b88ed
008b88c6 80be8a01000004           cmp       byte ptr [esi + 0x18a], 4
008b88cd 8b563f                   mov       edx, dword ptr [esi + 0x3f]
008b88d0 895510                   mov       dword ptr [ebp + 0x10], edx
008b88d3 7411                     je        0x8b88e6
008b88d5 6a03                     push      3
008b88d7 53                       push      ebx
008b88d8 e83303b9ff               call      0x448c10
008b88dd d84d10                   fmul      dword ptr [ebp + 0x10]
008b88e0 83c408                   add       esp, 8
008b88e3 d95d10                   fstp      dword ptr [ebp + 0x10]
008b88e6 b9e0fe0b01               mov       ecx, 0x10bfee0
008b88eb eb3f                     jmp       0x8b892c
008b88ed 3c01                     cmp       al, 1
008b88ef 7549                     jne       0x8b893a
008b88f1 8b4643                   mov       eax, dword ptr [esi + 0x43]
008b88f4 894510                   mov       dword ptr [ebp + 0x10], eax
008b88f7 80be8a01000004           cmp       byte ptr [esi + 0x18a], 4
008b88fe 7411                     je        0x8b8911
008b8900 6a05                     push      5
008b8902 53                       push      ebx
008b8903 e80803b9ff               call      0x448c10
008b8908 d84d10                   fmul      dword ptr [ebp + 0x10]
008b890b 83c408                   add       esp, 8
008b890e d95d10                   fstp      dword ptr [ebp + 0x10]
008b8911 8a86c1010000             mov       al, byte ptr [esi + 0x1c1]
008b8917 84c0                     test      al, al
008b8919 740c                     je        0x8b8927
008b891b 81bec2010000b2b30000     cmp       dword ptr [esi + 0x1c2], 0xb3b2
008b8925 7413                     je        0x8b893a
008b8927 b980fe0b01               mov       ecx, 0x10bfe80
008b892c e87faab7ff               call      0x4333b0
008b8931 d87d10                   fdivr     dword ptr [ebp + 0x10]
008b8934 d84508                   fadd      dword ptr [ebp + 8]
008b8937 d95d08                   fstp      dword ptr [ebp + 8]
008b893a 8a4605                   mov       al, byte ptr [esi + 5]
008b893d 84c0                     test      al, al
008b893f 0f8580000000             jne       0x8b89c5
008b8945 8a4604                   mov       al, byte ptr [esi + 4]
008b8948 d9460f                   fld       dword ptr [esi + 0xf]
008b894b 84c0                     test      al, al
008b894d 740b                     je        0x8b895a
008b894f db4663                   fild      dword ptr [esi + 0x63]
008b8952 d88eab000000             fmul      dword ptr [esi + 0xab]
008b8958 dec1                     faddp     st(1)
008b895a d94606                   fld       dword ptr [esi + 6]
008b895d 6a07                     push      7
008b895f d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8965 53                       push      ebx
008b8966 d805581fcc00             fadd      dword ptr [0xcc1f58]
008b896c d8c9                     fmul      st(1)
008b896e d94637                   fld       dword ptr [esi + 0x37]
008b8971 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8977 d805581fcc00             fadd      dword ptr [0xcc1f58]
008b897d dec9                     fmulp     st(1)
008b897f d95d10                   fstp      dword ptr [ebp + 0x10]
008b8982 ddd8                     fstp      st(0)
008b8984 e88702b9ff               call      0x448c10
008b8989 d84d10                   fmul      dword ptr [ebp + 0x10]
008b898c 8b8e99010000             mov       ecx, dword ptr [esi + 0x199]
008b8992 83e111                   and       ecx, 0x11
008b8995 83c408                   add       esp, 8
008b8998 80f911                   cmp       cl, 0x11
008b899b d84508                   fadd      dword ptr [ebp + 8]
008b899e d95d08                   fstp      dword ptr [ebp + 8]
008b89a1 0f85b0000000             jne       0x8b8a57
008b89a7 8a460e                   mov       al, byte ptr [esi + 0xe]
008b89aa 84c0                     test      al, al
008b89ac 0f85a5000000             jne       0x8b8a57
008b89b2 db86af000000             fild      dword ptr [esi + 0xaf]
008b89b8 6a08                     push      8
008b89ba d84e5f                   fmul      dword ptr [esi + 0x5f]
008b89bd da86b7000000             fiadd     dword ptr [esi + 0xb7]
008b89c3 eb7d                     jmp       0x8b8a42
008b89c5 3c01                     cmp       al, 1
008b89c7 0f8595000000             jne       0x8b8a62
008b89cd 8a4604                   mov       al, byte ptr [esi + 4]
008b89d0 d9460f                   fld       dword ptr [esi + 0xf]
008b89d3 84c0                     test      al, al
008b89d5 740b                     je        0x8b89e2
008b89d7 db4667                   fild      dword ptr [esi + 0x67]
008b89da d88eab000000             fmul      dword ptr [esi + 0xab]
008b89e0 dec1                     faddp     st(1)
008b89e2 d94606                   fld       dword ptr [esi + 6]
008b89e5 6a09                     push      9
008b89e7 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b89ed 53                       push      ebx
008b89ee d805581fcc00             fadd      dword ptr [0xcc1f58]
008b89f4 d8c9                     fmul      st(1)
008b89f6 d9463b                   fld       dword ptr [esi + 0x3b]
008b89f9 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b89ff d805581fcc00             fadd      dword ptr [0xcc1f58]
008b8a05 dec9                     fmulp     st(1)
008b8a07 d95d10                   fstp      dword ptr [ebp + 0x10]
008b8a0a ddd8                     fstp      st(0)
008b8a0c e8ff01b9ff               call      0x448c10
008b8a11 d84d10                   fmul      dword ptr [ebp + 0x10]
008b8a14 8b8699010000             mov       eax, dword ptr [esi + 0x199]
008b8a1a 83e011                   and       eax, 0x11
008b8a1d 83c408                   add       esp, 8
008b8a20 3c11                     cmp       al, 0x11
008b8a22 d84508                   fadd      dword ptr [ebp + 8]
008b8a25 d95d08                   fstp      dword ptr [ebp + 8]
008b8a28 752d                     jne       0x8b8a57
008b8a2a 8a460e                   mov       al, byte ptr [esi + 0xe]
008b8a2d 84c0                     test      al, al
008b8a2f 7526                     jne       0x8b8a57
008b8a31 db86b3000000             fild      dword ptr [esi + 0xb3]
008b8a37 6a0a                     push      0xa
008b8a39 d84e5f                   fmul      dword ptr [esi + 0x5f]
008b8a3c da86bb000000             fiadd     dword ptr [esi + 0xbb]
008b8a42 57                       push      edi
008b8a43 d95d10                   fstp      dword ptr [ebp + 0x10]
008b8a46 e8c501b9ff               call      0x448c10
008b8a4b d84d10                   fmul      dword ptr [ebp + 0x10]
008b8a4e 83c408                   add       esp, 8
008b8a51 d86d08                   fsubr     dword ptr [ebp + 8]
008b8a54 d95d08                   fstp      dword ptr [ebp + 8]
008b8a57 8b17                     mov       edx, dword ptr [edi]
008b8a59 8bcf                     mov       ecx, edi
008b8a5b 53                       push      ebx
008b8a5c ff9220030000             call      dword ptr [edx + 0x320]
008b8a62 d94508                   fld       dword ptr [ebp + 8]
008b8a65 d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
008b8a6b dfe0                     fnstsw    ax
008b8a6d f6c405                   test      ah, 5
008b8a70 7a07                     jp        0x8b8a79
008b8a72 c7450800000000           mov       dword ptr [ebp + 8], 0
008b8a79 8d45f8                   lea       eax, [ebp - 8]
008b8a7c 50                       push      eax
008b8a7d 8d4d08                   lea       ecx, [ebp + 8]
008b8a80 51                       push      ecx
008b8a81 56                       push      esi
008b8a82 e829f0ffff               call      0x8b7ab0
008b8a87 d94508                   fld       dword ptr [ebp + 8]
008b8a8a 8ad8                     mov       bl, al
008b8a8c 8a86a6010000             mov       al, byte ptr [esi + 0x1a6]
008b8a92 83c40c                   add       esp, 0xc
008b8a95 84c0                     test      al, al
008b8a97 889ea5010000             mov       byte ptr [esi + 0x1a5], bl
008b8a9d 7416                     je        0x8b8ab5
008b8a9f d80d9051df00             fmul      dword ptr [0xdf5190]
008b8aa5 d94508                   fld       dword ptr [ebp + 8]
008b8aa8 d8e9                     fsubr     st(1)
008b8aaa e8958a3400               call      0xc01544
008b8aaf 8986a7010000             mov       dword ptr [esi + 0x1a7], eax
008b8ab5 d84e1b                   fmul      dword ptr [esi + 0x1b]
008b8ab8 8a86c3000000             mov       al, byte ptr [esi + 0xc3]
008b8abe 84c0                     test      al, al
008b8ac0 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8ac6 da8eac010000             fimul     dword ptr [esi + 0x1ac]
008b8acc d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8ad2 d95508                   fst       dword ptr [ebp + 8]
008b8ad5 740c                     je        0x8b8ae3
008b8ad7 d84e1f                   fmul      dword ptr [esi + 0x1f]
008b8ada d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8ae0 d95508                   fst       dword ptr [ebp + 8]
008b8ae3 8a86c4000000             mov       al, byte ptr [esi + 0xc4]
008b8ae9 84c0                     test      al, al
008b8aeb 740c                     je        0x8b8af9
008b8aed d84e23                   fmul      dword ptr [esi + 0x23]
008b8af0 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8af6 d95508                   fst       dword ptr [ebp + 8]
008b8af9 8a86c5000000             mov       al, byte ptr [esi + 0xc5]
008b8aff 84c0                     test      al, al
008b8b01 740c                     je        0x8b8b0f
008b8b03 d84e27                   fmul      dword ptr [esi + 0x27]
008b8b06 d80dac10cc00             fmul      dword ptr [0xcc10ac]
008b8b0c d95508                   fst       dword ptr [ebp + 8]
008b8b0f 8b9695010000             mov       edx, dword ptr [esi + 0x195]
008b8b15 8bc2                     mov       eax, edx
008b8b17 2511010000               and       eax, 0x111
008b8b1c 3d11010000               cmp       eax, 0x111
008b8b21 7506                     jne       0x8b8b29
008b8b23 d84e6b                   fmul      dword ptr [esi + 0x6b]
008b8b26 d95508                   fst       dword ptr [ebp + 8]
008b8b29 d815581fcc00             fcom      dword ptr [0xcc1f58]
008b8b2f dfe0                     fnstsw    ax
008b8b31 f6c405                   test      ah, 5
008b8b34 7a0b                     jp        0x8b8b41
008b8b36 ddd8                     fstp      st(0)
008b8b38 d905581fcc00             fld       dword ptr [0xcc1f58]
008b8b3e d95508                   fst       dword ptr [ebp + 8]
008b8b41 8b8e9d010000             mov       ecx, dword ptr [esi + 0x19d]
008b8b47 81e111010000             and       ecx, 0x111
008b8b4d 81f911010000             cmp       ecx, 0x111
008b8b53 7566                     jne       0x8b8bbb
008b8b55 33c0                     xor       eax, eax
008b8b57 84db                     test      bl, bl
008b8b59 0f95c0                   setne     al
008b8b5c b902000000               mov       ecx, 2
008b8b61 6bc05c                   imul      eax, eax, 0x5c
008b8b64 8d8430ca000000           lea       eax, [eax + esi + 0xca]
008b8b6b eb03                     jmp       0x8b8b70
008b8b6d 8d4900                   lea       ecx, [ecx]
008b8b70 d848fc                   fmul      dword ptr [eax - 4]
008b8b73 83c020                   add       eax, 0x20
008b8b76 49                       dec       ecx
008b8b77 d848e0                   fmul      dword ptr [eax - 0x20]
008b8b7a d848e4                   fmul      dword ptr [eax - 0x1c]
008b8b7d d848e8                   fmul      dword ptr [eax - 0x18]
008b8b80 d848ec                   fmul      dword ptr [eax - 0x14]
008b8b83 d848f0                   fmul      dword ptr [eax - 0x10]
008b8b86 d848f4                   fmul      dword ptr [eax - 0xc]
008b8b89 d848f8                   fmul      dword ptr [eax - 8]
008b8b8c 75e2                     jne       0x8b8b70
008b8b8e 8a86a5010000             mov       al, byte ptr [esi + 0x1a5]
008b8b94 33c9                     xor       ecx, ecx
008b8b96 84c0                     test      al, al
008b8b98 0f95c1                   setne     cl
008b8b9b 6bc95c                   imul      ecx, ecx, 0x5c
008b8b9e 8d843106010000           lea       eax, [ecx + esi + 0x106]
008b8ba5 b907000000               mov       ecx, 7
008b8baa 8d9b00000000             lea       ebx, [ebx]
008b8bb0 d808                     fmul      dword ptr [eax]
008b8bb2 83c004                   add       eax, 4
008b8bb5 49                       dec       ecx
008b8bb6 75f8                     jne       0x8b8bb0
008b8bb8 d95508                   fst       dword ptr [ebp + 8]
008b8bbb 83e211                   and       edx, 0x11
008b8bbe 80fa11                   cmp       dl, 0x11
008b8bc1 750f                     jne       0x8b8bd2
008b8bc3 817e730000803f           cmp       dword ptr [esi + 0x73], 0x3f800000
008b8bca 7406                     je        0x8b8bd2
008b8bcc d84e73                   fmul      dword ptr [esi + 0x73]
008b8bcf d95508                   fst       dword ptr [ebp + 8]
008b8bd2 8b1d48280001             mov       ebx, dword ptr [0x1002848]
008b8bd8 8b9340100000             mov       edx, dword ptr [ebx + 0x1040]
008b8bde 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
008b8be4 8b8344100000             mov       eax, dword ptr [ebx + 0x1044]
008b8bea 81c340100000             add       ebx, 0x1040
008b8bf0 33d7                     xor       edx, edi
008b8bf2 2bd3                     sub       edx, ebx
008b8bf4 3bd0                     cmp       edx, eax
008b8bf6 7413                     je        0x8b8c0b
008b8bf8 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
008b8bfe ddd8                     fstp      st(0)
008b8c00 6a3f                     push      0x3f
008b8c02 53                       push      ebx
008b8c03 e8a8e42500               call      0xb170b0
008b8c08 d94508                   fld       dword ptr [ebp + 8]
008b8c0b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
008b8c11 8b4304                   mov       eax, dword ptr [ebx + 4]
008b8c14 8b5144                   mov       edx, dword ptr [ecx + 0x44]
008b8c17 c1e002                   shl       eax, 2
008b8c1a 03d0                     add       edx, eax
008b8c1c 8bfa                     mov       edi, edx
008b8c1e 333ddc012101             xor       edi, dword ptr [0x12101dc]
008b8c24 333a                     xor       edi, dword ptr [edx]
008b8c26 8b5148                   mov       edx, dword ptr [ecx + 0x48]
008b8c29 03c2                     add       eax, edx
008b8c2b 8bd0                     mov       edx, eax
008b8c2d 3315dc012101             xor       edx, dword ptr [0x12101dc]
008b8c33 3310                     xor       edx, dword ptr [eax]
008b8c35 3bfa                     cmp       edi, edx
008b8c37 740d                     je        0x8b8c46
008b8c39 6a40                     push      0x40
008b8c3b ddd8                     fstp      st(0)
008b8c3d 53                       push      ebx
008b8c3e e86de42500               call      0xb170b0
008b8c43 d94508                   fld       dword ptr [ebp + 8]
008b8c46 83ff04                   cmp       edi, 4
008b8c49 0f85f5010000             jne       0x8b8e44
008b8c4f 8b                       .byte     0x8b
