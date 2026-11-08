00499100  8b81f8000000             mov        eax, dword ptr [ecx + 0xf8]
00499106  8b08                     mov        ecx, dword ptr [eax]
00499108  85c9                     test       ecx, ecx
0049910a  7405                     je         0x499111
0049910c  0fbe4134                 movsx      eax, byte ptr [ecx + 0x34]
00499110  c3                       ret        
00499111  0fbe403c                 movsx      eax, byte ptr [eax + 0x3c]
00499115  c3                       ret        
