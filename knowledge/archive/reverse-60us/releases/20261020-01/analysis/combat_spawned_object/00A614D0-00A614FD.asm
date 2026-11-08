00a614d0  55                       push       ebp
00a614d1  8bec                     mov        ebp, esp
00a614d3  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a614d6  56                       push       esi
00a614d7  8bf1                     mov        esi, ecx
00a614d9  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a614dc  50                       push       eax
00a614dd  51                       push       ecx
00a614de  6a00                     push       0
00a614e0  8bce                     mov        ecx, esi
00a614e2  e8c9ad1100               call       0xb7c2b0
00a614e7  8b5508                   mov        edx, dword ptr [ebp + 8]
00a614ea  c706f4c4e400             mov        dword ptr [esi], 0xe4c4f4
00a614f0  899620020000             mov        dword ptr [esi + 0x220], edx
00a614f6  8bc6                     mov        eax, esi
00a614f8  5e                       pop        esi
00a614f9  5d                       pop        ebp
00a614fa  c20c00                   ret        0xc