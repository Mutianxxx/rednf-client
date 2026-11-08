004869d0  55                       push       ebp
004869d1  8bec                     mov        ebp, esp
004869d3  51                       push       ecx
004869d4  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
004869da  85c0                     test       eax, eax
004869dc  741e                     je         0x4869fc
004869de  8b911c020000             mov        edx, dword ptr [ecx + 0x21c]
004869e4  2bd0                     sub        edx, eax
004869e6  b8398ee338               mov        eax, 0x38e38e39
004869eb  f7ea                     imul       edx
004869ed  c1fa03                   sar        edx, 3
004869f0  8bc2                     mov        eax, edx
004869f2  c1e81f                   shr        eax, 0x1f
004869f5  03c2                     add        eax, edx
004869f7  8945fc                   mov        dword ptr [ebp - 4], eax
004869fa  7506                     jne        0x486a02
004869fc  33c0                     xor        eax, eax
004869fe  8be5                     mov        esp, ebp
00486a00  5d                       pop        ebp
00486a01  c3                       ret        
00486a02  8b8128020000             mov        eax, dword ptr [ecx + 0x228]
00486a08  85c0                     test       eax, eax
00486a0a  56                       push       esi
00486a0b  7504                     jne        0x486a11
00486a0d  33f6                     xor        esi, esi
00486a0f  eb19                     jmp        0x486a2a
00486a11  8b912c020000             mov        edx, dword ptr [ecx + 0x22c]
00486a17  2bd0                     sub        edx, eax
00486a19  b8398ee338               mov        eax, 0x38e38e39
00486a1e  f7ea                     imul       edx
00486a20  c1fa03                   sar        edx, 3
00486a23  8bf2                     mov        esi, edx
00486a25  c1ee1f                   shr        esi, 0x1f
00486a28  03f2                     add        esi, edx
00486a2a  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
00486a30  85c0                     test       eax, eax
00486a32  750d                     jne        0x486a41
00486a34  8bc6                     mov        eax, esi
00486a36  33c9                     xor        ecx, ecx
00486a38  33d2                     xor        edx, edx
00486a3a  f7f1                     div        ecx
00486a3c  5e                       pop        esi
00486a3d  8be5                     mov        esp, ebp
00486a3f  5d                       pop        ebp
00486a40  c3                       ret        
00486a41  8b891c020000             mov        ecx, dword ptr [ecx + 0x21c]
00486a47  2bc8                     sub        ecx, eax
00486a49  b8398ee338               mov        eax, 0x38e38e39
00486a4e  f7e9                     imul       ecx
00486a50  c1fa03                   sar        edx, 3
00486a53  8bca                     mov        ecx, edx
00486a55  c1e91f                   shr        ecx, 0x1f
00486a58  03ca                     add        ecx, edx
00486a5a  8bc6                     mov        eax, esi
00486a5c  33d2                     xor        edx, edx
00486a5e  f7f1                     div        ecx
00486a60  5e                       pop        esi
00486a61  8be5                     mov        esp, ebp
00486a63  5d                       pop        ebp
00486a64  c3                       ret        
