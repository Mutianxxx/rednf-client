005ea85e  6870080000               push       0x870
005ea863  e8e893e1ff               call       0x403c50
005ea868  83c404                   add        esp, 4
005ea86b  894508                   mov        dword ptr [ebp + 8], eax
005ea86e  85c0                     test       eax, eax
005ea870  c745fc80000000           mov        dword ptr [ebp - 4], 0x80
005ea877  0f84736d0000             je         0x5f15f0
005ea87d  8b550c                   mov        edx, dword ptr [ebp + 0xc]
005ea880  52                       push       edx
005ea881  56                       push       esi
005ea882  8bc8                     mov        ecx, eax
005ea884  e8b73efeff               call       0x5ce740
005ea889  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
005ea88c  64890d00000000           mov        dword ptr fs:[0], ecx
005ea893  5e                       pop        esi
005ea894  8be5                     mov        esp, ebp
005ea896  5d                       pop        ebp
005ea897  c3                       ret        