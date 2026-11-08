004aedd0  5c                       pop        esp
004aedd1  16                       push       ss
004aedd2  0000                     add        byte ptr [eax], al
004aedd4  889e64160000             mov        byte ptr [esi + 0x1664], bl
004aedda  889e66160000             mov        byte ptr [esi + 0x1666], bl
004aede0  899e68160000             mov        dword ptr [esi + 0x1668], ebx
004aede6  c7866c160000ffffffff     mov        dword ptr [esi + 0x166c], 0xffffffff
004aedf0  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004aedf6  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004aedf9  8b8674160000             mov        eax, dword ptr [esi + 0x1674]
004aedff  8d0482                   lea        eax, [edx + eax*4]
004aee02  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004aee08  8bc8                     mov        ecx, eax
004aee0a  f7d1                     not        ecx
004aee0c  33ca                     xor        ecx, edx
004aee0e  8908                     mov        dword ptr [eax], ecx
004aee10  a1d8012101               mov        eax, dword ptr [0x12101d8]
004aee15  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004aee18  8b9674160000             mov        edx, dword ptr [esi + 0x1674]
004aee1e  8d0491                   lea        eax, [ecx + edx*4]
004aee21  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004aee27  8bd0                     mov        edx, eax
004aee29  6a01                     push       1
004aee2b  f7d2                     not        edx
004aee2d  6a01                     push       1
004aee2f  33d1                     xor        edx, ecx
004aee31  53                       push       ebx
004aee32  8910                     mov        dword ptr [eax], edx
004aee34  8b06                     mov        eax, dword ptr [esi]
004aee36  53                       push       ebx
004aee37  8bce                     mov        ecx, esi
004aee39  ff902c020000             call       dword ptr [eax + 0x22c]
004aee3f  8d8e44160000             lea        ecx, [esi + 0x1644]
004aee45  e826315a00               call       0xa51f70
004aee4a  8b16                     mov        edx, dword ptr [esi]
004aee4c  8bce                     mov        ecx, esi
004aee4e  ff923c030000             call       dword ptr [edx + 0x33c]
004aee54  8b06                     mov        eax, dword ptr [esi]
004aee56  8bce                     mov        ecx, esi
004aee58  ff90d8040000             call       dword ptr [eax + 0x4d8]
004aee5e  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004aee64  8b4244                   mov        eax, dword ptr [edx + 0x44]
004aee67  8b8e84180000             mov        ecx, dword ptr [esi + 0x1884]
004aee6d  8b15dc012101             mov        edx, dword ptr [0x12101dc]
004aee73  8d0488                   lea        eax, [eax + ecx*4]
004aee76  8bc8                     mov        ecx, eax
004aee78  33ca                     xor        ecx, edx
004aee7a  8908                     mov        dword ptr [eax], ecx
004aee7c  a1d8012101               mov        eax, dword ptr [0x12101d8]
004aee81  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004aee84  8b9684180000             mov        edx, dword ptr [esi + 0x1884]
004aee8a  8d0491                   lea        eax, [ecx + edx*4]
004aee8d  8b                       .byte      0x8b
004aee8e  0d                       .byte      0x0d
004aee8f  dc                       .byte      0xdc