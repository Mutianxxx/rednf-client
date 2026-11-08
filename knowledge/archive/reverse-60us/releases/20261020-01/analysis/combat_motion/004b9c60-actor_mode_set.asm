004b9c60  55                       push       ebp
004b9c61  8bec                     mov        ebp, esp
004b9c63  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b9c66  53                       push       ebx
004b9c67  56                       push       esi
004b9c68  8bf1                     mov        esi, ecx
004b9c6a  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b9c6d  898614160000             mov        dword ptr [esi + 0x1614], eax
004b9c73  898e10160000             mov        dword ptr [esi + 0x1610], ecx
004b9c79  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b9c7e  8b4044                   mov        eax, dword ptr [eax + 0x44]
004b9c81  8b962c160000             mov        edx, dword ptr [esi + 0x162c]
004b9c87  8d0490                   lea        eax, [eax + edx*4]
004b9c8a  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004b9c90  57                       push       edi
004b9c91  8dbe28160000             lea        edi, [esi + 0x1628]
004b9c97  8bd8                     mov        ebx, eax
004b9c99  33da                     xor        ebx, edx
004b9c9b  8b5518                   mov        edx, dword ptr [ebp + 0x18]
004b9c9e  33da                     xor        ebx, edx
004b9ca0  8918                     mov        dword ptr [eax], ebx
004b9ca2  8b1dd8012101             mov        ebx, dword ptr [0x12101d8]
004b9ca8  8b5b48                   mov        ebx, dword ptr [ebx + 0x48]
004b9cab  8b4704                   mov        eax, dword ptr [edi + 4]
004b9cae  8d0483                   lea        eax, [ebx + eax*4]
004b9cb1  8bd8                     mov        ebx, eax
004b9cb3  331ddc012101             xor        ebx, dword ptr [0x12101dc]
004b9cb9  33da                     xor        ebx, edx
004b9cbb  8918                     mov        dword ptr [eax], ebx
004b9cbd  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b9cc2  8b4044                   mov        eax, dword ptr [eax + 0x44]
004b9cc5  8b9634160000             mov        edx, dword ptr [esi + 0x1634]
004b9ccb  8d0490                   lea        eax, [eax + edx*4]
004b9cce  8d9e30160000             lea        ebx, [esi + 0x1630]
004b9cd4  8bd0                     mov        edx, eax
004b9cd6  3315dc012101             xor        edx, dword ptr [0x12101dc]
004b9cdc  33551c                   xor        edx, dword ptr [ebp + 0x1c]
004b9cdf  8910                     mov        dword ptr [eax], edx
004b9ce1  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b9ce7  8b5248                   mov        edx, dword ptr [edx + 0x48]
004b9cea  8b4304                   mov        eax, dword ptr [ebx + 4]
004b9ced  8d0482                   lea        eax, [edx + eax*4]
004b9cf0  8bd0                     mov        edx, eax
004b9cf2  3315dc012101             xor        edx, dword ptr [0x12101dc]
004b9cf8  33551c                   xor        edx, dword ptr [ebp + 0x1c]
004b9cfb  85c9                     test       ecx, ecx
004b9cfd  8910                     mov        dword ptr [eax], edx
004b9cff  7427                     je         0x4b9d28
004b9d01  8b06                     mov        eax, dword ptr [esi]
004b9d03  51                       push       ecx
004b9d04  8bce                     mov        ecx, esi
004b9d06  ff9084050000             call       dword ptr [eax + 0x584]
004b9d0c  89451c                   mov        dword ptr [ebp + 0x1c], eax
004b9d0f  db451c                   fild       dword ptr [ebp + 0x1c]
004b9d12  8bcf                     mov        ecx, edi
004b9d14  d95d1c                   fstp       dword ptr [ebp + 0x1c]
004b9d17  e89496f7ff               call       0x4333b0
004b9d1c  d84d1c                   fmul       dword ptr [ebp + 0x1c]
004b9d1f  e820787400               call       0xc01544
004b9d24  8bf8                     mov        edi, eax
004b9d26  eb03                     jmp        0x4b9d2b
004b9d28  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
004b9d2b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b9d2e  85c0                     test       eax, eax
004b9d30  7427                     je         0x4b9d59
004b9d32  8b16                     mov        edx, dword ptr [esi]
004b9d34  50                       push       eax
004b9d35  8bce                     mov        ecx, esi
004b9d37  ff9284050000             call       dword ptr [edx + 0x584]
004b9d3d  89451c                   mov        dword ptr [ebp + 0x1c], eax
004b9d40  db451c                   fild       dword ptr [ebp + 0x1c]
004b9d43  8bcb                     mov        ecx, ebx
004b9d45  d95d1c                   fstp       dword ptr [ebp + 0x1c]
004b9d48  e86396f7ff               call       0x4333b0
004b9d4d  d84d1c                   fmul       dword ptr [ebp + 0x1c]
004b9d50  e8ef777400               call       0xc01544
004b9d55  8bd8                     mov        ebx, eax
004b9d57  eb03                     jmp        0x4b9d5c
004b9d59  8b5d14                   mov        ebx, dword ptr [ebp + 0x14]
004b9d5c  8b06                     mov        eax, dword ptr [esi]
004b9d5e  57                       push       edi
004b9d5f  8bce                     mov        ecx, esi
004b9d61  ff9088050000             call       dword ptr [eax + 0x588]
004b9d67  8b16                     mov        edx, dword ptr [esi]
004b9d69  53                       push       ebx
004b9d6a  8b                       .byte      0x8b
