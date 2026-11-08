00727620  e84b67deff               call       0x50dd70
00727625  8b4dd8                   mov        ecx, dword ptr [ebp - 0x28]
00727628  8b01                     mov        eax, dword ptr [ecx]
0072762a  8b16                     mov        edx, dword ptr [esi]
0072762c  8bce                     mov        ecx, esi
0072762e  8945f0                   mov        dword ptr [ebp - 0x10], eax
00727631  ff92c0000000             call       dword ptr [edx + 0xc0]
00727637  8b5dd8                   mov        ebx, dword ptr [ebp - 0x28]
0072763a  50                       push       eax
0072763b  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
0072763e  8bcb                     mov        ecx, ebx
00727640  ff90bc000000             call       dword ptr [eax + 0xbc]
00727646  8b07                     mov        eax, dword ptr [edi]
00727648  8b1b                     mov        ebx, dword ptr [ebx]
0072764a  8bcf                     mov        ecx, edi
0072764c  ff90e4000000             call       dword ptr [eax + 0xe4]
00727652  99                       cdq        
00727653  2bc2                     sub        eax, edx
00727655  8b17                     mov        edx, dword ptr [edi]
00727657  d1f8                     sar        eax, 1
00727659  8bcf                     mov        ecx, edi
0072765b  8945f0                   mov        dword ptr [ebp - 0x10], eax
0072765e  ff929c000000             call       dword ptr [edx + 0x9c]
00727664  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00727667  8b7de0                   mov        edi, dword ptr [ebp - 0x20]
0072766a  03c8                     add        ecx, eax
0072766c  8b07                     mov        eax, dword ptr [edi]
0072766e  51                       push       ecx
0072766f  8bcf                     mov        ecx, edi
00727671  ff9098000000             call       dword ptr [eax + 0x98]
00727677  8b17                     mov        edx, dword ptr [edi]
00727679  50                       push       eax
0072767a  8bcf                     mov        ecx, edi
0072767c  ff9294000000             call       dword ptr [edx + 0x94]
00727682  8b4dd8                   mov        ecx, dword ptr [ebp - 0x28]
00727685  50                       push       eax
00727686  ff9388000000             call       dword ptr [ebx + 0x88]
0072768c  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
0072768f  8b8ecc2b0000             mov        ecx, dword ptr [esi + 0x2bcc]
00727695  8b38                     mov        edi, dword ptr [eax]
00727697  8d55d0                   lea        edx, [ebp - 0x30]
0072769a  894dd0                   mov        dword ptr [ebp - 0x30], ecx
0072769d  52                       push       edx
0072769e  8d4de4                   lea        ecx, [ebp - 0x1c]
007276a1  897de4                   mov        dword ptr [ebp - 0x1c], edi
007276a4  e8b7cee3ff               call       0x564560
007276a9  33db                     xor        ebx, ebx
007276ab  84c0                     test       al, al
007276ad  0f85befdffff             jne        0x727471
007276b3  8b8efc2b0000             mov        ecx, dword ptr [esi + 0x2bfc]
007276b9  3bcb                     cmp        ecx, ebx
007276bb  740c                     je         0x7276c9
007276bd  682c010000               push       0x12c
007276c2  6a03                     push       3
007276c4  e8b73bffff               call       0x71b280
007276c9  c7                       .byte      0xc7
007276ca  86ec                     xchg       ah, ch
007276cc  2b00                     sub        eax, dword ptr [eax]
007276ce  00ff                     add        bh, bh