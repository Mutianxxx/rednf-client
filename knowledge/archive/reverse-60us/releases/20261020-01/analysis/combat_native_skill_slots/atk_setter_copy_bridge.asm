004afa10  55                       push       ebp
004afa11  8bec                     mov        ebp, esp
004afa13  8b4508                   mov        eax, dword ptr [ebp + 8]
004afa16  53                       push       ebx
004afa17  56                       push       esi
004afa18  57                       push       edi
004afa19  50                       push       eax
004afa1a  8bf9                     mov        edi, ecx
004afa1c  e8afe20300               call       0x4edcd0
004afa21  8db7ec140000             lea        esi, [edi + 0x14ec]
004afa27  bb17000000               mov        ebx, 0x17
004afa2c  8d642400                 lea        esp, [esp]
004afa30  8b06                     mov        eax, dword ptr [esi]
004afa32  85c0                     test       eax, eax
004afa34  7411                     je         0x4afa47
004afa36  8bc8                     mov        ecx, eax
004afa38  8b11                     mov        edx, dword ptr [ecx]
004afa3a  8d8760020000             lea        eax, [edi + 0x260]
004afa40  50                       push       eax
004afa41  ff92ac000000             call       dword ptr [edx + 0xac]
004afa47  83c604                   add        esi, 4
004afa4a  4b                       dec        ebx
004afa4b  75e3                     jne        0x4afa30
004afa4d  8b8fdc120000             mov        ecx, dword ptr [edi + 0x12dc]
004afa53  85c9                     test       ecx, ecx
004afa55  740c                     je         0x4afa63
004afa57  81c760020000             add        edi, 0x260
004afa5d  57                       push       edi
004afa5e  e84d700000               call       0x4b6ab0
004afa63  5f                       pop        edi
004afa64  5e                       pop        esi
004afa65  5b                       pop        ebx
004afa66  5d                       pop        ebp
004afa67  c2                       .byte      0xc2
