00726150  55                       push       ebp
00726151  8bec                     mov        ebp, esp
00726153  6aff                     push       -1
00726155  685113c700               push       0xc71351
0072615a  64a100000000             mov        eax, dword ptr fs:[0]
00726160  50                       push       eax
00726161  64892500000000           mov        dword ptr fs:[0], esp
00726168  81ec98070000             sub        esp, 0x798
0072616e  53                       push       ebx
0072616f  56                       push       esi
00726170  57                       push       edi
00726171  8bf1                     mov        esi, ecx
00726173  e85898d9ff               call       0x4bf9d0
00726178  8b86582b0000             mov        eax, dword ptr [esi + 0x2b58]