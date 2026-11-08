004bb091 8b4304                   mov       eax, dword ptr [ebx + 4]
004bb094 db4004                   fild      dword ptr [eax + 4]
004bb097 8b4808                   mov       ecx, dword ptr [eax + 8]
004bb09a 8b38                     mov       edi, dword ptr [eax]
004bb09c 898ebc160000             mov       dword ptr [esi + 0x16bc], ecx
004bb0a2 d80dac10cc00             fmul      dword ptr [0xcc10ac]
004bb0a8 8b4304                   mov       eax, dword ptr [ebx + 4]
004bb0ab 33d2                     xor       edx, edx
004bb0ad 3bc2                     cmp       eax, edx
004bb0af d95ddc                   fstp      dword ptr [ebp - 0x24]
004bb0b2 89550c                   mov       dword ptr [ebp + 0xc], edx
004bb0b5 7413                     je        0x4bb0ca
004bb0b7 8b4b08                   mov       ecx, dword ptr [ebx + 8]
004bb0ba 2bc8                     sub       ecx, eax
004bb0bc c1f902                   sar       ecx, 2
004bb0bf 83f903                   cmp       ecx, 3
004bb0c2 7606                     jbe       0x4bb0ca
004bb0c4 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004bb0c7 894d0c                   mov       dword ptr [ebp + 0xc], ecx
