004edfad 8b06                     mov        eax, dword ptr [esi]
004edfaf 57                       push       edi
004edfb0 8bce                     mov        ecx, esi
004edfb2 ff90a8010000             call       dword ptr [eax + 0x1a8]
004edfb8 83bed803000002           cmp        dword ptr [esi + 0x3d8], 2
004edfbf 88450b                   mov        byte ptr [ebp + 0xb], al
004edfc2 7418                     je         0x4edfdc
004edfc4 84c0                     test       al, al
004edfc6 7414                     je         0x4edfdc
004edfc8 5f                       pop        edi
004edfc9 32c0                     xor        al, al
004edfcb 5e                       pop        esi
004edfcc 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
