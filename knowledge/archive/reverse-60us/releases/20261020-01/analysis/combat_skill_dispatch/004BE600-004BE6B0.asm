004be600  55                       push       ebp
004be601  8bec                     mov        ebp, esp
004be603  56                       push       esi
004be604  57                       push       edi
004be605  8b7d08                   mov        edi, dword ptr [ebp + 8]
004be608  833f04                   cmp        dword ptr [edi], 4
004be60b  8bf1                     mov        esi, ecx
004be60d  7531                     jne        0x4be640
004be60f  8b06                     mov        eax, dword ptr [esi]
004be611  ff9030020000             call       dword ptr [eax + 0x230]
004be617  83f810                   cmp        eax, 0x10
004be61a  7524                     jne        0x4be640
004be61c  8b16                     mov        edx, dword ptr [esi]
004be61e  6a01                     push       1
004be620  6a01                     push       1
004be622  6a00                     push       0
004be624  6a11                     push       0x11
004be626  8bce                     mov        ecx, esi
004be628  ff922c020000             call       dword ptr [edx + 0x22c]
004be62e  8b06                     mov        eax, dword ptr [esi]
004be630  6a01                     push       1
004be632  6a01                     push       1
004be634  6a00                     push       0
004be636  6a00                     push       0
004be638  8bce                     mov        ecx, esi
004be63a  ff902c020000             call       dword ptr [eax + 0x22c]
004be640  57                       push       edi
004be641  8bce                     mov        ecx, esi
004be643  e8c80cffff               call       0x4af310
004be648  5f                       pop        edi
004be649  5e                       pop        esi
004be64a  5d                       pop        ebp
004be64b  c20400                   ret        4
004be64e  cc                       int3       
004be64f  cc                       int3       
004be650  56                       push       esi
004be651  8bf1                     mov        esi, ecx
004be653  8b86702a0000             mov        eax, dword ptr [esi + 0x2a70]
004be659  85c0                     test       eax, eax
004be65b  0f84b3000000             je         0x4be714
004be661  8b06                     mov        eax, dword ptr [esi]
004be663  6a01                     push       1
004be665  6a01                     push       1
004be667  6a00                     push       0
004be669  6a10                     push       0x10
004be66b  ff902c020000             call       dword ptr [eax + 0x22c]
004be671  8b8e702a0000             mov        ecx, dword ptr [esi + 0x2a70]
004be677  0fbf01                   movsx      eax, word ptr [ecx]
004be67a  8b16                     mov        edx, dword ptr [esi]
004be67c  6a00                     push       0
004be67e  6a00                     push       0
004be680  6a00                     push       0
004be682  50                       push       eax
004be683  50                       push       eax
004be684  6a00                     push       0
004be686  8bce                     mov        ecx, esi
004be688  ff9288040000             call       dword ptr [edx + 0x488]
004be68e  8b86702a0000             mov        eax, dword ptr [esi + 0x2a70]
004be694  0fbf4002                 movsx      eax, word ptr [eax + 2]
004be698  8b16                     mov        edx, dword ptr [esi]
004be69a  6a00                     push       0
004be69c  6a00                     push       0
004be69e  6a00                     push       0
004be6a0  50                       push       eax
004be6a1  50                       push       eax
004be6a2  6a01                     push       1
004be6a4  8bce                     mov        ecx, esi
004be6a6  ff9288040000             call       dword ptr [edx + 0x488]
004be6ac  8b                       .byte      0x8b
004be6ad  86702a                   xchg       byte ptr [eax + 0x2a], dh