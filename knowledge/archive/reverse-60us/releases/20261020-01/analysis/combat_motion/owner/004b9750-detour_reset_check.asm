004b9750  56                       push       esi
004b9751  8bf1                     mov        esi, ecx
004b9753  8b8678160000             mov        eax, dword ptr [esi + 0x1678]
004b9759  83f8ff                   cmp        eax, -1
004b975c  744e                     je         0x4b97ac
004b975e  85c0                     test       eax, eax
004b9760  750a                     jne        0x4b976c
004b9762  8b06                     mov        eax, dword ptr [esi]
004b9764  ff90e0000000             call       dword ptr [eax + 0xe0]
004b976a  eb08                     jmp        0x4b9774
004b976c  8b16                     mov        edx, dword ptr [esi]
004b976e  ff92dc000000             call       dword ptr [edx + 0xdc]
004b9774  398680160000             cmp        dword ptr [esi + 0x1680], eax
004b977a  7526                     jne        0x4b97a2
004b977c  8b8678160000             mov        eax, dword ptr [esi + 0x1678]
004b9782  85c0                     test       eax, eax
004b9784  8bce                     mov        ecx, esi
004b9786  750a                     jne        0x4b9792
004b9788  8b06                     mov        eax, dword ptr [esi]
004b978a  ff9098000000             call       dword ptr [eax + 0x98]
004b9790  eb08                     jmp        0x4b979a
004b9792  8b16                     mov        edx, dword ptr [esi]
004b9794  ff9294000000             call       dword ptr [edx + 0x94]
004b979a  398684160000             cmp        dword ptr [esi + 0x1684], eax
004b97a0  740a                     je         0x4b97ac
004b97a2  c78678160000ffffffff     mov        dword ptr [esi + 0x1678], 0xffffffff
004b97ac  5e                       pop        esi
004b97ad  c3                       ret        
