0049f090 55                       push      ebp
0049f091 8bec                     mov       ebp, esp
0049f093 56                       push      esi
0049f094 8b7508                   mov       esi, dword ptr [ebp + 8]
0049f097 8b4604                   mov       eax, dword ptr [esi + 4]
0049f09a 57                       push      edi
0049f09b 33ff                     xor       edi, edi
0049f09d 3bc7                     cmp       eax, edi
0049f09f 7409                     je        0x49f0aa
0049f0a1 50                       push      eax
0049f0a2 e8360f7600               call      0xbfffdd
0049f0a7 83c404                   add       esp, 4
0049f0aa 8d4d10                   lea       ecx, [ebp + 0x10]
0049f0ad 51                       push      ecx
0049f0ae 33c0                     xor       eax, eax
0049f0b0 6a01                     push      1
0049f0b2 50                       push      eax
0049f0b3 8bce                     mov       ecx, esi
0049f0b5 897e04                   mov       dword ptr [esi + 4], edi
0049f0b8 897e08                   mov       dword ptr [esi + 8], edi
0049f0bb 897e0c                   mov       dword ptr [esi + 0xc], edi
0049f0be e89d6ef6ff               call      0x405f60
0049f0c3 8b4e04                   mov       ecx, dword ptr [esi + 4]
0049f0c6 3bcf                     cmp       ecx, edi
0049f0c8 7504                     jne       0x49f0ce
0049f0ca 33d2                     xor       edx, edx
0049f0cc eb08                     jmp       0x49f0d6
0049f0ce 8b5608                   mov       edx, dword ptr [esi + 8]
0049f0d1 2bd1                     sub       edx, ecx
0049f0d3 c1fa02                   sar       edx, 2
0049f0d6 3bcf                     cmp       ecx, edi
0049f0d8 741c                     je        0x49f0f6
0049f0da 8b460c                   mov       eax, dword ptr [esi + 0xc]
0049f0dd 2bc1                     sub       eax, ecx
0049f0df c1f802                   sar       eax, 2
0049f0e2 3bd0                     cmp       edx, eax
0049f0e4 7310                     jae       0x49f0f6
0049f0e6 8b4608                   mov       eax, dword ptr [esi + 8]
0049f0e9 8b5514                   mov       edx, dword ptr [ebp + 0x14]
0049f0ec 8910                     mov       dword ptr [eax], edx
0049f0ee 83c004                   add       eax, 4
0049f0f1 894608                   mov       dword ptr [esi + 8], eax
0049f0f4 eb11                     jmp       0x49f107
0049f0f6 8b4608                   mov       eax, dword ptr [esi + 8]
0049f0f9 8d4d14                   lea       ecx, [ebp + 0x14]
0049f0fc 51                       push      ecx
0049f0fd 6a01                     push      1
0049f0ff 50                       push      eax
0049f100 8bce                     mov       ecx, esi
0049f102 e8596ef6ff               call      0x405f60
0049f107 8b5604                   mov       edx, dword ptr [esi + 4]
0049f10a 3bd7                     cmp       edx, edi
0049f10c 7504                     jne       0x49f112
0049f10e 33c9                     xor       ecx, ecx
0049f110 eb08                     jmp       0x49f11a
0049f112 8b4e08                   mov       ecx, dword ptr [esi + 8]
0049f115 2bca                     sub       ecx, edx
0049f117 c1f902                   sar       ecx, 2
0049f11a 3bd7                     cmp       edx, edi
0049f11c 741c                     je        0x49f13a
0049f11e 8b460c                   mov       eax, dword ptr [esi + 0xc]
0049f121 2bc2                     sub       eax, edx
0049f123 c1f802                   sar       eax, 2
0049f126 3bc8                     cmp       ecx, eax
0049f128 7310                     jae       0x49f13a
0049f12a 8b4608                   mov       eax, dword ptr [esi + 8]
0049f12d 8b5518                   mov       edx, dword ptr [ebp + 0x18]
0049f130 8910                     mov       dword ptr [eax], edx
0049f132 83c004                   add       eax, 4
0049f135 894608                   mov       dword ptr [esi + 8], eax
0049f138 eb11                     jmp       0x49f14b
0049f13a 8b4608                   mov       eax, dword ptr [esi + 8]
0049f13d 8d4d18                   lea       ecx, [ebp + 0x18]
0049f140 51                       push      ecx
0049f141 6a01                     push      1
0049f143 50                       push      eax
0049f144 8bce                     mov       ecx, esi
0049f146 e8156ef6ff               call      0x405f60
0049f14b 8b5604                   mov       edx, dword ptr [esi + 4]
0049f14e 3bd7                     cmp       edx, edi
0049f150 7504                     jne       0x49f156
0049f152 33c9                     xor       ecx, ecx
0049f154 eb08                     jmp       0x49f15e
0049f156 8b4e08                   mov       ecx, dword ptr [esi + 8]
0049f159 2bca                     sub       ecx, edx
0049f15b c1f902                   sar       ecx, 2
0049f15e 3bd7                     cmp       edx, edi
0049f160 741c                     je        0x49f17e
0049f162 8b460c                   mov       eax, dword ptr [esi + 0xc]
0049f165 2bc2                     sub       eax, edx
0049f167 c1f802                   sar       eax, 2
0049f16a 3bc8                     cmp       ecx, eax
0049f16c 7310                     jae       0x49f17e
0049f16e 8b4608                   mov       eax, dword ptr [esi + 8]
0049f171 8b551c                   mov       edx, dword ptr [ebp + 0x1c]
0049f174 8910                     mov       dword ptr [eax], edx
0049f176 83c004                   add       eax, 4
0049f179 894608                   mov       dword ptr [esi + 8], eax
0049f17c eb11                     jmp       0x49f18f
0049f17e 8b4608                   mov       eax, dword ptr [esi + 8]
0049f181 8d4d1c                   lea       ecx, [ebp + 0x1c]
0049f184 51                       push      ecx
0049f185 6a01                     push      1
0049f187 50                       push      eax
0049f188 8bce                     mov       ecx, esi
0049f18a e8d16df6ff               call      0x405f60
0049f18f 8b5604                   mov       edx, dword ptr [esi + 4]
0049f192 3bd7                     cmp       edx, edi
0049f194 7504                     jne       0x49f19a
0049f196 33c9                     xor       ecx, ecx
0049f198 eb08                     jmp       0x49f1a2
0049f19a 8b4e08                   mov       ecx, dword ptr [esi + 8]
0049f19d 2bca                     sub       ecx, edx
0049f19f c1f902                   sar       ecx, 2
0049f1a2 3bd7                     cmp       edx, edi
0049f1a4 741c                     je        0x49f1c2
0049f1a6 8b460c                   mov       eax, dword ptr [esi + 0xc]
0049f1a9 2bc2                     sub       eax, edx
0049f1ab c1f802                   sar       eax, 2
0049f1ae 3bc8                     cmp       ecx, eax
0049f1b0 7310                     jae       0x49f1c2
0049f1b2 8b4608                   mov       eax, dword ptr [esi + 8]
0049f1b5 8b5520                   mov       edx, dword ptr [ebp + 0x20]
0049f1b8 8910                     mov       dword ptr [eax], edx
0049f1ba 83c004                   add       eax, 4
0049f1bd 894608                   mov       dword ptr [esi + 8], eax
0049f1c0 eb11                     jmp       0x49f1d3
0049f1c2 8b4608                   mov       eax, dword ptr [esi + 8]
0049f1c5 8d4d20                   lea       ecx, [ebp + 0x20]
0049f1c8 51                       push      ecx
0049f1c9 6a01                     push      1
0049f1cb 50                       push      eax
0049f1cc 8bce                     mov       ecx, esi
0049f1ce e88d6df6ff               call      0x405f60
0049f1d3 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049f1d6 3bcf                     cmp       ecx, edi
0049f1d8 743a                     je        0x49f214
0049f1da 8b11                     mov       edx, dword ptr [ecx]
0049f1dc ff92a0020000             call      dword ptr [edx + 0x2a0]
0049f1e2 8bf8                     mov       edi, eax
0049f1e4 8b07                     mov       eax, dword ptr [edi]
0049f1e6 8bcf                     mov       ecx, edi
0049f1e8 ff503c                   call      dword ptr [eax + 0x3c]
0049f1eb 8d4d14                   lea       ecx, [ebp + 0x14]
0049f1ee 51                       push      ecx
0049f1ef 8bce                     mov       ecx, esi
0049f1f1 894514                   mov       dword ptr [ebp + 0x14], eax
0049f1f4 e8277ff6ff               call      0x407120
0049f1f9 8b17                     mov       edx, dword ptr [edi]
0049f1fb 8bcf                     mov       ecx, edi
0049f1fd ff5240                   call      dword ptr [edx + 0x40]
0049f200 894514                   mov       dword ptr [ebp + 0x14], eax
0049f203 8d4514                   lea       eax, [ebp + 0x14]
0049f206 50                       push      eax
0049f207 8bce                     mov       ecx, esi
0049f209 e8127ff6ff               call      0x407120
0049f20e 5f                       pop       edi
0049f20f 5e                       pop       esi
0049f210 5d                       pop       ebp
0049f211 c21c00                   ret       0x1c
0049f214 8d4d14                   lea       ecx, [ebp + 0x14]
0049f217 51                       push      ecx
0049f218 bfffff0000               mov       edi, 0xffff
0049f21d 8bce                     mov       ecx, esi
0049f21f 897d14                   mov       dword ptr [ebp + 0x14], edi
0049f222 e8f97ef6ff               call      0x407120
0049f227 8d5514                   lea       edx, [ebp + 0x14]
0049f22a 52                       push      edx
0049f22b 8bce                     mov       ecx, esi
0049f22d 897d14                   mov       dword ptr [ebp + 0x14], edi
0049f230 e8eb7ef6ff               call      0x407120
0049f235 5f                       pop       edi
0049f236 5e                       pop       esi
0049f237 5d                       pop       ebp
0049f238 c21c00                   ret       0x1c
