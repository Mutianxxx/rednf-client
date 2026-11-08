004bb091 8b4304                   mov        eax, dword ptr [ebx + 4]
004bb094 db4004                   fild       dword ptr [eax + 4]
004bb097 8b4808                   mov        ecx, dword ptr [eax + 8]
004bb09a 8b38                     mov        edi, dword ptr [eax]
004bb09c 898ebc160000             mov        dword ptr [esi + 0x16bc], ecx
004bb0a2 d80dac10cc00             fmul       dword ptr [0xcc10ac]
004bb0a8 8b4304                   mov        eax, dword ptr [ebx + 4]
004bb0ab 33d2                     xor        edx, edx
004bb0ad 3bc2                     cmp        eax, edx
004bb0af d95ddc                   fstp       dword ptr [ebp - 0x24]
004bb0b2 89550c                   mov        dword ptr [ebp + 0xc], edx
004bb0b5 7413                     je         0x4bb0ca
004bb0b7 8b4b08                   mov        ecx, dword ptr [ebx + 8]
004bb0ba 2bc8                     sub        ecx, eax
004bb0bc c1f902                   sar        ecx, 2
004bb0bf 83f903                   cmp        ecx, 3
004bb0c2 7606                     jbe        0x4bb0ca
004bb0c4 8b480c                   mov        ecx, dword ptr [eax + 0xc]
004bb0c7 894d0c                   mov        dword ptr [ebp + 0xc], ecx
004bb0ca 3bc2                     cmp        eax, edx
004bb0cc 8955e0                   mov        dword ptr [ebp - 0x20], edx
004bb0cf 7413                     je         0x4bb0e4
004bb0d1 8b5b08                   mov        ebx, dword ptr [ebx + 8]
004bb0d4 2bd8                     sub        ebx, eax
004bb0d6 c1fb02                   sar        ebx, 2
004bb0d9 83fb04                   cmp        ebx, 4
004bb0dc 7606                     jbe        0x4bb0e4
004bb0de 8b5010                   mov        edx, dword ptr [eax + 0x10]
004bb0e1 8955e0                   mov        dword ptr [ebp - 0x20], edx
004bb0e4 33db                     xor        ebx, ebx
004bb0e6 53                       push       ebx
004bb0e7 68f49df500               push       0xf59df4
004bb0ec 686c52f500               push       0xf5526c
004bb0f1 53                       push       ebx
004bb0f2 56                       push       esi
004bb0f3 e8135c7400               call       0xc00d0b
004bb0f8 83c414                   add        esp, 0x14
004bb0fb 3bc3                     cmp        eax, ebx
004bb0fd 740a                     je         0x4bb109
004bb0ff 8a8870270000             mov        cl, byte ptr [eax + 0x2770]
004bb105 84c9                     test       cl, cl
004bb107 741c                     je         0x4bb125
004bb109 83ff04                   cmp        edi, 4
004bb10c 8bce                     mov        ecx, esi
004bb10e 750c                     jne        0x4bb11c
004bb110 8b06                     mov        eax, dword ptr [esi]
004bb112 ff90c0000000             call       dword ptr [eax + 0xc0]
004bb118 8bf8                     mov        edi, eax
004bb11a eb09                     jmp        0x4bb125
004bb11c 8b16                     mov        edx, dword ptr [esi]
004bb11e 57                       push       edi
004bb11f ff92b8000000             call       dword ptr [edx + 0xb8]
004bb125 8b550c                   mov        edx, dword ptr [ebp + 0xc]
004bb128 8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
004bb12b 8b06                     mov        eax, dword ptr [esi]
004bb12d 83fa02                   cmp        edx, 2
004bb130 0f94c2                   sete       dl
004bb133 51                       push       ecx
004bb134 8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
004bb137 895de8                   mov        dword ptr [ebp - 0x18], ebx
004bb13a 895de4                   mov        dword ptr [ebp - 0x1c], ebx
004bb13d 52                       push       edx
004bb13e 51                       push       ecx
004bb13f 8d55e4                   lea        edx, [ebp - 0x1c]
004bb142 52                       push       edx
004bb143 8d4de8                   lea        ecx, [ebp - 0x18]
004bb146 51                       push       ecx
004bb147 8bce                     mov        ecx, esi
004bb149 ff9018050000             call       dword ptr [eax + 0x518]
004bb14f 8d550c                   lea        edx, [ebp + 0xc]
004bb152 52                       push       edx
004bb153 8d8ec0160000             lea        ecx, [esi + 0x16c0]
004bb159 89450c                   mov        dword ptr [ebp + 0xc], eax
004bb15c e8ff93f4ff               call       0x404560
004bb161 8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
004bb164 8b16                     mov        edx, dword ptr [esi]
004bb166 6a01                     push       1
004bb168 50                       push       eax
004bb169 8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004bb16c 53                       push       ebx
004bb16d 50                       push       eax
004bb16e 50                       push       eax
004bb16f 53                       push       ebx
004bb170 8bce                     mov        ecx, esi
004bb172 ff9288040000             call       dword ptr [edx + 0x488]
004bb178 8b16                     mov        edx, dword ptr [esi]
004bb17a 53                       push       ebx
004bb17b 53                       push       ebx
004bb17c 53                       push       ebx
004bb17d 53                       push       ebx
004bb17e 53                       push       ebx
004bb17f 6a01                     push       1
004bb181 8bce                     mov        ecx, esi
004bb183 ff9288040000             call       dword ptr [edx + 0x488]
004bb189 8b06                     mov        eax, dword ptr [esi]
004bb18b 680000803f               push       0x3f800000
004bb190 680000803f               push       0x3f800000
004bb195 68e8030000               push       0x3e8
004bb19a 68e8030000               push       0x3e8
004bb19f 53                       push       ebx
004bb1a0 53                       push       ebx
004bb1a1 8bce                     mov        ecx, esi
004bb1a3 ff9094040000             call       dword ptr [eax + 0x494]
004bb1a9 8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004bb1af 53                       push       ebx
004bb1b0 6a02                     push       2
004bb1b2 e8895e0500               call       0x511040
004bb1b7 8b06                     mov        eax, dword ptr [esi]
004bb1b9 53                       push       ebx
004bb1ba 6a04                     push       4
004bb1bc 57                       push       edi
004bb1bd 89450c                   mov        dword ptr [ebp + 0xc], eax
004bb1c0 e89bc7f8ff               call       0x447960
004bb1c5 83c404                   add        esp, 4
004bb1c8 50                       push       eax
004bb1c9 8b450c                   mov        eax, dword ptr [ebp + 0xc]
004bb1cc 8bce                     mov        ecx, esi
004bb1ce ff909c040000             call       dword ptr [eax + 0x49c]
004bb1d4 53                       push       ebx
004bb1d5 6a02                     push       2
004bb1d7 8bce                     mov        ecx, esi
004bb1d9 e8e2eeffff               call       0x4ba0c0
004bb1de 8b86bc160000             mov        eax, dword ptr [esi + 0x16bc]
004bb1e4 8b16                     mov        edx, dword ptr [esi]
004bb1e6 50                       push       eax
004bb1e7 8bce                     mov        ecx, esi
004bb1e9 ff9274030000             call       dword ptr [edx + 0x374]
004bb1ef 85c0                     test       eax, eax
004bb1f1 0f844e140000             je         0x4bc645
004bb1f7 8b8ebc160000             mov        ecx, dword ptr [esi + 0x16bc]
004bb1fd 8b3e                     mov        edi, dword ptr [esi]
004bb1ff 51                       push       ecx
004bb200 8bce                     mov        ecx, esi
