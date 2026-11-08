004a3630  55                       push       ebp
004a3631  8bec                     mov        ebp, esp
004a3633  51                       push       ecx
004a3634  53                       push       ebx
004a3635  56                       push       esi
004a3636  8bf1                     mov        esi, ecx
004a3638  8b5e08                   mov        ebx, dword ptr [esi + 8]
004a363b  57                       push       edi
004a363c  8b7e04                   mov        edi, dword ptr [esi + 4]
004a363f  8bcb                     mov        ecx, ebx
004a3641  2bcf                     sub        ecx, edi
004a3643  b895204f09               mov        eax, 0x94f2095
004a3648  f7e9                     imul       ecx
004a364a  c1fa04                   sar        edx, 4
004a364d  8bca                     mov        ecx, edx
004a364f  c1e91f                   shr        ecx, 0x1f
004a3652  03ca                     add        ecx, edx
004a3654  8b560c                   mov        edx, dword ptr [esi + 0xc]
004a3657  2bd7                     sub        edx, edi
004a3659  b895204f09               mov        eax, 0x94f2095
004a365e  f7ea                     imul       edx
004a3660  c1fa04                   sar        edx, 4
004a3663  8bc2                     mov        eax, edx
004a3665  c1e81f                   shr        eax, 0x1f
004a3668  03c2                     add        eax, edx
004a366a  3bc8                     cmp        ecx, eax
004a366c  731f                     jae        0x4a368d
004a366e  8b5508                   mov        edx, dword ptr [ebp + 8]
004a3671  52                       push       edx
004a3672  8d8bb8010000             lea        ecx, [ebx + 0x1b8]
004a3678  53                       push       ebx
004a3679  894e08                   mov        dword ptr [esi + 8], ecx
004a367c  e8affcffff               call       0x4a3330
004a3681  83c408                   add        esp, 8
004a3684  5f                       pop        edi
004a3685  5e                       pop        esi
004a3686  5b                       pop        ebx
004a3687  8be5                     mov        esp, ebp
004a3689  5d                       pop        ebp
004a368a  c20400                   ret        4
