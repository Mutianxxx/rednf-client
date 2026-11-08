0071cab0  55                       push       ebp
0071cab1  8bec                     mov        ebp, esp
0071cab3  56                       push       esi
0071cab4  8bf1                     mov        esi, ecx
0071cab6  e8d5f5d7ff               call       0x49c090
0071cabb  84c0                     test       al, al
0071cabd  744a                     je         0x71cb09
0071cabf  8b8628240000             mov        eax, dword ptr [esi + 0x2428]
0071cac5  85c0                     test       eax, eax
0071cac7  57                       push       edi
0071cac8  8b7d08                   mov        edi, dword ptr [ebp + 8]
0071cacb  752f                     jne        0x71cafc
0071cacd  8d8e2c240000             lea        ecx, [esi + 0x242c]
0071cad3  e88855ceff               call       0x402060
0071cad8  83f84a                   cmp        eax, 0x4a
0071cadb  751f                     jne        0x71cafc
0071cadd  83ffff                   cmp        edi, -1
0071cae0  751a                     jne        0x71cafc
0071cae2  8b06                     mov        eax, dword ptr [esi]
0071cae4  6a00                     push       0
0071cae6  6a00                     push       0
0071cae8  6a00                     push       0
0071caea  6a00                     push       0
0071caec  6a29                     push       0x29
0071caee  8bce                     mov        ecx, esi
0071caf0  ff908c020000             call       dword ptr [eax + 0x28c]
0071caf6  5f                       pop        edi
0071caf7  5e                       pop        esi
0071caf8  5d                       pop        ebp
0071caf9  c20800                   ret        8
0071cafc  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0071caff  51                       push       ecx
0071cb00  57                       push       edi
0071cb01  8bce                     mov        ecx, esi
0071cb03  e8e8b5dbff               call       0x4d80f0
0071cb08  5f                       pop        edi
0071cb09  5e                       pop        esi
0071cb0a  5d                       pop        ebp
0071cb0b  c20800                   ret        8