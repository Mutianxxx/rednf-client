00404C1D 8db42479010000           lea esi, [esp + 0x179]
00404C24 baa0f4a500               mov edx, 0xa5f4a0
00404C29 c646ffe8                 mov byte ptr [esi - 1], 0xe8
00404C2D 89f1                     mov ecx, esi
00404C2F 68c7373b01               push 0x13b37c7
00404C34 e8e93a0000               call 0x408722
00404C39 58                       pop eax
00404C3A c64604e9                 mov byte ptr [esi + 4], 0xe9
00404C3E 8d8c247e010000           lea ecx, [esp + 0x17e]
00404C45 ba58974d00               mov edx, 0x4d9758
00404C4A 68cc373b01               push 0x13b37cc
00404C4F e8ce3a0000               call 0x408722
00404C54 58                       pop eax
00404C55 89f9                     mov ecx, edi
00404C57 bac2373b01               mov edx, 0x13b37c2
00404C5C 6a0a                     push 0xa
00404C5E 5e                       pop esi
00404C5F 56                       push esi
00404C60 8d84247c010000           lea eax, [esp + 0x17c]
00404C67 50                       push eax
00404C68 56                       push esi
00404C69 6827674300               push 0x436727
00404C6E e813250000               call 0x407186
00404C73 83c410                   add esp, 0x10
00404C76 6685c0                   test ax, ax
00404C79 0f85d50b0000             jne 0x405854
