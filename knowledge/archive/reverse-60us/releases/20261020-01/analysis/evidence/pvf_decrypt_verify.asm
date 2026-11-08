; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a54e70..00a54f39 (end exclusive); file offset 00654e70
; This is an instruction excerpt, not a recovered original source file.
00a54e70  55                       push       ebp
00a54e71  8bec                     mov        ebp, esp
00a54e73  53                       push       ebx
00a54e74  8bd8                     mov        ebx, eax
00a54e76  f6451003                 test       byte ptr [ebp + 0x10], 3
00a54e7a  56                       push       esi
00a54e7b  8bf1                     mov        esi, ecx
00a54e7d  7406                     je         0xa54e85
00a54e7f  5e                       pop        esi
00a54e80  33c0                     xor        eax, eax
00a54e82  5b                       pop        ebx
00a54e83  5d                       pop        ebp
00a54e84  c3                       ret        
00a54e85  e8a6ad0000               call       0xa5fc30
00a54e8a  a17c420d01               mov        eax, dword ptr [0x10d427c]
00a54e8f  85c0                     test       eax, eax
00a54e91  f7d6                     not        esi
00a54e93  7402                     je         0xa54e97
00a54e95  33d8                     xor        ebx, eax
00a54e97  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a54e9a  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a54e9d  c1e802                   shr        eax, 2
00a54ea0  57                       push       edi
00a54ea1  8d3c81                   lea        edi, [ecx + eax*4]
00a54ea4  3bcf                     cmp        ecx, edi
00a54ea6  747e                     je         0xa54f26
00a54ea8  8b11                     mov        edx, dword ptr [ecx]
00a54eaa  33d3                     xor        edx, ebx
00a54eac  8bc2                     mov        eax, edx
00a54eae  c1ea06                   shr        edx, 6
00a54eb1  c1e01a                   shl        eax, 0x1a
00a54eb4  0bc2                     or         eax, edx
00a54eb6  33d2                     xor        edx, edx
00a54eb8  8ad0                     mov        dl, al
00a54eba  8901                     mov        dword ptr [ecx], eax
00a54ebc  8bc6                     mov        eax, esi
00a54ebe  c1e808                   shr        eax, 8
00a54ec1  83c104                   add        ecx, 4
00a54ec4  33d6                     xor        edx, esi
00a54ec6  81e2ff000000             and        edx, 0xff
00a54ecc  8b349588420d01           mov        esi, dword ptr [edx*4 + 0x10d4288]
00a54ed3  33d2                     xor        edx, edx
00a54ed5  8a51fd                   mov        dl, byte ptr [ecx - 3]
00a54ed8  33c6                     xor        eax, esi
00a54eda  33d0                     xor        edx, eax
00a54edc  81e2ff000000             and        edx, 0xff
00a54ee2  8b349588420d01           mov        esi, dword ptr [edx*4 + 0x10d4288]
00a54ee9  33d2                     xor        edx, edx
00a54eeb  8a51fe                   mov        dl, byte ptr [ecx - 2]
00a54eee  c1e808                   shr        eax, 8
00a54ef1  33c6                     xor        eax, esi
00a54ef3  33d0                     xor        edx, eax
00a54ef5  81e2ff000000             and        edx, 0xff
00a54efb  8b349588420d01           mov        esi, dword ptr [edx*4 + 0x10d4288]
00a54f02  33d2                     xor        edx, edx
00a54f04  8a51ff                   mov        dl, byte ptr [ecx - 1]
00a54f07  c1e808                   shr        eax, 8
00a54f0a  33c6                     xor        eax, esi
00a54f0c  33d0                     xor        edx, eax
00a54f0e  81e2ff000000             and        edx, 0xff
00a54f14  8b349588420d01           mov        esi, dword ptr [edx*4 + 0x10d4288]
00a54f1b  c1e808                   shr        eax, 8
00a54f1e  33c6                     xor        eax, esi
00a54f20  3bcf                     cmp        ecx, edi
00a54f22  8bf0                     mov        esi, eax
00a54f24  7582                     jne        0xa54ea8
00a54f26  8bc6                     mov        eax, esi
00a54f28  8b7508                   mov        esi, dword ptr [ebp + 8]
00a54f2b  f7d0                     not        eax
00a54f2d  2bc6                     sub        eax, esi
00a54f2f  f7d8                     neg        eax
00a54f31  5f                       pop        edi
00a54f32  1bc0                     sbb        eax, eax
00a54f34  5e                       pop        esi
00a54f35  40                       inc        eax
00a54f36  5b                       pop        ebx
00a54f37  5d                       pop        ebp
00a54f38  c3                       ret        
