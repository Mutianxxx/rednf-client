00729b56 8d8e64150000             lea        ecx, [esi + 0x1564]
00729b5c e89fd33d00               call       0xb06f00
00729b61 50                       push       eax
00729b62 8d8e00330000             lea        ecx, [esi + 0x3300]
00729b68 e843843200               call       0xa51fb0
00729b6d 84c0                     test       al, al
00729b6f 740a                     je         0x729b7b
00729b71 8b06                     mov        eax, dword ptr [esi]
00729b73 8bce                     mov        ecx, esi
00729b75 ff90a0010000             call       dword ptr [eax + 0x1a0]
