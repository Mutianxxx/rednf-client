004edac0  55                       push       ebp
004edac1  8bec                     mov        ebp, esp
004edac3  6aff                     push       -1
004edac5  68cc98c500               push       0xc598cc
004edaca  64a100000000             mov        eax, dword ptr fs:[0]
004edad0  50                       push       eax
004edad1  64892500000000           mov        dword ptr fs:[0], esp
004edad8  83ec20                   sub        esp, 0x20
004edadb  56                       push       esi
004edadc  8bf1                     mov        esi, ecx
004edade  8a869d040000             mov        al, byte ptr [esi + 0x49d]
004edae4  84c0                     test       al, al
004edae6  0f8505010000             jne        0x4edbf1
004edaec  83bea0040000ff           cmp        dword ptr [esi + 0x4a0], -1
004edaf3  0f84f8000000             je         0x4edbf1
004edaf9  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edaff  8b01                     mov        eax, dword ptr [ecx]
004edb01  53                       push       ebx
004edb02  57                       push       edi
004edb03  6a02                     push       2
004edb05  6a05                     push       5
004edb07  ff5008                   call       dword ptr [eax + 8]
004edb0a  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edb10  8b39                     mov        edi, dword ptr [ecx]
004edb12  8b16                     mov        edx, dword ptr [esi]
004edb14  8bce                     mov        ecx, esi
004edb16  ff523c                   call       dword ptr [edx + 0x3c]
004edb19  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edb1f  50                       push       eax
004edb20  ff5724                   call       dword ptr [edi + 0x24]
004edb23  a164310001               mov        eax, dword ptr [0x1003164]
004edb28  8b16                     mov        edx, dword ptr [esi]
004edb2a  8b38                     mov        edi, dword ptr [eax]
004edb2c  8bce                     mov        ecx, esi
004edb2e  ff5240                   call       dword ptr [edx + 0x40]
004edb31  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edb37  50                       push       eax
004edb38  ff5724                   call       dword ptr [edi + 0x24]
004edb3b  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edb41  8b01                     mov        eax, dword ptr [ecx]
004edb43  33d2                     xor        edx, edx
004edb45  8a96a0040000             mov        dl, byte ptr [esi + 0x4a0]
004edb4b  52                       push       edx
004edb4c  ff5020                   call       dword ptr [eax + 0x20]
004edb4f  33db                     xor        ebx, ebx
004edb51  895de8                   mov        dword ptr [ebp - 0x18], ebx
004edb54  895dec                   mov        dword ptr [ebp - 0x14], ebx
004edb57  895df0                   mov        dword ptr [ebp - 0x10], ebx
004edb5a  8d86a4040000             lea        eax, [esi + 0x4a4]
004edb60  50                       push       eax
004edb61  8d4de4                   lea        ecx, [ebp - 0x1c]
004edb64  895dfc                   mov        dword ptr [ebp - 4], ebx
004edb67  e804ffffff               call       0x4eda70
004edb6c  8d4de4                   lea        ecx, [ebp - 0x1c]
004edb6f  51                       push       ecx
004edb70  8d4dd4                   lea        ecx, [ebp - 0x2c]
004edb73  e888f4f7ff               call       0x46d000
004edb78  8b7dd8                   mov        edi, dword ptr [ebp - 0x28]
004edb7b  3bfb                     cmp        edi, ebx
004edb7d  c645fc01                 mov        byte ptr [ebp - 4], 1
004edb81  7504                     jne        0x4edb87
004edb83  33c0                     xor        eax, eax
004edb85  eb05                     jmp        0x4edb8c
004edb87  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
004edb8a  2bc7                     sub        eax, edi
004edb8c  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edb92  8b11                     mov        edx, dword ptr [ecx]
004edb94  50                       push       eax
004edb95  ff5224                   call       dword ptr [edx + 0x24]
004edb98  85ff                     test       edi, edi
004edb9a  741d                     je         0x4edbb9
004edb9c  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
004edb9f  2bc7                     sub        eax, edi
004edba1  3bd8                     cmp        ebx, eax
004edba3  7314                     jae        0x4edbb9
004edba5  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004edbab  8b01                     mov        eax, dword ptr [ecx]
004edbad  33d2                     xor        edx, edx
004edbaf  8a141f                   mov        dl, byte ptr [edi + ebx]
004edbb2  52                       push       edx
004edbb3  ff5020                   call       dword ptr [eax + 0x20]
004edbb6  43                       inc        ebx
004edbb7  ebdf                     jmp        0x4edb98
004edbb9  8b0d90070c01             mov        ecx, dword ptr [0x10c0790]
004edbbf  8b01                     mov        eax, dword ptr [ecx]
004edbc1  6a03                     push       3
004edbc3  56                       push       esi
004edbc4  6aff                     push       -1
004edbc6  6a01                     push       1
004edbc8  ff5044                   call       dword ptr [eax + 0x44]
004edbcb  85ff                     test       edi, edi
004edbcd  c6869d04000001           mov        byte ptr [esi + 0x49d], 1
004edbd4  7409                     je         0x4edbdf
004edbd6  57                       push       edi
004edbd7  e801247100               call       0xbfffdd
004edbdc  83c404                   add        esp, 4
004edbdf  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004edbe2  85c0                     test       eax, eax
004edbe4  5f                       pop        edi
004edbe5  5b                       pop        ebx
004edbe6  7409                     je         0x4edbf1
004edbe8  50                       push       eax
004edbe9  e8ef237100               call       0xbfffdd
004edbee  83c404                   add        esp, 4
004edbf1  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004edbf4  5e                       pop        esi
004edbf5  64890d00000000           mov        dword ptr fs:[0], ecx
004edbfc  8be5                     mov        esp, ebp
004edbfe  5d                       pop        ebp
004edbff  c3                       ret        