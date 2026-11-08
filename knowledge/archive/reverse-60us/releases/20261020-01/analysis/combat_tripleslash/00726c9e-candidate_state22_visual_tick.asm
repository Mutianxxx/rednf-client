00726c9e  8d8e64150000             lea        ecx, [esi + 0x1564]
00726ca4  e857023e00               call       0xb06f00
00726ca9  8b8e402f0000             mov        ecx, dword ptr [esi + 0x2f40]
00726caf  81c1c8000000             add        ecx, 0xc8
00726cb5  3bc1                     cmp        eax, ecx
00726cb7  0f8c743e0000             jl         0x72ab31
00726cbd  8b16                     mov        edx, dword ptr [esi]
00726cbf  6a02                     push       2
00726cc1  8bce                     mov        ecx, esi
00726cc3  ff92d0040000             call       dword ptr [edx + 0x4d0]
00726cc9  8b3c85782e0001           mov        edi, dword ptr [eax*4 + 0x1002e78]
00726cd0  8b06                     mov        eax, dword ptr [esi]
00726cd2  8bce                     mov        ecx, esi
00726cd4  897de0                   mov        dword ptr [ebp - 0x20], edi
00726cd7  ff90c0000000             call       dword ptr [eax + 0xc0]
00726cdd  f7d8                     neg        eax
00726cdf  1ac0                     sbb        al, al
00726ce1  fec0                     inc        al
00726ce3  8845c7                   mov        byte ptr [ebp - 0x39], al
00726ce6  8bce                     mov        ecx, esi
00726ce8  740d                     je         0x726cf7
00726cea  8b16                     mov        edx, dword ptr [esi]
00726cec  ff9294000000             call       dword ptr [edx + 0x94]
00726cf2  83c014                   add        eax, 0x14
00726cf5  eb0b                     jmp        0x726d02
00726cf7  8b06                     mov        eax, dword ptr [esi]
00726cf9  ff9094000000             call       dword ptr [eax + 0x94]
00726cff  83e814                   sub        eax, 0x14
00726d02  8b16                     mov        edx, dword ptr [esi]
00726d04  8945f0                   mov        dword ptr [ebp - 0x10], eax
00726d07  8b07                     mov        eax, dword ptr [edi]
00726d09  8bce                     mov        ecx, esi
00726d0b  8945d4                   mov        dword ptr [ebp - 0x2c], eax
00726d0e  ff929c000000             call       dword ptr [edx + 0x9c]
00726d14  50                       push       eax
00726d15  8b06                     mov        eax, dword ptr [esi]
00726d17  8bce                     mov        ecx, esi
00726d19  ff9098000000             call       dword ptr [eax + 0x98]
00726d1f  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00726d22  8b7de0                   mov        edi, dword ptr [ebp - 0x20]
00726d25  50                       push       eax
00726d26  8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
00726d29  51                       push       ecx
00726d2a  8bcf                     mov        ecx, edi
00726d2c  ff5028                   call       dword ptr [eax + 0x28]
00726d2f  8b17                     mov        edx, dword ptr [edi]
00726d31  8bcf                     mov        ecx, edi
00726d33  ff521c                   call       dword ptr [edx + 0x1c]
00726d36  8a4dc7                   mov        cl, byte ptr [ebp - 0x39]
00726d39  884858                   mov        byte ptr [eax + 0x58], cl
00726d3c  8b17                     mov        edx, dword ptr [edi]
00726d3e  53                       push       ebx
00726d3f  8bcf                     mov        ecx, edi
00726d41  ff520c                   call       dword ptr [edx + 0xc]
00726d44  8b07                     mov        eax, dword ptr [edi]
00726d46  8d8d3cfbffff             lea        ecx, [ebp - 0x4c4]
00726d4c  51                       push       ecx
00726d4d  8bcf                     mov        ecx, edi
00726d4f  ff505c                   call       dword ptr [eax + 0x5c]
00726d52  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
00726d58  53                       push       ebx
00726d59  8d953cfbffff             lea        edx, [ebp - 0x4c4]
00726d5f  52                       push       edx
00726d60  53                       push       ebx
00726d61  6a02                     push       2
00726d63  56                       push       esi
00726d64  c745fc08000000           mov        dword ptr [ebp - 4], 8
00726d6b  e8f072deff               call       0x50e060
00726d70  8d8e64150000             lea        ecx, [esi + 0x1564]
00726d76  e885013e00               call       0xb06f00
00726d7b  8d8d3cfbffff             lea        ecx, [ebp - 0x4c4]
00726d81  8986402f0000             mov        dword ptr [esi + 0x2f40], eax
00726d87  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00726d8e  e8bddff1ff               call       0x644d50
00726d93  e9                       .byte      0xe9
