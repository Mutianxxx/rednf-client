004b9b20  55                       push       ebp
004b9b21  8bec                     mov        ebp, esp
004b9b23  51                       push       ecx
004b9b24  57                       push       edi
004b9b25  8bf9                     mov        edi, ecx
004b9b27  e86425feff               call       0x49c090
004b9b2c  84c0                     test       al, al
004b9b2e  750b                     jne        0x4b9b3b
004b9b30  8a4510                   mov        al, byte ptr [ebp + 0x10]
004b9b33  84c0                     test       al, al
004b9b35  0f84ac000000             je         0x4b9be7
004b9b3b  8b87b0010000             mov        eax, dword ptr [edi + 0x1b0]
004b9b41  85c0                     test       eax, eax
004b9b43  0f859e000000             jne        0x4b9be7
004b9b49  8b07                     mov        eax, dword ptr [edi]
004b9b4b  6a10                     push       0x10
004b9b4d  8bcf                     mov        ecx, edi
004b9b4f  ff9010040000             call       dword ptr [eax + 0x410]
004b9b55  84c0                     test       al, al
004b9b57  0f858a000000             jne        0x4b9be7
004b9b5d  53                       push       ebx
004b9b5e  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004b9b61  83fb04                   cmp        ebx, 4
004b9b64  56                       push       esi
004b9b65  c645fc01                 mov        byte ptr [ebp - 4], 1
004b9b69  7406                     je         0x4b9b71
004b9b6b  837d0c04                 cmp        dword ptr [ebp + 0xc], 4
004b9b6f  7504                     jne        0x4b9b75
004b9b71  c645fc00                 mov        byte ptr [ebp - 4], 0
004b9b75  c6450a01                 mov        byte ptr [ebp + 0xa], 1
004b9b79  c6450b01                 mov        byte ptr [ebp + 0xb], 1
004b9b7d  33f6                     xor        esi, esi
004b9b7f  90                       nop        
004b9b80  85f6                     test       esi, esi
004b9b82  8bc3                     mov        eax, ebx
004b9b84  7403                     je         0x4b9b89
004b9b86  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b9b89  3b84b708160000           cmp        eax, dword ptr [edi + esi*4 + 0x1608]
004b9b90  7515                     jne        0x4b9ba7
004b9b92  8d8cf7f4150000           lea        ecx, [edi + esi*8 + 0x15f4]
004b9b99  e8c284f4ff               call       0x402060
004b9b9e  85c0                     test       eax, eax
004b9ba0  7405                     je         0x4b9ba7
004b9ba2  c644350a00               mov        byte ptr [ebp + esi + 0xa], 0
004b9ba7  46                       inc        esi
004b9ba8  83fe02                   cmp        esi, 2
004b9bab  7cd3                     jl         0x4b9b80
004b9bad  8a450a                   mov        al, byte ptr [ebp + 0xa]
004b9bb0  84c0                     test       al, al
004b9bb2  8b75fc                   mov        esi, dword ptr [ebp - 4]
004b9bb5  7412                     je         0x4b9bc9
004b9bb7  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b9bba  8b17                     mov        edx, dword ptr [edi]
004b9bbc  50                       push       eax
004b9bbd  56                       push       esi
004b9bbe  53                       push       ebx
004b9bbf  6a00                     push       0
004b9bc1  8bcf                     mov        ecx, edi
004b9bc3  ff9298040000             call       dword ptr [edx + 0x498]
004b9bc9  8a450b                   mov        al, byte ptr [ebp + 0xb]
004b9bcc  84c0                     test       al, al
004b9bce  7415                     je         0x4b9be5
004b9bd0  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b9bd3  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b9bd6  8b17                     mov        edx, dword ptr [edi]
004b9bd8  50                       push       eax
004b9bd9  56                       push       esi
004b9bda  51                       push       ecx
004b9bdb  6a01                     push       1
004b9bdd  8bcf                     mov        ecx, edi
004b9bdf  ff9298040000             call       dword ptr [edx + 0x498]
004b9be5  5e                       pop        esi
004b9be6  5b                       pop        ebx
004b9be7  5f                       pop        edi
004b9be8  8be5                     mov        esp, ebp
004b9bea  5d                       pop        ebp
004b9beb  c20c00                   ret        0xc
004b9bee  cc                       int3       
004b9bef  cc                       int3       
004b9bf0  55                       push       ebp
004b9bf1  8bec                     mov        ebp, esp
004b9bf3  8b4508                   mov        eax, dword ptr [ebp + 8]
004b9bf6  83f801                   cmp        eax, 1
004b9bf9  7515                     jne        0x4b9c10
004b9bfb  8b01                     mov        eax, dword ptr [ecx]
004b9bfd  6a03                     push       3
004b9bff  ff9044030000             call       dword ptr [eax + 0x344]
004b9c05  8bc8                     mov        ecx, eax
004b9c07  e8e4050000               call       0x4ba1f0
004b9c0c  5d                       pop        ebp
004b9c0d  c20400                   ret        4
004b9c10  83f802                   cmp        eax, 2
004b9c13  7515                     jne        0x4b9c2a
004b9c15  8b11                     mov        edx, dword ptr [ecx]
004b9c17  6a03                     push       3
