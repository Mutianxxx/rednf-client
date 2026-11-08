00ac9c10  55                       push       ebp
00ac9c11  8bec                     mov        ebp, esp
00ac9c13  53                       push       ebx
00ac9c14  56                       push       esi
00ac9c15  8b7514                   mov        esi, dword ptr [ebp + 0x14]
00ac9c18  8bc6                     mov        eax, esi
00ac9c1a  83e800                   sub        eax, 0
00ac9c1d  57                       push       edi
00ac9c1e  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00ac9c21  7408                     je         0xac9c2b
00ac9c23  48                       dec        eax
00ac9c24  7514                     jne        0xac9c3a
00ac9c26  57                       push       edi
00ac9c27  6a01                     push       1
00ac9c29  eb03                     jmp        0xac9c2e
00ac9c2b  57                       push       edi
00ac9c2c  6a00                     push       0
00ac9c2e  e88d080000               call       0xaca4c0
00ac9c33  8bc8                     mov        ecx, eax
00ac9c35  e8b6affcff               call       0xa94bf0
00ac9c3a  8b5d18                   mov        ebx, dword ptr [ebp + 0x18]
00ac9c3d  c1e604                   shl        esi, 4
00ac9c40  8b866cab0d01             mov        eax, dword ptr [esi + 0x10dab6c]
00ac9c46  85c0                     test       eax, eax
00ac9c48  745f                     je         0xac9ca9
00ac9c4a  85db                     test       ebx, ebx
00ac9c4c  7434                     je         0xac9c82
00ac9c4e  8b03                     mov        eax, dword ptr [ebx]
00ac9c50  85c0                     test       eax, eax
00ac9c52  742e                     je         0xac9c82
00ac9c54  83f802                   cmp        eax, 2
00ac9c57  7518                     jne        0xac9c71
00ac9c59  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00ac9c5c  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00ac9c5f  57                       push       edi
00ac9c60  50                       push       eax
00ac9c61  51                       push       ecx
00ac9c62  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9c68  e843f9ffff               call       0xac95b0
00ac9c6d  85c0                     test       eax, eax
00ac9c6f  750c                     jne        0xac9c7d
00ac9c71  85db                     test       ebx, ebx
00ac9c73  7406                     je         0xac9c7b
00ac9c75  c70300000000             mov        dword ptr [ebx], 0
00ac9c7b  33c0                     xor        eax, eax
00ac9c7d  5f                       pop        edi
00ac9c7e  5e                       pop        esi
00ac9c7f  5b                       pop        ebx
00ac9c80  5d                       pop        ebp
00ac9c81  c3                       ret        
00ac9c82  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac9c85  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9c88  57                       push       edi
00ac9c89  52                       push       edx
00ac9c8a  50                       push       eax
00ac9c8b  8d8e60ab0d01             lea        ecx, [esi + 0x10dab60]
00ac9c91  e81af9ffff               call       0xac95b0
00ac9c96  85c0                     test       eax, eax
00ac9c98  74d7                     je         0xac9c71
00ac9c9a  85db                     test       ebx, ebx
00ac9c9c  74df                     je         0xac9c7d
00ac9c9e  5f                       pop        edi
00ac9c9f  5e                       pop        esi
00ac9ca0  c70302000000             mov        dword ptr [ebx], 2
00ac9ca6  5b                       pop        ebx
00ac9ca7  5d                       pop        ebp
00ac9ca8  c3                       ret        
00ac9ca9  68a036e100               push       0xe136a0
00ac9cae  57                       push       edi
00ac9caf  e875801300               call       0xc01d29
00ac9cb4  8bf8                     mov        edi, eax
00ac9cb6  83c408                   add        esp, 8
00ac9cb9  85ff                     test       edi, edi
00ac9cbb  74b4                     je         0xac9c71
00ac9cbd  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00ac9cc0  85c0                     test       eax, eax
00ac9cc2  7406                     je         0xac9cca
00ac9cc4  c70001000000             mov        dword ptr [eax], 1
00ac9cca  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00ac9ccd  85f6                     test       esi, esi
00ac9ccf  740e                     je         0xac9cdf
00ac9cd1  8b4f10                   mov        ecx, dword ptr [edi + 0x10]
00ac9cd4  51                       push       ecx
00ac9cd5  e8f0a41300               call       0xc041ca
00ac9cda  83c404                   add        esp, 4
00ac9cdd  8906                     mov        dword ptr [esi], eax
00ac9cdf  8b4508                   mov        eax, dword ptr [ebp + 8]
00ac9ce2  85c0                     test       eax, eax
00ac9ce4  7406                     je         0xac9cec
00ac9ce6  c70000000000             mov        dword ptr [eax], 0
00ac9cec  8bc7                     mov        eax, edi
00ac9cee  5f                       pop        edi
00ac9cef  5e                       pop        esi
00ac9cf0  5b                       pop        ebx
00ac9cf1  5d                       pop        ebp
00ac9cf2  c3                       ret        