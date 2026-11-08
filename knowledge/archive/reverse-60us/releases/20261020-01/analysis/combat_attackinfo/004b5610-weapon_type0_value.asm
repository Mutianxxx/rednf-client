004b5610  55                       push       ebp
004b5611  8bec                     mov        ebp, esp
004b5613  51                       push       ecx
004b5614  56                       push       esi
004b5615  57                       push       edi
004b5616  8db158020000             lea        esi, [ecx + 0x258]
004b561c  8db960020000             lea        edi, [ecx + 0x260]
004b5622  8bce                     mov        ecx, esi
004b5624  e837caf4ff               call       0x402060
004b5629  8945fc                   mov        dword ptr [ebp - 4], eax
004b562c  db45fc                   fild       dword ptr [ebp - 4]
004b562f  8bcf                     mov        ecx, edi
004b5631  d95dfc                   fstp       dword ptr [ebp - 4]
004b5634  e877ddf7ff               call       0x4333b0
004b5639  d84dfc                   fmul       dword ptr [ebp - 4]
004b563c  e803bf7400               call       0xc01544
004b5641  3d24faffff               cmp        eax, 0xfffffa24
004b5646  7d0b                     jge        0x4b5653
004b5648  5f                       pop        edi
004b5649  b824faffff               mov        eax, 0xfffffa24
004b564e  5e                       pop        esi
004b564f  8be5                     mov        esp, ebp
004b5651  5d                       pop        ebp
004b5652  c3                       ret        
004b5653  8bce                     mov        ecx, esi
004b5655  e806caf4ff               call       0x402060
004b565a  8945fc                   mov        dword ptr [ebp - 4], eax
004b565d  db45fc                   fild       dword ptr [ebp - 4]
004b5660  8bcf                     mov        ecx, edi
004b5662  d95dfc                   fstp       dword ptr [ebp - 4]
004b5665  e846ddf7ff               call       0x4333b0
004b566a  d84dfc                   fmul       dword ptr [ebp - 4]
004b566d  e8d2be7400               call       0xc01544
004b5672  5f                       pop        edi
004b5673  5e                       pop        esi
004b5674  8be5                     mov        esp, ebp
004b5676  5d                       pop        ebp
004b5677  c3                       ret        
