004ede20 55                       push      ebp
004ede21 8bec                     mov       ebp, esp
004ede23 56                       push      esi
004ede24 8b7508                   mov       esi, dword ptr [ebp + 8]
004ede27 85f6                     test      esi, esi
004ede29 57                       push      edi
004ede2a 8bf9                     mov       edi, ecx
004ede2c 7473                     je        0x4edea1
004ede2e 8b07                     mov       eax, dword ptr [edi]
004ede30 ff90c8010000             call      dword ptr [eax + 0x1c8]
004ede36 3bc7                     cmp       eax, edi
004ede38 741b                     je        0x4ede55
004ede3a 8b17                     mov       edx, dword ptr [edi]
004ede3c 8bcf                     mov       ecx, edi
004ede3e ff92c8010000             call      dword ptr [edx + 0x1c8]
004ede44 8b10                     mov       edx, dword ptr [eax]
004ede46 56                       push      esi
004ede47 8bc8                     mov       ecx, eax
004ede49 ff92a4010000             call      dword ptr [edx + 0x1a4]
004ede4f 5f                       pop       edi
004ede50 5e                       pop       esi
004ede51 5d                       pop       ebp
004ede52 c20400                   ret       4
004ede55 8b06                     mov       eax, dword ptr [esi]
004ede57 53                       push      ebx
004ede58 8bce                     mov       ecx, esi
004ede5a ff90c8010000             call      dword ptr [eax + 0x1c8]
004ede60 8d4d08                   lea       ecx, [ebp + 8]
004ede63 81c718040000             add       edi, 0x418
004ede69 51                       push      ecx
004ede6a 8bcf                     mov       ecx, edi
004ede6c 894508                   mov       dword ptr [ebp + 8], eax
004ede6f e87c0e0000               call      0x4eecf0
004ede74 8b16                     mov       edx, dword ptr [esi]
004ede76 8bce                     mov       ecx, esi
004ede78 8bd8                     mov       ebx, eax
004ede7a ff92c8010000             call      dword ptr [edx + 0x1c8]
004ede80 8903                     mov       dword ptr [ebx], eax
004ede82 8b06                     mov       eax, dword ptr [esi]
004ede84 8bce                     mov       ecx, esi
004ede86 ff90c8010000             call      dword ptr [eax + 0x1c8]
004ede8c 3bf0                     cmp       esi, eax
004ede8e 5b                       pop       ebx
004ede8f 7410                     je        0x4edea1
004ede91 8d4d08                   lea       ecx, [ebp + 8]
004ede94 51                       push      ecx
004ede95 8bcf                     mov       ecx, edi
004ede97 897508                   mov       dword ptr [ebp + 8], esi
004ede9a e8510e0000               call      0x4eecf0
004ede9f 8930                     mov       dword ptr [eax], esi
004edea1 5f                       pop       edi
004edea2 5e                       pop       esi
004edea3 5d                       pop       ebp
004edea4 c20400                   ret       4
004edea7 cc                       int3      
004edea8 cc                       int3      
004edea9 cc                       int3      
004edeaa cc                       int3      
004edeab cc                       int3      
004edeac cc                       int3      
004edead cc                       int3      
004edeae cc                       int3      
004edeaf cc                       int3      
004edeb0 55                       push      ebp
004edeb1 8bec                     mov       ebp, esp
004edeb3 83ec10                   sub       esp, 0x10
004edeb6 8b4508                   mov       eax, dword ptr [ebp + 8]
004edeb9 53                       push      ebx
004edeba 56                       push      esi
004edebb 57                       push      edi
004edebc 8bf9                     mov       edi, ecx
004edebe 803800                   cmp       byte ptr [eax], 0
004edec1 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004edec4 8d45fc                   lea       eax, [ebp - 4]
004edec7 754f                     jne       0x4edf18
004edec9 8d5508                   lea       edx, [ebp + 8]
004edecc 52                       push      edx
004edecd 894d08                   mov       dword ptr [ebp + 8], ecx
004eded0 8db770040000             lea       esi, [edi + 0x470]
004eded6 50                       push      eax
004eded7 8bce                     mov       ecx, esi
004eded9 e8026e5700               call      0xa64ce0
004edede 8b5dfc                   mov       ebx, dword ptr [ebp - 4]
004edee1 3b5e08                   cmp       ebx, dword ptr [esi + 8]
004edee4 751e                     jne       0x4edf04
004edee6 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004edee9 8d55f8                   lea       edx, [ebp - 8]
004edeec 52                       push      edx
004edeed 8d45f0                   lea       eax, [ebp - 0x10]
004edef0 894df8                   mov       dword ptr [ebp - 8], ecx
004edef3 50                       push      eax
004edef4 8bce                     mov       ecx, esi
004edef6 c745fc00000000           mov       dword ptr [ebp - 4], 0
004edefd e88e0b0000               call      0x4eea90
004edf02 8b18                     mov       ebx, dword ptr [eax]
004edf04 8d4f60                   lea       ecx, [edi + 0x60]
004edf07 e8f48f6100               call      0xb06f00
004edf0c 5f                       pop       edi
004edf0d 5e                       pop       esi
004edf0e 89430c                   mov       dword ptr [ebx + 0xc], eax
004edf11 5b                       pop       ebx
004edf12 8be5                     mov       esp, ebp
004edf14 5d                       pop       ebp
004edf15 c20800                   ret       8
004edf18 8d550c                   lea       edx, [ebp + 0xc]
004edf1b 52                       push      edx
004edf1c 894d0c                   mov       dword ptr [ebp + 0xc], ecx
004edf1f 50                       push      eax
004edf20 8d8f70040000             lea       ecx, [edi + 0x470]
004edf26 e8b56d5700               call      0xa64ce0
004edf2b 8b5dfc                   mov       ebx, dword ptr [ebp - 4]
004edf2e 3b9f78040000             cmp       ebx, dword ptr [edi + 0x478]
004edf34 7424                     je        0x4edf5a
004edf36 8d7760                   lea       esi, [edi + 0x60]
004edf39 8bce                     mov       ecx, esi
004edf3b e8c08f6100               call      0xb06f00
004edf40 2b430c                   sub       eax, dword ptr [ebx + 0xc]
004edf43 3de8030000               cmp       eax, 0x3e8
004edf48 7c10                     jl        0x4edf5a
004edf4a 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004edf4d c60100                   mov       byte ptr [ecx], 0
004edf50 8bce                     mov       ecx, esi
004edf52 e8a98f6100               call      0xb06f00
004edf57 89430c                   mov       dword ptr [ebx + 0xc], eax
004edf5a 5f                       pop       edi
004edf5b 5e                       pop       esi
004edf5c 5b                       pop       ebx
004edf5d 8be5                     mov       esp, ebp
004edf5f 5d                       pop       ebp
004edf60 c20800                   ret       8
004edf63 cc                       int3      
004edf64 cc                       int3      
004edf65 cc                       int3      
004edf66 cc                       int3      
004edf67 cc                       int3      
004edf68 cc                       int3      
004edf69 cc                       int3      
004edf6a cc                       int3      
004edf6b cc                       int3      
004edf6c cc                       int3      
004edf6d cc                       int3      
004edf6e cc                       int3      
004edf6f cc                       int3      
