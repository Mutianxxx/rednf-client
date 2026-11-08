004eb780  55                       push       ebp
004eb781  8bec                     mov        ebp, esp
004eb783  81ecd8010000             sub        esp, 0x1d8
004eb789  53                       push       ebx
004eb78a  56                       push       esi
004eb78b  8b7514                   mov        esi, dword ptr [ebp + 0x14]
004eb78e  8b06                     mov        eax, dword ptr [esi]
004eb790  57                       push       edi
004eb791  8bf9                     mov        edi, ecx
004eb793  8bce                     mov        ecx, esi
004eb795  897df8                   mov        dword ptr [ebp - 8], edi
004eb798  ff909c010000             call       dword ptr [eax + 0x19c]
004eb79e  8bd8                     mov        ebx, eax
004eb7a0  85db                     test       ebx, ebx
004eb7a2  895df4                   mov        dword ptr [ebp - 0xc], ebx
004eb7a5  7412                     je         0x4eb7b9
004eb7a7  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004eb7aa  85c0                     test       eax, eax
004eb7ac  7e0b                     jle        0x4eb7b9
004eb7ae  8bcb                     mov        ecx, ebx
004eb7b0  e8cbbcf7ff               call       0x467480
004eb7b5  84c0                     test       al, al
004eb7b7  750b                     jne        0x4eb7c4
004eb7b9  5f                       pop        edi
004eb7ba  5e                       pop        esi
004eb7bb  33c0                     xor        eax, eax
004eb7bd  5b                       pop        ebx
004eb7be  8be5                     mov        esp, ebp
004eb7c0  5d                       pop        ebp
004eb7c1  c21800                   ret        0x18
