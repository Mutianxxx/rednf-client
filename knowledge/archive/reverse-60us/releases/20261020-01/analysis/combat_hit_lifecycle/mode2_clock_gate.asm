004edeb0 55                       push       ebp
004edeb1 8bec                     mov        ebp, esp
004edeb3 83ec10                   sub        esp, 0x10
004edeb6 8b4508                   mov        eax, dword ptr [ebp + 8]
004edeb9 53                       push       ebx
004edeba 56                       push       esi
004edebb 57                       push       edi
004edebc 8bf9                     mov        edi, ecx
004edebe 803800                   cmp        byte ptr [eax], 0
004edec1 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004edec4 8d45fc                   lea        eax, [ebp - 4]
004edec7 754f                     jne        0x4edf18
004edec9 8d5508                   lea        edx, [ebp + 8]
004edecc 52                       push       edx
004edecd 894d08                   mov        dword ptr [ebp + 8], ecx
004eded0 8db770040000             lea        esi, [edi + 0x470]
004eded6 50                       push       eax
004eded7 8bce                     mov        ecx, esi
004eded9 e8026e5700               call       0xa64ce0
004edede 8b5dfc                   mov        ebx, dword ptr [ebp - 4]
004edee1 3b5e08                   cmp        ebx, dword ptr [esi + 8]
004edee4 751e                     jne        0x4edf04
004edee6 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004edee9 8d55f8                   lea        edx, [ebp - 8]
004edeec 52                       push       edx
004edeed 8d45f0                   lea        eax, [ebp - 0x10]
004edef0 894df8                   mov        dword ptr [ebp - 8], ecx
004edef3 50                       push       eax
004edef4 8bce                     mov        ecx, esi
004edef6 c745fc00000000           mov        dword ptr [ebp - 4], 0
004edefd e88e0b0000               call       0x4eea90
004edf02 8b18                     mov        ebx, dword ptr [eax]
004edf04 8d4f60                   lea        ecx, [edi + 0x60]
004edf07 e8f48f6100               call       0xb06f00
004edf0c 5f                       pop        edi
004edf0d 5e                       pop        esi
004edf0e 89430c                   mov        dword ptr [ebx + 0xc], eax
004edf11 5b                       pop        ebx
004edf12 8be5                     mov        esp, ebp
004edf14 5d                       pop        ebp
004edf15 c20800                   ret        8
004edf18 8d550c                   lea        edx, [ebp + 0xc]
004edf1b 52                       push       edx
004edf1c 894d0c                   mov        dword ptr [ebp + 0xc], ecx
004edf1f 50                       push       eax
004edf20 8d8f70040000             lea        ecx, [edi + 0x470]
004edf26 e8b56d5700               call       0xa64ce0
004edf2b 8b5dfc                   mov        ebx, dword ptr [ebp - 4]
004edf2e 3b9f78040000             cmp        ebx, dword ptr [edi + 0x478]
004edf34 7424                     je         0x4edf5a
004edf36 8d7760                   lea        esi, [edi + 0x60]
004edf39 8bce                     mov        ecx, esi
004edf3b e8c08f6100               call       0xb06f00
004edf40 2b430c                   sub        eax, dword ptr [ebx + 0xc]
004edf43 3de8030000               cmp        eax, 0x3e8
004edf48 7c10                     jl         0x4edf5a
004edf4a 8b4d08                   mov        ecx, dword ptr [ebp + 8]
004edf4d c60100                   mov        byte ptr [ecx], 0
004edf50 8bce                     mov        ecx, esi
004edf52 e8a98f6100               call       0xb06f00
004edf57 89430c                   mov        dword ptr [ebx + 0xc], eax
004edf5a 5f                       pop        edi
004edf5b 5e                       pop        esi
004edf5c 5b                       pop        ebx
004edf5d 8be5                     mov        esp, ebp
004edf5f 5d                       pop        ebp
