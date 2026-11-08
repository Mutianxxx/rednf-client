0049a5b7 3bbe0c010000             cmp        edi, dword ptr [esi + 0x10c]
0049a5bd 7470                     je         0x49a62f
0049a5bf 90                       nop        
0049a5c0 8a4719                   mov        al, byte ptr [edi + 0x19]
0049a5c3 84c0                     test       al, al
0049a5c5 755e                     jne        0x49a625
0049a5c7 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a5ca e891d95800               call       0xa27f60
0049a5cf 8b45ec                   mov        eax, dword ptr [ebp - 0x14]
0049a5d2 85c0                     test       eax, eax
0049a5d4 7413                     je         0x49a5e9
0049a5d6 807f1a01                 cmp        byte ptr [edi + 0x1a], 1
0049a5da 750d                     jne        0x49a5e9
0049a5dc 8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
0049a5df 51                       push       ecx
0049a5e0 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a5e3 50                       push       eax
0049a5e4 e8e7b15800               call       0xa257d0
0049a5e9 8a45fa                   mov        al, byte ptr [ebp - 6]
0049a5ec 84c0                     test       al, al
0049a5ee 7409                     je         0x49a5f9
0049a5f0 8b4f10                   mov        ecx, dword ptr [edi + 0x10]
0049a5f3 8bc3                     mov        eax, ebx
0049a5f5 2bc1                     sub        eax, ecx
0049a5f7 eb05                     jmp        0x49a5fe
0049a5f9 8b4710                   mov        eax, dword ptr [edi + 0x10]
0049a5fc 03c3                     add        eax, ebx
0049a5fe 8a5718                   mov        dl, byte ptr [edi + 0x18]
0049a601 8b4dfa                   mov        ecx, dword ptr [ebp - 6]
0049a604 84d2                     test       dl, dl
0049a606 0f95c2                   setne      dl
0049a609 feca                     dec        dl
0049a60b 23d1                     and        edx, ecx
0049a60d 8b4f14                   mov        ecx, dword ptr [edi + 0x14]
0049a610 52                       push       edx
0049a611 034df4                   add        ecx, dword ptr [ebp - 0xc]
0049a614 8b152ca90d01             mov        edx, dword ptr [0x10da92c]
0049a61a 51                       push       ecx
0049a61b 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a61e 50                       push       eax
0049a61f 52                       push       edx
0049a620 e86bc35800               call       0xa26990
0049a625 8b3f                     mov        edi, dword ptr [edi]
0049a627 3bbe0c010000             cmp        edi, dword ptr [esi + 0x10c]
0049a62d 7591                     jne        0x49a5c0
