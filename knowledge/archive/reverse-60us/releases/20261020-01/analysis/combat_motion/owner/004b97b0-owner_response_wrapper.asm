004b97b0  55                       push       ebp
004b97b1  8bec                     mov        ebp, esp
004b97b3  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b97b6  56                       push       esi
004b97b7  57                       push       edi
004b97b8  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b97bb  8bf1                     mov        esi, ecx
004b97bd  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b97c0  50                       push       eax
004b97c1  51                       push       ecx
004b97c2  57                       push       edi
004b97c3  8bce                     mov        ecx, esi
004b97c5  e866f20200               call       0x4e8a30
004b97ca  8a8606160000             mov        al, byte ptr [esi + 0x1606]
004b97d0  84c0                     test       al, al
004b97d2  7427                     je         0x4b97fb
004b97d4  8a8607160000             mov        al, byte ptr [esi + 0x1607]
004b97da  84c0                     test       al, al
004b97dc  741d                     je         0x4b97fb
004b97de  83be78160000ff           cmp        dword ptr [esi + 0x1678], -1
004b97e5  7514                     jne        0x4b97fb
004b97e7  85ff                     test       edi, edi
004b97e9  7405                     je         0x4b97f0
004b97eb  83ff01                   cmp        edi, 1
004b97ee  750b                     jne        0x4b97fb
004b97f0  8b16                     mov        edx, dword ptr [esi]
004b97f2  57                       push       edi
004b97f3  8bce                     mov        ecx, esi
004b97f5  ff927c050000             call       dword ptr [edx + 0x57c]
004b97fb  5f                       pop        edi
004b97fc  5e                       pop        esi
004b97fd  5d                       pop        ebp
004b97fe  c20c00                   ret        0xc
