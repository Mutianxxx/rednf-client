00ac95b0  55                       push       ebp
00ac95b1  8bec                     mov        ebp, esp
00ac95b3  51                       push       ecx
00ac95b4  53                       push       ebx
00ac95b5  8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
00ac95b8  56                       push       esi
00ac95b9  57                       push       edi
00ac95ba  8bf1                     mov        esi, ecx
00ac95bc  53                       push       ebx
00ac95bd  8975fc                   mov        dword ptr [ebp - 4], esi
00ac95c0  e808681300               call       0xbffdcd
00ac95c5  83c404                   add        esp, 4
00ac95c8  48                       dec        eax
00ac95c9  7815                     js         0xac95e0
00ac95cb  eb03                     jmp        0xac95d0
00ac95cd  8d4900                   lea        ecx, [ecx]
00ac95d0  66833c435c               cmp        word ptr [ebx + eax*2], 0x5c
00ac95d5  7506                     jne        0xac95dd
00ac95d7  66c704432f00             mov        word ptr [ebx + eax*2], 0x2f
00ac95dd  48                       dec        eax
00ac95de  79f0                     jns        0xac95d0
00ac95e0  53                       push       ebx
00ac95e1  e8ea0c0400               call       0xb0a2d0
00ac95e6  8b4604                   mov        eax, dword ptr [esi + 4]
00ac95e9  8b30                     mov        esi, dword ptr [eax]
00ac95eb  83c404                   add        esp, 4
00ac95ee  3bf0                     cmp        esi, eax
00ac95f0  7419                     je         0xac960b
00ac95f2  53                       push       ebx
00ac95f3  8d4e28                   lea        ecx, [esi + 0x28]
00ac95f6  e825fcffff               call       0xac9220
00ac95fb  8bf8                     mov        edi, eax
00ac95fd  85ff                     test       edi, edi
00ac95ff  7515                     jne        0xac9616
00ac9601  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac9604  8b36                     mov        esi, dword ptr [esi]
00ac9606  3b7004                   cmp        esi, dword ptr [eax + 4]
00ac9609  75e7                     jne        0xac95f2
00ac960b  5f                       pop        edi
00ac960c  5e                       pop        esi
00ac960d  33c0                     xor        eax, eax
00ac960f  5b                       pop        ebx
00ac9610  8be5                     mov        esp, ebp
00ac9612  5d                       pop        ebp
00ac9613  c20c00                   ret        0xc
00ac9616  8b0f                     mov        ecx, dword ptr [edi]
00ac9618  8b5e08                   mov        ebx, dword ptr [esi + 8]
00ac961b  8b5508                   mov        edx, dword ptr [ebp + 8]
00ac961e  83c608                   add        esi, 8
00ac9621  85db                     test       ebx, ebx
00ac9623  890a                     mov        dword ptr [edx], ecx
00ac9625  8b4704                   mov        eax, dword ptr [edi + 4]
00ac9628  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00ac962b  8901                     mov        dword ptr [ecx], eax
00ac962d  7419                     je         0xac9648
00ac962f  8b17                     mov        edx, dword ptr [edi]
00ac9631  6a00                     push       0
00ac9633  52                       push       edx
00ac9634  53                       push       ebx
00ac9635  e87a901300               call       0xc026b4
00ac963a  83c40c                   add        esp, 0xc
00ac963d  5f                       pop        edi
00ac963e  5e                       pop        esi
00ac963f  8bc3                     mov        eax, ebx
00ac9641  5b                       pop        ebx
00ac9642  8be5                     mov        esp, ebp
00ac9644  5d                       pop        ebp
00ac9645  c20c00                   ret        0xc
00ac9648  85f6                     test       esi, esi
00ac964a  74bf                     je         0xac960b
00ac964c  837e1c08                 cmp        dword ptr [esi + 0x1c], 8
00ac9650  7205                     jb         0xac9657
00ac9652  8b4608                   mov        eax, dword ptr [esi + 8]
00ac9655  eb03                     jmp        0xac965a
00ac9657  8d4608                   lea        eax, [esi + 8]
00ac965a  68a036e100               push       0xe136a0
00ac965f  50                       push       eax
00ac9660  e8c4861300               call       0xc01d29
00ac9665  8bd8                     mov        ebx, eax
00ac9667  83c408                   add        esp, 8
00ac966a  85db                     test       ebx, ebx
00ac966c  749d                     je         0xac960b
00ac966e  8b07                     mov        eax, dword ptr [edi]
00ac9670  6a00                     push       0
00ac9672  50                       push       eax
00ac9673  53                       push       ebx
00ac9674  e83b901300               call       0xc026b4
00ac9679  83c40c                   add        esp, 0xc
00ac967c  5f                       pop        edi
00ac967d  891e                     mov        dword ptr [esi], ebx
00ac967f  5e                       pop        esi
00ac9680  8bc3                     mov        eax, ebx
00ac9682  5b                       pop        ebx
00ac9683  8be5                     mov        esp, ebp
00ac9685  5d                       pop        ebp
00ac9686  c20c00                   ret        0xc