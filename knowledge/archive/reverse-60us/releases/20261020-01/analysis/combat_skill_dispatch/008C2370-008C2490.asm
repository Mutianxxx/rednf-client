008c2370  07                       pop        es
008c2371  1900                     sbb        dword ptr [eax], eax
008c2373  83c410                   add        esp, 0x10
008c2376  50                       push       eax
008c2377  b928070001               mov        ecx, 0x1000728
008c237c  e8efc7b4ff               call       0x40eb70
008c2381  47                       inc        edi
008c2382  ebcc                     jmp        0x8c2350
008c2384  0fb6550b                 movzx      edx, byte ptr [ebp + 0xb]
008c2388  8b06                     mov        eax, dword ptr [esi]
008c238a  6a01                     push       1
008c238c  6a01                     push       1
008c238e  8d4d94                   lea        ecx, [ebp - 0x6c]
008c2391  51                       push       ecx
008c2392  52                       push       edx
008c2393  8bce                     mov        ecx, esi
008c2395  ff902c020000             call       dword ptr [eax + 0x22c]
008c239b  8b7df0                   mov        edi, dword ptr [ebp - 0x10]
008c239e  3bfb                     cmp        edi, ebx
008c23a0  743e                     je         0x8c23e0
008c23a2  8b06                     mov        eax, dword ptr [esi]
008c23a4  6a11                     push       0x11
008c23a6  8bce                     mov        ecx, esi
008c23a8  ff502c                   call       dword ptr [eax + 0x2c]
008c23ab  84c0                     test       al, al
008c23ad  741e                     je         0x8c23cd
008c23af  8a450b                   mov        al, byte ptr [ebp + 0xb]
008c23b2  3c03                     cmp        al, 3
008c23b4  7417                     je         0x8c23cd
008c23b6  3c04                     cmp        al, 4
008c23b8  7413                     je         0x8c23cd
008c23ba  3c05                     cmp        al, 5
008c23bc  740f                     je         0x8c23cd
008c23be  3c09                     cmp        al, 9
008c23c0  740b                     je         0x8c23cd
008c23c2  83ff01                   cmp        edi, 1
008c23c5  7506                     jne        0x8c23cd
008c23c7  837dd0ff                 cmp        dword ptr [ebp - 0x30], -1
008c23cb  7513                     jne        0x8c23e0
008c23cd  8b45c8                   mov        eax, dword ptr [ebp - 0x38]
008c23d0  8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
008c23d3  8b16                     mov        edx, dword ptr [esi]
008c23d5  50                       push       eax
008c23d6  51                       push       ecx
008c23d7  57                       push       edi
008c23d8  8bce                     mov        ecx, esi
008c23da  ff921c010000             call       dword ptr [edx + 0x11c]
008c23e0  8b16                     mov        edx, dword ptr [esi]
008c23e2  8bce                     mov        ecx, esi
008c23e4  ff9294020000             call       dword ptr [edx + 0x294]
008c23ea  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c23ee  3bc1                     cmp        eax, ecx
008c23f0  750a                     jne        0x8c23fc
008c23f2  8b16                     mov        edx, dword ptr [esi]
008c23f4  8bce                     mov        ecx, esi
008c23f6  ff9298020000             call       dword ptr [edx + 0x298]
008c23fc  8bce                     mov        ecx, esi
008c23fe  e88d9cbdff               call       0x49c090
008c2403  84c0                     test       al, al
008c2405  0f846a340000             je         0x8c5875
008c240b  8b06                     mov        eax, dword ptr [esi]
008c240d  6a01                     push       1
008c240f  6a01                     push       1
008c2411  8bce                     mov        ecx, esi
008c2413  ff5048                   call       dword ptr [eax + 0x48]
008c2416  8bc8                     mov        ecx, eax
008c2418  e853f7c4ff               call       0x511b70
008c241d  e953340000               jmp        0x8c5875
008c2422  8b16                     mov        edx, dword ptr [esi]
008c2424  33db                     xor        ebx, ebx
008c2426  8d450c                   lea        eax, [ebp + 0xc]
008c2429  50                       push       eax
008c242a  8bce                     mov        ecx, esi
008c242c  895d0c                   mov        dword ptr [ebp + 0xc], ebx
008c242f  895d08                   mov        dword ptr [ebp + 8], ebx
008c2432  895d10                   mov        dword ptr [ebp + 0x10], ebx
008c2435  ff5254                   call       dword ptr [edx + 0x54]
008c2438  8b16                     mov        edx, dword ptr [esi]
008c243a  8d4508                   lea        eax, [ebp + 8]
008c243d  50                       push       eax
008c243e  8bce                     mov        ecx, esi
008c2440  ff5254                   call       dword ptr [edx + 0x54]
008c2443  8b16                     mov        edx, dword ptr [esi]
008c2445  8d4510                   lea        eax, [ebp + 0x10]
008c2448  50                       push       eax
008c2449  8bce                     mov        ecx, esi
008c244b  ff5254                   call       dword ptr [edx + 0x54]
008c244e  8b8660a01000             mov        eax, dword ptr [esi + 0x10a060]
008c2454  3bc3                     cmp        eax, ebx
008c2456  0f84f4390000             je         0x8c5e50
008c245c  3998b0000000             cmp        dword ptr [eax + 0xb0], ebx
008c2462  0f84e8390000             je         0x8c5e50
008c2468  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
008c246b  51                       push       ecx
008c246c  8b0d3c310001             mov        ecx, dword ptr [0x100313c]
008c2472  e85998c9ff               call       0x55bcd0
008c2477  8bf8                     mov        edi, eax
008c2479  3bfb                     cmp        edi, ebx
008c247b  0f8456010000             je         0x8c25d7
008c2481  8b8704020000             mov        eax, dword ptr [edi + 0x204]
008c2487  3bc3                     cmp        eax, ebx
008c2489  0f8442010000             je         0x8c25d1
008c248f  8b                       .byte      0x8b