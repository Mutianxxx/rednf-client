0049bb48 8b8e50010000             mov       ecx, dword ptr [esi + 0x150]
0049bb4e 3bcf                     cmp       ecx, edi
0049bb50 89be4c010000             mov       dword ptr [esi + 0x14c], edi
0049bb56 7406                     je        0x49bb5e
0049bb58 8b01                     mov       eax, dword ptr [ecx]
0049bb5a 6a01                     push      1
0049bb5c ff10                     call      dword ptr [eax]
0049bb5e 89be50010000             mov       dword ptr [esi + 0x150], edi
0049bb64 33db                     xor       ebx, ebx
