00486a70  8b8118020000             mov        eax, dword ptr [ecx + 0x218]
00486a76  85c0                     test       eax, eax
00486a78  7504                     jne        0x486a7e
00486a7a  6bc00e                   imul       eax, eax, 0xe
00486a7d  c3                       ret        
00486a7e  8b891c020000             mov        ecx, dword ptr [ecx + 0x21c]
00486a84  2bc8                     sub        ecx, eax
00486a86  b8398ee338               mov        eax, 0x38e38e39
00486a8b  f7e9                     imul       ecx
00486a8d  c1fa03                   sar        edx, 3
00486a90  8bc2                     mov        eax, edx
00486a92  c1e81f                   shr        eax, 0x1f
00486a95  03c2                     add        eax, edx
00486a97  6bc00e                   imul       eax, eax, 0xe
00486a9a  c3                       ret        
