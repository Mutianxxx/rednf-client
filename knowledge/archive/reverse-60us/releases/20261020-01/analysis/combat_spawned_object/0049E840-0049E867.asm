0049e840  55                       push       ebp
0049e841  8bec                     mov        ebp, esp
0049e843  6aff                     push       -1
0049e845  681a6bc500               push       0xc56b1a
0049e84a  64a100000000             mov        eax, dword ptr fs:[0]
0049e850  50                       push       eax
0049e851  64892500000000           mov        dword ptr fs:[0], esp
0049e858  83ec10                   sub        esp, 0x10
0049e85b  8b4508                   mov        eax, dword ptr [ebp + 8]
0049e85e  53                       push       ebx
0049e85f  50                       push       eax
0049e860  8bd9                     mov        ebx, ecx
0049e862  e8b9a8ffff               call       0x499120