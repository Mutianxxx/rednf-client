0072afb4  0000                     add        byte ptr [eax], al
0072afb6  8d8da4fcffff             lea        ecx, [ebp - 0x35c]
0072afbc  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0072afc3  e8889df1ff               call       0x644d50
0072afc8  8bcf                     mov        ecx, edi
0072afca  e89170cdff               call       0x402060
0072afcf  83f816                   cmp        eax, 0x16
0072afd2  0f8500010000             jne        0x72b0d8
0072afd8  8b96202f0000             mov        edx, dword ptr [esi + 0x2f20]
0072afde  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
0072afe4  4a                       dec        edx
0072afe5  3bc2                     cmp        eax, edx
0072afe7  0f8dce000000             jge        0x72b0bb
0072afed  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
0072aff3  8b8924010000             mov        ecx, dword ptr [ecx + 0x124]
0072aff9  3b0c854497d700           cmp        ecx, dword ptr [eax*4 + 0xd79744]
0072b000  0f8cb5000000             jl         0x72b0bb
0072b006  8b16                     mov        edx, dword ptr [esi]
0072b008  6a01                     push       1
0072b00a  6a08                     push       8
0072b00c  8bce                     mov        ecx, esi
0072b00e  ff927c060000             call       dword ptr [edx + 0x67c]
0072b014  8bc8                     mov        ecx, eax
0072b016  e85542e2ff               call       0x54f270
0072b01b  8b06                     mov        eax, dword ptr [esi]
0072b01d  53                       push       ebx
0072b01e  6a08                     push       8
0072b020  8bce                     mov        ecx, esi
0072b022  ff903c070000             call       dword ptr [eax + 0x73c]
0072b028  8bc8                     mov        ecx, eax
0072b02a  e811e1e2ff               call       0x559140
0072b02f  83f8ff                   cmp        eax, -1
0072b032  8945f0                   mov        dword ptr [ebp - 0x10], eax
0072b035  0f8480000000             je         0x72b0bb
0072b03b  8b16                     mov        edx, dword ptr [esi]
0072b03d  6a01                     push       1
0072b03f  6a01                     push       1
0072b041  6a01                     push       1
0072b043  6a08                     push       8
0072b045  8bce                     mov        ecx, esi
0072b047  ff9268070000             call       dword ptr [edx + 0x768]
0072b04d  84c0                     test       al, al
0072b04f  746a                     je         0x72b0bb
0072b051  899d58fcffff             mov        dword ptr [ebp - 0x3a8], ebx
0072b057  899d5cfcffff             mov        dword ptr [ebp - 0x3a4], ebx
0072b05d  899d60fcffff             mov        dword ptr [ebp - 0x3a0], ebx
0072b063  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
0072b069  8d4dec                   lea        ecx, [ebp - 0x14]
0072b06c  40                       inc        eax
0072b06d  51                       push       ecx
0072b06e  8d8d54fcffff             lea        ecx, [ebp - 0x3ac]
0072b074  c745fc21000000           mov        dword ptr [ebp - 4], 0x21
0072b07b  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b07e  e89dc0cdff               call       0x407120
0072b083  8d55f0                   lea        edx, [ebp - 0x10]
0072b086  52                       push       edx
0072b087  8d8d54fcffff             lea        ecx, [ebp - 0x3ac]
0072b08d  e88ec0cdff               call       0x407120
0072b092  8b06                     mov        eax, dword ptr [esi]
0072b094  53                       push       ebx
0072b095  53                       push       ebx
0072b096  6a01                     push       1
0072b098  8d8d54fcffff             lea        ecx, [ebp - 0x3ac]
0072b09e  51                       push       ecx
0072b09f  6a16                     push       0x16
0072b0a1  8bce                     mov        ecx, esi
0072b0a3  ff908c020000             call       dword ptr [eax + 0x28c]
0072b0a9  8d8d54fcffff             lea        ecx, [ebp - 0x3ac]
0072b0af  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0072b0b6  e8959cf1ff               call       0x644d50
0072b0bb  8b9604010000             mov        edx, dword ptr [esi + 0x104]
0072b0c1  389a3a010000             cmp        byte ptr [edx + 0x13a], bl
0072b0c7  740f                     je         0x72b0d8
0072b0c9  8b06                     mov        eax, dword ptr [esi]
0072b0cb  53                       push       ebx
0072b0cc  53                       push       ebx
0072b0cd  53                       push       ebx
0072b0ce  53                       push       ebx
0072b0cf  53                       push       ebx
0072b0d0  8bce                     mov        ecx, esi
0072b0d2  ff908c020000             call       dword ptr [eax + 0x28c]
0072b0d8  8b                       .byte      0x8b
