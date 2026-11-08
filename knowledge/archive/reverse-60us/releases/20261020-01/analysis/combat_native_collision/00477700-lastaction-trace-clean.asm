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
004777bd 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004777c3 c1e002                   shl       eax, 2
004777c6 8d1401                   lea       edx, [ecx + eax]
004777c9 f7d2                     not       edx
004777cb 33d7                     xor       edx, edi
004777cd 891401                   mov       dword ptr [ecx + eax], edx
004777d0 33ff                     xor       edi, edi
004777d2 8a8394010000             mov       al, byte ptr [ebx + 0x194]
004777d8 84c0                     test      al, al
004777da 0f84e3000000             je        0x4778c3
004777e0 6a1c                     push      0x1c
004777e2 e836617700               call      0xbed91d
004777e7 83c404                   add       esp, 4
004777ea 3bc7                     cmp       eax, edi
004777ec 7415                     je        0x477803
004777ee 897810                   mov       dword ptr [eax + 0x10], edi
004777f1 897814                   mov       dword ptr [eax + 0x14], edi
004777f4 897804                   mov       dword ptr [eax + 4], edi
004777f7 897808                   mov       dword ptr [eax + 8], edi
004777fa 89780c                   mov       dword ptr [eax + 0xc], edi
004777fd c6401800                 mov       byte ptr [eax + 0x18], 0
00477801 eb02                     jmp       0x477805
00477803 33c0                     xor       eax, eax
00477805 898624010000             mov       dword ptr [esi + 0x124], eax
0047780b 8b8b8c010000             mov       ecx, dword ptr [ebx + 0x18c]
00477811 894810                   mov       dword ptr [eax + 0x10], ecx
00477814 8b9624010000             mov       edx, dword ptr [esi + 0x124]
0047781a 8b8390010000             mov       eax, dword ptr [ebx + 0x190]
00477820 894214                   mov       dword ptr [edx + 0x14], eax
00477823 8b8e24010000             mov       ecx, dword ptr [esi + 0x124]
00477829 8a9394010000             mov       dl, byte ptr [ebx + 0x194]
0047782f 885118                   mov       byte ptr [ecx + 0x18], dl
00477832 8b8b80010000             mov       ecx, dword ptr [ebx + 0x180]
00477838 3bcf                     cmp       ecx, edi
0047783a c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00477841 7504                     jne       0x477847
00477843 33c0                     xor       eax, eax
00477845 eb0b                     jmp       0x477852
00477847 8b8384010000             mov       eax, dword ptr [ebx + 0x184]
0047784d 2bc1                     sub       eax, ecx
0047784f c1f802                   sar       eax, 2
00477852 8b8e24010000             mov       ecx, dword ptr [esi + 0x124]
00477858 57                       push      edi
00477859 50                       push      eax
0047785a e8b11a0000               call      0x479310
0047785f 33c0                     xor       eax, eax
00477861 8b9380010000             mov       edx, dword ptr [ebx + 0x180]
00477867 3bd7                     cmp       edx, edi
00477869 8d8b7c010000             lea       ecx, [ebx + 0x17c]
0047786f 7452                     je        0x4778c3
00477871 8b5108                   mov       edx, dword ptr [ecx + 8]
00477874 8b7904                   mov       edi, dword ptr [ecx + 4]
00477877 2bd7                     sub       edx, edi
00477879 c1fa02                   sar       edx, 2
0047787c 3bc2                     cmp       eax, edx
0047787e 7341                     jae       0x4778c1
