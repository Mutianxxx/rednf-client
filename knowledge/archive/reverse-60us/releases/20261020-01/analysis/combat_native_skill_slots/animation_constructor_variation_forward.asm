00472c74  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00472c77  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00472c7a  8b5518                   mov        edx, dword ptr [ebp + 0x18]
00472c7d  50                       push       eax
00472c7e  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00472c81  51                       push       ecx
00472c82  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00472c85  53                       push       ebx
00472c86  6a01                     push       1
00472c88  52                       push       edx
00472c89  50                       push       eax
00472c8a  51                       push       ecx
00472c8b  8bce                     mov        ecx, esi
00472c8d  e83e6e5b00               call       0xa29ad0
00472c92  8bc6                     mov        eax, esi
00472c94  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00472c97  5f                       pop        edi
00472c98  5e                       pop        esi
00472c99  5b                       pop        ebx
00472c9a  64890d00000000           mov        dword ptr fs:[0], ecx
00472ca1  8be5                     mov        esp, ebp
00472ca3  5d                       pop        ebp
00472ca4  c21400                   ret        0x14
