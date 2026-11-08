00484670  8b01                     mov        eax, dword ptr [ecx]
00484672  ff9008020000             call       dword ptr [eax + 0x208]
00484678  33c9                     xor        ecx, ecx
0048467a  85c0                     test       eax, eax
0048467c  0f9fc1                   setg       cl
0048467f  8ac1                     mov        al, cl
00484681  c3                       ret        
