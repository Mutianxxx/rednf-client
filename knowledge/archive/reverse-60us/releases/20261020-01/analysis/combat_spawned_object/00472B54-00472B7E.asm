00472b54  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00472b57  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00472b5a  8b5508                   mov        edx, dword ptr [ebp + 8]
00472b5d  53                       push       ebx
00472b5e  53                       push       ebx
00472b5f  53                       push       ebx
00472b60  53                       push       ebx
00472b61  50                       push       eax
00472b62  51                       push       ecx
00472b63  52                       push       edx
00472b64  8bce                     mov        ecx, esi
00472b66  e8656f5b00               call       0xa29ad0
00472b6b  5f                       pop        edi
00472b6c  8bc6                     mov        eax, esi
00472b6e  5e                       pop        esi
00472b6f  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00472b72  5b                       pop        ebx
00472b73  64890d00000000           mov        dword ptr fs:[0], ecx
00472b7a  8be5                     mov        esp, ebp
00472b7c  5d                       pop        ebp
00472b7d  c2                       .byte      0xc2