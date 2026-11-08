00477700 2101                     and       dword ptr [ecx], eax
00477702 8b5244                   mov       edx, dword ptr [edx + 0x44]
00477705 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0047770b 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
00477711 8b4904                   mov       ecx, dword ptr [ecx + 4]
00477714 c1e002                   shl       eax, 2
00477717 8d3c10                   lea       edi, [eax + edx]
0047771a 333ddc012101             xor       edi, dword ptr [0x12101dc]
00477720 c7450800401c46           mov       dword ptr [ebp + 8], 0x461c4000
00477727 33f9                     xor       edi, ecx
00477729 893c10                   mov       dword ptr [eax + edx], edi
0047772c a1d8012101               mov       eax, dword ptr [0x12101d8]
00477731 8b5048                   mov       edx, dword ptr [eax + 0x48]
00477734 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0047773a c1e002                   shl       eax, 2
0047773d 8d3c10                   lea       edi, [eax + edx]
00477740 333ddc012101             xor       edi, dword ptr [0x12101dc]
00477746 33f9                     xor       edi, ecx
00477748 893c10                   mov       dword ptr [eax + edx], edi
0047774b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00477751 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
00477754 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0047775a 8b5508                   mov       edx, dword ptr [ebp + 8]
0047775d c1e002                   shl       eax, 2
00477760 8d3c01                   lea       edi, [ecx + eax]
00477763 33fa                     xor       edi, edx
00477765 333ddc012101             xor       edi, dword ptr [0x12101dc]
0047776b 893c01                   mov       dword ptr [ecx + eax], edi
0047776e a1d8012101               mov       eax, dword ptr [0x12101d8]
00477773 8b4848                   mov       ecx, dword ptr [eax + 0x48]
00477776 8b8650010000             mov       eax, dword ptr [esi + 0x150]
0047777c c1e002                   shl       eax, 2
0047777f 8d3c01                   lea       edi, [ecx + eax]
00477782 33fa                     xor       edi, edx
00477784 333ddc012101             xor       edi, dword ptr [0x12101dc]
0047778a 893c01                   mov       dword ptr [ecx + eax], edi
0047778d 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00477793 8b8658010000             mov       eax, dword ptr [esi + 0x158]
00477799 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
0047779c 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004777a2 c1e002                   shl       eax, 2
004777a5 8d1401                   lea       edx, [ecx + eax]
004777a8 f7d2                     not       edx
004777aa 33d7                     xor       edx, edi
004777ac 891401                   mov       dword ptr [ecx + eax], edx
004777af a1d8012101               mov       eax, dword ptr [0x12101d8]
004777b4 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004777b7 8b8658010000             mov       eax, dword ptr [esi + 0x158]
004777bd 8b                       .byte     0x8b
004777be 3d                       .byte     0x3d
004777bf dc                       .byte     0xdc
