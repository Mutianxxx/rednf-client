00404DB8 8db424b8010000           lea esi, [esp + 0x1b8]
00404DBF 89fa                     mov edx, edi
00404DC1 89f1                     mov ecx, esi
00404DC3 6a40                     push 0x40
00404DC5 6800100000               push 0x1000
00404DCA e8333d0000               call 0x408b02
00404DCF 58                       pop eax
00404DD0 59                       pop ecx
00404DD1 66837e0400               cmp word ptr [esi + 4], 0
00404DD6 0f85780a0000             jne 0x405854
00404DDC 8b9c24b8010000           mov ebx, dword ptr [esp + 0x1b8]
00404DE3 8db424b00f0000           lea esi, [esp + 0xfb0]
00404DEA 89f1                     mov ecx, esi
00404DEC 89da                     mov edx, ebx
00404DEE e84ea30000               call 0x40f141
00404DF3 8d8424bc130000           lea eax, [esp + 0x13bc]
00404DFA b9e4000000               mov ecx, 0xe4
00404DFF 89da                     mov edx, ebx
00404E01 89c7                     mov edi, eax
00404E03 f3a4                     rep movsb byte ptr es:[edi], byte ptr [esi]
00404E05 895c2408                 mov dword ptr [esp + 8], ebx
00404E09 8b7c2404                 mov edi, dword ptr [esp + 4]
00404E0D 89f9                     mov ecx, edi
00404E0F 68e4000000               push 0xe4
00404E14 50                       push eax
00404E15 e8eb230000               call 0x407205
00404E1A 59                       pop ecx
00404E1B 5a                       pop edx
00404E1C 6685c0                   test ax, ax
00404E1F 0f852f0a0000             jne 0x405854
00404E25 8b542408                 mov edx, dword ptr [esp + 8]
00404E29 8d8c2493030000           lea ecx, [esp + 0x393]
00404E30 c641ffe9                 mov byte ptr [ecx - 1], 0xe9
00404E34 68d5a14f00               push 0x4fa1d5
00404E39 e8e4380000               call 0x408722
00404E3E 58                       pop eax
00404E3F 8d842492030000           lea eax, [esp + 0x392]
00404E46 89f9                     mov ecx, edi
00404E48 bad0a14f00               mov edx, 0x4fa1d0
00404E4D 6a05                     push 5
00404E4F 5e                       pop esi
00404E50 56                       push esi
00404E51 50                       push eax
00404E52 56                       push esi
00404E53 689b754300               push 0x43759b
00404E58 e829230000               call 0x407186
00404E5D 83c410                   add esp, 0x10
00404E60 6685c0                   test ax, ax
00404E63 0f85eb090000             jne 0x405854
