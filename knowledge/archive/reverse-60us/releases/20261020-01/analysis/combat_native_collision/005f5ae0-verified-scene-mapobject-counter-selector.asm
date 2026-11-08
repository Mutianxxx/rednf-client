005f5ae0 56                       push      esi
005f5ae1 8bf1                     mov       esi, ecx
005f5ae3 8b8e80080000             mov       ecx, dword ptr [esi + 0x880]
005f5ae9 8b867c080000             mov       eax, dword ptr [esi + 0x87c]
005f5aef 8b16                     mov       edx, dword ptr [esi]
005f5af1 3bc1                     cmp       eax, ecx
005f5af3 8bce                     mov       ecx, esi
005f5af5 7536                     jne       0x5f5b2d
005f5af7 ff9294030000             call      dword ptr [edx + 0x394]
005f5afd 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
005f5b03 85c9                     test      ecx, ecx
005f5b05 7424                     je        0x5f5b2b
005f5b07 8b8624010000             mov       eax, dword ptr [esi + 0x124]
005f5b0d 2bc1                     sub       eax, ecx
005f5b0f c1f802                   sar       eax, 2
005f5b12 85c0                     test      eax, eax
005f5b14 7615                     jbe       0x5f5b2b
005f5b16 8bc1                     mov       eax, ecx
005f5b18 8b08                     mov       ecx, dword ptr [eax]
005f5b1a 85c9                     test      ecx, ecx
005f5b1c 740d                     je        0x5f5b2b
005f5b1e 8b16                     mov       edx, dword ptr [esi]
005f5b20 8bc1                     mov       eax, ecx
005f5b22 50                       push      eax
005f5b23 8bce                     mov       ecx, esi
005f5b25 ff92f0000000             call      dword ptr [edx + 0xf0]
005f5b2b 5e                       pop       esi
005f5b2c c3                       ret       
005f5b2d 5e                       pop       esi
005f5b2e ffa298030000             jmp       dword ptr [edx + 0x398]
