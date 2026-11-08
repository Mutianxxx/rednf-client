00748db4  6b8c7400a18c7400         imul       ecx, dword ptr [esp + esi*2 + 0x748ca100], 0
00748dbc  d7                       xlatb      
00748dbd  8c                       .byte      0x8c
00748dbe  7400                     je         0x748dc0
00748dc0  0d8d74003f               or         eax, 0x3f00748d
00748dc5  8d740071                 lea        esi, [eax + eax + 0x71]
00748dc9  8d                       .byte      0x8d
00748dca  7400                     je         0x748dcc