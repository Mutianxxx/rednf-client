005c77b0  55                       push       ebp
005c77b1  8bec                     mov        ebp, esp
005c77b3  db4508                   fild       dword ptr [ebp + 8]
005c77b6  56                       push       esi
005c77b7  8bf1                     mov        esi, ecx
005c77b9  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
005c77bf  8b5144                   mov        edx, dword ptr [ecx + 0x44]
005c77c2  d95d08                   fstp       dword ptr [ebp + 8]
005c77c5  8b86e0050000             mov        eax, dword ptr [esi + 0x5e0]
005c77cb  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
005c77d1  8d0482                   lea        eax, [edx + eax*4]
005c77d4  8bd0                     mov        edx, eax
005c77d6  33d1                     xor        edx, ecx
005c77d8  8b4d08                   mov        ecx, dword ptr [ebp + 8]
005c77db  33d1                     xor        edx, ecx
005c77dd  8910                     mov        dword ptr [eax], edx
005c77df  8b15d8012101             mov        edx, dword ptr [0x12101d8]
005c77e5  8b5248                   mov        edx, dword ptr [edx + 0x48]
005c77e8  8b86e0050000             mov        eax, dword ptr [esi + 0x5e0]
005c77ee  8d0482                   lea        eax, [edx + eax*4]
005c77f1  57                       push       edi
005c77f2  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
005c77f8  8bd0                     mov        edx, eax
005c77fa  33d7                     xor        edx, edi
005c77fc  33d1                     xor        edx, ecx
005c77fe  68a008cf00               push       0xcf08a0
005c7803  8910                     mov        dword ptr [eax], edx
005c7805  e8c3856300               call       0xbffdcd
005c780a  83c404                   add        esp, 4
005c780d  50                       push       eax
005c780e  68a008cf00               push       0xcf08a0
005c7813  8d8ebc070000             lea        ecx, [esi + 0x7bc]
005c7819  e862b6e3ff               call       0x402e80
005c781e  5f                       pop        edi
005c781f  5e                       pop        esi
005c7820  5d                       pop        ebp
005c7821  c20400                   ret        4