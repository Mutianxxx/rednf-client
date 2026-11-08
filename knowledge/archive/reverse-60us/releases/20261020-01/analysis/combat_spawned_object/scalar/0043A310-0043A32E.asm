0043a310  8b8150100000             mov        eax, dword ptr [ecx + 0x1050]
0043a316  85c0                     test       eax, eax
0043a318  7411                     je         0x43a32b
0043a31a  8b903c020000             mov        edx, dword ptr [eax + 0x23c]
0043a320  33c9                     xor        ecx, ecx
0043a322  83fa0a                   cmp        edx, 0xa
0043a325  0f94c1                   sete       cl
0043a328  8ac1                     mov        al, cl
0043a32a  c3                       ret        
0043a32b  32c0                     xor        al, al
0043a32d  c3                       ret        