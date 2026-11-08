004ed140 56                       push       esi
004ed141 57                       push       edi
004ed142 8bf1                     mov        esi, ecx
004ed144 e807d0faff               call       0x49a150
004ed149 8d8e60020000             lea        ecx, [esi + 0x260]
004ed14f e8dc82f4ff               call       0x435430
004ed154 8b06                     mov        eax, dword ptr [esi]
004ed156 8bce                     mov        ecx, esi
004ed158 ff90a0010000             call       dword ptr [eax + 0x1a0]
004ed15e 8b16                     mov        edx, dword ptr [esi]
004ed160 8bce                     mov        ecx, esi
004ed162 c6869c04000001           mov        byte ptr [esi + 0x49c], 1
004ed169 ff9298020000             call       dword ptr [edx + 0x298]
004ed16f 8b06                     mov        eax, dword ptr [esi]
004ed171 6a01                     push       1
004ed173 8bce                     mov        ecx, esi
004ed175 ff90d0020000             call       dword ptr [eax + 0x2d0]
004ed17b 8b16                     mov        edx, dword ptr [esi]
004ed17d 6a01                     push       1
004ed17f 8bce                     mov        ecx, esi
004ed181 ff92d8020000             call       dword ptr [edx + 0x2d8]
004ed187 8b06                     mov        eax, dword ptr [esi]
004ed189 33ff                     xor        edi, edi
004ed18b 57                       push       edi
004ed18c 57                       push       edi
004ed18d 8bce                     mov        ecx, esi
004ed18f ff90e0020000             call       dword ptr [eax + 0x2e0]
004ed195 89be58040000             mov        dword ptr [esi + 0x458], edi
004ed19b 83c8ff                   or         eax, 0xffffffff
004ed19e 898654040000             mov        dword ptr [esi + 0x454], eax
004ed1a4 89be60040000             mov        dword ptr [esi + 0x460], edi
004ed1aa 89be64040000             mov        dword ptr [esi + 0x464], edi
004ed1b0 898668040000             mov        dword ptr [esi + 0x468], eax
004ed1b6 89866c040000             mov        dword ptr [esi + 0x46c], eax
004ed1bc 89be0c050000             mov        dword ptr [esi + 0x50c], edi
004ed1c2 5f                       pop        edi
004ed1c3 5e                       pop        esi
004ed1c4 c3                       ret        
