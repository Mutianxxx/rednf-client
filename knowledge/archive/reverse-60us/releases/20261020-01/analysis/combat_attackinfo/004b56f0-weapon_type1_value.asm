004b56f0  55                       push       ebp
004b56f1  8bec                     mov        ebp, esp
004b56f3  51                       push       ecx
004b56f4  56                       push       esi
004b56f5  57                       push       edi
004b56f6  8db178020000             lea        esi, [ecx + 0x278]
004b56fc  8db980020000             lea        edi, [ecx + 0x280]
004b5702  8bce                     mov        ecx, esi
004b5704  e857c9f4ff               call       0x402060
004b5709  8945fc                   mov        dword ptr [ebp - 4], eax
004b570c  db45fc                   fild       dword ptr [ebp - 4]
004b570f  8bcf                     mov        ecx, edi
004b5711  d95dfc                   fstp       dword ptr [ebp - 4]
004b5714  e897dcf7ff               call       0x4333b0
004b5719  d84dfc                   fmul       dword ptr [ebp - 4]
004b571c  e823be7400               call       0xc01544
004b5721  3d24faffff               cmp        eax, 0xfffffa24
004b5726  7d0b                     jge        0x4b5733
004b5728  5f                       pop        edi
004b5729  b824faffff               mov        eax, 0xfffffa24
004b572e  5e                       pop        esi
004b572f  8be5                     mov        esp, ebp
004b5731  5d                       pop        ebp
004b5732  c3                       ret        
004b5733  8bce                     mov        ecx, esi
004b5735  e826c9f4ff               call       0x402060
004b573a  8945fc                   mov        dword ptr [ebp - 4], eax
004b573d  db45fc                   fild       dword ptr [ebp - 4]
004b5740  8bcf                     mov        ecx, edi
004b5742  d95dfc                   fstp       dword ptr [ebp - 4]
004b5745  e866dcf7ff               call       0x4333b0
004b574a  d84dfc                   fmul       dword ptr [ebp - 4]
004b574d  e8f2bd7400               call       0xc01544
004b5752  5f                       pop        edi
004b5753  5e                       pop        esi
004b5754  8be5                     mov        esp, ebp
004b5756  5d                       pop        ebp
004b5757  c3                       ret        
