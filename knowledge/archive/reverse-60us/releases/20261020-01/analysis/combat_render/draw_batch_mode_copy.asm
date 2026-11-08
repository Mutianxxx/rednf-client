00b091ff 8b4324                   mov        eax, dword ptr [ebx + 0x24]
00b09202 8d1480                   lea        edx, [eax + eax*4]
00b09205 8b8348030500             mov        eax, dword ptr [ebx + 0x50348]
00b0920b 8984d340210000           mov        dword ptr [ebx + edx*8 + 0x2140], eax
00b09212 8b8b4c030500             mov        ecx, dword ptr [ebx + 0x5034c]
00b09218 898cd344210000           mov        dword ptr [ebx + edx*8 + 0x2144], ecx