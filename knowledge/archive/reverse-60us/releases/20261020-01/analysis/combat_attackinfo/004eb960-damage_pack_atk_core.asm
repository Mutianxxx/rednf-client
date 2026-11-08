004eb960  8b16                     mov        edx, dword ptr [esi]
004eb962  8bce                     mov        ecx, esi
004eb964  ff928c010000             call       dword ptr [edx + 0x18c]
004eb96a  85c0                     test       eax, eax
004eb96c  0f95c0                   setne      al
004eb96f  8bcb                     mov        ecx, ebx
004eb971  8845b5                   mov        byte ptr [ebp - 0x4b], al
004eb974  e8377af4ff               call       0x4333b0
004eb979  d99d28feffff             fstp       dword ptr [ebp - 0x1d8]
004eb97f  8d4b1c                   lea        ecx, [ebx + 0x1c]
004eb982  e8d966f1ff               call       0x402060
004eb987  88852cfeffff             mov        byte ptr [ebp - 0x1d4], al
004eb98d  8a4b18                   mov        cl, byte ptr [ebx + 0x18]
004eb990  888d2dfeffff             mov        byte ptr [ebp - 0x1d3], cl
004eb996  8d4b10                   lea        ecx, [ebx + 0x10]
004eb999  e8c266f1ff               call       0x402060
004eb99e  894510                   mov        dword ptr [ebp + 0x10], eax
004eb9a1  db4510                   fild       dword ptr [ebp + 0x10]
004eb9a4  d99d2efeffff             fstp       dword ptr [ebp - 0x1d2]
004eb9aa  8b4b40                   mov        ecx, dword ptr [ebx + 0x40]
004eb9ad  8b01                     mov        eax, dword ptr [ecx]
004eb9af  3bc1                     cmp        eax, ecx
004eb9b1  894510                   mov        dword ptr [ebp + 0x10], eax
004eb9b4  7420                     je         0x4eb9d6
004eb9b6  8b400c                   mov        eax, dword ptr [eax + 0xc]
004eb9b9  83f804                   cmp        eax, 4
004eb9bc  7408                     je         0x4eb9c6
004eb9be  c6840532feffff01         mov        byte ptr [ebp + eax - 0x1ce], 1
004eb9c6  8d4d10                   lea        ecx, [ebp + 0x10]
004eb9c9  e8f278f4ff               call       0x4332c0
004eb9ce  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004eb9d1  3b4340                   cmp        eax, dword ptr [ebx + 0x40]
004eb9d4  75e0                     jne        0x4eb9b6
004eb9d6  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004eb9d9  85c0                     test       eax, eax
004eb9db  7471                     je         0x4eba4e
004eb9dd  c7451000000000           mov        dword ptr [ebp + 0x10], 0
004eb9e4  bf88000000               mov        edi, 0x88
004eb9e9  8da42400000000           lea        esp, [esp]
004eb9f0  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004eb9f3  8a841532feffff           mov        al, byte ptr [ebp + edx - 0x1ce]
004eb9fa  84c0                     test       al, al
004eb9fc  743e                     je         0x4eba3c
004eb9fe  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
004eba01  8b01                     mov        eax, dword ptr [ecx]
004eba03  6a03                     push       3
004eba05  ff9044030000             call       dword ptr [eax + 0x344]
004eba0b  8d4c07e0                 lea        ecx, [edi + eax - 0x20]
004eba0f  8945fc                   mov        dword ptr [ebp - 4], eax
004eba12  e84966f1ff               call       0x402060
004eba17  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004eba1a  89451c                   mov        dword ptr [ebp + 0x1c], eax
004eba1d  db451c                   fild       dword ptr [ebp + 0x1c]
004eba20  03cf                     add        ecx, edi
004eba22  d95d1c                   fstp       dword ptr [ebp + 0x1c]
004eba25  e88679f4ff               call       0x4333b0
004eba2a  d84d1c                   fmul       dword ptr [ebp + 0x1c]
004eba2d  e8125b7100               call       0xc01544
004eba32  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004eba35  8984959ffeffff           mov        dword ptr [ebp + edx*4 - 0x161], eax
004eba3c  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004eba3f  42                       inc        edx
004eba40  83c708                   add        edi, 8
004eba43  81ffa8000000             cmp        edi, 0xa8
004eba49  895510                   mov        dword ptr [ebp + 0x10], edx
004eba4c  7ca2                     jl         0x4eb9f0
004eba4e  8d8b38010000             lea        ecx, [ebx + 0x138]
004eba54  e80766f1ff               call       0x402060
004eba59  8d4b08                   lea        ecx, [ebx + 8]
004eba5c  888536feffff             mov        byte ptr [ebp - 0x1ca], al
004eba62  e8f965f1ff               call       0x402060
004eba67  894510                   mov        dword ptr [ebp + 0x10], eax
004eba6a  db4510                   fild       dword ptr [ebp + 0x10]
004eba6d  8d8b00010000             lea        ecx, [ebx + 0x100]
004eba73  d9                       .byte      0xd9
004eba74  9d                       popfd      
004eba75  37                       aaa        
004eba76  fe                       .byte      0xfe
