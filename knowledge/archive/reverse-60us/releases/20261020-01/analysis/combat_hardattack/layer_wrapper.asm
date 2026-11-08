004acf80 55                       push       ebp
004acf81 8bec                     mov        ebp, esp
004acf83 8b4528                   mov        eax, dword ptr [ebp + 0x28]
004acf86 8b5520                   mov        edx, dword ptr [ebp + 0x20]
004acf89 53                       push       ebx
004acf8a 8b5d2c                   mov        ebx, dword ptr [ebp + 0x2c]
004acf8d 56                       push       esi
004acf8e 57                       push       edi
004acf8f 8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
004acf92 53                       push       ebx
004acf93 50                       push       eax
004acf94 8b451c                   mov        eax, dword ptr [ebp + 0x1c]
004acf97 8bf1                     mov        esi, ecx
004acf99 8b4d24                   mov        ecx, dword ptr [ebp + 0x24]
004acf9c 51                       push       ecx
004acf9d 8b4d18                   mov        ecx, dword ptr [ebp + 0x18]
004acfa0 52                       push       edx
004acfa1 8b5514                   mov        edx, dword ptr [ebp + 0x14]
004acfa4 50                       push       eax
004acfa5 8b4510                   mov        eax, dword ptr [ebp + 0x10]
004acfa8 51                       push       ecx
004acfa9 8b4d08                   mov        ecx, dword ptr [ebp + 8]
004acfac 52                       push       edx
004acfad 50                       push       eax
004acfae 57                       push       edi
004acfaf 51                       push       ecx
004acfb0 8bce                     mov        ecx, esi
004acfb2 e8f9e7feff               call       0x49b7b0
004acfb7 85ff                     test       edi, edi
004acfb9 7436                     je         0x4acff1
004acfbb 84db                     test       bl, bl
004acfbd 7432                     je         0x4acff1
004acfbf 8d8e20160000             lea        ecx, [esi + 0x1620]
004acfc5 e89650f5ff               call       0x402060
004acfca 89452c                   mov        dword ptr [ebp + 0x2c], eax
004acfcd db452c                   fild       dword ptr [ebp + 0x2c]
004acfd0 b904340001               mov        ecx, 0x1003404
004acfd5 d95d2c                   fstp       dword ptr [ebp + 0x2c]
004acfd8 e8d363f8ff               call       0x4333b0
004acfdd d84d2c                   fmul       dword ptr [ebp + 0x2c]
004acfe0 51                       push       ecx
004acfe1 8bcf                     mov        ecx, edi
004acfe3 d80df811cc00             fmul       dword ptr [0xcc11f8]
004acfe9 d91c24                   fstp       dword ptr [esp]
004acfec e87fcc5700               call       0xa29c70
004acff1 5f                       pop        edi
004acff2 5e                       pop        esi
004acff3 5b                       pop        ebx
004acff4 5d                       pop        ebp
004acff5 c22800                   ret        0x28