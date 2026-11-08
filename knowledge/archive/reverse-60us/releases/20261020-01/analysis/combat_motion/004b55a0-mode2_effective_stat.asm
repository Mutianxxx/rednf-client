004b55a0  55                       push       ebp
004b55a1  8bec                     mov        ebp, esp
004b55a3  51                       push       ecx
004b55a4  56                       push       esi
004b55a5  57                       push       edi
004b55a6  8db1f8010000             lea        esi, [ecx + 0x1f8]
004b55ac  8db900020000             lea        edi, [ecx + 0x200]
004b55b2  8bce                     mov        ecx, esi
004b55b4  e8a7caf4ff               call       0x402060
004b55b9  8945fc                   mov        dword ptr [ebp - 4], eax
004b55bc  db45fc                   fild       dword ptr [ebp - 4]
004b55bf  8bcf                     mov        ecx, edi
004b55c1  d95dfc                   fstp       dword ptr [ebp - 4]
004b55c4  e8e7ddf7ff               call       0x4333b0
004b55c9  d84dfc                   fmul       dword ptr [ebp - 4]
004b55cc  e873bf7400               call       0xc01544
004b55d1  83f801                   cmp        eax, 1
004b55d4  7e25                     jle        0x4b55fb
004b55d6  8bce                     mov        ecx, esi
004b55d8  e883caf4ff               call       0x402060
004b55dd  8945fc                   mov        dword ptr [ebp - 4], eax
004b55e0  db45fc                   fild       dword ptr [ebp - 4]
004b55e3  8bcf                     mov        ecx, edi
004b55e5  d95dfc                   fstp       dword ptr [ebp - 4]
004b55e8  e8c3ddf7ff               call       0x4333b0
004b55ed  d84dfc                   fmul       dword ptr [ebp - 4]
004b55f0  e84fbf7400               call       0xc01544
004b55f5  5f                       pop        edi
004b55f6  5e                       pop        esi
004b55f7  8be5                     mov        esp, ebp
004b55f9  5d                       pop        ebp
004b55fa  c3                       ret        
004b55fb  5f                       pop        edi
004b55fc  b801000000               mov        eax, 1
004b5601  5e                       pop        esi
004b5602  8be5                     mov        esp, ebp
004b5604  5d                       pop        ebp
004b5605  c3                       ret        
