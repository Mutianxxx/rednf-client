005ce7a0  56                       push       esi
005ce7a1  8bf1                     mov        esi, ecx
005ce7a3  e8c8f4ecff               call       0x49dc70
005ce7a8  8b8604010000             mov        eax, dword ptr [esi + 0x104]
005ce7ae  8a883a010000             mov        cl, byte ptr [eax + 0x13a]
005ce7b4  84c9                     test       cl, cl
005ce7b6  7416                     je         0x5ce7ce
005ce7b8  8a86e8010000             mov        al, byte ptr [esi + 0x1e8]
005ce7be  84c0                     test       al, al
005ce7c0  750c                     jne        0x5ce7ce
005ce7c2  8b16                     mov        edx, dword ptr [esi]
005ce7c4  6a00                     push       0
005ce7c6  8bce                     mov        ecx, esi
005ce7c8  ff9264010000             call       dword ptr [edx + 0x164]
005ce7ce  5e                       pop        esi
005ce7cf  c3                       ret        