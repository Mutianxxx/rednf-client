0073d5c0  92                       xchg       edx, eax
0073d5c1  a17300cfa1               mov        eax, dword ptr [0xa1cf0073]
0073d5c6  7300                     jae        0x73d5c8
0073d5c8  d7                       xlatb      
0073d5c9  a973001dd4               test       eax, 0xd41d0073
0073d5ce  7300                     jae        0x73d5d0
0073d5d0  2cb4                     sub        al, 0xb4
0073d5d2  7300                     jae        0x73d5d4
0073d5d4  1dd47300e8               sbb        eax, 0xe80073d4
0073d5d9  b373                     mov        bl, 0x73
0073d5db  001dd473009a             add        byte ptr [0x9a0073d4], bl
0073d5e1  d37300                   sal        dword ptr [ebx], cl