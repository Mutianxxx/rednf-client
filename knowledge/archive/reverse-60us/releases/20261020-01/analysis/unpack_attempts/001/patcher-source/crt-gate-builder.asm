00402120 8b542404                 mov edx, dword ptr [esp + 4]
00402124 8db424b00f0000           lea esi, [esp + 0xfb0]
0040212B 89f1                     mov ecx, esi
0040212D 6a40                     push 0x40
0040212F 6800100000               push 0x1000
00402134 e8c9690000               call 0x408b02
00402139 58                       pop eax
0040213A 59                       pop ecx
0040213B 66837e0400               cmp word ptr [esi + 4], 0
00402140 0f85da230000             jne 0x404520
00402146 8bb424b00f0000           mov esi, dword ptr [esp + 0xfb0]
0040214D 31c9                     xor ecx, ecx
0040214F 8d842400070000           lea eax, [esp + 0x700]
00402156 66c78424bc130000ff05     mov word ptr [esp + 0x13bc], 0x5ff
00402160 8d7e20                   lea edi, [esi + 0x20]
00402163 89fa                     mov edx, edi
00402165 d3ea                     shr edx, cl
00402167 83c108                   add ecx, 8
0040216A 8810                     mov byte ptr [eax], dl
0040216C 40                       inc eax
0040216D 83f920                   cmp ecx, 0x20
00402170 75f1                     jne 0x402163
00402172 8b842400070000           mov eax, dword ptr [esp + 0x700]
00402179 8d5624                   lea edx, [esi + 0x24]
0040217C 31c9                     xor ecx, ecx
0040217E 8d9c2408060000           lea ebx, [esp + 0x608]
00402185 898424be130000           mov dword ptr [esp + 0x13be], eax
0040218C 66c78424c2130000803d     mov word ptr [esp + 0x13c2], 0x3d80
00402196 89d0                     mov eax, edx
00402198 d3e8                     shr eax, cl
0040219A 83c108                   add ecx, 8
0040219D 8803                     mov byte ptr [ebx], al
0040219F 43                       inc ebx
004021A0 83f920                   cmp ecx, 0x20
004021A3 75f1                     jne 0x402196
004021A5 8b842408060000           mov eax, dword ptr [esp + 0x608]
004021AC 31c9                     xor ecx, ecx
004021AE 8d9c2488070000           lea ebx, [esp + 0x788]
004021B5 89942464030000           mov dword ptr [esp + 0x364], edx
004021BC 898424c4130000           mov dword ptr [esp + 0x13c4], eax
004021C3 b86450c000               mov eax, 0xc05064
004021C8 66c78424c81300000074     mov word ptr [esp + 0x13c8], 0x7400
004021D2 c68424ca130000f1         mov byte ptr [esp + 0x13ca], 0xf1
004021DA c78424cb1300006a6c6888   mov dword ptr [esp + 0x13cb], 0x88686c6a
004021E5 c78424ce13000088d5e900   mov dword ptr [esp + 0x13ce], 0xe9d588
004021F0 c68424d2130000e9         mov byte ptr [esp + 0x13d2], 0xe9
004021F8 29f0                     sub eax, esi
004021FA 89c2                     mov edx, eax
004021FC d3ea                     shr edx, cl
004021FE 83c108                   add ecx, 8
00402201 8813                     mov byte ptr [ebx], dl
00402203 43                       inc ebx
00402204 83f920                   cmp ecx, 0x20
00402207 75f1                     jne 0x4021fa
00402209 8b842488070000           mov eax, dword ptr [esp + 0x788]
00402210 8b4c2404                 mov ecx, dword ptr [esp + 4]
00402214 89f2                     mov edx, esi
00402216 898424d3130000           mov dword ptr [esp + 0x13d3], eax
0040221D 6a1b                     push 0x1b
0040221F 8d8424c0130000           lea eax, [esp + 0x13c0]
00402226 50                       push eax
00402227 e8d94f0000               call 0x407205
0040222C 59                       pop ecx
0040222D 5a                       pop edx
0040222E 6685c0                   test ax, ax
00402231 8d9c24a00b0000           lea ebx, [esp + 0xba0]
00402238 0f85e2220000             jne 0x404520
0040223E 81c683af3fff             add esi, 0xff3faf83
00402244 31c9                     xor ecx, ecx
00402246 8d9424b8110000           lea edx, [esp + 0x11b8]
0040224D c68424a00b0000e9         mov byte ptr [esp + 0xba0], 0xe9
00402255 66c78424a50b00009090     mov word ptr [esp + 0xba5], 0x9090
0040225F 89f0                     mov eax, esi
00402261 d3e8                     shr eax, cl
00402263 83c108                   add ecx, 8
00402266 8802                     mov byte ptr [edx], al
00402268 42                       inc edx
00402269 83f920                   cmp ecx, 0x20
0040226C 75f1                     jne 0x40225f
0040226E 8b8424b8110000           mov eax, dword ptr [esp + 0x11b8]
00402275 8b4c2404                 mov ecx, dword ptr [esp + 4]
00402279 ba7850c000               mov edx, 0xc05078
0040227E 898424a10b0000           mov dword ptr [esp + 0xba1], eax
00402285 6a07                     push 7
00402287 53                       push ebx
00402288 e8784f0000               call 0x407205
0040228D 59                       pop ecx
0040228E 5a                       pop edx
0040228F 6685c0                   test ax, ax
00402292 0f8588220000             jne 0x404520
