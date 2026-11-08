0049dc70 56                       push      esi
0049dc71 8bf1                     mov       esi, ecx
0049dc73 e888ff0400               call      0x4edc00
0049dc78 8bce                     mov       ecx, esi
0049dc7a e8e1fcffff               call      0x49d960
0049dc7f 8a86d8070000             mov       al, byte ptr [esi + 0x7d8]
0049dc85 84c0                     test      al, al
0049dc87 752f                     jne       0x49dcb8
0049dc89 83bed407000008           cmp       dword ptr [esi + 0x7d4], 8
0049dc90 7208                     jb        0x49dc9a
0049dc92 8b86c0070000             mov       eax, dword ptr [esi + 0x7c0]
0049dc98 eb06                     jmp       0x49dca0
0049dc9a 8d86c0070000             lea       eax, [esi + 0x7c0]
0049dca0 8b16                     mov       edx, dword ptr [esi]
0049dca2 6a00                     push      0
0049dca4 6a00                     push      0
0049dca6 6aff                     push      -1
0049dca8 50                       push      eax
0049dca9 8bce                     mov       ecx, esi
0049dcab ff920c010000             call      dword ptr [edx + 0x10c]
0049dcb1 c686d807000001           mov       byte ptr [esi + 0x7d8], 1
0049dcb8 8bce                     mov       ecx, esi
0049dcba e8d1e3ffff               call      0x49c090
0049dcbf 84c0                     test      al, al
0049dcc1 7422                     je        0x49dce5
0049dcc3 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
0049dcc9 8b4878                   mov       ecx, dword ptr [eax + 0x78]
0049dccc 85c9                     test      ecx, ecx
0049dcce 7415                     je        0x49dce5
0049dcd0 8b11                     mov       edx, dword ptr [ecx]
0049dcd2 ff5234                   call      dword ptr [edx + 0x34]
0049dcd5 84c0                     test      al, al
0049dcd7 750c                     jne       0x49dce5
0049dcd9 8b06                     mov       eax, dword ptr [esi]
0049dcdb 6a00                     push      0
0049dcdd 8bce                     mov       ecx, esi
0049dcdf ff9064010000             call      dword ptr [eax + 0x164]
0049dce5 8b8e20080000             mov       ecx, dword ptr [esi + 0x820]
0049dceb 85c9                     test      ecx, ecx
0049dced 741a                     je        0x49dd09
0049dcef 8b8624080000             mov       eax, dword ptr [esi + 0x824]
0049dcf5 2bc1                     sub       eax, ecx
0049dcf7 c1f805                   sar       eax, 5
0049dcfa 85c0                     test      eax, eax
0049dcfc 740b                     je        0x49dd09
0049dcfe 8b16                     mov       edx, dword ptr [esi]
0049dd00 8bce                     mov       ecx, esi
0049dd02 5e                       pop       esi
0049dd03 ffa264030000             jmp       dword ptr [edx + 0x364]
0049dd09 5e                       pop       esi
0049dd0a c3                       ret       
0049dd0b cc                       int3      
