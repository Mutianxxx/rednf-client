004bf9d0  a1d4f10401               mov        eax, dword ptr [0x104f1d4]
004bf9d5  56                       push       esi
004bf9d6  8bf1                     mov        esi, ecx
004bf9d8  3bc6                     cmp        eax, esi
004bf9da  742b                     je         0x4bfa07
004bf9dc  e8afc6fdff               call       0x49c090
004bf9e1  84c0                     test       al, al
004bf9e3  7422                     je         0x4bfa07
004bf9e5  8b06                     mov        eax, dword ptr [esi]
004bf9e7  8bce                     mov        ecx, esi
004bf9e9  ff903c070000             call       dword ptr [eax + 0x73c]
004bf9ef  8bc8                     mov        ecx, eax
004bf9f1  e88a930900               call       0x558d80
004bf9f6  8b16                     mov        edx, dword ptr [esi]
004bf9f8  8bce                     mov        ecx, esi
004bf9fa  ff9238070000             call       dword ptr [edx + 0x738]
004bfa00  8b10                     mov        edx, dword ptr [eax]
004bfa02  8bc8                     mov        ecx, eax
004bfa04  ff5204                   call       dword ptr [edx + 4]
004bfa07  8b06                     mov        eax, dword ptr [esi]
004bfa09  8bce                     mov        ecx, esi
004bfa0b  ff5034                   call       dword ptr [eax + 0x34]
004bfa0e  84c0                     test       al, al
004bfa10  0f84a0000000             je         0x4bfab6
004bfa16  8d8e5c150000             lea        ecx, [esi + 0x155c]
004bfa1c  e83f26f4ff               call       0x402060
004bfa21  85c0                     test       eax, eax
004bfa23  0f8583000000             jne        0x4bfaac
004bfa29  83bea42a0000fe           cmp        dword ptr [esi + 0x2aa4], -2
004bfa30  757a                     jne        0x4bfaac
004bfa32  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004bfa38  8b08                     mov        ecx, dword ptr [eax]
004bfa3a  85c9                     test       ecx, ecx
004bfa3c  7503                     jne        0x4bfa41
004bfa3e  8d4808                   lea        ecx, [eax + 8]
004bfa41  8b11                     mov        edx, dword ptr [ecx]
004bfa43  6a00                     push       0
004bfa45  ff5208                   call       dword ptr [edx + 8]
004bfa48  d905a4d7e900             fld        dword ptr [0xe9d7a4]
004bfa4e  dae9                     fucompp    
004bfa50  dfe0                     fnstsw     ax
004bfa52  f6c444                   test       ah, 0x44
004bfa55  7b18                     jnp        0x4bfa6f
004bfa57  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004bfa5d  8b08                     mov        ecx, dword ptr [eax]
004bfa5f  85c9                     test       ecx, ecx
004bfa61  7503                     jne        0x4bfa66
004bfa63  8d4808                   lea        ecx, [eax + 8]
004bfa66  8b01                     mov        eax, dword ptr [ecx]
004bfa68  6a00                     push       0
004bfa6a  6a00                     push       0
004bfa6c  ff500c                   call       dword ptr [eax + 0xc]
004bfa6f  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004bfa75  8b08                     mov        ecx, dword ptr [eax]
004bfa77  85c9                     test       ecx, ecx
004bfa79  7503                     jne        0x4bfa7e
004bfa7b  8d4808                   lea        ecx, [eax + 8]
004bfa7e  8b11                     mov        edx, dword ptr [ecx]
004bfa80  6a01                     push       1
004bfa82  ff5208                   call       dword ptr [edx + 8]
004bfa85  d905a4d7e900             fld        dword ptr [0xe9d7a4]
004bfa8b  dae9                     fucompp    
004bfa8d  dfe0                     fnstsw     ax
004bfa8f  f6c444                   test       ah, 0x44
004bfa92  7b18                     jnp        0x4bfaac
004bfa94  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004bfa9a  8b08                     mov        ecx, dword ptr [eax]
004bfa9c  85c9                     test       ecx, ecx
004bfa9e  7503                     jne        0x4bfaa3
004bfaa0  8d4808                   lea        ecx, [eax + 8]
004bfaa3  8b01                     mov        eax, dword ptr [ecx]
004bfaa5  6a00                     push       0
004bfaa7  6a01                     push       1
004bfaa9  ff500c                   call       dword ptr [eax + 0xc]
004bfaac  8b16                     mov        edx, dword ptr [esi]
004bfaae  8bce                     mov        ecx, esi
004bfab0  ff92d4070000             call       dword ptr [edx + 0x7d4]
004bfab6  8bce                     mov        ecx, esi
004bfab8  e863c70100               call       0x4dc220