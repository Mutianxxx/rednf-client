004edd10 55                       push       ebp
004edd11 8bec                     mov        ebp, esp
004edd13 51                       push       ecx
004edd14 53                       push       ebx
004edd15 56                       push       esi
004edd16 57                       push       edi
004edd17 8b7d08                   mov        edi, dword ptr [ebp + 8]
004edd1a 57                       push       edi
004edd1b 8bf1                     mov        esi, ecx
004edd1d e8fedefaff               call       0x49bc20
004edd22 8b07                     mov        eax, dword ptr [edi]
004edd24 6a01                     push       1
004edd26 8bcf                     mov        ecx, edi
004edd28 ff502c                   call       dword ptr [eax + 0x2c]
004edd2b 84c0                     test       al, al
004edd2d 7408                     je         0x4edd37
004edd2f 57                       push       edi
004edd30 8bce                     mov        ecx, esi
004edd32 e8e9ecffff               call       0x4eca20
004edd37 8d4d08                   lea        ecx, [ebp + 8]
004edd3a 51                       push       ecx
004edd3b 8d55fc                   lea        edx, [ebp - 4]
004edd3e 8d9e18040000             lea        ebx, [esi + 0x418]
004edd44 52                       push       edx
004edd45 8bcb                     mov        ecx, ebx
004edd47 e8946f5700               call       0xa64ce0
004edd4c 8b45fc                   mov        eax, dword ptr [ebp - 4]
004edd4f 3b8620040000             cmp        eax, dword ptr [esi + 0x420]
004edd55 740c                     je         0x4edd63
004edd57 50                       push       eax
004edd58 8d45fc                   lea        eax, [ebp - 4]
004edd5b 50                       push       eax
004edd5c 8bcb                     mov        ecx, ebx
004edd5e e81d680700               call       0x564580
004edd63 8d4d08                   lea        ecx, [ebp + 8]
004edd66 51                       push       ecx
004edd67 8d55fc                   lea        edx, [ebp - 4]
004edd6a 8d9e70040000             lea        ebx, [esi + 0x470]
004edd70 52                       push       edx
004edd71 8bcb                     mov        ecx, ebx
004edd73 e8686f5700               call       0xa64ce0
004edd78 8b45fc                   mov        eax, dword ptr [ebp - 4]
004edd7b 3b8678040000             cmp        eax, dword ptr [esi + 0x478]
004edd81 740c                     je         0x4edd8f
004edd83 50                       push       eax
004edd84 8d4508                   lea        eax, [ebp + 8]
004edd87 50                       push       eax
004edd88 8bcb                     mov        ecx, ebx
004edd8a e8f1670700               call       0x564580
004edd8f 8b8658040000             mov        eax, dword ptr [esi + 0x458]
004edd95 33db                     xor        ebx, ebx
004edd97 3bc7                     cmp        eax, edi
004edd99 7506                     jne        0x4edda1
004edd9b 899e58040000             mov        dword ptr [esi + 0x458], ebx
004edda1 39bee0040000             cmp        dword ptr [esi + 0x4e0], edi
004edda7 7506                     jne        0x4eddaf
004edda9 899ee0040000             mov        dword ptr [esi + 0x4e0], ebx
004eddaf 39beec040000             cmp        dword ptr [esi + 0x4ec], edi
004eddb5 7506                     jne        0x4eddbd
004eddb7 899eec040000             mov        dword ptr [esi + 0x4ec], ebx
004eddbd 3bfe                     cmp        edi, esi
004eddbf 754a                     jne        0x4ede0b
004eddc1 56                       push       esi
004eddc2 e8d9ccf5ff               call       0x44aaa0
004eddc7 8b86d4040000             mov        eax, dword ptr [esi + 0x4d4]
004eddcd 83c404                   add        esp, 4
004eddd0 3bc3                     cmp        eax, ebx
004eddd2 7409                     je         0x4edddd
004eddd4 50                       push       eax
004eddd5 e803227100               call       0xbfffdd
004eddda 83c404                   add        esp, 4
004edddd 8d8e18040000             lea        ecx, [esi + 0x418]
004edde3 899ed4040000             mov        dword ptr [esi + 0x4d4], ebx
004edde9 899ed8040000             mov        dword ptr [esi + 0x4d8], ebx
004eddef 899edc040000             mov        dword ptr [esi + 0x4dc], ebx
004eddf5 e8b6abf4ff               call       0x4389b0
004eddfa 8d8e70040000             lea        ecx, [esi + 0x470]
004ede00 e8ababf4ff               call       0x4389b0
004ede05 899e58040000             mov        dword ptr [esi + 0x458], ebx
004ede0b 5f                       pop        edi
004ede0c 5e                       pop        esi
004ede0d 5b                       pop        ebx
004ede0e 8be5                     mov        esp, ebp
004ede10 5d                       pop        ebp
