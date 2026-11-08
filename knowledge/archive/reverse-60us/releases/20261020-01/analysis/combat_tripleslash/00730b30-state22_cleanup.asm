00730b30  83ff16                   cmp        edi, 0x16
00730b33  7419                     je         0x730b4e
00730b35  8b3e                     mov        edi, dword ptr [esi]
00730b37  6aff                     push       -1
00730b39  6a08                     push       8
00730b3b  8bce                     mov        ecx, esi
00730b3d  ff974c060000             call       dword ptr [edi + 0x64c]
00730b43  50                       push       eax
00730b44  6a08                     push       8
00730b46  8bce                     mov        ecx, esi
00730b48  ff972c070000             call       dword ptr [edi + 0x72c]
00730b4e  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
00730b54  8b8c86242f0000           mov        ecx, dword ptr [esi + eax*4 + 0x2f24]
00730b5b  8b16                     mov        edx, dword ptr [esi]
00730b5d  51                       push       ecx
00730b5e  8bce                     mov        ecx, esi
00730b60  ff92fc000000             call       dword ptr [edx + 0xfc]
00730b66  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
00730b6c  2501000080               and        eax, 0x80000001
00730b71  8b16                     mov        edx, dword ptr [esi]
00730b73  7905                     jns        0x730b7a
00730b75  48                       dec        eax
00730b76  83c8fe                   or         eax, 0xfffffffe
00730b79  40                       inc        eax
00730b7a  8b8c86382f0000           mov        ecx, dword ptr [esi + eax*4 + 0x2f38]
00730b81  51                       push       ecx
00730b82  e9                       .byte      0xe9
00730b83  17                       pop        ss
