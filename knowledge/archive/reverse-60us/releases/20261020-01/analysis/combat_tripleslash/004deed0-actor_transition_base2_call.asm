004deed0  6a01                     push       1
004deed2  50                       push       eax
004deed3  8bce                     mov        ecx, esi
004deed5  ff9254050000             call       dword ptr [edx + 0x554]
004deedb  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
004deede  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004deee1  8b7d08                   mov        edi, dword ptr [ebp + 8]
004deee4  51                       push       ecx
004deee5  52                       push       edx
004deee6  53                       push       ebx
004deee7  57                       push       edi
004deee8  8bce                     mov        ecx, esi
004deeea  e871befdff               call       0x4bad60
004deeef  83ff08                   cmp        edi, 8
004deef2  0f873e030000             ja         0x4df236
004deef8  ff24bddcf24d00           jmp        dword ptr [edi*4 + 0x4df2dc]
004deeff  8b                       .byte      0x8b
