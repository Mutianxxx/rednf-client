0049a359 8b860c010000             mov        eax, dword ptr [esi + 0x10c]
0049a35f 8b38                     mov        edi, dword ptr [eax]
0049a361 3bf8                     cmp        edi, eax
0049a363 7476                     je         0x49a3db
0049a365 8b4708                   mov        eax, dword ptr [edi + 8]
0049a368 85c0                     test       eax, eax
0049a36a 7d6f                     jge        0x49a3db
0049a36c 8a4719                   mov        al, byte ptr [edi + 0x19]
0049a36f 84c0                     test       al, al
0049a371 755e                     jne        0x49a3d1
0049a373 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a376 e8e5db5800               call       0xa27f60
0049a37b 8b45ec                   mov        eax, dword ptr [ebp - 0x14]
0049a37e 85c0                     test       eax, eax
0049a380 7413                     je         0x49a395
0049a382 807f1a01                 cmp        byte ptr [edi + 0x1a], 1
0049a386 750d                     jne        0x49a395
0049a388 8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
0049a38b 51                       push       ecx
0049a38c 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a38f 50                       push       eax
0049a390 e83bb45800               call       0xa257d0
0049a395 8a45fa                   mov        al, byte ptr [ebp - 6]
0049a398 84c0                     test       al, al
0049a39a 7409                     je         0x49a3a5
0049a39c 8b4f10                   mov        ecx, dword ptr [edi + 0x10]
0049a39f 8bc3                     mov        eax, ebx
0049a3a1 2bc1                     sub        eax, ecx
0049a3a3 eb05                     jmp        0x49a3aa
0049a3a5 8b4710                   mov        eax, dword ptr [edi + 0x10]
0049a3a8 03c3                     add        eax, ebx
0049a3aa 8a5718                   mov        dl, byte ptr [edi + 0x18]
0049a3ad 8b4dfa                   mov        ecx, dword ptr [ebp - 6]
0049a3b0 84d2                     test       dl, dl
0049a3b2 0f95c2                   setne      dl
0049a3b5 feca                     dec        dl
0049a3b7 23d1                     and        edx, ecx
0049a3b9 8b4f14                   mov        ecx, dword ptr [edi + 0x14]
0049a3bc 52                       push       edx
0049a3bd 034df4                   add        ecx, dword ptr [ebp - 0xc]
0049a3c0 8b152ca90d01             mov        edx, dword ptr [0x10da92c]
0049a3c6 51                       push       ecx
0049a3c7 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
0049a3ca 50                       push       eax
0049a3cb 52                       push       edx
0049a3cc e8bfc55800               call       0xa26990
0049a3d1 8b3f                     mov        edi, dword ptr [edi]
0049a3d3 3bbe0c010000             cmp        edi, dword ptr [esi + 0x10c]
0049a3d9 758a                     jne        0x49a365