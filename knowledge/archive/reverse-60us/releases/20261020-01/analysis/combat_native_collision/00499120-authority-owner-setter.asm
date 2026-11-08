00499120 55                       push      ebp
00499121 8bec                     mov       ebp, esp
00499123 8a4508                   mov       al, byte ptr [ebp + 8]
00499126 84c0                     test      al, al
00499128 56                       push      esi
00499129 8bf1                     mov       esi, ecx
0049912b 7516                     jne       0x499143
0049912d 8b06                     mov       eax, dword ptr [esi]
0049912f ff9060010000             call      dword ptr [eax + 0x160]
00499135 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
0049913b 3bc1                     cmp       eax, ecx
0049913d 7567                     jne       0x4991a6
0049913f 85c9                     test      ecx, ecx
00499141 7463                     je        0x4991a6
00499143 80bee801000001           cmp       byte ptr [esi + 0x1e8], 1
0049914a 745a                     je        0x4991a6
0049914c 8b0d64310001             mov       ecx, dword ptr [0x1003164]
00499152 8b11                     mov       edx, dword ptr [ecx]
00499154 57                       push      edi
00499155 6a02                     push      2
00499157 6a17                     push      0x17
00499159 ff5208                   call      dword ptr [edx + 8]
0049915c a164310001               mov       eax, dword ptr [0x1003164]
00499161 8b16                     mov       edx, dword ptr [esi]
00499163 8b38                     mov       edi, dword ptr [eax]
00499165 8bce                     mov       ecx, esi
00499167 ff523c                   call      dword ptr [edx + 0x3c]
0049916a 8b0d64310001             mov       ecx, dword ptr [0x1003164]
00499170 50                       push      eax
00499171 ff5724                   call      dword ptr [edi + 0x24]
00499174 a164310001               mov       eax, dword ptr [0x1003164]
00499179 8b16                     mov       edx, dword ptr [esi]
0049917b 8b38                     mov       edi, dword ptr [eax]
0049917d 8bce                     mov       ecx, esi
0049917f ff5240                   call      dword ptr [edx + 0x40]
00499182 8b0d64310001             mov       ecx, dword ptr [0x1003164]
00499188 50                       push      eax
00499189 ff5724                   call      dword ptr [edi + 0x24]
0049918c 8b0d90070c01             mov       ecx, dword ptr [0x10c0790]
00499192 8b01                     mov       eax, dword ptr [ecx]
00499194 6a03                     push      3
00499196 56                       push      esi
00499197 6aff                     push      -1
00499199 6a01                     push      1
0049919b ff5044                   call      dword ptr [eax + 0x44]
0049919e c686e801000001           mov       byte ptr [esi + 0x1e8], 1
004991a5 5f                       pop       edi
004991a6 5e                       pop       esi
004991a7 5d                       pop       ebp
004991a8 c20400                   ret       4
004991ab cc                       int3      
004991ac cc                       int3      
004991ad cc                       int3      
004991ae cc                       int3      
004991af cc                       int3      
