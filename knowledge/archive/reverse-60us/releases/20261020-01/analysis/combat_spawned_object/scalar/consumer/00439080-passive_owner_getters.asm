00439080  8b8130050000             mov        eax, dword ptr [ecx + 0x530]
00439086  c3                       ret        
00439087  cc                       int3       
00439088  cc                       int3       
00439089  cc                       int3       
0043908a  cc                       int3       
0043908b  cc                       int3       
0043908c  cc                       int3       
0043908d  cc                       int3       
0043908e  cc                       int3       
0043908f  cc                       int3       
00439090  56                       push       esi
00439091  8bf1                     mov        esi, ecx
00439093  8b06                     mov        eax, dword ptr [esi]
00439095  ff908c010000             call       dword ptr [eax + 0x18c]
0043909b  85c0                     test       eax, eax
0043909d  7504                     jne        0x4390a3
0043909f  32c0                     xor        al, al
004390a1  5e                       pop        esi
004390a2  c3                       ret        
004390a3  8b16                     mov        edx, dword ptr [esi]
004390a5  8bce                     mov        ecx, esi
004390a7  ff928c010000             call       dword ptr [edx + 0x18c]
004390ad  8b10                     mov        edx, dword ptr [eax]
004390af  8bc8                     mov        ecx, eax
004390b1  5e                       pop        esi
004390b2  ffa2bc010000             jmp        dword ptr [edx + 0x1bc]