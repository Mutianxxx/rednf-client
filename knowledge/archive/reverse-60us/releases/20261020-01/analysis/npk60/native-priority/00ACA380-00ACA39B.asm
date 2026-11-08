00aca380  55                       push       ebp
00aca381  8bec                     mov        ebp, esp
00aca383  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00aca386  8b4508                   mov        eax, dword ptr [ebp + 8]
00aca389  c1e104                   shl        ecx, 4
00aca38c  50                       push       eax
00aca38d  81c160ab0d01             add        ecx, 0x10dab60
00aca393  e828fdffff               call       0xaca0c0
00aca398  5d                       pop        ebp
00aca399  c3                       ret        
00aca39a  cc                       int3       