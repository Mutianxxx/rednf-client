004edcd0  55                       push       ebp
004edcd1  8bec                     mov        ebp, esp
004edcd3  8b4508                   mov        eax, dword ptr [ebp + 8]
004edcd6  85c0                     test       eax, eax
004edcd8  56                       push       esi
004edcd9  8bf1                     mov        esi, ecx
004edcdb  8d8e60020000             lea        ecx, [esi + 0x260]
004edce1  7514                     jne        0x4edcf7
004edce3  e84877f4ff               call       0x435430
004edce8  8b06                     mov        eax, dword ptr [esi]
004edcea  8bce                     mov        ecx, esi
004edcec  ff90a0010000             call       dword ptr [eax + 0x1a0]
004edcf2  5e                       pop        esi
004edcf3  5d                       pop        ebp
004edcf4  c20400                   ret        4
004edcf7  50                       push       eax
004edcf8  e8e34afbff               call       0x4a27e0
004edcfd  8b06                     mov        eax, dword ptr [esi]
004edcff  8bce                     mov        ecx, esi
004edd01  ff90a0010000             call       dword ptr [eax + 0x1a0]
004edd07  5e                       pop        esi
004edd08  5d                       pop        ebp
004edd09  c20400                   ret        4
