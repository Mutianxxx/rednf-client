0049a150 56                       push      esi
0049a151 6a00                     push      0
0049a153 8bf1                     mov       esi, ecx
0049a155 8b06                     mov       eax, dword ptr [esi]
0049a157 6aff                     push      -1
0049a159 6a00                     push      0
0049a15b ff901c010000             call      dword ptr [eax + 0x11c]
0049a161 8b16                     mov       edx, dword ptr [esi]
0049a163 6a11                     push      0x11
0049a165 8bce                     mov       ecx, esi
0049a167 ff522c                   call      dword ptr [edx + 0x2c]
0049a16a 84c0                     test      al, al
0049a16c 7424                     je        0x49a192
0049a16e 8d8e68180000             lea       ecx, [esi + 0x1868]
0049a174 e8e77ef6ff               call      0x402060
0049a179 85c0                     test      eax, eax
0049a17b 750e                     jne       0x49a18b
0049a17d 8b06                     mov       eax, dword ptr [esi]
0049a17f 8bce                     mov       ecx, esi
0049a181 ff90f4040000             call      dword ptr [eax + 0x4f4]
0049a187 84c0                     test      al, al
0049a189 7407                     je        0x49a192
0049a18b 68ffffff00               push      0xffffff
0049a190 eb02                     jmp       0x49a194
0049a192 6aff                     push      -1
0049a194 8bce                     mov       ecx, esi
0049a196 e8c5ecffff               call      0x498e60
0049a19b 8b16                     mov       edx, dword ptr [esi]
0049a19d 6a00                     push      0
0049a19f 6a00                     push      0
0049a1a1 6a00                     push      0
0049a1a3 8bce                     mov       ecx, esi
0049a1a5 ff9234010000             call      dword ptr [edx + 0x134]
0049a1ab 8b06                     mov       eax, dword ptr [esi]
0049a1ad 6a00                     push      0
0049a1af 6a00                     push      0
0049a1b1 8bce                     mov       ecx, esi
0049a1b3 ff9040010000             call      dword ptr [eax + 0x140]
0049a1b9 8b16                     mov       edx, dword ptr [esi]
0049a1bb 6a02                     push      2
0049a1bd 6a01                     push      1
0049a1bf 6a00                     push      0
0049a1c1 6a00                     push      0
0049a1c3 8bce                     mov       ecx, esi
0049a1c5 ff924c010000             call      dword ptr [edx + 0x14c]
0049a1cb 5e                       pop       esi
0049a1cc c3                       ret       
0049a1cd cc                       int3      
0049a1ce cc                       int3      
0049a1cf cc                       int3      
