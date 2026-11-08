00511dd0  55                       push       ebp
00511dd1  8bec                     mov        ebp, esp
00511dd3  56                       push       esi
00511dd4  8bf1                     mov        esi, ecx
00511dd6  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511dd9  85c9                     test       ecx, ecx
00511ddb  7442                     je         0x511e1f
00511ddd  e8aea2f8ff               call       0x49c090
00511de2  84c0                     test       al, al
00511de4  7439                     je         0x511e1f
00511de6  8b06                     mov        eax, dword ptr [esi]
00511de8  85c0                     test       eax, eax
00511dea  8bd0                     mov        edx, eax
00511dec  7503                     jne        0x511df1
00511dee  8d5608                   lea        edx, [esi + 8]
00511df1  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00511df4  53                       push       ebx
00511df5  8b5c8a1c                 mov        ebx, dword ptr [edx + ecx*4 + 0x1c]
00511df9  57                       push       edi
00511dfa  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00511dfd  3bdf                     cmp        ebx, edi
00511dff  741c                     je         0x511e1d
00511e01  85c0                     test       eax, eax
00511e03  7503                     jne        0x511e08
00511e05  8d4608                   lea        eax, [esi + 8]
00511e08  6aff                     push       -1
00511e0a  897c881c                 mov        dword ptr [eax + ecx*4 + 0x1c], edi
00511e0e  51                       push       ecx
00511e0f  8bce                     mov        ecx, esi
00511e11  c686f800000001           mov        byte ptr [esi + 0xf8], 1
00511e18  e8a3f2ffff               call       0x5110c0
00511e1d  5f                       pop        edi
00511e1e  5b                       pop        ebx
00511e1f  5e                       pop        esi
00511e20  5d                       pop        ebp
00511e21  c20800                   ret        8
00511e24  cc                       int3       
00511e25  cc                       int3       
00511e26  cc                       int3       
00511e27  cc                       int3       
00511e28  cc                       int3       
00511e29  cc                       int3       
00511e2a  cc                       int3       
00511e2b  cc                       int3       
00511e2c  cc                       int3       
00511e2d  cc                       int3       
00511e2e  cc                       int3       
00511e2f  cc                       int3       
00511e30  55                       push       ebp
00511e31  8bec                     mov        ebp, esp
00511e33  56                       push       esi
00511e34  8bf1                     mov        esi, ecx
00511e36  8a8600010000             mov        al, byte ptr [esi + 0x100]
00511e3c  84c0                     test       al, al
00511e3e  746e                     je         0x511eae
00511e40  8d8ea0000000             lea        ecx, [esi + 0xa0]
00511e46  e8b5505f00               call       0xb06f00
00511e4b  89863c010000             mov        dword ptr [esi + 0x13c], eax
00511e51  8b4508                   mov        eax, dword ptr [ebp + 8]
00511e54  85c0                     test       eax, eax
00511e56  6a00                     push       0
00511e58  7512                     jne        0x511e6c
00511e5a  d98630010000             fld        dword ptr [esi + 0x130]
00511e60  51                       push       ecx
00511e61  d8054069cd00             fadd       dword ptr [0xcd6940]
00511e67  d91c24                   fstp       dword ptr [esp]
00511e6a  eb07                     jmp        0x511e73
00511e6c  8b8630010000             mov        eax, dword ptr [esi + 0x130]
00511e72  50                       push       eax
00511e73  8bce                     mov        ecx, esi
00511e75  e896f4ffff               call       0x511310
00511e7a  8b06                     mov        eax, dword ptr [esi]
00511e7c  85c0                     test       eax, eax
00511e7e  7503                     jne        0x511e83
00511e80  8d4608                   lea        eax, [esi + 8]
00511e83  c6403400                 mov        byte ptr [eax + 0x34], 0
00511e87  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511e8a  85c9                     test       ecx, ecx
00511e8c  7420                     je         0x511eae
00511e8e  8b11                     mov        edx, dword ptr [ecx]
