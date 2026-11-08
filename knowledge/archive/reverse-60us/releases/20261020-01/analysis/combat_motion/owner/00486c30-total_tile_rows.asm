00486c30  55                       push       ebp
00486c31  8bec                     mov        ebp, esp
00486c33  51                       push       ecx
00486c34  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
00486c3a  85c0                     test       eax, eax
00486c3c  56                       push       esi
00486c3d  741e                     je         0x486c5d
00486c3f  8b911c020000             mov        edx, dword ptr [ecx + 0x21c]
00486c45  2bd0                     sub        edx, eax
00486c47  b8398ee338               mov        eax, 0x38e38e39
00486c4c  f7ea                     imul       edx
00486c4e  c1fa03                   sar        edx, 3
00486c51  8bc2                     mov        eax, edx
00486c53  c1e81f                   shr        eax, 0x1f
00486c56  03c2                     add        eax, edx
00486c58  8945fc                   mov        dword ptr [ebp - 4], eax
00486c5b  7512                     jne        0x486c6f
00486c5d  33f6                     xor        esi, esi
00486c5f  e86cfdffff               call       0x4869d0
00486c64  8d0c80                   lea        ecx, [eax + eax*4]
00486c67  8d044e                   lea        eax, [esi + ecx*2]
00486c6a  5e                       pop        esi
00486c6b  8be5                     mov        esp, ebp
00486c6d  5d                       pop        ebp
00486c6e  c3                       ret        
00486c6f  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
00486c75  8b5018                   mov        edx, dword ptr [eax + 0x18]
00486c78  85d2                     test       edx, edx
00486c7a  74e1                     je         0x486c5d
00486c7c  8b701c                   mov        esi, dword ptr [eax + 0x1c]
00486c7f  2bf2                     sub        esi, edx
00486c81  c1fe04                   sar        esi, 4
00486c84  e847fdffff               call       0x4869d0
00486c89  8d0c80                   lea        ecx, [eax + eax*4]
00486c8c  8d044e                   lea        eax, [esi + ecx*2]
00486c8f  5e                       pop        esi
00486c90  8be5                     mov        esp, ebp
00486c92  5d                       pop        ebp
00486c93  c3                       ret        
