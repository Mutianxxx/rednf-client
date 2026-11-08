0050da30 51                       push      ecx
0050da31 44                       inc       esp
0050da32 8b4608                   mov       eax, dword ptr [esi + 8]
0050da35 8d0482                   lea       eax, [edx + eax*4]
0050da38 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0050da3e 8bc8                     mov       ecx, eax
0050da40 33ca                     xor       ecx, edx
0050da42 8908                     mov       dword ptr [eax], ecx
0050da44 a1d8012101               mov       eax, dword ptr [0x12101d8]
0050da49 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0050da4c 8b5608                   mov       edx, dword ptr [esi + 8]
0050da4f 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
0050da55 8d0491                   lea       eax, [ecx + edx*4]
0050da58 8bd0                     mov       edx, eax
0050da5a 33d7                     xor       edx, edi
0050da5c 8910                     mov       dword ptr [eax], edx
0050da5e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0050da64 8b5144                   mov       edx, dword ptr [ecx + 0x44]
0050da67 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0050da6d 8d0482                   lea       eax, [edx + eax*4]
0050da70 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0050da76 8bc8                     mov       ecx, eax
0050da78 33ca                     xor       ecx, edx
0050da7a 8908                     mov       dword ptr [eax], ecx
0050da7c a1d8012101               mov       eax, dword ptr [0x12101d8]
0050da81 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0050da84 8b9650010000             mov       edx, dword ptr [esi + 0x150]
0050da8a 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
0050da90 8d0491                   lea       eax, [ecx + edx*4]
0050da93 8bd0                     mov       edx, eax
0050da95 33d7                     xor       edx, edi
0050da97 8910                     mov       dword ptr [eax], edx
0050da99 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0050da9f 8b5144                   mov       edx, dword ptr [ecx + 0x44]
0050daa2 8b8658010000             mov       eax, dword ptr [esi + 0x158]
0050daa8 8d0482                   lea       eax, [edx + eax*4]
0050daab 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0050dab1 8bc8                     mov       ecx, eax
0050dab3 33ca                     xor       ecx, edx
0050dab5 8908                     mov       dword ptr [eax], ecx
0050dab7 a1d8012101               mov       eax, dword ptr [0x12101d8]
0050dabc 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0050dabf 8b9658010000             mov       edx, dword ptr [esi + 0x158]
0050dac5 8d0491                   lea       eax, [ecx + edx*4]
0050dac8 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0050dace 8bd0                     mov       edx, eax
