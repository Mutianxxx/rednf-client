004b89a2  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b89a5  85c0                     test       eax, eax
004b89a7  7504                     jne        0x4b89ad
004b89a9  33c9                     xor        ecx, ecx
004b89ab  eb08                     jmp        0x4b89b5
004b89ad  8b4e3c                   mov        ecx, dword ptr [esi + 0x3c]
004b89b0  2bc8                     sub        ecx, eax
004b89b2  c1f902                   sar        ecx, 2
004b89b5  8b5738                   mov        edx, dword ptr [edi + 0x38]
004b89b8  85d2                     test       edx, edx
004b89ba  741d                     je         0x4b89d9
004b89bc  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b89bf  2bc2                     sub        eax, edx
004b89c1  c1f802                   sar        eax, 2
004b89c4  3bc8                     cmp        ecx, eax
004b89c6  7311                     jae        0x4b89d9
004b89c8  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b89cb  85c9                     test       ecx, ecx
004b89cd  7505                     jne        0x4b89d4
004b89cf  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b89d2  eb1c                     jmp        0x4b89f0
004b89d4  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b89d7  eb0f                     jmp        0x4b89e8
004b89d9  8b4f38                   mov        ecx, dword ptr [edi + 0x38]
004b89dc  85c9                     test       ecx, ecx
004b89de  7505                     jne        0x4b89e5
004b89e0  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b89e3  eb0b                     jmp        0x4b89f0
004b89e5  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b89e8  2bc1                     sub        eax, ecx
004b89ea  c1f802                   sar        eax, 2
004b89ed  894510                   mov        dword ptr [ebp + 0x10], eax
004b89f0  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b89f3  33db                     xor        ebx, ebx
004b89f5  85c0                     test       eax, eax
004b89f7  7e34                     jle        0x4b8a2d
004b89f9  8da42400000000           lea        esp, [esp]
004b8a00  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b8a03  8d0c98                   lea        ecx, [eax + ebx*4]
004b8a06  833900                   cmp        dword ptr [ecx], 0
004b8a09  741a                     je         0x4b8a25
004b8a0b  8b5738                   mov        edx, dword ptr [edi + 0x38]
004b8a0e  8d049a                   lea        eax, [edx + ebx*4]
004b8a11  8b10                     mov        edx, dword ptr [eax]
004b8a13  85d2                     test       edx, edx
004b8a15  740e                     je         0x4b8a25
004b8a17  8b09                     mov        ecx, dword ptr [ecx]
004b8a19  8bc2                     mov        eax, edx
004b8a1b  8b5508                   mov        edx, dword ptr [ebp + 8]
004b8a1e  50                       push       eax
004b8a1f  52                       push       edx
004b8a20  e84b135700               call       0xa29d70
004b8a25  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b8a28  43                       inc        ebx
004b8a29  3bd8                     cmp        ebx, eax
004b8a2b  7cd3                     jl         0x4b8a00
004b8a2d  5f                       pop        edi
004b8a2e  5e                       pop        esi
004b8a2f  5b                       pop        ebx
004b8a30  5d                       pop        ebp
004b8a31  c2                       .byte      0xc2
