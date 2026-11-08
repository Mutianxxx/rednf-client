008b79c0  55                       push       ebp
008b79c1  8bec                     mov        ebp, esp
008b79c3  51                       push       ecx
008b79c4  56                       push       esi
008b79c5  8b7508                   mov        esi, dword ptr [ebp + 8]
008b79c8  8a4604                   mov        al, byte ptr [esi + 4]
008b79cb  d906                     fld        dword ptr [esi]
008b79cd  84c0                     test       al, al
008b79cf  57                       push       edi
008b79d0  7417                     je         0x8b79e9
008b79d2  8a4605                   mov        al, byte ptr [esi + 5]
008b79d5  84c0                     test       al, al
008b79d7  740d                     je         0x8b79e6
008b79d9  3c02                     cmp        al, 2
008b79db  7409                     je         0x8b79e6
008b79dd  3c01                     cmp        al, 1
008b79df  7508                     jne        0x8b79e9
008b79e1  d84633                   fadd       dword ptr [esi + 0x33]
008b79e4  eb03                     jmp        0x8b79e9
008b79e6  d8462f                   fadd       dword ptr [esi + 0x2f]
008b79e9  d94606                   fld        dword ptr [esi + 6]
008b79ec  8a4605                   mov        al, byte ptr [esi + 5]
008b79ef  84c0                     test       al, al
008b79f1  d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b79f7  d805581fcc00             fadd       dword ptr [0xcc1f58]
008b79fd  d8c9                     fmul       st(1)
008b79ff  d95d08                   fstp       dword ptr [ebp + 8]
008b7a02  ddd8                     fstp       st(0)
008b7a04  7505                     jne        0x8b7a0b
008b7a06  d94637                   fld        dword ptr [esi + 0x37]
008b7a09  eb07                     jmp        0x8b7a12
008b7a0b  3c01                     cmp        al, 1
008b7a0d  7515                     jne        0x8b7a24
008b7a0f  d9463b                   fld        dword ptr [esi + 0x3b]
008b7a12  d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b7a18  d805581fcc00             fadd       dword ptr [0xcc1f58]
008b7a1e  d84d08                   fmul       dword ptr [ebp + 8]
008b7a21  d95d08                   fstp       dword ptr [ebp + 8]
008b7a24  84c0                     test       al, al
008b7a26  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
008b7a29  7527                     jne        0x8b7a52
008b7a2b  8b463f                   mov        eax, dword ptr [esi + 0x3f]
008b7a2e  8945fc                   mov        dword ptr [ebp - 4], eax
008b7a31  80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b7a38  7411                     je         0x8b7a4b
008b7a3a  6a03                     push       3
008b7a3c  57                       push       edi
008b7a3d  e8ce11b9ff               call       0x448c10
008b7a42  d84dfc                   fmul       dword ptr [ebp - 4]
008b7a45  83c408                   add        esp, 8
008b7a48  d95dfc                   fstp       dword ptr [ebp - 4]
008b7a4b  b9d8fe0b01               mov        ecx, 0x10bfed8
008b7a50  eb29                     jmp        0x8b7a7b
008b7a52  3c01                     cmp        al, 1
008b7a54  7539                     jne        0x8b7a8f
008b7a56  80be8a01000004           cmp        byte ptr [esi + 0x18a], 4
008b7a5d  8b4e43                   mov        ecx, dword ptr [esi + 0x43]
008b7a60  894dfc                   mov        dword ptr [ebp - 4], ecx
008b7a63  7411                     je         0x8b7a76
008b7a65  6a05                     push       5
008b7a67  57                       push       edi
008b7a68  e8a311b9ff               call       0x448c10
008b7a6d  d84dfc                   fmul       dword ptr [ebp - 4]
008b7a70  83c408                   add        esp, 8
008b7a73  d95dfc                   fstp       dword ptr [ebp - 4]
008b7a76  b978fe0b01               mov        ecx, 0x10bfe78
008b7a7b  e830b9b7ff               call       0x4333b0
008b7a80  d87dfc                   fdivr      dword ptr [ebp - 4]
008b7a83  d805581fcc00             fadd       dword ptr [0xcc1f58]
008b7a89  d84d08                   fmul       dword ptr [ebp + 8]
008b7a8c  d95d08                   fstp       dword ptr [ebp + 8]
008b7a8f  6a00                     push       0
008b7a91  57                       push       edi
008b7a92  e87911b9ff               call       0x448c10
008b7a97  d84d08                   fmul       dword ptr [ebp + 8]
008b7a9a  d94647                   fld        dword ptr [esi + 0x47]
008b7a9d  83c408                   add        esp, 8
008b7aa0  d805581fcc00             fadd       dword ptr [0xcc1f58]
008b7aa6  5f                       pop        edi
008b7aa7  5e                       pop        esi
008b7aa8  dec9                     fmulp      st(1)
008b7aaa  8be5                     mov        esp, ebp
008b7aac  5d                       pop        ebp
008b7aad  c3                       ret        
008b7aae  cc                       int3       
