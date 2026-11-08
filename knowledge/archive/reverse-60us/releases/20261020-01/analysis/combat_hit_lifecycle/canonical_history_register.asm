004ede20 55                       push       ebp
004ede21 8bec                     mov        ebp, esp
004ede23 56                       push       esi
004ede24 8b7508                   mov        esi, dword ptr [ebp + 8]
004ede27 85f6                     test       esi, esi
004ede29 57                       push       edi
004ede2a 8bf9                     mov        edi, ecx
004ede2c 7473                     je         0x4edea1
004ede2e 8b07                     mov        eax, dword ptr [edi]
004ede30 ff90c8010000             call       dword ptr [eax + 0x1c8]
004ede36 3bc7                     cmp        eax, edi
004ede38 741b                     je         0x4ede55
004ede3a 8b17                     mov        edx, dword ptr [edi]
004ede3c 8bcf                     mov        ecx, edi
004ede3e ff92c8010000             call       dword ptr [edx + 0x1c8]
004ede44 8b10                     mov        edx, dword ptr [eax]
004ede46 56                       push       esi
004ede47 8bc8                     mov        ecx, eax
004ede49 ff92a4010000             call       dword ptr [edx + 0x1a4]
004ede4f 5f                       pop        edi
004ede50 5e                       pop        esi
004ede51 5d                       pop        ebp
004ede52 c20400                   ret        4
004ede55 8b06                     mov        eax, dword ptr [esi]
004ede57 53                       push       ebx
004ede58 8bce                     mov        ecx, esi
004ede5a ff90c8010000             call       dword ptr [eax + 0x1c8]
004ede60 8d4d08                   lea        ecx, [ebp + 8]
004ede63 81c718040000             add        edi, 0x418
004ede69 51                       push       ecx
004ede6a 8bcf                     mov        ecx, edi
004ede6c 894508                   mov        dword ptr [ebp + 8], eax
004ede6f e87c0e0000               call       0x4eecf0
004ede74 8b16                     mov        edx, dword ptr [esi]
004ede76 8bce                     mov        ecx, esi
004ede78 8bd8                     mov        ebx, eax
004ede7a ff92c8010000             call       dword ptr [edx + 0x1c8]
004ede80 8903                     mov        dword ptr [ebx], eax
004ede82 8b06                     mov        eax, dword ptr [esi]
004ede84 8bce                     mov        ecx, esi
004ede86 ff90c8010000             call       dword ptr [eax + 0x1c8]
004ede8c 3bf0                     cmp        esi, eax
004ede8e 5b                       pop        ebx
004ede8f 7410                     je         0x4edea1
004ede91 8d4d08                   lea        ecx, [ebp + 8]
004ede94 51                       push       ecx
004ede95 8bcf                     mov        ecx, edi
004ede97 897508                   mov        dword ptr [ebp + 8], esi
004ede9a e8510e0000               call       0x4eecf0
004ede9f 8930                     mov        dword ptr [eax], esi
004edea1 5f                       pop        edi
004edea2 5e                       pop        esi
004edea3 5d                       pop        ebp
