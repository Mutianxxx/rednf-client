004a0840 55                       push      ebp
004a0841 8bec                     mov       ebp, esp
004a0843 6aff                     push      -1
004a0845 68036cc500               push      0xc56c03
004a084a 64a100000000             mov       eax, dword ptr fs:[0]
004a0850 50                       push      eax
004a0851 64892500000000           mov       dword ptr fs:[0], esp
004a0858 83ec14                   sub       esp, 0x14
004a085b 53                       push      ebx
004a085c 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a085f 56                       push      esi
004a0860 8bf1                     mov       esi, ecx
004a0862 3bde                     cmp       ebx, esi
004a0864 57                       push      edi
004a0865 0f853b010000             jne       0x4a09a6
004a086b 68e0baca00               push      0xcabae0
004a0870 8dbef4070000             lea       edi, [esi + 0x7f4]
004a0876 e852f57500               call      0xbffdcd
004a087b 83c404                   add       esp, 4
004a087e 50                       push      eax
004a087f 8b4714                   mov       eax, dword ptr [edi + 0x14]
004a0882 68e0baca00               push      0xcabae0
004a0887 50                       push      eax
004a0888 6a00                     push      0
004a088a 8bcf                     mov       ecx, edi
004a088c e85f37f6ff               call      0x403ff0
004a0891 85c0                     test      eax, eax
004a0893 0f840d010000             je        0x4a09a6
004a0899 68e0020000               push      0x2e0
004a089e e8ad33f6ff               call      0x403c50
004a08a3 83c404                   add       esp, 4
004a08a6 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a08a9 85c0                     test      eax, eax
004a08ab c745fc00000000           mov       dword ptr [ebp - 4], 0
004a08b2 7446                     je        0x4a08fa
004a08b4 8b5718                   mov       edx, dword ptr [edi + 0x18]
004a08b7 b908000000               mov       ecx, 8
004a08bc 3bd1                     cmp       edx, ecx
004a08be 7205                     jb        0x4a08c5
004a08c0 8b7f04                   mov       edi, dword ptr [edi + 4]
004a08c3 eb03                     jmp       0x4a08c8
004a08c5 83c704                   add       edi, 4
004a08c8 398e5c020000             cmp       dword ptr [esi + 0x25c], ecx
004a08ce 7215                     jb        0x4a08e5
004a08d0 8b9648020000             mov       edx, dword ptr [esi + 0x248]
004a08d6 6a00                     push      0
004a08d8 57                       push      edi
004a08d9 52                       push      edx
004a08da 8bc8                     mov       ecx, eax
004a08dc e81f300000               call      0x4a3900
004a08e1 8bf8                     mov       edi, eax
004a08e3 eb17                     jmp       0x4a08fc
004a08e5 6a00                     push      0
004a08e7 8d9648020000             lea       edx, [esi + 0x248]
004a08ed 57                       push      edi
004a08ee 52                       push      edx
004a08ef 8bc8                     mov       ecx, eax
004a08f1 e80a300000               call      0x4a3900
004a08f6 8bf8                     mov       edi, eax
004a08f8 eb02                     jmp       0x4a08fc
004a08fa 33ff                     xor       edi, edi
004a08fc 56                       push      esi
004a08fd 8bcf                     mov       ecx, edi
004a08ff c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a0906 e815c75800               call      0xa2d020
004a090b 85ff                     test      edi, edi
004a090d 0f8493000000             je        0x4a09a6
004a0913 6870080000               push      0x870
004a0918 e83333f6ff               call      0x403c50
004a091d 83c404                   add       esp, 4
004a0920 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a0923 85c0                     test      eax, eax
004a0925 c745fc01000000           mov       dword ptr [ebp - 4], 1
004a092c 7410                     je        0x4a093e
004a092e 6a00                     push      0
004a0930 6a01                     push      1
004a0932 57                       push      edi
004a0933 8bc8                     mov       ecx, eax
004a0935 e8e62e0000               call      0x4a3820
004a093a 8bf8                     mov       edi, eax
004a093c eb02                     jmp       0x4a0940
004a093e 33ff                     xor       edi, edi
004a0940 8b16                     mov       edx, dword ptr [esi]
004a0942 6a00                     push      0
004a0944 6a00                     push      0
004a0946 56                       push      esi
004a0947 57                       push      edi
004a0948 8bce                     mov       ecx, esi
004a094a c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a0951 ff5240                   call      dword ptr [edx + 0x40]
004a0954 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a095a 50                       push      eax
004a095b 6a21                     push      0x21
004a095d 56                       push      esi
004a095e e80dd40600               call      0x50dd70
004a0963 8b06                     mov       eax, dword ptr [esi]
004a0965 8b1f                     mov       ebx, dword ptr [edi]
004a0967 8bce                     mov       ecx, esi
004a0969 ff909c000000             call      dword ptr [eax + 0x9c]
004a096f 8b16                     mov       edx, dword ptr [esi]
004a0971 50                       push      eax
004a0972 8bce                     mov       ecx, esi
004a0974 ff9298000000             call      dword ptr [edx + 0x98]
004a097a 50                       push      eax
004a097b 8b06                     mov       eax, dword ptr [esi]
004a097d 8bce                     mov       ecx, esi
004a097f ff9094000000             call      dword ptr [eax + 0x94]
004a0985 50                       push      eax
004a0986 8bcf                     mov       ecx, edi
004a0988 ff9388000000             call      dword ptr [ebx + 0x88]
004a098e 8b16                     mov       edx, dword ptr [esi]
004a0990 8b1f                     mov       ebx, dword ptr [edi]
004a0992 8bce                     mov       ecx, esi
004a0994 ff92c0000000             call      dword ptr [edx + 0xc0]
004a099a 50                       push      eax
004a099b 8bcf                     mov       ecx, edi
004a099d ff93b8000000             call      dword ptr [ebx + 0xb8]
004a09a3 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a09a6 53                       push      ebx
004a09a7 8bce                     mov       ecx, esi
004a09a9 e862d30400               call      0x4edd10
004a09ae 3b9e30050000             cmp       ebx, dword ptr [esi + 0x530]
004a09b4 7530                     jne       0x4a09e6
004a09b6 8b03                     mov       eax, dword ptr [ebx]
004a09b8 6a21                     push      0x21
004a09ba 8bcb                     mov       ecx, ebx
004a09bc ff502c                   call      dword ptr [eax + 0x2c]
004a09bf 84c0                     test      al, al
004a09c1 7417                     je        0x4a09da
004a09c3 8b13                     mov       edx, dword ptr [ebx]
004a09c5 8b3e                     mov       edi, dword ptr [esi]
004a09c7 8bcb                     mov       ecx, ebx
004a09c9 ff928c010000             call      dword ptr [edx + 0x18c]
004a09cf 50                       push      eax
004a09d0 8bce                     mov       ecx, esi
004a09d2 ff9744030000             call      dword ptr [edi + 0x344]
004a09d8 eb0c                     jmp       0x4a09e6
004a09da 8b06                     mov       eax, dword ptr [esi]
004a09dc 6a00                     push      0
004a09de 8bce                     mov       ecx, esi
004a09e0 ff9044030000             call      dword ptr [eax + 0x344]
004a09e6 3b9e34050000             cmp       ebx, dword ptr [esi + 0x534]
004a09ec 750a                     jne       0x4a09f8
004a09ee c7863405000000000000     mov       dword ptr [esi + 0x534], 0
004a09f8 3bde                     cmp       ebx, esi
004a09fa 0f85d8010000             jne       0x4a0bd8
004a0a00 8b8e94070000             mov       ecx, dword ptr [esi + 0x794]
004a0a06 85c9                     test      ecx, ecx
004a0a08 747c                     je        0x4a0a86
004a0a0a 8b11                     mov       edx, dword ptr [ecx]
004a0a0c 6a00                     push      0
004a0a0e ff520c                   call      dword ptr [edx + 0xc]
004a0a11 8b8694070000             mov       eax, dword ptr [esi + 0x794]
004a0a17 8b16                     mov       edx, dword ptr [esi]
004a0a19 8b38                     mov       edi, dword ptr [eax]
004a0a1b 8bce                     mov       ecx, esi
004a0a1d ff929c000000             call      dword ptr [edx + 0x9c]
004a0a23 50                       push      eax
004a0a24 8b06                     mov       eax, dword ptr [esi]
004a0a26 8bce                     mov       ecx, esi
004a0a28 ff9098000000             call      dword ptr [eax + 0x98]
004a0a2e 8b16                     mov       edx, dword ptr [esi]
004a0a30 50                       push      eax
004a0a31 8bce                     mov       ecx, esi
004a0a33 ff9294000000             call      dword ptr [edx + 0x94]
004a0a39 8b8e94070000             mov       ecx, dword ptr [esi + 0x794]
004a0a3f 50                       push      eax
004a0a40 ff5728                   call      dword ptr [edi + 0x28]
004a0a43 8b8e94070000             mov       ecx, dword ptr [esi + 0x794]
004a0a49 8b01                     mov       eax, dword ptr [ecx]
004a0a4b 8d55e0                   lea       edx, [ebp - 0x20]
004a0a4e 52                       push      edx
004a0a4f ff505c                   call      dword ptr [eax + 0x5c]
004a0a52 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a0a58 6a00                     push      0
004a0a5a 8d45e0                   lea       eax, [ebp - 0x20]
004a0a5d 50                       push      eax
004a0a5e 6a00                     push      0
004a0a60 6a02                     push      2
004a0a62 56                       push      esi
004a0a63 c745fc02000000           mov       dword ptr [ebp - 4], 2
004a0a6a e8f1d50600               call      0x50e060
004a0a6f 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
004a0a72 85c0                     test      eax, eax
004a0a74 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a0a7b 7409                     je        0x4a0a86
004a0a7d 50                       push      eax
004a0a7e e85af57500               call      0xbfffdd
004a0a83 83c404                   add       esp, 4
004a0a86 8bce                     mov       ecx, esi
004a0a88 e803b6ffff               call      0x49c090
004a0a8d 84c0                     test      al, al
004a0a8f 0f848b000000             je        0x4a0b20
004a0a95 8a86a4050000             mov       al, byte ptr [esi + 0x5a4]
004a0a9b 84c0                     test      al, al
004a0a9d 0f857d000000             jne       0x4a0b20
004a0aa3 83be6005000001           cmp       dword ptr [esi + 0x560], 1
004a0aaa 7574                     jne       0x4a0b20
004a0aac 33ff                     xor       edi, edi
004a0aae 8bff                     mov       edi, edi
004a0ab0 8b8e68050000             mov       ecx, dword ptr [esi + 0x568]
004a0ab6 85c9                     test      ecx, ecx
004a0ab8 745f                     je        0x4a0b19
004a0aba 8b866c050000             mov       eax, dword ptr [esi + 0x56c]
004a0ac0 2bc1                     sub       eax, ecx
004a0ac2 c1f802                   sar       eax, 2
004a0ac5 3bf8                     cmp       edi, eax
004a0ac7 7350                     jae       0x4a0b19
004a0ac9 8b16                     mov       edx, dword ptr [esi]
004a0acb 6a00                     push      0
004a0acd 6a00                     push      0
004a0acf 6a00                     push      0
004a0ad1 6a00                     push      0
004a0ad3 8d1cb9                   lea       ebx, [ecx + edi*4]
004a0ad6 6a00                     push      0
004a0ad8 8bce                     mov       ecx, esi
004a0ada ff92c0000000             call      dword ptr [edx + 0xc0]
004a0ae0 50                       push      eax
004a0ae1 8b06                     mov       eax, dword ptr [esi]
004a0ae3 8bce                     mov       ecx, esi
004a0ae5 ff909c000000             call      dword ptr [eax + 0x9c]
004a0aeb 8b16                     mov       edx, dword ptr [esi]
004a0aed 50                       push      eax
004a0aee 8bce                     mov       ecx, esi
004a0af0 ff9298000000             call      dword ptr [edx + 0x98]
004a0af6 50                       push      eax
004a0af7 8b06                     mov       eax, dword ptr [esi]
004a0af9 8bce                     mov       ecx, esi
004a0afb ff9094000000             call      dword ptr [eax + 0x94]
004a0b01 8b0b                     mov       ecx, dword ptr [ebx]
004a0b03 8b9630050000             mov       edx, dword ptr [esi + 0x530]
004a0b09 50                       push      eax
004a0b0a 6a00                     push      0
004a0b0c 51                       push      ecx
004a0b0d 52                       push      edx
004a0b0e e88d930400               call      0x4e9ea0
004a0b13 83c430                   add       esp, 0x30
004a0b16 47                       inc       edi
004a0b17 eb97                     jmp       0x4a0ab0
004a0b19 c686a405000001           mov       byte ptr [esi + 0x5a4], 1
004a0b20 8b8698050000             mov       eax, dword ptr [esi + 0x598]
004a0b26 85c0                     test      eax, eax
004a0b28 7504                     jne       0x4a0b2e
004a0b2a 33db                     xor       ebx, ebx
004a0b2c eb0b                     jmp       0x4a0b39
004a0b2e 8b9e9c050000             mov       ebx, dword ptr [esi + 0x59c]
004a0b34 2bd8                     sub       ebx, eax
004a0b36 c1fb02                   sar       ebx, 2
004a0b39 33ff                     xor       edi, edi
004a0b3b 85db                     test      ebx, ebx
004a0b3d 7e28                     jle       0x4a0b67
004a0b3f 90                       nop       
004a0b40 8b8698050000             mov       eax, dword ptr [esi + 0x598]
004a0b46 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004a0b49 85c9                     test      ecx, ecx
004a0b4b 8d04b8                   lea       eax, [eax + edi*4]
004a0b4e 7c12                     jl        0x4a0b62
004a0b50 83f9ff                   cmp       ecx, -1
004a0b53 740d                     je        0x4a0b62
004a0b55 8b16                     mov       edx, dword ptr [esi]
004a0b57 8bc1                     mov       eax, ecx
004a0b59 50                       push      eax
004a0b5a 8bce                     mov       ecx, esi
004a0b5c ff9210010000             call      dword ptr [edx + 0x110]
004a0b62 47                       inc       edi
004a0b63 3bfb                     cmp       edi, ebx
004a0b65 7cd9                     jl        0x4a0b40
004a0b67 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
004a0b6d 8b4810                   mov       ecx, dword ptr [eax + 0x10]
004a0b70 83c010                   add       eax, 0x10
004a0b73 85c9                     test      ecx, ecx
004a0b75 0f8585000000             jne       0x4a0c00
004a0b7b 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
004a0b81 85c9                     test      ecx, ecx
004a0b83 747b                     je        0x4a0c00
004a0b85 8b869c050000             mov       eax, dword ptr [esi + 0x59c]
004a0b8b 2bc1                     sub       eax, ecx
004a0b8d c1f802                   sar       eax, 2
004a0b90 85c0                     test      eax, eax
004a0b92 766c                     jbe       0x4a0c00
004a0b94 8bc1                     mov       eax, ecx
004a0b96 8b4810                   mov       ecx, dword ptr [eax + 0x10]
004a0b99 83f9fe                   cmp       ecx, -2
004a0b9c 7429                     je        0x4a0bc7
004a0b9e 83caff                   or        edx, 0xffffffff
004a0ba1 3bca                     cmp       ecx, edx
004a0ba3 7404                     je        0x4a0ba9
004a0ba5 3bca                     cmp       ecx, edx
004a0ba7 741e                     je        0x4a0bc7
004a0ba9 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
004a0baf 8b3e                     mov       edi, dword ptr [esi]
004a0bb1 6a00                     push      0
004a0bb3 6a00                     push      0
004a0bb5 83c110                   add       ecx, 0x10
004a0bb8 52                       push      edx
004a0bb9 e832255b00               call      0xa530f0
004a0bbe 50                       push      eax
004a0bbf 8bce                     mov       ecx, esi
004a0bc1 ff970c010000             call      dword ptr [edi + 0x10c]
004a0bc7 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
004a0bcd 83c010                   add       eax, 0x10
004a0bd0 c70001000000             mov       dword ptr [eax], 1
004a0bd6 eb28                     jmp       0x4a0c00
004a0bd8 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a0bde 8a8800010000             mov       cl, byte ptr [eax + 0x100]
004a0be4 84c9                     test      cl, cl
004a0be6 7418                     je        0x4a0c00
004a0be8 8b8818010000             mov       ecx, dword ptr [eax + 0x118]
004a0bee 85c9                     test      ecx, ecx
004a0bf0 740e                     je        0x4a0c00
004a0bf2 3bcb                     cmp       ecx, ebx
004a0bf4 750a                     jne       0x4a0c00
004a0bf6 c7801801000000000000     mov       dword ptr [eax + 0x118], 0
004a0c00 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004a0c06 8b3d0ce6ff00             mov       edi, dword ptr [0xffe60c]
004a0c0c 8b1510e6ff00             mov       edx, dword ptr [0xffe610]
004a0c12 8bcb                     mov       ecx, ebx
004a0c14 33cf                     xor       ecx, edi
004a0c16 81e90ce6ff00             sub       ecx, 0xffe60c
004a0c1c 3bca                     cmp       ecx, edx
004a0c1e 741e                     je        0x4a0c3e
004a0c20 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a0c26 6a3f                     push      0x3f
004a0c28 680ce6ff00               push      0xffe60c
004a0c2d e87e646700               call      0xb170b0
004a0c32 8b1510e6ff00             mov       edx, dword ptr [0xffe610]
004a0c38 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004a0c3e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a0c44 8b4144                   mov       eax, dword ptr [ecx + 0x44]
004a0c47 8b3c90                   mov       edi, dword ptr [eax + edx*4]
004a0c4a 8d0490                   lea       eax, [eax + edx*4]
004a0c4d 33f8                     xor       edi, eax
004a0c4f 8b4148                   mov       eax, dword ptr [ecx + 0x48]
004a0c52 8d0490                   lea       eax, [eax + edx*4]
004a0c55 8b10                     mov       edx, dword ptr [eax]
004a0c57 33d0                     xor       edx, eax
004a0c59 33fb                     xor       edi, ebx
004a0c5b 33d3                     xor       edx, ebx
004a0c5d 3bfa                     cmp       edi, edx
004a0c5f 740c                     je        0x4a0c6d
004a0c61 6a40                     push      0x40
004a0c63 680ce6ff00               push      0xffe60c
004a0c68 e843646700               call      0xb170b0
004a0c6d 85ff                     test      edi, edi
004a0c6f 0f850d010000             jne       0x4a0d82
004a0c75 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004a0c7b 81c140100000             add       ecx, 0x1040
004a0c81 e8da13f6ff               call      0x402060
004a0c86 83f803                   cmp       eax, 3
004a0c89 742c                     je        0x4a0cb7
004a0c8b 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004a0c91 81c140100000             add       ecx, 0x1040
004a0c97 e8c413f6ff               call      0x402060
004a0c9c 83f80a                   cmp       eax, 0xa
004a0c9f 7416                     je        0x4a0cb7
004a0ca1 8d8efc010000             lea       ecx, [esi + 0x1fc]
004a0ca7 e8b413f6ff               call      0x402060
004a0cac 3df97f0000               cmp       eax, 0x7ff9
004a0cb1 0f85cb000000             jne       0x4a0d82
004a0cb7 8dbefc010000             lea       edi, [esi + 0x1fc]
004a0cbd 8bcf                     mov       ecx, edi
004a0cbf e89c13f6ff               call      0x402060
004a0cc4 3df97f0000               cmp       eax, 0x7ff9
004a0cc9 0f85b3000000             jne       0x4a0d82
004a0ccf 8bcf                     mov       ecx, edi
004a0cd1 e88a13f6ff               call      0x402060
004a0cd6 3df97f0000               cmp       eax, 0x7ff9
004a0cdb 750e                     jne       0x4a0ceb
004a0cdd 6800f1cc00               push      0xccf100
004a0ce2 ff15bc2eff00             call      dword ptr [0xff2ebc]
004a0ce8 83c404                   add       esp, 4
004a0ceb b9fc510001               mov       ecx, 0x10051fc
004a0cf0 e86b13f6ff               call      0x402060
004a0cf5 50                       push      eax
004a0cf6 68e0f0cc00               push      0xccf0e0
004a0cfb ff15bc2eff00             call      dword ptr [0xff2ebc]
004a0d01 83c408                   add       esp, 8
004a0d04 8d4508                   lea       eax, [ebp + 8]
004a0d07 50                       push      eax
004a0d08 b9fc510001               mov       ecx, 0x10051fc
004a0d0d c7450801000000           mov       dword ptr [ebp + 8], 1
004a0d14 e89769fcff               call      0x4676b0
004a0d19 b9fc510001               mov       ecx, 0x10051fc
004a0d1e e83d13f6ff               call      0x402060
004a0d23 85c0                     test      eax, eax
004a0d25 7f5b                     jg        0x4a0d82
004a0d27 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a0d2d 6a01                     push      1
004a0d2f e87ca00600               call      0x50adb0
004a0d34 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004a0d3a 8b8914010000             mov       ecx, dword ptr [ecx + 0x114]
004a0d40 6a00                     push      0
004a0d42 6a1e                     push      0x1e
004a0d44 6870170000               push      0x1770
004a0d49 e8b28e0900               call      0x539c00
004a0d4e 6a00                     push      0
004a0d50 6a00                     push      0
004a0d52 6aff                     push      -1
004a0d54 68c0f0cc00               push      0xccf0c0
004a0d59 e8526cfaff               call      0x4479b0
004a0d5e 8b16                     mov       edx, dword ptr [esi]
004a0d60 83c410                   add       esp, 0x10
004a0d63 6a00                     push      0
004a0d65 8bce                     mov       ecx, esi
004a0d67 ff92d8020000             call      dword ptr [edx + 0x2d8]
004a0d6d 8b8600010000             mov       eax, dword ptr [esi + 0x100]
004a0d73 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
004a0d79 6a00                     push      0
004a0d7b 6a04                     push      4
004a0d7d e8eeb00900               call      0x53be70
004a0d82 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a0d85 5f                       pop       edi
004a0d86 5e                       pop       esi
004a0d87 5b                       pop       ebx
004a0d88 64890d00000000           mov       dword ptr fs:[0], ecx
004a0d8f 8be5                     mov       esp, ebp
004a0d91 5d                       pop       ebp
004a0d92 c20400                   ret       4
