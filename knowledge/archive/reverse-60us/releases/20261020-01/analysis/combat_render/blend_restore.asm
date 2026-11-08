004010b0 55                       push       ebp
004010b1 8bec                     mov        ebp, esp
004010b3 8b4508                   mov        eax, dword ptr [ebp + 8]
004010b6 85c0                     test       eax, eax
004010b8 7c28                     jl         0x4010e2
004010ba 83f804                   cmp        eax, 4
004010bd 7e16                     jle        0x4010d5
004010bf 83f805                   cmp        eax, 5
004010c2 751e                     jne        0x4010e2
004010c4 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
004010ca 6a00                     push       0
004010cc 6a00                     push       0
004010ce e8fd737000               call       0xb084d0
004010d3 5d                       pop        ebp
004010d4 c3                       ret        
004010d5 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
004010db 6a00                     push       0
004010dd e8ce737000               call       0xb084b0
004010e2 5d                       pop        ebp
004010e3 c3                       ret        