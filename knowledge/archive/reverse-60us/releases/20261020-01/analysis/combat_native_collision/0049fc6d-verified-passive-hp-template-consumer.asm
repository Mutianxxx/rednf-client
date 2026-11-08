0049fc6d a1dc012101               mov       eax, dword ptr [0x12101dc]
0049fc72 8b97ac000000             mov       edx, dword ptr [edi + 0xac]
0049fc78 8d9fac000000             lea       ebx, [edi + 0xac]
0049fc7e 33d0                     xor       edx, eax
0049fc80 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fc83 2bd3                     sub       edx, ebx
0049fc85 3bd0                     cmp       edx, eax
0049fc87 740e                     je        0x49fc97
0049fc89 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fc8f 6a3f                     push      0x3f
0049fc91 53                       push      ebx
0049fc92 e819746700               call      0xb170b0
0049fc97 a1d8012101               mov       eax, dword ptr [0x12101d8]
0049fc9c 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049fc9f 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fca2 c1e002                   shl       eax, 2
0049fca5 8d0c02                   lea       ecx, [edx + eax]
0049fca8 330c02                   xor       ecx, dword ptr [edx + eax]
0049fcab 330ddc012101             xor       ecx, dword ptr [0x12101dc]
0049fcb1 894d08                   mov       dword ptr [ebp + 8], ecx
0049fcb4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fcba 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
0049fcbd 8d1401                   lea       edx, [ecx + eax]
0049fcc0 331401                   xor       edx, dword ptr [ecx + eax]
0049fcc3 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fcc9 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fccc 33d1                     xor       edx, ecx
0049fcce 3bc2                     cmp       eax, edx
0049fcd0 740e                     je        0x49fce0
0049fcd2 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fcd8 6a40                     push      0x40
0049fcda 53                       push      ebx
0049fcdb e8d0736700               call      0xb170b0
0049fce0 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fce3 85c0                     test      eax, eax
0049fce5 0f8e8e000000             jle       0x49fd79
0049fceb 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fcf1 8b03                     mov       eax, dword ptr [ebx]
0049fcf3 33c1                     xor       eax, ecx
0049fcf5 8b4b04                   mov       ecx, dword ptr [ebx + 4]
0049fcf8 2bc3                     sub       eax, ebx
0049fcfa 3bc1                     cmp       eax, ecx
0049fcfc 740e                     je        0x49fd0c
0049fcfe 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd04 6a3f                     push      0x3f
0049fd06 53                       push      ebx
0049fd07 e8a4736700               call      0xb170b0
0049fd0c 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd12 8b5144                   mov       edx, dword ptr [ecx + 0x44]
0049fd15 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fd18 c1e002                   shl       eax, 2
0049fd1b 8d0c02                   lea       ecx, [edx + eax]
0049fd1e 330c02                   xor       ecx, dword ptr [edx + eax]
0049fd21 330ddc012101             xor       ecx, dword ptr [0x12101dc]
0049fd27 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049fd2d 894d08                   mov       dword ptr [ebp + 8], ecx
0049fd30 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
0049fd33 8d1401                   lea       edx, [ecx + eax]
0049fd36 331401                   xor       edx, dword ptr [ecx + eax]
0049fd39 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fd3f 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fd42 33d1                     xor       edx, ecx
0049fd44 3bc2                     cmp       eax, edx
0049fd46 740e                     je        0x49fd56
0049fd48 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd4e 6a40                     push      0x40
0049fd50 53                       push      ebx
0049fd51 e85a736700               call      0xb170b0
0049fd56 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049fd59 8b06                     mov       eax, dword ptr [esi]
0049fd5b 51                       push      ecx
0049fd5c 8bce                     mov       ecx, esi
0049fd5e ff9060030000             call      dword ptr [eax + 0x360]
0049fd64 8b1e                     mov       ebx, dword ptr [esi]
0049fd66 8bd3                     mov       edx, ebx
0049fd68 8bce                     mov       ecx, esi
0049fd6a ff9238020000             call      dword ptr [edx + 0x238]
0049fd70 50                       push      eax
0049fd71 8bce                     mov       ecx, esi
0049fd73 ff935c030000             call      dword ptr [ebx + 0x35c]
0049fd79 8a4761                   mov       al, byte ptr [edi + 0x61]
0049fd7c 84c0                     test      al, al
0049fd7e 740e                     je        0x49fd8e
0049fd80 8b06                     mov       eax, dword ptr [esi]
0049fd82 8bce                     mov       ecx, esi
0049fd84 ff903c030000             call      dword ptr [eax + 0x33c]
0049fd8a c6403401                 mov       byte ptr [eax + 0x34], 1
