005ce740  55                       push       ebp
005ce741  8bec                     mov        ebp, esp
005ce743  6aff                     push       -1
005ce745  68083bc600               push       0xc63b08
005ce74a  64a100000000             mov        eax, dword ptr fs:[0]
005ce750  50                       push       eax
005ce751  64892500000000           mov        dword ptr fs:[0], esp
005ce758  51                       push       ecx
005ce759  8b4508                   mov        eax, dword ptr [ebp + 8]
005ce75c  56                       push       esi
005ce75d  57                       push       edi
005ce75e  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
005ce761  57                       push       edi
005ce762  8bf1                     mov        esi, ecx
005ce764  50                       push       eax
005ce765  8975f0                   mov        dword ptr [ebp - 0x10], esi
005ce768  e8b31fecff               call       0x490720
005ce76d  57                       push       edi
005ce76e  8bce                     mov        ecx, esi
005ce770  c745fc00000000           mov        dword ptr [ebp - 4], 0
005ce777  c706d457d000             mov        dword ptr [esi], 0xd057d4
005ce77d  e82e90ffff               call       0x5c77b0
005ce782  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
005ce785  5f                       pop        edi
005ce786  8bc6                     mov        eax, esi
005ce788  5e                       pop        esi
005ce789  64890d00000000           mov        dword ptr fs:[0], ecx
005ce790  8be5                     mov        esp, ebp
005ce792  5d                       pop        ebp
005ce793  c20800                   ret        8