00486ca0  55                       push       ebp
00486ca1  8bec                     mov        ebp, esp
00486ca3  51                       push       ecx
00486ca4  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
00486caa  85c0                     test       eax, eax
00486cac  741e                     je         0x486ccc
00486cae  8b911c020000             mov        edx, dword ptr [ecx + 0x21c]
00486cb4  2bd0                     sub        edx, eax
00486cb6  b8398ee338               mov        eax, 0x38e38e39
00486cbb  f7ea                     imul       edx
00486cbd  c1fa03                   sar        edx, 3
00486cc0  8bc2                     mov        eax, edx
00486cc2  c1e81f                   shr        eax, 0x1f
00486cc5  03c2                     add        eax, edx
00486cc7  8945fc                   mov        dword ptr [ebp - 4], eax
00486cca  750c                     jne        0x486cd8
00486ccc  33c0                     xor        eax, eax
00486cce  8d0440                   lea        eax, [eax + eax*2]
00486cd1  c1e002                   shl        eax, 2
00486cd4  8be5                     mov        esp, ebp
00486cd6  5d                       pop        ebp
00486cd7  c3                       ret        
00486cd8  8b8918020000             mov        ecx, dword ptr [ecx + 0x218]
00486cde  8b5118                   mov        edx, dword ptr [ecx + 0x18]
00486ce1  85d2                     test       edx, edx
00486ce3  74e7                     je         0x486ccc
00486ce5  8b411c                   mov        eax, dword ptr [ecx + 0x1c]
00486ce8  2bc2                     sub        eax, edx
00486cea  c1f804                   sar        eax, 4
00486ced  8d0440                   lea        eax, [eax + eax*2]
00486cf0  c1e002                   shl        eax, 2
00486cf3  8be5                     mov        esp, ebp
00486cf5  5d                       pop        ebp
00486cf6  c3                       ret        
