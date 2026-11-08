004f9760 2101                     and       dword ptr [ecx], eax
004f9762 8b4304                   mov       eax, dword ptr [ebx + 4]
004f9765 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004f9768 c1e002                   shl       eax, 2
004f976b 8b3c02                   mov       edi, dword ptr [edx + eax]
004f976e 03d0                     add       edx, eax
004f9770 33fa                     xor       edi, edx
004f9772 333ddc012101             xor       edi, dword ptr [0x12101dc]
004f9778 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004f977b 03c2                     add       eax, edx
004f977d 8b10                     mov       edx, dword ptr [eax]
004f977f 33d0                     xor       edx, eax
004f9781 3315dc012101             xor       edx, dword ptr [0x12101dc]
004f9787 3bfa                     cmp       edi, edx
004f9789 7408                     je        0x4f9793
004f978b 6a40                     push      0x40
004f978d 53                       push      ebx
004f978e e81dd96100               call      0xb170b0
004f9793 85ff                     test      edi, edi
004f9795 0f8519030000             jne       0x4f9ab4
004f979b 8b8e18240000             mov       ecx, dword ptr [esi + 0x2418]
004f97a1 85c9                     test      ecx, ecx
004f97a3 0f840b030000             je        0x4f9ab4
004f97a9 8b861c240000             mov       eax, dword ptr [esi + 0x241c]
004f97af 2bc1                     sub       eax, ecx
004f97b1 c1f802                   sar       eax, 2
004f97b4 85c0                     test      eax, eax
004f97b6 0f84f8020000             je        0x4f9ab4
004f97bc 8bc1                     mov       eax, ecx
004f97be 833800                   cmp       dword ptr [eax], 0
004f97c1 0f84ed020000             je        0x4f9ab4
004f97c7 8b8604010000             mov       eax, dword ptr [esi + 0x104]
004f97cd 85c0                     test      eax, eax
004f97cf 750e                     jne       0x4f97df
004f97d1 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004f97d7 85c0                     test      eax, eax
004f97d9 0f84d5020000             je        0x4f9ab4
004f97df 8b06                     mov       eax, dword ptr [esi]
004f97e1 8bce                     mov       ecx, esi
004f97e3 ff90dc030000             call      dword ptr [eax + 0x3dc]
004f97e9 84c0                     test      al, al
004f97eb 0f85c3020000             jne       0x4f9ab4
004f97f1 8b16                     mov       edx, dword ptr [esi]
004f97f3 8bce                     mov       ecx, esi
004f97f5 ff9278030000             call      dword ptr [edx + 0x378]
004f97fb 398604010000             cmp       dword ptr [esi + 0x104], eax
004f9801 7516                     jne       0x4f9819
004f9803 8b06                     mov       eax, dword ptr [esi]
004f9805 8bce                     mov       ecx, esi
004f9807 ff90a0030000             call      dword ptr [eax + 0x3a0]
004f980d 398648010000             cmp       dword ptr [esi + 0x148], eax
004f9813 0f849b020000             je        0x4f9ab4
004f9819 8b16                     mov       edx, dword ptr [esi]
004f981b 8bce                     mov       ecx, esi
004f981d ff927c030000             call      dword ptr [edx + 0x37c]
004f9823 398604010000             cmp       dword ptr [esi + 0x104], eax
004f9829 7516                     jne       0x4f9841
004f982b 8b06                     mov       eax, dword ptr [esi]
004f982d 8bce                     mov       ecx, esi
004f982f ff90a4030000             call      dword ptr [eax + 0x3a4]
004f9835 398648010000             cmp       dword ptr [esi + 0x148], eax
004f983b 0f8473020000             je        0x4f9ab4
004f9841 8b8e80240000             mov       ecx, dword ptr [esi + 0x2480]
004f9847 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004f984d 8b8684240000             mov       eax, dword ptr [esi + 0x2484]
004f9853 8d9e80240000             lea       ebx, [esi + 0x2480]
004f9859 33cf                     xor       ecx, edi
004f985b 2bcb                     sub       ecx, ebx
004f985d 3bc8                     cmp       ecx, eax
004f985f 740e                     je        0x4f986f
004f9861 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f9867 6a3f                     push      0x3f
004f9869 53                       push      ebx
004f986a e841d86100               call      0xb170b0
004f986f 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f9875 8b4304                   mov       eax, dword ptr [ebx + 4]
004f9878 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004f987b c1e002                   shl       eax, 2
004f987e 03d0                     add       edx, eax
004f9880 8bfa                     mov       edi, edx
004f9882 333ddc012101             xor       edi, dword ptr [0x12101dc]
004f9888 333a                     xor       edi, dword ptr [edx]
004f988a 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004f988d 03c2                     add       eax, edx
004f988f 8b10                     mov       edx, dword ptr [eax]
004f9891 33d0                     xor       edx, eax
004f9893 3315dc012101             xor       edx, dword ptr [0x12101dc]
004f9899 3bfa                     cmp       edi, edx
004f989b 7408                     je        0x4f98a5
004f989d 6a40                     push      0x40
004f989f 53                       push      ebx
004f98a0 e80bd86100               call      0xb170b0
004f98a5 85ff                     test      edi, edi
004f98a7 7508                     jne       0x4f98b1
004f98a9 8d8e68240000             lea       ecx, [esi + 0x2468]
004f98af eb0f                     jmp       0x4f98c0
004f98b1 8dbe68240000             lea       edi, [esi + 0x2468]
004f98b7 8bcf                     mov       ecx, edi
004f98b9 e832b6f0ff               call      0x404ef0
004f98be 8bcf                     mov       ecx, edi
