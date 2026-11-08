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
