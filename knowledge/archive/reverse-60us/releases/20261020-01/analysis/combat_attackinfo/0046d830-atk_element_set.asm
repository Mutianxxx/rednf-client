0046d830  55                       push       ebp
0046d831  8bec                     mov        ebp, esp
0046d833  83ec08                   sub        esp, 8
0046d836  8b5508                   mov        edx, dword ptr [ebp + 8]
0046d839  b804000000               mov        eax, 4
0046d83e  3bd0                     cmp        edx, eax
0046d840  56                       push       esi
0046d841  8d713c                   lea        esi, [ecx + 0x3c]
0046d844  752d                     jne        0x46d873
0046d846  8b4604                   mov        eax, dword ptr [esi + 4]
0046d849  8b4804                   mov        ecx, dword ptr [eax + 4]
0046d84c  51                       push       ecx
0046d84d  8bce                     mov        ecx, esi
0046d84f  e8dc5ffcff               call       0x433830
0046d854  8b4604                   mov        eax, dword ptr [esi + 4]
0046d857  894004                   mov        dword ptr [eax + 4], eax
0046d85a  8b4604                   mov        eax, dword ptr [esi + 4]
0046d85d  c7460800000000           mov        dword ptr [esi + 8], 0
0046d864  8900                     mov        dword ptr [eax], eax
0046d866  8b7604                   mov        esi, dword ptr [esi + 4]
0046d869  897608                   mov        dword ptr [esi + 8], esi
0046d86c  5e                       pop        esi
0046d86d  8be5                     mov        esp, ebp
0046d86f  5d                       pop        ebp
0046d870  c20400                   ret        4
0046d873  8d55fc                   lea        edx, [ebp - 4]
0046d876  52                       push       edx
0046d877  8bce                     mov        ecx, esi
0046d879  8945fc                   mov        dword ptr [ebp - 4], eax
0046d87c  e8affaffff               call       0x46d330
0046d881  8d4508                   lea        eax, [ebp + 8]
0046d884  50                       push       eax
0046d885  8d4df8                   lea        ecx, [ebp - 8]
0046d888  51                       push       ecx
0046d889  8bce                     mov        ecx, esi
0046d88b  e8e0e4ffff               call       0x46bd70
0046d890  5e                       pop        esi
0046d891  8be5                     mov        esp, ebp
0046d893  5d                       pop        ebp
0046d894  c20400                   ret        4
