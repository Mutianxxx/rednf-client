004b9e40  55                       push       ebp
004b9e41  8bec                     mov        ebp, esp
004b9e43  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b9e49  8b5244                   mov        edx, dword ptr [edx + 0x44]
004b9e4c  8b811c160000             mov        eax, dword ptr [ecx + 0x161c]
004b9e52  56                       push       esi
004b9e53  8d0482                   lea        eax, [edx + eax*4]
004b9e56  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004b9e5c  8bf0                     mov        esi, eax
004b9e5e  33f2                     xor        esi, edx
004b9e60  8b5508                   mov        edx, dword ptr [ebp + 8]
004b9e63  33f2                     xor        esi, edx
004b9e65  8930                     mov        dword ptr [eax], esi
004b9e67  8b35d8012101             mov        esi, dword ptr [0x12101d8]
004b9e6d  8b7648                   mov        esi, dword ptr [esi + 0x48]
004b9e70  8b811c160000             mov        eax, dword ptr [ecx + 0x161c]
004b9e76  8d0486                   lea        eax, [esi + eax*4]
004b9e79  57                       push       edi
004b9e7a  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b9e80  8bf0                     mov        esi, eax
004b9e82  33f7                     xor        esi, edi
004b9e84  33f2                     xor        esi, edx
004b9e86  8930                     mov        dword ptr [eax], esi
004b9e88  8b810c160000             mov        eax, dword ptr [ecx + 0x160c]
004b9e8e  8b11                     mov        edx, dword ptr [ecx]
004b9e90  6a00                     push       0
004b9e92  50                       push       eax
004b9e93  8b8108160000             mov        eax, dword ptr [ecx + 0x1608]
004b9e99  50                       push       eax
004b9e9a  ff929c040000             call       dword ptr [edx + 0x49c]
004b9ea0  5f                       pop        edi
004b9ea1  5e                       pop        esi
004b9ea2  5d                       pop        ebp
004b9ea3  c20400                   ret        4
